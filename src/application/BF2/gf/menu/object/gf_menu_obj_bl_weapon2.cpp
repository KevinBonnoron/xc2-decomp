#include "gf/menu/object/gf_menu_obj_bl_weapon2.h"

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_shop.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "gf/util/gf_shop_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x68;

// Inferred role: menu id; original name unknown.
constexpr u32 unknown003 = 0x21;

// Inferred role: shop layer; original name unknown.
constexpr u32 unknown004 = 0x2d;

GfMenuObjBlWeapon2::GfMenuObjBlWeapon2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown40(nullptr), unknown58(this), unknown2e8(false), unknown2ec(0), unknown2f0(0), unknown2f8(nullptr), unknown300(false) {
  unknown50 = GfMenuCallContext::create();
}

GfMenuObjBlWeapon2::~GfMenuObjBlWeapon2() {
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  unknown38 = nullptr;
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown2f8);
}

void GfMenuObjBlWeapon2::initialize() {
  {
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      unknown2f0 = layerParam.get<unknown002>().unknown00;
      unknown2f4 = layerParam.get<unknown002>().unknown02;
      removeFSLayerParam(unknown20);
    } else {
      unknown2f0 = 0;
    }
  }
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 171 as in the original file: it is the line argument of operator new.
#line 171
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 chips = acc.searchChild("LAY_chips");
// __LINE__ must be 176 as in the original file: it is the line argument of operator new.
#line 176
  ItemSelectListener *itemSelectListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ItemSelectListener(this);
  itemSelectListener->addRef();
  ui::UIEventManager::get()->registObjectListener(chips, itemSelectListener);
  if (itemSelectListener != nullptr) {
    itemSelectListener->release();
  }
  u32 weapon = acc.searchChild("LAY_weapon");
// __LINE__ must be 180 as in the original file: it is the line argument of operator new.
#line 180
  WeaponListener *weaponListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) WeaponListener(this);
  weaponListener->addRef();
  ui::UIEventManager::get()->registObjectListener(weapon, weaponListener);
  if (weaponListener != nullptr) {
    weaponListener->release();
  }
  u32 chrChange = acc.searchChild("LAY_chr_change");
// __LINE__ must be 184 as in the original file: it is the line argument of operator new.
#line 184
  ChrChangeListener *chrChangeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ChrChangeListener(this);
  chrChangeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(chrChange, chrChangeListener);
  if (chrChangeListener != nullptr) {
    chrChangeListener->release();
  }
  ui::UISelectObjList::CreateParam createParam;
  createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown30 = ui::UISelectObjList::create(createParam);
  unknown28 = GfMenuItemList::create();
  unknown38 = unknown160();
  unknown38->unknown162(0);
  unknown40 = GfMenuCallContext::create();
  unknown2f8 = GfMenuBladeList::create();
  disableInput(acc.searchChild("LAY_chips"));
  disableInput(acc.searchChild("LAY_chr_change"));
  GfMenuObject::initialize();
}

void GfMenuObjBlWeapon2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  unknown002 &data = layerParam.get<unknown002>();
  data.unknown00 = param.unknown00;
  data.unknown02 = param.unknown04;
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown003), layerParam);
}

void GfMenuObjBlWeapon2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlWeapon2::openForShop(u32 weapon) {
  OpenParam param;
  param.unknown00 = 1;
  param.unknown04 = weapon;
  registOpenParam(param);
  ui::UIManager::get()->createLayer(unknown004);
}

void GfMenuObjBlWeapon2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlWeapon2::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlWeapon2::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBlWeapon2::isSameWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  u32 weapon = GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip);
  return acc.getEquipWeapon(-1, false) == weapon;
}

bool GfMenuObjBlWeapon2::isDownWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  u32 rank = GfDataWeapon::getRank(acc.getEquipWeapon(-1, false));
  return GfDataWeapon::getRank(GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip)) < rank;
}

void GfMenuObjBlWeapon2::closeCharChange() {
  if (unknown2f0 == 0) {
    if (GfMenuObjMainMenu2::isOpenCharMenu()) {
      ui::UIObjectAcc chips(unknown18, "LAY_chips");
      GfMenuObjMainMenu2::disableCharChange();
    }
  } else {
    ui::UIObjectAcc acc(unknown18);
    unknown158(acc.searchChild("LAY_chr_change"), 0x102, 0, 0.0f);
  }
}

