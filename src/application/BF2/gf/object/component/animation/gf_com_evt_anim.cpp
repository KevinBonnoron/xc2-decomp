#include "gf/object/component/animation/gf_com_evt_anim.h"

#include <string.h>

#include "anm/anm_animation_importer.h"
#include "anm/anm_asm_control.h"
#include "anm/anm_binding.h"
#include "anm/anm_blender.h"
#include "anm/anm_control.h"
#include "anm/anm_factory.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_state_machine.h"
#include "anm/anm_util.h"
#include "framework/anim/anim_manager.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"

namespace anm {
class ExtraTruckBuffer;
class Pose;
} // namespace anm

namespace gf {

bool GfComEvtAnim::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.id == MSG_DEBUG_ACTIVATE_COMPONENT_WINDOW) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComEvtAnim::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComEvtAnim::Asm::Asm() : model(nullptr), asmControl(nullptr), callbackCaches(getAllocator(ALLOCATOR_DEFAULT)), viewer(nullptr) {
  listener.owner = this;
  viewerListener.owner = this;
}

void GfComEvtAnim::Asm::cleanup(u32 layer) {
  if (asmControl == nullptr) {
    return;
  }

  if (flags.test(FLAG_REGISTERED)) {
    fw::AnimationManager *manager = fw::AnimationManager::get();
    if (manager != nullptr) {
      manager->removePoseSampler(layer, poseSampler);
      manager->removeControlUpdater(layer, updater);
    }
    flags.set(FLAG_REGISTERED, false);
  }

  poseSampler.unbind();
  updater.unbind();
  callbackCaches.clear();
  asmControl->setListener(nullptr);
  if (asmControl != nullptr) {
    asmControl->release();
    asmControl = nullptr;
  }
}

void GfComEvtAnim::Asm::setup(u32 layer, GfComModel *model, anm::ResASM *resAsm, const char *state, bool isLocalSpace) {
  this->model = model;
  if (resAsm == nullptr) {
    return;
  }

  anm::Pose *pose = model->pose;
  if (pose == nullptr) {
    return;
  }

  anm::ExtraTruckBuffer *extraTruckBuffer = model->extraTruckBuffer;
  asmControl = anm::Factory::createASMControl(*resAsm, *getAllocator(ALLOCATOR_ANIMATION));
  updater.bind(asmControl);
  if (updater.asmControl == nullptr) {
    return;
  }

  poseSampler.isLocalSpace = isLocalSpace;
  poseSampler.bind(asmControl, pose, extraTruckBuffer);
  if (poseSampler.asmControl == nullptr || poseSampler.pose == nullptr) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    manager->addControlUpdater(layer, updater);
    manager->addPoseSampler(layer, poseSampler);
    flags.set(FLAG_REGISTERED);
  }

  asmControl->setListener(&listener);
  callbackCaches.reserve(32);
  asmControl->m_stateMachines[ANIM_LAYER_BASE].setState(state);
  asmControl->m_stateMachines[ANIM_LAYER_BASE].executeCmd("C_idle");
}

void GfComEvtAnim::Asm::changeLayer(u32 oldLayer, u32 newLayer) {
  if (asmControl == nullptr || !flags.test(FLAG_REGISTERED)) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (poseSampler.asmControl != nullptr && poseSampler.pose != nullptr) {
    manager->removePoseSampler(oldLayer, poseSampler);
    manager->addPoseSampler(newLayer, poseSampler);
  }
  if (updater.asmControl != nullptr) {
    manager->removeControlUpdater(oldLayer, updater);
    manager->addControlUpdater(newLayer, updater);
  }
}

bool GfComEvtAnim::Asm::execCmd(AnimLayer layer, const char *command) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->executeCmd(command);
  }

  return false;
}

const char *GfComEvtAnim::Asm::getStateName(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getStateName();
  }

  return nullptr;
}

bool GfComEvtAnim::Asm::setState(AnimLayer layer, const char *state) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setState(state);
  }

  return false;
}

void GfComEvtAnim::Asm::setVariable(const char *name, f32 value) {
  if (asmControl != nullptr) {
    asmControl->setVariable(name, value);
  }
}

