#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct SDataPouch;

// Layout evidence: GfPouchUtil::getEffect stores it into a FixedVector of 8 byte elements; the favorite item effect builder
// (0x7100363290) writes the item type at 0x0 and the factor at 0x4. The type name is the template argument of the mangled getEffect.
struct PouchEffect {
  u32 unknown00; // Inferred role: favorite item type; original member name unknown.
  f32 unknown04; // Inferred role: factor; original member name unknown.
};

class GfPouchUtil {
public:
  static SDataPouch &getPouch(u32 driver, u32 slot);
  static void setPouch(u32 driver, u32 slot, const SDataPouch &pouch);
  static void updatePouch(u32 driver, u32 slot, const SDataPouch &pouch, const fw::UpdateInfo &info);
  static void execOpen(u32 driver);
  static bool isEnableOpen(u32 driver);
  static u32 getOpenCount(u32 driver);
  static void setTimeUpForDebug(u32 driver, u32 slot);
  static bool isExistOpenItem();
  static bool getEffect(mm::mtl::FixedVector<PouchEffect, 3> &effects, u32 driver);
  static bool getEffect(mm::mtl::FixedVector<PouchEffect, 3> &effects, u32 driver, u32 slot);
};

static_assert(offsetof(PouchEffect, unknown04) == 0x4, "");
static_assert(sizeof(PouchEffect) == 0x8, "");

} // namespace gf
