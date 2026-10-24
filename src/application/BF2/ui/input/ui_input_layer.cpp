#include "ui/input/ui_input_layer.h"

namespace ui {

UIInputLayer::~UIInputLayer() {}

void UIInputLayer::resetSelection() { unknown48 = -1; }

bool UIInputLayer::isEnableSelect(int index) {
  if (unknown1d8 != nullptr) {
    return unknown1d8->isEnableSelect(unknown40, index);
  }
  return true;
}

void UIInputLayer::setActionEnable(u16 actId, bool enable) {
  for (InputAction *it = unknown50.unknown00.begin(); it != unknown50.unknown00.end(); ++it) {
    if (it->unknown02 == actId) {
      it->unknown0d = enable;
      return;
    }
  }
}

bool UIInputLayer::getActionEnable(u16 actId) {
  for (InputAction *it = unknown50.unknown00.begin(); it != unknown50.unknown00.end(); ++it) {
    if (it->unknown02 == actId) {
      return it->unknown0d;
    }
  }
  return false;
}

bool UIInputLayer::hasEventExt() const { return false; }

void UIInputLayer::clear() {
  unknown10.unknown00 = 0;
  unknown28.unknown00 = 0;
  unknown10.unknown08 = 0;
  unknown10.unknown0c = 0;
  unknown10.unknown10 = 0;
  unknown10.unknown14 = 0;
  unknown28.unknown08 = 0;
  unknown28.unknown0c = 0;
  unknown28.unknown10 = 0;
  unknown28.unknown14 = 0;
  clearExt();
}

void UIInputLayer::clearExt() {}

UIInputPad *UIInputLayer::castUIInputPad() { return nullptr; }

UIInputWheel *UIInputLayer::castUIInputWheel() { return nullptr; }

UIInputPointer *UIInputLayer::castUIInputPointer() { return nullptr; }

} // namespace ui
