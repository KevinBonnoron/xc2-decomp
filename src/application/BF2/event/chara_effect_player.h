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
  virtual ~CharaEffectPlayer() {}
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
  mm::mtl::BitFlag<FLAG_MAX> flags;
  gf::GF_OBJ_HANDLE *handle;
  int volumeFadeIds[VF_TYPE_MAX];
  mm::Vec3 volumeFadePositions[VF_TYPE_MAX];
  mm::Vec3 volumeFadeScales[VF_TYPE_MAX];
  f32 volumeFadeFrames[VF_TYPE_MAX];
  f32 volumeFadeRates[VF_TYPE_MAX];
  int volumeFadeModes[VF_TYPE_MAX];
  f32 volumeFadeSpeeds[VF_TYPE_MAX];
  AnmF32 mVolumeFadeAnms[VF_TYPE_MAX];
  int mRimBloomID;
  int afterImageId;
  int afterImageCount;
  f32 afterImageInterval;
  f32 afterImageAlpha;
  f32 afterImageLife;
};

static_assert(sizeof(CharaEffectPlayer) == 0x2c0, "");

} // namespace event
