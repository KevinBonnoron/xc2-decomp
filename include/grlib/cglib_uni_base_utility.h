#pragma once
#include <stddef.h>

#include "grlib/cglib_etc_uniform_block.h"
#include "types.h"

namespace mm {
struct Col3;
struct Col4;
struct Mat44;
struct Vec3;
struct Vec4;
} // namespace mm

namespace grlib {

class CGLibDecShader;

class CGLibUniBaseUtility {
public:
  CGLibUniBaseUtility(const CGLibDecShader *decShader);
  void setF32SetMat44(u32 offset, const f32 *source);
  void setF32TransposeMat34(u32 offset, const f32 *source);
  void setF32TransposeMat44(u32 offset, const f32 *source);
  void setMat44SetMat44(u32 offset, const mm::Mat44 &source);
  void setMat44SetMat34(u32 offset, const mm::Mat44 &source);
  void setMat44TransposeMat34(u32 offset, const mm::Mat44 &source);
  void setMat44TransposeMat44(u32 offset, const mm::Mat44 &source);
  void setMat44SetMat44Array(u32 offset, const mm::Mat44 *source, int count);
  void setMat44TransposeMat34Array(u32 offset, const mm::Mat44 *source, int count);
  void setMat44TransposeMat44Array(u32 offset, const mm::Mat44 *source, int count);
  void setF32SetF32Array(u32 offset, const f32 *source, int count);
  void setF32SetVec2(u32 offset, const f32 *source);
  void setF32SetVec3(u32 offset, const f32 *source);
  void setF32SetVec4(u32 offset, const f32 *source);
  void setF32SetVec4Array(u32 offset, const f32 *source, int count);
  void setVec3SetVec3(u32 offset, const mm::Vec3 &source);
  void setVec4SetVec4(u32 offset, const mm::Vec4 &source);
  void setCol3SetVec3(u32 offset, const mm::Col3 &source);
  void setCol4SetVec4(u32 offset, const mm::Col4 &source);
  void setUniformS32SetS32Array(u32 offset, int *source, int count);
  void setS32SetIVec4(u32 offset, int *source);
  void setU32SetUVec4(u32 offset, u32 *source);
  void setUseUniformBlock(const char *name);
  void setUseUniformBlock(u32 index);
  void setUseStorageBuffer(const char *name);
  void setUseStorageBuffer(u32 index);
  u8 *getUniformBlockAdder(const char *name);
  u8 *getStorageBufferAdder(const char *name);

  virtual ~CGLibUniBaseUtility() {}
  virtual u8 *getBuff() = 0;
  virtual void updateData() = 0;
  virtual void setUniformBlock() = 0;
  virtual void setStorageBuffer() = 0;
  virtual void setMoveMem();

  const CGLibDecShader *unknown08; // Inferred role: dec shader; original member name unknown.
  u32 unknown10;                   // Inferred role: index; original member name unknown.
  u32 m_size;
  bool unknown18; // Inferred role: storage buffer; original member name unknown.
};

static_assert(offsetof(CGLibUniBaseUtility, unknown10) == 0x10, "");
static_assert(offsetof(CGLibUniBaseUtility, unknown18) == 0x18, "");

class CGLibUniformEtcUtility : public CGLibUniBaseUtility {
public:
  CGLibUniformEtcUtility(const CGLibDecShader *decShader);
  ~CGLibUniformEtcUtility() override {}
  void setMoveMem() override;
  u8 *getBuff() override;
  void updateData() override;
  void setUniformBlock() override;
  void setStorageBuffer() override;

  CGLibEtcUniformBlock unknown20; // Inferred role: block; original member name unknown.
};

static_assert(offsetof(CGLibUniformEtcUtility, unknown20) == 0x20, "");
static_assert(sizeof(CGLibUniformEtcUtility) == 0x38, "");

} // namespace grlib
