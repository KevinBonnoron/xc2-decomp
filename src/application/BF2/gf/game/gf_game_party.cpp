#include "gf/game/gf_game_party.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/gf_pause.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_scom.h"

namespace gf {

static GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

constexpr u32 PARTY_ID_NONE = 0xffffffff;
constexpr u32 PARTY_MEMBER_NUM = 3;
constexpr u32 PARTY_MEMBER_MAX = 10;
constexpr u32 PLAYER_ID_NONE = 0xffffffff;
constexpr u32 WEAPON_HANDLE_NUM = 10;
constexpr int SET_BLADE_NUM_MAX = 5;
constexpr u32 READY_FRAME_MEMBER_OK = 2;
constexpr u32 READY_FRAME_MAX = 100;
constexpr int SLOT_HIKARI = 3;
constexpr u32 BLADE_NEW_GAME = 1012;
constexpr u32 BLADE_INDEX_LIST_START = 20;
constexpr u32 BLADE_INDEX_END = 422;

static u32 getValidDriverId(const DataParamAcc &paramAcc) {
  return paramAcc.isValid() && paramAcc.getObjType() == OBJECT_TYPE_DRIVER ? paramAcc.getBdatId() : 0;
}

static u32 getValidBdatId(const DataParamAcc &paramAcc) { return paramAcc.isValid() ? paramAcc.getBdatId() : 0; }

static bool isReadyBlade(const GfObjAcc &objAcc, GF_OBJ_HANDLE *blade) {
  if (GfDataBlade::isDummyBlade(objAcc.getBladeId())) {
    return true;
  }

  if (objAcc.testFlag(OBJ_FLAG_LOADED_WAIT) && GfObjUtil::isLoading(blade)) {
    return true;
  }

  return GfGameObj::isValidGameObj(blade, true, nullptr) || GfGameObj::isEnterGameObj(blade);
}

static bool isInGameObj(GF_OBJ_HANDLE *handle) {
  if (!GfGameObj::isValidGameObj(handle, true, nullptr)) {
    return GfGameObj::isEnterGameObj(handle);
  }

  if (GfObjUtil::isTrinityBlade(handle)) {
    return true;
  }

  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  u32 playerId = GfGameUtil::getFormationPlayerID(handle);
  if (playerId == PLAYER_ID_NONE) {
    return false;
  }

  u32 followIndex = formation->players[playerId].followIndex;
  return followIndex == PLAYER_ID_NONE || formation->players[followIndex].handle != INVALID_HANDLE;
}

GfSelectBlade *GfSelectBlade::s_pThis;
static bool s_isHomuraSelected = true;

GfGameParty::GfGameParty(const GfSetupParam &param) : mReadyFrame(0), mIsReadyLost(false), mLeader(INVALID_HANDLE) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_ALL);
}

void GfGameParty::initialize(const GfSetupParam &) {
  mPartyObjStates[0] = PARTYOBJ_STATE_NONE;
  mPartyObjStates[1] = PARTYOBJ_STATE_NONE;
  mPartyObjStates[2] = PARTYOBJ_STATE_NONE;
  mInitialized = true;
}

GfGameParty::~GfGameParty() { GfObjManager::removeListener(this); }

void GfGameParty::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameParty(param); }

void GfGameParty::destroy() {
  GfGameParty *party = get();
  party->finalize();
  delete party;
}

void GfGameParty::finalize() { mInitialized = false; }

bool GfGameParty::isInitialized() {
  GfGameParty *party = get();
  if (party == nullptr) {
    return false;
  }

  return party->mInitialized;
}

void GfGameParty::update(const fw::UpdateInfo &info) { get()->updatePartyObjReady(info); }

void GfGameParty::updatePartyObjReady(const fw::UpdateInfo &) {
  checkPartyObjReady();
  bool isNotify = false;
  bool isMemberOK = false;
  if (mReadyFrame == READY_FRAME_MEMBER_OK && !mIsReadyLost) {
    isNotify = true;
    isMemberOK = true;
  } else if (mIsReadyLost) {
    mIsReadyLost = false;
    mReadyFrame = 0;
    isNotify = true;
  }

  if (isNotify) {
    GfEvent::callPartyMemberOK(isMemberOK);
  }

  if (mReadyFrame > 0 && mReadyFrame < READY_FRAME_MAX) {
    mReadyFrame++;
  }

  GF_OBJ_HANDLE *leader = GfGameManager::getPartyLeader();
  if (leader != INVALID_HANDLE && mLeader != leader) {
    mLeader = leader;
    GfEvent::callChangeLeader(leader);
  }
}

u32 GfGameParty::getPartyId(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
    GfMemberInfo *member = &get()->mMembers[0];
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
      if (member->driver == handle || member->trinityBlade == handle) {
        return partyId;
      }

      int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->driver);
      for (int slot = 0; slot < setBladeNum; slot++) {
        if (member->blades[slot] == handle) {
          return partyId;
        }

        GfWeapon *weapon = GfMountManager::getGfWeapon(member->blades[slot], GFATTACH_WEAPON);
        if (weapon == nullptr) {
          continue;
        }

        if (weapon->isExistHandle(handle)) {
          return partyId;
        }
      }
    }
  }

  return PARTY_ID_NONE;
}

u32 GfGameParty::getDriverBdatId(u32 partyId) {
  if (partyId == PARTY_ID_NONE) {
    return 0;
  }

  return GfDataParty::getPartyMember(partyId)->driver;
}

u32 GfGameParty::getPartyId(u32 objectType, u32 id) {
  GfMemberInfo *member = &get()->mMembers[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->driver);
    if (objectType == OBJECT_TYPE_DRIVER) {
      DataParamAcc paramAcc(member->driver);
      if (paramAcc.isValid() && getValidDriverId(paramAcc) == id) {
        return partyId;
      }
    }

    for (int slot = 0; slot < setBladeNum; slot++) {
      if (objectType == OBJECT_TYPE_BLADE) {
        DataParamAcc paramAcc(member->blades[slot]);
        if (paramAcc.isValid() && getValidBdatId(paramAcc) == id) {
          return partyId;
        }
      }

      if (objectType == OBJECT_TYPE_PC_WEAPON) {
        GfWeapon *weapon = GfMountManager::getGfWeapon(member->blades[slot], GFATTACH_WEAPON);
        for (u32 index = 0; index < WEAPON_HANDLE_NUM; index++) {
          DataParamAcc paramAcc(weapon->getCurrentHandles()[index]);
          if (paramAcc.isValid() && getValidBdatId(paramAcc) == id) {
            return partyId;
          }
        }
      }
    }
  }

  return PARTY_ID_NONE;
}

