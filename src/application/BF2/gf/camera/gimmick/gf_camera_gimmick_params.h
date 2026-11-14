#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GimmickCameraParams {
public:
  struct Param {
    f32 unknown00; // Inferred role: position x, read by the GfMenuModelViewCamera constructor; original member name unknown.
    f32 unknown04; // Inferred role: position y; original member name unknown.
    f32 unknown08; // Inferred role: position z; original member name unknown.
    f32 unknown0c; // Inferred role: rotation x; original member name unknown.
    f32 unknown10; // Inferred role: rotation y; original member name unknown.
    f32 unknown14; // Inferred role: rotation z; original member name unknown.
    u8 _18[0x2c - 0x18];
  };

  GimmickCameraParams();
  GimmickCameraParams(void *data, int version);
  virtual ~GimmickCameraParams();
  void setup(void *data, int version);
  int getSize() const;
  const Param &getParam(int index) const;
  static mm::mtl::FixStr<128> getPath(const char *name);

  u32 m_size;
  const Param *unknown10; // Inferred role: parameter array inside the loaded data; original member name unknown.
};

static_assert(offsetof(GimmickCameraParams, m_size) == 0x08, "");
static_assert(offsetof(GimmickCameraParams, unknown10) == 0x10, "");
static_assert(sizeof(GimmickCameraParams) == 0x18, "");
static_assert(sizeof(GimmickCameraParams::Param) == 0x2c, "");

} // namespace gf
