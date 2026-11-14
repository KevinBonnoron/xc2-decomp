#include "gf/menu/object/gf_menu_obj_mercenaries.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
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
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_dock_plugin.h"
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

// Inferred role: sends the close event to a layer of a screen; original name unknown.
static void unknown003(u32 handle, const char *layer) {
  ui::UIObjectAcc root(handle);
  unknown164(root.searchChild(layer), GfMenuTypes::unknown003_34);
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

void GfMenuObjMercenaries::setupLocation(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  for (int i = 1; i <= 10; i++) {
    name.format("IMG_loc_unit_state_icon@%02d", i);
    GfMenuZoneAdapter *adapter = GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild(name.c_str()), 4, true);
    adapter->unknown5c = i;
  }
  GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_loc_info_notice_icon"), 5, false);
  GfMenuZoneAdapter *adapter = GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_loc_info_notice_txt@01"), 6, false);
  adapter->unknown5c = 1;
  adapter->unknown24 = acc.searchChild("LAY_loc_info_notice@01");
  adapter = GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_loc_info_notice_txt@02"), 6, false);
  adapter->unknown5c = 2;
  adapter->unknown24 = acc.searchChild("LAY_loc_info_notice@02");
}

void GfMenuObjMercenaries::setupMissionList(ui::UIObjectAcc &acc, GfMenuMissionList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 6; i++) {
    name.format("IMG_mis_win@%02d", i + 1);
    GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 7, list, i, false);
    adapter->unknown70 = 1;
    name.format("IMG_mis_status_bg@%02d", i + 1);
    adapter = GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 7, list, i, false);
    adapter->unknown70 = 0;
    name.format("IMG_mis_unit_symbol@%02d", i + 1);
    adapter = GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 7, list, i, false);
    adapter->unknown70 = 2;
    name.format("TXT_mis_status@%02d", i + 1);
    GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 6, list, i, false);
    name.format("IMG_mis_unit_symbol@%02d", i + 1);
    GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 0x1a, list, i, false);
    name.format("IMG_mis_party_symbol@%02d", i + 1);
    GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 0x1b, list, i, false);
    name.format("IMG_mis_type_icon@%02d", i + 1);
    GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 2, list, i, false);
    name.format("TXT_mis_title@%02d", i + 1);
    GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 0, list, i, false);
    name.format("TXT_mis_rest_time@%02d", i + 1);
    GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 4, list, i, false);
    name.format("TXT_mis_new@%02d", i + 1);
    GfMenuMissionAdapter::createFromMissionList(acc.searchChild(name.c_str()), 0x1d, list, i, false);
  }
}

void GfMenuObjMercenaries::setupMissionFieldSkill(ui::UIObjectAcc &acc, const GfMenuBladeList *blades) {
  mm::mtl::FixStr<32> name;
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("TXT_fs_act_unit_name"), 0, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("IMG_fs_act_unit_symbol"), 2, false);
  for (u32 i = 0; i < 3; i++) {
    name.format("TXT_fs_act_name@%02d", i + 1);
    GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x10, i, false);
    name.format("IMG_fs_act_name_bg@%02d", i + 1);
    GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x20, i, false);
    name.format("LAY_fs_act@%02d", i + 1);
    GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x1f, i, false);
    name.format("IMG_fs_act_bg@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    for (int j = 0; j < 6; j++) {
      name.format("IMG_fs_act_blade_face@%02d%02d", j + 1, i + 1);
      GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, blades, j, false);
      adapter = GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x22, i, false);
      adapter->unknown60 = j;
      name.format("TXT_fs_act_blade_fs_lv@%02d%02d", j + 1, i + 1);
      adapter = GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x21, i, false);
      adapter->unknown60 = j;
    }
  }
  name.format("TXT_fs_act_time@%02d", 1);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x23, 0, false);
  name.format("TXT_fs_act_time@%02d", 2);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x24, 0, false);
}

