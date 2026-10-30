#include "ssd/ssd_hash.h"
#include "ssd/ssd_sound_param.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {

void SoundParam::Name::Init() { unknown00[0] = u'\0'; }

SoundParam::Name &SoundParam::Name::operator=(const TextRef &text) {
  if (text.unknown18 == TEXT_ENCODE_UTF8) {
    Utf8ToUTF16(static_cast<const char *>(text.unknown10), unknown00, 32);
    unknown40 = Hash();
    unknown40.CalcTextHash(unknown00);
  } else {
    const char16_t *source = static_cast<const char16_t *>(text.unknown10);
    char16_t *destination = unknown00;
    unsigned long limit = 31;
    while (*source != u'\0' && static_cast<u32>(destination - unknown00) < limit) {
      *destination = *source;
      destination++;
      source++;
    }
    *destination = u'\0';
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

void SoundParam::Effect::Init() {
  unknown00 = 0.0f;
  unknown04 = 1.0f;
}

} // namespace ssd
