#include "gf/menu/object/gf_menu_obj_quest_result.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1f;

GfMenuObjQuestResult::GfMenuObjQuestResult(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestResult::~GfMenuObjQuestResult() { ; }

void GfMenuObjQuestResult::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestResult::update() { GfMenuObject::update(); }

void GfMenuObjQuestResult::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
