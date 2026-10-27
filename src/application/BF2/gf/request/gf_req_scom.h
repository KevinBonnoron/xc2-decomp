#pragma once
#include <stddef.h>

#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/request/gf_scom.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GAME_VOICE_HANDLE;
struct GF_SCOM_HANDLE;
struct GF_OBJ_HANDLE;
struct ParamObj;

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

class SCOM_ADD_ETHER : public SCOM {
public:
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int ether);

  int unknown1c; // Inferred role: ether; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_ETHER, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_ETHER) == 0x20, "");

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

class SCOM_REFRESH_COMPASS : public SCOM, public mm::mtl::PtrSingleton<SCOM_REFRESH_COMPASS> {
public:
  SCOM_REFRESH_COMPASS(GF_SCOM_HANDLE *handle);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();

  int unknown28; // Inferred role: wait count; original member name unknown.
};

static_assert(offsetof(SCOM_REFRESH_COMPASS, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_REFRESH_COMPASS) == 0x30, "");

class SCOM_BATTLE_TASK_RESET : public SCOM, public mm::mtl::PtrSingleton<SCOM_BATTLE_TASK_RESET> {
public:
  SCOM_BATTLE_TASK_RESET(GF_SCOM_HANDLE *handle);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();

  int unknown28; // Inferred role: wait count; original member name unknown.
};

static_assert(offsetof(SCOM_BATTLE_TASK_RESET, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_BATTLE_TASK_RESET) == 0x30, "");

enum CV_SALVAGE {};
enum CV_SALVAGE_RESULT {};

enum CV_FIELD {
  CV_FIELD_UNKNOWN_3 = 3,
  CV_FIELD_UNKNOWN_4 = 4,
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
  static void create(CV_FIELD voice, CV_PRIO priority);
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

class SCOM_SALVAGER_POINT {
public:
  static void setPoint(u32 point);
};

class SCOM_RANDOM_INN {
public:
  static void setRandom();
};

class SCOM_MAXIMUM_HEAL {
public:
  static void create(GF_OBJ_HANDLE *handle);
};

class SCOM_ADD_IDEA : public SCOM {
public:
  SCOM_ADD_IDEA(GF_SCOM_HANDLE *handle, int point, u32 driver, u32 idea, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_9, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(driver), unknown24(idea), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, u32 idea, int point);

  int unknown1c;            // Inferred role: idea point; original member name unknown.
  u32 unknown20;            // Inferred role: driver; original member name unknown.
  u32 unknown24;            // Inferred role: idea; original member name unknown.
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_IDEA, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ADD_IDEA, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_ADD_IDEA, unknown24) == 0x24, "");
static_assert(offsetof(SCOM_ADD_IDEA, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_ADD_IDEA) == 0x30, "");

class SCOM_EXEC_DRIVER_ARTS_LVUP : public SCOM {
public:
  SCOM_EXEC_DRIVER_ARTS_LVUP(GF_SCOM_HANDLE *handle, u32 level, u32 driver, u32 arts, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_54, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(level), unknown20(driver), unknown24(arts), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 level, u32 arts, GF_OBJ_HANDLE *handle);
  static GF_SCOM_HANDLE *create(u32 level, u32 arts, u32 driver);

  u32 unknown1c;            // Inferred role: level; original member name unknown.
  u32 unknown20;            // Inferred role: driver; original member name unknown.
  u32 unknown24;            // Inferred role: arts; original member name unknown.
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown24) == 0x24, "");
static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_EXEC_DRIVER_ARTS_LVUP) == 0x30, "");

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

class SCOM_ADD_MONEY : public SCOM {
public:
  SCOM_ADD_MONEY(GF_SCOM_HANDLE *handle, int money) : SCOM(handle, SCOM_TYPE_UNKNOWN_1, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(money) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int money);

  int unknown1c; // Inferred role: money; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_MONEY, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_MONEY) == 0x20, "");

class SCOM_ADD_COIN : public SCOM {
public:
  SCOM_ADD_COIN(GF_SCOM_HANDLE *handle, int coin) : SCOM(handle, SCOM_TYPE_UNKNOWN_2, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(coin) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int coin);

