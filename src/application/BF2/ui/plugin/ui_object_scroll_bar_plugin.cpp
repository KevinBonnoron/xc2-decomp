#include "ui/plugin/ui_object_scroll_bar_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectScrollBarPlugin::UIObjectScrollBarPlugin() : unknown20(nullptr), unknown28(0), unknown2c(0), unknown30(0, 0), unknown50(true) {}

UIObjectScrollBarPlugin::~UIObjectScrollBarPlugin() { ; }

UIObjectScrollBarPlugin *UIObjectScrollBarPlugin::create(u32 handle, u32 direction, const UIListInfoBase *list, const char *barName) {
  UIObjectScrollBarPlugin *plugin = nullptr;
  if (list != nullptr && barName != nullptr) {
// __LINE__ is the line argument of the operator new call.
#line 51
    plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectScrollBarPlugin();
    plugin->addRef();
    UIObjectAcc acc(handle);
    if (acc.isValid() && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
      plugin->unknown20 = list;
      plugin->unknown28 = acc.searchSibiling(barName);
      plugin->unknown2c = direction;
      acc.getPos(plugin->unknown30);
      acc.getScale(plugin->unknown40);
    } else if (plugin != nullptr) {
      plugin->release();
      plugin = nullptr;
    }
  }
  return plugin;
}

void UIObjectScrollBarPlugin::setScaleEnable(bool enable) { unknown50 = enable; }

const mm::mtl::RTTI *UIObjectScrollBarPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectScrollBarPlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
