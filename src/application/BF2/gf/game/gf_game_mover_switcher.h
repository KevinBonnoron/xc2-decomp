#pragma once

namespace gf {

struct GfSetupParam;

class GfGameMoverSwitcher {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
};

} // namespace gf
