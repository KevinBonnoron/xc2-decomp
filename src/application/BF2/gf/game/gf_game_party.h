#pragma once
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
struct GfPartyPosInfo;
struct GfSetupParam;
struct RQ_SETUP_PARTY;
struct RQ_SETUP_PARTY_DRIVER;
class GfComTransform;
class GfObj;
class GfWeapon;

enum CHANGE_BLADE {};

class GfMemberInfo {
public:
  GfMemberInfo();
  void clear();
  ~GfMemberInfo();

  GF_OBJ_HANDLE *driver;
  GF_OBJ_HANDLE *blades[5];
  GF_OBJ_HANDLE *trinityBlade;
  mm::mtl::IntrusivePtr<GfStatusProperty> statusProperty;
};

static_assert(offsetof(GfMemberInfo, blades) == 0x08, "");
static_assert(offsetof(GfMemberInfo, trinityBlade) == 0x30, "");
static_assert(offsetof(GfMemberInfo, statusProperty) == 0x38, "");
static_assert(sizeof(GfMemberInfo) == 0x40, "");

class GfSelectBlade {
public:
  struct Member {
    u8 bladeIndices[3];
    u8 defaultBladeIndices[3];
  };

  static void setupBattleStart(u32 partyId);
  GfSelectBlade();
  ~GfSelectBlade();
  static bool isNeedFieldBladeChange(u32 partyId);
  static int getStartBattleSetId(u32 partyId);
  static int getNeedFieldBladeChange(u32 partyId);
  static void resetStartBattleSetId(u32 partyId);
  static int resetCurrentBlade(GF_OBJ_HANDLE *handle);
  static void resetDefaultBladeForDebug(GF_OBJ_HANDLE *handle);
  static int getCurrentBladeIndex(GF_OBJ_HANDLE *handle);
  static int getChangeBladeIndex(GF_OBJ_HANDLE *handle, CHANGE_BLADE change);
  static void setBladeSetID(GF_OBJ_HANDLE *handle, int slot);
  static int getBladeSetID(GF_OBJ_HANDLE *handle, int slot);
  static int getDefBladeIndexForDebug(u32 partyId, int index);
  static int getChangeBladeIndexForDebug(u32 partyId, int index);

  static GfSelectBlade *s_pThis;

  Member members[3];
  int startBattleSetIds[3];
};

static_assert(offsetof(GfSelectBlade, startBattleSetIds) == 0x14, "");
static_assert(sizeof(GfSelectBlade) == 0x20, "");

class GfGameParty : public mm::mtl::PtrSingleton<GfGameParty>, public IGfObjListener {
public:
  enum PARTYOBJ_STATE {
    PARTYOBJ_STATE_NONE,
    PARTYOBJ_STATE_LOADING,
    PARTYOBJ_STATE_READY,
  };

