#include "gf/menu/object/gf_menu_obj_hana_custom.h"

#include "gf/data/gf_data_hana.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/adapter/gf_menu_hana_adapter.h"
#include "gf/menu/adapter/gf_menu_hana_parts_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjHanaCustom::GfMenuObjHanaCustom(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown80(0), unknown84(0), unknown88(nullptr), unknown90(nullptr), unknown98(nullptr),
      unknown0a0(nullptr), unknown0a8(this), unknown340(nullptr), unknown348(nullptr), unknown350(0) {
  for (int i = 0; i < 7; i++) {
    unknown48[i] = nullptr;
  }
}

GfMenuObjHanaCustom::~GfMenuObjHanaCustom() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown88);
  mm::mtl::safeRelease(unknown90);
  mm::mtl::safeRelease(unknown98);
  mm::mtl::safeRelease(unknown0a0);
  unknown340 = nullptr;
  unknown358 = nullptr;
  for (int i = 0; i < 7; i++) {
    mm::mtl::safeRelease(unknown48[i]);
  }
}

void GfMenuObjHanaCustom::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaCustom::update() {
  unknown0a8.unknown003();
  GfMenuObject::update();
}

u32 GfMenuObjHanaCustom::convPartsId(u32 partsId) {
  if (partsId > 0xf) {
    return partsId - 7;
  }
  return partsId;
}

bool GfMenuObjHanaCustom::isExpandParts(u32 partsId) { return partsId - 9 < 6; }

void GfMenuObjHanaCustom::refreshPlanLine(ui::UIObjectAcc &) {}

void GfMenuObjHanaCustom::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaCustom::setFadeIn(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaCustom::setFadeOut(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjHanaCustom::setupMain(ui::UIObjectAcc &acc) { GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hplist_etnum"), 0, 0, true); }

u32 GfMenuObjHanaCustom::getPartsId() { return unknown28->getContents(unknown28->getIndex(false)).unknown00 + unknown80; }

void GfMenuObjHanaCustom::updateItemList(GfMenuItemList *list, ItemType::Type type) {
  list->clear();
  GfMenuItemList::ItemBoxSetup setup;
  setup.unknown00.unknown08 = 9;
  setup.unknown00.unknown10 = true;
  setup.unknown14 = type;
  setup.unknown28 = true;
  setup.unknown29 = true;
  list->setupFromBox(setup);
}

void GfMenuObjHanaCustom::removeParts(u32 blade, u32 parts) {
  switch (parts) {
  case 3:
  case 4:
  case 5:
    GfGameUtilHana::execEquipNArtsParts(blade, 0, GfItemHandle(0), parts - 3);
    break;
  case 6:
  case 7:
  case 8:
    GfGameUtilHana::execEquipCondenserParts(blade, 0, GfItemHandle(0), parts - 6);
    break;
  case 9:
  case 10:
  case 11:
    GfGameUtilHana::execEquipArtsParts(blade, 0, GfItemHandle(0), parts - 9);
    break;
  case 12:
  case 13:
  case 14:
    GfGameUtilHana::execEquipExtendCondenserParts(blade, 0, GfItemHandle(0), parts - 12);
    break;
  }
}

void GfMenuObjHanaCustom::expandCircuit(u32 blade, u32 parts) {
  switch (parts) {
  case 9:
  case 10:
  case 11:
  case 16:
  case 17:
  case 18:
    GfGameUtilHana::openArtsCircuit(blade, parts > 15 ? parts - 16 : parts - 9);
    break;
  case 12:
  case 13:
  case 14:
  case 19:
  case 20:
  case 21:
    GfGameUtilHana::openCondenserCircuit(blade, parts > 18 ? parts - 19 : parts - 12);
    break;
  case 15:
    GfGameUtilHana::execPowerRankup(blade, GfGameUtilHana::getPowerRank(blade) + 1);
    break;
  }
}

void GfMenuObjHanaCustom::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < selectList->getSize(); i++) {
    name.format("TXT_sbpartsname@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    name.format("IMG_sbpartsicon@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false);
  }
}

void GfMenuObjHanaCustom::equipParts(u32 blade, u32 parts, u32 partsId, GfItemHandle handle) {
  switch (parts) {
  case 1:
    GfGameUtilHana::execEquipRoleParts(blade, partsId, handle);
    break;
  case 2:
    GfGameUtilHana::execEquipAttributeParts(blade, partsId, handle);
    break;
  case 3:
  case 4:
  case 5:
    GfGameUtilHana::execEquipNArtsParts(blade, partsId, handle, parts - 3);
    break;
  case 6:
  case 7:
  case 8:
    GfGameUtilHana::execEquipCondenserParts(blade, partsId, handle, parts - 6);
    break;
  case 9:
  case 10:
  case 11:
    GfGameUtilHana::execEquipArtsParts(blade, partsId, handle, parts - 9);
    break;
  case 12:
  case 13:
  case 14:
    GfGameUtilHana::execEquipExtendCondenserParts(blade, partsId, handle, parts - 12);
    break;
  }
}

void GfMenuObjHanaCustom::setupPlan(ui::UIObjectAcc &acc, GfMenuIDList *list) {
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_num"), 1, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_max"), 2, 0, true);
  GfMenuHanaAdapter *adapter = GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hn_gauge"), 1, 0, true);
  if (adapter != nullptr) {
    adapter->setNumberInterpolateMode(0.2f);
  }
  ui::UIObjectAcc gauge(acc.searchChild("IMG_hn_gauge"));
  gauge.setExtType(4);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_ench_num"), 8, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_ench_max"), 9, 0, false);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_rol"), 3, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hn_elml"), 5, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hana"), 6, 0, false);
}

