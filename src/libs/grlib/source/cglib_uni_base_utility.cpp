#include "grlib/cglib_uni_base_utility.h"

#include <string.h>

#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_shader.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"

namespace grlib {

void ShdInstancePosMatrix3x4Set(f32 *destination, const mm::Mat44 &source, f32 value) {
  destination[0] = source.rows[0][0];
  destination[1] = source.rows[1][0];
  destination[2] = source.rows[2][0];
  destination[3] = source.rows[3][0];
  destination[4] = source.rows[0][1];
  destination[5] = source.rows[1][1];
  destination[6] = source.rows[2][1];
  destination[7] = source.rows[3][1];
  destination[8] = source.rows[0][2];
  destination[9] = source.rows[1][2];
  destination[10] = source.rows[2][2];
  destination[11] = source.rows[3][2];
  destination[12] = value;
}

void ShdF32SetMat44(f32 *destination, const f32 *source) {
  for (int i = 0; i < 16; i++) {
    destination[i] = source[i];
  }
}

void ShdF32TransposeMat34(f32 *destination, const f32 *source) {
  for (int column = 0; column < 3; column++) {
    for (int row = 0; row < 4; row++) {
      destination[column * 4 + row] = source[row * 4 + column];
    }
  }
}

void ShdF32TransposeMat44(f32 *destination, const f32 *source) {
  for (int column = 0; column < 4; column++) {
    for (int row = 0; row < 4; row++) {
      destination[column * 4 + row] = source[row * 4 + column];
    }
  }
}

void ShdMat44SetMat44(f32 *destination, const mm::Mat44 &source) {
  for (int row = 0; row < 4; row++) {
    for (int column = 0; column < 4; column++) {
      destination[row * 4 + column] = source.rows[row][column];
    }
  }
}

void ShdMat44SetMat34(f32 *destination, const mm::Mat44 &source) {
  for (int row = 0; row < 3; row++) {
    for (int column = 0; column < 4; column++) {
      destination[row * 4 + column] = source.rows[row][column];
    }
  }
}

void ShdMat44TransposeMat34(f32 *destination, const mm::Mat44 &source) {
  for (int column = 0; column < 3; column++) {
    for (int row = 0; row < 4; row++) {
      destination[column * 4 + row] = source.rows[row][column];
    }
  }
}

void ShdMat44TransposeMat44(f32 *destination, const mm::Mat44 &source) {
  for (int column = 0; column < 4; column++) {
    for (int row = 0; row < 4; row++) {
      destination[column * 4 + row] = source.rows[row][column];
    }
  }
}

void ShdMat44SetMat44Array(f32 *destination, const mm::Mat44 *source, int count) {
  for (int i = 0; i < count; i++) {
    ShdMat44SetMat44(&destination[i * 16], source[i]);
  }
}

void ShdMat44TransposeMat34Array(f32 *destination, const mm::Mat44 *source, int count) {
  for (int i = 0; i < count; i++) {
    for (int column = 0; column < 3; column++) {
      for (int row = 0; row < 4; row++) {
        destination[i * 12 + column * 4 + row] = source[i].rows[row][column];
      }
    }
  }
}

void ShdMat44TransposeMat44Array(f32 *destination, const mm::Mat44 *source, int count) {
  for (int i = 0; i < count; i++) {
    ShdMat44TransposeMat44(&destination[i * 16], source[i]);
  }
}

void ShdF32SetF32Array(f32 *destination, const f32 *source, int count) {
  for (int i = 0; i < count; i++) {
    destination[i] = source[i];
  }
}

void ShdF32SetVec2(f32 *destination, const f32 *source) {
  destination[0] = source[0];
  destination[1] = source[1];
}

void ShdF32SetVec3(f32 *destination, const f32 *source) {
  destination[0] = source[0];
  destination[1] = source[1];
  destination[2] = source[2];
}

void ShdF32SetVec4(f32 *destination, const f32 *source) {
  destination[0] = source[0];
  destination[1] = source[1];
  destination[2] = source[2];
  destination[3] = source[3];
}

void ShdVec3SetVec3(f32 *destination, const mm::Vec3 &source) {
  destination[0] = source.x;
  destination[1] = source.y;
  destination[2] = source.z;
}

void ShdVec4SetVec4(f32 *destination, const mm::Vec4 &source) {
  destination[0] = source.x;
  destination[1] = source.y;
  destination[2] = source.z;
  destination[3] = source.w;
}

void ShdCol3SetVec3(f32 *destination, const mm::Col3 &source) {
  destination[0] = source.r;
  destination[1] = source.g;
  destination[2] = source.b;
}

void ShdCol4SetVec4(f32 *destination, const mm::Col4 &source) {
  destination[0] = source.r;
  destination[1] = source.g;
  destination[2] = source.b;
  destination[3] = source.a;
}

void ShdUniformS32SetS32Array(int *destination, const int *source, int count) {
  for (int i = 0; i < count; i++) {
    destination[i * 4 + 0] = *source;
    destination[i * 4 + 1] = *source;
    destination[i * 4 + 2] = *source;
    destination[i * 4 + 3] = *source;
    source++;
  }
}

void ShdS32SetIVec4(int *destination, const int *source) {
  destination[0] = source[0];
  destination[1] = source[1];
  destination[2] = source[2];
  destination[3] = source[3];
}

void ShdU32SetUVec4(u32 *destination, const u32 *source) {
  destination[0] = source[0];
  destination[1] = source[1];
  destination[2] = source[2];
  destination[3] = source[3];
}

static const CGLibShader *getCurrentShader(const CGLibDecShader *decShader) { return decShader->unknown38 + decShader->unknown58; }

static const CGLibShaderBlockInfo *getUniformBlocks(const CGLibShader *shader) { return reinterpret_cast<const CGLibShaderBlockInfo *>(shader->m_data + shader->unknown08->unknown24); }

static const CGLibShaderBlockInfo *getStorageBuffers(const CGLibShader *shader) { return reinterpret_cast<const CGLibShaderBlockInfo *>(shader->m_data + shader->unknown08->unknown30); }

static u32 findUniformBlockIndex(const CGLibShader *shader, const char *name) {
  u32 index = -1;
  u32 num = shader->unknown08->unknown20;
  if (num != 0) {
    const CGLibShaderBlockInfo *block = getUniformBlocks(shader);
    for (u32 i = 0; i < num; i++, block++) {
      if (strcmp(reinterpret_cast<const char *>(shader->m_data + block->unknown00), name) == 0) {
        index = block->unknown0c;
        break;
      }
    }
  }
  return index;
}

static u32 findStorageBufferIndex(const CGLibShader *shader, const char *name) {
  u32 index = -1;
  u32 num = shader->unknown08->unknown2c;
  if (num != 0) {
    const CGLibShaderBlockInfo *block = getStorageBuffers(shader);
    for (u32 i = 0; i < num; i++, block++) {
      if (strcmp(reinterpret_cast<const char *>(shader->m_data + block->unknown00), name) == 0) {
        index = block->unknown0c;
        break;
      }
    }
  }
  return index;
}

static u32 getUniformBlockSize(const CGLibShader *shader, u32 index) {
  if (index > shader->unknown08->unknown22) {
    return 0;
  }
  u8 block = (shader->m_data + shader->unknown08->unknown28)[index];
  if (block != 0xff) {
    return getUniformBlocks(shader)[block].unknown0e;
  }
  return 0;
}

static u32 getStorageBufferSize(const CGLibShader *shader, u32 index) {
  if (index > shader->unknown08->unknown2e) {
    return 0;
  }
  u8 block = (shader->m_data + shader->unknown08->unknown34)[index];
  if (block != 0xff) {
    return getStorageBuffers(shader)[block].unknown0e;
  }
  return 0;
}

CGLibUniBaseUtility::CGLibUniBaseUtility(const CGLibDecShader *decShader) : unknown08(decShader), unknown10(-1), m_size(0), unknown18(false) {}

void CGLibUniBaseUtility::setF32SetMat44(u32 offset, const f32 *source) {
  if (offset != 0xffffffff) {
    ShdF32SetMat44(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setF32TransposeMat34(u32 offset, const f32 *source) {
  if (offset != 0xffffffff) {
    ShdF32TransposeMat34(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setF32TransposeMat44(u32 offset, const f32 *source) {
  if (offset != 0xffffffff) {
    ShdF32TransposeMat44(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setMat44SetMat44(u32 offset, const mm::Mat44 &source) {
  if (offset != 0xffffffff) {
    ShdMat44SetMat44(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setMat44SetMat34(u32 offset, const mm::Mat44 &source) {
  if (offset != 0xffffffff) {
    ShdMat44SetMat34(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setMat44TransposeMat34(u32 offset, const mm::Mat44 &source) {
  if (offset != 0xffffffff) {
    ShdMat44TransposeMat34(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setMat44TransposeMat44(u32 offset, const mm::Mat44 &source) {
  if (offset != 0xffffffff) {
    ShdMat44TransposeMat44(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setMat44SetMat44Array(u32 offset, const mm::Mat44 *source, int count) {
  if (offset != 0xffffffff) {
    ShdMat44SetMat44Array(reinterpret_cast<f32 *>(getBuff() + offset), source, count);
  }
}

void CGLibUniBaseUtility::setMat44TransposeMat44Array(u32 offset, const mm::Mat44 *source, int count) {
  if (offset != 0xffffffff) {
    ShdMat44TransposeMat44Array(reinterpret_cast<f32 *>(getBuff() + offset), source, count);
  }
}

void CGLibUniBaseUtility::setF32SetF32Array(u32 offset, const f32 *source, int count) {
  if (offset != 0xffffffff) {
    ShdF32SetF32Array(reinterpret_cast<f32 *>(getBuff() + offset), source, count);
  }
}

void CGLibUniBaseUtility::setF32SetVec2(u32 offset, const f32 *source) {
  if (offset != 0xffffffff) {
    ShdF32SetVec2(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setF32SetVec3(u32 offset, const f32 *source) {
  if (offset != 0xffffffff) {
    ShdF32SetVec3(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setF32SetVec4(u32 offset, const f32 *source) {
  if (offset != 0xffffffff) {
    ShdF32SetVec4(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setVec3SetVec3(u32 offset, const mm::Vec3 &source) {
  if (offset != 0xffffffff) {
    ShdVec3SetVec3(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setVec4SetVec4(u32 offset, const mm::Vec4 &source) {
  if (offset != 0xffffffff) {
    ShdVec4SetVec4(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setCol3SetVec3(u32 offset, const mm::Col3 &source) {
  if (offset != 0xffffffff) {
    ShdCol3SetVec3(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setCol4SetVec4(u32 offset, const mm::Col4 &source) {
  if (offset != 0xffffffff) {
    ShdCol4SetVec4(reinterpret_cast<f32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setUniformS32SetS32Array(u32 offset, int *source, int count) {
  if (offset != 0xffffffff) {
    int *destination = reinterpret_cast<int *>(getBuff() + offset);
    for (int i = 0; i < count; i++) {
      destination[0] = source[i];
      destination[1] = source[i];
      destination[2] = source[i];
      destination[3] = source[i];
      destination += 4;
    }
  }
}

void CGLibUniBaseUtility::setS32SetIVec4(u32 offset, int *source) {
  if (offset != 0xffffffff) {
    ShdS32SetIVec4(reinterpret_cast<int *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setU32SetUVec4(u32 offset, u32 *source) {
  if (offset != 0xffffffff) {
    ShdU32SetUVec4(reinterpret_cast<u32 *>(getBuff() + offset), source);
  }
}

void CGLibUniBaseUtility::setUseUniformBlock(const char *name) {
  unknown10 = findUniformBlockIndex(getCurrentShader(unknown08), name);
  m_size = getUniformBlockSize(getCurrentShader(unknown08), unknown10);
  unknown18 = false;
  setMoveMem();
}

void CGLibUniBaseUtility::setUseUniformBlock(u32 index) {
  unknown10 = index;
  m_size = getUniformBlockSize(getCurrentShader(unknown08), index);
  unknown18 = false;
  setMoveMem();
}

void CGLibUniBaseUtility::setUseStorageBuffer(const char *name) {
  unknown10 = findStorageBufferIndex(getCurrentShader(unknown08), name);
  m_size = getStorageBufferSize(getCurrentShader(unknown08), unknown10);
  unknown18 = true;
  setMoveMem();
}

void CGLibUniBaseUtility::setUseStorageBuffer(u32 index) {
  unknown10 = index;
  m_size = getStorageBufferSize(getCurrentShader(unknown08), index);
  unknown18 = true;
  setMoveMem();
}

CGLibUniformEtcUtility::CGLibUniformEtcUtility(const CGLibDecShader *decShader) : CGLibUniBaseUtility(decShader) {}

u8 *CGLibUniformEtcUtility::getBuff() { return unknown20.m_buff; }

u8 *CGLibEtcUniformBlock::getBuff() { return m_buff; }

void CGLibUniformEtcUtility::updateData() {}

void CGLibEtcUniformBlock::updateDataMoveOff() {}

} // namespace grlib
