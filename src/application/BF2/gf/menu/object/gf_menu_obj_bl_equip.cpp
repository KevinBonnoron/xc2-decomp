#include "gf/menu/object/gf_menu_obj_bl_equip.h"

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_equip_util.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

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
    info.unknown00 = ItemType::EQUIP_ORB;
    info.unknown04 = 0;
    info.unknown08 = 0;
    info.unknown0c = GfItemHandle(0);
  }
  refreshItemList(acc, list, selectList, slot);
  return true;
}

} // namespace gf
