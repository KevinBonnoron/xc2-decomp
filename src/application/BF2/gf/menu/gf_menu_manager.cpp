#include "gf/menu/gf_menu_manager.h"

#include "bdat.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/salvage/gf_game_salvage.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_hud.h"
#include "gf/menu/gf_menu_location.h"
#include "gf/menu/gf_menu_map_info.h"
#include "gf/menu/gf_menu_minimap.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_action_window.h"
#include "gf/menu/object/gf_menu_obj_blade_create.h"
#include "gf/menu/object/gf_menu_obj_chain_attack.h"
#include "gf/menu/object/gf_menu_obj_chapter_telop.h"
#include "gf/menu/object/gf_menu_obj_combo_route.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_damage_buff.h"
#include "gf/menu/object/gf_menu_obj_damage_value.h"
#include "gf/menu/object/gf_menu_obj_drop_item.h"
#include "gf/menu/object/gf_menu_obj_dummy_tutorial.h"
#include "gf/menu/object/gf_menu_obj_enemy_status.h"
#include "gf/menu/object/gf_menu_obj_environment_info.h"
#include "gf/menu/object/gf_menu_obj_exp_get.h"
#include "gf/menu/object/gf_menu_obj_main_root.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_option.h"
#include "gf/menu/object/gf_menu_obj_party_gauge.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/menu/object/gf_menu_obj_party_status2.h"
#include "gf/menu/object/gf_menu_obj_quest_log.h"
#include "gf/menu/object/gf_menu_obj_save_load2.h"
#include "gf/menu/object/gf_menu_obj_tutorial.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "layer/layer_acc_manager.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/input/ui_input_manager.h"
#include "ui/ui_manager.h"

namespace gf {

bool GfMenuManager::isOpenFullScreen() { return GfMenuFullScreen::isOpen(); }

bool GfMenuManager::isSwitchingFullScreen() { return GfMenuFullScreen::isSwitching(); }

void GfMenuManager::changeHUDScene(u32 scene) { GfMenuHUD::changeScene(scene); }

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
  if (manager->unknown40d0 == nullptr) {
    return false;
  }
  if (manager->unknown40d0->getState() == GfMenuCallContext::STATE_IDLE) {
    return false;
  }
  if (manager->unknown40d0->isActive()) {
    return manager->unknown40d0->unknown10 == menu;
  }
  return false;
}

// Inferred role: refresh the quest locators of the map; original name unknown.
void unknown001() {
  GfMenuLocation::refreshLocator(0);
  GfMenuLocation::refreshLocator(1);
  GfMenuLocation::refreshLocator(3);
}

// Inferred role: close the battle popups (damage, buff, drop, exp); original name unknown.
void unknown002() {
  GfMenuObjDamageValue::closeAll();
  GfMenuObjDamageBuff::closeAll();
  GfMenuObjDropItem::closeAll();
  GfMenuObjExpGet::closeAll();
}

} // namespace

void GfMenuManager::qevOrderQuest(const QuestOrderParam &) { unknown001(); }

void GfMenuManager::qevCompleteQuest(const QuestCompleteParam &) {}

void GfMenuManager::qevChangeTaskState(const QuestTaskParam &param) {
  const QuestID &quest = param.unknown04;
  if (quest.unknown00 == 0 && quest.unknown02 == 0) {
    return;
  }

  GfMenuLocation::refreshLocator(0);
  GfMenuLocation::refreshLocator(1);
  if (param.unknown18 == TASK_STATE_UNKNOWN_1) {
    GfMenuObjQuestLog::completeTask(param);
    return;
  }

  if (GfGameScene::get() != nullptr && quest == GfGameScene::get()->getQuestIdForTaskLog()) {
    GfMenuObjQuestLog::updateTask();
  }
}

void GfMenuManager::qevLoadTaskState(u32 count) {
  if (count != 0) {
    unknown001();
  }
}

void GfMenuManager::qevCompleteChildQuest(const QuestCompleteChildParam &param) {
  const QuestID &quest = param.unknown04;
  if (quest.unknown00 == 0 && quest.unknown02 == 0) {
    return;
  }

  unknown001();
}

void GfMenuManager::qevChangeQuestState(const QuestStateParam &) {
  GfMenuLocation::refreshLocator(0);
  GfMenuLocation::refreshLocator(1);
}

void GfMenuManager::qevChangeCurrentQuest(const QuestChangeParam &) { unknown001(); }

void GfMenuManager::beginUpdate(const fw::UpdateInfo &info) { GfMenuAdapterManager::postUpdateAfter(info); }

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
    return get()->unknown4104 == REGION_JP;
  }
  return false;
}

