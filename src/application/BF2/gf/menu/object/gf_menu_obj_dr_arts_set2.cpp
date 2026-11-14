#include "gf/menu/object/gf_menu_obj_dr_arts_set2.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_item_id.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_arts_adapter.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_diff_adapter.h"
#include "gf/menu/adapter/gf_menu_weapon_type_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_arts_list.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuAdapter;

GfMenuObjDrArtsSet2::GfMenuObjDrArtsSet2(u32 handle)
    : GfMenuObject(handle), unknown0b8(nullptr), unknown0c0(nullptr), unknown0c8(nullptr), unknown0d0(-1), unknown0d4(-1), unknown0d8(nullptr), unknown0e0(false), unknown0e8(nullptr),
      unknown0f0(nullptr), unknown0f8(this), unknown258(false) {
  unknown0e8 = GfMenuBladeList::create();
  unknown0f0 = GfMenuItemList::create();
}

GfMenuObjDrArtsSet2::~GfMenuObjDrArtsSet2() {
  unknown0a0 = nullptr;
  unknown0a8 = nullptr;
  mm::mtl::safeRelease(unknown0f0);
  mm::mtl::safeRelease(unknown0e8);
  mm::mtl::safeRelease(unknown0b8);
  mm::mtl::safeRelease(unknown0c8);
  mm::mtl::safeRelease(unknown0c0);
  mm::mtl::safeRelease(unknown0d8);
}

void GfMenuObjDrArtsSet2::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 148 as in the original file: it is the line argument of operator new.
#line 148
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(0x65, main);
  u32 wpn = acc.searchChild("LAY_wpn");
// __LINE__ must be 154 as in the original file: it is the line argument of operator new.
#line 154
  WpnTypeListener *wpnTypeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) WpnTypeListener(this);
  wpnTypeListener->addRef();
  ui::UIEventManager::get()->registObjectListener(wpn, wpnTypeListener);
  if (wpnTypeListener != nullptr) {
    wpnTypeListener->release();
  }
  u32 arts = acc.searchChild("LAY_arts");
// __LINE__ must be 158 as in the original file: it is the line argument of operator new.
#line 158
  ArtsListListener *artsListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ArtsListListener(this);
  artsListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(arts, artsListListener);
  if (artsListListener != nullptr) {
    artsListListener->release();
  }
  u32 lvupEff = acc.searchChild("LAY_lvup_eff");
// __LINE__ must be 162 as in the original file: it is the line argument of operator new.
#line 162
  LevelupListener *levelupListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LevelupListener(this);
  levelupListener->addRef();
  ui::UIEventManager::get()->registObjectListener(lvupEff, levelupListener);
  if (levelupListener != nullptr) {
    levelupListener->release();
  }
  unknown0a0 = unknown160();
  unknown0a0->unknown162(0);
  unknown0a8 = unknown160();
  unknown0a8->unknown162(0);
  unknown0c0 = GfMenuCallContext::create();
  unknown0c8 = GfMenuCallContext::create();
  unknown0d8 = GfMenuArtsList::create();
  ui::UIListInfoBase::SetupParam artsParam;
  artsParam.unknown08 = 4;
  unknown0d8->setup(getAllocator(ALLOCATOR_UNKNOWN_0), artsParam);
  {
    ui::UIListInfoBase::SetupParam itemParam;
    itemParam.unknown08 = 3;
    unknown0f0->setup(getAllocator(ALLOCATOR_UNKNOWN_0), itemParam);
  }
  for (u32 item = ITEM_UNKNOWN_25405; item <= ITEM_UNKNOWN_25407; item++) {
    GfItem info = GfItemUtil::getInfo(item);
    if (info.unknown02 != 0) {
      MenuItemInfo menuItem;
      menuItem.unknown04 = item;
      menuItem.unknown00 = GfItemUtil::getType(item);
      menuItem.unknown08 = info.unknown02;
      unknown0f0->addItem(menuItem, false);
    }
  }
  disableInput(acc.searchChild("LAY_wpn"));
  disableInput(acc.searchChild("LAY_arts"));
  GfMenuObject::initialize();
}
void GfMenuObjDrArtsSet2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrArtsSet2::update() {
  unknown0f8.unknown003();
  GfMenuObject::update();
}

