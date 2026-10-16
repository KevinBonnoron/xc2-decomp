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
  TYPE getType() const { return mType; }
  f32 getRadius() const { return mRadius; }
  void clear();
  void update();
  void draw();
  void setField(TYPE type, const mm::Vec3 &pos, f32 radius);
  bool isInside(const mm::Vec3 &pos) const;

private:
  TYPE mType;
  mm::Vec3 mDefinePos;
  f32 mDefineRadius;
  mm::Vec3 mPos;
  f32 mRadius;
};

static_assert(sizeof(OutsiderField) == 0x50, "");

} // namespace event
