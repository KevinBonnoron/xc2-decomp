#pragma once
#include "gf/data/gf_data_map.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

enum {
  CONDITION_TYPE_UNKNOWN_0,  // Inferred role: condition type none; original name unknown.
  CONDITION_TYPE_UNKNOWN_1,  // Inferred role: condition type scenario; original name unknown.
  CONDITION_TYPE_UNKNOWN_2,  // Inferred role: condition type quest; original name unknown.
  CONDITION_TYPE_UNKNOWN_3,  // Inferred role: condition type environment; original name unknown.
  CONDITION_TYPE_UNKNOWN_4,  // Inferred role: condition type flag; original name unknown.
  CONDITION_TYPE_UNKNOWN_5,  // Inferred role: condition type item; original name unknown.
  CONDITION_TYPE_UNKNOWN_6,  // Inferred role: condition type party; original name unknown.
  CONDITION_TYPE_UNKNOWN_7,  // Inferred role: condition type idea; original name unknown.
  CONDITION_TYPE_UNKNOWN_8,  // Inferred role: condition type level; original name unknown.
  CONDITION_TYPE_UNKNOWN_9,  // Inferred role: condition type achievement; original name unknown.
  CONDITION_TYPE_UNKNOWN_10, // Inferred role: condition type field skill level; original name unknown.
};

constexpr u32 CONDITION_UNKNOWN_8 = 8; // Inferred role: condition list count; original name unknown.

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
