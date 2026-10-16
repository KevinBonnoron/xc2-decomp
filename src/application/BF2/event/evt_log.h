#pragma once

namespace event {

class EvtLog {
public:
  static void setFrame(float frame);
  static void log(const char *format, ...);
};

} // namespace event
