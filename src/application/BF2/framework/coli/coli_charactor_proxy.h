#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {

class ColiObject;

class ColiCharactorProxy {
public:
  ColiCharactorProxy();
  void integrate(const mm::Vec3 &position, const mm::Vec3 &move, mm::Vec3 *result);

  ColiObject *m_coliObject; // Inferred role: coli object; original member name unknown.
  f32 unknown08;            // Inferred role: floor; original member name unknown.
};

static_assert(offsetof(ColiCharactorProxy, m_coliObject) == 0x00, "");
static_assert(offsetof(ColiCharactorProxy, unknown08) == 0x08, "");

} // namespace fw
