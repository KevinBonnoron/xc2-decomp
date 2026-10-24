#include "event/chara_eva_player.h"

#include "event/chara_obj.h"
#include "event/chara_play_action.h"
#include "event/chara_util.h"
#include "event/tar_axis.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/gf_obj_util.h"

enum EVT_aimtype : int;
enum EVT_tarcvtype : int;

namespace gf {
class GfObj;
} // namespace gf

namespace event {

CharaEvaPlayer::CharaEvaPlayer()
    : flags(0), chara(nullptr), model(nullptr), dysUpdater(nullptr), weaponData(nullptr), rcha(nullptr), frame(0.0f), offset(0.0f, 0.0f, 0.0f), isTar(false), tar(0.0f, 0.0f, 0.0f), action(0),
      faceType(0), eyeType(0), dispWeapon(1), mountWeapon(1), battleWeapon(1) {}

void CharaEvaPlayer::setScaleWeapon(f32 scale) {
  if (model->type == gf::GF_EVT_MODEL_WEAPON) {
    chara->setScaleWeapon(scale);
  }
}

void CharaEvaPlayer::playTar(bool isPlay, const mm::Vec3 &tar) {
  if ((flags & FLAG_CHARA) == 0) {
    return;
  }
  if (isPlay) {
    chara->setTar(TarAxis(TarAxis::AXIS_POS, tar), -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  } else {
    chara->setTar(TarAxis(TarAxis::AXIS_POS, tar), 0.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  }
  isTar = isPlay;
  this->tar = tar;
}

void CharaEvaPlayer::playAction(int type) {
  if (model == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(model->handle);
  if (obj == nullptr || (flags & FLAG_CHARA) == 0) {
    return;
  }
  stopAction();
  if (type <= 0) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (type == 1) {
    CharaUtil::setStat(obj, CharaPlayAction::type2stat(type, 1));
  } else if (type <= 16) {
    CharaUtil::setStat(obj, CharaPlayAction::type2stat(type, 1));
  } else if (type <= 22) {
    CharaUtil::setStat(obj, CharaPlayAction::type2stat(type, 1));
    CharaUtil::combat(model, true, true);
  }
  action = type;
}

void CharaEvaPlayer::setDispWeapon(int type) {
  if (model->type == gf::GF_EVT_MODEL_DRIVER) {
    chara->setHideWeapon(WPNHIDEID_EVA, type > 1, false);
    chara->setHideWeapon(WPNHIDEID_EVA, type > 1, true);
  } else if (model->type == gf::GF_EVT_MODEL_BLADE) {
    chara->setHideWeapon(WPNHIDEID_EVA, type > 1, false);
    chara->setHideWeapon(WPNHIDEID_EVA, type > 1, true);
  }
  dispWeapon = type;
}

void CharaEvaPlayer::setMountWeapon(int type) {
  if (model->type == gf::GF_EVT_MODEL_DRIVER) {
    wpnAsmRight.mount(model, type > 1, false);
    wpnAsmLeft.mount(model, type > 1, true);
  } else if (model->type == gf::GF_EVT_MODEL_BLADE) {
    wpnAsmRight.mount(model, type > 1, false);
    wpnAsmLeft.mount(model, type > 1, true);
  }
  mountWeapon = type;
}

void CharaEvaPlayer::stopTar() {
  if (isTar) {
    isTar = false;
    tar = mm::Vec3::zero;
  }
}

void CharaEvaPlayer::stopAction() {
  if (model == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(model->handle);
  if (obj == nullptr || action <= 0) {
    return;
  }
  if (action == 1) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (action <= 16) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (action <= 22) {
    CharaUtil::setStat(obj, "S_idle");
    CharaUtil::combat(model, false, true);
  }
  action = 0;
}

} // namespace event
