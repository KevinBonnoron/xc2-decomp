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

void GfComAsm::procMsgObjectSetAsmPlaybackSpeed(fw::MessageObject *sender, MsgObjectSetAsmPlaybackSpeed &message) {
  setSpeed(message.speed, message.layer);
}

void GfComAsm::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComAsm::GfComAsm() : asmControl(nullptr), callbackCaches(getAllocator(ALLOCATOR_DEFAULT)), viewer(nullptr) {
  listener.owner = this;
  viewerListener.owner = this;
}

GfComAsm::~GfComAsm() {}

void GfComAsm::cleanup() {
  callbackCaches.clear();
  if (asmControl == nullptr) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    if (poseSampler.asmControl != nullptr && poseSampler.pose != nullptr) {
      manager->removePoseSampler(getLayer(), poseSampler);
      poseSampler.unbind();
    }
    if (updater.asmControl != nullptr) {
      manager->removeControlUpdater(getLayer(), updater);
      updater.unbind();
    }
  }

  if (asmControl != nullptr) {
    asmControl->release();
    asmControl = nullptr;
  }
}

void GfComAsm::clearCallback() { callbackCaches.clear(); }

const anm::ResASM *GfComAsm::getResource() const {
  if (asmControl != nullptr) {
    return asmControl->resAsm;
  }

  return nullptr;
}

bool GfComAsm::getPlaybackTime(const char *state, f32 *time) const {
  if (asmControl != nullptr && asmControl->resAsm != nullptr) {
    return anm::Util::getAsmPlaybackTime(*asmControl->resAsm, state, 0, time);
  }

  return false;
}

bool GfComAsm::getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const {
  if (asmControl != nullptr && asmControl->resAsm != nullptr) {
    return anm::Util::getAsmLocomotionReference(*asmControl->resAsm, state, time, 0, transform);
  }

  return false;
}

bool GfComAsm::getLocomotionDeltaReference(const char *state, f32 startTime, f32 endTime, anm::QsTransform *transform) const {
  if (asmControl != nullptr && asmControl->resAsm != nullptr) {
    return anm::Util::getAsmLocomotionDeltaReference(*asmControl->resAsm, state, startTime, endTime, 0, transform);
  }

  return false;
}

bool GfComAsm::getClipInvFps(const char *state, u32 index, f32 *invFps) const {
  if (asmControl == nullptr) {
    return false;
  }

  const anm::ResASM *resAsm = asmControl->resAsm;
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
  if (asmControl == nullptr) {
    return false;
  }

  const anm::ResASM *resAsm = asmControl->resAsm;
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
  if (asmControl == nullptr) {
    return false;
  }

  const anm::ResASM *resAsm = asmControl->resAsm;
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
  if (asmControl == nullptr) {
    return nullptr;
  }

  const anm::ResASM *resAsm = asmControl->resAsm;
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
  if (asmControl != nullptr && asmControl->resAsm != nullptr && asmControl->resAsm->findResStateData(state) != nullptr) {
    return true;
  }

  return false;
}

void GfComAsm::executeCallback() {
  for (u32 i = 0; i < callbackCaches.size(); i++) {
    const anm::AsmAnnotetion *annotation = callbackCaches[i].annotation;
    u32 index;
    for (index = 1; index < CALLBACK_MAX; index++) {
      if (callbacks[index].delegate.isValid() && strcmp(callbacks[index].name, annotation->name) == 0) {
        break;
      }
    }

    if (index < CALLBACK_MAX) {
      callbacks[index].delegate(this, callbackCaches[i]);
    } else if (callbacks[0].delegate.isValid()) {
      callbacks[0].delegate(this, callbackCaches[i]);
    }
  }

  callbackCaches.clear();
}

bool GfComAsm::execCmd(const char *command, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->executeCmd(command);
  }

  return false;
}

const char *GfComAsm::getStateName(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getStateName();
  }

  return nullptr;
}

bool GfComAsm::setState(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setState(state);
  }

  return false;
}

void GfComAsm::clearState(AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    stateMachine->clearState();
  }
}

bool GfComAsm::resetState(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->resetState(state);
  }

  return false;
}

bool GfComAsm::easeIn(const char *state, f32 time, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseInAdditive(state, time);
  }

  return false;
}

bool GfComAsm::easeOut(const char *state, f32 time, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseOutAdditive(state, time);
  }

  return false;
}

void GfComAsm::clearAdditiveState(AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    stateMachine->clearAdditiveState();
  }
}

bool GfComAsm::setWeightAdditiveState(const char *state, f32 weight, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateWeight(state, weight);
  }

  return false;
}

bool GfComAsm::setSpeedAdditiveState(const char *state, f32 speed, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateSpeed(state, speed);
  }

  return false;
}

bool GfComAsm::isEnd(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->isEnd();
  }

  return false;
}

bool GfComAsm::isLoop(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->isLoop();
  }

  return false;
}

bool GfComAsm::isInterpolate(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  return stateMachine != nullptr && stateMachine->m_pInterpolateInfo != nullptr;
}

void GfComAsm::setLocalTime(f32 time, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    stateMachine->setLocalTime(time);
  }
}

f32 GfComAsm::getLocalTime(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getLocalTime();
  }

  return 0.0f;
}

void GfComAsm::setSpeed(f32 speed, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    stateMachine->setSpeed(speed);
  }
}

f32 GfComAsm::getSpeed(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getSpeed();
  }

  return 0.0f;
}

u64 GfComAsm::getAttribute(AsmCategory category, AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getAttribute(category);
  }

  return 0;
}

const anm::QsTransform &GfComAsm::getLocomotion() const {
  if (asmControl != nullptr) {
    return asmControl->locomotion;
  }

  static const anm::QsTransform identity(mm::Vec3::zero, mm::Quat::identity, mm::Vec3::unit);
  return identity;
}

void GfComAsm::setVariable(const char *name, f32 value) {
  if (asmControl != nullptr) {
    asmControl->setVariable(name, value);
  }
}

void GfComAsm::getVariable(const char *name, f32 *value) const {
  if (asmControl != nullptr) {
    asmControl->getVariable(name, value);
  }
}

void GfComAsm::setVariable(const char *name, int value) {
  if (asmControl != nullptr) {
    asmControl->setVariable(name, value);
  }
}

void GfComAsm::getVariable(const char *name, int *value) const {
  if (asmControl != nullptr) {
    asmControl->getVariable(name, value);
  }
}

void GfComAsm::cacheCallback(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion &annotation) {
  callbackCaches.push_back(CallBackCache(type, &annotation));
}

void GfComAsm::changeLayer(u32 oldLayer, u32 newLayer) {
  if (oldLayer == newLayer) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (poseSampler.asmControl != nullptr && poseSampler.pose != nullptr) {
    manager->removePoseSampler(getLayer(), poseSampler);
    manager->addPoseSampler(newLayer, poseSampler);
  }
  if (updater.asmControl != nullptr) {
    manager->removeControlUpdater(getLayer(), updater);
    manager->addControlUpdater(newLayer, updater);
  }
}

const mm::mtl::RTTI *GfComAsm::getRTTI() const { return &m_rtti; }

} // namespace gf
