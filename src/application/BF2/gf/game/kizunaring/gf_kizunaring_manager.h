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
  static u32 getReleaseAchievement(u32 blade, u32 line, u32 level);
  static u32 getAchievementCategory(u32 blade, u32 line, u32 level);
  static bool getAchievementResultMsg(u8 *&bdat, u32 &textId, u32 blade, u32 line, u32 level);
  static u16 getAchievementResultEnhance(u32 blade, u32 line, u32 level);
  static u32 getAchievementIcon(u32 blade, u32 line, u32 level);
  static u32 getAchievementVoiceCategory(u32 blade, u32 line, u32 level);
  static u32 getAchievementAfterVoice(u32 blade, u32 line, u32 level);
  static u32 getAchievementDifficulty(u32 blade, u32 line, u32 level);
  static u32 getAchievementQuest(u32 blade, u32 line, u32 level);
  static u32 getAchievementSetCategory(u32 blade, u32 line);
  static u32 getAchievementSetAbilityLevel(u32 blade, u32 line);
  static bool isNetabareOK(u32 blade, u32 line, u32 level);
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
