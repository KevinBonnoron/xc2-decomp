#pragma once
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "types.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

class GfMenuEnhanceAdapter : public GfMenuAdapter {
public:
  static bool getEnhanceCaption(u32 enhance, ui::UIStr &caption);
};

} // namespace gf