  int unknown1c; // Inferred role: coin; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_COIN, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_COIN) == 0x20, "");

class SCOM_ADD_DEVELOP : public SCOM {
public:
  SCOM_ADD_DEVELOP(GF_SCOM_HANDLE *handle, u32 nation, u32 point) : SCOM(handle, SCOM_TYPE_UNKNOWN_11, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(nation) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 nation, u32 point);
  static void createGmk(u32 fieldZone, u32 point);

  u32 unknown1c; // Inferred role: point; original member name unknown.
  u32 unknown20; // Inferred role: nation; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_DEVELOP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ADD_DEVELOP, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_ADD_DEVELOP) == 0x28, "");

class SCOM_ACCESS_TARGET : public SCOM {
public:
  SCOM_ACCESS_TARGET(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_46, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SCOM_ACCESS_TARGET, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_ACCESS_TARGET) == 0x28, "");

class SCOM_GAME_SPEED : public SCOM {
public:
  SCOM_GAME_SPEED(GF_SCOM_HANDLE *handle, f32 speed) : SCOM(handle, SCOM_TYPE_UNKNOWN_20, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(speed) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(f32 speed);

  f32 unknown1c; // Inferred role: speed; original member name unknown.
};

static_assert(offsetof(SCOM_GAME_SPEED, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_GAME_SPEED) == 0x20, "");

class SCOM_INTERVAL_SPEED : public SCOM {
public:
  SCOM_INTERVAL_SPEED(GF_SCOM_HANDLE *handle, f32 speed, f32 time) : SCOM(handle, SCOM_TYPE_UNKNOWN_19, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(speed), unknown20(time) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(f32 speed, f32 time);

  f32 unknown1c; // Inferred role: speed; original member name unknown.
  f32 unknown20; // Inferred role: time; original member name unknown.
};

static_assert(offsetof(SCOM_INTERVAL_SPEED, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_INTERVAL_SPEED, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_INTERVAL_SPEED) == 0x28, "");

class SCOM_SET_CAMTYPE : public SCOM {
public:
  SCOM_SET_CAMTYPE(GF_SCOM_HANDLE *handle, int type) : SCOM(handle, SCOM_TYPE_UNKNOWN_49, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(type) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int type);

  int unknown1c; // Inferred role: camera control type; original member name unknown.
};

static_assert(offsetof(SCOM_SET_CAMTYPE, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_SET_CAMTYPE) == 0x20, "");

class SCOM_QUEST_EVENT : public SCOM {
public:
  SCOM_QUEST_EVENT(GF_SCOM_HANDLE *handle, u32 event) : SCOM(handle, SCOM_TYPE_UNKNOWN_45, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(event) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 event);

  u32 unknown1c; // Inferred role: event; original member name unknown.
};

static_assert(offsetof(SCOM_QUEST_EVENT, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_QUEST_EVENT) == 0x20, "");

class SCOM_QUEST_ORDER : public SCOM {
public:
  SCOM_QUEST_ORDER(GF_SCOM_HANDLE *handle, QuestID quest) : SCOM(handle, SCOM_TYPE_UNKNOWN_41, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(quest) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(QuestID quest);

  QuestID unknown1c; // Inferred role: quest; original member name unknown.
};

static_assert(offsetof(SCOM_QUEST_ORDER, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_QUEST_ORDER) == 0x20, "");

class SCOM_ITEM_USE : public SCOM {
public:
  SCOM_ITEM_USE(GF_SCOM_HANDLE *handle, u32 item, u32 count) : SCOM(handle, SCOM_TYPE_UNKNOWN_68, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(item), unknown20(count) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 item, u32 count);

