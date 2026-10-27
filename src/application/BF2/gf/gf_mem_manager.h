#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace gf {

struct GfSetupParam;

class GfMemManager {
public:
  static void buildCoreMemory(const GfSetupParam &param);
  static void destroyCoreMemory();
  static void build(const GfSetupParam &param);
  static void destroy();
  static void initializeGame(mtl::ALLOC_HANDLE handle);
  static void finalizeGame();
};

} // namespace gf
