#include "gf/menu/object/gf_menu_obj_mercenary_top.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_mercenary_root.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_quest_reward.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_curve.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x34;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x100;
// Inferred role: common window id; original name unknown.
constexpr u16 unknown003 = 0x9e;
// Inferred role: mission stop text window id; original name unknown.
constexpr u32 unknown004 = 0x22;

GfMenuObjMercenaryTop::GfMenuObjMercenaryTop(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(1.0f), unknown60(nullptr), unknown68(nullptr), unknown70(nullptr),
      unknown98(nullptr), unknown0a0(this), unknown330(false), unknown334(0), unknown338(nullptr), unknown340(true) {
  unknown80 = unknown160();
  unknown88 = unknown160();
  unknown90 = unknown161();
  unknown98 = GfMenuCallContext::create();
  unknown338 = GfMenuCallContext::create();
}

GfMenuObjMercenaryTop::~GfMenuObjMercenaryTop() {
  mm::mtl::safeRelease(unknown338);
  mm::mtl::safeRelease(unknown98);
  unknown90 = nullptr;
  unknown88 = nullptr;
  unknown80 = nullptr;
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
}

void GfMenuObjMercenaryTop::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(unknown001, layerParam);
}

void GfMenuObjMercenaryTop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  u32 mission = 0;
  {
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      mission = layerParam.get<OpenParam>().unknown00;
      removeFSLayerParam(unknown20);
    }
  }
  updateTargetTeam();
  u32 zoneId = GfGameManager::getMapZoneID();
  unknown28 = GfMenuIDList::create();
  {
    ui::UIListInfoBase::SetupParam zoneParam;
    unknown28->setupMercenaryZoneList(zoneParam, true);
  }
  if (unknown28->getSize() != 0) {
    if (mission != 0) {
      zoneId = GfDataMercenaries::getMissionZoneID(mission);
    }
    for (u32 i = 0; i < unknown28->getSize(); i++) {
      if (zoneId == unknown28->getContents(i).unknown00) {
        unknown28->setIndex(i);
        break;
      }
    }
    unknown80->unknown162(unknown28->getContents(unknown28->getIndex(false)).unknown00);
  }
  unknown38 = GfMenuBladeList::create();
  unknown40 = GfMenuBladeList::create();
  updateBladeList();
  {
    ui::UIObjectAcc zone(main.unknown10, "LAY_zone");
    mm::mtl::FixStr<32> name;
// __LINE__ must be 208 as in the original file: it is the line argument of operator new.
#line 208
    ZoneListener *zoneListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ZoneListener(this);
    zoneListener->addRef();
    ui::UIEventManager::get()->registObjectListener(zone.unknown10, zoneListener);
    if (zoneListener != nullptr) {
      zoneListener->release();
    }
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown48 = ui::UISelectObjList::create(createParam);
    }
    for (u32 i = 0; i < unknown28->getSize(); i++) {
      name.format("IMG_zone_sel_flag@%02d", unknown28->getContents(i).unknown00);
      ui::UIObjectAcc flag(zone.unknown10, name.c_str());
      flag.setImageIndex(unknown28->getContents(i).unknown00 - 1);
      name.format("LAY_zone_sel_flag@%02d", unknown28->getContents(i).unknown00);
      unknown48->addObject(zone.searchChild(name.c_str()));
    }
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown60 = ui::UISelectObjList::create(createParam);
    }
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown68 = ui::UISelectObjList::create(createParam);
    }
    {
      mm::Rect<s16> rect;
      zone.getLayoutRect("mnu090_icon_flag_select", rect);
      ui::UICtrlRevolveSelect::RevolveSetting setting;
      setting.unknown02 = 2;
      setting.unknown0c = 500;
      setting.unknown08 = mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2);
      setting.unknown04 = 0.25f;
      setting.unknown18 = 0.0f;
      setting.unknown28 = ui::CURVE_TYPE_SIN90;
      setting.unknown24 = ui::CURVE_TYPE_SIN90;
      setting.unknown03 = 1;
      if (unknown28->getSize() == 7) {
        setting.unknown00 = 360;
      } else if (unknown28->getSize() != 1) {
        // The game converts the angle to an unsigned integer (fcvtzu) before the 16-bit store; a direct float to u16 assignment does not match.
        setting.unknown00 = static_cast<u32>(unknown28->getSize() * 51.42857f);
      }
      unknown50 = ui::UICtrlRevolveSelect::create(zone.unknown10, setting, unknown48);
      if (unknown50 != nullptr) {
        unknown50->setupEventHanding(main.unknown10, 1);
      }
    }
    GfMenuZoneAdapter::createFromReference(zone.searchChild("TXT_zone_info_name"), 0, unknown80, false);
    GfMenuZoneAdapter::createFromReference(zone.searchChild("IMG_zone_info_lv"), 3, unknown80, false);
    {
      ui::UIObjectAcc zoneMer(main.unknown10, "LAY_zone_mer");
      GfMenuGameAdapter::create(zoneMer.searchChild("TXT_zone_info_mer_lv"), 0xb, false);
      {
        ui::UIObjectAcc gauge(zoneMer.unknown10, "IMG_zone_mer_lv_gauge");
        GfMenuGameAdapter::create(gauge.unknown10, 0xc, false);
        gauge.setExtType(1);
        if (GfDataMercenaries::getLevel() == 5) {
          gauge.setAlpha(0.0f);
        }
      }
      GfMenuGameAdapter::create(zoneMer.searchChild("TXT_zone_mer_lv_next_num"), 0xc, false);
      GfMenuGameAdapter::create(zoneMer.searchChild("TXT_zone_mer_lv_next_max"), 0xd, false);
    }
    {
      mm::mtl::FixStr<32> unitName;
      for (u32 i = 0; i < 3; i++) {
        unitName.format("TXT_zone_unit_name@%02d", i + 1);
        GfMenuMercenariesAdapter::create(zone.searchChild(unitName.c_str()), 0, i + 1, false);
        unitName.format("TXT_zone_unit_mission_name@%02d", i + 1);
        GfMenuMercenariesAdapter::create(zone.searchChild(unitName.c_str()), 9, i + 1, false);
        unitName.format("IMG_zone_unit_bl_icon@%02d", i + 1);
        GfMenuMercenariesAdapter::create(zone.searchChild(unitName.c_str()), 1, i + 1, false);
        unitName.format("IMG_zone_unit_flag@%02d", i + 1);
        GfMenuMercenariesAdapter::create(zone.searchChild(unitName.c_str()), 8, i + 1, false);
        unitName.format("TXT_zone_unit_mission_time@%02d", i + 1);
        ui::UIObjectAcc time(zone.unknown10, unitName.c_str());
        GfMenuMercenariesAdapter::create(zone.searchChild(unitName.c_str()), 10, i + 1, true);
        unitName.format("TXT_zone_unit_mission_inf@%02d", i + 1);
        GfMenuObjUtil::createSyncPlugin(zone.searchChild(unitName.c_str()), time.unknown10, 0x40);
        unitName.format("TXT_zone_unit_come_back@%02d", i + 1);
        GfMenuMercenariesAdapter::create(zone.searchChild(unitName.c_str()), 0xb, i + 1, true);
        addDispEventCondition(zone.unknown10, unitName.c_str(), 1, i, false);
      }
    }
    mm::Rect<s16> nonSelectRect;
    zone.getLayoutRect("mnu090_icon_flag_nonselect", nonSelectRect);
    mm::Rect<s16> selectRect;
    zone.getLayoutRect("mnu090_icon_flag_select", selectRect);
    unknown58 = static_cast<f32>(selectRect.width) / static_cast<f32>(nonSelectRect.width) - 1.0f;
    setFSInputObject(0, zone.unknown10);
  }
  {
    ui::UIObjectAcc missionSelect(main.unknown10, "LAY_mis_sel");
    mm::mtl::FixStr<32> name;
    {
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown70 = ui::UISelectObjList::create(createParam);
    }
    unknown70->pickupObject(missionSelect.unknown10, "LAY_mis_sel_item@%02d", 1);
    unknown30 = GfMenuIDList::create();
    updateMissionList();
    GfMenuAdapterManager::beginAddAfter();
    for (u32 i = 0; i < unknown70->getSize(); i++) {
      name.format("TXT_mis_sel_title@%02d", i + 1);
      GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromList(missionSelect.searchChild(name.c_str()), 0, unknown30, i, nullptr, false);
      if (adapter != nullptr) {
        adapter->unknown24 = unknown70->getObject(i);
      }
      name.format("TXT_mis_sel_time@%02d", i + 1);
      ui::UIObjectAcc time(missionSelect.unknown10, name.c_str());
      GfMenuMissionAdapter::createFromList(time.unknown10, 0x23, unknown30, i, nullptr, false);
      name.format("TXT_mis_sel_time_inf@%02d", i + 1);
      GfMenuObjUtil::createSyncPlugin(missionSelect.searchChild(name.c_str()), time.unknown10, 0x40);
      name.format("IMG_mis_sel_icon@%02d", i + 1);
      GfMenuMissionAdapter::createFromList(missionSelect.searchChild(name.c_str()), 2, unknown30, i, nullptr, false);
      name.format("IMG_mis_sel_new@%02d", i + 1);
      GfMenuMissionAdapter::createFromList(missionSelect.searchChild(name.c_str()), 0x1c, unknown30, i, nullptr, true);
    }
    {
      GfMenuObjQuestReward::OpenParam rewardParam;
      rewardParam.unknown10 = unknown88;
      rewardParam.unknown08 = missionSelect.searchChild("LAY_mis_sel_detail_reward");
      rewardParam.unknown0c = 1;
      GfMenuObjQuestReward::create(unknown98, rewardParam, true);
    }
    GfMenuMissionAdapter::createFromReferenceMission(missionSelect.searchChild("TXT_mis_sel_detail_info"), 1, 0, false);
    GfMenuZoneAdapter::createFromReference(missionSelect.searchChild("IMG_mis_sel_detail_flag"), 2, unknown80, false);
    for (u32 i = 0; i < 3; i++) {
      name.format("IMG_mis_sel_cond_icon@%02d", i + 1);
      GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromReferenceMission(missionSelect.searchChild(name.c_str()), 0x12, i, false);
      if (adapter != nullptr) {
        name.format("LAY_mis_sel_cond@%02d", i + 1);
        adapter->unknown24 = missionSelect.searchChild(name.c_str());
      }
      name.format("TXT_mis_sel_cond_txt@%02d", i + 1);
      GfMenuMissionAdapter::createFromReferenceMission(missionSelect.searchChild(name.c_str()), 0x11, i, false);
      u32 text = missionSelect.searchChild(name.c_str());
      if (text != 0) {
        name.format("TXT_mis_sel_cond_val@%02d", i + 1);
        GfMenuObjUtil::createDockPlugin(missionSelect.searchChild(name.c_str()), text, 1, mm::Pnt<s16>(12, 0), 0);
        GfMenuMissionAdapter::createFromReferenceMission(missionSelect.searchChild(name.c_str()), 0x13, i, false);
        name.format("TXT_mis_sel_cond_lv@%02d", i + 1);
        GfMenuObjUtil::createDockPlugin(missionSelect.searchChild(name.c_str()), text, 1, mm::Pnt<s16>(12, 0), 0);
        GfMenuMissionAdapter::createFromReferenceMission(missionSelect.searchChild(name.c_str()), 0x14, i, false);
        name.format("TXT_mis_sel_cond_max@%02d", i + 1);
        GfMenuMissionAdapter::createFromReferenceMission(missionSelect.searchChild(name.c_str()), 0x16, i, false);
      }
    }
    GfMenuAdapterManager::endAddAfter();
    GfMenuObjUtil::createVScrollBarPlugin(missionSelect.searchChild("IMG_mis_sel_scroll_bar"), unknown30, "IMG_mis_sel_scroll_base", true);
// __LINE__ must be 480 as in the original file: it is the line argument of operator new.
#line 480
    MissionListener *missionListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MissionListener(this);
    missionListener->addRef();
    ui::UIEventManager::get()->registObjectListener(missionSelect.unknown10, missionListener);
    if (missionListener != nullptr) {
      missionListener->release();
    }
    setFSInputObject(1, missionSelect.unknown10);
  }
  if (mission == 0) {
    sendOpenEvent(main.searchChild("LAY_zone"), 0);
  } else {
    for (u32 i = 0; i < unknown30->getSize(); i++) {
      if (mission == unknown30->getContents(i).unknown00) {
        unknown30->setIndex(i);
        break;
      }
    }
    unknown80->unknown162(unknown28->getContents(unknown28->getIndex(false)).unknown00);
    unknown88->unknown162(unknown30->getContents(unknown30->getIndex(false)).unknown00);
    unknown90->m_questID = GfDataMercenaries::getMissionQuestID(mission);
    GfMenuReference::setReferenceZoneID(unknown28->getContents(unknown28->getIndex(false)).unknown00);
    GfMenuReference::setReferenceMissionID(unknown30->getContents(unknown30->getIndex(false)).unknown00);
    sendOpenEvent(main.searchChild("LAY_mis_sel"), 0);
  }
  disableFSInput();
