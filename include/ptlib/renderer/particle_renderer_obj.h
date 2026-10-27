#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "ptlib/renderer/particle_renderer_back_buffer.h"
#include "ptlib/renderer/particle_renderer_shader.h"
#include "types.h"

namespace grlib {
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
  void fxcore_setup_target_update(int index);
  void draw(emitter::EmitterManager &emitterManager, FxParam &fxParam, int viewIndex, int isBlur);
  void prioritySort(emitter::EmitterManager &emitterManager, int prioIdx, FxParam &fxParam, mm::mtl::FixedVector<sort::EmitterSort, EMITTER_SORT_MAX> &sorts);

  BackBuffer unknown00; // Inferred role: back buffers; original member name unknown.
  u8 _30[0xb0 - 0x30];
  ShaderManager unknownb0; // Inferred role: shaders; original member name unknown.
  u8 _250[0x258 - 0x250];
  const DrDrawWorkInfoEF *unknown258; // Inferred role: draw work info; original member name unknown.
  u8 _260[0x268 - 0x260];
  StaticAllocObj *unknown268; // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(RenderGrObj, unknownb0) == 0xb0, "");
static_assert(offsetof(RenderGrObj, unknown258) == 0x258, "");
static_assert(offsetof(RenderGrObj, unknown268) == 0x268, "");

} // namespace renderer
} // namespace ptlib