  GfGameParty(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameParty();

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  void updatePartyObjReady(const fw::UpdateInfo &info);

  static u32 getPartyId(GF_OBJ_HANDLE *handle);
  static u32 getDriverBdatId(u32 partyId);
  static u32 getPartyId(u32 objectType, u32 id);
  static u32 getPartyId(GF_MOUNT_HANDLE *mountHandle);
  static u32 getPartyId(u32 hierarchy);
  static GF_OBJ_HANDLE *getHandleByHierarchy(u32 hierarchy);
  static GF_OBJ_HANDLE *getHandleMover(u32 partyId);
  static GF_OBJ_HANDLE *getHandleDriver(u32 partyId);
  static GF_OBJ_HANDLE *getHandleDriverByBdatID(u32 driver);
  static GF_OBJ_HANDLE *getHandleBlade(u32 partyId, int slot);
  static GF_OBJ_HANDLE *getHandleDriverByHierarchy(u32 hierarchy);
  static u32 getHierarchyByHandle(GF_OBJ_HANDLE *handle);
  static u32 getHierarchyDriver(u32 partyId);
  static u32 getHierarchyBlade(u32 partyId);
  static u32 getPartyMemberNum();
  static int getBladeSetId(u32 partyId, int slot);
  static u32 getBladeBdatId(u32 partyId, int slot);
  static u32 getHierarchyMax();
  static GF_OBJ_HANDLE *getHandleBladeByBdatID(u32 blade);
  static GfWeapon *getHandleWeapon(u32 partyId, int slot);
  static void destroyHandleWeapon(u32 partyId, int slot);
  static GF_MOUNT_HANDLE *getMountHandle(u32 partyId, int slot);
  static bool isExistObj();
  static bool isMemberEmpty();
  static bool isReadyObj();
  bool isReadyAllObjDisplay(bool isCheckLeader);
  void setPartyObjState(u32 partyId, PARTYOBJ_STATE state);
  virtual void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType);
  void entryHandle(GF_OBJ_HANDLE *handle, u32 objectType);
  void destroyedObject(GF_OBJ_HANDLE *handle);
  void removeHandle(GF_OBJ_HANDLE *handle);
  static void gevGameObjEnter(GF_OBJ_HANDLE *handle);
  void createdObject(GF_OBJ_HANDLE *handle);
  static void gevGameObjLeave(GF_OBJ_HANDLE *handle);
  static void gevPartyIDMemberOK(bool isOK, u32 partyId);
  static void setupBattleStart(u32 partyId);
  void buildObjDriver(GF_OBJ_HANDLE *handle);
  void buildObjBlade(GF_OBJ_HANDLE *handle);
  void buildObjWeapon(GF_OBJ_HANDLE *handle);
  void destroyObjDriver(GF_OBJ_HANDLE *handle);
  void destroyObjBlade(GF_OBJ_HANDLE *handle);
  void setPartyStateForDestroyObj(GF_OBJ_HANDLE *handle);
  void checkPartyObjReady();
  static u32 isExistDriver(u32 driver);
  static bool isExistBlade(u32 blade);
  static u32 getPartySetBladeNum();
  static u32 getPartySetBlade(u32 index);
  static void getCurrentPartyInfo(RQ_SETUP_PARTY &info);
  static void getCurrentPartyInfo(RQ_SETUP_PARTY_DRIVER &info);
  static u16 getPartyGauge();
  static void setPartyGauge(u16 partyGauge);
  static void gevChangeBlade(GF_OBJ_HANDLE *handle, int oldSlot, int newSlot);
  static void setPartyLeader(GF_OBJ_HANDLE *handle);
  static void recalcHierarchy();
  static bool setPartyLeader(u32 objectType, u32 id);
  static void createPartyStatusProperty(u32 partyId, u32 maxHp, u32 hp);
  static GfStatusProperty *getPartyStatusProperty(u32 partyId);
  static void setupRequestData(const RQ_SETUP_PARTY &info);
  static void setupNewGameParty();
  static void setDebugData(u32 partyId, bool isInvincible, bool isDisableFallDead);
  static bool isBtlLeaderDirver();
  static GF_OBJ_HANDLE *getLeaderDriver();
  static void judgeRandomTalkWarp();
  static bool isExistMismatchScenarioMask(u32 partyId);
  static u32 getLeaderLevel();
  static u32 getLeaderBdatID();
  static GF_OBJ_HANDLE *getLeader();
  static bool isLeaderBattle();
  static bool isLeaderBlade();
  static bool isMemberBattle();
  static bool reviveMembere();
  static bool isLeader(u32 objectType, u32 id);
  static GfComTransform *getLeaderTransform();
  static GfObj *getLeaderTransformObj();
  static bool isLeaderDriver(GF_OBJ_HANDLE *handle);
  static bool isPartyMemberInGameObj();
  static void getPartyPosition(GfPartyPosInfo &info);
  static void setupPartyPositionByPartyPosition(const GfPartyPosInfo &info);
  static void refreshPartyMemberPosition();

private:
  mm::mtl::FixedArray<GfMemberInfo, 3> mMembers;
  bool mInitialized;
  GfSelectBlade mSelectBlade;
  u32 mReadyFrame;
  bool mIsReadyLost;
  GF_OBJ_HANDLE *mLeader;
  PARTYOBJ_STATE mPartyObjStates[3];
};

static_assert(sizeof(GfGameParty) == 0x118, "");

class GfPartySelect {
public:
  enum LIST_TYPE {
    LIST_TYPE_PARTY,
    LIST_TYPE_RESERVER,
    LIST_TYPE_PARTY_AND_RESERVER,
  };

  static bool getDriverList(mm::mtl::FixedVector<u16, 16> &drivers, LIST_TYPE listType, u32 option);
};

} // namespace gf