void GfMenuObjDrArtsSet2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrArtsSet2::setFadeIn(u32 handle, u32 dir, const char *child) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_motion_lr";
  param.unknown58 = dir != 0 ? "fade_in_r_early" : "fade_in_l_early";
  param.unknown04 = 1;
  param.unknown11 = true;
  int ctrl = GfMenuObjUtil::startCtrl(handle, param, child);
  if (child != nullptr) {
    GfMenuObject::hookCtrlEvent(handle, ctrl);
  }
  return ctrl;
}

int GfMenuObjDrArtsSet2::setFadeOut(u32 handle, u32 dir, const char *child) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_motion_lr";
  param.unknown58 = dir != 0 ? "fade_out_r_early" : "fade_out_l_early";
  param.unknown04 = 2;
  param.unknown11 = true;
  param.unknown14 = 10;
  int ctrl = GfMenuObjUtil::startCtrl(handle, param, child);
  if (child != nullptr) {
    GfMenuObject::hookCtrlEvent(handle, ctrl);
  }
  return ctrl;
}

void GfMenuObjDrArtsSet2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjMainMenu2::setSubIndexText(6);
    GfMenuObject::sendOpenEvent(acc.searchChild("LAY_wpn"), 1, 0.0f);
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjCharSelect::returnSubMenu();
      GfMenuObject::returnFSSubLayer(unknown20);
    }
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(acc.unknown10, 0, nullptr);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjDrArtsSet2::LevelupListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 3: {
    u32 arts = owner.searchChild("LAY_arts");
    ui::EventData resume;
    resume.unknown00 = GfMenuTypes::unknown003_258;
    ui::UIManager::get()->requestObjectEvent(arts, resume, 0.0f);
    acc.setDisp(false);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    acc.setDisp(true);
    {
      ui::UIObjectAcc effect(acc.unknown10, "IMG_lvup_eff");
      effect.startAnimation("fade_in", false);
    }
    ui::UIObjectAcc blur(acc.unknown10, "TXT_lvup_eff_blur");
    ui::UIObjectAcc blur2(acc.unknown10, "TXT_lvup_eff_blur");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_levelup_text_fadein";
    param.unknown58 = "fade_in";
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, "TXT_lvup_eff");
    param.unknown50 = "cmn_levelup_text_fadein_blur";
    int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "TXT_lvup_eff_blur");
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjDrArtsSet2::setFadeInBG(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_r_early");
  param.unknown04 = 1;
  param.unknown11 = true;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjDrArtsSet2::setFadeOutBG(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown00 = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_r_early");
  param.unknown04 = 1;
  param.unknown11 = true;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjDrArtsSet2::moveRight(ui::UIObjectAcc &acc) {
  mm::Pnt<s16> pos;
  acc.getPos(pos);
  pos.x += 0x10;
  acc.setPos(pos);
}

void GfMenuObjDrArtsSet2::moveLeft(ui::UIObjectAcc &acc) {
  mm::Pnt<s16> pos;
  acc.getPos(pos);
  pos.x -= 0x10;
  acc.setPos(pos);
}

GfMenuObjDrArtsSet2::unknown001 GfMenuObjDrArtsSet2::checkArtsLvUp(u32 driver, u32 weaponType, u32 arts, u32 level) {
  if (arts == 0 || level >= GfDataDriverArts::getLevelMax(arts)) {
    return UNKNOWN001_UNKNOWN_4;
  }
  if (GfDataDriverArts::getNeedLevelupWp(driver, arts) <= GfDataDriverArts::getWp(driver, weaponType)) {
    return UNKNOWN001_UNKNOWN_0;
  }
  return UNKNOWN001_UNKNOWN_5;
}

GfMenuObjDrArtsSet2::unknown001 GfMenuObjDrArtsSet2::checkArtsLvUp(u32 driver, u32 weaponType, GfMenuArtsList *list, u32 index) {
  return checkArtsLvUp(driver, weaponType, list->getContents(index).unknown00, list->getContents(index).unknown04);
}

void GfMenuObjDrArtsSet2::refreshParam(ui::UIObjectAcc &acc, u32 driver, u32 weaponType, GfMenuArtsList *list, u32 index) {
  unknown001 result = checkArtsLvUp(driver, weaponType, list, index);
  if (result == UNKNOWN001_UNKNOWN_4) {
    acc.setDispChild(true, "LAY_param_num_max@01");
    acc.setDispChild(true, "LAY_param_num_max@02");
  } else {
    acc.setDispChild(true, "LAY_param_num_diff@01");
    acc.setDispChild(true, "LAY_param_num_diff@02");
    u32 number = acc.searchChild("TXT_param_num_r@01");
    if (result == UNKNOWN001_UNKNOWN_0) {
      GfMenuObjUtil::setColMulandAdd(number, "txt_lvup");
      GfMenuObjUtil::setColMulandAdd(acc.searchChild("TXT_param_num_r@02"), "txt_lvup");
    } else {
      GfMenuObjUtil::setColDefault(number);
      GfMenuObjUtil::setColDefault(acc.searchChild("TXT_param_num_r@02"));
    }
    acc.setDispChild(false, "LAY_param_num_max@01");
    acc.setDispChild(false, "LAY_param_num_max@02");
  }
}

void GfMenuObjDrArtsSet2::refreshLvUp(ui::UIObjectAcc &acc, u32 driver, u32 weaponType, GfMenuArtsList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 4; i++) {
    bool canLevelUp = list->getSize() > i && checkArtsLvUp(driver, weaponType, list, i) == UNKNOWN001_UNKNOWN_0;
    name.format("LAY_wpn_arts_lv_up@%02d", i + 1);
    acc.setDispChild(canLevelUp, name.c_str());
  }
}

void GfMenuObjDrArtsSet2::refreshArtsSelect(ui::UIObjectAcc &acc, int selected, int held) {
  mm::mtl::FixStr<32> name;
  u32 i = 0;
  do {
    u32 number = i + 1;
    name.format("IMG_arts_icon_tag_base@%02d", number);
    ui::UIObjectAcc tagBase(acc.searchChild(name.c_str()));
    name.format("IMG_arts_icon_base@%02d", number);
    ui::UIObjectAcc iconBase(acc.searchChild(name.c_str()));
    name.format("TXT_arts_name@%02d", number);
    ui::UIObjectAcc artsName(acc.searchChild(name.c_str()));
    if (held == i) {
      tagBase.setAddColor("sys_hold");
      iconBase.setMulColor("black");
      iconBase.setAddColor("sys_hold");
      GfMenuObjUtil::setColMulandAdd(artsName.unknown10, "txt_column");
    } else {
      if (selected == i) {
        tagBase.setAddColor("sys_select");
        iconBase.setMulColor("black");
        iconBase.setAddColor("sys_select");
      } else {
        tagBase.loadDefColor();
        iconBase.loadDefColor();
      }
      artsName.loadDefColor();
    }
    i = number;
  } while (i != 4);
}

void GfMenuObjDrArtsSet2::refreshLvCap(ui::UIObjectAcc &acc, u32 driver, u32 weaponType, GfMenuArtsList *list, u32 index) {
  mm::mtl::FixStr<32> name;
  // The game reads the arts of the entry first (its bounds checks stay) and never uses it.
  u32 arts = list->getContents(index).unknown00;
  u32 level = list->getContents(index).unknown04;
  for (u32 i = 1; i < 5; i++) {
    name.format("IMG_arts_lv_cap_base@%02d", i);
    ui::UIObjectAcc base(acc.unknown10, name.c_str());
    bool isCurrent;
    if (i > level) {
      base.setImageIndex(2);
      isCurrent = false;
    } else if (level == i && checkArtsLvUp(driver, weaponType, list, index) == UNKNOWN001_UNKNOWN_0) {
      isCurrent = true;
      base.setImageIndex(1);
    } else {
      base.setImageIndex(0);
      isCurrent = false;
    }
    name.format("TXT_arts_lv_cap_num@%02d", i);
    u32 number = acc.searchChild(name.c_str());
    if (isCurrent) {
      GfMenuObjUtil::setColMulandAdd(number, "txt_column");
    } else {
      GfMenuObjUtil::setColDefault(number);
    }
  }
}

void GfMenuObjDrArtsSet2::setupWpnType(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, GfMenuArtsList *list, GfMenuBladeList *blades) {
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_wpn_wp_name"), 0, 0, number, 0, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_wpn_wp_num"), 2, 0, number, 0, true);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 4; i++) {
    name.format("TXT_wpn_arts_name@%02d", i + 1);
    GfMenuArtsAdapter *adapter = GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 0, list, i, 0, false);
    if (adapter != nullptr) {
      name.format("LAY_wpn_arts@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("TXT_wpn_arts_lv@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 8, list, i, 0, false);
  }
  name.format("IMG_wpn_blade_face@%02d", 1);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, blades, 0, false);
  name.format("IMG_wpn_blade_face@%02d", 2);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, blades, 1, false);
  name.format("IMG_wpn_blade_face@%02d", 3);
  GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, blades, 2, false);
}

