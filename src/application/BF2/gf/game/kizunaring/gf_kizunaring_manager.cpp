#include "gf/game/kizunaring/gf_kizunaring_manager.h"

#include "gf/gf_allocator.h"

namespace gf {

GfKizunaringManager::GfKizunaringManager(const GfSetupParam &param) { initialize(param); }

void GfKizunaringManager::initialize(const GfSetupParam &) { initialized = true; }

GfKizunaringManager::~GfKizunaringManager() {}

void GfKizunaringManager::build(const GfSetupParam &param) {
  // __LINE__ must be 55 as in the original file: its value changes the instruction order.
#line 55
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfKizunaringManager(param);
}

void GfKizunaringManager::destroy() {
  GfKizunaringManager *kizunaringManager = get();
  kizunaringManager->finalize();
  delete kizunaringManager;
}

void GfKizunaringManager::finalize() { initialized = false; }

bool GfKizunaringManager::isInitialized() { return get() != nullptr && get()->initialized; }

void GfKizunaringManager::orderAchievement(u32 blade) { GfKizunaringBlade::orderAchievement(blade); }

void GfKizunaringManager::setupGame() {}

void GfKizunaringManager::completeAllAchievementForDebug(u32 blade) { GfKizunaringBlade::completeAllAchievementForDebug(blade); }

void GfKizunaringManager::qevCompleteQuest(const QuestCompleteParam &param) { GfKizunaringBlade::qevCompleteQuest(param); }

} // namespace gf
