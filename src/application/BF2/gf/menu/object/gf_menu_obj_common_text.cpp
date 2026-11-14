#include "gf/menu/object/gf_menu_obj_common_text.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_common_window_param.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/input/ui_input_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_sync_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x64;

ui::UIListInfo<MenuItemInfo> *GfMenuObjCommonText::s_pItemList;
ui::UIListInfo<MenuID> *GfMenuObjCommonText::s_pSubMenuIDList;
ui::UIListInfo<MenuDriverInfo> *GfMenuObjCommonText::s_pChangeDrList;

void GfMenuObjCommonText::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonText::update() { GfMenuObject::update(); }

void GfMenuObjCommonText::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown10 = 0xff;
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuAdapterManager::addActiveCategory(3);
    unknown10 = event.unknown16;
    u32 window;
    switch (unknown10) {
    case 0:
      window = acc.searchChild("LAY_dialog");
      break;
    case 1:
      window = acc.searchChild("LAY_error");
      break;
    case 2:
      window = acc.searchChild("LAY_dialog_mer");
      break;
    case 3:
      window = acc.searchChild("LAY_dialog_kizuna");
      break;
    case 4:
      window = acc.searchChild("LAY_get_item");
      break;
    case 5:
      window = acc.searchChild("LAY_select");
      break;
    case 6:
      window = acc.searchChild("LAY_dr_change");
      break;
    case 7:
      window = acc.searchChild("LAY_owner_change");
      break;
    case 8:
      window = acc.searchChild("LAY_num_select");
      break;
    default:
      GfMenuObject::termCallContext(acc.unknown10);
      return;
    }
    if (window == 0) {
      return;
    }
    if (unknown10 == 5) {
      GfMenuObject::sendEvent(window, event, 0.06666667f);
    } else {
      GfMenuObject::sendEvent(window, event, 0.0f);
    }
    ui::UIObjectAcc(window).setSuspend(false);
    ui::UIInputManager *inputManager = ui::UIInputManager::get();
    unknown0c = inputManager->unknown20;
    inputManager->unknown20 = ui::UIUtil::getGroupPriority(4);
    GfMenuObjUtil::playSE(9);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    // The game holds the window lookup of event 0x21 a second time here (its own jump table at 0x7100f6e0a8), with a default that only leaves.
    u32 window;
    switch (unknown10) {
    case 0:
      window = acc.searchChild("LAY_dialog");
      break;
    case 1:
      window = acc.searchChild("LAY_error");
      break;
    case 2:
      window = acc.searchChild("LAY_dialog_mer");
      break;
    case 3:
      window = acc.searchChild("LAY_dialog_kizuna");
      break;
    case 4:
      window = acc.searchChild("LAY_get_item");
      break;
    case 5:
      window = acc.searchChild("LAY_select");
      break;
    case 6:
      window = acc.searchChild("LAY_dr_change");
      break;
    case 7:
      window = acc.searchChild("LAY_owner_change");
      break;
    case 8:
      window = acc.searchChild("LAY_num_select");
      break;
    default:
      return;
    }
    if (window == 0) {
      return;
    }
    GfMenuObject::sendEvent(window, event, 0.0f);
    ui::UIInputManager *inputManager = ui::UIInputManager::get();
    inputManager->unknown20 = unknown0c;
    GfMenuObject::termCallContext(handle);
    unknown10 = 0xff;
    GfMenuAdapterManager::delActiveCategory(3);
    break;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCommonText::setupDialog(u32 handle) {
  GfMenuObjUtil::FitOption option;
  option.unknown00 = true;
  option.unknown01 = true;
  u32 text = ui::UIUtil::searchChild(handle, "LAY_dialog_text");
  GfMenuObjUtil::createFitPlugin(ui::UIUtil::searchChild(handle, "IMG_dialog_win@01"), text, 0, 0, option);
  GfMenuObjUtil::createFitPlugin(ui::UIUtil::searchChild(handle, "IMG_dialog_win@02"), text, 0, 0, option);
  u32 cursor = ui::UIUtil::searchChild(handle, "LAY_dialog_cursor");
  ui::UIObjectSyncPlugin *plugin;
  {
    ui::UIObjectAcc acc(cursor);
    plugin = ui::UIObjectSyncPlugin::create(acc.searchSibiling("LAY_dialog_cursor_base"));
  }
  plugin->setTargetObject(cursor);
  plugin->setTargetFlag(0x3e);
  if (plugin != nullptr) {
    plugin->release();
  }
}

void GfMenuObjCommonText::sendEvent(u32 handle, u32 type, u32 param, f32 delay) { unknown140(handle, type, param, delay); }

