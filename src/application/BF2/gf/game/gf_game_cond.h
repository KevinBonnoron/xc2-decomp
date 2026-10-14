#pragma once
#include "gf/data/gf_data_map.h"
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

  static bool isGameCond(u32 condition);
};

} // namespace gf
