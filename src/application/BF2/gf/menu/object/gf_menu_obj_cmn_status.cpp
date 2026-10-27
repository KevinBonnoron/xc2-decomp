#include "gf/menu/object/gf_menu_obj_cmn_status.h"

namespace gf {

bool GfMenuObjCmnStatus::s_DispFlag[2];

bool GfMenuObjCmnStatus::isOpenDrStatus() { return s_DispFlag[0]; }

bool GfMenuObjCmnStatus::isOpenBlStatus() { return s_DispFlag[1]; }

void GfMenuObjCmnStatus::update() { GfMenuObject::update(); }

} // namespace gf
