/* 
 * Mach Operating System
 * Copyright (c) 1992,1991,1990 Carnegie Mellon University
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

#ifndef	_TYPE_H
#define	_TYPE_H

#include <sys/types.h>

#include "boolean.h"
#include "mig_string.h"

typedef u_int ipc_flags_t;

#define	flNone		(0x00)
#define	flLong		(0x01)	/* IsLong specified */
#define	flNotLong	(0x02)	/* NotIsLong specified */
#define	flDealloc	(0x04)	/* Dealloc specified */
#define	flNotDealloc	(0x08)	/* NotDealloc specified */
#define	flMaybeDealloc	(0x10)	/* Dealloc[] specified */
#define	flServerCopy	(0x20)	/* ServerCopy specified */
#define	flCountInOut	(0x40)	/* CountInOut specified */

typedef enum dealloc {
	d_NO,			/* do not deallocate */
	d_YES,			/* always deallocate */
	d_MAYBE			/* deallocate according to parameter */
} dealloc_t;

/* Convert dealloc_t to TRUE/FALSE */
#define	strdealloc(d)	(strbool(d == d_YES))

typedef enum {
   CTYPE_NONE, /* Not a C Type at all. */
   CTYPE_BASIC, /* Includes basic types such as int. */
   CTYPE_STRUCT, /* Structures passed by value. */
   CTYPE_UNION, /* Unions passed by value. */
   CTYPE_POINTER, /* Simple pointers using *. */
   CTYPE_VARARRAY, /* Arrays using [] syntax. */
   CTYPE_ARRAY, /* Arrays using [N] syntax. */
   CTYPE_STRING, /* Char arrays using the char[N] syntax. */
	CTYPE_ENUM
} CTypeConstruct;

typedef struct {
    int min_alignment; /* Minimum alignment. */
} CAttributes;

inline CAttributes CAttributesDefault()
{
    CAttributes def;
	 def.min_alignment = 0;
	 return def;
}

