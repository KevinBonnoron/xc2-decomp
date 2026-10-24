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

  const mm::Pnt<s16> &getPos() const { return unknown08; }

  mm::Pnt<s16> unknown08; // Inferred role: pos; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  mm::Vec2 unknown10; // Inferred role: scale; original member name unknown.
  u8 _18[0x20 - 0x18];
  f32 unknown20;  // Inferred role: rot; original member name unknown.
  bool unknown24; // Inferred role: dirty; original member name unknown.
  u8 _25[0x30 - 0x25];
};

static_assert(offsetof(UITransform, unknown08) == 0x08, "");
static_assert(offsetof(UITransform, unknown10) == 0x10, "");
static_assert(offsetof(UITransform, unknown20) == 0x20, "");
static_assert(offsetof(UITransform, unknown24) == 0x24, "");
static_assert(sizeof(UITransform) == 0x30, "");

} // namespace ui
