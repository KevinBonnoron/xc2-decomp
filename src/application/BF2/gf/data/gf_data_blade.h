#pragma once
#include "gf/data/gf_data_hana.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataBlade {
  u8 _000[0x006 - 0x000];
  u16 id;
  u8 _008[0x0c0 - 0x008];
  u8 extraParts[6];
  u8 _0c6[0x68c - 0x0c6];
  EquipHana equipHana;
  u16 equipPowerRank;
  u16 openCircuit;
  u8 race;
  u8 gender;
  u8 _70a[0x70c - 0x70a];
  char modelName[0x28];
  char motionName[0x28];
  u8 _75c[0x821 - 0x75c];
  u8 weaponType;
  u8 _822[0x826 - 0x822];
  u8 eyeRotControl;
  u8 _827[0x82c - 0x827];
  u16 weapon;
  u8 _82e[0x836 - 0x82e];
  u16 scale;
  u8 _838[0x83a - 0x838];
  u16 offsetID;
  u16 collisionId;
  u8 _83e[0x846 - 0x83e];
  u8 questRace;
  u8 _847[0x848 - 0x847];
  u8 footStep;
  u8 footStepEffect;
  u8 _84a[0x8a4 - 0x84a];
};

static_assert(offsetof(SDataBlade, id) == 0x006, "");
static_assert(offsetof(SDataBlade, extraParts) == 0x0c0, "");
static_assert(offsetof(SDataBlade, race) == 0x708, "");
static_assert(offsetof(SDataBlade, modelName) == 0x70c, "");
static_assert(offsetof(SDataBlade, motionName) == 0x734, "");
static_assert(offsetof(SDataBlade, eyeRotControl) == 0x826, "");
static_assert(offsetof(SDataBlade, scale) == 0x836, "");
static_assert(offsetof(SDataBlade, offsetID) == 0x83a, "");
static_assert(offsetof(SDataBlade, collisionId) == 0x83c, "");
static_assert(offsetof(SDataBlade, footStep) == 0x848, "");
static_assert(offsetof(SDataBlade, footStepEffect) == 0x849, "");
static_assert(offsetof(SDataBlade, equipHana) == 0x68c, "");
static_assert(offsetof(SDataBlade, equipPowerRank) == 0x704, "");
static_assert(offsetof(SDataBlade, openCircuit) == 0x706, "");
static_assert(offsetof(SDataBlade, gender) == 0x709, "");
static_assert(offsetof(SDataBlade, weaponType) == 0x821, "");
static_assert(offsetof(SDataBlade, weapon) == 0x82c, "");
static_assert(offsetof(SDataBlade, questRace) == 0x846, "");
static_assert(sizeof(SDataBlade) == 0x8a4, "");

class GfDataBlade {
public:
  static SDataBlade *getSDataBlade(u32 blade);
  static bool getNameWithMsgID(u8 *&bdat, u32 &textId, const SDataBlade &dataBlade);
  static void getListReserver(mm::mtl::FixedVector<u16, 422> &reservers);
  static u32 getBladePower(SDataBlade &dataBlade);
  static u32 getBladePower(u32 blade);
  static bool isHikariCurrent();
  static void setHikariCurrent(bool hikariCurrent);
  static bool isHomuriNameHikari();
  static void setHomuriNameHikari(bool homuriNameHikari);
  static void setActivateDriver(u32 bladeId, int slot, u32 driverId, u32 option);
};

} // namespace gf
