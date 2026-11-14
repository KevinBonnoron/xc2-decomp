#pragma once
#include "event/anm_f32.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaEffectPlayer {
public:
  enum VF_TYPE {
    VF_TYPE_UNKNOWN_0 = 0, // Inferred role: main; original name unknown.
    VF_TYPE_UNKNOWN_1 = 1, // Inferred role: sub; original name unknown.
    VF_TYPE_MAX = 2,
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: volume fade main flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: volume fade sub flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: rim bloom flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: after image flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: volume fade anim main flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: volume fade anim sub flag; original name unknown.
  };

  CharaEffectPlayer();
  virtual ~CharaEffectPlayer() = default;
  void create(gf::GF_OBJ_HANDLE *handle);
  void destroy();
  void stopAfterImage();
  void stopRimBloom();
  void stopVolumeFade(VF_TYPE type);
  void update(f32 delta);
  void updateVolumeFadeAnim(VF_TYPE type, f32 delta);
  void render(const mm::Vec3 &position, f32 height);
  void playVolumeFade(VF_TYPE type, int id, const mm::Vec3 &position, const mm::Vec3 &scale, f32 frame, f32 rate, int mode, f32 speed);
  void playVolumeFadeAnim(VF_TYPE type, f32 rate, f32 frame);
  void playRimBloom(int id);
  void playAfterImage(int id, int count, f32 interval, f32 alpha, f32 life);

private:
  u32 unknown08;                   // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10;    // Inferred role: handle; original member name unknown.
  int unknown18[VF_TYPE_MAX];      // Inferred role: volume fade ids; original member name unknown.
  mm::Vec3 unknown20[VF_TYPE_MAX]; // Inferred role: volume fade positions; original member name unknown.
  mm::Vec3 unknown40[VF_TYPE_MAX]; // Inferred role: volume fade scales; original member name unknown.
  f32 unknown60[VF_TYPE_MAX];      // Inferred role: volume fade frames; original member name unknown.
  f32 unknown68[VF_TYPE_MAX];      // Inferred role: volume fade rates; original member name unknown.
  int unknown70[VF_TYPE_MAX];      // Inferred role: volume fade modes; original member name unknown.
  f32 unknown78[VF_TYPE_MAX];      // Inferred role: volume fade speeds; original member name unknown.
  AnmF32 unknown80[VF_TYPE_MAX];   // Inferred role: volume fade anms; original member name unknown.
  int unknown2a0;                  // Inferred role: rim bloom id; original member name unknown.
  int unknown2a4;                  // Inferred role: after image id; original member name unknown.
  int unknown2a8;                  // Inferred role: after image count; original member name unknown.
  f32 unknown2ac;                  // Inferred role: after image interval; original member name unknown.
  f32 unknown2b0;                  // Inferred role: after image alpha; original member name unknown.
  f32 unknown2b4;                  // Inferred role: after image life; original member name unknown.
};

static_assert(sizeof(CharaEffectPlayer) == 0x2c0, "");

} // namespace event
