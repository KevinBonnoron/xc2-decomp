#include "ui/plugin/ui_object_world_pos_plugin.h"

#include "framework/memory/framework_memory.h"
#include "layer/layer_acc_obj_base.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectWorldPosPlugin::UIObjectWorldPosPlugin() : unknowna0(0.0f, 0.0f, 0.0f) {}

UIObjectWorldPosPlugin::~UIObjectWorldPosPlugin() { ; }

UIObjectWorldPosPlugin *UIObjectWorldPosPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 44
  UIObjectWorldPosPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectWorldPosPlugin();
  plugin->addRef();
  if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    layer::LayerAccObjBase(UIUtil::getObject(handle)->unknownc8).setSpace(static_cast<layer::LAYER_SPACE_TYPE>(1));
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

const mm::mtl::RTTI *UIObjectWorldPosPlugin::getRTTI() const { return &m_rtti; }

} // namespace ui
