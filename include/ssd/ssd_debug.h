#pragma once
#include <stddef.h>

#include "ssd/ssd_result.h"
#include "types.h"

namespace ssd {
class Mutex;

struct LogMessage {
  enum Type {};
};

struct LogTimeStamp {
  enum Type {
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

void log_message(const char *format, ...);
void log_message(const char16_t *format, ...);
const char16_t *get_logfilename(const char16_t *path);
void abort();
Result log_error(Result result, Debug::LogFlag::Type flag, const char *format, ...);
Result log_error(Result result, Debug::LogFlag::Type flag, const char16_t *format, ...);

} // namespace ssd