void GfMenuObjHanaCustom::setupItemInfo2(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 blade) {
  GfMenuHanaPartsAdapter *adapter = GfMenuHanaPartsAdapter::createFromReference(acc.searchChild("TXT_ndetl_num"), 2, number, true);
  if (adapter != nullptr) {
    adapter->unknown58 = blade;
  }
}

u32 GfMenuObjHanaCustom::chkSameSlot(mm::mtl::FixedArray<GfMenuIDList *, 7> &lists, u32 parts) {
  for (u32 i = 0; i < 7; i++) {
    if (lists[i]->getContents(0).unknown00 == parts) {
      return lists[i]->getSize();
    }
  }
  return 0;
}

u8 GfMenuObjHanaCustom::getEquipSlot(mm::mtl::FixedArray<GfMenuIDList *, 7> &lists, u32 parts) {
  EquipHana *equip = GfDataHana::getEquipParts(GfMenuReference::getReferenceBladeID(0));
  u8 slot = 0;
  switch (parts) {
  case 1:
  case 2:
  case 15:
    return 1;
  case 3:
    for (u32 i = 0; i < 3; i++) {
      if (equip->unknown28[i].unknown04 != 0) {
        slot++;
      }
    }
    break;
  case 6:
    for (u32 i = 0; i < 3; i++) {
      if (equip->unknown4c[i] != 0) {
        slot++;
      }
    }
    break;
  case 9:
    for (u32 i = 0; i < 3; i++) {
      if (equip->unknown04[i].unknown04 != 0) {
        slot++;
      }
    }
    break;
  case 12:
    for (u32 i = 0; i < 3; i++) {
      if (equip->unknown52[i] != 0) {
        slot++;
      }
    }
    break;
  }
  return slot;
}

void GfMenuObjHanaCustom::clearPLanSelect(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 1; i < 16; i++) {
    name.format("IMG_hnptslot_base@%02d", i);
    ui::UIObjectAcc(acc.searchChild(name.c_str())).setImageIndex(0);
  }
}

u32 GfMenuObjHanaCustom::searchIdList(GfMenuIDList *list, u32 id) {
  for (u32 i = 0; i < list->getSize(); i++) {
    if (list->getContents(i).unknown00 == id) {
      return i;
    }
  }
  return 0xffffffff;
}

void GfMenuObjHanaCustom::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMain(acc);
    GfMenuObjOperationInfo::setGuideText(0x18, 0);
    GfMenuObjMainMenu2::setSubIndexText(0x19);
    GfMenuObjMainMenu2::closeCharChange();
    setFadeIn(handle, 0);
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjCharSelect::returnSubMenu();
      GfMenuObject::returnFSSubLayer(unknown20);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjHanaCustom>(const mm::mtl::Delegate<bool()> *);
