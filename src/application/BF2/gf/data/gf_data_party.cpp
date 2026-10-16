#include "gf/data/gf_data_party.h"

#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"

namespace gf {

constexpr u32 PARTY_MEMBER_COUNT = 10;
constexpr u32 PARTY_BATTLE_MEMBER_COUNT = 3;
constexpr u32 SET_BLADE_NUM_MAX = 5;
constexpr u32 WEAPON_NUM_PER_BLADE = 8;
constexpr u32 MEMBER_NONE = 0xffffffff;

bool GfDataParty::isExistBlade(u32 blade) {
  if (blade == 0) {
    return false;
  }

  for (u32 member = 0; member < PARTY_BATTLE_MEMBER_COUNT; member++) {
    if (isExistBlade(member, blade)) {
      return true;
    }
  }

  return false;
}

u32 GfDataParty::getDriver(u32 member) { return GfDataManager::getDataGame()->party.members[member].driver; }

int GfDataParty::getDriverPartyID(u32 driver) {
  if (driver == 0) {
    return -1;
  }

  for (u32 member = 0; member < PARTY_MEMBER_COUNT; member++) {
    if (getDriver(member) == driver) {
      return member;
    }
  }

  return -1;
}

bool GfDataParty::setDriver(u32 member, u32 driver) {
  SDataPartyMember &partyMember = GfDataManager::getDataGame()->party.members[member];
  u16 previousDriver = partyMember.driver;
  partyMember.driver = driver;
  partyMember.hierarchyDriver = 0;
  partyMember.hierarchyBlade = 0;
  return previousDriver != static_cast<u16>(driver);
}

SDataParty *GfDataParty::getSDataParty() { return &GfDataManager::getDataGame()->party; }

bool GfDataParty::isExistDriver(u32 driver) {
  for (u32 member = 0; member < PARTY_BATTLE_MEMBER_COUNT; member++) {
    if (getDriver(member) == driver) {
      return true;
    }
  }

  return false;
}

SDataPartyMember *GfDataParty::getPartyMember(u32 member) { return &GfDataManager::getDataGame()->party.members[member]; }

mm::Vec3 *GfDataParty::getSavePos(u32 member, bool isDriver) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (isDriver) {
    return &dataGame->map.driverSavePos[member];
  }

  return &dataGame->map.bladeSavePos[member];
}

mm::Vec3 *GfDataParty::getSaveRot(u32 member, bool isDriver) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (isDriver) {
    return &dataGame->map.driverSaveRot[member];
  }

  return &dataGame->map.bladeSaveRot[member];
}

bool GfDataParty::isEmptyDriver() {
  for (u32 member = 0; member < PARTY_BATTLE_MEMBER_COUNT; member++) {
    if (getDriver(member) == 0) {
      return true;
    }
  }

  return false;
}

bool GfDataParty::isExistBlade(u32 member, u32 blade) {
  SDataPartyMember &partyMember = GfDataManager::getDataGame()->party.members[member];
  if (partyMember.driver == 0) {
    return false;
  }

  for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(partyMember.driver); slot++) {
    if (GfDataDriver::getBlade(partyMember.driver, slot) == blade) {
      return true;
    }
  }

  return false;
}

bool GfDataParty::empty() {
  for (u32 member = 0; member < PARTY_BATTLE_MEMBER_COUNT; member++) {
    if (getDriver(member) != 0) {
      return false;
    }
  }

  return true;
}

u32 GfDataParty::getFixedHandleForDriver(u32 member) { return member; }

u32 GfDataParty::getFixedHandleForBlade(u32 member, int slot) { return PARTY_BATTLE_MEMBER_COUNT + member * SET_BLADE_NUM_MAX + slot; }

u32 GfDataParty::getFixedHandleForWeapon(u32 member, int slot, u32 weapon) {
  return member * SET_BLADE_NUM_MAX * WEAPON_NUM_PER_BLADE + slot * WEAPON_NUM_PER_BLADE + weapon +
         PARTY_BATTLE_MEMBER_COUNT * (1 + SET_BLADE_NUM_MAX);
}

void GfDataParty::getDriver(mm::mtl::FixedArray<u16, 10> &drivers) {
  for (u32 member = 0; member < drivers.size(); member++) {
    drivers[member] = getDriver(member);
  }
}

bool GfDataParty::isNiaByakko(u32 member) {
  if (member == MEMBER_NONE) {
    return false;
  }

  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->party.members[member].driver != DRIVER_NIA) {
    return false;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, DRIVER_NIA, static_cast<GimmickType>(0));
  bool isByakko = false;
  if (paramAcc.getBlade(-1, false) == BLADE_BYAKKO) {
    isByakko = isRideChar(dataGame->party.leader);
  }

  return isByakko;
}

bool GfDataParty::isRideChar(u32 chara) { return chara == DRIVER_NIA || chara == BLADE_BYAKKO; }

bool GfDataParty::isLeader(u32 chara) {
  if (chara == 0) {
    return false;
  }

  return GfDataManager::getDataGame()->party.leader == chara;
}

} // namespace gf
