#include "gf/game/gf_game_trinity_attack.h"

#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_driver.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_array.h"

namespace gf {
struct GF_MOUNT_HANDLE;

GfTrinityAttack::GfTrinityAttack() : m_state(0), m_blade(INVALID_HANDLE) { unknown10.clear(); }

GfTrinityAttack::~GfTrinityAttack() {}

u32 GfTrinityAttack::getBladeId() const {
  if (GfGameParty::getDriverBdatId(0) == DRIVER_REX) {
    int bladeSet = GfDataDriver::getBladeSet(DRIVER_REX);
    if (GfGameParty::getBladeBdatId(0, bladeSet) == BLADE_HOMURA) {
      int bladeNum = GfDataDriver::getMaxSetBladeNum(DRIVER_REX);
      for (int slot = 0; slot < bladeNum; slot++) {
        if (bladeSet != slot && GfGameParty::getBladeBdatId(0, slot) == BLADE_UNKNOWN_1011) {
          return BLADE_UNKNOWN_1011;
        }
      }
    }
  }
  if (GfGameParty::getDriverBdatId(0) == DRIVER_REX) {
    int bladeSet = GfDataDriver::getBladeSet(DRIVER_REX);
    if (GfGameParty::getBladeBdatId(0, bladeSet) == BLADE_UNKNOWN_1011) {
      int bladeNum = GfDataDriver::getMaxSetBladeNum(DRIVER_REX);
      for (int slot = 0; slot < bladeNum; slot++) {
        if (bladeSet != slot && GfGameParty::getBladeBdatId(0, slot) == BLADE_HOMURA) {
          return BLADE_HOMURA;
        }
      }
    }
  }
  return 0;
}

bool GfTrinityAttack::isEnableAttackMember() const { return getBladeId() != 0; }

bool GfTrinityAttack::isLoading() const {
  if (!GfGameObj::isValidGameObj(m_blade, true, nullptr)) {
    return true;
  }
  GfWeapon *weapon = GfMountManager::getGfWeapon(m_blade, GFATTACH_WEAPON_EXTRA);
  if (weapon != nullptr) {
    for (u32 index = 0; index < 10; index++) {
      GF_OBJ_HANDLE *handle = weapon->getCurrentHandles()[index];
      if (handle != INVALID_HANDLE && !GfGameObj::isValidGameObj(handle, true, nullptr)) {
        return true;
      }
    }
  }
  return false;
}

void GfTrinityAttack::updateForSetup(const fw::UpdateInfo &) {
  if (!isLoading()) {
    m_state = 2;
    unknown10.bind(this, &GfTrinityAttack::updateForPlay);
  }
}

void GfTrinityAttack::endAttack() {
  GF_OBJ_HANDLE *leader = GfGameManager::getPartyLeaderDriver();
  if (GfObjUtil::getMountHandle(leader, GFATTACH_WEAPON_EXTRA) != reinterpret_cast<GF_MOUNT_HANDLE *>(-1)) {
    GfMountManager::removeMountHandle(leader, GFATTACH_WEAPON_EXTRA);
  }
  GfObjUtil::destroy(m_blade);
  m_blade = INVALID_HANDLE;
  unknown10.clear();
  m_state = 0;
}

void GfTrinityAttack::updateForPlay(const fw::UpdateInfo &) {}

void GfTrinityAttack::update(const fw::UpdateInfo &info) {
  if (unknown10.isValid()) {
    unknown10(info);
  }
}

GfTrinityAttack *GfTrinityAttack::create() {
  GfTrinityAttack *trinityAttack = get();
  if (trinityAttack == nullptr) {
#line 189
    trinityAttack = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfTrinityAttack();
  }
  return trinityAttack;
}

void GfTrinityAttack::destroy() {
  GfTrinityAttack *trinityAttack = get();
  if (trinityAttack != nullptr) {
    trinityAttack->finish();
    delete trinityAttack;
  }
}

void GfTrinityAttack::finish() {
  if (m_blade != INVALID_HANDLE) {
    GfGameObj::destroyGameObj(m_blade, 0.0f);
    m_blade = INVALID_HANDLE;
  }
  unknown10.clear();
  m_state = 0;
}

s32 GfTrinityAttack::getState() const { return m_state; }

GF_OBJ_HANDLE *GfTrinityAttack::getBlade() const { return m_blade; }

GfWeapon *GfTrinityAttack::getWeapon() const { return GfMountManager::getGfWeapon(m_blade, GFATTACH_WEAPON_EXTRA); }

} // namespace gf
