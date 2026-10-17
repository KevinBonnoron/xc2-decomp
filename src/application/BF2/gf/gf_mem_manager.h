#pragma once

namespace gf {

struct GfSetupParam;

class GfMemManager {
public:
  static void buildCoreMemory(const GfSetupParam &param);
  static void destroyCoreMemory();
  static void build(const GfSetupParam &param);
  static void destroy();
};

} // namespace gf
