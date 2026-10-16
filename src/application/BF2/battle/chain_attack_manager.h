#pragma once
#include "mm_mtl/singleton.h"

namespace btl {

class ChainAttackManager : public mm::mtl::PtrSingleton<ChainAttackManager> {
public:
  bool IsProc(bool) const;
  int GetGroupIndex() const;
};

} // namespace btl
