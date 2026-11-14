#include "gf/menu/gf_menu_manager.h"

#include "bdat.h"
#include "framework/lang_util.h"
#include "framework/resource/common_resource.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_pad.h"
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
#include "gf/menu/call/gf_menu_call_manager.h"
#include "gf/menu/gf_menu_equip.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_hud.h"
#include "gf/menu/gf_menu_kizunaring.h"
#include "gf/menu/gf_menu_location.h"
#include "gf/menu/gf_menu_main.h"
#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_map_info.h"
#include "gf/menu/gf_menu_minimap.h"
#include "gf/menu/gf_menu_order_mgr.h"
#include "gf/menu/gf_menu_precious.h"
#include "gf/menu/gf_menu_quest.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_script_manager.h"
#include "gf/menu/gf_menu_shop.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_status.h"
#include "gf/menu/object/gf_menu_obj_action_window.h"
#include "gf/menu/object/gf_menu_obj_arts_palette.h"
#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "gf/menu/object/gf_menu_obj_blade_create.h"
#include "gf/menu/object/gf_menu_obj_blade_switch.h"
#include "gf/menu/object/gf_menu_obj_chain_attack.h"
#include "gf/menu/object/gf_menu_obj_chapter_telop.h"
#include "gf/menu/object/gf_menu_obj_combo_route.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_compass.h"
#include "gf/menu/object/gf_menu_obj_damage_buff.h"
#include "gf/menu/object/gf_menu_obj_damage_value.h"
#include "gf/menu/object/gf_menu_obj_drop_item.h"
#include "gf/menu/object/gf_menu_obj_dummy_tutorial.h"
#include "gf/menu/object/gf_menu_obj_enemy_status.h"
#include "gf/menu/object/gf_menu_obj_environment_info.h"
#include "gf/menu/object/gf_menu_obj_exp_get.h"
#include "gf/menu/object/gf_menu_obj_field_icon.h"
#include "gf/menu/object/gf_menu_obj_help_hud.h"
#include "gf/menu/object/gf_menu_obj_location_telop.h"
#include "gf/menu/object/gf_menu_obj_main_root.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_minimap2.h"
#include "gf/menu/object/gf_menu_obj_option.h"
#include "gf/menu/object/gf_menu_obj_other_cursor.h"
#include "gf/menu/object/gf_menu_obj_party_gauge.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/menu/object/gf_menu_obj_party_status2.h"
#include "gf/menu/object/gf_menu_obj_popup.h"
#include "gf/menu/object/gf_menu_obj_quest_log.h"
#include "gf/menu/object/gf_menu_obj_save_load2.h"
#include "gf/menu/object/gf_menu_obj_special_gauge.h"
#include "gf/menu/object/gf_menu_obj_target_cursor.h"
#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "gf/menu/object/gf_menu_obj_tutorial.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"
#include "layer/layer_acc_def_obj.h"
#include "layer/layer_acc_manager.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/input/ui_input_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_util.h"

namespace fw {
enum LangType : u32;
enum SoundCategory : int;
} // namespace fw

