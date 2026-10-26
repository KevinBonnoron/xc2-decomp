#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "skd/skd_force_interface.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class WindProbe;

class ForceCalculator : public mm::mtl::ReferenceObject, public skd::ForceInterface {
public:
  static mm::mtl::RTTI m_rtti;

  virtual const mm::mtl::RTTI *getRTTI() const;
};

class WindForceCalculator : public ForceCalculator {
public:
  static mm::mtl::RTTI m_rtti;

  static mm::mtl::IntrusivePtr<WindForceCalculator> create();
  WindForceCalculator();
  ~WindForceCalculator() override;
  void unbindProbe();
  void bindProbe(WindProbe &probe);
  void calcForce(f32 deltaTime, const skd::DynamicsSolver &solver, mm::mtl::Vector<mm::Vec3> *forces) override;
  const mm::mtl::RTTI *getRTTI() const override;

  WindProbe *unknown18; // Inferred role: bound probe; original member name unknown.
  f32 unknown20;        // Inferred role: power ratio; original member name unknown.
};

static_assert(offsetof(WindForceCalculator, unknown18) == 0x18, "");
static_assert(offsetof(WindForceCalculator, unknown20) == 0x20, "");
static_assert(sizeof(WindForceCalculator) == 0x28, "");

} // namespace fw
