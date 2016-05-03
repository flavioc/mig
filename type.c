/*
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
 * All Rights Reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "global.h"
#include "type.h"
#include "message.h"

#if word_size_in_bits == 32
#define	word_size_name MACH_MSG_TYPE_INTEGER_32
#define	word_size_name_string "MACH_MSG_TYPE_INTEGER_32"
#else
#if word_size_in_bits == 64
#define	word_size_name MACH_MSG_TYPE_INTEGER_64
#define	word_size_name_string "MACH_MSG_TYPE_INTEGER_64"
#else
#error Unsupported word size!
#endif
#endif

ipc_type_t *itRetCodeType;	/* used for return codes */
ipc_type_t *itDummyType;	/* used for camelot dummy args */
ipc_type_t *itRequestPortType;	/* used for default Request port arg */
ipc_type_t *itZeroReplyPortType;/* used for dummy Reply port arg */
ipc_type_t *itRealReplyPortType;/* used for default Reply port arg */
ipc_type_t *itWaitTimeType;	/* used for dummy WaitTime args */
ipc_type_t *itMsgOptionType;	/* used for dummy MsgOption args */

/* Defines a symbol table.  */
typedef struct symbol_table {
	ipc_type_t *list;
} symbol_table_t;

static symbol_table_t type_table = {NULL};

static ipc_type_t *
tableLookUp(symbol_table_t *table, identifier_t name)
{
    ipc_type_t *it, **last;

    for (it = *(last = &table->list); it != itNULL;
			 it = *(last = &it->itNext))
	if (streql(name, it->itName))
	{
	    /* move this type to the front of the list */
	    *last = it->itNext;
	    it->itNext = table->list;
	    table->list = it;

	    return it;
	}

    return itNULL;
}

static void
tableInsert(symbol_table_t *table, identifier_t name, ipc_type_t *it)
{
    it->itName = name;
    it->itNext = table->list;
    table->list = it;
}

/*
 *  Searches for a named type.  We use a simple
 *  self-organizing linked list.
 */
ipc_type_t *
itLookUp(identifier_t name)
{
	return tableLookUp(&type_table, name);
}

/*
 *  Enters a new name-type association into
 *  our self-organizing linked list.
 */
void
itInsert(identifier_t name, ipc_type_t *it)
{
	tableInsert(&type_table, name, it);
}

static ipc_type_t *
itAlloc(void)
{
    static const ipc_type_t prototype =
    {
	strNULL,		/* identifier_t itName */
	0,			/* ipc_type_t *itNext */
	0,			/* u_int itTypeSize */
	0,			/* u_int itPadSize */
	0,			/* u_int itMinTypeSize */
	0,			/* u_int itInName */
	0,			/* u_int itOutName */
	0,			/* u_int itSize */
	1,			/* u_int itNumber */
	TRUE,			/* boolean_t itInLine */
	FALSE,			/* boolean_t itLongForm */
	d_NO,			/* dealloc_t itDeallocate */
	strNULL,		/* string_t itInNameStr */
	strNULL,		/* string_t itOutNameStr */
	flNone,			/* ipc_flags_t itFlags */
	TRUE,			/* boolean_t itStruct */
	FALSE,			/* boolean_t itString */
	FALSE,			/* boolean_t itVarArray */
	FALSE,			/* boolean_t itIndefinite */
	FALSE,			/* boolean_t itKernelPort */
	itNULL,			/* ipc_type_t *itElement */
	strNULL,		/* identifier_t itUserType */
	strNULL,		/* identifier_t itServerType */
	strNULL,		/* identifier_t itTransType */
	strNULL,		/* identifier_t itInTrans */
	strNULL,		/* identifier_t itInTransPayload */
	strNULL,		/* identifier_t itOutTrans */
	strNULL,		/* identifier_t itDestructor */
   0,      /* u_int itAlignment */
   CTYPE_NONE  /* C type constructor */
    };
    ipc_type_t *new;

    new = malloc(sizeof *new);
    if (new == itNULL)
	fatal("itAlloc(): %s", unix_error_string(errno));
    *new = prototype;
    return new;
}

/*
 * Convert an IPC type-name into a string.
 */
static string_t
itNameToString(u_int name)
{
    char buffer[100];

    (void) sprintf(buffer, "%u", name);
    return strmake(buffer);
}

static inline size_t
computeSizePadding(const size_t size, const size_t align)
{
   return (align - size % align) % align;
}

/*
 * Calculate itTypeSize, itPadSize, itMinTypeSize.
 * Every type needs this info; it is recalculated
 * when itInLine, itNumber, or itSize changes.
 */
static void
itCalculateSizeInfo(ipc_type_t *it)
{
    if (it->itInLine)
    {
	u_int bytes = (it->itNumber * it->itSize + 7) / 8;
	u_int padding = computeSizePadding(bytes, word_size);

	it->itTypeSize = bytes;
	it->itPadSize = padding;
	if (it->itVarArray)
	    it->itMinTypeSize = 0;
	else
	    it->itMinTypeSize = bytes + padding;
    }
    else
    {
	/* out-of-line, so use size of pointers */
	u_int bytes = sizeof_pointer;

	it->itTypeSize = bytes;
	it->itPadSize = 0;
	it->itMinTypeSize = bytes;
    }

    /* Unfortunately, these warning messages can't give a type name;
       we haven't seen a name yet (it might stay anonymous.) */

    if ((it->itNumber * it->itSize) % 8 != 0)
	warn("size of C types must be multiples of 8 bits");

    if ((it->itTypeSize == 0) && !it->itVarArray)
	warn("sizeof(%s) == 0", it->itName);
}

