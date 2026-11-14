#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "fw/fw_update_info.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "mm_mtl/fixed_array.h"

namespace gf {

// Inferred role: FLD_MercenariesConfig row before the reward bonus of mercenaries level 1; original name unknown.
constexpr u32 unknown001 = 10;

// Inferred role: reward bonus percent of the current mercenaries level; original name unknown.
static f32 unknown002() {
  f32 ratio = 0.0f;
  u32 level = GfDataMercenaries::getLevel();
  if (level != 0) {
    ratio = QuestListAcc::get()->getFLD_MercenariesConfigValue(level + unknown001);
  }
  return ratio;
}

// Inferred role: mission flag argument of getMission that selects every mission; original name unknown.
constexpr u32 unknown003 = 5;

GfGameMercenaries::GfGameMercenaries(const GfSetupParam &param) : unknown08(false), unknown788(false) { initialize(param); }

void GfGameMercenaries::initialize(const GfSetupParam &) {
  rebuildAutoStartList();
  unknown08 = true;
}

GfGameMercenaries::~GfGameMercenaries() {}

void GfGameMercenaries::build(const GfSetupParam &param) {
  // __LINE__ must be 72 as in the original file: its value changes the instruction order.
#line 72
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameMercenaries(param);
}

void GfGameMercenaries::destroy() {
  GfGameMercenaries *mercenaries = get();
  mercenaries->finalize();
  delete mercenaries;
}

void GfGameMercenaries::finalize() { unknown08 = false; }

bool GfGameMercenaries::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
  }
  return false;
}

void GfGameMercenaries::update(const fw::UpdateInfo &info) { get()->updateMercenariesTeam(info); }

void GfGameMercenaries::updateMercenariesTeam(const fw::UpdateInfo &info) {
  u32 teamNum = GfDataMercenaries::getTeamNum();
  u32 teamMax = GfDataMercenaries::getTeamMax();
  if (teamNum < teamMax) {
    for (u32 i = 0; i < teamMax - teamNum; i++) {
      GfDataMercenaries::addTeam();
    }
  }
  if (!GfGameManager::isStartGame() && !unknown788) {
    mm::mtl::FixedVector<u16, 3> teams;
    getTeam(teams);
    for (u16 teamID : teams) {
      GfDataMercenaries::decTeamMissionTime(teamID, info.unknown00);
    }
  }
  checkTeamMissionComplete();
}

void GfGameMercenaries::checkTeamMissionComplete() {
  mm::mtl::FixedVector<u16, 3> teams;
  getTeam(teams);
  for (const u16 &teamID : teams) {
    unknown120 *team = GfDataMercenaries::getTeamByTeamID(teamID);
    u32 mission = GfDataMercenaries::getTeamMission(teamID);
    if (team->_24 || GfDataMercenaries::getMissionTime(mission) != 0) {
      ElapseTime time = GfDataMercenaries::getTeamMissionTime(teamID);
      if (GfDataMercenaries::getMissionFlag(mission) == 2 && ((time.unknown00_0 == 0 && time.unknown00_6 == 0 && time.unknown01_4 == 0) || team->_24)) {
        team->_24 = false;
        setMissionComplete(mission);
        if (GfDataMercenaries::getTeamLeader(teamID) != 0) {
          SCOM_POPUP::createMercenaryReturn(GfDataMercenaries::getMissionMapID(mission), teamID);
        }
      }
    }
  }
}

void GfGameMercenaries::rebuildAutoStartList() {
  unknown380.clear();
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 mission = questListAcc->getFLD_MercenariesMissionStart();
  u32 end = questListAcc->getFLD_MercenariesMissionEnd();
  for (; mission < end; mission++) {
    if (questListAcc->getFLD_MercenariesMissionAutoStart(mission) != 0) {
      unknown380.push_back(mission);
    }
  }
}

void GfGameMercenaries::findMemberForMission(u16 blade) {
  GfGameMercenaries *mercenaries = get();
  if (GfDataMercenaries::isEnableMissionBlade(blade, mercenaries->unknown378)) {
    mercenaries->unknown10.push_back(blade);
  }
}

void GfGameMercenaries::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_UNKNOWN_7 && get() != nullptr) {
    get()->unknown788 = false;
  }
}

void GfGameMercenaries::stopMissionTime(bool isStop) {
  if (get() != nullptr) {
    get()->unknown788 = isStop;
  }
}

