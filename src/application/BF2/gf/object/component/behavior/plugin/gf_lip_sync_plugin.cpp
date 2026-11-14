#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace gf {
struct GF_OBJ_HANDLE;

static const char *const unknown012 = "S_lip_talk"; // Inferred role: lip talk state; original name unknown.

constexpr f32 unknown013 = 0.05f; // Inferred role: lip ease out time; original name unknown.

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
  GfComAsm *comAsm = unknown10->unknown08->getComponent<GfComAsm>();
  if (unknown20 && comAsm != nullptr) {
    comAsm->easeOut(unknown012, 0.0f, ANIM_LAYER_UNKNOWN_4);
    unknown20 = false;
  }
}

void LipSyncPlugin::update(GfComBehavior &, const fw::UpdateInfo &) {
  GfComAsm *comAsm = unknown10->unknown08->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  bool isTalk = judgeTalk();
  if (isTalk != unknown20) {
    if (isTalk) {
      comAsm->easeIn(unknown012, 0.0f, ANIM_LAYER_UNKNOWN_4);
      comAsm->setSpeedAdditiveState(unknown012, unknown18, ANIM_LAYER_UNKNOWN_4);
      comAsm->setWeightAdditiveState(unknown012, unknown1c, ANIM_LAYER_UNKNOWN_4);
    } else {
      comAsm->easeOut(unknown012, unknown013, ANIM_LAYER_UNKNOWN_4);
    }
    unknown20 = isTalk;
  }
}

bool LipSyncPlugin::judgeTalk() {
  GF_OBJ_HANDLE *handle = static_cast<GfObj *>(unknown10->unknown08)->unknownf8;
  bool isVoice = GfGameUtil::isPlayVoice(handle);
  bool isObjTalking = GfObjUtil::isTalking(handle);
  return unknown21 || isVoice || isObjTalking;
}

void LipSyncPlugin::setSpeed(f32 speed) {
  this->unknown18 = speed;
  GfComAsm *comAsm = unknown10->unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr && comAsm->isActiveAdditiveState(unknown012, ANIM_LAYER_UNKNOWN_4)) {
    comAsm->setSpeedAdditiveState(unknown012, this->unknown18, ANIM_LAYER_UNKNOWN_4);
  }
}

void LipSyncPlugin::setWeight(f32 weight) {
  this->unknown1c = weight;
  GfComAsm *comAsm = unknown10->unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr && comAsm->isActiveAdditiveState(unknown012, ANIM_LAYER_UNKNOWN_4)) {
    comAsm->setWeightAdditiveState(unknown012, this->unknown1c, ANIM_LAYER_UNKNOWN_4);
  }
}

} // namespace gf
