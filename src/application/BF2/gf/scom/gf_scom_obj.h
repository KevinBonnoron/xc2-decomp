#pragma once
#include <stddef.h>

#include "fw/fw_transform.h"
#include "gf/request/gf_scom.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SCOM_HANDLE;

class SCOM_QUEST_REACH : public SCOM {
public:
  // Inferred role: kind of reach (1 discover landmark, 2 arrive landmark, 3 arrive place); original enum and enumerator names unknown.
  enum unknown001 {
    unknown001_1 = 1,
    unknown001_2 = 2,
    unknown001_3 = 3,
  };

  SCOM_QUEST_REACH(GF_SCOM_HANDLE *handle, unknown001 type, u32 id) : SCOM(handle, SCOM_TYPE_UNKNOWN_42, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(type), unknown20(id) {}
  bool checkEventScequence() const;
  bool exec(const fw::UpdateInfo &info) override;
  static void createDiscoverLandmark(u32 landmark);
  static void createArriveLandmark(u32 landmark);
  static void createArrivePlace(u32 place);

  unknown001 unknown1c; // Inferred role: reach kind; original member name unknown.
  u32 unknown20;        // Inferred role: landmark or place; original member name unknown.
};

static_assert(offsetof(SCOM_QUEST_REACH, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_QUEST_REACH, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_QUEST_REACH) == 0x28, "");

class SCOM_QUEST_GIMMICK : public SCOM {
public:
  SCOM_QUEST_GIMMICK(GF_SCOM_HANDLE *handle, gmk::GmkType type, u32 gimmick, f32 delay)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_43, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(type), unknown20(gimmick), unknown24(delay) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *createDoor(u32 gimmick, f32 delay);
  static GF_SCOM_HANDLE *createElevator(u32 gimmick, f32 delay);
  static GF_SCOM_HANDLE *createJump(u32 gimmick, f32 delay);
  static GF_SCOM_HANDLE *createMapGimmick(u32 gimmick, f32 delay);
  static GF_SCOM_HANDLE *createWarp(u32 gimmick, f32 delay);
  static GF_SCOM_HANDLE *createSalvage(u32 gimmick, f32 delay);
  static GF_SCOM_HANDLE *createTresure(u32 gimmick, f32 delay);

  gmk::GmkType unknown1c; // Inferred role: gimmick type; original member name unknown.
  u32 unknown20;          // Inferred role: gimmick; original member name unknown.
  f32 unknown24;          // Inferred role: delay; original member name unknown.
};

static_assert(offsetof(SCOM_QUEST_GIMMICK, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_QUEST_GIMMICK, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_QUEST_GIMMICK, unknown24) == 0x24, "");
static_assert(sizeof(SCOM_QUEST_GIMMICK) == 0x28, "");

class SCOM_OBJ_WARP_POS : public SCOM {
public:
  SCOM_OBJ_WARP_POS(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, const fw::Transform &transform, bool isResetState)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_17, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown30(transform), unknown50(isResetState) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow);
  static GF_SCOM_HANDLE *create(const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow);
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, const fw::Transform &transform, bool isFollow);
  static GF_SCOM_HANDLE *create(const fw::Transform &transform, bool isFollow);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  u8 _28[0x30 - 0x28];
  fw::Transform unknown30; // Inferred role: transform; original member name unknown.
  bool unknown50;          // Inferred role: reset state; original member name unknown.
};

static_assert(offsetof(SCOM_OBJ_WARP_POS, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_OBJ_WARP_POS, unknown30) == 0x30, "");
static_assert(offsetof(SCOM_OBJ_WARP_POS, unknown50) == 0x50, "");
static_assert(sizeof(SCOM_OBJ_WARP_POS) == 0x60, "");

class SCOM_DESTROY_GAME_OBJ : public SCOM {
public:
  SCOM_DESTROY_GAME_OBJ(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 fadeTime, u32 attribute)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_0, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(fadeTime), unknown2c(attribute) {}
  bool exec(const fw::UpdateInfo &info) override;
  static void create(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  f32 unknown28;            // Inferred role: fade time; original member name unknown.
  u32 unknown2c;            // Inferred role: attribute; original member name unknown.
};

static_assert(offsetof(SCOM_DESTROY_GAME_OBJ, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_DESTROY_GAME_OBJ, unknown28) == 0x28, "");
static_assert(offsetof(SCOM_DESTROY_GAME_OBJ, unknown2c) == 0x2c, "");
static_assert(sizeof(SCOM_DESTROY_GAME_OBJ) == 0x30, "");

} // namespace gf
