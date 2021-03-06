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
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS 
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
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

%token	sySkip
%token	syRoutine
%token	sySimpleRoutine

%token	sySubsystem
%token	syKernelUser
%token	syKernelServer

%token	syMsgOption
%token	syMsgSeqno
%token	syWaitTime
%token	syNoWaitTime
%token	syErrorProc
%token	syServerPrefix
%token	syUserPrefix
%token	syServerDemux
%token	syRCSId

%token	syImport
%token	syUImport
%token	sySImport

%token	syIn
%token	syOut
%token	syInOut
%token	syRequestPort
%token	syReplyPort
%token	sySReplyPort
%token	syUReplyPort

%token	syType
%token	syArray
%token	syStruct
%token	syOf

%token	syInTran
%token	syOutTran
%token	syDestructor
%token	syCType
%token	syCUserType
%token	syCServerType

%token	syCString

%token	syColon
%token	sySemi
%token	syComma
%token	syPlus
%token	syMinus
%token	syStar
%token	syDiv
%token	syLParen
%token	syRParen
%token	syEqual
%token	syDoubleEqual
%token	syCaret
%token	syTilde
%token	syLAngle
%token	syRAngle
%token	syLBrack
%token	syRBrack
%token	syLCrack
%token	syRCrack
%token	syBar
%token	syQuestion
%token	syRShift
%token	syLShift
%token	syAmper

%token	syTypedef
%token   syUnion

%token   syInline
%token   syInline2
%token   syHard
%token	syModType
%token   sySizeof
%token   syThreeDots
%token	syAttribute
%token	syASM
%token	syExtension
%token	syNoReturn
%token	syNoThrow
%token	syNonNull
%token	syAttrLeaf
%token	syAttrConst
%token	syRestrict
%token	syAligned
%token	syAlignOf
%token	syMode
%token	syTransUnion
%token	syModeQI
%token	syModeHI
%token	syModeSI
%token	syModeDI
%token	syModeByte
%token	syModeWord
%token	syModePointer
%token	syExtern
%token	syTypeof
%token	syStatic
%token	syVolatile
%token	syReturn
%token	syEnum
%token	syVoid
%token	syConst
%token	syCStringLiteral

%token	syError			/* lex error */

%token	<number>	syNumber
%token	<symtype>	sySymbolicType
%token	<identifier>	syIdentifier
%token	<string>	syString syQString
%token	<string>	syFileName
%token	<flag>		syIPCFlag
%token	<c_type>	syCTypeKeyword

%token	syInTranPayload

%right syQuestion syColon
%left	syDoubleEqual
%left	syPlus syMinus
%left syRShift syLShift
%left	syStar syDiv
%right syAmper
%left syBar

%type	<c_type> CTypeKeyword
%type	<identifier> IdentifierOrCTypeName TypeIdentifier VarName
%type	<identifier> DefineCType DefineUserType DefineServerType
%type	<statement_kind> ImportIndicant
%type	<number> VarArrayHead ArrayHead StructHead IntExp CArraySpec
%type	<number> CIntModeSize MoreVariableNames MoreVariableList
%type	<number> AlignParameter
%type	<type> NamedTypeSpec TransTypeSpec TypeSpec
%type	<type> CStringSpec BuiltinType TypedefConstruct
%type	<type> BasicTypeSpec PrevTypeSpec ArgumentType
%type	<type> CTypeSpec StructMember StructMembers
%type	<type> StructDef UnionDef SimpleUnion
%type <type> InlineDef TransModType ModTypeDecl
%type	<type> EnumDef SimpleEnum
%type	<nametype> CVarNameAndType CVarDeclNameAndType CVarDecl
%type	<symtype> PrimIPCType IPCType
%type	<routine> RoutineDecl Routine SimpleRoutine
%type	<direction> Direction
%type	<argument> Argument Arguments ArgumentList
%type	<flag> IPCFlags
%type	<cattr> Attributes ListOfAttributes CAttribute
%type	<cattr> CAttributeList CAttributeMember

%{

#include <assert.h>
#include <stdio.h>

#include "cpu.h"
#include "error.h"
#include "lexxer.h"
#include "global.h"
#include "mig_string.h"
#include "type.h"
#include "routine.h"
#include "statement.h"

static const char *import_name(statement_kind_t sk);

void
yyerror(const char *s)
{
    error("%s", s);
}

%}

%code requires {
   typedef enum {
       CTYPE_NOT_SET,
       CTYPE_INT,
       CTYPE_CHAR,
       CTYPE_FLOAT,
       CTYPE_DOUBLE
   } c_type_t;
}

