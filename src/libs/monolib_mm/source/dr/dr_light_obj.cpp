#include "dr/dr_light_obj.h"

#include <math.h>
#include <string.h>

#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_man.h"

namespace ml {

void DrLightObj::setSoftShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_1 : unknown1c | FLAG_UNKNOWN_1; }

void DrLightObj::setAmbModeOn(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_11 : unknown1c | FLAG_UNKNOWN_11; }

void DrLightObj::setSubtractOn(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_22 : unknown1c | FLAG_UNKNOWN_22; }

void DrLightObj::setCharShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_18 : unknown1c | FLAG_UNKNOWN_18; }

void DrLightObj::setBaseMapShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_19 : unknown1c | FLAG_UNKNOWN_19; }

void DrLightObj::setInstMapShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_20 : unknown1c | FLAG_UNKNOWN_20; }

void DrLightObj::setInstSelMapShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_21 : unknown1c | FLAG_UNKNOWN_21; }

bool DrLightObj::isShadowLight() const { return unknown1c & FLAG_UNKNOWN_0; }

void DrLightObj::setCacheShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_2 : unknown1c | FLAG_UNKNOWN_2; }

bool DrLightObj::isSubtract() const { return (unknown1c & FLAG_UNKNOWN_22) != 0; }

void DrLightObj::setCullON(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_30 : unknown1c | FLAG_UNKNOWN_30; }

bool DrLightObj::isCullON() const { return (unknown1c & FLAG_UNKNOWN_30) != 0; }

DrLightObj::DrLightObj() : unknown08(nullptr), unknown10(nullptr), unknown1c(0), unknown20(nullptr), unknown28(nullptr) {}

// The statements are in the order that matches this constructor (0x71007e9858) and its copies inlined into the derived light constructors
// and the createXxxLight functions: a member initialiser list, in declaration order or with the one body statement it replaces, changes the
// stores of the inlined copies.
DrLightObj::DrLightObj(DrPixlMan *pixlMan) {
  unknown10 = nullptr;
  unknown20 = pixlMan;
  unknown08 = nullptr;
  unknown1c = 0;
  unknown28 = nullptr;
}

void DrLightObj::setTexLoop(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_4 : unknown1c | FLAG_UNKNOWN_4; }

void DrLightObj::setOutLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_12 : unknown1c | FLAG_UNKNOWN_12; }

void DrLightObj::setInLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_13 : unknown1c | FLAG_UNKNOWN_13; }

void DrLightObj::setCharLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_14 : unknown1c | FLAG_UNKNOWN_14; }

void DrLightObj::setMapLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_UNKNOWN_15 : unknown1c | FLAG_UNKNOWN_15; }

bool DrLightObj::isAmb() const { return unknown18 == TYPE_UNKNOWN_0; }

bool DrLightObj::isDir() const { return unknown18 == TYPE_UNKNOWN_1; }

bool DrLightObj::isPnt() const { return unknown18 == TYPE_UNKNOWN_2; }

bool DrLightObj::isSpt() const { return unknown18 == TYPE_UNKNOWN_3; }

bool DrLightObj::isSoftShadow() const { return (unknown1c & FLAG_UNKNOWN_1) != 0; }

bool DrLightObj::isCharShadow() const { return (unknown1c & FLAG_UNKNOWN_18) != 0; }

bool DrLightObj::isBaseMapShadow() const { return (unknown1c & FLAG_UNKNOWN_19) != 0; }

bool DrLightObj::isInstMapShadow() const { return (unknown1c & FLAG_UNKNOWN_20) != 0; }

bool DrLightObj::isInstSelMapShadow() const { return (unknown1c & FLAG_UNKNOWN_21) != 0; }

bool DrLightObj::isTex() const { return (unknown1c & FLAG_UNKNOWN_3) != 0; }

bool DrLightObj::isTexLoop() const { return (unknown1c & FLAG_UNKNOWN_4) != 0; }

bool DrLightObj::isOutLgtOff() const { return (unknown1c & FLAG_UNKNOWN_12) != 0; }

bool DrLightObj::isInLgtOff() const { return (unknown1c & FLAG_UNKNOWN_13) != 0; }

bool DrLightObj::isCharLgtOff() const { return (unknown1c & FLAG_UNKNOWN_14) != 0; }

bool DrLightObj::isMapLgtOff() const { return (unknown1c & FLAG_UNKNOWN_15) != 0; }

