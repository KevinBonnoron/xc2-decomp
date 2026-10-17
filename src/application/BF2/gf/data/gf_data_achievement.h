#pragma once
#include "types.h"

namespace gf {
struct AchievQuest;

enum ACHIEVEMENT_TYPE {
  ACHIEVEMENT_TYPE_ARTS,
  ACHIEVEMENT_TYPE_SKILL,
  ACHIEVEMENT_TYPE_FIELD_SKILL,
  ACHIEVEMENT_TYPE_KEY,
};

class GfDataAchievement {
public:
  static bool getAchievementType(ACHIEVEMENT_TYPE &type, u32 &index, u32 achievement);
  static u32 getStatsQuestIcon(u32 stats);
  static const char *getStatsNameForDebug(u32 stats);
  static const char *getTitle(u32 achievement);
  static bool getTitle(u8 *&bdat, u32 &textId, u32 achievement);
  static int getAchievementTotalFlgIndex(u16 stats);
  static bool isAddAchievementBonusCount(const AchievQuest &achievQuest);
  static u32 getTotalCount(u32 stats);
  static void addTotalCount(u32 stats, u32 count);
  static bool isWaitControllFreeStats(u32 stats);
  static void setupTotalCount(AchievQuest &achievQuest);
  static void clearTotalCount(u32 stats);
};

} // namespace gf
