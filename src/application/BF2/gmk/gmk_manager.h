#pragma once
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"
#include <stddef.h>

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace mm {
struct Quat;
struct Vec2;
struct Vec3;
} // namespace mm

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
  GMK_TYPE_INVALID = 59,
};

enum ShapeType {
  SHAPE_TYPE_NONE = 0,
  SHAPE_TYPE_POINT = 1,
  SHAPE_TYPE_SPHERE = 2,
  SHAPE_TYPE_BOX = 3,
  SHAPE_TYPE_CAPSULE = 4,
};

enum InterestType {
  INTEREST_TYPE_PLAYER = 0,
  INTEREST_TYPE_CAMERA = 1,
};

class AGmkBase;
class GmkSet;

class GmkManager : public mm::mtl::PtrSingleton<GmkManager> {
public:
  ~GmkManager() override;

  void updateImmediate();
  const char *getFilenameByType(int gmkSetId, GmkType type) const;
  const char *getSheetnameByType(int gmkSetId, GmkType type) const;
  int getMapBdatId(int gmkSetId) const;
  const AGmkBase *findFirstGmkInstByBdatId(GmkType type, int bdatId) const;
  const AGmkBase *findGmkInstByGmkInstIndex(int gmkSetId, GmkType type, u32 index) const;
  GmkSet *findGmkSet(int gmkSetId) const;

  u8 _08[0x190 - 0x08];
  u8 *gmkSetListBdat;
  InterestType interestType;
  u8 _19c[0xf358 - 0x19c];
  mm::mtl::Vector<GmkSet *> sets;
};

static_assert(offsetof(GmkManager, gmkSetListBdat) == 0x190, "");
static_assert(offsetof(GmkManager, interestType) == 0x198, "");
static_assert(offsetof(GmkManager, sets) == 0xf358, "");

int getCurrentMapBdatId();
bool isInEvent();
void setDispByGmkType(GmkType type, bool isDisp);
void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool isDisp);
void setDispByGmkTypeAndGmkIdx(int gmkSet, GmkType type, u32 index, bool isDisp);
bool isInterestPosExist();
bool isPlayerExist();
bool isCameraExist();
const mm::Vec3 &getInterestPos();
const mm::Vec3 &getPlayerPos();
const mm::Vec3 &getCameraPos();
bool isPlayerInDoor();
gf::GF_OBJ_HANDLE *getPlayer();
bool toScreenPos(mm::Vec2 &screenPos, const mm::Vec3 &position);
AGmkBase *getBindedGmkInst(gf::GF_OBJ_HANDLE *handle);
GmkType getBindedGmkInstType(gf::GF_OBJ_HANDLE *handle);
void setEventDisp(gf::GF_OBJ_HANDLE *handle, bool isDisp);
bool getGobPosRot(mm::Vec3 &position, mm::Quat &rotation, gf::GF_OBJ_HANDLE *handle);
bool isModelRendered(gf::GF_OBJ_HANDLE *handle);
bool isNaviMeshExist(const mm::Vec3 &position);
bool isGfObjNumFull(u32 objectType);
bool isInBattle();
bool isInMapJumpWithLoadingSaveData();
void setOpenMainMenuEnable(bool isEnable);
void createMenuObj(gf::GF_OBJ_HANDLE *handle);
u32 getDefeatedNum(int enemy);
void disposeGobInst(gf::GF_OBJ_HANDLE *handle, f32 fadeTime);
void disposeGobInstWithAttr(gf::GF_OBJ_HANDLE *handle, u32 attribute, f32 fadeTime);
bool canObtainPreciousItem();
bool canCreateBattleLock();
bool canDisposeBattleLock();
const char *debugGetGmkTypeName(GmkType type);
const char *debugGetShapeTypeName(ShapeType type);
const char *debugGetGmkFileName(const AGmkBase &gmk);
const char *debugGetGmkBdatRowName(const AGmkBase &gmk);
const char *debugGetGmkBdatSheetName(const AGmkBase &gmk);

inline bool debugIsDispGmkType(GmkType type) { return true; }

} // namespace gmk
