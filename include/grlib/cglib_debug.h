#pragma once
#include "types.h"

namespace grlib {

class CGLibDebug {
public:
  static void setCmdLabel(const char *label);
  static void setPushDebugGroup(const char *name);
  static void setPopDebugGroup();
  static f32 getGLVersion();
  static const char *getGpuName();
};

} // namespace grlib
