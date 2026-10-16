#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "types.h"

namespace ui {

class UITransform {
public:
  UITransform();
  virtual ~UITransform();
  void syncParent();
  void setPos(s16 x, s16 y);
  void setScale(f32 x, f32 y);
  void setParent(const UITransform *parent, bool sync);
  UITransform &operator=(const UITransform &other);

  const mm::Pnt<s16> &getPos() const { return pos; }

  mm::Pnt<s16> pos;
  u8 _0c[0x10 - 0x0c];
  mm::Vec2 scale;
  u8 _18[0x20 - 0x18];
  f32 rot;
  bool dirty;
  u8 _25[0x30 - 0x25];
};

static_assert(offsetof(UITransform, pos) == 0x08, "");
static_assert(offsetof(UITransform, scale) == 0x10, "");
static_assert(offsetof(UITransform, rot) == 0x20, "");
static_assert(offsetof(UITransform, dirty) == 0x24, "");
static_assert(sizeof(UITransform) == 0x30, "");

} // namespace ui
