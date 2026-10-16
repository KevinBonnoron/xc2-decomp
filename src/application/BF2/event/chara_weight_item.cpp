#include "event/chara_weight_item.h"

#include "event/chara_util.h"
#include "fw/fw_debug.h"

namespace event {

void CharaWeightItem::create(gf::GfObj *obj, gf::AnimLayer layer, const char *, const char *stat) {
  if (CharaUtil::hasResAsm(obj) && CharaUtil::easeIn(obj, stat, layer)) {
    CharaUtil::setEaseWeight(obj, stat, layer, 0.0f);
    flags.set(FLAG_EASE_IN, true);
  } else {
    flags.set(FLAG_EASE_IN, false);
  }
  mLayer = layer;
  mStat = stat;
  mAddWeights[WEIGHT_LAYER_PLAY] = 1.0f;
  mAddWeights[WEIGHT_LAYER_WINK] = 1.0f;
  mSpeeds[WEIGHT_LAYER_PLAY] = 1.0f;
  mSpeeds[WEIGHT_LAYER_WINK] = 1.0f;
}

void CharaWeightItem::destroy(gf::GfObj *obj) {
  if (flags.test(FLAG_EASE_IN)) {
    CharaUtil::easeOut(obj, mStat, mLayer);
  }
  flags.set(FLAG_EASE_IN, false);
}

void CharaWeightItem::update(gf::GfObj *obj, f32 delta) {
  mWeightAnms[WEIGHT_LAYER_PLAY].update(delta);
  mWeightAnms[WEIGHT_LAYER_WINK].update(delta);
  mWeight = 1.0f - (1.0f - mWeightAnms[WEIGHT_LAYER_PLAY].getValue()) * (1.0f - mWeightAnms[WEIGHT_LAYER_WINK].getValue());
  if (flags.test(FLAG_EASE_IN)) {
    CharaUtil::setEaseWeight(obj, mStat, mLayer, mWeight * mAddWeights[WEIGHT_LAYER_PLAY] * mAddWeights[WEIGHT_LAYER_WINK]);
  }
  if (flags.test(FLAG_EASE_IN)) {
    CharaUtil::setEaseSpeed(obj, mStat, mLayer, mSpeeds[WEIGHT_LAYER_PLAY] * mSpeeds[WEIGHT_LAYER_WINK]);
  }
  if (mWeight <= 0.0f && mWeightAnms[WEIGHT_LAYER_PLAY].isEnd() && mWeightAnms[WEIGHT_LAYER_WINK].isEnd()) {
    flags.set(FLAG_ACTIVE, false);
  }
}

void CharaWeightItem::render(int x, int y) {
  fw::debug::drawFont(x, y, mStat);
  fw::debug::drawFont(x + 120, y, "%.1f", mWeight * mAddWeights[WEIGHT_LAYER_PLAY] * mAddWeights[WEIGHT_LAYER_WINK]);
}

bool CharaWeightItem::isActive() const { return flags.test(FLAG_ACTIVE); }

const char *CharaWeightItem::getStat() const { return mStat; }

void CharaWeightItem::easeIn(f32 frame, f32 weight, f32 speed, CV_TYPE cv, WeightLayer layer) {
  AnmF32 &anm = mWeightAnms[layer];
  anm.clear();
  if (frame > 0.0f) {
    anm.append(0.0f, mWeight, cv);
  }
  anm.append(frame, weight, cv);
  mSpeeds[layer] = speed;
  flags.set(FLAG_ACTIVE, true);
}

void CharaWeightItem::easeOut(f32 frame, CV_TYPE cv, WeightLayer layer) {
  AnmF32 &anm = mWeightAnms[layer];
  anm.clear();
  if (frame > 0.0f) {
    anm.append(0.0f, mWeight, cv);
  }
  anm.append(frame, 0.0f, cv);
}

void CharaWeightItem::setAddWeight(f32 weight, WeightLayer layer) { mAddWeights[layer] = weight; }

} // namespace event
