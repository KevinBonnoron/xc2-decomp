#include "ui/event/ui_event_number_condition.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/ui_util.h"

namespace ui {

UIEventNumberCondition::UIEventNumberCondition(u32 event, u32 value)
    : UIEventCondition(event, value), plugin(nullptr), threshold(0.0f), prevNumber(0), first(true), mode(MODE_CHANGE) {}

UIEventNumberCondition::~UIEventNumberCondition() { ; }

UIEventNumberCondition *UIEventNumberCondition::create(u32 event, u32 value, const UIObjectNumberPlugin *plugin, int threshold) {
  if (plugin == nullptr) {
    return nullptr;
  }

// __LINE__ is the line argument of the operator new calls.
#line 46
  UIEventNumberCondition *condition = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIEventNumberCondition(event, value);
  condition->addRef();
  UIEventNumberCondition *result = nullptr;
  int min = plugin->min;
  if (min <= threshold && threshold < plugin->max) {
    f32 ratio = static_cast<f32>(threshold - min) / static_cast<f32>(plugin->max - min);
    condition->plugin = plugin;
    condition->threshold = ratio;
    condition->prevNumber = plugin->number;
    condition->mode = MODE_THRESHOLD;
    result = condition;
  }
  return result;
}

UIEventNumberCondition *UIEventNumberCondition::create(u32 event, u32 value, const UIObjectNumberPlugin *plugin, f32 threshold) {
  if (plugin == nullptr) {
    return nullptr;
  }

#line 67
  UIEventNumberCondition *condition = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIEventNumberCondition(event, value);
  condition->addRef();
  condition->plugin = plugin;
  condition->threshold = threshold;
  condition->prevNumber = plugin->number;
  condition->mode = MODE_THRESHOLD;
  return condition;
}

UIEventNumberCondition *UIEventNumberCondition::create(u32 event, u32 value, const UIObjectNumberPlugin *plugin) {
  if (plugin == nullptr) {
    return nullptr;
  }

#line 82
  UIEventNumberCondition *condition = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIEventNumberCondition(event, value);
  condition->addRef();
  condition->plugin = plugin;
  condition->prevNumber = plugin->number;
  condition->mode = MODE_CHANGE;
  return condition;
}

int UIEventNumberCondition::update() {
  int number = plugin->number;
  int min = plugin->min;
  int target = static_cast<int>(threshold * (plugin->max - min)) + min;
  int prev = prevNumber;
  if (number == prev && !first) {
    return 0;
  }

  int result;
  if (mode != MODE_THRESHOLD) {
    result = 4;
  } else {
    if (target == number) {
      result = 1;
    } else if (number < target && prev >= target) {
      result = 2;
    } else {
      result = number > target && prev <= target ? 3 : 0;
    }
  }
  prevNumber = number;
  first = false;
  return result;
}

u32 UIEventNumberCondition::getArg() const { return plugin->number; }

} // namespace ui
