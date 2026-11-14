#include "gf/menu/object/gf_menu_obj_mercenary_report.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_bl_kizuna_ring.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_mercenary_root.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_quest_reward.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/sound/gf_sound.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMercenaryReport::GfMenuObjMercenaryReport(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(this), unknown358(false), unknown359(false), unknown360(nullptr), unknown368(nullptr), unknown370(nullptr) {
  unknown360 = unknown160();
  unknown368 = GfMenuCallContext::create();
  unknown370 = GfMenuCallContext::create();
}

GfMenuObjMercenaryReport::~GfMenuObjMercenaryReport() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown370);
  mm::mtl::safeRelease(unknown368);
  unknown360 = nullptr;
}

void GfMenuObjMercenaryReport::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
  unknown28 = GfMenuBladeList::create();
  GfMenuZoneAdapter::createFromReferenceZone(main.searchChild("TXT_report_unit_zone"), 0, false);
  GfMenuZoneAdapter::createFromReferenceZone(main.searchChild("IMG_reward_flag"), 2, false);
  GfMenuMissionAdapter::createFromReferenceMission(main.searchChild("TXT_report_mission_name"), 0, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(main.searchChild("TXT_reward_result"), 1, 0, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(main.searchChild("TXT_report_unit_idx_name"), 0, false);
  GfMenuCharDataAdapter::createFromBladeList(main.searchChild("IMG_bl_img"), 0x36, unknown28, 0, false);
  for (int i = 0; i < 6; i++) {
    name.format("IMG_report_unit_bl_face@%02d", i + 1);
    GfMenuCharDataAdapter *adapter = GfMenuCharDataAdapter::createFromBladeList(main.searchChild(name.c_str()), 3, unknown28, i, false);
    if (adapter != nullptr) {
      name.format("LAY_report_unit_bl@%02d", i + 1);
      adapter->unknown24 = main.searchChild(name.c_str());
    }
  }
  {
    ui::UIObjectAcc reward(main.unknown10, "LAY_reward");
    GfMenuObjQuestReward::OpenParam param;
    param.unknown10 = unknown360;
    param.unknown08 = reward.searchChild("LAY_reward_info");
    param.unknown0c = 1;
    GfMenuObjQuestReward::create(unknown368, param, false);
// __LINE__ must be 136 as in the original file: it is the line argument of operator new.
#line 136
    RewardListener *rewardListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RewardListener(this);
    rewardListener->addRef();
    ui::UIEventManager::get()->registObjectListener(reward.unknown10, rewardListener);
    if (rewardListener != nullptr) {
      rewardListener->release();
    }
  }
// __LINE__ must be 140 as in the original file: it is the line argument of operator new.
#line 140
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  GfMenuObjMainMenu2::setSystemKeyEnable(false);
  GfMenuObjMainMenu2::setCloseKeyEnable(false);
  GfMenuObject::initialize();
}

void GfMenuObjMercenaryReport::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryReport::update() {
  unknown30.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjMercenaryReport::seqStart() {
  for (u32 i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
    unknown120 *team = GfDataMercenaries::getTeamByIndex(i);
    if (team != nullptr && GfDataMercenaries::isTeamStateReward(team->unknown10)) {
      unknown24 = team->unknown10;
      break;
    }
  }
  if (unknown24 == 0) {
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqEnd);
  } else {
    u32 mission = GfDataMercenaries::getTeamMission(unknown24);
    u32 zone = GfDataMercenaries::getMissionZoneID(mission);
    GfMenuReference::setReferenceTeamID(unknown24);
    GfMenuReference::setReferenceMissionID(mission);
    GfMenuReference::setReferenceZoneID(zone);
    GfMenuObjMercenaryRoot::openBg(zone);
    unknown360->unknown0c = mission;
    {
      GfMenuBladeList::TeamSetup setup;
      setup.unknown18 = unknown24;
      unknown28->clear();
      unknown28->setupFromTeam(setup);
    }
    unknown358 = false;
    unknown30.unknown004(15);
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqDispBlade);
    {
      ui::UIObjectAcc main(unknown18, "LAY_main");
      main.setDisp(true);
      mm::Rect<s16> rect;
      main.getLayoutRect("blade_l_1", rect);
      mm::Rect<s16> next;
      main.getLayoutRect("blade_l_2", next);
      GfMenuObjUtil::placeObjectH(main.unknown10, "LAY_report_unit_bl@%02d", unknown28->getSize(), mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.x - rect.x);
    }
    GfMenuObjQuestReward::open(unknown368, false);
  }
  return true;
}

