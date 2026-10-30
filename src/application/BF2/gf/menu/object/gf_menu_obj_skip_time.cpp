#include "gf/menu/object/gf_menu_obj_skip_time.h"

#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjSkipTime::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSkipTime::update() { GfMenuObject::update(); }

void GfMenuObjSkipTime::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjSkipTime::rotHand(ui::UIObjectAcc &acc, u32 value) { acc.setRot(static_cast<f32>(value) * -0.2617994f); }

} // namespace gf
