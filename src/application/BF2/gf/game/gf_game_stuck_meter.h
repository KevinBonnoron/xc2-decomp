#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace fw {
class ColiMoveObject;
} // namespace fw

namespace gf {

class GfGameStuckMeter {
public:
  struct CreateInfo {
    void dispose();
    void setColiObj(fw::ColiMoveObject *object);

    f32 unknown00;                 // Role and original member name unknown.
    f32 unknown04;                 // Role and original member name unknown.
    fw::ColiMoveObject *unknown08; // Inferred role: collision object, reference counted by hand; original member name unknown.
    f32 unknown10;                 // Role and original member name unknown.
  };

  GfGameStuckMeter(const CreateInfo *info);
  void create(const CreateInfo &info);
  void dispose();
  bool isStuck() const;

  f32 unknown00;                 // Role and original member name unknown.
  f32 unknown04;                 // Inferred role: stuck time threshold; original member name unknown.
  fw::ColiMoveObject *unknown08; // Inferred role: collision object, reference counted by hand; original member name unknown.
  f32 unknown10;                 // Role and original member name unknown.
  u8 _14[0x18 - 0x14];
  f32 unknown18; // Inferred role: radius of the collision object; original member name unknown.
  f32 unknown1c; // Inferred role: height of the collision object; original member name unknown.
  f32 unknown20; // Inferred role: radius of the collision object; original member name unknown.
  u8 _24[0x30 - 0x24];
  mm::Vec3 unknown30; // Inferred role: last position; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: average position; original member name unknown.
  f32 unknown50;      // Role and original member name unknown.
  f32 unknown54;      // Inferred role: stuck time; original member name unknown.
};

static_assert(offsetof(GfGameStuckMeter, unknown08) == 0x08, "");
static_assert(offsetof(GfGameStuckMeter, unknown18) == 0x18, "");
static_assert(offsetof(GfGameStuckMeter, unknown30) == 0x30, "");
static_assert(offsetof(GfGameStuckMeter, unknown40) == 0x40, "");
static_assert(offsetof(GfGameStuckMeter, unknown54) == 0x54, "");
static_assert(sizeof(GfGameStuckMeter) == 0x60, "");

} // namespace gf
