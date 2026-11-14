#include "gf/menu/object/gf_menu_obj_party_status.h"

#include <string.h>

#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_party.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_gfobj_adapter.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_party_status2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: party status call id; original name unknown.
constexpr u32 unknown001 = 0x3d;

// Inferred role: combo request call id; original name unknown.
constexpr u32 unknown002 = 0x3e;

// Inferred helper: requests an event with a flag parameter on the object attached to a call unless it is terminating; original name unknown.
static inline void unknown003(u32 call, u16 type, bool param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(call));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = type;
    event.unknown08 = param;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

GfMenuObjPartyStatus::GfMenuObjPartyStatus(u32 handle) : GfMenuObject(handle), unknown38(-1), unknown3c(false) { memset(unknown30, 0xff, sizeof(unknown30)); }

GfMenuObjPartyStatus::~GfMenuObjPartyStatus() { ; }

void GfMenuObjPartyStatus::initialize() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  if (acc.isValid()) {
// __LINE__ must be 103 as in the original file: it is the line argument of operator new.
#line 103
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(acc.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
    attachExternalCall(unknown001, acc.unknown10);
    {
      ui::UIObjectAcc comboReq(unknown18, "LAY_combo_req2");
      if (comboReq.isValid()) {
        attachExternalCall(unknown002, comboReq.unknown10);
// __LINE__ must be 117 as in the original file: it is the line argument of operator new.
#line 117
        ComboReqListener *comboReqListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ComboReqListener(this);
        comboReqListener->addRef();
        ui::UIEventManager::get()->registObjectListener(comboReq.unknown10, comboReqListener);
        if (comboReqListener != nullptr) {
          comboReqListener->release();
        }
      }
      GfMenuObjUtil::createDockPlugin(comboReq.searchChild("IMG_combo_req2_name_top@01"), comboReq.searchChild("IMG_combo_req2_name_base@01"), 1, mm::Pnt<s16>(0, 0), 0);
      GfMenuObjUtil::createDockPlugin(comboReq.searchChild("IMG_combo_req2_name_top@02"), comboReq.searchChild("IMG_combo_req2_name_base@02"), 1, mm::Pnt<s16>(0, 0), 0);
      GfMenuObjUtil::createDockPlugin(comboReq.searchChild("IMG_combo_req2_name_top@03"), comboReq.searchChild("IMG_combo_req2_name_base@03"), 0, mm::Pnt<s16>(0, 0), 0);
    }
    mm::mtl::FixStr<32> name;
    for (int i = 0; i < 3; i++) {
      name.format("IMG_mem%d_hpgauge", i + 1);
      GfMenuGfObjAdapter::createFromPartyDriver(acc.searchChild(name.c_str()), 0, i, true);
      ui::UIObjectAcc(acc.searchChild(name.c_str())).setExtType(1);
      addNumberEventCondition(acc.unknown10, name.c_str(), 0x1000, i + 1, 1.0f);
      addNumberEventCondition(acc.unknown10, name.c_str(), 0x1001, i + 1, 0.2f);
      addNumberEventCondition(acc.unknown10, name.c_str(), 0x1002, i + 1, 0.0f);
    }
    GfMenuObject::initialize();
  }
}

void GfMenuObjPartyStatus::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus::update() { GfMenuObject::update(); }

void GfMenuObjPartyStatus::attachComboRequest(GfMenuCallContext *context) { unknown152(context, unknown002); }

void GfMenuObjPartyStatus::open(bool isLock) { unknown003(unknown001, GfMenuTypes::unknown003_33, isLock); }

void GfMenuObjPartyStatus::close(bool isImmediate) { unknown003(unknown001, GfMenuTypes::unknown003_34, isImmediate); }

void GfMenuObjPartyStatus::lock(bool lock) { unknown003(unknown001, 0x110, lock); }

