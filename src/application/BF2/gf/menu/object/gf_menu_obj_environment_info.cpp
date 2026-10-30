#include "gf/menu/object/gf_menu_obj_environment_info.h"

#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x2a;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x100;

GfMenuObjEnvironmentInfo::GfMenuObjEnvironmentInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEnvironmentInfo::~GfMenuObjEnvironmentInfo() { ; }

void GfMenuObjEnvironmentInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEnvironmentInfo::update() { GfMenuObject::update(); }

void GfMenuObjEnvironmentInfo::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjEnvironmentInfo::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjEnvironmentInfo::disable() {
  if (unknown143(unknown001, unknown002)) {
    GfMenuFlag::set1(0x1e, 1);
  }
}

void GfMenuObjEnvironmentInfo::enable() {
  if (unknown143(unknown001, unknown003)) {
    GfMenuFlag::set1(0x1e, 0);
  }
}

} // namespace gf
