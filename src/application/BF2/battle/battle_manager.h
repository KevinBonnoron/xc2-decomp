#pragma once
#include "mm_mtl/singleton.h"

namespace btl {

class BattleManager : public mm::mtl::PtrSingleton<BattleManager> {
public:
  static bool isInitialized();
};

} // namespace btl