bool DrLightObj::isAmbModeOn() const { return (unknown1c & FLAG_UNKNOWN_11) != 0; }

bool DrLightObj::isCacheShadow() const { return (unknown1c & FLAG_UNKNOWN_2) != 0; }

DrLightObjAmb::DrLightObjAmb() {}

DrLightObjAmb::DrLightObjAmb(DrPixlMan *pixlMan) : DrLightObj(pixlMan) {}

namespace {

// Inferred role: copies 16 floats into a matrix; shared by the setMat of the light objects; original name unknown.
void unknown031(mm::Mat44 &destination, const f32 *matrix) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      destination.rows[i][j] = matrix[i * 4 + j];
    }
  }
}

// Inferred role: normalized direction of a light matrix (its third row negated); shared by DrLightObjDir::setMat and
// DrLightObjSpt::setMat; original name unknown.
void unknown032(mm::Vec3 &direction, const mm::Mat44 &matrix) {
  direction = mm::Vec3(matrix.rows[0][0] * 0.0f + matrix.rows[1][0] * 0.0f - matrix.rows[2][0],
                       matrix.rows[0][1] * 0.0f + matrix.rows[1][1] * 0.0f - matrix.rows[2][1],
                       matrix.rows[0][2] * 0.0f + matrix.rows[1][2] * 0.0f - matrix.rows[2][2]);
  direction.unknown001();
}

} // namespace

DrLightObjAmb::~DrLightObjAmb() { releaseAmb(); }

void DrLightObjAmb::releaseAmb() {}

DrLightObjDir::DrLightObjDir() : DrLightObj() { initDir(); }

DrLightObjDir::DrLightObjDir(DrPixlMan *pixlMan) : DrLightObj(pixlMan) { initDir(); }

void DrLightObjDir::setDir(const mm::Vec3 &direction) {
  f32 pitch = atan2f(direction.y, sqrtf(direction.x * direction.x + direction.z * direction.z));
  f32 yaw = atan2f(direction.x, -direction.z);
  unknown30.setRotXYZ(mm::Vec3(pitch, -yaw, 0.0f));
  unknown70 = direction;
}

void DrLightObjDir::setMat(const f32 *matrix) {
  unknown031(unknown30, matrix);
  unknown032(unknown70, unknown30);
}

void DrLightObjDir::setDirShadow(bool isEnable, int index) {
  releaseDir();
  if (isEnable) {
    unknown1c |= FLAG_UNKNOWN_0;
    unknown28 = unknown20->unknown7f0->unknown178->createDirCacheShadow(this, index);
  } else {
    unknown1c &= ~FLAG_UNKNOWN_0;
  }
}

void DrLightObjDir::initDir() {
  unknown80.r = 1.0f;
  unknown80.g = 1.0f;
  unknown80.b = 1.0f;
  unknown80.a = 1.0f;
  unknown70.x = 0.0f;
  unknown70.y = 0.0f;
  unknown70.z = -1.0f;
  unknown90 = 1.0f;
  unknown30 = mm::Mat44::identity;
  unknown18 = TYPE_UNKNOWN_1;
}

DrLightObjDir::~DrLightObjDir() { releaseDir(); }

void DrLightObjDir::releaseDir() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_UNKNOWN_0;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

void DrLightObjDir::deleteDirShadow() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_UNKNOWN_0;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

void DrLightObjDir::update(DrLightMan *lightMan) {
  if (unknown1c & FLAG_UNKNOWN_0) {
    if (unknown90 > 0.0f) {
      unknown20->unknown800->unknown00 |= 4;
    } else {
      unknown20->unknown800->unknown00 |= 0x20;
    }
  }
}

void DrLightObjPnt::setMat(const mm::Mat44 &matrix) {
  unknown30 = matrix;
  m_pos = mm::Vec3(unknown30.rows[3][0], unknown30.rows[3][1], unknown30.rows[3][2]);
}

void DrLightObjPnt::setMat(const f32 *matrix) {
  unknown031(unknown30, matrix);
  m_pos = unknown30.unknown004();
}

// The translation row is copied from a Vec3 filled by memcpy, the way Mat44::unknown004 reads it: the game loads x and y as
// one 64-bit value and splits it (ldr x8, [x1]; lsr x9, x8, #32; stp w8, w9 at 0x71007dc0e4); the component-wise Mat44::setTrans
// and a memcpy straight into the row give 13 and 11 instructions against the game's 12.
void DrLightObjPnt::setPos(const mm::Vec3 &position) {
  m_pos = position;
  mm::Vec3 pos;
  memcpy(&pos, &position, sizeof(f32) * 3);
  unknown30.setTrans(pos);
}