bool GfMenuManager::isFading(u32 fade) {
  if (get() != nullptr && get()->unknown4090) {
    return GfMenuFade::isFading(fade);
  }
  return false;
}

void GfMenuManager::getFadeColor(u32 fade, mm::Col4 &color) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && !manager->unknown4091) {
    GfMenuFade::getFadeColor(fade, color);
  }
}

void GfMenuManager::initOptionData(SDataOption &option) { GfMenuObjOption::initOptionData(option); }

void GfMenuManager::applyGammaCorrectValue(f32 value) {
  f32 gamma = value + value + 1.2f;
  layer::LayerAccManager layerAcc;
  layerAcc.setGamma(gamma);
  ml::ScnRenderDrSysParmAcc renderParam;
  renderParam.setGamma(gamma);
}

void GfMenuManager::applyOptionData(const SDataOption &option) { applyGammaCorrectValue(static_cast<f32>(option._66) / VOLUME_SCALE); }

f32 GfMenuManager::getUpdateDT() {
  GfMenuManager *manager = get();
  f32 updateDT = 0.0f;
  if (manager != nullptr && manager->unknown4090) {
    updateDT = manager->unknown40f8;
  }
  return updateDT;
}

GF_OBJ_HANDLE *GfMenuManager::getTargetObjHandle() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  if (manager->unknown4090) {
    return manager->unknown40b8;
  }
  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfMenuManager::getAccessObjHandle() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return INVALID_HANDLE;
  }
  if (manager->unknown4090) {
    return manager->unknown40c0;
  }
  return INVALID_HANDLE;
}

bool GfMenuManager::isTargetChanged() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  if (manager->unknown4090) {
    return manager->unknown40c8;
  }
  return false;
}

bool GfMenuManager::isAccessChanged() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  if (manager->unknown4090) {
    return manager->unknown40c9;
  }
  return false;
}

u32 GfMenuManager::getCurCameraType() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return 0;
  }
  if (manager->unknown4090) {
    return manager->unknown40cc;
  }
  return 0;
}

void GfMenuManager::gevMapjump(GEV, const MapjumpCallbackInfo &) {
  GfMenuObjComboRoute::close();
  GfMenuObjPartyGauge::close();
}

void GfMenuManager::gevAccessTarget(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (!acc.isValid()) {
    GfMenuObjActionWindow::close();
    if (unknown40c0 != INVALID_HANDLE) {
      unknown40c9 = true;
    }
    unknown40c0 = INVALID_HANDLE;
  } else {
    GfMenuObjActionWindow::OpenParam param;
    param.unknown00 = handle;
    param.unknown08 = 4;
    GfMenuObjActionWindow::open(param);
    if (unknown40c0 != handle) {
      unknown40c9 = true;
    }
    unknown40c0 = handle;
  }
}

void GfMenuManager::gevChangeTarget(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (!acc.isValid() || acc.getType() != OBJECT_TYPE_ENEMY) {
    GfMenuReference::setPartyStatusLock(0, false);
    GfMenuObjPartyStatus::close(false);
    GfMenuObjEnemyStatus::close();
  } else {
    GfMenuObjEnemyStatus::OpenParam param;
    param.unknown00 = handle;
    GfMenuObjEnemyStatus::open(param);
    GfMenuReference::setPartyStatusLock(0, true);
    GfMenuObjPartyStatus::open(true);
  }

  if (unknown40b8 != handle) {
    unknown40c8 = true;
  }
  unknown40b8 = handle;
}

void GfMenuManager::gevCameraControl(u32 type) { unknown40cc = type; }

void GfMenuManager::gevBattleStart() {
  GfMenuObjEnemyStatus::disp(true);
  GfMenuObjComboRoute::disp(true);
  GfMenuObjPartyGauge::disp(true);
  setBattleState(0, true);
}

void GfMenuManager::gevBattleEnd() {
  unknown40dc.clear();
  GfMenuReference::setChainNum(0);
  GfMenuObjComboRoute::close();
  GfMenuObjPartyGauge::close();
}

void GfMenuManager::gevPlayEvent(GEV event, u32) {
  if (GfMenuFullScreen::isOpen()) {
    return;
  }

  switch (event) {
  case GEV_EVENT_SEQUENCE_START:
    unknown40dc.clear();
    unknown40ca = false;
    GfMenuObjPartyGauge::close();
    GfMenuObjPartyStatus::close(true);
    GfMenuObjComboRoute::close();
    GfMenuObjChainAttack::closeResult();
    break;
  case GEV_EVENT_SEQUENCE_END:
    if (ui::UIInputManager::get() != nullptr) {
      ui::UIInputManager::get()->enable();
    }
    break;
  case GEV_EVENT_START_FRAME:
    unknown002();
    GfMenuObjPartyGauge::close();
    GfMenuObjChainAttack::closeResult();
    // fallthrough
  case GEV_EVENT_END:
    GfMenuObjComboRoute::close();
    GfMenuObjPartyStatus::close(true);
    break;
  default:
    break;
  }
}

