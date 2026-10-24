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
    UICtrlMethod *unknown00;      // Inferred role: method; original member name unknown.
    const UICtrlCurve *unknown08; // Inferred role: curve; original member name unknown.
  };

  typedef mm::mtl::FixedVector<Method, 5> MethodList;

  UICtrl();
  virtual ~UICtrl();
  void update(f32 deltaTime);
  void stop();
  void start(UIObject *object, f32 duration, const MethodList &methods, bool loop);

  bool isFinished() const { return unknown18 <= unknown10; }
  bool isBusy() const { return unknown1c || !isFinished(); }

  UIObject *unknown08;  // Inferred role: object; original member name unknown.
  f32 unknown10;        // Inferred role: time; original member name unknown.
  f32 unknown14;        // Inferred role: prev time; original member name unknown.
  f32 unknown18;        // Inferred role: duration; original member name unknown.
  bool unknown1c;       // Inferred role: loop; original member name unknown.
  u32 unknown20;        // Inferred role: loop count; original member name unknown.
  MethodList unknown28; // Inferred role: methods; original member name unknown.
  f32 unknown80;        // Inferred role: speed factor; original member name unknown.
};

static_assert(offsetof(UICtrl, unknown08) == 0x08, "");
static_assert(offsetof(UICtrl, unknown10) == 0x10, "");
static_assert(offsetof(UICtrl, unknown14) == 0x14, "");
static_assert(offsetof(UICtrl, unknown18) == 0x18, "");
static_assert(offsetof(UICtrl, unknown1c) == 0x1c, "");
static_assert(offsetof(UICtrl, unknown20) == 0x20, "");
static_assert(offsetof(UICtrl, unknown28) == 0x28, "");
static_assert(offsetof(UICtrl, unknown80) == 0x80, "");
static_assert(sizeof(UICtrl) == 0x88, "");

} // namespace ui
