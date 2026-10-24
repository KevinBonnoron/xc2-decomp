#include "event/chara_play_action.h"

#include "bdat.h"
#include "event/chara_dys_updater.h"
#include "event/chara_obj.h"
#include "event/chara_util.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "gf/event/gf_evt_model.h"
#include "gf/game/gf_game_message.h"
#include "gf/object/gf_obj.h"
#include "mm_mtl/singleton.h"

namespace event {

const char *CharaPlayAction::type2stat(int type, u32 index) {
  unsigned char *fp = Bdat::getFP("EVT_acttype");
  switch (index) {
  case 0:
    return reinterpret_cast<const char *>(Bdat::getValCheck(fp, "stat0", type, 7));
  case 1:
    return reinterpret_cast<const char *>(Bdat::getValCheck(fp, "stat1", type, 7));
  default:
    return reinterpret_cast<const char *>(Bdat::getValCheck(fp, "stat2", type, 7));
  }
}

const char *CharaPlayAction::type2cmd(int type, u32 index) {
  unsigned char *fp = Bdat::getFP("EVT_acttype");
  switch (index) {
  case 0:
    return reinterpret_cast<const char *>(Bdat::getValCheck(fp, "cmd0", type, 7));
  case 1:
    return reinterpret_cast<const char *>(Bdat::getValCheck(fp, "cmd1", type, 7));
  default:
    return reinterpret_cast<const char *>(Bdat::getValCheck(fp, "cmd2", type, 7));
  }
}

const char *CharaPlayAction::type2idle(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), "statI", type, 7)); }

const char *CharaPlayAction::type2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_acttype"), "name", type, 7)); }

void CharaPlayAction::stanby(int type, f32 life, bool isBlendIn, bool isBlendOut) {
  bool isBlend = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? false : isBlendIn;
  type2cmd(type, 0);
  type2stat(type, 0);
  type2stat(type, 1);
  const char *name = type2name(type);
  this->unknown38 = name;
  this->unknown30 = type;
  this->unknown34 = life;
  if (life <= 0.0f) {
    unknown08 |= FLAG_LOOP;
  } else {
    unknown08 &= ~FLAG_LOOP;
  }
  if (isBlend) {
    unknown08 |= FLAG_BLEND_IN;
  } else {
    unknown08 &= ~FLAG_BLEND_IN;
  }
  if (isBlendOut) {
    unknown08 |= FLAG_BLEND_OUT;
  } else {
    unknown08 &= ~FLAG_BLEND_OUT;
  }
  unknown08 |= FLAG_STANBY;
}

void CharaPlayAction::play(gf::GfObj *obj) {
  const char *cmd = type2cmd(unknown30, 0);
  const char *stat = type2stat(unknown30, 0);
  const char *loop = type2stat(unknown30, 1);
  type2name(unknown30);
  if ((unknown08 & FLAG_MESSAGE) != 0) {
    if (*cmd != '\0') {
      if ((unknown08 & FLAG_BLEND_IN) == 0) {
        gf::MsgGameTalkAction message(1, true);
        obj->sendMessage(obj, message);
      } else {
        gf::MsgGameTalkAction message(0, false);
        obj->sendMessage(obj, message);
      }
      unknown08 |= FLAG_PLAY;
    } else {
      unknown08 |= FLAG_NONE;
    }
  } else if (*cmd != '\0') {
    if ((unknown08 & FLAG_BLEND_IN) == 0) {
      if (unknown30 == TYPE_COMBAT) {
        if (unknown18 != nullptr) {
          switch (unknown18->unknown18) {
          case gf::GF_EVT_MODEL_DRIVER:
            unknown18->setWeaponBattleState();
            break;
          case gf::GF_EVT_MODEL_BLADE:
            unknown18->setWeaponBattleState();
            break;
          case gf::GF_EVT_MODEL_WEAPON:
            unknown18->setWeaponBattleState();
            break;
          case gf::GF_EVT_MODEL_ENEMY:
            unknown18->setWeaponBattleState();
            break;
          default:
            CharaUtil::setStat(obj, loop);
            break;
          }
        }
      } else {
        CharaUtil::setStat(obj, loop);
      }
    } else if (unknown30 == TYPE_COMBAT) {
      if (unknown18 != nullptr) {
        switch (unknown18->unknown18) {
        case gf::GF_EVT_MODEL_DRIVER:
          unknown18->setWeaponBattleCommand();
          break;
        case gf::GF_EVT_MODEL_BLADE:
          unknown18->setWeaponBattleCommand();
          break;
        case gf::GF_EVT_MODEL_WEAPON:
          unknown18->setWeaponBattleCommand();
          break;
        case gf::GF_EVT_MODEL_ENEMY:
          unknown18->setWeaponBattleCommand();
          break;
        default:
          CharaUtil::execCmd(obj, cmd, stat, stat);
          break;
        }
      }
    } else {
      CharaUtil::execCmd(obj, cmd, stat, stat);
    }
    unknown08 |= FLAG_PLAY;
  } else {
    unknown08 |= FLAG_NONE;
  }
  if ((unknown08 & FLAG_BLEND_IN) == 0) {
    unknown20->resetDynamics(0);
  }
}

void CharaPlayAction::clr() {
  if (gf::GfObjUtil::getObj(unknown10) != nullptr && (unknown08 & FLAG_PLAY) != 0) {
    unknown30 = 0;
    unknown34 = -1.0f;
    unknown38 = "";
  }
  unknown08 &= ~(FLAG_STANBY | FLAG_PLAY | FLAG_NONE);
}

void CharaPlayAction::init() {}

ICmd::RESULT CharaPlayAction::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr) {
    return RESULT_END;
  }
  f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().unknown04;
  if (param.getFrame() <= 0) {
    stanby(param.val(1).getS32(), param.val(2).getF32(), param.val(3).getBool(), param.val(4).getBool());
  }
  if ((unknown08 & (FLAG_PLAY | FLAG_NONE)) == 0 && !CharaUtil::isActionBusy(obj)) {
    play(obj);
  }
  if ((unknown08 & FLAG_LOOP) == 0) {
    unknown34 -= delta;
    if (unknown34 < 0.0f) {
      idle();
      return RESULT_END;
    }
  }
  if ((unknown08 & FLAG_PLAY) == 0) {
    return RESULT_WAIT;
  }
  if (!CharaUtil::checkStat(obj, type2stat(unknown30, 2), type2idle(unknown30))) {
    return RESULT_WAIT;
  }
  clr();
  return RESULT_END;
}

void CharaPlayAction::term() {
  if ((unknown08 & FLAG_KEEP) == 0) {
    idle();
    return;
  }
  unknown08 &= ~FLAG_KEEP;
}

} // namespace event
