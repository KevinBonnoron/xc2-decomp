#include "gf/menu/object/gf_menu_obj_battle_telop.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: telop names by message; original name unknown.
static const char *const unknown005[] = {nullptr, "TXT_unite_combo_finish"};

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4e;

// Inferred helper: starts the preset 1 control of a UI object on a control id, with a direction and a control type; original name unknown.
static int unknown006(u32 handle, int ctrl, u32 direction, u32 type) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown00 = 1;
  param.unknown04 = direction;
  param.unknown0d = true;
  param.unknown08 = ctrl;
  param.unknown10 = type;
  return GfMenuObjUtil::startPresetCtrl(handle, param);
}

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x21;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown007 = 0x100;

GfMenuObjBattleTelop::GfMenuObjBattleTelop(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(this), unknown2b8(false) {
  for (int i = 0; i < 3; i++) {
    unknown2c0[i] = unknown160();
  }
}

GfMenuObjBattleTelop::~GfMenuObjBattleTelop() {
  for (int i = 0; i < 3; i++) {
    unknown2c0[i] = nullptr;
  }
}

void GfMenuObjBattleTelop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 133 as in the original file: it is the line argument of operator new.
#line 133
  MainListener *telop = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  telop->addRef();
  ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_telop"), telop);
  if (telop != nullptr) {
    telop->release();
  }
// __LINE__ must be 136 as in the original file: it is the line argument of operator new.
#line 136
  UniteComboListener *combo = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) UniteComboListener(this);
  combo->addRef();
  ui::UIEventManager::get()->registObjectListener(main.searchChild("LAY_fusion_combo"), combo);
  if (combo != nullptr) {
    combo->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  {
    ui::UIObjectAcc bonus(main.unknown10, "LAY_fusion_bonus");
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < 3; i++) {
      name.format("TXT_fusion_bonus_param@%02d", i + 1);
      GfMenuReferenceAdapter::create(bonus.searchChild(name.c_str()), unknown2c0[i], false);
    }
  }
  GfMenuObject::initialize();
}

void GfMenuObjBattleTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBattleTelop::update() { GfMenuObject::update(); }

void GfMenuObjBattleTelop::open(const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = unknown003;
    event.unknown08_u16 = param.unknown00;
    sendEvent(acc.searchChild("LAY_telop"), event, 0.0f);
  }
}

void GfMenuObjBattleTelop::close() { unknown147(unknown001, "LAY_telop", GfMenuTypes::unknown003_34); }

void GfMenuObjBattleTelop::openUniteCombo(const OpenUniteParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    // __LINE__ must be 97 as in the original file: it is the line argument of operator new.
#line 97
    OpenUniteParam *copy = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OpenUniteParam();
    if (copy != nullptr) {
      *copy = param;
      ui::EventData event;
      event.unknown00 = unknown007;
      event.unknown08_u64 = reinterpret_cast<u64>(copy);
      sendEvent(acc.searchChild("LAY_fusion_combo"), event, 0.0f);
    }
  }
}

void GfMenuObjBattleTelop::closeUniteCombo() { unknown147(unknown001, "LAY_fusion_combo", unknown002); }

void GfMenuObjBattleTelop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = unknown004();
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::registTimer(acc.unknown10, 1, 2.0f, false);
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
    }
    break;
  case 0xb:
    if (event.unknown08 == 1) {
      close();
    }
    break;
  case 0x21: {
    u16 message = event.unknown08_u16;
    if (message == 0) {
      break;
    }
    unknown10.unknown00 = 1;
    if (unknown20->unknown24 != 0) {
      ui::UIObjectAcc(unknown20->unknown24).setDisp(false);
    }
    unknown20->unknown24 = acc.searchChild(unknown005[message]);
    {
      ui::UIObjectAcc telop(unknown20->unknown24);
      if (!telop.isValid()) {
        break;
      }
      telop.setDisp(true);
    }
    if (unknown10.unknown04 == 0) {
      acc.setDisp(true);
      int ctrl = unknown006(acc.unknown10, unknown0c, 0, 1);
      if (ctrl != -1) {
        GfMenuObject::releaseTimer(acc.unknown10);
        unknown0c = ctrl;
      }
      unknown10.unknown04 = 1;
    }
    break;
  }
  case 0x22:
    unknown10.unknown00 = 0;
    if (unknown10.unknown04 != 0) {
      unknown006(acc.unknown10, unknown0c, 1, 2);
      unknown10.unknown04 = 0;
    }
    GfMenuObject::releaseTimer(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
