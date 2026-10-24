#include "gf/object/component/animation/gf_com_asm.h"

#include <string.h>

#include "anm/anm_asm_control.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_res_asm.h"
#include "anm/anm_res_state_data.h"
#include "anm/anm_state_machine.h"
#include "anm/anm_util.h"
#include "framework/anim/anim_manager.h"
#include "gf/gf_allocator.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace anm {
class Binding;
} // namespace anm

namespace gf {
struct MsgDebugActivateComponentWindow;

void GfComAsm::procMsgObjectSetAsmPlaybackSpeed(fw::MessageObject *sender, MsgObjectSetAsmPlaybackSpeed &message) { setSpeed(message.unknown08, message.unknown0c); }

void GfComAsm::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComAsm::GfComAsm() : unknown10(nullptr), unknown148(getAllocator(ALLOCATOR_DEFAULT)), unknown180(nullptr) {
  unknown138.unknown08 = this;
  unknown170.unknown08 = this;
}

GfComAsm::~GfComAsm() {}

void GfComAsm::cleanup() {
  unknown148.clear();
  if (unknown10 == nullptr) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (unknown38.asmControl != nullptr && unknown38.pose != nullptr) {
      manager->removePoseSampler(getLayer(), unknown38);
      unknown38.unbind();
    }
    if (unknown18.asmControl != nullptr) {
      manager->removeControlUpdater(getLayer(), unknown18);
      unknown18.unbind();
    }
  }

  if (unknown10 != nullptr) {
    unknown10->release();
    unknown10 = nullptr;
  }
}

void GfComAsm::clearCallback() { unknown148.clear(); }

const anm::ResASM *GfComAsm::getResource() const {
  if (unknown10 != nullptr) {
    return unknown10->resAsm;
  }

  return nullptr;
}

bool GfComAsm::getPlaybackTime(const char *state, f32 *time) const {
  if (unknown10 != nullptr && unknown10->resAsm != nullptr) {
    return anm::Util::getAsmPlaybackTime(*unknown10->resAsm, state, 0, time);
  }

  return false;
}

bool GfComAsm::getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const {
  if (unknown10 != nullptr && unknown10->resAsm != nullptr) {
    return anm::Util::getAsmLocomotionReference(*unknown10->resAsm, state, time, 0, transform);
  }

  return false;
}

bool GfComAsm::getLocomotionDeltaReference(const char *state, f32 startTime, f32 endTime, anm::QsTransform *transform) const {
  if (unknown10 != nullptr && unknown10->resAsm != nullptr) {
    return anm::Util::getAsmLocomotionDeltaReference(*unknown10->resAsm, state, startTime, endTime, 0, transform);
  }

  return false;
}

bool GfComAsm::getClipInvFps(const char *state, u32 index, f32 *invFps) const {
  if (unknown10 == nullptr) {
    return false;
  }

  const anm::ResASM *resAsm = unknown10->resAsm;
  if (resAsm == nullptr) {
    return false;
  }

  const anm::Binding *binding = anm::Util::getAsmBinding(*resAsm, state, index);
  if (binding == nullptr) {
    return false;
  }

  *invFps = anm::Util::getInvFps(*binding);
  return true;
}

bool GfComAsm::getClipFps(const char *state, u32 index, f32 *fps) const {
  if (unknown10 == nullptr) {
    return false;
  }

  const anm::ResASM *resAsm = unknown10->resAsm;
  if (resAsm == nullptr) {
    return false;
  }

  const anm::Binding *binding = anm::Util::getAsmBinding(*resAsm, state, index);
  if (binding == nullptr) {
    return false;
  }

  *fps = anm::Util::getFps(*binding);
  return true;
}

bool GfComAsm::existEndTrans(const char *state) {
  if (unknown10 == nullptr) {
    return false;
  }

  const anm::ResASM *resAsm = unknown10->resAsm;
  if (resAsm == nullptr) {
    return false;
  }

  const anm::ResStateData *stateData = resAsm->findResStateData(state);
  if (stateData == nullptr) {
    return false;
  }

  return stateData->m_pResState->loopCount != nullptr;
}

const void *GfComAsm::getAppendix(const char *name) const {
  if (unknown10 == nullptr) {
    return nullptr;
  }

  const anm::ResASM *resAsm = unknown10->resAsm;
  if (resAsm == nullptr) {
    return nullptr;
  }

  const anm::Appendix *appendix = anm::Util::findAppendix(*resAsm, name);
  if (appendix == nullptr) {
    return nullptr;
  }

  return appendix->data;
}

