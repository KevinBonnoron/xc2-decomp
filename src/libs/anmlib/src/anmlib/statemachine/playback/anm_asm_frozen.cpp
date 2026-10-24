#include "anm/anm_asm_frozen.h"

#include "anm/anm_res_clip_data.h"
#include "anm/anm_res_state_data.h"
#include "mm_mtl/vector.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

FrozenState::FrozenState(const ResStateData *pResStateData, mm::mtl::IAllocator &allocator) : AsmState(pResStateData, allocator) { m_clip.createControl(pResStateData->unknown08[0], allocator); }

FrozenState::~FrozenState() { m_clip.destroyControl(); }

void FrozenState::attach(AsmBlender *blender) { blender->addClip(m_clip); }

void FrozenState::dettach(AsmBlender *blender) { blender->removeClip(m_clip); }

void FrozenState::onEnter(AsmListener *listener) {
  m_clip.setLocalTime(unknown18->unknown08[0].unknown10);
  m_clip.setSpeed(0.0f);
  notifyEnter(listener);
}

void FrozenState::onLeave(AsmListener *listener) { notifyLeave(listener); }

void FrozenState::update(f32 deltaTime, AsmListener *listener) {}

f32 FrozenState::getLocalTime() const { return m_clip.getLocalTime(); }

void FrozenState::onSetWeight() { m_clip.setWeight(unknown24); }

void FrozenState::setLocalTime(f32 time) {}

void FrozenState::onSetSpeed() {}

const AsmClip *FrozenState::getBaseClip() const { return &m_clip; }

} // namespace anm