void GfMenuObjMercenaries::setupFormBladeSelect(ui::UIObjectAcc &acc, const GfMenuBladeList *blades) {
  for (int i = 0; i < 6; i++) {
    mm::mtl::FixStr<32> name;
    name.format("LAY_form_bl_name@%02d", i + 1);
    ui::UIObjectAcc bladeName(acc.searchChild(name.c_str()));
    name.format("TXT_form_bl_name_sel@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(bladeName.searchChild(name.c_str()), 2, blades, i, false);
    name.format("TXT_form_bl_name_def@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(bladeName.searchChild(name.c_str()), 2, blades, i, false);
    name.format("LAY_form_bl_plate@%02d", i + 1);
    ui::UIObjectAcc plate(acc.searchChild(name.c_str()));
    mm::Rect<s16> rect;
    bladeName.getRect(rect, 2);
    ui::UIObjectDockPlugin *plugin = ui::UIObjectDockPlugin::create(bladeName.unknown10, 0, rect.height, plate.unknown10);
    plugin->unknown24 = 2;
    mm::mtl::safeRelease(plugin);
    name.format("IMG_form_bl_elem@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(plate.searchChild(name.c_str()), 0x38, blades, i, false);
    name.format("IMG_form_bl_bustup@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(plate.searchChild(name.c_str()), 0x36, blades, i, false);
    name.format("IMG_form_bl_st_wpn@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(plate.searchChild(name.c_str()), 0x29, blades, i, false);
    name.format("TXT_form_bl_st_pow_num@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(plate.searchChild(name.c_str()), 0x37, blades, i, false);
    name.format("IMG_form_bl_st_gen@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(plate.searchChild(name.c_str()), 0x3b, blades, i, false);
  }
}

void GfMenuObjMercenaries::setupReward(ui::UIObjectAcc &acc, const GfMenuBladeList *blades) {
  mm::mtl::FixStr<32> name;
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("TXT_reward_unit_info_name"), 0, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("IMG_reward_unit_info_symbol"), 2, false);
  for (int i = 0; i < 6; i++) {
    name.format("IMG_reward_bl@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, blades, i, false);
  }
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_reward_notice_location"), 0xb, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_reward_notice_mis_title"), 0, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_rwd_money_num"), 8, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_rwd_money_bonus_num"), 9, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_rwd_exp_num"), 10, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_rwd_dev_location"), 0xb, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_rwd_dev_point_num"), 0xc, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_rwd_dev_bonus_num"), 0xd, 0, false);
  for (u32 i = 0; i < 4; i++) {
    name.format("TXT_rwd_item_name@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0, i, false);
    name.format("LAY_rwd_item@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    name.format("TXT_rwd_item_num@%02d", i + 1);
    GfMenuItemAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 3, i, false);
  }
}

void GfMenuObjMercenaries::setupMissionDetail(ui::UIObjectAcc &acc, GfMenuBladeList *blades, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) {
  mm::mtl::FixStr<32> name;
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_mis_detail_index_title"), 0, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("IMG_mis_detail_index_icon"), 2, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_mis_detail_body"), 1, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_mis_detail_time"), 0x23, 0, false);
  for (u32 i = 0; i < 3; i++) {
    name.format("TXT_mis_detail_fs@%02d", i + 1);
    GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x10, i, false);
  }
  for (u32 i = 0; i < 3; i++) {
    name.format("TXT_mis_detail_cond@%02d", i + 1);
    GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x11, i, false);
    name.format("LAY_mis_detail_cond@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    name.format("IMG_mis_detail_cond_type@%02d", i + 1);
    GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x12, i, false);
    name.format("IMG_mis_detail_cond_check@%02d", i + 1);
    adapter = GfMenuMissionAdapter::createFromReferenceMissionBladeList(acc.searchChild(name.c_str()), 0x18, i, blades, true);
    adapter->unknown70 = i;
    name.format("TXT_mis_detail_cond_num@%02d", i + 1);
    adapter = GfMenuMissionAdapter::createFromReferenceMissionBladeList(acc.searchChild(name.c_str()), 0x17, i, blades, true);
    adapter->unknown70 = i;
    name.format("TXT_mis_detail_cond_max@%02d", i + 1);
    GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0x16, i, false);
    setupMercenariesCondParam(acc, i, 1, "IMG_mer_detail_cond_wpn@%02d", "LAY_mer_detail_cond_wpn@%02d");
    setupMercenariesCondParam(acc, i, 2, "TXT_mer_detail_cond_pow@%02d", "LAY_mer_detail_cond_pow@%02d");
    setupMercenariesCondParam(acc, i, 3, "IMG_mer_detail_cond_type@%02d", "LAY_mer_detail_cond_type@%02d");
    setupMercenariesCondParam(acc, i, 4, "IMG_mer_detail_cond_gen@%02d", "LAY_mer_detail_cond_gen@%02d");
    setupMercenariesCondParam(acc, i, 5, "TXT_mer_detail_cond_arts_lv@%02d", "LAY_mer_detail_cond_arts@%02d");
    setupMercenariesCondParam(acc, i, 6, "TXT_mer_detail_cond_arts_lv@%02d", "LAY_mer_detail_cond_arts@%02d");
  }
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_mis_detail_reward_money"), 8, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_mis_detail_reward_dev"), 0xc, 0, false);
  GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_mis_detail_reward_exp"), 10, 0, false);
  for (u32 i = 0; i < 4; i++) {
    name.format("TXT_mis_detail_reward_item@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 0, i, false);
    name.format("LAY_mis_detail_reward_item@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    name.format("IMG_mis_detail_reward_item_i@%02d", i + 1);
    GfMenuItemAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 1, i, false);
    name.format("TXT_mis_detail_reward_item_n@%02d", i + 1);
    GfMenuItemAdapter::createFromReferenceMission(acc.searchChild(name.c_str()), 3, i, false);
  }
  GfMenuReferenceAdapter::create(acc.searchChild("IMG_mis_detail_btn"), number, false);
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

bool GfMenuObjMercenaries::seqRewardComp() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_complete", true);
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_result", false);
  ui::UIObjectAcc complete(unknown18, "LAY_reward_complete");
  complete.setScale(mm::Vec2(2.0f, 2.0f));
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0;
  param.unknown00 = 0.5f;
  unknown378 = GfMenuObjUtil::startCtrl(complete.unknown10, param, nullptr);
  disableInput(handle);
  return true;
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

void GfMenuObjMercenaries::LocationSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuReference::setReferenceZoneID(1);
    GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_loc_select_name"), 0, false);
    GfMenuObject::migrateInput(acc.searchChild("LAY_loc_select_input"), handle);
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 6:
    unknown20->unknown40->setIndex(event.unknown08);
    GfMenuReference::setReferenceZoneID(event.unknown08 + 1);
    break;
  case GfMenuTypes::unknown003_33:
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown40);
    GfMenuObject::enableInput(handle);
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    break;
  }
}

