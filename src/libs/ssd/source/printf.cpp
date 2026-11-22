#include <stdarg.h>

#include "ssd/ssd_debug.h"
#include "ssd/ssd_text.h"

namespace ssd {

void printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  char text[256];
  vsprintf(text, sizeof(text), format, args);
  va_end(args);
  char16_t wide[256];
  SjisToUTF16(text, wide, 256);
  Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(0), wide);
}

int vsprintf(char *buffer, unsigned long size, const char *format, va_list args) { return vsprintf_impl<char>(buffer, size, format, args) - buffer; }

void printf(const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  char16_t text[256];
  vsprintf(text, 512, format, args);
  va_end(args);
  Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(0), text);
}

unsigned long vsprintf(char16_t *buffer, unsigned long size, const char16_t *format, va_list args) {
  return (reinterpret_cast<unsigned long>(vsprintf_impl<char16_t>(buffer, size, format, args)) - reinterpret_cast<unsigned long>(buffer)) / sizeof(char16_t);
}

int sprintf(char *buffer, unsigned long size, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *end = vsprintf_impl<char>(buffer, size, format, args);
  va_end(args);
  return end - buffer;
}

unsigned long sprintf(char16_t *buffer, unsigned long size, const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  char16_t *end = vsprintf_impl<char16_t>(buffer, size, format, args);
  va_end(args);
  return (reinterpret_cast<unsigned long>(end) - reinterpret_cast<unsigned long>(buffer)) / sizeof(char16_t);
}

} // namespace ssd
