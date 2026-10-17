#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DebDraw;
class Scn;

class ScnObj {
public:
  enum Type {
    TYPE_MODEL = 1,
    TYPE_CAM = 2,
    TYPE_LIGHT = 4,
    TYPE_IBL = 5,
    TYPE_CLIP = 6,
  };

  ScnObj(Scn *scn, u16 type) : m_scn(scn), m_type(type), m_isDelete(false) {}
  virtual ~ScnObj() {}
  virtual void update() {}
  virtual void renderDebug(DebDraw *debDraw) {}
  virtual void apply() {}
  virtual void tail() {}
  virtual const char *getName() const = 0;
  virtual void setDelete();

  Scn *m_scn;
  u16 m_type;
  bool m_isDelete;
};

static_assert(offsetof(ScnObj, m_scn) == 0x08, "");
static_assert(offsetof(ScnObj, m_type) == 0x10, "");
static_assert(offsetof(ScnObj, m_isDelete) == 0x12, "");

} // namespace ml