void GfMenuObjBlWeapon2::openCharChange() {
  if (unknown2f0 == 0) {
    if (GfMenuObjMainMenu2::isOpenCharMenu()) {
      ui::UIObjectAcc chips(unknown18, "LAY_chips");
      GfMenuObjMainMenu2::openCharChange(chips.unknown10, 1, false);
    }
  } else {
    ui::UIObjectAcc acc(unknown18);
    unknown158(acc.searchChild("LAY_chr_change"), GfMenuTypes::unknown003_33, 0, 0.0f);
  }
}

bool GfMenuObjBlWeapon2::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

void GfMenuObjBlWeapon2::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjBlWeapon2::seqStart() {
  GfMenuObjOperationInfo::setDisp(false);
  GfMenuObjMainMenu2::setCloseKeyEnable(false);
  unknown2e8 = false;
  return true;
}

bool GfMenuObjBlWeapon2::seqSrcLeave() {
  ui::UIObjectAcc image(unknown18, "LAY_wpn_img@01");
  bool isEnd;
  if (!unknown2e8) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_zoom_2";
    param.unknown58 = "fade_out";
    param.unknown11 = true;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    ui::UIObjectAcc main(unknown18, "LAY_main");
    param = GfMenuObjUtil::CtrlParam();
    param.unknown08 = 2;
    param.unknown00 = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_zoom_2", "fade_out");
    GfMenuObjUtil::startCtrl(main.unknown10, param, "LAY_bl_weapon@02");
    GfMenuObjUtil::startCtrl(main.unknown10, param, "IMG_weapon_arrow");
    unknown2e8 = true;
    isEnd = false;
  } else {
    int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
    if (ctrl == -1 || !GfMenuObjUtil::isBusyCtrl(ctrl)) {
      unknown2e8 = false;
      unknown58.unknown004(15);
      unknown58.unknown002(&GfMenuObjBlWeapon2::seqSrcAppear);
      isEnd = true;
    } else {
      isEnd = false;
    }
  }
  return isEnd;
}

bool GfMenuObjBlWeapon2::seqSrcAppear() {
  ui::UIObjectAcc image(unknown18, "LAY_wpn_img@01");
  bool isEnd;
  if (!unknown2e8) {
    GfEquipUtil::equipBladeChip(GfMenuReference::getReferenceBladeID(0), unknown38->unknown0c);
    GfMenuObjUtil::playSE(0x12);
    MenuItemInfo info = unknown28->getContents(unknown28->getIndex(false));
    info.unknown08 = 1;
    u32 index = unknown28->getIndex(false);
    unknown28->decItem(info, false);
    if (unknown2f0 == 1) {
      GfMenuItemList::ItemShopSetup setup;
      setup.unknown00.unknown08 = unknown30->getSize();
      setup.unknown14 = unknown2f4;
      unknown28->setupFromShop(setup);
      unknown28->setIndex(index);
    }
    {
      ui::UIObjectAcc chips(unknown18, "LAY_chips");
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < unknown30->getSize(); i++) {
        name.format("IMG_ch_listcrsor_@%02d", i + 1);
        chips.setDispChild(false, name.c_str());
      }
      GfMenuObject::resetInputSelection(chips.unknown10);
      GfMenuObject::setupInputSelectionFromList(chips.unknown10, *unknown28);
    }
    unknown38->unknown0c = 0;
    image.setDisp(true);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "sample";
    param.unknown58 = "fadein";
    param.unknown11 = true;
    param.unknown14 = 8;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    unknown2e8 = true;
    isEnd = false;
  } else {
    int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
    if (ctrl == -1 || !GfMenuObjUtil::isBusyCtrl(ctrl)) {
      unknown2e8 = false;
      unknown58.unknown002(&GfMenuObjBlWeapon2::seqSrcEffect);
      isEnd = true;
    } else {
      isEnd = false;
    }
  }
  return isEnd;
}

