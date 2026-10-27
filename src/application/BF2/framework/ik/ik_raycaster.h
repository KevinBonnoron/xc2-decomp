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

class IKFootGroundInterface {
public:
  virtual const mm::Plane *getPlane() const = 0;
  virtual ~IKFootGroundInterface() {}
};

class PlaneRayCaster : public Raycaster {
public:
  PlaneRayCaster();
  void bind(IKFootGroundInterface &ground);
  ~PlaneRayCaster() override {}

  IKFootGroundInterface *unknown08; // Inferred role: ground interface; original member name unknown.
};

} // namespace fw
