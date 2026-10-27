#include "ptlib/renderer/particle_renderer_obj.h"

#include <algorithm>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3_na.h"
#include "mm_mtl/fixed_vector.h"
#include "ptlib/emitter/particle_emitter.h"
#include "ptlib/emitter/particle_emitter_manager.h"
#include "ptlib/emitter/particle_emitter_param.h"
#include "ptlib/particle_system.h"

namespace ptlib {
namespace renderer {

constexpr int ARG_DRAW_TYPE_NONE = 5;
constexpr int PRIORITY_MAX = 0xff;

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