/*
 * Fill in default values for some fields used in code generation:
 *	itInNameStr, itOutNameStr, itUserType, itServerType, itTransType
 * Every argument's type should have these values filled in.
 */
static void
itCalculateNameInfo(ipc_type_t *it)
{
    if (it->itInNameStr == strNULL)
	it->itInNameStr = strmake(itNameToString(it->itInName));
    if (it->itOutNameStr == strNULL)
	it->itOutNameStr = strmake(itNameToString(it->itOutName));

    if (it->itUserType == strNULL)
	it->itUserType = it->itName;
    if (it->itServerType == strNULL)
	it->itServerType = it->itName;

    /*
     *	KernelServer and KernelUser interfaces get special treatment here.
     *	On the kernel side of the interface, ports are really internal
     *	port pointers (ipc_port_t), not port names (mach_port_t).
     *	At this point, we don't know if the argument is in or out,
     *	so we don't know if we should look at itInName or itOutName.
     *	Looking at both should be OK.
     *
     *	This is definitely a hack, but I think it is cleaner than
     *	mucking with type declarations throughout the kernel .def files,
     *	hand-conditionalizing on KERNEL_SERVER and KERNEL_USER.
     */

    if (IsKernelServer &&
	streql(it->itServerType, "mach_port_t") &&
	(((it->itInName == MACH_MSG_TYPE_POLYMORPHIC) &&
	  (it->itOutName == MACH_MSG_TYPE_POLYMORPHIC)) ||
	 MACH_MSG_TYPE_PORT_ANY(it->itInName) ||
	 MACH_MSG_TYPE_PORT_ANY(it->itOutName))) {
	it->itServerType = "ipc_port_t";
        it->itKernelPort = TRUE;
    } else if (IsKernelUser &&
	streql(it->itUserType, "mach_port_t") &&
	(((it->itInName == MACH_MSG_TYPE_POLYMORPHIC) &&
	  (it->itOutName == MACH_MSG_TYPE_POLYMORPHIC)) ||
	 MACH_MSG_TYPE_PORT_ANY(it->itInName) ||
	 MACH_MSG_TYPE_PORT_ANY(it->itOutName))) {
	it->itUserType = "ipc_port_t";
        it->itKernelPort = TRUE;
    } else
        it->itKernelPort = FALSE;

    if (it->itTransType == strNULL)
	it->itTransType = it->itServerType;
}

ipc_flags_t
itCheckFlags(ipc_flags_t flags, identifier_t name)
{
    /* only one of flLong and flNotLong */

    if ((flags&(flLong|flNotLong)) == (flLong|flNotLong)) {
	warn("%s: IsLong and IsNotLong cancel out", name);
	flags &= ~(flLong|flNotLong);
    }

    /* only one of flDealloc, flNotDealloc, flMaybeDealloc */

    if (flags & flMaybeDealloc) {
	if (flags & (flDealloc|flNotDealloc)) {
	    warn("%s: Dealloc and NotDealloc ignored with Dealloc[]", name);
	    flags &= ~(flDealloc|flNotDealloc);
	}
    }

    if ((flags&(flDealloc|flNotDealloc)) == (flDealloc|flNotDealloc)) {
	warn("%s: Dealloc and NotDealloc cancel out", name);
	flags &= ~(flDealloc|flNotDealloc);
    }

    return flags;
}

dealloc_t
itCheckDeallocate(const ipc_type_t *it, ipc_flags_t flags, dealloc_t dfault,
		  identifier_t name)
{
    dealloc_t dealloc = dfault;

    if (flags & flMaybeDealloc)
	dealloc = d_MAYBE;
    if (flags & flDealloc)
	dealloc = d_YES;
    if (flags & flNotDealloc)
	dealloc = d_NO;

    if (dealloc == dfault) {
	if (flags & flMaybeDealloc)
	    warn("%s: Dealloc[] is redundant", name);
	if (flags & flDealloc)
	    warn("%s: Dealloc is redundant", name);
	if (flags & flNotDealloc)
	    warn("%s: NotDealloc is redundant", name);
    }

    if (flags & (flMaybeDealloc|flDealloc|flNotDealloc)) {
	/* only give semantic warnings if the user specified something */

	if (dealloc != d_NO) {
	    if (it->itInLine && !it->itIndefinite)
		warn("%s: Dealloc will cause an IPC error", name);
	}
    }

    return dealloc;
}

static enum uselong { NotLong, CanBeLong, ShouldBeLong, MustBeLong, TooLong }
itUseLong(const ipc_type_t *it)
{
    enum uselong uselong = NotLong;

    if ((it->itInName == MACH_MSG_TYPE_POLYMORPHIC) ||
	(it->itOutName == MACH_MSG_TYPE_POLYMORPHIC) ||
	it->itVarArray)
	uselong = CanBeLong;

    if ((it->itVarArray && !it->itInLine) || it->itIndefinite)
	uselong = ShouldBeLong;

    if (((it->itInName != MACH_MSG_TYPE_POLYMORPHIC) &&
	 (it->itInName >= (1<<8))) ||
	((it->itOutName != MACH_MSG_TYPE_POLYMORPHIC) &&
	 (it->itOutName >= (1<<8))) ||
	(it->itSize >= (1<<8)) ||
	(it->itNumber >= (1<<12)))
	uselong = MustBeLong;

    if (((it->itInName != MACH_MSG_TYPE_POLYMORPHIC) &&
	 (it->itInName >= (1<<16))) ||
	((it->itOutName != MACH_MSG_TYPE_POLYMORPHIC) &&
	 (it->itOutName >= (1<<16))) ||
	(it->itSize >= (1<<16)))
	uselong = TooLong;

    return uselong;
}

