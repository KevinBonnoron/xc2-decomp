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

  const UIObjectNumberPlugin *plugin;
  f32 threshold;
  int prevNumber;
  bool first;
  u32 mode;
};

static_assert(offsetof(UIEventNumberCondition, plugin) == 0x20, "");
static_assert(offsetof(UIEventNumberCondition, threshold) == 0x28, "");
static_assert(offsetof(UIEventNumberCondition, prevNumber) == 0x2c, "");
static_assert(offsetof(UIEventNumberCondition, first) == 0x30, "");
static_assert(offsetof(UIEventNumberCondition, mode) == 0x34, "");
static_assert(sizeof(UIEventNumberCondition) == 0x38, "");

} // namespace ui
