#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "types.h"

namespace ui {

class UIMotionData;
class UIObject;

class UICtrlMethod {
public:
  struct TimeInfo {
    f32 prevTime;
    f32 time;
    f32 length;
  };

  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo) = 0;
};

class UICtrlMethodAlpha : public UICtrlMethod {
public:
  void setup(const UIObject *object, f32 to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  f32 unknown08; // Inferred role: from; original member name unknown.
  f32 unknown0c; // Inferred role: to; original member name unknown.
};

static_assert(offsetof(UICtrlMethodAlpha, unknown08) == 0x08, "");
static_assert(offsetof(UICtrlMethodAlpha, unknown0c) == 0x0c, "");

class UICtrlMethodBright : public UICtrlMethod {
public:
  void setup(const UIObject *object, f32 to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  f32 unknown08; // Inferred role: from; original member name unknown.
  f32 unknown0c; // Inferred role: to; original member name unknown.
};

static_assert(offsetof(UICtrlMethodBright, unknown08) == 0x08, "");
static_assert(offsetof(UICtrlMethodBright, unknown0c) == 0x0c, "");

class UICtrlMethodPos : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Pnt<s16> &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  mm::Pnt<s16> unknown08; // Inferred role: from; original member name unknown.
  mm::Pnt<s16> unknown0c; // Inferred role: to; original member name unknown.
};

static_assert(offsetof(UICtrlMethodPos, unknown08) == 0x08, "");
static_assert(offsetof(UICtrlMethodPos, unknown0c) == 0x0c, "");

class UICtrlMethodScale : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Vec2 &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  alignas(16) mm::Vec2 unknown10; // Inferred role: from; original member name unknown.
  alignas(16) mm::Vec2 unknown20; // Inferred role: to; original member name unknown.
};

static_assert(offsetof(UICtrlMethodScale, unknown10) == 0x10, "");
static_assert(offsetof(UICtrlMethodScale, unknown20) == 0x20, "");
static_assert(sizeof(UICtrlMethodScale) == 0x30, "");

class UICtrlMethodRot : public UICtrlMethod {
public:
  void setup(const UIObject *object, f32 to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  f32 unknown08; // Inferred role: from; original member name unknown.
  f32 unknown0c; // Inferred role: to; original member name unknown.
};

static_assert(offsetof(UICtrlMethodRot, unknown08) == 0x08, "");
static_assert(offsetof(UICtrlMethodRot, unknown0c) == 0x0c, "");

class UICtrlMethodMulColor : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Col3 &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  mm::Col3 unknown08; // Inferred role: from; original member name unknown.
  mm::Col3 unknown14; // Inferred role: to; original member name unknown.
};

static_assert(offsetof(UICtrlMethodMulColor, unknown08) == 0x08, "");
static_assert(offsetof(UICtrlMethodMulColor, unknown14) == 0x14, "");

class UICtrlMethodAddColor : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Col3 &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  mm::Col3 unknown08; // Inferred role: from; original member name unknown.
  mm::Col3 unknown14; // Inferred role: to; original member name unknown.
};

static_assert(offsetof(UICtrlMethodAddColor, unknown08) == 0x08, "");
static_assert(offsetof(UICtrlMethodAddColor, unknown14) == 0x14, "");

class UICtrlMethodMotion : public UICtrlMethod {
public:
  void setup(const UIObject *object, const UIMotionData *motionData, const char *name);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  const UIMotionData *unknown08;  // Inferred role: motion data; original member name unknown.
  u32 unknown10;                  // Inferred role: motion; original member name unknown.
  u32 unknown14;                  // Inferred role: frame; original member name unknown.
  alignas(16) mm::Vec2 unknown20; // Inferred role: pos; original member name unknown.
  alignas(16) mm::Vec2 unknown30; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(UICtrlMethodMotion, unknown08) == 0x08, "");
static_assert(offsetof(UICtrlMethodMotion, unknown10) == 0x10, "");
static_assert(offsetof(UICtrlMethodMotion, unknown14) == 0x14, "");
static_assert(offsetof(UICtrlMethodMotion, unknown20) == 0x20, "");
static_assert(offsetof(UICtrlMethodMotion, unknown30) == 0x30, "");
static_assert(sizeof(UICtrlMethodMotion) == 0x40, "");

} // namespace ui
