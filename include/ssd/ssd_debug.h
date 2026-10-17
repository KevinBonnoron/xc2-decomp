#pragma once
#include "ssd/ssd_result.h"

namespace ssd {

namespace Debug {

struct LogFlag {
  enum Type {
    All = 0x7fffffff,
  };
};

} // namespace Debug

Result log_error(Result result, Debug::LogFlag::Type flag, const char *format, ...);
Result log_error(Result result, Debug::LogFlag::Type flag, const char16_t *format, ...);

} // namespace ssd