boolean_t
itCheckIsLong(const ipc_type_t *it, ipc_flags_t flags, boolean_t dfault,
	      identifier_t name)
{
    boolean_t islong = dfault;

    if (flags & flLong)
	islong = TRUE;
    if (flags & flNotLong)
	islong = FALSE;

    if (islong == dfault) {
	if (flags & flLong)
	    warn("%s: IsLong is redundant", name);
	if (flags & flNotLong)
	    warn("%s: IsNotLong is redundant", name);
    }

    if (flags & (flLong|flNotLong)) {
	enum uselong uselong = itUseLong(it);

	/* only give semantic warnings if the user specified something */

	if (islong && ((int)uselong <= (int)NotLong))
	    warn("%s: doesn't need IsLong", name);
	if (!islong && ((int)uselong >= (int)MustBeLong))
	    warn("%s: too big for IsNotLong", name);
    }

    return islong;
}

static void
itRecomputeFlags(ipc_type_t *it, identifier_t name)
{
    /* process the IPC flag specification */
    enum uselong uselong;

    it->itFlags = itCheckFlags(it->itFlags, name);

    it->itDeallocate = itCheckDeallocate(it, it->itFlags, d_NO, name);

    uselong = itUseLong(it);
    if (uselong == TooLong)
	warn("%s: too big for mach_msg_type_long_t", name);
    it->itLongForm = itCheckIsLong(it, it->itFlags,
				   (int)uselong >= (int)ShouldBeLong, name);
}

/******************************************************
 *  Checks for non-implemented types, conflicting type
 *  flags and whether the long or short form of msg type
 *  descriptor is appropriate. Called after each type statement
 *  is parsed.
 ******************************************************/
static void
itCheckDecl(identifier_t name, ipc_type_t *it)
{
    it->itName = name;

    itCalculateNameInfo(it);

    /* do a bit of error checking, mostly necessary because of
       limitations in Mig */

    if (it->itVarArray) {
	if ((it->itInTrans != strNULL) ||
	    (it->itInTransPayload != strNULL) ||
	    (it->itOutTrans != strNULL))
	    error("%s: can't translate variable-sized arrays", name);

	if (it->itDestructor != strNULL)
	    error("%s: can't destroy variable-sized array", name);
    }

    if (it->itVarArray && it->itInLine) {
	if ((it->itElement->itUserType == strNULL) ||
	    (it->itElement->itServerType == strNULL))
	    error("%s: variable-sized in-line arrays need a named base type %s %s",
		  name, it->itElement->itUserType,
        it->itElement->itServerType);
    }

    itRecomputeFlags(it, name);
}

/*
 *  Pretty-prints translation/destruction/type information.
 */
static void
itPrintTrans(const ipc_type_t *it)
{
    if (!streql(it->itName, it->itUserType))
	printf("\tCUserType:\t%s\n", it->itUserType);

    if (!streql(it->itName, it->itServerType))
	printf("\tCServerType:\t%s\n", it->itServerType);

    if (it->itInTrans != strNULL)
       printf("\tInTran:\t\t%s %s(%s)\n",
	      it->itTransType, it->itInTrans, it->itServerType);

    if (it->itInTransPayload != strNULL)
       printf("\tInTranPayload:\t\t%s %s\n",
	      it->itTransType, it->itInTransPayload);

    if (it->itOutTrans != strNULL)
       printf("\tOutTran:\t%s %s(%s)\n",
	      it->itServerType, it->itOutTrans, it->itTransType);

    if (it->itDestructor != strNULL)
	printf("\tDestructor:\t%s(%s)\n", it->itDestructor, it->itTransType);
}

/*
 *  Pretty-prints type declarations.
 */
static void
itPrintDecl(identifier_t name, const ipc_type_t *it)
{
    printf("Type %s = ", name);
    if (!it->itInLine)
	printf("^ ");
    if (it->itVarArray)
	if (it->itNumber == 0 || it->itIndefinite)
	    printf("array [] of ");
	else
	    printf("array [*:%d] of ", it->itNumber);
    else if (it->itStruct && ((it->itNumber != 1) ||
			      (it->itInName == MACH_MSG_TYPE_STRING_C)))
	printf("struct [%d] of ", it->itNumber);
    else if (it->itNumber != 1)
	printf("array [%d] of ", it->itNumber);

    if (streql(it->itInNameStr, it->itOutNameStr))
	printf("(%s,", it->itInNameStr);
    else
	printf("(%s|%s", it->itInNameStr, it->itOutNameStr);

    printf(" %d%s%s)\n", it->itSize,	it->itLongForm ? ", IsLong" : "",
	   it->itDeallocate == d_YES ? ", Dealloc"
				     :it->itDeallocate == d_MAYBE ?", Dealloc[]"
								  : "");

    itPrintTrans(it);

    printf("\n");
}

/*
 *  Handles named type-specs, which can occur in type
 *  declarations or in argument lists.  For example,
 *	type foo = type-spec;	// itInsert will get called later
 *	routine foo(arg : bar = type-spec);	// itInsert won't get called
 */
