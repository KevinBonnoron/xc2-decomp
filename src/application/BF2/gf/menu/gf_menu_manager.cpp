#include "gf/menu/gf_menu_manager.h"

#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_minimap.h"
#include "gf/menu/object/gf_menu_obj_blade_create.h"
#include "gf/menu/object/gf_menu_obj_chapter_telop.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_dummy_tutorial.h"
#include "gf/menu/object/gf_menu_obj_main_root.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_save_load2.h"
#include "gf/menu/object/gf_menu_obj_tutorial.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_handle.h"
#include "ui/ui_manager.h"

namespace gf {

namespace {

constexpr u32 MENU_CHAPTER_TELOP = 68;
constexpr u32 MENU_ZONE_TELOP = 69;
constexpr u32 MENU_COMMON_TEXT = 100;
constexpr u32 MENU_DUMMY_TUTORIAL = 121;

constexpr u32 COMMON_TEXT_PRECIOUS = 11;
constexpr u8 CHAPTER_MAX = 10;

constexpr u32 LAYER_BTL_MODEL_VIEW = 10;
constexpr u32 LAYER_NAME_SELECT = 12;
constexpr u32 LAYER_OPENING_TELOP = 13;
constexpr u32 LAYER_STAFFROLL = 14;

constexpr u32 FULL_SCREEN_MAIN_ROOT = 2;
constexpr u32 MAIN_ROOT_BLADE_CREATE = 11;
constexpr u32 MAIN_ROOT_SAVE_LOAD = 53;
constexpr u32 MAINMENU2_MAP = 1;
constexpr u32 MAINMENU2_SYSTEM = 6;
constexpr u16 SAVE_LOAD_SAVE = 1;
constexpr u32 SE_ACCEPT_ACCESS = 27;

bool isOpenCallMenu(GfMenuManager *manager, u32 menu) {
  if (manager->callContext == nullptr) {
    return false;
  }
  if (manager->callContext->getState() == GfMenuCallContext::STATE_IDLE) {
    return false;
  }
  if (manager->callContext->isActive()) {
    return manager->callContext->menu == menu;
  }
  return false;
}

} // namespace

void GfMenuManager::build(const GfSetupParam &param) {
  // __LINE__ must be 347 as in the original file: it is an argument of the allocation.
#line 347
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuManager(param);
}

void GfMenuManager::destroy() {
  GfMenuManager *manager = get();
  manager->finalize();
  delete manager;
}

bool GfMenuManager::isRegionJP() {
  if (get() != nullptr) {
    return get()->region == REGION_JP;
  }
  return false;
}

bool GfMenuManager::isFading(u32 fade) {
  if (get() != nullptr && get()->initialized) {
    return GfMenuFade::isFading(fade);
  }
  return false;
}

f32 GfMenuManager::getUpdateDT() {
  GfMenuManager *manager = get();
  f32 updateDT = 0.0f;
  if (manager != nullptr && manager->initialized) {
    updateDT = manager->updateDT;
  }
  return updateDT;
}

GF_OBJ_HANDLE *GfMenuManager::getTargetObjHandle() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  if (manager->initialized) {
    return manager->targetObj;
  }
  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfMenuManager::getAccessObjHandle() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  if (manager->initialized) {
    return manager->accessObj;
  }
  return INVALID_HANDLE;
}

bool GfMenuManager::isTargetChanged() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  if (manager->initialized) {
    return manager->isTargetObjChanged;
  }
  return false;
}

bool GfMenuManager::isAccessChanged() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  if (manager->initialized) {
    return manager->isAccessObjChanged;
  }
  return false;
}

u32 GfMenuManager::getCurCameraType() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return 0;
  }
  if (manager->initialized) {
    return manager->cameraType;
  }
  return 0;
}

void GfMenuManager::openCommonWindow(u16 window) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized && manager->callContext != nullptr) {
    manager->callContext->reset();
    GfMenuObjCommonText::open(manager->callContext, window, 0);
    manager->latestCommonWindow = window;
  }
}

