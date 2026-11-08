#include "gf/menu/object/gf_menu_obj_blade_set.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"
#include "gf/menu/adapter/gf_menu_mission_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_common_detail.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: GfMenuMissionAdapter type of each condition type; original name unknown.
static const u32 unknown001[] = {21, 19, 21, 21};

// Inferred role: layout names of each mode; original name unknown.
static const char *const unknown002[] = {"LAY_bl_form", "LAY_release", "LAY_mer"};
// Inferred role: slot layout names of each mode; original name unknown.
static const char *const unknown003[] = {"LAY_bl_form_slot", "LAY_bl_release_slot", "LAY_mer_slot"};

GfMenuObjBladeSet::GfMenuObjBladeSet(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(0), unknown34(false), unknown35(true), unknown38(0), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr),
      unknown58(nullptr), unknown60(nullptr), unknown68(nullptr), unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(nullptr) {}

GfMenuObjBladeSet::~GfMenuObjBladeSet() {
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown88);
}

void GfMenuObjBladeSet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeSet::update() { GfMenuObject::update(); }

void GfMenuObjBladeSet::registOpenParam(const OpenParam &) {}

u32 GfMenuObjBladeSet::setEmptyTeamId() {
  u32 team = 0;
  for (u32 i = 1; i <= GfDataMercenaries::getTeamNum(); i++) {
    if (GfDataMercenaries::isTeamMemberEmpty(i)) {
      team = i;
      break;
    }
  }
  GfMenuReference::setReferenceTeamID(team);
  return team;
}

void GfMenuObjBladeSet::setMenuBtnStat(int menu, u32 blade, const GfMenuBladeList *list) {
  for (int i = 0; i < 3; i++) {
    int stat = 1;
    if (i == menu) {
      stat = isMenuBtnEnable(i, blade, list) ? 3 : 2;
    }
    GfMenuReference::setReferenceNumber(i + 1, stat);
  }
}

void GfMenuObjBladeSet::setCompleteBtnStat(int menu, u32 mission, const GfMenuBladeList *list) {
  int stat = 1;
  if (menu == 6) {
    bool isEnable = true;
    for (u32 task = 0; task < 3; task++) {
      GfRequestBladeData data = {};
      if (GfDataMercenaries::getRequestCondition(data, mission, task)) {
        u32 count = GfMenuObjUtil::getMissionCondBladeCount(data, list);
        u32 need = data.unknown0c == 0 ? 1 : data.unknown0c;
        if (count < need) {
          isEnable = false;
          break;
        }
      }
    }
    stat = isEnable ? 3 : 2;
  }
  GfMenuReference::setReferenceNumber(0, stat);
}

void GfMenuObjBladeSet::setupMercenariesCondParam(ui::UIObjectAcc &acc, u32 mission, int task, u32 type, const char *format, const char *layoutFormat) {
  mm::mtl::FixStr<32> name;
  u32 adapterType = 0x13;
  if (type - 1 < 4) {
    adapterType = unknown001[static_cast<int>(type - 1)];
  }
  name.format(format, task + 1);
  GfMenuMissionAdapter *adapter = GfMenuMissionAdapter::create(acc.searchChild(name.c_str()), adapterType, mission, false);
  adapter->unknown70 = task;
  adapter->unknown64 = type;
  name.format(layoutFormat, task + 1);
  adapter->unknown24 = acc.searchChild(name.c_str());
}