%union
{
    u_int number;
    identifier_t identifier;
    const_string_t string;
    statement_kind_t statement_kind;
    ipc_type_t *type;
    CAttributes cattr;
    struct
    {
        identifier_t name;
        ipc_type_t *type;
    } nametype;
    struct
    {
	c_type_t basic_type;
	boolean_t is_short;
      	boolean_t is_signed;
      	boolean_t is_unsigned;
      	size_t long_count;
    } c_type;
    struct
    {
	u_int innumber;		/* msgt_name value, when sending */
	const_string_t instr;
	u_int outnumber;	/* msgt_name value, when receiving */
	const_string_t outstr;
	u_int size;		/* 0 means there is no default size */
    } symtype;
    routine_t *routine;
    arg_kind_t direction;
    argument_t *argument;
    ipc_flags_t flag;
}
%%

Statements		:	%empty
			|	Statements Statement
			;

Statement		:	Subsystem sySemi
			|	WaitTime sySemi
			|	MsgOption sySemi
			|	Error sySemi
			|	ServerPrefix sySemi
			|	UserPrefix sySemi
			|	ServerDemux sySemi
			|	TypeDecl sySemi
			|	Typedef sySemi
			|	TopLevelStructDef sySemi
			|	TopLevelEnumDef sySemi
			|	TopLevelTypeOf sySemi
			|	UnionDef sySemi
			|  InlineDef sySemi
			|	TopLevelCVarDecl sySemi
			|	TopLevelCDefinition
			|	ModTypeDecl sySemi
			|	RoutineDecl sySemi
{
    statement_t *st = stAlloc();

    st->stKind = skRoutine;
    st->stRoutine = $1;
    rtCheckRoutine($1);
    if (BeVerbose)
	rtPrintRoutine($1);
}
			|	sySkip sySemi
				{ rtSkip(1); }
			|	sySkip syNumber sySemi
				{ rtSkip($2); }
			|	Import sySemi
			|	RCSDecl sySemi
			|	sySemi
			|	error sySemi
				{ yyerrok; }
			;

Subsystem		:	SubsystemStart SubsystemMods
				SubsystemName SubsystemBase
{
    if (BeVerbose)
    {
	printf("Subsystem %s: base = %u%s%s\n\n",
	       SubsystemName, SubsystemBase,
	       IsKernelUser ? ", KernelUser" : "",
	       IsKernelServer ? ", KernelServer" : "");
    }
}
			;

SubsystemStart		:	sySubsystem
{
    if (SubsystemName != strNULL)
    {
	warn("previous Subsystem decl (of %s) will be ignored", SubsystemName);
	IsKernelUser = FALSE;
	IsKernelServer = FALSE;
	strfree((string_t) SubsystemName);
    }
}
			;

SubsystemMods		:	%empty
			|	SubsystemMods SubsystemMod
			;

SubsystemMod		:	syKernelUser
{
    if (IsKernelUser)
	warn("duplicate KernelUser keyword");
    IsKernelUser = TRUE;
}
			|	syKernelServer
{
    if (IsKernelServer)
	warn("duplicate KernelServer keyword");
    IsKernelServer = TRUE;
}
			;

SubsystemName		:	syIdentifier	{ SubsystemName = $1; }
			;

SubsystemBase		:	syNumber	{ SubsystemBase = $1; }
			;

MsgOption		:	LookString syMsgOption syString
{
    if (streql($3, "MACH_MSG_OPTION_NONE"))
    {
	MsgOption = strNULL;
	if (BeVerbose)
	    printf("MsgOption: canceled\n\n");
    }
    else
    {
	MsgOption = $3;
	if (BeVerbose)
	    printf("MsgOption %s\n\n",$3);
    }
}
			;

WaitTime		:	LookString syWaitTime syString
{
    WaitTime = $3;
    if (BeVerbose)
	printf("WaitTime %s\n\n", WaitTime);
}
			|	syNoWaitTime
{
    WaitTime = strNULL;
    if (BeVerbose)
	printf("NoWaitTime\n\n");
}
			;

Error			:	syErrorProc syIdentifier
{
    ErrorProc = $2;
    if (BeVerbose)
	printf("ErrorProc %s\n\n", ErrorProc);
}
			;

ServerPrefix		:	syServerPrefix syIdentifier
{
    ServerPrefix = $2;
    if (BeVerbose)
	printf("ServerPrefix %s\n\n", ServerPrefix);
}
			;

