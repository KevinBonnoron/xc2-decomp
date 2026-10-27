#include "gf/menu/object/gf_menu_obj_quest_log.h"
#include "gf/menu/gf_menu_flag.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjQuestLog::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestLog::lockLogOpen() { GfMenuFlag::set1(0x20, 1); }

void GfMenuObjQuestLog::unlockLogOpen() { GfMenuFlag::set1(0x20, 0); }

bool GfMenuObjQuestLog::seqLogNextEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  enableInput(acc.unknown10);
  return true;
}

bool GfMenuObjQuestLog::seqLogStart() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  enableInput(acc.unknown10);
  return true;
}

} // namespace gf
