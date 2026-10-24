#include "event/block_wtr.h"

#include <string.h>

namespace event {

namespace {

const char *const WTR_NAMES[] = {
    "WTR_ALL",
    "WTR_FINE",
    "WTR_SUN_SHOWER",
    "WTR_CLOUDY",
    "WTR_FOG",
    "WTR_RAIN",
    "WTR_THUNDER",
    "WTR_HEAVY_RAIN",
    "WTR_HEAT_WAVE",
    "WTR_SANDSTORM",
    "WTR_THUNDER_RAIN",
    "WTR_ELECTRO_STORM",
    "WTR_LIGHT_PARTICLES_A",
    "WTR_LIGHT_PARTICLES_B",
    "WTR_FIRE_RAIN",
    "WTR_SPORE",
    "WTR_AURORA",
    "WTR_RED_AURORA",
    "WTR_METEOR_STREAM",
    "WTR_RAINBOW",
    "WTR_HEAVY_RAIN2",
    "WTR_SP01",
    "WTR_SP02",
    "WTR_SP03",
    "WTR_SP04",
    "WTR_SP05",
    nullptr,
};

} // namespace

BlockWtr::BlockWtr() { setRules("WTR_ALL"); }

void BlockWtr::setRules(const char *rules) {
  for (u32 i = 0; i < WTR_COUNT; i++) {
    unknown00[i] = true;
  }
  char buffer[512];
  size_t length = __builtin_strlen(rules);
  size_t rest = sizeof(buffer) - length;
  size_t size = length > sizeof(buffer) - 1 ? 0 : rest;
  __builtin_memset(buffer + length, 0, size);
  __builtin_memcpy(buffer, rules, length);
  char *next = buffer;
  if (*next == '\0') {
    return;
  }
  do {
    char *token = strtok(next, "|");
    next = token + __builtin_strlen(token) + 1;
    if (__builtin_strcmp(token, "WTR_ALL") == 0) {
      for (u32 i = 0; i < WTR_COUNT; i++) {
        unknown00[i] = false;
      }
    } else {
      u32 index = 0;
      while (__builtin_strcmp(WTR_NAMES[index], token) != 0) {
        index++;
      }
      unknown00[index] = false;
    }
  } while (*next != '\0');
}

} // namespace event
