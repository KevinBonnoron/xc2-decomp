#include "gf/menu/object/gf_menu_obj_drop_item.h"

namespace gf {

GfMenuObjDropItem::GfMenuObjDropItem(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDropItem::~GfMenuObjDropItem() { GfMenuManyObjects::destroy<DropItemInfo>(GfMenuManyObjects::unknown001_3); }

void GfMenuObjDropItem::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDropItem::update() { GfMenuObject::update(); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDropItem::DropItemInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDropItem::DropItemInfo>::push_back(const gf::GfMenuObjDropItem::DropItemInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDropItem::DropItemInfo>::expand(size_t, size_t);
