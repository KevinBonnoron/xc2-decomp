#include "ml/ml_misc.h"

#include <string.h>
#include <time.h>

#include "ml/char_code.h"
#include "ml/critical_section.h"
#include "ml/path_util.h"
#include "ml/stack_trace.h"
#include "ml/time_util.h"
#include "ml/work_cpu.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace _mlmisc {

ml::CriticalSection &getCriticalSection() {
  static ml::CriticalSection sect;
  return sect;
}

} // namespace _mlmisc

namespace {

// Inferred role: Shift-JIS / UTF-16 conversion table, 0x7100f77138 in the game (27512 bytes): 6878 pairs of u16, the
// Shift-JIS code then the UTF-16 code, sorted by Shift-JIS code; original name unknown.
const u16 unknown001[] = {
#include "util/ml_char_code_table.inl" // IWYU pragma: keep
};

// Inferred role: index of the conversion buffer of the calling thread (the game clamps the CPU id minus one to the
// three buffers); original name unknown.
int unknown002() {
  int index = ml::WorkCpu::getCurrentCPUID() - 1;
  if (index > 2) {
    index = 2;
  }
  if (index < 0) {
    index = 0;
  }
  return index;
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the
// match proves; rename if a sibling build gives a symbol. Inferred role: Shift-JIS code to UTF-16 code, 0xffff when the
// table has no entry. Its user is mlSJIStoUTF16 (0x710075d988); with the search written inside the function the best
// form measured (about twenty source forms: declaration orders of the search variables, loop shapes, local pointers
// and variable types) keeps 7 to 14 instructions different, the helper matches.
u16 sjisToUTF16(u32 code) {
  if (code < 0x80) {
    return code;
  }
  u32 low = 0;
  u32 high = sizeof(unknown001) / sizeof(u16) / 2;
  u32 count = high;
  while (count > 16) {
    count /= 2;
    u32 middle = low + count;
    if (unknown001[middle * 2] > code) {
      high = middle;
    } else {
      low = middle;
      count = high - middle;
    }
  }
  for (u32 i = low; i < high; i++) {
    if (unknown001[i * 2] == code) {
      return unknown001[i * 2 + 1];
    }
  }
  return 0xffff;
}

} // namespace

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

bool mlUTF16toSJIS(char *destination, size_t destinationSize, const u16 *source) {
  ml::CS lock(_mlmisc::getCriticalSection());
  size_t length = 0;
  for (; *source != 0; source++) {
    u16 ch = *source;
    u16 code = ch;
    if (ch >= 0x80) {
      code = 0xffff;
      for (size_t i = 0; i < sizeof(unknown001) / sizeof(u16) / 2; i++) {
        if (unknown001[i * 2 + 1] == ch) {
          code = unknown001[i * 2];
          break;
        }
      }
    }
    if (code == 0xffff) {
      destination[length++] = ' ';
    } else if (code <= 0x7f) {
      destination[length++] = code & 0x7f;
    } else {
      char *out = destination + length;
      out[0] = code >> 8;
      out[1] = code;
      length += 2;
    }
  }
  destination[length] = 0;
  return true;
}

bool mlSJIStoUTF16(u16 *destination, size_t destinationSize, const char *source) {
  ml::CS lock(_mlmisc::getCriticalSection());
  size_t length = 0;
  while (*source) {
    u8 lead = *source++;
    u32 code = lead;
    if (lead >= 0x81 && lead <= 0x98) {
      code = (lead << 8) | static_cast<u8>(*source++);
    }
    u16 utf16 = sjisToUTF16(code);
    if (utf16 == 0xffff) {
      destination[length] = ' ';
    } else {
      destination[length] = utf16;
    }
    length++;
  }
  destination[length] = 0;
  return true;
}

bool mlUTF8toUTF16(u16 *destination, size_t destinationLength, const char *source) {
  ml::CS lock(_mlmisc::getCriticalSection());
  size_t length = 0;
  while (*source) {
    u8 lead = *source;
    if ((lead & 0x80) == 0) {
      destination[length] = lead & 0x7f;
      source += 1;
    } else if ((lead & 0xe0) == 0xc0) {
      destination[length] = (lead & 0x1f) << 6;
      destination[length] |= source[1] & 0x3f;
      source += 2;
    } else if ((lead & 0xf0) == 0xe0) {
      destination[length] = lead << 12;
      destination[length] |= (source[1] & 0x3f) << 6;
      destination[length] |= source[2] & 0x3f;
      source += 3;
    } else {
      break;
    }
    length++;
  }
  destination[length] = 0;
  return true;
}

char *mlGetSJIS(const u16 *source) {
  ml::CS lock(_mlmisc::getCriticalSection());
  // The game has a function-local buffer here, but no symbol names it; the original name is unknown.
  static char unknown003[3][1024];
  char *buffer = unknown003[unknown002()];
  mlUTF16toSJIS(buffer, sizeof(unknown003[0]), source);
  return buffer;
}

u16 *mlGetUTF16(const char *source) {
  ml::CS lock(_mlmisc::getCriticalSection());
  // The game has a function-local buffer here, but no symbol names it; the original name is unknown.
  static u16 unknown003[3][512];
  u16 *buffer = unknown003[unknown002()];
  mlSJIStoUTF16(buffer, sizeof(unknown003[0]) / sizeof(u16), source);
  return buffer;
}

u16 *mlGetUTF16ByUTF8(const char *source) {
  ml::CS lock(_mlmisc::getCriticalSection());
  // The game has a function-local buffer here, but no symbol names it; the original name is unknown.
  static u16 unknown003[3][512];
  u16 *buffer = unknown003[unknown002()];
  mlUTF8toUTF16(buffer, sizeof(unknown003[0]) / sizeof(u16), source);
  return buffer;
}

bool mlSJIStoUTF8() { return false; }

void mlGetUtf16Info(const void **table, size_t *size) {
  *table = unknown001;
  *size = sizeof(unknown001);
}

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
