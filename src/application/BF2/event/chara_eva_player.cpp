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
    : unknown08(0), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(0.0f), unknown40(0.0f, 0.0f, 0.0f), unknown50(false),
      unknown60(0.0f, 0.0f, 0.0f), unknown70(0), unknown74(0), unknown78(0), unknown7c(1), unknown80(1), unknown84(1) {}

void CharaEvaPlayer::setScaleWeapon(f32 scale) {
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_WEAPON) {
    unknown10->setScaleWeapon(scale);
  }
}

void CharaEvaPlayer::playTar(bool isPlay, const mm::Vec3 &tar) {
  if ((unknown08 & FLAG_CHARA) == 0) {
    return;
  }
  if (isPlay) {
    unknown10->setTar(TarAxis(TarAxis::AXIS_POS, tar), -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  } else {
    unknown10->setTar(TarAxis(TarAxis::AXIS_POS, tar), 0.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  }
  unknown50 = isPlay;
  this->unknown60 = tar;
}

void CharaEvaPlayer::playAction(int type) {
  if (unknown18 == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown18->unknown20);
  if (obj == nullptr || (unknown08 & FLAG_CHARA) == 0) {
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
    CharaUtil::combat(unknown18, true, true);
  }
  unknown70 = type;
}

void CharaEvaPlayer::setDispWeapon(int type) {
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_DRIVER) {
    unknown10->setHideWeapon(WPNHIDEID_EVA, type > 1, false);
    unknown10->setHideWeapon(WPNHIDEID_EVA, type > 1, true);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_BLADE) {
    unknown10->setHideWeapon(WPNHIDEID_EVA, type > 1, false);
    unknown10->setHideWeapon(WPNHIDEID_EVA, type > 1, true);
  }
  unknown7c = type;
}

void CharaEvaPlayer::setBattleWeapon(int type) {
  CharaWpnAsm::CMD cmd = static_cast<CharaWpnAsm::CMD>(type - 1);
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_WEAPON) {
    unknown88.execCmd(unknown18, cmd, false, nullptr);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_DRIVER) {
    unknown88.execCmd(unknown18, cmd, false, nullptr);
    unknowne0.execCmd(unknown18, cmd, true, nullptr);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_BLADE) {
    unknown88.execCmd(unknown18, cmd, false, nullptr);
    unknowne0.execCmd(unknown18, cmd, true, nullptr);
  }
  unknown84 = type;
}

void CharaEvaPlayer::setMountWeapon(int type) {
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_DRIVER) {
    unknown88.mount(unknown18, type > 1, false);
    unknowne0.mount(unknown18, type > 1, true);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_BLADE) {
    unknown88.mount(unknown18, type > 1, false);
    unknowne0.mount(unknown18, type > 1, true);
  }
  unknown80 = type;
}

void CharaEvaPlayer::stopTar() {
  if (unknown50) {
    unknown50 = false;
    unknown60 = mm::Vec3::zero;
  }
}

void CharaEvaPlayer::stopAction() {
  if (unknown18 == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown18->unknown20);
  if (obj == nullptr || unknown70 <= 0) {
    return;
  }
  if (unknown70 == 1) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (unknown70 <= 16) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (unknown70 <= 22) {
    CharaUtil::setStat(obj, "S_idle");
    CharaUtil::combat(unknown18, false, true);
  }
  unknown70 = 0;
}

} // namespace event
