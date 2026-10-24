#include "anm/anm_asm_simplex.h"

#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "mm_mtl/vector.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

SimplexState::SimplexState(const ResStateData *pResStateData, mm::mtl::IAllocator &allocator) : AsmState(pResStateData, allocator) { m_clip.createControl(pResStateData->unknown08[0], allocator); }

SimplexState::~SimplexState() { m_clip.destroyControl(); }

void SimplexState::attach(AsmBlender *blender) { blender->addClip(m_clip); }

void SimplexState::dettach(AsmBlender *blender) { blender->removeClip(m_clip); }

void SimplexState::onEnter(AsmListener *listener) {
  initLoopCount();
  setSpeed(1.0f);
  notifyEnter(listener);
}

void SimplexState::onLeave(AsmListener *listener) { notifyLeave(listener); }

void SimplexState::update(f32 deltaTime, AsmListener *listener) { updateLoopCount(m_clip.update(deltaTime, listener)); }

void SimplexState::onSetSpeed() { m_clip.setSpeed(unknown20); }

void SimplexState::onSetWeight() { m_clip.setWeight(unknown24); }

void SimplexState::setLocalTime(f32 time) { m_clip.setLocalTime(time); }

f32 SimplexState::getLocalTime() const { return m_clip.getLocalTime(); }

const AsmClip *SimplexState::getBaseClip() const { return &m_clip; }

} // namespace anm
