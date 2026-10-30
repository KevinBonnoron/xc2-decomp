#include "gf/menu/gf_menu_fullscreen.h"

#include "ui/input/ui_input_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_util.h"

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

void GfMenuFullScreen::postUpdate(const fw::UpdateInfo &) {
  GfMenuFullScreen *fullScreen = get();
  if (fullScreen != nullptr && fullScreen->unknown08) {
    if (fullScreen->unknown110.isValid()) {
      fullScreen->unknown110();
    }
    if (fullScreen->unknown138.isValid()) {
      fullScreen->unknown138();
    }
  }
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

void GfMenuFullScreen::registLayerParam(u32 layer, const GfMenuTypes::Param &param) {
  GfMenuFullScreen *fullScreen = get();
  if (fullScreen != nullptr) {
    for (unknown003 *entry = fullScreen->unknown188.begin(); entry != fullScreen->unknown188.end(); entry++) {
      if (entry->unknown00 == layer) {
        entry->unknown08 = param;
        return;
      }
    }
    if (fullScreen->unknown188.size() != fullScreen->unknown188.capacity()) {
      unknown003 entry;
      entry.unknown00 = layer;
      entry.unknown08 = param;
      fullScreen->unknown188.push_back(entry);
    }
  }
}

bool GfMenuFullScreen::getLayerParam(u32 layer, GfMenuTypes::Param &param) {
  GfMenuFullScreen *fullScreen = get();
  if (layer != 0 && fullScreen != nullptr) {
    for (unknown003 *entry = fullScreen->unknown188.begin(); entry != fullScreen->unknown188.end(); entry++) {
      if (entry->unknown00 == layer) {
        param = entry->unknown08;
        return true;
      }
    }
  }
  return false;
}

void GfMenuFullScreen::registLayerObject(u32 layer, u32 object) {
  u16 group = getLayerGroup(layer);
  if (group < LAYER_COUNT) {
    get()->unknown18[group].unknown30 = object;
  }
}

void GfMenuFullScreen::setShadowLayer(u32 layer, bool shadow) {
  u16 group = getLayerGroup(layer);
  if (group < LAYER_COUNT) {
    get()->unknown18[group].unknown34 = shadow;
  }
}

u16 GfMenuFullScreen::getLayerGroup(u32 layer) {
  GfMenuFullScreen *fullScreen = get();
  if (layer != 0 && fullScreen != nullptr) {
    for (u16 i = 0; i < LAYER_COUNT; i++) {
      if (fullScreen->unknown18[i].unknown00 == layer) {
        return i;
      }
    }
  }
  return 0xff;
}

void GfMenuFullScreen::startProcess() {
  ui::UIInputManager *inputManager = ui::UIInputManager::get();
  if (inputManager != nullptr) {
    inputManager->unknown20 = ui::UIUtil::getGroupPriority(4);
  }
}

void GfMenuFullScreen::exitProcess(bool isReset) {
  ui::UIInputManager *inputManager = ui::UIInputManager::get();
  if (inputManager != nullptr) {
    if (isReset) {
      inputManager->unknown20 = 0;
    } else if (unknown104 == 0) {
      inputManager->unknown20 = ui::UIUtil::getGroupPriority(3);
    } else {
      inputManager->unknown20 = unknown104;
      unknown104 = 0;
    }
  }
  if (!unknown110.isValid() && !unknown138.isValid()) {
    unknownf9 = false;
  }
  unknownf8 = true;
}

void GfMenuFullScreen::terminateLayer(u16 index, bool isImmediate, bool isKeep) {
  if (index < 5 && unknown18[index].unknown00 != 0) {
    if (isKeep && unknown18[index].unknown08.size() != unknown18[index].unknown08.capacity()) {
      unknown18[index].unknown08.push_back(unknown18[index].unknown00);
    }
    ui::UIManager::get()->terminateLayer(unknown18[index].unknown00, isImmediate);
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuFullScreen>::~PtrSingleton();
