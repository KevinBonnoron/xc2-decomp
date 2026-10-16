#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
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
  };

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
  DrLightObjPnt();
  void initPnt();
  DrLightObjPnt(DrPixlMan *pixlMan);
  ~DrLightObjPnt() override;
  void releasePnt();
};

class DrLightObjSpt : public DrLightObj {
public:
  DrLightObjSpt();
  void initSpt();
  DrLightObjSpt(DrPixlMan *pixlMan);
  ~DrLightObjSpt() override;
  void releaseSpt();
  void setDir(const mm::Vec3 &direction);
};

} // namespace ml
