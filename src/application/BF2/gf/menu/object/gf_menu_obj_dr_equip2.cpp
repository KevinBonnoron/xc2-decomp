#include "gf/menu/object/gf_menu_obj_dr_equip2.h"

#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjDrEquip2::GfMenuObjDrEquip2(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(false), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown60(nullptr), unknown68(nullptr),
      unknown70(nullptr), unknown7c(0) {
  unknown70 = GfMenuCallContext::create();
}

GfMenuObjDrEquip2::~GfMenuObjDrEquip2() {
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  unknown58 = nullptr;
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjDrEquip2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrEquip2::update() { GfMenuObject::update(); }

void GfMenuObjDrEquip2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrEquip2::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  if (type == 0) {
    ctrl = GfMenuObjUtil::unknown002(handle);
  } else if (type == 1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrEquip2::setFadeOut(u32 handle, u32 type) {
  int ctrl = -1;
  if (type == 0) {
    ctrl = GfMenuObjUtil::unknown003(handle);
  } else if (type == 1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjDrEquip2::setupEquipItem(ui::UIObjectAcc &acc, GfMenuItemList *list) {
  GfMenuItemAdapter::createFromList(acc.searchChild("TXT_equip_item_tag"), 0, list, -1, false);
  GfMenuItemAdapter::createFromList(acc.searchChild("TXT_equip_item_info"), 9, list, -1, false);
  GfMenuItemAdapter::createFromList(acc.searchChild("IMG_equip_item_reality_icon"), 7, list, -1, false);
}

} // namespace gf
