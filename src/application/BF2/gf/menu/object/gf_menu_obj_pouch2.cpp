#include "gf/menu/object/gf_menu_obj_pouch2.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/game/item/gf_pouch_util.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_pouch_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred helper: requests an event with its type and first two parameters on a UI object; original name unknown.
static inline void unknown001(u32 handle, u16 type, u32 param0, u32 param1) {
  ui::EventData event;
  event.unknown10_u64 = 0;
  event.unknown0c = param1;
  event.unknown00 = type;
  event.unknown08 = param0;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

GfMenuObjPouch2::GfMenuObjPouch2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown5c(0), unknown60(0), unknown64(0), unknown68(nullptr),
      unknown70(), unknownd0(), unknown130(this), unknown3c9(false), unknown3d0(nullptr), unknown3d8(0), unknown3e0(nullptr), unknown3e8(false) {}

GfMenuObjPouch2::~GfMenuObjPouch2() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown3e0);
  unknown38 = nullptr;
}

void GfMenuObjPouch2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPouch2::update() {
  unknown130.unknown003();
  GfMenuObject::update();
}

void GfMenuObjPouch2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPouch2::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown002(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r_early");
    param.unknown04 = 1;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPouch2::setFadeOut(u32 handle, u32 type) {
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
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjPouch2::setupSlot(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber>) {
  mm::mtl::FixStr<32> name;
  for (u32 slot = 1; slot != 4; slot++) {
    u32 index = slot - 1;
    name.format("IMG_eqpouch_slicon@%02d", slot);
    GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 2, index, 0, false);
    name.format("TXT_eqpouch_efftime@%02d", slot);
    ui::UIObjectAcc time(acc.searchChild(name.c_str()));
    GfMenuPouchAdapter *adapter = GfMenuPouchAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0, index, 0, false);
    name.format("IMG_eqpouch_efftime_bg@%02d", slot);
    ui::UIObjectAcc background(acc.searchChild(name.c_str()));
    if (adapter != nullptr) {
      adapter->unknown24 = background.unknown10;
    }
    GfMenuObjUtil::FitOption option;
    GfMenuObjUtil::createFitPlugin(background.unknown10, time.unknown10, 8, 8, option);
    name.format("TXT_eqpouch_name@%02d", slot);
    GfMenuItemAdapter::createFromPouchReferenceDriver(acc.searchChild(name.c_str()), 0, index, 0, false);
  }
}

void GfMenuObjPouch2::getFilterText(u32 filter, ui::UIStr &text) {
  ui::UIStr filterText(GfDataBdat::getFP(BDAT_MENU_FILTER_CATEGORY), GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_POUCH_FILTER, filter + 1));
  text.copy(filterText);
}

bool GfMenuObjPouch2::seqFavOpen() {
  unknown3c8 = false;
  unknown3c0 = 0;
  return true;
}

GAME_VOICE_HANDLE *GfMenuObjPouch2::procFavFlag(ui::UIObjectAcc &acc, FavoriteFlag &flag, u32 index, u32 favorite) {
  static const char *const effects[] = {"IMG_chr_fvicon01eff@%02d", "IMG_chr_fvicon02eff@%02d", "IMG_chr_fviconit01eff@%02d", "IMG_chr_fviconit02eff@%02d"};
  static const char *const icons[] = {"IMG_chr_fvicon01anm@%02d", "IMG_chr_fvicon02anm@%02d", "IMG_chr_fviconit01anm@%02d", "IMG_chr_fviconit02anm@%02d"};
  mm::mtl::FixStr<32> name;
  name.format(effects[favorite], index + 1);
  ui::UIObjectAcc effect(acc.searchChild(name.c_str()));
  effect.startAnimation("flash", false);
  name.format(icons[favorite], index + 1);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "mnu070_heart";
  param.unknown58 = "fadein_a";
  param.unknown04 = 1;
  GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
  return SCOM_FIELD_VOICE::createFavorite(flag.unknown00, static_cast<FAVORITE>(favorite));
}

void GfMenuObjPouch2::updateSlotList(GfMenuItemList *list) {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  list->clear();
  for (u32 slot = 0; slot < 3; slot++) {
    SDataPouch *pouch = GfPouchUtil::getPouch(driver, slot);
    if (pouch->_06 != 0) {
      MenuItemInfo info;
      info.unknown00 = ItemType::FAVORITE;
      info.unknown04 = pouch->unknown04;
      info.unknown08 = info.unknown04 != 0;
      list->addContents(info);
    }
  }
}

bool GfMenuObjPouch2::seqFavClose() {
  ui::UIObjectAcc acc(unknown18);
  sendEvent(acc.searchChild("LAY_fvstock_fevitem"), 0x22, 0);
  unknown001(acc.searchChild("LAY_stock_filter2"), 0x22, 0, 0);
  unknown001(acc.searchChild("LAY_chr_fevinfo"), 0x102, 0, 0);
  unknown001(acc.searchChild("LAY_eqp_fevitem"), 0x101, 1, 0);
  unknown3c0 = 0;
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPouch2>(const mm::mtl::Delegate<bool()> *);
