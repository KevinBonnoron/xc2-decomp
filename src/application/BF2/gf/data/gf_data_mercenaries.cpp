#include "gf/data/gf_data_mercenaries.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "mm_mtl/fixstr.h"

namespace gf {

enum {
  FLAG_MERCENARIES_LEVEL = 0x2,
  FLAG_MERCENARIES_POINT = 0x3,
  FLAG_MERCENARIES_MISSION = 0x5,
  FLAG_MERCENARIES_MISSION_PROGRESS = 0x87cf,
  FLAG_MERCENARIES_MISSION_PROGRESS_DISPLAY = 0x89c4,
  FLAG_MERCENARIES_MISSION_SEEN = 0x9a97,
  FLAG_MERCENARIES_MISSION_COMPLETE = 0xb4cd,
};

enum {
  MISSION_STATE_NONE = 0,
  MISSION_STATE_ORDER_ENABLE = 1,
  MISSION_STATE_EXPEDITION = 2,
  MISSION_STATE_REWARD = 3,
  MISSION_STATE_COMPLETE = 4,
};

enum {
  MERCENARIES_CONFIG_REWARD_ACHIEVMENT_RATIO = 0x10,
  MERCENARIES_CONFIG_MISSION_PERFORMANCE_RATIO = 0x11,
};

enum {
  WILDCARD_MERCENARIES_POINT_LIMIT = 0x3e,
};

enum {
  REQUEST_GENDER_ANY = 4,
};

enum {
  REQUEST_BLADE_CATEGORY = 1,
  REQUEST_BLADE_PERFORMANCE = 2,
  REQUEST_BLADE_RACE = 3,
  REQUEST_BLADE_GENDER = 4,
  REQUEST_BLADE_ARTS = 5,
  REQUEST_BLADE_FIELD_SKILL = 6,
  REQUEST_BLADE_ATTRIBUTE = 7,
};

enum {
  CONDITION_PARTY_CATEGORY_BLADE = 4,
};

constexpr u32 CONDITION_PARTY_MEMBER_COUNT = 3;

constexpr u32 BLADE_ARTS_COUNT = 3;
constexpr u32 BLADE_FIELD_SKILL_COUNT = 3;

constexpr u32 RESERVER_PER_LEVEL = 24;
constexpr u32 RESERVER_GAME_CLEAR_BONUS = 48;
constexpr u32 REWARD_ACHIEVMENT_RATIO_PER_LEVEL = 5;
constexpr u32 MISSION_TASK_COUNT = 4;
constexpr u32 MISSION_FIELD_SKILL_COUNT = 3;
constexpr f32 FIELD_SKILL_TIME_REDUCTION_PER_LEVEL = 6.0f;

static f32 getBladeFieldSkillLevel(u32 blade, u32 fieldSkill) {
  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  f32 level = 0.0f;
  if (paramAcc.isValid()) {
    if (paramAcc.getFieldSkill(0, false) == fieldSkill) {
      level = paramAcc.getFieldSkillLevel(0, false);
    }

    if (paramAcc.getFieldSkill(1, false) == fieldSkill) {
      level += paramAcc.getFieldSkillLevel(1, false);
    }

    if (paramAcc.getFieldSkill(2, false) == fieldSkill) {
      level += paramAcc.getFieldSkillLevel(2, false);
    }
  }

  return level;
}

u32 GfDataMercenaries::getReserverMax() {
  return getLevel() * RESERVER_PER_LEVEL + RESERVER_PER_LEVEL + (GfDataManager::getDataGame()->gameClearCount != 0 ? RESERVER_GAME_CLEAR_BONUS : 0);
}

SDataMercenaries *GfDataMercenaries::getSDataMercenaries() { return &GfDataManager::getDataGame()->mercenaries; }

u32 GfDataMercenaries::getLevel() { return GfGameFlag::getLocal(4, FLAG_MERCENARIES_LEVEL); }

u32 GfDataMercenaries::getLevelMax() { return MERCENARIES_LEVEL_MAX; }

void GfDataMercenaries::setLevel(u32 level) { GfGameFlag::setLocal(4, FLAG_MERCENARIES_LEVEL, level); }

u32 GfDataMercenaries::getPoint() { return GfGameFlag::getLocal(16, FLAG_MERCENARIES_POINT); }

u32 GfDataMercenaries::getPointMax() {
  static const u16 pointMaxWildcards[] = {0, 59, 60, 61, 62, 0};
  u32 level = getLevel();
  if (level == 0 || level == MERCENARIES_LEVEL_MAX) {
    return 0;
  }

  return GfBdatBtl::get()->getWildcardDatavalueU2(pointMaxWildcards[level]);
}

u32 GfDataMercenaries::getPointLimit() { return GfBdatBtl::get()->getWildcardDatavalueU2(WILDCARD_MERCENARIES_POINT_LIMIT); }

void GfDataMercenaries::setPoint(u32 point) { GfGameFlag::setLocal(16, FLAG_MERCENARIES_POINT, point); }

u32 GfDataMercenaries::getTeamMax() {
  u32 level = getLevel();
  u32 teamMax = 1;
  if (level > 1) {
    teamMax = 2;
  }

  if (level > 3) {
    teamMax++;
  }

  return teamMax;
}

u32 GfDataMercenaries::getTeamNum() { return GfDataManager::getDataGame()->mercenaries.teams.size(); }

bool GfDataMercenaries::getReserver(mm::mtl::FixedVector<u16, 422> &reservers) {
  GfDataBlade::getListReserver(reservers);
  return !reservers.empty();
}

bool GfDataMercenaries::isValidTeamID(u32 teamID) { return getTeamByTeamID(teamID) != nullptr; }

SDataMercenariesTeam *GfDataMercenaries::getTeamByTeamID(u32 teamID) {
  for (SDataMercenariesTeam &team : GfDataManager::getDataGame()->mercenaries.teams) {
    if (team.teamID == teamID) {
      return &team;
    }
  }

  return nullptr;
}

u32 GfDataMercenaries::getTeamPower(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  u32 power = 0;
  for (u16 member : team->members) {
    power += GfDataBlade::getBladePower(member);
  }

  return power;
}

u32 GfDataMercenaries::getTeamID(u32 blade) {
  for (SDataMercenariesTeam &team : GfDataManager::getDataGame()->mercenaries.teams) {
    for (u16 member : team.members) {
      if (member == blade) {
        return team.teamID;
      }
    }
  }

  return 0;
}

u32 GfDataMercenaries::getMissionIdByBlade(u32 blade) {
  for (SDataMercenariesTeam &team : GfDataManager::getDataGame()->mercenaries.teams) {
    for (u16 member : team.members) {
      if (member == blade) {
        return team.mission;
      }
    }
  }

  return 0;
}

SDataMercenariesTeam *GfDataMercenaries::getTeamByIndex(u32 index) { return &GfDataManager::getDataGame()->mercenaries.teams[index]; }

SDataMercenariesTeam *GfDataMercenaries::getTeamByMissionID(u32 mission) {
  if (mission == 0) {
    return nullptr;
  }

  for (SDataMercenariesTeam &team : GfDataManager::getDataGame()->mercenaries.teams) {
    if (team.mission == mission) {
      return &team;
    }
  }

  return nullptr;
}

u32 GfDataMercenaries::getTeamIDByMissionID(u32 mission) {
  SDataMercenariesTeam *team = getTeamByMissionID(mission);
  if (team == nullptr) {
    return 0;
  }

  return team->teamID;
}

SDataMercenariesTeam *GfDataMercenaries::getTeamMember(u32 teamID) { return getTeamByTeamID(teamID); }

u8 GfDataMercenaries::getTeamAnimalNum(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  u8 animalNum = 0;
  for (u32 i = 0; i < 6; i++) {
    if (team->members[i] != 0 && GfDataBlade::getSDataBlade(team->members[i])->questRace == QUEST_RACE_ANIMAL) {
      animalNum++;
    }
  }

  return animalNum;
}

bool GfDataMercenaries::getTeamByZoneMissionWorking(mm::mtl::FixedVector<u16, 3> &teams, u32 zone) {
  mm::mtl::FixedVector<SDataMercenariesTeam, 3> &mercenariesTeams = GfDataManager::getDataGame()->mercenaries.teams;
  for (SDataMercenariesTeam *team = mercenariesTeams.begin(); team != mercenariesTeams.end(); team++) {
    if (team->mission != 0 && GfGameFlag::getLocal(4, FLAG_MERCENARIES_MISSION + team->mission) == MISSION_STATE_EXPEDITION) {
      u32 map = getMissionMapID(team->mission);
      if (map != 0 && GfDataMap::getZoneIdForGameMap(map) == zone) {
        teams.push_back(team->teamID);
      }
    }
  }

  return !teams.empty();
}

u32 GfDataMercenaries::getMissionFlag(u32 mission) {
  if (mission == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(4, FLAG_MERCENARIES_MISSION + mission);
}

u32 GfDataMercenaries::getMissionMapID(u32 mission) {
  if (mission == 0) {
    return 0;
  }

  QuestID quest = getMissionQuestID(mission);
  if (quest.empty()) {
    return 0;
  }

  u32 hints = GfDataQuest::getListHintsID(quest);
  if (hints == 0) {
    return 0;
  }

  u32 map = QuestListAcc::get()->getHintsZoneID(hints);
  if (GfDataMap::isArcadiaDestroy() && map == MAP_ARCADIA) {
    return MAP_LIBERALITAS;
  }

  return map;
}

bool GfDataMercenaries::isTeamStateReward(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr || team->mission == 0) {
    return false;
  }

  return GfGameFlag::getLocal(4, FLAG_MERCENARIES_MISSION + team->mission) == MISSION_STATE_REWARD;
}

void GfDataMercenaries::setMissionFlag(u32 mission, u32 missionFlag) {
  GfGameFlag::setLocal(4, FLAG_MERCENARIES_MISSION + mission, missionFlag);
  int progress = GfGameFlag::getLocal(2, FLAG_MERCENARIES_MISSION_PROGRESS + mission);
  if (progress >= 2) {
    return;
  }

  int newProgress;
  switch (missionFlag) {
  case MISSION_STATE_EXPEDITION:
    newProgress = 1;
    break;
  case MISSION_STATE_REWARD:
    newProgress = 1;
    break;
  case MISSION_STATE_COMPLETE:
    newProgress = 2;
    break;
  default:
    newProgress = 0;
    break;
  }

  if (progress != newProgress) {
    GfGameFlag::setLocal(2, FLAG_MERCENARIES_MISSION_PROGRESS + mission, newProgress);
    GfGameFlag::setLocal(2, FLAG_MERCENARIES_MISSION_PROGRESS_DISPLAY + mission, newProgress);
  }
}

bool GfDataMercenaries::isMissionCompleteFlag(u32 mission) { return GfGameFlag::getLocal(1, FLAG_MERCENARIES_MISSION_COMPLETE + mission) != 0; }

void GfDataMercenaries::setMissionCompleteFlag(u32 mission) { GfGameFlag::setLocal(1, FLAG_MERCENARIES_MISSION_COMPLETE + mission, 1); }

u32 GfDataMercenaries::getRequestPerformance(u32 mission) { return QuestListAcc::get()->getFLD_MercenariesMissionRequestPerformance(mission); }

u32 GfDataMercenaries::getTeamMissionTime(u32 teamID, u32 mission) {
  u32 missionTime = getMissionTime(mission);
  if (missionTime == 0) {
    return missionTime;
  }

  f32 time = missionTime;
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team != nullptr) {
    f32 fieldSkillLevel = 0.0f;
    for (u32 index = 0; index < MISSION_FIELD_SKILL_COUNT; index++) {
      u32 fieldSkill = getFieldSkill(mission, index);
      if (fieldSkill == 0) {
        continue;
      }

      for (u16 member : team->members) {
        if (member == 0) {
          continue;
        }

        fieldSkillLevel += getBladeFieldSkillLevel(member, fieldSkill);
      }
    }

    f32 reducedTime = time * (fieldSkillLevel * -FIELD_SKILL_TIME_REDUCTION_PER_LEVEL + 100.0f) * 0.01f;
    f32 minTime = time * getMissionPerformanceRatio();
    time = reducedTime < minTime ? minTime : reducedTime;

    if (time <= 1.0f) {
      time = 1.0f;
    }
  }

