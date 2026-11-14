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
  if (obj == nullptr || (unknown08 & FLAG_UNKNOWN_2) == 0) {
    return;
  }
  if ((unknown08 & FLAG_UNKNOWN_0) != 0) {
    gf::MsgGameTalkAction message(2, false);
    obj->sendMessage(obj, message);
  } else {
    const char *cmd = CharaPlayAction::type2cmd(ACT_TALK_A, 2);
    const char *stat = CharaPlayAction::type2stat(ACT_TALK_A, 2);
    CharaUtil::execCmd(obj, cmd, stat, stat);
  }
}

void CharaPlayActionAuto::stanby(f32 life) {
  this->unknown20 = life;
  unknown08 |= FLAG_UNKNOWN_1;
}

void CharaPlayActionAuto::init() {}

ICmd::RESULT CharaPlayActionAuto::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr) {
    return RESULT_UNKNOWN_1;
  }
  f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().unknown08;
  if (param.getFrame() <= 0) {
    stanby(param.val(1).getF32());
  }
  if ((unknown08 & FLAG_UNKNOWN_2) == 0 && !CharaUtil::isActionBusy(obj) && !mm::mtl::Singleton<ScheManager>::getPtr()->isPlay(Scheduler::ORDER_UNKNOWN_0, unknown10)) {
    play(obj);
    unknown08 |= FLAG_UNKNOWN_2;
  }
  unknown20 -= delta;
  if (unknown20 < 0.0f) {
    idle();
    return RESULT_UNKNOWN_1;
  }
  return RESULT_UNKNOWN_0;
}

void CharaPlayActionAuto::term() {}

} // namespace event
