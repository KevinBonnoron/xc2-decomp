#include "ui/event/ui_event_pos_condition.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_pos_plugin.h"
#include "ui/ui_util.h"

namespace ui {

UIEventPosCondition::UIEventPosCondition(u32 event, u32 value) : UIEventCondition(event, value), plugin(nullptr), adjusting(false) {}

UIEventPosCondition::~UIEventPosCondition() { ; }

UIEventPosCondition *UIEventPosCondition::create(u32 event, u32 value, const UIObjectPosPlugin *plugin) {
  if (plugin == nullptr) {
    return nullptr;
  }

// __LINE__ is the line argument of the operator new call.
#line 43
  UIEventPosCondition *condition = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIEventPosCondition(event, value);
  condition->addRef();
  condition->plugin = plugin;
  condition->adjusting = !plugin->adjusting;
  return condition;
}

int UIEventPosCondition::update() {
  bool adjusting = plugin->adjusting;
  int result = adjusting == this->adjusting ? 0 : (adjusting ? 7 : 8);
  this->adjusting = adjusting;
  return result;
}

} // namespace ui
