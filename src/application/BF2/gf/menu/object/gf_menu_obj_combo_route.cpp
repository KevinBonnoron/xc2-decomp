#include "gf/menu/object/gf_menu_obj_combo_route.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5e;

// Inferred role: cursor images of the combo route; original name unknown.
static const char *const unknown002[] = {
    "IMG_root_cursor@0101", "IMG_root_cursor@0201", "IMG_root_cursor@0202", "IMG_root_cursor@0301", "IMG_root_cursor@0302", "IMG_root_cursor@0303", "IMG_root_cursor@0304"};

GfMenuObjComboRoute::GfMenuObjComboRoute(u32 handle) : GfMenuObject(handle) {
  for (u32 i = 0; i < 8; i++) {
    unknown24[i] = -1;
  }
}

GfMenuObjComboRoute::~GfMenuObjComboRoute() { ; }

void GfMenuObjComboRoute::finalize() { GfMenuObject::finalize(); }

void GfMenuObjComboRoute::update() { GfMenuObject::update(); }

void GfMenuObjComboRoute::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjComboRoute::disp(bool isDisp) { unknown154(unknown001, isDisp); }

void GfMenuObjComboRoute::open() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjComboRoute::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupComboRoute(acc);
    acc.setDisp(true);
    break;
  case 0xd:
    if (event.unknown0c == 1) {
      u32 index = event.unknown10;
      u32 type = event.unknown08;
      ui::UIObjectAcc cursor(acc.searchChild(unknown002[index]));
      if (type == 5) {
        GfMenuObjUtil::CtrlParam param;
        cursor.setDisp(true);
        cursor.setAlpha(1.0f);
        param.unknown08 = 0x40004;
        param.unknown00 = 0.5f;
        param.unknown3c = 0.5f;
        param.unknown2c = 0.3f;
        param.unknown10 = true;
        param.unknown14 = 8;
        param.unknown0c = 3;
        int ctrl = GfMenuObjUtil::startCtrl(cursor.unknown10, param, nullptr);
        if (unknown20->unknown24[index] == -1) {
          unknown20->unknown24[index] = ctrl;
        }
      } else if (type == 6) {
        if (unknown20->unknown24[index] != -1) {
          GfMenuObjUtil::stopCtrl(unknown20->unknown24[index]);
          unknown20->unknown24[index] = -1;
        }
        cursor.setDisp(false);
      }
    }
    break;
  case 0x21:
    if (unknown0c == 0) {
      ui::UIObjectAcc root(handle, "LAY_root");
      GfMenuObjUtil::setChildDisp(handle, "LAY_root@01", true);
      GfMenuObjUtil::setChildDisp(handle, "LAY_root_base", true);
      root.setDisp(true);
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x401;
      param.unknown0c = 1;
      param.unknown00 = 0.3f;
      param.unknown11 = true;
      param.unknown14 = 4;
      param.unknown18 = unknown20->unknown24[7];
      unknown20->unknown24[7] = GfMenuObjUtil::startCtrl(root.unknown10, param, nullptr);
      unknown0c = 1;
    }
    break;
  case 0x22: {
    ui::UIObjectAcc root(handle, "LAY_root");
    if (unknown0c == 1) {
      if (unknown20->unknown24[7] != -1) {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x4002;
        param.unknown00 = 0.3f;
        param.unknown0c = 1;
        param.unknown14 = 4;
        param.unknown18 = unknown20->unknown24[7];
        GfMenuObjUtil::startCtrl(root.unknown10, param, nullptr);
      }
      unknown0c = 0;
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
