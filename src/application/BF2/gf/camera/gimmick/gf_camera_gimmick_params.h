#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GimmickCameraParams {
public:
  struct Param {
    u8 _00[0x2c];
  };

  GimmickCameraParams();
  GimmickCameraParams(void *data, int version);
  virtual ~GimmickCameraParams() {}
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
