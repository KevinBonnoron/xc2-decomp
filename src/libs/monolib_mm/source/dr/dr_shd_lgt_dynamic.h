#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrLightMan;
class DrLightObjPnt;
class DrLightObjSpt;
class DrMan;
class DrShdLgtMan;

enum DrShdLgtDynamicType {
  DR_SHD_LGT_DYNAMIC_TILE_BASED,
  DR_SHD_LGT_DYNAMIC_CLUSTERED,
};

class DrShdLgtDynamic {
public:
  virtual ~DrShdLgtDynamic() {}
  virtual void stockBegin() = 0;
  virtual void stockEnd() = 0;
  virtual void update() = 0;
  virtual void setupCate(int cate) { m_cate = cate; }
  virtual void addViewInfo(int cate) = 0;
  virtual void delViewInfo(int cate) = 0;
  virtual void stockPntList(DrLightObjPnt *light) = 0;
  virtual void stockSptList(DrLightObjSpt *light) = 0;
  virtual void render(DrShdLgtMan *shdLgtMan, DrLightMan *lightMan) = 0;
  virtual void debugRender() = 0;

  s32 m_cate;
  DrMan *m_drMan;
};

static_assert(offsetof(DrShdLgtDynamic, m_cate) == 0x8, "");
static_assert(offsetof(DrShdLgtDynamic, m_drMan) == 0x10, "");

} // namespace ml
