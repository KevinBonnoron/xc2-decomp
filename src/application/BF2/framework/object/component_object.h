#pragma once
#include "types.h"
#include <stddef.h>

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class UpdatableObject;

class ComponentObject {
public:
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~ComponentObject() {}

  u32 getLayer() const;

  UpdatableObject *unknown08; // Inferred role: owner; original member name unknown.
};

static_assert(offsetof(ComponentObject, unknown08) == 0x08, "");

} // namespace fw
