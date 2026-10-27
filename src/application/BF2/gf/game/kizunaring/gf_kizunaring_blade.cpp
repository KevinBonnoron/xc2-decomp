#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_blade_arts.h"
#include "gf/data/gf_data_blade_skill.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_field_skill.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/request/gf_req_scom.h"
#include "types.h"

namespace gf {

u32 GfKizunaringBlade::getAchievementCategory(u32 blade, u32 line, u32 level) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      u32 achievement = QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievementSet, level - 1);
      if (achievement != 0) {
        return QuestListAcc::get()->getFLD_AchievementListCategory(achievement);
      }
    }
  }

  return 0;
}

u32 GfKizunaringBlade::getAchievementIcon(u32 blade, u32 line, u32 level) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      u32 achievement = QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievementSet, level - 1);
      if (achievement != 0) {
        return QuestListAcc::get()->getFLD_AchievementListIcon(achievement);
      }
    }
  }

  return 0;
}

u32 GfKizunaringBlade::getAchievementVoiceCategory(u32 blade, u32 line, u32 level) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      u32 achievement = QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievementSet, level - 1);
      if (achievement != 0) {
        return QuestListAcc::get()->getFLD_AchievementListVoiceCategory(achievement);
      }
    }
  }

  return 0;
}

u32 GfKizunaringBlade::getAchievementAfterVoice(u32 blade, u32 line, u32 level) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      u32 achievement = QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievementSet, level - 1);
      if (achievement != 0) {
        return QuestListAcc::get()->getFLD_AchievementListAfterVoice(achievement);
      }
    }
  }

  return 0;
}

u32 GfKizunaringBlade::getAchievementDifficulty(u32 blade, u32 line, u32 level) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      u32 achievement = QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievementSet, level - 1);
      if (achievement != 0) {
        return QuestListAcc::get()->getFLD_AchievementListDifficulty(achievement);
      }
    }
  }

  return 0;
}

u32 GfKizunaringBlade::getAchievementQuest(u32 blade, u32 line, u32 level) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      u32 achievement = QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievementSet, level - 1);
      if (achievement != 0) {
        return QuestListAcc::get()->getFLD_AchievementListTask(achievement);
      }
    }
  }

  return 0;
}

u32 GfKizunaringBlade::getAchievementSetCategory(u32 blade, u32 line) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      return QuestListAcc::get()->getFLD_AchievementSetCategory(achievementSet);
    }
  }

  return 0;
}

u32 GfKizunaringBlade::getAchievementSetAbilityLevel(u32 blade, u32 line) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      return QuestListAcc::get()->getFLD_AchievementSetAbilityLevel(achievementSet);
    }
  }

  return 0;
}

bool GfKizunaringBlade::isEnableAchievementCount(u32 blade) {
  if (blade == 0 || GfDataBlade::isActivateUnuse(blade)) {
    return false;
  }

  if (GfDataBlade::isUnselect(blade)) {
    return false;
  }

  u32 driver = GfDataBlade::getSetDriver(blade);
  if (driver != 0 && GfDataDriver::isActivateUnuse(driver)) {
    return false;
  }

  return true;
}

u16 GfKizunaringBlade::getAchievementResultEnhance(u32 blade, u32 line, u32 level) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  ACHIEVEMENT_TYPE type;
  u32 index;
  GfDataAchievement::getAchievementType(type, index, line);
  u16 enhance = 0;
  if (type == ACHIEVEMENT_TYPE_ARTS) {
    enhance = GfDataBladeArts::getEnhance(dataParamAcc.getBladeArts(index, false), level);
  } else if (type == ACHIEVEMENT_TYPE_SKILL) {
    enhance = GfDataBladeSkill::getEnhance(dataParamAcc.getBladeSkill(index, false), level);
  }

  return enhance;
}

bool GfKizunaringBlade::isNetabareOK(u32 blade, u32 line, u32 level) {
  SDataBladeAchievement *achievement = GfDataBlade::getAchievInfo(blade, line);
  AchievQuest *achievQuest = &achievement->unknown04[level - 1];
  if (!achievQuest->unknown00.empty()) {
    QuestID nextQuest = GfDataQuest::getListNextQuestA(achievQuest->unknown00);
    QuestListAcc *questListAcc = QuestListAcc::get();
    QuestTaskParam taskParam(nextQuest, 0, TASK_STATE_NONE);
    u32 condition = questListAcc->getTaskTaskCondition1(taskParam.unknown08);
    if (condition != 0) {
      return GfGameCond::isGameCond(condition);
    }
  }

  return true;
}

