#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace event {

class OutsiderField {
public:
  enum TYPE {
    TYPE_NONE,
    TYPE_CIRCLE,
  };

  OutsiderField();
  TYPE getType() const { return unknown00; }
  f32 getRadius() const { return unknown40; }
  void clear();
  void update();
  void draw();
  void setField(TYPE type, const mm::Vec3 &pos, f32 radius);
  bool isInside(const mm::Vec3 &pos) const;

private:
  TYPE unknown00;     // Inferred role: type; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: define pos; original member name unknown.
  f32 unknown20;      // Inferred role: define radius; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: pos; original member name unknown.
  f32 unknown40;      // Inferred role: radius; original member name unknown.
};

static_assert(sizeof(OutsiderField) == 0x50, "");

} // namespace event
