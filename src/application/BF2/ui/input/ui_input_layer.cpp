#include "ui/input/ui_input_layer.h"

namespace ui {

UIInputLayer::~UIInputLayer() {}

void UIInputLayer::resetSelection() { selectIndex = -1; }

bool UIInputLayer::isEnableSelect(int index) {
  if (selectionChecker != nullptr) {
    return selectionChecker->isEnableSelect(handle, index);
  }
  return true;
}

void UIInputLayer::setActionEnable(u16 actId, bool enable) {
  for (InputAction *it = setup.actions.begin(); it != setup.actions.end(); ++it) {
    if (it->actId == actId) {
      it->enable = enable;
      return;
    }
  }
}

bool UIInputLayer::getActionEnable(u16 actId) {
  for (InputAction *it = setup.actions.begin(); it != setup.actions.end(); ++it) {
    if (it->actId == actId) {
      return it->enable;
    }
  }
  return false;
}

bool UIInputLayer::hasEventExt() const { return false; }

void UIInputLayer::clear() {
  event.type = 0;
  actionEvent.type = 0;
  event.param0 = 0;
  event.param1 = 0;
  event.param2 = 0;
  event.param3 = 0;
  actionEvent.param0 = 0;
  actionEvent.param1 = 0;
  actionEvent.param2 = 0;
  actionEvent.param3 = 0;
  clearExt();
}

void UIInputLayer::clearExt() {}

UIInputPad *UIInputLayer::castUIInputPad() { return nullptr; }

UIInputWheel *UIInputLayer::castUIInputWheel() { return nullptr; }

UIInputPointer *UIInputLayer::castUIInputPointer() { return nullptr; }

} // namespace ui
