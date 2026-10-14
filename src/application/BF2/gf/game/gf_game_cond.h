#pragma once
#include "gf/data/gf_data_map.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

class GfGameCond : public mm::mtl::PtrSingleton<GfGameCond> {
public:
  GfGameCond(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameCond();

  static void build(const GfSetupParam &param);
  static void destroy();
  static void finalize();

  static bool isQuest(u32 condition);
  static void applyQuest(u32 condition);
  static bool isScenario(u32 condition);
  static void applyScenario(u32 condition);
  static bool isGameEnv(u32 condition, u32 weatherBits, u32 timeRangeBits, CLOUD_SEA cloudSea);
  static bool isGameEnv(u32 condition, u32 map);
  static void applyGameEnv(u32 condition);
  static bool isFlag(u32 condition, bool *isAboveMin, bool *isBelowMax);
  static void applyFlag(u32 condition);
  static bool isGameCondParam(u32 condition, u32 index, u32 &conditionType, u32 &conditionParam);
  static bool isLevel(u32 condition);
  static void applyLevel(u32 condition);
  static bool isParty(u32 condition, mm::mtl::FixedArray<bool, 3> *results);
  static void applyParty(u32 condition);
  static bool isItem(u32 condition);
  static void applyItem(u32 condition);
  static bool isIdea(u32 condition, u32 blade, mm::mtl::FixedArray<bool, 5> *results);
  static bool isAchievement(u32 condition, u32 blade);
  static bool isFieldSkillLevel(u32 condition, u32 blade);
  static void applyIdea(u32 condition, u32 blade);
  static void applyAchievement(u32 condition, u32 blade);
  static void applyFieldSkillLevel(u32 condition, u32 blade);
  static bool isGameCondWithoutEnv(u32 condition);
  static bool isGameCond(u32 condition);
  static bool isGameCondWithMap(u32 condition, u32 map);
  static bool isGameCondWithBlade(u32 condition, u32 blade);
  static bool isGameCondWithIndex(u32 condition, u32 index, u32 blade);
  static void applyCond(u32 condition, u32 blade);
};

} // namespace gf
