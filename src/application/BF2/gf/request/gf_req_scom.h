#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct ParamObj;
struct QuestID;

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
  static void createQuest(QuestID quest);
  static void createDevelop(u32 location, u32 level);
  static void createAffinity(u32 blade, u32 driver, u32 trustRank);
  static bool createAchievement(u32 blade, u32 achievement, u32 level);
  static void createIdea(u32 driver, u32 idea, u32 level);
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

class SCOM_PARTY_ADD {
public:
  static void removeDriver(u32 driver, bool isForce);
};

class SCOM_PARTY_LEADER {
public:
  static void create(u32 objectType, u32 leader);
};

class SCOM_REFRESH_COMPASS {
public:
  static void create();
};

class SCOM_BATTLE_TASK_RESET {
public:
  static void create();
};

class SCOM_FIELD_VOICE {
public:
  static void createLevelup(const ParamObj &paramObj);
};

class SCOM_MAXIMUM_HEAL {
public:
  static void create(GF_OBJ_HANDLE *handle);
};

class SCOM_ADD_IDEA {
public:
  static void create(GF_OBJ_HANDLE *handle, u32 idea, int point);
};

class SCOM_OBJ_ALPHA {
public:
  static void create(GF_OBJ_HANDLE *handle, f32 time, f32 alpha);
};

class GfReqSmallCom {
public:
  static bool isExistCommand(SCOM_TYPE type);
};

} // namespace gf