void GfMenuObjDrArtsSet2::refreshArtsList(ui::UIObjectAcc &acc, GfMenuArtsList *list, u32 driver, u32 weaponType, GfMenuBladeList *blades) {
  mm::mtl::FixedArray<u32, 4> arts;
  GfMenuObjUtil::getEnableArts(arts, driver, weaponType);
  list->clear();
  for (u32 i = 0; i < arts.size(); i++) {
    MenuArtsInfo info = {arts[i], 0};
    info.unknown04 = GfDataDriverArts::getArtsLevel(driver, info.unknown00);
    list->addContents(info);
  }
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < blades->getSize(); i++) {
    name.format("IMG_wpn_blade_face@%02d", i + 1);
    ui::UIObjectAcc face(acc.unknown10, name.c_str());
    if (GfDataBlade::getBladeWpnType(blades->getContents(i).unknown00) == weaponType) {
      face.setMulColor("white");
    } else {
      face.setMulColor("gray");
    }
  }
}

void GfMenuObjDrArtsSet2::setupArtsList(ui::UIObjectAcc &acc, GfMenuArtsList *list, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> artsIndex) {
  mm::mtl::FixStr<32> name;
  GfMenuAdapterManager::beginAddAfter();
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_list_index"), 0, 0, wpnType, 0, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("IMG_arts_wpn_icon"), 1, 0, wpnType, 0, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_arts_wp_num"), 2, 0, wpnType, 0, true);
  for (u32 i = 0; i < 4; i++) {
    name.format("TXT_arts_name@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 0, list, i, 0, false);
    name.format("IMG_arts_icon_type@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 2, list, i, 0, false);
    name.format("IMG_arts_icon_enhance@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 3, list, i, 0, false);
    name.format("IMG_arts_icon_react@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 4, list, i, 0, false);
    name.format("IMG_arts_icon_range@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 5, list, i, 0, false);
    name.format("TXT_arts_tag_wp_num@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 6, list, i, 0, false);
    name.format("TXT_arts_tag_wp_max@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 0x14, list, i, 0, false)->unknown64 = 1;
    name.format("TXT_arts_lv@%02d", i + 1);
    GfMenuArtsAdapter::createFromListReferenceDriver(acc.searchChild(name.c_str()), 8, list, i, 0, false);
  }
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_txt@01"), 10, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_txt@01"), 10, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_txt@02"), 0xb, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_txt@02"), 0xb, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_txt@03"), 0xc, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_txt@03"), 0xc, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_num_index@01"), 0x15, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_num_index@01"), 0x15, list, artsIndex, 0, false);
  GfMenuAdapter *a = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_num@01"), 0xd, list, artsIndex, 0, false);
  GfMenuAdapter *b = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_num@01"), 0x11, list, artsIndex, 0, false);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_param_b_num@01"), a, b, 1, true);
  a = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_a_num@02"), 0xe, list, artsIndex, 0, false);
  b = GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_param_b_num@02"), 0x12, list, artsIndex, 0, false);
  GfMenuDiffAdapter::create(acc.searchChild("TXT_param_b_num@02"), b, a, 1, true);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_arts_detail_a_enhance"), 0xf, list, artsIndex, 0, false);
  GfMenuArtsAdapter::createFromListReferenceDriverReferenceIndex(acc.searchChild("TXT_arts_detail_b_enhance"), 0x13, list, artsIndex, 0, false);
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjDrArtsSet2::refreshArtsNeedWP(ui::UIObjectAcc &acc, GfMenuArtsList *list, u32 driver, u32 weaponType) {
  mm::mtl::FixStr<32> name;
  for (int i = 0; i < 4; i++) {
    bool isEnough;
    if (i < list->getSize()) {
      isEnough = checkArtsLvUp(driver, weaponType, list, i) == UNKNOWN001_UNKNOWN_0;
    } else {
      isEnough = false;
    }
    name.format("TXT_arts_tag_wp_num@%02d", i + 1);
    ui::UIObjectAcc text(acc.unknown10, name.c_str());
    if (isEnough) {
      text.loadDefColor();
      text.setBorderWeight(-0.5f);
    } else {
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_warning");
      text.setBorderWeight(2.0f);
    }
  }
}

