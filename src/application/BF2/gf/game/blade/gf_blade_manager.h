#pragma once

namespace gf {

struct GfSetupParam;

class GfBladeManager {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void setupGame();
};

} // namespace gf