  u32 unknown1c; // Inferred role: item; original member name unknown.
  u32 unknown20; // Inferred role: count; original member name unknown.
};

static_assert(offsetof(SCOM_ITEM_USE, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ITEM_USE, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_ITEM_USE) == 0x28, "");

class SCOM_DESTROY_FIELD_OBJ : public SCOM {
public:
  SCOM_DESTROY_FIELD_OBJ(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_24, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();
};

static_assert(sizeof(SCOM_DESTROY_FIELD_OBJ) == 0x20, "");

class SCOM_DESTROY_MAP_OBJ : public SCOM {
public:
  SCOM_DESTROY_MAP_OBJ(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_25, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();
};

static_assert(sizeof(SCOM_DESTROY_MAP_OBJ) == 0x20, "");

class SCOM_STOP_LAYER : public SCOM {
public:
  SCOM_STOP_LAYER(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, bool stop) : SCOM(handle, SCOM_TYPE_UNKNOWN_32, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(stop) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, bool stop);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  bool unknown28;           // Inferred role: stop; original member name unknown.
};

static_assert(offsetof(SCOM_STOP_LAYER, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_STOP_LAYER, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_STOP_LAYER) == 0x30, "");

class SCOM_SET_IDEA_POINT_FOR_DEBUG : public SCOM {
public:
  SCOM_SET_IDEA_POINT_FOR_DEBUG(GF_SCOM_HANDLE *handle, u32 driver, u32 idea, int point)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_10, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(driver), unknown24(idea) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 driver, u32 idea, int point);

  int unknown1c; // Inferred role: point; original member name unknown.
  u32 unknown20; // Inferred role: driver; original member name unknown.
  u32 unknown24; // Inferred role: idea; original member name unknown.
};

static_assert(offsetof(SCOM_SET_IDEA_POINT_FOR_DEBUG, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_SET_IDEA_POINT_FOR_DEBUG, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_SET_IDEA_POINT_FOR_DEBUG, unknown24) == 0x24, "");
static_assert(sizeof(SCOM_SET_IDEA_POINT_FOR_DEBUG) == 0x28, "");

class SCOM_BATTLE_BGM : public SCOM {
public:
  SCOM_BATTLE_BGM(GF_SCOM_HANDLE *handle, u32 bgm) : SCOM(handle, SCOM_TYPE_UNKNOWN_62, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(bgm) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 bgm);

  u32 unknown1c; // Inferred role: battle bgm; original member name unknown.
};

static_assert(offsetof(SCOM_BATTLE_BGM, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_BATTLE_BGM) == 0x20, "");

class SCOM_COLI_CHAR_VALID : public SCOM {
public:
  SCOM_COLI_CHAR_VALID(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, bool isEnable) : SCOM(handle, SCOM_TYPE_UNKNOWN_33, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(isEnable) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, bool isEnable);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  bool unknown28;           // Inferred role: enable; original member name unknown.
};

static_assert(offsetof(SCOM_COLI_CHAR_VALID, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_COLI_CHAR_VALID, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_COLI_CHAR_VALID) == 0x30, "");

class SCOM_CREATE_GMK_SET : public SCOM {
public:
  SCOM_CREATE_GMK_SET(GF_SCOM_HANDLE *handle, u32 gimmickSet) : SCOM(handle, SCOM_TYPE_UNKNOWN_39, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(gimmickSet) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 gimmickSet);

  u32 unknown1c; // Inferred role: gimmick set; original member name unknown.
};

static_assert(offsetof(SCOM_CREATE_GMK_SET, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_CREATE_GMK_SET) == 0x20, "");

class SCOM_DESTROY_GMK_SET : public SCOM {
public:
  SCOM_DESTROY_GMK_SET(GF_SCOM_HANDLE *handle, u32 gimmickSet) : SCOM(handle, SCOM_TYPE_UNKNOWN_38, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(gimmickSet) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 gimmickSet);

  u32 unknown1c; // Inferred role: gimmick set; original member name unknown.
};

static_assert(offsetof(SCOM_DESTROY_GMK_SET, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_DESTROY_GMK_SET) == 0x20, "");

class SCOM_REBUILD : public SCOM {
public:
  SCOM_REBUILD(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_58, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SCOM_REBUILD, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_REBUILD) == 0x28, "");

class SCOM_ADD_MERCENARIES_POINT : public SCOM {
public:
  SCOM_ADD_MERCENARIES_POINT(GF_SCOM_HANDLE *handle, u32 point) : SCOM(handle, SCOM_TYPE_UNKNOWN_59, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 point);

  u32 unknown1c; // Inferred role: point; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_MERCENARIES_POINT, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_MERCENARIES_POINT) == 0x20, "");

class SCOM_SET_MERCENARIES_LEVEL : public SCOM {
public:
  SCOM_SET_MERCENARIES_LEVEL(GF_SCOM_HANDLE *handle, u32 level) : SCOM(handle, SCOM_TYPE_UNKNOWN_60, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(level) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 level);

