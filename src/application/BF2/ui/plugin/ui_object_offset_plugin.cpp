#include "ui/plugin/ui_object_offset_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectOffsetPlugin::UIObjectOffsetPlugin() {
  targetPos.x = 0;
  targetPos.y = 0;
  maxOffset.x = 0xffff;
  maxOffset.y = 0xffff;
}

UIObjectOffsetPlugin::~UIObjectOffsetPlugin() { ; }

UIObjectOffsetPlugin *UIObjectOffsetPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 42
  UIObjectOffsetPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectOffsetPlugin();
  plugin->addRef();
  if (!UIObjectPluginUtil::attachPlugin(handle, plugin) && plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

const mm::mtl::RTTI *UIObjectOffsetPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectOffsetPlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