u32 GfGameParty::getPartyId(GF_MOUNT_HANDLE *mountHandle) {
  GfMemberInfo *member = &get()->mMembers[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (GfObjUtil::getMountHandle(member->driver, GFATTACH_WEAPON) == mountHandle) {
      return partyId;
    }

    int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->driver);
    for (int slot = 0; slot < setBladeNum; slot++) {
      if (GfObjUtil::getMountHandle(member->blades[slot], GFATTACH_WEAPON) == mountHandle) {
        return partyId;
      }

      GfWeapon *weapon = GfMountManager::getGfWeapon(member->blades[slot], GFATTACH_WEAPON);
      for (u32 index = 0; index < WEAPON_HANDLE_NUM; index++) {
        if (GfObjUtil::getMountHandle(weapon->getCurrentHandles()[index], GFATTACH_WEAPON) == mountHandle) {
          return partyId;
        }
      }
    }
  }

  return PARTY_ID_NONE;
}

u32 GfGameParty::getPartyId(u32 hierarchy) { return getPartyId(getHandleByHierarchy(hierarchy)); }

GF_OBJ_HANDLE *GfGameParty::getHandleByHierarchy(u32 hierarchy) {
  if (hierarchy == 0 || get() == nullptr) {
    return INVALID_HANDLE;
  }

  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    SDataPartyMember *partyMember = GfDataParty::getPartyMember(partyId);
    if (partyMember->hierarchyDriver == hierarchy) {
      return getHandleDriver(partyId);
    }

    if (partyMember->hierarchyBlade == hierarchy) {
      return getHandleBlade(partyId, -1);
    }
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfGameParty::getHandleMover(u32 partyId) {
  if (partyId == 0) {
    return GfGameManager::getControlMover();
  }

  return getHandleDriver(partyId);
}

GF_OBJ_HANDLE *GfGameParty::getHandleDriver(u32 partyId) {
  GfGameParty *party = get();
  if (partyId == PARTY_ID_NONE || party == nullptr) {
    return INVALID_HANDLE;
  }

  return party->mMembers[partyId].driver;
}

GF_OBJ_HANDLE *GfGameParty::getHandleDriverByBdatID(u32 driver) {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    if (GfDataParty::getPartyMember(partyId)->driver == driver) {
      return getHandleDriver(partyId);
    }
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfGameParty::getHandleBlade(u32 partyId, int slot) {
  GfGameParty *party = get();
  if (partyId == PARTY_ID_NONE || party == nullptr) {
    return INVALID_HANDLE;
  }

  if (slot < 0) {
    slot = GfDataDriver::getBladeSet(GfDataParty::getPartyMember(partyId)->driver);
    if (slot < 0) {
      return INVALID_HANDLE;
    }
  }

  return party->mMembers[partyId].blades[slot];
}

GF_OBJ_HANDLE *GfGameParty::getHandleDriverByHierarchy(u32 hierarchy) {
  GF_OBJ_HANDLE *handle = getHandleByHierarchy(hierarchy);
  if (handle == INVALID_HANDLE) {
    return INVALID_HANDLE;
  }

  return getHandleDriver(getPartyId(handle));
}

u32 GfGameParty::getHierarchyDriver(u32 partyId) { return GfDataParty::getPartyMember(partyId)->hierarchyDriver; }

u32 GfGameParty::getHierarchyBlade(u32 partyId) { return GfDataParty::getPartyMember(partyId)->hierarchyBlade; }

u32 GfGameParty::getPartyMemberNum() {
  GfDataManager::getDataGame();
  u32 memberNum = 0;
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    if (getDriverBdatId(partyId) == 0) {
      continue;
    }

    int bladeSet = GfDataDriver::getBladeSet(getDriverBdatId(partyId));
    memberNum += bladeSet >= 0 ? 2 : 1;
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(getDriverBdatId(partyId));
    for (int slot = 0; slot < setBladeNum; slot++) {
      if (slot != bladeSet && getBladeBdatId(partyId, slot) != 0) {
        memberNum++;
      }
    }
  }

  return memberNum;
}

int GfGameParty::getBladeSetId(u32 partyId, int slot) {
  if (slot >= 0) {
    return slot;
  }

  return GfDataDriver::getBladeSet(getDriverBdatId(partyId));
}

u32 GfGameParty::getBladeBdatId(u32 partyId, int slot) {
  DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, getDriverBdatId(partyId), GIMMICK_TYPE_NONE);
  return paramAcc.getBlade(slot, false);
}

u32 GfGameParty::getHierarchyMax() {
  u32 hierarchyMax = 0;
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    SDataPartyMember *partyMember = GfDataParty::getPartyMember(partyId);
    if (hierarchyMax < partyMember->hierarchyDriver) {
      hierarchyMax = partyMember->hierarchyDriver;
    }

    if (hierarchyMax < partyMember->hierarchyBlade) {
      hierarchyMax = partyMember->hierarchyBlade;
    }
  }

  return hierarchyMax;
}

GF_OBJ_HANDLE *GfGameParty::getHandleBladeByBdatID(u32 blade) {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    if (getBladeBdatId(partyId, -1) == blade) {
      return getHandleBlade(partyId, -1);
    }
  }

  return INVALID_HANDLE;
}

GfWeapon *GfGameParty::getHandleWeapon(u32 partyId, int slot) {
  return GfMountManager::getGfWeapon(getHandleBlade(partyId, getBladeSetId(partyId, slot)), GFATTACH_WEAPON);
}

void GfGameParty::destroyHandleWeapon(u32 partyId, int slot) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(getHandleBlade(partyId, getBladeSetId(partyId, slot)), GFATTACH_WEAPON);
  if (weapon == nullptr) {
    return;
  }

  weapon->isAlternate = true;
  for (u32 index = 0; index < WEAPON_HANDLE_NUM; index++) {
    GfObjUtil::destroy(weapon->getCurrentHandles()[index]);
    weapon->getCurrentHandles()[index] = INVALID_HANDLE;
  }

  weapon->isAlternate = false;
  for (u32 index = 0; index < WEAPON_HANDLE_NUM; index++) {
    GfObjUtil::destroy(weapon->getCurrentHandles()[index]);
    weapon->getCurrentHandles()[index] = INVALID_HANDLE;
  }
}

