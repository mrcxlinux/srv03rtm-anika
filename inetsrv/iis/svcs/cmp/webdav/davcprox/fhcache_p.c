
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for fhcache.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "fhcache.h"

#define TYPE_FORMAT_STRING_SIZE   225                               
#define PROC_FORMAT_STRING_SIZE   403                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IFileHandleCache_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IFileHandleCache_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure HrRegisterWorkerProcess */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter dwProcessId */

/* 24 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetGUIDString */

/* 36 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 38 */	NdrFcLong( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x4 ),	/* 4 */
/* 44 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 46 */	NdrFcShort( 0x8 ),	/* 8 */
/* 48 */	NdrFcShort( 0x24 ),	/* 36 */
/* 50 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 52 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 54 */	NdrFcShort( 0x1 ),	/* 1 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter cchBufferLen */

/* 60 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 62 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 64 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pwszGUIDString */

/* 66 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Parameter pcchGUIDString */

/* 72 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 74 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 76 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetNewLockData */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x5 ),	/* 5 */
/* 92 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 94 */	NdrFcShort( 0x20 ),	/* 32 */
/* 96 */	NdrFcShort( 0x24 ),	/* 36 */
/* 98 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x9,		/* 9 */
/* 100 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 102 */	NdrFcShort( 0x1 ),	/* 1 */
/* 104 */	NdrFcShort( 0x1 ),	/* 1 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hFile */

/* 108 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 110 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter dwProcessId */

/* 114 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 116 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter dwSid */

/* 120 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 122 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbSid */

/* 126 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 128 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 130 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pnld */

/* 132 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 134 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 136 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter cchBufferLen */

/* 138 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 140 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pwszLockToken */

/* 144 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 146 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 148 */	NdrFcShort( 0x50 ),	/* Type Offset=80 */

	/* Parameter pcchLockToken */

/* 150 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 152 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 156 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 158 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetLockData */

/* 162 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 164 */	NdrFcLong( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x6 ),	/* 6 */
/* 170 */	NdrFcShort( 0x34 ),	/* x86 Stack size/offset = 52 */
/* 172 */	NdrFcShort( 0x30 ),	/* 48 */
/* 174 */	NdrFcShort( 0x50 ),	/* 80 */
/* 176 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0xb,		/* 11 */
/* 178 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 180 */	NdrFcShort( 0x1 ),	/* 1 */
/* 182 */	NdrFcShort( 0x1 ),	/* 1 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter liLockID */

/* 186 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 190 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Parameter dwSid */

/* 192 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 194 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 196 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbSid */

/* 198 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 200 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 202 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pwszPath */

/* 204 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 206 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 208 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Parameter dwTimeout */

/* 210 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 212 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pnld */

/* 216 */	NdrFcShort( 0x6113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=24 */
/* 218 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 220 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter plhd */

/* 222 */	NdrFcShort( 0x2112 ),	/* Flags:  must free, out, simple ref, srv alloc size=8 */
/* 224 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 226 */	NdrFcShort( 0x6e ),	/* Type Offset=110 */

	/* Parameter cchBufferLen */

/* 228 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 230 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pwszLockToken */

/* 234 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 236 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 238 */	NdrFcShort( 0x7a ),	/* Type Offset=122 */

	/* Parameter pcchLockToken */

/* 240 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 242 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 248 */	NdrFcShort( 0x30 ),	/* x86 Stack size/offset = 48 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrCheckLockID */

/* 252 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 254 */	NdrFcLong( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0x7 ),	/* 7 */
/* 260 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 262 */	NdrFcShort( 0x20 ),	/* 32 */
/* 264 */	NdrFcShort( 0x8 ),	/* 8 */
/* 266 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 268 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0x1 ),	/* 1 */
/* 274 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter liLockID */

/* 276 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 278 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 280 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Parameter dwSid */

/* 282 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 284 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbSid */

/* 288 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 290 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 292 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pwszPath */

/* 294 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 296 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 298 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 302 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrDeleteLock */

/* 306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 314 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 316 */	NdrFcShort( 0x18 ),	/* 24 */
/* 318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 320 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 322 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter liLockID */

/* 330 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 332 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 334 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetAllLockDataForName */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0x9 ),	/* 9 */
/* 350 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 352 */	NdrFcShort( 0x8 ),	/* 8 */
/* 354 */	NdrFcShort( 0x24 ),	/* 36 */
/* 356 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 358 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 360 */	NdrFcShort( 0x2 ),	/* 2 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pwszPath */