// __LINE__ must be 520 as in the original file: it is the line argument of operator new.
#line 520
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjMercenaryTop::sendOpenEvent(u32 handle, int type) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjMercenaryTop::sendCloseEvent(u32 handle, int type) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjMercenaryTop::listenerCtrl(const ui::EventData &event) { ui::UICtrlObject::getEventType(event); }

bool GfMenuObjMercenaryTop::seqExit() {
  if (unknown334 != 0) {
    ui::EventData event;
    event.unknown00 = unknown002;
    sendEvent(unknown334, event, 0.0f);
    unknown334 = 0;
  }
  return true;
}

void GfMenuObjMercenaryTop::updateBladeList() {
  GfMenuBladeList::TeamSetup setup;
  setup.unknown14 = 3;
  setup.m_setupParam.unknown08 = 3;
  setup.unknown1c = false;
  unknown38->clear();
  unknown38->setupFromTeam(setup);
}

void GfMenuObjMercenaryTop::updateTargetTeam() {
  GfMenuReference::setReferenceTeamID(0);
  for (u32 index = 0; index < GfDataMercenaries::getTeamNum(); index++) {
    unknown120 *team = GfDataMercenaries::getTeamByIndex(index);
    if (team != nullptr && GfDataMercenaries::isTeamStateEmpty(team->unknown10)) {
      GfMenuReference::setReferenceTeamID(team->unknown10);
      return;
    }
  }
}

