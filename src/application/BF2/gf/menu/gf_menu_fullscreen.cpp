#include "gf/menu/gf_menu_fullscreen.h"

#include "ui/ui_manager.h"

namespace gf {

static const u32 unknown002[8] = {0, 9, 2, 4, 7, 11, 3, 26}; // Inferred role: screen to ui layer id table; original name unknown.

void GfMenuFullScreen::initialize(const GfSetupParam &param) { unknown08 = true; }

void GfMenuFullScreen::finalize() { unknown08 = false; }

void GfMenuFullScreen::createLayer(u16 index, u16 layer) {
  if (index < 5 && layer != 0) {
    unknown001 &slot = unknown18[index];
    ui::UIManager::get()->createLayer(layer);
    slot.unknown00 = layer;
  }
}

void GfMenuFullScreen::releaseLayer(u16 index) {
  if (index < 5 && unknown18[index].unknown00 != 0) {
    ui::UIManager::get()->releaseLayer(unknown18[index].unknown00);
  }
}

bool GfMenuFullScreen::isInitialized() { return get()->unknown08; }

void GfMenuFullScreen::destroy() {
  GfMenuFullScreen *fullScreen = get();
  fullScreen->finalize();
  delete fullScreen;
}

bool GfMenuFullScreen::isDisp() {
  GfMenuFullScreen *fullScreen = get();
  if (fullScreen == nullptr) {
    return false;
  }
  for (u32 i = 0; i < LAYER_COUNT; i++) {
    if (fullScreen->unknown18[i].unknown00 != 0) {
      return true;
    }
  }
  return !fullScreen->unknown110.isValid();
}

bool GfMenuFullScreen::isSwitching() {
  GfMenuFullScreen *fullScreen = get();
  if (fullScreen == nullptr) {
    return false;
  }
  if (fullScreen->unknown08) {
    return fullScreen->unknownf9;
  }
  return false;
}

void GfMenuFullScreen::enableSwitching() { get()->unknown108 = true; }

void GfMenuFullScreen::disableSwitching() { get()->unknown108 = false; }

void GfMenuFullScreen::overrideFadeInFrame(u32 frame) { get()->unknownfc = frame; }

void GfMenuFullScreen::overrideFadeOutFrame(u32 frame) { get()->unknown100 = frame; }

void GfMenuFullScreen::overrideInputBorder(u32 border) { get()->unknown104 = border; }

u32 GfMenuFullScreen::getScreenID() {
  u32 screen = 0;
  if (get()->unknown08) {
    screen = get()->unknown0c;
  }
  return screen;
}

u32 GfMenuFullScreen::convScreenIDToLayerID(u32 screen) const {
  if (screen > 7) {
    return 0;
  }
  return unknown002[screen];
}

u32 GfMenuFullScreen::getScreenLayerID(u32 screen) {
  if (screen > 7) {
    return 0;
  }
  return unknown002[screen];
}

void GfMenuFullScreen::preloadScreenResource(u32 screen) {
  if (screen - 1 > 6) {
    return;
  }
  u32 layer = unknown002[screen];
  ui::UIManager::get()->preloadLayer(layer);
}

bool GfMenuFullScreen::setInputObject(u32 layer, u32 object) {
  if (get() != nullptr) {
    return get()->unknown160.setInputObject(layer, object);
  }
  return false;
}

u32 GfMenuFullScreen::getInputObject(u32 layer) {
  if (get() != nullptr) {
    return get()->unknown160.getInputObject(layer);
  }
  return 0;
}

void GfMenuFullScreen::enableInput(u32 layer) {
  if (get() != nullptr) {
    get()->unknown160.enable(layer);
  }
}

void GfMenuFullScreen::disableInput() {
  if (get() != nullptr) {
    get()->unknown160.disable();
  }
}

bool GfMenuFullScreen::isActiveInput(u32 layer) {
  if (get() != nullptr) {
    return get()->unknown160.isActive(layer);
  }
  return false;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuFullScreen>::~PtrSingleton();