int GfMenuObjCommonText::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjCommonText::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjCommonText::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjCommonText::open(GfMenuCallContext *context, const MenuCommonWindowParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (!isTerm) {
      startCallContext(context, unknown001, handle);
      u16 title = 0xffff;
      if (param.unknown00 != nullptr) {
        ui::UIStr str(param.unknown00, param.unknown08);
        title = registString(str);
      }
      u16 text = 0xffff;
      if (param.unknown10 != nullptr) {
        ui::UIStr str(param.unknown10, param.unknown18);
        text = registString(str);
      }
      u16 ok = 0xffff;
      if (param.unknown20 != nullptr) {
        ui::UIStr str(param.unknown20, param.unknown28);
        ok = registString(str);
      }
      u16 cancel = 0xffff;
      if (param.unknown30 != nullptr) {
        ui::UIStr str(param.unknown30, param.unknown38);
        cancel = registString(str);
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown08_u16 = title;
      event.unknown0a = text;
      event.unknown0c_u16 = ok;
      event.unknown0e = cancel;
      event.unknown10_u16 = param.unknown3c;
      event.unknown12 = param.unknown40 != 0;
      event.unknown14_u16 = param.unknown44;
      event.unknown16 = param.unknown48;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjCommonText::open(GfMenuCallContext *context, u32 window, u32 param) {
  u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
  if (windowBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_CMNWINDOW);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      u16 title = Bdat::getVal(windowBdat, "title", window).valueU16;
      if (title != 0) {
        windowParam.unknown00 = textBdat;
        windowParam.unknown08 = title;
      }
      u16 text = Bdat::getVal(windowBdat, "text", window).valueU16;
      if (text != 0) {
        windowParam.unknown10 = textBdat;
        windowParam.unknown18 = text;
      }
      u16 ok = Bdat::getVal(windowBdat, "select_ok_txt", window).valueU16;
      if (ok != 0) {
        windowParam.unknown20 = textBdat;
        windowParam.unknown28 = ok;
      }
      u16 cancel = Bdat::getVal(windowBdat, "select_cancel_txt", window).valueU16;
      if (cancel != 0) {
        windowParam.unknown30 = textBdat;
        windowParam.unknown38 = cancel;
      }
      windowParam.unknown3c = Bdat::getVal(windowBdat, "type", window).valueU8;
      windowParam.unknown40 = Bdat::getVal(windowBdat, "select", window).valueU8;
      windowParam.unknown44 = param;
      windowParam.unknown48 = 0;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openItem(GfMenuCallContext *context, u32 window, u32 item) {
  u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
  if (windowBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_CMNWINDOW);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      windowParam.unknown00 = textBdat;
      windowParam.unknown08 = Bdat::getVal(windowBdat, "title", window).valueU16;
      {
        u8 itemType = GfDataItem::getItemType(item);
        ui::UIStr name;
        GfMenuItemUtil::getItemName(itemType, item, name);
        windowParam.unknown10 = name.getMsgFP();
        windowParam.unknown18 = name.getMsgID();
      }
      windowParam.unknown3c = Bdat::getVal(windowBdat, "type", window).valueU8;
      windowParam.unknown40 = Bdat::getVal(windowBdat, "select", window).valueU8;
      windowParam.unknown48 = 0;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openError(GfMenuCallContext *context, u32 error, u32 param) {
  u8 *errorBdat = GfDataBdat::getFP(BDAT_MNU_MSG_ERROR_INFO);
  if (errorBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_ERROR_INFO_MS);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      u16 name = Bdat::getVal(errorBdat, "name", error).valueU16;
      if (name != 0) {
        windowParam.unknown10 = textBdat;
        windowParam.unknown18 = name;
      }
      windowParam.unknown44 = param;
      windowParam.unknown48 = 1;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openMissionStop(GfMenuCallContext *context, u32 mission, u32 param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
      if (windowBdat != nullptr) {
        u16 text = Bdat::getVal(windowBdat, "text", mission).valueU16;
        if (text == 0) {
          context->abort();
        } else {
          u16 textId;
          {
            ui::UIStr str(GfDataBdat::getFP(BDAT_MENU_CMNWINDOW), text);
            textId = registString(str);
          }
          ui::EventData event;
          event.unknown00 = 0x21;
          event.unknown08 = param;
          event.unknown0c_u16 = textId;
          event.unknown0e = Bdat::getVal(windowBdat, "type", mission).valueU8;
          event.unknown10_u16 = Bdat::getVal(windowBdat, "select", mission).valueU8;
          event.unknown16 = 2;
          GfMenuObject::sendEvent(handle, event, 0.0f);
          startCallContext(context, unknown001, handle);
        }
      }
    }
  }
}

void GfMenuObjCommonText::openKizunaDialog(GfMenuCallContext *context, const OpenKizunaParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm && GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW) != nullptr) {
      u16 textId;
      {
        ui::UIStr str(param.unknown00, param.unknown08);
        textId = registString(str);
      }
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x21;
      event.unknown08 = param.unknown0c;
      event.unknown0c_u16 = textId;
      event.unknown16 = 3;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openGetItem(GfMenuCallContext *context, const GfMenuItemList *items) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pItemList->clear();
      for (u32 i = 0; i < items->getSize(); i++) {
        s_pItemList->addContents(items->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 4;
      GfMenuObject::sendEvent(handle, event, 0.033333335f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openSubMenu(GfMenuCallContext *context, const GfMenuIDList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pSubMenuIDList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pSubMenuIDList->addContents(list->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 5;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openSelectItem(GfMenuCallContext *context, const GfMenuItemList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pItemList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pItemList->addContents(list->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown08 = 1;
      event.unknown16 = 5;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openDrChange(GfMenuCallContext *context, u32 driver, const GfMenuDriverList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pChangeDrList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pChangeDrList->addContents(list->getContents(i));
      }
      s_pChangeDrList->setIndex(0);
      GfMenuReference::setReferenceDriverID(4, driver);
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 6;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openOwnerChange(GfMenuCallContext *context, u32 driver, u32 other) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      GfMenuReference::setReferenceDriverID(4, driver);
      GfMenuReference::setReferenceDriverID(5, other);
      ui::EventData event;
      event.unknown08_u16 = 0;
      event.unknown00 = 0x21;
      event.unknown16 = 7;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openNumSelect(GfMenuCallContext *context, const OpenNumSelectParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x21;
      event.unknown08_u16 = param.unknown00;
      event.unknown0a = param.unknown04;
      event.unknown0c_u16 = param.unknown08;
      event.unknown10 = param.unknown0c;
      event.unknown16 = 8;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::ErrorListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setSuspend(true);
    unknown18 = 0;
    break;
  case 3:
    if (event.unknown08 == 0) {
      return;
    }
    if (event.unknown08 == 2 && unknown18 == 0) {
      acc.setSuspend(true);
    }
    break;
  case 8:
    GfMenuObject::addResultCallContext(owner.searchChild("LAY_main"), 0, 0);
    close();
    break;
  case GfMenuTypes::unknown003_33: {
    u16 text = event.unknown0a;
    s16 bottom = event.unknown14_u16;
    if (text != 0xffff) {
      GfMenuObjUtil::setChildText(handle, "TXT_error", text);
    }
    setFadeIn(handle);
    GfMenuObject::enableInput(handle);
    mm::Rect<s16> rect;
    acc.getLayoutRect(bottom == 0 ? "error_dialog_top" : "error_dialog_bottom", rect);
    mm::Pnt<s16> center(rect.x + rect.width / 2, rect.y + rect.height / 2);
    acc.setPosCenter(center);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    setFadeOut(handle);
    GfMenuObject::disableInput(handle);
    unknown18 = 0;
    break;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjCommonText::OwnerChangeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    acc.setSuspend(true);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setAlpha(1.0f);
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
      GfMenuObject::termCallContext(acc.getParentHandle());
    }
    break;
  case 8: {
    u32 input = event.unknown0c;
    if (input == 1 || input == 2) {
      close();
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    s16 owner = event.unknown08_u16;
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = 0.25f;
      param.unknown04 = 1;
      param.unknown08 = 1;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    acc.setDispChild(owner == 0, "TXT_owner_change_caption");
    acc.setDispChild(owner == 1, "TXT_owner_change_caption_rex");
    acc.setDispChild(owner == 2, "TXT_owner_change_caption_rex2");
    {
      ui::UIObjectAcc okOnly(acc.searchChild("LAY_owner_ch_ok_only"));
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_owner_ch_cursor_l"), okOnly.unknown10, 1, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_owner_ch_cursor_l"), -10, 0);
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_owner_ch_cursor_r"), okOnly.unknown10, 2, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_owner_ch_cursor_r"), 10, 0);
    }
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.25f;
    param.unknown04 = 2;
    param.unknown08 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::GetItemListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    acc.setSuspend(true);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setAlpha(1.0f);
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    break;
  case 8: {
    u32 input = event.unknown0c;
    if (input == 1 || input == 2) {
      close();
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case GfMenuTypes::unknown003_33: {
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = 0.25f;
      param.unknown08 = 1;
      param.unknown1c = 1.0f / 30.0f;
      param.unknown04 = 1;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    acc.setAlpha(0.0f);
    {
      ui::UIObjectAcc okOnly(acc.searchChild("LAY_get_item_ok_only"));
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_get_item_cursor_l"), okOnly.unknown10, 1, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_get_item_cursor_l"), -10, 0);
      GfMenuObjUtil::setDockPos(acc.searchChild("IMG_get_item_cursor_r"), okOnly.unknown10, 2, true);
      GfMenuObjUtil::addPos(acc.searchChild("IMG_get_item_cursor_r"), 10, 0);
    }
    mm::Rect<s16> rect;
    acc.getLayoutRect("item_3", rect);
    mm::Rect<s16> next;
    acc.getLayoutRect("item_4", next);
    GfMenuObjUtil::placeObjectV(acc.unknown10, "LAY_get_item@%02d", s_pItemList->getSize(), mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.y - rect.y);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObject::disableInput(acc.unknown10);
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.25f;
    param.unknown04 = 2;
    param.unknown08 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::DrChangeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(false);
    acc.setSuspend(true);
    unknown18 = 0;
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
      unknown20->unknown70->setDisp(true);
    } else if (event.unknown08 == 2) {
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    s_pChangeDrList->setIndex(index);
    unknown20->unknown68->setIndex(index);
    if (previous != 0xffffffff && index != previous) {
      GfMenuObjUtil::playSECommonCursor();
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      u32 driver = event.unknown08;
      GfMenuObject::addResultCallContext(acc.getParentHandle(), driver, 0);
      GfMenuObjUtil::playSE(10);
    } else if (event.unknown0c == 2) {
      GfMenuObjUtil::playSECommonCancel();
    } else {
      break;
    }
    close();
    unknown20->unknown70->setDisp(true);
    break;
  case GfMenuTypes::unknown003_33: {
    acc.setAlpha(1.0f);
    {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = 0.25f;
      param.unknown04 = 1;
      param.unknown08 = 1;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    mm::Rect<s16> rect;
    acc.getLayoutRect("dr_select", rect);
    mm::Rect<s16> next;
    acc.getLayoutRect("dr_select_next", next);
    GfMenuObjUtil::placeObjectH(acc.unknown10, "LAY_dr_change@%02d", s_pChangeDrList->getSize(), mm::Pnt<s16>(rect.x + rect.width / 2, rect.y + rect.height / 2), next.x - rect.x);
    unknown20->unknown70->setDisp(false);
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelectionFromList(acc.unknown10, *s_pChangeDrList);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.25f;
    param.unknown04 = 2;
    param.unknown08 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::disableInput(acc.unknown10);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjCommonText::NumSelectListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuAdapterManager::beginCategory(3);
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_value"), unknown20->unknown78, true);
    GfMenuReferenceAdapter::create(acc.searchChild("TXT_num_select_total_price"), unknown20->unknown80, true);
    GfMenuAdapterManager::endCategory();
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(false);
    acc.setSuspend(true);
    unknown18 = 0;
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      if (unknown18 == 0) {
        acc.setSuspend(true);
      }
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 6: {
    int index = event.unknown08;
    int previous = event.unknown0c;
    unknown20->unknown78->unknown162(index);
    unknown20->unknown80->unknown162(unknown20->unknown88 * index);
    if (previous != -1 && index != previous) {
      GfMenuObjUtil::playSE(0x19);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      if (unknown20->unknown78->unknown0c == 0) {
        break;
      }
      GfMenuObject::addResultCallContext(owner.searchChild("LAY_main"), 0, unknown20->unknown78->unknown0c);
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
    } else if (event.unknown0c == 2) {
      GfMenuObject::addResultCallContext(owner.searchChild("LAY_main"), 1, 0);
      unknown164(owner.searchChild("LAY_main"), GfMenuTypes::unknown003_34);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  case GfMenuTypes::unknown003_33: {
    s16 isSingle = event.unknown08_u16;
    ui::UIObjectAcc first(acc.searchChild("TXT_num_select_index@01"));
    first.setDisp(isSingle == 0);
    ui::UIObjectAcc second(acc.searchChild("TXT_num_select_index@02"));
    second.setDisp(isSingle != 0);
    unknown20->unknown78->unknown162(0);
    unknown20->unknown78->unknown165(event.unknown0a);
    unknown20->unknown78->unknown166(event.unknown0c_u16);
    unknown20->unknown80->unknown162(0);
    unknown20->unknown80->unknown165(0);
    unknown20->unknown80->unknown166(999999999);
    unknown20->unknown88 = event.unknown10;
    GfMenuObject::resetInputSelection(handle);
    GfMenuObject::setupInputSelection(handle, 0, event.unknown0c_u16 + 1);
    setFadeIn(handle);
    unknown18 = 1;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObject::disableInput(acc.unknown10);
    setFadeOut(handle);
    unknown18 = 0;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