u32 GfGameMercenaries::getMissionFlag(u32 mission) { return GfDataMercenaries::getMissionFlag(mission); }

void GfGameMercenaries::setLevel(u32 level) {
  GfDataMercenaries::getLevel();
  if (level > GfDataMercenaries::getLevelMax()) {
    level = GfDataMercenaries::getLevelMax();
  }
  GfDataMercenaries::setLevel(level);
}

void GfGameMercenaries::addPoint(u32 point) {
  if (GfDataMercenaries::getLevel() != 0 && GfDataMercenaries::getLevel() < 5) {
    u32 current = GfDataMercenaries::getPoint();
    point += current;
    u32 limit = GfDataMercenaries::getPointLimit();
    if (point > limit) {
      point = limit;
    }
    if (point != current) {
      GfDataMercenaries::setPoint(point);
    }
  }
}

void GfGameMercenaries::setMissionCompleteForce(u32 mission) {
  unknown120 *team = GfDataMercenaries::getTeamByMissionID(mission);
  if (team != nullptr) {
    team->unknown1c = ElapseTime();
    team->unknown20 = ElapseTime();
    team->_24 = true;
  }
}

void GfGameMercenaries::setMissionTimeForDebug(u32 mission, u32 time) {
  unknown120 *team = GfDataMercenaries::getTeamByMissionID(mission);
  if (team != nullptr && (team->unknown1c.unknown00_0 != 0 || team->unknown1c.unknown00_6 != 0 || team->unknown1c.unknown01_4 != 0)) {
    ElapseTime elapseTime = ElapseTime();
    elapseTime.unknown00_0 = time;
    team->unknown1c = elapseTime;
  }
}

bool GfGameMercenaries::isAddTeamMember(u32 team) {
  unknown120 *members = GfDataMercenaries::getTeamMember(team);
  for (u32 i = 0; i < 6; i++) {
    if (members->unknown00[i] == 0) {
      return true;
    }
  }
  return false;
}

bool GfGameMercenaries::isCompleteMission() {
  for (u32 mission = GfDataMercenaries::getStartMissionID(); mission < GfDataMercenaries::getEndMissionID(); mission++) {
    if (GfDataMercenaries::getMissionFlag(mission) == 3) {
      return true;
    }
  }
  return false;
}

bool GfGameMercenaries::orderMission(u32 mission) {
  if (GfDataMercenaries::getMissionFlag(mission) == 1) {
    QuestID quest = GfDataMercenaries::getMissionQuestID(mission);
    if (!quest.empty()) {
      GfQuestManager::resetQuest(quest);
      GfQuestManager::openOrder(quest, false);
      GfDataMercenaries::clearNewMission(mission);
      return true;
    }
  }
  return false;
}

bool GfGameMercenaries::orderMission(u32 teamID, u32 mission) {
  unknown120 *team = GfDataMercenaries::getTeamByTeamID(teamID);
  if (team != nullptr && GfDataMercenaries::getMissionFlag(mission) == 1) {
    u32 time = GfDataMercenaries::getTeamMissionTime(team->unknown10, mission);
    ElapseTime elapseTime;
    elapseTime.unknown00_0 = 0;
    elapseTime.unknown01_4 = time / 60;
    elapseTime.unknown00_6 = time % 60;
    QuestID quest = GfDataMercenaries::getMissionQuestID(mission);
    if (!quest.empty()) {
      team->unknown14 = mission;
      team->unknown0c = quest;
      team->unknown1c = elapseTime;
      team->unknown20 = elapseTime;
      team->unknown18 = 0.0f;
      GfDataMercenaries::clearNewMission(mission);
      setMissionFlag(mission, 2);
      return true;
    }
  }
  return false;
}

bool GfGameMercenaries::addTeamMember(u32 team, u32 blade) {
  unknown120 *members = GfDataMercenaries::getTeamMember(team);
  for (u32 i = 0; i < 6; i++) {
    if (members->unknown00[i] == 0) {
      members->unknown00[i] = blade;
      GfGameUtil::execActivateMercenaryTeamForBlade(blade);
      GfEvent::callMercenariesTeam(team);
      return true;
    }
  }
  return false;
}

bool GfGameMercenaries::isRemoveTeamMember(u32 team, u32 blade) {
  if (blade != 0) {
    unknown120 *members = GfDataMercenaries::getTeamMember(team);
    for (u32 i = 0; i < 6; i++) {
      if (members->unknown00[i] == blade) {
        return GfDataMercenaries::getReserverNum() < GfDataMercenaries::getReserverMax();
      }
    }
  }
  return false;
}

