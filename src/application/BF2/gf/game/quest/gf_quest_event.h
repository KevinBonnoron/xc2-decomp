#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

class GfQuestEvent : public mm::mtl::PtrSingleton<GfQuestEvent> {
public:
  GfQuestEvent();
  ~GfQuestEvent();
  static bool setQuestEntry(u32 quest);
  static u32 getQuestState(u32 quest);
  static void setQuestComp(u32 quest, u32 taskIndex);
  static bool getQuestComp(u32 quest, u32 taskIndex);
  static bool isActive();
  static void openEntry(u32 quest);
  static void openResult(u32 quest);
  static void clearDispUI();

  bool unknown08; // Inferred role: entry open; original member name unknown.
  bool unknown09; // Inferred role: result open; original member name unknown.
};

static_assert(offsetof(GfQuestEvent, unknown08) == 0x08, "");
static_assert(offsetof(GfQuestEvent, unknown09) == 0x09, "");
static_assert(sizeof(GfQuestEvent) == 0x10, "");

} // namespace gf
