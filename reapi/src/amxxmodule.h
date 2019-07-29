// vim: set ts=4 sw=4 tw=99 noet:
//
// AMX Mod X, based on AMX Mod by Aleksander Naszko ("OLO").
// Copyright (C) The AMX Mod X Development Team.
//
// This software is licensed under the GNU General Public License, version 3 or higher.
// Additional exceptions apply. For full license details, see LICENSE.txt or visit:
//     https://alliedmods.net/amxmodx-license
//

//
// Module SDK
//

// prevent double include
#ifndef __AMXXMODULE_H__
#define __AMXXMODULE_H__

// module interface version was 1
// 2 - added logtag to struct (amxx1.1-rc1)
// 3 - added new tagAMX structure (amxx1.5)
// 4 - added new 'library' setting for direct loading
#define AMXX_INTERFACE_VERSION 4

// amxx module info
struct amxx_module_info_s
{
	const char *name;
	const char *author;
	const char *version;
	int reload;		// reload on mapchange when nonzero
	const char *logtag;	// added in version 2
	const char *library;	// added in version 4
	const char *libclass;	// added in version 4
};

// return values from functions called by amxx
#define AMXX_OK					0			/* no error */
#define AMXX_IFVERS				1			/* interface version */
#define AMXX_PARAM				2			/* Invalid parameter */
#define AMXX_FUNC_NOT_PRESENT			3			/* Function not present */

#define AMXX_GAME_OK			0			/* This module can load on the current game mod. */
#define AMXX_GAME_BAD			1			/* This module can not load on the current game mod. */

// *** Small stuff ***
// The next section is copied from the amx.h file
// Copyright (c) ITB CompuPhase, 1997-2005

#if defined _LP64 || defined WIN64 || defined _WIN64
#if !defined __64BIT__
#define __64BIT__
#endif
#endif

/* calling convention for native functions */
#if !defined AMX_NATIVE_CALL
#define AMX_NATIVE_CALL EXT_FUNC
#endif
/* calling convention for all interface functions and callback functions */
#if !defined AMXAPI
#if defined STDECL
#define AMXAPI      STDECL
#elif defined CDECL
#define AMXAPI      CDECL
#else
#define AMXAPI
#endif
#endif
#if !defined AMXEXPORT
#define AMXEXPORT
#endif

#if !defined PAWN_CELL_SIZE
#define PAWN_CELL_SIZE 32     /* by default, use 32-bit cells */
#endif
#if PAWN_CELL_SIZE==16
typedef uint16  ucell;
typedef int16   cell;
#elif PAWN_CELL_SIZE==32
typedef uint32  ucell;
typedef int32   cell;
#define REAL	float
#elif PAWN_CELL_SIZE==64
typedef uint64  ucell;
typedef int64   cell;
#define REAL	double
#else
#error Unsupported cell size (PAWN_CELL_SIZE)
#endif

#define UNPACKEDMAX	((1 << (sizeof(cell) - 1) * 8) - 1)
#define UNLIMITED	(~1u >> 1)

struct tagAMX;
typedef cell(AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, cell *params);
typedef int (AMXAPI *AMX_CALLBACK)(struct tagAMX *amx, cell index, cell *result, cell *params);
typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
#if !defined _FAR
#define _FAR
#endif

#if defined _MSC_VER
#pragma warning(disable:4103)  /* disable warning message 4103 that complains
* about pragma pack in a header file */
#pragma warning(disable:4100)  /* "'%$S' : unreferenced formal parameter" */

#if _MSC_VER >= 1400
#if !defined NO_MSVC8_AUTO_COMPAT

/* Disable deprecation warnings concerning unsafe CRT functions */
#if !defined _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

/* Disable deprecation warnings because MSVC8 seemingly thinks the ISO C++ conformant
* functions above are deprecated. */
#pragma warning (disable:4996)

#endif
#else
#define vsnprintf _vsnprintf
#endif
#endif

/* Some compilers do not support the #pragma align, which should be fine. Some
* compilers give a warning on unknown #pragmas, which is not so fine...
*/
#if (defined SN_TARGET_PS2 || defined __GNUC__) && !defined AMX_NO_ALIGN
#define AMX_NO_ALIGN
#endif

#if defined __GNUC__
#define PACKED	__attribute__((packed))
#else
#define PACKED
#endif

