#include "gf/menu/object/gf_menu_obj_common_info.h"

namespace gf {

GfMenuObjCommonInfo::GfMenuObjCommonInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonInfo::~GfMenuObjCommonInfo() { GfMenuManyObjects::destroy<CommonInfo>(GfMenuManyObjects::unknown001_6); }

void GfMenuObjCommonInfo::finalize() {}

void GfMenuObjCommonInfo::update() {}

void GfMenuObjCommonInfo::close(u32) {}

void GfMenuObjCommonInfo::closeAll() {}

void GfMenuObjCommonInfo::pausePickup() {}

void GfMenuObjCommonInfo::continuePickup() {}

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjCommonInfo::CommonInfo>(u32, u32);
