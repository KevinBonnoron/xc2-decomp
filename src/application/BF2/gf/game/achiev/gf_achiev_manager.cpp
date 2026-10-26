#include "gf/game/achiev/gf_achiev_manager.h"

#include "gf/game/quest/gf_quest_manager.h"
#include "gf/gf_allocator.h"

namespace gf {

constexpr u32 unknown001 = 4; // Inferred role: mission flag value; original name unknown.

GfAchievManager::GfAchievManager(const GfSetupParam &) : unknown1808(0), unknown1810(0) {}

GfAchievManager::~GfAchievManager() {}

void GfAchievManager::build(const GfSetupParam &param) {
  // __LINE__ must be 77 as in the original file: its value changes the instruction order.
#line 77
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfAchievManager(param);
}

void GfAchievManager::destroy() { delete get(); }

void GfAchievManager::gevItemAdd(u32 item, int count) { GfAchievStats::checkItem(item, count); }

void GfAchievManager::gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType) {
  if (oldActivateType != ACTIVATE_TYPE_UNUSE && activateType != oldActivateType) {
    GfAchievStats::checkBladeActivate(blade);
  }
}

void GfAchievManager::gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value) {
  if (flag == unknown001) {
    GfQuestManager::eventCheckTaskAll();
  }
}

void GfAchievManager::initialize(const GfSetupParam &) {}

void GfAchievManager::finalize() {}

} // namespace gf