/*
 * itName and itNext are internal fields (not used for code generation).
 * They are only meaningful for types entered into the symbol table.
 * The symbol table is a simple self-organizing linked list.
 *
 * The function itCheckDecl checks & fills in computed information.
 * Every type actually used (pointed at by argType) is so processed.
 *
 * The itInName, itOutName, itSize, itNumber, itInLine, itLongForm,
 * and itDeallocate fields correspond directly to mach_msg_type_t fields.
 * For out-of-line variable sized types, itNumber is zero.  For
 * in-line variable sized types, itNumber is the maximum size of the
 * array.  itInName is the msgt_name value supplied to the kernel,
 * and itOutName is the msgt_name value received from the kernel.
 * Either or both may be MACH_MSG_TYPE_POLYMORPHIC, indicating a
 * "polymorphic" msgt_name.  For itInName, this means the user
 * supplies the value with an argument.  For itOutName, this means the
 * the value is returned in an argument.
 *
 * The itInNameStr and itOutNameStr fields contain "printing" versions
 * of the itInName and itOutName values.  The mapping from number->string
 * is not into (eg, MACH_MSG_TYPE_UNSTRUCTURED/MACH_MSG_TYPE_BOOLEAN/
 * MACH_MSG_TYPE_BIT).  These fields are used for code-generation and
 * pretty-printing.
 *
 * itFlags contains the user's requests for itLongForm and itDeallocate
 * values.  itCheckDecl takes it into account when setting itLongForm
 * and itDeallocate, but they can be overridden (with a warning message).
 *
 * itTypeSize is the calculated size of the C type, in bytes.
 * itPadSize is the size of any padded needed after the data field.
 * itMinTypeSize is the minimum size of the data field, including padding.
 * For variable-length inline data, it is zero.
 *
 * itUserType, itServerType, itTransType are the C types used in
 * code generation.  itUserType is the C type passed to the user-side stub
 * and used for msg declarations in the user-side stub.  itServerType
 * is the C type used for msg declarations in the server-side stub.
 * itTransType is the C type passed to the server function by the
 * server-side stub.  Normally it differs from itServerType only when
 * translation functions are defined.
 *
 * itInTrans and itOutTrans are translation functions.  itInTrans
 * takes itServerType values and returns itTransType values.  itOutTrans
 * takes itTransType vaulues and returns itServerType values.
 * itDestructor is a finalization function applied to In arguments
 * after the server-side stub calls the server function.  It takes
 * itTransType values.  Any combination of these may be defined.
 *
 * The following type specification syntax modifies these values:
 *	type new = old
 *		ctype: name		// itUserType and itServerType
 *		cusertype: itUserType
 *		cservertype: itServerType
 *		intran: itTransType itInTrans(itServerType)
 *		intranpayload: itTransType itInTransPayload
 *		outtran: itServerType itOutTrans(itTransType)
 *		destructor: itDestructor(itTransType);
 *
 * At most one of itStruct and itString should be TRUE.  If both are
 * false, then this is assumed to be an array type (msg data is passed
 * by reference).  If itStruct is TRUE, then msg data is passed by value
 * and can be assigned with =.  If itString is TRUE, then the msg_data
 * is a null-terminated string, assigned with strncpy.  The itNumber
 * value is a maximum length for the string; the msg field always
 * takes up this much space.
 *
 * itVarArray means this is a variable-sized array.  If it is inline,
 * then itStruct and itString are FALSE.  If it is out-of-line, then
 * itStruct is TRUE (because pointers can be assigned).
 *
 * itIndefinite means this is an indefinite-length array - it may be sent
 * either inline or out-of-line.  itNumber is assigned so that at most
 * 2048 bytes are sent inline.
 *
 * itElement points to any substructure that the type may have.
 * It is only used with variable-sized array types.
 *
 * itKernelPort is used only on kernel interfaces and is set to TRUE when
 * the initial type is mach_port_t, which in turn is actually translated to
 * internal port pointers (ipc_port_t).
 */

typedef struct ipc_type
{
    identifier_t itName;	/* Mig's name for this type */
    struct ipc_type *itNext;	/* next type in symbol table */

    u_int itTypeSize;		/* size of the C type */
    u_int itPadSize;		/* amount of padding after data */
    u_int itMinTypeSize;	/* minimal amount of space occupied by data */

    u_int itInName;		/* name supplied to kernel in sent msg */
    u_int itOutName;		/* name in received msg */
    u_int itSize;
    u_int itNumber;
    boolean_t itInLine;
    boolean_t itLongForm;
    dealloc_t itDeallocate;

    const_string_t itInNameStr;	/* string form of itInName */
    const_string_t itOutNameStr;/* string form of itOutName */

    /* what the user wants, not necessarily what he gets */
    ipc_flags_t itFlags;

    boolean_t itStruct;
    boolean_t itString;
    boolean_t itVarArray;
    boolean_t itIndefinite;
    boolean_t itKernelPort;

    struct ipc_type *itElement;	/* may be NULL */

    identifier_t itUserType;
    identifier_t itServerType;
    identifier_t itTransType;

    identifier_t itInTrans;	/* may be NULL */
    identifier_t itInTransPayload;	/* may be NULL */
    identifier_t itOutTrans;	/* may be NULL */
    identifier_t itDestructor;	/* may be NULL */

    u_int itAlignment;  /* amount of alignment for this type in bytes */

    CTypeConstruct itTypeConstruct;  /* Type of C construct if any */
} ipc_type_t;

#define	itNULL		((ipc_type_t *) 0)

extern ipc_type_t *itLookUp(identifier_t name);
extern void itInsert(identifier_t name, ipc_type_t *it);
extern void itTypeDecl(identifier_t name, ipc_type_t *it);

extern ipc_type_t *itShortDecl(u_int inname, const_string_t instr,
			       u_int outname, const_string_t outstr,
			       u_int defsize);