void GfMenuManager::openCommonWindow(const MenuCommonWindowParam &param) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized && manager->callContext != nullptr) {
    manager->callContext->reset();
    GfMenuObjCommonText::open(manager->callContext, param);
  }
}

void GfMenuManager::closeCommonWindow() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized && manager->callContext != nullptr) {
    GfMenuObjCommonText::close();
  }
}

bool GfMenuManager::isOpenCommonWindow() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized) {
    return isOpenCallMenu(manager, MENU_COMMON_TEXT);
  }
  return false;
}

int GfMenuManager::getCommonWindowResult() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return 0;
  }
  if (manager->initialized) {
    return manager->commonWindowResult;
  }
  return 0;
}

u32 GfMenuManager::getLatestCommonWinID() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return 0;
  }
  if (manager->initialized) {
    return manager->latestCommonWindow;
  }
  return 0;
}

void GfMenuManager::openPreciousWindow(u16 item) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized && manager->callContext != nullptr) {
    manager->callContext->reset();
    GfMenuObjCommonText::openItem(manager->callContext, COMMON_TEXT_PRECIOUS, item);
  }
}

bool GfMenuManager::isOpenPreciousWindow() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized) {
    return isOpenCallMenu(manager, MENU_COMMON_TEXT);
  }
  return false;
}

void GfMenuManager::openChapterTelop(u8 chapter) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized && chapter >= 1 && chapter <= CHAPTER_MAX && manager->callContext != nullptr) {
    manager->callContext->reset();
    GfMenuObjChapterTelop::openBeginTelop(manager->callContext, chapter);
  }
}

void GfMenuManager::openChapterEndTelop(u8 chapter) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized && chapter >= 1 && chapter <= CHAPTER_MAX && manager->callContext != nullptr) {
    manager->callContext->reset();
    GfMenuObjChapterTelop::openEndTelop(manager->callContext, chapter);
  }
}

bool GfMenuManager::isOpenChapterTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized) {
    return isOpenCallMenu(manager, MENU_CHAPTER_TELOP);
  }
  return false;
}

bool GfMenuManager::isOpenZoneTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized) {
    return isOpenCallMenu(manager, MENU_ZONE_TELOP);
  }
  return false;
}

void GfMenuManager::openDummyTutorial(u8 tutorial) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized && manager->callContext != nullptr) {
    manager->callContext->reset();
    GfMenuObjDummyTutorial::OpenParam param;
    param.tutorial = tutorial;
    GfMenuObjDummyTutorial::open(manager->callContext, param);
  }
}

bool GfMenuManager::isOpenDummyTutorial() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized) {
    return isOpenCallMenu(manager, MENU_DUMMY_TUTORIAL);
  }
  return false;
}

void GfMenuManager::setEnableQuestOpen(bool isEnable) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->initialized) {
    manager->isQuestOpenEnable = isEnable;
  }
}

bool GfMenuManager::isEnableQuestOpen() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  if (manager->initialized) {
    return manager->isQuestOpenEnable;
  }
  return false;
}

GfMenuManager::REGION GfMenuManager::getRegion() {
  if (get() != nullptr) {
    return get()->region;
  }
  return REGION_JP;
}

bool GfMenuManager::isRegionUS() {
  if (get() != nullptr) {
    return get()->region == REGION_US;
  }
  return false;
}

void GfMenuManager::openFullScreen(u32 screen, bool isFadeOut, bool isFadeIn) { GfMenuFullScreen::open(screen, isFadeOut, isFadeIn); }

void GfMenuManager::openMenu(u32 menu) {
  GfMenuObjMainRoot::OpenParam param;
  param.menu = menu;
  GfMenuObjMainRoot::registOpenParam(param);
  GfMenuFullScreen::open(FULL_SCREEN_MAIN_ROOT, true, true);
}

