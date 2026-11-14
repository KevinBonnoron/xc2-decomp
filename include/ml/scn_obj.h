#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DebDraw;
class Scn;

class ScnObj {
public:
  enum Type {
    TYPE_UNKNOWN_1 = 1, // Inferred role: model; original name unknown.
    TYPE_UNKNOWN_2 = 2, // Inferred role: cam; original name unknown.
    TYPE_UNKNOWN_4 = 4, // Inferred role: light; original name unknown.
    TYPE_UNKNOWN_5 = 5, // Inferred role: ibl; original name unknown.
    TYPE_UNKNOWN_6 = 6, // Inferred role: clip; original name unknown.
  };

  ScnObj(Scn *scn, u16 type) : unknown08(scn), unknown10(type), m_delete(false) {}
  virtual ~ScnObj() {}
  virtual void update() {}
  virtual void renderDebug(DebDraw *debDraw) {}
  virtual void apply() {}
  virtual void tail() {}
  virtual const char *getName() const = 0;
  virtual void setDelete();

  Scn *unknown08; // Inferred role: scn; original member name unknown.
  u16 unknown10;  // Inferred role: type; original member name unknown.
  bool m_delete;
};

static_assert(offsetof(ScnObj, unknown08) == 0x08, "");
static_assert(offsetof(ScnObj, unknown10) == 0x10, "");
static_assert(offsetof(ScnObj, m_delete) == 0x12, "");

} // namespace ml
