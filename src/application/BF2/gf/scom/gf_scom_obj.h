#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

class SCOM_QUEST_REACH {
public:
  static void createArrivePlace(u32 questId);
};

class SCOM_QUEST_GIMMICK {
public:
  static void createJump(u32 gimmick, f32 delay);
  static void createWarp(u32 gimmick, f32 delay);
  static void createDoor(u32 gimmick, f32 delay);
  static void createTresure(u32 gimmick, f32 delay);
  static void createMapGimmick(u32 gimmick, f32 delay);
  static void createElevator(u32 gimmick, f32 delay);
  static void createSalvage(u32 gimmick, f32 delay);
};

class SCOM_OBJ_WARP_POS {
public:
  static void create(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, const mm::Vec3 &rotation, bool isFollow);
};

class SCOM_DESTROY_GAME_OBJ {
public:
  static void create(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute);
};

} // namespace gf
