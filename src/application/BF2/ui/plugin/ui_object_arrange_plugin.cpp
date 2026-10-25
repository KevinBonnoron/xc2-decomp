#include "ui/plugin/ui_object_arrange_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectArrangePlugin::UIObjectArrangePlugin() : unknown7c(true) {}

UIObjectArrangePlugin::~UIObjectArrangePlugin() { ; }

UIObjectArrangePlugin *UIObjectArrangePlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 45
  UIObjectArrangePlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectArrangePlugin();
  plugin->addRef();
  if (!UIObjectPluginUtil::attachPlugin(handle, plugin) && plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

const mm::mtl::RTTI *UIObjectArrangePlugin::getRTTI() const { return &m_rtti; }

bool UIObjectArrangePlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
