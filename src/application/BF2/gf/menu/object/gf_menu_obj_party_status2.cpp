#include "gf/menu/object/gf_menu_obj_party_status2.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5d;

void GfMenuObjPartyStatus2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus2::update() { GfMenuObject::update(); }

void GfMenuObjPartyStatus2::sendEvent(u32 handle, u32 type, u32 param) {
  if (handle != 0) {
    unknown140(handle, type, param, 0.0f);
  }
}

void GfMenuObjPartyStatus2::close() { unknown142(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjPartyStatus2::open() { unknown142(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
