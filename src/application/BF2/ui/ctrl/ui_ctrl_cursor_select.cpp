#include "ui/ctrl/ui_ctrl_cursor_select.h"

#include "mm_math/mm_col3.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace ui {

void UICtrlCursorSelect::CursorSetting::setType(int type) {
  switch (type) {
  case 0:
    unknown00 = 0.0f;
    break;
  case 1:
    unknown00 = 0.15f;
    unknown04 = CURVE_TYPE_LINEAR;
    break;
  case 2:
    unknown00 = 0.15f;
    unknown04 = CURVE_TYPE_SIN90;
    break;
  }
}

UICtrlCursorSelect::UICtrlCursorSelect(u32 object) : UICtrlObject(object), unknown30(), unknown58(nullptr), unknown60(0), unknown68(), unknown98(0), unknown9c(0, 0), unknowna0(true) {}

UICtrlCursorSelect::~UICtrlCursorSelect() { mm::mtl::safeRelease(unknown58); }

void UICtrlCursorSelect::setIndex(u32 index) {
  if (unknown58 != nullptr) {
    unknown58->setIndex(index);
  }
}

bool UICtrlCursorSelect::inputChange(u32 index) {
  if (unknown58 == nullptr) {
    return false;
  }
  UIObjectAcc acc(unknown98);
  if (acc.isValid()) {
    if (index != 0xffffffff && unknown58->getSize() != 0) {
      if (unknown58 != nullptr) {
        unknown58->setIndex(index);
      }
      if (unknowna0) {
        acc.setDisp(true);
      }
      return true;
    }
    acc.setDisp(false);
  }
  return false;
}

void UICtrlCursorSelect::setDisp(bool disp) {
  UIObjectAcc acc(unknown98);
  if (acc.isValid()) {
    acc.setDisp(disp);
    unknowna0 = disp;
  }
}

void UICtrlCursorSelect::setAddColor(const char *name) {
  UIObjectAcc acc(unknown98);
  if (acc.isValid()) {
    if (name == nullptr) {
      mm::Col3 black(0.0f, 0.0f, 0.0f);
      acc.setAddColor(black);
    } else {
      acc.setAddColor(name);
    }
  }
}

void UICtrlCursorSelect::setMulColor(const char *name) {
  UIObjectAcc acc(unknown98);
  if (acc.isValid()) {
    if (name == nullptr) {
      acc.setMulColor("white");
    } else {
      acc.setMulColor(name);
    }
  }
}

void UICtrlCursorSelect::setAlpha(f32 alpha) {
  UIObjectAcc acc(unknown98);
  if (acc.isValid()) {
    acc.setAlpha(alpha);
  }
}

} // namespace ui
