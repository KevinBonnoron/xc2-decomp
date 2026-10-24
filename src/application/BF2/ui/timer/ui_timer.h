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

  u64 unknown08; // Inferred role: elapsed; original member name unknown.
  u64 unknown10; // Inferred role: duration; original member name unknown.
  f32 unknown18; // Inferred role: speed factor; original member name unknown.
};

static_assert(offsetof(UITimer, unknown08) == 0x08, "");
static_assert(offsetof(UITimer, unknown10) == 0x10, "");
static_assert(offsetof(UITimer, unknown18) == 0x18, "");
static_assert(sizeof(UITimer) == 0x20, "");

} // namespace ui
