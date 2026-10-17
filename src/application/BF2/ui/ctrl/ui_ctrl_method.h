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

  f32 from;
  f32 to;
};

static_assert(offsetof(UICtrlMethodAlpha, from) == 0x08, "");
static_assert(offsetof(UICtrlMethodAlpha, to) == 0x0c, "");

class UICtrlMethodBright : public UICtrlMethod {
public:
  void setup(const UIObject *object, f32 to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  f32 from;
  f32 to;
};

static_assert(offsetof(UICtrlMethodBright, from) == 0x08, "");
static_assert(offsetof(UICtrlMethodBright, to) == 0x0c, "");

class UICtrlMethodPos : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Pnt<s16> &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  mm::Pnt<s16> from;
  mm::Pnt<s16> to;
};

static_assert(offsetof(UICtrlMethodPos, from) == 0x08, "");
static_assert(offsetof(UICtrlMethodPos, to) == 0x0c, "");

class UICtrlMethodScale : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Vec2 &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  alignas(16) mm::Vec2 from;
  alignas(16) mm::Vec2 to;
};

static_assert(offsetof(UICtrlMethodScale, from) == 0x10, "");
static_assert(offsetof(UICtrlMethodScale, to) == 0x20, "");
static_assert(sizeof(UICtrlMethodScale) == 0x30, "");

class UICtrlMethodRot : public UICtrlMethod {
public:
  void setup(const UIObject *object, f32 to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  f32 from;
  f32 to;
};

static_assert(offsetof(UICtrlMethodRot, from) == 0x08, "");
static_assert(offsetof(UICtrlMethodRot, to) == 0x0c, "");

class UICtrlMethodMulColor : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Col3 &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  mm::Col3 from;
  mm::Col3 to;
};

static_assert(offsetof(UICtrlMethodMulColor, from) == 0x08, "");
static_assert(offsetof(UICtrlMethodMulColor, to) == 0x14, "");

class UICtrlMethodAddColor : public UICtrlMethod {
public:
  void setup(const UIObject *object, const mm::Col3 &to);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  mm::Col3 from;
  mm::Col3 to;
};

static_assert(offsetof(UICtrlMethodAddColor, from) == 0x08, "");
static_assert(offsetof(UICtrlMethodAddColor, to) == 0x14, "");

class UICtrlMethodMotion : public UICtrlMethod {
public:
  void setup(const UIObject *object, const UIMotionData *motionData, const char *name);
  virtual void execute(UIObject *object, f32 rate, const TimeInfo &timeInfo);

  const UIMotionData *motionData;
  u32 motion;
  u32 frame;
  alignas(16) mm::Vec2 pos;
  alignas(16) mm::Vec2 scale;
};

static_assert(offsetof(UICtrlMethodMotion, motionData) == 0x08, "");
static_assert(offsetof(UICtrlMethodMotion, motion) == 0x10, "");
static_assert(offsetof(UICtrlMethodMotion, frame) == 0x14, "");
static_assert(offsetof(UICtrlMethodMotion, pos) == 0x20, "");
static_assert(offsetof(UICtrlMethodMotion, scale) == 0x30, "");
static_assert(sizeof(UICtrlMethodMotion) == 0x40, "");

} // namespace ui
