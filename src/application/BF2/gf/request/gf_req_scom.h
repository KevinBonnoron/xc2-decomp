#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GAME_VOICE_HANDLE;
struct GF_SCOM_HANDLE;
struct GF_OBJ_HANDLE;
struct ParamObj;
struct QuestID;

enum SCOM_TYPE {
  SCOM_TYPE_CREATE_PARTY_OBJ = 0x16,
  SCOM_TYPE_CREATE_MAP_OBJ = 0x1a,
  SCOM_TYPE_FADE = 0x1b,
  SCOM_TYPE_PARTY_ADD = 0x35,
};

class SCOM_ADD_MONEY {
public:
  static void create(int money);
};

class SCOM_ADD_TRUST {
public:
  static void create(u32 blade, u32 point);
};

class SCOM_MISSION_COMPLETE {
public:
  static void create(u32 mission);
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
  static void createCrystalOK(u32 item);
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
  static void addDriver(u32 driver, u32 partyId);
  static void removeDriver(u32 driver, bool isForce);
  static void addBlade(u32 blade, u32 driver, int slot);
  static void removeBlade(u32 blade, bool isForce);
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

enum CV_SALVAGE {};
enum CV_SALVAGE_RESULT {};

enum CV_FIELD {
  CV_FIELD_TIME_MORNING = 31,
  CV_FIELD_TIME_NIGHT = 32,
};

class SCOM_SALVAGE_VOICE {
public:
  static GAME_VOICE_HANDLE *create(GF_OBJ_HANDLE *handle, CV_SALVAGE voice);
  static GAME_VOICE_HANDLE *createResult(GF_OBJ_HANDLE *handle, CV_SALVAGE_RESULT voice);
  static bool isPlayEnd(GAME_VOICE_HANDLE *voice);
};

class SCOM_FIELD_VOICE {
public:
  static void createLevelup(const ParamObj &paramObj);
  static void createBadWeather();
  static void createTime(CV_FIELD voice);
};

class SCOM_ZONE {
public:
  static void create(u32 map);
};

class SCOM_HOMURI_PARTS {
public:
  static void create(u32 partyId, bool isVisible, f32 alpha);
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

class GfReqSmallCom : public mm::mtl::PtrSingleton<GfReqSmallCom> {
public:
  bool isValid(GF_SCOM_HANDLE *handle);
  static bool isExistCommand(SCOM_TYPE type);
  static bool isExistCommand();

  u8 _08[0x4820 - 0x08];
  s32 unknown4820; // Inferred role: number of commands; original member name unknown.
  u8 _4824[0x9040 - 0x4824];
  s32 unknown9040; // Inferred role: number of commands; original member name unknown.
};

static_assert(offsetof(GfReqSmallCom, unknown4820) == 0x4820, "");
static_assert(offsetof(GfReqSmallCom, unknown9040) == 0x9040, "");

} // namespace gf
