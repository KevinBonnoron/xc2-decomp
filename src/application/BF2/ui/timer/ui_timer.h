#pragma once
#include <stddef.h>

#include "types.h"

namespace ui {

class UITimer {
public:
  UITimer();
  virtual ~UITimer();
  void update(f32 sec);
  void start(u64 duration);
  void restart();
  void stop();
  bool isActive() const;
  bool isOver() const;

  u64 elapsed;
  u64 duration;
  f32 speedFactor;
};

static_assert(offsetof(UITimer, elapsed) == 0x08, "");
static_assert(offsetof(UITimer, duration) == 0x10, "");
static_assert(offsetof(UITimer, speedFactor) == 0x18, "");
static_assert(sizeof(UITimer) == 0x20, "");

} // namespace ui
