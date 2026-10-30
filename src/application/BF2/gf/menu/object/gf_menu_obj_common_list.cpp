#include "gf/menu/object/gf_menu_obj_common_list.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x24;

GfMenuObjCommonList::GfMenuObjCommonList(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonList::~GfMenuObjCommonList() { ; }

void GfMenuObjCommonList::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonList::update() { GfMenuObject::update(); }

void GfMenuObjCommonList::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