bool GfComAsm::existState(const char *state) {
  if (unknown10 != nullptr && unknown10->resAsm != nullptr && unknown10->resAsm->findResStateData(state) != nullptr) {
    return true;
  }

  return false;
}

void GfComAsm::executeCallback() {
  for (u32 i = 0; i < unknown148.size(); i++) {
    const anm::AsmAnnotetion *annotation = unknown148[i].unknown08;
    u32 index;
    for (index = 1; index < CALLBACK_MAX; index++) {
      if (unknown70[index].unknown08.isValid() && strcmp(unknown70[index].unknown00, annotation->name) == 0) {
        break;
      }
    }

    if (index < CALLBACK_MAX) {
      unknown70[index].unknown08(this, unknown148[i]);
    } else if (unknown70[0].unknown08.isValid()) {
      unknown70[0].unknown08(this, unknown148[i]);
    }
  }

  unknown148.clear();
}

bool GfComAsm::execCmd(const char *command, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->executeCmd(command);
  }

  return false;
}

const char *GfComAsm::getStateName(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getStateName();
  }

  return nullptr;
}

bool GfComAsm::setState(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setState(state);
  }

  return false;
}

void GfComAsm::clearState(AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    stateMachine->clearState();
  }
}

bool GfComAsm::resetState(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->resetState(state);
  }

  return false;
}

bool GfComAsm::easeIn(const char *state, f32 time, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseInAdditive(state, time);
  }

  return false;
}

bool GfComAsm::easeOut(const char *state, f32 time, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseOutAdditive(state, time);
  }

  return false;
}

void GfComAsm::clearAdditiveState(AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    stateMachine->clearAdditiveState();
  }
}

bool GfComAsm::setWeightAdditiveState(const char *state, f32 weight, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateWeight(state, weight);
  }

  return false;
}

bool GfComAsm::setSpeedAdditiveState(const char *state, f32 speed, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateSpeed(state, speed);
  }

  return false;
}

bool GfComAsm::isEnd(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->isEnd();
  }

  return false;
}

bool GfComAsm::isLoop(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->isLoop();
  }

  return false;
}

bool GfComAsm::isInterpolate(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  return stateMachine != nullptr && stateMachine->m_pInterpolateInfo != nullptr;
}

void GfComAsm::setLocalTime(f32 time, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    stateMachine->setLocalTime(time);
  }
}

f32 GfComAsm::getLocalTime(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getLocalTime();
  }

  return 0.0f;
}

void GfComAsm::setSpeed(f32 speed, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    stateMachine->setSpeed(speed);
  }
}

f32 GfComAsm::getSpeed(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getSpeed();
  }

  return 0.0f;
}

u64 GfComAsm::getAttribute(AsmCategory category, AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getAttribute(category);
  }

  return 0;
}

const anm::QsTransform &GfComAsm::getLocomotion() const {
  if (unknown10 != nullptr) {
    return unknown10->locomotion;
  }

  static const anm::QsTransform identity(mm::Vec3::zero, mm::Quat::identity, mm::Vec3::unit);
  return identity;
}

void GfComAsm::setVariable(const char *name, f32 value) {
  if (unknown10 != nullptr) {
    unknown10->setVariable(name, value);
  }
}

void GfComAsm::getVariable(const char *name, f32 *value) const {
  if (unknown10 != nullptr) {
    unknown10->getVariable(name, value);
  }
}

void GfComAsm::setVariable(const char *name, int value) {
  if (unknown10 != nullptr) {
    unknown10->setVariable(name, value);
  }
}

void GfComAsm::getVariable(const char *name, int *value) const {
  if (unknown10 != nullptr) {
    unknown10->getVariable(name, value);
  }
}

void GfComAsm::cacheCallback(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion &annotation) { unknown148.push_back(CallBackCache(type, &annotation)); }

void GfComAsm::changeLayer(u32 oldLayer, u32 newLayer) {
  if (oldLayer == newLayer) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (unknown38.asmControl != nullptr && unknown38.pose != nullptr) {
    manager->removePoseSampler(getLayer(), unknown38);
    manager->addPoseSampler(newLayer, unknown38);
  }
  if (unknown18.asmControl != nullptr) {
    manager->removeControlUpdater(getLayer(), unknown18);
    manager->addControlUpdater(newLayer, unknown18);
  }
}

const mm::mtl::RTTI *GfComAsm::getRTTI() const { return &m_rtti; }

} // namespace gf
