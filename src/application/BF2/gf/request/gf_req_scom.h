#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

enum SCOM_TYPE {
  SCOM_TYPE_CREATE_PARTY_OBJ = 0x16,
  SCOM_TYPE_FADE = 0x1b,
  SCOM_TYPE_PARTY_ADD = 0x35,
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
  static void createArts(u32 driver, u32 arts);
};

class SCOM_ACCESS_TARGET {
public:
  static void create(GF_OBJ_HANDLE *target);
};

class SCOM_TARGET_UI {
public:
  static void create(GF_OBJ_HANDLE *target);
};

class GfReqSmallCom {
public:
  static bool isExistCommand(SCOM_TYPE type);
};

} // namespace gf
