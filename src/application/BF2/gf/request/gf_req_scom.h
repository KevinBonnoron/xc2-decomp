#pragma once
#include <stddef.h>

#include "gf/request/gf_scom.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GAME_VOICE_HANDLE;
struct GF_SCOM_HANDLE;
struct GF_OBJ_HANDLE;
struct ParamObj;
struct QuestID;

class SCOM_ADD_MONEY {
public:
  static void create(int money);
};

class SCOM_ADD_TRUST : public SCOM {
public:
  SCOM_ADD_TRUST(GF_SCOM_HANDLE *handle, u32 blade, u32 point) : SCOM(handle, SCOM_TYPE_UNKNOWN_64, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(blade) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 blade, u32 point);

  u32 unknown1c; // Inferred role: trust point; original member name unknown.
  u32 unknown20; // Inferred role: blade; original member name unknown.
};

class SCOM_MISSION_COMPLETE {
public:
  static void create(u32 mission);
};

class SCOM_ADD_DEVELOP {
public:
  static void create(u32 nation, u32 point);
};

class SCOM_LEVELUP_DEVELOP : public SCOM {
public:
  SCOM_LEVELUP_DEVELOP(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_12, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
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

class SCOM_TARGET_UI : public SCOM {
public:
  SCOM_TARGET_UI(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_47, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static void create(GF_OBJ_HANDLE *target);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
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

class SCOM_ZONE : public SCOM {
public:
  SCOM_ZONE(GF_SCOM_HANDLE *handle, u32 map) : SCOM(handle, SCOM_TYPE_UNKNOWN_66, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(map) {}
  bool exec(const fw::UpdateInfo &info) override;
  static void create(u32 map);

  u32 unknown1c; // Inferred role: map; original member name unknown.
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

class SCOM_OBJ_ALPHA : public SCOM {
public:
  SCOM_OBJ_ALPHA(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 alpha);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, f32 time, f32 alpha);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  f32 unknown28;            // Inferred role: fade time; original member name unknown.
  f32 unknown2c;            // Inferred role: elapsed time; original member name unknown.
  f32 unknown30;            // Inferred role: target alpha; original member name unknown.
  f32 unknown34;            // Inferred role: start alpha; original member name unknown.
};

static_assert(offsetof(SCOM_OBJ_ALPHA, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown28) == 0x28, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown2c) == 0x2c, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown30) == 0x30, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown34) == 0x34, "");
static_assert(sizeof(SCOM_OBJ_ALPHA) == 0x38, "");

class SCOM_OBJ_VFADE_OFF : public SCOM {
public:
  SCOM_OBJ_VFADE_OFF(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SCOM_OBJ_VFADE_OFF, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_OBJ_VFADE_OFF) == 0x28, "");

class SCOM_ADD_SP : public SCOM {
public:
  SCOM_ADD_SP(GF_SCOM_HANDLE *handle, int skillPoint, u32 driver, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_8, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(skillPoint), unknown20(driver), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, int skillPoint);
  static GF_SCOM_HANDLE *create(u32 driver, int skillPoint);

  int unknown1c; // Inferred role: skill point; original member name unknown.
  u32 unknown20; // Inferred role: driver; original member name unknown.
  u8 _24[0x28 - 0x24];
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_SP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ADD_SP, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_ADD_SP, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_ADD_SP) == 0x30, "");

class SCOM_EXEC_LVUP : public SCOM {
public:
  SCOM_EXEC_LVUP(GF_SCOM_HANDLE *handle, u32 level, u32 driver, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_5, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(level), unknown20(driver), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 level, GF_OBJ_HANDLE *handle);
  static GF_SCOM_HANDLE *create(u32 level, u32 driver);

  u32 unknown1c; // Inferred role: level; original member name unknown.
  u32 unknown20; // Inferred role: driver; original member name unknown.
  u8 _24[0x28 - 0x24];
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_EXEC_LVUP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_EXEC_LVUP, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_EXEC_LVUP, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_EXEC_LVUP) == 0x30, "");

class GfReqSmallCom : public mm::mtl::PtrSingleton<GfReqSmallCom> {
public:
  static GF_SCOM_HANDLE *addRequestParallel(SCOM *scom);
  GF_SCOM_HANDLE *allocate();
  bool isValid(GF_SCOM_HANDLE *handle);
  static bool isExistCommand(SCOM_TYPE type);
  static bool isExistCommand();

  u8 _08[0x4820 - 0x08];
  s32 unknown4820; // Inferred role: number of commands; original member name unknown.
  u8 _4824[0x9040 - 0x4824];
  s32 unknown9040; // Inferred role: number of commands; original member name unknown.
  u8 _9044[0xd868 - 0x9044];
  s64 unknownd868; // Inferred role: next command handle; original member name unknown.
};

static_assert(offsetof(GfReqSmallCom, unknown4820) == 0x4820, "");
static_assert(offsetof(GfReqSmallCom, unknown9040) == 0x9040, "");
static_assert(offsetof(GfReqSmallCom, unknownd868) == 0xd868, "");

} // namespace gf
