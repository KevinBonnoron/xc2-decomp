#include "ptlib/renderer/particle_renderer_manager.h"

#include "mm/mm_std_base.h"
#include "ptlib/particle_stack_allocater.h"
#include "ptlib/particle_system.h"
#include "ptlib/renderer/particle_renderer_eff_state.h"
#include "ptlib/renderer/particle_renderer_obj.h"
// The game executable compiles the RenderGrObj and ShaderManager functions in this translation unit, where they are inlined into the RenderManager functions.
// clang-format off
#include "particle_renderer_obj.cpp"
// clang-format on

namespace ptlib {
namespace renderer {

namespace {
RenderManager *unknown002;
} // namespace

RenderManager *RenderManager::get() {
#line 17
  MM_ASSERT(getPtr());
  return getPtr();
}

RenderManager *&RenderManager::getPtr() { return unknown002; }

void RenderManager::term() {
  if (unknown002 != nullptr) {
    unknown002->unknown08->term();
    unknown002->unknown08->~RenderGrObj();
    unknown002->unknown18->~EffStateManager();
    unknown002->unknown00 = nullptr;
    StaticAllocObj::destroy(unknown002->unknown10);
    unknown002 = nullptr;
  } else {
    efAstMsg("0", "initialize error");
  }
}

void RenderManager::setDrInfo(const DrDrawWorkInfoEF *info) {
  if (unknown08 != nullptr) {
    unknown08->unknown258 = info;
  }
}

const DrDrawWorkInfoEF *RenderManager::getDrInfo() {
  if (unknown08 != nullptr) {
    return unknown08->unknown258;
  }
  return nullptr;
}

RenderGrObj *RenderManager::getRenderGrObj() { return unknown08; }

void RenderManager::fxcore_setup_target_update(int index) {
  if (unknown08 != nullptr) {
    unknown08->fxcore_setup_target_update(index);
  }
}

void RenderManager::fxcore_setup_target() {
  if (unknown08 != nullptr) {
    unknown08->fxcore_setup_target();
  }
}

void RenderManager::draw(emitter::EmitterManager &emitterManager, FxParam &fxParam, int viewIndex, int isBlur) {
  if (unknown08 != nullptr) {
    unknown08->fxcore_setup_target_update(viewIndex);
    if (unknown08 != nullptr) {
      unknown08->draw(emitterManager, fxParam, viewIndex, isBlur);
    }
  }
}

material::MaterialBase *RenderManager::tex_loadmem(int key, void *data, int size, int format, u8 *userData, bool isResident, void *owner) {
  if (unknown08 == nullptr) {
    return nullptr;
  }
  return unknown08->tex_loadmem(key, data, size, format, userData, isResident, owner);
}

void RenderManager::tex_freemem(int key, void *owner) {
  if (unknown08 != nullptr) {
    unknown08->tex_freemem(key, owner);
  }
}

void RenderManager::tex_freemem(void *material, void *owner) {
  if (unknown08 != nullptr) {
    unknown08->tex_freemem(material, owner);
  }
}

} // namespace renderer
} // namespace ptlib
