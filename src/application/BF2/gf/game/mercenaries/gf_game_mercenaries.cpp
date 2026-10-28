#include "gf/game/mercenaries/gf_game_mercenaries.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"

namespace gf {

GfGameMercenaries::GfGameMercenaries(const GfSetupParam &param) : unknown08(false), unknown788(false) { initialize(param); }

void GfGameMercenaries::initialize(const GfSetupParam &) {
  rebuildAutoStartList();
  unknown08 = true;
}

GfGameMercenaries::~GfGameMercenaries() {}

void GfGameMercenaries::build(const GfSetupParam &param) {
  // __LINE__ must be 72 as in the original file: its value changes the instruction order.
#line 72
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameMercenaries(param);
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
  if (event == GEV_MAPJUMP_END && get() != nullptr) {
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
  SDataMercenariesTeam *team = GfDataMercenaries::getTeamByMissionID(mission);
  if (team != nullptr) {
    team->unknown1c = ElapseTime();
    team->unknown20 = ElapseTime();
    team->_24 = true;
  }
}

void GfGameMercenaries::setMissionTimeForDebug(u32 mission, u32 time) {
  SDataMercenariesTeam *team = GfDataMercenaries::getTeamByMissionID(mission);
  if (team != nullptr && (team->unknown1c.unknown00_0 != 0 || team->unknown1c.unknown00_6 != 0 || team->unknown1c.unknown01_4 != 0)) {
    ElapseTime elapseTime = ElapseTime();
    elapseTime.unknown00_0 = time;
    team->unknown1c = elapseTime;
  }
}

bool GfGameMercenaries::isAddTeamMember(u32 team) {
  SDataMercenariesTeam *members = GfDataMercenaries::getTeamMember(team);
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

bool GfGameMercenaries::addTeamMember(u32 team, u32 blade) {
  SDataMercenariesTeam *members = GfDataMercenaries::getTeamMember(team);
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
    SDataMercenariesTeam *members = GfDataMercenaries::getTeamMember(team);
    for (u32 i = 0; i < 6; i++) {
      if (members->unknown00[i] == blade) {
        return GfDataMercenaries::getReserverNum() < GfDataMercenaries::getReserverMax();
      }
    }
  }
  return false;
}

void GfGameMercenaries::clearTeamMember(u32 team) {
  SDataMercenariesTeam *members = GfDataMercenaries::getTeamMember(team);
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
  u32 previous = GfDataMercenaries::getMissionFlag(mission);
  GfDataMercenaries::setMissionFlag(mission, 3);
  GfEvent::callMercenariesMissionFlag(mission, 3, previous);
  if (GfDataMercenaries::getMissionTaskType(mission) == 2) {
    previous = GfDataMercenaries::getMissionFlag(mission);
    GfDataMercenaries::setMissionFlag(mission, 4);
    if (!GfDataMercenaries::isMissionCompleteFlag(mission)) {
      GfDataMercenaries::setMissionCompleteFlag(mission);
    }
    GfEvent::callMercenariesMissionFlag(mission, 4, previous);
  }
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
    u32 previous = GfDataMercenaries::getMissionFlag(mission);
    GfDataMercenaries::setMissionFlag(mission, 2);
    GfEvent::callMercenariesMissionFlag(mission, 2, previous);
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

u32 GfGameMercenaries::getRewardDevelopZone(u32 mission) {
  GfQuestReward reward;
  u16 zone = 0;
  if (GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
    zone = reward.unknown00[4].getDevelopZone();
  }
  return zone;
}

u32 GfGameMercenaries::getRewardTrust(u32 mission) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  return isValid ? reward.unknown00[5].unknown44 : 0;
}

u16 GfGameMercenaries::getRewardIdeaPoint(u32 mission) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  return isValid ? reward.unknown00[6].unknown44 : 0;
}

u16 GfGameMercenaries::getRewardIdeaType(u32 mission) {
  GfQuestReward reward;
  bool isValid = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false);
  return isValid ? reward.unknown00[6].m_developZone : 0;
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
        u32 previous = GfDataMercenaries::getMissionFlag(mission);
        GfDataMercenaries::setMissionFlag(mission, 0);
        GfEvent::callMercenariesMissionFlag(mission, 0, previous);
      }
    }
  }
}

void GfGameMercenaries::execMissionAchievementForBlade(u32 mission) {
  SCOM_ACHIEV_INC::addTotalCount(0x14, 1);
  SCOM_ACHIEV_INC::create(0x14, 1, 0);
  SDataMercenariesTeam *team = GfDataMercenaries::getTeamByMissionID(mission);
  if (team != nullptr) {
    for (u32 i = 0; i < 6; i++) {
      if (team->unknown00[i] != 0) {
        SCOM_ACHIEV_INC::create(0x40, 1, team->unknown00[i]);
      }
    }
  }
}

void GfGameMercenaries::applyMercenariesLevel(const QuestCompleteParam &param) {
  static const u16 levelWildcards[] = {0, 53, 54, 55, 56, 0};
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 level = GfDataMercenaries::getLevel();
  for (u32 i = 1; i <= 6; i++) {
    if (bdatBtl->getWildcardDatavalueU2(levelWildcards[i - 1]) == param.unknown04.unknown00 && level < i) {
      level = i;
    }
  }
  if (level > GfDataMercenaries::getLevel()) {
    SCOM_SET_MERCENARIES_LEVEL::create(level);
  }
}

void GfGameMercenaries::setupNewGameParam() {}

} // namespace gf
