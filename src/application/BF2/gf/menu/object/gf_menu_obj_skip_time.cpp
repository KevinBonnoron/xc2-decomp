#include "gf/menu/object/gf_menu_obj_skip_time.h"

#include "gf/field/gf_field_time.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjSkipTime::GfMenuObjSkipTime(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(), unknown34() {}

GfMenuObjSkipTime::~GfMenuObjSkipTime() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjSkipTime::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSkipTime::update() { GfMenuObject::update(); }

void GfMenuObjSkipTime::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjSkipTime::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjSkipTime::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjSkipTime::rotHand(ui::UIObjectAcc &acc, u32 value) { acc.setRot(static_cast<f32>(value) * -0.2617994f); }

void GfMenuObjSkipTime::setTime(ui::UIObjectTimePlugin *plugin, GameTime &time) {
  plugin->setHour(time.unknown01_4);
  plugin->setMin(time.unknown00_6);
  plugin->setSec(time.unknown00_0);
}

} // namespace gf