UserPrefix		:	syUserPrefix syIdentifier
{
    UserPrefix = $2;
    if (BeVerbose)
	printf("UserPrefix %s\n\n", UserPrefix);
}
			;

ServerDemux		:	syServerDemux syIdentifier
{
    ServerDemux = $2;
    if (BeVerbose)
	printf("ServerDemux %s\n\n", ServerDemux);
}
			;

Import			:	LookFileName ImportIndicant syFileName
{
    statement_t *st = stAlloc();
    st->stKind = $2;
    st->stFileName = $3;

    if (BeVerbose)
	printf("%s %s\n\n", import_name($2), $3);
}
			;

ImportIndicant		:	syImport	{ $$ = skImport; }
			|	syUImport	{ $$ = skUImport; }
			|	sySImport	{ $$ = skSImport; }
			;

RCSDecl			:	LookQString syRCSId syQString
{
    if (RCSId != strNULL)
	warn("previous RCS decl will be ignored");
    if (BeVerbose)
	printf("RCSId %s\n\n", $3);
    RCSId = $3;
}
			;

InlineDef   :  syInline syIdentifier syDiv IntExp
               {
                  ipc_type_t *it = itLookUp($2);
                  if (it == itNULL)
                     error("type %s could not be found", $2);
                  if (it->itTypeConstruct != CTYPE_POINTER)
                     error("type %s is not a pointer type", $2);
                  itSetAsVarArray(it, $4, TRUE);
               }
            |  syInline syHard syIdentifier syDiv IntExp
               {
                  ipc_type_t *it = itLookUp($3);
                  if (it == itNULL)
                     error("type %s could not be found", $3);
                  if (it->itTypeConstruct != CTYPE_POINTER)
                     error("type %s is not a pointer type", $3);
                  itSetAsVarArray(it, $5, FALSE);
               }
            ;

TopLevelTypeOf	:	syExtern syTypeof syLParen syIdentifier syRParen syIdentifier;

Typedef		:	TypedefQualifier syTypedef CVarQualifierList TypedefConstruct
			{
				identifier_t name = $4->itName;
				if (itLookUp(name) != itNULL)
					warn("overriding previous definition of %s", name);
				itInsert(name, $4);
			}
		;

TypedefQualifier	:	%empty
						|	syExtension
						;

TypedefConstruct	:	CVarDeclNameAndType
							{
								if ($1.type) {
									$$ = itResetType($1.type);
									itTypeDecl($1.name, $$);
								}
							}
						;

TypeDecl		:	syType NamedTypeSpec
{
    identifier_t name = $2->itName;

    if (itLookUp(name) != itNULL)
	warn("overriding previous definition of %s", name);
    itInsert(name, $2);
}
			;

TopLevelCDefinition	:	CVarQualifiers CFunctionDefinition
							|	CFunctionDefinition
							;

TopLevelCVarDecl	:	CVarDecl
							{ itFree($1.type); }
						;

CFunctionDefinition	:	CTypeSpec VarName CFunctionArgsBody
							;

CFunctionArgsBody	: CFunctionSpec Attributes syLCrack CFunctionBody syRCrack;

NamedTypeSpec		:	TypeIdentifier syEqual TransTypeSpec
				{ itTypeDecl($1, $$ = $3); }
				;

TopLevelStructDef	:	StructDef
						|	syStruct syIdentifier
						;

TopLevelEnumDef	:	EnumDef
						|	SimpleEnum
							{ itFree($1); }
						|	syEnum syIdentifier
							{
								if (enumLookUp($2) == itNULL) {
									ipc_type_t *en = enumCreateNew($2);
									enumRegister($2, en);
								}
							}
						;

TypeIdentifier		:	syIdentifier
				{ $$ = $1; }
			|	syCTypeKeyword
{
    if ($1.is_unsigned)
        $$ = "unsigned";
    else if ($1.is_signed)
        $$ = "signed";
    else if ($1.is_short)
        $$ = "short";
    else if ($1.long_count == 1)
        $$ = "long";
    else {
        switch ($1.basic_type) {
            case CTYPE_INT: $$ = "int"; break;
            case CTYPE_CHAR: $$ = "char"; break;
            case CTYPE_FLOAT: $$ = "float"; break;
            case CTYPE_DOUBLE: $$ = "double"; break;
            default: error("unrecognized C keyword"); break;
        }
    }
}
			;