namespace gf {

bool GfMenuManager::isOpenFullScreen() { return GfMenuFullScreen::isOpen(); }

bool GfMenuManager::isSwitchingFullScreen() { return GfMenuFullScreen::isSwitching(); }

void GfMenuManager::changeHUDScene(u32 scene) { GfMenuHUD::changeScene(scene); }

namespace {

// Inferred role: call menu of the chapter telop; original name unknown.
constexpr u32 MENU_UNKNOWN_68 = 68;
// Inferred role: call menu of the zone telop; original name unknown.
constexpr u32 MENU_UNKNOWN_69 = 69;
// Inferred role: call menu of the common text; original name unknown.
constexpr u32 MENU_UNKNOWN_100 = 100;
// Inferred role: call menu of the dummy tutorial; original name unknown.
constexpr u32 MENU_UNKNOWN_121 = 121;

// Inferred role: common text type that shows a precious item; original name unknown.
constexpr u32 COMMON_TEXT_UNKNOWN_11 = 11;
// Inferred role: maximum chapter number of the chapter telop; original name unknown.
constexpr u8 CHAPTER_UNKNOWN_10 = 10;

// Inferred role: UI layer of the battle model view; original name unknown.
constexpr u32 LAYER_UNKNOWN_10 = 10;
// Inferred role: UI layer of the name selection; original name unknown.
constexpr u32 LAYER_UNKNOWN_12 = 12;
// Inferred role: UI layer of the opening telop; original name unknown.
constexpr u32 LAYER_UNKNOWN_13 = 13;
// Inferred role: UI layer of the staff roll; original name unknown.
constexpr u32 LAYER_UNKNOWN_14 = 14;

// Inferred role: full screen of the main root; original name unknown.
constexpr u32 FULL_SCREEN_UNKNOWN_2 = 2;
// Inferred role: open parameter of the main root that shows the blade creation; original name unknown.
constexpr u32 MAIN_ROOT_UNKNOWN_11 = 11;
// Inferred role: open parameter of the main root that shows the save and load; original name unknown.
constexpr u32 MAIN_ROOT_UNKNOWN_53 = 53;
// Inferred role: open parameter of the main menu 2 that shows the map; original name unknown.
constexpr u32 MAINMENU2_UNKNOWN_1 = 1;
// Inferred role: open parameter of the main menu 2 that shows the system menu; original name unknown.
constexpr u32 MAINMENU2_UNKNOWN_6 = 6;
// Inferred role: open parameter of the save and load that selects the save; original name unknown.
constexpr u16 SAVE_LOAD_UNKNOWN_1 = 1;
// Inferred role: sound effect of acceptAccess; original name unknown.
constexpr u32 SE_UNKNOWN_27 = 27;
// Inferred role: language selection step that waits for the language resource to load; original name unknown.
constexpr u32 LANGUAGE_STEP_UNKNOWN_1 = 1;
// Inferred role: language selection step where the player chooses; original name unknown.
constexpr u32 LANGUAGE_STEP_UNKNOWN_2 = 2;
// Inferred role: language selection step that waits for the confirmation resource to load; original name unknown.
constexpr u32 LANGUAGE_STEP_UNKNOWN_3 = 3;
// Inferred role: language selection step where the player confirms; original name unknown.
constexpr u32 LANGUAGE_STEP_UNKNOWN_4 = 4;
// Inferred role: language selection step that releases the resources; original name unknown.
constexpr u32 LANGUAGE_STEP_UNKNOWN_5 = 5;
// Inferred role: language selection step after which the selection is done; original name unknown.
constexpr u32 LANGUAGE_STEP_UNKNOWN_6 = 6;

// Inferred role: trigger bits of the control pad read by the language selection; original names unknown.
constexpr u32 PAD_BUTTON_UNKNOWN_0 = 1 << 0;
constexpr u32 PAD_BUTTON_UNKNOWN_1 = 1 << 1;
constexpr u32 PAD_BUTTON_UNKNOWN_2 = 1 << 2;
constexpr u32 PAD_BUTTON_UNKNOWN_3 = 1 << 3;

// Inferred role: places the layer object of a loaded layout at a position, centered; original name unknown.
void unknown004(layer::LayerBase *layer, f32 x, f32 y) {
  layer::LayerAccDefObj object(layer);
  object.setCenterType(layer::LAYER_CENTER_TYPE_CENTER);
  object.setPos(x, y);
}

bool isOpenCallMenu(GfMenuManager *manager, u32 menu) {
  if (manager->unknown40d0 == nullptr) {
    return false;
  }
  if (manager->unknown40d0->getState() == GfMenuCallContext::STATE_UNKNOWN_0) {
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

// Inferred role: state of a function-local static of GfMenuManager::update, only constructed; original type name unknown.
struct unknown003 {
  unknown003() : unknown00(false), unknown10(0) {}

  bool unknown00;
  u8 _01[0x10 - 0x01];
  u32 unknown10;
};

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

void GfMenuManager::update(const fw::UpdateInfo &) {
  if (get() != nullptr) {
    static unknown003 s_unknown;
  }
}

void GfMenuManager::build(const GfSetupParam &param) {
  // __LINE__ must be 347 as in the original file: it is an argument of the allocation.
#line 347
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMenuManager(param);
}

void GfMenuManager::destroy() {
  GfMenuManager *manager = get();
  manager->finalize();
  delete manager;
}

bool GfMenuManager::isInitialized() {
  GfMenuManager *manager = get();
  if (manager == nullptr || !manager->unknown4090 || manager->unknown40b0) {
    return false;
  }
  return GfMenuReference::isInitialized() && GfMenuCallManager::isInitialized() && GfMenuAdapterManager::isInitialized() && GfMenuFade::isInitialized() && GfMenuFullScreen::isInitialized() &&
         GfMenuHUD::isInitialized() && GfMenuStatus::isInitialized() && GfMenuEquip::isInitialized() && GfMenuMain::isInitialized() && GfMenuShop::isInitialized() && GfMenuPrecious::isInitialized() &&
         GfMenuKizunaring::isInitialized() && GfMenuQuest::isInitialized() && GfMenuMinimap::isInitialized() && GfMenuScriptManager::isInitialized() && GfMenuFieldSkill::isInitialized() &&
         GfMenuManyObjects::isInitialized() && GfMenuOrderMgr::isInitialized() && GfMenuLocation::isInitialized() && GfMenuMapInfo::isInitialized() && GfMenuSoundManager::isInitialized();
}

bool GfMenuManager::isRegionJP() {
  if (get() != nullptr) {
    return get()->unknown4104 == REGION_UNKNOWN_0;
  }
  return false;
}

bool GfMenuManager::selectLanguage() {
  switch (unknown4108) {
  case 0: {
    mm::mtl::FixStr<128> fileName;
    ui::UIUtil::makeMenuImageFileName(fileName, "mnu001_langage");
    mm::mtl::safeRelease(unknown4110);
    unknown4110 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), fileName.c_str(), 10, true);
    ui::UIUtil::makeMenuImageFileName(fileName, "mnu001_langage_caution");
    mm::mtl::safeRelease(unknown4120);
    unknown4120 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), fileName.c_str(), 10, true);
    ui::UIUtil::makeMenuImageFileName(fileName, "mnu001_langage_select");
    mm::mtl::safeRelease(unknown4130);
    unknown4130 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), fileName.c_str(), 10, true);
    ui::UIUtil::makeMenuImageFileName(fileName, "mnu001_langage_select_cn");
    mm::mtl::safeRelease(unknown4138);
    unknown4138 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), fileName.c_str(), 10, true);
    ui::UIUtil::makeMenuImageFileName(fileName, "mnu001_langage_select_tw");
    mm::mtl::safeRelease(unknown4140);
    unknown4140 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), fileName.c_str(), 10, true);
    unknown4108 = LANGUAGE_STEP_UNKNOWN_1;
    return false;
  }
  case LANGUAGE_STEP_UNKNOWN_1:
    if (!unknown4110->valid()) {
      return false;
    }
    if (unknown4120->valid()) {
      layer::LayerAccManager layerAcc;
      mm::mtl::safeRelease(unknown4118);
      unknown4118 = layerAcc.createObj(unknown4110->getAssetData());
      unknown004(unknown4118, 640.0f, 300.0f);
      if (fw::LangUtil::getLangType() == 0) {
        mm::mtl::safeRelease(unknown4128);
        unknown4128 = layerAcc.createObj(unknown4120->getAssetData());
        unknown004(unknown4128, 640.0f, 470.0f);
      }
      unknown4108 = LANGUAGE_STEP_UNKNOWN_2;
    }
    return false;
  case LANGUAGE_STEP_UNKNOWN_2: {
    const fw::PadData *pad = fw::PadManager::getControlPadData(0);
    layer::LayerAccDefObj layout(unknown4118);
    layout.setDisp(true);
    if (unknown4128 != nullptr) {
      layer::LayerAccDefObj caution(unknown4128);
      caution.setDisp(true);
    }
    u32 trigger = pad->unknown04;
    bool isSelected = false;
    if ((trigger & PAD_BUTTON_UNKNOWN_3) != 0) {
      unknown4150 = 0;
      isSelected = true;
    } else if ((trigger & PAD_BUTTON_UNKNOWN_0) != 0) {
      unknown4150 = 1;
      isSelected = true;
    } else if ((trigger & PAD_BUTTON_UNKNOWN_1) != 0) {
      unknown4150 = 2;
      isSelected = true;
    }
    if (isSelected) {
      layout.setDisp(false);
      if (unknown4128 != nullptr) {
        layer::LayerAccDefObj caution(unknown4128);
        caution.setDisp(false);
      }
      unknown4108 = LANGUAGE_STEP_UNKNOWN_3;
      fw::SoundManager::get()->playSe(1, nullptr, 1.0f, static_cast<fw::SoundCategory>(0));
    }
    return false;
  }
  case LANGUAGE_STEP_UNKNOWN_3: {
    fw::CommonResource *confirm = unknown4150 == 1 ? unknown4140 : (unknown4150 == 2 ? unknown4138 : unknown4130);
    if (confirm != nullptr && confirm->valid()) {
      layer::LayerAccManager layerAcc;
      mm::mtl::safeRelease(unknown4148);
      unknown4148 = layerAcc.createObj(confirm->getAssetData());
      unknown004(unknown4148, 640.0f, 360.0f);
      unknown4108 = LANGUAGE_STEP_UNKNOWN_4;
    }
    return false;
  }
  case LANGUAGE_STEP_UNKNOWN_4: {
    const fw::PadData *pad = fw::PadManager::getControlPadData(0);
    if ((pad->unknown04 & PAD_BUTTON_UNKNOWN_2) == 0) {
      if ((pad->unknown04 & PAD_BUTTON_UNKNOWN_1) == 0) {
        return false;
      }
      layer::LayerAccDefObj layout(unknown4148);
      layout.setDisp(false);
      fw::SoundManager::get()->playSe(2, nullptr, 1.0f, static_cast<fw::SoundCategory>(0));
      unknown4108 = LANGUAGE_STEP_UNKNOWN_2;
      return false;
    }
    switch (unknown4150) {
    case 0:
      SCOM_RELOAD_TEXT::create(static_cast<fw::LangType>(0));
      break;
    case 1:
      SCOM_RELOAD_TEXT::create(static_cast<fw::LangType>(11));
      break;
    case 2:
      SCOM_RELOAD_TEXT::create(static_cast<fw::LangType>(6));
      break;
    }
    fw::SoundManager::get()->playSe(1, nullptr, 1.0f, static_cast<fw::SoundCategory>(0));
    unknown4108 = LANGUAGE_STEP_UNKNOWN_5;
    return false;
  }
  case LANGUAGE_STEP_UNKNOWN_5:
    mm::mtl::safeRelease(unknown4140);
    mm::mtl::safeRelease(unknown4138);
    mm::mtl::safeRelease(unknown4130);
    mm::mtl::safeRelease(unknown4148);
    mm::mtl::safeRelease(unknown4120);
    mm::mtl::safeRelease(unknown4128);
    mm::mtl::safeRelease(unknown4110);
    mm::mtl::safeRelease(unknown4118);
    unknown4108 = LANGUAGE_STEP_UNKNOWN_6;
    return false;
  default:
    return true;
  }
}

