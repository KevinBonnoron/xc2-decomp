#include "event/chara_play_talk.h"

namespace event {

void CharaPlayTalk::init() {
  unknown08 = 0;
  unknown68 = 1.0f;
  unknown6c = 1.0f;
  unknown70 = 0.0f;
  unknown74 = 0.0f;
}

void CharaPlayTalk::term() { idle(); }

} // namespace event