GF_MOUNT_HANDLE *GfGameParty::getMountHandle(u32 partyId, int slot) {
  GfObjAcc objAcc(getHandleBlade(partyId, slot));
  return objAcc.getMountHandle(GFATTACH_WEAPON);
}

bool GfGameParty::isExistObj() {
  GfGameParty *party = get();
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GF_OBJ_HANDLE *driver = party->mMembers[partyId].driver;
    if (driver != INVALID_HANDLE) {
      GfObjAcc objAcc(driver);
      if (objAcc.isDestroy()) {
        return true;
      }
    }

    int bladeSet = GfDataDriver::getBladeSet(GfDataParty::getPartyMember(partyId)->driver);
    if (bladeSet >= 0) {
      GF_OBJ_HANDLE *blade = party->mMembers[partyId].blades[bladeSet];
      if (blade != INVALID_HANDLE) {
        GfObjAcc objAcc(blade);
        if (objAcc.isDestroy()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool GfGameParty::isMemberEmpty() { return GfDataParty::empty(); }

bool GfGameParty::isReadyObj() {
  if (GfReqSmallCom::isExistCommand(SCOM_TYPE_CREATE_PARTY_OBJ)) {
    return false;
  }

  if (GfDataParty::empty()) {
    return true;
  }

  GfMemberInfo *member = &get()->mMembers[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (member->driver != INVALID_HANDLE && !GfGameObj::isValidGameObj(member->driver, true, nullptr) && !GfGameObj::isEnterGameObj(member->driver)) {
      return false;
    }

    int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->driver);
    for (int slot = 0; slot < setBladeNum; slot++) {
      if (member->blades[slot] == INVALID_HANDLE) {
        continue;
      }

      GfObjAcc objAcc(member->blades[slot]);
      if (GfDataBlade::isDummyBlade(objAcc.getBladeId())) {
        continue;
      }

      if (objAcc.testFlag(OBJ_FLAG_LOADED_WAIT) && GfObjUtil::isLoading(member->blades[slot])) {
        continue;
      }

      if (!GfGameObj::isValidGameObj(member->blades[slot], true, nullptr) && !GfGameObj::isEnterGameObj(member->blades[slot])) {
        return false;
      }
    }
  }

  return GfGameManager::getControlMover() != INVALID_HANDLE;
}

bool GfGameParty::isReadyAllObjDisplay(bool isCheckLeader) {
  if (GfReqSmallCom::isExistCommand(SCOM_TYPE_CREATE_PARTY_OBJ) || GfDataParty::empty()) {
    return false;
  }

  u32 objNum = 0;
  GfMemberInfo *member = &mMembers[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (member->driver != INVALID_HANDLE) {
      objNum++;
      if (!GfGameObj::isValidGameObj(member->driver, true, nullptr) && !GfGameObj::isEnterGameObj(member->driver)) {
        return false;
      }
    }

    DataParamAcc paramAcc(member->driver);
    int bladeSet = paramAcc.getBladeSet(false);
    if (bladeSet < 0) {
      continue;
    }

    GF_OBJ_HANDLE *blade = member->blades[bladeSet];
    if (blade != INVALID_HANDLE) {
      objNum++;
      GfObjAcc objAcc(blade);
      if (!isReadyBlade(objAcc, blade)) {
        return false;
      }
    }
  }

  if (objNum == 0) {
    return false;
  }

  if (isCheckLeader && GfGameManager::getPartyLeader() == INVALID_HANDLE) {
    return false;
  }

  return true;
}

void GfGameParty::setPartyObjState(u32 partyId, PARTYOBJ_STATE state) {
  PARTYOBJ_STATE oldState = mPartyObjStates[partyId];
  if (oldState == state) {
    return;
  }

  mPartyObjStates[partyId] = state;
  if (state == PARTYOBJ_STATE_READY) {
    GfEvent::callPartyIDMemberOK(true, partyId);
  } else if (oldState == PARTYOBJ_STATE_READY) {
    GfEvent::callPartyIDMemberOK(false, partyId);
  }
}

void GfGameParty::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (objectType != OBJECT_TYPE_DRIVER && objectType != OBJECT_TYPE_BLADE && objectType != OBJECT_TYPE_PC_WEAPON) {
    return;
  }

  switch (event) {
  case OBJEVT_ENTRY:
    entryHandle(handle, objectType);
    break;
  case OBJEVT_LOADED:
    if (GfPause::isPause(PAUSE_BIT_SYSTEM) && getHandleByHierarchy(1) == handle) {
      GfGameScene *scene = GfGameScene::get();
      if (scene != nullptr) {
        scene->setCameraAvtivateOneTime();
      }
    }
    break;
  case OBJEVT_DESTROY:
    destroyedObject(handle);
    break;
  case OBJEVT_REMOVE:
    removeHandle(handle);
    break;
  default:
    break;
  }
}

void GfGameParty::entryHandle(GF_OBJ_HANDLE *handle, u32 objectType) {
  switch (objectType) {
  case OBJECT_TYPE_DRIVER: {
    GfObjSetupDriver *setup = mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->setup);
    if (setup->partyMember != PARTY_ID_NONE) {
      mMembers[setup->partyMember].driver = handle;
    }
    break;
  }
  case OBJECT_TYPE_BLADE: {
    GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->setup);
    if (setup->partyMember == PARTY_ID_NONE) {
      break;
    }

    int slot = getBladeSetId(setup->partyMember, setup->slot);
    GfMemberInfo &member = mMembers[setup->partyMember];
    if (GfObjUtil::isTrinityBlade(handle)) {
      member.trinityBlade = handle;
    } else {
      member.blades[slot] = handle;
    }
    break;
  }
  case OBJECT_TYPE_PC_WEAPON: {
    GfObjSetupWeapon *setup = mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->setup);
    if (setup->partyMember == PARTY_ID_NONE) {
      break;
    }

    int slot = getBladeSetId(setup->partyMember, setup->slot);
    GfWeapon *weapon = GfMountManager::getGfWeapon(getHandleBlade(setup->partyMember, slot), GFATTACH_WEAPON);
    GfAppend *append = GfObjUtil::getAppend(handle, GFATTACH_WEAPON);
    if (append != nullptr && setup->partyMember != PARTY_ID_NONE) {
      u16 index = append->getMountIndex();
      weapon->getCurrentHandles()[index] = handle;
    }
    break;
  }
  }
}