bool GfMenuObjBladeSet::isMenuBtnEnable(int menu, u32 blade, const GfMenuBladeList *list) {
  if (menu == 0) {
    mm::mtl::FixedArray<u16, 6> members;
    return GfGameMercenaries::getMemberForMission(members, blade, MERCENARY_SELECT_UNKNOWN_0);
  }
  if (menu == 1) {
    for (u32 i = 0; i < list->getSize(); i++) {
      if (list->getContents(i).unknown00 != 0) {
        return true;
      }
    }
  } else if (menu == 2) {
    for (u32 i = 0; i < 8; i++) {
      unknown121 *preset = GfDataMercenaries::getPreset(i);
      for (u32 j = 0; j < 6; j++) {
        if (preset->unknown00[j] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}

void GfMenuObjBladeSet::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBladeSet::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBladeSet::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBladeSet::checkBladeRelease(u32 blade) {
  if (GfDataBlade::isActivateDriver(blade)) {
    return false;
  }
  return !GfDataBlade::isActivateMercenaryTeam(blade);
}

void GfMenuObjBladeSet::setupMercenaries(ui::UIObjectAcc &acc) {
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("IMG_mer_name_symbol"), 2, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("TXT_mer_name"), 0, false);
}

void GfMenuObjBladeSet::createBladeList(eMode mode, int driver, GfMenuBladeList *list) {
  switch (mode) {
  case eMode_UNKNOWN_0: {
    GfMenuBladeList::DriverSetup setup;
    setup.unknown14 = 0;
    setup.unknown18 = driver;
    setup.unknown00.unknown08 = 4;
    setup.unknown00.unknown0c = 6;
    list->setupFromDriver(setup);
    break;
  }
  case eMode_UNKNOWN_1: {
    GfMenuBladeList::DriverSetup setup;
    setup.unknown00.unknown08 = 4;
    setup.unknown00.unknown0c = 6;
    list->setupFromDriver(setup);
    break;
  }
  case eMode_UNKNOWN_2: {
    GfMenuBladeList::DriverSetup setup;
    setup.unknown00.unknown08 = 4;
    setup.unknown00.unknown0c = 6;
    list->setupFromDriver(setup);
    break;
  }
  }
}

void GfMenuObjBladeSet::setupReleaseSlot(ui::UIObjectAcc &acc, const GfMenuBladeList *list) {
  GfMenuGameAdapter::create(acc.searchChild("IMG_bl_release_slot_btn_bg"), 9, true)->unknown50 = 0;
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild("IMG_bl_release_bl_face"), 3, list, 0, false);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild("IMG_bl_release_bl_base"), 0x38, list, 0, false);
}

void GfMenuObjBladeSet::detailOpen(GfMenuObjBladeSet *object, ui::UIObjectAcc &acc, const char *layout, u32 unknown) {
  object->unknown48->reset();
  GfMenuObjCommonDetail::OpenParam param;
  param.unknown1c = 1;
  param.unknown00.push_back(0x21f);
  if (layout == nullptr) {
    param.unknown20.x = 0x1e0;
    param.unknown20.y = 0xc8;
    param.unknown20.width = 0x12c;
    param.unknown20.height = 400;
  } else {
    acc.getLayoutRect(layout, param.unknown20);
  }
  GfMenuObjCommonDetail::open(object->unknown48, param);
}

void GfMenuObjBladeSet::setupMercenariesSlotMenu(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  name.format("IMG_mer_slot_menu_btn@%02d", 1);
  GfMenuGameAdapter::create(acc.searchChild(name.c_str()), 9, true)->unknown50 = 1;
  name.format("IMG_mer_slot_menu_btn@%02d", 2);
  GfMenuGameAdapter::create(acc.searchChild(name.c_str()), 9, true)->unknown50 = 2;
  name.format("IMG_mer_slot_menu_btn@%02d", 3);
  GfMenuGameAdapter::create(acc.searchChild(name.c_str()), 9, true)->unknown50 = 3;
}

void GfMenuObjBladeSet::setupMercenariesSlotBl(ui::UIObjectAcc &acc, const GfMenuBladeList *list) {
  mm::mtl::FixStr<32> name;
  GfMenuGameAdapter::create(acc.searchChild("IMG_mer_slot_bl_btn_bg"), 9, true)->unknown50 = 0;
  for (int i = 0; i < 6; i++) {
    name.format("IMG_mer_bl_face@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("IMG_mer_bl_base@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x38, list, i, false);
  }
}

void GfMenuObjBladeSet::setupBladePreview(ui::UIObjectAcc &acc) {
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_bl_prev_bl_name"), 2, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_bl_prev_bl_full"), 0x36, 0, false);
  GfMenuCharDataAdapter *driverName = GfMenuCharDataAdapter::createFromReferenceBladeOwnerDriver(acc.searchChild("TXT_bl_prev_dr_name"), 2, 0, false);
  driverName->unknown24 = acc.searchChild("LAY_bl_prev_dr_name");
  GfMenuMercenariesAdapter *mercenariesIcon = GfMenuMercenariesAdapter::createFromReferenceBlade(acc.searchChild("IMG_bl_prev_mer_icon"), 2, 0, false);
  mercenariesIcon->unknown24 = acc.searchChild("LAY_bl_prev_mer");
  GfMenuMercenariesAdapter::createFromReferenceBlade(acc.searchChild("TXT_bl_prev_mer_status"), 3, 0, false);
}

