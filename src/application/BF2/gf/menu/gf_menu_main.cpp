#include "gf/menu/gf_menu_main.h"

#include "gf/gf_allocator.h"
#include "types.h"
#include "ui/ui_manager.h"

namespace gf {

constexpr u32 MAIN_LAYER = 3;

GfMenuMain::GfMenuMain(const GfSetupParam &param) { initialize(param); }

void GfMenuMain::initialize(const GfSetupParam &param) { unknown08 = true; }

GfMenuMain::~GfMenuMain() {}

void GfMenuMain::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuMain(param); }

void GfMenuMain::destroy() {
  GfMenuMain *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuMain::finalize() { unknown08 = false; }

bool GfMenuMain::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuMain::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuMain::setDisp(bool disp) {
  if (disp) {
    ui::UIManager::get()->createLayer(MAIN_LAYER);
  } else {
    ui::UIManager::get()->releaseLayer(MAIN_LAYER);
  }
}

bool GfMenuMain::isDisp() { return false; }

} // namespace gf
