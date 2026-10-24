#include "ui/plugin/ui_object_fit_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectFitPlugin::UIObjectFitPlugin() : unknown1c(0, 0), unknown20(0, 0), unknown24(0, 0), unknown28(0) {}

UIObjectFitPlugin::~UIObjectFitPlugin() { ; }

UIObjectFitPlugin *UIObjectFitPlugin::create(u32 handle, u32 target, u16 marginX, u16 marginY) {
// __LINE__ is the line argument of the operator new call.
#line 52
  UIObjectFitPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectFitPlugin();
  plugin->addRef();
  if (UIUtil::isValid(handle) && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->unknown1c.x = marginX;
    plugin->unknown1c.y = marginY;
    plugin->unknown2c = target;
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

const mm::mtl::RTTI *UIObjectFitPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectFitPlugin::isNeedUpdate(UIObjectAcc &acc) { return acc.isDisp(); }

} // namespace ui
