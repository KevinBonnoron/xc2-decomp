#include "event/voice_maker.h"

#include "framework/lang_util.h"
#include <stddef.h>

namespace event {

VoiceMaker::VoiceMaker() : unknown08(0) {}

namespace {

bool isVoiceGroup(const char *name, size_t length, const char *prefix) {
  size_t prefixLength = __builtin_strlen(prefix);
  return length > prefixLength && __builtin_memcmp(name, prefix, prefixLength) == 0;
}

} // namespace

void VoiceMaker::create(bool isEnable, const char *directory, const char *name) {
  unknown08 = 0;
  unknown0c.clear();
  if (!isEnable) {
    return;
  }
  size_t length = __builtin_strlen(name);
  if (isVoiceGroup(name, length, "bf") || isVoiceGroup(name, length, "qst") || isVoiceGroup(name, length, "fev") || isVoiceGroup(name, length, "deb") || isVoiceGroup(name, length, "kizuna")) {
    unknown0c.format("/stream/%s/%s/%s/", directory, fw::LangUtil::getVoiceFolder().c_str(), name);
    unknown08 |= FLAG_ENABLE;
  }
}

const char *VoiceMaker::makePath(const char *file) {
  if ((unknown08 & FLAG_ENABLE) == 0) {
    return nullptr;
  }
  unknown110 = unknown0c.c_str();
  unknown110 += file;
  return unknown110.c_str();
}

} // namespace event
