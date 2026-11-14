#include "dr/dr_light_obj.h"

#include <math.h>

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

DrLightObj::DrLightObj(DrPixlMan *pixlMan) : unknown10(nullptr), unknown1c(0), unknown20(pixlMan), unknown28(nullptr) { unknown08 = nullptr; }

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

void DrLightObjPnt::initPnt() {
  unknownb0 = 1.0f;
  m_pos.x = 0.0f;
  unknown90.r = 1.0f;
  unknowna4 = 1.0f;
  unknownac = 0.1f;
  m_pos.y = 0.0f;
  unknown90.g = 1.0f;
  m_pos.z = 0.0f;
  m_size = 5.0f;
  unknowna0 = true;
  unknowna8 = 1.0f;
  unknown90.b = 1.0f;
  unknown18 = TYPE_UNKNOWN_2;
  unknown30 = mm::Mat44::identity;
  unknownb4[0] = 0.0f;
  unknownb4[1] = 0.0f;
}

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

void DrLightObjSpt::deleteSptShadow() { releaseSpt(); }

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
