#include <stdarg.h>

#include "nn/diag.h"
#include "ssd/ssd_debug.h"
#include "ssd/ssd_mutex.h"
#include "ssd/ssd_sound_core.h"
#include "ssd/ssd_text.h"
#include "types.h"

namespace ssd {
enum Result : long;

void abort() { nn::diag::detail::AbortImpl("", "", "", 0); }

void log_make_text(char *buffer, unsigned long size, const char *format, va_list args) {
  char timeStamp[32];
  get_log_time_stamp(SoundCore::instance_->GetLogTimeStampType(), timeStamp, sizeof(timeStamp));
  char text[256];
  vsprintf(text, sizeof(text), format, args);
  sprintf(buffer, size, "SSD %s: %s\n", timeStamp, text);
}

void log_make_text(char16_t *buffer, unsigned long size, const char16_t *format, va_list args) {
  char16_t timeStamp[32];
  get_log_time_stamp(SoundCore::instance_->GetLogTimeStampType(), timeStamp, sizeof(timeStamp));
  char16_t text[256];
  vsprintf(text, sizeof(text), format, args);
  sprintf(buffer, size, u"SSD %s: %s\n", timeStamp, text);
}

void log_debug(Debug::LogFlag::Type flag, const char *format, ...) {
  va_list args;
  va_start(args, format);
  if ((Debug::log_.unknown0c & flag) != 0) {
    char buffer[256];
    log_make_text(buffer, sizeof(buffer), format, args);
    char16_t text[256];
    Utf8ToUTF16(buffer, text, 256);
    Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(4), text);
  }
  va_end(args);
}

void log_debug(Debug::LogFlag::Type flag, const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  if ((Debug::log_.unknown0c & flag) != 0) {
    char16_t buffer[256];
    log_make_text(buffer, sizeof(buffer), format, args);
    Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(4), buffer);
  }
  va_end(args);
}

void log_message(const char *format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[256];
  log_make_text(buffer, sizeof(buffer), format, args);
  va_end(args);
  char16_t text[256];
  Utf8ToUTF16(buffer, text, 256);
  Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(0), text);
}

void log_message(const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  char16_t buffer[256];
  log_make_text(buffer, sizeof(buffer), format, args);
  va_end(args);
  Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(0), buffer);
}

void log_error(Result result, Debug::LogFlag::Type flag, const char *format, ...) {
  va_list args;
  va_start(args, format);
  if (SoundCore::instance_ != nullptr) {
    SoundCore::instance_->unknown08 = result;
  }
  if ((Debug::log_.m_errorLogFlag & flag) != 0) {
    char buffer[256];
    log_make_text(buffer, sizeof(buffer), format, args);
    char16_t text[256];
    Utf8ToUTF16(buffer, text, 256);
    Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(2), text);
  }
  va_end(args);
}

void log_error(Result result, Debug::LogFlag::Type flag, const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  if (SoundCore::instance_ != nullptr) {
    SoundCore::instance_->unknown08 = result;
  }
  if ((Debug::log_.m_errorLogFlag & flag) != 0) {
    char16_t buffer[256];
    log_make_text(buffer, sizeof(buffer), format, args);
    Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(2), buffer);
  }
  va_end(args);
}

void log_warning(Result result, Debug::LogFlag::Type flag, const char *format, ...) {
  va_list args;
  va_start(args, format);
  if (SoundCore::instance_ != nullptr) {
    SoundCore::instance_->unknown08 = result;
  }
  if ((Debug::log_.m_warningLogFlag & flag) != 0) {
    char buffer[256];
    log_make_text(buffer, sizeof(buffer), format, args);
    char16_t text[256];
    Utf8ToUTF16(buffer, text, 256);
    Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(1), text);
  }
  va_end(args);
}

void log_warning(Result result, Debug::LogFlag::Type flag, const char16_t *format, ...) {
  va_list args;
  va_start(args, format);
  if (SoundCore::instance_ != nullptr) {
    SoundCore::instance_->unknown08 = result;
  }
  if ((Debug::log_.m_warningLogFlag & flag) != 0) {
    char16_t buffer[256];
    log_make_text(buffer, sizeof(buffer), format, args);
    Debug::log_.m_messageMethod(static_cast<LogMessage::Type>(1), buffer);
  }
  va_end(args);
}

const char16_t *get_logfilename(const char16_t *path) {
  const char16_t *name = path;
  for (const char16_t *p = path; *p != u'\0'; p++) {
    if (*p == u'/') {
      name = p + 1;
    }
  }
  return name;
}

namespace Debug {

unknown002 log_;

void Init() {
  log_.m_logTimeStampType = LogTimeStamp::TYPE_UNKNOWN_3;
  log_.m_errorLogFlag = 0x10000015;
  log_.m_warningLogFlag = 0x10000015;
  log_.unknown0c = 0x10000015;
  log_.m_messageMethod = LogMethodT;
}

Result LogMethodT(LogMessage::Type type, const char16_t *text) { return static_cast<Result>(0); }

void SetMessageMethod(unknown001 method) { log_.m_messageMethod = method != nullptr ? method : LogMethodT; }

void SetTimeStampType(LogTimeStamp::Type type) { log_.m_logTimeStampType = type; }

void OnWarningFlag(u32 flag) { log_.m_warningLogFlag |= flag; }

void OnErrorFlag(u32 flag) { log_.m_errorLogFlag |= flag; }

} // namespace Debug

Mutex OutStreamLock;

void InitDebug() { OutStreamLock.unknown001(); }

void QuitDebug() { OutStreamLock.unknown002(); }

} // namespace ssd
