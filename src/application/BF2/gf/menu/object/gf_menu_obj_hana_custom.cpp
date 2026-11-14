#include "gf/menu/object/gf_menu_obj_hana_custom.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/adapter/gf_menu_hana_adapter.h"
#include "gf/menu/adapter/gf_menu_hana_parts_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: item type of each equip list category; original name unknown.
static const ItemType::Type unknown001[] = {
    ItemType::ITEM_TYPE_UNKNOWN_16,
    ItemType::ITEM_TYPE_UNKNOWN_17,
    ItemType::ITEM_TYPE_UNKNOWN_19,
    ItemType::ITEM_TYPE_UNKNOWN_19,
    ItemType::ITEM_TYPE_UNKNOWN_19,
    ItemType::ITEM_TYPE_UNKNOWN_20,
    ItemType::ITEM_TYPE_UNKNOWN_20,
    ItemType::ITEM_TYPE_UNKNOWN_20,
    ItemType::ITEM_TYPE_UNKNOWN_18,
    ItemType::ITEM_TYPE_UNKNOWN_18,
    ItemType::ITEM_TYPE_UNKNOWN_18,
    ItemType::ITEM_TYPE_UNKNOWN_20,
    ItemType::ITEM_TYPE_UNKNOWN_20,
    ItemType::ITEM_TYPE_UNKNOWN_20,
};

// Inferred role: column of the parts mode table of each hana blade; original name unknown.
static const char *const unknown002[] = {"JS_SET", "JK_SET", "JD_SET"};

// Inferred role: layout of each parts category frame, indexed by the number of parts of the category minus one; original name unknown.
static const char *const unknown003[] = {"parts_category_one_S18_L1C12", "parts_category_two_S18_L1C12", "parts_category_three_S18_L1C12"};

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

void GfMenuObjHanaCustom::getEquipItem(u32 blade, u32 parts, MenuItemInfo &info) {
  EquipHana equip;
  GfGameUtilHana::getEquip(equip, blade);
  switch (parts) {
  case 1:
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_16;
    info.unknown04 = equip.unknown00;
    break;
  case 2:
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_17;
    info.unknown04 = equip.unknown02;
    break;
  case 3:
  case 4:
  case 5:
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_19;
    info.unknown04 = equip.unknown28[parts - 3].unknown04;
    break;
  case 6:
  case 7:
  case 8:
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_20;
    info.unknown04 = equip.unknown4c[parts - 6];
    break;
  case 9:
  case 10:
  case 11:
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_18;
    info.unknown04 = equip.unknown04[parts - 9].unknown04;
    break;
  case 12:
  case 13:
  case 14:
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_20;
    info.unknown04 = equip.unknown52[parts - 12];
    break;
  default:
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_0;
    info.unknown04 = 0;
    break;
  }
}

bool GfMenuObjHanaCustom::refreshEquipListSub(ui::UIObjectAcc &acc, u32 type, u32 item, u32 index) {
  mm::mtl::FixStr<32> name;
  u8 *msBdat = GfDataBdat::getFP(BDAT_MENU_MS);
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_SET);
  name.format("IMG_equip_list_icon@%02d", index + 1);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  if (item != 0) {
    icon.setDisp(true);
    icon.setImageIndex(Bdat::getVal(bdat, "icon", type).valueU16);
  }
  name.format("TXT_equip_list_cate_name@%02d", index + 1);
  ui::UIObjectAcc category(acc.searchChild(name.c_str()));
  u16 nameId = Bdat::getVal(bdat, "name", type).valueU16;
  if (item != 0 && nameId != 0) {
    category.setDisp(true);
    category.setText(ui::UIStr(msBdat, nameId));
  }
  name.format("TXT_equip_list_name@%02d", index + 1);
  ui::UIObjectAcc text(acc.searchChild(name.c_str()));
  ui::UIStr itemName;
  GfMenuItemUtil::getItemName(unknown001[type - 1], item, itemName);
  if (item != 0 && itemName.isValid()) {
    text.setDisp(true);
    text.setText(itemName);
  }
  return item != 0;
}

