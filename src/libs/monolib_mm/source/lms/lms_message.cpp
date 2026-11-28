#include <stddef.h>

#include "lms/lms_impl.h"
#include "types.h"

// Third translation unit of the message library (see lms_impl.h): the analysis of the message binary. The binary is
// read at byte offsets, as the other resource blobs of the game (decision 38 of docs/decisions.md). Its header is 0x20
// bytes: the encoding byte at 0xc, the block count (u16) at 0xe, the size of the file (u32) at 0x12. The blocks follow,
// each starting 0x10 aligned: a 4 byte tag, the size of the payload (u32), a u16 at offset 8, then the payload at 0x10.

extern "C" {

void LMSi_AnalyzeMessageHeader(unknown001 *project) {
  project->unknown10 = project->unknown00[0xc];
  project->unknown12 = *reinterpret_cast<const u16 *>(project->unknown00 + 0xe);
  if (project->unknown12 == 0) {
    project->unknown18 = nullptr;
  } else {
    project->unknown18 = static_cast<unknown002 *>(LMSi_Malloc(project->unknown12 * sizeof(unknown002)));
  }
  project->unknown08 = *reinterpret_cast<const u32 *>(project->unknown00 + 0x12);
}

void LMSi_AnalyzeMessageBlocks(unknown001 *project) {
  size_t offset = 0x20;
  for (int i = 0; i < project->unknown12; i++) {
    unknown002 *block = &project->unknown18[i];
    // The game reads the fields of the block header one after the other: the addresses of the tag bytes are
    // `offset | 1`, `(offset | 1) + 1`, `offset | 3` and the next fields `(offset | 3) + 1`, `+ 5` (0x71009863f0 to
    // 0x7100986460), which only a cursor advanced after each field gives (the sum of two constants would fold). A
    // loop over the four tag bytes (ruling 8 of docs/decisions.md) is measured: same 43 instructions, but the tag
    // bytes are addressed `offset | 2` instead of `(offset | 1) + 1` (0x7100986428).
    size_t pos = offset;
    block->unknown00 = project->unknown00 + pos + 0x10;
    block->unknown08[0] = project->unknown00[pos];
    pos++;
    block->unknown08[1] = project->unknown00[pos];
    pos++;
    block->unknown08[2] = project->unknown00[pos];
    pos++;
    block->unknown08[3] = project->unknown00[pos];
    pos++;
    block->unknown0c = *reinterpret_cast<const u32 *>(project->unknown00 + pos);
    pos += 4;
    block->unknown10 = *reinterpret_cast<const u16 *>(project->unknown00 + pos);
    offset = (offset + block->unknown0c + 0x1f) & ~0xfUL;
  }
}

void LMSi_AnalyzeMessageBinary(unknown001 *project, const char *, int) {
  LMSi_AnalyzeMessageHeader(project);
  LMSi_AnalyzeMessageBlocks(project);
}

int LMSi_SearchBlockByName(unknown001 *project, const char *name) {
  for (u16 i = 0; i < project->unknown12; i++) {
    if (LMSi_MemCmp(project->unknown18[i].unknown08, name, 4)) {
      return i;
    }
  }
  return -1;
}

unknown002 *LMSi_GetBlockInfoByName(unknown001 *project, const char *name) {
  for (int i = 0; i < project->unknown12; i++) {
    if (LMSi_MemCmp(project->unknown18[i].unknown08, name, 4)) {
      return &project->unknown18[i];
    }
  }
  return nullptr;
}

// Hash of a label: `hash * 0x492 + byte` over the bytes (unsigned), then the remainder of the table size. The label
// tables of the blocks "CLB1", "ALB1" and "SLB1" hold the buckets.
int LMSi_GetHashTableIndexFromLabel(const char *label, u32 size) {
  u32 hash = 0;
  while (*label != 0) {
    hash = hash * 0x492 + static_cast<u8>(*label);
    label++;
  }
  return hash % size;
}
}
