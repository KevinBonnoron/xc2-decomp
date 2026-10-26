#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfFieldBgm : public mm::mtl::PtrSingleton<GfFieldBgm> {
public:
  bool isBossBgmCopied() const;
  void setGimmickBgmID(u32 id);
};

} // namespace gf