void GfMenuObjMercenaries::MissionFieldSkillListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMissionFieldSkill(acc, unknown20->unknown50);
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3: {
    int type = event.unknown08;
    if (type != 0) {
      u32 mission = GfMenuReference::getReferenceMissionID();
      switch (type) {
      case 7:
        moveFieldSkillStart(acc, mission, 0);
        break;
      case 8:
        moveFieldSkillStart(acc, mission, 1);
        break;
      case 9:
        moveFieldSkillStart(acc, mission, 2);
        break;
      case 10:
        moveFieldSkillEnd(acc, mission, 0);
        break;
      case 11:
        moveFieldSkillEnd(acc, mission, 1);
        break;
      case 12:
        moveFieldSkillEnd(acc, mission, 2);
        break;
      }
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      ui::UIObjectAcc owner(unknown20->unknown18);
      ui::UIObjectAcc mission(owner.searchChild("LAY_mission"));
      mission.setAlpha(0.0f);
      unknown002(unknown20->unknown18, "LAY_form");
      int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 6, 0);
      GfMenuObject::hookCtrlEvent(handle, ctrl);
      GfMenuObject::disableInput(handle);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    updateBladeList(unknown20->unknown50, GfMenuReference::getReferenceTeamID());
    GfMenuObject::enableInput(handle);
    acc.setDisp(true);
    for (u32 i = 1; i <= 3; i++) {
      mm::mtl::FixStr<32> name;
      name.format("LAY_fs_act@%02d", i);
      ui::UIObjectAcc fieldSkill(acc.searchChild(name.c_str()));
      mm::Pnt<s16> pos;
      fieldSkill.getPos(pos);
      fieldSkill.setPos(mm::Pnt<s16>(0x500, pos.y));
      name.format("IMG_fs_act_bg@%02d", i);
      ui::UIObjectAcc background(acc.searchChild(name.c_str()));
      background.setAlpha(0.0f);
    }
    unknown140(handle, 3, 7, 0.0f);
    int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 5, 0);
    GfMenuObject::hookCtrlEvent(handle, ctrl);
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    break;
  }
  }
}

