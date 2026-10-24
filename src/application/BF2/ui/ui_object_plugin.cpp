#include "ui/ui_object_plugin.h"

#include "ui/ui_object_acc.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

UIObjectPlugin::UIObjectPlugin() : unknown10(nullptr), unknown18(true) {}

void UIObjectPlugin::execute(UIObjectAcc &) { unknown18 = false; }

bool UIObjectPlugin::isNeedUpdate(UIObjectAcc &acc) {
  if (!acc.isDisp()) {
    return false;
  }
  return unknown18 & 1;
}

const mm::mtl::RTTI *UIObjectPlugin::getRTTI() const { return &m_rtti; }

} // namespace ui