void
itTypeDecl(identifier_t name, ipc_type_t *it)
{
    itCheckDecl(name, it);

    if (BeVerbose)
	itPrintDecl(name, it);
}

/*
 *  Handles declarations like
 *	type new = name;
 *	type new = inname|outname;
 */
ipc_type_t *
itShortDecl(u_int inname, const_string_t instr, u_int outname,
	    const_string_t outstr, u_int defsize)
{
    if (defsize == 0)
	error("must use full IPC type decl");

    return itLongDecl(inname, instr, outname, outstr, defsize, defsize, flNone);
}

/*
 *  Handles declarations like
 *	type new = (name, size, flags...)
 *	type new = (inname|outname, size, flags...)
 */
ipc_type_t *
itLongDecl(u_int inname, const_string_t instr, u_int outname,
	   const_string_t outstr, u_int defsize, u_int size, ipc_flags_t flags)
{
    ipc_type_t *it;

    if ((defsize != 0) && (defsize != size))
	warn("IPC type decl has strange size (%u instead of %u)",
	     size, defsize);

    it = itAlloc();
    it->itInName = inname;
    it->itInNameStr = instr;
    it->itOutName = outname;
    it->itOutNameStr = outstr;
    it->itSize = size;
    if (inname == MACH_MSG_TYPE_STRING_C)
    {
	it->itStruct = FALSE;
	it->itString = TRUE;
    }
    it->itFlags = flags;
    it->itAlignment = size/8;

    itCalculateSizeInfo(it);
    return it;
}

ipc_type_t *
itCopyType(const ipc_type_t *old)
{
    ipc_type_t *new = itAlloc();

    *new = *old;
    new->itName = strNULL;
    new->itNext = itNULL;
    new->itElement = (ipc_type_t *) old;

    /* size info still valid */
    return new;
}

ipc_type_t *
itCopyBuiltinType(const ipc_type_t *old)
{
   ipc_type_t *copy = itCopyType(old);
   copy->itName = old->itName;
   itCalculateNameInfo(copy);
   return copy;
}

/*
 * A call to itCopyType is almost always followed with itResetType.
 * The exception is itPrevDecl.  Also called before adding any new
 * translation/destruction/type info (see parser.y).
 *
 *	type new = old;	// new doesn't get old's info
 *	type new = array[*:10] of old;
 *			// new doesn't get old's info, but new->itElement does
 *	type new = array[*:10] of struct[3] of old;
 *			// new and new->itElement don't get old's info
 */

ipc_type_t *
itResetType(ipc_type_t *old)
{
    /* reset all special translation/destruction/type info */

    old->itInTrans = strNULL;
    old->itInTransPayload = strNULL;
    old->itOutTrans = strNULL;
    old->itDestructor = strNULL;
    old->itUserType = strNULL;
    old->itServerType = strNULL;
    old->itTransType = strNULL;
    return old;
}

/*
 *  Handles the declaration
 *	type new = old;
 */
ipc_type_t *
itPrevDecl(identifier_t name)
{
    ipc_type_t *old;

    old = itLookUp(name);
    if (old == itNULL)
    {
	error("type '%s' not defined", name);
	return itAlloc();
    }
    else
	return itCopyType(old);
}

void
itSetServerType(ipc_type_t *it, identifier_t server_type)
{
    if (it->itServerType != strNULL &&
        it->itServerType != it->itName && /* Default server type. */
        !streql(it->itServerType, server_type))
        warn("Conflicting server types (%s, %s)", it->itServerType,
            server_type);
    it->itServerType = server_type;
}

void
itSetUserType(ipc_type_t *it, identifier_t user_type)
{
    if (it->itUserType != strNULL &&
        it->itUserType != it->itName && /* Default user type. */
        !streql(it->itUserType, user_type))
        warn("Conflicting user types (%s, %s)", it->itUserType,
            user_type);
    it->itUserType = user_type;
}

void
itSetOutTrans(ipc_type_t *it, identifier_t out_trans)
{
    if (it->itOutTrans != strNULL && !streql(it->itOutTrans, out_trans))
        warn("Conflicting out-translation functions (%s, %s)",
            it->itOutTrans, out_trans);
	 it->itOutTrans = out_trans;
}

void
itSetInTrans(ipc_type_t *it, identifier_t in_trans)
{
    if (it->itInTrans != strNULL && !streql(it->itInTrans, in_trans))
        warn("Conflicting in-translation functions (%s, %s)",
            it->itInTrans, in_trans);
    it->itInTrans = in_trans;
}

void
itSetTransType(ipc_type_t *it, identifier_t trans_type)
{
    if (it->itTransType != strNULL &&
        it->itTransType != it->itName && /* Default type. */
        !streql(it->itTransType, trans_type))
        warn("Conflicting translation types (%s, %s)", it->itTransType,
            trans_type);
    it->itTransType = trans_type;
}

void
itSetInTransPayload(ipc_type_t *it, identifier_t in_trans_payload)
{
    if (it->itInTransPayload != strNULL &&
            !streql(it->itInTransPayload, in_trans_payload))
        warn("conflicting in-translation payload functions (%s, %s)",
             it->itInTransPayload, in_trans_payload);
    it->itInTransPayload = in_trans_payload;
}

void
itSetDestructor(ipc_type_t *it, identifier_t destructor)
{
    if (it->itDestructor != strNULL && !streql(it->itDestructor, destructor))
        warn("Conflicting destructor functions (%s, %s)", it->itDestructor,
            destructor);
    it->itDestructor = destructor;
}

