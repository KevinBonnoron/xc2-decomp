#pragma once
#include "event/anm_f32.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaEffectPlayer {
public:
  enum VF_TYPE {
    VF_TYPE_MAIN = 0,
    VF_TYPE_SUB = 1,
    VF_TYPE_MAX = 2,
  };

  enum {
    FLAG_VOLUME_FADE_MAIN = 0,
    FLAG_VOLUME_FADE_SUB = 1,
    FLAG_RIM_BLOOM = 2,
    FLAG_AFTER_IMAGE = 3,
    FLAG_VOLUME_FADE_ANIM_MAIN = 4,
    FLAG_VOLUME_FADE_ANIM_SUB = 5,
    FLAG_MAX = 32,
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
  mm::mtl::unknown027<FLAG_MAX> unknown08; // Inferred role: flags; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10;            // Inferred role: handle; original member name unknown.
  int unknown18[VF_TYPE_MAX];              // Inferred role: volume fade ids; original member name unknown.
  mm::Vec3 unknown20[VF_TYPE_MAX];         // Inferred role: volume fade positions; original member name unknown.
  mm::Vec3 unknown40[VF_TYPE_MAX];         // Inferred role: volume fade scales; original member name unknown.
  f32 unknown60[VF_TYPE_MAX];              // Inferred role: volume fade frames; original member name unknown.
  f32 unknown68[VF_TYPE_MAX];              // Inferred role: volume fade rates; original member name unknown.
  int unknown70[VF_TYPE_MAX];              // Inferred role: volume fade modes; original member name unknown.
  f32 unknown78[VF_TYPE_MAX];              // Inferred role: volume fade speeds; original member name unknown.
  AnmF32 unknown80[VF_TYPE_MAX];           // Inferred role: volume fade anms; original member name unknown.
  int unknown2a0;                          // Inferred role: rim bloom id; original member name unknown.
  int unknown2a4;                          // Inferred role: after image id; original member name unknown.
  int unknown2a8;                          // Inferred role: after image count; original member name unknown.
  f32 unknown2ac;                          // Inferred role: after image interval; original member name unknown.
  f32 unknown2b0;                          // Inferred role: after image alpha; original member name unknown.
  f32 unknown2b4;                          // Inferred role: after image life; original member name unknown.
};

static_assert(sizeof(CharaEffectPlayer) == 0x2c0, "");

} // namespace event
