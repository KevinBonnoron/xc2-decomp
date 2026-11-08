#include "gf/menu/object/gf_menu_obj_party_status.h"

#include <string.h>

#include "gf/game/gf_game_party.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_party_status2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

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
      if (partyId == GfMenuObjUtil::getLeaderPartyID() || GfGameParty::getHandleDriver(partyId) != INVALID_HANDLE) {
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

} // namespace gf
