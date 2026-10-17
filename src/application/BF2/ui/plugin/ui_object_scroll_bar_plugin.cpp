#include "ui/plugin/ui_object_scroll_bar_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectScrollBarPlugin::UIObjectScrollBarPlugin() : list(nullptr), bar(0), direction(0), basePos(0, 0), scaleEnable(true) {}

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
      plugin->list = list;
      plugin->bar = acc.searchSibiling(barName);
      plugin->direction = direction;
      acc.getPos(plugin->basePos);
      acc.getScale(plugin->baseScale);
    } else if (plugin != nullptr) {
      plugin->release();
      plugin = nullptr;
    }
  }
  return plugin;
}

void UIObjectScrollBarPlugin::setScaleEnable(bool enable) { scaleEnable = enable; }

const mm::mtl::RTTI *UIObjectScrollBarPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectScrollBarPlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
