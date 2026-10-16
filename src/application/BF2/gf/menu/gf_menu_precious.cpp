#include "gf/menu/gf_menu_precious.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuPrecious::GfMenuPrecious(const GfSetupParam &param) { initialize(param); }

void GfMenuPrecious::initialize(const GfSetupParam &param) { initialized = true; }

GfMenuPrecious::~GfMenuPrecious() {}

void GfMenuPrecious::build(const GfSetupParam &param) {
// __LINE__ must be 39 as in the original file: its value changes the instruction order.
#line 39
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuPrecious(param);
}

void GfMenuPrecious::destroy() {
  GfMenuPrecious *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuPrecious::finalize() { initialized = false; }

bool GfMenuPrecious::isInitialized() {
  if (get() != nullptr) {
    return get()->initialized;
  }
  return false;
}

void GfMenuPrecious::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuPrecious::setDisp(bool disp, u32 type) {}

bool GfMenuPrecious::isDisp() { return false; }

} // namespace gf
