#include "ui/plugin/ui_object_offset_plugin.h"

namespace ui {

UIObjectOffsetPlugin::UIObjectOffsetPlugin() {
  targetPos.x = 0;
  targetPos.y = 0;
  maxOffset.x = 0xffff;
  maxOffset.y = 0xffff;
}

UIObjectOffsetPlugin::~UIObjectOffsetPlugin() { ; }

const mm::mtl::RTTI *UIObjectOffsetPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectOffsetPlugin::isNeedUpdate(UIObjectAcc &acc) { return true; }

} // namespace ui
