#include "ptlib/renderer/particle_renderer_obj.h"

#include <algorithm>

#include "grlib/cglib_render_target.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_manager.h"
#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/material/particle_material_manager.h"
#include "ptlib/particle_system.h"

// clang-format off
#include "particle_renderer_shader.cpp"
// clang-format on

namespace ptlib {
namespace renderer {

constexpr int ARG_DRAW_TYPE_NONE = 5;
constexpr int PRIORITY_MAX = 0xff;

RenderGrObj::RenderGrObj() : unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown60(mm::Vec3::zero), unknown70(nullptr) {
  clear();
  unknown80 = nullptr;
  unknown88 = nullptr;
  unknown90 = nullptr;
  unknown98 = nullptr;
  unknowna0 = nullptr;
  unknowna8 = nullptr;
  unknown260 = nullptr;
  unknown270 = 0;
}

RenderGrObj::~RenderGrObj() { term(); }

void RenderGrObj::clear() { unknown00.unknown002(); }

BackBuffer *RenderGrObj::getBackBuffer() { return &unknown00; }

grlib::CGLibTextureBuffer *RenderGrObj::getDummyTex() { return unknown00.unknown20->unknown70; }

grlib::CGLibRenderTarget *RenderGrObj::getReduceBuffer(u32 index) { return unknown258->unknown060; }

void RenderGrObj::fxcore_setup_target() {
  grlib::CGLibRenderTarget *target = unknown258->unknown000;
  grlib::CGLibRenderTarget *subTarget = unknown258->unknown068;
  unknown00.createAll(
      unknown268, static_cast<s32>(target->unknownbc), static_cast<s32>(target->unknownc0), static_cast<s32>(subTarget->unknownbc), static_cast<s32>(subTarget->unknownc0), unknown258->unknown1d0);
}

material::MaterialBase *RenderGrObj::tex_loadmem(int key, void *data, int size, int format, u8 *userData, bool isResident, void *owner) {
  material::MaterialBase *material = material::MaterialManager::getPtr()->create(key, material::eMaterialType_UNKNOWN_0, data, size, false, userData, owner, format);
  if (material != nullptr && isResident) {
    material->unknown3c = true;
  }
  return material;
}

void RenderGrObj::tex_freemem(int key, void *owner) {
  int materialKey = key;
  material::MaterialManager::getPtr()->destroyMateriaByKey(materialKey, owner);
}

void RenderGrObj::tex_freemem(void *material, void *owner) { material::MaterialManager::getPtr()->destroyMateriaByKey(material, owner); }

void RenderGrObj::fxcore_setup_target_core(int &width, int &height, int &subWidth, int &subHeight) {
  width = unknown258->unknown000->unknownbc;
  height = unknown258->unknown000->unknownc0;
  subWidth = unknown258->unknown068->unknownbc;
  subHeight = unknown258->unknown068->unknownc0;
}

void RenderGrObj::setEffectRenderTarget(grlib::CGLibRenderTarget *target, grlib::CGLibDepthBuffer *depth, grlib::CGLibRenderTarget *subTarget1, grlib::CGLibRenderTarget *subTarget2) {
  if (subTarget1 == nullptr) {
    if (depth == nullptr) {
      if (subTarget2 != nullptr) {
        target->setRenderTarget(*subTarget2);
        return;
      }
      target->setRenderTarget();
      return;
    }
    if (subTarget2 != nullptr) {
      target->setRenderTarget(*depth, *subTarget2);
      return;
    }
    target->setRenderTarget(*depth);
    return;
  }
  if (depth == nullptr) {
    if (subTarget2 != nullptr) {
      target->setRenderTarget(*subTarget1, *subTarget2);
      return;
    }
    target->setRenderTarget(*subTarget1);
    return;
  }
  if (subTarget2 != nullptr) {
    target->setRenderTarget(*depth, *subTarget1, *subTarget2);
    return;
  }
  target->setRenderTarget(*depth, *subTarget1);
}

void *RenderGrObj::lockStream(emitter::EmitterObj *emitter) {
  if (emitter != nullptr) {
    return emitter->lockStream(unknown258);
  }
  return nullptr;
}

void RenderGrObj::unlockStream(emitter::EmitterObj *emitter, int count) {
  if (emitter != nullptr) {
    emitter->unlockStream(unknown258, count);
  }
}

void RenderGrObj::term() {
  unknown00.unknown001();
  unknownb0.term();
}

void RenderGrObj::prioritySort(emitter::EmitterManager &emitterManager, int prioIdx, FxParam &fxParam, mm::mtl::FixedVector<sort::EmitterSort, EMITTER_SORT_MAX> &sorts) {
  const CamParam &camParam = ParticleManager::get()->getCamParam();
  if (!ParticleManager::get()->unknown168) {
    return;
  }
  for (emitter::EmitterObj *emitter = emitterManager.unknown1750; emitter != nullptr; emitter = emitter->unknownc8) {
    if (emitter->isRenderCheck() && emitter->unknown274 == prioIdx && emitter->unknown151 && emitter->unknown12c > 0.0f && emitter->unknown98 != nullptr &&
        emitter->unknown98->unknown100 != ARG_DRAW_TYPE_NONE) {
      const mm::Mat44 &view = camParam.m_viewMatrix;
      sort::EmitterSort entry;
      entry.unknown00 = emitter->unknown98->unknownfc == 0;
      int priority = emitter->unknown260 + emitter->unknown150;
      if (priority < 0) {
        priority = 0;
      }
      if (priority > PRIORITY_MAX) {
        priority = PRIORITY_MAX;
      }
      entry.unknown01 = priority;
      entry.unknown04 = emitter->unknowne0.unknown30.x * view.rows[0][2] + emitter->unknowne0.unknown30.y * view.rows[1][2] + emitter->unknowne0.unknown30.z * view.rows[2][2] + view.rows[3][2];
      entry.unknown08 = false;
      entry.unknown10 = emitter;
      sorts.push_back(entry);
    }
  }
  std::stable_sort(sorts.begin(), sorts.end(), sort::Compare());
}

} // namespace renderer
} // namespace ptlib