void GfMenuObjMercenaries::MissionListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_mis_location"), 0, false);
    GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_mis_flag_logo"), 2, false);
    GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_mis_flag_dev_lv"), 3, false);
    break;
  case GfMenuTypes::unknown003_33: {
    acc.setDisp(true);
    unknown002(unknown20->unknown18, "LAY_mis_list");
    unknown163(acc.searchChild("LAY_mis_select"), GfMenuTypes::unknown003_33, 0);
    int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 5, 0);
    GfMenuObject::hookCtrlEvent(handle, ctrl);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    unknown003(unknown20->unknown18, "LAY_mis_list");
    unknown163(acc.searchChild("LAY_mis_select"), GfMenuTypes::unknown003_34, 0);
    int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 6, 0);
    GfMenuObject::hookCtrlEvent(handle, ctrl);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaries::MissionRewardListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupReward(acc, unknown20->unknown50);
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 != 0) {
      if (event.unknown08 == 6) {
        ui::UIObjectAcc main(unknown20->unknown18);
        unknown164(main.searchChild("LAY_main"), GfMenuTypes::unknown003_260);
        u32 team = GfMenuReference::getReferenceTeamID();
        u32 mission = GfDataMercenaries::getTeamMission(team);
        GfGameMercenaries::execMissionRewardByTeamID(team);
        if (GfDataMercenaries::isEnableOrder(mission)) {
          GfGameMercenaries::setMissionFlag(mission, 1);
        }
        GfMenuReference::setReferenceTeamID(team + 1);
      }
      ui::UIObjectListener::reciveEvent(event, handle);
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      if (unknown20->unknown9e == 0) {
        unknown20->unknown9e = 1;
        unknown20->unknown0e8.unknown005();
        unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardComp);
        unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardComp2);
        unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardComp3);
        unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardComp4);
        unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardComp5);
      } else {
        int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 6, 0);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        GfMenuObject::disableInput(handle);
      }
    }
    break;
  case GfMenuTypes::unknown003_33: {
    u32 team = GfMenuReference::getReferenceTeamID();
    updateBladeList(unknown20->unknown50, team);
    unknown20->unknown9e = 0;
    unknown20->unknown0e8.unknown005();
    unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardStart);
    unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardStart2);
    unknown20->unknown0e8.unknown002(&GfMenuObjMercenaries::seqRewardStart3);
    break;
  }
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    break;
  }
}

