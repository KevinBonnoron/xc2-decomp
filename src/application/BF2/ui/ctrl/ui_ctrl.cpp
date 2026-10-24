#include "ui/ctrl/ui_ctrl.h"

#include "mm_mtl/reference_object.h"
#include "ui/ui_object.h"

namespace ui {

UICtrl::UICtrl() : unknown08(nullptr), unknown10(0.0f), unknown14(0.0f), unknown18(0.0f), unknown1c(false), unknown20(0), unknown80(1.0f) {}

UICtrl::~UICtrl() { mm::mtl::safeRelease(unknown08); }

void UICtrl::stop() {
  mm::mtl::safeRelease(unknown08);
  unknown10 = 0.0f;
  unknown18 = 0.0f;
  unknown1c = false;
  unknown20 = 0;
  unknown28.clear();
  unknown80 = 1.0f;
  unknown14 = 0.0f;
}

void UICtrl::start(UIObject *object, f32 duration, const MethodList &methods, bool loop) {
  mm::mtl::safeRelease(this->unknown08);
  this->unknown08 = object;
  object->addRef();
  unknown10 = 0.0f;
  this->unknown18 = duration;
  this->unknown1c = loop;
  unknown20 = 0;
  this->unknown28 = methods;
  unknown80 = 1.0f;
  unknown14 = 0.0f;
}

} // namespace ui
