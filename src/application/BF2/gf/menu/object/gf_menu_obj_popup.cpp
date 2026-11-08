#include "gf/menu/object/gf_menu_obj_popup.h"

#include "gf/game/gf_game_manager.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col3.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/ui_manager.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x76;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x102;

GfMenuObjPopup::GfMenuObjPopup(u32 handle)
    : GfMenuObject(handle), unknown24(false), unknown28(0), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(this) {}

GfMenuObjPopup::~GfMenuObjPopup() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown58);
  GfMenuManyObjects::destroy<PopupInfo>(GfMenuManyObjects::unknown001_7);
}

void GfMenuObjPopup::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPopup::update() {
  unknown60.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPopup::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPopup::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown002(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPopup::setFadeOut(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown003(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjPopup::pausePickup() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

void GfMenuObjPopup::continuePickup(u32 type) {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (!isTerm && !GfGameManager::isEvent(false) && !GfGameManager::isEventWait()) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = unknown003;
      event.unknown08 = type;
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjPopup::close(u32 handle) {
  ui::UIObjectAcc main(GfMenuObject::getAttachedObject(unknown001));
  if (main.isValid() && !main.isTerm()) {
    ui::UIObjectAcc acc(handle);
    if (acc.isValid() && acc.isDuplicate()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjPopup::sendOpen(u32 handle, const PopupInfo &info) {
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_33;
  event.unknown08 = info.unknown0c.unknown00;
  event.unknown0c = info.unknown0c.unknown04;
  event.unknown10 = info.unknown0c.unknown08;
  event.unknown14 = info.unknown0c.unknown0c;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

void GfMenuObjPopup::setFlagIcon(ui::UIObjectAcc &acc, u32 flag) {
  if (flag != 0) {
    acc.setDisp(true);
    acc.setAddColor(mm::Col3(0.3f, 0.3f, 0.3f));
    acc.setImageIndex(flag - 1);
  }
}

void GfMenuObjPopup::setFaceIcon(ui::UIObjectAcc &acc, const DataParamAcc &param) {
  acc.setDisp(true);
  int icon = GfMenuObjUtil::getFaceIconID(param);
  if (icon != 0) {
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
  }
}

void GfMenuObjPopup::removeObject(ui::UIObjectAcc acc) { GfMenuManyObjects::remove<PopupInfo>(GfMenuManyObjects::unknown001_7, acc.unknown10); }

void GfMenuObjPopup::closeAll() { GfMenuManyObjects::closeAll<PopupInfo>(GfMenuManyObjects::unknown001_7, &GfMenuObjPopup::close); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPopup>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjPopup, 8>>(const mm::mtl::Delegate<bool()> *);

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjPopup::PopupInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjPopup::PopupInfo>::push_back(const gf::GfMenuObjPopup::PopupInfo &);
template void mm::mtl::Queue<gf::GfMenuObjPopup::PopupInfo>::expand(size_t, size_t);
