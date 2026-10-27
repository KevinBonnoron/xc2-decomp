#pragma once

namespace mm {
struct Plane;
struct Vec3;
} // namespace mm

namespace fw {

class IKFootGroundInterface;

enum IKFootIndex {
  IK_FOOT_INDEX_UNKNOWN_0,
  IK_FOOT_INDEX_UNKNOWN_1,
  IK_FOOT_INDEX_UNKNOWN_2,
  IK_FOOT_INDEX_UNKNOWN_3,
  IK_FOOT_INDEX_UNKNOWN_4,
  IK_FOOT_INDEX_UNKNOWN_5,
};

// Declaration rebuilt from the vtable slots used by gf::GfComIK::Ground (five virtual functions, then the destructor at offsets 0x28 and 0x30).
class IKGroundInterface {
public:
  virtual IKFootGroundInterface *getFootGround(IKFootIndex index) = 0;
  virtual const mm::Plane *getPlane() const = 0;
  virtual const mm::Vec3 *getHitPos() const = 0;
  virtual const mm::Plane *getPlaneSub() const = 0;
  virtual const mm::Vec3 *getHitPosSub() const = 0;
  virtual ~IKGroundInterface() {}
};

} // namespace fw
