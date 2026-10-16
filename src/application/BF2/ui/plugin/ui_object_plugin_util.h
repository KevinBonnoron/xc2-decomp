#pragma once
#include "types.h"

namespace ui {

class UIObjectPlugin;

class UIObjectPluginUtil {
public:
  static bool attachPlugin(u32 handle, UIObjectPlugin *plugin);
  static bool detachPlugin(u32 handle);
};

} // namespace ui
