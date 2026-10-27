#include "gf/camera/chain_attack/gf_camera_chain_attack.h"

#include <math.h>

namespace gf {

ChainAttackCameraEntity::~ChainAttackCameraEntity() {}

void ChainAttackCameraEntity::onActivate() {}

void ChainAttackCameraEntity::calcSpeedTypeLinearSpacing() {
  f32 rate = unknown11c / unknown114;
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ChainAttackCameraEntity::calcSpeedTypeFastOut() {
  f32 rate = fastOut(unknown11c / unknown114);
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ChainAttackCameraEntity::calcSpeedTypeSlowOut() {
  f32 rate = slowOut(unknown11c / unknown114);
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ChainAttackCameraEntity::calcSpeedTypeFastInFastOut() {
  f32 rate = fastInFastOut(unknown11c / unknown114);
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

f32 ChainAttackCameraEntity::curve(f32 a, f32 b, f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return (1.0f - x) * a + x * b;
}

f32 ChainAttackCameraEntity::slowOut(f32 t) {
  f32 x = sinf((1.0f - t) * 1.5707964f + 4.712389f) + 1.0f;
  return 1.0f - (x + (1.0f - x) * 0.0f);
}

f32 ChainAttackCameraEntity::fastOut(f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return x + (1.0f - x) * 0.0f;
}

f32 ChainAttackCameraEntity::fastInFastOut(f32 t) { return (tanf(t * 1.8849556f + 2.1991148f) + 1.38f) / 2.76f; }

void ChainAttackCameraEntity::setPlayTimeRate(f32 rate) {
  unknown110 = rate;
  unknown114 = 0.0f;
  unknown11c = 0.0f;
}

void ChainAttackCameraEntity::setPlayTimeDuration(f32 duration) {
  unknown110 = 0.0f;
  unknown114 = duration;
  unknown11c = 0.0f;
}

void ChainAttackCameraEntity::setMoveType(int moveType) { unknown118 = moveType; }

const mm::mtl::RTTI *ChainAttackCameraEntity::getRTTI() const { return &m_rtti; }

const char *ChainAttackCameraEntity::getName() const { return "ChainAttackCameraEntity"; }

} // namespace gf
