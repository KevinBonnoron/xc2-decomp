#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

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
    FLAG_UNKNOWN_16 = 1 << 16, // Inferred role: release per buffer; original name unknown.
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

  DrLightObj *unknown08;      // Inferred role: prev; original member name unknown.
  DrLightObj *unknown10;      // Inferred role: next; original member name unknown.
  Type unknown18;             // Inferred role: type; original member name unknown.
  u32 unknown1c;              // Inferred role: flags; original member name unknown.
  DrPixlMan *unknown20;       // Inferred role: pixl man; original member name unknown.
  DrPixlShadowObj *unknown28; // Inferred role: shadow; original member name unknown.
};

static_assert(offsetof(DrLightObj, unknown08) == 0x08, "");
static_assert(offsetof(DrLightObj, unknown18) == 0x18, "");
static_assert(offsetof(DrLightObj, unknown1c) == 0x1c, "");
static_assert(offsetof(DrLightObj, unknown20) == 0x20, "");
static_assert(offsetof(DrLightObj, unknown28) == 0x28, "");

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
  void setDir(const mm::Vec3 &direction);
  void setDirShadow(bool isEnable, int index);
  void setMat(const mm::Mat44 &matrix);
  void setMat(const f32 *matrix);
  DrLightObjDir(DrPixlMan *pixlMan);
  ~DrLightObjDir() override;
  void releaseDir();
  void deleteDirShadow();
  void update(DrLightMan *lightMan) override;

  mm::Mat44 unknown30; // Inferred role: matrix; original member name unknown.
  mm::Vec3 unknown70;  // Inferred role: direction; original member name unknown.
  mm::Col4 unknown80;  // Inferred role: color; original member name unknown.
  f32 unknown90;       // Inferred role: intensity; original member name unknown.
};

static_assert(offsetof(DrLightObjDir, unknown30) == 0x30, "");
static_assert(offsetof(DrLightObjDir, unknown70) == 0x70, "");
static_assert(offsetof(DrLightObjDir, unknown80) == 0x80, "");
static_assert(offsetof(DrLightObjDir, unknown90) == 0x90, "");
static_assert(sizeof(DrLightObjDir) == 0xa0, "");

class DrLightObjPnt : public DrLightObj {
public:
  void setMat(const mm::Mat44 &matrix);
  void setMat(const f32 *matrix);
  void setPos(const mm::Vec3 &position);
  void deletePntShadow();
  DrLightObjPnt();
  void initPnt();
  DrLightObjPnt(DrPixlMan *pixlMan);
  ~DrLightObjPnt() override;
  void releasePnt();

  mm::Mat44 unknown30; // Inferred role: matrix; original member name unknown.
  mm::Vec3 m_pos;
  u8 _80[0x90 - 0x80];
  f32 unknown90; // Inferred role: color r; original member name unknown.
  f32 unknown94; // Inferred role: color g; original member name unknown.
  f32 unknown98; // Inferred role: color b; original member name unknown.
  f32 m_size;
  bool unknowna0; // Inferred role: spe enable; original member name unknown.
  u8 _a1[0xa4 - 0xa1];
  f32 unknowna4;    // Inferred role: color intensity; original member name unknown.
  f32 unknowna8;    // Inferred role: tex ofs x; original member name unknown.
  f32 unknownac;    // Inferred role: tex ofs y; original member name unknown.
  f32 unknownb0;    // Inferred role: spe intensity; original member name unknown.
  f32 unknownb4[2]; // Inferred role: spot params; original member name unknown.
};

static_assert(offsetof(DrLightObjPnt, unknown30) == 0x30, "");
static_assert(offsetof(DrLightObjPnt, m_pos) == 0x70, "");
static_assert(offsetof(DrLightObjPnt, unknown90) == 0x90, "");
static_assert(offsetof(DrLightObjPnt, m_size) == 0x9c, "");
static_assert(offsetof(DrLightObjPnt, unknowna0) == 0xa0, "");
static_assert(offsetof(DrLightObjPnt, unknownb0) == 0xb0, "");
static_assert(offsetof(DrLightObjPnt, unknownb4) == 0xb4, "");
static_assert(sizeof(DrLightObjPnt) == 0xc0, "");

class DrLightObjSpt : public DrLightObj {
public:
  void setMat(const mm::Mat44 &matrix);
  void setMat(const f32 *matrix);
  void setPos(const mm::Vec3 &position);
  void deleteSptShadow();
  DrLightObjSpt();
  void initSpt();
  DrLightObjSpt(DrPixlMan *pixlMan);
  ~DrLightObjSpt() override;
  void releaseSpt();
  void setDir(const mm::Vec3 &direction);

  u8 _30[0xbc - 0x30];
  f32 unknownbc; // Inferred role: angle; original member name unknown.
  f32 m_size;
  u8 _c4[0xd4 - 0xc4];
  f32 unknownd4; // Inferred role: spe intensity; original member name unknown.
};

static_assert(offsetof(DrLightObjSpt, unknownbc) == 0xbc, "");
static_assert(offsetof(DrLightObjSpt, m_size) == 0xc0, "");
static_assert(offsetof(DrLightObjSpt, unknownd4) == 0xd4, "");

} // namespace ml
