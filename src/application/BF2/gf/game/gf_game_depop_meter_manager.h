#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
class GfGameDepopMeter;

class GfGameDepopMeterManager : public mm::mtl::PtrSingleton<GfGameDepopMeterManager> {
public:
  GfGameDepopMeterManager(u32 count);
  static void create(u32 count);
  static void dispose();
  static void update(f32 deltaTime);
  static void addDepopMeter(GfGameDepopMeter *meter);
  static void removeDepopMeter(GfGameDepopMeter *meter);

  u32 unknown08;                                                // Inferred role: meters updated per frame; original member name unknown.
  mm::mtl::IntrusiveList<GfGameDepopMeter> unknown10;           // Inferred role: registered meters; original member name unknown.
  mm::mtl::IntrusiveList<GfGameDepopMeter>::iterator unknown28; // Inferred role: next meter to update; original member name unknown.
};

static_assert(offsetof(GfGameDepopMeterManager, unknown08) == 0x08, "");
static_assert(offsetof(GfGameDepopMeterManager, unknown10) == 0x10, "");
static_assert(offsetof(GfGameDepopMeterManager, unknown28) == 0x28, "");
static_assert(sizeof(GfGameDepopMeterManager) == 0x30, "");

} // namespace gf
