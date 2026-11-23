#include "gf/menu/object/gf_menu_obj_pouch.h"

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "gf/game/item/gf_pouch_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_enhance_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the pouch layouts; original name unknown.
constexpr u32 CALL_UNKNOWN_89 = 89;

GfMenuObjPouch::GfMenuObjPouch(u32 handle) : GfMenuObject(handle), m_menuItemList(nullptr), unknown30(nullptr), unknown38(nullptr), m_menuCallContext(nullptr), unknown48(0), unknown4c(0) {}

GfMenuObjPouch::~GfMenuObjPouch() {
  mm::mtl::safeRelease(m_menuItemList);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(m_menuCallContext);
  unknown50 = nullptr;
}

void GfMenuObjPouch::initialize() {
  ui::UIObjectAcc acc(unknown18);
  m_menuCallContext = GfMenuCallContext::create();
  m_menuItemList = GfMenuItemList::create();
  unknown50 = GfMenuReferenceItem::unknown001();
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 110 as in the original file: it is the line argument of operator new.
#line 110
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_89, main);
  u32 pouch = acc.searchChild("LAY_pouch");
// __LINE__ must be 116 as in the original file: it is the line argument of operator new.
#line 116
  PouchListener *pouchListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PouchListener(this);
  pouchListener->addRef();
  ui::UIEventManager::get()->registObjectListener(pouch, pouchListener);
  if (pouchListener != nullptr) {
    pouchListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_89, pouch);
  u32 itemList = acc.searchChild("LAY_item_list");
// __LINE__ must be 121 as in the original file: it is the line argument of operator new.
#line 121
  ItemListListener *itemListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListListener(this);
  itemListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(itemList, itemListListener);
  if (itemListListener != nullptr) {
    itemListListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_89, itemList);
  u32 enhance = acc.searchChild("LAY_enhance");
// __LINE__ must be 126 as in the original file: it is the line argument of operator new.
#line 126
  DescriptionListener *descriptionListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DescriptionListener(this);
  descriptionListener->addRef();
  ui::UIEventManager::get()->registObjectListener(enhance, descriptionListener);
  if (descriptionListener != nullptr) {
    descriptionListener->release();
  }
  attachExternalCall(CALL_UNKNOWN_89, enhance);
  GfMenuObject::initialize();
}

void GfMenuObjPouch::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPouch::update() { GfMenuObject::update(); }

void GfMenuObjPouch::setupPouch(ui::UIObjectAcc &) {}

void GfMenuObjPouch::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPouch::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 0, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPouch::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjPouch::updateItemList(GfMenuItemList *list) {
  list->clear();
  GfMenuItemList::ItemBoxSetup setup;
  setup.unknown28 = true;
  setup.unknown29 = true;
  setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_10;
  setup.m_setupParam.unknown08 = 10;
  list->setupFromBox(setup);
}

void GfMenuObjPouch::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list) {
  mm::mtl::FixStr<32> name;
  ui::UIObjectAcc category(acc.searchChild("LAY_item_category"));
  category.setDisp(false);
  for (u32 i = 0; i < 10; i++) {
    name.format("TXT_item_name@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    name.format("LAY_item@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    name.format("TXT_item_num@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false);
  }
}

void GfMenuObjPouch::setupDescription(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceItem> &item) {
  GfMenuEnhanceAdapter::createFromReferenceItem(acc.searchChild("TXT_enhance"), 0, item.get(), true);
}

void GfMenuObjPouch::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown163(handle, GfMenuTypes::unknown003_33, 0);
    break;
  case 2:
    unknown163(handle, GfMenuTypes::unknown003_34, 0);
    break;
  case 3:
    if (event.unknown08 == 1) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObject::returnFSSubLayer(handle, 1);
    }
    break;
  case GfMenuTypes::unknown003_33:
    setFadeIn(handle);
    unknown163(acc.searchChild("LAY_pouch"), GfMenuTypes::unknown003_33, 0);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjOperationInfo::close();
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPouch::DescriptionListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(m_menuObjPouch->unknown18);
  if (event.unknown00 == 1) {
    setupDescription(acc, m_menuObjPouch->unknown50);
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjPouch::PouchListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(m_menuObjPouch->unknown18);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = handle;
    param.unknown04 = acc.searchChild("IMG_pouch_cursor");
    param.unknown1a = 1;
    param.unknown08 = "LAY_pouch_slot@%02d";
    param.m_cursorSetting.unknown18 = 5;
    m_menuObjPouch->unknown38 = GfMenuObjUtil::createCursor(param);
    GfMenuObject::disableInput(handle);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    if (m_menuObjPouch->unknown38->inputChange(index)) {
      m_menuObjPouch->unknown48 = index;
      u16 item = GfPouchUtil::getPouch(0, index).unknown04;
      MenuItemInfo &info = m_menuObjPouch->unknown50.get()->m_menuItemInfo;
      info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_10;
      info.unknown04 = item;
      info.unknown08 = 1;
      info.m_itemHandle = 0;
    }
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1:
      if (m_menuObjPouch->m_menuItemList->getSize() == 0) {
        m_menuObjPouch->m_menuCallContext->reset();
        m_menuObjPouch->unknown4c = 0x15;
        GfMenuObjCommonText::open(m_menuObjPouch->m_menuCallContext, m_menuObjPouch->unknown4c, 0);
        GfMenuObject::setCallContextEventHandler(m_menuObjPouch->m_menuCallContext, handle);
        GfMenuObject::disableInput(handle);
      } else {
        unknown164(handle, GfMenuTypes::unknown003_34);
        unknown163(owner.searchChild("LAY_item_list"), GfMenuTypes::unknown003_33, 0);
      }
      break;
    case 2:
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
      break;
    }
    break;
  case GfMenuTypes::unknown003_33:
    m_menuObjPouch->unknown38->open(0);
    GfMenuObject::setupInputSelection(handle, m_menuObjPouch->unknown48, 3);
    GfMenuObject::enableInput(handle);
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    break;
  case 0x41:
    if (m_menuObjPouch->m_menuCallContext != nullptr && m_menuObjPouch->m_menuCallContext->unknown0c == event.unknown08 && m_menuObjPouch->unknown4c == 0x15) {
      GfMenuObject::enableInput(handle);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
