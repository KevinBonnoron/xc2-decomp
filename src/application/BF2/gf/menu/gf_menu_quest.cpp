#include "gf/menu/gf_menu_quest.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMenuQuest::GfMenuQuest(const GfSetupParam &param) : openPage(0), openQuestId(-1) { initialize(param); }

void GfMenuQuest::initialize(const GfSetupParam &param) { initialized = true; }

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

void GfMenuQuest::finalize() { initialized = false; }

bool GfMenuQuest::isInitialized() {
  if (get() != nullptr) {
    return get()->initialized;
  }
  return false;
}

void GfMenuQuest::postUpdate(const fw::UpdateInfo &info) {}

void GfMenuQuest::updateQuestTaskLog(const fw::UpdateInfo &info) {}

void GfMenuQuest::openMenu(u32 questId, u32 page, bool isTaskLog) {
  GfMenuQuest *quest = get();
  if (quest != nullptr) {
    quest->openQuestId = questId;
    quest->openPage = page;
    quest->openTaskLog = isTaskLog;
  }
}

} // namespace gf