#if !defined AMX_NO_ALIGN
#if defined LINUX || defined __FreeBSD__ || defined __APPLE__
#pragma pack(1)	/* structures must be packed (byte-aligned) */
#elif defined MACOS && defined __MWERKS__
#pragma options align=mac68k
#else
#pragma pack(push)
#pragma pack(1) /* structures must be packed (byte-aligned) */
#if defined __TURBOC__
#pragma option -a- /* "pack" pragma for older Borland compilers */
#endif
#endif
#endif

typedef struct
{
	const char _FAR *name PACKED;
	AMX_NATIVE func       PACKED;
} AMX_NATIVE_INFO;

#define AMX_USERNUM	4

/* The AMX structure is the internal structure for many functions. Not all
* fields are valid at all times; many fields are cached in local variables.
*/
typedef struct tagAMX
{
	unsigned char _FAR *base PACKED; /* points to the AMX header plus the code, optionally also the data */
	unsigned char _FAR *data PACKED; /* points to separate data+stack+heap, may be NULL */
	AMX_CALLBACK callback PACKED;
	AMX_DEBUG debug       PACKED; /* debug callback */
	/* for external functions a few registers must be accessible from the outside */
	cell cip              PACKED; /* instruction pointer: relative to base + amxhdr->cod */
	cell frm              PACKED; /* stack frame base: relative to base + amxhdr->dat */
	cell hea              PACKED; /* top of the heap: relative to base + amxhdr->dat */
	cell hlw              PACKED; /* bottom of the heap: relative to base + amxhdr->dat */
	cell stk              PACKED; /* stack pointer: relative to base + amxhdr->dat */
	cell stp              PACKED; /* top of the stack: relative to base + amxhdr->dat */
	int flags             PACKED; /* current status, see amx_Flags() */
	/* user data */
	long usertags[AMX_USERNUM] PACKED;
	//okay userdata[3] in AMX Mod X is for the CPlugin * pointer
	//we're also gonna set userdata[2] to a special debug structure
	void _FAR *userdata[AMX_USERNUM] PACKED;
	/* native functions can raise an error */
	int error             PACKED;
	/* passing parameters requires a "count" field */
	int paramcount;
	/* the sleep opcode needs to store the full AMX status */
	cell pri              PACKED;
	cell alt              PACKED;
	cell reset_stk        PACKED;
	cell reset_hea        PACKED;
	cell sysreq_d         PACKED; /* relocated address/value for the SYSREQ.D opcode */
	/* support variables for the JIT */
	int reloc_size        PACKED; /* required temporary buffer for relocations */
	long code_size        PACKED; /* estimated memory footprint of the native code */
} PACKED AMX;

/* The AMX_HEADER structure is both the memory format as the file format. The
* structure is used internaly.
*/
typedef struct tagAMX_HEADER
{
	int32 size          PACKED; /* size of the "file" */
	uint16 magic        PACKED; /* signature */
	char file_version;          /* file format version */
	char amx_version;           /* required version of the AMX */
	int16 flags         PACKED;
	int16 defsize       PACKED; /* size of a definition record */
	int32 cod           PACKED; /* initial value of COD - code block */
	int32 dat           PACKED; /* initial value of DAT - data block */
	int32 hea           PACKED; /* initial value of HEA - start of the heap */
	int32 stp           PACKED; /* initial value of STP - stack top */
	int32 cip           PACKED; /* initial value of CIP - the instruction pointer */
	int32 publics       PACKED; /* offset to the "public functions" table */
	int32 natives       PACKED; /* offset to the "native functions" table */
	int32 libraries     PACKED; /* offset to the table of libraries */
	int32 pubvars       PACKED; /* the "public variables" table */
	int32 tags          PACKED; /* the "public tagnames" table */
	int32 nametable     PACKED; /* name table */
} PACKED AMX_HEADER;

enum
{
	AMX_ERR_NONE,
	/* reserve the first 15 error codes for exit codes of the abstract machine */
	AMX_ERR_EXIT,         /* forced exit */
	AMX_ERR_ASSERT,       /* assertion failed */
	AMX_ERR_STACKERR,     /* stack/heap collision */
	AMX_ERR_BOUNDS,       /* index out of bounds */
	AMX_ERR_MEMACCESS,    /* invalid memory access */
	AMX_ERR_INVINSTR,     /* invalid instruction */
	AMX_ERR_STACKLOW,     /* stack underflow */
	AMX_ERR_HEAPLOW,      /* heap underflow */
	AMX_ERR_CALLBACK,     /* no callback, or invalid callback */
	AMX_ERR_NATIVE,       /* native function failed */
	AMX_ERR_DIVIDE,       /* divide by zero */
	AMX_ERR_SLEEP,        /* go into sleepmode - code can be restarted */
	AMX_ERR_INVSTATE,     /* invalid state for this access */

