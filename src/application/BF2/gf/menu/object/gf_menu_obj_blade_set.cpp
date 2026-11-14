#include "gf/menu/object/gf_menu_obj_blade_set.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
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
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: GfMenuMissionAdapter type of each condition type; original name unknown.
static const u32 unknown001[] = {21, 19, 21, 21};

// Inferred role: layout names of each mode; original name unknown.
static const char *const unknown002[] = {"LAY_bl_form", "LAY_release", "LAY_mer"};
// Inferred role: slot layout names of each mode; original name unknown.
static const char *const unknown003[] = {"LAY_bl_form_slot", "LAY_bl_release_slot", "LAY_mer_slot"};
// Inferred role: call id of the blade set layout; original name unknown.
constexpr u32 CALL_UNKNOWN_88 = 88;

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

void GfMenuObjBladeSet::initialize() {
  ui::UIObjectAcc acc(unknown18);
  unknown40 = GfMenuCallContext::create();
  unknown48 = GfMenuCallContext::create();
  unknown50 = GfMenuBladeList::create();
  unknown60 = GfMenuBladeList::create();
  unknown70 = GfMenuBladeList::create();
  unknown80 = GfMenuBladeList::create();
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 190 as in the original file: it is the line argument of operator new.
#line 190
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, main);
  u32 bladeSelect = acc.searchChild("LAY_bl_select");
// __LINE__ must be 195 as in the original file: it is the line argument of operator new.
#line 195
  BladeSelectListener *bladeSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BladeSelectListener(this);
  bladeSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(bladeSelect, bladeSelectListener);
  if (bladeSelectListener != nullptr) {
    bladeSelectListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, bladeSelect);
  u32 form = acc.searchChild("LAY_bl_form");
// __LINE__ must be 200 as in the original file: it is the line argument of operator new.
#line 200
  FormListener *formListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FormListener(this);
  formListener->addRef();
  ui::UIEventManager::get()->registObjectListener(form, formListener);
  if (formListener != nullptr) {
    formListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, form);
  u32 formSlot = acc.searchChild("LAY_bl_form_slot");
// __LINE__ must be 205 as in the original file: it is the line argument of operator new.
#line 205
  FormSlotListener *formSlotListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) FormSlotListener(this);
  formSlotListener->addRef();
  ui::UIEventManager::get()->registObjectListener(formSlot, formSlotListener);
  if (formSlotListener != nullptr) {
    formSlotListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, formSlot);
  u32 preview = acc.searchChild("LAY_bl_preview");
// __LINE__ must be 210 as in the original file: it is the line argument of operator new.
#line 210
  PreviewListener *previewListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PreviewListener(this);
  previewListener->addRef();
  ui::UIEventManager::get()->registObjectListener(preview, previewListener);
  if (previewListener != nullptr) {
    previewListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, preview);
  u32 release = acc.searchChild("LAY_release");
// __LINE__ must be 215 as in the original file: it is the line argument of operator new.
#line 215
  ReleaseListener *releaseListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReleaseListener(this);
  releaseListener->addRef();
  ui::UIEventManager::get()->registObjectListener(release, releaseListener);
  if (releaseListener != nullptr) {
    releaseListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, release);
  u32 releaseSlot = acc.searchChild("LAY_bl_release_slot");
// __LINE__ must be 220 as in the original file: it is the line argument of operator new.
#line 220
  ReleaseSlotListener *releaseSlotListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReleaseSlotListener(this);
  releaseSlotListener->addRef();
  ui::UIEventManager::get()->registObjectListener(releaseSlot, releaseSlotListener);
  if (releaseSlotListener != nullptr) {
    releaseSlotListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, releaseSlot);
  u32 mercenaries = acc.searchChild("LAY_mer");
// __LINE__ must be 225 as in the original file: it is the line argument of operator new.
#line 225
  MercenariesListener *mercenariesListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MercenariesListener(this);
  mercenariesListener->addRef();
  ui::UIEventManager::get()->registObjectListener(mercenaries, mercenariesListener);
  if (mercenariesListener != nullptr) {
    mercenariesListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, mercenaries);
  u32 mercenariesSlot = acc.searchChild("LAY_mer_slot");
// __LINE__ must be 230 as in the original file: it is the line argument of operator new.
#line 230
  MercenariesSlotListener *mercenariesSlotListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MercenariesSlotListener(this);
  mercenariesSlotListener->addRef();
  ui::UIEventManager::get()->registObjectListener(mercenariesSlot, mercenariesSlotListener);
  if (mercenariesSlotListener != nullptr) {
    mercenariesSlotListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, mercenariesSlot);
  u32 mercenariesSlotBl = acc.searchChild("LAY_mer_slot_bl");