TransTypeSpec		:	TypeSpec
				{ $$ = itResetType($1); }
			|	TransTypeSpec syInTran syColon IdentifierOrCTypeName
				syIdentifier syLParen IdentifierOrCTypeName syRParen 
				{
					$$ = $1;
					itSetTransType($$, $4);
					itSetInTrans($$, $5);
					itSetServerType($$, $7);
				}
			|	TransTypeSpec syInTranPayload syColon
				syIdentifier syIdentifier
				{
					$$ = $1;
					itSetTransType($$, $4);
					itSetInTransPayload($$, $5);
				}
			|	TransTypeSpec syOutTran syColon IdentifierOrCTypeName
				syIdentifier syLParen IdentifierOrCTypeName syRParen
				{
					$$ = $1;
					itSetServerType($$, $4);
					itSetOutTrans($$, $5);
					itSetTransType($$, $7);
				}
			|	TransTypeSpec syDestructor syColon syIdentifier
				syLParen IdentifierOrCTypeName syRParen
				{
					$$ = $1;
					itSetDestructor($$, $4);
					itSetTransType($$, $6);
				}
			|	TransTypeSpec DefineCType
				{
					$$ = $1;
					itSetUserType($$, $2);
					itSetServerType($$, $2);
				}
			|	TransTypeSpec DefineUserType
				{
					$$ = $1;
					itSetUserType($$, $2);
				}
			|	TransTypeSpec DefineServerType
				{
					$$ = $1;
					itSetServerType($$, $2);
				}
			;

ModTypeDecl	:	syModType TransModType
					{ $$ = $2; }
				;

TransModType	:	syIdentifier
						{
							$$ = itLookUp($1);
							if ($$ == itNULL)
								error("Type %s was not found", $1);
						}
					|	TransModType DefineCType
						{
							$$ = $1;
							itSetUserType($$, $2);
							itSetServerType($$, $2);
						}
					|	TransModType DefineUserType
						{
							$$ = $1;
							itSetUserType($$, $2);
						}
					|	TransModType DefineServerType
						{
							$$ = $1;
							itSetServerType($$, $2);
						}
					|	TransModType syDestructor syColon syIdentifier
						syLParen syIdentifier syRParen
						{
							$$ = $1;
							itSetDestructor($$, $4);
							itSetTransType($$, $6);
						}
					|	TransModType syOutTran syColon IdentifierOrCTypeName
						syIdentifier syLParen IdentifierOrCTypeName syRParen
						{
							$$ = $1;
							itSetServerType($$, $4);
							itSetOutTrans($$, $5);
							itSetTransType($$, $7);
						}
					|	TransModType syInTran syColon IdentifierOrCTypeName
						syIdentifier syLParen IdentifierOrCTypeName syRParen 
						{
							$$ = $1;
							itSetTransType($$, $4);
							itSetInTrans($$, $5);
							itSetServerType($$, $7);
						}
					|	TransModType syInTranPayload syColon
						syIdentifier syIdentifier
						{
							$$ = $1;
							itSetTransType($$, $4);
							itSetInTransPayload($$, $5);
						}
					;

DefineCType			:	syCType syColon IdentifierOrCTypeName
							{ $$ = $3; }
						;
DefineServerType	:	syCServerType syColon IdentifierOrCTypeName
							{ $$ = $3; }
						;
DefineUserType	:	syCUserType syColon IdentifierOrCTypeName
							{ $$ = $3; }
					;

IdentifierOrCTypeName		:	syIdentifier
				{ $$ = $1; }
			|	BuiltinType
				{ $$ = $1->itName; }
			;

TypeSpec		:	BasicTypeSpec
				{ $$ = $1; }
			|	CTypeSpec
				{ $$ = $1; }
			|	VarArrayHead TypeSpec
				{ $$ = itVarArrayDecl($1, $2); }
			|	ArrayHead TypeSpec
				{ $$ = itArrayDecl($1, $2); }
			|	syCaret TypeSpec
				{ $$ = itPtrDecl($2); }
			|	StructHead TypeSpec
				{ $$ = itStructDecl($1, $2); }
			|	CStringSpec
				{ $$ = $1; }
			;

