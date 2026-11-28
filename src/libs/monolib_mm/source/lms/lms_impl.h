#pragma once

#include <stddef.h>

#include "types.h"

// Message library (LMS) of the game: the reader of the message project binary that ms::MsWrapper drives (blocks of the
// "MsgPrjBn" file: colours, attributes, tag groups, styles, contents). The library is third-party middleware linked as
// C; the repository builds it as C++ with C linkage, like the other third-party libraries. Its public names (LMS_*,
// LMSi_*) are kept as the executable exports them. The same symbols exist, with the same sizes of the small functions,
// in the Torna build (e.g. LMS_GetStyleIndexByName 0xaa2d48, LMSi_GetHashTableIndexFromLabel 0xaa3440) and in the
// Xenoblade Chronicles: Definitive Edition build (0x928a00, 0x929500); neither names a structure or a member, so the
// types below are inferred (unknownNNN) from the offsets that the functions read.
//
// The library is three translation units, in this order in the executable (0x7100984db0 to 0x71009866d0):
//   - lms_memory.cpp:  the allocator table and the byte helpers;
//   - lms_project.cpp: LMS_InitProject and the accessors of the project;
//   - lms_message.cpp: the analysis of the binary and the label hash.
// The split is proven by the calls that stay `bl` although clang 3.9 inlines a callee of this size from its own unit
// (LMSi_Malloc is three instructions): LMS_InitProject (0x7100984ea4) calls LMSi_Malloc, LMSi_AnalyzeMessageBinary and
// LMSi_SearchBlockByName; LMS_CloseProject calls LMSi_Free; the label lookups (0x7100985078, 0x7100985298,
// 0x7100985fa0) call LMSi_MemCmp and LMSi_GetHashTableIndexFromLabel; LMSi_SearchBlockByName and
// LMSi_GetBlockInfoByName call LMSi_MemCmp. Inside the units the callees are inlined: LMSi_AnalyzeMessageBinary
// (0x7100986488) holds LMSi_AnalyzeMessageHeader and LMSi_AnalyzeMessageBlocks, the ...ByName accessors hold their
// index accessor.

// One block of the binary (stride 0x18, allocated by LMSi_AnalyzeMessageHeader with `count * 0x18`).
struct unknown002 {
  const char *unknown00; // Inferred role: payload of the block, 0x10 bytes after the start of its header in the binary; original member name unknown.
  char unknown08[4];     // Inferred role: tag of the block ("CLR1", "TGG2"...), compared by LMSi_SearchBlockByName; original member name unknown.
  u32 unknown0c;         // Inferred role: size of the payload, from offset 4 of the block header; original member name unknown.
  u16 unknown10;         // Inferred role: u16 at offset 8 of the block header; original member name unknown.
};

static_assert(offsetof(unknown002, unknown08) == 0x08, "LMSi_AnalyzeMessageBlocks 0x7100986410");
static_assert(offsetof(unknown002, unknown0c) == 0x0c, "LMSi_AnalyzeMessageBlocks 0x7100986450");
static_assert(offsetof(unknown002, unknown10) == 0x10, "LMSi_AnalyzeMessageBlocks 0x7100986460");
static_assert(sizeof(unknown002) == 0x18, "stride 0x18 of LMSi_AnalyzeMessageBlocks, LMSi_SearchBlockByName");

// The project (LMS_InitProject allocates 0x50 bytes, 0x7100984eb4). The block indexes are -1 for a block that the
// binary does not hold; the accessors test them before every use.
struct unknown001 {
  const char *unknown00; // Inferred role: message project binary, the argument of LMS_InitProject (0x7100984ecc); original member name unknown.
  u64 unknown08;         // Inferred role: size of the binary, u32 at offset 0x12 of its header; original member name unknown.
  u8 unknown10;          // Inferred role: byte at offset 0xc of the header (encoding); original member name unknown.
  u16 unknown12;         // Inferred role: block count, u16 at offset 0xe of the header; original member name unknown.
  unknown002 *unknown18; // Inferred role: the blocks; original member name unknown.
  s32 unknown20;         // Inferred role: index of the "CLB1" block (colour labels); original member name unknown.
  s32 unknown24;         // Inferred role: index of the "CLR1" block (colours); original member name unknown.
  s32 unknown28;         // Inferred role: index of the "ALB1" block (attribute labels); original member name unknown.
  s32 unknown2c;         // Inferred role: index of the "ATI2" block (attribute infos); original member name unknown.
  s32 unknown30;         // Inferred role: index of the "ALI2" block (attribute list items); original member name unknown.
  s32 unknown34;         // Inferred role: index of the "TGG2" block (tag groups); original member name unknown.
  s32 unknown38;         // Inferred role: index of the "TAG2" block (tags); original member name unknown.
  s32 unknown3c;         // Inferred role: index of the "TGP2" block (tag parameters); original member name unknown.
  s32 unknown40;         // Inferred role: index of the "TGL2" block (tag parameter list items); original member name unknown.
  s32 unknown44;         // Inferred role: index of the "SYL3" block (styles); original member name unknown.
  s32 unknown48;         // Inferred role: index of the "SLB1" block (style labels); original member name unknown.
  s32 unknown4c;         // Inferred role: index of the "CTI1" block (contents); original member name unknown.
};

static_assert(offsetof(unknown001, unknown08) == 0x08, "LMSi_AnalyzeMessageHeader 0x71009863cc");
static_assert(offsetof(unknown001, unknown10) == 0x10, "LMSi_AnalyzeMessageHeader 0x710098639c");
static_assert(offsetof(unknown001, unknown12) == 0x12, "LMSi_AnalyzeMessageHeader 0x71009863a4");
static_assert(offsetof(unknown001, unknown18) == 0x18, "LMSi_AnalyzeMessageHeader 0x71009863bc");
static_assert(offsetof(unknown001, unknown20) == 0x20, "LMS_InitProject 0x7100984efc");
static_assert(offsetof(unknown001, unknown24) == 0x24, "LMS_InitProject 0x7100984ee8");
static_assert(offsetof(unknown001, unknown4c) == 0x4c, "LMS_InitProject 0x7100984fc0");
static_assert(sizeof(unknown001) == 0x50, "LMSi_Malloc(0x50) of LMS_InitProject 0x7100984eb4");

extern "C" {

void *LMSi_Malloc(size_t size);
void LMSi_Free(void *pointer);
int LMSi_MemCmp(const char *a, const char *b, int size);
void LMSi_MemCopy(char *destination, const char *source, int size);
// LMS_InitProject passes "MsgPrjBn" and 4 (x1 and w2, 0x7100984ec4); the definition reads neither (0x7100986488).
void LMSi_AnalyzeMessageBinary(unknown001 *project, const char *, int);
int LMSi_SearchBlockByName(unknown001 *project, const char *name);
int LMSi_GetHashTableIndexFromLabel(const char *label, u32 size);
}