// __LINE__ must be 235 as in the original file: it is the line argument of operator new.
#line 235
  MercenariesSlotBlListener *mercenariesSlotBlListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MercenariesSlotBlListener(this);
  mercenariesSlotBlListener->addRef();
  ui::UIEventManager::get()->registObjectListener(mercenariesSlotBl, mercenariesSlotBlListener);
  if (mercenariesSlotBlListener != nullptr) {
    mercenariesSlotBlListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, mercenariesSlotBl);
  u32 mercenariesSlotMenu = acc.searchChild("LAY_mer_slot_menu");
// __LINE__ must be 240 as in the original file: it is the line argument of operator new.
#line 240
  MercenariesSlotMenuListener *mercenariesSlotMenuListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MercenariesSlotMenuListener(this);
  mercenariesSlotMenuListener->addRef();
  ui::UIEventManager::get()->registObjectListener(mercenariesSlotMenu, mercenariesSlotMenuListener);
  if (mercenariesSlotMenuListener != nullptr) {
    mercenariesSlotMenuListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, mercenariesSlotMenu);
  u32 mercenariesPreview = acc.searchChild("LAY_mer_preview");
// __LINE__ must be 245 as in the original file: it is the line argument of operator new.
#line 245
  MercenariesPreviewListener *mercenariesPreviewListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MercenariesPreviewListener(this);
  mercenariesPreviewListener->addRef();
  ui::UIEventManager::get()->registObjectListener(mercenariesPreview, mercenariesPreviewListener);
  if (mercenariesPreviewListener != nullptr) {
    mercenariesPreviewListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_88, mercenariesPreview);
  GfMenuObject::initialize();
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
  // Decision 2026-11-14 #3: the game stores unknown18 = 0 and unknown1c = 1 with one stp (stp wzr, w8, [sp, #0x20] at 0x7100407d24), after the constructor's own zeroing.
  param.unknown18 = 0;
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

bool GfMenuObjBladeSet::checkBladeSet(u32, u32 blade, GfMenuBladeList *list) {
  u32 selected = list->getIndex(false);
  if (list->getContents(list->getIndex(false)).unknown00 != 0) {
    for (u32 i = 0; i < list->getSize(); i++) {
      const MenuBladeInfo &info = list->getContents(i);
      if (selected != i && info.unknown00 == blade) {
        return true;
      }
    }
  }
  for (u32 i = 0; i < list->getSize(); i++) {
    if (list->getContents(i).unknown00 == blade) {
      return false;
    }
  }
  return true;
}

void GfMenuObjBladeSet::setupMercenariesCond(ui::UIObjectAcc &acc, u32 mission, GfMenuBladeList *list) {
  mm::mtl::FixStr<32> name;
  for (int i = 0; i < 3; i++) {
    name.format("TXT_mer_prev_cond_index@%02d", i + 1);
    GfMenuMissionAdapter *index = GfMenuMissionAdapter::create(acc.searchChild(name.c_str()), 0x11, mission, false);
    index->unknown70 = i;
    name.format("LAY_mer_prev_cond@%02d", i + 1);
    index->unknown24 = acc.searchChild(name.c_str());
    name.format("IMG_mer_prev_cond_icon@%02d", i + 1);
    GfMenuMissionAdapter::create(acc.searchChild(name.c_str()), 0x12, mission, false)->unknown70 = i;
    name.format("IMG_mer_prev_cond_chk@%02d", i + 1);
    GfMenuMissionAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x18, mission, list, true)->unknown70 = i;
    name.format("TXT_mer_prev_cond_num@%02d", i + 1);
    GfMenuMissionAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x17, mission, list, true)->unknown70 = i;
    name.format("TXT_mer_prev_cond_max@%02d", i + 1);
    GfMenuMissionAdapter::create(acc.searchChild(name.c_str()), 0x16, mission, false)->unknown70 = i;
    setupMercenariesCondParam(acc, mission, i, 1, "IMG_mer_prev_cond_wpn@%02d", "LAY_mer_prev_cond_wpn@%02d");
    setupMercenariesCondParam(acc, mission, i, 2, "TXT_mer_prev_cond_pow@%02d", "LAY_mer_prev_cond_pow@%02d");
    setupMercenariesCondParam(acc, mission, i, 3, "IMG_mer_prev_cond_type@%02d", "LAY_mer_prev_cond_type@%02d");
    setupMercenariesCondParam(acc, mission, i, 4, "IMG_mer_prev_cond_gen@%02d", "LAY_mer_prev_cond_gen@%02d");
    setupMercenariesCondParam(acc, mission, i, 5, "TXT_mer_prev_cond_arts_lv@%02d", "LAY_mer_prev_cond_arts@%02d");
    setupMercenariesCondParam(acc, mission, i, 6, "TXT_mer_prev_cond_arts_lv@%02d", "LAY_mer_prev_cond_arts@%02d");
  }
  for (int i = 0; i < 3; i++) {
    name.format("TXT_mer_prev_fs_name@%02d", i + 1);
    GfMenuMissionAdapter *fsName = GfMenuMissionAdapter::create(acc.searchChild(name.c_str()), 0x10, mission, false);
    fsName->unknown70 = i;
    name.format("LAY_mer_prev_fs_num@%02d", i + 1);
    fsName->unknown24 = acc.searchChild(name.c_str());
    name.format("TXT_mer_prev_fs_lv@%02d", i + 1);
    GfMenuMissionAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x25, mission, list, true)->unknown70 = i;
    name.format("TXT_mer_prev_fs_num@%02d", i + 1);
    GfMenuMissionAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x26, mission, list, true)->unknown70 = i;
    name.format("TXT_mer_prev_fs_max@%02d", i + 1);
    GfMenuMissionAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x27, mission, list, false)->unknown70 = i;
  }
}