/* 366 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 368 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 370 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Parameter dwLockType */

/* 372 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 374 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pdwLocksFound */

/* 378 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppNewLockDatas */

/* 384 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 386 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 388 */	NdrFcShort( 0x86 ),	/* Type Offset=134 */

	/* Parameter ppwszLockTokens */

/* 390 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 392 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 394 */	NdrFcShort( 0xb8 ),	/* Type Offset=184 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x0,	/* FC_RP */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 14 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 16 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 18 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 20 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 22 */	
			0x11, 0x0,	/* FC_RP */
/* 24 */	NdrFcShort( 0x2 ),	/* Offset= 2 (26) */
/* 26 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 28 */	NdrFcShort( 0x1 ),	/* 1 */
/* 30 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 32 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 34 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 36 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 38 */	
			0x11, 0x0,	/* FC_RP */
/* 40 */	NdrFcShort( 0x2 ),	/* Offset= 2 (42) */
/* 42 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 44 */	NdrFcShort( 0x18 ),	/* 24 */
/* 46 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 48 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 50 */	NdrFcShort( 0x10 ),	/* 16 */
/* 52 */	NdrFcShort( 0x10 ),	/* 16 */
/* 54 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 56 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 58 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 60 */	NdrFcShort( 0x14 ),	/* 20 */
/* 62 */	NdrFcShort( 0x14 ),	/* 20 */
/* 64 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 66 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 68 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 70 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 72 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 74 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 76 */	
			0x11, 0x0,	/* FC_RP */
/* 78 */	NdrFcShort( 0x2 ),	/* Offset= 2 (80) */
/* 80 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 82 */	NdrFcShort( 0x2 ),	/* 2 */
/* 84 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 86 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 88 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 90 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 92 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 94 */	NdrFcShort( 0x8 ),	/* 8 */
/* 96 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 98 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 100 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 102 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 104 */	NdrFcShort( 0xffffffc2 ),	/* Offset= -62 (42) */
/* 106 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 108 */	NdrFcShort( 0x2 ),	/* Offset= 2 (110) */
/* 110 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 112 */	NdrFcShort( 0x8 ),	/* 8 */
/* 114 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 116 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 118 */	
			0x11, 0x0,	/* FC_RP */
/* 120 */	NdrFcShort( 0x2 ),	/* Offset= 2 (122) */
/* 122 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 124 */	NdrFcShort( 0x2 ),	/* 2 */
/* 126 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 128 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 130 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 132 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 134 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 136 */	NdrFcShort( 0x2 ),	/* Offset= 2 (138) */
/* 138 */	
			0x13, 0x0,	/* FC_OP */
/* 140 */	NdrFcShort( 0x2 ),	/* Offset= 2 (142) */
/* 142 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 144 */	NdrFcShort( 0x18 ),	/* 24 */
/* 146 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 148 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 150 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 152 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 154 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 156 */	NdrFcShort( 0x18 ),	/* 24 */
/* 158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 160 */	NdrFcShort( 0x2 ),	/* 2 */
/* 162 */	NdrFcShort( 0x10 ),	/* 16 */
/* 164 */	NdrFcShort( 0x10 ),	/* 16 */
/* 166 */	0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 168 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 170 */	NdrFcShort( 0x14 ),	/* 20 */
/* 172 */	NdrFcShort( 0x14 ),	/* 20 */
/* 174 */	0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 176 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 178 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 180 */	0x0,		/* 0 */
			NdrFcShort( 0xffffff75 ),	/* Offset= -139 (42) */
			0x5b,		/* FC_END */
/* 184 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 186 */	NdrFcShort( 0x2 ),	/* Offset= 2 (188) */
/* 188 */	
			0x13, 0x0,	/* FC_OP */
/* 190 */	NdrFcShort( 0x2 ),	/* Offset= 2 (192) */
/* 192 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 194 */	NdrFcShort( 0x4 ),	/* 4 */
/* 196 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 198 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 200 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 202 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 204 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 206 */	NdrFcShort( 0x4 ),	/* 4 */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0x1 ),	/* 1 */
/* 212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 218 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 220 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 222 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */

			0x0
        }
    };


