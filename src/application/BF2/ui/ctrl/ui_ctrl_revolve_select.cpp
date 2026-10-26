#include "ui/ctrl/ui_ctrl_revolve_select.h"

#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"

namespace ui {

UICtrlRevolveSelect::UICtrlRevolveSelect(u32 object)
    : UICtrlObject(object), unknown2c(), unknown5c(0), unknown60(nullptr), unknown68(0), unknown6c(0.0f), unknown70(0.0f), unknown78(), unknowna0(0, 0), unknowna8(), unknownd8(0) {}

UICtrlRevolveSelect::~UICtrlRevolveSelect() { mm::mtl::safeRelease(unknown60); }

void UICtrlRevolveSelect::resetAngelRange(u16 range) { unknown2c.unknown00 = range; }

void UICtrlRevolveSelect::getCenterPos(mm::Pnt<s16> &pos) const {
  pos.x = unknown2c.unknown08.x + unknowna0.x;
  pos.y = unknown2c.unknown08.y + unknowna0.y;
}

bool UICtrlRevolveSelect::isRolling() const { return unknown78.isBusy(); }

bool UICtrlRevolveSelect::isMoving() const { return unknowna8.isBusy(); }

} // namespace ui