void GfGameParty::destroyedObject(GF_OBJ_HANDLE *handle) {
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_DRIVER:
    destroyObjDriver(handle);
    break;
  case OBJECT_TYPE_BLADE:
    destroyObjBlade(handle);
    break;
  }

  if (mLeader == handle) {
    mLeader = INVALID_HANDLE;
  }

  setPartyStateForDestroyObj(handle);
}

void GfGameParty::removeHandle(GF_OBJ_HANDLE *handle) {
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_DRIVER: {
    GfObjSetupDriver *setup = mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->setup);
    if (setup->partyMember != PARTY_ID_NONE) {
      mMembers[setup->partyMember].driver = INVALID_HANDLE;
    }
    break;
  }
  case OBJECT_TYPE_BLADE: {
    GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->setup);
    if (setup->partyMember == PARTY_ID_NONE) {
      break;
    }

    GfMemberInfo &member = mMembers[setup->partyMember];
    if (GfObjUtil::isTrinityBlade(handle)) {
      member.trinityBlade = INVALID_HANDLE;
    } else {
      member.blades[getBladeSetId(setup->partyMember, setup->slot)] = INVALID_HANDLE;
    }
    break;
  }
  case OBJECT_TYPE_PC_WEAPON: {
    GfObjSetupWeapon *setup = mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->setup);
    if (setup->partyMember == PARTY_ID_NONE) {
      break;
    }

    int slot = getBladeSetId(setup->partyMember, setup->slot);
    GfWeapon *weapon = GfMountManager::getGfWeapon(getHandleBlade(setup->partyMember, slot), GFATTACH_WEAPON);
    if (weapon == nullptr) {
      break;
    }

    GfAppend *append = GfObjUtil::getAppend(handle, GFATTACH_WEAPON);
    if (append != nullptr) {
      u16 index = append->getMountIndex();
      weapon->getCurrentHandles()[index] = INVALID_HANDLE;
    }
    break;
  }
  }
}

void GfGameParty::gevGameObjEnter(GF_OBJ_HANDLE *handle) {
  GfGameParty *party = get();
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_DRIVER:
    party->buildObjDriver(handle);
    break;
  case OBJECT_TYPE_BLADE:
    party->buildObjBlade(handle);
    break;
  case OBJECT_TYPE_PC_WEAPON:
    party->buildObjWeapon(handle);
    break;
  }

  if (GfObjUtil::getObjType(handle) == OBJECT_TYPE_DRIVER && GfObjUtil::getObjSetup(handle)->characterType == CHARACTER_TYPE_PARTY) {
    GfEvent::callPartyDriver(handle, GfObjUtil::getObjSetup(handle)->partyMember, true);
  }
}

void GfGameParty::createdObject(GF_OBJ_HANDLE *handle) {
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_DRIVER:
    buildObjDriver(handle);
    break;
  case OBJECT_TYPE_BLADE:
    buildObjBlade(handle);
    break;
  case OBJECT_TYPE_PC_WEAPON:
    buildObjWeapon(handle);
    break;
  }
}

void GfGameParty::gevGameObjLeave(GF_OBJ_HANDLE *handle) {
  if (GfObjUtil::getObjType(handle) == OBJECT_TYPE_DRIVER && GfObjUtil::getObjSetup(handle)->characterType == CHARACTER_TYPE_PARTY) {
    GfEvent::callPartyDriver(handle, GfObjUtil::getObjSetup(handle)->partyMember, false);
  }
}

void GfGameParty::gevPartyIDMemberOK(bool isOK, u32 partyId) {
  if (isOK) {
    GfGameScene *scene = GfGameScene::get();
    if (scene != nullptr) {
      scene->setRideOn(partyId);
    }
  }
}

void GfGameParty::setupBattleStart(u32 partyId) {
  DataParamAcc paramAcc(getHandleDriver(partyId));
  GfSelectBlade::s_pThis->startBattleSetIds[partyId] = paramAcc.getBladeSet(false);
}

void GfSelectBlade::setupBattleStart(u32 partyId) {
  DataParamAcc paramAcc(GfGameParty::getHandleDriver(partyId));
  s_pThis->startBattleSetIds[partyId] = paramAcc.getBladeSet(false);
}

void GfGameParty::buildObjDriver(GF_OBJ_HANDLE *handle) {
  GfObjSetupDriver *setup = mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->setup);
  if (setup->partyMember != PARTY_ID_NONE && mMembers[setup->partyMember].driver == INVALID_HANDLE) {
    mMembers[setup->partyMember].driver = handle;
  }
}

void GfGameParty::buildObjBlade(GF_OBJ_HANDLE *handle) {
  GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->setup);
  if (setup->partyMember == PARTY_ID_NONE) {
    return;
  }

  int slot = getBladeSetId(setup->partyMember, setup->slot);
  GfMemberInfo &member = mMembers[setup->partyMember];
  if (GfObjUtil::isTrinityBlade(handle)) {
    if (member.trinityBlade == INVALID_HANDLE) {
      member.trinityBlade = INVALID_HANDLE;
    }
  } else if (member.blades[slot] == INVALID_HANDLE) {
    member.blades[slot] = handle;
  }
}

void GfGameParty::buildObjWeapon(GF_OBJ_HANDLE *handle) {
  GfObjSetupWeapon *setup = mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->setup);
  if (setup->partyMember == PARTY_ID_NONE) {
    return;
  }

  GfWeapon *weapon = GfMountManager::getGfWeapon(handle, GFATTACH_WEAPON);
  GfAppend *append = GfObjUtil::getAppend(handle, GFATTACH_WEAPON);
  if (weapon == nullptr || append == nullptr) {
    return;
  }

  if (weapon->getHandle(setup->isAlternate, append->getMountIndex()) == INVALID_HANDLE) {
    u16 index = append->getMountIndex();
    weapon->getCurrentHandles()[index] = handle;
  }
}

void GfGameParty::destroyObjDriver(GF_OBJ_HANDLE *handle) { mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->setup); }

