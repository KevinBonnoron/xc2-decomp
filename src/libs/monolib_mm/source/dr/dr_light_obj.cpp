#include "dr/dr_light_obj.h"

#include <math.h>

#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_man.h"

namespace ml {

void DrLightObj::setSoftShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_SOFT_SHADOW : unknown1c | FLAG_SOFT_SHADOW; }

void DrLightObj::setAmbModeOn(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_AMB_MODE_ON : unknown1c | FLAG_AMB_MODE_ON; }

void DrLightObj::setSubtractOn(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_SUBTRACT : unknown1c | FLAG_SUBTRACT; }

void DrLightObj::setCharShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_CHAR_SHADOW : unknown1c | FLAG_CHAR_SHADOW; }

void DrLightObj::setBaseMapShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_BASE_MAP_SHADOW : unknown1c | FLAG_BASE_MAP_SHADOW; }

void DrLightObj::setInstMapShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_INST_MAP_SHADOW : unknown1c | FLAG_INST_MAP_SHADOW; }

void DrLightObj::setInstSelMapShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_INST_SEL_MAP_SHADOW : unknown1c | FLAG_INST_SEL_MAP_SHADOW; }

bool DrLightObj::isShadowLight() const { return unknown1c & FLAG_SHADOW; }

void DrLightObj::setCacheShadow(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_CACHE_SHADOW : unknown1c | FLAG_CACHE_SHADOW; }

bool DrLightObj::isSubtract() const { return (unknown1c & FLAG_SUBTRACT) != 0; }

void DrLightObj::setCullON(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_CULL_ON : unknown1c | FLAG_CULL_ON; }

bool DrLightObj::isCullON() const { return (unknown1c & FLAG_CULL_ON) != 0; }

DrLightObj::DrLightObj() : unknown08(nullptr), unknown10(nullptr), unknown1c(0), unknown20(nullptr), unknown28(nullptr) {}

DrLightObj::DrLightObj(DrPixlMan *pixlMan) : unknown10(nullptr), unknown1c(0), unknown20(pixlMan), unknown28(nullptr) { unknown08 = nullptr; }

void DrLightObj::setTexLoop(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_TEX_LOOP : unknown1c | FLAG_TEX_LOOP; }

void DrLightObj::setOutLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_OUT_LGT_OFF : unknown1c | FLAG_OUT_LGT_OFF; }

void DrLightObj::setInLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_IN_LGT_OFF : unknown1c | FLAG_IN_LGT_OFF; }

void DrLightObj::setCharLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_CHAR_LGT_OFF : unknown1c | FLAG_CHAR_LGT_OFF; }

void DrLightObj::setMapLgtOff(bool isEnable) { unknown1c = !isEnable ? unknown1c & ~FLAG_MAP_LGT_OFF : unknown1c | FLAG_MAP_LGT_OFF; }

bool DrLightObj::isAmb() const { return unknown18 == TYPE_AMB; }

bool DrLightObj::isDir() const { return unknown18 == TYPE_DIR; }

bool DrLightObj::isPnt() const { return unknown18 == TYPE_PNT; }

bool DrLightObj::isSpt() const { return unknown18 == TYPE_SPT; }

bool DrLightObj::isSoftShadow() const { return (unknown1c & FLAG_SOFT_SHADOW) != 0; }

bool DrLightObj::isCharShadow() const { return (unknown1c & FLAG_CHAR_SHADOW) != 0; }

bool DrLightObj::isBaseMapShadow() const { return (unknown1c & FLAG_BASE_MAP_SHADOW) != 0; }

bool DrLightObj::isInstMapShadow() const { return (unknown1c & FLAG_INST_MAP_SHADOW) != 0; }

bool DrLightObj::isInstSelMapShadow() const { return (unknown1c & FLAG_INST_SEL_MAP_SHADOW) != 0; }

bool DrLightObj::isTex() const { return (unknown1c & FLAG_TEX) != 0; }

bool DrLightObj::isTexLoop() const { return (unknown1c & FLAG_TEX_LOOP) != 0; }

bool DrLightObj::isOutLgtOff() const { return (unknown1c & FLAG_OUT_LGT_OFF) != 0; }

bool DrLightObj::isInLgtOff() const { return (unknown1c & FLAG_IN_LGT_OFF) != 0; }

bool DrLightObj::isCharLgtOff() const { return (unknown1c & FLAG_CHAR_LGT_OFF) != 0; }

bool DrLightObj::isMapLgtOff() const { return (unknown1c & FLAG_MAP_LGT_OFF) != 0; }

bool DrLightObj::isAmbModeOn() const { return (unknown1c & FLAG_AMB_MODE_ON) != 0; }

bool DrLightObj::isCacheShadow() const { return (unknown1c & FLAG_CACHE_SHADOW) != 0; }

DrLightObjAmb::DrLightObjAmb() {}

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

void DrLightObjDir::setDirShadow(bool isEnable, int index) {
  releaseDir();
  if (isEnable) {
    unknown1c |= FLAG_SHADOW;
    unknown28 = unknown20->unknown7f0->unknown178->createDirCacheShadow(this, index);
  } else {
    unknown1c &= ~FLAG_SHADOW;
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
  unknown18 = TYPE_DIR;
}

DrLightObjDir::~DrLightObjDir() { releaseDir(); }

void DrLightObjDir::releaseDir() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

void DrLightObjDir::deleteDirShadow() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

void DrLightObjDir::update(DrLightMan *lightMan) {
  if (unknown1c & FLAG_SHADOW) {
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

void DrLightObjPnt::deletePntShadow() { releasePnt(); }

DrLightObjPnt::~DrLightObjPnt() { releasePnt(); }

void DrLightObjPnt::releasePnt() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

void DrLightObjSpt::deleteSptShadow() { releaseSpt(); }

DrLightObjSpt::~DrLightObjSpt() { releaseSpt(); }

void DrLightObjSpt::releaseSpt() {
  if (unknown28 != nullptr) {
    DrPixlShadowMan *shadowMan = unknown20->unknown7f0->unknown178;
    unknown1c &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(unknown28);
    unknown28 = nullptr;
  }
}

} // namespace ml