void GfMenuObjBladeSet::setupFormSlot(ui::UIObjectAcc &acc, const GfMenuBladeList *list) {
  mm::mtl::FixStr<32> name;
  GfMenuGameAdapter::create(acc.searchChild("IMG_bl_form_slot_btn_bg"), 9, true)->unknown50 = 0;
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("TXT_bl_form_slot_dr_name"), 2, 0, false);
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_bl_form_slot_dr_face"), 3, 0, false);
  name.format("IMG_bl_form_bl_face@%02d", 1);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, list, 0, false);
  name.format("IMG_bl_form_bl_base@%02d", 1);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x38, list, 0, false);
  name.format("IMG_bl_form_bl_face@%02d", 2);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, list, 1, false);
  name.format("IMG_bl_form_bl_base@%02d", 2);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x38, list, 1, false);
  name.format("IMG_bl_form_bl_face@%02d", 3);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, list, 2, false);
  name.format("IMG_bl_form_bl_base@%02d", 3);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x38, list, 2, false);
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

void GfMenuObjBladeSet::PreviewListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupBladePreview(acc);
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeSet::MercenariesPreviewListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMercenariesPreview(acc, unknown20->unknown80);
    setupMercenariesCond(acc, unknown20->unknown28, unknown20->unknown80);
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeSet::ReleaseListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_33:
    unknown164(owner.searchChild("LAY_bl_release_slot"), GfMenuTypes::unknown003_33);
    unknown163(owner.searchChild("LAY_bl_preview"), GfMenuTypes::unknown003_33, 0);
    GfMenuObjOperationInfo::open(owner.searchChild("LAY_bl_form"), owner.searchChild("LAY_bl_form_slot"), 0, 0);
    setFadeIn(handle);
    break;
  case GfMenuTypes::unknown003_34:
    unknown164(owner.searchChild("LAY_bl_release_slot"), GfMenuTypes::unknown003_34);
    unknown163(owner.searchChild("LAY_bl_preview"), GfMenuTypes::unknown003_34, 0);
    unknown163(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34, 0);
    GfMenuObjOperationInfo::close();
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeSet::FormListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1:
  case 8:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case GfMenuTypes::unknown003_33:
    unknown164(owner.searchChild("LAY_bl_form_slot"), GfMenuTypes::unknown003_33);
    unknown163(owner.searchChild("LAY_bl_preview"), GfMenuTypes::unknown003_33, 0);
    GfMenuObjOperationInfo::open(owner.searchChild("LAY_bl_form"), owner.searchChild("LAY_bl_form_slot"), 0, 0);
    setFadeIn(handle);
    break;
  case GfMenuTypes::unknown003_34:
    unknown164(owner.searchChild("LAY_bl_form_slot"), GfMenuTypes::unknown003_34);
    unknown163(owner.searchChild("LAY_bl_preview"), GfMenuTypes::unknown003_34, 0);
    unknown163(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34, 0);
    GfMenuObjOperationInfo::close();
    break;
  }
}