bool GfKizunaringBlade::isCompleteLevel(u32 blade, u32 line, u32 level) {
  if (blade == 0 || GfDataBlade::isActivateUnuse(blade)) {
    return false;
  }

  if (GfDataBlade::isUnselect(blade)) {
    return false;
  }

  u32 driver = GfDataBlade::getSetDriver(blade);
  if (driver != 0 && GfDataDriver::isActivateUnuse(driver)) {
    return false;
  }

  SDataBladeAchievement *achievement = GfDataBlade::getAchievInfo(blade, line);
  if (achievement->unknown00 == 0 || !isNetabareOK(blade, line, level)) {
    return false;
  }

  for (u32 index = 1; index < level; index++) {
    const AchievQuest &achievQuest = achievement->unknown04[index - 1];
    if (!achievQuest.unknown00.empty() && (achievQuest.unknown0c & 1) == 0 && (GfQuestInfo::isQuestOrder(achievQuest.unknown00) || GfQuestInfo::isQuestNotOrder(achievQuest.unknown00))) {
      return false;
    }
  }

  return true;
}

bool GfKizunaringBlade::isCompleteLevel(const AchievQuest &achievQuest) { return isCompleteLevel(achievQuest.unknown16, achievQuest.unknown12, achievQuest.unknown14); }

bool GfKizunaringBlade::getAchievementTitleMsg(u8 *&bdat, u32 &textId, u32 blade, u32 line, u32 level) {
  if (blade != 0) {
    u32 achievementSet = GfDataBlade::getAchievInfo(blade, line)->unknown00;
    if (achievementSet != 0) {
      u32 achievement = QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievementSet, level - 1);
      if (achievement != 0) {
        textId = QuestListAcc::get()->getFLD_AchievementListTitle(achievement);
        bdat = GfDataBdat::getFP(BDAT_FLD_ACHIEVEMENTTXT);
        return true;
      }
    }
  }

  return false;
}

bool GfKizunaringBlade::getAchievementResultMsg(u8 *&bdat, u32 &textId, u32 blade, u32 line, u32 level) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  ACHIEVEMENT_TYPE type;
  u32 index;
  GfDataAchievement::getAchievementType(type, index, line);
  bool hasMsg = false;
  if (type == ACHIEVEMENT_TYPE_ARTS) {
    hasMsg = GfDataBladeArts::getEnhanceCaption(bdat, textId, dataParamAcc.getBladeArts(index, false), level);
  } else if (type == ACHIEVEMENT_TYPE_SKILL) {
    hasMsg = GfDataBladeSkill::getEnhanceCaption(bdat, textId, dataParamAcc.getBladeSkill(index, false), level);
  } else if (type == ACHIEVEMENT_TYPE_FIELD_SKILL) {
    hasMsg = GfDataFieldSkill::getCaption(bdat, textId, dataParamAcc.getFieldSkill(index, false));
  }

  return hasMsg;
}

int GfKizunaringBlade::getSkillLevel(u32 blade, u32 line, u32 level) {
  SDataBladeAchievement *achievement = GfDataBlade::getAchievInfo(blade, line);
  int skillLevel = 0;
  for (u32 index = 1; index <= level; index++) {
    const AchievQuest &achievQuest = achievement->unknown04[index - 1];
    if (!achievQuest.unknown00.empty() || (achievQuest.unknown14 == 1 && (achievQuest.unknown0c & 1) != 0)) {
      skillLevel++;
    }
  }

  return skillLevel;
}

void GfKizunaringBlade::qevCompleteQuest(const QuestCompleteParam &param) {
  if (param.unknown04.unknown02 != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    if (achievQuest != nullptr) {
      SCOM_POPUP::createAchievement(achievQuest->unknown16, achievQuest->unknown12, achievQuest->unknown14);
    }
  }
}

void GfKizunaringBlade::completeAllAchievementForDebug(u32) {}

void GfKizunaringBlade::completeAchievementForDebug(QuestID) {}

} // namespace gf
