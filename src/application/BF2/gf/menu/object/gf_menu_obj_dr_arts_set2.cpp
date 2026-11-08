#include "gf/menu/object/gf_menu_obj_dr_arts_set2.h"

#include "gf/data/gf_data_driver_arts.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_arts_list.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ui_object_acc.h"

namespace gf {

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

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrArtsSet2>(const mm::mtl::Delegate<bool()> *);