void GfMenuObjMercenaryTop::updateMissionList() {
  u32 zone = unknown80->unknown0c;
  ui::UIListInfoBase::SetupParam param;
  param.unknown08 = unknown70->getSize();
  param.unknown10 = true;
  unknown30->setupMissionListFromZone(param, zone);
  u32 index = 0;
  bool hasOrderOnlyOne = false;
  bool hasOrderMultiple = false;
  GfMenuObjUtil::MissionInfo info;
  for (; index < unknown30->getSize(); index++) {
    if (GfMenuObjUtil::getMissionInfo(unknown30->getContents(index).unknown00, info) && (info.unknown0c & 1)) {
      if (GfDataMercenaries::isOrderOnlyOne(unknown30->getContents(index).unknown00)) {
        hasOrderOnlyOne = true;
      } else {
        hasOrderMultiple = true;
      }
    }
  }
  ui::UIObjectAcc acc(unknown18, "LAY_zone_notice");
  acc.setDisp(hasOrderOnlyOne || hasOrderMultiple);
  if (acc.isDisp()) {
    acc.setDispChild(hasOrderMultiple, "IMG_zone_notice_icon@01");
    if (hasOrderMultiple) {
      unknown68->addObject(acc.searchChild("IMG_zone_notice_icon@01"));
    }
    acc.setDispChild(hasOrderOnlyOne, "IMG_zone_notice_icon@02");
    if (hasOrderOnlyOne) {
      unknown68->addObject(acc.searchChild("IMG_zone_notice_icon@02"));
    }
    mm::Rect<s16> rect;
    acc.getLayoutRect("mnu090_mercenary_icon_categorie", rect);
    mm::Rect<s16> range;
    acc.getLayoutRect("mnu090_mercenary_icon_categorie_range", range);
    GfMenuObjUtil::placeObjectH(unknown68, mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), range.x - rect.x);
    unknown68->clear();
  }
}