void GfMenuObjDrArtsSet2::refreshLvUpWpn(ui::UIObjectAcc &acc, u32 driver, const mm::mtl::FixedVector<u32, 27> &weaponTypes) {
  for (u32 i = 0; i < weaponTypes.size();) {
    mm::mtl::FixedArray<u32, 4> arts;
    u32 count = GfMenuObjUtil::getEnableArts(arts, driver, weaponTypes[i]);
    bool canLevelUp = false;
    mm::mtl::FixStr<32> name;
    for (u32 j = 0; j < count; j++) {
      u32 art = arts[j];
      u32 level = GfDataDriverArts::getArtsLevel(driver, art);
      bool isEnough = checkArtsLvUp(driver, weaponTypes[i], art, level) == UNKNOWN001_UNKNOWN_0;
      canLevelUp |= isEnough;
      if (isEnough) {
        break;
      }
    }
    i++;
    name.format("IMG_wpn_lvup@%02d", i);
    acc.setDispChild(canLevelUp, name.c_str());
  }
}

void GfMenuObjDrArtsSet2::setupArtsDetail(ui::UIObjectAcc &, GfMenuArtsList *, mm::mtl::IntrusivePtr<GfMenuReferenceNumber>) {}

bool GfMenuObjDrArtsSet2::seqReturnWeaponSelect() {
  ui::UIObjectAcc acc(unknown18, "LAY_wpn");
  sendEvent(acc.unknown10, 0x101, 0);
  return true;
}

