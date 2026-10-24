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

  ScnObj(Scn *scn, u16 type) : unknown08(scn), unknown10(type), unknown12(false) {}
  virtual ~ScnObj() {}
  virtual void update() {}
  virtual void renderDebug(DebDraw *debDraw) {}
  virtual void apply() {}
  virtual void tail() {}
  virtual const char *getName() const = 0;
  virtual void setDelete();

  Scn *unknown08; // Inferred role: scn; original member name unknown.
  u16 unknown10;  // Inferred role: type; original member name unknown.
  bool unknown12; // Inferred role: delete; original member name unknown.
};

static_assert(offsetof(ScnObj, unknown08) == 0x08, "");
static_assert(offsetof(ScnObj, unknown10) == 0x10, "");
static_assert(offsetof(ScnObj, unknown12) == 0x12, "");

} // namespace ml