void GfMenuObjHanaCustom::refreshEquipList(ui::UIObjectAcc &acc, u32 blade) {
  for (u32 i = 1; i < 15; i++) {
    mm::mtl::FixStr<32> name;
    name.format("IMG_equip_list_icon@%02d", i);
    ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
    icon.setDisp(false);
    name.format("TXT_equip_list_cate_name@%02d", i);
    ui::UIObjectAcc category(acc.searchChild(name.c_str()));
    category.setDisp(false);
    name.format("TXT_equip_list_name@%02d", i);
    ui::UIObjectAcc text(acc.searchChild(name.c_str()));
    text.setDisp(false);
  }
  EquipHana *equip = GfDataHana::getEquipParts(blade);
  u32 index = 0;
  if (refreshEquipListSub(acc, 1, equip->unknown00, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 2, equip->unknown02, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 3, equip->unknown28[0].unknown04, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 4, equip->unknown28[1].unknown04, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 5, equip->unknown28[2].unknown04, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 6, equip->unknown4c[0], index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 7, equip->unknown4c[1], index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 8, equip->unknown4c[2], index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 9, equip->unknown04[0].unknown04, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 10, equip->unknown04[1].unknown04, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 11, equip->unknown04[2].unknown04, index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 12, equip->unknown52[0], index)) {
    index++;
  }
  if (refreshEquipListSub(acc, 13, equip->unknown52[1], index)) {
    index++;
  }
  refreshEquipListSub(acc, 14, equip->unknown52[2], index);
}

void GfMenuObjHanaCustom::setupItemInfo(ui::UIObjectAcc &acc, GfMenuItemList *list) {
  mm::mtl::FixStr<32> name;
  name.format("TXT_parts_ennum@%02d", 1);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 15, list, -1, false);
  name.format("TXT_sparts_etxt@%02d", 1);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 9, list, -1, false);
  name.format("TXT_ptpdf_num@%02d", 1);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 18, list, -1, false);
  name.format("TXT_ptedf_num@%02d", 1);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 19, list, -1, false);
  name.format("TXT_ptsp_num@%02d", 1);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 20, list, -1, false);
  name.format("TXT_ptrl_name@%02d", 1);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 22, list, -1, false);
  name.format("TXT_ptsp_id_hpmax@%02d", 1);
  GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 21, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown70 = 0;
  }
  name.format("TXT_ptsp_id_str@%02d", 1);
  adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 21, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown70 = 1;
  }
  name.format("TXT_ptsp_id_ether@%02d", 1);
  adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 21, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown70 = 2;
  }
  name.format("TXT_ptsp_id_dex@%02d", 1);
  adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 21, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown70 = 3;
  }
  name.format("TXT_ptsp_id_agi@%02d", 1);
  adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 21, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown70 = 4;
  }
  name.format("TXT_ptsp_id_luck@%02d", 1);
  adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 21, list, -1, false);
  if (adapter != nullptr) {
    adapter->unknown70 = 5;
  }
}

