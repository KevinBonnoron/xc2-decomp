#include "gf/menu/object/gf_menu_obj_hana_parts_make.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_hana.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/adapter/gf_menu_hana_adapter.h"
#include "gf/menu/adapter/gf_menu_hana_parts_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_color.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjHanaPartsMake::GfMenuObjHanaPartsMake(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown70(0), unknown74(0) {}

GfMenuObjHanaPartsMake::~GfMenuObjHanaPartsMake() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown58);
  unknown60 = nullptr;
  unknown68 = nullptr;
}

void GfMenuObjHanaPartsMake::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsMake::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsMake::getCrystalItemCount(u32 item) { return GfGameUtilHana::getConvertToEther(item); }

u16 GfMenuObjHanaPartsMake::getFirstSortTableId(u32 type, u32 isEquip) {
  if (isEquip != 0) {
    return GfMenuHanaAdapter::getSortTableId(type);
  }
  return GfMenuHanaAdapter::getMakeSortTableId(type);
}

u32 GfMenuObjHanaPartsMake::getMakeItemCount(u32 parts) {
  ItemProperty property;
  GfItemUtil::getProperty(property, parts, 0);
  u32 needEther = property.unknown68;
  u32 count = GfDataHana::getEther() / needEther;
  return mm::min(GfGameUtilHana::getEmptyParts(parts), count);
}

RESULT_HANA GfMenuObjHanaPartsMake::makeParts(u32 type, u32 parts) {
  switch (type) {
  case 1:
    return GfGameUtilHana::exchangeRoleParts(parts);
  case 2:
    return GfGameUtilHana::exchangeAttributeParts(parts);
  case 3:
    return GfGameUtilHana::exchangeNArtsParts(parts);
  case 6:
    return GfGameUtilHana::exchangeCondenserParts(parts);
  case 9:
    return GfGameUtilHana::exchangeArtsParts(parts);
  }
  return RESULT_HANA_UNKNOWN_6;
}

RESULT_HANA GfMenuObjHanaPartsMake::crystalParts(u32 type, u32 parts) {
  switch (type) {
  case 1:
  case 2:
  case 3:
  case 6:
  case 9:
    return GfGameUtilHana::execConvertToEther(parts);
  }
  return RESULT_HANA_UNKNOWN_8;
}

void GfMenuObjHanaPartsMake::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaPartsMake::setFadeIn(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaPartsMake::setFadeOut(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjHanaPartsMake::setupMain(ui::UIObjectAcc &acc) {
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hplist_etnum"), 0, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_num"), 1, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_enu_max"), 2, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_hn_rol"), 3, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hn_elml"), 5, 0, true);
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("IMG_hana"), 6, 0, false);
}

void GfMenuObjHanaPartsMake::setupNumSelect(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price) {
  GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_value"), number, true);
  GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_total_price"), price, true);
}

void GfMenuObjHanaPartsMake::updatePartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects) {
  list->clear();
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_HANA_MODE);
  int top = Bdat::getIdTop(bdat);
  u32 count = Bdat::getIdCount(bdat);
  for (u32 i = 0; i < count; i++) {
    MenuID id = {};
    id.unknown00 = Bdat::getVal(bdat, "ITEM_MAKE", top + i).valueU16;
    if (id.unknown00 != 0) {
      list->addContents(id);
    }
  }
}

void GfMenuObjHanaPartsMake::setupPartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects) {
  mm::mtl::FixStr<32> name;
  objects->clear();
  objects->pickupObject(acc.unknown10, "LAY_hplist_tag@%02d", 1);
  for (u32 i = 0; i < objects->getSize(); i++) {
    name.format("TXT_partsname@%02d", i + 1);
    GfMenuHanaPartsAdapter *adapter = GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    if (adapter != nullptr) {
      name.format("LAY_mplist_tag@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_partsicon@%02d01", i + 1);
    GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.c_str()), 1, list, i, false);
  }
}

// Inferred role: parts type and item type of a parts category; original name unknown.
struct unknown001 {
  u32 unknown00;
  ItemType::Type unknown04;
};

// Inferred role: parts categories; original name unknown.
static const unknown001 unknown002[] = {
    {1, ItemType::HANA_ROLE},
    {2, ItemType::HANA_ATR},
    {3, ItemType::HANA_N_ARTS_SET},
    {9, ItemType::HANA_ARTS_ENH},
    {6, ItemType::HANA_ASSIST},
};

void GfMenuObjHanaPartsMake::makeCategoryItemList(GfMenuIDList *idList, GfMenuItemList *itemList, u32 isEquip, u32 sort) {
  u32 type = idList->getContents(idList->getIndex(false)).unknown00;
  for (int i = 0; i < 5; i++) {
    if (unknown002[i].unknown00 == type) {
      updateItemList(itemList, unknown002[i].unknown04, isEquip);
      itemList->sort(GfMenuObjSort::getSortID(getFirstSortTableId(type, isEquip), sort), false);
      return;
    }
  }
}

} // namespace gf
