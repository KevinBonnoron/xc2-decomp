#include "gf/menu/gf_menu_hud.h"

namespace gf {

GfMenuHUD::~GfMenuHUD() {}

bool GfMenuHUD::isDisp() { return true; }

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
