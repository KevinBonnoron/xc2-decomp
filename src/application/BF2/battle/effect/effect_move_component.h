#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class EffectMoveComponent {
public:
  enum MOVE_TYPE {
    MOVE_TYPE_NONE,
    MOVE_TYPE_NORMAL,
    MOVE_TYPE_PARABOLA,
    MOVE_TYPE_HOMING,
    MOVE_TYPE_BOUNCE,
    MOVE_TYPE_LINK_OBJ,
    MOVE_TYPE_UP,
  };

  struct MOVE_PARAM;

  EffectMoveComponent();
  void Initialize();
  void Initialize(const MOVE_PARAM &param);
  f32 CalcFakeGravity(const mm::Vec3 &position, const mm::Vec3 &target, f32 time) const;
  void SetGravity(f32 gravity);
  bool IsEnd(const mm::Vec3 &previous, mm::Vec3 &position, f32 time) const;
  void UpdateNormal(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateHoming(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateBounce(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateLinkObj(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateUp(f32 time, f32 frame, const mm::Vec3 &position);
  void Update(const fw::UpdateInfo &updateInfo, const mm::Vec3 &position);

  static void (EffectMoveComponent::*const m_apUpdateFuncList[])(f32 time, f32 frame, const mm::Vec3 &position);

  union {
    struct {
      gf::GF_OBJ_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
      f32 unknown08;                // Inferred role: target X; original member name unknown.
      f32 unknown0c;                // Inferred role: target Y; original member name unknown.
      f32 unknown10;                // Inferred role: target Z; original member name unknown.
      f32 unknown14;                // Inferred role: way X; original member name unknown.
      f32 unknown18;                // Inferred role: way Y; original member name unknown.
      f32 unknown1c;                // Inferred role: way Z; original member name unknown.
      f32 unknown20;                // Inferred role: start time; original member name unknown.
      f32 unknown24;                // Inferred role: time; original member name unknown.
      f32 unknown28;                // Inferred role: wait time; original member name unknown.
      f32 unknown2c;                // Inferred role: way time; original member name unknown.
      f32 unknown30;                // Inferred role: turn speed; original member name unknown.
      f32 unknown34;                // Inferred role: turn speed max; original member name unknown.
      f32 unknown38;                // Inferred role: turn acceleration; original member name unknown.
      bool unknown3c;               // Inferred role: far flag; original member name unknown.
    } unknown00_0;                  // Inferred role: homing move parameters; original member name unknown.
    struct {
      gf::GF_OBJ_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
      const char *unknown08;        // Inferred role: bone name; original member name unknown.
      f32 unknown10;                // Inferred role: time; original member name unknown.
    } unknown00_1;                  // Inferred role: link object parameters; original member name unknown.
    struct {
      f32 unknown00; // Inferred role: time; original member name unknown.
    } unknown00_2;   // Inferred role: up move parameters; original member name unknown.
  };
  mm::Vec3 unknown40; // Inferred role: move; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: direction; original member name unknown.
  f32 unknown60;      // Inferred role: time; original member name unknown.
  f32 unknown64;      // Inferred role: distance; original member name unknown.
  f32 unknown68;      // Inferred role: distance XZ; original member name unknown.
  f32 unknown6c;      // Inferred role: speed; original member name unknown.
  f32 unknown70;      // Inferred role: speed max; original member name unknown.
  f32 unknown74;      // Inferred role: speed rate; original member name unknown.
  f32 unknown78;      // Inferred role: acceleration; original member name unknown.
  f32 unknown7c;      // Inferred role: acceleration delay; original member name unknown.
  f32 unknown80;      // Inferred role: acceleration time; original member name unknown.
  f32 unknown84;      // Inferred role: gravity; original member name unknown.
  f32 unknown88;      // Inferred role: gravity time; original member name unknown.
  f32 unknown8c[6];   // Inferred role: end parameters; original member name unknown.
  u8 unknowna4;       // Inferred role: end flags; original member name unknown.
  u8 unknowna5;       // Inferred role: move type; original member name unknown.
};

static_assert(offsetof(EffectMoveComponent, unknown00_0.unknown38) == 0x38, "");
static_assert(offsetof(EffectMoveComponent, unknown00_0.unknown3c) == 0x3c, "");
static_assert(offsetof(EffectMoveComponent, unknown40) == 0x40, "");
static_assert(offsetof(EffectMoveComponent, unknown50) == 0x50, "");
static_assert(offsetof(EffectMoveComponent, unknown60) == 0x60, "");
static_assert(offsetof(EffectMoveComponent, unknown6c) == 0x6c, "");
static_assert(offsetof(EffectMoveComponent, unknown84) == 0x84, "");
static_assert(offsetof(EffectMoveComponent, unknown8c) == 0x8c, "");
static_assert(offsetof(EffectMoveComponent, unknowna4) == 0xa4, "");
static_assert(offsetof(EffectMoveComponent, unknowna5) == 0xa5, "");
static_assert(sizeof(EffectMoveComponent) == 0xb0, "");

} // namespace btl
