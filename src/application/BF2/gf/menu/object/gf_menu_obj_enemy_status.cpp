#include "gf/menu/object/gf_menu_obj_enemy_status.h"

#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x10;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x100;
// Inferred role: attached display call id; original name unknown.
constexpr u32 unknown004 = 0x14;

GfMenuObjEnemyStatus::GfMenuObjEnemyStatus(u32 handle) : GfMenuObject(handle), unknown28(-1), unknown100(-1) {}

GfMenuObjEnemyStatus::~GfMenuObjEnemyStatus() {}

void GfMenuObjEnemyStatus::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEnemyStatus::close() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

void GfMenuObjEnemyStatus::open(const OpenParam &) { GF_MENU_REQUEST_EVENT(unknown001, unknown003); }

void GfMenuObjEnemyStatus::disp(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown004));
  if (acc.isValid() && !acc.isTerm()) {
    acc.setDisp(isDisp);
  }
}

} // namespace gf
