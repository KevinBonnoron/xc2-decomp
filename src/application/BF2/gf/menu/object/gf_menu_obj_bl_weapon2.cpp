#include "gf/menu/object/gf_menu_obj_bl_weapon2.h"

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
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
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  u32 weapon = GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip);
  return acc.getEquipWeapon(-1, false) == weapon;
}

bool GfMenuObjBlWeapon2::isDownWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
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

} // namespace gf
