#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {
class DrLightMan;
class DrPixlMan;
class DrPixlShadowObj;

class DrLightObj {
public:
  enum Type {
    TYPE_AMB,
    TYPE_DIR,
    TYPE_PNT,
    TYPE_SPT,
  };

  enum Flag {
    FLAG_SHADOW = 1 << 0,
    FLAG_SOFT_SHADOW = 1 << 1,
    FLAG_CACHE_SHADOW = 1 << 2,
    FLAG_TEX = 1 << 3,
    FLAG_TEX_LOOP = 1 << 4,
    FLAG_AMB_MODE_ON = 1 << 11,
    FLAG_OUT_LGT_OFF = 1 << 12,
    FLAG_IN_LGT_OFF = 1 << 13,
    FLAG_CHAR_LGT_OFF = 1 << 14,
    FLAG_MAP_LGT_OFF = 1 << 15,
    FLAG_CHAR_SHADOW = 1 << 18,
    FLAG_BASE_MAP_SHADOW = 1 << 19,
    FLAG_INST_MAP_SHADOW = 1 << 20,
    FLAG_INST_SEL_MAP_SHADOW = 1 << 21,
    FLAG_SUBTRACT = 1 << 22,
    FLAG_CULL_ON = 1 << 30,
  };

  void setSoftShadow(bool isEnable);
  void setAmbModeOn(bool isEnable);
  void setSubtractOn(bool isEnable);
  void setCharShadow(bool isEnable);
  void setBaseMapShadow(bool isEnable);
  void setInstMapShadow(bool isEnable);
  void setInstSelMapShadow(bool isEnable);
  bool isShadowLight() const;
  void setCacheShadow(bool isEnable);
  bool isSubtract() const;
  void setCullON(bool isEnable);
  bool isCullON() const;
  DrLightObj();
  DrLightObj(DrPixlMan *pixlMan);
  virtual ~DrLightObj() {}
  virtual void update(DrLightMan *lightMan) {}
  void setTexLoop(bool isEnable);
  void setOutLgtOff(bool isEnable);
  void setInLgtOff(bool isEnable);
  void setCharLgtOff(bool isEnable);
  void setMapLgtOff(bool isEnable);
  bool isAmb() const;
  bool isDir() const;
  bool isPnt() const;
  bool isSpt() const;
  bool isSoftShadow() const;
  bool isCharShadow() const;
  bool isBaseMapShadow() const;
  bool isInstMapShadow() const;
  bool isInstSelMapShadow() const;
  bool isTex() const;
  bool isTexLoop() const;
  bool isOutLgtOff() const;
  bool isInLgtOff() const;
  bool isCharLgtOff() const;
  bool isMapLgtOff() const;
  bool isAmbModeOn() const;
  bool isCacheShadow() const;

  DrLightObj *m_prev;
  DrLightObj *m_next;
  Type m_type;
  u32 m_flags;
  DrPixlMan *m_pixlMan;
  DrPixlShadowObj *m_shadow;
};

static_assert(offsetof(DrLightObj, m_prev) == 0x08, "");
static_assert(offsetof(DrLightObj, m_type) == 0x18, "");
static_assert(offsetof(DrLightObj, m_flags) == 0x1c, "");
static_assert(offsetof(DrLightObj, m_pixlMan) == 0x20, "");
static_assert(offsetof(DrLightObj, m_shadow) == 0x28, "");

class DrLightObjAmb : public DrLightObj {
public:
  DrLightObjAmb();
  DrLightObjAmb(DrPixlMan *pixlMan);
  ~DrLightObjAmb() override;
  void releaseAmb();
};

class DrLightObjDir : public DrLightObj {
public:
  DrLightObjDir();
  void initDir();
  DrLightObjDir(DrPixlMan *pixlMan);
  ~DrLightObjDir() override;
  void releaseDir();
  void deleteDirShadow();
  void update(DrLightMan *lightMan) override;

  u8 _30[0x90 - 0x30];
  f32 m_intensity;
};

static_assert(offsetof(DrLightObjDir, m_intensity) == 0x90, "");

class DrLightObjPnt : public DrLightObj {
public:
  void setMat(const mm::Mat44 &matrix);
  void setPos(const mm::Vec3 &position);
  DrLightObjPnt();
  void initPnt();
  DrLightObjPnt(DrPixlMan *pixlMan);
  ~DrLightObjPnt() override;
  void releasePnt();

  u8 _30[0x9c - 0x30];
  f32 m_size;
  u8 _a0[0xb0 - 0xa0];
  f32 m_speIntensity;
};

static_assert(offsetof(DrLightObjPnt, m_size) == 0x9c, "");
static_assert(offsetof(DrLightObjPnt, m_speIntensity) == 0xb0, "");

class DrLightObjSpt : public DrLightObj {
public:
  void setMat(const mm::Mat44 &matrix);
  void setPos(const mm::Vec3 &position);
  DrLightObjSpt();
  void initSpt();
  DrLightObjSpt(DrPixlMan *pixlMan);
  ~DrLightObjSpt() override;
  void releaseSpt();
  void setDir(const mm::Vec3 &direction);

  u8 _30[0xbc - 0x30];
  f32 m_angle;
  f32 m_size;
  u8 _c4[0xd4 - 0xc4];
  f32 m_speIntensity;
};

static_assert(offsetof(DrLightObjSpt, m_angle) == 0xbc, "");
static_assert(offsetof(DrLightObjSpt, m_size) == 0xc0, "");
static_assert(offsetof(DrLightObjSpt, m_speIntensity) == 0xd4, "");

} // namespace ml
