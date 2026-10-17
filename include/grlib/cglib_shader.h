#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {

struct CGLibShaderBlockInfo {
  u32 nameOfs;
  u16 valueNum;
  u16 valueIdx;
  u32 stageBindOfs;
  u8 index;
  u8 stageBindNum;
  u16 size;
};

static_assert(sizeof(CGLibShaderBlockInfo) == 0x10, "");

struct CGLibShaderInfo {
  u8 _00[0x20 - 0x00];
  s16 uniformBlockNum;
  u16 uniformBlockMax;
  u32 uniformBlockOfs;
  u32 uniformBlockIdxOfs;
  s16 storageBufferNum;
  u16 storageBufferMax;
  u32 storageBufferOfs;
  u32 storageBufferIdxOfs;
};

static_assert(offsetof(CGLibShaderInfo, uniformBlockNum) == 0x20, "");
static_assert(offsetof(CGLibShaderInfo, storageBufferIdxOfs) == 0x34, "");

class CGLibShader {
public:
  CGLibShader();
  int getTextureLocation(const char *name) const;
  int getUniformBlockOfs(const char *name) const;

  const u8 *m_data;
  const CGLibShaderInfo *m_info;
  u8 _10[0xd8 - 0x10];
};

static_assert(sizeof(CGLibShader) == 0xd8, "");

} // namespace grlib
