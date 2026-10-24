#include "event/chara_play_action_auto.h"

#include "event/chara_obj.h"
#include "event/chara_play_action.h"
#include "event/chara_util.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "event/sche_manager.h"
#include "event/scheduler.h"
#include "gf/game/gf_game_message.h"
#include "gf/object/gf_obj.h"
#include "mm_mtl/singleton.h"

namespace event {

CharaPlayActionAuto::~CharaPlayActionAuto() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr || (unknown08 & FLAG_PLAY) == 0) {
    return;
  }
  if ((unknown08 & FLAG_MESSAGE) != 0) {
    gf::MsgGameTalkAction message(2, false);
    obj->sendMessage(obj, message);
  } else {
    const char *cmd = CharaPlayAction::type2cmd(TYPE_TALK, 2);
    const char *stat = CharaPlayAction::type2stat(TYPE_TALK, 2);
    CharaUtil::execCmd(obj, cmd, stat, stat);
  }
}

void CharaPlayActionAuto::stanby(f32 life) {
  this->unknown20 = life;
  unknown08 |= FLAG_STANBY;
}

void CharaPlayActionAuto::init() {}

ICmd::RESULT CharaPlayActionAuto::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr) {
    return RESULT_END;
  }
  f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().unknown08;
  if (param.getFrame() <= 0) {
    stanby(param.val(1).getF32());
  }
  if ((unknown08 & FLAG_PLAY) == 0 && !CharaUtil::isActionBusy(obj) && !mm::mtl::Singleton<ScheManager>::getPtr()->isPlay(Scheduler::ORDER_FLD2EVT, unknown10)) {
    play(obj);
    unknown08 |= FLAG_PLAY;
  }
  unknown20 -= delta;
  if (unknown20 < 0.0f) {
    idle();
    return RESULT_END;
  }
  return RESULT_WAIT;
}

void CharaPlayActionAuto::term() {}

} // namespace event
