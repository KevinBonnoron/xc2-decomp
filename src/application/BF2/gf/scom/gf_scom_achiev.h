#pragma once
#include <stddef.h>

#include "gf/request/gf_scom.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SCOM_HANDLE;

class SCOM_ACHIEV_INC : public SCOM {
public:
  SCOM_ACHIEV_INC(GF_SCOM_HANDLE *handle, u32 stats, int count, u32 blade);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *createBladeArts(GF_OBJ_HANDLE *handle, u32 arts);
  static GF_SCOM_HANDLE *createBladeArtsSp(GF_OBJ_HANDLE *handle, u32 arts);
  static GF_SCOM_HANDLE *createBladeNArts(GF_OBJ_HANDLE *handle);
  static void createElementalCombo(GF_OBJ_HANDLE *handle);
  static void createElementalComboFinish(GF_OBJ_HANDLE *handle);
  static void createFightCombo(GF_OBJ_HANDLE *handle);
  static void createFightComboFinish(GF_OBJ_HANDLE *handle);
  static void createChainAttack(GF_OBJ_HANDLE *handle);
  static void createButtonChallenge();
  static void createHelp(GF_OBJ_HANDLE *handle);
  static void createPotGet();
  static void createAvoid(GF_OBJ_HANDLE *handle);
  static void createGuard(GF_OBJ_HANDLE *handle);
  static void createBladeChange(GF_OBJ_HANDLE *handle);
  static void createRecover(GF_OBJ_HANDLE *handle, u32 value);
  static void createBackAttack(GF_OBJ_HANDLE *handle);
  static void createDamageMax(GF_OBJ_HANDLE *handle, u32 damage);
  static void createDamageAdd(GF_OBJ_HANDLE *handle, u32 damage);
  static void createDamageGet(GF_OBJ_HANDLE *handle, u32 damage);
  static void createCriticalHit(GF_OBJ_HANDLE *handle);
  static void createCriticalGet(GF_OBJ_HANDLE *handle);
  static void createKizuna(GF_OBJ_HANDLE *handle);
  static void createKillEnemy(GF_OBJ_HANDLE *handle);
  static void createBattle();
  static void createBladeCreate();
  static void createCrystal();
  static void addTotalCount(u32 stats, u32 count);
  static void create(u32 stats, int count, u32 blade);
  static void createParty(u32 stats, int count);
  static GF_SCOM_HANDLE *createCurrentBlade(GF_OBJ_HANDLE *handle, u32 stats, int count);

  static int s_countSalvageShop;

  u32 unknown1c;                            // Inferred role: stats; original member name unknown.
  int unknown20;                            // Inferred role: count; original member name unknown.
  mm::mtl::FixedVector<u16, 422> unknown28; // Inferred role: blades; original member name unknown.
};

static_assert(offsetof(SCOM_ACHIEV_INC, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ACHIEV_INC, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_ACHIEV_INC, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_ACHIEV_INC) == 0x380, "");

} // namespace gf
