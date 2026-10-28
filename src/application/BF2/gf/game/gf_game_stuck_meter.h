#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

namespace fw {
class ColiMoveObject;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameDepopMeter : public mm::mtl::IntrusiveListNode<GfGameDepopMeter> {
public:
  void dispose();
  void update(f32 deltaTime);

  GF_OBJ_HANDLE *unknown10; // Inferred role: target object; original member name unknown.
  bool unknown18;           // Inferred role: destroy the object when it is hidden by a collision; original member name unknown.
  u8 _19[0x20 - 0x19];
  bool unknown20; // Role and original member name unknown.
  u8 _21[0x30 - 0x21];
  mm::Vec3 unknown30; // Inferred role: last position of the object; original member name unknown.
  bool unknown40;     // Inferred role: hidden by a collision; original member name unknown.
};

static_assert(offsetof(GfGameDepopMeter, unknown10) == 0x10, "");
static_assert(offsetof(GfGameDepopMeter, unknown18) == 0x18, "");
static_assert(offsetof(GfGameDepopMeter, unknown20) == 0x20, "");
static_assert(offsetof(GfGameDepopMeter, unknown30) == 0x30, "");
static_assert(offsetof(GfGameDepopMeter, unknown40) == 0x40, "");
static_assert(sizeof(GfGameDepopMeter) == 0x50, "");

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