void GfMenuObjMercenaryTop::refreshMissionList() {
  ui::UIObjectAcc list(unknown18, "LAY_mis_sel_list");
  if (list.isValid()) {
    mm::mtl::FixStr<32> name;
    for (u32 index = 0; index < unknown70->getSize(); index++) {
      u32 number = index + 1;
      name.format("TXT_mis_sel_title@%02d", number);
      ui::UIObjectAcc title(list.unknown10, name.c_str());
      name.format("TXT_mis_sel_time@%02d", number);
      ui::UIObjectAcc time(list.unknown10, name.c_str());
      name.format("TXT_mis_sel_time_inf@%02d", number);
      ui::UIObjectAcc timeInfo(list.unknown10, name.c_str());
      u32 mission = unknown30->getContents(unknown30->getPageIndex(index)).unknown00;
      if (GfDataMercenaries::isMissionOrderTeam(mission)) {
        GfMenuObjUtil::setColMulandAdd(title.unknown10, "txt_highlight");
        title.setBorderWeight(1.0f);
        time.setBorderWeight(1.0f);
        timeInfo.setBorderWeight(1.0f);
      } else if (mission == 0 || !GfMenuObjUtil::checkMissionCond(mission, unknown38)) {
        GfMenuObjUtil::setColMulandAdd(title.unknown10, "txt_disable");
        title.setBorderWeight(1.0f);
        time.setBorderWeight(1.0f);
        timeInfo.setBorderWeight(1.0f);
      } else {
        GfMenuObjUtil::setColDefault(title.unknown10);
        title.setBorderWeight(-0.5f);
        time.setBorderWeight(-0.5f);
        timeInfo.setBorderWeight(-0.5f);
      }
      if (unknown30->getIndex(true) == index) {
        GfRequestBladeData request = {};
        for (u32 condition = 0; condition < 3; condition++) {
          name.format("TXT_mis_sel_cond_txt@%02d", condition + 1);
          ui::UIObjectAcc text(list.unknown10, name.c_str());
          name.format("IMG_mis_sel_cond_icon@%02d", condition + 1);
          ui::UIObjectAcc icon(list.unknown10, name.c_str());
          if (GfDataMercenaries::getRequestCondition(request, mission, condition) && (request.unknown0c == 0 ? 1 : request.unknown0c) <= GfMenuObjUtil::getMissionCondBladeCount(request, unknown38)) {
            GfMenuObjUtil::setColDefault(text.unknown10);
            icon.setAddColor("mer_cond_ok");
          } else {
            GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_warning");
            icon.setAddColor("mer_cond_ng");
          }
        }
      }
    }
  }
}

