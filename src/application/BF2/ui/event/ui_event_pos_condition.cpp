#include "ui/event/ui_event_pos_condition.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_pos_plugin.h"
#include "ui/ui_util.h"

namespace ui {

UIEventPosCondition::UIEventPosCondition(u32 event, u32 value) : UIEventCondition(event, value), unknown20(nullptr), unknown28(false) {}

UIEventPosCondition::~UIEventPosCondition() { ; }

UIEventPosCondition *UIEventPosCondition::create(u32 event, u32 value, const UIObjectPosPlugin *plugin) {
  if (plugin == nullptr) {
    return nullptr;
  }

// __LINE__ is the line argument of the operator new call.
#line 43
  UIEventPosCondition *condition = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIEventPosCondition(event, value);
  condition->addRef();
  condition->unknown20 = plugin;
  condition->unknown28 = !plugin->unknown90;
  return condition;
}

int UIEventPosCondition::update() {
  bool adjusting = unknown20->unknown90;
  int result = adjusting == this->unknown28 ? 0 : (adjusting ? 7 : 8);
  this->unknown28 = adjusting;
  return result;
}

} // namespace ui
