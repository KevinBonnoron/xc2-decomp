#include "gf/game/achiev/gf_achiev_manager.h"

#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_quest.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"

namespace gf {

constexpr u32 unknown001 = 4;  // Inferred role: mission flag value; original name unknown.
constexpr s32 unknown002 = 60; // Inferred role: maximum increments flushed per update; original name unknown.

GfAchievManager::GfAchievManager(const GfSetupParam &) {}

GfAchievManager::~GfAchievManager() {}

void GfAchievManager::build(const GfSetupParam &param) {
  // __LINE__ must be 77 as in the original file: its value changes the instruction order.
#line 77
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfAchievManager(param);
}

void GfAchievManager::destroy() { delete get(); }

void GfAchievManager::update(const fw::UpdateInfo &) {
  for (s32 count = unknown002; !unknown08.empty() && count > 0; count--) {
    flushEventIncAchiev(unknown08.front());
    unknown08.pop_front();
  }
}

void GfAchievManager::flushEventIncAchiev(const IncQuest &incQuest) {
  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(incQuest.unknown00);
  if (achievQuest == nullptr || achievQuest->unknown16 == 0 || achievQuest->unknown14 == 0) {
    return;
  }
  ACHIEVEMENT_TYPE type;
  u32 index;
  mm::mtl::FixStr<128> name;
  GfDataAchievement::getAchievementType(type, index, achievQuest->unknown12);
  switch (type) {
  case ACHIEVEMENT_TYPE_UNKNOWN_0:
    name.format("アーツアチーブメント[%d]", index + 1);
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_1:
    name.format("ブレイドスキルアチーブメント[%d]", index + 1);
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_2:
    name.format("フィールドスキルアチーブメント[%d]", index + 1);
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_3:
    name.format("キーアチーブメント");
    break;
  }
}

void GfAchievManager::incleaseAchievCount(QuestID quest, u32 count, u32 add) {
  if (add == 0) {
    return;
  }
  IncQuest incQuest;
  incQuest.unknown00 = quest;
  incQuest.unknown04 = count;
  incQuest.unknown08 = add;
  if (unknown08.full()) {
    flushEventIncAchiev(incQuest);
  } else {
    unknown08.push(incQuest);
  }
}

void GfAchievManager::gevItemAdd(u32 item, int count) { GfAchievStats::checkItem(item, count); }

void GfAchievManager::gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType) {
  if (oldActivateType != ACTIVATE_TYPE_UNKNOWN_0 && activateType != oldActivateType) {
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
