#include "gf/menu/object/gf_menu_obj_quest_order.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1e;

GfMenuObjQuestOrder::GfMenuObjQuestOrder(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestOrder::~GfMenuObjQuestOrder() { ; }

void GfMenuObjQuestOrder::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestOrder::update() { GfMenuObject::update(); }

void GfMenuObjQuestOrder::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