bool GfMenuObjBlWeapon2::seqSrcEffect() {
  ui::UIObjectAcc tag(unknown18, "IMG_wpn_tag_eff@01");
  bool isEnd;
  if (!unknown2e8) {
    ui::UIObjectAcc image(unknown18, "IMG_wpn_img_eff@01");
    tag.startAnimationFromIndex(1, false);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "mnu071_wep_flash";
    param.unknown58 = "flash";
    param.unknown11 = true;
    param.unknown14 = 8;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    unknown2e8 = true;
    isEnd = false;
  } else if (!tag.isPlayingAnimation()) {
    {
      ui::UIObjectAcc weapon(unknown18, "LAY_bl_weapon@02");
      weapon.setDisp(true);
      unknown38->unknown162(unknown28->getContents(unknown28->getIndex(false)).unknown04);
      GfMenuReference::setBladeVirtualEquipWpnChip(unknown28->getContents(unknown28->getIndex(false)).unknown04);
      if (unknown28->getSize() == 0) {
        weapon.setDispChild(false, "LAY_wpn_img@02");
      }
    }
    unknown2e8 = false;
    unknown58.unknown002(&GfMenuObjBlWeapon2::seqDstResume);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBlWeapon2::seqDstResume() {
  ui::UIObjectAcc weapon(unknown18, "LAY_bl_weapon@02");
  bool isEnd;
  if (!unknown2e8) {
    ui::UIObjectAcc arrow(unknown18, "IMG_weapon_arrow");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    GfMenuObjUtil::startCtrl(weapon.unknown10, param, nullptr);
    GfMenuObjUtil::startCtrl(arrow.unknown10, param, nullptr);
    unknown2e8 = true;
    isEnd = false;
  } else {
    int ctrl = GfMenuObjUtil::getCtrlID(weapon.unknown10);
    if (ctrl == -1 || !GfMenuObjUtil::isBusyCtrl(ctrl)) {
      unknown2e8 = false;
      unknown58.unknown002(&GfMenuObjBlWeapon2::seqEnd);
      isEnd = true;
    } else {
      isEnd = false;
    }
  }
  return isEnd;
}

bool GfMenuObjBlWeapon2::seqEnd() {
  GfMenuObjOperationInfo::setDisp(true);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  {
    ui::UIObjectAcc chips(unknown18, "LAY_chips");
    ui::EventData event;
    event.unknown00 = 0x100;
    GfMenuObject::sendEvent(chips.unknown10, event, 0.0f);
  }
  openCharChange();
  unknown2e8 = false;
  return true;
}

void GfMenuObjBlWeapon2::setupWeapon(ui::UIObjectAcc &acc, GfMenuItemList *list, GfMenuWeaponAdapter::ReferenceChip &chip) {
  GfMenuWeaponAdapter *adapter = GfMenuWeaponAdapter::createFromReferenceBlade(acc.searchChild("TXT_wpname_@01"), 0, 0, false);
  if (adapter != nullptr) {
    adapter->unknown24 = acc.searchChild("LAY_bl_weapon_text@01");
  }
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_wpn_img@01"), 0x59, 0, true);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_wpn_img_eff@01"), 0x59, 0, true);
  GfMenuObjUtil::setChildDisp(acc.unknown10, "TXT_wptype_@01", false);
  GfMenuWeaponAdapter::createFromReferenceBlade(acc.searchChild("TXT_wp_text_@01"), 6, 0, false);
  GfMenuObjUtil::createSyncPlugin(acc.searchChild("TXT_wp_text_no_eff@01"), acc.searchChild("TXT_wp_text_@01"), 0x40);
  adapter = GfMenuWeaponAdapter::createFromReferenceChip(acc.searchChild("TXT_wpname_@02"), 0, chip, false);
  if (adapter != nullptr) {
    adapter->unknown24 = acc.searchChild("LAY_bl_weapon_text@02");
  }
  GfMenuCharDataAdapter *charAdapter = GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_wpn_img@02"), 0x59, 0, true);
  if (charAdapter != nullptr) {
    charAdapter->unknown79 = 1;
  }
  GfMenuObjUtil::setChildDisp(acc.unknown10, "TXT_wp_chip_@02", false);
  GfMenuObjUtil::setChildDisp(acc.unknown10, "TXT_wptype_@02", false);
  GfMenuObjUtil::setChildDisp(acc.unknown10, "TXT_wp_plus_@02", false);
  GfMenuWeaponAdapter::createFromReferenceChip(acc.searchChild("TXT_wp_text_@02"), 6, chip, false);
  GfMenuObjUtil::createSyncPlugin(acc.searchChild("TXT_wp_text_no_eff@02"), acc.searchChild("TXT_wp_text_@02"), 0x40);
}

