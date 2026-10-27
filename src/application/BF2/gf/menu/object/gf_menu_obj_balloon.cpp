#include "gf/menu/object/gf_menu_obj_balloon.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjBalloon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBalloon::resetFeeling(ui::UIObjectAcc &acc) { acc.setAddColor("black"); }

} // namespace gf