void GfMenuObjHanaCustom::refreshItemInfo(ui::UIObjectAcc &acc, GfMenuItemList *list, u32 type, u32 index) {
  mm::mtl::FixStr<32> name;
  switch (type) {
  case 0:
    name.format("LAY_ptinfo01@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo02@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo03@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo04@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    break;
  case 1:
    name.format("LAY_ptinfo01@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo02@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo03@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), true);
    name.format("LAY_ptinfo04@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    break;
  case 2:
  case 3:
  case 4:
  case 5:
    name.format("LAY_ptinfo01@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), true);
    name.format("LAY_ptinfo02@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), true);
    name.format("LAY_ptinfo03@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo04@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    break;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
    name.format("LAY_ptinfo01@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo02@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), true);
    name.format("LAY_ptinfo03@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo04@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    break;
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
    name.format("LAY_ptinfo01@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo02@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo03@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("LAY_ptinfo04@%02d", index);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), true);
    break;
  }
}

void GfMenuObjHanaCustom::refreshItemList(GfMenuItemList *list, ui::UISelectObjList *selectList, u32 type) {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < selectList->getSize(); i++) {
    MenuItemInfo &info = list->getContents(list->getPageIndex(i));
    ui::UIObjectAcc acc(selectList->getObject(i));
    name.format("TXT_sbpartsname@%02d", i + 1);
    ui::UIObjectAcc partsName(acc.searchChild(name.c_str()));
    RESULT_HANA result;
    if (!GfMenuHanaAdapter::isEquipParts(blade, type, info.unknown04, result)) {
      GfMenuObjUtil::setColMulandAdd(partsName.unknown10, "txt_disable");
    }
    u32 user = GfMenuItemUtil::searchEquipHanaParts(type, info.unknown04, info.unknown0c);
    bool isUsed = user != 0;
    mm::mtl::FixStr<32> useName;
    useName.format("TXT_sbpartsuse@%02d", i + 1);
    ui::UIObjectAcc partsUse(acc.searchChild(useName.c_str()));
    partsUse.setDisp(isUsed);
    if (isUsed) {
      DataParamAcc userAcc(OBJECT_TYPE_BLADE, user, GIMMICK_TYPE_UNKNOWN_0);
      partsUse.setText(GfMenuObjUtil::getName(userAcc));
      GfMenuObjUtil::setColMulandAdd(partsUse.unknown10, user == blade ? "txt_normal" : "txt_disable");
    }
  }
}

void GfMenuObjHanaCustom::refreshPartsList(ui::UIObjectAcc &acc, mm::mtl::FixedArray<GfMenuIDList *, 7> &lists) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_MODE);
  int top = Bdat::getIdTop(bdat);
  int count = Bdat::getIdCount(bdat);
  mm::mtl::FixStr<32> name;
  for (int i = 0; i != count; i++) {
    u16 set = Bdat::getVal(bdat, "BASE_SET", i + top).valueU16;
    if (set != 0) {
      u32 size = chkSameSlot(lists, set);
      name.format("IMG_parts_base@%02d", i + 1);
      ui::UIObjectAcc base(acc.searchChild(name.c_str()));
      mm::mtl::FixStr<32> animation;
      if (getEquipSlot(lists, set) != 0) {
        animation.format("icon_%d_set", size);
      } else {
        animation.format("icon_%d", size);
      }
      base.startAnimation(animation.c_str(), false);
    }
  }
}

void GfMenuObjHanaCustom::updatePartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *selectList, mm::mtl::FixedArray<GfMenuIDList *, 7> &lists) {
  int blade = GfMenuReference::getReferenceBladeID(0);
  list->clear();
  if (blade >= BLADE_UNKNOWN_1005 && blade <= BLADE_UNKNOWN_1007) {
    for (u32 i = 0; i < 7; i++) {
      lists[i]->clear();
    }
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_MODE);
    int top = Bdat::getIdTop(bdat);
    int count = Bdat::getIdCount(bdat);
    for (int i = 0; i != count; i++) {
      MenuID id = {};
      id.unknown00 = Bdat::getVal(bdat, unknown002[blade - BLADE_UNKNOWN_1005], i + top).valueU16;
      if (id.unknown00 != 0) {
        int index;
        switch (id.unknown00) {
        case 1:
        case 2:
        case 3:
        case 6:
        case 9:
        case 12:
        case 15:
          lists[list->getSize()]->addContents(id);
          list->addContents(id);
          continue;
        case 4:
        case 5:
          index = searchIdList(list, 3);
          break;
        case 7:
        case 8:
          index = searchIdList(list, 6);
          break;
        case 10:
        case 11:
          index = searchIdList(list, 9);
          break;
        case 13:
        case 14:
          index = searchIdList(list, 12);
          break;
        default:
          continue;
        }
        lists[index]->addContents(id);
      }
    }
  }
}

void GfMenuObjHanaCustom::setupPartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *selectList, GfMenuReferenceItem *item, mm::mtl::FixedArray<GfMenuIDList *, 7> &lists) {
  mm::mtl::FixStr<32> name;
  selectList->clear();
  selectList->pickupObject(acc.unknown10, "LAY_hplist_tag@%02d", 1);
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_MODE);
  int top = Bdat::getIdTop(bdat);
  int count = Bdat::getIdCount(bdat);
  for (int i = 0; i != count; i++) {
    u32 set = Bdat::getVal(bdat, "BASE_SET", i + top).valueU16;
    if (set != 0) {
      u32 size = chkSameSlot(lists, set);
      name.format("TXT_partsname@%02d", i + 1);
      GfMenuHanaPartsAdapter::create(acc.searchChild(name.c_str()), 0, set, false);
      ui::UIObjectAcc partsName(acc.searchChild(name.c_str()));
      mm::Rect<s16> rect;
      acc.getLayoutRect(unknown003[size - 1], rect);
      mm::Pnt<s16> center(rect.x + rect.width / 2, rect.y + rect.height / 2);
      partsName.setPosCenter(center);
      for (u32 j = 0; j < 3; j++) {
        u32 parts = j < size ? set + j : 0;
        name.format("IMG_partsicon@%02d%02d", i + 1, j + 1);
        GfMenuHanaAdapter *adapter = GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild(name.c_str()), 7, 0, false);
        if (adapter != nullptr) {
          adapter->unknown58 = parts;
        }
        adapter = GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild(name.c_str()), 11, 0, true);
        if (adapter != nullptr) {
          adapter->unknown58 = parts;
        }
        name.format("IMG_partsbase@%02d%02d", i + 1, j + 1);
        adapter = GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild(name.c_str()), 10, 0, true);
        if (adapter != nullptr) {
          adapter->unknown58 = parts;
        }
      }
    }
  }
  GfMenuHanaPartsAdapter::createFromList(acc.searchChild("IMG_hp_partsinfo_icon"), 1, list, -1, false);
  GfMenuHanaPartsAdapter::createFromList(acc.searchChild("TXT_hp_partsinfo_cate_name"), 0, list, -1, false);
  GfMenuItemAdapter::createFromReference(acc.searchChild("TXT_hp_partsinfo_name"), 0, item, false);
  name.format("TXT_parts_ennum@%02d", 2);
  GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 15, item, false);
  name.format("TXT_sparts_etxt@%02d", 2);
  GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 9, item, false);
  name.format("TXT_ptrl_name@%02d", 2);
  GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 22, item, false);
  name.format("TXT_ptsp_num@%02d", 2);
  GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 20, item, false);
  name.format("TXT_ptpdf_num@%02d", 2);
  GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 18, item, false);
  name.format("TXT_ptedf_num@%02d", 2);
  GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 19, item, false);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_parts_ennum@03"), 2, 0, true);
  name.format("TXT_ptsp_id_hpmax@%02d", 2);
  GfMenuItemAdapter *itemAdapter = GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 21, item, false);
  if (itemAdapter != nullptr) {
    itemAdapter->unknown70 = 0;
  }
  name.format("TXT_ptsp_id_str@%02d", 2);
  itemAdapter = GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 21, item, false);
  if (itemAdapter != nullptr) {
    itemAdapter->unknown70 = 1;
  }
  name.format("TXT_ptsp_id_ether@%02d", 2);
  itemAdapter = GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 21, item, false);
  if (itemAdapter != nullptr) {
    itemAdapter->unknown70 = 2;
  }
  name.format("TXT_ptsp_id_dex@%02d", 2);
  itemAdapter = GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 21, item, false);
  if (itemAdapter != nullptr) {
    itemAdapter->unknown70 = 3;
  }
  name.format("TXT_ptsp_id_agi@%02d", 2);
  itemAdapter = GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 21, item, false);
  if (itemAdapter != nullptr) {
    itemAdapter->unknown70 = 4;
  }
  name.format("TXT_ptsp_id_luck@%02d", 2);
  itemAdapter = GfMenuItemAdapter::createFromReference(acc.searchChild(name.c_str()), 21, item, false);
  if (itemAdapter != nullptr) {
    itemAdapter->unknown70 = 5;
  }
}

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

u32 GfMenuObjHanaCustom::getEquipSlot(mm::mtl::FixedArray<GfMenuIDList *, 7> &lists, u32 parts) {
  EquipHana *equip = GfDataHana::getEquipParts(GfMenuReference::getReferenceBladeID(0));
  u32 slot = 0;
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
