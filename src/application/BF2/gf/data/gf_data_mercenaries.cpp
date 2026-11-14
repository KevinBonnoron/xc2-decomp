#include "gf/data/gf_data_mercenaries.h"

#include <math.h>

#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrbl.h"
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
#include "gf/util/gf_util.h"
#include "mm_mtl/fixstr.h"

namespace gf {

enum {
  FLAG_MERCENARIES_UNKNOWN_2 = 0x2,        // Inferred role: flag mercenaries level; original name unknown.
  FLAG_MERCENARIES_UNKNOWN_3 = 0x3,        // Inferred role: flag mercenaries point; original name unknown.
  FLAG_MERCENARIES_UNKNOWN_5 = 0x5,        // Inferred role: flag mercenaries mission; original name unknown.
  FLAG_MERCENARIES_UNKNOWN_34767 = 0x87cf, // Inferred role: flag mercenaries mission progress; original name unknown.
  FLAG_MERCENARIES_UNKNOWN_35268 = 0x89c4, // Inferred role: flag mercenaries mission progress display; original name unknown.
  FLAG_MERCENARIES_UNKNOWN_39575 = 0x9a97, // Inferred role: flag mercenaries mission seen; original name unknown.
  FLAG_MERCENARIES_UNKNOWN_46285 = 0xb4cd, // Inferred role: flag mercenaries mission complete; original name unknown.
};

enum {
  MISSION_STATE_UNKNOWN_0 = 0, // Inferred role: mission state none; original name unknown.
  MISSION_STATE_UNKNOWN_1 = 1, // Inferred role: mission state order enable; original name unknown.
  MISSION_STATE_UNKNOWN_2 = 2, // Inferred role: mission state expedition; original name unknown.
  MISSION_STATE_UNKNOWN_3 = 3, // Inferred role: mission state reward; original name unknown.
  MISSION_STATE_UNKNOWN_4 = 4, // Inferred role: mission state complete; original name unknown.
};

enum {
  MERCENARIES_CONFIG_UNKNOWN_16 = 0x10, // Inferred role: mercenaries config reward achievment ratio; original name unknown.
  MERCENARIES_CONFIG_UNKNOWN_17 = 0x11, // Inferred role: mercenaries config mission performance ratio; original name unknown.
};

enum {
  WILDCARD_UNKNOWN_62 = 0x3e, // Inferred role: wildcard mercenaries point limit; original name unknown.
};

enum {
  REQUEST_UNKNOWN_4 = 4, // Inferred role: request gender any; original name unknown.
};

enum {
  REQUEST_BLADE_UNKNOWN_1 = 1, // Inferred role: request blade category; original name unknown.
  REQUEST_BLADE_UNKNOWN_2 = 2, // Inferred role: request blade performance; original name unknown.
  REQUEST_BLADE_UNKNOWN_3 = 3, // Inferred role: request blade race; original name unknown.
  REQUEST_BLADE_UNKNOWN_4 = 4, // Inferred role: request blade gender; original name unknown.
  REQUEST_BLADE_UNKNOWN_5 = 5, // Inferred role: request blade arts; original name unknown.
  REQUEST_BLADE_UNKNOWN_6 = 6, // Inferred role: request blade field skill; original name unknown.
  REQUEST_BLADE_UNKNOWN_7 = 7, // Inferred role: request blade attribute; original name unknown.
};

enum {
  CONDITION_UNKNOWN_4 = 4, // Inferred role: condition party category blade; original name unknown.
};

constexpr u32 CONDITION_UNKNOWN_3 = 3; // Inferred role: condition party member count; original name unknown.

constexpr u32 BLADE_UNKNOWN_3 = 3;       // Inferred role: blade arts count; original name unknown.
constexpr u32 BLADE_FIELD_UNKNOWN_3 = 3; // Inferred role: blade field skill count; original name unknown.

constexpr u32 RESERVER_UNKNOWN_24 = 24; // Inferred role: reserver per level; original name unknown.
constexpr u32 RESERVER_UNKNOWN_48 = 48; // Inferred role: reserver game clear bonus; original name unknown.
constexpr u32 LEVEL_UNKNOWN_5 = 5;      // Inferred role: reward achievment ratio per level; original name unknown.
constexpr u32 MISSION_UNKNOWN_4 = 4;    // Inferred role: mission task count; original name unknown.
constexpr u32 MISSION_UNKNOWN_3 = 3;    // Inferred role: mission field skill count; original name unknown.
constexpr f32 unknown025 = 6.0f;        // Inferred role: field skill time reduction per level; original name unknown.

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

u32 GfDataMercenaries::getReserverMax() { return getLevel() * RESERVER_UNKNOWN_24 + RESERVER_UNKNOWN_24 + (GfDataManager::getDataGame()->unknown109b2c != 0 ? RESERVER_UNKNOWN_48 : 0); }

unknown122 *GfDataMercenaries::getSDataMercenaries() { return &GfDataManager::getDataGame()->unknown1098c8; }

u32 GfDataMercenaries::getLevel() { return GfGameFlag::getLocal(4, FLAG_MERCENARIES_UNKNOWN_2); }

u32 GfDataMercenaries::getLevelMax() { return MERCENARIES_LEVEL_UNKNOWN_5; }

void GfDataMercenaries::setLevel(u32 level) { GfGameFlag::setLocal(4, FLAG_MERCENARIES_UNKNOWN_2, level); }

u32 GfDataMercenaries::getPoint() { return GfGameFlag::getLocal(16, FLAG_MERCENARIES_UNKNOWN_3); }

u32 GfDataMercenaries::getPointMax() {
  static const u16 unknown026[] = {0, 59, 60, 61, 62, 0}; // Inferred role: point max wildcards; original name unknown.
  u32 level = getLevel();
  if (level == 0 || level == MERCENARIES_LEVEL_UNKNOWN_5) {
    return 0;
  }

  return GfBdatBtl::get()->getWildcardDatavalueU2(unknown026[level]);
}

u32 GfDataMercenaries::getPointLimit() { return GfBdatBtl::get()->getWildcardDatavalueU2(WILDCARD_UNKNOWN_62); }

void GfDataMercenaries::setPoint(u32 point) { GfGameFlag::setLocal(16, FLAG_MERCENARIES_UNKNOWN_3, point); }

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

u32 GfDataMercenaries::getTeamNum() { return GfDataManager::getDataGame()->unknown1098c8.unknown00.size(); }

bool GfDataMercenaries::getReserver(mm::mtl::FixedVector<u16, 422> &reservers) {
  GfDataBlade::getListReserver(reservers);
  return !reservers.empty();
}

bool GfDataMercenaries::isValidTeamID(u32 teamID) { return getTeamByTeamID(teamID) != nullptr; }

unknown120 *GfDataMercenaries::getTeamByTeamID(u32 teamID) {
  mm::mtl::FixedVector<unknown120, 3> &mercenariesTeams = GfDataManager::getDataGame()->unknown1098c8.unknown00;
  for (unknown120 *team = mercenariesTeams.begin(); team != mercenariesTeams.end(); team++) {
    if (team->unknown10 == teamID) {
      return team;
    }
  }

  return nullptr;
}

u32 GfDataMercenaries::getTeamPower(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  u32 power = 0;
  for (u16 member : team->unknown00) {
    power += GfDataBlade::getBladePower(member);
  }

  return power;
}

bool GfDataMercenaries::decTeamMissionTime(u32 teamID, f32 time) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return false;
  }
  if (team->unknown1c.unknown00_0 == 0 && team->unknown1c.unknown00_6 == 0 && team->unknown1c.unknown01_4 == 0) {
    return false;
  }

  team->unknown18 += time;
  f32 elapsed = team->unknown18;
  u32 hour = elapsed / 3600.0f;
  elapsed = fmodf(elapsed, 3600.0f);
  u32 minute = elapsed / 60.0f;
  elapsed = fmodf(elapsed, 60.0f);
  u32 second = elapsed;
  team->unknown18 = fmodf(elapsed, 1.0f);
  ElapseTime elapseTime;
  elapseTime.unknown00_0 = second;
  elapseTime.unknown00_6 = minute;
  elapseTime.unknown01_4 = hour;
  ElapseTime before = team->unknown1c;
  team->unknown1c = team->unknown1c - elapseTime;
  bool isEnd = team->unknown1c.unknown00_0 == 0 && team->unknown1c.unknown00_6 == 0 && team->unknown1c.unknown01_4 == 0;
  bool isRemain = before.unknown00_0 != 0 || before.unknown00_6 != 0 || before.unknown01_4 != 0;
  return isRemain && isEnd;
}