void GfMenuManager::changeBattleState(u32 state, bool isEnable) {
  switch (state) {
  case 0:
    if (isEnable) {
      unknown40e4.set(0);
      unknown40e4.set(2, false);
      unknown40e4.set(3, false);
    } else {
      unknown40e4.set(0, false);
      if (!unknown40dc.test(1) && unknown40ca) {
        unknown40e4.set(2);
        unknown40e4.set(3);
      }
    }
    break;
  case 1:
    if (isEnable) {
      unknown40e4.set(2, false);
      unknown40e4.set(3, false);
    } else if (!unknown40dc.test(0) && unknown40ca) {
      unknown40e4.set(2);
      unknown40e4.set(3);
    }
    break;
  case 3:
    unknown40e4.set(4, isEnable);
    break;
  case 4:
    if (isEnable) {
      GfMenuObjBladeChange::enableAwakening(true);
    } else {
      GfMenuObjBladeChange::enableAwakening(false);
    }
    break;
  case 6:
    if (isEnable) {
      unknown40e4.set(0, false);
    } else if (unknown40dc.test(0)) {
      unknown40e4.set(0);
    }
    break;
  case 7:
    unknown40e4.set(5, isEnable);
    break;
  default:
    break;
  }
}

void GfMenuManager::updateHudState() {
  if (!get()->unknown4091) {
    for (u32 hud = 0; hud < 6; hud++) {
      u32 flags = unknown40e4.unknown001(0);
      u32 mask = 1UL << hud;
      bool isEnable = (flags & mask) != 0;
      if (isEnable != unknown40e8.test(hud)) {
        switch (hud) {
        case 0:
          if (isEnable) {
            GfMenuObjArtsPalette::open();
            GfMenuObjPartyGauge::open();
            if (GfMenuObjUtil::isLeaderBladeEnable()) {
              GfMenuObjBladeChange::open();
              GfMenuObjSpecialGauge::open();
            }
            GfMenuObjPartyStatus::open(true);
          } else {
            GfMenuObjArtsPalette::close();
            if (!unknown40ca || !unknown40dc.test(6)) {
              GfMenuObjPartyGauge::close();
            }
            if (GfMenuObjUtil::isLeaderBladeEnable()) {
              GfMenuObjBladeChange::close();
              GfMenuObjSpecialGauge::close();
            }
            GfMenuObjPartyStatus::close(false);
          }
          break;
        case 1:
          if (isEnable) {
            GfMenuObjPartyStatus::open(false);
            GfMenuObjTargetInfo::disp(true);
            GfMenuObjTargetCursor::disp(true);
            GfMenuObjFieldIcon::dispAll(true);
            GfMenuObjOtherCursor::disp(true);
            GfMenuObjActionWindow::disp(true);
            GfMenuObjEnemyStatus::disp(true);
          } else {
            GfMenuObjPartyStatus::close(true);
            GfMenuObjTargetInfo::disp(false);
            GfMenuObjTargetCursor::disp(false);
            GfMenuObjFieldIcon::dispAll(false);
            GfMenuObjOtherCursor::disp(false);
            GfMenuObjActionWindow::disp(false);
            GfMenuObjEnemyStatus::disp(false);
            GfMenuObjLocationTelop::close();
          }
          break;
        case 2:
          if (isEnable) {
            GfMenuObjCompass::open();
            GfMenuObjMinimap2::open();
            GfMenuObjEnvironmentInfo::open();
            GfMenuObjTargetInfo::dispAllOther(true);
            GfMenuObjTargetInfo::dispAllSymbol(true);
            GfMenuObjFieldIcon::dispAll(true);
            GfMenuObjHelpHud::enable();
          } else {
            GfMenuObjCompass::close();
            GfMenuObjMinimap2::close();
            GfMenuObjEnvironmentInfo::close();
            GfMenuObjTargetInfo::dispAllOther(false);
            GfMenuObjTargetInfo::dispAllSymbol(false);
            GfMenuObjFieldIcon::dispAll(false);
            GfMenuObjHelpHud::disable();
          }
          break;
        case 3:
          if (isEnable) {
            GfMenuObjQuestLog::openLog();
            GfMenuObjBladeSwitch::setActive(true);
            GfMenuObjPopup::continuePickup(0);
          } else {
            GfMenuObjQuestLog::closeLog();
            GfMenuObjBladeSwitch::setActive(false);
            GfMenuObjPopup::pausePickup();
          }
          break;
        case 4:
          if (isEnable) {
            GfMenuObjTargetInfo::disp(false);
            GfMenuObjComboRoute::disp(false);
            GfMenuObjPartyGauge::disp(false);
          } else {
            GfMenuObjTargetInfo::disp(true);
            GfMenuObjComboRoute::disp(true);
            GfMenuObjPartyGauge::disp(true);
          }
          break;
        case 5:
          if (unknown40dc.test(0) || unknown40dc.test(1)) {
            if (isEnable) {
              GfMenuObjEnemyStatus::disp(false);
              GfMenuObjComboRoute::disp(false);
              GfMenuObjPartyStatus2::disp(false);
              GfMenuObjPartyGauge::disp(false);
            } else {
              GfMenuObjEnemyStatus::disp(true);
              GfMenuObjComboRoute::disp(true);
              GfMenuObjPartyStatus2::disp(true);
              GfMenuObjPartyGauge::disp(true);
            }
          } else {
            GfMenuObjEnemyStatus::disp(false);
            GfMenuObjComboRoute::disp(false);
            GfMenuObjPartyStatus2::disp(false);
            GfMenuObjPartyGauge::disp(false);
          }
          break;
        }
      }
    }
    unknown40e8 = unknown40e4;
  }
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

void GfMenuManager::applyOptionData(const SDataOption &option) { applyGammaCorrectValue(static_cast<f32>(option.unknown4c._1a) / unknown005); }

void GfMenuManager::setupGame() {
  if (GfMenuFlag::get1(0x31) == 0) {
    GfMenuFlag::set1(0x28, 1);
    GfMenuFlag::set1(0x29, 1);
    GfMenuFlag::set1(0x2a, 0);
    GfMenuFlag::set1(0x2b, 1);
    GfMenuFlag::set1(0x2c, 1);
    GfMenuFlag::set1(0x2d, 0);
    GfMenuFlag::set1(0x2e, 1);
    GfMenuFlag::set1(0x2f, 1);
    GfMenuFlag::set1(0x30, 1);
    GfMenuFlag::set1(0x31, 1);
  }
  for (int flag = 0x3b; flag < 0x50; flag++) {
    mm::mtl::FixedVector<GfItem, 1024> items;
    GfItemUtil::getInfo(items, static_cast<ItemType::Type>(flag - 0x3a), false);
    if (!items.empty()) {
      GfMenuFlag::set1(flag, 1);
    }
  }
  GfMenuObjPopup::closeAll();
}

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
    return unknown020;
  }
  if (manager->unknown4090) {
    return manager->unknown40b8;
  }
  return unknown020;
}

