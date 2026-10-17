#include "dr/dr_light_obj.h"

#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_pixl_shadow_man.h"

namespace ml {

void DrLightObj::setSoftShadow(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_SOFT_SHADOW : m_flags | FLAG_SOFT_SHADOW; }

void DrLightObj::setAmbModeOn(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_AMB_MODE_ON : m_flags | FLAG_AMB_MODE_ON; }

void DrLightObj::setSubtractOn(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_SUBTRACT : m_flags | FLAG_SUBTRACT; }

void DrLightObj::setCharShadow(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_CHAR_SHADOW : m_flags | FLAG_CHAR_SHADOW; }

void DrLightObj::setBaseMapShadow(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_BASE_MAP_SHADOW : m_flags | FLAG_BASE_MAP_SHADOW; }

void DrLightObj::setInstMapShadow(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_INST_MAP_SHADOW : m_flags | FLAG_INST_MAP_SHADOW; }

void DrLightObj::setInstSelMapShadow(bool isEnable) {
  m_flags = !isEnable ? m_flags & ~FLAG_INST_SEL_MAP_SHADOW : m_flags | FLAG_INST_SEL_MAP_SHADOW;
}

bool DrLightObj::isShadowLight() const { return m_flags & FLAG_SHADOW; }

void DrLightObj::setCacheShadow(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_CACHE_SHADOW : m_flags | FLAG_CACHE_SHADOW; }

bool DrLightObj::isSubtract() const { return (m_flags & FLAG_SUBTRACT) != 0; }

void DrLightObj::setCullON(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_CULL_ON : m_flags | FLAG_CULL_ON; }

bool DrLightObj::isCullON() const { return (m_flags & FLAG_CULL_ON) != 0; }

DrLightObj::DrLightObj() : m_prev(nullptr), m_next(nullptr), m_flags(0), m_pixlMan(nullptr), m_shadow(nullptr) {}

DrLightObj::DrLightObj(DrPixlMan *pixlMan) : m_next(nullptr), m_flags(0), m_pixlMan(pixlMan), m_shadow(nullptr) { m_prev = nullptr; }

void DrLightObj::setTexLoop(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_TEX_LOOP : m_flags | FLAG_TEX_LOOP; }

void DrLightObj::setOutLgtOff(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_OUT_LGT_OFF : m_flags | FLAG_OUT_LGT_OFF; }

void DrLightObj::setInLgtOff(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_IN_LGT_OFF : m_flags | FLAG_IN_LGT_OFF; }

void DrLightObj::setCharLgtOff(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_CHAR_LGT_OFF : m_flags | FLAG_CHAR_LGT_OFF; }

void DrLightObj::setMapLgtOff(bool isEnable) { m_flags = !isEnable ? m_flags & ~FLAG_MAP_LGT_OFF : m_flags | FLAG_MAP_LGT_OFF; }

bool DrLightObj::isAmb() const { return m_type == TYPE_AMB; }

bool DrLightObj::isDir() const { return m_type == TYPE_DIR; }

bool DrLightObj::isPnt() const { return m_type == TYPE_PNT; }

bool DrLightObj::isSpt() const { return m_type == TYPE_SPT; }

bool DrLightObj::isSoftShadow() const { return (m_flags & FLAG_SOFT_SHADOW) != 0; }

bool DrLightObj::isCharShadow() const { return (m_flags & FLAG_CHAR_SHADOW) != 0; }

bool DrLightObj::isBaseMapShadow() const { return (m_flags & FLAG_BASE_MAP_SHADOW) != 0; }

bool DrLightObj::isInstMapShadow() const { return (m_flags & FLAG_INST_MAP_SHADOW) != 0; }

bool DrLightObj::isInstSelMapShadow() const { return (m_flags & FLAG_INST_SEL_MAP_SHADOW) != 0; }

bool DrLightObj::isTex() const { return (m_flags & FLAG_TEX) != 0; }

bool DrLightObj::isTexLoop() const { return (m_flags & FLAG_TEX_LOOP) != 0; }

bool DrLightObj::isOutLgtOff() const { return (m_flags & FLAG_OUT_LGT_OFF) != 0; }

bool DrLightObj::isInLgtOff() const { return (m_flags & FLAG_IN_LGT_OFF) != 0; }

bool DrLightObj::isCharLgtOff() const { return (m_flags & FLAG_CHAR_LGT_OFF) != 0; }

bool DrLightObj::isMapLgtOff() const { return (m_flags & FLAG_MAP_LGT_OFF) != 0; }

bool DrLightObj::isAmbModeOn() const { return (m_flags & FLAG_AMB_MODE_ON) != 0; }

bool DrLightObj::isCacheShadow() const { return (m_flags & FLAG_CACHE_SHADOW) != 0; }

DrLightObjAmb::DrLightObjAmb() {}

DrLightObjAmb::~DrLightObjAmb() { releaseAmb(); }

void DrLightObjAmb::releaseAmb() {}

DrLightObjDir::~DrLightObjDir() { releaseDir(); }

void DrLightObjDir::releaseDir() {
  if (m_shadow != nullptr) {
    DrPixlShadowMan *shadowMan = m_pixlMan->m_res->shadowMan;
    m_flags &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(m_shadow);
    m_shadow = nullptr;
  }
}

void DrLightObjDir::deleteDirShadow() {
  if (m_shadow != nullptr) {
    DrPixlShadowMan *shadowMan = m_pixlMan->m_res->shadowMan;
    m_flags &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(m_shadow);
    m_shadow = nullptr;
  }
}

void DrLightObjDir::update(DrLightMan *lightMan) {
  if (m_flags & FLAG_SHADOW) {
    if (m_intensity > 0.0f) {
      m_pixlMan->m_shadowCacheMan->m_flags |= 4;
    } else {
      m_pixlMan->m_shadowCacheMan->m_flags |= 0x20;
    }
  }
}

DrLightObjPnt::~DrLightObjPnt() { releasePnt(); }

void DrLightObjPnt::releasePnt() {
  if (m_shadow != nullptr) {
    DrPixlShadowMan *shadowMan = m_pixlMan->m_res->shadowMan;
    m_flags &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(m_shadow);
    m_shadow = nullptr;
  }
}

DrLightObjSpt::~DrLightObjSpt() { releaseSpt(); }

void DrLightObjSpt::releaseSpt() {
  if (m_shadow != nullptr) {
    DrPixlShadowMan *shadowMan = m_pixlMan->m_res->shadowMan;
    m_flags &= ~FLAG_SHADOW;
    shadowMan->releaseShadow(m_shadow);
    m_shadow = nullptr;
  }
}

} // namespace ml
