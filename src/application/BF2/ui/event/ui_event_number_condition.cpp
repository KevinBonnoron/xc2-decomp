#include "ui/event/ui_event_number_condition.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/ui_util.h"

namespace ui {

UIEventNumberCondition::UIEventNumberCondition(u32 event, u32 value) : UIEventCondition(event, value), unknown20(nullptr), unknown28(0.0f), unknown2c(0), unknown30(true), unknown34(MODE_CHANGE) {}

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
  int min = plugin->unknown80;
  if (min <= threshold && threshold < plugin->unknown84) {
    f32 ratio = static_cast<f32>(threshold - min) / static_cast<f32>(plugin->unknown84 - min);
    condition->unknown20 = plugin;
    condition->unknown28 = ratio;
    condition->unknown2c = plugin->unknown7c;
    condition->unknown34 = MODE_THRESHOLD;
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
  condition->unknown20 = plugin;
  condition->unknown28 = threshold;
  condition->unknown2c = plugin->unknown7c;
  condition->unknown34 = MODE_THRESHOLD;
  return condition;
}

UIEventNumberCondition *UIEventNumberCondition::create(u32 event, u32 value, const UIObjectNumberPlugin *plugin) {
  if (plugin == nullptr) {
    return nullptr;
  }

#line 82
  UIEventNumberCondition *condition = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIEventNumberCondition(event, value);
  condition->addRef();
  condition->unknown20 = plugin;
  condition->unknown2c = plugin->unknown7c;
  condition->unknown34 = MODE_CHANGE;
  return condition;
}

int UIEventNumberCondition::update() {
  int number = unknown20->unknown7c;
  int min = unknown20->unknown80;
  int target = static_cast<int>(unknown28 * (unknown20->unknown84 - min)) + min;
  int prev = unknown2c;
  if (number == prev && !unknown30) {
    return 0;
  }

  int result;
  if (unknown34 != MODE_THRESHOLD) {
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
  unknown2c = number;
  unknown30 = false;
  return result;
}

u32 UIEventNumberCondition::getArg() const { return unknown20->unknown7c; }

} // namespace ui
