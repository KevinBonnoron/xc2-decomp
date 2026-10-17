#include "ui/ctrl/ui_ctrl.h"

#include "mm_mtl/reference_object.h"
#include "ui/ui_object.h"

namespace ui {

UICtrl::UICtrl() : object(nullptr), time(0.0f), prevTime(0.0f), duration(0.0f), loop(false), loopCount(0), speedFactor(1.0f) {}

UICtrl::~UICtrl() { mm::mtl::safeRelease(object); }

void UICtrl::stop() {
  mm::mtl::safeRelease(object);
  time = 0.0f;
  duration = 0.0f;
  loop = false;
  loopCount = 0;
  methods.clear();
  speedFactor = 1.0f;
  prevTime = 0.0f;
}

void UICtrl::start(UIObject *object, f32 duration, const MethodList &methods, bool loop) {
  mm::mtl::safeRelease(this->object);
  this->object = object;
  object->addRef();
  time = 0.0f;
  this->duration = duration;
  this->loop = loop;
  loopCount = 0;
  this->methods = methods;
  speedFactor = 1.0f;
  prevTime = 0.0f;
}

} // namespace ui
