#include "gf/menu/object/gf_menu_obj_quest_result.h"

namespace gf {

GfMenuObjQuestResult::GfMenuObjQuestResult(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestResult::~GfMenuObjQuestResult() { ; }

void GfMenuObjQuestResult::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestResult::update() { GfMenuObject::update(); }

} // namespace gf
