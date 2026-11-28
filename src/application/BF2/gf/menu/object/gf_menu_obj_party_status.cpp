#include "gf/menu/object/gf_menu_obj_party_status.h"

#include <string.h>

#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_party.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
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

GfMenuObjPartyStatus::GfMenuObjPartyStatus(u32 handle) : GfMenuObject(handle), unknown3c(false) { memset(unknown30, 0xff, sizeof(unknown30)); }

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

// The game's first parameter (x1) is never read. `slot` and `params` are the game's two loads of the event (ldr w21 / ldr x20, 0x71004aebd0), made before the
// isExitDriver call (0x71004aebe0): without `slot` the shifts reload event.unknown10 after the call (32 instructions), without `params` the parameters are
// loaded after the call and `flags` is stored twice.
void GfMenuObjPartyStatus::reciveHpEvent(u32 handle, const ui::EventData &event, int &flags) {
  u32 slot = event.unknown10;
  u64 params = event.unknown08_u64;
  if (GfMenuObjUtil::isExitDriver(slot - 1)) {
    flags |= 1 << slot;
  } else {
    flags &= ~(1 << slot);
  }
  if ((params & 0xffffefffffffffff) == 1) {
    flags &= ~(1 << slot);
  }
}

// Forms measured against the game (0x71004aec30, 595 instructions; each compared with check on the unit, differing lines in brackets):
// - The `switch` over event.unknown00 is the game's two jump tables; the u32 tables read by case 8 (0xa, 0x22, 0x42) and 0x102 (0x8002, 0x2002, 0x1002) are the lookup tables
//   clang makes of the two inner `switch`.
// - Case 8: `flags` is declared before `slot` and `param.unknown08` is stored first (`slot` first: 5 lines, `unknown20` stored first: 6 lines).
// - Case 1: `owner` is the game's single load of the owner (without it 597 instructions); the two `createDockPlugin` calls are written in both arms (one call with `i == 2 ? 0 : 1`
//   has 589 instructions); the FitOption lives in its own scope (4 lines without it: its slot is x29 - 128 in the game, sp + 32 without the scope). The loop head
//   (`FixStr<32> name; for (u32 i = 0; i < 3; i++) { name.format(..., i + 1);`) is shared with other menu objects; the quality gate lists it (5 functions, 3 statements). A loop head
//   with different bodies cannot be a helper; the closest form, a static helper holding the whole loop body (taking `acc`, `name` and `i`), gives 595 instructions as the game
//   and 56 differing lines (the stack slots of the accessors and the name, first difference 0x71004aec5c), so the loop stays written out (ruling 8).
// - Case 0x101: `combo`, `isEnable`, `effect` and `button` are the game's loads of event+8 (x19) and event+0x10 (w22) made before the format call (0x71004aec8c,
//   0x71004aec9c); without the four the function has 590 instructions (without `button`, `isEnable` or `effect` alone 594, without `combo` alone 3 differing lines). Case 0x103
//   passes the fields in the call, its locals change nothing.
// - Case 0x102: `param` is the load of event+8 made before the `index` load (inline: 594 instructions), `isCombo` is the compare made before the switch (inline: 10 lines) and
//   `layer` is the `searchChild` call made before the CtrlParam (inline: 593 instructions).
// - Case order: 0x102 is written before 0x108; with 0x108 first the function has 596 instructions.
// - Case 0x107: `startCtrl` of the fade control is written in both arms of the `if` (BranchFolding tail merges the two calls, as in GfMenuObjPouch2::updateItemList, docs/lessons.md).
//   The game keeps the effect block (0x71004af388) apart from the fade block: neither the constant 1 nor the scaled index (`lsl x24, x21, #2`) is shared with it, which the single
//   call after the `if` shares (594 instructions, 38 differing lines). The stores of `param` are in the one order that matches (the other 23 orders give 6 to 45 lines),
//   and `unknown10 = unknown10 | (1 << index)` loads the bit set before the shift where `|=` swaps the registers of the two (3 lines).
void GfMenuObjPartyStatus::ComboReqListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = 0;
    GfMenuObjPartyStatus *owner = m_menuObjPartyStatus;
    owner->unknown40[0] = -1;
    owner->unknown40[1] = -1;
    owner->unknown40[2] = -1;
    GfMenuObject::disableInput(acc.unknown10);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < 3; i++) {
      name.format("TXT_combo_req2_name@%02d", i + 1);
      ui::UIObjectAcc text(acc.unknown10, name.c_str());
      name.format("IMG_combo_req2_name_bg@%02d", i + 1);
      if (i == 2) {
        GfMenuObjUtil::createDockPlugin(text.unknown10, acc.searchChild(name.c_str()), 0, mm::Pnt<s16>(0, 0), 0);
      } else {
        GfMenuObjUtil::createDockPlugin(text.unknown10, acc.searchChild(name.c_str()), 1, mm::Pnt<s16>(0, 0), 0);
      }
      {
        GfMenuObjUtil::FitOption option;
        option.unknown02 = true;
        name.format("IMG_combo_req2_name_base@%02d", i + 1);
        GfMenuObjUtil::createFitPlugin(acc.searchChild(name.c_str()), text.unknown10, 0, 0, option);
      }
      name.format("IMG_combo_req2_face@%02d", i + 1);
      ui::UIObjectAcc face(acc.unknown10, name.c_str());
      GfMenuCharDataAdapter::createFromPartyDriver(face.unknown10, 0x28, i, false);
    }
    break;
  }
  case 8: {
    u32 flags = 2;
    int slot = -1;
    switch (event.unknown0c_u16) {
    case 9:
      slot = 0;
      flags = 0xa;
      break;
    case 10:
      slot = 1;
      flags = 0x22;
      break;
    case 11:
      slot = 2;
      flags = 0x42;
      break;
    }
    if (unknown10 & (1 << slot)) {
      mm::mtl::FixStr<32> name;
      GfMenuObjUtil::CtrlParam param;
      name.format("LAY_combo_req2@%02d", slot + 1);
      param.unknown08 = flags;
      param.unknown20 = 0x20;
      param.unknown00 = 0.5f;
      param.unknown14 = 10;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, name.c_str());
      unknown10 &= ~(1 << slot);
      GfMenuObject::addResultCallContext(acc.unknown10, 0, slot);
    }
  }
  // fall through
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 0x21: {
    mm::mtl::FixStr<32> name;
    if (!acc.isDisp()) {
      for (int i = 1; i <= 3; i++) {
        name.format("LAY_combo_req2@%02d", i);
        acc.setDispChild(false, name.c_str());
      }
      acc.setDisp(true);
      unknown10 = 0;
    }
    break;
  }
  case 0x22:
    acc.setDisp(false);
    break;
  case 0x101: {
    u16 index = event.unknown08_u16;
    if (index > 2) {
      break;
    }
    u16 combo = event.unknown0a;
    bool isEnable = event.unknown0c_u16 == 1;
    u16 effect = event.unknown0e;
    u32 button = event.unknown10;
    mm::mtl::FixStr<32> name;
    name.format("LAY_combo_req2@%02d", index + 1);
    ui::UIObjectAcc layer(acc.unknown10, name.c_str());
    if (layer.isValid()) {
      layer.setAlpha(1.0f);
    }
    m_menuObjPartyStatus->setupComboReq(acc, index, combo, isEnable, effect, button);
    ui::EventData data = event;
    data.unknown00 = 0x107;
    GfMenuObject::sendEvent(acc.unknown10, data, 0.033333335f);
    break;
  }
  case 0x103: {
    m_menuObjPartyStatus->setupComboReq(acc, event.unknown08_u16, event.unknown0a, event.unknown0c_u16 == 1, event.unknown0e, event.unknown10);
    ui::EventData data = event;
    data.unknown00 = 0x108;
    GfMenuObject::sendEvent(acc.unknown10, data, 0.033333335f);
    break;
  }
  case 0x107: {
    u16 index = event.unknown08_u16;
    acc.setDisp(true);
    if (index > 2) {
      break;
    }
    u32 number = index + 1;
    mm::mtl::FixStr<32> name;
    name.format("LAY_combo_req2@%02d", number);
    ui::UIObjectAcc layer(acc.unknown10, name.c_str());
    {
      GfMenuObjUtil::CtrlParam param;
      u32 flags;
      switch (index) {
      case 0: {
        name.format("LAY_combo_req2_name@%02d", number);
        ui::UIObjectAcc nameLayer(acc.unknown10, name.c_str());
        mm::Pnt<s16> pos;
        nameLayer.getPosCenter(pos);
        pos.x = 0x280;
        nameLayer.setPosCenter(pos);
        flags = 0x801;
        break;
      }
      case 2:
        flags = 0x101;
        break;
      case 1:
        flags = 0x201;
        break;
      default:
        flags = 1;
        break;
      }
      param.unknown08 = flags;
      param.unknown0c = 1;
      param.unknown00 = 0.2f;
      param.unknown14 |= 4;
      if (m_menuObjPartyStatus->unknown40[index] != -1) {
        param.unknown11 = true;
        param.unknown18 = m_menuObjPartyStatus->unknown40[index];
        layer.setDisp(true);
        m_menuObjPartyStatus->unknown40[index] = GfMenuObjUtil::startCtrl(layer.unknown10, param, nullptr);
      } else {
        m_menuObjPartyStatus->unknown40[index] = GfMenuObjUtil::startCtrl(layer.unknown10, param, nullptr);
      }
    }
    name.format("IMG_combo_req2_eff@%02d", number);
    {
      ui::UIObjectAcc eff(acc.unknown10, name.c_str());
      eff.setRot(0.0f);
      GfMenuObjUtil::CtrlParam effect;
      effect.unknown08 = 0x1000000;
      effect.unknown34 = -6.2831855f;
      effect.unknown00 = 1.0f;
      effect.unknown10 = true;
      effect.unknown14 = 4;
      m_menuObjPartyStatus->unknown30[index] = GfMenuObjUtil::startCtrl(acc.unknown10, effect, name.c_str());
    }
    unknown10 = unknown10 | (1 << index);
    GfMenuObject::enableInput(acc.unknown10);
    GfMenuObjUtil::playSE(0x29);
    break;
  }
  case 0x102: {
    u32 param = event.unknown08;
    u16 index = event.unknown08_u16;
    bool isCombo = (param >> 16) == 1;
    u32 flags;
    switch (index) {
    case 0:
      flags = 0x8002;
      break;
    case 1:
      flags = 0x2002;
      break;
    case 2:
      flags = 0x1002;
      break;
    default:
      return;
    }
    if (!(unknown10 & (1 << index))) {
      break;
    }
    u32 number = index + 1;
    mm::mtl::FixStr<32> name;
    name.format("LAY_combo_req2@%02d", number);
    u32 layer = acc.searchChild(name.c_str());
    if (m_menuObjPartyStatus->unknown40[index] != -1) {
      GfMenuObjUtil::CtrlParam ctrl;
      if (isCombo) {
        ctrl.unknown08 = 0x04080002;
        ctrl.unknown2c = 2.0f;
        ctrl.unknown20 = 0x40;
        ctrl.unknown38 = 1.0f;
        ctrl.unknown14 = 10;
        ctrl.unknown0c = 1;
        name.format("IMG_combo_req2_eff@%02d", number);
        ui::UIObjectAcc(acc.unknown10, name.c_str()).getAddColor(ctrl.unknown40_col3);
        ctrl.unknown00 = 1.0f;
        GfMenuObjUtil::playSE(0x2a);
      } else {
        ctrl.unknown08 = flags;
        ctrl.unknown0c = 1;
        ctrl.unknown00 = 0.4f;
        GfMenuObjUtil::playSE(0x2b);
      }
      ctrl.unknown14 |= 4;
      ctrl.unknown18 = m_menuObjPartyStatus->unknown40[index];
      m_menuObjPartyStatus->unknown40[index] = GfMenuObjUtil::startCtrl(layer, ctrl, nullptr);
      if (m_menuObjPartyStatus->unknown30[index] != -1) {
        name.format("IMG_combo_req2_eff@%02d", number);
        acc.setDispChild(false, name.c_str());
        GfMenuObjUtil::stopCtrl(m_menuObjPartyStatus->unknown30[index]);
        m_menuObjPartyStatus->unknown30[index] = -1;
      }
    }
    name.format("LAY_combo_icon@%02d", number);
    ui::UIObjectAcc icon(acc.unknown10, name.c_str());
    icon.setAlpha(0.0f);
    unknown10 &= ~(1 << index);
    if (unknown10 == 0) {
      GfMenuObject::disableInput(acc.unknown10);
    }
    break;
  }
  case 0x108: {
    if (event.unknown08_u16 != 0) {
      break;
    }
    mm::mtl::FixStr<32> name;
    name.format("LAY_combo_req2_name@%02d", 1);
    ui::UIObjectAcc layer(acc.unknown10, name.c_str());
    mm::Pnt<s16> pos;
    layer.getPosCenter(pos);
    pos.x = 0x280;
    layer.setPosCenter(pos);
    break;
  }
  }
}

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
