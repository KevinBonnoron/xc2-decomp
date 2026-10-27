#pragma once
#include <stddef.h>

#include <math.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class DrMan;

class DrMdoZSortObj {
public:
  void setNext(DrMdoZSortObj *next);
  void setParent(DrMdoZSortObj *parent);
  DrMdoZSortObj *getNext();
  DrMdoZSortObj *getParent();
  DrMdoZSortObj(void *owner);
  virtual ~DrMdoZSortObj() {}
  virtual void SetupRender() {}
  virtual void ZPrepassRender() {}
  virtual void ThicknessRenderFirst() {}
  virtual void ThicknessRenderSecond() {}
  virtual void render() {}
  virtual void GBuffRender() {}
  virtual void lightPrePassRender() {}
  virtual void alphaRender() {}
  virtual void spAlphaRender() {}
  virtual void refractionRender() {}

  DrMdoZSortObj *m_next;
  DrMdoZSortObj *m_parent;
  void *unknown18; // Inferred role: owner; original member name unknown.
};

static_assert(offsetof(DrMdoZSortObj, m_next) == 0x08, "");
static_assert(offsetof(DrMdoZSortObj, m_parent) == 0x10, "");
static_assert(offsetof(DrMdoZSortObj, unknown18) == 0x18, "");

class DrMdoZSortMan {
public:
  void beginViewWorld();
  void endViewWorld();
  void stockObj(DrMdoZSortObj *object, int index);
  void setViewCloud(DrMdoZSortObj *object);
  void setViewCloudBack(DrMdoZSortObj *object);
  void setViewLast(DrMdoZSortObj *object);
  void setViewSeamLast(DrMdoZSortObj *object);
  void setViewWorldPos(DrMdoZSortObj *object, const mm::Vec3 &position);
  void setViewWorldPosLastAlpha(DrMdoZSortObj *object, const mm::Vec3 &position);
  void setViewWorldPosFastAlpha(DrMdoZSortObj *object, const mm::Vec3 &position);

  // Inferred role: distance from the view position to the position over the far distance, the common start of the setViewWorldPos functions; original name unknown.
  f32 unknown001(const mm::Vec3 &position) const {
    f32 dx = position.x - unknown40.x;
    f32 dy = position.y - unknown40.y;
    f32 dz = position.z - unknown40.z;
    return sqrtf(dx * dx + dy * dy + dz * dz) / unknown50;
  }
  void viewRender();
  void viewAlphaRender();
  void viewGBuffRender();
  void viewSetupRender();
  void viewSpAlphaRender();
  void viewZPrepassRender();
  void viewRefractionRender();
  void viewLightPrePassRender();
  void viewThicknessRenderFirst();
  void viewThicknessRenderSecond();

  DrMan *unknown00;          // Inferred role: dr man; original member name unknown.
  DrMdoZSortObj **unknown08; // Inferred role: first objects per chain; original member name unknown.
  DrMdoZSortObj **unknown10; // Inferred role: last objects per chain; original member name unknown.
  u32 *unknown18;            // Inferred role: used chain bits; original member name unknown.
  u8 _20[0x28 - 0x20];
  DrMdoZSortObj *unknown28; // Inferred role: first object of the next chain; original member name unknown.
  DrMdoZSortObj *unknown30; // Inferred role: first object of the parent chain; original member name unknown.
  DrMdoZSortObj *unknown38; // Inferred role: cloud object; original member name unknown.
  mm::Vec3 unknown40;       // Inferred role: view position; original member name unknown.
  f32 unknown50;            // Inferred role: far distance; original member name unknown.
  f32 unknown54;            // Inferred role: distance power; original member name unknown.
};

static_assert(offsetof(DrMdoZSortMan, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoZSortMan, unknown10) == 0x10, "");
static_assert(offsetof(DrMdoZSortMan, unknown18) == 0x18, "");
static_assert(offsetof(DrMdoZSortMan, unknown40) == 0x40, "");
static_assert(offsetof(DrMdoZSortMan, unknown50) == 0x50, "");
static_assert(offsetof(DrMdoZSortMan, unknown54) == 0x54, "");
static_assert(offsetof(DrMdoZSortMan, unknown28) == 0x28, "");
static_assert(offsetof(DrMdoZSortMan, unknown30) == 0x30, "");
static_assert(offsetof(DrMdoZSortMan, unknown38) == 0x38, "");

} // namespace ml