GF_OBJ_HANDLE *GfMenuManager::getAccessObjHandle() {
  GfMenuManager *manager = get();
  if (manager == nullptr) {
    return unknown020;
  }
  if (manager->unknown4090) {
    return manager->unknown40c0;
  }
  return unknown020;
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
    if (unknown40c0 != unknown020) {
      unknown40c9 = true;
    }
    unknown40c0 = unknown020;
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

void GfMenuManager::checkElementCombo() {
  GF_OBJ_HANDLE *handle = getTargetObjHandle();
  if (handle == unknown020) {
    return;
  }
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return;
  }
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return;
  }
  GfObjPropertyEnemy *enemy = property->getEnemy();
  if (enemy == nullptr) {
    return;
  }
  bool isCombo = enemy->unknowndc != 0;
  if (unknown40fc != isCombo) {
    if (isCombo) {
      GfMenuObjComboRoute::open();
    } else {
      GfMenuObjComboRoute::close();
    }
    unknown40fc = isCombo;
  }
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
  case GEV_UNKNOWN_11:
    unknown40dc.clear();
    unknown40ca = false;
    GfMenuObjPartyGauge::close();
    GfMenuObjPartyStatus::close(true);
    GfMenuObjComboRoute::close();
    GfMenuObjChainAttack::closeResult();
    break;
  case GEV_UNKNOWN_12:
    if (ui::UIInputManager::get() != nullptr) {
      ui::UIInputManager::get()->enable();
    }
    break;
  case GEV_UNKNOWN_13:
    unknown002();
    GfMenuObjPartyGauge::close();
    GfMenuObjChainAttack::closeResult();
    // fallthrough
  case GEV_UNKNOWN_9:
    GfMenuObjComboRoute::close();
    GfMenuObjPartyStatus::close(true);
    break;
  default:
    break;
  }
}