void GfGameParty::destroyObjBlade(GF_OBJ_HANDLE *handle) {
  GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->setup);
  if (setup->partyMember == PARTY_ID_NONE) {
    return;
  }

  getBladeSetId(setup->partyMember, setup->slot);
  GfObjUtil::isTrinityBlade(handle);
}

void GfGameParty::setPartyStateForDestroyObj(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  u32 partyId = objAcc.getPartyID();
  if (partyId != PARTY_ID_NONE) {
    setPartyObjState(partyId, PARTYOBJ_STATE_NONE);
  }
}

u32 GfGameParty::isExistDriver(u32 driver) {
  GfGameParty *party = get();
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GF_OBJ_HANDLE *handle = party->mMembers[partyId].driver;
    if (handle != INVALID_HANDLE) {
      GfObjAcc objAcc(handle);
      if (objAcc.getDriverId() == driver) {
        return partyId + 1;
      }
    }
  }

  return 0;
}

u32 GfGameParty::getPartySetBladeNum() {
  u32 bladeNum = 0;
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GF_OBJ_HANDLE *driver = getHandleDriver(partyId);
    if (driver == INVALID_HANDLE) {
      continue;
    }

    DataParamAcc paramAcc(driver);
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(getValidDriverId(paramAcc));
    for (int slot = 0; slot < setBladeNum; slot++) {
      u32 blade = paramAcc.getBlade(slot, false);
      if (blade != 0) {
        bladeNum++;
      }
    }
  }

  return bladeNum;
}

u32 GfGameParty::getPartySetBlade(u32 index) {
  u32 bladeIndex = 0;
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GF_OBJ_HANDLE *driver = getHandleDriver(partyId);
    if (driver == INVALID_HANDLE) {
      continue;
    }

    DataParamAcc paramAcc(driver);
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(getValidDriverId(paramAcc));
    for (int slot = 0; slot < setBladeNum; slot++) {
      u32 blade = paramAcc.getBlade(slot, false);
      if (blade != 0) {
        if (bladeIndex == index) {
          return blade;
        }
        bladeIndex++;
      }
    }
  }

  return 0;
}

void GfGameParty::getCurrentPartyInfo(RQ_SETUP_PARTY &info) {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_MAX; partyId++) {
    RQ_SETUP_PARTY::Member &member = info.members[partyId];
    member.driver = GfDataParty::getPartyMember(partyId)->driver;
    member.bladeSet = GfDataDriver::getBladeSet(GfDataParty::getPartyMember(partyId)->driver);
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(member.driver);
    for (int slot = 0; slot < setBladeNum; slot++) {
      member.blades[slot] = getBladeBdatId(partyId, slot);
    }
  }

  SDataParty *dataParty = GfDataParty::getSDataParty();
  info.leaderObjectType = dataParty->leaderObjectType;
  info.savedLeaderObjectType = dataParty->savedLeaderObjectType;
  info.leader = dataParty->leader;
  info.savedLeader = dataParty->savedLeader;
}

void GfGameParty::getCurrentPartyInfo(RQ_SETUP_PARTY_DRIVER &info) {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_MAX; partyId++) {
    info.drivers[partyId] = GfDataParty::getPartyMember(partyId)->driver;
  }

  info.leader = GfDataParty::getSDataParty()->leader;
}

u16 GfGameParty::getPartyGauge() { return GfDataParty::getSDataParty()->partyGauge; }

void GfGameParty::setPartyGauge(u16 partyGauge) { GfDataParty::getSDataParty()->partyGauge = partyGauge; }

void GfGameParty::gevChangeBlade(GF_OBJ_HANDLE *handle, int, int) {
  u32 partyId = getPartyId(handle);
  if (partyId == PARTY_ID_NONE) {
    return;
  }

  GF_OBJ_HANDLE *driver = getHandleDriver(partyId);
  if (driver == INVALID_HANDLE) {
    return;
  }

  OPTMNT mountType = GfMountManager::getMountType(driver, GFATTACH_WEAPON);
  GfMountManager::removeMountHandle(driver, GFATTACH_WEAPON);
  GfMountManager::addMountHandle(GfObjUtil::getMountHandle(getHandleBlade(partyId, -1), GFATTACH_WEAPON), driver);
  GfMountManager::setMountType(driver, GFATTACH_WEAPON, mountType);
}

void GfGameParty::setPartyLeader(GF_OBJ_HANDLE *handle) {
  SDataParty *dataParty = GfDataParty::getSDataParty();
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GF_OBJ_HANDLE *driver = getHandleDriver(partyId);
    GF_OBJ_HANDLE *blade = getHandleBlade(partyId, -1);
    if (driver == handle || blade == handle) {
      DataParamAcc paramAcc(handle);
      dataParty->leader = paramAcc.getObjType() == OBJECT_TYPE_DRIVER ? getValidDriverId(paramAcc) : getValidBdatId(paramAcc);
      dataParty->leaderObjectType = paramAcc.getObjType();
      recalcHierarchy();
      GfEvent::callPartyChange();
      return;
    }
  }
}

