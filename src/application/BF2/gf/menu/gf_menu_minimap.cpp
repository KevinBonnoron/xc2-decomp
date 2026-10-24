#include "gf/menu/gf_menu_minimap.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuMinimap::GfMenuMinimap(const GfSetupParam &param) { initialize(param); }

void GfMenuMinimap::initialize(const GfSetupParam &param) { unknown08 = true; }

GfMenuMinimap::~GfMenuMinimap() {}

void GfMenuMinimap::build(const GfSetupParam &param) {
// __LINE__ must be 39 as in the original file: its value changes the instruction order.
#line 39
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuMinimap(param);
}

void GfMenuMinimap::destroy() {
  GfMenuMinimap *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuMinimap::finalize() { unknown08 = false; }

bool GfMenuMinimap::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuMinimap::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuMinimap::setDisp(bool disp) {}

bool GfMenuMinimap::isDisp() { return false; }

} // namespace gf
