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

  bool unknown08; // Inferred role: initialized; original member name unknown.
  u32 unknown0c;  // Inferred role: open page; original member name unknown.
  u32 unknown10;  // Inferred role: open quest id; original member name unknown.
  bool unknown14; // Inferred role: open task log; original member name unknown.
};

static_assert(offsetof(GfMenuQuest, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuQuest, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuQuest, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuQuest, unknown14) == 0x14, "");
static_assert(sizeof(GfMenuQuest) == 0x18, "");

} // namespace gf