/* Returns element type for strings. */
ipc_type_t *
itCreateStringElement()
{
    ipc_type_t *it = itShortDecl(MACH_MSG_TYPE_STRING_C,
          "MACH_MSG_TYPE_STRING_C",
          MACH_MSG_TYPE_STRING_C,
          "MACH_MSG_TYPE_STRING_C",
          8);
    itCheckDecl("char", it);
    return it;
}

/*
 * Allows a type to be set as a variable array even if it was turned into
 * a pointer before. This allows an array to be sent inline for up to
 * 'inlined_elements'. If 'indefinite' is set to TRUE, then the array can be
 * sent out-of-line if its size surpasses 'inlined_elements'.
 */
void
itSetAsVarArray(ipc_type_t *it, const size_t inlined_elements,
      const boolean_t indefinite)
{
    ipc_type_t *element = it->itElement;
    if (!element->itInLine || element->itVarArray)
         error("IPC type decl is too complicated");
    it->itNumber = inlined_elements * element->itNumber;
    it->itSize = element->itSize;
    it->itIndefinite = indefinite;
    it->itVarArray = TRUE;
    it->itStruct = FALSE;
    it->itInLine = TRUE;
    it->itAlignment = element->itAlignment;
    it->itString = element->itName != strNULL &&
        streql(element->itName, "char");
    if (it->itString) {
        free(element);
        it->itElement = itCreateStringElement();
        it->itTypeConstruct = CTYPE_STRING;
    }
    /* Flags may need to be recomputed since the sizes may have changed. */
    itRecomputeFlags(it, it->itName);

    itCalculateSizeInfo(it);
}

/*
 *  Handles the declarations
 *	type new = array[] of old;	// number is 0
 *	type new = array[*] of old;	// number is 0
 *	type new = array[*:number] of old;
 */
ipc_type_t *
itVarArrayDecl(u_int number, const ipc_type_t *old)
{
    ipc_type_t *it = itResetType(itCopyType(old));

    const boolean_t indefinite = number == 0;
    if (number == 0)
    {
        /* Compute the number of elements that can be sent using 2048 bytes. */
        const u_int bytes = (it->itNumber * it->itSize + 7) / 8;
        number = (2048 / bytes) * it->itNumber;
    }
    itSetAsVarArray(it, number, indefinite);

    return it;
}

/*
 *  Handles the declaration
 *	type new = array[number] of old;
 */
ipc_type_t *
itArrayDecl(u_int number, const ipc_type_t *old)
{
    ipc_type_t *it = itResetType(itCopyType(old));

    if (!it->itInLine || it->itVarArray)
	error("IPC type decl is too complicated");
    it->itNumber *= number;
    it->itStruct = FALSE;
    it->itString = FALSE;
    it->itAlignment = old->itAlignment;

    itCalculateSizeInfo(it);
    return it;
}

/*
 * Handles the declaration
 * typedef old new[N];
 */
ipc_type_t *
itCArrayDecl(const u_int number, ipc_type_t *old)
{
    if (streql(old->itName, "char")) {
        /* We delete the char type and create the string type. */
        free (old);
        ipc_type_t *it = itCStringDecl(number, FALSE);
        it->itTypeConstruct = CTYPE_STRING;
        return it;
   }
   ipc_type_t *it = itArrayDecl(number, old);
   it->itTypeConstruct = CTYPE_ARRAY;
   return it;
}

/*
 * Handles the declaration
 * typedef old new[];
 */
ipc_type_t *
itCVarArrayDecl(const ipc_type_t *old)
{
   ipc_type_t *it = itVarArrayDecl(0, old);
   it->itTypeConstruct = CTYPE_VARARRAY;
   return it;
}

/*
 *  Handles the declaration
 *	type new = ^ old;
 */
ipc_type_t *
itPtrDecl(ipc_type_t *it)
{
    if (!it->itInLine ||
	(it->itVarArray && !it->itIndefinite && (it->itNumber > 0)))
	error("IPC type decl is too complicated");
    it->itNumber = 0;
    it->itIndefinite = FALSE;
    it->itInLine = FALSE;
    it->itStruct = TRUE;
    it->itString = FALSE;
    it->itAlignment = word_size;

    itCalculateSizeInfo(it);
    return it;
}

/*
 * Handles the declaration
 * typedef old *new;
 */
ipc_type_t *
itCPtrDecl(ipc_type_t *it)
{
   ipc_type_t *ret = itVarArrayDecl(0, it);
   itPtrDecl(ret);
   ret->itTypeConstruct = CTYPE_POINTER;
   return ret;
}

/*
 *  Handles the declaration
 *	type new = struct[number] of old;
 */
ipc_type_t *
itStructDecl(u_int number, const ipc_type_t *old)
{
    ipc_type_t *it = itResetType(itCopyType(old));

    if (!it->itInLine || it->itVarArray)
	error("IPC type decl is too complicated");
    it->itNumber *= number;
    it->itStruct = TRUE;
    it->itString = FALSE;

    itCalculateSizeInfo(it);
    return it;
}

/*
 * Treat 'c_string[n]' as
 * 'array[n] of (MSG_TYPE_STRING_C, 8)'
 */
ipc_type_t *
itCStringDecl(u_int count, boolean_t varying)
{
    ipc_type_t *itElement = itCreateStringElement();
    ipc_type_t *it = itResetType(itCopyType(itElement));
    it->itNumber = count;
    it->itVarArray = varying;
    it->itStruct = FALSE;
    it->itString = TRUE;

    itCalculateSizeInfo(it);
    return it;
}

