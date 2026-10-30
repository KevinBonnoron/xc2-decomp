#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrLightMan;
class DrLightObjPnt;
class DrLightObjSpt;
class DrMan;
class DrShdLgtMan;

// Inferred role: shd lgt dynamic type; original type name unknown.
enum unknown063 {
  unknown063_0, // Inferred role: tile based; original name unknown.
  unknown063_1, // Inferred role: clustered; original name unknown.
};

class DrShdLgtDynamic {
public:
  virtual ~DrShdLgtDynamic() {}
  virtual void stockBegin() = 0;
  virtual void stockEnd() = 0;
  virtual void update() = 0;
  virtual void setupCate(int cate);
  virtual void addViewInfo(int cate) = 0;
  virtual void delViewInfo(int cate) = 0;
  virtual void stockPntList(DrLightObjPnt *light) = 0;
  virtual void stockSptList(DrLightObjSpt *light) = 0;
  virtual void render(DrShdLgtMan *shdLgtMan, DrLightMan *lightMan) = 0;
  virtual void debugRender() = 0;

  s32 unknown08;    // Inferred role: cate; original member name unknown.
  DrMan *unknown10; // Inferred role: dr man; original member name unknown.
};

static_assert(offsetof(DrShdLgtDynamic, unknown08) == 0x8, "");
static_assert(offsetof(DrShdLgtDynamic, unknown10) == 0x10, "");

} // namespace ml