  return static_cast<u32>(time);
}

u32 GfDataMercenaries::getFieldSkill(u32 mission, u32 index) {
  switch (index) {
  case 0:
    return getFieldSkill1(mission);
  case 1:
    return getFieldSkill2(mission);
  case 2:
    return getFieldSkill3(mission);
  default:
    return 0;
  }
}

f32 GfDataMercenaries::getMissionPerformanceRatio() {
  return QuestListAcc::get()->getFLD_MercenariesConfigValue(MERCENARIES_CONFIG_MISSION_PERFORMANCE_RATIO) * 0.01f + 0.001f;
}

u32 GfDataMercenaries::getStartMissionID() { return QuestListAcc::get()->getFLD_MercenariesMissionStart(); }

u32 GfDataMercenaries::getEndMissionID() { return QuestListAcc::get()->getFLD_MercenariesMissionEnd(); }

QuestID GfDataMercenaries::getMissionQuestID(u32 mission) { return toQuestID(QuestListAcc::get()->getFLD_MercenariesMissionQuestID(mission)); }

u32 GfDataMercenaries::getMissionPurposeID(u32 mission) {
  QuestID quest = getMissionQuestID(mission);
  if (quest.empty()) {
    return 0;
  }

  QuestID nextQuest = GfDataQuest::getListNextQuestA(quest);
  if (nextQuest.empty()) {
    return 0;
  }

  return GfDataQuest::getListPurposeID(nextQuest);
}

