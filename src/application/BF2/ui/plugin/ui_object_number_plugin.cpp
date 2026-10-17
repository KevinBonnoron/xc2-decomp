#include "ui/plugin/ui_object_number_plugin.h"

#include <string.h>

#include "framework/lang_util.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectNumberPlugin::UIObjectNumberPlugin()
    : number(0), min(0), max(9999), type(TYPE_NONE), isReverse(false), interpolate(false), format(nullptr), interpolateTime(0.0f) {}

UIObjectNumberPlugin::~UIObjectNumberPlugin() {
  if (interpolationUpdater.ctrl != nullptr) {
    UICtrlManager::get()->delUpdater(interpolationUpdater);
  }
  interpolationUpdater.ctrl = nullptr;
}

UIObjectNumberPlugin *UIObjectNumberPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 56
  UIObjectNumberPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectNumberPlugin();
  plugin->addRef();
  UIObjectAcc acc(handle);
  if (acc.isValid()) {
    int max;
    if (acc.isText()) {
      const char *text = acc.getTextPtr();
      plugin->format = text;
      if (text == nullptr || !UIUtil::checkNumberTextFormat(text, 1)) {
        plugin->format = "e%d";
      }
      plugin->type = strstr(text, "%s") != nullptr ? TYPE_TEXT_STRING : TYPE_TEXT;
      max = 9999;
    } else if (acc.isImage()) {
      max = acc.getImageMax();
      plugin->type = TYPE_IMAGE;
    } else if (acc.isLayout()) {
      plugin->setDispControl(false);
      max = 9999;
    } else {
      mm::mtl::safeRelease(plugin);
      return plugin;
    }

    if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
      plugin->max = max;
      plugin->number = 0;
      plugin->min = 0;
      plugin->init(handle);
      return plugin;
    }
  }
  mm::mtl::safeRelease(plugin);
  return plugin;
}

UIObjectNumberPlugin *UIObjectNumberPlugin::getPlugin(u32 handle) {
  UIObject *object = UIUtil::getObject(handle);
  if (object == nullptr) {
    return nullptr;
  }
  UIObjectPlugin *plugin = object->plugins;
  if (plugin == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<UIObjectNumberPlugin>(plugin);
}

void UIObjectNumberPlugin::setMin(int min) {
  if (max <= min) {
    max = min + 1;
  }
  if (this->min != min) {
    this->min = min;
    needUpdate |= true;
  }
}

void UIObjectNumberPlugin::setMax(int max) {
  if (max <= min) {
    max = min + 1;
  }
  if (max != this->max) {
    this->max = max;
    needUpdate |= true;
  }
}

void UIObjectNumberPlugin::setInterpolate(f32 time) {
  interpolate = true;
  interpolateTime = time;
}

void UIObjectNumberPlugin::reload(UIObjectAcc &acc) {
  if (type != TYPE_TEXT && type != TYPE_TEXT_STRING) {
    return;
  }

  const char *text = acc.getTextPtr();
  format = text;
  if (text == nullptr || !UIUtil::checkNumberTextFormat(text, 1)) {
    format = "e%d";
  }
  type = strstr(text, "%s") != nullptr ? TYPE_TEXT_STRING : TYPE_TEXT;
  needUpdate |= true;
}

void UIObjectNumberPlugin::refreshMoneySeparetor() { s_MoneySeparetor = UIUtil::getMoneySeparetor(fw::LangUtil::getLangType()); }

const mm::mtl::RTTI *UIObjectNumberPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectNumberPlugin::isNeedUpdate(UIObjectAcc &acc) {
  return (needUpdate & 1) || interpolationUpdater.ctrl != nullptr || acc.isDisp() != disp || fadeUpdater.ctrl != nullptr || followObjHandle != 0;
}

} // namespace ui
