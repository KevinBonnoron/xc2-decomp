#include "ui/ui_displayinfo.h"

#include "framework/memory/framework_memory.h"
#include "ui/ui_util.h"

namespace ui {

UIDisplayInfo::UIDisplayInfo() {
  unknown08 = true;
  unknown09 = 0;
  unknown0a = 0;
  unknown0c = 0;
  unknown10.r = 1.0f;
  unknown10.g = 1.0f;
  unknown10.b = 1.0f;
  unknown10.a = 1.0f;
  unknown20.r = 0.0f;
  unknown20.g = 0.0f;
  unknown20.b = 0.0f;
  unknown2c = 0;
  unknown2e = 0;
  unknown30 = false;
  unknown38 = nullptr;
  unknown40 = nullptr;
}

UIDisplayInfo::UIDisplayInfo(const UIDisplayInfo &other) {
  unknown08 = other.unknown08;
  unknown09 = other.unknown09;
  unknown0a = other.unknown0a;
  unknown0c = other.unknown0c;
  unknown10 = other.unknown10;
  unknown20 = other.unknown20;
  unknown2c = other.unknown2c;
  unknown2e = other.unknown2e;
  unknown30 = false;
  unknown38 = nullptr;
  unknown40 = nullptr;
  if (other.unknown38 != nullptr) {
    saveDefColor();
  }
}

void UIDisplayInfo::saveDefColor() {
  if (unknown38 == nullptr) {
// __LINE__ is the line argument of the operator new call.
#line 130
    unknown38 = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) DefColor();
  }
  unknown38->addColor = getAddColor();
  unknown38->mulColor = mm::Col3(getMulColor().r, getMulColor().g, getMulColor().b);
}

UIDisplayInfo::~UIDisplayInfo() {
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
}

void UIDisplayInfo::syncParent() {}

void UIDisplayInfo::setParent(const UIDisplayInfo *) {}

void UIDisplayInfo::setDisp(bool disp) {
  if (this->unknown08 != disp) {
    unknown30 = true;
  }
  this->unknown08 = disp;
}

void UIDisplayInfo::loadDefColor() {
  if (unknown38 != nullptr) {
    unknown20 = unknown38->addColor;
    mm::Col4 color = {unknown38->mulColor.r, unknown38->mulColor.g, unknown38->mulColor.b, getMulColor().a};
    unknown10 = color;
  }
}

void UIDisplayInfo::linkColor(const UIDisplayInfo *link) { unknown40 = link; }

void UIDisplayInfo::setPixelWidth(u16 width) {
  if (unknown2c != width) {
    unknown30 = true;
  }
  unknown2c = width;
}

void UIDisplayInfo::setPixelHeight(u16 height) {
  if (unknown2e != height) {
    unknown30 = true;
  }
  unknown2e = height;
}

void UIDisplayInfo::operator=(const UIDisplayInfo &other) {
  unknown08 = other.unknown08;
  unknown09 = other.unknown09;
  unknown0c = other.unknown0c;
  unknown10 = other.unknown10;
  unknown20 = other.unknown20;
  unknown2c = other.unknown2c;
  unknown2e = other.unknown2e;
  unknown30 = true;
  if (other.unknown38 != nullptr) {
    saveDefColor();
  }
}

} // namespace ui
