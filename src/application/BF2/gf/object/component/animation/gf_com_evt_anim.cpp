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

GfComEvtAnim::Asm::Asm() : unknown08(nullptr), unknown10(nullptr), unknown148(getAllocator(ALLOCATOR_DEFAULT)), unknown180(nullptr) {
  unknown138.unknown08 = this;
  unknown170.unknown08 = this;
}

void GfComEvtAnim::Asm::cleanup(u32 layer) {
  if (unknown10 == nullptr) {
    return;
  }

  if (unknown00.test(FLAG_REGISTERED)) {
    fw::AnimationManager *manager = fw::AnimationManager::get();
    if (manager != nullptr) {
      manager->removePoseSampler(layer, unknown38);
      manager->removeControlUpdater(layer, unknown18);
    }
    unknown00.set(FLAG_REGISTERED, false);
  }

  unknown38.unbind();
  unknown18.unbind();
  unknown148.clear();
  unknown10->setListener(nullptr);
  if (unknown10 != nullptr) {
    unknown10->release();
    unknown10 = nullptr;
  }
}

void GfComEvtAnim::Asm::setup(u32 layer, GfComModel *model, anm::ResASM *resAsm, const char *state, bool isLocalSpace) {
  this->unknown08 = model;
  if (resAsm == nullptr) {
    return;
  }

  anm::Pose *pose = model->unknown30;
  if (pose == nullptr) {
    return;
  }

  anm::ExtraTruckBuffer *extraTruckBuffer = model->unknown38;
  unknown10 = anm::Factory::createASMControl(*resAsm, *getAllocator(ALLOCATOR_ANIMATION));
  unknown18.bind(unknown10);
  if (unknown18.asmControl == nullptr) {
    return;
  }

  unknown38.isLocalSpace = isLocalSpace;
  unknown38.bind(unknown10, pose, extraTruckBuffer);
  if (unknown38.asmControl == nullptr || unknown38.pose == nullptr) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    manager->addControlUpdater(layer, unknown18);
    manager->addPoseSampler(layer, unknown38);
    unknown00.set(FLAG_REGISTERED);
  }

  unknown10->setListener(&unknown138);
  unknown148.reserve(32);
  unknown10->m_stateMachines[ANIM_LAYER_BASE].setState(state);
  unknown10->m_stateMachines[ANIM_LAYER_BASE].executeCmd("C_idle");
}

void GfComEvtAnim::Asm::changeLayer(u32 oldLayer, u32 newLayer) {
  if (unknown10 == nullptr || !unknown00.test(FLAG_REGISTERED)) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (unknown38.asmControl != nullptr && unknown38.pose != nullptr) {
    manager->removePoseSampler(oldLayer, unknown38);
    manager->addPoseSampler(newLayer, unknown38);
  }
  if (unknown18.asmControl != nullptr) {
    manager->removeControlUpdater(oldLayer, unknown18);
    manager->addControlUpdater(newLayer, unknown18);
  }
}

bool GfComEvtAnim::Asm::execCmd(AnimLayer layer, const char *command) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->executeCmd(command);
  }

  return false;
}

const char *GfComEvtAnim::Asm::getStateName(AnimLayer layer) const {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->getStateName();
  }

  return nullptr;
}

bool GfComEvtAnim::Asm::setState(AnimLayer layer, const char *state) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setState(state);
  }

  return false;
}

void GfComEvtAnim::Asm::setVariable(const char *name, f32 value) {
  if (unknown10 != nullptr) {
    unknown10->setVariable(name, value);
  }
}

void GfComEvtAnim::Asm::setVariable(const char *name, int value) {
  if (unknown10 != nullptr) {
    unknown10->setVariable(name, value);
  }
}

void GfComEvtAnim::Asm::setSpeed(AnimLayer layer, f32 speed) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    stateMachine->setSpeed(speed);
  }
}

void GfComEvtAnim::Asm::setLocalTime(AnimLayer layer, f32 time) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    stateMachine->setLocalTime(time);
  }
}

