#include "gf/menu/object/gf_menu_obj_chain_count.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_battle_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the chain count layout; original name unknown.
constexpr u32 CALL_UNKNOWN_64 = 64;

// Inferred helper: starts the preset 1 fade in (0) or fade out (1) control of a UI object on a control id; original name unknown.
static int unknown001(u32 handle, int ctrl, u32 type) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown10 = 0;
  param.unknown00 = 1;
  param.unknown04 = type;
  param.unknown0d = true;
  param.unknown08 = ctrl;
  return GfMenuObjUtil::startPresetCtrl(handle, param);
}

GfMenuObjChainCount::GfMenuObjChainCount(u32 handle) : GfMenuObject(handle) {}

GfMenuObjChainCount::~GfMenuObjChainCount() { ; }

void GfMenuObjChainCount::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!main.isValid()) {
    return;
  }
// __LINE__ must be 58 as in the original file: it is the line argument of operator new.
#line 58
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(CALL_UNKNOWN_64, main.unknown10);
  GfMenuBattleAdapter::create(main.searchChild("TXT_num"), 11);
  addNumberEventCondition(main.unknown10, "TXT_num", 0, 0, 0.0f);
  GfMenuObject::initialize();
}

void GfMenuObjChainCount::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainCount::update() { GfMenuObject::update(); }

void GfMenuObjChainCount::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = 0;
    unknown14 = 0;
    unknown18 = 0;
    break;
  case 0xd:
    if (event.unknown0c == 0) {
      if (event.unknown08 == 1) {
        unknown18 = 0;
        if (unknown14 == 1 && unknown10 != 0) {
          unknown001(acc.unknown10, unknown0c, 1);
          unknown14 = 0;
        }
      } else {
        unknown18 = 1;
        if (unknown14 == 0 && unknown10 != 0) {
          int ctrl = unknown001(acc.unknown10, unknown0c, 0);
          if (ctrl != -1) {
            unknown0c = ctrl;
          }
          unknown14 = 1;
        }
      }
    }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case GfMenuTypes::unknown003_33:
    unknown10 = 1;
    if (unknown14 == 0 && unknown18 == 1) {
      int ctrl = unknown001(acc.unknown10, unknown0c, 0);
      if (ctrl != -1) {
        unknown0c = ctrl;
      }
      unknown14 = 1;
    }
    break;
  case GfMenuTypes::unknown003_34:
    unknown10 = 0;
    if (unknown14 != 0) {
      unknown001(acc.unknown10, unknown0c, 1);
      unknown14 = 0;
    }
    break;
  }
}

void GfMenuObjChainCount::open() { unknown146(CALL_UNKNOWN_64, GfMenuTypes::unknown003_33); }

void GfMenuObjChainCount::close() { unknown146(CALL_UNKNOWN_64, GfMenuTypes::unknown003_34); }

} // namespace gf
