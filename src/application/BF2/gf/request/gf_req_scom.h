#pragma once
#include "types.h"

namespace gf {

enum SCOM_TYPE {
  SCOM_TYPE_CREATE_PARTY_OBJ = 0x16,
};

class SCOM_ADD_MONEY {
public:
  static void create(int money);
};

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

class GfReqSmallCom {
public:
  static bool isExistCommand(SCOM_TYPE type);
};

} // namespace gf
