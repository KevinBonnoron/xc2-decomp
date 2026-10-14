#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct AchievQuest;
struct GfSetupParam;
struct QuestCompleteParam;

class GfKizunaringBlade {
public:
  static bool isCompleteLevel(const AchievQuest &achievQuest);
};

class GfKizunaringManager : public mm::mtl::PtrSingleton<GfKizunaringManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void orderAchievement(u32 blade);
  static void setupGame();
  void qevCompleteQuest(const QuestCompleteParam &param);
};

} // namespace gf
