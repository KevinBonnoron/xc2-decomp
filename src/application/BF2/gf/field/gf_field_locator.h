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

  u8 _08[0x0c - 0x08];
  int m_iconBdatId;
  int m_mapBdatId;
};

static_assert(offsetof(AFieldLocator, m_iconBdatId) == 0x0c, "");
static_assert(offsetof(AFieldLocator, m_mapBdatId) == 0x10, "");

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
