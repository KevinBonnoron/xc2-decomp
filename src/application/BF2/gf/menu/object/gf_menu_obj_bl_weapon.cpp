#include "gf/menu/object/gf_menu_obj_bl_weapon.h"

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_diff_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_weapon_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/util/gf_equip_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {
class GfMenuAdapter;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7c;

GfMenuObjBlWeapon::GfMenuObjBlWeapon(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(0), m_menuItemList(nullptr), unknown38(nullptr), unknown40(nullptr), unknown50(this), unknown2e0(-1), m_menuCallContext(nullptr) {}

GfMenuObjBlWeapon::~GfMenuObjBlWeapon() {
  mm::mtl::safeRelease(m_menuItemList);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(m_menuCallContext);
  unknown48 = nullptr;
}

void GfMenuObjBlWeapon::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    unknown24 = 0;
    u32 blade = GfMenuReference::getReferenceBladeID(0);
// __LINE__ must be 82 as in the original file: it is the line argument of operator new.
#line 82
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
    attachExternalCall(unknown001, main.unknown10);
    {
      ui::UIObjectAcc list(main.unknown10, "LAY_item_list");
// __LINE__ must be 94 as in the original file: it is the line argument of operator new.
#line 94
      ItemListener *itemListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemListener(this);
      itemListener->addRef();
      ui::UIEventManager::get()->registObjectListener(list.unknown10, itemListener);
      if (itemListener != nullptr) {
        itemListener->release();
      }
      {
        ui::UISelectObjList::CreateParam createParam = {};
        createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
        unknown38 = ui::UISelectObjList::create(createParam);
      }
      unknown38->pickupObject(list.unknown10, "LAY_item@%02d", 1);
      if (unknown38->getSize() != 0) {
        {
          GfMenuItemList::ItemBoxSetup setup;
          mm::mtl::FixStr<32> name;
          m_menuItemList = GfMenuItemList::create();
          setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_1;
          setup.m_setupParam.unknown08 = unknown38->getSize();
          m_menuItemList->setupFromBox(setup);
          m_menuItemList->setIndex(0);
          for (u32 i = 0; i < unknown38->getSize(); i++) {
            ui::UIObjectAcc item(unknown38->getObject(i));
            if (item.isValid()) {
              name.format("TXT_item_name@%02d", i + 1);
              GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 0, m_menuItemList, i, false);
              adapter->unknown24 = item.unknown10;
              name.format("TXT_item_num@%02d", i + 1);
              GfMenuItemAdapter::createFromList(item.searchChild(name.c_str()), 3, m_menuItemList, i, false);
              name.format("TXT_item_atk@%02d", i + 1);
              GfMenuWeaponAdapter::createFromBladeWithChipList(item.searchChild(name.c_str()), 1, blade, m_menuItemList, i, false);
            }
          }
        }
        GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_item_list_scr_bar"), m_menuItemList, "IMG_item_list_scr_base", true);
        if (m_menuItemList->getSize() != 0) {
          ui::UICtrlCursorSelect::CursorSetting setting;
          setting.unknown18 = 1;
          setting.unknown1a = 4;
          setting.setType(0);
          ui::UICtrlCursorSelect::create(list.searchChild("IMG_item_list_cursor"), setting, unknown38);
          list.setDispChild(true, "IMG_item_list_cursor");
          setupInputSelectionFromList(list.unknown10, *m_menuItemList);
        }
      }
    }
    unknown48 = unknown160();
    {
      ui::UIObjectAcc detail(main.unknown10, "LAY_detail");
      GfMenuWeaponAdapter::ReferenceChip chip;
      unknown48->unknown162(m_menuItemList->getContents(m_menuItemList->getIndex(false)).unknown04);
      chip.unknown00 = 0;
      chip.unknown08 = unknown48;
      if (m_menuItemList->getSize() == 0) {
        detail.setDispChild(false, "TXT_detail_st_atk_num");
        detail.setDispChild(false, "TXT_detail_st_num@01");
        detail.setDispChild(false, "TXT_detail_st_num@02");
        detail.setDispChild(false, "TXT_detail_st_num@03");
      } else {
        GfMenuWeaponAdapter::createFromReferenceChip(detail.searchChild("TXT_detail_wpn_name"), 0, chip, false);
        GfMenuAdapter *base = GfMenuWeaponAdapter::createFromBlade(detail.searchChild("TXT_detail_st_atk_num"), 1, blade, false);
        GfMenuAdapter *other = GfMenuWeaponAdapter::createFromReferenceChip(detail.searchChild("TXT_detail_st_atk_num"), 1, chip, false);
        GfMenuDiffAdapter::create(detail.searchChild("IMG_detail_st_atk_diff"), base, other, 0, true);
        base = GfMenuWeaponAdapter::createFromBlade(detail.searchChild("TXT_detail_st_num@01"), 2, blade, false);
        other = GfMenuWeaponAdapter::createFromReferenceChip(detail.searchChild("TXT_detail_st_num@01"), 2, chip, false);
        GfMenuDiffAdapter::create(detail.searchChild("IMG_detail_st_diff@01"), base, other, 0, true);
        base = GfMenuWeaponAdapter::createFromBlade(detail.searchChild("TXT_detail_st_num@02"), 3, blade, false);
        other = GfMenuWeaponAdapter::createFromReferenceChip(detail.searchChild("TXT_detail_st_num@02"), 3, chip, false);
        GfMenuDiffAdapter::create(detail.searchChild("IMG_detail_st_diff@02"), base, other, 0, true);
        base = GfMenuWeaponAdapter::createFromBlade(detail.searchChild("TXT_detail_st_num@03"), 4, blade, false);
        other = GfMenuWeaponAdapter::createFromReferenceChip(detail.searchChild("TXT_detail_st_num@03"), 4, chip, false);
        GfMenuDiffAdapter::create(detail.searchChild("IMG_detail_st_diff@03"), base, other, 0, true);
      }
    }
    m_menuCallContext = GfMenuCallContext::create();
    GfMenuObject::initialize();
  }
}

