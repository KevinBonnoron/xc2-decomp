#include "ui/ui_displayinfo.h"

#include "framework/memory/framework_memory.h"
#include "ui/ui_util.h"

namespace ui {

UIDisplayInfo::UIDisplayInfo() {
  disp = true;
  displayMode = 0;
  blendType = 0;
  priority = 0;
  mulColor.r = 1.0f;
  mulColor.g = 1.0f;
  mulColor.b = 1.0f;
  mulColor.a = 1.0f;
  addColor.r = 0.0f;
  addColor.g = 0.0f;
  addColor.b = 0.0f;
  pixelWidth = 0;
  pixelHeight = 0;
  dirty = false;
  defColor = nullptr;
  colorLink = nullptr;
}

UIDisplayInfo::UIDisplayInfo(const UIDisplayInfo &other) {
  disp = other.disp;
  displayMode = other.displayMode;
  blendType = other.blendType;
  priority = other.priority;
  mulColor = other.mulColor;
  addColor = other.addColor;
  pixelWidth = other.pixelWidth;
  pixelHeight = other.pixelHeight;
  dirty = false;
  defColor = nullptr;
  colorLink = nullptr;
  if (other.defColor != nullptr) {
    saveDefColor();
  }
}

void UIDisplayInfo::saveDefColor() {
  if (defColor == nullptr) {
// __LINE__ is the line argument of the operator new call.
#line 130
    defColor = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) DefColor();
  }
  defColor->addColor = getAddColor();
  defColor->mulColor = mm::Col3(getMulColor().r, getMulColor().g, getMulColor().b);
}

UIDisplayInfo::~UIDisplayInfo() {
  if (defColor != nullptr) {
    delete defColor;
    defColor = nullptr;
  }
}

void UIDisplayInfo::syncParent() {}

void UIDisplayInfo::setParent(const UIDisplayInfo *) {}

void UIDisplayInfo::setDisp(bool disp) {
  if (this->disp != disp) {
    dirty = true;
  }
  this->disp = disp;
}

void UIDisplayInfo::loadDefColor() {
  if (defColor != nullptr) {
    addColor = defColor->addColor;
    mm::Col4 color = {defColor->mulColor.r, defColor->mulColor.g, defColor->mulColor.b, getMulColor().a};
    mulColor = color;
  }
}

void UIDisplayInfo::linkColor(const UIDisplayInfo *link) { colorLink = link; }

void UIDisplayInfo::setPixelWidth(u16 width) {
  if (pixelWidth != width) {
    dirty = true;
  }
  pixelWidth = width;
}

void UIDisplayInfo::setPixelHeight(u16 height) {
  if (pixelHeight != height) {
    dirty = true;
  }
  pixelHeight = height;
}

void UIDisplayInfo::operator=(const UIDisplayInfo &other) {
  disp = other.disp;
  displayMode = other.displayMode;
  priority = other.priority;
  mulColor = other.mulColor;
  addColor = other.addColor;
  pixelWidth = other.pixelWidth;
  pixelHeight = other.pixelHeight;
  dirty = true;
  if (other.defColor != nullptr) {
    saveDefColor();
  }
}

} // namespace ui
