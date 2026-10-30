#pragma once

namespace mm {
struct Plane;
struct Vec3;
} // namespace mm

namespace fw {

class Raycaster {
public:
  virtual ~Raycaster() {}
  virtual bool castRay(const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 *position, mm::Vec3 *normal);
};

// Evidence: the vtable of the game is 0x20 bytes (two virtual functions, no virtual destructor) and
// gf::GfComIK::FootGround overrides getPlane then getHitPos (1.0.0: 0x7100528714, 0x7100528750).
class IKFootGroundInterface {
public:
  virtual const mm::Plane *getPlane() const = 0;
  virtual const mm::Vec3 *getHitPos() const = 0;
  ~IKFootGroundInterface() {}
};

class PlaneRayCaster : public Raycaster {
public:
  PlaneRayCaster();
  void bind(IKFootGroundInterface &ground);
  ~PlaneRayCaster() override {}

  IKFootGroundInterface *unknown08; // Inferred role: ground interface; original member name unknown.
};

} // namespace fw