bool GfMenuObjBladeSet::checkMercenaries(u32 blade, GfMenuBladeList *list) {
  if (GfDataBlade::isActivateDriver(blade) || GfDataBlade::isActivateMercenaryTeam(blade)) {
    return false;
  }
  for (u32 i = 0; i < list->getSize(); i++) {
    if (list->getContents(i).unknown00 == blade) {
      return false;
    }
  }
  return true;
}

void GfMenuObjBladeSet::setupBladeSelect(ui::UIObjectAcc &acc, const GfMenuBladeList *list, GfMenuBladeList *slotList) {
  mm::mtl::FixStr<32> name;
  for (int i = 0; i < 24; i++) {
    name.format("LAY_bl_select_bl@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x49, list, i, true)->setSlotList(slotList);
    name.format("IMG_bl_select_bl_face@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("IMG_bl_select_bl_base@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x38, list, i, false);
  }
}

void GfMenuObjBladeSet::setupMercenariesPreview(ui::UIObjectAcc &acc, GfMenuBladeList *list) {
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_mer_prev_bl_name"), 2, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_mer_prev_bl"), 0x36, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_mer_prev_bl_st_pow_num"), 0x37, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_mer_prev_bl_st_wpn_icon"), 0x29, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_mer_prev_bl_st_kind_icon"), 0x3b, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_mer_prev_bl_base"), 0x38, 0, false);
  GfMenuCharDataAdapter *driverName = GfMenuCharDataAdapter::createFromReferenceBladeOwnerDriver(acc.searchChild("TXT_mer_prev_dr_name"), 2, 0, false);
  driverName->unknown24 = acc.searchChild("LAY_mer_prev_dr_name");
  GfMenuMercenariesAdapter::createFromReferenceBlade(acc.searchChild("IMG_mer_unit_symbol"), 4, 0, false);
  GfMenuMercenariesAdapter *unit = GfMenuMercenariesAdapter::createFromReferenceBlade(acc.searchChild("IMG_mer_unit_symbol"), 2, 0, false);
  unit->unknown24 = acc.searchChild("LAY_mer_unit");
}

void GfMenuObjBladeSet::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuTypes::Param param;
    if (!GfMenuObject::getFSLayerParam(unknown20->unknown20, param)) {
      unknown20->unknown24 = 0;
      unknown20->unknown28 = 2;
    } else {
      u32 mode = param.get<OpenParam>().unknown00;
      unknown20->unknown24 = mode < 3 ? mode : 0;
      unknown20->unknown28 = param.get<OpenParam>().unknown04;
      GfMenuObject::removeFSLayerParam(unknown20->unknown20);
    }
    unknown158(handle, GfMenuTypes::unknown003_33, 0, 0.0f);
    break;
  }
  case 2:
    unknown158(handle, GfMenuTypes::unknown003_34, 0, 0.0f);
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObject::returnFSSubLayer(handle, 1);
    }
    break;
  case 0x21: {
    unknown163(acc.searchChild("LAY_bl_select"), GfMenuTypes::unknown003_257, 0);
    const char *form = nullptr;
    const char *slot = nullptr;
    if (unknown20->unknown24 >= 0 && unknown20->unknown24 < 3) {
      form = unknown002[unknown20->unknown24];
      slot = unknown003[unknown20->unknown24];
    }
    unknown163(acc.searchChild(slot), GfMenuTypes::unknown003_257, 0);
    unknown163(acc.searchChild(form), GfMenuTypes::unknown003_33, 0);
    acc.setDisp(true);
    break;
  }
  case 0x22:
    GfMenuObjOperationInfo::close();
    GfMenuObject::hookCtrlEvent(handle, GfMenuObjUtil::setCommonFadeOut(handle, 2, 0));
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