/* Standard interface: __MIDL_itf_fhcache_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IFileHandleCache, ver. 0.0,
   GUID={0x3017e0e1,0x94d6,0x4896,{0xbc,0x57,0xb2,0xdf,0x75,0x92,0xd1,0x75}} */

#pragma code_seg(".orpc")
static const unsigned short IFileHandleCache_FormatStringOffsetTable[] =
    {
    0,
    36,
    84,
    162,
    252,
    306,
    342
    };

static const MIDL_STUBLESS_PROXY_INFO IFileHandleCache_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IFileHandleCache_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IFileHandleCache_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IFileHandleCache_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IFileHandleCacheProxyVtbl = 
{
    &IFileHandleCache_ProxyInfo,
    &IID_IFileHandleCache,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrRegisterWorkerProcess */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetGUIDString */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetNewLockData */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetLockData */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrCheckLockID */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrDeleteLock */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetAllLockDataForName */
};

const CInterfaceStubVtbl _IFileHandleCacheStubVtbl =
{
    &IID_IFileHandleCache,
    &IFileHandleCache_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x6000165, /* MIDL Version 6.0.357 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _fhcache_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IFileHandleCacheProxyVtbl,
    0
};

const CInterfaceStubVtbl * _fhcache_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IFileHandleCacheStubVtbl,
    0
};

PCInterfaceName const _fhcache_InterfaceNamesList[] = 
{
    "IFileHandleCache",
    0
};


#define _fhcache_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _fhcache, pIID, n)

int __stdcall _fhcache_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_fhcache_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo fhcache_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _fhcache_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _fhcache_StubVtblList,
    (const PCInterfaceName * ) & _fhcache_InterfaceNamesList,
    0, // no delegation
    & _fhcache_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0357 */
/* Compiler settings for fhcache.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "fhcache.h"

#define TYPE_FORMAT_STRING_SIZE   205                               
#define PROC_FORMAT_STRING_SIZE   417                               
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IFileHandleCache_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IFileHandleCache_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure HrRegisterWorkerProcess */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter dwProcessId */

/* 26 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 30 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetGUIDString */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x4 ),	/* 4 */
/* 46 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	NdrFcShort( 0x24 ),	/* 36 */
/* 52 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 54 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 56 */	NdrFcShort( 0x1 ),	/* 1 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter cchBufferLen */

/* 64 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 66 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 68 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pwszGUIDString */

/* 70 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 72 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 74 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Parameter pcchGUIDString */

/* 76 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 78 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 80 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 82 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 84 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 86 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetNewLockData */

/* 88 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 90 */	NdrFcLong( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x5 ),	/* 5 */
/* 96 */	NdrFcShort( 0x50 ),	/* ia64 Stack size/offset = 80 */
/* 98 */	NdrFcShort( 0x20 ),	/* 32 */
/* 100 */	NdrFcShort( 0x24 ),	/* 36 */
/* 102 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x9,		/* 9 */
/* 104 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 106 */	NdrFcShort( 0x1 ),	/* 1 */
/* 108 */	NdrFcShort( 0x1 ),	/* 1 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hFile */

/* 114 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 116 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 118 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter dwProcessId */

/* 120 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 122 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter dwSid */

/* 126 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 128 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbSid */

/* 132 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 134 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 136 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter pnld */

/* 138 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 140 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 142 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter cchBufferLen */

/* 144 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 146 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 148 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pwszLockToken */

/* 150 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 152 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 154 */	NdrFcShort( 0x46 ),	/* Type Offset=70 */

	/* Parameter pcchLockToken */

/* 156 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 158 */	NdrFcShort( 0x40 ),	/* ia64 Stack size/offset = 64 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 164 */	NdrFcShort( 0x48 ),	/* ia64 Stack size/offset = 72 */
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetLockData */

/* 168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0x6 ),	/* 6 */
/* 176 */	NdrFcShort( 0x60 ),	/* ia64 Stack size/offset = 96 */
/* 178 */	NdrFcShort( 0x30 ),	/* 48 */
/* 180 */	NdrFcShort( 0x24 ),	/* 36 */
/* 182 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0xb,		/* 11 */
/* 184 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 186 */	NdrFcShort( 0x1 ),	/* 1 */
/* 188 */	NdrFcShort( 0x1 ),	/* 1 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter liLockID */

/* 194 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 196 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 198 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Parameter dwSid */

/* 200 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 202 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 204 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbSid */

/* 206 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 208 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 210 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Parameter pwszPath */

/* 212 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 214 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 216 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */

	/* Parameter dwTimeout */

/* 218 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 220 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pnld */

/* 224 */	NdrFcShort( 0x8113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=32 */
/* 226 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 228 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter plhd */

/* 230 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 232 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 234 */	NdrFcShort( 0x74 ),	/* Type Offset=116 */

	/* Parameter cchBufferLen */

/* 236 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 238 */	NdrFcShort( 0x40 ),	/* ia64 Stack size/offset = 64 */
/* 240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pwszLockToken */

/* 242 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 244 */	NdrFcShort( 0x48 ),	/* ia64 Stack size/offset = 72 */
/* 246 */	NdrFcShort( 0x84 ),	/* Type Offset=132 */

	/* Parameter pcchLockToken */

/* 248 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 250 */	NdrFcShort( 0x50 ),	/* ia64 Stack size/offset = 80 */
/* 252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 256 */	NdrFcShort( 0x58 ),	/* ia64 Stack size/offset = 88 */
/* 258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrCheckLockID */

/* 260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 266 */	NdrFcShort( 0x7 ),	/* 7 */
/* 268 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 270 */	NdrFcShort( 0x20 ),	/* 32 */
/* 272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 274 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 276 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x1 ),	/* 1 */
/* 282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 284 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter liLockID */

/* 286 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 288 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 290 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Parameter dwSid */

/* 292 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 294 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbSid */

/* 298 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 300 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 302 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Parameter pwszPath */

/* 304 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 306 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 308 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */

	/* Return value */

/* 310 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 312 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 314 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrDeleteLock */

/* 316 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 318 */	NdrFcLong( 0x0 ),	/* 0 */
/* 322 */	NdrFcShort( 0x8 ),	/* 8 */
/* 324 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 326 */	NdrFcShort( 0x18 ),	/* 24 */
/* 328 */	NdrFcShort( 0x8 ),	/* 8 */
/* 330 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 332 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 334 */	NdrFcShort( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter liLockID */

/* 342 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 344 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 346 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 348 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 350 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HrGetAllLockDataForName */

/* 354 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 356 */	NdrFcLong( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x9 ),	/* 9 */
/* 362 */	NdrFcShort( 0x38 ),	/* ia64 Stack size/offset = 56 */
/* 364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 366 */	NdrFcShort( 0x24 ),	/* 36 */
/* 368 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 370 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 372 */	NdrFcShort( 0x2 ),	/* 2 */
/* 374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 378 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pwszPath */

/* 380 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 382 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 384 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */

	/* Parameter dwLockType */

/* 386 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 388 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pdwLocksFound */

/* 392 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 394 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 396 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppNewLockDatas */

/* 398 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 400 */	NdrFcShort( 0x20 ),	/* ia64 Stack size/offset = 32 */
/* 402 */	NdrFcShort( 0x90 ),	/* Type Offset=144 */

	/* Parameter ppwszLockTokens */

/* 404 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 406 */	NdrFcShort( 0x28 ),	/* ia64 Stack size/offset = 40 */
/* 408 */	NdrFcShort( 0xae ),	/* Type Offset=174 */

	/* Return value */

/* 410 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 412 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 414 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x0,	/* FC_RP */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0x8 ),	/* ia64 Stack size/offset = 8 */
/* 14 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 16 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 18 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 20 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 22 */	
			0x11, 0x0,	/* FC_RP */
/* 24 */	NdrFcShort( 0x2 ),	/* Offset= 2 (26) */
/* 26 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 28 */	NdrFcShort( 0x1 ),	/* 1 */
/* 30 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 32 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 34 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 36 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 38 */	
			0x11, 0x0,	/* FC_RP */
/* 40 */	NdrFcShort( 0x2 ),	/* Offset= 2 (42) */
/* 42 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 44 */	NdrFcShort( 0x20 ),	/* 32 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0xa ),	/* Offset= 10 (58) */
/* 50 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 52 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 54 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 56 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 58 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 60 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 62 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 64 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 66 */	
			0x11, 0x0,	/* FC_RP */
/* 68 */	NdrFcShort( 0x2 ),	/* Offset= 2 (70) */
/* 70 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 72 */	NdrFcShort( 0x2 ),	/* 2 */
/* 74 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 76 */	NdrFcShort( 0x30 ),	/* ia64 Stack size/offset = 48 */
/* 78 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 80 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 82 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 84 */	NdrFcShort( 0x8 ),	/* 8 */
/* 86 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 88 */	
			0x11, 0x0,	/* FC_RP */
/* 90 */	NdrFcShort( 0x2 ),	/* Offset= 2 (92) */
/* 92 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 94 */	NdrFcShort( 0x1 ),	/* 1 */
/* 96 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 98 */	NdrFcShort( 0x10 ),	/* ia64 Stack size/offset = 16 */
/* 100 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 102 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 104 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 106 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 108 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 110 */	NdrFcShort( 0xffffffbc ),	/* Offset= -68 (42) */
/* 112 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 114 */	NdrFcShort( 0x2 ),	/* Offset= 2 (116) */
/* 116 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 118 */	NdrFcShort( 0x10 ),	/* 16 */
/* 120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 122 */	NdrFcShort( 0x0 ),	/* Offset= 0 (122) */
/* 124 */	0xb9,		/* FC_UINT3264 */
			0x8,		/* FC_LONG */
/* 126 */	0x40,		/* FC_STRUCTPAD4 */
			0x5b,		/* FC_END */
/* 128 */	
			0x11, 0x0,	/* FC_RP */
/* 130 */	NdrFcShort( 0x2 ),	/* Offset= 2 (132) */
/* 132 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 134 */	NdrFcShort( 0x2 ),	/* 2 */
/* 136 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 138 */	NdrFcShort( 0x40 ),	/* ia64 Stack size/offset = 64 */
/* 140 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 142 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 144 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 146 */	NdrFcShort( 0x2 ),	/* Offset= 2 (148) */
/* 148 */	
			0x13, 0x0,	/* FC_OP */
/* 150 */	NdrFcShort( 0x2 ),	/* Offset= 2 (152) */
/* 152 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 156 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 158 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 160 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 162 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 166 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 168 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 170 */	NdrFcShort( 0xffffff80 ),	/* Offset= -128 (42) */
/* 172 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 174 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 176 */	NdrFcShort( 0x2 ),	/* Offset= 2 (178) */
/* 178 */	
			0x13, 0x0,	/* FC_OP */
/* 180 */	NdrFcShort( 0x2 ),	/* Offset= 2 (182) */
/* 182 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
/* 188 */	NdrFcShort( 0x18 ),	/* ia64 Stack size/offset = 24 */
/* 190 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 192 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 196 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 198 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 200 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 202 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */

			0x0
        }
    };


