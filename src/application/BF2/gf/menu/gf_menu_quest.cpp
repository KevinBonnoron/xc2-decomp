#include "gf/menu/gf_menu_quest.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuQuest::GfMenuQuest(const GfSetupParam &param) : unknown0c(0), unknown10(-1) { initialize(param); }

void GfMenuQuest::initialize(const GfSetupParam &param) { unknown08 = true; }

GfMenuQuest::~GfMenuQuest() {}

void GfMenuQuest::build(const GfSetupParam &param) {
// __LINE__ must be 47 as in the original file: its value changes the instruction order.
#line 47
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuQuest(param);
}

void GfMenuQuest::destroy() {
  GfMenuQuest *menu = get();
  menu->finalize();
  delete menu;
}

void GfMenuQuest::finalize() { unknown08 = false; }

bool GfMenuQuest::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfMenuQuest::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuQuest::updateQuestTaskLog(const fw::UpdateInfo &info) {}

void GfMenuQuest::openMenu(u32 questId, u32 page, bool isTaskLog) {
  GfMenuQuest *quest = get();
  if (quest != nullptr) {
    quest->unknown10 = questId;
    quest->unknown0c = page;
    quest->unknown14 = isTaskLog;
  }
}

} // namespace gf
