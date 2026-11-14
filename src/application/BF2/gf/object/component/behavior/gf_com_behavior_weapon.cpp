#include "gf/object/component/behavior/gf_com_behavior_weapon.h"

#include <string.h>

#include "anm/anm_asm_listener.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_mount.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/fixstr.h"

namespace gf {

bool GfComBehaviorWeapon::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 != MSG_UNKNOWN_16777280) {
    if (message.unknown00 != MSG_OBJECT_UNKNOWN_16777279) {
      return false;
    }

    procMsgObjectNotifyAsmCallback(sender, static_cast<MsgObjectNotifyAsmCallback &>(message));
    return true;
  }

  procMsgObjectOnChangeWeapon(sender, static_cast<MsgObjectForceWeaponMount &>(message));
  return true;
}

void GfComBehaviorWeapon::procMsgObjectNotifyAsmCallback(fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message) {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  const anm::AsmAnnotetion *annotation = message.unknown10;
  if (strcmp(annotation->unknown00, "weaponTrans") == 0) {
    if (annotation->unknown08 == ANNOTATION_KIND_UNKNOWN_1) {
      unknown98.push_back(annotation->unknown10);
    }
  } else if (strcmp(annotation->unknown00, "battleStartEnd") == 0 && annotation->unknown08 == ANNOTATION_KIND_UNKNOWN_1) {
    GfFadeInfo info;
    if (GfObjUtil::parseFadeParam(annotation->unknown10, &info)) {
      f32 invFps = 0.0f;
      comAsm->getClipInvFps(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), 0, &invFps);
      f32 time = info.unknown04 * invFps;
      if (info.unknown00 == 0) {
        SCOM_OBJ_ALPHA::create(static_cast<GfObj *>(unknown08)->unknownf8, time, 1.0f);
      } else if (info.unknown00 == 1) {
        SCOM_OBJ_ALPHA::create(static_cast<GfObj *>(unknown08)->unknownf8, time, 0.0f);
      }
    }
  }
}

void GfComBehaviorWeapon::procMsgObjectOnChangeWeapon(fw::MessageObject *sender, MsgObjectForceWeaponMount &message) {
  mm::mtl::FixStr<64> state("S_");
  const char *name = GfObjUtil::getMotionResourceName(message.unknown10);
  if (name != nullptr) {
    state += name + 3;
    state += "_";
  }

  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return;
  }

  switch (message.unknown08) {
  case OPTMNT_UNKNOWN_0:
  case OPTMNT_UNKNOWN_2:
  case OPTMNT_UNKNOWN_4:
    state += "idle";
    break;
  case OPTMNT_UNKNOWN_1:
  case OPTMNT_UNKNOWN_3:
    state += "btidle";
    break;
  default:
    return;
  }

  comAsm->setState(state.c_str(), ANIM_LAYER_UNKNOWN_0);
}

GfComBehaviorWeapon::GfComBehaviorWeapon() : unknown98(getAllocator(ALLOCATOR_UNKNOWN_0)) {}

GfComBehaviorWeapon::~GfComBehaviorWeapon() {}

void GfComBehaviorWeapon::update(const fw::UpdateInfo &info) {
  GfComAsm *comAsm = unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    for (u32 i = 0; i < unknown98.size(); i++) {
      if (!comAsm->execCmd(unknown98[i], ANIM_LAYER_UNKNOWN_0)) {
        // The game calls it and drops the result, likely the argument of a debug message removed from the release build.
        comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
      }
    }
    unknown98.clear();
  }
}

const mm::mtl::RTTI *GfComBehaviorWeapon::getRTTI() const { return &m_rtti; }

void GfComBehaviorWeapon::changeLayer(u32 oldLayer, u32 newLayer) {}

} // namespace gf