bool GfComEvtAnim::Asm::getPlaybackTime(const char *state, f32 *time) const {
  if (unknown10 != nullptr && unknown10->resAsm != nullptr) {
    return anm::Util::getAsmPlaybackTime(*unknown10->resAsm, state, 0, time);
  }

  return false;
}

bool GfComEvtAnim::Asm::getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const {
  if (unknown10 != nullptr && unknown10->resAsm != nullptr) {
    return anm::Util::getAsmLocomotionReference(*unknown10->resAsm, state, time, 0, transform);
  }

  return false;
}

const anm::QsTransform &GfComEvtAnim::Asm::getLocomotion() const {
  if (unknown10 != nullptr) {
    return unknown10->locomotion;
  }

  static anm::QsTransform identity;
  identity.translation = mm::Vec4::zero;
  identity.rotation = mm::Quat::identity;
  identity.scale = mm::Vec4::unit;
  return identity;
}

void GfComEvtAnim::Asm::setPause(u32 layer, bool isPause) {
  if (unknown10 != nullptr) {
    unknown38.isPause = isPause;
  }
}

bool GfComEvtAnim::Asm::isEnd(AnimLayer layer) const {
  if (unknown10 == nullptr) {
    return true;
  }

  if (layer < anm::ASMControl::LAYER_MAX) {
    return unknown10->m_stateMachines[layer].isEnd();
  }

  return false;
}

bool GfComEvtAnim::Asm::easeIn(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseInAdditive(state, 0.0f);
  }

  return false;
}

bool GfComEvtAnim::Asm::easeOut(const char *state, AnimLayer layer) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->doEaseOutAdditive(state, 0.0f);
  }

  return false;
}

bool GfComEvtAnim::Asm::setEaseWeight(const char *state, AnimLayer layer, f32 weight) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateWeight(state, weight);
  }

  return false;
}

bool GfComEvtAnim::Asm::setEaseSpeed(const char *state, AnimLayer layer, f32 speed) {
  anm::StateMachine *stateMachine = getStateMachine(unknown10, layer);
  if (stateMachine != nullptr) {
    return stateMachine->setAdditiveStateSpeed(state, speed);
  }

  return false;
}

void GfComEvtAnim::Asm::executeCallback(GfComEvtAnim *owner) {
  for (u32 i = 0; i < unknown148.size(); i++) {
    const anm::AsmAnnotetion *annotation = unknown148[i].unknown08;
    u32 index;
    for (index = 1; index < CALLBACK_MAX; index++) {
      if (unknown70[index].unknown08.isValid() && strcmp(unknown70[index].unknown00, annotation->name) == 0) {
        break;
      }
    }

    if (index < CALLBACK_MAX) {
      unknown70[index].unknown08(owner, unknown148[i]);
    } else if (unknown70[0].unknown08.isValid()) {
      unknown70[0].unknown08(owner, unknown148[i]);
    }
  }

  unknown148.clear();
}

void GfComEvtAnim::Asm::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComEvtAnim::Asm::cacheCallback(anm::AsmListener::CallBackType type, const anm::AsmAnnotetion &annotation) { unknown148.push_back(CallBackCache(type, &annotation)); }

GfComEvtAnim::Mot::Mot() : unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown3a8(0), unknown3b0(0), unknown3b4(1.0f) {}

void GfComEvtAnim::Mot::cleanup(u32 layer) {
  stop(layer);
  for (u64 i = 0; i < unknown78.size(); i++) {
    unknown18->removeControl(unknown78[i]);
    if (unknown78[i] != nullptr) {
      unknown78[i]->release();
      unknown78[i] = nullptr;
    }
  }

  unknown40.unbind();
  unknown20.unbind();
  if (unknown18 != nullptr) {
    unknown18->release();
    unknown18 = nullptr;
  }

  unknown78.clear();
  unknown100.clear();
}

