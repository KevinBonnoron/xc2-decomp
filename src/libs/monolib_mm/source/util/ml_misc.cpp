#include "ml/ml_misc.h"

#include <string.h>
#include <time.h>

#include "ml/char_code.h"
#include "ml/critical_section.h"
#include "ml/path_util.h"
#include "ml/stack_trace.h"
#include "ml/time_util.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace _mlmisc {

ml::CriticalSection &getCriticalSection() {
  static ml::CriticalSection sect;
  return sect;
}

} // namespace _mlmisc

extern "C" {

void mlGetDateName(char *name, int size) {
  name[0] = 0;
  time_t now = time(nullptr);
  const tm *local = localtime(&now);
  mm::mtl::FixStr<16> date;
  mm::mtl::FixStr<16> part;
  ml::PathUtil::itoa(part, local->tm_year + 1900, 4);
  date += part.c_str();
  ml::PathUtil::itoa(part, local->tm_mon + 1, 2);
  date += part.c_str();
  ml::PathUtil::itoa(part, local->tm_mday, 2);
  date += part.c_str();
  ml::PathUtil::itoa(part, local->tm_hour, 2);
  date += part.c_str();
  ml::PathUtil::itoa(part, local->tm_min, 2);
  date += part.c_str();
  ml::PathUtil::itoa(part, local->tm_sec, 2);
  date += part.c_str();
  strcpy(name, date.c_str());
}

void mlGetStackAdr(u64 *address, u64 *size) {
  *address = 0;
  *size = 0;
}

bool mlSJIStoUTF8() { return false; }

long mlUtf8len(const char *source) {
  size_t length = strlen(source);
  if (length == 0) {
    return 0;
  }
  long count = 0;
  size_t i = 0;
  while (i < length) {
    u8 c = source[i];
    if (c != 0) {
      if (c < 0x80) {
        i += 1;
      } else if (c > 0xc1) {
        if (c < 0xe0) {
          i += 2;
        } else if (c < 0xf0) {
          i += 3;
        } else if (c < 0xf8) {
          i += 4;
        } else if (c < 0xfc) {
          i += 5;
        } else if (c < 0xfe) {
          i += 6;
        } else {
          i += 1;
        }
      }
    }
    count++;
  }
  return count;
}

bool mlSaveLog() { return true; }

bool mlSaveSnap() { return true; }

void mlSetLogTitleDir() {}

bool mlGetEnvVariable(size_t *length, char *buffer, size_t bufferSize) {
  *length = 0;
  if (bufferSize != 0) {
    buffer[0] = 0;
  }
  return false;
}

bool mlGetCurrentPath(char *path) {
  path[0] = 0;
  return false;
}

bool mlGetModulePath(char *path) {
  path[0] = 0;
  return false;
}
}
