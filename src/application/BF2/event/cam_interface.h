#pragma once
#include "fw/fw_camera.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
struct Vec3;
}

namespace fw {
enum CAMERA_TYPE : int;
}

namespace event {

class CamInterface : public fw::Camera {
public:
  CamInterface(fw::CAMERA_TYPE type);
  virtual ~CamInterface() {}
  void setEnable(bool isEnable);
  void setTargetPos(const mm::Vec3 &position, const mm::Vec3 &target, f32 roll);
  void setRoll(f32 roll);
  void setFov(f32 fov);
  void setNearFar(f32 nearClip, f32 farClip);

private:
  u32 type;
  bool isEnable;
  f32 currentRoll;
  mm::mtl::IntrusivePtr<fw::Camera> self;
};

static_assert(sizeof(CamInterface) == 0xc0, "");

} // namespace event