bool GfMenuObjMercenaryTop::seqCanNotOrder() {
  bool isEnd;
  if (!unknown330) {
    GfMenuManager::openCommonWindow(unknown003);
    isEnd = false;
    unknown330 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    GfMenuManager::getCommonWindowResult();
    unknown0a0.unknown002(&GfMenuObjMercenaryTop::seqExit);
    isEnd = true;
    unknown330 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjMercenaryTop::seqUnitBreak() {
  bool isEnd;
  if (!unknown330) {
    u32 mission = unknown30->getContents(unknown30->getIndex(false)).unknown00;
    u32 leader = GfDataMercenaries::getTeamLeader(GfDataMercenaries::getTeamIDByMissionID(mission));
    unknown338->reset();
    GfMenuObjCommonText::openMissionStop(unknown338, unknown004, leader);
    isEnd = false;
    unknown330 = true;
  } else if (!unknown338->isActive()) {
    GfMenuCallContext::GfMenuResult result;
    if (unknown338->popResult(result) && result.unknown00 == 0 && result.unknown04 == 0) {
      u32 mission = GfMenuReference::getReferenceMissionID();
      u32 team = GfDataMercenaries::getTeamIDByMissionID(mission);
      GfGameMercenaries::cancelMission(mission);
      GfGameMercenaries::clearTeamMember(team);
      updateTargetTeam();
    }
    unknown0a0.unknown002(&GfMenuObjMercenaryTop::seqExit);
    isEnd = true;
    unknown330 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

void GfMenuObjMercenaryTop::setDispUnitReady(u32 handle, u32 index) {
  ui::UIObjectAcc acc(handle);
  u32 number = index + 1;
  mm::mtl::FixStr<32> name;
  name.format("TXT_zone_unit_name@%02d", number);
  ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(0.0f);
  name.format("TXT_zone_unit_ready@%02d", number);
  acc.setDispChild(true, name.c_str());
  name.format("TXT_zone_unit_mission_name@%02d", number);
  ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(0.0f);
  name.format("TXT_zone_unit_mission_time@%02d", number);
  ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(0.0f);
  name.format("IMG_zone_unit_base@%02d", number);
  GfMenuObjUtil::setChildAddColor(acc.unknown10, name.c_str(), "mer_unit_empty");
  name.format("TXT_zone_unit_mission_inf@%02d", number);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setAlpha(0.0f);
}

void GfMenuObjMercenaryTop::setDispUnitProgress(u32 handle, u32 index) {
  ui::UIObjectAcc acc(handle);
  u32 number = index + 1;
  mm::mtl::FixStr<32> name;
  name.format("TXT_zone_unit_name@%02d", number);
  GfMenuObjUtil::setColDefault(acc.searchChild(name.c_str()));
  ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(1.0f);
  name.format("TXT_zone_unit_ready@%02d", number);
  acc.setDispChild(false, name.c_str());
  name.format("TXT_zone_unit_mission_name@%02d", number);
  GfMenuObjUtil::setColDefault(acc.searchChild(name.c_str()));
  ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(1.0f);
  name.format("TXT_zone_unit_mission_time@%02d", number);
  GfMenuObjUtil::setColDefault(acc.searchChild(name.c_str()));
  name.format("IMG_zone_unit_base@%02d", number);
  GfMenuObjUtil::setColDefault(acc.searchChild(name.c_str()));
  name.format("TXT_zone_unit_mission_inf@%02d", number);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setAlpha(1.0f);
}

void GfMenuObjMercenaryTop::setDispUnitReturn(u32 handle, u32 index) {
  ui::UIObjectAcc acc(handle);
  u32 number = index + 1;
  mm::mtl::FixStr<32> name;
  name.format("TXT_zone_unit_name@%02d", number);
  GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.c_str()), "txt_disable");
  ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(0.5f);
  name.format("TXT_zone_unit_ready@%02d", number);
  acc.setDispChild(false, name.c_str());
  name.format("TXT_zone_unit_mission_name@%02d", number);
  GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.c_str()), "txt_disable");
  ui::UIObjectAcc(acc.searchChild(name.c_str())).setAlpha(0.5f);
  name.format("TXT_zone_unit_mission_time@%02d", number);
  GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.c_str()), "txt_disable");
  name.format("IMG_zone_unit_base@%02d", number);
  GfMenuObjUtil::setChildAddColor(acc.unknown10, name.c_str(), "black");
  name.format("TXT_zone_unit_mission_inf@%02d", number);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setAlpha(0.0f);
}

void GfMenuObjMercenaryTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryTop::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjMercenaryTop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 0;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case 2:
  case GfMenuTypes::unknown003_34:
    if (!m_menuObjMercenaryTop->unknown340) {
      acc.setTerm();
    } else {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      param.unknown04 = 1;
      param.unknown00 = 6;
      param.unknown0c = true;
      GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    }
    break;
  case 0x24: {
    GfMenuObject::disableInput(acc.searchChild("LAY_zone"));
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    m_menuObjMercenaryTop->unknown340 = false;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Role: sends the open event (type GfMenuTypes::unknown003_33, param 1) of the mission selection to the sibling layer "LAY_mis_sel" of the accessor, or to "LAY_main" of the owner when there is none.
// Its user is ZoneListener::reciveEvent case 8 (0x710049c920, 699 instructions). Forms tried without the helper (measured with check on the unit): the member sendOpenEvent
// (`sendOpenEvent(acc.searchSibiling("LAY_mis_sel"), 1)`) gives 699 instructions with 5 lines differing at +0x258 (0x710049cb78: the game stores unknown00 first, sendOpenEvent stores it
// last); written in the case, the accessor as a temporary of the `if` gives 699 with 75 lines differing from +0x1c (0x710049c93c: a markerless slot of its own), the accessor as a named
// local 701 (256 lines), the event declared before the target 699 (84 lines), `?:` for the target 702 (318 lines). With the helper the temporary gets the lifetime markers of the inliner
// and the slots are the game's.
static void openMissionSelect(ui::UIObjectAcc &acc, GfMenuObjMercenaryTop *top) {
  u32 target = acc.searchSibiling("LAY_mis_sel");
  if (target == 0) {
    target = ui::UIObjectAcc(top->unknown18, "LAY_main").unknown10;
  }
  ui::EventData openEvent;
  openEvent.unknown00 = GfMenuTypes::unknown003_33;
  openEvent.unknown0c = 0;
  openEvent.unknown08 = 1;
  GfMenuObject::sendEvent(target, openEvent, 0.0f);
}

void GfMenuObjMercenaryTop::ZoneListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown0c = 0;
    acc.setDisp(false);
    break;
  case 2:
    if (unknown0c == 1) {
      GfMenuObjMercenaryRoot::openBg(m_menuObjMercenaryTop->unknown28->getContents(m_menuObjMercenaryTop->unknown28->getIndex(false)).unknown00);
    }
    GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    acc.setTerm();
    break;
  // Not a duplicated block: the text shared with other listeners is the end of case 3 and the start of case 6, and a case label cannot be in a helper. A helper holding the four calls of
  // case 3 gives 699 instructions with 0 differing lines but has this single user in the file (MissionListener's case 3 differs), so it is not used.
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObjMainMenu2::setSystemKeyEnable(true);
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      GfMenuObject::enableFSInput(0);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    if (index != 0xffffffff) {
      mm::mtl::FixStr<32> name;
      if (previous != 0xffffffff) {
        u32 zone = m_menuObjMercenaryTop->unknown28->getContents(previous).unknown00;
        name.format("IMG_zone_sel_flag@%02d", zone);
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x80000000;
        param.unknown00 = 0.25f;
        GfMenuObjUtil::startCtrl(m_menuObjMercenaryTop->unknown48->getObject(previous), param, name.c_str());
        name.format("LAY_zone_sel_flag_notice@%02d", zone);
        GfMenuObjUtil::setChildDisp(m_menuObjMercenaryTop->unknown48->getSelectObject(), name.c_str(), true);
      }
      m_menuObjMercenaryTop->unknown28->setIndex(index);
      m_menuObjMercenaryTop->unknown48->setIndex(index);
      u32 zone = m_menuObjMercenaryTop->unknown28->getContents(m_menuObjMercenaryTop->unknown28->getIndex(false)).unknown00;
      name.format("IMG_zone_sel_flag@%02d", zone);
      GfMenuObjUtil::CtrlParam param;
      param.unknown2c = 1.0f;
      param.unknown08 = 0x4080000;
      param.unknown40_col3 = GfMenuObjUtil::getPresetColor("mer_flag_sel");
      param.unknown14 = 4;
      param.unknown00 = 0.25f;
      GfMenuObjUtil::startCtrl(m_menuObjMercenaryTop->unknown48->getSelectObject(), param, name.c_str());
      name.format("LAY_zone_sel_flag_notice@%02d", zone);
      GfMenuObjUtil::setChildDisp(m_menuObjMercenaryTop->unknown48->getSelectObject(), name.c_str(), false);
      m_menuObjMercenaryTop->unknown80->unknown162(m_menuObjMercenaryTop->unknown28->getContents(m_menuObjMercenaryTop->unknown28->getIndex(false)).unknown00);
      m_menuObjMercenaryTop->updateMissionList();
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonTab();
      }
    }
    GfMenuObject::releaseTimer(acc.unknown10);
    GfMenuObject::registTimer(acc.unknown10, 1, 0.5f, false);
    unknown0c = 1;
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      // Written out like the fade out blocks of the sibling listeners (ruling 8): GfMenuObjUtil::unknown003(acc.unknown10) gives 699 instructions with 9 lines differing from +0x1d8 (0x710049caf8).
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown00 = 6;
      param.unknown04 = 1;
      param.unknown10 = 2;
      GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      GfMenuObject::disableFSInput();
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      openMissionSelect(acc, m_menuObjMercenaryTop);
      m_menuObjMercenaryTop->updateMissionList();
      GfMenuReference::setReferenceZoneID(m_menuObjMercenaryTop->unknown28->getContents(m_menuObjMercenaryTop->unknown28->getIndex(false)).unknown00);
      GfMenuObjMainMenu2::setSystemKeyEnable(false);
      GfMenuObjUtil::playSECommonDecide();
    }
    break;
  case 0xb:
    GfMenuObjMercenaryRoot::openBg(m_menuObjMercenaryTop->unknown28->getContents(m_menuObjMercenaryTop->unknown28->getIndex(false)).unknown00);
    unknown0c = 0;
    break;
  case 0xd:
    if (event.unknown0c == 1) {
      u32 index = event.unknown10;
      if (event.unknown08 == 5) {
        setDispUnitReturn(acc.unknown10, index);
      } else if (GfDataMercenaries::getTeamMission(index + 1) == 0) {
        setDispUnitReady(acc.unknown10, index);
      } else {
        setDispUnitProgress(acc.unknown10, index);
      }
    }
    break;
  case 0xe:
    if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
      ui::UICtrlObject::getEventType(event);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    mm::mtl::FixStr<32> name;
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_menuObjMercenaryTop->unknown28);
    acc.setDispChild(m_menuObjMercenaryTop->unknown28->getSize() > 1, "LAY_zone_sel_arrow");
    // Written out like the fade in blocks of the sibling listeners (ruling 8): GfMenuObjUtil::unknown002(acc.unknown10) gives 699 instructions with 132 lines differing from +0x1c (0x710049c93c).
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    for (u32 i = 0; i < m_menuObjMercenaryTop->unknown28->getSize(); i++) {
      mm::mtl::FixedVector<u16, 500> missions;
      GfGameMercenaries::getZoneMission(missions, m_menuObjMercenaryTop->unknown28->getContents(i).unknown00);
      bool isNew = false;
      for (u32 j = 0; j < missions.size(); j++) {
        if (GfDataMercenaries::isNewMission(missions[j])) {
          isNew = true;
          break;
        }
      }
      name.format("IMG_zone_sel_flag_notice@%02d", m_menuObjMercenaryTop->unknown28->getContents(i).unknown00);
      acc.setDispChild(isNew, name.c_str());
    }
    if (GfDataMercenaries::getTeamMax() == 0) {
      acc.setDispChild(false, "LAY_zone_unit");
    } else {
      u32 count = acc.countChild("LAY_zone_unit@%02d", 1);
      acc.setDispChild(true, "LAY_zone_unit");
      m_menuObjMercenaryTop->unknown60->clear();
      for (u32 i = 0; i < count; i++) {
        bool isActive = i < GfDataMercenaries::getTeamMax();
        u32 number = i + 1;
        name.format("LAY_zone_unit@%02d", number);
        acc.setDispChild(isActive, name.c_str());
        if (isActive) {
          m_menuObjMercenaryTop->unknown60->addObject(acc.searchChild(name.c_str()));
          u32 mission = GfDataMercenaries::getTeamMission(number);
          if (mission == 0 || !GfDataMercenaries::isMissionOrderTeam(mission)) {
            setDispUnitReady(acc.searchChild(name.c_str()), i);
          } else {
            // The flag places the call before the search of the unit layer (inlined into the test: 702 instructions, 114 lines differ from +0x6c).
            bool isReward = GfDataMercenaries::isTeamStateReward(number);
            u32 unit = acc.searchChild(name.c_str());
            if (!isReward) {
              setDispUnitProgress(unit, i);
            } else {
              setDispUnitReturn(unit, i);
            }
          }
        }
      }
      // Written out like updateMissionList (ruling 8): a file-local helper taking the accessor, the list and both layout names (also as `static inline`) gives 700 instructions against the game's 699
      // here (209 lines differ, first difference at +0x2c, 0x710049c94c) and 188 against 187 in updateMissionList (33 lines differ, first difference at +0x50, 0x710049bbc4).
      mm::Rect<s16> rect;
      acc.getLayoutRect("mercenary_condition_2", rect);
      mm::Rect<s16> next;
      acc.getLayoutRect("mercenary_condition_3", next);
      GfMenuObjUtil::placeObjectH(m_menuObjMercenaryTop->unknown60, mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.x - rect.x);
    }
    GfMenuObjOperationInfo::setGuideText(7, 0);
    GfMenuObjOperationInfo::setGuideDisp(true);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaryTop::MissionListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 2:
    if (acc.isDisp()) {
      GfDataMercenaries::clearNewMission(m_menuObjMercenaryTop->unknown30->getContents(m_menuObjMercenaryTop->unknown30->getIndex(false)).unknown00);
    }
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      GfMenuObject::enableFSInput(1);
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    if (index != 0xffffffff) {
      mm::mtl::FixStr<32> name;
      // The locals of the previous and the new slot place their calls before and after the setIndex calls (inlined into the formats: 558 instructions).
      u32 previousSlot = m_menuObjMercenaryTop->unknown70->getIndex(false);
      m_menuObjMercenaryTop->unknown30->setIndex(index);
      m_menuObjMercenaryTop->unknown70->setIndex(m_menuObjMercenaryTop->unknown30->getIndex(true));
      u32 slot = m_menuObjMercenaryTop->unknown70->getIndex(false);
      u32 mission = m_menuObjMercenaryTop->unknown30->getContents(m_menuObjMercenaryTop->unknown30->getIndex(false)).unknown00;
      m_menuObjMercenaryTop->unknown88->unknown162(mission);
      m_menuObjMercenaryTop->unknown90->m_questID = GfDataMercenaries::getMissionQuestID(mission);
      GfMenuObjQuestReward::open(m_menuObjMercenaryTop->unknown98, false);
      GfMenuReference::setReferenceMissionID(mission);
      if (previous != 0xffffffff) {
        name.format("IMG_mis_sel_item_base@%02d", previousSlot + 1);
        ui::UIObjectAcc item(acc.unknown10, name.c_str());
        item.loadDefColor();
        GfDataMercenaries::clearNewMission(m_menuObjMercenaryTop->unknown30->getContents(previous).unknown00);
      }
      name.format("IMG_mis_sel_item_base@%02d", slot + 1);
      ui::UIObjectAcc item(acc.unknown10, name.c_str());
      item.setMulColor("black");
      item.setAddColor("sys_select");
      m_menuObjMercenaryTop->refreshMissionList();
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    break;
  }
  case 0x21:
    if (event.unknown08 == 1) {
      m_menuObjMercenaryTop->unknown30->setIndex(0);
    }
    if (m_menuObjMercenaryTop->unknown30->getSize() != 0) {
      GfMenuObject::resetInputSelection(acc.unknown10);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *m_menuObjMercenaryTop->unknown30);
    }
    // The `int ctrl` local is the game's (the `{}` keeps it out of the later case labels): hooked straight from the call it gives 560 instructions (131 lines differ from +0x44, 0x710049d458).
    {
      int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_mis_sel_list"), 1, 1);
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    }
    GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_mis_sel_detail"), 1, 2);
    acc.setDisp(true);
    GfMenuObjOperationInfo::setGuideText(0x24, 0);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    break;
  case 8:
    if (event.unknown0c == 1) {
      u32 mission = m_menuObjMercenaryTop->unknown30->getContents(m_menuObjMercenaryTop->unknown30->getIndex(false)).unknown00;
      GfDataMercenaries::clearNewMission(mission);
      if (GfDataMercenaries::isMissionOrderTeam(mission)) {
        m_menuObjMercenaryTop->unknown334 = acc.unknown10;
        m_menuObjMercenaryTop->unknown0a0.unknown005();
        m_menuObjMercenaryTop->unknown0a0.unknown002(&GfMenuObjMercenaryTop::seqUnitBreak);
        GfMenuObject::disableFSInput();
      } else {
        if (GfDataMercenaries::isOrderOnlyOne(mission) && GfDataMercenaries::isMissionCompleteFlag(mission)) {
          GfMenuManager::openCommonWindow(0xce);
          break;
        }
        if (GfMenuObjUtil::checkMissionCond(mission, m_menuObjMercenaryTop->unknown38)) {
          if (!GfDataMercenaries::isValidTeamID(GfMenuReference::getReferenceTeamID())) {
            GfMenuManager::openCommonWindow(0xaa);
          } else {
            OpenParam param;
            param.unknown00 = GfMenuReference::getReferenceMissionID();
            registOpenParam(param);
            GfMenuObject::changeFSSubLayer(acc.unknown10, 2, 0x35, true);
            GfMenuObjUtil::playSECommonDecide();
          }
          break;
        }
        m_menuObjMercenaryTop->unknown334 = acc.unknown10;
        m_menuObjMercenaryTop->unknown0a0.unknown005();
        m_menuObjMercenaryTop->unknown0a0.unknown002(&GfMenuObjMercenaryTop::seqCanNotOrder);
        GfMenuObject::disableFSInput();
      }
    } else if (event.unknown0c == 2) {
      m_menuObjMercenaryTop->sendOpenEvent(acc.searchSibiling("LAY_zone"), 0);
      GfDataMercenaries::clearNewMission(m_menuObjMercenaryTop->unknown30->getContents(m_menuObjMercenaryTop->unknown30->getIndex(false)).unknown00);
      GfMenuObjUtil::playSECommonCancel();
      mm::mtl::FixStr<32> name;
      name.format("IMG_mis_sel_item_base@%02d", m_menuObjMercenaryTop->unknown30->getIndex(true) + 1);
      // The `{}` around the accessor and the `int ctrl` local are the game's: without the scope 557 instructions (82 lines differ from +0x64), without the local 560 (45 lines).
      {
        ui::UIObjectAcc item(acc.unknown10, name.c_str());
        item.loadDefColor();
      }
      int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_mis_sel_list"), 2, 1);
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
      GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_mis_sel_detail"), 1, 2);
      GfMenuObject::disableFSInput();
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
    }
    break;
  case 0x100:
    m_menuObjMercenaryTop->updateBladeList();
    m_menuObjMercenaryTop->refreshMissionList();
    GfMenuObject::enableFSInput(1);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaryTop>(const mm::mtl::Delegate<bool()> *);