u32 GfDataMercenaries::getTeamMission(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  return team->mission;
}

ElapseTime GfDataMercenaries::getTeamMissionTime(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    ElapseTime none = {};
    return none;
  }

  return team->missionTime;
}

ElapseTime GfDataMercenaries::getTeamMissionTimeOriginal(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    ElapseTime none = {};
    return none;
  }

  return team->missionTimeOriginal;
}

bool GfDataMercenaries::isTeamStateEmpty(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return true;
  }

  return team->mission == 0;
}

bool GfDataMercenaries::isTeamStateExpedition(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr || team->mission == 0) {
    return false;
  }

  return GfGameFlag::getLocal(4, FLAG_MERCENARIES_MISSION + team->mission) == MISSION_STATE_EXPEDITION;
}

u32 GfDataMercenaries::getMissionTaskType(u32 mission, u32 index) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 purpose = getMissionPurposeID(mission);
  if (purpose == 0) {
    return 0;
  }

  return questListAcc->getTaskTaskType(purpose, index);
}

u32 GfDataMercenaries::getMissionTaskType(u32 mission) {
  u32 taskType = 0;
  for (u32 index = 0; index < MISSION_TASK_COUNT; index++) {
    u32 type = getMissionTaskType(mission, index);
    if (type != TASK_TYPE_REQUEST_BLADE) {
      taskType = type;
      break;
    }
  }

  return taskType;
}

