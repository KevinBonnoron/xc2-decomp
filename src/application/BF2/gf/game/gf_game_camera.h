#pragma once
#include <stddef.h>

#include "fw/fw_camera.h" // IWYU pragma: keep
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"

namespace gf {

struct GfSetupParam;

class GfGameCamera : public mm::mtl::PtrSingleton<GfGameCamera> {
public:
  ~GfGameCamera();
  static void build(const GfSetupParam &param);
  static void destroy();
  static void clear();
  static void setCameraControlType(int type);
  static bool isInitialized();
  void createSubViewCamera();
  void destroySubViewCamera();

  mm::mtl::FixedArray<mm::mtl::IntrusivePtr<fw::Camera>, 3> unknown08; // Inferred role: sub view cameras; original member name unknown.
  bool unknown20;                                                      // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfGameCamera, unknown08) == 0x08, "");
static_assert(offsetof(GfGameCamera, unknown20) == 0x20, "");

} // namespace gf
