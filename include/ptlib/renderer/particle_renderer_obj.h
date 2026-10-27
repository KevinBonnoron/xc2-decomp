#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "ptlib/renderer/particle_renderer_back_buffer.h"
#include "ptlib/renderer/particle_renderer_shader.h"
#include "types.h"

namespace grlib {
class CGLibDepthBuffer;
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace ptlib {

class StaticAllocObj;
struct DrDrawWorkInfoEF;
struct FxParam;

namespace emitter {
class EmitterManager;
class EmitterObj;
} // namespace emitter

namespace material {
class MaterialBase;
} // namespace material

namespace renderer {

namespace sort {

struct EmitterSort {
  bool unknown00; // Inferred role: opaque; original member name unknown.
  u8 unknown01;   // Inferred role: priority; original member name unknown.
  f32 unknown04;  // Inferred role: depth; original member name unknown.
  bool unknown08; // Inferred role: capture; original member name unknown.
  u8 _09[0x10 - 0x09];
  emitter::EmitterObj *unknown10; // Inferred role: emitter; original member name unknown.
};

static_assert(offsetof(EmitterSort, unknown04) == 0x04, "");
static_assert(offsetof(EmitterSort, unknown08) == 0x08, "");
static_assert(offsetof(EmitterSort, unknown10) == 0x10, "");
static_assert(sizeof(EmitterSort) == 0x18, "");

struct Compare {
  bool operator()(const EmitterSort &sort, const EmitterSort &other) const {
    if (sort.unknown01 < other.unknown01) {
      return true;
    }
    if (sort.unknown01 == other.unknown01) {
      if (sort.unknown00 > other.unknown00) {
        return true;
      }
      if (sort.unknown00 == other.unknown00 && sort.unknown04 < other.unknown04) {
        return true;
      }
    }
    return false;
  }
};

} // namespace sort

class RenderGrObj {
public:
  static const u32 EMITTER_SORT_MAX = 4000;

  RenderGrObj();
  ~RenderGrObj();
  void term();
  void clear();
  BackBuffer *getBackBuffer();
  grlib::CGLibTextureBuffer *getDummyTex();
  grlib::CGLibRenderTarget *getReduceBuffer(u32 index);
  void fxcore_setup_target();
  material::MaterialBase *tex_loadmem(int key, void *data, int size, int format, u8 *userData, bool isResident, void *owner);
  void tex_freemem(int key, void *owner);
  void tex_freemem(void *material, void *owner);
  void fxcore_setup_target_core(int &width, int &height, int &subWidth, int &subHeight);
  void setEffectRenderTarget(grlib::CGLibRenderTarget *target, grlib::CGLibDepthBuffer *depth, grlib::CGLibRenderTarget *subTarget1, grlib::CGLibRenderTarget *subTarget2);
  void fxcore_setup_target_update(int index);
  void *lockStream(emitter::EmitterObj *emitter);
  void unlockStream(emitter::EmitterObj *emitter, int count);
  void draw(emitter::EmitterManager &emitterManager, FxParam &fxParam, int viewIndex, int isBlur);
  void prioritySort(emitter::EmitterManager &emitterManager, int prioIdx, FxParam &fxParam, mm::mtl::FixedVector<sort::EmitterSort, EMITTER_SORT_MAX> &sorts);

  BackBuffer unknown00; // Inferred role: back buffers; original member name unknown.
  u8 _30[0x40 - 0x30];
  void *unknown40; // Inferred role: cleared by the constructor; original member name unknown.
  void *unknown48; // Inferred role: cleared by the constructor; original member name unknown.
  void *unknown50; // Inferred role: cleared by the constructor; original member name unknown.
  u8 _58[0x60 - 0x58];
  mm::Vec3 unknown60; // Inferred role: reset by the constructor; original member name unknown.
  void *unknown70;    // Inferred role: cleared by the constructor; original member name unknown.
  u8 _78[0x80 - 0x78];
  void *unknown80;         // Inferred role: cleared by the constructor; original member name unknown.
  void *unknown88;         // Inferred role: cleared by the constructor; original member name unknown.
  void *unknown90;         // Inferred role: cleared by the constructor; original member name unknown.
  void *unknown98;         // Inferred role: cleared by the constructor; original member name unknown.
  void *unknowna0;         // Inferred role: cleared by the constructor; original member name unknown.
  void *unknowna8;         // Inferred role: cleared by the constructor; original member name unknown.
  ShaderManager unknownb0; // Inferred role: shaders; original member name unknown.
  u8 _250[0x258 - 0x250];
  const DrDrawWorkInfoEF *unknown258; // Inferred role: draw work info; original member name unknown.
  void *unknown260;                   // Inferred role: cleared by the constructor; original member name unknown.
  StaticAllocObj *unknown268;         // Inferred role: allocator; original member name unknown.
  s32 unknown270;                     // Inferred role: render target state; original member name unknown.
  u8 _274[0x280 - 0x274];
};

static_assert(offsetof(RenderGrObj, unknown40) == 0x40, "");
static_assert(offsetof(RenderGrObj, unknown50) == 0x50, "");
static_assert(offsetof(RenderGrObj, unknown60) == 0x60, "");
static_assert(offsetof(RenderGrObj, unknown70) == 0x70, "");
static_assert(offsetof(RenderGrObj, unknown80) == 0x80, "");
static_assert(offsetof(RenderGrObj, unknowna8) == 0xa8, "");
static_assert(offsetof(RenderGrObj, unknownb0) == 0xb0, "");
static_assert(offsetof(RenderGrObj, unknown258) == 0x258, "");
static_assert(offsetof(RenderGrObj, unknown260) == 0x260, "");
static_assert(offsetof(RenderGrObj, unknown268) == 0x268, "");
static_assert(offsetof(RenderGrObj, unknown270) == 0x270, "");
static_assert(sizeof(RenderGrObj) == 0x280, "");

} // namespace renderer
} // namespace ptlib
