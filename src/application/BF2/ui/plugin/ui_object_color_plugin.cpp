#include "ui/plugin/ui_object_color_plugin.h"

#include "framework/memory/framework_memory.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "ui/ctrl/ui_ctrl_simple.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_color_library.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

namespace {

bool isSameColor(const mm::Col3 &a, const mm::Col3 &b) { return mm::fabs(a.r - b.r) <= 1e-6f && mm::fabs(a.g - b.g) <= 1e-6f && mm::fabs(a.b - b.b) <= 1e-6f; }

} // namespace

UIObjectColorPlugin::UIObjectColorPlugin() : color(1.0f, 1.0f, 1.0f), colorMode(COLOR_MODE_MUL) {}

UIObjectColorPlugin::~UIObjectColorPlugin() { ; }

UIObjectColorPlugin *UIObjectColorPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 45
  UIObjectColorPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectColorPlugin();
  plugin->addRef();
  UIObjectAcc acc(handle);
  if (acc.isValid() && UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    acc.getMulColor(plugin->color);
    plugin->init(handle);
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

void UIObjectColorPlugin::setMulColor(const mm::Col3 &color) {
  colorMode = COLOR_MODE_MUL;
  if (!isSameColor(color, this->color)) {
    this->color = color;
    needUpdate |= true;
  }
}

void UIObjectColorPlugin::setMulColor(const char *name) {
  mm::Col4 libraryColor;
  if (UIColorLibrary::get()->find(name, libraryColor)) {
    setMulColor(mm::Col3(libraryColor.r, libraryColor.g, libraryColor.b));
  }
}

void UIObjectColorPlugin::setAddColor(const mm::Col3 &color) {
  colorMode = COLOR_MODE_ADD;
  if (!isSameColor(color, this->color)) {
    this->color = color;
    needUpdate |= true;
  }
}

void UIObjectColorPlugin::setAddColor(const char *name) {
  mm::Col4 libraryColor;
  if (UIColorLibrary::get()->find(name, libraryColor)) {
    setAddColor(mm::Col3(libraryColor.r, libraryColor.g, libraryColor.b));
  }
}

void UIObjectColorPlugin::setColorMode(u32 mode) {
  if (mode <= COLOR_MODE_ADD) {
    colorMode = mode;
  }
}

void UIObjectColorPlugin::setColor(const mm::Col3 &color) {
  switch (colorMode) {
  case COLOR_MODE_MUL:
    setMulColor(color);
    break;
  case COLOR_MODE_ADD:
    setAddColor(color);
    break;
  }
}

void UIObjectColorPlugin::setColor(const char *name) {
  switch (colorMode) {
  case COLOR_MODE_MUL:
    setMulColor(name);
    break;
  case COLOR_MODE_ADD:
    setAddColor(name);
    break;
  }
}

void UIObjectColorPlugin::execute(UIObjectAcc &acc) {
  switch (colorMode) {
  case COLOR_MODE_MUL:
    acc.setMulColor(color);
    break;
  case COLOR_MODE_ADD:
    acc.setAddColor(color);
    break;
  }
  UIObjectDispPlugin::execute(acc);
}

const mm::mtl::RTTI *UIObjectColorPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectColorPlugin::isNeedUpdate(UIObjectAcc &acc) { return (needUpdate & 1) || acc.isDisp() != disp || fadeUpdater.ctrl != nullptr || followObjHandle != 0; }

} // namespace ui
