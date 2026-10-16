#pragma once
#include "mm_math/mm_rect.h"

namespace mm {
struct Vec3;
template <typename T> struct Pnt;
} // namespace mm

namespace event {

class BouRect : public mm::Rect<int> {
public:
  BouRect();
  virtual ~BouRect();
  void render();
  bool isInside(const mm::Pnt<int> &point) const;
  bool isInside(const mm::Vec3 &position) const;
};

static_assert(sizeof(BouRect) == 0x18, "");

} // namespace event
