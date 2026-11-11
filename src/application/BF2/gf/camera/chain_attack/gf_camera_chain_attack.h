#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "fw/fw_coli_check.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {
struct GF_OBJ_HANDLE;

class ChainAttackCameraEntity : public fw::Camera {
public:
  static mm::mtl::RTTI m_rtti;

  ~ChainAttackCameraEntity() override;
  void onActivate() override;
  void update(const fw::UpdateInfo &info) override;
  void setPoint(const mm::Vec3 &startPosition, const mm::Vec3 &startTarget, const mm::Vec3 &endPosition, const mm::Vec3 &endTarget);
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

  mm::Vec3 unknownb0;             // Inferred role: start position; original member name unknown.
  mm::Vec3 unknownc0;             // Inferred role: start target; original member name unknown.
  mm::Vec3 unknownd0;             // Inferred role: end position; original member name unknown.
  mm::Vec3 unknowne0;             // Inferred role: end target; original member name unknown.
  mm::Vec3 unknownf0;             // Inferred role: current position; original member name unknown.
  mm::Vec3 unknown100;            // Inferred role: current target; original member name unknown.
  f32 unknown110;                 // Inferred role: play time rate; original member name unknown.
  f32 unknown114;                 // Inferred role: play time duration; original member name unknown.
  s32 unknown118;                 // Inferred role: move type; original member name unknown.
  f32 unknown11c;                 // Inferred role: elapsed play time; original member name unknown.
  fw::ColiCheckConfig unknown120; // Inferred role: collision check; original member name unknown.
  u8 _138[0x140 - 0x138];
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
static_assert(sizeof(ChainAttackCameraEntity) == 0x140, "");

class ChainAttackCamera {
public:
  // Layout evidence: getParam (0x71001d3a24) fills it from the bdat columns named in the member comments.
  struct Param {
    u8 unknown00;       // Inferred role: speed type ("SpeedType"); original member name unknown.
    f32 unknown04;      // Inferred role: speed ("SpeedNum"); original member name unknown.
    u8 unknown08;       // Inferred role: move type ("MoveType"); original member name unknown.
    u8 unknown09;       // Inferred role: start look position type ("S_LookPosType"); original member name unknown.
    mm::Vec3 unknown10; // Inferred role: start position ("S_PosX" to "S_PosZ"); original member name unknown.
    mm::Vec3 unknown20; // Inferred role: start target ("S_LookX" to "S_LookZ"); original member name unknown.
    u8 unknown30;       // Inferred role: end look position type ("E_LookPosType"); original member name unknown.
    mm::Vec3 unknown40; // Inferred role: end position ("E_PosX" to "E_PosZ"); original member name unknown.
    mm::Vec3 unknown50; // Inferred role: end target ("E_LookX" to "E_LookZ"); original member name unknown.
  };

  ChainAttackCamera();
  virtual ~ChainAttackCamera();
  void start();
  void end();
  void setCameraParam(const Param &param);
  void destroyCamera(mm::mtl::IntrusivePtr<fw::Camera> *camera, f32 time);
  u32 lottery(u8 camType);

  mm::mtl::IntrusivePtr<fw::Camera> unknown08; // Inferred role: camera; original member name unknown.
  Param unknown10;                             // Inferred role: current parameters; original member name unknown.
  s8 unknown70;                                // Inferred role: enemy size mask; original member name unknown.
  GF_OBJ_HANDLE *unknown78;                    // Inferred role: target object; original member name unknown.
  fw::ColiCheckConfig unknown80;               // Inferred role: collision check; original member name unknown.
};

static_assert(offsetof(ChainAttackCamera::Param, unknown04) == 0x04, "");
static_assert(offsetof(ChainAttackCamera::Param, unknown10) == 0x10, "");
static_assert(offsetof(ChainAttackCamera::Param, unknown30) == 0x30, "");
static_assert(offsetof(ChainAttackCamera::Param, unknown50) == 0x50, "");
static_assert(sizeof(ChainAttackCamera::Param) == 0x60, "");
static_assert(offsetof(ChainAttackCamera, unknown08) == 0x08, "");
static_assert(offsetof(ChainAttackCamera, unknown10) == 0x10, "");
static_assert(offsetof(ChainAttackCamera, unknown70) == 0x70, "");
static_assert(offsetof(ChainAttackCamera, unknown78) == 0x78, "");
static_assert(offsetof(ChainAttackCamera, unknown80) == 0x80, "");

} // namespace gf
