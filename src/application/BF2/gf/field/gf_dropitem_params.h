#pragma once
#include <stddef.h>

#include "gf/field/gf_dropitem_param.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

class GfDropitemParams {
public:
  virtual ~GfDropitemParams() {}
  void create();
  void dispose();
  void update();
  bool isBdatIdValid(u32 bdatId) const;

  mm::mtl::Vector<GfDropitemParam> unknown08; // Inferred role: parameters of each bdat id; original member name unknown.
  u32 unknown30;                              // Inferred role: first bdat id; original member name unknown.
};

static_assert(offsetof(GfDropitemParams, unknown08) == 0x08, "");
static_assert(offsetof(GfDropitemParams, unknown30) == 0x30, "");
static_assert(sizeof(GfDropitemParams) == 0x38, "");

} // namespace gf