bool GfGameMercenaries::removeTeamMember(u32 blade) {
  u32 teamID = GfDataMercenaries::getTeamID(blade);
  unknown120 *members = GfDataMercenaries::getTeamMember(teamID);
  for (u32 i = 0; i < 6; i++) {
    if (members->unknown00[i] == blade) {
      members->unknown00[i] = 0;
      GfGameUtil::execActivateReserverForBlade(blade);
      for (; i < 5; i++) {
        members->unknown00[i] = members->unknown00[i + 1];
      }
      members->unknown00[5] = 0;
      u32 mission = GfDataMercenaries::getTeamMission(teamID);
      if (GfDataMercenaries::isTeamMemberEmpty(teamID) && mission != 0) {
        cancelMission(mission);
      }
      GfEvent::callMercenariesTeam(teamID);
      return true;
    }
  }
  return false;
}

void GfGameMercenaries::clearTeamMember(u32 team) {
  unknown120 *members = GfDataMercenaries::getTeamMember(team);
  if (members != nullptr) {
    for (u32 i = 0; i < 6; i++) {
      if (members->unknown00[i] != 0) {
        GfGameUtil::execActivateReserverForBlade(members->unknown00[i]);
        members->unknown00[i] = 0;
      }
    }
  }
}

void GfGameMercenaries::setMissionComplete(u32 mission) {
  GfDataMercenaries::getMissionFlag(mission);
  setMissionFlag(mission, 3);
  if (GfDataMercenaries::getMissionTaskType(mission) == 2) {
    setMissionFlag(mission, 4);
  }
}

void GfGameMercenaries::setMissionFlag(u32 mission, u32 missionFlag) {
  u32 previous = GfDataMercenaries::getMissionFlag(mission);
  GfDataMercenaries::setMissionFlag(mission, missionFlag);
  if (missionFlag == 1 && previous == 0) {
    u8 *bdat;
    u32 textId;
    GfDataQuest::getTitle(bdat, textId, GfDataMercenaries::getMissionQuestID(mission));
  } else if (missionFlag == 4 && !GfDataMercenaries::isMissionCompleteFlag(mission)) {
    GfDataMercenaries::setMissionCompleteFlag(mission);
  }
  GfEvent::callMercenariesMissionFlag(mission, missionFlag, previous);
}

void GfGameMercenaries::applyCompleteMission(const QuestCompleteParam &param) {
  u32 mission = GfDataMercenaries::getMissionByQuestID(param.unknown04);
  if (mission != 0 && GfDataMercenaries::getMissionFlag(mission) == 2) {
    setMissionComplete(mission);
  }
}

void GfGameMercenaries::qevOrderQuest(const QuestOrderParam &param) {
  u32 mission = GfDataMercenaries::getMissionByQuestID(param.unknown04);
  if (mission != 0 && GfDataMercenaries::getMissionFlag(mission) == 1) {
    setMissionFlag(mission, 2);
  }
}

void GfGameMercenaries::gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value) {
  if (flag == 1 && value == 0) {
    SCOM_POPUP::createMercenaryAdd(mission);
  }
}

bool GfGameMercenaries::isTeamEnableMission(u32 teamID, u32 mission) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (GfDataMercenaries::isValidTeamID(teamID)) {
    unknown120 *members = GfDataMercenaries::getTeamMember(teamID);
    u32 purpose = GfDataMercenaries::getMissionPurposeID(mission);
    if (purpose != 0) {
      u32 state = 1;
      if (questListAcc->getTaskPreCondition(purpose) != 0) {
        state = 4;
      }
      for (u32 task = 0; task < QUEST_UNKNOWN_4; task++) {
        u32 current = state;
        if (GfQuestTask::isEnableTaskCondition(QuestTaskParam(QuestID(), task, purpose, TASK_STATE_UNKNOWN_0))) {
          if (questListAcc->getTaskTaskType(purpose, task) == 0) {
            continue;
          }
          if (questListAcc->getTaskTaskType(purpose, task) == TASK_TYPE_UNKNOWN_9) {
            u32 request = questListAcc->getTaskTaskID(purpose, task);
            if (request == 0 || questListAcc->getRequestBladeRequestNumber(request) == 0) {
              continue;
            }
            u32 count = 0;
            for (u32 i = 0; i < 6; i++) {
              if (GfDataMercenaries::isEnableMissionBlade(members->unknown00[i], request)) {
                count++;
              }
            }
            if (count != 0 && questListAcc->getRequestBladeRequestNumber(request) <= count) {
              current = 0;
            }
          }
        }
        if (current != 0 && current != 4) {
          return false;
        }
      }
      return !GfDataMercenaries::isTeamMemberEmpty(teamID);
    }
  }
  return false;
}

