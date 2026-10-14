#pragma once
#include "types.h"

namespace gf {

class SCOM_ADD_DEVELOP {
public:
  static void create(u32 nation, u32 point);
};

class SCOM_LEVELUP_DEVELOP {
public:
  static void create();
};

class SCOM_POPUP {
public:
  static bool createAchievement(u32 blade, u32 achievement, u32 level);
};

} // namespace gf
