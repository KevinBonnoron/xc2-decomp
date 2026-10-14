#pragma once

namespace gf {

struct GfSetupParam;

class GfGameCamera {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void clear();
};

} // namespace gf
