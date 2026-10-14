#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

enum {
  OWNER_BONUS_FAVORITE_VALUE_MAX = 3,
  OWNER_BONUS_BOOSTER_VALUE_MAX = 13,
};

struct OwnerBonus {
  s16 values[14];
};

static_assert(sizeof(OwnerBonus) == 0x1c, "");

class GfGameManager {
public:
  static GF_OBJ_HANDLE *getPartyLeaderDriver();
  static bool isBattle();
  static bool isEvent(bool isIncludeSequentialPlay);
  static OwnerBonus *getOwnerBonus();
  static bool isChangeNormalHomuraForce(u32 blade);
};

} // namespace gf
