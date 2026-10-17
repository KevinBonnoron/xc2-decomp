#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {

class UICtrlCurve;
class UICtrlMethod;
class UIObject;

class UICtrl {
public:
  struct Method {
    UICtrlMethod *method;
    const UICtrlCurve *curve;
  };

  typedef mm::mtl::FixedVector<Method, 5> MethodList;

  UICtrl();
  virtual ~UICtrl();
  void update(f32 deltaTime);
  void stop();
  void start(UIObject *object, f32 duration, const MethodList &methods, bool loop);

  bool isBusy() const { return object != nullptr; }

  UIObject *object;
  f32 time;
  f32 prevTime;
  f32 duration;
  bool loop;
  u32 loopCount;
  MethodList methods;
  f32 speedFactor;
};

static_assert(offsetof(UICtrl, object) == 0x08, "");
static_assert(offsetof(UICtrl, time) == 0x10, "");
static_assert(offsetof(UICtrl, prevTime) == 0x14, "");
static_assert(offsetof(UICtrl, duration) == 0x18, "");
static_assert(offsetof(UICtrl, loop) == 0x1c, "");
static_assert(offsetof(UICtrl, loopCount) == 0x20, "");
static_assert(offsetof(UICtrl, methods) == 0x28, "");
static_assert(offsetof(UICtrl, speedFactor) == 0x80, "");
static_assert(sizeof(UICtrl) == 0x88, "");

} // namespace ui
