#pragma once
#include <stddef.h>

#include "types.h"

namespace ptlib {

class StaticAllocObj;
struct DrDrawWorkInfoEF;
struct FxParam;

namespace emitter {
struct EmitterArg;
class EmitterManager;
class EmitterObj;
} // namespace emitter

namespace material {
class MaterialBase;
} // namespace material

namespace renderer {

class EffStateManager;
class RenderGrObj;

// Layout evidence: init 0x7100938ccc, term 0x7100938efc.
class RenderManager {
public:
  static RenderManager *get();
  static RenderManager *&getPtr();
  static void init(const DrDrawWorkInfoEF *info, FxParam *fxParam);
  static void term();
  void setDrInfo(const DrDrawWorkInfoEF *info);
  const DrDrawWorkInfoEF *getDrInfo();
  RenderGrObj *getRenderGrObj();
  void setEmitterDraw(emitter::EmitterObj *emitter, emitter::EmitterArg *arg);
  void fxcore_setup_target_update(int index);
  void fxcore_setup_target();
  void draw(emitter::EmitterManager &emitterManager, FxParam &fxParam, int viewIndex, int isBlur);
  material::MaterialBase *tex_loadmem(int key, void *data, int size, int format, u8 *userData, bool isResident, void *owner);
  void tex_freemem(int key, void *owner);
  void tex_freemem(void *material, void *owner);

  FxParam *unknown00;         // Inferred role: effect parameters; original member name unknown.
  RenderGrObj *unknown08;     // Inferred role: renderer; original member name unknown.
  StaticAllocObj *unknown10;  // Inferred role: allocator; original member name unknown.
  EffStateManager *unknown18; // Inferred role: state manager; original member name unknown.
};

static_assert(offsetof(RenderManager, unknown08) == 0x08, "");
static_assert(offsetof(RenderManager, unknown10) == 0x10, "");
static_assert(offsetof(RenderManager, unknown18) == 0x18, "");
static_assert(sizeof(RenderManager) == 0x20, "");

} // namespace renderer
} // namespace ptlib
