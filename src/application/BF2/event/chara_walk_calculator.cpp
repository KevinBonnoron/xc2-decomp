#include "event/chara_walk_calculator.h"

namespace event {

bool CharaWalkCalculator::s_initializeAcc;
bool CharaWalkCalculator::s_initializeDec;
f32 CharaWalkCalculator::s_lengthAcc[2][LENGTH_COUNT];
f32 CharaWalkCalculator::s_lengthDec[2][LENGTH_COUNT];

CharaWalkCalculator::CharaWalkCalculator()
    : unknown00(0), unknown10(0.0f, 0.0f, 0.0f), unknown20(0.0f, 0.0f, 0.0f), unknown30(0.0f), unknown40(0.0f, 0.0f, 0.0f), unknown50(0.0f, 0.0f, 0.0f), unknown60(30.0f), unknown64(0.0f),
      unknown84(0.0f) {}

void CharaWalkCalculator::clear() { unknown00 = 0; }

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

void CharaWalkCalculator::test() {}

} // namespace event