void GfGameMercenaries::updateMissionAutoStart() {
  GfGameMercenaries *mercenaries = get();
  if (mercenaries != nullptr) {
    QuestListAcc *questListAcc = QuestListAcc::get();
    for (const u16 &mission : mercenaries->unknown380) {
      u32 flag = GfDataMercenaries::getMissionFlag(mission);
      if ((flag == 0 || flag > 3) && (flag != 4 || questListAcc->getFLD_MercenariesMissionRepeatable(mission) != 0)) {
        if (GfGameCond::isGameCond(questListAcc->getFLD_MercenariesMissionAutoStart(mission))) {
          setMissionFlag(mission, 1);
        }
      }
    }
  }
}

bool GfGameMercenaries::isQuestMission(QuestID quest) {
  for (u32 mission = GfDataMercenaries::getStartMissionID(); mission < GfDataMercenaries::getEndMissionID(); mission++) {
    if (quest == GfDataMercenaries::getMissionQuestID(mission)) {
      return GfDataMercenaries::getMissionFlag(mission) != 0;
    }
  }
  return false;
}

void GfGameMercenaries::execMissionReward(u32 mission) {
  if (GfDataMercenaries::getMissionFlag(mission) != 3) {
    return;
  }

  unknown120 *team = GfDataMercenaries::getTeamByMissionID(mission);
  u32 gold = getRewardGold(mission, false);
  if (gold != 0) {
    SCOM_ADD_MONEY::create(gold);
  }
  u32 exp = getRewardExp(mission, false);
  if (exp != 0) {
    SCOM_ADD_EXP::createInnExp(exp);
  }
  u32 develop = getRewardDevelop(mission, false);
  if (develop != 0) {
    SCOM_ADD_DEVELOP::create(getRewardDevelopZone(mission), develop);
  }
  u32 trust = getRewardTrust(mission);
  if (trust != 0) {
    for (u32 i = 0; i < 6; i++) {
      if (team->unknown00[i] != 0) {
        SCOM_ADD_TRUST::create(team->unknown00[i], trust);
      }
    }
  }
  u16 ideaPoint = getRewardIdeaPoint(mission);
  if (ideaPoint != 0) {
    SCOM_ADD_IDEA::create(unknown020, getRewardIdeaType(mission), ideaPoint);
  }
  {
    GfQuestReward reward;
    if (GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false) && reward.unknown00[QUEST_REWARD_UNKNOWN_7].unknown44 != 0) {
      SCOM_ADD_MERCENARIES_POINT::create(reward.unknown00[QUEST_REWARD_UNKNOWN_7].unknown44);
    }
  }
  {
    GfQuestReward reward;
    if (GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
      for (u32 i = QUEST_REWARD_UNKNOWN_8; i < sizeof(reward.unknown00) / sizeof(reward.unknown00[0]); i++) {
        if (reward.unknown00[i].unknown44 != 0) {
          SCOM_ADD_ITEM::create(reward.unknown00[i].unknown44, reward.unknown00[i].m_developZone);
        }
      }
    }
  }
  execMissionRewardAchievementBonusForBlade(mission);
  execMissionAchievementForBlade(mission);
  if (team != nullptr) {
    team->unknown14 = 0;
    team->unknown0c = toQuestID(0);
  }
  setMissionFlag(mission, 4);
  GfQuestManager::requestOrderAchievementQuestForce();
  GfQuestManager::requestOrderQuestForce();
}

bool GfGameMercenaries::getTeam(mm::mtl::FixedVector<u16, 3> &teams) {
  teams.clear();
  for (u32 i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
    teams.push_back(GfDataMercenaries::getTeamByIndex(i)->unknown10);
  }
  return !teams.empty();
}

void GfGameMercenaries::execMissionRewardByTeamID(u32 team) {
  execMissionReward(GfDataMercenaries::getTeamMission(team));
  GfQuestManager::requestOrderAchievementQuestForce();
}

