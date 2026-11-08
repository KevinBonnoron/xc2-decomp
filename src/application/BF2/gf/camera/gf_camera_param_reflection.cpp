// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/camera/gf_camera_param_reflection.cpp.
#include "gf/camera/gf_camera_param_reflection.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/camera/fusion_combo/gf_camera_fusion_combo.h"
#include "gf/camera/gf_camera_player.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createCameraReflection() {
#line 25
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(2, nullptr);
  PlayerCamera::createReflection(reflection, "normal_camera", 0);
  FusionComboCamera::createReflection(reflection, "fusion_combo_camera", 1);
  return reflection;
}

} // namespace gf
