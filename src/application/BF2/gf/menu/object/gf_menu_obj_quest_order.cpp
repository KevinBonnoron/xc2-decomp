#include "gf/menu/object/gf_menu_obj_quest_order.h"

namespace gf {

GfMenuObjQuestOrder::GfMenuObjQuestOrder(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestOrder::~GfMenuObjQuestOrder() { ; }

void GfMenuObjQuestOrder::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestOrder::update() { GfMenuObject::update(); }

} // namespace gf