u32 GfGameMercenaries::getRewardGold(u32 mission, bool) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  u32 gold = isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_0].unknown44_u32 : 0;
  return gold + getRewardGoldHosei(mission, false);
}

u32 GfGameMercenaries::getRewardExp(u32 mission, bool) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  u32 exp = isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_3].unknown44_u32 : 0;
  return static_cast<u32>(exp * unknown002() * 0.01f) + exp;
}

u32 GfGameMercenaries::getRewardDevelop(u32 mission, bool) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  u32 develop = isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_4].unknown44 : 0;
  return develop + getRewardDevelopHosei(mission, false);
}

u32 GfGameMercenaries::getRewardDevelopZone(u32 mission) {
  GfQuestReward reward;
  u16 zone = 0;
  if (GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
    zone = reward.unknown00[QUEST_REWARD_UNKNOWN_4].getDevelopZone();
  }
  return zone;
}

u32 GfGameMercenaries::getRewardTrust(u32 mission) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  return isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_5].unknown44 : 0;
}

u32 GfGameMercenaries::getRewardMercenariesPoint(u32 mission) {
  GfQuestReward reward;
  u32 point = 0;
  if (GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
    point = reward.unknown00[QUEST_REWARD_UNKNOWN_7].unknown44;
  }
  return point;
}

u16 GfGameMercenaries::getRewardIdeaPoint(u32 mission) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  return isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_6].unknown44 : 0;
}

u16 GfGameMercenaries::getRewardIdeaType(u32 mission) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  return isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_6].m_developZone : 0;
}

u32 GfGameMercenaries::getRewardGoldHosei(u32 mission, bool) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  f32 gold = isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_0].unknown44_u32 : 0;
  return gold * unknown002() * 0.01f;
}

u32 GfGameMercenaries::getRewardDevelopHosei(u32 mission, bool) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  f32 develop = isValid ? reward.unknown00[QUEST_REWARD_UNKNOWN_4].unknown44 : 0;
  return develop * unknown002() * 0.01f;
}

u32 GfGameMercenaries::getRewardFSkillHosei(u32 mission) {
  u32 skill1 = GfDataMercenaries::getFieldSkill1(mission);
  u32 skill2 = GfDataMercenaries::getFieldSkill2(mission);
  u32 skill3 = GfDataMercenaries::getFieldSkill3(mission);
  unknown120 *team = GfDataMercenaries::getTeamByMissionID(mission);
  if (team == nullptr) {
    return 0;
  }
  int level2 = 0;
  int level3 = 0;
  int level1 = 0;
  for (u32 i = 0; i < 6; i++) {
    DataParamAcc acc(OBJECT_TYPE_BLADE, team->unknown00[i], GIMMICK_TYPE_UNKNOWN_0);
    if (acc.isValid()) {
      for (u32 slot = 0; slot < 3; slot++) {
        if (skill1 != 0 && acc.getFieldSkill(slot, false) == skill1) {
          level1 += acc.getFieldSkillLevel(slot, false);
        }
        if (skill2 != 0 && acc.getFieldSkill(slot, false) == skill2) {
          level2 += acc.getFieldSkillLevel(slot, false);
        }
        if (skill3 != 0 && acc.getFieldSkill(slot, false) == skill3) {
          level3 += acc.getFieldSkillLevel(slot, false);
        }
      }
    }
  }
  return level3 + level2 + level1 * 2;
}

bool GfGameMercenaries::getRewardItem(u32 &item, u32 &number, u32 mission, QUEST_REWARD type) {
  GfQuestReward reward;
  if (!GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
    return false;
  }
  item = reward.unknown00[type].unknown44;
  number = reward.unknown00[type].m_developZone;
  return item != 0;
}

bool GfGameMercenaries::getMission(mm::mtl::FixedVector<u16, 500> &missions, u32 missionFlag) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 mission = questListAcc->getFLD_MercenariesMissionStart();
  u32 end = questListAcc->getFLD_MercenariesMissionEnd();
  for (; mission < end; mission++) {
    if (missionFlag == unknown003 || GfDataMercenaries::getMissionFlag(mission) == missionFlag) {
      missions.push_back(mission);
    }
  }
  return !missions.empty();
}

