#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
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
    TYPE_UNKNOWN_0, // Inferred role: amb; original name unknown.
    TYPE_UNKNOWN_1, // Inferred role: dir; original name unknown.
    TYPE_UNKNOWN_2, // Inferred role: pnt; original name unknown.
    TYPE_UNKNOWN_3, // Inferred role: spt; original name unknown.
  };

  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0,   // Inferred role: shadow; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1,   // Inferred role: soft shadow; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2,   // Inferred role: cache shadow; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3,   // Inferred role: tex; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4,   // Inferred role: tex loop; original name unknown.
    FLAG_UNKNOWN_16 = 1 << 16, // Inferred role: release per buffer; original name unknown.
    FLAG_UNKNOWN_11 = 1 << 11, // Inferred role: amb mode on; original name unknown.
    FLAG_UNKNOWN_12 = 1 << 12, // Inferred role: out lgt off; original name unknown.
    FLAG_UNKNOWN_13 = 1 << 13, // Inferred role: in lgt off; original name unknown.
    FLAG_UNKNOWN_14 = 1 << 14, // Inferred role: char lgt off; original name unknown.
    FLAG_UNKNOWN_15 = 1 << 15, // Inferred role: map lgt off; original name unknown.
    FLAG_UNKNOWN_18 = 1 << 18, // Inferred role: char shadow; original name unknown.
    FLAG_UNKNOWN_19 = 1 << 19, // Inferred role: base map shadow; original name unknown.
    FLAG_UNKNOWN_20 = 1 << 20, // Inferred role: inst map shadow; original name unknown.
    FLAG_UNKNOWN_21 = 1 << 21, // Inferred role: inst sel map shadow; original name unknown.
    FLAG_UNKNOWN_22 = 1 << 22, // Inferred role: subtract; original name unknown.
    FLAG_UNKNOWN_30 = 1 << 30, // Inferred role: cull on; original name unknown.
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

  mm::Col3 unknown30; // Inferred role: color; original member name unknown.
};

static_assert(offsetof(DrLightObjAmb, unknown30) == 0x30, "");

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
  mm::Col3 unknown90; // Inferred role: color; original member name unknown.
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

  mm::Mat44 unknown30; // Inferred role: matrix; original member name unknown.
  mm::Vec3 m_pos;
  u8 _80[0x90 - 0x80];
  mm::Vec3 unknown90; // Inferred role: direction, the -z axis of the matrix; original member name unknown.
  u8 _a0[0xb0 - 0xa0];
  mm::Col3 unknownb0; // Inferred role: color; original member name unknown.
  f32 unknownbc;      // Inferred role: angle; original member name unknown.
  f32 m_size;
  u8 _c4[0xc8 - 0xc4];
  f32 unknownc8; // Inferred role: color intensity; original member name unknown.
  u8 _cc[0xd0 - 0xcc];
  f32 unknownd0; // Inferred role: light value set from the spot data; original member name unknown.
  f32 unknownd4; // Inferred role: spe intensity; original member name unknown.
  f32 unknownd8; // Inferred role: light value set from the spot data, 4.0 by default; original member name unknown.
  f32 unknowndc; // Inferred role: light value set from the spot data; original member name unknown.
  f32 unknowne0; // Inferred role: light value set from the spot data; original member name unknown.
  f32 unknowne4; // Inferred role: light value set from the spot data; original member name unknown.
  u8 _e8[0xf0 - 0xe8];
};

static_assert(offsetof(DrLightObjSpt, m_pos) == 0x70, "");
static_assert(offsetof(DrLightObjSpt, unknown90) == 0x90, "");
static_assert(offsetof(DrLightObjSpt, unknownb0) == 0xb0, "");
static_assert(offsetof(DrLightObjSpt, unknownbc) == 0xbc, "");
static_assert(offsetof(DrLightObjSpt, unknownc8) == 0xc8, "");
static_assert(offsetof(DrLightObjSpt, unknownd0) == 0xd0, "");
static_assert(offsetof(DrLightObjSpt, m_size) == 0xc0, "");
static_assert(offsetof(DrLightObjSpt, unknownd4) == 0xd4, "");
static_assert(offsetof(DrLightObjSpt, unknowne4) == 0xe4, "");
// Size from the spot light array stride of DrEnvironmentObjLgt::releaseLgt (1.0.0: 0x71007e0210).
static_assert(sizeof(DrLightObjSpt) == 0xf0, "");

} // namespace ml