bool GfMenuObjMercenaryReport::seqEnd() {
  bool isEnd;
  if (!GfMenuManager::isSwitchingFullScreen()) {
    changeFSSubLayer(unknown18, 2, 0x34, false);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqDispBlade() {
  ui::UIObjectAcc image(unknown18, "IMG_bl_img");
  bool isEnd;
  if (!unknown358) {
    ui::UIObjectAcc layer(unknown18, "LAY_bl_img");
    layer.setDisp(true);
    u32 blade = unknown28->getContents(0).unknown00;
    layer.setLayout(image.unknown10, "character");
    GfMenuObjUtil::ImageParam imageParam;
    if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
      mm::Vec2 scale;
      image.getScale(scale);
      scale.x = imageParam.unknown04 * scale.x;
      scale.y = imageParam.unknown04 * scale.y;
      image.setScale(scale);
      GfMenuObjUtil::addPos(image.unknown10, imageParam.unknown00, imageParam.unknown02);
    }
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x200;
    param.unknown0c = 1;
    param.unknown00 = 0.2f;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    GfMenuObjUtil::playSE("se_fld_allmap_503");
    SCOM_FIELD_VOICE::createMercenariesResult(unknown28->getContents(0).unknown00);
    unknown358 = true;
    isEnd = false;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.unknown10))) {
    unknown358 = false;
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqDispInfo);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqDispInfo() {
  ui::UIObjectAcc report(unknown18, "LAY_report");
  ui::UIObjectAcc effect(report.unknown10, "IMG_report_eff");
  bool isEnd;
  if (!unknown358) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    GfMenuObjUtil::startCtrl(report.unknown10, param, nullptr);
    effect.startAnimation("start", false);
    effect.setDisp(true);
    GfMenuObjUtil::playSE(16);
    isEnd = false;
    unknown358 = true;
  } else if (!effect.isPlayingAnimation()) {
    unknown358 = false;
    unknown30.unknown004(60);
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqDispReward);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqDispReward() {
  bool isEnd;
  if (!unknown358) {
    ui::UIObjectAcc reward(unknown18, "LAY_reward");
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    sendEvent(reward.unknown10, event, 0.0f);
    unknown358 = true;
    isEnd = false;
  } else if (!unknown359) {
    isEnd = false;
  } else {
    unknown358 = false;
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqClose);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqClose() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown358) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(main.unknown10, param, "LAY_report");
    GfMenuObjUtil::startCtrl(main.unknown10, param, "LAY_bl_img");
    isEnd = false;
    unknown358 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(main.searchChild("LAY_report")))) {
    main.setDispChild(false, "LAY_bl_img");
    u32 mission = GfDataMercenaries::getTeamMission(unknown24);
    GfGameMercenaries::execMissionRewardByTeamID(unknown24);
    GfGameMercenaries::clearTeamMember(unknown24);
    if (GfDataMercenaries::isEnableOrder(mission)) {
      GfGameMercenaries::setMissionFlag(mission, 1);
    }
    unknown24 = 0;
    unknown30.unknown004(15);
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqCheckAchive);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryReport::seqCheckAchive() {
  if (unknown28->getSize() != 0) {
    while (unknown28->getSize() != 0) {
      if (GfMenuObjUtil::isBladeAchivementReleased(unknown28->getContents(0).unknown00)) {
        MM_VERIFY(unknown28->getSize());
        ui::UIObjectAcc main(unknown18, "LAY_main");
        u32 blade = unknown28->getContents(0).unknown00;
        GfMenuObjBlKizunaRing::openForMercenary(main.unknown10, blade, 3);
        unknown30.unknown002(&GfMenuObjMercenaryReport::seqWaitLoadKizuna);
        return true;
      }
      GfMenuBladeList *list = unknown28;
      list->contents.erase(list->contents.begin());
      list->subSize(1);
      list->contentsChanged = true;
    }
  }
  unknown30.unknown002(&GfMenuObjMercenaryReport::seqStart);
  return true;
}

bool GfMenuObjMercenaryReport::seqWaitLoadKizuna() {
  if (!GfMenuManager::isSwitchingFullScreen()) {
    unknown370->reset();
    if (GfMenuObjBlKizunaRing::attach(unknown370)) {
      unknown30.unknown002(&GfMenuObjMercenaryReport::seqWaitEndKizuna);
      return true;
    }
  }
  return false;
}

bool GfMenuObjMercenaryReport::seqWaitEndKizuna() {
  bool isEnd;
  if (unknown370->isTerm() && !GfMenuManager::isSwitchingFullScreen()) {
    unknown30.unknown002(&GfMenuObjMercenaryReport::seqCheckAchive);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

void GfMenuObjMercenaryReport::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown30.unknown005();
    unknown20->unknown30.unknown002(&GfMenuObjMercenaryReport::seqStart);
    GfMenuObjOperationInfo::setGuideDisp(false);
    break;
  case 2: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown0c = true;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case 3:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryReport::RewardListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::registTimer(acc.unknown10, 0, 2.0f, false);
    } else if (event.unknown08 == 2) {
      GfMenuObject::enableInput(acc.unknown10);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    } else if (event.unknown08 == 3) {
      acc.setDispChild(false, "TXT_reward_complete");
      unknown20->unknown359 = true;
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      GfMenuObject::disableInput(acc.unknown10);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "cmn_fade_emotion";
      param.unknown58 = "fade_out";
      param.unknown14 = 10;
      param.unknown04 = 3;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      GfMenuObjUtil::playSECommonDecide();
    }
    break;
  case 0xb: {
    acc.setDispChild(true, "TXT_reward_complete");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "sample";
    param.unknown58 = "fadein";
    param.unknown14 = 8;
    param.unknown04 = 2;
    int ctrl = GfMenuObjUtil::startCtrl(acc.searchChild("TXT_reward_complete"), param, nullptr);
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    GfMenuObject::releaseTimer(acc.unknown10);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    acc.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_zoom_2";
    param.unknown58 = "fade_in";
    param.unknown14 = 8;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown20->unknown359 = false;
    GfMenuObjUtil::playJingle(7);
    break;
  }
  }
}

} // namespace gf
