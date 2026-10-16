#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct AchievQuest;
struct GfSetupParam;
struct QuestCompleteParam;

class GfKizunaringBlade {
public:
  static void orderAchievement(u32 blade);
  static void removeAchievement(u32 blade);
  static bool isCompleteLevel(const AchievQuest &achievQuest);
  static void completeAllAchievementForDebug(u32 blade);
  static void qevCompleteQuest(const QuestCompleteParam &param);
};

class GfKizunaringManager : public mm::mtl::PtrSingleton<GfKizunaringManager> {
public:
  GfKizunaringManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfKizunaringManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void orderAchievement(u32 blade);
  static void setupGame();
  static void completeAllAchievementForDebug(u32 blade);
  void qevCompleteQuest(const QuestCompleteParam &param);

private:
  bool initialized;
};

static_assert(sizeof(GfKizunaringManager) == 0x10, "");

} // namespace gf