/* Creates a new MIG type based on a basic integral C type. */
static ipc_type_t *
itCIntTypeDecl(const_string_t ctype, const size_t size)
{
    ipc_type_t *it;
    switch (size) {
      case 1:
          it = itShortDecl(MACH_MSG_TYPE_CHAR, "MACH_MSG_TYPE_CHAR",
              MACH_MSG_TYPE_CHAR, "MACH_MSG_TYPE_CHAR", size * 8);
          break;
      case 2:
          it = itShortDecl(MACH_MSG_TYPE_INTEGER_16,
              "MACH_MSG_TYPE_INTEGER_16", MACH_MSG_TYPE_INTEGER_16,
              "MACH_MSG_TYPE_INTEGER_16", size * 8);
          break;
      case 4:
          it = itShortDecl(MACH_MSG_TYPE_INTEGER_32,
              "MACH_MSG_TYPE_INTEGER_32", MACH_MSG_TYPE_INTEGER_32,
              "MACH_MSG_TYPE_INTEGER_32", size * 8);
          break;
      case 8:
          it = itShortDecl(MACH_MSG_TYPE_INTEGER_64,
              "MACH_MSG_TYPE_INTEGER_64", MACH_MSG_TYPE_INTEGER_64,
              "MACH_MSG_TYPE_INTEGER_64", size * 8);
          break;
      default:
          fprintf(stderr, "Unrecognized size %zu for type %s\n", size, ctype);
          exit(EXIT_FAILURE);
    }
    it->itName = ctype;
    return it;
}

static ipc_type_t *
itInsertCType(const_string_t ctype, const size_t size)
{
    ipc_type_t *type = itCIntTypeDecl(ctype, size);
    type->itTypeConstruct = CTYPE_BASIC;
    itInsert(ctype, type);
}

ipc_type_t *
itMakeCountType(void)
{
    ipc_type_t *it = itAlloc();

    it->itName = "mach_msg_type_number_t";
    it->itInName = word_size_name;
    it->itInNameStr = word_size_name_string;
    it->itOutName = word_size_name;
    it->itOutNameStr = word_size_name_string;
    it->itSize = word_size_in_bits;

    itCalculateSizeInfo(it);
    itCalculateNameInfo(it);
    return it;
}

static ipc_type_t *
itMakeNaturalType(const char *name)
{
    ipc_type_t *it = itAlloc();

    it->itName = name;
    it->itInName = word_size_name;
    it->itInNameStr = word_size_name_string;
    it->itOutName = word_size_name;
    it->itOutNameStr = word_size_name_string;
    it->itSize = word_size_in_bits;

    itCalculateSizeInfo(it);
    itCalculateNameInfo(it);
    return it;
}

ipc_type_t *
itMakePolyType(void)
{
    ipc_type_t *it = itAlloc();

    it->itName = "mach_msg_type_name_t";
    it->itInName = word_size_name;
    it->itInNameStr = word_size_name_string;
    it->itOutName = word_size_name;
    it->itOutNameStr = word_size_name_string;
    it->itSize = word_size_in_bits;

    itCalculateSizeInfo(it);
    itCalculateNameInfo(it);
    return it;
}

ipc_type_t *
itMakeDeallocType(void)
{
    ipc_type_t *it = itAlloc();

    it->itName = "boolean_t";
    it->itInName = MACH_MSG_TYPE_BOOLEAN;
    it->itInNameStr = "MACH_MSG_TYPE_BOOLEAN";
    it->itOutName = MACH_MSG_TYPE_BOOLEAN;
    it->itOutNameStr = "MACH_MSG_TYPE_BOOLEAN";
    it->itSize = 32;

    itCalculateSizeInfo(it);
    itCalculateNameInfo(it);
    return it;
}

/*
 *  Initializes the pre-defined types.
 */
