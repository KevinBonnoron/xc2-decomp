#include "gf/menu/object/gf_menu_obj_bl_orb.h"

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_enhance_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/util/gf_equip_util.h"
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
constexpr u32 unknown001 = 0x7d;

GfMenuObjBlOrb::GfMenuObjBlOrb(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown58(this), unknown2e8(-1), unknown2f0(nullptr) {}

GfMenuObjBlOrb::~GfMenuObjBlOrb() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown2f0);
  unknown50 = nullptr;
}

void GfMenuObjBlOrb::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    unknown24 = 0;
    u32 blade = GfMenuReference::getReferenceBladeID(0);
// __LINE__ must be 87 as in the original file: it is the line argument of operator new.
#line 87
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
    attachExternalCall(unknown001, main.unknown10);
    {
      ui::UIObjectAcc slot(main.unknown10, "LAY_slot");
      u32 equipOrbMax = GfEquipUtil::getEquipOrbMax(blade);
// __LINE__ must be 100 as in the original file: it is the line argument of operator new.
#line 100
      SlotListener *slotListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SlotListener(this);
      slotListener->addRef();
      ui::UIEventManager::get()->registObjectListener(slot.unknown10, slotListener);
      if (slotListener != nullptr) {
        slotListener->release();
      }
      if (equipOrbMax == 0) {
        slot.setDisp(false);
      } else {
        {
          ui::UISelectObjList::CreateParam createParam = {};
          createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
          unknown28 = ui::UISelectObjList::create(createParam);
        }
        unknown28->pickupObject(slot.unknown10, "LAY_slot_item@%02d", 1);
        if (unknown28->getSize() != 0) {
          ui::UICtrlCursorSelect::CursorSetting setting;
          mm::mtl::FixStr<32> name;
          setting.unknown18 = 5;
          setting.unknown1a = 8;
          setting.unknown1c = 8;
          setting.setType(0);
          unknown30 = ui::UICtrlCursorSelect::create(slot.searchChild("IMG_slot_cursor"), setting, unknown28);
          slot.setDispChild(true, "IMG_slot_cursor");
          setupInputSelection(slot.unknown10, 0, equipOrbMax);
          for (u32 i = 0; i < unknown28->getSize(); i++) {
            ui::UIObjectAcc item(unknown28->getObject(i));
            if (i < equipOrbMax) {
              mm::mtl::IntrusivePtr<IGfMenuReferenceItem> reference(unknown161(blade, i));
              name.format("TXT_slot_item_name@%02d", i + 1);
              GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromReference(item.searchChild(name.c_str()), 0, reference, false);
              name.format("LAY_slot_item_body@%02d", i + 1);
              adapter->unknown24 = item.searchChild(name.c_str());
              name.format("TXT_slot_item_enhance@%02d", i + 1);
              GfMenuEnhanceAdapter::createFromReferenceItem(item.searchChild(name.c_str()), 0, reference, false);
            } else {
              item.setDisp(false);
            }
          }
        }
      }
    }
    {
      ui::UIObjectAcc itemSelect(main.unknown10, "LAY_item_select");
// __LINE__ must be 177 as in the original file: it is the line argument of operator new.
#line 177
      ItemListener *itemListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListener(this);
      itemListener->addRef();
      ui::UIEventManager::get()->registObjectListener(itemSelect.unknown10, itemListener);
      if (itemListener != nullptr) {
        itemListener->release();
      }
      {
        ui::UISelectObjList::CreateParam createParam = {};
        createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
        unknown40 = ui::UISelectObjList::create(createParam);
      }
      unknown40->pickupObject(itemSelect.unknown10, "LAY_item@%02d", 1);
      if (unknown40->getSize() != 0) {
        {
          GfMenuItemList::ItemBoxSetup setup;
          mm::mtl::FixStr<32> name;
          unknown38 = GfMenuItemList::create();
          setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_3;
          setup.unknown00.unknown08 = unknown40->getSize();
          unknown38->setupFromBox(setup);
          unknown38->setIndex(0);
          for (u32 i = 0; i < unknown40->getSize(); i++) {
            ui::UIObjectAcc item(unknown40->getObject(i));
            if (item.isValid()) {
              GfMenuItemAdapter::createFromList(item.unknown10, 8, unknown38, i, false);
              name.format("TXT_item_name@%02d", i + 1);
              GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, unknown38, i, false);
              adapter->unknown24 = item.unknown10;
              name.format("TXT_item_num@%02d", i + 1);
              GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, unknown38, i, false);
            }
          }
        }
        GfMenuObjUtil::createVScrollBarPlugin(itemSelect.searchChild("IMG_item_list_scr_bar"), unknown38, "IMG_item_list_scr_base", true);
        if (unknown38->getSize() != 0) {
          ui::UICtrlCursorSelect::CursorSetting setting;
          setting.unknown18 = 1;
          setting.unknown1a = 4;
          setting.setType(0);
          unknown48 = ui::UICtrlCursorSelect::create(itemSelect.searchChild("IMG_item_list_cursor"), setting, unknown40);
          itemSelect.setDispChild(true, "IMG_item_list_cursor");
          setupInputSelectionFromList(itemSelect.unknown10, *unknown38);
        }
      }
      GfMenuEnhanceAdapter::createFromItemList(itemSelect.searchChild("TXT_detail_enhance_text"), 0, unknown38, -1, false);
    }
    unknown50 = unknown160();
    GfMenuObject::initialize();
  }
}

