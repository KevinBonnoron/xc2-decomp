#include "gf/menu/gf_menu_minimap.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuMinimap::GfMenuMinimap(const GfSetupParam &param) { initialize(param); }

void GfMenuMinimap::initialize(const GfSetupParam &param) { initialized = true; }

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

void GfMenuMinimap::finalize() { initialized = false; }

bool GfMenuMinimap::isInitialized() {
  if (get() != nullptr) {
    return get()->initialized;
  }
  return false;
}

void GfMenuMinimap::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuMinimap::setDisp(bool disp) {}

bool GfMenuMinimap::isDisp() { return false; }

} // namespace gf