extern ipc_type_t *itLongDecl(u_int inname, const_string_t instr,
			      u_int outname, const_string_t outstr,
			      u_int defsize, u_int size, ipc_flags_t flags);
extern ipc_type_t *itPrevDecl(identifier_t name);
extern ipc_type_t *itCopyType(const ipc_type_t *it);
extern ipc_type_t *itCopyBuiltinType(const ipc_type_t *it);
extern ipc_type_t *itResetType(ipc_type_t *it);
extern ipc_type_t *itVarArrayDecl(u_int number, const ipc_type_t *it);
extern void itSetAsVarArray(ipc_type_t *it, const size_t inlined_elements,
      const boolean_t indefinite);
extern void itSetServerType(ipc_type_t *it, identifier_t server_type);
extern void itSetUserType(ipc_type_t *it, identifier_t user_type);
extern void itSetInTrans(ipc_type_t *it, identifier_t in_trans);
extern void itSetOutTrans(ipc_type_t *it, identifier_t out_trans);
extern void itSetTransType(ipc_type_t *it, identifier_t trans_type);
extern void itSetInTransPayload(ipc_type_t *it, identifier_t in_trans_payload);
extern void itSetDestructor(ipc_type_t *it, identifier_t destructor);
extern ipc_type_t *itArrayDecl(u_int number, const ipc_type_t *it);
extern ipc_type_t *itCArrayDecl(u_int number, ipc_type_t *it);
extern ipc_type_t *itCVarArrayDecl(const ipc_type_t *it);
extern ipc_type_t *itPtrDecl(ipc_type_t *it);
extern ipc_type_t *itCPtrDecl(ipc_type_t *it);
extern ipc_type_t *itStructDecl(u_int number, const ipc_type_t *it);
extern ipc_type_t *itCStringDecl(u_int number, boolean_t varying);

extern ipc_type_t *itRetCodeType;
extern ipc_type_t *itDummyType;
extern ipc_type_t *itRequestPortType;
extern ipc_type_t *itZeroReplyPortType;
extern ipc_type_t *itRealReplyPortType;
extern ipc_type_t *itWaitTimeType;
extern ipc_type_t *itMsgOptionType;
extern ipc_type_t *itMakeCountType(void);
extern ipc_type_t *itMakePolyType(void);
extern ipc_type_t *itMakeDeallocType(void);

extern void init_type(void);

extern void itCheckReturnType(identifier_t name, const ipc_type_t *it);
extern void itCheckRequestPortType(identifier_t name, const ipc_type_t *it);
extern void itCheckReplyPortType(identifier_t name, const ipc_type_t *it);
extern void itCheckIntType(identifier_t name, const ipc_type_t *it);
extern void itCheckNaturalType(identifier_t name, ipc_type_t *it);


extern ipc_flags_t itCheckFlags(ipc_flags_t flags, identifier_t name);
extern dealloc_t itCheckDeallocate(const ipc_type_t *it, ipc_flags_t flags,
				   dealloc_t dfault, identifier_t name);
extern boolean_t itCheckIsLong(const ipc_type_t *it, ipc_flags_t flags,
			       boolean_t dfault, identifier_t name);

/* C structs related functions.  */

void structRegister(identifier_t name, ipc_type_t *it);
ipc_type_t* structLookUp(identifier_t name);
ipc_type_t* structCreateNew(identifier_t name, ipc_type_t *members, const CAttributes attr);

/* C unions related functions.  */

void unionRegister(identifier_t name, ipc_type_t *it);
ipc_type_t* unionCreateNew(identifier_t name, ipc_type_t *members);
ipc_type_t* unionLookUp(identifier_t name);

/* C enums related functions.  */

void enumRegister(identifier_t name, ipc_type_t *it);
ipc_type_t* enumCreateNew(identifier_t name);
ipc_type_t* enumLookUp(identifier_t name);

#endif	/* _TYPE_H */