	AMX_ERR_MEMORY = 16,  /* out of memory */
	AMX_ERR_FORMAT,       /* invalid file format */
	AMX_ERR_VERSION,      /* file is for a newer version of the AMX */
	AMX_ERR_NOTFOUND,     /* function not found */
	AMX_ERR_INDEX,        /* invalid index parameter (bad entry point) */
	AMX_ERR_DEBUG,        /* debugger cannot run */
	AMX_ERR_INIT,         /* AMX not initialized (or doubly initialized) */
	AMX_ERR_USERDATA,     /* unable to set user data field (table full) */
	AMX_ERR_INIT_JIT,     /* cannot initialize the JIT */
	AMX_ERR_PARAMS,       /* parameter error */
	AMX_ERR_DOMAIN,       /* domain error, expression result does not fit in range */
};

#if !defined AMX_NO_ALIGN
#if defined(__linux__) || defined(__APPLE__)
#pragma pack() /* reset default packing */
#else
#pragma pack(pop) /* reset previous packing */
#endif
#endif

// *** Types ***
typedef void * (*PFN_REQ_FNPTR)(const char *name);

// ***** Module funcs stuff *****
enum ForwardExecType
{
	ET_IGNORE = 0,				// Ignore return vaue
	ET_STOP,					// Stop on PLUGIN_HANDLED
	ET_STOP2,					// Stop on PLUGIN_HANDLED, continue on other values, return biggest return value
	ET_CONTINUE,				// Continue; return biggest return value
};

enum ForwardParam
{
	FP_DONE = -1,				// specify this as the last argument
	// only tells the function that there are no more arguments
	FP_CELL,					// normal cell
	FP_FLOAT,					// float; used as normal cell though
	FP_STRING,					// string
	FP_STRINGEX,				// string; will be updated to the last function's value
	FP_ARRAY,					// array; use the return value of prepareArray.
};

enum PlayerProp
{
	Player_Name,			// String
	Player_Ip,				// String
	Player_Team,			// String
	Player_Ingame,			// bool
	Player_Authorized,		// bool
	Player_Vgui,			// bool
	Player_Time,			// float
	Player_Playtime,		// float
	Player_MenuExpire,		// float
	Player_Weapons,			// struct{int,int}[32]
	Player_CurrentWeapon,	// int
	Player_TeamID,			// int
	Player_Deaths,			// int
	Player_Aiming,			// int
	Player_Menu,			// int
	Player_Keys,			// int
	Player_Flags,			// int[32]
	Player_Newmenu,			// int
	Player_NewmenuPage,		// int
};

enum LibType
{
	LibType_Library,
	LibType_Class
};

#define STKMARGIN	((cell)(16 * sizeof(cell)))

#define MSGBLOCK_SET	0
#define MSGBLOCK_GET	1

#define BLOCK_NOT	0
#define BLOCK_ONCE	1
#define BLOCK_SET	2

typedef void(*AUTHORIZEFUNC)				(int player, const char *authstring);

