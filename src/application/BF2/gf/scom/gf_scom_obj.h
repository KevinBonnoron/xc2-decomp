#pragma once
#include <stddef.h>

#include "gf/request/gf_scom.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SCOM_HANDLE;

class SCOM_QUEST_REACH {
public:
  static void createArrivePlace(u32 questId);
};

class SCOM_QUEST_GIMMICK : public SCOM {
public:
  bool exec(const fw::UpdateInfo &info) override;
  static void createJump(u32 gimmick, f32 delay);
  static void createWarp(u32 gimmick, f32 delay);
  static void createDoor(u32 gimmick, f32 delay);
  static void createTresure(u32 gimmick, f32 delay);
  static void createMapGimmick(u32 gimmick, f32 delay);
  static void createElevator(u32 gimmick, f32 delay);
  static void createSalvage(u32 gimmick, f32 delay);

  gmk::GmkType unknown1c; // Inferred role: gimmick type; original member name unknown.
  u32 unknown20;          // Inferred role: gimmick; original member name unknown.
  f32 unknown24;          // Inferred role: delay; original member name unknown.
};

static_assert(offsetof(SCOM_QUEST_GIMMICK, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_QUEST_GIMMICK, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_QUEST_GIMMICK, unknown24) == 0x24, "");
static_assert(sizeof(SCOM_QUEST_GIMMICK) == 0x28, "");

class SCOM_OBJ_WARP_POS {
public:
  static void create(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow);
};

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
