#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameManager {
public:
  static GF_OBJ_HANDLE *getPartyLeaderDriver();
  static bool isBattle();
  static bool isChangeNormalHomuraForce(u32 blade);
};

} // namespace gf
