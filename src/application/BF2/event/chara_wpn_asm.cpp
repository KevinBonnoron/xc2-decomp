#include "event/chara_wpn_asm.h"

#include "gf/event/gf_evt_model.h"
#include "gf/object/gf_obj_util.h"

namespace event {

CharaWpnAsm::CharaWpnAsm() : unknown08(0), unknown10(nullptr), unknown18(nullptr), unknown20(0.0f), unknown50(MOT_UNKNOWN_1) {}

CharaWpnAsm::~CharaWpnAsm() {}

void CharaWpnAsm::clear() {
  unknown28.clear();
  unknown10 = nullptr;
  unknown18 = nullptr;
  unknown50 = MOT_UNKNOWN_1;
}

void CharaWpnAsm::update(f32 speed) {
  if (unknown10 == nullptr || gf::GfObjUtil::getObj(unknown10->unknown20) == nullptr) {
    clear();
    return;
  }
  if ((unknown08 & FLAG_UNKNOWN_0) != 0 && isPlayEnd(unknown10, (unknown08 & FLAG_UNKNOWN_2) != 0)) {
    unknown08 &= ~FLAG_UNKNOWN_0;
  }
  if ((unknown08 & FLAG_UNKNOWN_0) == 0 && !unknown28.empty()) {
    play(unknown10, unknown28.front(), (unknown08 & FLAG_UNKNOWN_2) != 0, unknown18);
    unknown28.erase(unknown28.begin());
    if (!unknown28.empty()) {
      unknown08 |= FLAG_UNKNOWN_0;
    }
  }
  setSpeed(unknown10, unknown20, (unknown08 & FLAG_UNKNOWN_2) != 0);
  unknown20 = speed;
}

bool CharaWpnAsm::isPlayEnd(gf::GfEvtModel *model, bool isLeft) {
  switch (model->unknown18) {
  case gf::GF_EVT_MODEL_UNKNOWN_2:
    if (!static_cast<gf::GfEvtModelWeapon *>(model)->isPlayEndAnimCS()) {
      return false;
    }
    break;
  case gf::GF_EVT_MODEL_UNKNOWN_1:
    if (isLeft) {
      if (!static_cast<gf::GfEvtModelBlade *>(model)->isPlayEndAnimWeaponLeftCS()) {
        return false;
      }
    } else if (!static_cast<gf::GfEvtModelBlade *>(model)->isPlayEndAnimWeaponRightCS()) {
      return false;
    }
    break;
  case gf::GF_EVT_MODEL_UNKNOWN_0:
    if (isLeft) {
      if (!static_cast<gf::GfEvtModelDriver *>(model)->isPlayEndAnimWeaponLeftCS()) {
        return false;
      }
    } else if (!static_cast<gf::GfEvtModelDriver *>(model)->isPlayEndAnimWeaponRightCS()) {
      return false;
    }
    break;
  default:
    break;
  }
  return true;
}

void CharaWpnAsm::setSpeed(gf::GfEvtModel *model, f32 speed, bool isLeft) {
  switch (model->unknown18) {
  case gf::GF_EVT_MODEL_UNKNOWN_2:
    static_cast<gf::GfEvtModelWeapon *>(model)->setAnimSpeedCS(speed);
    break;
  case gf::GF_EVT_MODEL_UNKNOWN_1:
    if (isLeft) {
      static_cast<gf::GfEvtModelBlade *>(model)->setAnimSpeedWeaponLeftCS(speed);
    } else {
      static_cast<gf::GfEvtModelBlade *>(model)->setAnimSpeedWeaponRightCS(speed);
    }
    break;
  case gf::GF_EVT_MODEL_UNKNOWN_0:
    if (isLeft) {
      static_cast<gf::GfEvtModelDriver *>(model)->setAnimSpeedWeaponLeftCS(speed);
    } else {
      static_cast<gf::GfEvtModelDriver *>(model)->setAnimSpeedWeaponRightCS(speed);
    }
    break;
  default:
    break;
  }
}

void CharaWpnAsm::mount(gf::GfEvtModel *model, bool isMount, bool isLeft) {
  unknown28.clear();
  if (isMount) {
    unknown28.push_back(MOT_UNKNOWN_1);
  } else {
    unknown28.push_back(MOT_UNKNOWN_0);
  }
  unknown50 = unknown28[unknown28.size() - 1];
  this->unknown10 = model;
  unknown08 &= ~FLAG_UNKNOWN_0;
  setFlag(FLAG_UNKNOWN_1, isMount);
  setFlag(FLAG_UNKNOWN_2, isLeft);
}

void CharaWpnAsm::execCmd(gf::GfEvtModel *model, CMD cmd, bool isLeft, void *data) {
  if (model->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_0) {
    if ((unknown08 & FLAG_UNKNOWN_1) == 0) {
      return;
    }
  } else if (model->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_1) {
    if ((unknown08 & FLAG_UNKNOWN_1) == 0) {
      return;
    }
  }
  MOT mot = unknown50;
  unknown28.clear();
  switch (cmd) {
  case CMD_UNKNOWN_0:
    unknown28.push_back(MOT_UNKNOWN_1);
    break;
  case CMD_UNKNOWN_1:
    unknown28.push_back(MOT_UNKNOWN_2);
    unknown28.push_back(MOT_UNKNOWN_3);
    break;
  case CMD_UNKNOWN_2:
    unknown28.push_back(MOT_UNKNOWN_3);
    break;
  case CMD_UNKNOWN_3:
    unknown28.push_back(MOT_UNKNOWN_4);
    unknown28.push_back(MOT_UNKNOWN_1);
    break;
  case CMD_UNKNOWN_4:
    switch (mot) {
    case MOT_UNKNOWN_1:
    case MOT_UNKNOWN_3:
    case MOT_UNKNOWN_8:
      unknown28.push_back(MOT_UNKNOWN_5);
      break;
    case MOT_UNKNOWN_11:
      unknown28.push_back(MOT_UNKNOWN_12);
      break;
    case MOT_UNKNOWN_14:
      unknown28.push_back(MOT_UNKNOWN_15);
      break;
    case MOT_UNKNOWN_17:
      unknown28.push_back(MOT_UNKNOWN_18);
      break;
    case MOT_UNKNOWN_20:
      unknown28.push_back(MOT_UNKNOWN_21);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_UNKNOWN_7);
    unknown28.push_back(MOT_UNKNOWN_8);
    break;
  case CMD_UNKNOWN_5:
    unknown28.push_back(MOT_UNKNOWN_8);
    break;
  case CMD_UNKNOWN_6:
    unknown28.push_back(MOT_UNKNOWN_9);
    unknown28.push_back(MOT_UNKNOWN_6);
    unknown28.push_back(MOT_UNKNOWN_3);
    break;
  case CMD_UNKNOWN_7:
    switch (mot) {
    case MOT_UNKNOWN_1:
    case MOT_UNKNOWN_3:
    case MOT_UNKNOWN_11:
      unknown28.push_back(MOT_UNKNOWN_5);
      break;
    case MOT_UNKNOWN_8:
      unknown28.push_back(MOT_UNKNOWN_9);
      break;
    case MOT_UNKNOWN_14:
      unknown28.push_back(MOT_UNKNOWN_15);
      break;
    case MOT_UNKNOWN_17:
      unknown28.push_back(MOT_UNKNOWN_18);
      break;
    case MOT_UNKNOWN_20:
      unknown28.push_back(MOT_UNKNOWN_21);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_UNKNOWN_10);
    unknown28.push_back(MOT_UNKNOWN_11);
    break;
  case CMD_UNKNOWN_8:
    unknown28.push_back(MOT_UNKNOWN_11);
    break;
  case CMD_UNKNOWN_9:
    unknown28.push_back(MOT_UNKNOWN_12);
    unknown28.push_back(MOT_UNKNOWN_6);
    unknown28.push_back(MOT_UNKNOWN_3);
    break;
  case CMD_UNKNOWN_10:
    switch (mot) {
    case MOT_UNKNOWN_1:
    case MOT_UNKNOWN_3:
    case MOT_UNKNOWN_14:
      unknown28.push_back(MOT_UNKNOWN_5);
      break;
    case MOT_UNKNOWN_8:
      unknown28.push_back(MOT_UNKNOWN_9);
      break;
    case MOT_UNKNOWN_11:
      unknown28.push_back(MOT_UNKNOWN_12);
      break;
    case MOT_UNKNOWN_17:
      unknown28.push_back(MOT_UNKNOWN_18);
      break;
    case MOT_UNKNOWN_20:
      unknown28.push_back(MOT_UNKNOWN_21);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_UNKNOWN_13);
    unknown28.push_back(MOT_UNKNOWN_14);
    break;
  case CMD_UNKNOWN_11:
    unknown28.push_back(MOT_UNKNOWN_14);
    break;
  case CMD_UNKNOWN_12:
    unknown28.push_back(MOT_UNKNOWN_15);
    unknown28.push_back(MOT_UNKNOWN_6);
    unknown28.push_back(MOT_UNKNOWN_3);
    break;
  case CMD_UNKNOWN_13:
    switch (mot) {
    case MOT_UNKNOWN_1:
    case MOT_UNKNOWN_3:
    case MOT_UNKNOWN_17:
      unknown28.push_back(MOT_UNKNOWN_5);
      break;
    case MOT_UNKNOWN_8:
      unknown28.push_back(MOT_UNKNOWN_9);
      break;
    case MOT_UNKNOWN_11:
      unknown28.push_back(MOT_UNKNOWN_12);
      break;
    case MOT_UNKNOWN_14:
      unknown28.push_back(MOT_UNKNOWN_15);
      break;
    case MOT_UNKNOWN_20:
      unknown28.push_back(MOT_UNKNOWN_21);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_UNKNOWN_16);
    unknown28.push_back(MOT_UNKNOWN_17);
    break;
  case CMD_UNKNOWN_14:
    unknown28.push_back(MOT_UNKNOWN_17);
    break;
  case CMD_UNKNOWN_15:
    unknown28.push_back(MOT_UNKNOWN_18);
    unknown28.push_back(MOT_UNKNOWN_6);
    unknown28.push_back(MOT_UNKNOWN_3);
    break;
  case CMD_UNKNOWN_16:
    switch (mot) {
    case MOT_UNKNOWN_1:
    case MOT_UNKNOWN_3:
    case MOT_UNKNOWN_20:
      unknown28.push_back(MOT_UNKNOWN_5);
      break;
    case MOT_UNKNOWN_8:
      unknown28.push_back(MOT_UNKNOWN_9);
      break;
    case MOT_UNKNOWN_11:
      unknown28.push_back(MOT_UNKNOWN_12);
      break;
    case MOT_UNKNOWN_14:
      unknown28.push_back(MOT_UNKNOWN_15);
      break;
    case MOT_UNKNOWN_17:
      unknown28.push_back(MOT_UNKNOWN_18);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_UNKNOWN_19);
    unknown28.push_back(MOT_UNKNOWN_20);
    break;
  case CMD_UNKNOWN_17:
    unknown28.push_back(MOT_UNKNOWN_20);
    break;
  case CMD_UNKNOWN_18:
    unknown28.push_back(MOT_UNKNOWN_21);
    unknown28.push_back(MOT_UNKNOWN_6);
    unknown28.push_back(MOT_UNKNOWN_3);
    break;
  case CMD_UNKNOWN_19:
    unknown28.push_back(MOT_UNKNOWN_22);
    break;
  default:
    break;
  }
  unknown50 = unknown28[unknown28.size() - 1];
  unknown20 = 0.0f;
  this->unknown10 = model;
  this->unknown18 = data;
  unknown08 &= ~FLAG_UNKNOWN_0;
  setFlag(FLAG_UNKNOWN_2, isLeft);
}

} // namespace event
