#include "gf/menu/object/gf_menu_obj_mercenaries.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "gf/menu/list/gf_menu_mission_list.h"
#include "gf/menu/list/gf_menu_team_list.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: mission adapter type of each condition type; original name unknown.
static const u32 unknown001[4] = {21, 19, 21, 21};

// Inferred role: sends the open event to a layer of a screen; original name unknown.
static void unknown002(u32 handle, const char *layer) {
  ui::UIObjectAcc root(handle);
  unknown164(root.searchChild(layer), GfMenuTypes::unknown003_33);
}

GfMenuObjMercenaries::GfMenuObjMercenaries(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr),
      unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(nullptr), unknown90(nullptr), unknown98(0), unknown9c(1), unknown9e(0), unknowna0(0), unknown0a8(nullptr),
      unknown0b0(nullptr), unknown0b8(nullptr), unknown0e8(this), unknown388(0) {
  unknown0c0 = nullptr;
  unknown0c8 = nullptr;
  unknown0d0 = 0;
  unknown0d8 = 0;
  unknown0e0 = 0;
}

GfMenuObjMercenaries::~GfMenuObjMercenaries() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown88);
  mm::mtl::safeRelease(unknown90);
  mm::mtl::safeRelease(unknown0a8);
  mm::mtl::safeRelease(unknown0b0);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown0b8);
  mm::mtl::safeRelease(unknown0c0);
  mm::mtl::safeRelease(unknown0c8);
  unknown380 = nullptr;
}

void GfMenuObjMercenaries::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaries::update() {
  unknown0e8.unknown003();
  GfMenuObject::update();
}

void GfMenuObjMercenaries::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjMercenaries::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 5, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjMercenaries::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 6, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjMercenaries::setupLocationSelect(ui::UIObjectAcc &acc) { GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_loc_select_name"), 0, false); }

void GfMenuObjMercenaries::setupLocationZone(ui::UIObjectAcc &acc, u16 zone) {
  GfMenuZoneAdapter::create(acc.searchChild("IMG_loc_flag_logo"), 2, zone, false);
  GfMenuZoneAdapter::create(acc.searchChild("IMG_loc_flag_dev_lv"), 3, zone, false);
  GfMenuZoneAdapter::create(acc.searchChild("LAY_loc_flag_notice"), 5, zone, false);
}

void GfMenuObjMercenaries::setupMission(ui::UIObjectAcc &acc) {
  GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_mis_location"), 0, false);
  GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_mis_flag_logo"), 2, false);
  GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_mis_flag_dev_lv"), 3, false);
}

void GfMenuObjMercenaries::setupMercenaries(ui::UIObjectAcc &acc) {
  GfMenuGameAdapter::create(acc.searchChild("TXT_root_mer_lv_num"), 0xb, false);
  ui::UIObjectAcc exp(acc.searchChild("IMG_root_mer_exp"));
  exp.setExtType(1);
  GfMenuGameAdapter::create(exp.unknown10, 0xc, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("TXT_root_select_unit_name"), 0, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("IMG_root_select_unit_symbol"), 2, false);
}

void GfMenuObjMercenaries::updateTeamList(GfMenuTeamList *list) {
  GfMenuTeamList::TeamSetup setup;
  setup.param.unknown08 = 3;
  list->clear();
  list->setupFromMercenaries(setup);
}

void GfMenuObjMercenaries::updateMissionList(GfMenuMissionList *list, u16 zone) {
  GfMenuMissionList::MissionSetup setup;
  setup.unknown00.unknown08 = 6;
  setup.unknown14 = zone;
  list->clear();
  list->setupFromZone(setup);
}

void GfMenuObjMercenaries::updateBladeListReserver(GfMenuBladeList *list) {
  GfMenuBladeList::TeamSetup setup;
  setup.unknown14 = 3;
  setup.unknown00.unknown08 = 3;
  list->clear();
  list->setupFromTeam(setup);
}

void GfMenuObjMercenaries::updateBladeList(GfMenuBladeList *list, u32 team) {
  GfMenuBladeList::TeamSetup setup;
  setup.unknown00.unknown08 = 6;
  setup.unknown18 = team;
  if (list != nullptr) {
    list->clear();
    list->setupFromTeam(setup);
  }
}

void GfMenuObjMercenaries::updateFieldSkillList(GfMenuFieldSkillList *list, const GfMenuBladeList *blades) {
  if (list != nullptr && blades != nullptr) {
    list->clear();
    list->addFieldSkillFromBladeList(blades);
  }
}

void GfMenuObjMercenaries::moveFieldSkillEnd(ui::UIObjectAcc &acc, u32 mission, u32 index) {
  mm::mtl::FixStr<32> name;
  GfMenuObjUtil::CtrlParam param;
  if (isExistFieldSkill(mission, index)) {
    name.format("IMG_fs_act_bg@%02d", index + 1);
    ui::UIObjectAcc background(acc.searchChild(name.c_str()));
    param.unknown08 = 1;
    param.unknown00 = 0.2f;
    GfMenuObjUtil::startCtrl(background.unknown10, param, nullptr);
  }
  if (index > 1 || GfDataMercenaries::getFieldSkill(mission, index + 1) == 0) {
    ui::UIObjectAcc fieldSkillIndex(acc.searchChild("LAY_fs_act_index"));
    param.unknown08 = 0x200001;
    param.unknown00 = 0.2f;
    GfMenuObjUtil::startCtrl(fieldSkillIndex.unknown10, param, nullptr);
  }
}

void GfMenuObjMercenaries::setupMercenariesCondParam(ui::UIObjectAcc &acc, int index, u32 type, const char *adapterFormat, const char *iconFormat) {
  mm::mtl::FixStr<32> name;
  u32 adapterType = 0x13;
  int slot = type - 1;
  if (slot >= 0 && slot < 4) {
    adapterType = unknown001[slot];
  }
  name.format(adapterFormat, index + 1);
  GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), adapterType, 0, false);
  adapter->unknown70 = index;
  adapter->unknown64 = type;
  name.format(iconFormat, index + 1);
  adapter->unknown24 = acc.searchChild(name.c_str());
}