void
init_type(void)
{
    itRetCodeType = itAlloc();
    itRetCodeType->itName = "kern_return_t";
    itRetCodeType->itInName = MACH_MSG_TYPE_INTEGER_32;
    itRetCodeType->itInNameStr = "MACH_MSG_TYPE_INTEGER_32";
    itRetCodeType->itOutName = MACH_MSG_TYPE_INTEGER_32;
    itRetCodeType->itOutNameStr = "MACH_MSG_TYPE_INTEGER_32";
    itRetCodeType->itSize = 32;
    itCalculateSizeInfo(itRetCodeType);
    itCalculateNameInfo(itRetCodeType);

    itDummyType = itAlloc();
    itDummyType->itName = "char *";
    itDummyType->itInName = MACH_MSG_TYPE_UNSTRUCTURED;
    itDummyType->itInNameStr = "MACH_MSG_TYPE_UNSTRUCTURED";
    itDummyType->itOutName = MACH_MSG_TYPE_UNSTRUCTURED;
    itDummyType->itOutNameStr = "MACH_MSG_TYPE_UNSTRUCTURED";
    itDummyType->itSize = word_size_in_bits;
    itCalculateSizeInfo(itDummyType);
    itCalculateNameInfo(itDummyType);

    itRequestPortType = itAlloc();
    itRequestPortType->itName = "mach_port_t";
    itRequestPortType->itInName = MACH_MSG_TYPE_COPY_SEND;
    itRequestPortType->itInNameStr = "MACH_MSG_TYPE_COPY_SEND";
    itRequestPortType->itOutName = MACH_MSG_TYPE_PORT_SEND;
    itRequestPortType->itOutNameStr = "MACH_MSG_TYPE_PORT_SEND";
    itRequestPortType->itSize = word_size_in_bits;
    itCalculateSizeInfo(itRequestPortType);
    itCalculateNameInfo(itRequestPortType);

    itZeroReplyPortType = itAlloc();
    itZeroReplyPortType->itName = "mach_port_t";
    itZeroReplyPortType->itInName = 0;
    itZeroReplyPortType->itInNameStr = "0";
    itZeroReplyPortType->itOutName = 0;
    itZeroReplyPortType->itOutNameStr = "0";
    itZeroReplyPortType->itSize = word_size_in_bits;
    itCalculateSizeInfo(itZeroReplyPortType);
    itCalculateNameInfo(itZeroReplyPortType);

    itRealReplyPortType = itAlloc();
    itRealReplyPortType->itName = "mach_port_t";
    itRealReplyPortType->itInName = MACH_MSG_TYPE_MAKE_SEND_ONCE;
    itRealReplyPortType->itInNameStr = "MACH_MSG_TYPE_MAKE_SEND_ONCE";
    itRealReplyPortType->itOutName = MACH_MSG_TYPE_PORT_SEND_ONCE;
    itRealReplyPortType->itOutNameStr = "MACH_MSG_TYPE_PORT_SEND_ONCE";
    itRealReplyPortType->itSize = word_size_in_bits;
    itCalculateSizeInfo(itRealReplyPortType);
    itCalculateNameInfo(itRealReplyPortType);

    itWaitTimeType = itMakeNaturalType("mach_msg_timeout_t");
    itMsgOptionType = itMakeNaturalType("mach_msg_option_t");

    /* Define basic C integral types. */
    itInsertCType("char", sizeof_char);
    itInsertCType("unsigned char", sizeof_char);
    itInsertCType("short", sizeof_short);
    itInsertCType("unsigned short", sizeof_short);
    itInsertCType("int", sizeof_int);
    itInsertCType("unsigned int", sizeof_int);
    itInsertCType("long", sizeof_long);
    itInsertCType("unsigned long", sizeof_long);
    itInsertCType("long long", sizeof_long_long);
    itInsertCType("unsigned long long", sizeof_long_long);
}

/******************************************************
 *  Make sure return values of functions are assignable.
 ******************************************************/
void
itCheckReturnType(identifier_t name, const ipc_type_t *it)
{
    if (!it->itStruct)
	error("type of %s is too complicated", name);
    if ((it->itInName == MACH_MSG_TYPE_POLYMORPHIC) ||
	(it->itOutName == MACH_MSG_TYPE_POLYMORPHIC))
	error("type of %s can't be polymorphic", name);
}


/******************************************************
 *  Called by routine.c to check that request ports are
 *  simple and correct ports with send rights.
 ******************************************************/
void
itCheckRequestPortType(identifier_t name, const ipc_type_t *it)
{
    if (((it->itOutName != MACH_MSG_TYPE_PORT_SEND) &&
	 (it->itOutName != MACH_MSG_TYPE_PORT_SEND_ONCE) &&
	 (it->itOutName != MACH_MSG_TYPE_POLYMORPHIC)) ||
	(it->itNumber != 1) ||
	(it->itSize != word_size_in_bits) ||
	!it->itInLine ||
	it->itDeallocate != d_NO ||
	!it->itStruct ||
	it->itVarArray)
	error("argument %s isn't a proper request port", name);
}


/******************************************************
 *  Called by routine.c to check that reply ports are
 *  simple and correct ports with send rights.
 ******************************************************/
void
itCheckReplyPortType(identifier_t name, const ipc_type_t *it)
{
    if (((it->itOutName != MACH_MSG_TYPE_PORT_SEND) &&
	 (it->itOutName != MACH_MSG_TYPE_PORT_SEND_ONCE) &&
	 (it->itOutName != MACH_MSG_TYPE_POLYMORPHIC) &&
	 (it->itOutName != 0)) ||
	(it->itNumber != 1) ||
	(it->itSize != word_size_in_bits) ||
	!it->itInLine ||
	it->itDeallocate != d_NO ||
	!it->itStruct ||
	it->itVarArray)
	error("argument %s isn't a proper reply port", name);
}


/******************************************************
 *  Used by routine.c to check that WaitTime is a
 *  simple bit 32 integer.
 ******************************************************/
void
itCheckIntType(identifier_t name, const ipc_type_t *it)
{
    if ((it->itInName != MACH_MSG_TYPE_INTEGER_32) ||
	(it->itOutName != MACH_MSG_TYPE_INTEGER_32) ||
	(it->itNumber != 1) ||
	(it->itSize != 32) ||
	!it->itInLine ||
	it->itDeallocate != d_NO ||
	!it->itStruct ||
	it->itVarArray)
	error("argument %s isn't a proper integer", name);
}
void
itCheckNaturalType(name, it)
    identifier_t name;
    ipc_type_t *it;
{
    if ((it->itInName != word_size_name) ||
	(it->itOutName != word_size_name) ||
	(it->itNumber != 1) ||
	(it->itSize != word_size_in_bits) ||
	!it->itInLine ||
	it->itDeallocate != d_NO ||
	!it->itStruct ||
	it->itVarArray)
	error("argument %s should have been a %s", name, word_size_name_string);
}