void GfMenuManager::gevSalvageStateChange(u32 state) {
  switch (state) {
  case GfGameSalvage::STATE_UNKNOWN_3:
    unknown40e4.set(1, false);
    unknown40e4.set(2, false);
    break;
  case GfGameSalvage::STATE_UNKNOWN_4:
    GfMenuObjEnvironmentInfo::close();
    break;
  case GfGameSalvage::STATE_UNKNOWN_6:
    unknown002();
    break;
  case GfGameSalvage::STATE_UNKNOWN_20:
    unknown40e4.set(1);
    unknown40e4.set(2);
    break;
  default:
    break;
  }
}

void GfMenuManager::gevPlayerControl(GEV event) {
  if (event == GEV_UNKNOWN_15) {
    GfMenuReference::clearPartyStatusLock();
    unknown40e4.set(1, false);
    unknown40e4.set(2, false);
    unknown40e4.set(3, false);
    unknown40ca = false;
  } else if (event == GEV_UNKNOWN_14) {
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
  if (type >= ItemType::ITEM_TYPE_UNKNOWN_1 && type <= ItemType::ITEM_TYPE_UNKNOWN_20) {
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
    return isOpenCallMenu(manager, MENU_UNKNOWN_100);
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
    GfMenuObjCommonText::openItem(manager->unknown40d0, COMMON_TEXT_UNKNOWN_11, item);
  }
}

bool GfMenuManager::isOpenPreciousWindow() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_UNKNOWN_100);
  }
  return false;
}