void GfComEvtAnim::Asm::setVariable(const char *name, int value) {
  if (asmControl != nullptr) {
    asmControl->setVariable(name, value);
  }
}

void GfComEvtAnim::Asm::setSpeed(AnimLayer layer, f32 speed) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    stateMachine->setSpeed(speed);
  }
}

void GfComEvtAnim::Asm::setLocalTime(AnimLayer layer, f32 time) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    stateMachine->setLocalTime(time);
  }
}

bool GfComEvtAnim::Asm::getPlaybackTime(const char *state, f32 *time) const {
  if (asmControl != nullptr && asmControl->resAsm != nullptr) {
    return anm::Util::getAsmPlaybackTime(*asmControl->resAsm, state, 0, time);
  }

  return false;
}

bool GfComEvtAnim::Asm::getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const {
  if (asmControl != nullptr && asmControl->resAsm != nullptr) {
    return anm::Util::getAsmLocomotionReference(*asmControl->resAsm, state, time, 0, transform);
  }

  return false;
}

const anm::QsTransform &GfComEvtAnim::Asm::getLocomotion() const {
  if (asmControl != nullptr) {
    return asmControl->locomotion;
  }

  static anm::QsTransform identity;
  identity.translation = mm::Vec4::zero;
  identity.rotation = mm::Quat::identity;
  identity.scale = mm::Vec4::unit;
  return identity;
}

void GfComEvtAnim::Asm::setPause(u32 layer, bool isPause) {
  if (asmControl != nullptr) {
    poseSampler.isPause = isPause;
  }
}

bool GfComEvtAnim::Asm::isEnd(AnimLayer layer) const {
  if (asmControl == nullptr) {
    return true;
  }

  if (layer < anm::ASMControl::LAYER_MAX) {
    return asmControl->m_stateMachines[layer].isEnd();
  }

  return false;
}

bool GfComEvtAnim::Asm::easeIn(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseInAdditive(state, 0.0f);
  }

  return false;
}

bool GfComEvtAnim::Asm::easeOut(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseOutAdditive(state, 0.0f);
  }

  return false;
}

bool GfComEvtAnim::Asm::setEaseWeight(const char *state, AnimLayer layer, f32 weight) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateWeight(state, weight);
  }

  return false;
}

bool GfComEvtAnim::Asm::setEaseSpeed(const char *state, AnimLayer layer, f32 speed) {
  anm::StateMachine *stateMachine = getStateMachine(asmControl, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateSpeed(state, speed);
  }

  return false;
}

void GfComEvtAnim::Asm::executeCallback(GfComEvtAnim *owner) {
  for (u32 i = 0; i < callbackCaches.size(); i++) {
    const anm::AsmAnnotetion *annotation = callbackCaches[i].annotation;
    u32 index;
    for (index = 1; index < CALLBACK_MAX; index++) {
      if (callbacks[index].delegate.isValid() && strcmp(callbacks[index].name, annotation->name) == 0) {
        break;
      }
    }

    if (index < CALLBACK_MAX) {
      callbacks[index].delegate(owner, callbackCaches[i]);
    } else if (callbacks[0].delegate.isValid()) {
      callbacks[0].delegate(owner, callbackCaches[i]);
    }
  }

  callbackCaches.clear();
}

void GfComEvtAnim::Asm::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComEvtAnim::Asm::cacheCallback(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion &annotation) { callbackCaches.push_back(CallBackCache(type, &annotation)); }

GfComEvtAnim::Mot::Mot() : model(nullptr), resAsm(nullptr), blender(nullptr), controlCount(0), current(0), speed(1.0f) {}

void GfComEvtAnim::Mot::cleanup(u32 layer) {
  stop(layer);
  for (u64 i = 0; i < easeControls.size(); i++) {
    blender->removeControl(easeControls[i]);
    if (easeControls[i] != nullptr) {
      easeControls[i]->release();
      easeControls[i] = nullptr;
    }
  }

  poseSampler.unbind();
  blenderUpdater.unbind();
  if (blender != nullptr) {
    blender->release();
    blender = nullptr;
  }

  easeControls.clear();
  easeNames.clear();
}