/******************************************************
 *  Functions related to C-based structs.
 ******************************************************/

static symbol_table_t struct_union_table = {NULL};

void structRegister(identifier_t name, ipc_type_t *type)
{
    tableInsert(&struct_union_table, name, type);
}

ipc_type_t *
structLookUp(identifier_t name)
{
    return tableLookUp(&struct_union_table, name);
}

static ipc_type_t *
reverseTypeList(ipc_type_t *ls)
{
   ipc_type_t *res = itNULL;

   while (ls) {
      ipc_type_t *next = ls->itNext;
      ls->itNext = res;
      res = ls;
      ls = next;
   }
   return res;
}

ipc_type_t *
structCreateNew(identifier_t name, ipc_type_t *members, const CAttributes attrs)
{
	/* Number of bytes required to store the whole struct. */
	size_t total_size = 0;
	/* If all members of the struct have the same type,
	 * this is the number of smaller numbers required to represent
	 * the whole struct using the basic type. */
	size_t total_number = 0;

	boolean_t all_equal_names = TRUE;
	boolean_t all_equal_sizes = TRUE;
   size_t max_struct_alignment = 0;

   members = reverseTypeList(members);
	for (ipc_type_t *it = members; it != itNULL; it = it->itNext) {
		if (!it->itInLine)
		{
			/* This is a pointer so itSize will be 0.
			 * We must stop trying to find the right names and sizes and
			 * just use bytes instead.  */
			all_equal_names = FALSE;
			all_equal_sizes = FALSE;
			warn("using a pointer as a member of struct %s", name);
		}
      assert(it->itAlignment > 0);
      if (max_struct_alignment < it->itAlignment)
         max_struct_alignment = it->itAlignment;
      if (total_size % it->itAlignment != 0)
         total_size += computeSizePadding(total_size, it->itAlignment);
      total_size += it->itTypeSize;
		total_number += it->itNumber;
		if (it->itInName == MACH_MSG_TYPE_POLYMORPHIC ||
				it->itOutName == MACH_MSG_TYPE_POLYMORPHIC) {
			error("cannot have polymorphic types in structures");
		}
		if (all_equal_names) {
			if (members->itInName != it->itInName ||
					members->itOutName != it->itOutName) {
				all_equal_names = FALSE;
				if (members->itSize != it->itSize)
					all_equal_sizes = FALSE;
			}
		} else if (all_equal_sizes) {
			if (members->itSize != it->itSize)
				all_equal_sizes = FALSE;
		}
	}

	ipc_type_t *ret = itNULL;
	if (attrs.min_alignment == 0 && all_equal_names) {
		ret = itResetType(itCopyType(members));
		ret->itNumber = total_number;
	} else if (attrs.min_alignment == 0 && all_equal_sizes) {
		ret = itCIntTypeDecl(name, members->itSize / 8);
		ret->itNumber = total_number;
	} else {
		if (max_struct_alignment < attrs.min_alignment)
			max_struct_alignment = attrs.min_alignment;
      if (total_size % max_struct_alignment != 0)
         total_size += computeSizePadding(total_size, max_struct_alignment);
		ret = itCIntTypeDecl(name, 1);
		ret->itNumber = total_size;
	}

   ret->itAlignment = max_struct_alignment;
	ret->itStruct = TRUE;
	ret->itString = FALSE;

	itCalculateSizeInfo(ret);

	/* Free all members of the structure.  */
	while (members) {
		ipc_type_t *copy = members->itNext;
		free(members);
		members = copy;
	}
   ret->itTypeConstruct = CTYPE_STRUCT;

	return ret;
}

/******************************************************
 *  Functions related to C-based unions.
 ******************************************************/

ipc_type_t *
unionCreateNew(identifier_t name, ipc_type_t *members)
{
    assert(members != itNULL);

    ipc_type_t *largest_member = members;
    size_t largest_size;

    if (largest_member->itInLine) {
        largest_size = members->itSize * members->itNumber;
    } else {
       /* This is a pointer.  */
       warn("Pointer used in union %s", name);
       largest_size = word_size_in_bits;
    }

    /* Look for the largest member in the list of members.  */
    for (ipc_type_t *it = members->itNext; it != itNULL; it = it->itNext) {
        if (it->itInLine) {
            if (word_size_in_bits > largest_size) {
	        largest_size = word_size_in_bits;
		largest_member = it;
	    }
	} else {
	   warn("Pointer used in union %s", name);
	   if (it->itSize * it->itNumber > largest_size) {
	      largest_size = it->itSize * it->itNumber;
	      largest_member = it;
	   }
	}
    }

    /* Free all members of the structure.  */
    while (members) {
        ipc_type_t *copy = members->itNext;

	/* Keep the largest member since it will represent the union.  */
	if (members != largest_member)
	   free(members);

	members = copy;
    }

    largest_member->itNext = itNULL;
    if (!largest_member->itInLine) {
        /* If the largest member is a pointer, we turn it into a normal type.  */
        largest_member->itInLine = FALSE;
        largest_member->itSize = word_size_in_bits;
        largest_member->itNumber = 1;
    }
    largest_member->itTypeConstruct = CTYPE_UNION;
    return largest_member;
}

ipc_type_t*
unionLookUp(identifier_t name)
{
    return tableLookUp(&struct_union_table, name);
}

void unionRegister(identifier_t name, ipc_type_t *type)
{
    tableInsert(&struct_union_table, name, type);
}
