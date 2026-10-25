#pragma once

namespace gf {

struct GfSetupParam;

class GfGameCamera {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void clear();
  static void setCameraControlType(int type);
};

} // namespace gf
