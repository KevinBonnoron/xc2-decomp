#include "gf/menu/gf_menu_status.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuStatus::GfMenuStatus(const GfSetupParam &param) { initialize(param); }

void GfMenuStatus::initialize(const GfSetupParam &param) { unknown08 = true; }

GfMenuStatus::~GfMenuStatus() {}

void GfMenuStatus::build(const GfSetupParam &param) {
// __LINE__ must be 39 as in the original file: its value changes the instruction order.
#line 39
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuStatus(param);
}

void GfMenuStatus::destroy() {
  GfMenuStatus *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuStatus::finalize() { unknown08 = false; }

bool GfMenuStatus::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuStatus::postUpdate(const fw::UpdateInfo &info) {}

} // namespace gf
