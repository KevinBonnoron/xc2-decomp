#include "gf/menu/gf_menu_shop.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuShop::GfMenuShop(const GfSetupParam &param) { initialize(param); }

void GfMenuShop::initialize(const GfSetupParam &param) { unknown08 = true; }

GfMenuShop::~GfMenuShop() {}

void GfMenuShop::build(const GfSetupParam &param) {
// __LINE__ must be 39 as in the original file: its value changes the instruction order.
#line 39
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuShop(param);
}

void GfMenuShop::destroy() {
  GfMenuShop *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuShop::finalize() { unknown08 = false; }

bool GfMenuShop::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuShop::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuShop::setDisp(bool disp) {}

bool GfMenuShop::isDisp() { return false; }

} // namespace gf
