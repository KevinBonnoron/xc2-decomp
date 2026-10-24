#include "ui/event/ui_event_disp_condition.h"

#include "framework/memory/framework_memory.h"
#include "ui/plugin/ui_object_disp_plugin.h"
#include "ui/ui_util.h"

namespace ui {

UIEventDispCondition::UIEventDispCondition(u32 event, u32 value) : UIEventCondition(event, value), unknown20(nullptr), unknown28(false) {}

UIEventDispCondition::~UIEventDispCondition() { ; }

UIEventDispCondition *UIEventDispCondition::create(u32 event, u32 value, const UIObjectDispPlugin *plugin) {
  if (plugin == nullptr) {
    return nullptr;
  }

// __LINE__ is the line argument of the operator new call.
#line 43
  UIEventDispCondition *condition = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIEventDispCondition(event, value);
  condition->addRef();
  condition->unknown20 = plugin;
  condition->unknown28 = !plugin->unknown1d;
  return condition;
}

int UIEventDispCondition::update() {
  bool disp = unknown20->unknown1d;
  int result = disp == this->unknown28 ? 0 : (disp ? 5 : 6);
  this->unknown28 = disp;
  return result;
}

} // namespace ui