u32 GfDataMercenaries::getMissionCategory(u32 mission) { return QuestListAcc::get()->getFLD_MercenariesMissionCategory(mission); }

u32 GfDataMercenaries::getMissionRewardID(u32 mission) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (isMissionCompleteFlag(mission) && QuestListAcc::get()->getFLD_MercenariesMissionRepeatable(mission) != 0) {
    return questListAcc->getListRewardSetB(getMissionQuestID(mission));
  }

  return questListAcc->getListRewardSetA(getMissionQuestID(mission));
}

bool GfDataMercenaries::isOrderOnlyOne(u32 mission) { return QuestListAcc::get()->getFLD_MercenariesMissionRepeatable(mission) == 0; }

u32 GfDataMercenaries::getMissionZoneID(u32 mission) {
  u32 map = getMissionMapID(mission);
  if (map == 0) {
    return 0;
  }

  return GfDataMap::getZoneIdForGameMap(map);
}

bool GfDataMercenaries::isMissionOrderTeam(u32 mission) {
  SDataMercenariesTeam *team = getTeamByMissionID(mission);
  if (team == nullptr) {
    return false;
  }

  return team->teamID != 0;
}

bool GfDataMercenaries::isMissionComplete(u32 mission) {
  bool complete = false;
  if (mission != 0) {
    complete = GfGameFlag::getLocal(4, FLAG_MERCENARIES_MISSION + mission) == MISSION_STATE_COMPLETE;
  }

  return complete;
}

