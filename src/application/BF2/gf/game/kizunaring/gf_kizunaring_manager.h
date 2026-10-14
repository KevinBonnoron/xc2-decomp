#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;
struct QuestCompleteParam;

class GfKizunaringManager : public mm::mtl::PtrSingleton<GfKizunaringManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void orderAchievement(u32 blade);
  static void setupGame();
  void qevCompleteQuest(const QuestCompleteParam &param);
};

} // namespace gf
