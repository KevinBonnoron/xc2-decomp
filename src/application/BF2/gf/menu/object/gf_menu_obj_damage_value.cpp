#include "gf/menu/object/gf_menu_obj_damage_value.h"

namespace gf {

GfMenuObjDamageValue::GfMenuObjDamageValue(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDamageValue::~GfMenuObjDamageValue() { GfMenuManyObjects::destroy<DamageInfo>(GfMenuManyObjects::unknown001_0); }

void GfMenuObjDamageValue::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDamageValue::update() { GfMenuObject::update(); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDamageValue::DamageInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDamageValue::DamageInfo>::push_back(const gf::GfMenuObjDamageValue::DamageInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDamageValue::DamageInfo>::expand(size_t, size_t);
