#include "gf/menu/object/gf_menu_obj_blade_switch.h"

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x22;

GfMenuObjBladeSwitch::GfMenuObjBladeSwitch(u32 handle) : GfMenuObject(handle), unknown24(false), unknown25(false), unknown26(false), unknown28(this) {}

GfMenuObjBladeSwitch::~GfMenuObjBladeSwitch() {}

void GfMenuObjBladeSwitch::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  GfMenuObject::initialize();
}

void GfMenuObjBladeSwitch::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeSwitch::update() {
  if (!unknown26) {
    return;
  }
  if (GfGameManager::isEvent(false)) {
    return;
  }
  bool isEnable = GfGameScene::get()->isEnableFieldBladeChange();
  GF_OBJ_HANDLE *leader = GfGameParty::getLeader();
  if (leader == INVALID_HANDLE) {
    return;
  }
  GfObjAcc acc(leader);
  bool isActive = false;
  if (acc.getType() == OBJECT_TYPE_DRIVER) {
    u32 count = 0;
    for (int slot = 0; slot < 3; slot++) {
      count += GfMenuObjUtil::isValidBlade(GfDataDriver::getBlade(acc.getBdatId(), slot));
    }
    isActive = count != 1 && isEnable;
  }
  if (isActive != unknown24) {
    if (isActive) {
      unknown155(unknown001, GfMenuTypes::unknown003_33);
    } else {
      unknown155(unknown001, GfMenuTypes::unknown003_34);
    }
    unknown24 = isActive;
  }
  GfMenuObject::update();
}

void GfMenuObjBladeSwitch::open() { unknown144(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjBladeSwitch::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeSwitch::setActive(bool isActive) { unknown150(unknown001, 0x100, isActive); }

void GfMenuObjBladeSwitch::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 8:
    if (event.unknown0c == 9 && GfGameScene::get()->isEnableFieldBladeChange()) {
      GfGameScene::get()->requestFieldBladeChange();
    }
    break;
  case 0xc:
    if (!unknown20->unknown25) {
      acc.setDisp(false);
    }
    break;
  case GfMenuTypes::unknown003_33:
    if (!unknown20->unknown25) {
      {
        ui::UIObjectAcc base(acc.unknown10, "IMG_base");
        base.startAnimation("fade_in", false);
        GfMenuObject::hookAnimationEvent(0, base.unknown10);
      }
      {
        ui::UIObjectAcc input(acc.unknown10, "LAY_input");
        GfMenuObjUtil::CtrlParam param;
        param.unknown004("fade_in_l");
        param.unknown11 = true;
        GfMenuObjUtil::startCtrl(input.unknown10, param, nullptr);
      }
      unknown20->unknown25 = true;
      GfMenuObject::enableInput(acc.unknown10);
      acc.setDisp(true);
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown20->unknown25) {
      {
        ui::UIObjectAcc base(acc.unknown10, "IMG_base");
        base.startAnimation("fade_out", false);
        GfMenuObject::hookAnimationEvent(acc.unknown10, base.unknown10);
      }
      {
        ui::UIObjectAcc input(acc.unknown10, "LAY_input");
        GfMenuObjUtil::CtrlParam param;
        param.unknown004("fade_out_l");
        param.unknown11 = true;
        param.unknown14 = 10;
        GfMenuObjUtil::startCtrl(input.unknown10, param, nullptr);
      }
      unknown20->unknown25 = false;
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  default:
    if (event.unknown00 == 0x100) {
      unknown20->unknown26 = event.unknown08 == 1;
      if (!unknown20->unknown26) {
        if (unknown20->unknown25) {
          unknown155(unknown001, GfMenuTypes::unknown003_34);
        }
        unknown20->unknown24 = false;
      }
      break;
    }
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
