#include "gf/menu/object/gf_menu_obj_quest_log.h"
#include "gf/menu/gf_menu_flag.h"

namespace gf {

void GfMenuObjQuestLog::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestLog::lockLogOpen() { GfMenuFlag::set1(0x20, 1); }

void GfMenuObjQuestLog::unlockLogOpen() { GfMenuFlag::set1(0x20, 0); }

} // namespace gf
