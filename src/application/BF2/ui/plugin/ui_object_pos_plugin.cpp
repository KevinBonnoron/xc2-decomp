#include "ui/plugin/ui_object_pos_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectPosPlugin::UIObjectPosPlugin() : pos(0, 0), isAdjustScreen(false), offsetMode(0), adjusting(false) {
  adjustWidth = 0;
  adjustHeight = 0;
  adjustOffsetX = 0;
  adjustOffsetY = 0;
}

UIObjectPosPlugin::~UIObjectPosPlugin() { ; }

UIObjectPosPlugin *UIObjectPosPlugin::create(u32 handle, s16 x, s16 y) {
// __LINE__ is the line argument of the operator new call.
#line 49
  UIObjectPosPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectPosPlugin();
  plugin->addRef();
  if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->pos.x = x;
    plugin->pos.y = y;
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

const mm::mtl::RTTI *UIObjectPosPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectPosPlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
