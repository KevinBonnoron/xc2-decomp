#include "gf/menu/gf_menu_hud.h"

#include "bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "ui/ui_manager.h"

namespace gf {

GfMenuHUD::GfMenuHUD(const GfSetupParam &param) : unknown08(false), unknown0c(0), unknown10(0) { initialize(param); }

void GfMenuHUD::initialize(const GfSetupParam &param) {
  unknown08 = true;
  unknown0c = 0;
  unknown10 = 0;
  unknown40.bind(this, &GfMenuHUD::systemStart);
  u8 *bdat = GfMenuBdat::getFP(2);
  if (bdat != nullptr) {
    for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
      u32 layer = Bdat::getIdTop(bdat) + i;
      switch (Bdat::getVal(bdat, "group", layer).valueU8) {
      case 0:
      case 1:
      case 2:
      case 4:
        ui::UIManager::get()->createLayer(layer);
        break;
      default:
        break;
      }
    }
  }
}

GfMenuHUD::~GfMenuHUD() {}

bool GfMenuHUD::isDisp() { return true; }

void GfMenuHUD::build(const GfSetupParam &param) {
// __LINE__ must be 63 as in the original file: it is the line argument of operator new.
#line 63
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMenuHUD(param);
}

void GfMenuHUD::destroy() {
  GfMenuHUD *hud = get();
  hud->finalize();
  delete hud;
}

void GfMenuHUD::finalize() {
  unknown0c = 0;
  unknown10 = 0;
}

bool GfMenuHUD::isInitialized() { return get()->unknown08; }

void GfMenuHUD::postUpdate(const fw::UpdateInfo &info) {
  GfMenuHUD *hud = get();
  if (hud == nullptr || !hud->unknown08) {
    return;
  }
  if (hud->unknown40.isValid()) {
    hud->unknown40();
  }
  if (hud->unknown60.isValid()) {
    hud->unknown60();
  }
}

void GfMenuHUD::reciveUIEvent(const ui::EventData &event, u32 handle) {}

void GfMenuHUD::changeScene(u32 scene) {
  GfMenuHUD *hud = get();
  if (hud->unknown08 && hud->unknown0c != scene) {
    hud->unknown10 = scene;
    hud->unknown60.bind(hud, &GfMenuHUD::sceneChangeStart);
  }
}

u32 GfMenuHUD::getSceneID() {
  u32 scene = 0;
  if (get()->unknown08) {
    scene = get()->unknown0c;
  }
  return scene;
}

void GfMenuHUD::systemStart() { unknown40.bind(this, &GfMenuHUD::systemWait); }

void GfMenuHUD::sceneWaitChange() {}

void GfMenuHUD::sceneUpdateField() {}

void GfMenuHUD::sceneUpdateBattle() {}

void GfMenuHUD::sceneUpdateEvent() {}

void GfMenuHUD::sceneUpdateFullscreen() {}

void GfMenuHUD::systemWait() { unknown40.bind(this, &GfMenuHUD::systemUpdate); }

void GfMenuHUD::systemUpdate() {}

} // namespace gf
