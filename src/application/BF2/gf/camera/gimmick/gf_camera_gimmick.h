#pragma once
#include "fw/fw_camera.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
struct Vec3;
}

namespace gf {

class GimmickCamera : public fw::Camera {
public:
  static mm::mtl::IntrusivePtr<fw::Camera> create(const char *name, const mm::Vec3 &position, f32 rotation);
  void play();
  bool isPlayEnd() const;
  bool isLoaded() const;
  void setAuto(bool isAuto);
};

} // namespace gf
