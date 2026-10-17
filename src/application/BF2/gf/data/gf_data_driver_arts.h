#pragma once
#include "mm_mtl/fixed_array.h"
#include "types.h"

namespace gf {

class GfDataDriverArts {
public:
  static bool getEnableArts(mm::mtl::FixedArray<u32, 4> &enableArts, u32 driver, u32 weaponType);
  static void getSlotArts(mm::mtl::FixedArray<u32, 3> &slotArts, u32 driver, u32 weaponType);
  static void setSlotArts(u32 driver, u32 weaponType, const mm::mtl::FixedArray<u32, 3> &slotArts);
  static u32 getArtsLevel(u32 driver, u32 arts);
  static u32 getNeedLevelupWp(u32 driver, u32 arts);
  static u32 getLevelCap(u32 arts, u32 level);
  static u32 getWp(u32 driver, u32 weaponType);
  static void addWp(u32 driver, u32 weaponType, int wp);
  static void initializeWp(u32 driver, u32 weaponType);
  static u8 *getNameFP();
  static u8 *getCaptionFP();
  static u32 getNameID(u32 arts);
  static u32 getCaptionID(u32 arts);
  static u32 getIconID(u32 arts);
  static const char *getName(u32 arts);
  static const char *getDebugName(u32 arts);
  static u32 getWpnType(u32 arts);
  static u32 getRangeType(u32 arts);
  static u32 getReaction(u32 arts, u32 level);
  static u32 getDamageMul(u32 arts, u32 level);
  static u32 getRecast(u32 arts, u32 level);
  static u32 getEnhance(u32 arts, u32 level);
  static u32 getArtsType(u32 arts);
  static u32 getLevelMax(u32 arts);
};

} // namespace gf
