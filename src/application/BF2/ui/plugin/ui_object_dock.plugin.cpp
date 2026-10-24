#include "framework/memory/framework_memory.h"
#include "mm_math/mm_pnt.h"
#include "types.h"
#include "ui/plugin/ui_object_dock_plugin.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectDockPlugin::UIObjectDockPlugin(u32 target) : target(target), offset(0, 0), dockType(0), alignType(0), reverse(0), area(0, 0, 0, 0) { UIUtil::isValid(target); }

UIObjectDockPlugin::~UIObjectDockPlugin() { ; }

UIObjectDockPlugin *UIObjectDockPlugin::create(u32 handle, s16 offsetX, s16 offsetY, u32 target) {
// __LINE__ is the line argument of the operator new call.
#line 53
  UIObjectDockPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectDockPlugin(target);
  plugin->addRef();
  if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->offset.x = offsetX;
    plugin->offset.y = offsetY;
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

const mm::mtl::RTTI *UIObjectDockPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectDockPlugin::isNeedUpdate(UIObjectAcc &acc) { return acc.isDisp(); }

} // namespace ui