/* This includes type definitions that are found in the C language.  */
CTypeSpec	:	PrevTypeSpec /* Type reuse.  */
					{ $$ = $1; }
				/* A builtin type based on unsigned/signed int/char/float.  */
				|	BuiltinType
					{ $$ = itCopyBuiltinType($1); }
				|	syVoid
					{ $$ = itMakeVoidType(); }
				|	syStruct syIdentifier
					{
						ipc_type_t *str = structLookUp($2);
						if (str == itNULL) {
							/* This may be used as a pointer. */
							$$ = itMakeVoidType();
						} else {
							$$ = itCopyType(str);
						}
					}
				|  StructDef
					{ $$ = itCopyType($1); }
				|	EnumDef
					{ $$ = itCopyType($1); }
				|	SimpleEnum
					{ $$ = enumCreateNew("(unnamed)"); }
				|	syStruct syLCrack StructMembers syRCrack
					{ $$ = structCreateNew("(unnamed)", $3, CAttributesDefault()); }
				|	syUnion syIdentifier
					{
						ipc_type_t *uni = unionLookUp($2);
						if (uni == itNULL)
							error("union %s is not defined", $2);
						$$ = itCopyType(uni);
					}
				|	UnionDef
					{ $$ = itCopyType($1); }
				|	SimpleUnion
					{	$$ = $1; }
				|	syEnum syIdentifier
					{
						ipc_type_t *en = enumLookUp($2);
						if (en == itNULL)
							error("enum %s is not defined", $2);
						$$ = itCopyType(en);
					}
				|	CTypeSpec syStar PointerOptions
					{
						$$ = itCPtrDecl($1);
					}
				;

PointerOptions	:	%empty
					|	syRestrict
					;

StructMembers  :  StructMember sySemi
						{ $$ = $1; }
					|	StructMembers StructMember sySemi
						{
							ipc_type_t *it = $2;
							while (it->itNext) {
								it = it->itNext;
							}
							it->itNext = $1;
							$$ = $2;
						}
					;

StructMember	:	CVarDecl MoreVariableNames
						{
							int i;
							$$ = $1.type;
							$1.type->itNext = itNULL;
							for (i = 0; i < $2; ++i) {
								ipc_type_t *new = itCloneType($1.type);
								new->itNext = $$;
								$$ = new;
							}
						}
					|	CVarDecl syColon syNumber syComma BitfieldNumbers
						{ $$ = $1.type; }
					| SimpleUnion
						{ $$ = $1;
							$$->itNext = itNULL; }
					;

/* Unnamed union such as union { ... }.  */
SimpleUnion		:	syUnion syLCrack StructMembers syRCrack
					{
						$$ = unionCreateNew("(unnamed)", $3);
					}
					;

MoreVariableNames	:	%empty { $$ = 0; }
						|	MoreVariableList { $$ = $1; }
						;

MoreVariableList	:	syComma syIdentifier { $$ = 1; }
					  	|	MoreVariableList syComma syIdentifier
							{ $$ = $1 + 1; }
						;

BitfieldNumbers	:	BitfieldNumber
						|	BitfieldNumbers syComma BitfieldNumber
						;

BitfieldNumber	:	syIdentifier syColon syNumber;

EnumList	:	EnumMember
			|	EnumList syComma EnumMember
			;

EnumMembers	:	EnumList OptionalComma
				;

EnumMember	:	syIdentifier
				|	syIdentifier syEqual EnumAssignment
				;

EnumAssignment	:	IntExp
					|	syIdentifier
					|	syLParen syIdentifier syBar syIdentifier syRParen /* Fix hack. */
					;

CVarDecl	:	CVarQualifiers CVarDeclNameAndType
				{ $$ = $2; }
			|	CVarDeclNameAndType
				{ $$ = $1; }
			;

CVarQualifierList	:	%empty
						|	CVarQualifiers
						;

CVarQualifiers		:	CVarQualifier
						|	CVarQualifiers CVarQualifier
						;

CVarQualifier	:	syExtern
					|	syInline2
					|  syStatic
					|	syVolatile
					|	syConst
					|	syExtension
					;

CVarDeclNameAndType	:	CVarNameAndType Attributes
								{
									$$ = $1;
									itSetCAttributes($1.type, $2);
								}
							|	CTypeSpec VarName CFunctionSpec Attributes
								{ $$.type = itNULL; $$.name = strNULL; }
							;

CVarNameAndType	:	CTypeSpec VarName
								{
									$$.type = $1;
									$$.name = $2;
								}
							|	CTypeSpec VarName CArraySpec
								{
									$$.type = itCArrayDecl($3, $1);
									$$.name = $2;
								}
							|	CTypeSpec VarName syLBrack syRBrack
								{
									$$.type = itCVarArrayDecl($1);
									$$.name = $2;
								}
							;

VarName	:	syIdentifier { $$ = $1; }
			|	syLParen VarName syRParen { $$ = $2; }
			;

EnumDef	:	syEnum syIdentifier syLCrack EnumMembers syRCrack
		  		{
					if (enumLookUp($2) != itNULL)
						error("enum %s is already defined", $2);
					$$ = enumCreateNew($2);
					enumRegister($2, $$);
				}
			;

