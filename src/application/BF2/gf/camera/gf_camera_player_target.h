#pragma once
#include <stddef.h>

#include "fw/fw_camera.h"
#include "gf/event/gf_event.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

class PlayerCameraTarget : public fw::CameraTarget, public mm::mtl::PtrSingleton<PlayerCameraTarget>, public IGfEvent {
public:
  static mm::mtl::RTTI m_rtti;

  static PlayerCameraTarget *create();
  PlayerCameraTarget();
  ~PlayerCameraTarget() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void update(const fw::UpdateInfo &info) override;
  void requestResetCamera() override;
  void gevPartyMemberOK(bool isOK) override;
  void writeTargetInfo();

  mm::Vec3 unknown20;       // Inferred role: position of the player; original member name unknown.
  mm::Quat unknown30;       // Inferred role: rotation of the player; original member name unknown.
  bool unknown40;           // Role and original member name unknown.
  bool unknown41;           // Role and original member name unknown.
  bool unknown42;           // Role and original member name unknown.
  bool unknown43;           // Role and original member name unknown.
  bool unknown44;           // Role and original member name unknown.
  bool unknown45;           // Role and original member name unknown.
  bool unknown46;           // Role and original member name unknown.
  f32 unknown48;            // Role and original member name unknown.
  f32 unknown4c;            // Role and original member name unknown.
  mm::Vec3 unknown50;       // Inferred role: up vector of the player; original member name unknown.
  mm::Vec3 unknown60;       // Inferred role: direction of the player; original member name unknown.
  GF_OBJ_HANDLE *unknown70; // Inferred role: player; original member name unknown.
  bool unknown78;           // Inferred role: party member ok; original member name unknown.
  bool unknown79;           // Inferred role: camera reset requested; original member name unknown.
};

static_assert(offsetof(PlayerCameraTarget, unknown20) == 0x20, "");
static_assert(offsetof(PlayerCameraTarget, unknown30) == 0x30, "");
static_assert(offsetof(PlayerCameraTarget, unknown40) == 0x40, "");
static_assert(offsetof(PlayerCameraTarget, unknown48) == 0x48, "");
static_assert(offsetof(PlayerCameraTarget, unknown50) == 0x50, "");
static_assert(offsetof(PlayerCameraTarget, unknown60) == 0x60, "");
static_assert(offsetof(PlayerCameraTarget, unknown70) == 0x70, "");
static_assert(offsetof(PlayerCameraTarget, unknown78) == 0x78, "");
static_assert(sizeof(PlayerCameraTarget) == 0x80, "");

} // namespace gf
