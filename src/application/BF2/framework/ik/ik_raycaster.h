#pragma once
#include <stddef.h>

#include "anm/anm_foot_placement_ik_solver.h"

namespace mm {
struct Plane;
struct Vec3;
} // namespace mm

namespace fw {

// Evidence: the vtables of the game's Raycaster (1.0.0: 0x7101178530) and PlaneRayCaster (0x71011785d0) hold
// anm::RaycastInterface::~RaycastInterface (0x710018031c) in their first destructor slot, followed by their own deleting
// destructor and castRay, so Raycaster derives from anm::RaycastInterface.
class Raycaster : public anm::RaycastInterface {
public:
  ~Raycaster() override {}
  bool castRay(const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 *position, mm::Vec3 *normal) override;
};

class IKFootGroundInterface;

class PlaneRayCaster : public Raycaster {
public:
  PlaneRayCaster();
  void bind(IKFootGroundInterface &ground);
  ~PlaneRayCaster() override {}

  IKFootGroundInterface *unknown08; // Inferred role: ground interface; original member name unknown.
};

// Evidence: the vtable of the game is 0x20 bytes (two virtual functions, no virtual destructor),
// gf::GfComIK::FootGround overrides getPlane then getHitPos (1.0.0: 0x7100528714, 0x7100528750), and the
// constructor inlined in gf::GfComIK::setup runs the PlaneRayCaster constructor between the vtable stores of this class and of FootGround.
class IKFootGroundInterface {
public:
  virtual const mm::Plane *getPlane() const = 0;
  virtual const mm::Vec3 *getHitPos() const = 0;
  ~IKFootGroundInterface() {}

  PlaneRayCaster unknown08; // Inferred role: ray caster; original member name unknown.
};

static_assert(offsetof(PlaneRayCaster, unknown08) == 0x08, "");
static_assert(sizeof(PlaneRayCaster) == 0x10, "");
static_assert(offsetof(IKFootGroundInterface, unknown08) == 0x08, "");
static_assert(sizeof(IKFootGroundInterface) == 0x18, "");

} // namespace fw
