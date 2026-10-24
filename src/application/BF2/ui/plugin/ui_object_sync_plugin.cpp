#include "ui/plugin/ui_object_sync_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectSyncPlugin::UIObjectSyncPlugin() : m_targetObject(0), m_targetFlag(0) {}

UIObjectSyncPlugin::~UIObjectSyncPlugin() { ; }

UIObjectSyncPlugin *UIObjectSyncPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 45
  UIObjectSyncPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectSyncPlugin();
  plugin->addRef();
  UIObjectAcc acc(handle);
  if ((!acc.isValid() || !UIObjectPluginUtil::attachPlugin(handle, plugin)) && plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

void UIObjectSyncPlugin::setTargetObject(u32 handle) { m_targetObject = handle; }

void UIObjectSyncPlugin::setTargetFlag(u32 flags) { m_targetFlag = flags; }

const mm::mtl::RTTI *UIObjectSyncPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectSyncPlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