void GfMenuManager::openChapterTelop(u8 chapter) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && chapter >= 1 && chapter <= CHAPTER_UNKNOWN_10 && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjChapterTelop::openBeginTelop(manager->unknown40d0, chapter);
  }
}

void GfMenuManager::openChapterEndTelop(u8 chapter) {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090 && chapter >= 1 && chapter <= CHAPTER_UNKNOWN_10 && manager->unknown40d0 != nullptr) {
    manager->unknown40d0->reset();
    GfMenuObjChapterTelop::openEndTelop(manager->unknown40d0, chapter);
  }
}

bool GfMenuManager::isOpenChapterTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_UNKNOWN_68);
  }
  return false;
}

bool GfMenuManager::isOpenZoneTelop() {
  GfMenuManager *manager = get();
  if (manager != nullptr && manager->unknown4090) {
    return isOpenCallMenu(manager, MENU_UNKNOWN_69);
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
    return isOpenCallMenu(manager, MENU_UNKNOWN_121);
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
  return REGION_UNKNOWN_0;
}

bool GfMenuManager::isRegionUS() {
  if (get() != nullptr) {
    return get()->unknown4104 == REGION_UNKNOWN_1;
  }
  return false;
}

void GfMenuManager::openFullScreen(u32 screen, bool isFadeOut, bool isFadeIn) { GfMenuFullScreen::open(screen, isFadeOut, isFadeIn); }

void GfMenuManager::openMenu(u32 menu) {
  GfMenuObjMainRoot::OpenParam param;
  param.unknown00 = menu;
  GfMenuObjMainRoot::registOpenParam(param);
  GfMenuFullScreen::open(FULL_SCREEN_UNKNOWN_2, true, true);
}

void GfMenuManager::openBladeCreateFromEvent(u32 event) {
  GfMenuObjMainRoot::OpenParam mainRootParam;
  GfMenuObjBladeCreate::OpenParam bladeCreateParam;
  bladeCreateParam.unknown00 = event;
  GfMenuObjBladeCreate::registOpenParam(bladeCreateParam);
  mainRootParam.unknown00 = MAIN_ROOT_UNKNOWN_11;
  GfMenuObjMainRoot::registOpenParam(mainRootParam);
  GfMenuFullScreen::open(FULL_SCREEN_UNKNOWN_2, true, true);
}

void GfMenuManager::openBtlModelView() {
  if (get() != nullptr) {
    ui::UIManager::get()->createLayer(LAYER_UNKNOWN_10);
  }
}

void GfMenuManager::closeBtlModelView() {
  if (get() != nullptr && get()->unknown40fd) {
    ui::UIManager::get()->terminateLayer(LAYER_UNKNOWN_10, true);
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
    ui::UIManager::get()->createLayer(LAYER_UNKNOWN_12);
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
    ui::UIManager::get()->createLayer(LAYER_UNKNOWN_13);
    manager->unknown40ff = true;
  }
}

void GfMenuManager::closeOpeningTelop() {
  if (get() != nullptr) {
    ui::UIManager::get()->terminateLayer(LAYER_UNKNOWN_13, true);
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
    ui::UIManager::get()->createLayer(LAYER_UNKNOWN_14);
  }
}

void GfMenuManager::closeStaffroll() {
  if (get() != nullptr) {
    ui::UIManager::get()->terminateLayer(LAYER_UNKNOWN_14, true);
  }
}

void GfMenuManager::setMainmenuOpenMap() {
  GfMenuObjMainMenu2::OpenParam param;
  param.unknown00 = MAINMENU2_UNKNOWN_1;
  GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::setMainmenuOpenSystem() {
  GfMenuObjMainMenu2::OpenParam param;
  param.unknown00 = MAINMENU2_UNKNOWN_6;
  GfMenuObjMainMenu2::registOpenParam(param);
}

void GfMenuManager::acceptAccess(GF_OBJ_HANDLE *) { GfMenuObjUtil::playSE(SE_UNKNOWN_27); }

void GfMenuManager::closeFullScreen(bool isFadeOut, bool isFadeIn) { GfMenuFullScreen::close(isFadeOut, isFadeIn); }

void GfMenuManager::execMinimap(bool isExec) {
  if (!isExec) {
    GfMenuMinimap::setDisp(false);
    return;
  }
  if (GfGameManager::getState() == GF_STATE_UNKNOWN_3 && !GfGameManager::isEvent(false)) {
    GfMenuMinimap::setDisp(true);
  }
}

bool GfMenuManager::isFieldHudInputEnable() { return !GfMenuObjTutorial::isWaiting(); }

void GfMenuManager::openSave() {
  GfMenuObjMainRoot::OpenParam mainRootParam;
  GfMenuObjSaveLoad2::OpenParam saveLoadParam;
  saveLoadParam.unknown00 = SAVE_LOAD_UNKNOWN_1;
  GfMenuObjSaveLoad2::registOpenParam(saveLoadParam);
  mainRootParam.unknown00 = MAIN_ROOT_UNKNOWN_53;
  GfMenuObjMainRoot::registOpenParam(mainRootParam);
  GfMenuFullScreen::open(FULL_SCREEN_UNKNOWN_2, true, true);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuManager>::~PtrSingleton();
