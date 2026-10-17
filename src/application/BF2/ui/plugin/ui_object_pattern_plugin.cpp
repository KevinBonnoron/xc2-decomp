#include "ui/plugin/ui_object_pattern_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/ctrl/ui_ctrl_simple.h"
#include "ui/font/ui_font_manager.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectPatternPlugin::UIObjectPatternPlugin() : facePattern(0) {}

UIObjectPatternPlugin::~UIObjectPatternPlugin() { ; }

UIObjectPatternPlugin *UIObjectPatternPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 44
  UIObjectPatternPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectPatternPlugin();
  plugin->addRef();
  UIObjectAcc acc(handle);
  if (acc.isValid() && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->facePattern = acc.getTextFacePatternIndex();
    plugin->init(handle);
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

void UIObjectPatternPlugin::setFacePattern(const char *name) {
  u32 index;
  if (name != nullptr && UIFontManager::get()->findFacePattern(name, index) && facePattern != index) {
    facePattern = index;
    needUpdate |= true;
  }
}

void UIObjectPatternPlugin::execute(UIObjectAcc &acc) {
  acc.setTextFacePattern(facePattern);
  UIObjectDispPlugin::execute(acc);
}

const mm::mtl::RTTI *UIObjectPatternPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectPatternPlugin::isNeedUpdate(UIObjectAcc &acc) {
  return (needUpdate & 1) || acc.isDisp() != disp || fadeUpdater.ctrl != nullptr || followObjHandle != 0;
}

} // namespace ui
