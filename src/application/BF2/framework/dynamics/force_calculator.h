#pragma once
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
};

} // namespace fw
