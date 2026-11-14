#include "gf/menu/object/gf_menu_obj_hana_parts_crystal.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_hana_adapter.h"
#include "gf/menu/adapter/gf_menu_hana_parts_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_hana_custom.h"
#include "gf/menu/object/gf_menu_obj_hana_submenu.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_color.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the parts crystal layout; original name unknown.
constexpr u32 CALL_UNKNOWN_116 = 116;

GfMenuObjHanaPartsCrystal::GfMenuObjHanaPartsCrystal(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr) {}

GfMenuObjHanaPartsCrystal::~GfMenuObjHanaPartsCrystal() {
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

void GfMenuObjHanaPartsCrystal::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 128 as in the original file: it is the line argument of operator new.
#line 128
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_116, main);
  u32 partsWindow = acc.searchChild("LAY_partsmake_window");
// __LINE__ must be 134 as in the original file: it is the line argument of operator new.
#line 134
  PartsListListener *partsListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PartsListListener(this);
  partsListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(partsWindow, partsListListener);
  if (partsListListener != nullptr) {
    partsListListener->release();
  }
  u32 itemWindow = acc.searchChild("LAY_recry_window");
// __LINE__ must be 138 as in the original file: it is the line argument of operator new.
#line 138
  ItemListListener *itemListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
  itemListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(itemWindow, itemListListener);
  if (itemListListener != nullptr) {
    itemListListener->release();
  }
  u32 dialog = acc.searchChild("LAY_recrys_diarog");
// __LINE__ must be 142 as in the original file: it is the line argument of operator new.
#line 142
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

void GfMenuObjHanaPartsCrystal::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsCrystal::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsCrystal::getCrystalItemCount(u32 item) { return GfItemUtil::getItemBoxCount(item); }

RESULT_HANA GfMenuObjHanaPartsCrystal::crystalParts(u32 type, u32 parts) {
  // Label order from the copy the game inlines in NumSelectListener::reciveEvent (1.0.0: 0x7100471774), where the loop is unswitched on 1, 2, 3 and 9 and only 6 stays in the generic loop; this
  // function itself matches with any order.
  switch (type) {
  case 1:
  case 2:
  case 3:
  case 9:
  case 6:
    GfGameUtilHana::execConvertToEther(parts);
    break;
  }
  return RESULT_HANA_UNKNOWN_8;
}

void GfMenuObjHanaPartsCrystal::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaPartsCrystal::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaPartsCrystal::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjHanaPartsCrystal::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *objects) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    name.format("TXT_recpartsname@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    if (adapter != nullptr) {
      name.format("LAY_reclist_tag@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_recpartslicon@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false);
    name.format("TXT_reclist_ptnum@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("TXT_reclist_stcnum@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0x11, list, i, false);
  }
  GfMenuObjHanaCustom::setupItemInfo(acc, list);
}

void GfMenuObjHanaPartsCrystal::setupNumSelect(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> price) {
  GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_value"), number, true);
  GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_total_price"), price, true);
}

void GfMenuObjHanaPartsCrystal::setupPartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects) {
  mm::mtl::FixStr<32> name;
  objects->clear();
  objects->pickupObject(acc.unknown10, "LAY_mplist_tag@%02d", 1);
  for (u32 i = 0; i < objects->getSize(); i++) {
    name.format("TXT_partsname@%02d", i + 1);
    GfMenuHanaPartsAdapter *adapter = GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    if (adapter != nullptr) {
      name.format("LAY_mplist_tag@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_partsicon@%02d", i + 1);
    GfMenuHanaPartsAdapter::createFromList(acc.searchChild(name.c_str()), 1, list, i, false);
  }
  GfMenuHanaAdapter::createFromReferenceIndex(acc.searchChild("TXT_mplist_etnum"), 0, 0, true);
  ui::UIObjectAcc picture(acc.searchChild("IMG_mplist_pic"));
  picture.startAnimation("loop", false);
}

void GfMenuObjHanaPartsCrystal::updatePartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *objects) {
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

void GfMenuObjHanaPartsCrystal::updateItemList(GfMenuItemList *list, ItemType::Type type) {
  list->clear();
  GfMenuItemList::ItemBoxSetup setup;
  setup.unknown00.unknown08 = 10;
  setup.unknown14 = type;
  setup.unknown28 = false;
  setup.unknown29 = false;
  list->setupFromBox(setup);
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

void GfMenuObjHanaPartsCrystal::makeCategoryItemList(GfMenuIDList *idList, GfMenuItemList *itemList) {
  u32 type = idList->getContents(idList->getIndex(false)).unknown00;
  for (int i = 0; i < 5; i++) {
    if (unknown002[i].unknown00 == type) {
      updateItemList(itemList, unknown002[i].unknown04);
      return;
    }
  }
}

void GfMenuObjHanaPartsCrystal::refreshItemList(GfMenuItemList *list, ui::UISelectObjList *objects, u32 unknown) {}

void GfMenuObjHanaPartsCrystal::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(0x1a, 0);
    setFadeIn(handle);
    break;
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjHanaSubmenu::returnHanaSubMenu();
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjHanaPartsCrystal::NumSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  GfMenuReference::getReferenceBladeID(0);
  switch (event.unknown00) {
  case 1:
    setupNumSelect(acc, unknown20->unknown60, unknown20->unknown68);
    acc.setDisp(false);
    break;
  case 6: {
    int count = event.unknown08;
    unknown20->unknown60->unknown162(count);
    u32 parts = unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown04;
    ItemProperty property;
    GfItemUtil::getProperty(property, parts, 0);
    unknown20->unknown68->unknown0c = property.unknown6c * count;
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      u32 type = unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00;
      u32 parts = unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown04;
      u32 count = unknown20->unknown60->unknown0c;
      for (u32 i = 0; i < count; i++) {
        crystalParts(type, parts);
      }
    }
    case 2:
      unknown164(handle, GfMenuTypes::unknown003_258);
      unknown163(owner.searchChild("LAY_recry_window"), GfMenuTypes::unknown003_257, 0);
      break;
    }
    break;
  case GfMenuTypes::unknown003_257:
    setFadeIn(handle);
    GfMenuObject::setupInputSelection(handle, 0, getCrystalItemCount(unknown20->unknown40->getContents(unknown20->unknown40->getIndex(false)).unknown04) + 1);
    GfMenuObject::enableInput(handle);
    break;
  case GfMenuTypes::unknown003_258:
    setFadeOut(handle);
    GfMenuObject::disableInput(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