bool GfMenuObjMercenaries::seqRewardStart() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_complete", false);
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_result", false);
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_notice", false);
  GfMenuFade::setFade(2, 30, mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  return true;
}

bool GfMenuObjMercenaries::seqRewardStart2() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuFade::isFading(2)) {
    isEnd = false;
  } else {
    reward.setDisp(true);
    reward.setAlpha(1.0f);
    GfMenuObjUtil::setChildDisp(handle, "LAY_reward_notice", true);
    ui::UIObjectAcc notice(handle, "LAY_reward_notice");
    notice.setAlpha(1.0f);
    GfMenuFade::setFade(2, 20, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardStart3() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuFade::isFading(2)) {
    isEnd = false;
  } else {
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    enableInput(handle);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp2() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    GfMenuObjUtil::CtrlParam param;
    ui::UIObjectAcc complete(unknown18, "LAY_reward_complete");
    param.unknown08 = 0x80000;
    param.unknown0c = 1;
    param.unknown00 = 0.4f;
    param.unknown2c = 1.0f;
    unknown378 = GfMenuObjUtil::startCtrl(complete.unknown10, param, nullptr);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp3() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    ui::UIObjectAcc complete(unknown18, "LAY_reward_complete");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0;
    param.unknown00 = 0.5f;
    unknown378 = GfMenuObjUtil::startCtrl(complete.unknown10, param, nullptr);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp4() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    GfMenuObjUtil::CtrlParam param;
    ui::UIObjectAcc notice(unknown18, "LAY_reward_notice");
    param.unknown08 = 2;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(notice.unknown10, param, nullptr);
    GfMenuObjUtil::setChildDisp(handle, "LAY_reward_result", true);
    ui::UIObjectAcc result(unknown18, "LAY_reward_result");
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    unknown378 = GfMenuObjUtil::startCtrl(result.unknown10, param, nullptr);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp5() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    enableInput(handle);
    isEnd = true;
  }
  return isEnd;
}

void GfMenuObjMercenaries::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuTypes::Param param;
    u32 mission;
    if (!GfMenuObject::getFSLayerParam(unknown20->unknown20, param)) {
      unknown20->unknowna0 = 0;
      GfMenuReference::setReferenceTeamID(1);
      mission = 0;
    } else {
      mission = param.get<u32>();
      unknown20->unknowna0 = 1;
      GfMenuObject::removeFSLayerParam(unknown20->unknown20);
    }
    if (unknown20->unknowna0 != 1) {
      ui::EventData update;
      update.unknown00 = GfMenuTypes::unknown003_260;
      ui::UIManager::get()->requestObjectEvent(handle, update, 0.0f);
      break;
    }
    u32 team = GfMenuReference::getReferenceTeamID();
    GfMenuReference::setReferenceMissionID(mission);
    if (GfMenuReference::getReferenceTeamID() == 0) {
      unknown002(handle, "LAY_mission");
    } else if (!isInvokeFieldSkill(mission, team)) {
      unknown002(handle, "LAY_form");
    } else {
      unknown002(handle, "LAY_fs_activate");
    }
    break;
  }
  case 2:
    GfMenuObject::termCallContext(handle);
    GfMenuObjOperationInfo::close();
    acc.setDisp(false);
    acc.setTerm();
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::returnFSSubLayer(handle, 1);
    break;
  case GfMenuTypes::unknown003_260: {
    u32 team = GfMenuReference::getReferenceTeamID();
    while (true) {
      if (team > GfDataMercenaries::getTeamNum()) {
        updateTeamList(unknown20->unknown70);
        unknown002(unknown20->unknown18, "LAY_location");
        break;
      }
      if (GfDataMercenaries::isTeamStateReward(team)) {
        GfMenuReference::setReferenceMissionID(GfDataMercenaries::getTeamMission(team));
        GfMenuReference::setReferenceTeamID(team);
        unknown002(unknown20->unknown18, "LAY_reward");
        break;
      }
      team++;
    }
    break;
  }
  default:
    break;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaries>(const mm::mtl::Delegate<bool()> *);
