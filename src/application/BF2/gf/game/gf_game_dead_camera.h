#pragma once
#include "gf/game/sequential_play/gf_play_factory.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {
class Camera;
} // namespace fw

namespace gf {

class GfDeadCamera {
public:
  GfDeadCamera(GfPlayerDead dead);
  ~GfDeadCamera();

  mm::mtl::IntrusivePtr<fw::Camera> unknown00; // Inferred role: camera pushed on the first camera layer; original member name unknown.
};

static_assert(sizeof(GfDeadCamera) == 0x8, "");

} // namespace gf