void GfGameParty::recalcHierarchy() {
  SDataParty *dataParty = GfDataParty::getSDataParty();
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    SDataPartyMember *partyMember = GfDataParty::getPartyMember(partyId);
    partyMember->hierarchyDriver = 0;
    partyMember->hierarchyBlade = 0;
  }

  u32 leaderPartyId = 0;
  switch (dataParty->leaderObjectType) {
  case OBJECT_TYPE_DRIVER:
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
      SDataPartyMember *partyMember = GfDataParty::getPartyMember(partyId);
      if (getDriverBdatId(partyId) == dataParty->leader) {
        partyMember->hierarchyDriver = 1;
        leaderPartyId = partyId;
        break;
      }
    }
    break;
  case OBJECT_TYPE_BLADE:
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
      SDataPartyMember *partyMember = GfDataParty::getPartyMember(partyId);
      if (getBladeSetId(partyId, -1) >= 0 && getBladeBdatId(partyId, -1) == dataParty->leader) {
        partyMember->hierarchyBlade = 1;
        leaderPartyId = partyId;
        break;
      }
    }
    break;
  default:
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
      if (getDriverBdatId(partyId) != 0) {
        dataParty->leaderObjectType = OBJECT_TYPE_DRIVER;
        dataParty->leader = getDriverBdatId(partyId);
        for (u32 hierarchyPartyId = 0; hierarchyPartyId < PARTY_MEMBER_NUM; hierarchyPartyId++) {
          SDataPartyMember *partyMember = GfDataParty::getPartyMember(hierarchyPartyId);
          if (partyMember->hierarchyDriver == 0) {
            partyMember->hierarchyDriver = 1;
            leaderPartyId = hierarchyPartyId;
            break;
          }
        }
        break;
      }
    }
    break;
  }

  u32 hierarchy = 1;
  SDataPartyMember *leaderMember = GfDataParty::getPartyMember(leaderPartyId);
  if (leaderMember->driver != 0) {
    if (leaderMember->hierarchyDriver == 0) {
      if (leaderMember->hierarchyBlade == 0) {
        DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, leaderMember->driver, GIMMICK_TYPE_NONE);
        if (paramAcc.isScenarioMask()) {
          leaderMember->hierarchyBlade = 2;
          leaderMember->hierarchyDriver = 3;
        } else {
          leaderMember->hierarchyDriver = 2;
          leaderMember->hierarchyBlade = 3;
        }
        hierarchy = 3;
      } else {
        hierarchy = 2;
        leaderMember->hierarchyDriver = hierarchy;
      }
    } else if (leaderMember->hierarchyBlade == 0) {
      hierarchy = 2;
      leaderMember->hierarchyBlade = hierarchy;
    }
  }

  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    SDataPartyMember *partyMember = GfDataParty::getPartyMember(partyId);
    if (partyMember->driver == 0) {
      continue;
    }

    if (partyMember->hierarchyDriver == 0) {
      if (partyMember->hierarchyBlade == 0) {
        DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, partyMember->driver, GIMMICK_TYPE_NONE);
        if (paramAcc.isScenarioMask()) {
          partyMember->hierarchyBlade = hierarchy + 1;
          partyMember->hierarchyDriver = hierarchy + 2;
        } else {
          partyMember->hierarchyDriver = hierarchy + 1;
          partyMember->hierarchyBlade = hierarchy + 2;
        }
        hierarchy += 2;
      } else {
        partyMember->hierarchyDriver = ++hierarchy;
      }
    } else if (partyMember->hierarchyBlade == 0) {
      partyMember->hierarchyBlade = ++hierarchy;
    }
  }
}

void GfGameParty::createPartyStatusProperty(u32 partyId, u32, u32 hp) {
  GfGameParty *party = get();
  if (party == nullptr) {
    return;
  }

  party->mMembers[partyId].statusProperty = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfStatusProperty(hp);
}

GfStatusProperty *GfGameParty::getPartyStatusProperty(u32 partyId) {
  GfGameParty *party = get();
  if (party == nullptr) {
    return nullptr;
  }

  return party->mMembers[partyId].statusProperty.get();
}

void GfGameParty::setupNewGameParty() {
  RQ_SETUP_PARTY info;
  info.members[0].driver = DRIVER_REX;
  info.members[0].bladeSet = 0;
  info.members[0].blades[0] = BLADE_NEW_GAME;
  setupRequestData(info);
}

void GfGameParty::setDebugData(u32, bool, bool) {}

bool GfGameParty::isBtlLeaderDirver() { return GfObjUtil::isBattle(getLeaderDriver()); }

GF_OBJ_HANDLE *GfGameParty::getLeaderDriver() { return getHandleDriver(getPartyId(getHandleByHierarchy(1))); }

bool GfGameParty::isExistMismatchScenarioMask(u32 partyId) {
  for (u32 memberPartyId = 0; memberPartyId < PARTY_MEMBER_NUM; memberPartyId++) {
    if (partyId != PARTY_ID_NONE && partyId != memberPartyId) {
      continue;
    }

    GF_OBJ_HANDLE *driver = getHandleDriver(memberPartyId);
    if (driver == INVALID_HANDLE) {
      continue;
    }

    if (GfGameObj::isValidGameObj(driver, true, nullptr) == GfDataDriver::isScenarioMask(GfDataParty::getPartyMember(memberPartyId)->driver)) {
      return true;
    }
  }

  return false;
}

u32 GfGameParty::getLeaderLevel() {
  SDataParty *dataParty = GfDataParty::getSDataParty();
  u32 driver = 0;
  if (dataParty->leaderObjectType == OBJECT_TYPE_DRIVER) {
    driver = dataParty->leader;
  } else if (dataParty->leaderObjectType == OBJECT_TYPE_BLADE) {
    driver = getDriverBdatId(getPartyId(OBJECT_TYPE_BLADE, dataParty->leader));
  }

  DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  return paramAcc.getLevel(false);
}

u32 GfGameParty::getLeaderBdatID() { return GfDataParty::getSDataParty()->leader; }

GF_OBJ_HANDLE *GfGameParty::getLeader() { return getHandleByHierarchy(1); }

bool GfGameParty::isLeaderBattle() {
  GfObjAcc objAcc(getLeader());
  DataParamAcc paramAcc(getLeader());
  return objAcc.isBattle() && paramAcc.getHp() != 0;
}

bool GfGameParty::isLeaderBlade() {
  GfObjAcc objAcc(getLeader());
  return objAcc.getType() == OBJECT_TYPE_BLADE;
}

bool GfGameParty::isMemberBattle() {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    if (GfDataDriver::isScenarioMask(GfDataParty::getDriver(partyId))) {
      continue;
    }

    GfObjAcc objAcc(getHandleDriver(partyId));
    if (objAcc.isBattle()) {
      return true;
    }
  }

  return false;
}

bool GfGameParty::reviveMembere() {
  if (GfGameManager::isGameOver()) {
    return false;
  }

  bool isRevived = false;
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GfObj *obj = GfObjUtil::getObj(getHandleDriver(partyId));
    if (obj == nullptr) {
      continue;
    }

    DataParamAcc paramAcc(obj->handle);
    if (paramAcc.getHp() == 0) {
      MsgObjectHealHp message(0, HEAL_TYPE_FULL);
      message.isRevive = true;
      obj->sendMessage(obj, message);
      isRevived = true;
    }
  }

  return isRevived;
}

bool GfGameParty::isLeader(u32 objectType, u32 id) {
  GfObjAcc objAcc(getLeader());
  return objAcc.getType() == objectType && objAcc.getBdatId() == id;
}

GfComTransform *GfGameParty::getLeaderTransform() {
  GfObj *obj = GfObjUtil::getObj(GfGameManager::getControlMover());
  if (obj == nullptr) {
    return nullptr;
  }

  return obj->getComponent<GfComTransform>();
}

