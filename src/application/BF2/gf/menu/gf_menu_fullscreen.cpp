#include "gf/menu/gf_menu_fullscreen.h"

#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "mm_math/mm_col4.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/event/ui_event_data.h"
#include "ui/input/ui_input_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_util.h"

namespace gf {

static const u32 unknown002[8] = {0, 9, 2, 4, 7, 11, 3, 26}; // Inferred role: screen to ui layer id table; original name unknown.

GfMenuFullScreen::GfMenuFullScreen(const GfSetupParam &param)
    : unknown08(false), unknown0c(0), unknown10(0), unknownf8(true), unknownf9(false), unknownfc(0), unknown100(0), unknown104(0), unknown108(true), unknown109(true), unknown10a(true), unknown130(0),
      unknown134(0), unknown158(), unknown160(8) {
  initialize(param);
}

GfMenuFullScreen::~GfMenuFullScreen() {}

void GfMenuFullScreen::initialize(const GfSetupParam &param) { unknown08 = true; }

void GfMenuFullScreen::build(const GfSetupParam &param) {
// __LINE__ must be 89 as in the original file: it is the line argument of operator new.
#line 89
  GfMenuFullScreen *fullScreen = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuFullScreen(param);
  for (u16 i = 0; i < LAYER_COUNT; i++) {
    fullScreen->resetLayer(i);
  }
}

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

void GfMenuFullScreen::resetLayer(u16 index) {
  unknown18[index].unknown00 = 0;
  unknown18[index].unknown08.clear();
  unknown18[index].unknown30 = 0;
  unknown18[index].unknown34 = false;
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
  if (layer == 0 || fullScreen == nullptr) {
    return false;
  }
  for (unknown003 *entry = fullScreen->unknown188.begin(); entry != fullScreen->unknown188.end(); entry++) {
    if (entry->unknown00 == layer) {
      param = entry->unknown08;
      return true;
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

u32 GfMenuFullScreen::getLayerGroup(u32 layer) {
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

void GfMenuFullScreen::close(bool isFadeOut, bool isFadeIn) {
  if (isDisp()) {
    GfMenuFullScreen *fullScreen = get();
    fullScreen->unknown10 = 0;
    fullScreen->unknown110.bind(fullScreen, &GfMenuFullScreen::switchLayerStart);
    GfMenuObjCommonText::close();
    fullScreen->unknown109 = isFadeOut;
    fullScreen->unknown10a = isFadeIn;
  }
}

void GfMenuFullScreen::switchLayerStart() {
  startProcess();
  for (u32 i = 0; i < LAYER_COUNT; i++) {
    if (unknown18[i].unknown00 != 0) {
      ui::UIManager::get()->terminateLayer(unknown18[i].unknown00, false);
    }
  }
  if (unknown109) {
    if (unknown100 == 0) {
      GfMenuFade::setFade(2, 15, mm::Col4::black);
    } else {
      GfMenuFade::setFade(2, unknown100, mm::Col4::black);
      unknown100 = 0;
    }
  }
  unknown109 = true;
  unknown110.bind(this, &GfMenuFullScreen::switchLayerWaitFadeOut);
}

void GfMenuFullScreen::switchLayerWaitFadeOut() {
  if (GfMenuManager::isFading()) {
    return;
  }
  ml::ScnRenderDrSysParmAcc renderParam;
  if (unknown10 == 0) {
    renderParam.setViewRenderSkip(0, false);
  } else if (GfManager::isExecModeScenarioGame()) {
    renderParam.setViewRenderSkip(0, true);
  }
  for (u16 i = 0; i < LAYER_COUNT; i++) {
    releaseLayer(i);
  }
  unknown110.bind(this, &GfMenuFullScreen::switchLayerWaitRelease);
  unknown160.clearInputObject();
}

void GfMenuFullScreen::switchLayerWaitRelease() {
  for (u32 i = 0; i < LAYER_COUNT; i++) {
    if (unknown18[i].unknown00 != 0) {
      return;
    }
  }
  unknown110.bind(this, &GfMenuFullScreen::switchLayerOpenScreen);
}

void GfMenuFullScreen::switchLayerOpenScreen() {
  if (unknown10 == 0) {
    GfMenuObjOperationInfo::close();
    GfMenuObjCommonText::close();
    for (u16 i = 0; i < LAYER_COUNT; i++) {
      resetLayer(i);
    }
    unknown188.clear();
  } else {
    createLayer(0, unknown130);
  }
  unknown134 = 2;
  unknown110.bind(this, &GfMenuFullScreen::switchLayerWaitScreen);
}

void GfMenuFullScreen::switchLayerWaitScreen() {
  if (ui::UIManager::get()->isLoading()) {
    return;
  }
  unknown134--;
  if (unknown134 != 0) {
    return;
  }
  if (unknown10a) {
    if (unknownfc == 0) {
      GfMenuFade::setFade(2, 15, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    } else {
      GfMenuFade::setFade(2, unknownfc, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    }
  }
  unknown10a = true;
  if (unknown10 == 0) {
    unknown0c = 0;
    unknown10 = 0;
    unknown130 = 0;
    unknown110.clear();
    exitProcess(true);
  } else {
    unknown110.bind(this, &GfMenuFullScreen::switchLayerWaitFadeIn);
  }
}

void GfMenuFullScreen::switchLayerWaitFadeIn() {
  if (GfMenuManager::isFading()) {
    return;
  }
  unknown0c = unknown10;
  unknown10 = 0;
  unknown130 = 0;
  unknown110.clear();
  exitProcess(false);
}

void GfMenuFullScreen::subLayerWaitRelease() {
  for (u16 i = unknown158.unknown04; i < LAYER_COUNT; i++) {
    if (unknown18[i].unknown00 != 0) {
      return;
    }
  }
  unknown138.bind(this, &GfMenuFullScreen::subLayerCreate);
}

void GfMenuFullScreen::subLayerCreate() {
  if (unknown158.unknown00 == 0) {
    resetLayer(unknown158.unknown04);
  } else {
    createLayer(unknown158.unknown04, unknown158.unknown00);
  }
  unknown138.bind(this, &GfMenuFullScreen::subLayerWaitOpen);
}

void GfMenuFullScreen::subLayerWaitOpen() {
  if (ui::UIManager::get()->isLoading()) {
    return;
  }
  if (unknown158.unknown00 == 0) {
    size_t index = unknown158.unknown04;
    if (index != 0 && unknown18[index - 1].unknown30 != 0) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x43;
      event.unknown08 = index;
      ui::UIManager::get()->requestObjectEvent(unknown18[index - 1].unknown30, event, 0.0f);
    }
  }
  unknown138.clear();
  unknown158.unknown00 = 0;
  unknown158.unknown04 = 0;
  exitProcess(false);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuFullScreen>::~PtrSingleton();
template void mm::mtl::Delegate<void()>::memberFuncInvoker<gf::GfMenuFullScreen>(const mm::mtl::Delegate<void()> *);
