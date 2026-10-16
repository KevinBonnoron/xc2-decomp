#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuQuest : public mm::mtl::PtrSingleton<GfMenuQuest> {
public:
  GfMenuQuest(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuQuest() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void updateQuestTaskLog(const fw::UpdateInfo &info);
  static void openMenu(u32 questId, u32 page, bool isTaskLog);

  bool initialized;
  u32 openPage;
  u32 openQuestId;
  bool openTaskLog;
};

static_assert(offsetof(GfMenuQuest, initialized) == 0x08, "");
static_assert(offsetof(GfMenuQuest, openPage) == 0x0c, "");
static_assert(offsetof(GfMenuQuest, openQuestId) == 0x10, "");
static_assert(offsetof(GfMenuQuest, openTaskLog) == 0x14, "");
static_assert(sizeof(GfMenuQuest) == 0x18, "");

} // namespace gf
