#include "ui/ui_object_plugin.h"

#include "ui/ui_object_acc.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

UIObjectPlugin::UIObjectPlugin() : next(nullptr), needUpdate(true) {}

void UIObjectPlugin::execute(UIObjectAcc &) { needUpdate = false; }

bool UIObjectPlugin::isNeedUpdate(UIObjectAcc &acc) {
  if (!acc.isDisp()) {
    return false;
  }
  return needUpdate & 1;
}

const mm::mtl::RTTI *UIObjectPlugin::getRTTI() const { return &m_rtti; }

} // namespace ui
