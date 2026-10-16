#include <stdarg.h>
#include <stdio.h>

#include "mm/mm_std_base.h"
#include "nn/diag.h"

namespace mm {

MMStdBase *MMStdBase::s_pCurrentStd;
MMStd s_mm_std;

MMStdBase::MMStdBase() { s_pCurrentStd = this; }

void MMStdBase::mmPrint(const char *format, ...) {
  char buffer[0x400];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  s_pCurrentStd->customOutput(buffer);
}

void MMStd::customOutput(const char *text) {
// The log records its line number.
#line 67
  NN_LOG(text);
}

void MMStdBase::mmAssert(const char *cond, const char *file, unsigned int line) { s_pCurrentStd->customAssert(cond, file, line); }

void MMStdBase::mmAssertMsg(const char *cond, const char *file, unsigned int line, const char *format, ...) {
  char buffer[0x1000];
  va_list args;
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  s_pCurrentStd->customAssertMsg(cond, file, line, buffer);
}

void MMStd::customAssert(const char *cond, const char *file, unsigned int line) {
  mmPrint("Failed assertion at %s:%d\n  ", file, line);
  mmPrint(cond);
  mmPrint("\n");
  asm volatile(".inst 0xe7ffdefe");
}

void MMStd::customAssertMsg(const char *cond, const char *file, unsigned int line, const char *message) {
  mmPrint("Failed assertion at %s:%d\n  ", file, line);
  mmPrint(cond);
  mmPrint("\n");
  mmPrint("%s\n", message);
  asm volatile(".inst 0xe7ffdefe");
}

} // namespace mm
