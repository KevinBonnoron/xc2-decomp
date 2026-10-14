#pragma once

namespace gf {

struct GfSetupParam;

class GfDataBdat {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
};

} // namespace gf
