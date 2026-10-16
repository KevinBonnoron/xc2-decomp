#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

struct GfSetupParam;

class GfFieldDmgManager : public mm::mtl::PtrSingleton<GfFieldDmgManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
};

} // namespace gf
