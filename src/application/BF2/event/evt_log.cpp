#include "event/evt_log.h"

#include <stdarg.h>

namespace event {

void EvtLog::setFrame(float frame) {}

void EvtLog::log(const char *format, ...) {
  va_list args;
  va_start(args, format);
  va_end(args);
}

} // namespace event