void GfComEvtAnim::Mot::stop(u32 layer) {
  if (blender == nullptr) {
    return;
  }

  if (flags.test(FLAG_REGISTERED)) {
    fw::AnimationManager *manager = fw::AnimationManager::get();
    if (manager != nullptr) {
      poseSampler.resetPose();
      manager->removePoseSampler(layer, poseSampler);
      manager->removeControlUpdater(layer, blenderUpdater);
    }
    flags.set(FLAG_REGISTERED, false);
  }

  for (u64 i = 0; i < controlCount; i++) {
    blender->removeControl(controls[i]);
    if (controls[i] != nullptr) {
      controls[i]->release();
      controls[i] = nullptr;
    }
  }

  controlCount = 0;
  current = 0;
  speed = 1.0f;
}

void GfComEvtAnim::Mot::setup(GfComModel *model, anm::ResASM *resAsm, bool isLocalSpace) {
  this->model = model;
  this->resAsm = resAsm;
  if (model == nullptr) {
    return;
  }

  anm::Pose *pose = model->pose;
  if (pose == nullptr) {
    return;
  }

  anm::ExtraTruckBuffer *extraTruckBuffer = model->extraTruckBuffer;
  blender = anm::Factory::createBlender(model->skeleton, getAllocator(ALLOCATOR_ANIMATION));
  blenderUpdater.bind(blender);
  if (blenderUpdater.blender != nullptr) {
    poseSampler.isLocalSpace = isLocalSpace;
    poseSampler.bind(blender, pose, extraTruckBuffer);
  }
}

void GfComEvtAnim::Mot::changeLayer(u32 oldLayer, u32 newLayer) {
  if (blender == nullptr || !flags.test(FLAG_REGISTERED)) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (poseSampler.blender != nullptr && poseSampler.pose != nullptr) {
    manager->removePoseSampler(oldLayer, poseSampler);
    manager->addPoseSampler(newLayer, poseSampler);
  }
  if (blenderUpdater.blender != nullptr) {
    manager->removeControlUpdater(oldLayer, blenderUpdater);
    manager->addControlUpdater(newLayer, blenderUpdater);
  }
}

void GfComEvtAnim::Mot::init(u32 layer, void **motions, u64 *sizes, u64 count) {
  if (count == 0 || blender == nullptr) {
    return;
  }

  stop(layer);
  for (u64 i = 0; i < count; i++) {
    anm::Binding *binding = anm::AnimationImporter::import(motions[i]);
    controls[i] = anm::Factory::createControl(binding, getAllocator(ALLOCATOR_ANIMATION));
    playBackTimes[i] = anm::Util::getPlayBackTime(*binding);
    blender->addControl(controls[i]);
    if (binding != nullptr) {
      binding->release();
    }
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    manager->addControlUpdater(layer, blenderUpdater);
    manager->addPoseSampler(layer, poseSampler);
    flags.set(FLAG_REGISTERED);
  }

  for (u64 i = 0; i < count; i++) {
    anm::Control *control = controls[i];
    control->m_speed = 0.0f;
    control->m_weight = i == 0 ? 1.0f : 0.0f;
  }

  current = 0;
  controlCount = count;
  speed = 1.0f;
}

void GfComEvtAnim::Mot::play(u32 index, f32 time) {
  if (controlCount > index && blender != nullptr) {
    for (u64 i = 0; i < controlCount; i++) {
      anm::Control *control = controls[i];
      if (index == i) {
        control->setLocalTime(time);
        control->m_speed = speed;
        control->m_weight = 1.0f;
      } else {
        control->m_speed = 0.0f;
        control->m_weight = 0.0f;
      }
    }

    current = index;
  }
}

bool GfComEvtAnim::Mot::isEnd() const {
  if (blender != nullptr) {
    const anm::Control *control = controls[current];
    return playBackTimes[current] <= control->m_localTime;
  }

  return true;
}

