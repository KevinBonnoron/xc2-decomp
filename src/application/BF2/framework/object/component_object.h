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

  UpdatableObject *owner;
};

static_assert(offsetof(ComponentObject, owner) == 0x08, "");

} // namespace fw
