#include "gf/menu/object/gf_menu_obj_bl_equip.h"

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_item_handle.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x69;

GfMenuObjBlEquip::GfMenuObjBlEquip(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown58(nullptr), unknown60(0) {
  unknown58 = GfMenuCallContext::create();
}

GfMenuObjBlEquip::~GfMenuObjBlEquip() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
}

void GfMenuObjBlEquip::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 129 as in the original file: it is the line argument of operator new.
#line 129
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 slot = acc.searchChild("LAY_eqpac_slot");
// __LINE__ must be 134 as in the original file: it is the line argument of operator new.
#line 134
  SlotListener *slotListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SlotListener(this);
  slotListener->addRef();
  ui::UIEventManager::get()->registObjectListener(slot, slotListener);
  if (slotListener != nullptr) {
    slotListener->release();
  }
  u32 list = acc.searchChild("LAY_stockac_list");
// __LINE__ must be 138 as in the original file: it is the line argument of operator new.
#line 138
  ItemSelectListener *itemSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemSelectListener(this);
  itemSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(list, itemSelectListener);
  if (itemSelectListener != nullptr) {
    itemSelectListener->release();
  }
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown40 = ui::UISelectObjList::create(param);
  unknown28 = GfMenuItemList::create();
  ui::UIListInfoBase::SetupParam itemParam;
  itemParam.unknown08 = 3;
  unknown28->setup(getAllocator(ALLOCATOR_UNKNOWN_0), itemParam);
  unknown38 = GfMenuItemList::create();
  unknown48 = GfMenuCallContext::create();
  disableInput(acc.searchChild("LAY_eqpac_slot"));
  disableInput(acc.searchChild("LAY_stockac_list"));
  GfMenuObject::initialize();
}

void GfMenuObjBlEquip::updateEquipItemList(GfMenuItemList *list) {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  u32 equipOrbMax = GfEquipUtil::getEquipOrbMax(blade);
  list->clear();
  for (u32 slot = 0; slot < equipOrbMax; slot++) {
    MenuItemInfo info;
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_3;
    info.unknown04 = GfEquipUtil::getEquipBladeOrb(blade, slot);
    info.unknown08 = info.unknown04 != 0;
    list->addContents(info);
  }
}

void GfMenuObjBlEquip::setupSlot(ui::UIObjectAcc &acc, GfMenuItemList *list) {
  mm::mtl::FixStr<32> name;
  updateEquipItemList(list);
  GfMenuReference::getReferenceBladeID(0);
  name.format("IMG_asc_icon@%02d", 1);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 10, list, 0, false);
  name.format("IMG_asc_icon@%02d", 2);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 10, list, 1, false);
  name.format("IMG_asc_icon@%02d", 3);
  GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 10, list, 2, false);
  GfMenuItemAdapter::createFromList(acc.searchChild("TXT_eqasc_name"), 0, list, -1, false);
  GfMenuItemAdapter::createFromList(acc.searchChild("TXT_eqpasc_iftxt"), 9, list, -1, false);
  GfMenuItemAdapter::createFromList(acc.searchChild("IMG_eqp_raicon"), 7, list, -1, false);
  for (u32 slot = 1; slot < 4; slot++) {
    name.format("IMG_slot_select@%02d", slot);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
    name.format("IMG_slot_hold@%02d", slot);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  }
}

