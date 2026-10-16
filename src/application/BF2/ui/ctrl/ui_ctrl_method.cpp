#include "ui/ctrl/ui_ctrl_method.h"

#include "mm_math/mm_col4.h"
#include "ui/motion/ui_motion_data.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_object.h"
#include "ui/ui_transform.h"

namespace ui {

void UICtrlMethodAlpha::setup(const UIObject *object, f32 to) {
  from = object->displayInfo.getMulColor().a;
  this->to = to;
}

void UICtrlMethodAlpha::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) { object->displayInfo.mulColor.a = from + (to - from) * rate; }

void UICtrlMethodBright::setup(const UIObject *object, f32 to) {
  from = object->displayInfo.addColor.r;
  this->to = to;
}

void UICtrlMethodBright::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  f32 bright = from + (to - from) * rate;
  object->displayInfo.addColor.b = bright;
  object->displayInfo.addColor.g = bright;
  object->displayInfo.addColor.r = bright;
}

void UICtrlMethodPos::setup(const UIObject *object, const mm::Pnt<s16> &to) {
  mm::Pnt<s16> offset;
  object->getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  object->getPos(from);
  this->to = to;
  from.x -= offset.x;
  from.y -= offset.y;
  this->to.x -= offset.x;
  this->to.y -= offset.y;
}

void UICtrlMethodScale::setup(const UIObject *object, const mm::Vec2 &to) {
  from = object->transform.scale;
  this->to = to;
}

void UICtrlMethodScale::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  f32 deltaX = to.x - from.x;
  f32 deltaY = to.y - from.y;
  object->transform.setScale(from.x + deltaX * rate, from.y + deltaY * rate);
}

void UICtrlMethodRot::setup(const UIObject *object, f32 to) {
  from = object->transform.rot;
  this->to = to;
}

void UICtrlMethodRot::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) { object->transform.rot = from + (to - from) * rate; }

void UICtrlMethodMulColor::setup(const UIObject *object, const mm::Col3 &to) {
  from = reinterpret_cast<const mm::Col3 &>(object->displayInfo.getMulColor());
  this->to = to;
}

void UICtrlMethodMulColor::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  mm::Col4 color;
  color.r = from.r + (to.r - from.r) * rate;
  color.g = from.g + (to.g - from.g) * rate;
  color.b = from.b + (to.b - from.b) * rate;
  color.a = object->displayInfo.getMulColor().a;
  object->displayInfo.mulColor = color;
}

void UICtrlMethodAddColor::setup(const UIObject *object, const mm::Col3 &to) {
  from = object->displayInfo.getAddColor();
  this->to = to;
}

void UICtrlMethodAddColor::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  mm::Col3 color;
  color.r = from.r + (to.r - from.r) * rate;
  color.g = from.g + (to.g - from.g) * rate;
  color.b = from.b + (to.b - from.b) * rate;
  object->setAddColor(color);
}

void UICtrlMethodMotion::setup(const UIObject *object, const UIMotionData *motionData, const char *name) {
  this->motionData = motionData;
  motion = motionData->searchMotion(name);
  frame = 0;
  mm::Pnt<s16> current;
  mm::Pnt<s16> offset;
  object->getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  object->getPos(current);
  pos.x = current.x - offset.x;
  pos.y = current.y - offset.y;
  scale = object->transform.scale;
}

} // namespace ui