OptionalComma	:	%empty
				  	|	syComma;

SimpleEnum	:	syEnum syLCrack EnumMembers syRCrack
					{ $$ = enumCreateNew("(unnamed)"); }
				;

StructDef	:	syStruct syIdentifier syLCrack StructMembers syRCrack Attributes
					{
						if (structLookUp($2) != itNULL)
							error("struct %s or struct is already defined", $2);
						$$ = structCreateNew($2, $4, $6);
						structRegister($2, $$);
					}
				;

Attributes	: ListOfAttributes
					{ $$ = $1; }
				 |  %empty
					{ $$ = CAttributesDefault(); }
				;

ListOfAttributes	:	CAttribute
							{ $$ = $1; }
						|	CAttribute ListOfAttributes
							{ $$ = CAttributesMerge($1, $2); }
						;

CAttribute	:	syAttribute syLParen syLParen CAttributeList  syRParen syRParen
					{ $$ = $4;; }
				|	syASM syLParen StringList syRParen
					{ $$ = CAttributesDefault(); }
				;

StringList	:	syCStringLiteral
				|	StringList syCStringLiteral
				;

CAttributeList	:	CAttributeMember
						{ $$ = $1; }
					|	CAttributeList syComma CAttributeMember
						{ $$ = CAttributesMerge($1, $3); }
					;

CAttributeMember	:	syAligned syLParen AlignParameter syRParen
							{
								$$ = CAttributesDefault();
								$$.min_alignment = $3;
							}
						|	syNonNull syLParen ListIntExp syRParen
							{ $$ = CAttributesDefault(); }
						|	syNoReturn
							{ $$ = CAttributesDefault(); }
						|	syNoThrow
							{ $$ = CAttributesDefault(); }
						|	syAttrLeaf
							{ $$ = CAttributesDefault(); }
						|	syAttrConst
							{ $$ = CAttributesDefault(); }
						|	syTransUnion
							{ $$ = CAttributesDefault(); }
						|	syMode syLParen CIntModeSize syRParen
							{
								$$ = CAttributesDefault();
								$$.force_int_size = 1;
							}
						;

AlignParameter	:	IntExp
						{ $$ = $1; }
					|	syAlignOf syLParen BuiltinType syRParen
						{ $$ = $3->itTypeSize; }
					;

CIntModeSize	:	syModeQI { $$ = 1; }
					|	syModeHI { $$ = 2; }
					|	syModeSI { $$ = 4; }
					|	syModeDI { $$ = 8; }
					|	syModeByte { $$ = 1; }
					|	syModeWord { $$ = word_size; }
					|	syModePointer { $$ = sizeof_pointer; }
					;

ListIntExp	:	IntExp
				|	ListIntExp syComma IntExp
				;

CArraySpec	:	syLBrack IntExp syRBrack
					{ $$ = $2; }
				|	CArraySpec syLBrack IntExp syRBrack
					{ $$ = $1 * $3; }
				;

CFunctionSpec	:	syLParen CFunctionArguments syRParen
					;

CFunctionArguments	:	%empty
							|	CFunctionList
							;

CFunctionList	:	CFunctionArgument
					|	CFunctionList syComma CFunctionArgument
					;

CFunctionArgument	:	CTypeSpec { itFree($1); }
						|	CVarDecl { itFree($1.type); }
						|	syThreeDots
						;

CFunctionBody	: syReturn VarName syLParen CCallArguments syRParen sySemi
					;

CCallArguments	:	%empty
					|	CCallArgumentList
					;

CCallArgumentList	:	CCallArgument
						|	CCallArgumentList syComma CCallArgument
						;

CCallArgument	:	VarName
					|	IntExp
					|	syStar CCallArgument
					|	syAmper CCallArgument
					;

UnionDef		:	syUnion syIdentifier syLCrack StructMembers syRCrack
					{
						if (unionLookUp($2) != itNULL)
							error("union or struct %s is already defined", $2);
						$$ = unionCreateNew($2, $4);
						unionRegister($2, $$);
					}
				;

BasicTypeSpec		:	IPCType
{
    $$ = itShortDecl($1.innumber, $1.instr,
		     $1.outnumber, $1.outstr,
		     $1.size);
}
			|	syLParen IPCType syComma IntExp
				IPCFlags syRParen
{
    $$ = itLongDecl($2.innumber, $2.instr,
		    $2.outnumber, $2.outstr,
		    $2.size, $4, $5);
}
			;

