#include "ui/plugin/ui_object_pattern_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/ctrl/ui_ctrl_simple.h"
#include "ui/font/ui_font_manager.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectPatternPlugin::UIObjectPatternPlugin() : unknown7c(0) {}

UIObjectPatternPlugin::~UIObjectPatternPlugin() { ; }

UIObjectPatternPlugin *UIObjectPatternPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 44
  UIObjectPatternPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectPatternPlugin();
  plugin->addRef();
  UIObjectAcc acc(handle);
  if (acc.isValid() && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->unknown7c = acc.getTextFacePatternIndex();
    plugin->init(handle);
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

void UIObjectPatternPlugin::setFacePattern(const char *name) {
  u32 index;
  if (name != nullptr && UIFontManager::get()->findFacePattern(name, index) && unknown7c != index) {
    unknown7c = index;
    unknown18 |= true;
  }
}

void UIObjectPatternPlugin::execute(UIObjectAcc &acc) {
  acc.setTextFacePattern(unknown7c);
  UIObjectDispPlugin::execute(acc);
}

const mm::mtl::RTTI *UIObjectPatternPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectPatternPlugin::isNeedUpdate(UIObjectAcc &acc) { return (unknown18 & 1) || acc.isDisp() != unknown1d || unknown58.ctrl != nullptr || m_followObjHandle != 0; }

} // namespace ui