void GfMenuManager::openBladeCreateFromEvent(u32 event) {
  GfMenuObjMainRoot::OpenParam mainRootParam;
  GfMenuObjBladeCreate::OpenParam bladeCreateParam;
  bladeCreateParam.event = event;
  GfMenuObjBladeCreate::registOpenParam(bladeCreateParam);
  mainRootParam.menu = MAIN_ROOT_BLADE_CREATE;
  GfMenuObjMainRoot::registOpenParam(mainRootParam);
  GfMenuFullScreen::open(FULL_SCREEN_MAIN_ROOT, true, true);
}

void GfMenuManager::openBtlModelView() {
  if (get() != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_BTL_MODEL_VIEW);
  }
}

void GfMenuManager::closeBtlModelView() {
  if (get() != nullptr && get()->isBtlModelViewOpen) {
    ui::UIManager::get()->terminateLayer(LAYER_BTL_MODEL_VIEW, true);
  }
}

bool GfMenuManager::isOpenBtlModelView() {
  if (get() != nullptr) {
    return get()->isBtlModelViewOpen;
  }
  return false;
}

void GfMenuManager::openNameSelect() {
  GfMenuManager *manager = get();
  if (manager != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_NAME_SELECT);
    manager->isNameSelectOpen = true;
  }
}

bool GfMenuManager::isOpenNameSelect() {
  if (get() != nullptr) {
    return get()->isNameSelectOpen;
  }
  return false;
}

void GfMenuManager::openOpeningTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_OPENING_TELOP);
    manager->isOpeningTelopOpen = true;
  }
}

void GfMenuManager::closeOpeningTelop() {
  if (get() != nullptr) {
    ui::UIManager::get()->terminateLayer(LAYER_OPENING_TELOP, true);
  }
}

bool GfMenuManager::isOpenOpeningTelop() {
  if (get() != nullptr) {
    return get()->isOpeningTelopOpen;
  }
  return false;
}

void GfMenuManager::openStaffroll() {
  if (get() != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_STAFFROLL);
  }
}

void GfMenuManager::closeStaffroll() {
  if (get() != nullptr) {
    ui::UIManager::get()->terminateLayer(LAYER_STAFFROLL, true);
  }
}

void GfMenuManager::setMainmenuOpenMap() {
  GfMenuObjMainMenu2::OpenParam param;
  param.page = MAINMENU2_MAP;
  GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::setMainmenuOpenSystem() {
  GfMenuObjMainMenu2::OpenParam param;
  param.page = MAINMENU2_SYSTEM;
  GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::acceptAccess(GF_OBJ_HANDLE *) { GfMenuObjUtil::playSE(SE_ACCEPT_ACCESS); }

void GfMenuManager::closeFullScreen(bool isFadeOut, bool isFadeIn) { GfMenuFullScreen::close(isFadeOut, isFadeIn); }

void GfMenuManager::execMinimap(bool isExec) {
  if (!isExec) {
    GfMenuMinimap::setDisp(false);
    return;
  }
  if (GfGameManager::getState() == GF_STATE_CONTROL && !GfGameManager::isEvent(false)) {
    GfMenuMinimap::setDisp(true);
  }
}

bool GfMenuManager::isFieldHudInputEnable() { return !GfMenuObjTutorial::isWaiting(); }

void GfMenuManager::openSave() {
  GfMenuObjMainRoot::OpenParam mainRootParam;
  GfMenuObjSaveLoad2::OpenParam saveLoadParam;
  saveLoadParam.mode = SAVE_LOAD_SAVE;
  GfMenuObjSaveLoad2::registOpenParam(saveLoadParam);
  mainRootParam.menu = MAIN_ROOT_SAVE_LOAD;
  GfMenuObjMainRoot::registOpenParam(mainRootParam);
  GfMenuFullScreen::open(FULL_SCREEN_MAIN_ROOT, true, true);
}

} // namespace gf