void GfMenuObjBlEquip::refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList, u32 slot) {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  for (u32 i = 0; i < selectList->getSize(); i++) {
    MenuItemInfo &info = list->getContents(list->getPageIndex(i));
    mm::mtl::FixStr<32> name;
    u32 user = GfMenuItemUtil::searchEquipOrb(info.unknown04, info.unknown0c, nullptr);
    bool isUsed = user != 0;
    name.format("TXT_list_use@%02d", i + 1);
    ui::UIObjectAcc use(acc.searchChild(name.c_str()));
    use.setDisp(isUsed);
    if (isUsed) {
      DataParamAcc userAcc(OBJECT_TYPE_BLADE, user, GIMMICK_TYPE_UNKNOWN_0);
      use.setText(GfMenuObjUtil::getName(userAcc));
      GfMenuObjUtil::setColMulandAdd(use.unknown10, user == blade ? "txt_normal" : "txt_disable");
    }
    ItemType::Type type = info.unknown00;
    name.format("LAY_list_use@%02d", i + 1);
    ui::UIObjectAcc(acc.searchChild(name.c_str())).setDisp(type == ItemType::ITEM_TYPE_UNKNOWN_3);
    name.format("LAY_list_num@%02d", i + 1);
    ui::UIObjectAcc(acc.searchChild(name.c_str())).setDisp(type != ItemType::ITEM_TYPE_UNKNOWN_3);
    name.format("TXT_aslist_name@%02d", i + 1);
    ui::UIObjectAcc orbName(acc.searchChild(name.c_str()));
    u32 result = GfMenuItemUtil::canEquipOrb(info.unknown04, info.unknown0c, blade, slot);
    if (result == 1 || result == 3 || result == 4) {
      GfMenuObjUtil::setColMulandAdd(orbName.unknown10, "txt_disable");
    } else {
      orbName.loadDefColor();
    }
  }
}

void GfMenuObjBlEquip::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList) {
  selectList->pickupObject(acc.unknown10, "LAY_stcklist@%02d", 1);
  if (selectList->getSize() != 0 && list != nullptr) {
    GfMenuItemList::ItemBoxSetup setup;
    setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_3;
    setup.unknown28 = false;
    setup.unknown00.unknown08 = selectList->getSize();
    setup.unknown00.unknown10 = true;
    list->setupFromBox(setup);
    if (list->getSize() == 0) {
      ui::UIListInfoBase::SetupParam param = setup.unknown00;
      list->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
    }
    mm::mtl::FixedVector<GfItem, 1024> items;
    GfItemUtil::getInfo(items, ItemType::ITEM_TYPE_UNKNOWN_9, false);
    for (GfItem *it = items.begin(); it != items.end(); ++it) {
      MenuItemInfo info;
      info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_9;
      info.unknown04 = it->unknown00;
      info.unknown0c = it->unknown08;
      info.unknown08 = it->unknown02;
      list->addContents(info);
    }
    GfMenuAdapterManager::beginAddAfter();
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < selectList->getSize(); i++) {
      name.format("IMG_aslist_icon@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false);
      name.format("TXT_aslist_name@%02d", i + 1);
      GfMenuItemAdapter *orbName = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
      if (orbName != nullptr) {
        name.format("LAY_stcklist@%02d", i + 1);
        orbName->unknown24 = acc.searchChild(name.c_str());
      }
      name.format("IMG_list_rea@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 7, list, i, false);
      name.format("TXT_list_num@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false);
      name.format("TXT_list_max@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 4, list, i, false);
    }
    GfMenuAdapterManager::endAddAfter();
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_stockasc_info"), 9, list, -1, false);
    GfMenuItemAdapter::createFromList(acc.searchChild("TXT_stac_prisenum"), 5, list, -1, false);
    ui::UIObjectAcc stock(acc.searchChild("IMG_stock_icon"));
    stock.setImageIndex(1);
  }
}

void GfMenuObjBlEquip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlEquip::update() { GfMenuObject::update(); }

void GfMenuObjBlEquip::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlEquip::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlEquip::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBlEquip::removeItem(ui::UIObjectAcc &acc, GfMenuItemList *equipList, GfMenuItemList *list, ui::UISelectObjList *selectList, u32 blade, u32 slot, GfMenuCallContext *context) {
  GfEquipUtil::equipBladeOrb(blade, 0, slot, GfItemHandle(0));
  if (equipList != nullptr && slot < equipList->contents.size()) {
    MenuItemInfo &info = equipList->contents[slot];
    info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_3;
    info.unknown04 = 0;
    info.unknown08 = 0;
    info.unknown0c = GfItemHandle(0);
  }
  refreshItemList(acc, list, selectList, slot);
  return true;
}

void GfMenuObjBlEquip::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(true);
    setFadeIn(handle);
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjCharSelect::returnSubMenu();
      GfMenuObject::returnFSSubLayer(unknown20);
    } else if (event.unknown08 == 1) {
      unknown163(acc.searchChild("LAY_eqpac_slot"), GfMenuTypes::unknown003_257, 0);
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

} // namespace gf