void GfComEvtAnim::Mot::stop(u32 layer) {
  if (unknown18 == nullptr) {
    return;
  }

  if (unknown00.test(FLAG_REGISTERED)) {
    fw::AnimationManager *manager = fw::AnimationManager::get();
    if (manager != nullptr) {
      unknown40.resetPose();
      manager->removePoseSampler(layer, unknown40);
      manager->removeControlUpdater(layer, unknown20);
    }
    unknown00.set(FLAG_REGISTERED, false);
  }

  for (u64 i = 0; i < unknown3a8; i++) {
    unknown18->removeControl(unknown348[i]);
    if (unknown348[i] != nullptr) {
      unknown348[i]->release();
      unknown348[i] = nullptr;
    }
  }

  unknown3a8 = 0;
  unknown3b0 = 0;
  unknown3b4 = 1.0f;
}

void GfComEvtAnim::Mot::setup(GfComModel *model, anm::ResASM *resAsm, bool isLocalSpace) {
  this->unknown08 = model;
  this->unknown10 = resAsm;
  if (model == nullptr) {
    return;
  }

  anm::Pose *pose = model->unknown30;
  if (pose == nullptr) {
    return;
  }

  anm::ExtraTruckBuffer *extraTruckBuffer = model->unknown38;
  unknown18 = anm::Factory::createBlender(model->unknown28, getAllocator(ALLOCATOR_ANIMATION));
  unknown20.bind(unknown18);
  if (unknown20.blender != nullptr) {
    unknown40.isLocalSpace = isLocalSpace;
    unknown40.bind(unknown18, pose, extraTruckBuffer);
  }
}

void GfComEvtAnim::Mot::changeLayer(u32 oldLayer, u32 newLayer) {
  if (unknown18 == nullptr || !unknown00.test(FLAG_REGISTERED)) {
    return;
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }

  if (unknown40.blender != nullptr && unknown40.pose != nullptr) {
    manager->removePoseSampler(oldLayer, unknown40);
    manager->addPoseSampler(newLayer, unknown40);
  }
  if (unknown20.blender != nullptr) {
    manager->removeControlUpdater(oldLayer, unknown20);
    manager->addControlUpdater(newLayer, unknown20);
  }
}

void GfComEvtAnim::Mot::init(u32 layer, void **motions, u64 *sizes, u64 count) {
  if (count == 0 || unknown18 == nullptr) {
    return;
  }

  stop(layer);
  for (u64 i = 0; i < count; i++) {
    anm::Binding *binding = anm::AnimationImporter::import(motions[i]);
    unknown348[i] = anm::Factory::createControl(binding, getAllocator(ALLOCATOR_ANIMATION));
    unknown388[i] = anm::Util::getPlayBackTime(*binding);
    unknown18->addControl(unknown348[i]);
    if (binding != nullptr) {
      binding->release();
    }
  }

  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    manager->addControlUpdater(layer, unknown20);
    manager->addPoseSampler(layer, unknown40);
    unknown00.set(FLAG_REGISTERED);
  }

  for (u64 i = 0; i < count; i++) {
    anm::Control *control = unknown348[i];
    control->m_speed = 0.0f;
    control->m_weight = i == 0 ? 1.0f : 0.0f;
  }

  unknown3b0 = 0;
  unknown3a8 = count;
  unknown3b4 = 1.0f;
}

void GfComEvtAnim::Mot::play(u32 index, f32 time) {
  if (unknown3a8 > index && unknown18 != nullptr) {
    for (u64 i = 0; i < unknown3a8; i++) {
      anm::Control *control = unknown348[i];
      if (index == i) {
        control->setLocalTime(time);
        control->m_speed = unknown3b4;
        control->m_weight = 1.0f;
      } else {
        control->m_speed = 0.0f;
        control->m_weight = 0.0f;
      }
    }

    unknown3b0 = index;
  }
}

bool GfComEvtAnim::Mot::isEnd() const {
  if (unknown18 != nullptr) {
    const anm::Control *control = unknown348[unknown3b0];
    return unknown388[unknown3b0] <= control->m_localTime;
  }

  return true;
}

