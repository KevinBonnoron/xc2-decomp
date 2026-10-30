#include "ssd/ssd_hash.h"
#include "ssd/ssd_sound_param.h"
#include "ssd/ssd_text.h"

namespace ssd {

void SoundParam::Name::Init() { unknown00[0] = u'\0'; }

SoundParam::Name &SoundParam::Name::operator=(const TextRef &text) {
  if (text.unknown18 == TEXT_ENCODE_UTF8) {
    Utf8ToUTF16(text.unknown10_utf8, unknown00, 32);
    unknown40 = Hash();
    unknown40.CalcTextHash(unknown00);
  } else {
    TextRef::unknown003(unknown00, text.unknown10_utf16, 32);
    unknown40 = Hash();
    unknown40 = text.unknown08;
  }
  return *this;
}

bool SoundParam::Name::operator==(const TextRef &text) { return text.unknown08 == unknown40; }

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

void SoundParam::Surround::Init() {
  unknown04 = 1.0f;
  unknown00 = 0;
  unknown0c = 0;
  unknown08 = 100.0f;
  unknown10 = 1.0f;
}

void SoundParam::Effect::Init() {
  unknown00 = 0.0f;
  unknown04 = 1.0f;
}

} // namespace ssd
