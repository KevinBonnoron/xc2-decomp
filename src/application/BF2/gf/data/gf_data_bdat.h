#pragma once
#include "types.h"

namespace gf {

struct GfSetupParam;

class GfDataBdat {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static u8 *getFP(u32 bdat);
};

} // namespace gf
