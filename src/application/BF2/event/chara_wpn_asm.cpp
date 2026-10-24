#include "event/chara_wpn_asm.h"

#include "gf/event/gf_evt_model.h"

namespace event {

CharaWpnAsm::CharaWpnAsm() : unknown08(0), unknown10(nullptr), unknown18(nullptr), unknown20(0.0f), unknown50(MOT_NORMAL) {}

CharaWpnAsm::~CharaWpnAsm() {}

void CharaWpnAsm::clear() {
  unknown28.clear();
  unknown10 = nullptr;
  unknown18 = nullptr;
  unknown50 = MOT_NORMAL;
}

bool CharaWpnAsm::isPlayEnd(gf::GfEvtModel *model, bool isLeft) {
  switch (model->unknown18) {
  case gf::GF_EVT_MODEL_WEAPON:
    if (!static_cast<gf::GfEvtModelWeapon *>(model)->isPlayEndAnimCS()) {
      return false;
    }
    break;
  case gf::GF_EVT_MODEL_BLADE:
    if (isLeft) {
      if (!static_cast<gf::GfEvtModelBlade *>(model)->isPlayEndAnimWeaponLeftCS()) {
        return false;
      }
    } else if (!static_cast<gf::GfEvtModelBlade *>(model)->isPlayEndAnimWeaponRightCS()) {
      return false;
    }
    break;
  case gf::GF_EVT_MODEL_DRIVER:
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
  case gf::GF_EVT_MODEL_WEAPON:
    static_cast<gf::GfEvtModelWeapon *>(model)->setAnimSpeedCS(speed);
    break;
  case gf::GF_EVT_MODEL_BLADE:
    if (isLeft) {
      static_cast<gf::GfEvtModelBlade *>(model)->setAnimSpeedWeaponLeftCS(speed);
    } else {
      static_cast<gf::GfEvtModelBlade *>(model)->setAnimSpeedWeaponRightCS(speed);
    }
    break;
  case gf::GF_EVT_MODEL_DRIVER:
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
    unknown28.push_back(MOT_NORMAL);
  } else {
    unknown28.push_back(MOT_IDLE);
  }
  unknown50 = unknown28[unknown28.size() - 1];
  this->unknown10 = model;
  unknown08 &= ~FLAG_PLAY;
  setFlag(FLAG_MOUNT, isMount);
  setFlag(FLAG_LEFT, isLeft);
}

void CharaWpnAsm::execCmd(gf::GfEvtModel *model, CMD cmd, bool isLeft, void *data) {
  if (model->unknown18 == gf::GF_EVT_MODEL_DRIVER) {
    if ((unknown08 & FLAG_MOUNT) == 0) {
      return;
    }
  } else if (model->unknown18 == gf::GF_EVT_MODEL_BLADE) {
    if ((unknown08 & FLAG_MOUNT) == 0) {
      return;
    }
  }
  MOT mot = unknown50;
  unknown28.clear();
  switch (cmd) {
  case CMD_NORMAL:
    unknown28.push_back(MOT_NORMAL);
    break;
  case CMD_BATTLE_START:
    unknown28.push_back(MOT_BATTLE_START);
    unknown28.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_IDLE:
    unknown28.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_END:
    unknown28.push_back(MOT_BATTLE_END);
    unknown28.push_back(MOT_NORMAL);
    break;
  case CMD_BATTLE_MODE1_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE1:
      unknown28.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE2:
      unknown28.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE3:
      unknown28.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE4:
      unknown28.push_back(MOT_BATTLE_MODE4_END);
      break;
    case MOT_BATTLE_MODE5:
      unknown28.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_BATTLE_MODE1_START);
    unknown28.push_back(MOT_BATTLE_MODE1);
    break;
  case CMD_BATTLE_MODE1:
    unknown28.push_back(MOT_BATTLE_MODE1);
    break;
  case CMD_BATTLE_MODE1_END:
    unknown28.push_back(MOT_BATTLE_MODE1_END);
    unknown28.push_back(MOT_BATTLE_MODE_START);
    unknown28.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE2_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE2:
      unknown28.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      unknown28.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE3:
      unknown28.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE4:
      unknown28.push_back(MOT_BATTLE_MODE4_END);
      break;
    case MOT_BATTLE_MODE5:
      unknown28.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_BATTLE_MODE2_START);
    unknown28.push_back(MOT_BATTLE_MODE2);
    break;
  case CMD_BATTLE_MODE2:
    unknown28.push_back(MOT_BATTLE_MODE2);
    break;
  case CMD_BATTLE_MODE2_END:
    unknown28.push_back(MOT_BATTLE_MODE2_END);
    unknown28.push_back(MOT_BATTLE_MODE_START);
    unknown28.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE3_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE3:
      unknown28.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      unknown28.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE2:
      unknown28.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE4:
      unknown28.push_back(MOT_BATTLE_MODE4_END);
      break;
    case MOT_BATTLE_MODE5:
      unknown28.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_BATTLE_MODE3_START);
    unknown28.push_back(MOT_BATTLE_MODE3);
    break;
  case CMD_BATTLE_MODE3:
    unknown28.push_back(MOT_BATTLE_MODE3);
    break;
  case CMD_BATTLE_MODE3_END:
    unknown28.push_back(MOT_BATTLE_MODE3_END);
    unknown28.push_back(MOT_BATTLE_MODE_START);
    unknown28.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE4_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE4:
      unknown28.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      unknown28.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE2:
      unknown28.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE3:
      unknown28.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE5:
      unknown28.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_BATTLE_MODE4_START);
    unknown28.push_back(MOT_BATTLE_MODE4);
    break;
  case CMD_BATTLE_MODE4:
    unknown28.push_back(MOT_BATTLE_MODE4);
    break;
  case CMD_BATTLE_MODE4_END:
    unknown28.push_back(MOT_BATTLE_MODE4_END);
    unknown28.push_back(MOT_BATTLE_MODE_START);
    unknown28.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE5_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE5:
      unknown28.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      unknown28.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE2:
      unknown28.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE3:
      unknown28.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE4:
      unknown28.push_back(MOT_BATTLE_MODE4_END);
      break;
    default:
      break;
    }
    unknown28.push_back(MOT_BATTLE_MODE5_START);
    unknown28.push_back(MOT_BATTLE_MODE5);
    break;
  case CMD_BATTLE_MODE5:
    unknown28.push_back(MOT_BATTLE_MODE5);
    break;
  case CMD_BATTLE_MODE5_END:
    unknown28.push_back(MOT_BATTLE_MODE5_END);
    unknown28.push_back(MOT_BATTLE_MODE_START);
    unknown28.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_SPECIAL:
    unknown28.push_back(MOT_SPECIAL);
    break;
  default:
    break;
  }
  unknown50 = unknown28[unknown28.size() - 1];
  unknown20 = 0.0f;
  this->unknown10 = model;
  this->unknown18 = data;
  unknown08 &= ~FLAG_PLAY;
  setFlag(FLAG_LEFT, isLeft);
}

} // namespace event