void GfMenuObjBlWeapon::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjBlWeapon::isSameWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  u32 weapon = GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip);
  return acc.getEquipWeapon(-1, false) == weapon;
}

bool GfMenuObjBlWeapon::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjBlWeapon::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlWeapon::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
}

void GfMenuObjBlWeapon::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
}

bool GfMenuObjBlWeapon::seqStartOpen() {
  suspendInput();
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjBlWeapon::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlWeapon::seqStartClose() {
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjBlWeapon::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjBlWeapon::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjBlWeapon::seqLeavePhase1() { return unknown002(2); }

void GfMenuObjBlWeapon::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    m_menuObjBlWeapon->unknown50.unknown002(&GfMenuObjBlWeapon::seqStartOpen);
    m_menuObjBlWeapon->unknown50.unknown002(&GfMenuObjBlWeapon::seqAppearPhase1);
    m_menuObjBlWeapon->unknown50.unknown002(&GfMenuObjBlWeapon::seqEndOpen);
    break;
  case 2:
    m_menuObjBlWeapon->unknown50.unknown002(&GfMenuObjBlWeapon::seqStartClose);
    m_menuObjBlWeapon->unknown50.unknown002(&GfMenuObjBlWeapon::seqLeavePhase1);
    m_menuObjBlWeapon->unknown50.unknown002(&GfMenuObjBlWeapon::seqEndClose);
    break;
  case 8: {
    int result = event.unknown0c;
    GfMenuReference::getReferenceBladeID(m_menuObjBlWeapon->unknown24);
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

void GfMenuObjBlWeapon::ItemListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 8: {
    u32 index = event.unknown08;
    int result = event.unknown0c;
    const MenuItemInfo &info = m_menuObjBlWeapon->m_menuItemList->getContents(m_menuObjBlWeapon->m_menuItemList->getIndex(false));
    u32 blade = GfMenuReference::getReferenceBladeID(m_menuObjBlWeapon->unknown24);
    if (index != 0xffffffff && result == 1) {
      m_menuObjBlWeapon->m_menuCallContext->reset();
      if (m_menuObjBlWeapon->isSameWeapon(blade, info.unknown04)) {
        GfMenuObjCommonText::open(m_menuObjBlWeapon->m_menuCallContext, 0x1c, 0);
      } else {
        GfMenuObjCommonText::open(m_menuObjBlWeapon->m_menuCallContext, 0x1d, 0);
        m_menuObjBlWeapon->unknown28 = 1;
      }
      GfMenuObject::setCallContextEventHandler(m_menuObjBlWeapon->m_menuCallContext, acc.unknown10);
      m_menuObjBlWeapon->suspendInput();
    }
    break;
  }
  case 1:
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      m_menuObjBlWeapon->m_menuItemList->setIndex(index);
      m_menuObjBlWeapon->unknown38->setIndex(m_menuObjBlWeapon->m_menuItemList->getIndex(true));
      m_menuObjBlWeapon->unknown48->unknown162(m_menuObjBlWeapon->m_menuItemList->getContents(m_menuObjBlWeapon->m_menuItemList->getIndex(false)).unknown04);
    }
    acc.setDispChild(index != 0xffffffff, "IMG_item_cursor");
    break;
  }
  case 0x41: {
    u32 blade = GfMenuReference::getReferenceBladeID(m_menuObjBlWeapon->unknown24);
    u32 call = event.unknown08;
    if (m_menuObjBlWeapon->m_menuCallContext->unknown0c == call) {
      if (event.unknown10 == 0 && m_menuObjBlWeapon->unknown28 == 1) {
        const MenuItemInfo &item = m_menuObjBlWeapon->m_menuItemList->getContents(m_menuObjBlWeapon->m_menuItemList->getIndex(false));
        GfEquipUtil::equipBladeChip(blade, item.unknown04);
        MenuItemInfo info = item;
        info.unknown08 = 1;
        m_menuObjBlWeapon->m_menuItemList->decItem(info, false);
      }
      m_menuObjBlWeapon->resumeInput();
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlWeapon>(const mm::mtl::Delegate<bool()> *);