void GfMenuManager::gevSalvageStateChange(u32 state) {
  switch (state) {
  case GfGameSalvage::STATE_ITEM_SELECT:
    unknown40e4.set(1, false);
    unknown40e4.set(2, false);
    break;
  case GfGameSalvage::STATE_SETUP_FADE_OUT:
    GfMenuObjEnvironmentInfo::close();
    break;
  case GfGameSalvage::STATE_SETUP_FADE_IN:
    unknown002();
    break;
  case GfGameSalvage::STATE_FINISH:
    unknown40e4.set(1);
    unknown40e4.set(2);
    break;
  default:
    break;
  }
}

void GfMenuManager::gevPlayerControl(GEV event) {
  if (event == GEV_PLAYER_CONTROL_LOCK) {
    GfMenuReference::clearPartyStatusLock();
    unknown40e4.set(1, false);
    unknown40e4.set(2, false);
    unknown40e4.set(3, false);
    unknown40ca = false;
  } else if (event == GEV_PLAYER_CONTROL_FREE) {
    GfMenuMapInfo::setCurrentMap(GfGameManager::getMapID());
    unknown40e4.set(1);
    if (!unknown40dc.test(0)) {
      unknown40e4.set(3);
    }

    if (!unknown40dc.test(0) && !unknown40dc.test(1)) {
      unknown40e4.set(2);
    }

    unknown40ca = true;
    GfMenuObjPartyStatus2::disp(true);
    if (ui::UIInputManager::get() != nullptr) {
      ui::UIInputManager::get()->enable();
    }
  }
}

void GfMenuManager::gevItemAdd(u32 item, int count) {
  if (count <= 0) {
    return;
  }

  ItemType::Type type = GfDataItem::getItemType(item);
  if (type >= ItemType::PC_WPN_CHIP && type <= ItemType::HANA_ASSIST) {
    GfMenuFlag::set1(0x3a + type, 1);
  }
}

bool GfMenuManager::isBattleState(u32 state) {
  GfMenuManager *manager = get();
  if (manager == nullptr || !manager->unknown4090) {
    return false;
  }
  return manager->unknown40dc.test(state);
}

void GfMenuManager::setBattleState(u32 state, bool isEnable) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && manager->unknown40ca) {
    manager->unknown40dc.set(state, isEnable);
  }
}

bool GfMenuManager::isDispHud(int hud) {
  GfMenuManager *manager = get();
  if (manager == nullptr || manager->unknown4091) {
    return false;
  }
  return manager->unknown40e4.test(hud);
}

void GfMenuManager::setDispAll(bool isDisp) {
  GfMenuManager *manager = get();
  if (manager != nullptr && !manager->unknown4091) {
    manager->unknown4100 = !isDisp;
  }
}

void GfMenuManager::openCommonWindow(u16 window) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjCommonText::open(manager->unknown40d0, window, 0);
    manager->unknown4154 = window;
  }
}

void GfMenuManager::openCommonWindow(const MenuCommonWindowParam &param) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjCommonText::open(manager->unknown40d0, param);
  }
}

void GfMenuManager::closeCommonWindow() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && manager->unknown40d0 != nullptr) {
    GfMenuObjCommonText::close();
  }
}

bool GfMenuManager::isOpenCommonWindow() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_COMMON_TEXT);
  }
  return false;
}

int GfMenuManager::getCommonWindowResult() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return 0;
  }
  if (manager->unknown4090) {
    return manager->unknown40d8;
  }
  return 0;
}

u32 GfMenuManager::getLatestCommonWinID() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return 0;
  }
  if (manager->unknown4090) {
    return manager->unknown4154;
  }
  return 0;
}

void GfMenuManager::openPreciousWindow(u16 item) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjCommonText::openItem(manager->unknown40d0, COMMON_TEXT_PRECIOUS, item);
  }
}

bool GfMenuManager::isOpenPreciousWindow() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_COMMON_TEXT);
  }
  return false;
}

void GfMenuManager::openChapterTelop(u8 chapter) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && chapter >= 1 && chapter <= CHAPTER_MAX && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjChapterTelop::openBeginTelop(manager->unknown40d0, chapter);
  }
}

void GfMenuManager::openChapterEndTelop(u8 chapter) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && chapter >= 1 && chapter <= CHAPTER_MAX && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjChapterTelop::openEndTelop(manager->unknown40d0, chapter);
  }
}

bool GfMenuManager::isOpenChapterTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_CHAPTER_TELOP);
  }
  return false;
}