void GfMenuObjMercenaries::MissionListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    setupMissionList(acc, unknown20->unknown68);
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = ui::UIObjectAcc(handle).getParentHandle();
    param.unknown04 = acc.searchSibiling("IMG_mis_list_cursor");
    param.unknown20.unknown18 = 5;
    param.unknown1a = 1;
    param.unknown08 = "LAY_mis@%02d";
    unknown20->unknown90 = GfMenuObjUtil::createCursor(param);
    ui::UIObjectAcc bar(unknown20->unknown18, "IMG_mis_scroll_bar");
    if (bar.isValid()) {
      GfMenuObjUtil::createVScrollBarPlugin(bar.unknown10, unknown20->unknown68, "IMG_mis_scroll_base", true);
      bar.setDisp(true);
      bar.setAddColor("gray");
    }
    GfMenuObject::disableInput(handle);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    unknown20->unknown68->setIndex(index);
    u32 selected = unknown20->unknown68->getIndex(true);
    unknown20->unknown90->inputChange(selected);
    GfMenuReference::setReferenceMissionID(unknown20->unknown68->getContents(unknown20->unknown68->getIndex(false)).unknown00);
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    updateMissionList(unknown20->unknown68, GfMenuReference::getReferenceZoneID());
    GfMenuReference::setReferenceMissionID(0);
    unknown20->unknown90->open(0);
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown68);
    GfMenuObject::enableInput(handle);
    acc.setDisp(true);
    ui::UIObjectAcc owner(unknown20->unknown18);
    GfMenuObjOperationInfo::open(handle, owner.searchChild("LAY_mis_select"), 0, 0);
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1:
      if (unknown20->unknown68->getSize() != 0) {
        unknown002(unknown20->unknown18, "LAY_mis_detail");
        GfDataMercenaries::clearNewMission(GfMenuReference::getReferenceMissionID());
        GfMenuObject::disableInput(handle);
      }
      break;
    case 2: {
      unknown003(unknown20->unknown18, "LAY_mission");
      {
        ui::UIObjectAcc owner(unknown20->unknown18);
        unknown163(owner.searchChild("LAY_location"), GfMenuTypes::unknown003_33, 0);
      }
      GfMenuObject::disableInput(handle);
      break;
    }
    }
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    break;
  case GfMenuTypes::unknown003_257: {
    GfMenuObject::enableInput(handle);
    ui::UIObjectAcc owner(unknown20->unknown18);
    GfMenuObjOperationInfo::open(handle, owner.searchChild("LAY_mis_select"), 0, 0);
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjMercenaries::LaunchListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupFormBladeSelect(acc, unknown20->unknown50);
    GfMenuObject::migrateInput(acc.searchChild("LAY_form_bl"), handle);
    GfMenuObject::disableInput(handle);
    break;
  case 3:
    if (event.unknown08 == 5) {
      for (u32 i = 1; i <= 6; i++) {
        mm::mtl::FixStr<32> name;
        name.format("LAY_form_bl_plate@%02d", i);
        u32 plateHandle = acc.searchChild(name.c_str());
        ui::UIObjectAcc plate(plateHandle);
        name.format("blade_default_position%02d", i);
        mm::Rect<s16> rect;
        acc.getLayoutRect(name.c_str(), rect);
        GfMenuObjUtil::CtrlParam param;
        plate.getPos(param.unknown26);
        param.unknown26.x = rect.x;
        param.unknown26.y = rect.y;
        param.unknown08 = 0x80;
        param.unknown0c = 1;
        param.unknown00 = 0.2f;
        GfMenuObjUtil::startCtrl(plateHandle, param, nullptr);
      }
    }
    return;
  case 8:
    if (event.unknown0c == 1) {
      unknown20->unknown28->reset();
      unknown20->unknown388 = 0x25;
      GfMenuObjCommonText::open(unknown20->unknown28, unknown20->unknown388, 0);
      GfMenuObject::setCallContextEventHandler(unknown20->unknown28, handle);
      GfMenuObject::disableInput(handle);
    }
    return;
  case GfMenuTypes::unknown003_33: {
    u32 team = GfMenuReference::getReferenceTeamID();
    updateBladeList(unknown20->unknown50, team);
    ui::UIObjectAcc blades(acc.searchChild("LAY_form_bl"));
    blades.setDisp(true);
    for (u32 i = 0; i < 6; i++) {
      mm::mtl::FixStr<32> name;
      name.format("LAY_form_bl_plate@%02d", i + 1);
      ui::UIObjectAcc plate(acc.searchChild(name.c_str()));
      mm::Pnt<s16> pos;
      plate.getPos(pos);
      pos.x = 0;
      plate.setPos(pos);
      name.format("LAY_form_bl_name_def@%02d", i + 1);
      u32 nameHandle = acc.searchChild(name.c_str());
      f32 alpha = unknown20->unknown50->getContents(i).unknown00 == 0 ? 0.0f : 1.0f;
      ui::UIObjectAcc(nameHandle).setAlpha(alpha);
    }
    int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 5, 0);
    GfMenuObject::hookCtrlEvent(handle, ctrl);
    acc.setDisp(true);
    GfMenuObject::enableInput(handle);
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    return;
  }
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    GfMenuObject::disableInput(handle);
    return;
  case 0x41:
    if (unknown20->unknown28 != nullptr && unknown20->unknown28->unknown0c == event.unknown08) {
      u16 result = event.unknown10_u16;
      GfMenuReference::getReferenceMissionID();
      if (result == 0 && unknown20->unknown388 == 0x25) {
        unknown002(unknown20->unknown18, "LAY_mission");
        int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 6, 0);
        GfMenuObject::hookCtrlEvent(handle, ctrl);
        GfMenuObject::disableInput(handle);
      }
    }
    return;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaries>(const mm::mtl::Delegate<bool()> *);
