#include "event/chara_play_talk_auto.h"

#include "gf/game/gf_game_message.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

CharaPlayTalkAuto::~CharaPlayTalkAuto() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj != nullptr && unknown08.test(FLAG_PLAY) && unknown08.test(FLAG_MESSAGE)) {
    gf::MsgGameLipAction message(1);
    obj->sendMessage(obj, message);
  }
}

void CharaPlayTalkAuto::stanby(f32 life) {
  this->unknown20 = life;
  unknown08.set(FLAG_STANBY);
}

void CharaPlayTalkAuto::idle() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj != nullptr && unknown08.test(FLAG_PLAY)) {
    if (unknown08.test(FLAG_MESSAGE)) {
      gf::MsgGameLipAction message(1);
      obj->sendMessage(obj, message);
    }
    unknown20 = -1.0f;
  }
  unknown08.set(FLAG_STANBY, false);
  unknown08.set(FLAG_PLAY, false);
}

void CharaPlayTalkAuto::init() {}

void CharaPlayTalkAuto::term() {}

} // namespace event
