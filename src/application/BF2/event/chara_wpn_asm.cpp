#include "event/chara_wpn_asm.h"

#include "gf/event/gf_evt_model.h"

namespace event {

CharaWpnAsm::CharaWpnAsm() : flags(0), model(nullptr), data(nullptr), speed(0.0f), lastMot(MOT_NORMAL) {}

CharaWpnAsm::~CharaWpnAsm() {}

void CharaWpnAsm::clear() {
  queue.clear();
  model = nullptr;
  data = nullptr;
  lastMot = MOT_NORMAL;
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
  queue.clear();
  if (isMount) {
    queue.push_back(MOT_NORMAL);
  } else {
    queue.push_back(MOT_IDLE);
  }
  lastMot = queue[queue.size() - 1];
  this->model = model;
  flags &= ~FLAG_PLAY;
  setFlag(FLAG_MOUNT, isMount);
  setFlag(FLAG_LEFT, isLeft);
}

void CharaWpnAsm::execCmd(gf::GfEvtModel *model, CMD cmd, bool isLeft, void *data) {
  if (model->unknown18 == gf::GF_EVT_MODEL_DRIVER) {
    if ((flags & FLAG_MOUNT) == 0) {
      return;
    }
  } else if (model->unknown18 == gf::GF_EVT_MODEL_BLADE) {
    if ((flags & FLAG_MOUNT) == 0) {
      return;
    }
  }
  MOT mot = lastMot;
  queue.clear();
  switch (cmd) {
  case CMD_NORMAL:
    queue.push_back(MOT_NORMAL);
    break;
  case CMD_BATTLE_START:
    queue.push_back(MOT_BATTLE_START);
    queue.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_IDLE:
    queue.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_END:
    queue.push_back(MOT_BATTLE_END);
    queue.push_back(MOT_NORMAL);
    break;
  case CMD_BATTLE_MODE1_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE1:
      queue.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE2:
      queue.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE3:
      queue.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE4:
      queue.push_back(MOT_BATTLE_MODE4_END);
      break;
    case MOT_BATTLE_MODE5:
      queue.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    queue.push_back(MOT_BATTLE_MODE1_START);
    queue.push_back(MOT_BATTLE_MODE1);
    break;
  case CMD_BATTLE_MODE1:
    queue.push_back(MOT_BATTLE_MODE1);
    break;
  case CMD_BATTLE_MODE1_END:
    queue.push_back(MOT_BATTLE_MODE1_END);
    queue.push_back(MOT_BATTLE_MODE_START);
    queue.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE2_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE2:
      queue.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      queue.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE3:
      queue.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE4:
      queue.push_back(MOT_BATTLE_MODE4_END);
      break;
    case MOT_BATTLE_MODE5:
      queue.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    queue.push_back(MOT_BATTLE_MODE2_START);
    queue.push_back(MOT_BATTLE_MODE2);
    break;
  case CMD_BATTLE_MODE2:
    queue.push_back(MOT_BATTLE_MODE2);
    break;
  case CMD_BATTLE_MODE2_END:
    queue.push_back(MOT_BATTLE_MODE2_END);
    queue.push_back(MOT_BATTLE_MODE_START);
    queue.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE3_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE3:
      queue.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      queue.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE2:
      queue.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE4:
      queue.push_back(MOT_BATTLE_MODE4_END);
      break;
    case MOT_BATTLE_MODE5:
      queue.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    queue.push_back(MOT_BATTLE_MODE3_START);
    queue.push_back(MOT_BATTLE_MODE3);
    break;
  case CMD_BATTLE_MODE3:
    queue.push_back(MOT_BATTLE_MODE3);
    break;
  case CMD_BATTLE_MODE3_END:
    queue.push_back(MOT_BATTLE_MODE3_END);
    queue.push_back(MOT_BATTLE_MODE_START);
    queue.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE4_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE4:
      queue.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      queue.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE2:
      queue.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE3:
      queue.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE5:
      queue.push_back(MOT_BATTLE_MODE5_END);
      break;
    default:
      break;
    }
    queue.push_back(MOT_BATTLE_MODE4_START);
    queue.push_back(MOT_BATTLE_MODE4);
    break;
  case CMD_BATTLE_MODE4:
    queue.push_back(MOT_BATTLE_MODE4);
    break;
  case CMD_BATTLE_MODE4_END:
    queue.push_back(MOT_BATTLE_MODE4_END);
    queue.push_back(MOT_BATTLE_MODE_START);
    queue.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_BATTLE_MODE5_START:
    switch (mot) {
    case MOT_NORMAL:
    case MOT_BATTLE_IDLE:
    case MOT_BATTLE_MODE5:
      queue.push_back(MOT_BATTLE_MODE_CHANGE);
      break;
    case MOT_BATTLE_MODE1:
      queue.push_back(MOT_BATTLE_MODE1_END);
      break;
    case MOT_BATTLE_MODE2:
      queue.push_back(MOT_BATTLE_MODE2_END);
      break;
    case MOT_BATTLE_MODE3:
      queue.push_back(MOT_BATTLE_MODE3_END);
      break;
    case MOT_BATTLE_MODE4:
      queue.push_back(MOT_BATTLE_MODE4_END);
      break;
    default:
      break;
    }
    queue.push_back(MOT_BATTLE_MODE5_START);
    queue.push_back(MOT_BATTLE_MODE5);
    break;
  case CMD_BATTLE_MODE5:
    queue.push_back(MOT_BATTLE_MODE5);
    break;
  case CMD_BATTLE_MODE5_END:
    queue.push_back(MOT_BATTLE_MODE5_END);
    queue.push_back(MOT_BATTLE_MODE_START);
    queue.push_back(MOT_BATTLE_IDLE);
    break;
  case CMD_SPECIAL:
    queue.push_back(MOT_SPECIAL);
    break;
  default:
    break;
  }
  lastMot = queue[queue.size() - 1];
  speed = 0.0f;
  this->model = model;
  this->data = data;
  flags &= ~FLAG_PLAY;
  setFlag(FLAG_LEFT, isLeft);
}

} // namespace event
