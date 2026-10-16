#pragma once

namespace grlib {

class CGLibDebug {
public:
  static void setPushDebugGroup(const char *name);
  static void setPopDebugGroup();
};

} // namespace grlib
