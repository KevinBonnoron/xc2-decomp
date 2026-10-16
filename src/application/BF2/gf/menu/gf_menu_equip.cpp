#include "gf/menu/gf_menu_equip.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuEquip::GfMenuEquip(const GfSetupParam &param) { initialize(param); }

void GfMenuEquip::initialize(const GfSetupParam &param) { initialized = true; }

GfMenuEquip::~GfMenuEquip() {}

void GfMenuEquip::build(const GfSetupParam &param) {
// __LINE__ must be 39 as in the original file: its value changes the instruction order.
#line 39
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuEquip(param);
}

void GfMenuEquip::destroy() {
  GfMenuEquip *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuEquip::finalize() { initialized = false; }

bool GfMenuEquip::isInitialized() {
  if (get() != nullptr) {
    return get()->initialized;
  }
  return false;
}

void GfMenuEquip::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuEquip::setDisp(bool disp) {}

bool GfMenuEquip::isDisp() { return false; }

} // namespace gf
