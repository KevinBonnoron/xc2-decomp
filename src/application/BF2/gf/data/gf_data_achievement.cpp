#include "gf/data/gf_data_achievement.h"

#include <stddef.h>

#include "bdat.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_task_param.h"

namespace gf {

enum {
  FLAG_ACHIEVEMENT_TOTAL_COUNT = 0x102,
};

enum {
  STATS_WAIT_CONTROLL_FREE_FIRST = 0x22,
  STATS_WAIT_CONTROLL_FREE_SECOND = 0x23,
  STATS_WAIT_CONTROLL_FREE_THIRD = 0x25,
};

constexpr u32 ACHIEVEMENT_TYPE_COUNT_PER_TYPE = 3;
constexpr u32 ACHIEVEMENT_LAST = 9;
constexpr u32 TOTAL_COUNT_STATS_COUNT = 64;

static const u16 totalCountStats[TOTAL_COUNT_STATS_COUNT] = {
    49, 54, 60, 62, 99, 114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 51, 52, 53, 22, 2,
    4,  23, 20, 32, 33, 5,   14,  19,  1,   57,  59,  34,  58,  35,  37,  101, 65,  151, 152, 153, 154, 69,  70,  71, 72, 73, 74,
};

static const u16 bonusCountStats[] = {
    6,   7,   8,   9,   10,  11,  12,  13,  15,  16,  17,  18,  67,  24,  25,  26,  27,  28,  29,  30,  31,  50,  55,  61,  63,  66,  68,  93,  94,  95,  98,  97,  100, 102,
    103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 151, 152, 153, 154, 115, 117, 119, 121, 123, 125, 127, 129, 131, 133, 135, 137, 139, 141, 143, 145, 149, 150,
};

static u32 statsQuestIcons[] = {
    0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0,
    3, 3, 3, 3, 0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

bool GfDataAchievement::getAchievementType(ACHIEVEMENT_TYPE &type, u32 &index, u32 achievement) {
  if (achievement < ACHIEVEMENT_TYPE_COUNT_PER_TYPE) {
    type = static_cast<ACHIEVEMENT_TYPE>(0);
    index = achievement;
    return true;
  }

  if (achievement < ACHIEVEMENT_TYPE_COUNT_PER_TYPE * 2) {
    type = static_cast<ACHIEVEMENT_TYPE>(1);
    index = achievement - ACHIEVEMENT_TYPE_COUNT_PER_TYPE;
    return true;
  }

  if (achievement < ACHIEVEMENT_TYPE_COUNT_PER_TYPE * 3) {
    type = static_cast<ACHIEVEMENT_TYPE>(2);
    index = achievement - ACHIEVEMENT_TYPE_COUNT_PER_TYPE * 2;
    return true;
  }

  if (achievement == ACHIEVEMENT_LAST) {
    type = static_cast<ACHIEVEMENT_TYPE>(3);
    index = 0;
    return true;
  }

  return false;
}

u32 GfDataAchievement::getStatsQuestIcon(u32 stats) {
  if (stats >= sizeof(statsQuestIcons) / sizeof(statsQuestIcons[0])) {
    return 0;
  }

  return statsQuestIcons[stats];
}

const char *GfDataAchievement::getStatsNameForDebug(u32) { return ""; }

const char *GfDataAchievement::getTitle(u32 achievement) {
  u8 *bdat;
  u32 textId;
  const char *title = getTitle(bdat, textId, achievement) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (title == nullptr) {
    title = "";
  }

  return title;
}

bool GfDataAchievement::getTitle(u8 *&bdat, u32 &textId, u32 achievement) {
  if (achievement == 0) {
    return false;
  }

  textId = QuestListAcc::get()->getFLD_AchievementListTitle(achievement);
  bdat = GfBdatMsg::getFpAchievement();
  return textId != 0;
}

int GfDataAchievement::getAchievementTotalFlgIndex(u16 stats) {
  if (stats == 0) {
    return -1;
  }

  for (int index = 0; index < static_cast<int>(TOTAL_COUNT_STATS_COUNT); index++) {
    if (totalCountStats[index] == stats) {
      return index + FLAG_ACHIEVEMENT_TOTAL_COUNT;
    }
  }

  return -1;
}

bool GfDataAchievement::isAddAchievementBonusCount(const AchievQuest &achievQuest) {
  for (size_t index = 0; index < sizeof(bonusCountStats) / sizeof(bonusCountStats[0]); index++) {
    if (bonusCountStats[index] == achievQuest.unknown0e) {
      return true;
    }
  }

  QuestTaskParam taskParam(GfDataQuest::getListNextQuestA(achievQuest.unknown00), 0, TASK_STATE_NONE);
  switch (taskParam.unknown10) {
  case TASK_TYPE_BATTLE:
  case TASK_TYPE_USE:
  case TASK_TYPE_TALK:
  case TASK_TYPE_FIELD_SKILL_COUNT:
    return true;
  default:
    return false;
  }
}

u32 GfDataAchievement::getTotalCount(u32 stats) {
  int flag = getAchievementTotalFlgIndex(stats);
  if (flag < 0) {
    return 0;
  }

  return GfGameFlag::getLocal(32, flag);
}

void GfDataAchievement::addTotalCount(u32 stats, u32 count) {
  int flag = getAchievementTotalFlgIndex(stats);
  if (flag < 0) {
    return;
  }

  u32 totalCount = GfGameFlag::getLocal(32, flag);
  u32 newTotalCount = totalCount + count;
  if (newTotalCount < totalCount) {
    newTotalCount = 0xffffffff;
  }

  GfGameFlag::setLocal(32, flag, newTotalCount);
}

bool GfDataAchievement::isWaitControllFreeStats(u32 stats) {
  switch (stats) {
  case STATS_WAIT_CONTROLL_FREE_FIRST:
  case STATS_WAIT_CONTROLL_FREE_SECOND:
  case STATS_WAIT_CONTROLL_FREE_THIRD:
    return true;
  default:
    return false;
  }
}

void GfDataAchievement::setupTotalCount(AchievQuest &achievQuest) {
  if (achievQuest.unknown0e == 0 || getAchievementTotalFlgIndex(achievQuest.unknown0e) < 0) {
    return;
  }

  if (getTotalCount(achievQuest.unknown0e) == 0 || achievQuest.getCount() != 0) {
    return;
  }

  achievQuest.setCount(getTotalCount(achievQuest.unknown0e));
}

void GfDataAchievement::clearTotalCount(u32 stats) {
  int flag = getAchievementTotalFlgIndex(stats);
  if (flag < 0) {
    return;
  }

  GfGameFlag::setLocal(32, flag, 0);
}

} // namespace gf