void GfMenuObjPartyStatus::memberChange(u16 member, u32 value) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = 0x109;
    event.unknown08 = member;
    event.unknown0c = value;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjPartyStatus::openComboRequest(u16 index, const RequestParam &param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = GfMenuTypes::unknown003_257;
    event.unknown08_u16 = index;
    event.unknown0a = param.unknown00;
    event.unknown0c_u16 = param.unknown08;
    event.unknown0e = param.unknown02;
    event.unknown10 = param.unknown04;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjPartyStatus::closeComboRequest(u16 index, bool isImmediate) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = GfMenuTypes::unknown003_258;
    event.unknown08_u16 = index;
    event.unknown0a = isImmediate;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjPartyStatus::resetComboRequest(u16 index, const RequestParam &param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = GfMenuTypes::unknown003_259;
    event.unknown08_u16 = index;
    event.unknown0a = param.unknown00;
    event.unknown0c_u16 = param.unknown08;
    event.unknown0e = param.unknown02;
    event.unknown10 = param.unknown04;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjPartyStatus::closePartyStatus(u32 handle, int member) {
  ui::UIObjectAcc acc(handle);
  {
    ui::UIObjectAcc comboReq(unknown18, "LAY_combo_req2");
    if (comboReq.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      ui::UIManager::get()->requestObjectEvent(comboReq.unknown10, event, 0.0f);
    }
  }
  GfMenuObjPartyStatus2::close();
}

int GfMenuObjPartyStatus::openPartyStatus(u32 handle, int member) {
  u32 leader = GfMenuObjUtil::getLeaderPartyID();
  ui::UIObjectAcc acc(handle);
  if (leader == -1) {
    member = -1;
  } else {
    u32 partyId = leader;
    for (int i = 0; i < 3; i++) {
      mm::mtl::FixStr<32> name;
      name.format("LAY_mem%d", i + 1);
      if (partyId == GfMenuObjUtil::getLeaderPartyID() || GfGameParty::getHandleDriver(partyId) != unknown020) {
        acc.setDispChild(true, name.c_str());
      } else {
        acc.setDispChild(false, name.c_str());
      }
      partyId = partyId + 1 > 2 ? 0 : partyId + 1;
    }
    {
      ui::UIObjectAcc comboReq(unknown18, "LAY_combo_req2");
      if (comboReq.isValid()) {
        ui::EventData event;
        event.unknown00 = GfMenuTypes::unknown003_33;
        ui::UIManager::get()->requestObjectEvent(comboReq.unknown10, event, 0.0f);
      }
    }
    GfMenuObjPartyStatus2::open();
  }
  return member;
}

// Inferred role: default button of each combo request slot; original name unknown.
static const u32 unknown004[] = {4, 0x40, 0x80};

void GfMenuObjPartyStatus::setupComboReq(const ui::UIObjectAcc &acc, u16 index, u16 combo, bool isEnable, u16 effect, u32 button) {
  mm::mtl::FixStr<32> name;
  mm::mtl::FixStr<32> color;
  u8 atr = GfMenuObjUtil::getElementComboAtr(combo);
  color.format("elemental%02d", atr);
  u32 number = index + 1;
  name.format("TXT_combo_req2_name@%02d", number);
  ui::UIObjectAcc text(acc.unknown10, name.c_str());
  if (text.isValid()) {
    text.setText(GfMenuObjUtil::getElementComboName(combo));
    mm::mtl::FixStr<32> pattern;
    pattern.format("element%02d", atr);
    text.setTextFacePattern(pattern.c_str());
  }
  name.format("IMG_combo_req2_name_bg@%02d", number);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setMulColor(color.c_str());
  name.format("IMG_combo_req2_name_base@%02d", number);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setMulColor(color.c_str());
  name.format("IMG_combo_req2_name_top@%02d", number);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setMulColor(color.c_str());
  name.format("IMG_combo_req2_btn_bg@%02d", number);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setMulColor(color.c_str());
  name.format("IMG_combo_req2_btn_disable@%02d", number);
  ui::UIObjectAcc disable(acc.unknown10, name.c_str());
  if (disable.isValid()) {
    disable.setDisp(false);
  }
  name.format("IMG_combo_req2_btn@%02d", number);
  ui::UIObjectAcc btn(acc.unknown10, name.c_str());
  if (btn.isValid()) {
    btn.setDisp(isEnable);
  }
  name.format("IMG_combo_req2_eff@%02d", number);
  ui::UIObjectAcc eff(acc.unknown10, name.c_str());
  if (effect != 0) {
    eff.setImageIndex(effect - 1);
    eff.setAlpha(1.0f);
  } else {
    eff.setAlpha(0.0f);
  }
  if (button == 0) {
    button = unknown004[index];
  }
  name.format("IMG_combo_req2_btn@%02d", number);
  int icon = GfMenuObjUtil::getBtnIconNumber(button);
  ui::UIObjectAcc(acc.unknown10, name.c_str()).setImageIndex(GfMenuBdat::getIconImageIndex(icon));
  if (index == 0) {
    bool isDisp = GfDataParty::getDriver(index) == 1 && GfDataDriver::getBlade(1, -1) == BLADE_HOMURI;
    ui::UIObjectAcc(acc.unknown10, "IMG_combo_req2_sp@01").setDisp(isDisp);
  }
}

} // namespace gf