int GfDataMercenaries::getTeamMaleNum(u32 teamID) {
  unknown120 *team = getTeamMember(teamID);
  if (team == nullptr) {
    return 0;
  }

  int num = 0;
  for (u16 member : team->unknown00) {
    if (GfDataBlade::isMale(member)) {
      num++;
    }
  }

  return num;
}

int GfDataMercenaries::getTeamFemaleNum(u32 teamID) {
  unknown120 *team = getTeamMember(teamID);
  if (team == nullptr) {
    return 0;
  }

  int num = 0;
  for (u16 member : team->unknown00) {
    if (GfDataBlade::isFemale(member)) {
      num++;
    }
  }

  return num;
}

u32 GfDataMercenaries::getTeamID(u32 blade) {
  for (unknown120 &team : GfDataManager::getDataGame()->unknown1098c8.unknown00) {
    for (u16 member : team.unknown00) {
      if (member == blade) {
        return team.unknown10;
      }
    }
  }

  return 0;
}

u32 GfDataMercenaries::getMissionIdByBlade(u32 blade) {
  for (unknown120 &team : GfDataManager::getDataGame()->unknown1098c8.unknown00) {
    for (u16 member : team.unknown00) {
      if (member == blade) {
        return team.unknown14;
      }
    }
  }

  return 0;
}