IPCFlags		:	%empty
				{ $$ = flNone; }
			|	IPCFlags syComma syIPCFlag
{
    if ($1 & $3)
	warn("redundant IPC flag ignored");
    else
	$$ = $1 | $3;
}
			|	IPCFlags syComma syIPCFlag syLBrack syRBrack
{
    if ($3 != flDealloc)
	warn("only Dealloc is variable");
    else
	$$ = $1 | flMaybeDealloc;
}
			;

PrimIPCType		:	syNumber
{
    $$.innumber = $$.outnumber = $1;
    $$.instr = $$.outstr = strNULL;
    $$.size = 0;
}
			|	sySymbolicType
				{ $$ = $1; }
			;

IPCType			:	PrimIPCType
				{ $$ = $1; }
			|	PrimIPCType syBar PrimIPCType
{
    if ($1.size != $3.size)
    {
	if ($1.size == 0)
	    $$.size = $3.size;
	else if ($3.size == 0)
	    $$.size = $1.size;
	else
	{
	    error("sizes in IPCTypes (%d, %d) aren't equal",
		  $1.size, $3.size);
	    $$.size = 0;
	}
    }
    else
	$$.size = $1.size;
    $$.innumber = $1.innumber;
    $$.instr = $1.instr;
    $$.outnumber = $3.outnumber;
    $$.outstr = $3.outstr;
}
			;

PrevTypeSpec		:	VarName
						{ $$ = itCopyIdentifier($1); }
						;

VarArrayHead		:	syArray syLBrack syRBrack syOf
				{ $$ = 0; }
			|	syArray syLBrack syStar syRBrack syOf
				{ $$ = 0; }
			|	syArray syLBrack syStar syColon IntExp 
				syRBrack syOf
				{ $$ = $5; }
			;

ArrayHead		:	syArray syLBrack IntExp syRBrack syOf
				{ $$ = $3; }
			;

StructHead		:	syStruct syLBrack IntExp syRBrack syOf
				{ $$ = $3; }
			;

CStringSpec		:	syCString syLBrack IntExp syRBrack
				{ $$ = itCStringDecl($3, FALSE); }
			|	syCString syLBrack syStar syColon
				IntExp syRBrack
				{ $$ = itCStringDecl($5, TRUE); }
			;

IntExp			: 	IntExp	syPlus	IntExp
				{ $$ = $1 + $3;	}
			| 	IntExp	syMinus	IntExp
				{ $$ = $1 - $3;	}
			|	IntExp	syStar	IntExp
				{ $$ = $1 * $3;	}
			| 	IntExp	syDiv	IntExp
				{ $$ = $1 / $3;	}
			|	IntExp syRShift IntExp
				{ $$ = $1 >> $3;	}
			|	IntExp syLShift IntExp
				{ $$ = $1 << $3;	}
			|	IntExp syAmper IntExp
				{ $$ = $1 & $3;	}
			|	IntExp syBar IntExp
				{ $$ = $1 | $3;	}
			|	sySizeof syLParen CTypeSpec syRParen
				{
					$$ = $3->itTypeSize;
					itFree($3);
				}
			|	syNumber
				{ $$ = $1;	}
         |  syLParen syCTypeKeyword syRParen IntExp %prec syAmper
            { $$ = $4; }
			|	syLParen IntExp syRParen
				{ $$ = $2;	}
			|	IntExp syDoubleEqual IntExp
				{ $$ = $1 == $3; }
			|	IntExp syQuestion IntExp syColon IntExp
				{
					if ($1)
						$$ = $3;
					else
						$$ = $5;
				}
			;

 
RoutineDecl		:	Routine			{ $$ = $1; }
			|	SimpleRoutine		{ $$ = $1; }
			;

Routine			:	syRoutine syIdentifier Arguments
				{ $$ = rtMakeRoutine($2, $3); }
			;

SimpleRoutine		:	sySimpleRoutine syIdentifier Arguments
				{ $$ = rtMakeSimpleRoutine($2, $3); }
			;

Arguments		:	syLParen syRParen
				{ $$ = argNULL; }
			|	syLParen ArgumentList syRParen
				{ $$ = $2; }

			;

ArgumentList		:	Argument
				{ $$ = $1; }
			|	Argument sySemi ArgumentList
{
    $$ = $1;
    $$->argNext = $3;
}
			;

Argument		:	Direction syIdentifier syColon ArgumentType IPCFlags
{
    $$ = argAlloc();
    $$->argKind = $1;
    $$->argName = $2;
    $$->argType = $4;
    $$->argFlags = $5;
}
			;

