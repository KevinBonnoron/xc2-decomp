#include "gf/menu/object/gf_menu_obj_mercenary_root.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4d;

GfMenuObjMercenaryRoot::GfMenuObjMercenaryRoot(u32 handle) : GfMenuObject(handle), unknown24(-1), unknown28(this), unknown188(0) {}

GfMenuObjMercenaryRoot::~GfMenuObjMercenaryRoot() {}

void GfMenuObjMercenaryRoot::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryRoot::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

void GfMenuObjMercenaryRoot::closeBg() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaryRoot>(const mm::mtl::Delegate<bool()> *);