typedef int(*PFN_ADD_NATIVES)				(const AMX_NATIVE_INFO *list);
typedef int(*PFN_ADD_NEW_NATIVES)			(const AMX_NATIVE_INFO *list);
typedef char*(*PFN_BUILD_PATHNAME)			(const char *format, ...);
typedef char*(*PFN_BUILD_PATHNAME_R)			(char *buffer, size_t maxlen, const char *format, ...);
typedef cell*(*PFN_GET_AMXADDR)				(AMX *amx, cell offset);
typedef cell*(*PFN_GET_AMXVECTOR_NULL)			(AMX *amx, cell offset);
typedef void(*PFN_PRINT_SRVCONSOLE)			(const char *format, ...);
typedef const char*(*PFN_GET_MODNAME)			(void);
typedef const char*(*PFN_GET_AMXSCRIPTNAME)		(int id);
typedef AMX*(*PFN_GET_AMXSCRIPT)			(int id);
typedef int(*PFN_FIND_AMXSCRIPT_BYAMX)			(const AMX *amx);
typedef int(*PFN_FIND_AMXSCRIPT_BYNAME)			(const char *name);
typedef int(*PFN_SET_AMXSTRING)				(AMX *amx, cell amx_addr, const char *source, int max);
typedef int(*PFN_SET_AMXSTRING_UTF8_CHAR)		(AMX *amx, cell amx_addr, const char *source, size_t sourcelen, size_t maxlen);
typedef int(*PFN_SET_AMXSTRING_UTF8_CELL)		(AMX *amx, cell amx_addr, const cell *source, size_t sourcelen, size_t maxlen);
typedef char*(*PFN_GET_AMXSTRING)			(AMX *amx, cell amx_addr, int bufferId, int *pLen);
typedef char*(*PFN_GET_AMXSTRING_NULL)			(AMX *amx, cell amx_addr, int bufferId, int *pLen);
typedef int(*PFN_GET_AMXSTRINGLEN)			(const cell *ptr);
typedef char *(*PFN_FORMAT_AMXSTRING)			(AMX *amx, cell *params, int startParam, int *pLen);
typedef void(*PFN_COPY_AMXMEMORY)			(cell *dest, const cell *src, int len);
typedef void(*PFN_LOG)					(const char *fmt, ...);
typedef void(*PFN_LOG_ERROR)				(AMX *amx, int err, const char *fmt, ...);
typedef int(*PFN_RAISE_AMXERROR)			(AMX *amx, int error);
typedef int(*PFN_REGISTER_FORWARD)			(const char *funcname, ForwardExecType exectype, ... /*paramtypes terminated by PF_DONE*/);
typedef int(*PFN_EXECUTE_FORWARD)			(int id, ... /*params*/);
typedef cell(*PFN_PREPARE_CELLARRAY)			(cell *ptr, unsigned int size);
typedef cell(*PFN_PREPARE_CHARARRAY)			(char *ptr, unsigned int size);
typedef cell(*PFN_PREPARE_CELLARRAY_A)			(cell *ptr, unsigned int size, bool copyBack);
typedef cell(*PFN_PREPARE_CHARARRAY_A)			(char *ptr, unsigned int size, bool copyBack);
typedef int(*PFN_IS_PLAYER_VALID)			(int id);
typedef const char*(*PFN_GET_PLAYER_NAME)			(int id);
typedef const char*(*PFN_GET_PLAYER_IP)			(int id);
typedef int(*PFN_IS_PLAYER_INGAME)			(int id);
typedef int(*PFN_IS_PLAYER_BOT)				(int id);
typedef int(*PFN_IS_PLAYER_AUTHORIZED)			(int id);
typedef float(*PFN_GET_PLAYER_TIME)			(int id);
typedef float(*PFN_GET_PLAYER_PLAYTIME)			(int id);
typedef int(*PFN_GETPLAYERFLAGS) 			(int id);
typedef int(*PFN_GET_PLAYER_CURWEAPON)			(int id);
typedef const char*(*PFN_GET_PLAYER_TEAM)		(int id);
typedef int(*PFN_GET_PLAYER_TEAMID)			(int id);
typedef int(*PFN_GET_PLAYER_DEATHS)			(int id);
typedef int(*PFN_GET_PLAYER_MENU)			(int id);
typedef int(*PFN_GET_PLAYER_KEYS)			(int id);
typedef int(*PFN_IS_PLAYER_ALIVE)			(int id);
typedef int(*PFN_GET_PLAYER_FRAGS)			(int id);
typedef int(*PFN_IS_PLAYER_CONNECTING)			(int id);
typedef int(*PFN_IS_PLAYER_HLTV)			(int id);
typedef int(*PFN_GET_PLAYER_ARMOR)			(int id);
typedef int(*PFN_GET_PLAYER_HEALTH)			(int id);
#ifdef USE_METAMOD
typedef edict_t *(*PFN_GET_PLAYER_EDICT)		(int id);
#else
typedef void *(*PFN_GET_PLAYER_EDICT)			(int id);
#endif
typedef void *(*PFN_PLAYER_PROP_ADDR)			(int id, int prop);
typedef int(*PFN_AMX_EXEC)				(AMX *amx, cell *returnValue, int index);
typedef int(*PFN_AMX_EXECV)				(AMX *amx, cell *returnValue, int index, int numparams, cell params[]);
typedef int(*PFN_AMX_ALLOT)				(AMX *amx, int length, cell *amx_addr, cell **phys_addr);
typedef int(*PFN_AMX_FINDPUBLIC)			(AMX *amx, const char *funcName, int *index);
typedef int(*PFN_AMX_FINDNATIVE)			(AMX *amx, const char *funcName, int *index);
typedef int(*PFN_LOAD_AMXSCRIPT)			(AMX *amx, void **code, const char *path, char errorInfo[64], int debug);
typedef int(*PFN_UNLOAD_AMXSCRIPT)			(AMX *amx, void **code);
typedef cell(*PFN_REAL_TO_CELL)				(REAL x);
typedef REAL(*PFN_CELL_TO_REAL)				(cell x);
typedef int(*PFN_REGISTER_SPFORWARD)			(AMX *amx, int func, ... /*params*/);
typedef int(*PFN_REGISTER_SPFORWARD_BYNAME)		(AMX *amx, const char *funcName, ... /*params*/);
typedef void(*PFN_UNREGISTER_SPFORWARD)			(int id);
typedef void(*PFN_MERGEDEFINITION_FILE)			(const char *filename);
typedef const char *(*PFN_FORMAT)			(const char *fmt, ... /*params*/);
typedef void(*PFN_REGISTERFUNCTION)			(void *pfn, const char *desc);
typedef int(*PFN_AMX_PUSH)				(AMX *amx, cell value);
typedef int(*PFN_SET_TEAM_INFO)				(int player, int teamid, const char *name);
typedef void(*PFN_REG_AUTH_FUNC)			(AUTHORIZEFUNC);
typedef void(*PFN_UNREG_AUTH_FUNC)			(AUTHORIZEFUNC);
typedef int(*PFN_FINDLIBRARY)				(const char *name, LibType type);
typedef size_t(*PFN_ADDLIBRARIES)			(const char *name, LibType type, void *parent);
typedef size_t(*PFN_REMOVELIBRARIES)			(void *parent);
typedef void(*PFN_OVERRIDENATIVES)			(AMX_NATIVE_INFO *natives, const char *myname);
typedef const char *(*PFN_GETLOCALINFO)			(const char *name, const char *def);
typedef int(*PFN_AMX_REREGISTER)			(AMX *amx, AMX_NATIVE_INFO *list, int list2);
typedef void *(*PFN_REGISTERFUNCTIONEX)			(void *pfn, const char *desc);
typedef void(*PFN_MESSAGE_BLOCK)			(int mode, int message, int *opt);