void GfComEvtAnim::Mot::setSpeed(f32 speed) {
  for (u64 i = 0; i < controlCount; i++) {
    anm::Control *control = controls[i];
    control->m_speed = i == current ? speed : 0.0f;
  }

  this->speed = speed;
}

void GfComEvtAnim::Mot::setPause(u32 layer, bool isPause) {}

void GfComEvtAnim::Mot::setWeight(f32 *weights, u64 count) {
  if (blender == nullptr) {
    return;
  }

  for (u64 i = 0; i < count; i++) {
    if (i >= controlCount) {
      return;
    }
    anm::Control *control = controls[i];
    control->m_weight = weights[i];
  }
}

bool GfComEvtAnim::Mot::easeIn(const char *state, AnimLayer layer) {
  if (blender == nullptr) {
    return false;
  }

  if (resAsm == nullptr) {
    GfObjAcc acc(static_cast<GfObj *>(model->owner)->handle);
    return false;
  }

  for (const mm::mtl::FixStr<32> *name = easeNames.begin(); name != easeNames.end(); name++) {
    if (strcmp(name->c_str(), state) == 0) {
      return false;
    }
  }

  const anm::Binding *binding = anm::Util::getAsmBinding(*resAsm, state, 0);
  if (binding == nullptr) {
    return false;
  }

  anm::Control *control = anm::Factory::createControl(binding, getAllocator(ALLOCATOR_ANIMATION));
  blender->addControl(control);
  control->m_weight = 1.0f;
  control->m_speed = 1.0f;
  easeNames.push_back(mm::mtl::FixStr<32>(state));
  easeControls.push_back(control);
  return true;
}

bool GfComEvtAnim::Mot::easeOut(const char *state, AnimLayer layer) {
  if (blender == nullptr) {
    return false;
  }

  anm::Control **control = easeControls.begin();
  for (mm::mtl::FixStr<32> *name = easeNames.begin(); control != easeControls.end(); control++, name++) {
    if (strcmp(name->c_str(), state) == 0) {
      blender->removeControl(*control);
      if (*control != nullptr) {
        (*control)->release();
        *control = nullptr;
      }
      easeControls.erase(control);
      easeNames.erase(name);
      return true;
    }
  }

  return false;
}

bool GfComEvtAnim::Mot::setEaseWeight(const char *state, AnimLayer layer, f32 weight) {
  bool isSet = false;
  const mm::mtl::FixStr<32> *name = easeNames.begin();
  for (anm::Control **control = easeControls.begin(); control != easeControls.end(); control++, name++) {
    if (strcmp(name->c_str(), state) == 0) {
      (*control)->m_weight = weight;
      isSet = true;
      break;
    }
  }

  return isSet;
}

bool GfComEvtAnim::Mot::setEaseSpeed(const char *state, AnimLayer layer, f32 speed) {
  bool isSet = false;
  const mm::mtl::FixStr<32> *name = easeNames.begin();
  for (anm::Control **control = easeControls.begin(); control != easeControls.end(); control++, name++) {
    if (strcmp(name->c_str(), state) == 0) {
      (*control)->m_speed = speed;
      isSet = true;
      break;
    }
  }

  return isSet;
}

GfComEvtAnim::GfComEvtAnim() : resAsm(nullptr), isLocalSpace(true) {}

void GfComEvtAnim::cleanup() {
  mot.cleanup(getLayer());
  animAsm.cleanup(getLayer());
  resAsm = nullptr;
  state = "";
  flags.clear();
}

void GfComEvtAnim::setup(const SetupInfo &info) {
  resAsm = info.resAsm;
  state = info.state;
  isLocalSpace = info.isLocalSpace;
  updateSetup();
}

void GfComEvtAnim::updateSetup() {
  if (flags.test(FLAG_SETUP)) {
    return;
  }

  GfComModel *model = owner->getComponent<GfComModel>();
  if (model == nullptr) {
    return;
  }

  animAsm.setup(getLayer(), model, resAsm, state.c_str(), isLocalSpace);
  mot.setup(model, resAsm, isLocalSpace);
  flags.set(FLAG_SETUP);
}

