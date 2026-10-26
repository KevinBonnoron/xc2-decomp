#include "ui/ctrl/ui_ctrl_method.h"

#include "mm_math/mm_col4.h"
#include "ui/motion/ui_motion_data.h"
#include "ui/ui_displayinfo.h"
#include "ui/ui_object.h"
#include "ui/ui_transform.h"

namespace ui {

void UICtrlMethodAlpha::setup(const UIObject *object, f32 to) {
  unknown08 = object->unknown50.getMulColor().a;
  this->unknown0c = to;
}

void UICtrlMethodAlpha::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) { object->unknown50.unknown10.a = unknown08 + (unknown0c - unknown08) * rate; }

void UICtrlMethodBright::setup(const UIObject *object, f32 to) {
  unknown08 = object->unknown50.unknown20.r;
  this->unknown0c = to;
}

void UICtrlMethodBright::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  f32 bright = unknown08 + (unknown0c - unknown08) * rate;
  object->unknown50.unknown20.b = bright;
  object->unknown50.unknown20.g = bright;
  object->unknown50.unknown20.r = bright;
}

void UICtrlMethodPos::setup(const UIObject *object, const mm::Pnt<s16> &to) {
  mm::Pnt<s16> pos;
  mm::Pnt<s16> offset;
  object->getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  object->getPos(unknown08);
  this->unknown0c = to;
  unknown08.x -= offset.x;
  unknown08.y -= offset.y;
  this->unknown0c.x -= offset.x;
  this->unknown0c.y -= offset.y;
}

void UICtrlMethodScale::setup(const UIObject *object, const mm::Vec2 &to) {
  unknown10 = object->unknown20.unknown10;
  this->unknown20 = to;
}

void UICtrlMethodScale::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  f32 deltaX = unknown20.x - unknown10.x;
  f32 deltaY = unknown20.y - unknown10.y;
  object->unknown20.setScale(unknown10.x + deltaX * rate, unknown10.y + deltaY * rate);
}

void UICtrlMethodRot::setup(const UIObject *object, f32 to) {
  unknown08 = object->unknown20.unknown20;
  this->unknown0c = to;
}

void UICtrlMethodRot::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) { object->unknown20.unknown20 = unknown08 + (unknown0c - unknown08) * rate; }

void UICtrlMethodMulColor::setup(const UIObject *object, const mm::Col3 &to) {
  unknown08 = reinterpret_cast<const mm::Col3 &>(object->unknown50.getMulColor());
  this->unknown14 = to;
}

void UICtrlMethodMulColor::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  mm::Col4 color;
  color.r = unknown08.r + (unknown14.r - unknown08.r) * rate;
  color.g = unknown08.g + (unknown14.g - unknown08.g) * rate;
  color.b = unknown08.b + (unknown14.b - unknown08.b) * rate;
  color.a = object->unknown50.getMulColor().a;
  object->unknown50.unknown10 = color;
}

void UICtrlMethodAddColor::setup(const UIObject *object, const mm::Col3 &to) {
  unknown08 = object->unknown50.getAddColor();
  this->unknown14 = to;
}

void UICtrlMethodAddColor::execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) {
  mm::Col3 color;
  color.r = unknown08.r + (unknown14.r - unknown08.r) * rate;
  color.g = unknown08.g + (unknown14.g - unknown08.g) * rate;
  color.b = unknown08.b + (unknown14.b - unknown08.b) * rate;
  object->setAddColor(color);
}

void UICtrlMethodMotion::setup(const UIObject *object, const UIMotionData *motionData, const char *name) {
  this->unknown08 = motionData;
  unknown10 = motionData->searchMotion(name);
  unknown14 = 0;
  mm::Pnt<s16> current;
  mm::Pnt<s16> pos;
  mm::Pnt<s16> offset;
  object->getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  object->getPos(current);
  unknown20.x = current.x - offset.x;
  unknown20.y = current.y - offset.y;
  unknown30 = object->unknown20.unknown10;
}

void UICtrlMethodMotion::execute(UIObject *object, f32, const TimeInfo &timeInfo) {
  if (unknown10 == 0xffffffff) {
    return;
  }

  UIMotionData::MotionParam param;
  if (timeInfo.prevTime == 0.0f) {
    unknown08->getMotionParamDefault(unknown10, param);
    if (param.has(UIMotionData::PARAM_TYPE_ALPHA)) {
      object->unknown50.unknown10.a = param.unknown18;
    }
    f32 scaleX = 1.0f;
    f32 scaleY = 1.0f;
    if (param.unknown00 & (1 << UIMotionData::PARAM_TYPE_SCALE_X)) {
      scaleX = param.unknown0c;
    }
    if (param.unknown00 & (1 << UIMotionData::PARAM_TYPE_SCALE_Y)) {
      scaleY = param.unknown10;
    }
    object->unknown20.setScale(unknown30.x * scaleX, scaleY * unknown30.y);
  }

  f32 frameRate = unknown08->getMotionLength(unknown10) / timeInfo.length;
  unknown08->getMotionParamDelta(unknown10, frameRate * timeInfo.prevTime, frameRate * timeInfo.time, param);

  f32 x = object->unknown20.unknown10.x;
  f32 y = object->unknown20.unknown10.y;
  x += unknown30.x * param.unknown0c;
  y += unknown30.y * param.unknown10;
  object->unknown20.setScale(x, y);
  object->unknown20.unknown20 = object->unknown20.unknown20 + param.unknown14;

  mm::Pnt<s16> pos;
  mm::Pnt<s16> offset;
  object->getDisplayOffset(UI_DISPLAY_MODE_TOP_LEFT, offset);
  unknown20.x += param.unknown04;
  unknown20.y += param.unknown08;
  pos.x = static_cast<s16>(unknown20.x) + offset.x;
  pos.y = static_cast<s16>(unknown20.y) + offset.y;
  object->setPos(pos);

  f32 alpha = object->unknown50.getColorSource()->unknown10.a + param.unknown18;
  if (alpha > 1.0f) {
    alpha = 1.0f;
  }
  if (alpha < 0.0f) {
    alpha = 0.0f;
  }
  object->unknown50.unknown10.a = alpha;
}

} // namespace ui
