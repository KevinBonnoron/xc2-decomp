#include "gf/data/gf_data_party.h"

#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"

namespace gf {

constexpr u32 PARTY_UNKNOWN_10 = 10;                  // Inferred role: party member count; original name unknown.
constexpr u32 PARTY_UNKNOWN_3 = 3;                    // Inferred role: party battle member count; original name unknown.
constexpr u32 WEAPON_UNKNOWN_8 = 8;                   // Inferred role: weapon num per blade; original name unknown.
constexpr u32 MEMBER_UNKNOWN_4294967295 = 0xffffffff; // Inferred role: member none; original name unknown.

bool GfDataParty::isExistBlade(u32 blade) {
  if (blade == 0) {
    return false;
  }

  for (u32 member = 0; member < PARTY_UNKNOWN_3; member++) {
    if (isExistBlade(member, blade)) {
      return true;
    }
  }

  return false;
}

u32 GfDataParty::getDriver(u32 member) { return GfDataManager::getDataGame()->m_sDataParty.m_partyMember[member].m_driver; }

int GfDataParty::getDriverPartyID(u32 driver) {
  if (driver == 0) {
    return -1;
  }

  for (u32 member = 0; member < PARTY_UNKNOWN_10; member++) {
    if (getDriver(member) == driver) {
      return member;
    }
  }

  return -1;
}

bool GfDataParty::setDriver(u32 member, u32 driver) {
  unknown123 &partyMember = GfDataManager::getDataGame()->m_sDataParty.m_partyMember[member];
  u16 previousDriver = partyMember.m_driver;
  partyMember.m_driver = driver;
  partyMember.m_hierarchyDriver = 0;
  partyMember.m_hierarchyBlade = 0;
  return previousDriver != static_cast<u16>(driver);
}

unknown124 *GfDataParty::getSDataParty() { return &GfDataManager::getDataGame()->m_sDataParty; }

bool GfDataParty::isExistDriver(u32 driver) {
  for (u32 member = 0; member < PARTY_UNKNOWN_3; member++) {
    if (getDriver(member) == driver) {
      return true;
    }
  }

  return false;
}

unknown123 *GfDataParty::getPartyMember(u32 member) { return &GfDataManager::getDataGame()->m_sDataParty.m_partyMember[member]; }

mm::Vec3 *GfDataParty::getSavePos(u32 member, bool isDriver) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (isDriver) {
    return &dataGame->m_sDataMap.unknown00[member];
  }

  return &dataGame->m_sDataMap.unknown30[member];
}

mm::Vec3 *GfDataParty::getSaveRot(u32 member, bool isDriver) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (isDriver) {
    return &dataGame->m_sDataMap.unknown60[member];
  }

  return &dataGame->m_sDataMap.unknown90[member];
}

bool GfDataParty::isEmptyDriver() {
  for (u32 member = 0; member < PARTY_UNKNOWN_3; member++) {
    if (getDriver(member) == 0) {
      return true;
    }
  }

  return false;
}

bool GfDataParty::isExistBlade(u32 member, u32 blade) {
  unknown123 &partyMember = GfDataManager::getDataGame()->m_sDataParty.m_partyMember[member];
  if (partyMember.m_driver == 0) {
    return false;
  }

  for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(partyMember.m_driver); slot++) {
    if (GfDataDriver::getBlade(partyMember.m_driver, slot) == blade) {
      return true;
    }
  }

  return false;
}

bool GfDataParty::empty() {
  for (u32 member = 0; member < PARTY_UNKNOWN_3; member++) {
    if (getDriver(member) != 0) {
      return false;
    }
  }

  return true;
}

u32 GfDataParty::getFixedHandleForDriver(u32 member) { return member; }

u32 GfDataParty::getFixedHandleForBlade(u32 member, int slot) { return PARTY_UNKNOWN_3 + member * SET_UNKNOWN_5 + slot; }

u32 GfDataParty::getFixedHandleForWeapon(u32 member, int slot, u32 weapon) {
  return member * SET_UNKNOWN_5 * WEAPON_UNKNOWN_8 + slot * WEAPON_UNKNOWN_8 + weapon + PARTY_UNKNOWN_3 * (1 + SET_UNKNOWN_5);
}

void GfDataParty::getDriver(mm::mtl::FixedArray<u16, 10> &drivers) {
  for (u32 member = 0; member < drivers.size(); member++) {
    drivers[member] = getDriver(member);
  }
}

bool GfDataParty::isNiaByakko(u32 member) {
  if (member == MEMBER_UNKNOWN_4294967295) {
    return false;
  }

  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->m_sDataParty.m_partyMember[member].m_driver != DRIVER_UNKNOWN_2) {
    return false;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_PC, DRIVER_UNKNOWN_2, static_cast<GimmickType>(0));
  bool isByakko = false;
  if (paramAcc.getBlade(-1, false) == BLADE_BYAKKO) {
    isByakko = isRideChar(dataGame->m_sDataParty.m_leaderBdatID);
  }

  return isByakko;
}

bool GfDataParty::isRideChar(u32 chara) { return chara == DRIVER_UNKNOWN_2 || chara == BLADE_BYAKKO; }

bool GfDataParty::isLeader(u32 chara) {
  if (chara == 0) {
    return false;
  }

  return GfDataManager::getDataGame()->m_sDataParty.m_leaderBdatID == chara;
}

bool GfDataParty::isActivateMember(u32 chara) {
  if (chara < BLADE_HOMURA) {
    return !GfDataDriver::isActivateUnuse(chara);
  }
  if (chara < BLADE_UNKNOWN_1051) {
    if (chara != BLADE_UNKNOWN_1011) {
      u32 driver = GfDataBlade::getSetDriver(chara);
      if (driver == 0 || GfDataDriver::isActivateUnuse(driver)) {
        return false;
      }
    }
    return !GfDataBlade::isActivateMercenaryTeam(chara) && !GfDataBlade::isActivateUnuse(chara);
  }

  return false;
}

} // namespace gf
