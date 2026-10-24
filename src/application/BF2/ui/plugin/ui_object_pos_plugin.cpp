#include "ui/plugin/ui_object_pos_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectPosPlugin::UIObjectPosPlugin() : unknown7c(0, 0), unknown80(false), unknown8c(0), unknown90(false) {
  unknown82 = 0;
  unknown84 = 0;
  unknown86 = 0;
  unknown88 = 0;
}

UIObjectPosPlugin::~UIObjectPosPlugin() { ; }

UIObjectPosPlugin *UIObjectPosPlugin::create(u32 handle, s16 x, s16 y) {
// __LINE__ is the line argument of the operator new call.
#line 49
  UIObjectPosPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectPosPlugin();
  plugin->addRef();
  if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->unknown7c.x = x;
    plugin->unknown7c.y = y;
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

const mm::mtl::RTTI *UIObjectPosPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectPosPlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