Direction		:	%empty	{ $$ = akNone; }
			|	syIn		{ $$ = akIn; }
			|	syOut		{ $$ = akOut; }
			|	syInOut		{ $$ = akInOut; }
			|	syRequestPort	{ $$ = akRequestPort; }
			|	syReplyPort	{ $$ = akReplyPort; }
			|	sySReplyPort	{ $$ = akSReplyPort; }
			|	syUReplyPort	{ $$ = akUReplyPort; }
			|	syWaitTime	{ $$ = akWaitTime; }
			|	syMsgOption	{ $$ = akMsgOption; }
			|	syMsgSeqno	{ $$ = akMsgSeqno; }
			;

ArgumentType		:	syIdentifier
{
    $$ = itLookUp($1);
    if ($$ == itNULL)
	error("type '%s' not defined", $1);
}
			|	BuiltinType
				{
					const identifier_t name = $1->itName;
					itTypeDecl(name, $$ = itCopyType($1));
				}
			|	NamedTypeSpec
				{ $$ = $1; }
			;

LookString		:	%empty
				{ LookString(); }
			;

LookFileName		:	%empty
				{ LookFileName(); }
			;

LookQString		:	%empty
				{ LookQString(); }
			;

BuiltinType		:	CTypeKeyword
				 	{
						char *type;
						switch ($1.basic_type) {
							case CTYPE_FLOAT:
								if ($1.is_short || $1.is_signed || $1.is_unsigned
									|| $1.long_count > 0) {
									error("invalid float qualifiers");
								}
								type = "float";
								break;
							case CTYPE_DOUBLE:
								if ($1.is_short || $1.is_signed || $1.is_unsigned
									|| $1.long_count > 1)
									error("invalid double qualifiers");
								if ($1.long_count == 1)
									type = "long double";
								else
									type = "double";
								break;
							case CTYPE_INT:
								if ($1.is_short) {
									if ($1.is_unsigned)
										type = "unsigned short";
									else
										type = "short";
								} else if ($1.long_count == 1) {
									if ($1.is_unsigned)
										type = "unsigned long";
									else
										type = "long";
								} else if ($1.long_count == 2) {
									if ($1.is_unsigned)
										type = "unsigned long long";
									else
										type = "long long";
								} else {
									if ($1.is_signed)
										type = "int";
									if ($1.is_unsigned)
										type = "unsigned int";
									else
										type = "int";
								}
								break;
							case CTYPE_CHAR:
								if ($1.is_unsigned)
									type = "unsigned char";
								else
									type = "char";
								break;
							case CTYPE_NOT_SET:
								if ($1.is_short) {
									if ($1.is_unsigned)
										type = "unsigned short";
									else
										type = "short";
								} else if ($1.long_count == 1) {
									if ($1.is_unsigned)
										type = "unsigned long";
									else
										type = "long";
								} else if ($1.long_count == 2) {
									if ($1.is_unsigned)
										type = "unsigned long long";
									else
										type = "long long";
								} else if ($1.is_signed) {
									type = "int";
								} else if ($1.is_unsigned) {
									type = "unsigned int";
								} else {
									error("invalid type");
								}
								break;
							default:
								error("invalid type");
								break;
						}
						assert(type);
						$$ = itLookUp(type);
						if (!$$)
							error("could not find type %s", type);
					}
				 ;

CTypeKeyword	:	syCTypeKeyword
					 	{ $$ = $1; }
						|	CTypeKeyword syCTypeKeyword
						{
							$$ = $1;
							if ($$.basic_type != CTYPE_NOT_SET)
								error("bad type declaration");
							$$.basic_type = $2.basic_type;
							$$.long_count += $2.long_count;
							if ($$.is_short && $2.is_short)
								error("short can be used twice");
							$$.is_short |= $2.is_short;
							if ($$.is_signed && $2.is_signed)
								error("signed cannot be used twice");
							$$.is_signed |= $2.is_signed;
							if ($$.is_unsigned && $2.is_unsigned)
								error("unsigned cannot be used twice");
							$$.is_unsigned |= $2.is_unsigned;
							if ($$.is_short && $$.long_count > 0)
								error("long and short used together");
							if ($$.is_signed && $$.is_unsigned)
								error("signed and unsigned used together");
							if ($$.long_count > 2)
								error("too many long qualifiers");
						}
						;
%%

static const char *
import_name(statement_kind_t sk)
{
    switch (sk)
    {
      case skImport:
	return "Import";
      case skSImport:
	return "SImport";
      case skUImport:
	return "UImport";
      default:
	fatal("import_name(%d): not import statement", (int) sk);
	/*NOTREACHED*/
    }
}
