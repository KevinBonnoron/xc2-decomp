#include "gf/menu/object/gf_menu_obj_mercenary_top.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
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
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
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
  setup.unknown00.unknown08 = 3;
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
    if (!unknown20->unknown340) {
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
    unknown20->unknown340 = false;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaryTop>(const mm::mtl::Delegate<bool()> *);