void GfComEvtAnim::changeLayer(u32 oldLayer, u32 newLayer) {
  if (oldLayer == newLayer) {
    return;
  }

  animAsm.changeLayer(oldLayer, newLayer);
  mot.changeLayer(oldLayer, newLayer);
}

bool GfComEvtAnim::execCmd(const char *command) { return animAsm.execCmd(ANIM_LAYER_BASE, command); }

const char *GfComEvtAnim::getStateName() const { return animAsm.getStateName(ANIM_LAYER_BASE); }

bool GfComEvtAnim::setState(const char *state) { return animAsm.setState(ANIM_LAYER_BASE, state); }

void GfComEvtAnim::setVariable(const char *name, f32 value) { animAsm.setVariable(name, value); }

void GfComEvtAnim::setVariable(const char *name, int value) { animAsm.setVariable(name, value); }

void GfComEvtAnim::setLocalTime(f32 time, AnimLayer layer) { animAsm.setLocalTime(layer, time); }

bool GfComEvtAnim::getPlaybackTime(const char *state, f32 *time) const { return animAsm.getPlaybackTime(state, time); }

bool GfComEvtAnim::getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const { return animAsm.getLocomotionReference(state, time, transform); }

const anm::QsTransform &GfComEvtAnim::getLocomotion() const { return animAsm.getLocomotion(); }

bool GfComEvtAnim::isEnd(AnimLayer layer) const { return animAsm.isEnd(layer); }

void GfComEvtAnim::play(void *motion, u64 size, f32 time) {
  updateSetup();
  mot.init(getLayer(), &motion, &size, 1);
  mot.play(0, time);
  animAsm.setPause(getLayer(), true);
  mot.setPause(getLayer(), false);
}

void GfComEvtAnim::stop() {
  mot.stop(getLayer());
  animAsm.setPause(getLayer(), false);
  mot.setPause(getLayer(), true);
}

void GfComEvtAnim::initMulti(void **motions, u64 *sizes, u64 count) {
  updateSetup();
  mot.init(getLayer(), motions, sizes, count);
}

void GfComEvtAnim::playMulti(u32 index, f32 time) {
  mot.play(index, time);
  animAsm.setPause(getLayer(), true);
  mot.setPause(getLayer(), false);
}

void GfComEvtAnim::stopMulti() {
  mot.stop(getLayer());
  animAsm.setPause(getLayer(), false);
  mot.setPause(getLayer(), true);
}

bool GfComEvtAnim::isEndMulti() const { return mot.isEnd(); }

void GfComEvtAnim::setWeightMulti(f32 *weights, u64 count) { mot.setWeight(weights, count); }

void GfComEvtAnim::setSpeed(f32 speed, AnimLayer layer) {
  updateSetup();
  animAsm.setSpeed(layer, speed);
  mot.setSpeed(speed);
}

bool GfComEvtAnim::easeIn(const char *name, AnimLayer layer) {
  updateSetup();
  bool isEase = animAsm.easeIn(name, layer);
  if (mot.easeIn(name, layer)) {
    isEase = true;
  }
  return isEase;
}

bool GfComEvtAnim::easeOut(const char *name, AnimLayer layer) {
  bool isEase = animAsm.easeOut(name, layer);
  if (mot.easeOut(name, layer)) {
    isEase = true;
  }
  return isEase;
}

bool GfComEvtAnim::setEaseWeight(const char *name, AnimLayer layer, f32 weight) {
  bool isSet = animAsm.setEaseWeight(name, layer, weight);
  if (mot.setEaseWeight(name, layer, weight)) {
    isSet = true;
  }
  return isSet;
}

bool GfComEvtAnim::setEaseSpeed(const char *name, AnimLayer layer, f32 speed) {
  bool isSet = animAsm.setEaseSpeed(name, layer, speed);
  if (mot.setEaseSpeed(name, layer, speed)) {
    isSet = true;
  }
  return isSet;
}

const mm::mtl::RTTI *GfComEvtAnim::getRTTI() const { return &m_rtti; }

} // namespace gf