void GfComEvtAnim::Mot::setSpeed(f32 speed) {
  for (u64 i = 0; i < unknown3a8; i++) {
    anm::Control *control = unknown348[i];
    control->m_speed = i == unknown3b0 ? speed : 0.0f;
  }

  this->unknown3b4 = speed;
}

void GfComEvtAnim::Mot::setPause(u32 layer, bool isPause) {}

void GfComEvtAnim::Mot::setWeight(f32 *weights, u64 count) {
  if (unknown18 == nullptr) {
    return;
  }

  for (u64 i = 0; i < count; i++) {
    if (i >= unknown3a8) {
      return;
    }
    anm::Control *control = unknown348[i];
    control->m_weight = weights[i];
  }
}

bool GfComEvtAnim::Mot::easeIn(const char *state, AnimLayer layer) {
  if (unknown18 == nullptr) {
    return false;
  }

  if (unknown10 == nullptr) {
    GfObjAcc acc(static_cast<GfObj *>(unknown08->owner)->unknownf8);
    return false;
  }

  for (const mm::mtl::FixStr<32> *name = unknown100.begin(); name != unknown100.end(); name++) {
    if (strcmp(name->c_str(), state) == 0) {
      return false;
    }
  }

  const anm::Binding *binding = anm::Util::getAsmBinding(*unknown10, state, 0);
  if (binding == nullptr) {
    return false;
  }

  anm::Control *control = anm::Factory::createControl(binding, getAllocator(ALLOCATOR_ANIMATION));
  unknown18->addControl(control);
  control->m_weight = 1.0f;
  control->m_speed = 1.0f;
  unknown100.push_back(mm::mtl::FixStr<32>(state));
  unknown78.push_back(control);
  return true;
}

bool GfComEvtAnim::Mot::easeOut(const char *state, AnimLayer layer) {
  if (unknown18 == nullptr) {
    return false;
  }

  anm::Control **control = unknown78.begin();
  for (mm::mtl::FixStr<32> *name = unknown100.begin(); control != unknown78.end(); control++, name++) {
    if (strcmp(name->c_str(), state) == 0) {
      unknown18->removeControl(*control);
      if (*control != nullptr) {
        (*control)->release();
        *control = nullptr;
      }
      unknown78.erase(control);
      unknown100.erase(name);
      return true;
    }
  }

  return false;
}