bool GfDataMercenaries::isEnableMissionBlade(u32 blade, u32 requestBlade) {
  if (requestBlade == 0) {
    return false;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  if (!paramAcc.isValid()) {
    return false;
  }

  u32 category = questListAcc->getRequestBladeRequestCategory(requestBlade);
  if (category != 0 && category != paramAcc.getWeaponType(-1, false)) {
    return false;
  }

  u32 attribute = questListAcc->getRequestBladeRequestAtr(requestBlade);
  if (attribute != 0 && attribute != paramAcc.getAttribute(-1, false)) {
    return false;
  }

  u32 performance = questListAcc->getRequestBladeRequestPerformance(requestBlade);
  if (performance > GfDataBlade::getBladePower(blade)) {
    return false;
  }

  u32 race = questListAcc->getRequestBladeRequestRace(requestBlade);
  if (race != 0 && race != paramAcc.getQuestRace()) {
    return false;
  }

  u32 gender = questListAcc->getRequestBladeRequestGender(requestBlade);
  if (gender != 0 && gender != REQUEST_GENDER_ANY && gender != paramAcc.getGender()) {
    return false;
  }

  u32 arts = questListAcc->getRequestBladeRequestArts(requestBlade);
  if (arts != 0) {
    u32 index = 0;
    while (paramAcc.getBladeArts(index, false) != arts) {
      index++;
      if (index >= BLADE_ARTS_COUNT) {
        return false;
      }
    }

    u32 artsLevel = paramAcc.getBladeArtsLevel(index, false);
    if (artsLevel == 0 || questListAcc->getRequestBladeRequestArtsLevel(requestBlade) > artsLevel) {
      return false;
    }
  }

  u32 fieldSkill = questListAcc->getRequestBladeRequestFSkill(requestBlade);
  if (fieldSkill != 0) {
    u32 fieldSkillLevel = 0;
    for (u32 index = 0; index < BLADE_FIELD_SKILL_COUNT; index++) {
      if (paramAcc.getFieldSkill(index, false) == fieldSkill) {
        fieldSkillLevel = paramAcc.getFieldSkillLevel(index, false);
        break;
      }
    }

    if (questListAcc->getRequestBladeRequestFSLevel(requestBlade) > fieldSkillLevel) {
      return false;
    }
  }

  return true;
}

u16 GfDataMercenaries::getTeamLeader(u32 teamID) {
  if (teamID == 0) {
    return 0;
  }

  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  return team->members[0];
}

bool GfDataMercenaries::isEnableOrder(u32 mission) {
  if (mission == 0) {
    return true;
  }

  u32 missionFlag = GfGameFlag::getLocal(4, FLAG_MERCENARIES_MISSION + mission);
  if (missionFlag == MISSION_STATE_NONE) {
    return true;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  if (missionFlag == MISSION_STATE_COMPLETE) {
    return questListAcc->getFLD_MercenariesMissionRepeatable(mission) != 0;
  }

  return false;
}

bool GfDataMercenaries::isNewMission(u32 mission) { return GfGameFlag::getLocal(1, FLAG_MERCENARIES_MISSION_SEEN + mission) == 0; }

void GfDataMercenaries::clearNewMission(u32 mission) { GfGameFlag::setLocal(1, FLAG_MERCENARIES_MISSION_SEEN + mission, 1); }

u32 GfDataMercenaries::getFieldSkill1(u32 mission) {
  QuestID quest = getMissionQuestID(mission);
  if (quest.empty()) {
    return 0;
  }

  u32 hints = GfDataQuest::getListHintsID(quest);
  if (hints == 0) {
    return 0;
  }

  return QuestListAcc::get()->getHintsFSkillID1(hints);
}

u32 GfDataMercenaries::getFieldSkill2(u32 mission) {
  QuestID quest = getMissionQuestID(mission);
  if (quest.empty()) {
    return 0;
  }

  u32 hints = GfDataQuest::getListHintsID(quest);
  if (hints == 0) {
    return 0;
  }

  return QuestListAcc::get()->getHintsFSkillID2(hints);
}

u32 GfDataMercenaries::getFieldSkill3(u32 mission) {
  QuestID quest = getMissionQuestID(mission);
  if (quest.empty()) {
    return 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 hints = GfDataQuest::getListHintsID(quest);
  if (hints == 0) {
    return 0;
  }

  return questListAcc->getHintsFSkillID3(hints);
}

u32 GfDataMercenaries::getMissionTime(u32 mission) { return QuestListAcc::get()->getFLD_MercenariesMissionRequestPerformance(mission); }

bool GfDataMercenaries::getFieldSkill1Info(u8 *&bdat, u32 &textId, u32 mission) {
  u32 fieldSkill = getFieldSkill1(mission);
  if (fieldSkill == 0) {
    return false;
  }

  textId = QuestListAcc::get()->getFLD_FieldSkillListName(fieldSkill);
  bdat = GfBdatMsg::getFpFieldSkill();
  return textId != 0;
}

bool GfDataMercenaries::getFieldSkill2Info(u8 *&bdat, u32 &textId, u32 mission) {
  u32 fieldSkill = getFieldSkill2(mission);
  if (fieldSkill == 0) {
    return false;
  }

  textId = QuestListAcc::get()->getFLD_FieldSkillListName(fieldSkill);
  bdat = GfBdatMsg::getFpFieldSkill();
  return textId != 0;
}

bool GfDataMercenaries::getFieldSkill3Info(u8 *&bdat, u32 &textId, u32 mission) {
  u32 fieldSkill = getFieldSkill3(mission);
  if (fieldSkill == 0) {
    return false;
  }

  textId = QuestListAcc::get()->getFLD_FieldSkillListName(fieldSkill);
  bdat = GfBdatMsg::getFpFieldSkill();
  return textId != 0;
}

bool GfDataMercenaries::getFieldSkillInfo(u8 *&bdat, u32 &textId, u32 mission, u32 index) {
  switch (index) {
  case 0:
    return getFieldSkill1Info(bdat, textId, mission);
  case 1:
    return getFieldSkill2Info(bdat, textId, mission);
  case 2:
    return getFieldSkill3Info(bdat, textId, mission);
  default:
    return false;
  }
}

u32 GfDataMercenaries::getRewardAchievmentRatio() {
  u32 ratio = QuestListAcc::get()->getFLD_MercenariesConfigValue(MERCENARIES_CONFIG_REWARD_ACHIEVMENT_RATIO);
  return getLevel() * REWARD_ACHIEVMENT_RATIO_PER_LEVEL + ratio;
}

bool GfDataMercenaries::getMsgTitleName(u8 *&bdat, u32 &textId, u32 mission) {
  if (mission == 0) {
    return false;
  }

  QuestID quest = getMissionQuestID(mission);
  return GfDataQuest::getTitle(bdat, textId, quest);
}

bool GfDataMercenaries::getMsgZoneName(u8 *&bdat, u32 &textId, u32 mission) {
  u32 map = getMissionMapID(mission);
  if (map == 0) {
    return false;
  }

  return GfDataMap::getName(bdat, textId, map);
}

bool GfDataMercenaries::getMsgSummaryName(u8 *&bdat, u32 &textId, u32 mission) {
  if (mission == 0) {
    return false;
  }

  QuestID quest = getMissionQuestID(mission);
  return GfDataQuest::getSummary(bdat, textId, quest);
}

bool GfDataMercenaries::getMsgTaskName(u8 *&bdat, u32 &textId, u32 mission, u32 index) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 purpose = getMissionPurposeID(mission);
  if (purpose == 0) {
    return false;
  }

  textId = questListAcc->getTaskTaskLog(purpose, index);
  bdat = GfBdatMsg::getFpQuest(getMissionQuestID(mission));
  return textId != 0;
}

bool GfDataMercenaries::getRequestBladeTextForDebug(mm::mtl::FixStr<128> &, const GfRequestBladeData &) { return false; }

bool GfDataMercenaries::isTeamMemberFill(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  for (u16 member : team->members) {
    if (member == 0) {
      return false;
    }
  }

  return true;
}

bool GfDataMercenaries::isTeamMemberEmpty(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  for (u16 member : team->members) {
    if (member != 0) {
      return false;
    }
  }

  return true;
}

u8 GfDataMercenaries::getTeamMemberNum(u32 teamID) {
  SDataMercenariesTeam *team = getTeamByTeamID(teamID);
  u8 memberNum = 0;
  for (u32 i = 0; i < 6; i++) {
    if (team->members[i] != 0) {
      memberNum++;
    }
  }

  return memberNum;
}

bool GfDataMercenaries::getRequestCondition(GfRequestBladeData &requestBladeData, u32 mission, u32 task) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 purpose = getMissionPurposeID(mission);
  if (task >= MISSION_TASK_COUNT || purpose == 0) {
    return false;
  }

  if (questListAcc->getTaskTaskType(purpose, task) != TASK_TYPE_REQUEST_BLADE) {
    return false;
  }

  u32 requestBlade = questListAcc->getTaskTaskID(purpose, task);
  if (requestBlade == 0) {
    return false;
  }

  requestBladeData.number = questListAcc->getRequestBladeRequestNumber(requestBlade);
  u32 category = questListAcc->getRequestBladeRequestCategory(requestBlade);
  if (category != 0) {
    requestBladeData.type = REQUEST_BLADE_CATEGORY;
    requestBladeData.target = category;
    return true;
  }

  u32 attribute = questListAcc->getRequestBladeRequestAtr(requestBlade);
  if (attribute != 0) {
    requestBladeData.type = REQUEST_BLADE_ATTRIBUTE;
    requestBladeData.target = attribute;
    return true;
  }

  u32 performance = questListAcc->getRequestBladeRequestPerformance(requestBlade);
  if (performance != 0) {
    requestBladeData.type = REQUEST_BLADE_PERFORMANCE;
    requestBladeData.level = performance;
    return true;
  }

  int race = questListAcc->getRequestBladeRequestRace(requestBlade);
  if (race != 0) {
    if (race > QUEST_RACE_ANIMAL) {
      race = QUEST_RACE_HUMAN;
    }

    requestBladeData.type = REQUEST_BLADE_RACE;
    requestBladeData.target = race;
    return true;
  }

  u32 gender = questListAcc->getRequestBladeRequestGender(requestBlade);
  if (gender != 0) {
    requestBladeData.type = REQUEST_BLADE_GENDER;
    requestBladeData.target = gender;
    return true;
  }

  u32 arts = questListAcc->getRequestBladeRequestArts(requestBlade);
  u32 artsLevel = questListAcc->getRequestBladeRequestArtsLevel(requestBlade);
  if (arts != 0) {
    requestBladeData.type = REQUEST_BLADE_ARTS;
    requestBladeData.target = arts;
    requestBladeData.level = artsLevel;
    return true;
  }

  u32 fieldSkill = questListAcc->getRequestBladeRequestFSkill(requestBlade);
  u32 fieldSkillLevel = questListAcc->getRequestBladeRequestFSLevel(requestBlade);
  if (fieldSkill == 0) {
    return false;
  }

  requestBladeData.type = REQUEST_BLADE_FIELD_SKILL;
  requestBladeData.target = fieldSkill;
  requestBladeData.level = fieldSkillLevel;
  return true;
}

void GfDataMercenaries::setFullEnableOrderMissionForDebug() {
  for (u32 mission = getStartMissionID(); mission < getEndMissionID(); mission++) {
    if (getMissionFlag(mission) == MISSION_STATE_NONE) {
      setMissionFlag(mission, MISSION_STATE_ORDER_ENABLE);
    }
  }

  setLevel(MERCENARIES_LEVEL_MAX);
}

u32 GfDataMercenaries::getBladeWithLeader(u32 mission) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID quest = toQuestID(questListAcc->getFLD_MercenariesMissionQuestID(mission));
  u32 purpose = questListAcc->getListPurposeID(GfDataQuest::getListNextQuestA(quest));
  for (u32 task = 0; task < MISSION_TASK_COUNT; task++) {
    u32 condition = questListAcc->getTaskTaskCondition(purpose, task);
    GfBdatCond *bdatCond = GfBdatCond::get();
    for (u32 index = 0; index < CONDITION_LIST_COUNT; index++) {
      if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_PARTY) {
        continue;
      }

      u32 partyCondition = bdatCond->getConditionListCondition(condition, index);
      if (bdatCond->getConditionPTCategory(partyCondition) != CONDITION_PARTY_CATEGORY_BLADE) {
        continue;
      }

      for (u32 member = 0; member < CONDITION_PARTY_MEMBER_COUNT; member++) {
        u32 blade = bdatCond->getConditionPTPCID(partyCondition, member);
        if (blade - BLADE_ID_FIRST < BLADE_COUNT) {
          return blade;
        }
      }
    }
  }

  return 0;
}

SDataMercenariesPreset *GfDataMercenaries::getPreset(u32 index) { return &GfDataManager::getDataGame()->mercenaries.presets[index]; }

} // namespace gf
