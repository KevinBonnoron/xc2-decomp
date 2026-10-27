#include "gf/game/mercenaries/gf_game_mercenaries.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"

namespace gf {

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

void GfGameMercenaries::setupNewGameParam() {}

} // namespace gf
