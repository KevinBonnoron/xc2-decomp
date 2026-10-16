#include "event/agelog_util.h"

#include <stdarg.h>

namespace event {

void AgelogUtil::setPath(const char *path) {}

void AgelogUtil::print(const char *format, ...) {
  va_list args;
  va_start(args, format);
  va_end(args);
}

} // namespace event