void GfMenuObjBlOrb::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlOrb::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjBlOrb::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjBlOrb::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_slot"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
}

void GfMenuObjBlOrb::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_slot"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
}

bool GfMenuObjBlOrb::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlOrb::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlOrb::seqStartClose() {
  GfMenuObjOperationInfo::close();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlOrb::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjBlOrb::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjBlOrb::seqLeavePhase1() { return unknown002(2); }

void GfMenuObjBlOrb::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqStartOpen);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqAppearPhase1);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqEndOpen);
    break;
  case 2:
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqStartClose);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqLeavePhase1);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqEndClose);
    break;
  case 8: {
    int result = event.unknown0c;
    GfMenuReference::getReferenceBladeID(unknown20->unknown24);
    if (result == 2) {
      GfMenuObject::returnFSSubLayer(acc.unknown10, 2);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBlOrb::SlotListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
    return;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      unknown20->unknown28->setIndex(index);
      unknown20->unknown50->unknown162(unknown20->unknown38->getContents(unknown20->unknown38->getIndex(false)).unknown04);
    }
    acc.setDispChild(index != 0xffffffff, "IMG_item_cursor");
    return;
  }
  case 8: {
    u64 param = event.unknown08_u64;
    u32 blade = GfMenuReference::getReferenceBladeID(unknown20->unknown24);
    if (static_cast<u32>(param) != 0xffffffff) {
      u32 type = param >> 32;
      if (type == 1) {
        disableInput(acc.unknown10);
        ui::EventData sendData;
        sendData.unknown00 = 0x21;
        sendEvent(acc.searchSibiling("LAY_item_select"), sendData, 0.0f);
      } else if (type == 9) {
        if (GfEquipUtil::getEquipBladeOrb(blade, static_cast<u32>(param)) != 0) {
          if (unknown20->unknown2f0 == nullptr) {
            unknown20->unknown2f0 = GfMenuCallContext::create();
          }
          unknown20->unknown2f0->reset();
          GfMenuObjCommonText::open(unknown20->unknown2f0, 0x1e, 0);
          GfMenuObject::setCallContextEventHandler(unknown20->unknown2f0, acc.unknown10);
          unknown20->suspendInput();
        }
      }
    }
    return;
  }
  case 0x41: {
    u32 blade = GfMenuReference::getReferenceBladeID(unknown20->unknown24);
    if (unknown20->unknown2f0->unknown0c == event.unknown08) {
      if (event.unknown10 == 0) {
        GfEquipUtil::equipBladeOrb(blade, 0, unknown20->unknown28->getIndex(false), GfItemHandle(0));
      }
      unknown20->resumeInput();
      if (unknown20->unknown2f0 != nullptr) {
        unknown20->unknown2f0->release();
        unknown20->unknown2f0 = nullptr;
      }
    }
    return;
  }
  case 0x100:
    GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
    enableInput(acc.unknown10);
    return;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjBlOrb::ItemListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    disableInput(acc.unknown10);
    return;
  case 3:
    if (event.unknown08 == 1) {
      enableInput(acc.unknown10);
    }
    return;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      unknown20->unknown38->setIndex(index);
      unknown20->unknown40->setIndex(unknown20->unknown38->getIndex(true));
      unknown20->unknown50->unknown162(unknown20->unknown38->getContents(unknown20->unknown38->getIndex(false)).unknown04);
    }
    acc.setDispChild(index != 0xffffffff, "IMG_item_cursor");
    return;
  }
  case 8: {
    int type = event.unknown0c;
    MenuItemInfo &item = unknown20->unknown38->getContents(unknown20->unknown38->getIndex(false));
    u32 blade = GfMenuReference::getReferenceBladeID(unknown20->unknown24);
    if (type == 1) {
      u32 result = GfMenuItemUtil::canEquipOrb(item.unknown04, blade, unknown20->unknown28->getIndex(false));
      if (result == 0) {
        unknown20->unknown38->getSize();
        GfEquipUtil::equipBladeOrb(blade, item.unknown04, unknown20->unknown28->getIndex(false), GfItemHandle(0));
      } else {
        u32 window = GfMenuItemUtil::getEquipErrorCmnWindowID(result);
        if (window != 0) {
          if (unknown20->unknown2f0 == nullptr) {
            unknown20->unknown2f0 = GfMenuCallContext::create();
          }
          unknown20->unknown2f0->reset();
          GfMenuObjCommonText::open(unknown20->unknown2f0, window, 0);
          GfMenuObject::setCallContextEventHandler(unknown20->unknown2f0, acc.unknown10);
          unknown20->suspendInput();
        }
      }
    } else if (type == 2) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 2;
      param.unknown00 = 0.5f;
      param.unknown04 = 2;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      disableInput(acc.unknown10);
      ui::EventData sendData;
      sendData.unknown00 = 0x100;
      sendEvent(acc.searchSibiling("LAY_slot"), sendData, 0.0f);
    }
    return;
  }
  case 0x21: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
    return;
  }
  case 0x41:
    GfMenuReference::getReferenceBladeID(unknown20->unknown24);
    if (unknown20->unknown2f0->unknown0c == event.unknown08) {
      unknown20->resumeInput();
    }
    return;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlOrb>(const mm::mtl::Delegate<bool()> *);
