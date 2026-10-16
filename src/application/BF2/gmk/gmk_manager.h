#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace gmk {

enum GmkType {
  GMK_TYPE_ENEMY = 0,
  GMK_TYPE_ROUTED_ENEMY = 1,
  GMK_TYPE_ROUTED_ENEMY_POINT = 2,
  GMK_TYPE_NPC = 3,
  GMK_TYPE_ROUTED_NPC = 4,
  GMK_TYPE_NPC_ROUTE_POINT = 5,
  GMK_TYPE_MAP_OBJ = 6,
  GMK_TYPE_ROUTED_MAP_OBJ = 7,
  GMK_TYPE_MAP_OBJ_ROUTE_POINT = 8,
  GMK_TYPE_TBOX = 9,
  GMK_TYPE_EVENT = 10,
  GMK_TYPE_BATTLE_LOCK = 11,
  GMK_TYPE_FIELD_LOCK = 12,
  GMK_TYPE_EFFECT = 13,
  GMK_TYPE_EFFECT_LOCATOR = 14,
  GMK_TYPE_SE = 15,
  GMK_TYPE_SE_LINE = 16,
  GMK_TYPE_SE_LINE_POINT = 17,
  GMK_TYPE_MOB = 18,
  GMK_TYPE_ROUTED_MOB = 19,
  GMK_TYPE_MOB_ROUTE_POINT = 20,
  GMK_TYPE_LANDMARK = 21,
  GMK_TYPE_ROUTE = 22,
  GMK_TYPE_ROUTE_POINT = 23,
  GMK_TYPE_FORM_PC = 24,
  GMK_TYPE_FORM_PCNPC = 25,
  GMK_TYPE_FORM_PC_EV = 26,
  GMK_TYPE_FORM_PCNPC_EV = 27,
  GMK_TYPE_COLLECTION = 28,
  GMK_TYPE_AREA_BGM = 29,
  GMK_TYPE_AREA_WEATHER = 30,
  GMK_TYPE_SALVAGE = 31,
  GMK_TYPE_SALVAGE_LOCATOR = 32,
  GMK_TYPE_MAP_GIMMICK = 33,
  GMK_TYPE_PRECIOUS = 34,
  GMK_TYPE_GRAVE = 35,
  GMK_TYPE_KIZUNA_TALK = 36,
  GMK_TYPE_JUMP = 37,
  GMK_TYPE_WARP = 38,
  GMK_TYPE_SQUAD_LEADER = 39,
  GMK_TYPE_SQUAD_MEMBER = 40,
  GMK_TYPE_DOOR = 41,
  GMK_TYPE_ELEVATOR = 42,
  GMK_TYPE_ELEVATOR_LOCATOR = 43,
  GMK_TYPE_MAP_JUMP = 44,
  GMK_TYPE_FIELD_VOLUME = 45,
  GMK_TYPE_CLIMBING = 46,
  GMK_TYPE_BLADE = 47,
  GMK_TYPE_DMG_GIMMICK = 48,
  GMK_TYPE_DMG_PHANTOM = 49,
  GMK_TYPE_DMG_EFFECT = 50,
  GMK_TYPE_DMG_SE = 51,
  GMK_TYPE_TRIGGER = 52,
  GMK_TYPE_TARGET_POINT = 53,
  GMK_TYPE_ROUTED_FOOT_PRINT = 54,
  GMK_TYPE_ROUTED_FOOT_PRINT_POINT = 55,
  GMK_TYPE_ANTI_BLADE_AREA = 56,
  GMK_TYPE_TUTORIAL = 57,
  GMK_TYPE_NUM = 58,
};

class AGmkBase;

class GmkManager : public mm::mtl::PtrSingleton<GmkManager> {
public:
  void updateImmediate();
  const char *getFilenameByType(int gmkSetId, GmkType type) const;
  const char *getSheetnameByType(int gmkSetId, GmkType type) const;

  u8 _08[0x190 - 0x08];
  u8 *gmkSetListBdat;
};

static_assert(offsetof(GmkManager, gmkSetListBdat) == 0x190, "");

int getCurrentMapBdatId();
AGmkBase *getBindedGmkInst(gf::GF_OBJ_HANDLE *handle);
void setDispByGmkType(GmkType type, bool isDisp);
void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool isDisp);
void setDispByGmkTypeAndGmkIdx(int gmkSet, GmkType type, u32 index, bool isDisp);

} // namespace gmk
