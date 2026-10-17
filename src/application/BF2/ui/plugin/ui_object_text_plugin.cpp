#include "ui/plugin/ui_object_text_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/ctrl/ui_ctrl_simple.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectTextPlugin::UIObjectTextPlugin() {}

UIObjectTextPlugin::~UIObjectTextPlugin() {}

UIObjectTextPlugin *UIObjectTextPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 44
  UIObjectTextPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectTextPlugin();
  plugin->addRef();
  UIObjectAcc acc(handle);
  if (acc.isValid() && acc.isText() && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->init(handle);
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

void UIObjectTextPlugin::setText(const UIStr &text) {
  if (text.isValid() && !this->text.compare(text)) {
    this->text.copy(text);
    needUpdate |= true;
  }
}

void UIObjectTextPlugin::execute(UIObjectAcc &acc) {
  if (text.isValid()) {
    acc.setText(text);
  }
  UIObjectDispPlugin::execute(acc);
}

const mm::mtl::RTTI *UIObjectTextPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectTextPlugin::isNeedUpdate(UIObjectAcc &acc) {
  return (needUpdate & 1) || acc.isDisp() != disp || fadeUpdater.ctrl != nullptr || followObjHandle != 0;
}

} // namespace ui