DrLightObjPnt::DrLightObjPnt() : DrLightObj() { initPnt(); }

// The statement order is the one found to match this function (0x71007e9d68) and the two constructors that inline it (0x71007e9cdc,
// 0x71007e9dd4): the order of the members and the store order of the game do not (the game's stores are scheduled differently).
void DrLightObjPnt::initPnt() {
  m_pos.x = 0.0f;
  unknown90.g = 1.0f;
  unknown90.r = 1.0f;
  unknownb0 = 1.0f;
  unknowna4 = 1.0f;
  m_pos.y = 0.0f;
  m_size = 5.0f;
  m_pos.z = 0.0f;
  unknowna0 = true;
  unknowna8 = 1.0f;
  unknown90.b = 1.0f;
  unknownac = 0.1f;
  unknown18 = TYPE_UNKNOWN_2;
  unknown30 = mm::Mat44::identity;
  unknownb4[0] = 0.0f;
  unknownb4[1] = 0.0f;
}

DrLightObjPnt::DrLightObjPnt(DrPixlMan *pixlMan) : DrLightObj(pixlMan) { initPnt(); }

void DrLightObjPnt::deletePntShadow() { releasePnt(); }

DrLightObjPnt::~DrLightObjPnt() { releasePnt(); }

void DrLightObjPnt::releasePnt() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_UNKNOWN_0;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

void DrLightObjSpt::setMat(const f32 *matrix) {
  unknown031(unknown30, matrix);
  unknown032(unknown90, unknown30);
  m_pos = unknown30.unknown004();
}

// The translation row is set from a Vec3 copy of the position, as in setDir and event::EffectCtrl: the game loads x and y as one 64-bit
// value (ldr x8, [x1] at 0x71007dc248); setTrans(position) gives 13 instructions against the game's 12.
void DrLightObjSpt::setPos(const mm::Vec3 &position) {
  m_pos = position;
  unknown30.setTrans(mm::Vec3(position));
}

// Pitch and yaw as in DrLightObjDir::setDir (x and y loaded as a pair, ldp at 0x71007ea24c); the translation row is set from a Vec3
// copy of m_pos, which the game loads as one 64-bit value and a word (ldr x8, [x19, #0x70] at 0x71007ea32c), as in event::EffectCtrl.
void DrLightObjSpt::setDir(const mm::Vec3 &direction) {
  f32 pitch = atan2f(direction.y, sqrtf(direction.x * direction.x + direction.z * direction.z));
  f32 yaw = atan2f(direction.x, -direction.z);
  unknown30.unknown011(mm::Vec3(pitch, -yaw, 0.0f));
  unknown30.setTrans(mm::Vec3(m_pos));
  unknown90 = direction;
}

void DrLightObjSpt::deleteSptShadow() { releaseSpt(); }

DrLightObjSpt::DrLightObjSpt() : DrLightObj() { initSpt(); }

// As initPnt: the order of the members and the store order of the game do not match this function (0x71007e9ffc) and the constructors that
// inline it (0x71007e9f44, 0x71007ea094).
void DrLightObjSpt::initSpt() {
  unknownb0.g = 1.0f;
  unknownd4 = 1.0f;
  unknownd0 = 0.0001f;
  unknownb0.b = 1.0f;
  unknownb0.r = 1.0f;
  m_pos.x = 0.0f;
  m_pos.y = 0.0f;
  m_size = 5.0f;
  unknown90.x = 0.0f;
  m_pos.z = 0.0f;
  unknownd8 = 4.0f;
  unknown90.y = 0.0f;
  unknownc4 = true;
  unknowncc = 1.0f;
  unknownc8 = 0.4f;
  unknown90.z = 1.0f;
  unknownbc = 0.9424779f;
  unknown18 = TYPE_UNKNOWN_3;
  unknown30 = mm::Mat44::identity;
  unknowndc = 0.0f;
  unknowne0 = 0.5f;
  unknowne4 = 0.0f;
}

DrLightObjSpt::DrLightObjSpt(DrPixlMan *pixlMan) : DrLightObj(pixlMan) { initSpt(); }

DrLightObjSpt::~DrLightObjSpt() { releaseSpt(); }

void DrLightObjSpt::releaseSpt() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_UNKNOWN_0;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

} // namespace ml
