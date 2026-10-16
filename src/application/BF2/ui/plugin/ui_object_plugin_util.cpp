#include "ui/plugin/ui_object_plugin_util.h"

#include "ui/ui_object.h"
#include "ui/ui_util.h"

namespace ui {

bool UIObjectPluginUtil::attachPlugin(u32 handle, UIObjectPlugin *plugin) {
  if (UIUtil::isValid(handle)) {
    UIUtil::getObject(handle)->attachPlugin(plugin);
    return true;
  }
  return false;
}

bool UIObjectPluginUtil::detachPlugin(u32 handle) {
  if (UIUtil::isValid(handle)) {
    UIUtil::getObject(handle)->attachPlugin(nullptr);
    return true;
  }
  return false;
}

} // namespace ui
