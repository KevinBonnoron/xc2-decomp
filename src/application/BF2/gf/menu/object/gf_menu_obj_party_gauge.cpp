#include "gf/menu/object/gf_menu_obj_party_gauge.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_battle_adapter.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x55;

constexpr u32 BATTLE_STATE_UNKNOWN_3 = 3;

GfMenuObjPartyGauge::GfMenuObjPartyGauge(u32 handle) : GfMenuObject(handle), unknown24(-1) {}

GfMenuObjPartyGauge::~GfMenuObjPartyGauge() { ; }

void GfMenuObjPartyGauge::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(unknown001, main.unknown10);
    {
      ui::UIObjectAcc gauge(main.unknown10, "LAY_gauge");
// __LINE__ must be 64 as in the original file: it is the line argument of operator new.
#line 64
      GaugeListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GaugeListener(this);
      listener->addRef();
      ui::UIEventManager::get()->registObjectListener(gauge.unknown10, listener);
      if (listener != nullptr) {
        listener->release();
      }
      for (u32 slot = 1; slot < 4; slot++) {
        u32 index = slot - 1;
        mm::mtl::FixStr<32> name;
        name.format("IMG_gauge@%02d", slot);
        ui::UIObjectAcc image(gauge.unknown10, name.c_str());
        if (image.isValid()) {
          GfMenuBattleAdapter *adapter = GfMenuBattleAdapter::create(gauge.searchChild(name.c_str()), 0xc);
          if (adapter != nullptr) {
            image.setExtType(1);
            adapter->unknown30 = index;
          }
          addNumberEventCondition(gauge.unknown10, name.c_str(), 0, index, 1.0f);
        }
      }
    }
    GfMenuObject::initialize();
  }
}

void GfMenuObjPartyGauge::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyGauge::update() {
  ui::UIObjectAcc(unknown18).setAlpha(1.0f);
  GfMenuObject::update();
}

void GfMenuObjPartyGauge::close() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::UIObjectAcc child(acc.unknown10, "LAY_gauge");
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

void GfMenuObjPartyGauge::open() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    if (!GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_3)) {
      acc.setDisp(true);
    }
    ui::UIObjectAcc child(acc.unknown10, "LAY_gauge");
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

void GfMenuObjPartyGauge::disp(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    acc.setDisp(isDisp);
  }
}

void GfMenuObjPartyGauge::GaugeListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = -1;
    break;
  case 0xd:
    if (event.unknown0c == 0) {
      int slot = event.unknown10;
      int type = event.unknown08;
      mm::mtl::FixStr<32> name;
      name.format("IMG_gauge@%02d", slot + 1);
      ui::UIObjectAcc gauge(acc.unknown10, name.c_str());
      name.format("IMG_gauge_icon@%02d", slot + 1);
      ui::UIObjectAcc icon(acc.unknown10, name.c_str());
      if (type == 1) {
        icon.setDisp(true);
        if (slot == 2 && unknown20->unknown24 == -1) {
          GfMenuObjUtil::CtrlParam param;
          param.unknown08 = 0x40000000;
          param.unknown00 = 1.0f;
          param.unknown10 = true;
          param.unknown0c = 4;
          param.unknown14 = 8;
          param.unknown38 = 0.5f;
          unknown20->unknown24 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_gauge_bar"), param, nullptr);
          GfMenuObjUtil::playSE(0x26);
        } else {
          GfMenuObjUtil::playSE(0x25);
        }
      } else {
        icon.setDisp(false);
        if (unknown20->unknown24 != -1) {
          GfMenuObjUtil::stopCtrl(unknown20->unknown24);
          unknown20->unknown24 = -1;
        }
      }
    }
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown10 == 0) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      if (event.unknown08 == 0) {
        param.unknown00 = 1;
      }
      param.unknown04 = 0;
      param.unknown0d = true;
      param.unknown08 = unknown0c;
      unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      unknown10 = 1;
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown10 == 1) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown10 = 0;
      if (event.unknown08 == 0) {
        param.unknown00 = 1;
      }
      param.unknown04 = 1;
      param.unknown0d = true;
      param.unknown08 = unknown0c;
      unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      unknown10 = 0;
    }
    break;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf
