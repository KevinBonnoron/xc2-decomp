#include "gf/menu/object/gf_menu_obj_hana_parts_make.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_item_handle.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_hana_adapter.h"
#include "gf/menu/adapter/gf_menu_hana_parts_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_hana_custom.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "ui/ctrl/ui_ctrl_cursor_color.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the parts make layout; original name unknown.
constexpr u32 CALL_UNKNOWN_115 = 115;

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

void GfMenuObjHanaPartsMake::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 144 as in the original file: it is the line argument of operator new.
#line 144
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_115, main);
  u32 partsWindow = acc.searchChild("LAY_partsmake_window");
// __LINE__ must be 150 as in the original file: it is the line argument of operator new.
#line 150
  PartsListListener *partsListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PartsListListener(this);
  partsListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(partsWindow, partsListListener);
  if (partsListListener != nullptr) {
    partsListListener->release();
  }
  u32 itemWindow = acc.searchChild("LAY_metl_window");
// __LINE__ must be 154 as in the original file: it is the line argument of operator new.
#line 154
  ItemListListener *itemListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
  itemListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(itemWindow, itemListListener);
  if (itemListListener != nullptr) {
    itemListListener->release();
  }
  u32 dialog = acc.searchChild("LAY_make_diarog");
// __LINE__ must be 158 as in the original file: it is the line argument of operator new.
#line 158
  NumSelectListener *numSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) NumSelectListener(this);
  numSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(dialog, numSelectListener);
  if (numSelectListener != nullptr) {
    numSelectListener->release();
  }
  unknown40 = GfMenuItemList::create();
  ui::UISelectObjList::CreateParam createParam;
  createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown48 = ui::UISelectObjList::create(createParam);
  unknown28 = GfMenuIDList::create();
  ui::UIListInfoBase::SetupParam setup;
  setup.unknown08 = 5;
  setup.unknown10 = true;
  unknown28->setup(getAllocator(ALLOCATOR_UNKNOWN_0), setup);
  createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown30 = ui::UISelectObjList::create(createParam);
  unknown58 = GfMenuCallContext::create();
  unknown60 = unknown160();
  unknown60->unknown162(0);
  unknown60->unknown166(99);
  unknown68 = unknown160();
  unknown68->unknown162(0);
  unknown68->unknown166(999999999);
  GfMenuObject::initialize();
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

void GfMenuObjHanaPartsMake::refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *objects, u32 type, u32 isEquip) {
  GfMenuReference::getReferenceBladeID(0);
  {
    ui::UIObjectAcc baseMake(acc.searchChild("IMG_melist_base_make"));
    ui::UIObjectAcc baseCrystal(acc.searchChild("IMG_melist_base_crystal"));
    ui::UIObjectAcc titleMake(acc.searchChild("TXT_melist_title_make"));
    ui::UIObjectAcc titleCrystal(acc.searchChild("TXT_melist_title_crystal"));
    ui::UIObjectAcc colMake(acc.searchChild("TXT_melist_col_make"));
    ui::UIObjectAcc colCrystal(acc.searchChild("TXT_melist_col_crystal"));
    bool isMake = isEquip == 0;
    baseMake.setDisp(isMake);
    baseCrystal.setDisp(!isMake);
    titleMake.setDisp(isMake);
    titleCrystal.setDisp(!isMake);
    colMake.setDisp(isMake);
    colCrystal.setDisp(!isMake);
    for (u32 i = 0; i < 9; i++) {
      mm::mtl::FixStr<32> name;
      name.format("LAY_sbparts_make@%02d", i + 1);
      ui::UIObjectAcc make(acc.searchChild(name.c_str()));
      make.setDisp(isMake);
      name.format("LAY_sbparts_crystal@%02d", i + 1);
      ui::UIObjectAcc crystal(acc.searchChild(name.c_str()));
      crystal.setDisp(!isMake);
    }
  }
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    u32 parts = list->getContents(list->getPageIndex(i)).unknown04;
    ui::UIObjectAcc object(objects->getObject(i));
    name.format("TXT_sbpartsname@%02d", i + 1);
    ui::UIObjectAcc text(object.searchChild(name.c_str()));
    RESULT_HANA result;
    const char *color;
    if (isEquip == 0) {
      color = GfMenuHanaAdapter::isMakeParts(type, parts, result) ? "txt_normal2" : "txt_disable";
    } else {
      color = GfMenuHanaAdapter::isCrystalParts(type, parts, result) ? "txt_normal2" : "txt_disable";
    }
    GfMenuObjUtil::setColMulandAdd(text.unknown10, color);
  }
}

