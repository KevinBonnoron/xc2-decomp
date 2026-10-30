#include "gf/menu/object/gf_menu_obj_opening_telop.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x82;
// Inferred role: telop position; original name unknown.
constexpr u32 unknown002_0 = 0;
constexpr u32 unknown002_1 = 1;
constexpr u32 unknown002_2 = 2;

void GfMenuObjOpeningTelop::openCenter(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_0, telop); }

void GfMenuObjOpeningTelop::closeCenter() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjOpeningTelop::openLeft(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_1, telop); }

void GfMenuObjOpeningTelop::openRight(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_2, telop); }

void GfMenuObjOpeningTelop::finalize() { GfMenuObject::finalize(); }

} // namespace gf
