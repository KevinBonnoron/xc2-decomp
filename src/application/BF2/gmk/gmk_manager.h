#pragma once
#include <stddef.h>

#include "gmk/gmk_active_list.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace fw {
struct ColiCheckConfig;
} // namespace fw

namespace mm {
struct Quat;
struct Vec2;
struct Vec3;
} // namespace mm

namespace gmk {

// Enumerator names are the game class names without the Gmk prefix (symbols gmk::GmkEnemy, gmk::GmkRoutedEnemy, gmk::GmkNpc, gmk::GmkTbox, ...);
// GMK_TYPE_FORM_PC and GMK_TYPE_FORM_PCNPC (24 and 25) follow the template symbols gmk::TGmkFormPc<(GmkType)24, gmk::TGmkFormPcnpc<(GmkType)25>>
// and gmk::TGmkFormPcnpc<(GmkType)25>. The others have no name in the game.
enum GmkType {
  GMK_TYPE_ENEMY = 0,
  GMK_TYPE_ROUTED_ENEMY = 1,
  GMK_TYPE_ROUTED_ENEMY_POINT = 2,
  GMK_TYPE_NPC = 3,
  GMK_TYPE_ROUTED_NPC = 4,
  GMK_TYPE_UNKNOWN_5 = 5, // Inferred role: npc route point; original name unknown.
  GMK_TYPE_MAP_OBJ = 6,
  GMK_TYPE_ROUTED_MAP_OBJ = 7,
  GMK_TYPE_UNKNOWN_8 = 8, // Inferred role: map obj route point; original name unknown.
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
  GMK_TYPE_UNKNOWN_20 = 20, // Inferred role: mob route point; original name unknown.
  GMK_TYPE_LANDMARK = 21,
  GMK_TYPE_ROUTE = 22,
  GMK_TYPE_ROUTE_POINT = 23,
  GMK_TYPE_FORM_PC = 24,
  GMK_TYPE_FORM_PCNPC = 25,
  GMK_TYPE_UNKNOWN_26 = 26, // Inferred role: form pc ev; original name unknown.
  GMK_TYPE_UNKNOWN_27 = 27, // Inferred role: form pcnpc ev; original name unknown.
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
  GMK_TYPE_NUM = 58,        // Number of gimmick types: bound of the per-type tables (unknown014, GmkSet::unknown1b8) and loops; GMK_TYPE_UNKNOWN_59 follows it.
  GMK_TYPE_UNKNOWN_59 = 59, // Inferred role: invalid; original name unknown.
};

constexpr u16 SCENARIO_FLAG_UNKNOWN_7039 = 7039; // Inferred role: scenario flag keep battle lock in battle; original name unknown.

enum ShapeType {
  SHAPE_TYPE_UNKNOWN_0 = 0, // Inferred role: none; original name unknown.
  SHAPE_TYPE_UNKNOWN_1 = 1, // Inferred role: point; original name unknown.
  SHAPE_TYPE_UNKNOWN_2 = 2, // Inferred role: sphere; original name unknown.
  SHAPE_TYPE_UNKNOWN_3 = 3, // Inferred role: box; original name unknown.
  SHAPE_TYPE_UNKNOWN_4 = 4, // Inferred role: capsule; original name unknown.
};

// Inferred table: phantom shape type of each gimmick shape type; original name unknown.
const GmkPhantom::ShapeType unknown006[] = {
    GmkPhantom::SHAPE_TYPE_UNKNOWN_0, GmkPhantom::SHAPE_TYPE_UNKNOWN_0, GmkPhantom::SHAPE_TYPE_UNKNOWN_1, GmkPhantom::SHAPE_TYPE_UNKNOWN_3, GmkPhantom::SHAPE_TYPE_UNKNOWN_2};

// Inferred role: interest type; original type name unknown.
enum unknown080 {
  unknown080_0 = 0, // Inferred role: player; original name unknown.
  unknown080_1 = 1, // Inferred role: camera; original name unknown.
};

class AGmkBase;
class GmkBgmCondInfo;
class GmkEvent;
class GmkLandmark;
class GmkPrecious;
class GmkSe;
class GmkSeLine;
class GmkSet;
class GmkSquad;
class GmkTutorial;
class IGmkGameObjTraverser;

class GmkLandmarkManager : public mm::mtl::PtrSingleton<GmkLandmarkManager> {
public:
  GmkLandmarkManager();
  ~GmkLandmarkManager() override { dispose(); }
  void dispose();
  static void addGmkLandmark(GmkLandmark *landmark);
  static void removeGmkLandmark(GmkLandmark *landmark);
  const GmkLandmark *findFirstAddedGmkLandmarkByCategory(u8 category) const;