bool GfMenuObjDrArtsSet2::seqSelectItem() {
  if (!unknown258) {
    unknown0c0->reset();
    GfMenuObjCommonText::openSelectItem(unknown0c0, unknown0f0);
    unknown258 = true;
  }
  if (!unknown0c0->isTerm()) {
    return false;
  }
  GfMenuCallContext::GfMenuResult result;
  if (unknown0c0->unknown18.empty() || (unknown0c0->popResult(result), result.unknown04 == 0xffffffff)) {
    unknown0f8.unknown002(&GfMenuObjDrArtsSet2::seqReturnWeaponSelect);
  } else {
    unknown0f0->setIndex(result.unknown04);
    unknown0f8.unknown002(&GfMenuObjDrArtsSet2::seqConfirmItem);
  }
  unknown258 = false;
  return true;
}

bool GfMenuObjDrArtsSet2::seqConfirmItem() {
  if (!unknown258) {
    u32 item = unknown0f0->getContents(unknown0f0->getIndex(false)).unknown04;
    if (item >= ITEM_UNKNOWN_25405 && item <= ITEM_UNKNOWN_25407) {
      // 0x6267 is the inferred base of the common text window ids of the weapon point items.
      u32 window = item - 0x6267;
      unknown0c0->reset();
      GfMenuObjCommonText::open(unknown0c0, window, 0);
    }
    unknown258 = true;
  }
  if (!unknown0c0->isTerm()) {
    return false;
  }
  bool isConfirmed = false;
  if (!unknown0c0->unknown18.empty()) {
    GfMenuCallContext::GfMenuResult result;
    unknown0c0->popResult(result);
    isConfirmed = result.unknown00 == 0 && result.unknown04 == 0;
  }
  if (isConfirmed) {
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    u32 weaponType = unknown0a0->unknown0c;
    GfEquipUtil::execWpUpItem(driver, unknown0f0->getContents(unknown0f0->getIndex(false)).unknown04, weaponType);
    MenuItemInfo info = unknown0f0->getContents(unknown0f0->getIndex(false));
    info.unknown08 = 1;
    unknown0f0->decItem(info, false);
  }
  unknown0f8.unknown002(&GfMenuObjDrArtsSet2::seqReturnWeaponSelect);
  unknown258 = false;
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrArtsSet2>(const mm::mtl::Delegate<bool()> *);
