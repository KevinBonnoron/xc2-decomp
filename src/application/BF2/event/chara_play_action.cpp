#include "event/chara_play_action.h"

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

void CharaPlayAction::stanby(int type, f32 life, bool isBlendIn, bool isBlendOut) {
  bool isBlend = mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() ? false : isBlendIn;
  type2cmd(type, 0);
  type2stat(type, 0);
  type2stat(type, 1);
  const char *name = type2name(type);
  this->name = name;
  this->type = type;
  this->life = life;
  if (life <= 0.0f) {
    flags |= FLAG_LOOP;
  } else {
    flags &= ~FLAG_LOOP;
  }
  if (isBlend) {
    flags |= FLAG_BLEND_IN;
  } else {
    flags &= ~FLAG_BLEND_IN;
  }
  if (isBlendOut) {
    flags |= FLAG_BLEND_OUT;
  } else {
    flags &= ~FLAG_BLEND_OUT;
  }
  flags |= FLAG_STANBY;
}

void CharaPlayAction::play(gf::GfObj *obj) {
  const char *cmd = type2cmd(type, 0);
  const char *stat = type2stat(type, 0);
  const char *loop = type2stat(type, 1);
  type2name(type);
  if ((flags & FLAG_MESSAGE) != 0) {
    if (*cmd != '\0') {
      if ((flags & FLAG_BLEND_IN) == 0) {
        gf::MsgGameTalkAction message(1, true);
        obj->sendMessage(obj, message);
      } else {
        gf::MsgGameTalkAction message(0, false);
        obj->sendMessage(obj, message);
      }
      flags |= FLAG_PLAY;
    } else {
      flags |= FLAG_NONE;
    }
  } else if (*cmd != '\0') {
    if ((flags & FLAG_BLEND_IN) == 0) {
      if (type == TYPE_COMBAT) {
        if (model != nullptr) {
          switch (model->type) {
          case gf::GF_EVT_MODEL_DRIVER:
            model->setWeaponBattleState();
            break;
          case gf::GF_EVT_MODEL_BLADE:
            model->setWeaponBattleState();
            break;
          case gf::GF_EVT_MODEL_WEAPON:
            model->setWeaponBattleState();
            break;
          case gf::GF_EVT_MODEL_ENEMY:
            model->setWeaponBattleState();
            break;
          default:
            CharaUtil::setStat(obj, loop);
            break;
          }
        }
      } else {
        CharaUtil::setStat(obj, loop);
      }
    } else if (type == TYPE_COMBAT) {
      if (model != nullptr) {
        switch (model->type) {
        case gf::GF_EVT_MODEL_DRIVER:
          model->setWeaponBattleCommand();
          break;
        case gf::GF_EVT_MODEL_BLADE:
          model->setWeaponBattleCommand();
          break;
        case gf::GF_EVT_MODEL_WEAPON:
          model->setWeaponBattleCommand();
          break;
        case gf::GF_EVT_MODEL_ENEMY:
          model->setWeaponBattleCommand();
          break;
        default:
          CharaUtil::execCmd(obj, cmd, stat, stat);
          break;
        }
      }
    } else {
      CharaUtil::execCmd(obj, cmd, stat, stat);
    }
    flags |= FLAG_PLAY;
  } else {
    flags |= FLAG_NONE;
  }
  if ((flags & FLAG_BLEND_IN) == 0) {
    dys->resetDynamics(0);
  }
}

void CharaPlayAction::clr() {
  if (gf::GfObjUtil::getObj(handle) != nullptr && (flags & FLAG_PLAY) != 0) {
    type = 0;
    life = -1.0f;
    name = "";
  }
  flags &= ~(FLAG_STANBY | FLAG_PLAY | FLAG_NONE);
}

void CharaPlayAction::init() {}

ICmd::RESULT CharaPlayAction::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return RESULT_END;
  }
  f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().delta;
  if (param.getFrame() <= 0) {
    stanby(param.val(1).getS32(), param.val(2).getF32(), param.val(3).getBool(), param.val(4).getBool());
  }
  if ((flags & (FLAG_PLAY | FLAG_NONE)) == 0 && !CharaUtil::isActionBusy(obj)) {
    play(obj);
  }
  if ((flags & FLAG_LOOP) == 0) {
    life -= delta;
    if (life < 0.0f) {
      idle();
      return RESULT_END;
    }
  }
  if ((flags & FLAG_PLAY) == 0) {
    return RESULT_WAIT;
  }
  if (!CharaUtil::checkStat(obj, type2stat(type, 2), type2idle(type))) {
    return RESULT_WAIT;
  }
  clr();
  return RESULT_END;
}

void CharaPlayAction::term() {
  if ((flags & FLAG_KEEP) == 0) {
    idle();
    return;
  }
  flags &= ~FLAG_KEEP;
}

} // namespace event