bool GfGameMercenaries::getZoneMission(mm::mtl::FixedVector<u16, 500> &missions, u32 zone) {
  if (zone == 0) {
    return false;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 mission = questListAcc->getFLD_MercenariesMissionStart();
  u32 end = questListAcc->getFLD_MercenariesMissionEnd();
  for (; mission < end; mission++) {
    if (GfDataMercenaries::getMissionFlag(mission) != 0 && GfDataMercenaries::getMissionZoneID(mission) == zone) {
      missions.push_back(mission);
    }
  }
  return !missions.empty();
}

void GfGameMercenaries::applyDestroyMission() {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 mission = GfDataMercenaries::getStartMissionID();
  u32 end = GfDataMercenaries::getEndMissionID();
  for (; mission < end; mission++) {
    if (GfDataMercenaries::getMissionFlag(mission) == 1) {
      u32 condition = questListAcc->getListCancelCondition(GfDataMercenaries::getMissionQuestID(mission));
      if (condition != 0 && GfGameCond::isGameCond(condition)) {
        setMissionFlag(mission, 0);
      }
    }
  }
}

void GfGameMercenaries::execMissionAchievementForBlade(u32 mission) {
  SCOM_ACHIEV_INC::addTotalCount(0x14, 1);
  SCOM_ACHIEV_INC::create(0x14, 1, 0);
  unknown120 *team = GfDataMercenaries::getTeamByMissionID(mission);
  if (team != nullptr) {
    for (u32 i = 0; i < 6; i++) {
      if (team->unknown00[i] != 0) {
        SCOM_ACHIEV_INC::create(0x40, 1, team->unknown00[i]);
      }
    }
  }
}

void GfGameMercenaries::applyMercenariesLevel(const QuestCompleteParam &param) {
  static const u16 unknown019[] = {0, 53, 54, 55, 56, 0}; // Inferred role: level wildcards; original name unknown.
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 level = GfDataMercenaries::getLevel();
  for (u32 i = 1; i <= 6; i++) {
    if (bdatBtl->getWildcardDatavalueU2(unknown019[i - 1]) == param.unknown04.unknown00 && level < i) {
      level = i;
    }
  }
  if (level > GfDataMercenaries::getLevel()) {
    SCOM_SET_MERCENARIES_LEVEL::create(level);
  }
}

bool GfGameMercenaries::getEnableOrderTeam(mm::mtl::FixedVector<u16, 3> &teams, u32 mission) {
  teams.clear();
  u32 teamMax = GfDataMercenaries::getTeamMax();
  for (u32 i = 0; i < teamMax; i++) {
    unknown120 *team = GfDataMercenaries::getTeamByIndex(i);
    if (team->unknown14 == 0 && team->unknown10 != 0 && isTeamEnableMission(team->unknown10, mission)) {
      teams.push_back(team->unknown10);
    }
  }
  return !teams.empty();
}

bool GfGameMercenaries::getMemberForMission(mm::mtl::FixedArray<u16, 6> &members, u32 mission, MERCENARY_SELECT select) {
  mm::mtl::FixedVector<u16, 422> reservers;
  if (!GfDataMercenaries::getReserver(reservers)) {
    return false;
  }
  GfGameMercenaries *mercenaries = get();
  members.assign(0);
  mercenaries->unknown37c = 0;
  mercenaries->unknown368 = &members;
  mercenaries->unknown374 = mission;
  mercenaries->unknown370 = select;
  u32 purpose = GfDataMercenaries::getMissionPurposeID(mission);
  if (purpose == 0) {
    return false;
  }
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 task = 0; task < 4; task++) {
    if (questListAcc->getTaskTaskType(purpose, task) != TASK_TYPE_UNKNOWN_9) {
      continue;
    }
    u32 requestBlade = questListAcc->getTaskTaskID(purpose, task);
    if (requestBlade == 0) {
      continue;
    }
    mercenaries->unknown378 = requestBlade;
    mercenaries->unknown10.clear();
    for (u16 blade : reservers) {
      findMemberForMission(blade);
    }
    u32 number = questListAcc->getRequestBladeRequestNumber(requestBlade);
    if (mercenaries->unknown10.size() < number) {
      return false;
    }
    for (u32 i = 0; i < number; i++) {
      u32 j;
      for (j = 0; j < 6; j++) {
        if (members[j] == mercenaries->unknown10[i]) {
          break;
        }
      }
      if (j == 6) {
        members[mercenaries->unknown37c++] = mercenaries->unknown10[i];
      }
    }
  }
  return true;
}

void GfGameMercenaries::setupNewGameParam() {}

} // namespace gf
