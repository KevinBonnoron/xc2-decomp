#pragma once
#include <stddef.h>

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
  void *m_owner;
};

static_assert(offsetof(DrMdoZSortObj, m_next) == 0x08, "");
static_assert(offsetof(DrMdoZSortObj, m_parent) == 0x10, "");
static_assert(offsetof(DrMdoZSortObj, m_owner) == 0x18, "");

} // namespace ml
