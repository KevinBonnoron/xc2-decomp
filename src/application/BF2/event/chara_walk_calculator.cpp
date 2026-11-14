#include "event/chara_walk_calculator.h"

#include <math.h>

namespace event {

bool CharaWalkCalculator::s_initializeAcc;
bool CharaWalkCalculator::s_initializeDec;
f32 CharaWalkCalculator::s_lengthAcc[2][LENGTH_UNKNOWN_50];
f32 CharaWalkCalculator::s_lengthDec[2][LENGTH_UNKNOWN_50];

CharaWalkCalculator::CharaWalkCalculator()
    : unknown00(0), unknown10(0.0f, 0.0f, 0.0f), unknown20(0.0f, 0.0f, 0.0f), unknown30(0.0f), unknown40(0.0f, 0.0f, 0.0f), unknown50(0.0f, 0.0f, 0.0f), unknown60(30.0f), unknown64(0.0f),
      unknown84(0.0f) {}

void CharaWalkCalculator::clear() { unknown00 = 0; }

void CharaWalkCalculator::setup(TYPE type, const mm::Vec3 &from, const mm::Vec3 &to) {
  mm::Vec3 delta = to - from;
  unknown00 = FLAG_UNKNOWN_0;
  switch (type) {
  case TYPE_UNKNOWN_1:
    unknown00 = FLAG_UNKNOWN_0 | FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3;
    break;
  case TYPE_UNKNOWN_2:
    unknown00 = FLAG_UNKNOWN_0 | FLAG_UNKNOWN_2;
    break;
  case TYPE_UNKNOWN_3:
    unknown00 = FLAG_UNKNOWN_0 | FLAG_UNKNOWN_3;
    break;
  case TYPE_UNKNOWN_4:
    unknown00 = FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3;
    break;
  case TYPE_UNKNOWN_5:
    unknown00 = FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2;
    break;
  case TYPE_UNKNOWN_6:
    unknown00 = FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1 | FLAG_UNKNOWN_3;
    break;
  }
  unknown10 = from;
  unknown20 = to;
  unknown30 = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
  unknown40 = delta;
  if (!(fabsf(delta.x) <= 0.000001f && fabsf(delta.y) <= 0.000001f && fabsf(delta.z) <= 0.000001f)) {
    unknown40.unknown001();
  }
  unknown50 = mm::Vec3(unknown40.x, 0.0f, unknown40.z);
  unknown60 = getBlend((unknown00 & FLAG_UNKNOWN_1) != 0);
  unknown64 = calcTotalFrame(sqrtf(delta.x * delta.x + delta.z * delta.z));
  unknown70 = from;
  unknown80 = 0.0f;
  unknown84 = 0.0f;
}

f32 CharaWalkCalculator::getBlend(bool isRun) { return isRun ? 20.0f : 10.0f; }

f32 CharaWalkCalculator::getAccLength(bool isRun, f32 frame) {
  if (frame < 0.0f) {
    return 0.0f;
  }

  int index = frame;
  if (!s_initializeAcc) {
    for (int run = 0; run < 2; run++) {
      f32 length = 0.0f;
      for (u32 i = 0; i <= getBlend(run != 0); i++) {
        length += getAccSpeed(run != 0, i);
        s_lengthAcc[run][i] = length;
      }
    }
    s_initializeAcc = true;
  }
  return isRun ? s_lengthAcc[1][index] : s_lengthAcc[0][index];
}

f32 CharaWalkCalculator::getTopSpeed(bool isRun) { return isRun ? 0.259f : 0.056f; }

f32 CharaWalkCalculator::getDecLength(bool isRun, f32 frame) {
  if (frame < 0.0f) {
    return 0.0f;
  }

  int index = frame;
  if (!s_initializeDec) {
    for (int run = 0; run < 2; run++) {
      f32 length = 0.0f;
      for (u32 i = 0; i <= getBlend(run != 0); i++) {
        length += getDecSpeed(run != 0, i);
        s_lengthDec[run][i] = length;
      }
    }
    s_initializeDec = true;
  }
  return isRun ? s_lengthDec[1][index] : s_lengthDec[0][index];
}

f32 CharaWalkCalculator::getAccSpeed(bool isRun, f32 frame) {
  f32 blend = getBlend(isRun);
  return getTopSpeed(isRun) * frame / blend;
}

f32 CharaWalkCalculator::getDecSpeed(bool isRun, f32 frame) {
  f32 blend = getBlend(isRun);
  return getTopSpeed(isRun) * (blend - frame) / blend;
}

f32 CharaWalkCalculator::calcTotalFrame(f32 length) const {
  u32 flags = unknown00;
  f32 acc = 0.0f;
  f32 dec = 0.0f;
  bool isRun = (flags & FLAG_UNKNOWN_1) != 0;
  bool hasAcc = (flags & FLAG_UNKNOWN_2) != 0;
  bool hasDec = (flags & FLAG_UNKNOWN_3) != 0;
  f32 blend = getBlend(isRun);
  if (hasAcc) {
    acc = getAccLength(isRun, blend);
  }
  if (hasDec) {
    dec = getDecLength(isRun, blend);
  }
  if (acc + dec < length) {
    f32 rest = length;
    f32 frames = 0.0f;
    f32 speed = getTopSpeed(isRun);
    if (hasAcc) {
      rest -= acc;
      frames += blend;
    }
    if (hasDec) {
      rest -= dec;
      frames += blend;
    }
    return frames + rest / speed;
  }
  f32 scale = (flags & (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3)) == (FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3) ? 2.0f : 1.0f;
  for (f32 frame = 0.0f; frame <= blend; frame += 1.0f) {
    if (length <= scale * getAccLength(isRun, frame)) {
      return scale * frame - 1.0f;
    }
  }
  return blend * scale;
}

void CharaWalkCalculator::update(f32 delta) {
  if ((unknown00 & FLAG_UNKNOWN_0) != 0) {
    unknown70 = calcPos(unknown84);
    f32 frame = unknown84;
    unknown80 = calcSpeed(frame);
    frame += delta;
    unknown84 = frame;
    if (unknown64 < frame) {
      unknown64 = frame;
    }
  }
}

void CharaWalkCalculator::test() {}

} // namespace event
