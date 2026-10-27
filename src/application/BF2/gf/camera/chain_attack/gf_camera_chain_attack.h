#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class ChainAttackCameraEntity : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  ~ChainAttackCameraEntity() override;
  void onActivate() override;
  void calcSpeedTypeLinearSpacing();
  void calcSpeedTypeFastOut();
  void calcSpeedTypeSlowOut();
  void setPlayTimeRate(f32 rate);
  void setPlayTimeDuration(f32 duration);
  void setMoveType(int moveType);
  static f32 curve(f32 a, f32 b, f32 t);
  static f32 slowOut(f32 t);
  static f32 fastOut(f32 t);
  static f32 fastInFastOut(f32 t);
  void calcSpeedTypeFastInFastOut();
  const mm::mtl::RTTI *getRTTI() const override;
  const char *getName() const override;

  mm::Vec3 unknownb0;  // Inferred role: start position; original member name unknown.
  mm::Vec3 unknownc0;  // Inferred role: start target; original member name unknown.
  mm::Vec3 unknownd0;  // Inferred role: end position; original member name unknown.
  mm::Vec3 unknowne0;  // Inferred role: end target; original member name unknown.
  mm::Vec3 unknownf0;  // Inferred role: current position; original member name unknown.
  mm::Vec3 unknown100; // Inferred role: current target; original member name unknown.
  f32 unknown110;      // Inferred role: play time rate; original member name unknown.
  f32 unknown114;      // Inferred role: play time duration; original member name unknown.
  s32 unknown118;      // Inferred role: move type; original member name unknown.
  f32 unknown11c;      // Inferred role: elapsed play time; original member name unknown.
  s32 unknown120;      // Inferred role: unknown; original member name unknown.
  s32 unknown124;      // Inferred role: unknown; original member name unknown.
  u64 unknown128;      // Inferred role: unknown; original member name unknown.
  s32 unknown130;      // Inferred role: unknown; original member name unknown.
  bool unknown134;     // Inferred role: unknown; original member name unknown.
  bool unknown135;     // Inferred role: unknown; original member name unknown.
  u8 _136[0x140 - 0x136];
};

static_assert(offsetof(ChainAttackCameraEntity, unknownb0) == 0xb0, "");
static_assert(offsetof(ChainAttackCameraEntity, unknownc0) == 0xc0, "");
static_assert(offsetof(ChainAttackCameraEntity, unknownd0) == 0xd0, "");
static_assert(offsetof(ChainAttackCameraEntity, unknowne0) == 0xe0, "");
static_assert(offsetof(ChainAttackCameraEntity, unknownf0) == 0xf0, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown100) == 0x100, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown110) == 0x110, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown114) == 0x114, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown118) == 0x118, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown11c) == 0x11c, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown120) == 0x120, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown124) == 0x124, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown128) == 0x128, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown130) == 0x130, "");
static_assert(offsetof(ChainAttackCameraEntity, unknown134) == 0x134, "");
static_assert(sizeof(ChainAttackCameraEntity) == 0x140, "");

} // namespace gf