void GfMenuObjBladeSet::MercenariesSlotListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case GfMenuTypes::unknown003_257:
    unknown164(owner.searchChild("LAY_mer_slot_bl"), GfMenuTypes::unknown003_257);
    unknown163(owner.searchChild("LAY_mer_slot_menu"), GfMenuTypes::unknown003_257, 0);
    break;
  case GfMenuTypes::unknown003_34:
    unknown164(owner.searchChild("LAY_mer_slot_menu"), GfMenuTypes::unknown003_34);
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_259:
    unknown163(owner.searchChild("LAY_mer_slot_bl"), GfMenuTypes::unknown003_259, 0);
    break;
  case GfMenuTypes::unknown003_258:
    unknown163(owner.searchChild("LAY_mer_slot_bl"), GfMenuTypes::unknown003_258, 0);
    break;
  case GfMenuTypes::unknown003_33:
    unknown164(owner.searchChild("LAY_mer_slot_menu"), GfMenuTypes::unknown003_33);
    acc.setDisp(true);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeSet::MercenariesListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1:
    setupMercenaries(acc);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 8:
    if (event.unknown0c == 0xc) {
      if (!unknown20->unknown34) {
        if (GfMenuReference::getReferenceBladeID(0) != 0) {
          detailOpen(unknown20, owner, nullptr, 0);
          unknown20->unknown34 = true;
          GfMenuObject::disableInput(owner.searchChild(!unknown20->unknown35 ? "LAY_bl_select" : "LAY_mer_slot_bl"));
        }
      } else {
        GfMenuObjCommonDetail::close(unknown20->unknown48);
        unknown20->unknown34 = false;
        GfMenuObject::enableInput(owner.searchChild(!unknown20->unknown35 ? "LAY_bl_select" : "LAY_mer_slot_bl"));
      }
    }
    break;
  case GfMenuTypes::unknown003_33:
    setEmptyTeamId();
    unknown164(owner.searchChild("LAY_mer_slot"), GfMenuTypes::unknown003_33);
    unknown163(owner.searchChild("LAY_mer_preview"), GfMenuTypes::unknown003_33, 0);
    setFadeIn(handle);
    break;
  case GfMenuTypes::unknown003_34:
    unknown164(owner.searchChild("LAY_mer_slot"), GfMenuTypes::unknown003_34);
    unknown163(owner.searchChild("LAY_mer_preview"), GfMenuTypes::unknown003_34, 0);
    GfMenuObjOperationInfo::close();
    break;
  }
}

void GfMenuObjBladeSet::MercenariesSlotMenuListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 6:
    setMenuBtnStat(unknown20->unknown2c = event.unknown08, unknown20->unknown28, unknown20->unknown80);
    break;
  case 8:
    switch (event.unknown0c) {
    case 1: {
      int menu = unknown20->unknown2c;
      switch (menu) {
      case 0: {
        mm::mtl::FixedArray<u16, 6> members;
        if (GfGameMercenaries::getMemberForMission(members, unknown20->unknown28, MERCENARY_SELECT_UNKNOWN_0)) {
          for (u32 i = 0; i < 6; i++) {
            unknown20->unknown80->getContents(i).unknown00 = members[i];
          }
          unknown164(owner.searchChild("LAY_mer_slot_bl"), GfMenuTypes::unknown003_260);
          for (int i = 1; i <= 3; i++) {
            GfMenuReference::setReferenceNumber(i, 1);
          }
        }
        break;
      }
      case 1: {
        unknown121 *preset = GfDataMercenaries::getPreset(unknown20->unknown30);
        for (u32 i = 0; i < 6; i++) {
          if (i < unknown20->unknown80->getSize()) {
            preset->unknown00[i] = unknown20->unknown80->getContents(i).unknown00;
          } else {
            preset->unknown00[i] = 0;
          }
        }
        break;
      }
      case 2: {
        unknown121 *preset = GfDataMercenaries::getPreset(unknown20->unknown30);
        for (u32 i = 0; i < 6; i++) {
          unknown20->unknown80->getContents(i).unknown00 = preset->unknown00[i];
        }
        break;
      }
      }
      GfMenuReference::setReferenceNumber(menu + 1, 4);
      break;
    }
    case 9:
      unknown164(owner.searchChild("LAY_mer_slot_bl"), GfMenuTypes::unknown003_33);
      for (int i = 1; i <= 3; i++) {
        GfMenuReference::setReferenceNumber(i, 1);
      }
      GfMenuObject::disableInput(handle);
      break;
    case 2:
      GfMenuReference::setReferenceTeamID(0);
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
      GfMenuObject::disableInput(handle);
      break;
    }
    break;
  case 1:
    GfMenuObject::disableInput(handle);
    break;
  case GfMenuTypes::unknown003_33: {
    unknown20->unknown35 = false;
    unknown20->unknown2c = 0;
    GfMenuObject::setupInputSelection(handle, 0, 3);
    GfMenuObject::enableInput(handle);
    mm::mtl::FixedArray<u16, 6> members;
    GfMenuReference::setReferenceNumber(1, GfGameMercenaries::getMemberForMission(members, unknown20->unknown28, MERCENARY_SELECT_UNKNOWN_0) ? 3 : 2);
    GfMenuReference::setReferenceNumber(2, 1);
    GfMenuReference::setReferenceNumber(3, 1);
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    acc.setDisp(true);
    break;
  }
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_257:
    setupMercenariesSlotMenu(acc);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
