#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrLightObj;
class DrMan;
class MdoShdPxlWrkTex;

class DrPixlShadowObj {
public:
  enum Flag {
    FLAG_UNKNOWN_0 = 1 << 0,
    FLAG_UNKNOWN_1 = 1 << 1,
    FLAG_UNKNOWN_3 = 1 << 3,
    FLAG_UNKNOWN_4 = 1 << 4,
    FLAG_UNKNOWN_5 = 1 << 5,
    FLAG_UNKNOWN_6 = 1 << 6,
  };

  DrPixlShadowObj(DrMan *man, int type, int index) : unknown48(index), unknown4a(0), unknown4c(type), unknown50(0), unknown170(5.0f), unknown174(0.0001f), unknown178(man), unknown190(nullptr) {}
  virtual ~DrPixlShadowObj() {}
  virtual void update();
  virtual void afterUpdate();
  virtual bool dispChk();
  virtual bool clipChk(const mm::Vec3 &position, f32 value, bool flag);
  virtual int clipTypeChk(const mm::Vec3 &position, f32 value);
  virtual bool setSptCalcPos(const mm::Vec3 &position, f32 value);
  virtual void renderLight();
  virtual void stockTile();
  virtual void debugInfo();
  virtual const f32 *getParmTbl() const;
  void createWork(DrLightObj *light, int index, MdoShdPxlWrkTex *work);
  void setInstSelMapShadow(bool value);
  void releaseWork();
  void renderSetup();
  bool renderEnd();
  static void getScaleTranslateToFit(mm::Mat44 *mat, const mm::Vec3 &max, const mm::Vec3 &min);
  static void getLightMatrix(mm::Mat44 &matrix, const mm::Vec3 &position, const mm::Vec3 &target, const mm::Vec3 &up);

  grlib::CGLibDblUniformBlock unknown08; // Inferred role: shadow uniform; original member name unknown.
  MdoShdPxlWrkTex *unknown40;            // Inferred role: shadow work texture; original member name unknown.
  s16 unknown48;                         // Inferred role: shadow index; original member name unknown.
  s16 unknown4a;                         // Inferred role: light index; original member name unknown.
  s16 unknown4c;                         // Inferred role: shadow type; original member name unknown.
  u8 _4e[0x50 - 0x4e];
  u32 unknown50; // Inferred role: flags; original member name unknown.
  u8 _54[0x60 - 0x54];
  mm::Mat44 unknown60;  // Inferred role: light matrix; original member name unknown.
  mm::Mat44 unknowna0;  // Inferred role: light view projection matrix; original member name unknown.
  mm::Mat44 unknowne0;  // Inferred role: light view matrix; original member name unknown.
  mm::Mat44 unknown120; // Inferred role: shadow texture matrix; original member name unknown.
  u8 _160[0x170 - 0x160];
  f32 unknown170;    // Inferred role: shadow distance; original member name unknown.
  f32 unknown174;    // Inferred role: shadow bias; original member name unknown.
  DrMan *unknown178; // Inferred role: owner; original member name unknown.
  u8 _180[0x190 - 0x180];
  // Inferred role: next shadow of the same light; DrPixlShadowMan::createPntShadow (0x7100861d4c) chains a second point shadow here and
  // shadowDebugInfRender (0x710086262c) walks the chain. Original member name unknown.
  DrPixlShadowObj *unknown190;
  DrLightObj *unknown198; // Inferred role: light; original member name unknown.
};

static_assert(offsetof(DrPixlShadowObj, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlShadowObj, unknown40) == 0x40, "");
static_assert(offsetof(DrPixlShadowObj, unknown48) == 0x48, "");
static_assert(offsetof(DrPixlShadowObj, unknown4c) == 0x4c, "");
static_assert(offsetof(DrPixlShadowObj, unknown50) == 0x50, "");
static_assert(offsetof(DrPixlShadowObj, unknown60) == 0x60, "");
static_assert(offsetof(DrPixlShadowObj, unknowna0) == 0xa0, "");
static_assert(offsetof(DrPixlShadowObj, unknowne0) == 0xe0, "");
static_assert(offsetof(DrPixlShadowObj, unknown120) == 0x120, "");
static_assert(offsetof(DrPixlShadowObj, unknown170) == 0x170, "");
static_assert(offsetof(DrPixlShadowObj, unknown178) == 0x178, "");
static_assert(offsetof(DrPixlShadowObj, unknown190) == 0x190, "");
static_assert(offsetof(DrPixlShadowObj, unknown198) == 0x198, "");
static_assert(sizeof(DrPixlShadowObj) == 0x1a0, "");

} // namespace ml