  mm::mtl::IntrusiveList<GmkLandmark> unknown08; // Inferred role: landmarks sorted by category; original member name unknown.
  GmkLandmark *unknown20;                        // Inferred role: front landmark; original member name unknown.
};

static_assert(offsetof(GmkLandmarkManager, unknown20) == 0x20, "");
static_assert(sizeof(GmkLandmarkManager) == 0x28, "");

class GmkBgmCondInfoManager : public mm::mtl::PtrSingleton<GmkBgmCondInfoManager> {
public:
  GmkBgmCondInfoManager() : unknown20(nullptr) {}
  ~GmkBgmCondInfoManager() override { dispose(); }
  void dispose();
  static void addGmkBgmCondInfo(GmkBgmCondInfo *info);
  static void removeGmkBgmCondInfo(GmkBgmCondInfo *info);
  void applyFieldBgm() const;

  mm::mtl::IntrusiveList<GmkBgmCondInfo> unknown08; // Inferred role: active condition infos; original member name unknown.
  GmkBgmCondInfo *unknown20;                        // Inferred role: front condition info; original member name unknown.
};

static_assert(offsetof(GmkBgmCondInfoManager, unknown08) == 0x08, "");
static_assert(offsetof(GmkBgmCondInfoManager, unknown20) == 0x20, "");
static_assert(sizeof(GmkBgmCondInfoManager) == 0x28, "");

class GmkSquadManager : public mm::mtl::PtrSingleton<GmkSquadManager> {
public:
  ~GmkSquadManager() override { clearGmkSquads(); }
  void update(f32 deltaTime);
  void addGmkSquad(GmkSquad *squad);
  void removeGmkSquad(GmkSquad *squad);
  void clearGmkSquads();
  void debugDraw() const;

  mm::mtl::IntrusiveList<GmkSquad> unknown08; // Inferred role: squads; original member name unknown.
};

static_assert(offsetof(GmkSquadManager, unknown08) == 0x08, "");
static_assert(sizeof(GmkSquadManager) == 0x20, "");

class GmkManager : public mm::mtl::PtrSingleton<GmkManager> {
public:
  struct CreateInfo {
    CreateInfo() : unknown4c(2) {}

    mtl::ALLOC_HANDLE unknown00;   // Inferred role: memory; original member name unknown.
    mm::mtl::FixStr<32> unknown04; // Inferred role: res def bdat path; original member name unknown.
    mm::mtl::FixStr<32> unknown28; // Inferred role: gmk set list bdat name; original member name unknown.
    u32 unknown4c;                 // Inferred role: gmk set capacity; original member name unknown.
  };

  GmkManager();
  ~GmkManager() override;
  void create(const CreateInfo &info);
  bool isValid() const;
  void dispose();
  void seqWaitValidateResDefBdatFp(f32 deltaTime);
  void seqUpdate(f32 deltaTime);
  bool isGmkSetsReady() const;

  bool updateImmediate();
  bool isValidView() const;
  const char *getFilenameByType(int gmkSetId, GmkType type) const;
  const char *getSheetnameByType(int gmkSetId, GmkType type) const;
  int getMapBdatId(int gmkSetId) const;
  const AGmkBase *findFirstGmkInstByBdatId(GmkType type, int bdatId) const;
  const AGmkBase *findGmkInstByGmkInstIndex(int gmkSetId, GmkType type, u32 index) const;
  bool traverseGmkGameObj(IGmkGameObjTraverser &traverser) const;
  template <typename T> bool traverseGmkInst(GmkType type, T &traverser) const;
  template <typename T> void collectGameObjs(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024> &handles) const;
  template <typename T> void collectGameObjsUnbound(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024> &handles) const;
  GmkSet *findGmkSet(int gmkSetId) const;
  void update(f32 deltaTime);
  void clearGmkSets();
  void createGmkSet(mtl::ALLOC_HANDLE memory, int gmkSetId, const mm::Vec3 &position, f32 rotation);
  void disposeGmkSet(int gmkSetId);
  int findFirstBdatId_RSC_GmkSetList(int map) const;
  int findFirstBdatId_RSC_GmkSetList(GmkType type, int bdatId) const;
  bool isBdatIdOfGmkInstExist(int gmkSetId, GmkType type, int bdatId) const;

