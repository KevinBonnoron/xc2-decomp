#include "framework/dynamics/force_calculator.h"
#include "framework/memory/framework_memory.h"
#include "framework/wind/wind_probe.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace fw {

mm::mtl::IntrusivePtr<WindForceCalculator> WindForceCalculator::create() {
#line 31
  return new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) WindForceCalculator();
}

WindForceCalculator::WindForceCalculator() : unknown18(nullptr), unknown20(1.0f) {}

WindForceCalculator::~WindForceCalculator() { unbindProbe(); }

void WindForceCalculator::unbindProbe() { mm::mtl::safeRelease(unknown18); }

void WindForceCalculator::bindProbe(WindProbe &probe) {
  unbindProbe();
  unknown18 = &probe;
  probe.addRef();
}

const mm::mtl::RTTI *WindForceCalculator::getRTTI() const { return &m_rtti; }

} // namespace fw
