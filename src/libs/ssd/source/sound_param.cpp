#include "ssd/ssd_sound_param.h"

namespace ssd {

void SoundParam::Name::Init() { unknown00[0] = u'\0'; }

void SoundParam::Base::Init() {
  unknown01 = true;
  unknown02 = true;
  unknown00 = false;
  unknown0c = 1.0f;
  unknown04 = 1.0f;
  unknown08 = 0.0f;
  unknown10 = 0.0f;
  unknown14 = 0.0f;
  unknown18 = 0.0f;
  unknown03 = false;
}

void SoundParam::State::Init() {
  unknown00 = false;
  unknown01 = true;
  unknown02 = true;
  unknown03 = false;
  unknown04 = false;
  unknown05 = false;
  unknown06 = false;
  unknown07 = false;
}

void SoundParam::Effect::Init() {
  unknown00 = 0.0f;
  unknown04 = 1.0f;
}

} // namespace ssd
