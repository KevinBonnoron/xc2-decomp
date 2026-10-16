#pragma once

namespace event {

class AgelogUtil {
public:
  static void setPath(const char *path);
  static void print(const char *format, ...);
};

} // namespace event
