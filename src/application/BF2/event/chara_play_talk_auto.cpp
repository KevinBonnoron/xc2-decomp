#include "event/chara_play_talk_auto.h"

#include "gf/game/gf_game_message.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

CharaPlayTalkAuto::~CharaPlayTalkAuto() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr && flags.test(FLAG_PLAY) && flags.test(FLAG_MESSAGE)) {
    gf::MsgGameLipAction message(1);
    obj->sendMessage(obj, message);
  }
}

void CharaPlayTalkAuto::stanby(f32 life) {
  this->life = life;
  flags.set(FLAG_STANBY);
}

void CharaPlayTalkAuto::idle() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr && flags.test(FLAG_PLAY)) {
    if (flags.test(FLAG_MESSAGE)) {
      gf::MsgGameLipAction message(1);
      obj->sendMessage(obj, message);
    }
    life = -1.0f;
  }
  flags.set(FLAG_STANBY, false);
  flags.set(FLAG_PLAY, false);
}

void CharaPlayTalkAuto::init() {}

void CharaPlayTalkAuto::term() {}

} // namespace event
