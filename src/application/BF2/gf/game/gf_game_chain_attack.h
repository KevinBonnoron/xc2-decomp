#pragma once
#include "mm_mtl/delegate.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
class GfWeapon;

class GfChainAttack : public mm::mtl::PtrSingleton<GfChainAttack> {
public:
  GfChainAttack();
  ~GfChainAttack();
  void update(const fw::UpdateInfo &info);
  void startSetup();
  void updateForSetup(const fw::UpdateInfo &info);
  void updateForPlay(const fw::UpdateInfo &info);
  static GfChainAttack *create();
  static void destroy();
  void finish();
  bool isLoadingDrivers() const;
  s32 getState() const;
  GF_OBJ_HANDLE *getDriverByPartyId(u32 partyId) const;
  GF_OBJ_HANDLE *getDriverByGameDriver(GF_OBJ_HANDLE *handle) const;
  GfWeapon *getWeaponByPartyId(u32 partyId) const;
  GfWeapon *getWeaponByGameDriver(GF_OBJ_HANDLE *handle) const;

  s32 m_state;                                               // Name from getState().
  mm::mtl::Delegate<void(const fw::UpdateInfo &)> unknown10; // Inferred role: update callback; original member name unknown.
  GF_OBJ_HANDLE *m_driverByPartyId[3];                       // Name from getDriverByPartyId().
};

static_assert(offsetof(GfChainAttack, m_state) == 0x08, "");
static_assert(offsetof(GfChainAttack, unknown10) == 0x10, "");
static_assert(offsetof(GfChainAttack, m_driverByPartyId) == 0x30, "");
static_assert(sizeof(GfChainAttack) == 0x48, "");

} // namespace gf
