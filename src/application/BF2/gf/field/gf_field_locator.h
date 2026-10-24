#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class AFieldLocator {
public:
  virtual ~AFieldLocator();
  virtual int getIconBdatId() const;
  virtual u32 getPosNum() const = 0;
  virtual const mm::Vec3 *getPos(u32 index) const = 0;
  virtual int getMapBdatId() const;
};

class GfFieldLocator {
public:
  virtual ~GfFieldLocator();
  bool isOtherMap() const;

  u8 _08[0x18 - 0x08];
  AFieldLocator *unknown18; // Inferred role: locator; original member name unknown.
};

static_assert(offsetof(GfFieldLocator, unknown18) == 0x18, "");
static_assert(sizeof(GfFieldLocator) == 0x20, "");

} // namespace gf
