#include "gf/menu/object/gf_menu_obj_common_text.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/menu/gf_menu_common_window_param.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x64;

void GfMenuObjCommonText::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonText::update() { GfMenuObject::update(); }

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

} // namespace gf