GfObj *GfGameParty::getLeaderTransformObj() { return GfObjUtil::getObj(GfGameManager::getControlMover()); }

bool GfGameParty::isLeaderDriver(GF_OBJ_HANDLE *handle) {
  if (handle == INVALID_HANDLE) {
    return false;
  }

  return getLeaderDriver() == handle;
}

bool GfGameParty::isPartyMemberInGameObj() {
  GfGameParty *party = get();
  if (party == nullptr) {
    return true;
  }

  GfMemberInfo *member = &party->mMembers[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (member->driver == INVALID_HANDLE) {
      continue;
    }

    if (!isInGameObj(member->driver)) {
      return false;
    }

    DataParamAcc paramAcc(member->driver);
    int bladeSet = paramAcc.getBladeSet(false);
    if (bladeSet < 0) {
      continue;
    }

    GF_OBJ_HANDLE *blade = member->blades[bladeSet];
    GfObjAcc objAcc(blade);
    if (objAcc.isValid() && !isInGameObj(blade) && !objAcc.testFlag(OBJ_FLAG_LOADED_WAIT_BLOCK)) {
      return false;
    }
  }

  return true;
}

void GfGameParty::getPartyPosition(GfPartyPosInfo &info) {
  info = GfPartyPosInfo();
  for (u32 index = 0; index < 6; index++) {
    GfObjAcc objAcc(getHandleByHierarchy(index + 1));
    info.positions[index].isValid = objAcc.getObjPosRot(info.positions[index].position, info.positions[index].rotation);
  }
}

GfMemberInfo::GfMemberInfo() { clear(); }

void GfMemberInfo::clear() {
  driver = INVALID_HANDLE;
  for (int slot = SET_BLADE_NUM_MAX - 1; slot >= 0; slot--) {
    blades[slot] = INVALID_HANDLE;
  }
  trinityBlade = INVALID_HANDLE;
}

GfMemberInfo::~GfMemberInfo() { clear(); }

GfSelectBlade::GfSelectBlade() {
  s_pThis = this;
  for (int partyId = 0; partyId < 3; partyId++) {
    for (int index = 0; index < 3; index++) {
      members[partyId].defaultIndices[index] = index;
    }
  }
  for (int partyId = 0; partyId < 3; partyId++) {
    members[partyId].currentIndex = 0;
    for (int index = 0; index < 2; index++) {
      members[partyId].changeIndices[index] = index + 1;
    }
  }
  startBattleSetIds[0] = -1;
  startBattleSetIds[1] = -1;
  startBattleSetIds[2] = -1;
}

GfSelectBlade::~GfSelectBlade() { s_pThis = nullptr; }

bool GfSelectBlade::isNeedFieldBladeChange(u32 partyId) {
  if (partyId == PARTY_ID_NONE) {
    return false;
  }

  int startBattleSetId = getStartBattleSetId(partyId);
  if (startBattleSetId < 0) {
    return false;
  }

  u32 driver = GfDataParty::getPartyMember(partyId)->driver;
  if (driver == 0) {
    return false;
  }

  return GfDataDriver::getBladeSet(driver) != startBattleSetId;
}

int GfSelectBlade::getStartBattleSetId(u32 partyId) {
  if (s_pThis == nullptr) {
    return -1;
  }

  return s_pThis->startBattleSetIds[partyId];
}

int GfSelectBlade::getNeedFieldBladeChange(u32 partyId) {
  if (partyId == PARTY_ID_NONE) {
    return 0;
  }

  return s_pThis->members[partyId].defaultIndices[0];
}

void GfSelectBlade::resetStartBattleSetId(u32 partyId) {
  if (s_pThis != nullptr) {
    s_pThis->startBattleSetIds[partyId] = -1;
  }
}

int GfSelectBlade::resetCurrentBlade(GF_OBJ_HANDLE *handle) {
  u32 partyId = GfGameParty::getPartyId(handle);
  if (partyId == PARTY_ID_NONE) {
    return -1;
  }

  Member &member = s_pThis->members[partyId];
  member.currentIndex = member.defaultIndices[0];
  member.changeIndices[0] = member.defaultIndices[1];
  member.changeIndices[1] = member.defaultIndices[2];
  return member.currentIndex;
}

void GfSelectBlade::resetDefaultBladeForDebug(GF_OBJ_HANDLE *handle) {
  u32 partyId = GfGameParty::getPartyId(handle);
  GfSelectBlade *selectBlade = s_pThis;
  if (partyId == PARTY_ID_NONE) {
    return;
  }

  Member &member = selectBlade->members[partyId];
  int bladeSet = GfGameParty::getBladeSetId(partyId, -1);
  if (bladeSet < 0) {
    return;
  }

  switch (bladeSet) {
  case 0:
    member.defaultIndices[0] = 0;
    member.defaultIndices[1] = 1;
    member.defaultIndices[2] = 2;
    break;
  case 1:
    member.defaultIndices[0] = 1;
    member.defaultIndices[1] = 0;
    member.defaultIndices[2] = 2;
    break;
  case 2:
    member.defaultIndices[0] = 2;
    member.defaultIndices[1] = 0;
    member.defaultIndices[2] = 1;
    break;
  }

  member.currentIndex = member.defaultIndices[0];
  member.changeIndices[0] = member.defaultIndices[1];
  member.changeIndices[1] = member.defaultIndices[2];
}

int GfSelectBlade::getCurrentBladeIndex(GF_OBJ_HANDLE *handle) {
  u32 partyId = GfGameParty::getPartyId(handle);
  if (partyId == PARTY_ID_NONE) {
    return -1;
  }

  return s_pThis->members[partyId].currentIndex;
}

int GfSelectBlade::getChangeBladeIndex(GF_OBJ_HANDLE *handle, CHANGE_BLADE changeBlade) {
  u32 partyId = GfGameParty::getPartyId(handle);
  if (partyId == PARTY_ID_NONE) {
    return -1;
  }

  return s_pThis->members[partyId].changeIndices[changeBlade];
}