  u32 unknown1c; // Inferred role: level; original member name unknown.
};

static_assert(offsetof(SCOM_SET_MERCENARIES_LEVEL, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_SET_MERCENARIES_LEVEL) == 0x20, "");

class SCOM_EXEC_MOUNT : public SCOM {
public:
  SCOM_EXEC_MOUNT(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, OPTMNT mountType) : SCOM(handle, SCOM_TYPE_UNKNOWN_35, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(mountType) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, OPTMNT mountType);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  OPTMNT unknown28;         // Inferred role: mount type; original member name unknown.
};

static_assert(offsetof(SCOM_EXEC_MOUNT, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_EXEC_MOUNT, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_EXEC_MOUNT) == 0x30, "");

class SCOM_RESET_MOUNT : public SCOM {
public:
  SCOM_RESET_MOUNT(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, OPTMNT mountType) : SCOM(handle, SCOM_TYPE_UNKNOWN_35, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(mountType) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, OPTMNT mountType);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  OPTMNT unknown28;         // Inferred role: mount type; original member name unknown.
};

static_assert(offsetof(SCOM_RESET_MOUNT, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_RESET_MOUNT, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_RESET_MOUNT) == 0x30, "");

class SCOM_VALID_LOCAL_SPEED : public SCOM {
public:
  SCOM_VALID_LOCAL_SPEED(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, bool stop, f32 speed)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_37, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(speed), unknown2c(stop) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, bool stop, f32 speed);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  f32 unknown28;            // Inferred role: speed; original member name unknown.
  bool unknown2c;           // Inferred role: stop; original member name unknown.
};

static_assert(offsetof(SCOM_VALID_LOCAL_SPEED, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_VALID_LOCAL_SPEED, unknown28) == 0x28, "");
static_assert(offsetof(SCOM_VALID_LOCAL_SPEED, unknown2c) == 0x2c, "");
static_assert(sizeof(SCOM_VALID_LOCAL_SPEED) == 0x30, "");

class SCOM_LOADING : public SCOM {
public:
  SCOM_LOADING(GF_SCOM_HANDLE *handle, u32 type, bool isDisp) : SCOM(handle, SCOM_TYPE_UNKNOWN_28, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(type), unknown20(isDisp) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 type, bool isDisp);

  u32 unknown1c;  // Inferred role: loading type; original member name unknown.
  bool unknown20; // Inferred role: display; original member name unknown.
};

static_assert(offsetof(SCOM_LOADING, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_LOADING, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_LOADING) == 0x28, "");

class SCOM_STOP_BATTLE : public SCOM {
public:
  SCOM_STOP_BATTLE(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_15, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();
};

static_assert(sizeof(SCOM_STOP_BATTLE) == 0x20, "");

class GfReqSmallCom : public mm::mtl::PtrSingleton<GfReqSmallCom> {
public:
  static GF_SCOM_HANDLE *addRequest(SCOM *scom);
  static GF_SCOM_HANDLE *addRequestParallel(SCOM *scom);
  GF_SCOM_HANDLE *allocate();
  bool isValid(GF_SCOM_HANDLE *handle);
  static bool isExistCommand(SCOM_TYPE type);
  static bool isExistCommand();

  mm::mtl::FixedList<SCOM *, 1024> unknown08;   // Inferred role: commands; original member name unknown.
  mm::mtl::FixedList<SCOM *, 1024> unknown4828; // Inferred role: parallel commands; original member name unknown.
  mm::mtl::FixedList<SCOM *, 1024> unknown9048; // Inferred role: parallel commands added while updating; original member name unknown.
  s64 unknownd868;                              // Inferred role: next command handle; original member name unknown.
  bool unknownd870;                             // Inferred role: updating parallel commands; original member name unknown.
};

static_assert(offsetof(GfReqSmallCom, unknown08) == 0x08, "");
static_assert(offsetof(GfReqSmallCom, unknown4828) == 0x4828, "");
static_assert(offsetof(GfReqSmallCom, unknown9048) == 0x9048, "");
static_assert(offsetof(GfReqSmallCom, unknownd868) == 0xd868, "");
static_assert(offsetof(GfReqSmallCom, unknownd870) == 0xd870, "");

} // namespace gf
