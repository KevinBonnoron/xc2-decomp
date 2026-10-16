#pragma once
#include "ui/ui_object_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectPosPlugin : public UIObjectPlugin {
public:
  static mm::mtl::RTTI m_rtti;
};

} // namespace ui