void GfSelectBlade::setBladeSetID(GF_OBJ_HANDLE *handle, int slot) {
  DataParamAcc paramAcc(handle);
  if (paramAcc.isValid() && paramAcc.getObjType() == OBJECT_TYPE_DRIVER && paramAcc.getBdatId() == DRIVER_REX &&
      paramAcc.getBlade(SLOT_HIKARI, false) == BLADE_HIKARI && paramAcc.getBlade(slot, false) == BLADE_HOMURA) {
    if (paramAcc.getBlade(-1, false) == BLADE_HIKARI) {
      paramAcc.setBladeSet(slot);
      s_isHomuraSelected = true;
    } else if (paramAcc.getBlade(-1, false) == BLADE_HOMURA) {
      paramAcc.setBladeSet(SLOT_HIKARI);
      s_isHomuraSelected = false;
    } else if (s_isHomuraSelected) {
      paramAcc.setBladeSet(slot);
    } else {
      paramAcc.setBladeSet(SLOT_HIKARI);
    }
  } else {
    paramAcc.setBladeSet(slot);
  }
}

int GfSelectBlade::getBladeSetID(GF_OBJ_HANDLE *handle, int slot) {
  DataParamAcc paramAcc(handle);
  if (paramAcc.isValid() && paramAcc.getObjType() == OBJECT_TYPE_DRIVER && paramAcc.getBdatId() == DRIVER_REX &&
      paramAcc.getBlade(SLOT_HIKARI, false) == BLADE_HIKARI && paramAcc.getBlade(slot, false) == BLADE_HOMURA) {
    if (paramAcc.getBlade(-1, false) == BLADE_HIKARI) {
      for (int homuraSlot = 0; homuraSlot < SLOT_HIKARI; homuraSlot++) {
        if (paramAcc.getBlade(homuraSlot, false) == BLADE_HOMURA) {
          return homuraSlot;
        }
      }
    } else if (paramAcc.getBlade(-1, false) == BLADE_HOMURA) {
      return SLOT_HIKARI;
    }
  }

  return slot;
}

int GfSelectBlade::getDefBladeIndexForDebug(u32 partyId, int index) { return s_pThis->members[partyId].defaultIndices[index]; }

int GfSelectBlade::getChangeBladeIndexForDebug(u32 partyId, int index) { return s_pThis->members[partyId].changeIndices[index]; }

static void getPartyDriverList(mm::mtl::FixedVector<u16, 16> &drivers) {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    u32 driver = GfDataParty::getDriver(partyId);
    if (driver != 0 && !GfDataDriver::isDummyDriver(driver)) {
      drivers.push_back(driver);
    }
  }
}

static void getReserverDriverList(mm::mtl::FixedVector<u16, 16> &drivers) {
  for (u32 partyId = PARTY_MEMBER_NUM; partyId < PARTY_MEMBER_MAX; partyId++) {
    u32 driver = GfDataParty::getDriver(partyId);
    if (driver != 0 && !GfDataDriver::isDummyDriver(driver)) {
      drivers.push_back(driver);
    }
  }
}

bool GfPartySelect::getDriverList(mm::mtl::FixedVector<u16, 16> &drivers, LIST_TYPE listType, u32) {
  switch (listType) {
  case LIST_TYPE_PARTY:
    getPartyDriverList(drivers);
    break;
  case LIST_TYPE_RESERVER:
    getReserverDriverList(drivers);
    break;
  case LIST_TYPE_PARTY_AND_RESERVER:
    getPartyDriverList(drivers);
    getReserverDriverList(drivers);
    break;
  case LIST_TYPE_UNUSE: {
    GfBdatChrDr *bdatChrDr = GfBdatChrDr::get();
    u32 start = bdatChrDr->getChrDrStart();
    u32 end = bdatChrDr->getChrDrEnd();
    for (u32 driver = start; driver < end; driver++) {
      if (GfDataDriver::isActivateUnuse(driver) && !GfDataDriver::isDummyDriver(driver)) {
        drivers.push_back(driver);
      }
    }
    break;
  }
  case LIST_TYPE_ACCESSORY:
    GfGameUtil::getDriverAcceList(drivers);
    break;
  default:
    break;
  }

  return !drivers.empty();
}

static void getPartyBladeList(mm::mtl::FixedVector<u16, 422> &blades, u32 driver) {
  DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(driver); slot++) {
    u32 blade = paramAcc.getBlade(slot, false);
    if (GfDataBlade::isActivateDriver(blade) && !GfDataBlade::isDummyBlade(blade) && GfDataParty::isExistBlade(blade)) {
      blades.push_back(blade);
    }
  }
}

static void getReserverBladeList(mm::mtl::FixedVector<u16, 422> &blades, u32 driver) {
  for (u32 index = 0; index < BLADE_INDEX_END; index++) {
    u32 blade = GfDataBlade::getBladeID(index);
    if (blade == 0 || !GfDataBlade::isActivateReserver(blade) || GfDataBlade::isDummyBlade(blade)) {
      continue;
    }

    DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
    if (GfDataBlade::getCreator(blade) == driver) {
      blades.push_back(blade);
    }
  }
}

bool GfPartySelect::getBladeList(mm::mtl::FixedVector<u16, 422> &blades, u32 driver, LIST_TYPE listType, u32) {
  switch (listType) {
  case LIST_TYPE_PARTY:
    getPartyBladeList(blades, driver);
    break;
  case LIST_TYPE_PARTY_AND_RESERVER:
    getPartyBladeList(blades, driver);
    getReserverBladeList(blades, driver);
    break;
  case LIST_TYPE_RESERVER:
    getReserverBladeList(blades, driver);
    break;
  case LIST_TYPE_ALL:
    for (u32 index = BLADE_INDEX_LIST_START; index < BLADE_INDEX_END; index++) {
      u32 blade = GfDataBlade::getBladeID(index);
      if (blade != 0 && !GfDataBlade::isActivateMercenaryTeam(blade) && !GfDataBlade::isActivateUnuse(blade) && !GfDataBlade::isDummyBlade(blade)) {
        blades.push_back(blade);
      }
    }
    break;
  case LIST_TYPE_MERCENARY:
    for (u32 index = 0; index < BLADE_INDEX_END; index++) {
      u32 blade = GfDataBlade::getBladeID(index);
      if (blade != 0 && GfDataBlade::isActivateMercenaryTeam(blade) && !GfDataBlade::isDummyBlade(blade)) {
        blades.push_back(blade);
      }
    }
    break;
  default:
    break;
  }

  return !blades.empty();
}

} // namespace gf
