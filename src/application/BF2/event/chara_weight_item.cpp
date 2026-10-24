#include "event/chara_weight_item.h"

#include "event/chara_util.h"
#include "fw/fw_debug.h"

namespace event {

void CharaWeightItem::create(gf::GfObj *obj, gf::AnimLayer layer, const char *, const char *stat) {
  if (CharaUtil::hasResAsm(obj) && CharaUtil::easeIn(obj, stat, layer)) {
    CharaUtil::setEaseWeight(obj, stat, layer, 0.0f);
    unknown08.set(FLAG_EASE_IN, true);
  } else {
    unknown08.set(FLAG_EASE_IN, false);
  }
  unknown0c = layer;
  m_stat = stat;
  unknown23c[WEIGHT_LAYER_PLAY] = 1.0f;
  unknown23c[WEIGHT_LAYER_WINK] = 1.0f;
  unknown244[WEIGHT_LAYER_PLAY] = 1.0f;
  unknown244[WEIGHT_LAYER_WINK] = 1.0f;
}

void CharaWeightItem::destroy(gf::GfObj *obj) {
  if (unknown08.test(FLAG_EASE_IN)) {
    CharaUtil::easeOut(obj, m_stat, unknown0c);
  }
  unknown08.set(FLAG_EASE_IN, false);
}

void CharaWeightItem::update(gf::GfObj *obj, f32 delta) {
  unknown18[WEIGHT_LAYER_PLAY].update(delta);
  unknown18[WEIGHT_LAYER_WINK].update(delta);
  unknown238 = 1.0f - (1.0f - unknown18[WEIGHT_LAYER_PLAY].getValue()) * (1.0f - unknown18[WEIGHT_LAYER_WINK].getValue());
  if (unknown08.test(FLAG_EASE_IN)) {
    CharaUtil::setEaseWeight(obj, m_stat, unknown0c, unknown238 * unknown23c[WEIGHT_LAYER_PLAY] * unknown23c[WEIGHT_LAYER_WINK]);
  }
  if (unknown08.test(FLAG_EASE_IN)) {
    CharaUtil::setEaseSpeed(obj, m_stat, unknown0c, unknown244[WEIGHT_LAYER_PLAY] * unknown244[WEIGHT_LAYER_WINK]);
  }
  if (unknown238 <= 0.0f && unknown18[WEIGHT_LAYER_PLAY].isEnd() && unknown18[WEIGHT_LAYER_WINK].isEnd()) {
    unknown08.set(FLAG_ACTIVE, false);
  }
}

void CharaWeightItem::render(int x, int y) {
  fw::debug::drawFont(x, y, m_stat);
  fw::debug::drawFont(x + 120, y, "%.1f", unknown238 * unknown23c[WEIGHT_LAYER_PLAY] * unknown23c[WEIGHT_LAYER_WINK]);
}

bool CharaWeightItem::isActive() const { return unknown08.test(FLAG_ACTIVE); }

const char *CharaWeightItem::getStat() const { return m_stat; }

void CharaWeightItem::easeIn(f32 frame, f32 weight, f32 speed, CV_TYPE cv, WeightLayer layer) {
  AnmF32 &anm = unknown18[layer];
  anm.clear();
  if (frame > 0.0f) {
    anm.append(0.0f, unknown238, cv);
  }
  anm.append(frame, weight, cv);
  unknown244[layer] = speed;
  unknown08.set(FLAG_ACTIVE, true);
}

void CharaWeightItem::easeOut(f32 frame, CV_TYPE cv, WeightLayer layer) {
  AnmF32 &anm = unknown18[layer];
  anm.clear();
  if (frame > 0.0f) {
    anm.append(0.0f, unknown238, cv);
  }
  anm.append(frame, 0.0f, cv);
}

void CharaWeightItem::setAddWeight(f32 weight, WeightLayer layer) { unknown23c[layer] = weight; }

} // namespace event