unknown120 *GfDataMercenaries::getTeamByIndex(u32 index) { return &GfDataManager::getDataGame()->unknown1098c8.unknown00[index]; }

unknown120 *GfDataMercenaries::getTeamByMissionID(u32 mission) {
  if (mission == 0) {
    return nullptr;
  }

  for (unknown120 &team : GfDataManager::getDataGame()->unknown1098c8.unknown00) {
    if (team.unknown14 == mission) {
      return &team;
    }
  }

  return nullptr;
}

u32 GfDataMercenaries::getTeamIDByMissionID(u32 mission) {
  unknown120 *team = getTeamByMissionID(mission);
  if (team == nullptr) {
    return 0;
  }

  return team->unknown10;
}

unknown120 *GfDataMercenaries::getTeamMember(u32 teamID) { return getTeamByTeamID(teamID); }

int GfDataMercenaries::getTeamAnimalNum(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  int animalNum = 0;
  for (u32 i = 0; i < 6; i++) {
    if (team->unknown00[i] != 0 && GfDataBlade::getSDataBlade(team->unknown00[i]).unknown846 == QUEST_RACE_UNKNOWN_2) {
      animalNum++;
    }
  }

  return animalNum;
}

bool GfDataMercenaries::getTeamByZoneMissionWorking(mm::mtl::FixedVector<u16, 3> &teams, u32 zone) {
  mm::mtl::FixedVector<unknown120, 3> &mercenariesTeams = GfDataManager::getDataGame()->unknown1098c8.unknown00;
  for (unknown120 *team = mercenariesTeams.begin(); team != mercenariesTeams.end(); team++) {
    if (team->unknown14 != 0 && GfGameFlag::getLocal(4, FLAG_MERCENARIES_UNKNOWN_5 + team->unknown14) == MISSION_STATE_UNKNOWN_2) {
      u32 map = getMissionMapID(team->unknown14);
      if (map != 0 && GfDataMap::getZoneIdForGameMap(map) == zone) {
        teams.push_back(team->unknown10);
      }
    }
  }

  return !teams.empty();
}

u32 GfDataMercenaries::getMissionByQuestID(QuestID quest) {
  for (u32 mission = getStartMissionID(); mission < getEndMissionID(); mission++) {
    if (quest == getMissionQuestID(mission)) {
      return mission;
    }
  }

  return 0;
}

u32 GfDataMercenaries::getMissionFlag(u32 mission) {
  if (mission == 0) {
    return 0;
  }

  return GfGameFlag::getLocal(4, FLAG_MERCENARIES_UNKNOWN_5 + mission);
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
  if (GfDataMap::isArcadiaDestroy() && map == MAP_UNKNOWN_12) {
    return MAP_UNKNOWN_14;
  }

  return map;
}

bool GfDataMercenaries::isTeamStateReward(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr || team->unknown14 == 0) {
    return false;
  }

  return GfGameFlag::getLocal(4, FLAG_MERCENARIES_UNKNOWN_5 + team->unknown14) == MISSION_STATE_UNKNOWN_3;
}