  CreateInfo unknown08;                    // Inferred role: create info; original member name unknown.
  GmkBdat unknown58;                       // Inferred role: res def bdat; original member name unknown.
  u8 *unknown190;                          // Inferred role: gmk set list bdat; original member name unknown.
  unknown080 unknown198;                   // Inferred role: interest type; original member name unknown.
  GmkPhantomManager unknown1a0;            // Inferred role: phantom manager; original member name unknown.
  GmkLandmarkManager unknownf220;          // Inferred role: landmark manager; original member name unknown.
  GmkBgmCondInfoManager unknownf248;       // Inferred role: bgm condition info manager; original member name unknown.
  GmkSquadManager unknownf270;             // Inferred role: squad manager; original member name unknown.
  TGmkActiveList<GmkPrecious> unknownf290; // Inferred role: active precious list; original member name unknown.
  TGmkActiveList<GmkSe> unknownf2b8;       // Inferred role: active se list; original member name unknown.
  TGmkActiveList<GmkSeLine> unknownf2e0;   // Inferred role: active se line list; original member name unknown.
  TGmkActiveList<GmkEvent> unknownf308;    // Inferred role: active event list; original member name unknown.
  TGmkActiveList<GmkTutorial> unknownf330; // Inferred role: active tutorial list; original member name unknown.
  mm::mtl::Vector<GmkSet *> unknownf358;   // Inferred role: sets; original member name unknown.
  void (GmkManager::*unknownf380)(f32);    // Inferred role: seq; original member name unknown.
};

static_assert(sizeof(GmkManager::CreateInfo) == 0x50, "");
static_assert(offsetof(GmkManager, unknown08) == 0x08, "");
static_assert(offsetof(GmkManager, unknown58) == 0x58, "");
static_assert(offsetof(GmkManager, unknown190) == 0x190, "");
static_assert(offsetof(GmkManager, unknown198) == 0x198, "");
static_assert(offsetof(GmkManager, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GmkManager, unknownf220) == 0xf220, "");
static_assert(offsetof(GmkManager, unknownf248) == 0xf248, "");
static_assert(offsetof(GmkManager, unknownf270) == 0xf270, "");
static_assert(offsetof(GmkManager, unknownf290) == 0xf290, "");
static_assert(offsetof(GmkManager, unknownf2b8) == 0xf2b8, "");
static_assert(offsetof(GmkManager, unknownf2e0) == 0xf2e0, "");
static_assert(offsetof(GmkManager, unknownf308) == 0xf308, "");
static_assert(offsetof(GmkManager, unknownf330) == 0xf330, "");
static_assert(offsetof(GmkManager, unknownf358) == 0xf358, "");
static_assert(offsetof(GmkManager, unknownf380) == 0xf380, "");
// The GfFieldGimmick constructor places the next member 0xf3b0 bytes after its start, with the manager at 0x20.
static_assert(sizeof(GmkManager) == 0xf390, "");

int getCurrentMapBdatId();
bool isInEvent();
void setDispByGmkType(GmkType type, bool isDisp);
void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool isDisp);
void setDispByGmkTypeAndGmkIdx(int gmkSet, GmkType type, u32 index, bool isDisp);
void validateDispByGmkType(GmkType type);
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
bool hasEyeBlink(const AGmkBase &gmk);
GmkType getBindedGmkInstType(gf::GF_OBJ_HANDLE *handle);
void setEventDisp(gf::GF_OBJ_HANDLE *handle, bool isDisp);
bool getGobPosRot(mm::Vec3 &position, mm::Quat &rotation, gf::GF_OBJ_HANDLE *handle);
bool isValidView(gf::GF_OBJ_HANDLE *handle);
bool isModelRendered(gf::GF_OBJ_HANDLE *handle);
bool isNaviMeshExist(const mm::Vec3 &position);
bool getYSnapPos(mm::Vec3 &result, const mm::Vec3 &position, f32 distance);
bool getYSnapPos(mm::Vec3 &result, const mm::Vec3 &position, f32 distance, const fw::ColiCheckConfig &config);
bool getWaterHeight(f32 &height, const mm::Vec3 &position, f32 range);
bool isWaterHeightCondMatchedOfEnemy(const mm::Vec3 &position, u8 type, f32 depth);
void reqDrawCmnMsg(u32 messageId);
int getCapaOfGmkDmgPhantomTargetInfo();
bool isGfObjNumFull(u32 objectType);
bool isInBattle();
bool isInMapJumpWithLoadingSaveData();
f32 getMobPopDistSq();
void resetMobPopDistSq();
bool addFailedPopDistSq(f32 distSq);
u32 getBindedFsId(const AGmkBase &gmk);
bool isMapJumpingWithSaveData();
void setOpenMainMenuEnable(bool isEnable);
void createMenuObj(gf::GF_OBJ_HANDLE *handle);
bool isEnemyPopCondOfQuestMatched(u16 enemy);
u32 getBdatIdOfQuestTargetIcon(u32 iconType);
u32 getBdatIdOfQuestTargetIcon(gf::GF_OBJ_HANDLE *handle, u16 iconType);

bool canDepop(gf::GF_OBJ_HANDLE *handle);
bool canPopSquadMember(gf::GF_OBJ_HANDLE *handle);
bool isEnemyHoming(gf::GF_OBJ_HANDLE *handle);
void applyLodFade(u16 lodId, bool isImmediate);
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