void GfMenuObjHanaPartsMake::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *objects) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    name.format("TXT_sbpartsname@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    if (adapter != nullptr) {
      name.format("LAY_sbparts_num@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_sbpartsicon@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false);
    name.format("TXT_sbparts_num@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, true);
    name.format("TXT_sbparts_etlnum@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0x10, list, i, false);
    name.format("TXT_reclist_stcnum@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0x11, list, i, false);
  }
  GfMenuObjHanaCustom::setupItemInfo(acc, list);
}

// Inferred role: parts type and item type of a parts category; original name unknown.
struct unknown001 {
  u32 unknown00;
  ItemType::Type unknown04;
};

// Inferred role: parts categories; original name unknown.
static const unknown001 unknown002[] = {
    {1, ItemType::ITEM_TYPE_UNKNOWN_16},
    {2, ItemType::ITEM_TYPE_UNKNOWN_17},
    {3, ItemType::ITEM_TYPE_UNKNOWN_19},
    {9, ItemType::ITEM_TYPE_UNKNOWN_18},
    {6, ItemType::ITEM_TYPE_UNKNOWN_20},
};

// Inferred role: parts type of each parts item type, indexed from ITEM_TYPE_UNKNOWN_16; original name unknown.
static const u32 unknown003[] = {1, 2, 9, 3, 6};

void GfMenuObjHanaPartsMake::updateItemList(GfMenuItemList *list, ItemType::Type type, u32 isEquip) {
  list->clear();
  if (isEquip == 0) {
    GfMenuItemList::HanaPartsSetup setup;
    setup.unknown00.unknown08 = 9;
    setup.unknown00.unknown10 = true;
    setup.unknown14 = type;
    list->setupFromHanaParts(setup);
  } else {
    GfMenuItemList::ItemBoxSetup setup;
    setup.unknown00.unknown08 = 9;
    setup.unknown00.unknown10 = true;
    setup.unknown14 = type;
    setup.unknown28 = false;
    setup.unknown29 = false;
    list->setupFromBox(setup);
    if (list->getSize() != 0) {
      // Removes the parts that searchEquipHanaParts finds equipped; the others stay and the index advances. An item
      // whose type is not a parts type is neither removed nor skipped: the game branches to the loop test without
      // advancing (b.hs at 0x7100474dd8 to 0x7100474e30).
      for (u32 i = 0; i < list->getSize();) {
        MenuItemInfo &info = list->getContents(i);
        if (info.unknown00 >= ItemType::ITEM_TYPE_UNKNOWN_16 && info.unknown00 <= ItemType::ITEM_TYPE_UNKNOWN_20) {
          // The game loads the handle (0x7100474ddc) and the item before the parts type table entry.
          GfItemHandle handle = info.unknown0c;
          u32 item = info.unknown04;
          if (!GfMenuItemUtil::searchEquipHanaParts(unknown003[info.unknown00 - ItemType::ITEM_TYPE_UNKNOWN_16], item, handle)) {
            i++;
            continue;
          }
          list->contents.erase(list->contents.begin() + i);
          list->subSize(1);
          list->contentsChanged = true;
        }
      }
      if (list->getSize() != 0) {
        for (u32 i = 0; i < list->getSize() - 1; i++) {
          MenuItemInfo &first = list->getContents(i);
          ItemType::Type kind = first.unknown00;
          u32 item = first.unknown04;
          for (u32 j = i + 1; j < list->getSize();) {
            MenuItemInfo &other = list->getContents(j);
            if (kind == other.unknown00 && item == other.unknown04) {
              list->getContents(i).unknown08++;
              list->contents.erase(list->contents.begin() + j);
              list->subSize(1);
              list->contentsChanged = true;
            } else {
              j++;
            }
          }
        }
      }
    }
  }
}

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

void GfMenuObjHanaPartsMake::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMain(acc);
    GfMenuObjOperationInfo::setGuideText(0x19, 0);
    GfMenuObjMainMenu2::setSubIndexText(0x1a);
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

void GfMenuObjHanaPartsMake::NumSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  // The game calls getReferenceBladeID(0) here and drops the result (bl at 0x710047418c).
  GfMenuReference::getReferenceBladeID(0);
  switch (event.unknown00) {
  case 1:
    setupNumSelect(acc, unknown20->unknown60, unknown20->unknown68);
    acc.setDisp(false);
    break;
  case 6: {
    int count = event.unknown08;
    int previous = event.unknown0c;
    unknown20->unknown60->unknown162(count);
    u32 parts = unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown04;
    ItemProperty property;
    GfItemUtil::getProperty(property, parts, 0);
    unknown20->unknown68->unknown0c = (unknown20->unknown70 == 0 ? property.unknown68 : property.unknown6c) * count;
    if (previous != -1 && count != previous) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      u32 type = unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00;
      u32 parts = unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown04;
      u32 count = unknown20->unknown60->unknown0c;
      if (count != 0) {
        for (u32 i = 0; i < count; i++) {
          if (unknown20->unknown70 == 0) {
            makeParts(type, parts);
          } else {
            crystalParts(type, parts);
          }
        }
        if (unknown20->unknown70 == 0) {
          GfMenuObjUtil::playSE(0x14);
        } else {
          GfMenuObjUtil::playSE(0x15);
        }
        if (unknown20->unknown70 == 0) {
          unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown08 += count;
        } else {
          makeCategoryItemList(unknown20->unknown28, unknown20->unknown40, unknown20->unknown70, unknown20->unknown74);
          u32 selected = unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00;
          refreshItemList(acc, unknown20->unknown40, unknown20->unknown48, selected, unknown20->unknown70);
          if (unknown20->unknown40->getSize() == 0) {
            unknown164(handle, GfMenuTypes::unknown003_258);
            unknown163(owner.searchChild("LAY_partsmake_window"), GfMenuTypes::unknown003_257, 0);
            break;
          }
        }
        unknown164(handle, GfMenuTypes::unknown003_258);
        unknown163(owner.searchChild("LAY_metl_window"), GfMenuTypes::unknown003_257, 0);
      }
      break;
    }
    case 2:
      unknown164(handle, GfMenuTypes::unknown003_258);
      unknown163(owner.searchChild("LAY_metl_window"), GfMenuTypes::unknown003_257, 0);
      GfMenuObjUtil::playSECommonCancel();
      break;
    }
    break;
  case GfMenuTypes::unknown003_257: {
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    setFadeIn(handle, 0);
    u32 parts = unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown04;
    bool isMake = unknown20->unknown70 == 0;
    ui::UIObjectAcc(acc.searchChild("LAY_select_make")).setDisp(isMake);
    ui::UIObjectAcc(acc.searchChild("LAY_select_crystal")).setDisp(!isMake);
    u32 max;
    if (unknown20->unknown70 == 0) {
      max = getMakeItemCount(parts);
    } else {
      max = getCrystalItemCount(parts);
    }
    GfMenuObject::setupInputSelection(handle, 0, max + 1);
    GfMenuObject::enableInput(handle);
    unknown20->unknown60->unknown166(max);
    break;
  }
  case GfMenuTypes::unknown003_258:
    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
    setFadeOut(handle, 0);
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
