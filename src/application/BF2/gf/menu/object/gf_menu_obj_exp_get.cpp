#include "gf/menu/object/gf_menu_obj_exp_get.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x2e;

GfMenuObjExpGet::GfMenuObjExpGet(u32 handle) : GfMenuObject(handle) {}

GfMenuObjExpGet::~GfMenuObjExpGet() {
  GfMenuManyObjects::destroy<ExpGetInfo>(GfMenuManyObjects::unknown001_4);
  GfMenuManyObjects::destroy<ExpGetInfo>(GfMenuManyObjects::unknown001_5);
}

void GfMenuObjExpGet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjExpGet::close(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (!root.isValid()) {
    return;
  }
  if (root.isTerm()) {
    return;
  }
  ui::UIObjectAcc acc(handle);
  if (!acc.isValid()) {
    return;
  }
  if (!acc.isDuplicate()) {
    return;
  }
  ui::EventData event;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
  event.unknown0a = 0;
  sendEvent(root.unknown10, event, 0.0f);
}

void GfMenuObjExpGet::close2(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (!root.isValid()) {
    return;
  }
  if (root.isTerm()) {
    return;
  }
  ui::UIObjectAcc acc(handle);
  if (!acc.isValid()) {
    return;
  }
  if (!acc.isDuplicate()) {
    return;
  }
  ui::EventData event;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
  event.unknown0a = 1;
  sendEvent(root.unknown10, event, 0.0f);
}

void GfMenuObjExpGet::closeAll() {
  GfMenuManyObjects::closeAll<ExpGetInfo>(GfMenuManyObjects::unknown001_4, &GfMenuObjExpGet::close);
  GfMenuManyObjects::closeAll<ExpGetInfo>(GfMenuManyObjects::unknown001_5, &GfMenuObjExpGet::close2);
}

void GfMenuObjExpGet::removeObject2(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<ExpGetInfo>(GfMenuManyObjects::unknown001_5, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

void GfMenuObjExpGet::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<ExpGetInfo>(GfMenuManyObjects::unknown001_4, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

void GfMenuObjExpGet::sendOpen(u32 handle, const ExpGetInfo &info) {
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_33;
  event.unknown08 = info.unknown10.unknown00;
  event.unknown0c = info.unknown10.unknown04;
  event.unknown10_u16 = ui::UIObjectAcc(info.unknown08).getDuplicateIndex();
  event.unknown12 = info.unknown10.unknown18;
  event.unknown14 = info.unknown10.unknown08;
  sendEvent(handle, event, 0.0f);
}

const char *GfMenuObjExpGet::setupScreen(u32 handle, int type, int amount, int, int bonus) {
  ui::UIObjectAcc acc(handle);
  const char *name = nullptr;
  switch (type) {
  case 0:
    GfMenuObjUtil::createNumberPlugin(ui::UIObjectAcc(handle, "TXT_exp_num").unknown10, amount);
    GfMenuObjUtil::setChildDisp(handle, "IMG_exp_bonus", bonus != 0);
    name = "LAY_exp";
    GfMenuObjUtil::setChildDisp(handle, "LAY_exp", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_sp", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_wp", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", false);
    break;
  case 1:
    GfMenuObjUtil::createNumberPlugin(ui::UIObjectAcc(handle, "TXT_sp_num").unknown10, amount);
    GfMenuObjUtil::setChildDisp(handle, "IMG_sp_bonus", bonus != 0);
    GfMenuObjUtil::setChildDisp(handle, "LAY_exp", false);
    name = "LAY_sp";
    GfMenuObjUtil::setChildDisp(handle, "LAY_sp", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_wp", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", false);
    break;
  case 2:
    GfMenuObjUtil::createNumberPlugin(ui::UIObjectAcc(handle, "TXT_wp_num").unknown10, amount);
    GfMenuObjUtil::setChildDisp(handle, "IMG_wp_bonus", bonus != 0);
    GfMenuObjUtil::setChildDisp(handle, "LAY_exp", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_sp", false);
    name = "LAY_wp";
    GfMenuObjUtil::setChildDisp(handle, "LAY_wp", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", false);
    break;
  case 3: {
    ui::UIObjectAcc number(handle, "TXT_lvup_num");
    number.setDisp(false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_exp", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_sp", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_wp", false);
    name = "LAY_lvup";
    GfMenuObjUtil::setChildDisp(handle, "LAY_lvup", true);
    break;
  }
  }
  return name;
}

void GfMenuObjExpGet::update() { GfMenuObject::update(); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjExpGet::ExpGetInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjExpGet::ExpGetInfo>::push_back(const gf::GfMenuObjExpGet::ExpGetInfo &);
template void mm::mtl::Queue<gf::GfMenuObjExpGet::ExpGetInfo>::expand(size_t, size_t);
