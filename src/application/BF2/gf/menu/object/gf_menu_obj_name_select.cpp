#include "gf/menu/object/gf_menu_obj_name_select.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace gf {

GfMenuObjNameSelect::GfMenuObjNameSelect(u32 handle) : GfMenuObject(handle), unknown28(nullptr) { unknown28 = GfMenuCallContext::create(); }

GfMenuObjNameSelect::~GfMenuObjNameSelect() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjNameSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjNameSelect::update() { GfMenuObject::update(); }

} // namespace gf
