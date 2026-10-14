#pragma once
#include "gf/data/gf_data_hana.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataBlade {
  u8 _000[0x006 - 0x000];
  u16 id;
  u8 _008[0x68c - 0x008];
  EquipHana equipHana;
  u16 equipPowerRank;
  u16 openCircuit;
  u8 _708[0x709 - 0x708];
  u8 gender;
  u8 _70a[0x821 - 0x70a];
  u8 weaponType;
  u8 _822[0x82c - 0x822];
  u16 weapon;
  u8 _82e[0x846 - 0x82e];
  u8 questRace;
  u8 _847[0x8a4 - 0x847];
};

static_assert(offsetof(SDataBlade, id) == 0x006, "");
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
