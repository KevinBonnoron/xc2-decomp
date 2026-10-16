#pragma once
#include "event/anm_f32.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf
namespace mm {
struct Vec3;
} // namespace mm

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

private:
  mm::mtl::BitFlag<FLAG_MAX> flags;
  gf::GF_OBJ_HANDLE *handle;
  u8 _18[0x80 - 0x18];
  AnmF32 mVolumeFadeAnms[VF_TYPE_MAX];
  int mRimBloomID;
};

static_assert(sizeof(CharaEffectPlayer) == 0x2a8, "");

} // namespace event
