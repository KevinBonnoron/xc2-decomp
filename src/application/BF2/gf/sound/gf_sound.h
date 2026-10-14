#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

class GfSound : public mm::mtl::PtrSingleton<GfSound> {
public:
  void setupGame();
};

} // namespace gf
