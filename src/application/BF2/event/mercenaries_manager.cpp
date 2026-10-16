#include "event/mercenaries_manager.h"

#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/request/gf_req_scom.h"

namespace event {

MercenariesManager::MercenariesManager() {}

void MercenariesManager::clear() {}

void MercenariesManager::OnEventProc(MSG_TYPE type) {}

void MercenariesManager::entryable(u32 mission) { gf::GfGameMercenaries::setMissionFlag(mission, 1); }

void MercenariesManager::finish(u32 mission) { gf::SCOM_MISSION_COMPLETE::create(mission); }

u32 MercenariesManager::getState(u32 mission) { return gf::GfGameMercenaries::getMissionFlag(mission); }

} // namespace event
