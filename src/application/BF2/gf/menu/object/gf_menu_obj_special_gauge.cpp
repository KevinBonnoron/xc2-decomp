#include "gf/menu/object/gf_menu_obj_special_gauge.h"

#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown004 = 0x100;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x29;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

// Inferred helper: starts the preset 0 fade in (0) or fade out (1) control of a UI object on a control id; original name unknown.
static int unknown005(u32 handle, int ctrl, u32 type) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown10 = 0;
  param.unknown00 = 0;
  param.unknown04 = type;
  param.unknown0d = true;
  param.unknown08 = ctrl;
  return GfMenuObjUtil::startPresetCtrl(handle, param);
}

GfMenuObjSpecialGauge::GfMenuObjSpecialGauge(u32 handle) : GfMenuObject(handle) {}

GfMenuObjSpecialGauge::~GfMenuObjSpecialGauge() { ; }

void GfMenuObjSpecialGauge::push() { unknown144(unknown001, unknown002); }

void GfMenuObjSpecialGauge::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSpecialGauge::update() {
  ui::UIObjectAcc(unknown18).setAlpha(1.0f);
  GfMenuObject::update();
}

void GfMenuObjSpecialGauge::close() { unknown145(unknown001, unknown003); }

void GfMenuObjSpecialGauge::open() { unknown145(unknown001, unknown004); }

void GfMenuObjSpecialGauge::reverse(bool isReverse) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = 0x10b;
    event.unknown08 = isReverse;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjSpecialGauge::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = unknown006();
    unknown18 = 1;
    break;
  case 0xd: {
    int state = event.unknown08;
    switch (event.unknown0c) {
    case 0: {
      u32 index = event.unknown10;
      mm::mtl::FixStr<32> name;
      name.format("LAY_gauge_lv@%d", index);
      if (state == 1) {
        GfMenuObjUtil::playSE(0x27);
        acc.setDispChild(false, name.c_str());
      } else {
        acc.setDispChild(true, name.c_str());
      }
      break;
    }
    case 1:
      if (state == 1) {
        acc.setDispChild(false, "LAY_arts_lv");
      } else {
        acc.setDispChild(true, "LAY_arts_lv");
      }
      break;
    }
    break;
  }
  case 0x100:
    if (GfMenuManager::isBattleState(0)) {
      unknown10.unknown00 = 1;
      if (unknown10.unknown04 == 0 && unknown18 == 1) {
        int ctrl = unknown005(acc.unknown10, unknown0c, 0);
        if (ctrl != -1) {
          unknown0c = ctrl;
        }
        unknown10.unknown04 = 1;
      }
    }
    break;
  case 0x101:
    unknown10.unknown00 = 0;
    if (unknown10.unknown04 != 0) {
      unknown005(acc.unknown10, unknown0c, 1);
      unknown10.unknown04 = 0;
    }
    break;
  case 0x10a:
    if (unknown10.unknown04 == 1) {
      GfMenuObjUtil::playSE(0x28);
    }
    break;
  case 0x10b: {
    int state = event.unknown08;
    ui::UIObjectAcc parent(acc.getParentHandle());
    parent.setDisp(state != 1);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
