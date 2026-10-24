#include "gf/menu/gf_menu_kizunaring.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuKizunaring::GfMenuKizunaring(const GfSetupParam &param) { initialize(param); }

void GfMenuKizunaring::initialize(const GfSetupParam &param) { unknown08 = true; }

GfMenuKizunaring::~GfMenuKizunaring() {}

void GfMenuKizunaring::build(const GfSetupParam &param) {
// __LINE__ must be 41 as in the original file: its value changes the instruction order.
#line 41
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuKizunaring(param);
}

void GfMenuKizunaring::destroy() {
  GfMenuKizunaring *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuKizunaring::finalize() { unknown08 = false; }

bool GfMenuKizunaring::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuKizunaring::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuKizunaring::openMenu(u32 id) {}

void GfMenuKizunaring::closeMenu() {}

bool GfMenuKizunaring::isOpenMenu() { return false; }

} // namespace gf