struct amxxapi_t
{
	PFN_ADD_NATIVES			AddNatives;
	PFN_ADD_NEW_NATIVES		AddNewNatives;
	PFN_BUILD_PATHNAME		BuildPathname;
	PFN_BUILD_PATHNAME_R		BuildPathnameR;
	PFN_GET_AMXADDR			GetAmxAddr;
	PFN_GET_AMXVECTOR_NULL		GetAmxVectorNull;
	PFN_PRINT_SRVCONSOLE		PrintSrvConsole;
	PFN_GET_MODNAME			GetModname;
	PFN_GET_AMXSCRIPTNAME		GetAmxScriptName;
	PFN_GET_AMXSCRIPT		GetAmxScript;
	PFN_FIND_AMXSCRIPT_BYAMX	FindAmxScriptByAmx;
	PFN_FIND_AMXSCRIPT_BYNAME	FindAmxScriptByName;
	PFN_SET_AMXSTRING		SetAmxString;
	PFN_SET_AMXSTRING_UTF8_CHAR	SetAmxStringUTF8Char;
	PFN_SET_AMXSTRING_UTF8_CELL	SetAmxStringUTF8Cell;
	PFN_GET_AMXSTRING		GetAmxString;
	PFN_GET_AMXSTRING_NULL		GetAmxStringNull;
	PFN_GET_AMXSTRINGLEN		GetAmxStringLen;
	PFN_FORMAT_AMXSTRING		FormatAmxString;
	PFN_COPY_AMXMEMORY		CopyAmxMemory;
	PFN_LOG				Log;
	PFN_LOG_ERROR			LogError;
	PFN_RAISE_AMXERROR		RaiseAmxError;
	PFN_REGISTER_FORWARD		RegisterForward;
	PFN_EXECUTE_FORWARD		ExecuteForward;
	PFN_PREPARE_CELLARRAY		PrepareCellArray;
	PFN_PREPARE_CHARARRAY		PrepareCharArray;
	PFN_PREPARE_CELLARRAY_A		PrepareCellArrayA;
	PFN_PREPARE_CHARARRAY_A		PrepareCharArrayA;
	PFN_IS_PLAYER_VALID		IsPlayerValid;
	PFN_GET_PLAYER_NAME		GetPlayerName;
	PFN_GET_PLAYER_IP		GetPlayerIP;
	PFN_IS_PLAYER_INGAME		IsPlayerInGame;
	PFN_IS_PLAYER_BOT		IsPlayerBot;
	PFN_IS_PLAYER_AUTHORIZED	IsPlayerAuthorized;
	PFN_GET_PLAYER_TIME		GetPlayerTime;
	PFN_GET_PLAYER_PLAYTIME		GetPlayerPlayTime;
	PFN_GET_PLAYER_CURWEAPON	GetPlayerCurweapon;
	PFN_GET_PLAYER_TEAM		GetPlayerTeam;
	PFN_GET_PLAYER_TEAMID		GetPlayerTeamID;
	PFN_GET_PLAYER_DEATHS		GetPlayerDeaths;
	PFN_GET_PLAYER_MENU		GetPlayerMenu;
	PFN_GET_PLAYER_KEYS		GetPlayerKeys;
	PFN_IS_PLAYER_ALIVE		IsPlayerAlive;
	PFN_GET_PLAYER_FRAGS		GetPlayerFrags;
	PFN_IS_PLAYER_CONNECTING	IsPlayerConnecting;
	PFN_IS_PLAYER_HLTV		IsPlayerHLTV;
	PFN_GET_PLAYER_ARMOR		GetPlayerArmor;
	PFN_GET_PLAYER_HEALTH		GetPlayerHealth;
	PFN_AMX_EXEC			amx_Exec;
	PFN_AMX_EXECV			amx_Execv;
	PFN_AMX_ALLOT			amx_Allot;
	PFN_AMX_FINDPUBLIC		amx_FindPublic;
	PFN_LOAD_AMXSCRIPT		LoadAmxScript;
	PFN_UNLOAD_AMXSCRIPT		UnloadAmxScript;
	PFN_REAL_TO_CELL		RealToCell;
	PFN_CELL_TO_REAL		CellToReal;
	PFN_REGISTER_SPFORWARD		RegisterSPForward;
	PFN_REGISTER_SPFORWARD_BYNAME	RegisterSPForwardByName;
	PFN_UNREGISTER_SPFORWARD	UnregisterSPForward;
	PFN_MERGEDEFINITION_FILE	MergeDefinition_File;
	PFN_AMX_FINDNATIVE		amx_FindNative;
	PFN_GETPLAYERFLAGS		GetPlayerFlags;
	PFN_GET_PLAYER_EDICT		GetPlayerEdict;
	PFN_FORMAT			Format;
	PFN_REGISTERFUNCTION		RegisterFunction;
	PFN_REQ_FNPTR			RequestFunction;
	PFN_AMX_PUSH			amx_Push;
	PFN_SET_TEAM_INFO		SetPlayerTeamInfo;
	PFN_PLAYER_PROP_ADDR		PlayerPropAddr;
	PFN_REG_AUTH_FUNC		RegAuthFunc;
	PFN_UNREG_AUTH_FUNC		UnregAuthFunc;
	PFN_FINDLIBRARY			FindLibrary;
	PFN_ADDLIBRARIES		AddLibraries;
	PFN_REMOVELIBRARIES		RemoveLibraries;
	PFN_OVERRIDENATIVES		OverrideNatives;
	PFN_GETLOCALINFO		GetLocalInfo;
	PFN_AMX_REREGISTER		AmxReRegister;
	PFN_REGISTERFUNCTIONEX		RegisterFunctionEx;
	PFN_MESSAGE_BLOCK		MessageBlock;
};

extern amxxapi_t g_amxxapi;

void AMXX_Log(const char *fmt, ...);
void AMXX_LogError(AMX *amx, int err, const char *fmt, ...);
char* getAmxString(cell* src, char* dest, size_t max, size_t* len = nullptr);
void setAmxString(cell* dest, const char* string, size_t max);

inline cell* getAmxAddr(AMX *amx, cell amx_addr)
{
	return (cell *)(amx->base + (size_t)(((AMX_HEADER *)amx->base)->dat + amx_addr));
}

#endif // __AMXXMODULE_H__
