#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/event/ui_event_condition.h"

namespace ui {

class UIObjectNumberPlugin;

class UIEventNumberCondition : public UIEventCondition {
public:
  enum Mode {
    MODE_THRESHOLD = 0,
    MODE_CHANGE = 1,
  };

  UIEventNumberCondition(u32 event, u32 value);
  virtual ~UIEventNumberCondition();
  static UIEventNumberCondition *create(u32 event, u32 value, const UIObjectNumberPlugin *plugin, int threshold);
  static UIEventNumberCondition *create(u32 event, u32 value, const UIObjectNumberPlugin *plugin, f32 threshold);
  static UIEventNumberCondition *create(u32 event, u32 value, const UIObjectNumberPlugin *plugin);
  virtual int update();
  virtual u32 getArg() const;

  const UIObjectNumberPlugin *unknown20; // Inferred role: plugin; original member name unknown.
  f32 unknown28;                         // Inferred role: threshold; original member name unknown.
  int unknown2c;                         // Inferred role: prev number; original member name unknown.
  bool unknown30;                        // Inferred role: first; original member name unknown.
  u32 unknown34;                         // Inferred role: mode; original member name unknown.
};

static_assert(offsetof(UIEventNumberCondition, unknown20) == 0x20, "");
static_assert(offsetof(UIEventNumberCondition, unknown28) == 0x28, "");
static_assert(offsetof(UIEventNumberCondition, unknown2c) == 0x2c, "");
static_assert(offsetof(UIEventNumberCondition, unknown30) == 0x30, "");
static_assert(offsetof(UIEventNumberCondition, unknown34) == 0x34, "");
static_assert(sizeof(UIEventNumberCondition) == 0x38, "");

} // namespace ui
