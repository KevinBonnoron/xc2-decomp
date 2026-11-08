#pragma once
#include <stddef.h>

#include "gf/field/gf_dropitem_param.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

// Inferred role: parameter table; original type name unknown. The game stores the vtable pointer of GfDropitemParams
// after these members (1.0.0: 0x71002f6cc0), so they belong to a base class without virtual functions. It cannot be
// nested in GfDropitemParams, which derives from it; the name is unique among the types of namespace gf.
struct unknown400 {
  unknown400() : unknown30(0) {}

  mm::mtl::Vector<GfDropitemParam> unknown08; // Inferred role: parameters of each bdat id; original member name unknown.
  u32 unknown30;                              // Inferred role: first bdat id; original member name unknown.
};

class GfDropitemParams : public unknown400 {
public:
  GfDropitemParams();
  virtual ~GfDropitemParams();
  void create();
  void dispose();
  void update();
  bool isBdatIdValid(u32 bdatId) const;
  const GfDropitemParam &getParamByBdatId(u32 bdatId) const;
};

static_assert(offsetof(GfDropitemParams, unknown08) == 0x08, "");
static_assert(offsetof(GfDropitemParams, unknown30) == 0x30, "");
static_assert(sizeof(GfDropitemParams) == 0x38, "");

} // namespace gf
