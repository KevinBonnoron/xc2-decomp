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

LipSyncPlugin::LipSyncPlugin() : unknown10(nullptr), unknown18(1.0f), unknown1c(1.0f), unknown20(false), unknown21(false) {}

bool LipSyncPlugin::setup(GfComBehavior &behavior) {
  this->unknown10 = &behavior;
  return true;
}

void LipSyncPlugin::cleanup(GfComBehavior &) {}

void LipSyncPlugin::onActivate() {
  unknown18 = 1.0f;
  unknown1c = 1.0f;
}

void LipSyncPlugin::onDeactivate() {
  GfComAsm *comAsm = unknown10->owner->getComponent<GfComAsm>();
  if (unknown20 && comAsm != nullptr) {
    comAsm->easeOut(LIP_TALK_STATE, 0.0f, ANIM_LAYER_LIP);
    unknown20 = false;
  }
}

void LipSyncPlugin::update(GfComBehavior &, const fw::UpdateInfo &) {
  GfComAsm *comAsm = unknown10->owner->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  bool isTalk = judgeTalk();
  if (isTalk != unknown20) {
    if (isTalk) {
      comAsm->easeIn(LIP_TALK_STATE, 0.0f, ANIM_LAYER_LIP);
      comAsm->setSpeedAdditiveState(LIP_TALK_STATE, unknown18, ANIM_LAYER_LIP);
      comAsm->setWeightAdditiveState(LIP_TALK_STATE, unknown1c, ANIM_LAYER_LIP);
    } else {
      comAsm->easeOut(LIP_TALK_STATE, LIP_EASE_OUT_TIME, ANIM_LAYER_LIP);
    }
    unknown20 = isTalk;
  }
}

bool LipSyncPlugin::judgeTalk() {
  GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown10->owner)->unknownf8;
  bool isVoice = GfGameUtil::isPlayVoice(handle);
  bool isObjTalking = GfObjUtil::isTalking(handle);
  return unknown21 || isVoice || isObjTalking;
}

void LipSyncPlugin::setSpeed(f32 speed) {
  this->unknown18 = speed;
  GfComAsm *comAsm = unknown10->owner->getComponent<GfComAsm>();
  if (comAsm != nullptr && comAsm->isActiveAdditiveState(LIP_TALK_STATE, ANIM_LAYER_LIP)) {
    comAsm->setSpeedAdditiveState(LIP_TALK_STATE, this->unknown18, ANIM_LAYER_LIP);
  }
}

void LipSyncPlugin::setWeight(f32 weight) {
  this->unknown1c = weight;
  GfComAsm *comAsm = unknown10->owner->getComponent<GfComAsm>();
  if (comAsm != nullptr && comAsm->isActiveAdditiveState(LIP_TALK_STATE, ANIM_LAYER_LIP)) {
    comAsm->setWeightAdditiveState(LIP_TALK_STATE, this->unknown1c, ANIM_LAYER_LIP);
  }
}

} // namespace gf
