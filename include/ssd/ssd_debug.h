#pragma once
#include <stdarg.h>
#include <stddef.h>

#include "ssd/ssd_result.h"
#include "types.h"

// Probably the library's assert macro. Inferred macro name; macros leave no trace in the binary.
#define SSD_ASSERT(condition, format, text, file, line, ...)                                                                                                                                           \
  do {                                                                                                                                                                                                 \
    if (!(condition)) {                                                                                                                                                                                \
      ssd::log_message(format, text, ssd::get_logfilename(file), line, ##__VA_ARGS__);                                                                                                                 \
      ssd::abort();                                                                                                                                                                                    \
    }                                                                                                                                                                                                  \
  } while (0)

namespace ssd {
class Mutex;

struct LogMessage {
  enum Type {};
};

struct LogTimeStamp {
  enum Type {
    TYPE_UNKNOWN_1 = 1,
    TYPE_UNKNOWN_3 = 3,
  };
};

namespace Debug {

struct LogFlag {
  enum Type {
    All = 0x7fffffff,
  };
};

typedef Result (*unknown001)(LogMessage::Type type, const char16_t *text);

struct unknown002 {
  LogTimeStamp::Type m_logTimeStampType;
  u32 m_errorLogFlag;
  u32 m_warningLogFlag;
  u32 unknown0c;        // Inferred role: unused log flag set by Init; original member name unknown.
  unknown001 unknown10; // Inferred role: message method; original member name unknown.
};

static_assert(offsetof(unknown002, m_errorLogFlag) == 0x4, "");
static_assert(offsetof(unknown002, unknown10) == 0x10, "");

extern unknown002 log_;

void Init();
Result LogMethodT(LogMessage::Type type, const char16_t *text);
void SetMessageMethod(unknown001 method);
void SetTimeStampType(LogTimeStamp::Type type);
void OnWarningFlag(u32 flag);
void OnErrorFlag(u32 flag);

} // namespace Debug

extern Mutex OutStreamLock;

void InitDebug();
void QuitDebug();

void get_log_time_stamp(LogTimeStamp::Type type, char *buffer, unsigned long size);
void get_log_time_stamp(LogTimeStamp::Type type, char16_t *buffer, unsigned long size);
void log_make_text(char *buffer, unsigned long size, const char *format, va_list args);
void log_make_text(char16_t *buffer, unsigned long size, const char16_t *format, va_list args);
void log_debug(Debug::LogFlag::Type flag, const char *format, ...);
void log_debug(Debug::LogFlag::Type flag, const char16_t *format, ...);
void log_message(const char *format, ...);
void log_message(const char16_t *format, ...);
void log_error(Result result, Debug::LogFlag::Type flag, const char *format, ...);
void log_error(Result result, Debug::LogFlag::Type flag, const char16_t *format, ...);
void log_warning(Result result, Debug::LogFlag::Type flag, const char *format, ...);
void log_warning(Result result, Debug::LogFlag::Type flag, const char16_t *format, ...);
const char16_t *get_logfilename(const char16_t *path);
void abort();

template <typename T> T *vsprintf_impl(T *buffer, unsigned long size, const T *format, va_list args);

int sprintf(char *buffer, unsigned long size, const char *format, ...);
unsigned long sprintf(char16_t *buffer, unsigned long size, const char16_t *format, ...);
int vsprintf(char *buffer, unsigned long size, const char *format, va_list args);
unsigned long vsprintf(char16_t *buffer, unsigned long size, const char16_t *format, va_list args);
void printf(const char *format, ...);
void printf(const char16_t *format, ...);

} // namespace ssd
