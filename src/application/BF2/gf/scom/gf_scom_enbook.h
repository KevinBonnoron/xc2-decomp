#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class SCOM_ENBOOK_IN_BATTLE {
public:
  static void create(GF_OBJ_HANDLE *handle);
};

class SCOM_ENBOOK_BOSS_TIME {
public:
  static void create(GF_OBJ_HANDLE *handle, u32 time);
};

class SCOM_ENBOOK_DEFEAT_ENEMY {
public:
  static void create(GF_OBJ_HANDLE *handle);
};

class SCOM_ENBOOK_DEAD_PLAYER {
public:
  static void create(GF_OBJ_HANDLE *handle);
};

} // namespace gf
