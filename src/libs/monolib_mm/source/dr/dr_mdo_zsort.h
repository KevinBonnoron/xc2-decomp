#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

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
  void setViewCloud(DrMdoZSortObj *object);
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

  u8 _00[0x28 - 0x00];
  DrMdoZSortObj *unknown28; // Inferred role: first object of the next chain; original member name unknown.
  DrMdoZSortObj *unknown30; // Inferred role: first object of the parent chain; original member name unknown.
  DrMdoZSortObj *unknown38; // Inferred role: cloud object; original member name unknown.
};

static_assert(offsetof(DrMdoZSortMan, unknown28) == 0x28, "");
static_assert(offsetof(DrMdoZSortMan, unknown30) == 0x30, "");
static_assert(offsetof(DrMdoZSortMan, unknown38) == 0x38, "");

} // namespace ml
