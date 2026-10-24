#include "event/block_time.h"

#include <string.h>

namespace event {

namespace {

const char *const TIME_NAMES[] = {
    "TIME_ALL",
    "EARLY_MORNING",
    "MORNING",
    "DAYTIME",
    "EVENING",
    "NIGHT",
    "MIDNIGHT",
    nullptr,
};

} // namespace

BlockTime::BlockTime() { setRules("TIME_ALL"); }

void BlockTime::setRules(const char *rules) {
  for (u32 i = 0; i < TIME_COUNT; i++) {
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
    if (__builtin_strcmp(token, "TIME_ALL") == 0) {
      for (u32 i = 0; i < TIME_COUNT; i++) {
        unknown00[i] = false;
      }
    } else {
      u32 index = 0;
      while (__builtin_strcmp(TIME_NAMES[index], token) != 0) {
        index++;
      }
      unknown00[index] = false;
    }
  } while (*next != '\0');
}

} // namespace event