bool GfMenuManager::isOpenZoneTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_ZONE_TELOP);
  }
  return false;
}

void GfMenuManager::openDummyTutorial(u8 tutorial) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjDummyTutorial::OpenParam param;
    param.unknown00 = tutorial;
    GfMenuObjDummyTutorial::open(manager->unknown40d0, param);
  }
}

bool GfMenuManager::isOpenDummyTutorial() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_DUMMY_TUTORIAL);
  }
  return false;
}

u32 GfMenuManager::startTutorial(u32 tutorial) {
  u8 *bdat = GfDataBdat::getFP(0xe4);
  if (bdat != nullptr) {
    int top = Bdat::getIdTop(bdat);
    if (static_cast<int>(tutorial - top) >= 0) {
      int flag = (tutorial - top) + 0xc710;
      if (GfGameFlag::getLocal(1, flag) != 1) {
        GfPlayFactory::createStartTutorial(tutorial, nullptr);
        GfGameFlag::setLocal(1, flag, 1);
        return 1;
      }
    }
  }
  return 0;
}

void GfMenuManager::setEnableQuestOpen(bool isEnable) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    manager->unknown4101 = isEnable;
  }
}

bool GfMenuManager::isEnableQuestOpen() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  if (manager->unknown4090) {
    return manager->unknown4101;
  }
  return false;
}

GfMenuManager::REGION GfMenuManager::getRegion() {
  if (get() != nullptr) {
    return get()->unknown4104;
  }
  return REGION_JP;
}

bool GfMenuManager::isRegionUS() {
  if (get() != nullptr) {
    return get()->unknown4104 == REGION_US;
  }
  return false;
}

void GfMenuManager::openFullScreen(u32 screen, bool isFadeOut, bool isFadeIn) { GfMenuFullScreen::open(screen, isFadeOut, isFadeIn); }

void GfMenuManager::openMenu(u32 menu) {
  GfMenuObjMainRoot::OpenParam param;
  param.unknown00 = menu;
  GfMenuObjMainRoot::registOpenParam(param);
  GfMenuFullScreen::open(FULL_SCREEN_MAIN_ROOT, true, true);
}

void GfMenuManager::openBladeCreateFromEvent(u32 event) {
  GfMenuObjMainRoot::OpenParam mainRootParam;
  GfMenuObjBladeCreate::OpenParam bladeCreateParam;
  bladeCreateParam.unknown00 = event;
  GfMenuObjBladeCreate::registOpenParam(bladeCreateParam);
  mainRootParam.unknown00 = MAIN_ROOT_BLADE_CREATE;
  GfMenuObjMainRoot::registOpenParam(mainRootParam);
  GfMenuFullScreen::open(FULL_SCREEN_MAIN_ROOT, true, true);
}

void GfMenuManager::openBtlModelView() {
  if (get() != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_BTL_MODEL_VIEW);
  }
}

void GfMenuManager::closeBtlModelView() {
  if (get() != nullptr && get()->unknown40fd) {
    ui::UIManager::get()->terminateLayer(LAYER_BTL_MODEL_VIEW, true);
  }
}

bool GfMenuManager::isOpenBtlModelView() {
  if (get() != nullptr) {
    return get()->unknown40fd;
  }
  return false;
}

void GfMenuManager::openNameSelect() {
  GfMenuManager *manager = get();
  if (manager != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_NAME_SELECT);
    manager->unknown40fe = true;
  }
}

bool GfMenuManager::isOpenNameSelect() {
  if (get() != nullptr) {
    return get()->unknown40fe;
  }
  return false;
}

void GfMenuManager::openOpeningTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_OPENING_TELOP);
    manager->unknown40ff = true;
  }
}

void GfMenuManager::closeOpeningTelop() {
  if (get() != nullptr) {
    ui::UIManager::get()->terminateLayer(LAYER_OPENING_TELOP, true);
  }
}

bool GfMenuManager::isOpenOpeningTelop() {
  if (get() != nullptr) {
    return get()->unknown40ff;
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
  param.unknown00 = MAINMENU2_MAP;
  GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::setMainmenuOpenSystem() {
  GfMenuObjMainMenu2::OpenParam param;
  param.unknown00 = MAINMENU2_SYSTEM;
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
  saveLoadParam.unknown00 = SAVE_LOAD_SAVE;
  GfMenuObjSaveLoad2::registOpenParam(saveLoadParam);
  mainRootParam.unknown00 = MAIN_ROOT_SAVE_LOAD;
  GfMenuObjMainRoot::registOpenParam(mainRootParam);
  GfMenuFullScreen::open(FULL_SCREEN_MAIN_ROOT, true, true);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuManager>::~PtrSingleton();
