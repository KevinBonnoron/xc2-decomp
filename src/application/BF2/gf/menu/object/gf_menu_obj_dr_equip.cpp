#include "gf/menu/object/gf_menu_obj_dr_equip.h"

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_common_detail.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/util/gf_equip_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7b;

GfMenuObjDrEquip::GfMenuObjDrEquip(u32 handle)
    : GfMenuObject(handle), unknown24(0), m_menuItemList(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(this), unknown2e0(-1) {}

GfMenuObjDrEquip::~GfMenuObjDrEquip() {
  mm::mtl::safeRelease(m_menuItemList);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  unknown2e8 = nullptr;
}

void GfMenuObjDrEquip::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!main.isValid()) {
    return;
  }
  unknown24 = 0;
// __LINE__ must be 76 as in the original file: it is the line argument of operator new.
#line 76
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  {
    ui::UIObjectAcc equip(main.unknown10, "LAY_equip");
    GfMenuItemAdapter::createFromReferenceDriverEquip(equip.searchChild("TXT_equip_item_name"), 0, unknown24, 0, false);
    GfMenuItemAdapter::createFromReferenceDriverEquip(equip.searchChild("TXT_equip_item_count_num"), 3, unknown24, 0, false);
    GfMenuItemAdapter::createFromReferenceDriverEquip(equip.searchChild("TXT_equip_item_count_max"), 4, unknown24, 0, false);
    GfMenuItemAdapter::createFromReferenceDriverEquip(equip.searchChild("IMG_equip_item_rare_icon"), 7, unknown24, 0, false);
  }
  {
    ui::UIObjectAcc item(main.unknown10, "LAY_item");
// __LINE__ must be 119 as in the original file: it is the line argument of operator new.
#line 119
    ItemListener *itemListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListener(this);
    itemListener->addRef();
    ui::UIEventManager::get()->registObjectListener(item.unknown10, itemListener);
    if (itemListener != nullptr) {
      itemListener->release();
    }
    {
      ui::UISelectObjList::CreateParam createParam = {};
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown30 = ui::UISelectObjList::create(createParam);
    }
    if (unknown30 == nullptr) {
      return;
    }
    unknown30->pickupObject(item.unknown10, "LAY_item@%02d", 1);
    if (unknown30->getSize() != 0) {
      GfMenuItemList::ItemBoxSetup setup;
      mm::mtl::FixStr<32> name;
      m_menuItemList = GfMenuItemList::create();
      if (m_menuItemList != nullptr) {
        setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_2;
        setup.m_setupParam.unknown08 = unknown30->getSize();
        m_menuItemList->setupFromBox(setup);
      }
      for (u32 i = 0; i < unknown30->getSize(); i++) {
        name.format("TXT_item_name@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, m_menuItemList, i, false);
        name.format("LAY_item@%02d", i + 1);
        GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 8, m_menuItemList, i, true);
      }
    }
    if (m_menuItemList->getSize() != 0) {
      ui::UICtrlCursorSelect::CursorSetting setting;
      setting.unknown18 = 1;
      setting.setType(0);
      setting.unknown1a = -8;
      unknown38 = ui::UICtrlCursorSelect::create(item.searchChild("IMG_item_cursor"), setting, unknown30);
      if (unknown38 != nullptr) {
        setupInputSelectionFromList(item.unknown10, *m_menuItemList);
      }
      unknown2e8 = GfMenuReferenceItem::unknown001();
      GfMenuItemAdapter::createFromReference(item.searchChild("TXT_item_detail_count_num"), 3, unknown2e8.get(), false);
      GfMenuItemAdapter::createFromReference(item.searchChild("TXT_item_detail_count_max"), 4, unknown2e8.get(), false);
      GfMenuItemAdapter::createFromReference(item.searchChild("IMG_item_detail_rare_icon"), 7, unknown2e8.get(), false);
      GfMenuObjUtil::createVScrollBarPlugin(item.searchChild("IMG_item_list_scroll_bar"), m_menuItemList, "IMG_item_list_scroll_base", true);
    }
  }
  {
    GfMenuObjCommonDetail::OpenParam param;
    unknown40 = GfMenuCallContext::create();
    param.unknown1c = 0;
    param.unknown18 = unknown24;
    param.unknown28 = true;
    param.unknown30 = unknown24;
    param.unknown00.push_back(0x1c0);
    param.unknown2c = main.searchChild("LAY_equip_status");
    main.getLayoutRect("status_position", param.unknown20);
    GfMenuObjCommonDetail::open(unknown40, param);
    GfMenuReference::resetDriverVirtual();
  }
  GfMenuObject::initialize();
}

void GfMenuObjDrEquip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrEquip::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjDrEquip::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjDrEquip::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item"));
}

void GfMenuObjDrEquip::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item"));
}

bool GfMenuObjDrEquip::seqStartOpen() {
  suspendInput();
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjDrEquip::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjDrEquip::seqStartClose() {
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjDrEquip::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjDrEquip::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjDrEquip::seqLeavePhase1() { return unknown002(2); }

void GfMenuObjDrEquip::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    m_menuObjDrEquip->unknown50.unknown002(&GfMenuObjDrEquip::seqStartOpen);
    m_menuObjDrEquip->unknown50.unknown002(&GfMenuObjDrEquip::seqAppearPhase1);
    m_menuObjDrEquip->unknown50.unknown002(&GfMenuObjDrEquip::seqEndOpen);
    break;
  case 2:
    m_menuObjDrEquip->unknown50.unknown002(&GfMenuObjDrEquip::seqStartClose);
    m_menuObjDrEquip->unknown50.unknown002(&GfMenuObjDrEquip::seqLeavePhase1);
    m_menuObjDrEquip->unknown50.unknown002(&GfMenuObjDrEquip::seqEndClose);
    break;
  case 8: {
    int result = event.unknown0c;
    u32 driver = GfMenuReference::getReferenceDriverID(m_menuObjDrEquip->unknown24);
    if (result == 2) {
      GfMenuObject::returnFSSubLayer(acc.unknown10, 2);
    } else if (result == 9) {
      if (GfDataDriver::getEquipAcce(driver, 0) != 0) {
        if (m_menuObjDrEquip->unknown48 == nullptr) {
          m_menuObjDrEquip->unknown48 = GfMenuCallContext::create();
        }
        m_menuObjDrEquip->unknown48->reset();
        GfMenuObjCommonText::open(m_menuObjDrEquip->unknown48, 0x18, 0);
        GfMenuObject::setCallContextEventHandler(m_menuObjDrEquip->unknown48, acc.unknown10);
        m_menuObjDrEquip->suspendInput();
      }
    }
    break;
  }
  case 0x41:
    if (m_menuObjDrEquip->unknown48->unknown0c == event.unknown08) {
      if (event.unknown10_u16 == 0) {
        u32 driver = GfMenuReference::getReferenceDriverID(m_menuObjDrEquip->unknown24);
        // The game keeps the bounds asserts of this read (vector.h lines 0x152 and 0x153) but never uses the item: the accessory is unequipped with the constant 0
        // (ruling 2026-11-13 #5: statement without effect that the game holds).
        m_menuObjDrEquip->m_menuItemList->getContents(m_menuObjDrEquip->m_menuItemList->getIndex(false));
        GfItemHandle item(0);
        GfEquipUtil::equipDriverAcce(driver, 0, 0, item);
      }
      m_menuObjDrEquip->resumeInput();
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrEquip>(const mm::mtl::Delegate<bool()> *);