bool GfComEvtAnim::Mot::setEaseWeight(const char *state, AnimLayer layer, f32 weight) {
  bool isSet = false;
  const mm::mtl::FixStr<32> *name = unknown100.begin();
  for (anm::Control **control = unknown78.begin(); control != unknown78.end(); control++, name++) {
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
  const mm::mtl::FixStr<32> *name = unknown100.begin();
  for (anm::Control **control = unknown78.begin(); control != unknown78.end(); control++, name++) {
    if (strcmp(name->c_str(), state) == 0) {
      (*control)->m_speed = speed;
      isSet = true;
      break;
    }
  }

  return isSet;
}

GfComEvtAnim::GfComEvtAnim() : unknown550(nullptr), unknown580(true) {}

void GfComEvtAnim::cleanup() {
  unknown198.cleanup(getLayer());
  unknown10.cleanup(getLayer());
  unknown550 = nullptr;
  unknown558 = "";
  unknown57c.clear();
}

void GfComEvtAnim::setup(const SetupInfo &info) {
  unknown550 = info.resAsm;
  unknown558 = info.state;
  unknown580 = info.isLocalSpace;
  updateSetup();
}

void GfComEvtAnim::updateSetup() {
  if (unknown57c.test(FLAG_SETUP)) {
    return;
  }

  GfComModel *model = owner->getComponent<GfComModel>();
  if (model == nullptr) {
    return;
  }

  unknown10.setup(getLayer(), model, unknown550, unknown558.c_str(), unknown580);
  unknown198.setup(model, unknown550, unknown580);
  unknown57c.set(FLAG_SETUP);
}

void GfComEvtAnim::changeLayer(u32 oldLayer, u32 newLayer) {
  if (oldLayer == newLayer) {
    return;
  }

  unknown10.changeLayer(oldLayer, newLayer);
  unknown198.changeLayer(oldLayer, newLayer);
}

bool GfComEvtAnim::execCmd(const char *command) { return unknown10.execCmd(ANIM_LAYER_BASE, command); }

const char *GfComEvtAnim::getStateName() const { return unknown10.getStateName(ANIM_LAYER_BASE); }

bool GfComEvtAnim::setState(const char *state) { return unknown10.setState(ANIM_LAYER_BASE, state); }

void GfComEvtAnim::setVariable(const char *name, f32 value) { unknown10.setVariable(name, value); }

void GfComEvtAnim::setVariable(const char *name, int value) { unknown10.setVariable(name, value); }

void GfComEvtAnim::setLocalTime(f32 time, AnimLayer layer) { unknown10.setLocalTime(layer, time); }

bool GfComEvtAnim::getPlaybackTime(const char *state, f32 *time) const { return unknown10.getPlaybackTime(state, time); }

bool GfComEvtAnim::getLocomotionReference(const char *state, f32 time, anm::QsTransform *transform) const { return unknown10.getLocomotionReference(state, time, transform); }

const anm::QsTransform &GfComEvtAnim::getLocomotion() const { return unknown10.getLocomotion(); }

bool GfComEvtAnim::isEnd(AnimLayer layer) const { return unknown10.isEnd(layer); }

void GfComEvtAnim::play(void *motion, u64 size, f32 time) {
  updateSetup();
  unknown198.init(getLayer(), &motion, &size, 1);
  unknown198.play(0, time);
  unknown10.setPause(getLayer(), true);
  unknown198.setPause(getLayer(), false);
}

void GfComEvtAnim::stop() {
  unknown198.stop(getLayer());
  unknown10.setPause(getLayer(), false);
  unknown198.setPause(getLayer(), true);
}

void GfComEvtAnim::initMulti(void **motions, u64 *sizes, u64 count) {
  updateSetup();
  unknown198.init(getLayer(), motions, sizes, count);
}

void GfComEvtAnim::playMulti(u32 index, f32 time) {
  unknown198.play(index, time);
  unknown10.setPause(getLayer(), true);
  unknown198.setPause(getLayer(), false);
}

void GfComEvtAnim::stopMulti() {
  unknown198.stop(getLayer());
  unknown10.setPause(getLayer(), false);
  unknown198.setPause(getLayer(), true);
}

bool GfComEvtAnim::isEndMulti() const { return unknown198.isEnd(); }

void GfComEvtAnim::setWeightMulti(f32 *weights, u64 count) { unknown198.setWeight(weights, count); }

void GfComEvtAnim::setSpeed(f32 speed, AnimLayer layer) {
  updateSetup();
  unknown10.setSpeed(layer, speed);
  unknown198.setSpeed(speed);
}

bool GfComEvtAnim::easeIn(const char *name, AnimLayer layer) {
  updateSetup();
  bool isEase = unknown10.easeIn(name, layer);
  if (unknown198.easeIn(name, layer)) {
    isEase = true;
  }
  return isEase;
}

bool GfComEvtAnim::easeOut(const char *name, AnimLayer layer) {
  bool isEase = unknown10.easeOut(name, layer);
  if (unknown198.easeOut(name, layer)) {
    isEase = true;
  }
  return isEase;
}

bool GfComEvtAnim::setEaseWeight(const char *name, AnimLayer layer, f32 weight) {
  bool isSet = unknown10.setEaseWeight(name, layer, weight);
  if (unknown198.setEaseWeight(name, layer, weight)) {
    isSet = true;
  }
  return isSet;
}

bool GfComEvtAnim::setEaseSpeed(const char *name, AnimLayer layer, f32 speed) {
  bool isSet = unknown10.setEaseSpeed(name, layer, speed);
  if (unknown198.setEaseSpeed(name, layer, speed)) {
    isSet = true;
  }
  return isSet;
}

const mm::mtl::RTTI *GfComEvtAnim::getRTTI() const { return &m_rtti; }

} // namespace gf