/* Standard interface: __MIDL_itf_fhcache_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IFileHandleCache, ver. 0.0,
   GUID={0x3017e0e1,0x94d6,0x4896,{0xbc,0x57,0xb2,0xdf,0x75,0x92,0xd1,0x75}} */

#pragma code_seg(".orpc")
static const unsigned short IFileHandleCache_FormatStringOffsetTable[] =
    {
    0,
    38,
    88,
    168,
    260,
    316,
    354
    };

static const MIDL_STUBLESS_PROXY_INFO IFileHandleCache_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IFileHandleCache_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IFileHandleCache_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IFileHandleCache_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IFileHandleCacheProxyVtbl = 
{
    &IFileHandleCache_ProxyInfo,
    &IID_IFileHandleCache,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrRegisterWorkerProcess */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetGUIDString */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetNewLockData */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetLockData */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrCheckLockID */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrDeleteLock */ ,
    (void *) (INT_PTR) -1 /* IFileHandleCache::HrGetAllLockDataForName */
};

const CInterfaceStubVtbl _IFileHandleCacheStubVtbl =
{
    &IID_IFileHandleCache,
    &IFileHandleCache_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x6000165, /* MIDL Version 6.0.357 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _fhcache_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IFileHandleCacheProxyVtbl,
    0
};

const CInterfaceStubVtbl * _fhcache_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IFileHandleCacheStubVtbl,
    0
};

PCInterfaceName const _fhcache_InterfaceNamesList[] = 
{
    "IFileHandleCache",
    0
};


#define _fhcache_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _fhcache, pIID, n)

int __stdcall _fhcache_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_fhcache_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo fhcache_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _fhcache_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _fhcache_StubVtblList,
    (const PCInterfaceName * ) & _fhcache_InterfaceNamesList,
    0, // no delegation
    & _fhcache_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

