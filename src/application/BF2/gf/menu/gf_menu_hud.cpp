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
  sceneID = 0;
  nextSceneID = 0;
}

bool GfMenuHUD::isInitialized() { return get()->initialized; }

void GfMenuHUD::postUpdate(const fw::UpdateInfo &info) {
  GfMenuHUD *hud = get();
  if (hud == nullptr || !hud->initialized) {
    return;
  }
  if (hud->systemUpdater.isValid()) {
    hud->systemUpdater();
  }
  if (hud->sceneUpdater.isValid()) {
    hud->sceneUpdater();
  }
}

void GfMenuHUD::reciveUIEvent(const ui::EventData &event, u32 handle) {}

void GfMenuHUD::changeScene(u32 scene) {
  GfMenuHUD *hud = get();
  if (hud->initialized && hud->sceneID != scene) {
    hud->nextSceneID = scene;
    hud->sceneUpdater.bind(hud, &GfMenuHUD::sceneChangeStart);
  }
}

u32 GfMenuHUD::getSceneID() {
  u32 scene = 0;
  if (get()->initialized) {
    scene = get()->sceneID;
  }
  return scene;
}

void GfMenuHUD::systemStart() { systemUpdater.bind(this, &GfMenuHUD::systemWait); }

void GfMenuHUD::sceneWaitChange() {}

void GfMenuHUD::sceneUpdateField() {}

void GfMenuHUD::sceneUpdateBattle() {}

void GfMenuHUD::sceneUpdateEvent() {}

void GfMenuHUD::sceneUpdateFullscreen() {}

void GfMenuHUD::systemWait() { systemUpdater.bind(this, &GfMenuHUD::systemUpdate); }

void GfMenuHUD::systemUpdate() {}

} // namespace gf
