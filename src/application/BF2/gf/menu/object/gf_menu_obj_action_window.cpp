#include "gf/menu/object/gf_menu_obj_action_window.h"

namespace gf {

GfMenuObjActionWindow::GfMenuObjActionWindow(u32 handle) : GfMenuObject(handle) {}

GfMenuObjActionWindow::~GfMenuObjActionWindow() { ; }

void GfMenuObjActionWindow::finalize() { GfMenuObject::finalize(); }

void GfMenuObjActionWindow::update() { GfMenuObject::update(); }

} // namespace gf
