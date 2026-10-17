#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

class GfFieldBgm : public mm::mtl::PtrSingleton<GfFieldBgm> {
public:
  bool isBossBgmCopied() const;
};

} // namespace gf
