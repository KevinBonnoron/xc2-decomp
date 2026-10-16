#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace gf {
struct GF_OBJ_HANDLE;

static const char *const LIP_TALK_STATE = "S_lip_talk";

constexpr f32 LIP_EASE_OUT_TIME = 0.05f;

LipSyncPlugin::LipSyncPlugin() : behavior(nullptr), speed(1.0f), weight(1.0f), isTalking(false), isForceTalk(false) {}

bool LipSyncPlugin::setup(GfComBehavior &behavior) {
  this->behavior = &behavior;
  return true;
}

void LipSyncPlugin::cleanup(GfComBehavior &) {}

void LipSyncPlugin::onActivate() {
  speed = 1.0f;
  weight = 1.0f;
}

void LipSyncPlugin::onDeactivate() {
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  if (isTalking && comAsm != nullptr) {
    comAsm->easeOut(LIP_TALK_STATE, 0.0f, ANIM_LAYER_LIP);
    isTalking = false;
  }
}

void LipSyncPlugin::update(GfComBehavior &, const fw::UpdateInfo &) {
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  bool isTalk = judgeTalk();
  if (isTalk != isTalking) {
    if (isTalk) {
      comAsm->easeIn(LIP_TALK_STATE, 0.0f, ANIM_LAYER_LIP);
      comAsm->setSpeedAdditiveState(LIP_TALK_STATE, speed, ANIM_LAYER_LIP);
      comAsm->setWeightAdditiveState(LIP_TALK_STATE, weight, ANIM_LAYER_LIP);
    } else {
      comAsm->easeOut(LIP_TALK_STATE, LIP_EASE_OUT_TIME, ANIM_LAYER_LIP);
    }
    isTalking = isTalk;
  }
}

bool LipSyncPlugin::judgeTalk() {
  GF_OBJ_HANDLE *handle = static_cast<GfObj *>(behavior->owner)->handle;
  bool isVoice = GfGameUtil::isPlayVoice(handle);
  bool isObjTalking = GfObjUtil::isTalking(handle);
  return isForceTalk || isVoice || isObjTalking;
}

void LipSyncPlugin::setSpeed(f32 speed) {
  this->speed = speed;
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  if (comAsm != nullptr && comAsm->isActiveAdditiveState(LIP_TALK_STATE, ANIM_LAYER_LIP)) {
    comAsm->setSpeedAdditiveState(LIP_TALK_STATE, this->speed, ANIM_LAYER_LIP);
  }
}

void LipSyncPlugin::setWeight(f32 weight) {
  this->weight = weight;
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  if (comAsm != nullptr && comAsm->isActiveAdditiveState(LIP_TALK_STATE, ANIM_LAYER_LIP)) {
    comAsm->setWeightAdditiveState(LIP_TALK_STATE, this->weight, ANIM_LAYER_LIP);
  }
}

} // namespace gf
