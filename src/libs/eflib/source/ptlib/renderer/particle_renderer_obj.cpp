#include "ptlib/renderer/particle_renderer_obj.h"

#include <algorithm>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_manager.h"
#include "ptlib/particle_system.h"

namespace ptlib {
namespace renderer {

constexpr int ARG_DRAW_TYPE_NONE = 5;
constexpr int PRIORITY_MAX = 0xff;

void RenderGrObj::prioritySort(emitter::EmitterManager &emitterManager, int prioIdx, FxParam &fxParam,
                               mm::mtl::FixedVector<sort::EmitterSort, EMITTER_SORT_MAX> &sorts) {
  const CamParam &camParam = ParticleManager::get()->getCamParam();
  if (!ParticleManager::get()->m_isAllDisp) {
    return;
  }
  for (emitter::EmitterObj *emitter = emitterManager.m_pEmitterTop; emitter != nullptr; emitter = emitter->m_pNext) {
    if (emitter->isRenderCheck() && emitter->m_prioIdx == prioIdx && emitter->m_isDisp && emitter->m_alpha > 0.0f && emitter->m_pArg != nullptr &&
        emitter->m_pArg->m_drawType != ARG_DRAW_TYPE_NONE) {
      const mm::Mat44 &view = camParam.m_viewMatrix;
      sort::EmitterSort entry;
      entry.isOpaque = emitter->m_pArg->m_blendMode == 0;
      int priority = emitter->m_priority + emitter->m_priorityOffset;
      if (priority < 0) {
        priority = 0;
      }
      if (priority > PRIORITY_MAX) {
        priority = PRIORITY_MAX;
      }
      entry.priority = priority;
      entry.depth = emitter->m_pos.x * view.rows[0][2] + emitter->m_pos.y * view.rows[1][2] + emitter->m_pos.z * view.rows[2][2] + view.rows[3][2];
      entry.isCapture = false;
      entry.emitter = emitter;
      sorts.push_back(entry);
    }
  }
  std::stable_sort(sorts.begin(), sorts.end(), sort::Compare());
}

} // namespace renderer
} // namespace ptlib
