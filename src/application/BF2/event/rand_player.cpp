#include "event/rand_player.h"

#include "event/chara_obj.h"
#include "event/cmd_variable.h"
#include "event/object.h"
#include "event/object_chara.h"
#include "event/rand_util.h"
#include "event/tar_axis.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj_util.h"

enum EVT_aimtype : int;
enum EVT_tarcvtype : int;

namespace event {

ICmd::RESULT RandPlayer::Warp::update(const Param &param) {
  if (param.getFrame() == 0) {
    gf::GfGameParty::judgeRandomTalkWarp();
  }
  return RESULT_END;
}

ICmd::RESULT RandPlayer::Wait::update(const Param &param) {
  Object *object = RandUtil::searchByID(param.val(0).getS32());
  if (param.getFrame() < 60 && object->getType() == OBJTYPE_CHARA && !gf::GfObjUtil::isStanbyTalkingPlayer(static_cast<ObjectChara *>(object)->getCharaObj()->getHandle())) {
    return RESULT_WAIT;
  }
  return RESULT_END;
}

ICmd::RESULT RandPlayer::Reset::update(const Param &param) {
  if (param.getFrame() == 0) {
    int id = param.val(0).getS32();
    bool isReset = param.val(1).getBool();
    f32 x = param.val(2).getF32();
    f32 y = param.val(3).getF32();
    f32 z = param.val(4).getF32();
    bool isTar = param.val(5).getBool();
    Object *object = RandUtil::searchByID(id);
    if (isReset && object->getType() == OBJTYPE_CHARA) {
      CharaObj *chara = static_cast<ObjectChara *>(object)->getCharaObj();
      if (isTar) {
        chara->setTar(TarAxis(TarAxis::AXIS_POS, x, y, z), -1.0f, static_cast<EVT_tarcvtype>(1), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
      } else {
        chara->resetTar();
      }
    }
  }
  return RESULT_END;
}

RandPlayer::RandPlayer() : unknown978(0) {}

void RandPlayer::clear() {
  unknown28.clear();
  unknown978 = 0;
}

void RandPlayer::update() {
  if ((unknown978 & FLAG_PLAY) != 0) {
    unknown28.update();
    if (unknown28.isEmpty()) {
      unknown978 &= ~FLAG_PLAY;
    }
  }
}

bool RandPlayer::isPlaying() const { return (unknown978 & FLAG_PLAY) != 0; }

} // namespace event