void GfMenuObjBlWeapon2::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList, u32 isShop, u32 shop) {
  selectList->pickupObject(acc.unknown10, "LAY_ch_listtag@%02d", 1);
  if (selectList->getSize() != 0 && list != nullptr) {
    if (isShop == 0) {
      GfMenuItemList::ItemBoxSetup setup;
      setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_1;
      setup.unknown00.unknown08 = selectList->getSize();
      setup.unknown00.unknown10 = true;
      list->setupFromBox(setup);
    } else {
      GfMenuItemList::ItemShopSetup setup;
      setup.unknown00.unknown08 = selectList->getSize();
      setup.unknown14 = shop;
      list->setupFromShop(setup);
    }
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < selectList->getSize(); i++) {
      name.format("IMG_itemicon_@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false);
      name.format("IMG_ch_reaicon@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 7, list, i, false);
      name.format("TXT_chipname_@%02d", i + 1);
      GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
      name.format("LAY_ch_listtag_item@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
      name.format("TXT_shstnum_@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false);
      name.format("TXT_price@%02d", i + 1);
      GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 5, list, i, false);
    }
  }
}

void GfMenuObjBlWeapon2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDisp(true);
    GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_base"), 0, 0);
    GfMenuObject::sendOpenEvent(acc.searchChild("LAY_chips"), 0, 0.0f);
    GfMenuObject::sendOpenEvent(acc.searchChild("LAY_weapon"), 0, 0.0f);
    mm::mtl::FixStr<32> name;
    if (unknown20->unknown2f0 == 1) {
      GfMenuBladeList::DriverSetup setup;
      setup.unknown14 = 3;
      setup.unknown00.unknown08 = 5;
      setup.unknown1c = false;
      unknown20->unknown2f8->setupFromDriver(setup);
      GfMenuReference::setReferenceBladeID(0, unknown20->unknown2f8->getContents(0).unknown00);
      for (u32 i = 1; i != 7; i++) {
        name.format("LAY_menu@%02d", i);
        ui::UIObjectAcc menu(acc.searchChild(name.c_str()));
        menu.setDisp(false);
        name.format("LAY_shop@%02d", i);
        ui::UIObjectAcc shop(acc.searchChild(name.c_str()));
        shop.setDisp(true);
      }
      GfMenuObjCmnStatus::openBlStatus(1, -1);
    } else {
      for (u32 i = 1; i != 7; i++) {
        name.format("LAY_menu@%02d", i);
        ui::UIObjectAcc menu(acc.searchChild(name.c_str()));
        menu.setDisp(true);
        name.format("LAY_shop@%02d", i);
        ui::UIObjectAcc shop(acc.searchChild(name.c_str()));
        shop.setDisp(false);
      }
    }
    break;
  }
  case 3:
    if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      if (unknown20->unknown2f0 == 0) {
        GfMenuObjCharSelect::returnSubMenu();
        GfMenuObject::returnFSSubLayer(unknown20);
      } else {
        GfMenuObject::termCallContext(handle);
        ui::UIManager::get()->terminateLayer(unknown004, true);
      }
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34: {
    int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_base"), 2, 0);
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    GfMenuObject::sendCloseEvent(acc.searchChild("LAY_chips"), 0, 0.0f);
    GfMenuObject::sendCloseEvent(acc.searchChild("LAY_weapon"), 0, 0.0f);
    if (unknown20->unknown2f0 == 1) {
      GfMenuObjShop::dispBlade(false);
      GfMenuObjCmnStatus::closeBlStatus();
      unknown158(acc.searchChild("LAY_chr_change"), GfMenuTypes::unknown003_34, 0, 0.0f);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBlWeapon2::ItemSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    setupItemList(acc, unknown20->unknown28, unknown20->unknown30, unknown20->unknown2f0, unknown20->unknown2f4);
    bool isOpen = GfMenuObjCmnStatus::isOpenBlStatus();
    GfMenuObjOperationInfo::changeText(handle, 0x12, !isOpen);
    GfMenuObjOperationInfo::setGuideText(0x12, 0);
    GfMenuObjMainMenu2::setSubIndexText(9);
    GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_ch_list_scroll_bar"), unknown20->unknown28, "IMG_ch_list_scroll_base", true);
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown28);
    ui::UIObjectAcc equip(acc.searchChild("LAY_index_equip"));
    ui::UIObjectAcc shop(acc.searchChild("LAY_index_shop"));
    ui::UIObjectAcc sort(acc.searchChild("LAY_item_sort"));
    if (unknown20->unknown2f0 == 0) {
      if (GfMenuObjMainMenu2::isOpenCharMenu()) {
        equip.setDisp(true);
        shop.setDisp(false);
        sort.setDisp(true);
      }
    } else {
      equip.setDisp(false);
      shop.setDisp(true);
      sort.setDisp(false);
    }
    unknown20->openCharChange();
    if (unknown20->unknown2f0 == 0) {
      u16 sortId = GfMenuObjSort::getSortID(0x11, 0);
      GfMenuObjSort::setSortLabelText(sortId, owner.searchChild("TXT_item_sort_label"));
      unknown20->unknown2ec = 0;
      unknown20->unknown28->sort(sortId, false);
    }
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(handle);
      GfMenuObjOperationInfo::add(handle, 0, 0, 0);
      if (unknown20->unknown2f0 == 0) {
        GfMenuObjOperationInfo::setActionEnable(handle, 0x11, true);
      } else {
        GfMenuObjOperationInfo::setActionEnable(handle, 0x11, false);
        GfMenuObjShop::dispBlade(true);
      }
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 prev = event.unknown0c;
    if (unknown20->unknown28->getSize() == 0) {
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < unknown20->unknown30->getSize(); i++) {
        name.format("IMG_ch_listcrsor_@%02d", i + 1);
        acc.setDispChild(false, name.c_str());
      }
    } else {
      int prevIndex = unknown20->unknown28->getIndex(true);
      unknown20->unknown28->setIndex(index);
      u32 curIndex = unknown20->unknown28->getIndex(true);
      unknown20->unknown30->setIndex(curIndex);
      mm::mtl::FixStr<32> name;
      if (prev != 0xffffffff) {
        name.format("IMG_ch_listcrsor_@%02d", prevIndex + 1);
        acc.setDispChild(false, name.c_str());
      }
      name.format("IMG_ch_listcrsor_@%02d", curIndex + 1);
      acc.setDispChild(true, name.c_str());
      unknown20->unknown38->unknown162(unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown04);
      GfMenuReference::setBladeVirtualEquipWpnChip(unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown04);
      if (prev != 0xffffffff && index != prev) {
        ui::UIObjectAcc image(unknown20->unknown18, "IMG_wpn_img@02");
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x10000000;
        param.unknown50 = "mnu071_wep_select";
        param.unknown58 = "select";
        param.unknown11 = true;
        param.unknown14 = 8;
        GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      if (unknown20->unknown28->getSize() == 0) {
        break;
      }
      MenuItemInfo &item = unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false));
      u32 blade = GfMenuReference::getReferenceBladeID(0);
      unknown20->unknown40->reset();
      if (unknown20->unknown2f0 == 0) {
        if (!GfMenuObjUtil::isBladeNoBuildWeapon(blade)) {
          if (isSameWeapon(blade, item.unknown04)) {
            GfMenuObjCommonText::openError(unknown20->unknown40, 9, 0);
            unknown20->unknown48 = 1;
            GfMenuObjUtil::playSECommon(2);
          } else {
            GfMenuObjCommonText::open(unknown20->unknown40, 0x35, 0);
            unknown20->unknown48 = 0;
          }
        } else {
          GfMenuObjCommonText::open(unknown20->unknown40, 0xd5, 0);
          unknown20->unknown48 = 3;
          GfMenuObjUtil::playSECommon(2);
        }
      } else {
        ItemPrice price;
        price.clear();
        GfItemUtil::getPrice(price, item.unknown04, unknown20->unknown2f4);
        u32 count = GfItemUtil::getEnableStock(item.unknown04) - GfItemUtil::getItemBoxCount(item.unknown04);
        if (GfDataUtil::getMoney() < price.unknown04 * count) {
          count = GfDataUtil::getMoney() / price.unknown04;
        }
        GfMenuObjCommonText::OpenNumSelectParam param;
        param.unknown08 = count;
        param.unknown0c = price.unknown04;
        GfMenuObjCommonText::openNumSelect(unknown20->unknown40, param);
        unknown20->unknown48 = 4;
      }
      if (unknown20->unknown40->isActive()) {
        unknown20->closeCharChange();
      }
      GfMenuObject::setCallContextEventHandler(unknown20->unknown40, acc.unknown10);
      break;
    }
    case 2: {
      GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
      u32 main = owner.searchChild("LAY_main");
      ui::EventData closeEvent;
      closeEvent.unknown00 = GfMenuTypes::unknown003_34;
      ui::UIManager::get()->requestObjectEvent(main, closeEvent, 0.0f);
      GfMenuObject::disableInput(handle);
      GfMenuReference::setBladeVirtualEquipWpnChip(0);
      GfMenuObjMainMenu2::disableCharChange();
      GfMenuObjUtil::playSECommonCancel();
      break;
    }
    case 0x11:
      GfMenuObjSort::open(acc.unknown10, owner.searchChild("TXT_item_sort_label"), 0x11, unknown20->unknown2ec);
      GfMenuObject::disableInput(handle);
      GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
      break;
    case 0x12: {
      bool swapped = GfMenuObjCmnStatus::swapBlStatus();
      GfMenuObjOperationInfo::changeText(handle, 0x12, !swapped);
      break;
    }
    }
    break;
  case GfMenuTypes::unknown003_33:
    setFadeIn(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(acc.unknown10);
    break;
  case 0x41: {
    GfMenuReference::getReferenceBladeID(0);
    u32 chip = unknown20->unknown38->unknown0c;
    u32 count = event.unknown14;
    u32 call = event.unknown08;
    if (unknown20->unknown40->unknown0c == call) {
      if (event.unknown10 == 0) {
        switch (unknown20->unknown48) {
        case 0:
        case 2:
          GfMenuObject::disableInput(acc.unknown10);
          unknown20->unknown58.unknown002(&GfMenuObjBlWeapon2::seqStart);
          unknown20->unknown58.unknown002(&GfMenuObjBlWeapon2::seqSrcLeave);
          break;
        case 4: {
          if (count != 0) {
            GfShopUtil::execBuy(chip, count, unknown20->unknown2f4);
            MenuItemInfo info;
            info.unknown04 = chip;
            info.unknown00 = GfItemUtil::getType(chip);
            info.unknown08 = count;
            unknown20->unknown28->addItem(info, false);
            GfMenuObjUtil::playSE(0x18);
            ui::EventData endEvent;
            endEvent.unknown00 = GfMenuTypes::unknown003_259;
            ui::UIManager::get()->requestObjectEvent(handle, endEvent, 0.0f);
            unknown20->unknown300 = true;
          }
          break;
        }
        case 5: {
          u32 blade = GfMenuReference::getReferenceBladeID(0);
          unknown20->unknown40->reset();
          if (isSameWeapon(blade, chip)) {
            GfMenuObjCommonText::openError(unknown20->unknown40, 9, 0);
            unknown20->unknown48 = 1;
          } else {
            GfMenuObject::disableInput(acc.unknown10);
            unknown20->unknown58.unknown002(&GfMenuObjBlWeapon2::seqStart);
            unknown20->unknown58.unknown002(&GfMenuObjBlWeapon2::seqSrcLeave);
          }
          GfMenuObject::setCallContextEventHandler(unknown20->unknown40, acc.unknown10);
          unknown20->unknown300 = false;
          break;
        }
        default:
          unknown20->openCharChange();
          break;
        }
      } else {
        unknown20->openCharChange();
      }
    }
    break;
  }
  case GfMenuTypes::unknown003_256:
    GfMenuObject::enableInput(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_259: {
    u32 blade = GfMenuReference::getReferenceBladeID(0);
    if (!GfMenuObjUtil::isBladeNoBuildWeapon(blade)) {
      GfMenuObjCommonText::open(unknown20->unknown40, 0xd1, 0);
      unknown20->unknown48 = 5;
      GfMenuObject::setCallContextEventHandler(unknown20->unknown40, acc.unknown10);
    }
    break;
  }
  case 0x140:
    GfMenuReference::setReferenceBladeID(0, event.unknown08);
    GfMenuObjCharSelect::execCharPosScale(1);
    break;
  case 0x148:
    GfMenuObject::enableInput(handle);
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    if (unknown20->unknown2ec != event.unknown08) {
      u16 sortId = GfMenuObjSort::getSortID(0x11, event.unknown08);
      unknown20->unknown28->sort(sortId, false);
      unknown20->unknown2ec = event.unknown08;
      GfMenuObject::resetInputSelection(handle);
      GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown28);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