bool GfDataMercenaries::getTeamByZoneMissionComplete(mm::mtl::FixedVector<u16, 3> &teams, u32 zone) {
  mm::mtl::FixedVector<unknown120, 3> &mercenariesTeams = GfDataManager::getDataGame()->unknown1098c8.unknown00;
  for (unknown120 *team = mercenariesTeams.begin(); team != mercenariesTeams.end(); team++) {
    if (isTeamStateReward(team->unknown10)) {
      u32 map = getMissionMapID(team->unknown14);
      if (map != 0 && GfDataMap::getZoneIdForGameMap(map) == zone) {
        teams.push_back(team->unknown10);
      }
    }
  }

  return !teams.empty();
}

void GfDataMercenaries::setMissionFlag(u32 mission, u32 missionFlag) {
  GfGameFlag::setLocal(4, FLAG_MERCENARIES_UNKNOWN_5 + mission, missionFlag);
  int progress = GfGameFlag::getLocal(2, FLAG_MERCENARIES_UNKNOWN_34767 + mission);
  if (progress >= 2) {
    return;
  }

  int newProgress;
  switch (missionFlag) {
  case MISSION_STATE_UNKNOWN_2:
    newProgress = 1;
    break;
  case MISSION_STATE_UNKNOWN_3:
    newProgress = 1;
    break;
  case MISSION_STATE_UNKNOWN_4:
    newProgress = 2;
    break;
  default:
    newProgress = 0;
    break;
  }

  if (progress != newProgress) {
    GfGameFlag::setLocal(2, FLAG_MERCENARIES_UNKNOWN_34767 + mission, newProgress);
    GfGameFlag::setLocal(2, FLAG_MERCENARIES_UNKNOWN_35268 + mission, newProgress);
  }
}

bool GfDataMercenaries::isMissionCompleteFlag(u32 mission) { return GfGameFlag::getLocal(1, FLAG_MERCENARIES_UNKNOWN_46285 + mission) != 0; }

void GfDataMercenaries::setMissionCompleteFlag(u32 mission) { GfGameFlag::setLocal(1, FLAG_MERCENARIES_UNKNOWN_46285 + mission, 1); }

u32 GfDataMercenaries::getRequestPerformance(u32 mission) { return QuestListAcc::get()->getFLD_MercenariesMissionRequestPerformance(mission); }

u32 GfDataMercenaries::getTeamMissionTime(u32 teamID, u32 mission) {
  u32 missionTime = getMissionTime(mission);
  if (missionTime == 0) {
    return missionTime;
  }

  f32 time = missionTime;
  unknown120 *team = getTeamByTeamID(teamID);
  if (team != nullptr) {
    f32 fieldSkillLevel = 0.0f;
    for (u32 index = 0; index < MISSION_UNKNOWN_3; index++) {
      u32 fieldSkill = getFieldSkill(mission, index);
      if (fieldSkill == 0) {
        continue;
      }

      for (u16 member : team->unknown00) {
        if (member == 0) {
          continue;
        }

        fieldSkillLevel += getBladeFieldSkillLevel(member, fieldSkill);
      }
    }

    f32 reducedTime = time * (fieldSkillLevel * -unknown025 + 100.0f) * 0.01f;
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

f32 GfDataMercenaries::getMissionPerformanceRatio() { return QuestListAcc::get()->getFLD_MercenariesConfigValue(MERCENARIES_CONFIG_UNKNOWN_17) * 0.01f + 0.001f; }

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
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  return team->unknown14;
}

ElapseTime GfDataMercenaries::getTeamMissionTime(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    ElapseTime none = {};
    return none;
  }

  return team->unknown1c;
}

ElapseTime GfDataMercenaries::getTeamMissionTimeOriginal(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    ElapseTime none = {};
    return none;
  }

  return team->unknown20;
}

bool GfDataMercenaries::isTeamStateEmpty(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return true;
  }

  return team->unknown14 == 0;
}

bool GfDataMercenaries::isTeamStateExpedition(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr || team->unknown14 == 0) {
    return false;
  }

  return GfGameFlag::getLocal(4, FLAG_MERCENARIES_UNKNOWN_5 + team->unknown14) == MISSION_STATE_UNKNOWN_2;
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
  for (u32 index = 0; index < MISSION_UNKNOWN_4; index++) {
    u32 type = getMissionTaskType(mission, index);
    if (type != TASK_TYPE_UNKNOWN_9) {
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
  unknown120 *team = getTeamByMissionID(mission);
  if (team == nullptr) {
    return false;
  }

  return team->unknown10 != 0;
}

bool GfDataMercenaries::isMissionComplete(u32 mission) {
  bool complete = false;
  if (mission != 0) {
    complete = GfGameFlag::getLocal(4, FLAG_MERCENARIES_UNKNOWN_5 + mission) == MISSION_STATE_UNKNOWN_4;
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
  if (gender != 0 && gender != REQUEST_UNKNOWN_4 && gender != paramAcc.getGender()) {
    return false;
  }

  u32 arts = questListAcc->getRequestBladeRequestArts(requestBlade);
  if (arts != 0) {
    u32 index = 0;
    while (paramAcc.getBladeArts(index, false) != arts) {
      index++;
      if (index >= BLADE_UNKNOWN_3) {
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
    for (u32 index = 0; index < BLADE_FIELD_UNKNOWN_3; index++) {
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

u32 GfDataMercenaries::getTeamLeader(u32 teamID) {
  if (teamID == 0) {
    return 0;
  }

  unknown120 *team = getTeamByTeamID(teamID);
  if (team == nullptr) {
    return 0;
  }

  return team->unknown00[0];
}

bool GfDataMercenaries::isEnableOrder(u32 mission) {
  if (mission == 0) {
    return true;
  }

  u32 missionFlag = GfGameFlag::getLocal(4, FLAG_MERCENARIES_UNKNOWN_5 + mission);
  if (missionFlag == MISSION_STATE_UNKNOWN_0) {
    return true;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  if (missionFlag == MISSION_STATE_UNKNOWN_4) {
    return questListAcc->getFLD_MercenariesMissionRepeatable(mission) != 0;
  }

  return false;
}

bool GfDataMercenaries::isNewMission(u32 mission) { return GfGameFlag::getLocal(1, FLAG_MERCENARIES_UNKNOWN_39575 + mission) == 0; }

void GfDataMercenaries::clearNewMission(u32 mission) { GfGameFlag::setLocal(1, FLAG_MERCENARIES_UNKNOWN_39575 + mission, 1); }

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
  u32 ratio = QuestListAcc::get()->getFLD_MercenariesConfigValue(MERCENARIES_CONFIG_UNKNOWN_16);
  return getLevel() * LEVEL_UNKNOWN_5 + ratio;
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
  unknown120 *team = getTeamByTeamID(teamID);
  for (u16 member : team->unknown00) {
    if (member == 0) {
      return false;
    }
  }

  return true;
}

bool GfDataMercenaries::isTeamMemberEmpty(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  for (u16 member : team->unknown00) {
    if (member != 0) {
      return false;
    }
  }

  return true;
}

bool GfDataMercenaries::getTeamNameByTeamIDForDebug(mm::mtl::FixStr<128> &name, u32 teamID) {
  if (teamID != 0) {
    unknown120 *team = getTeamByTeamID(teamID);
    if (team != nullptr) {
      u16 leader = team->unknown00[0];
      if (leader != 0) {
        name = "";
        if (!GfDataBlade::isCommonBlade(leader)) {
          u32 textId = GfBdatChrBl::get()->getChrBlMerceName(leader);
          u8 *bdat = GfBdatMsg::getFpMerceName();
          if (textId != 0) {
            const char *text = Bdat::getMSText(bdat, textId);
            if (text != nullptr) {
              name = util::debugUTF8ToSJIS(text);
            }
          }
        }

        if (name.length() == 0) {
          name.format("%s隊", util::debugUTF8ToSJIS(GfDataBlade::getName(leader, 0)));
        }

        return true;
      }
    }
  }

  name.format("第%d傭兵部隊", teamID);
  return true;
}

u8 GfDataMercenaries::getTeamMemberNum(u32 teamID) {
  unknown120 *team = getTeamByTeamID(teamID);
  u8 memberNum = 0;
  for (u32 i = 0; i < 6; i++) {
    if (team->unknown00[i] != 0) {
      memberNum++;
    }
  }

  return memberNum;
}

bool GfDataMercenaries::getRequestCondition(GfRequestBladeData &requestBladeData, u32 mission, u32 task) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 purpose = getMissionPurposeID(mission);
  if (task >= MISSION_UNKNOWN_4 || purpose == 0) {
    return false;
  }

  if (questListAcc->getTaskTaskType(purpose, task) != TASK_TYPE_UNKNOWN_9) {
    return false;
  }

  u32 requestBlade = questListAcc->getTaskTaskID(purpose, task);
  if (requestBlade == 0) {
    return false;
  }

  requestBladeData.unknown0c = questListAcc->getRequestBladeRequestNumber(requestBlade);
  u32 category = questListAcc->getRequestBladeRequestCategory(requestBlade);
  if (category != 0) {
    requestBladeData.unknown00 = REQUEST_BLADE_UNKNOWN_1;
    requestBladeData.unknown04 = category;
    return true;
  }

  u32 attribute = questListAcc->getRequestBladeRequestAtr(requestBlade);
  if (attribute != 0) {
    requestBladeData.unknown00 = REQUEST_BLADE_UNKNOWN_7;
    requestBladeData.unknown04 = attribute;
    return true;
  }

  u32 performance = questListAcc->getRequestBladeRequestPerformance(requestBlade);
  if (performance != 0) {
    requestBladeData.unknown00 = REQUEST_BLADE_UNKNOWN_2;
    requestBladeData.unknown08 = performance;
    return true;
  }

  int race = questListAcc->getRequestBladeRequestRace(requestBlade);
  if (race != 0) {
    if (race > QUEST_RACE_UNKNOWN_2) {
      race = QUEST_RACE_UNKNOWN_1;
    }

    requestBladeData.unknown00 = REQUEST_BLADE_UNKNOWN_3;
    requestBladeData.unknown04 = race;
    return true;
  }

  u32 gender = questListAcc->getRequestBladeRequestGender(requestBlade);
  if (gender != 0) {
    requestBladeData.unknown00 = REQUEST_BLADE_UNKNOWN_4;
    requestBladeData.unknown04 = gender;
    return true;
  }

  u32 arts = questListAcc->getRequestBladeRequestArts(requestBlade);
  u32 artsLevel = questListAcc->getRequestBladeRequestArtsLevel(requestBlade);
  if (arts != 0) {
    requestBladeData.unknown00 = REQUEST_BLADE_UNKNOWN_5;
    requestBladeData.unknown04 = arts;
    requestBladeData.unknown08 = artsLevel;
    return true;
  }

  u32 fieldSkill = questListAcc->getRequestBladeRequestFSkill(requestBlade);
  u32 fieldSkillLevel = questListAcc->getRequestBladeRequestFSLevel(requestBlade);
  if (fieldSkill == 0) {
    return false;
  }

  requestBladeData.unknown00 = REQUEST_BLADE_UNKNOWN_6;
  requestBladeData.unknown04 = fieldSkill;
  requestBladeData.unknown08 = fieldSkillLevel;
  return true;
}

void GfDataMercenaries::setFullEnableOrderMissionForDebug() {
  for (u32 mission = getStartMissionID(); mission < getEndMissionID(); mission++) {
    if (getMissionFlag(mission) == MISSION_STATE_UNKNOWN_0) {
      setMissionFlag(mission, MISSION_STATE_UNKNOWN_1);
    }
  }

  setLevel(MERCENARIES_LEVEL_UNKNOWN_5);
}

u32 GfDataMercenaries::getBladeWithLeader(u32 mission) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID quest = toQuestID(questListAcc->getFLD_MercenariesMissionQuestID(mission));
  u32 purpose = questListAcc->getListPurposeID(GfDataQuest::getListNextQuestA(quest));
  for (u32 task = 0; task < MISSION_UNKNOWN_4; task++) {
    u32 condition = questListAcc->getTaskTaskCondition(purpose, task);
    GfBdatCond *bdatCond = GfBdatCond::get();
    for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
      if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_UNKNOWN_6) {
        continue;
      }

      u32 partyCondition = bdatCond->getConditionListCondition(condition, index);
      if (bdatCond->getConditionPTCategory(partyCondition) != CONDITION_UNKNOWN_4) {
        continue;
      }

      for (u32 member = 0; member < CONDITION_UNKNOWN_3; member++) {
        u32 blade = bdatCond->getConditionPTPCID(partyCondition, member);
        if (blade - BLADE_ID_UNKNOWN_1001 < BLADE_UNKNOWN_422) {
          return blade;
        }
      }
    }
  }

  return 0;
}

unknown121 *GfDataMercenaries::getPreset(u32 index) { return &GfDataManager::getDataGame()->unknown1098c8.unknown80[index]; }

} // namespace gf
