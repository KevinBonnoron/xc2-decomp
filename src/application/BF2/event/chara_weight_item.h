#pragma once
#include "event/anm_f32.h"
#include "event/curve.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
class GfObj;
} // namespace gf

namespace event {

enum WeightLayer {
  WEIGHT_LAYER_PLAY = 0,
  WEIGHT_LAYER_WINK = 1,
  WEIGHT_LAYER_MAX = 2,
};

class CharaWeightItem {
public:
  enum {
    FLAG_EASE_IN = 0,
    FLAG_ACTIVE = 1,
    FLAG_MAX = 32,
  };

  CharaWeightItem() : flags(), mStat(""), mWeight(0.0f) {
    mAddWeights[WEIGHT_LAYER_PLAY] = 1.0f;
    mAddWeights[WEIGHT_LAYER_WINK] = 1.0f;
    mSpeeds[WEIGHT_LAYER_PLAY] = 1.0f;
    mSpeeds[WEIGHT_LAYER_WINK] = 1.0f;
  }

  virtual ~CharaWeightItem() {}
  void create(gf::GfObj *obj, gf::AnimLayer layer, const char *, const char *stat);
  void destroy(gf::GfObj *obj);
  void update(gf::GfObj *obj, f32 delta);
  void render(int x, int y);
  bool isActive() const;
  const char *getStat() const;
  void easeIn(f32 frame, f32 weight, f32 speed, CV_TYPE cv, WeightLayer layer);
  void easeOut(f32 frame, CV_TYPE cv, WeightLayer layer);
  void setAddWeight(f32 weight, WeightLayer layer);

private:
  mm::mtl::BitFlag<FLAG_MAX> flags;
  gf::AnimLayer mLayer;
  const char *mStat;
  AnmF32 mWeightAnms[WEIGHT_LAYER_MAX];
  f32 mWeight;
  f32 mAddWeights[WEIGHT_LAYER_MAX];
  f32 mSpeeds[WEIGHT_LAYER_MAX];
};

static_assert(sizeof(CharaWeightItem) == 0x250, "");

} // namespace event
