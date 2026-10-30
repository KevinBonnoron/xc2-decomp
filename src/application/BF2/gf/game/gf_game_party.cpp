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
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_scom.h"
#include "gf/request/gf_scom.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/rtti.h"

namespace gf {

constexpr u32 PARTY_MEMBER_MAX = 10;
constexpr u32 READY_FRAME_MEMBER_OK = 2;
constexpr u32 READY_FRAME_MAX = 100;
constexpr int SLOT_HIKARI = 3;
constexpr u32 BLADE_NEW_GAME = 1012;
constexpr u32 BLADE_INDEX_LIST_START = 20;
constexpr u32 BLADE_INDEX_END = 422;

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

  u32 followIndex = formation->unknown1a0[playerId].unknown00;
  return followIndex == PLAYER_ID_NONE || formation->unknown1a0[followIndex].unknown08 != INVALID_HANDLE;
}

static bool isUpdateDriver(const GfMemberInfo &member) {
  GfObjAcc objAcc(member.unknown00);
  return GfGameObj::isValidGameObj(member.unknown00, true, nullptr) || GfGameObj::isEnterGameObj(member.unknown00) || objAcc.isDestroy() || objAcc.isRebuild();
}

GfSelectBlade *GfSelectBlade::s_pThis;
static bool s_isHomuraSelected = true;

GfGameParty::GfGameParty(const GfSetupParam &param) : unknownf4(0), unknownf8(false), unknown100(INVALID_HANDLE) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_ALL);
}

void GfGameParty::initialize(const GfSetupParam &) {
  unknown108[0] = PARTYOBJ_STATE_NONE;
  unknown108[1] = PARTYOBJ_STATE_NONE;
  unknown108[2] = PARTYOBJ_STATE_NONE;
  unknownd0 = true;
}

GfGameParty::~GfGameParty() { GfObjManager::removeListener(this); }

void GfGameParty::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameParty(param); }

void GfGameParty::destroy() {
  GfGameParty *party = get();
  party->finalize();
  delete party;
}

void GfGameParty::finalize() { unknownd0 = false; }

bool GfGameParty::isInitialized() {
  GfGameParty *party = get();
  if (party == nullptr) {
    return false;
  }

  return party->unknownd0;
}

void GfGameParty::update(const fw::UpdateInfo &info) { get()->updatePartyObjReady(info); }

void GfGameParty::updatePartyObjReady(const fw::UpdateInfo &) {
  checkPartyObjReady();
  bool isNotify = false;
  bool isMemberOK = false;
  if (unknownf4 == READY_FRAME_MEMBER_OK && !unknownf8) {
    isNotify = true;
    isMemberOK = true;
  } else if (unknownf8) {
    unknownf8 = false;
    unknownf4 = 0;
    isNotify = true;
  }

  if (isNotify) {
    GfEvent::callPartyMemberOK(isMemberOK);
  }

  if (unknownf4 > 0 && unknownf4 < READY_FRAME_MAX) {
    unknownf4++;
  }

  GF_OBJ_HANDLE *leader = GfGameManager::getPartyLeader();
  if (leader != INVALID_HANDLE && unknown100 != leader) {
    unknown100 = leader;
    GfEvent::callChangeLeader(leader);
  }
}

u32 GfGameParty::getPartyId(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
    GfMemberInfo *member = &get()->unknown10[0];
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
      if (member->unknown00 == handle || member->unknown30 == handle) {
        return partyId;
      }

      int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->unknown00);
      for (int slot = 0; slot < setBladeNum; slot++) {
        if (member->unknown08[slot] == handle) {
          return partyId;
        }

        GfWeapon *weapon = GfMountManager::getGfWeapon(member->unknown08[slot], GFATTACH_WEAPON);
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

  return GfDataParty::getPartyMember(partyId)->unknown00;
}

u32 GfGameParty::getPartyId(u32 objectType, u32 id) {
  GfMemberInfo *member = &get()->unknown10[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->unknown00);
    if (objectType == OBJECT_TYPE_DRIVER) {
      DataParamAcc paramAcc(member->unknown00);
      if (paramAcc.isValid() && paramAcc.getValidDriverId() == id) {
        return partyId;
      }
    }

    for (int slot = 0; slot < setBladeNum; slot++) {
      if (objectType == OBJECT_TYPE_BLADE) {
        DataParamAcc paramAcc(member->unknown08[slot]);
        if (paramAcc.isValid() && paramAcc.getValidBdatId() == id) {
          return partyId;
        }
      }

      if (objectType == OBJECT_TYPE_PC_WEAPON) {
        GfWeapon *weapon = GfMountManager::getGfWeapon(member->unknown08[slot], GFATTACH_WEAPON);
        for (u32 index = 0; index < WEAPON_HANDLE_NUM; index++) {
          DataParamAcc paramAcc(weapon->getCurrentHandles()[index]);
          if (paramAcc.isValid() && paramAcc.getValidBdatId() == id) {
            return partyId;
          }
        }
      }
    }
  }

  return PARTY_ID_NONE;
}

u32 GfGameParty::getPartyId(GF_MOUNT_HANDLE *mountHandle) {
  GfMemberInfo *member = &get()->unknown10[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (GfObjUtil::getMountHandle(member->unknown00, GFATTACH_WEAPON) == mountHandle) {
      return partyId;
    }

    int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->unknown00);
    for (int slot = 0; slot < setBladeNum; slot++) {
      if (GfObjUtil::getMountHandle(member->unknown08[slot], GFATTACH_WEAPON) == mountHandle) {
        return partyId;
      }

      GfWeapon *weapon = GfMountManager::getGfWeapon(member->unknown08[slot], GFATTACH_WEAPON);
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
    unknown123 *partyMember = GfDataParty::getPartyMember(partyId);
    if (partyMember->unknown02 == hierarchy) {
      return getHandleDriver(partyId);
    }

    if (partyMember->unknown04 == hierarchy) {
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

  return party->unknown10[partyId].unknown00;
}

GF_OBJ_HANDLE *GfGameParty::getHandleDriverByBdatID(u32 driver) {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    if (GfDataParty::getPartyMember(partyId)->unknown00 == driver) {
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
    slot = GfDataDriver::getBladeSet(GfDataParty::getPartyMember(partyId)->unknown00);
    if (slot < 0) {
      return INVALID_HANDLE;
    }
  }

  return party->unknown10[partyId].unknown08[slot];
}

GF_OBJ_HANDLE *GfGameParty::getHandleDriverByHierarchy(u32 hierarchy) {
  GF_OBJ_HANDLE *handle = getHandleByHierarchy(hierarchy);
  if (handle == INVALID_HANDLE) {
    return INVALID_HANDLE;
  }

  return getHandleDriver(getPartyId(handle));
}

u32 GfGameParty::getHierarchyDriver(u32 partyId) { return GfDataParty::getPartyMember(partyId)->unknown02; }

u32 GfGameParty::getHierarchyBlade(u32 partyId) { return GfDataParty::getPartyMember(partyId)->unknown04; }

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
    unknown123 *partyMember = GfDataParty::getPartyMember(partyId);
    if (hierarchyMax < partyMember->unknown02) {
      hierarchyMax = partyMember->unknown02;
    }

    if (hierarchyMax < partyMember->unknown04) {
      hierarchyMax = partyMember->unknown04;
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

GfWeapon *GfGameParty::getHandleWeapon(u32 partyId, int slot) { return GfMountManager::getGfWeapon(getHandleBlade(partyId, getBladeSetId(partyId, slot)), GFATTACH_WEAPON); }

void GfGameParty::destroyHandleWeapon(u32 partyId, int slot) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(getHandleBlade(partyId, getBladeSetId(partyId, slot)), GFATTACH_WEAPON);
  if (weapon == nullptr) {
    return;
  }

  weapon->unknowna8 = true;
  for (u32 index = 0; index < WEAPON_HANDLE_NUM; index++) {
    GfObjUtil::destroy(weapon->getCurrentHandles()[index]);
    weapon->getCurrentHandles()[index] = INVALID_HANDLE;
  }

  weapon->unknowna8 = false;
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
    GF_OBJ_HANDLE *driver = party->unknown10[partyId].unknown00;
    if (driver != INVALID_HANDLE) {
      GfObjAcc objAcc(driver);
      if (objAcc.isDestroy()) {
        return true;
      }
    }

    int bladeSet = GfDataDriver::getBladeSet(GfDataParty::getPartyMember(partyId)->unknown00);
    if (bladeSet >= 0) {
      GF_OBJ_HANDLE *blade = party->unknown10[partyId].unknown08[bladeSet];
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

  GfMemberInfo *member = &get()->unknown10[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (member->unknown00 != INVALID_HANDLE && !GfGameObj::isValidGameObj(member->unknown00, true, nullptr) && !GfGameObj::isEnterGameObj(member->unknown00)) {
      return false;
    }

    int setBladeNum = GfDataDriver::getMaxSetBladeNum(GfDataParty::getPartyMember(partyId)->unknown00);
    for (int slot = 0; slot < setBladeNum; slot++) {
      if (member->unknown08[slot] == INVALID_HANDLE) {
        continue;
      }

      GfObjAcc objAcc(member->unknown08[slot]);
      if (GfDataBlade::isDummyBlade(objAcc.getBladeId())) {
        continue;
      }

      if (objAcc.testFlag(OBJ_FLAG_LOADED_WAIT) && GfObjUtil::isLoading(member->unknown08[slot])) {
        continue;
      }

      if (!GfGameObj::isValidGameObj(member->unknown08[slot], true, nullptr) && !GfGameObj::isEnterGameObj(member->unknown08[slot])) {
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
  GfMemberInfo *member = &unknown10[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (member->unknown00 != INVALID_HANDLE) {
      objNum++;
      if (!GfGameObj::isValidGameObj(member->unknown00, true, nullptr) && !GfGameObj::isEnterGameObj(member->unknown00)) {
        return false;
      }
    }

    DataParamAcc paramAcc(member->unknown00);
    int bladeSet = paramAcc.getBladeSet(false);
    if (bladeSet < 0) {
      continue;
    }

    GF_OBJ_HANDLE *blade = member->unknown08[bladeSet];
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
  PARTYOBJ_STATE oldState = unknown108[partyId];
  if (oldState == state) {
    return;
  }

  unknown108[partyId] = state;
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
    GfObjSetupDriver *setup = mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->unknown30);
    if (setup->unknown14 != PARTY_ID_NONE) {
      unknown10[setup->unknown14].unknown00 = handle;
    }
    break;
  }
  case OBJECT_TYPE_BLADE: {
    GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->unknown30);
    if (setup->unknown14 == PARTY_ID_NONE) {
      break;
    }

    int slot = getBladeSetId(setup->unknown14, setup->unknown6c);
    GfMemberInfo &member = unknown10[setup->unknown14];
    if (GfObjUtil::isTrinityBlade(handle)) {
      member.unknown30 = handle;
    } else {
      member.unknown08[slot] = handle;
    }
    break;
  }
  case OBJECT_TYPE_PC_WEAPON: {
    GfObjSetupWeapon *setup = mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->unknown30);
    if (setup->unknown14 == PARTY_ID_NONE) {
      break;
    }

    int slot = getBladeSetId(setup->unknown14, setup->unknown6c);
    GfWeapon *weapon = GfMountManager::getGfWeapon(getHandleBlade(setup->unknown14, slot), GFATTACH_WEAPON);
    GfAppend *append = GfObjUtil::getAppend(handle, GFATTACH_WEAPON);
    if (append != nullptr && setup->unknown14 != PARTY_ID_NONE) {
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

  if (unknown100 == handle) {
    unknown100 = INVALID_HANDLE;
  }

  setPartyStateForDestroyObj(handle);
}

void GfGameParty::removeHandle(GF_OBJ_HANDLE *handle) {
  switch (GfObjUtil::getObjType(handle)) {
  case OBJECT_TYPE_DRIVER: {
    GfObjSetupDriver *setup = mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->unknown30);
    if (setup->unknown14 != PARTY_ID_NONE) {
      unknown10[setup->unknown14].unknown00 = INVALID_HANDLE;
    }
    break;
  }
  case OBJECT_TYPE_BLADE: {
    GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->unknown30);
    if (setup->unknown14 == PARTY_ID_NONE) {
      break;
    }

    GfMemberInfo &member = unknown10[setup->unknown14];
    if (GfObjUtil::isTrinityBlade(handle)) {
      member.unknown30 = INVALID_HANDLE;
    } else {
      member.unknown08[getBladeSetId(setup->unknown14, setup->unknown6c)] = INVALID_HANDLE;
    }
    break;
  }
  case OBJECT_TYPE_PC_WEAPON: {
    GfObjSetupWeapon *setup = mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->unknown30);
    if (setup->unknown14 == PARTY_ID_NONE) {
      break;
    }

    int slot = getBladeSetId(setup->unknown14, setup->unknown6c);
    GfWeapon *weapon = GfMountManager::getGfWeapon(getHandleBlade(setup->unknown14, slot), GFATTACH_WEAPON);
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

  if (GfObjUtil::getObjType(handle) == OBJECT_TYPE_DRIVER && GfObjUtil::getObjSetup(handle)->unknown1c == unknown030_1) {
    GfEvent::callPartyDriver(handle, GfObjUtil::getObjSetup(handle)->unknown14, true);
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
  if (GfObjUtil::getObjType(handle) == OBJECT_TYPE_DRIVER && GfObjUtil::getObjSetup(handle)->unknown1c == unknown030_1) {
    GfEvent::callPartyDriver(handle, GfObjUtil::getObjSetup(handle)->unknown14, false);
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
  GfSelectBlade::s_pThis->unknown14[partyId] = paramAcc.getBladeSet(false);
}

void GfSelectBlade::setupBattleStart(u32 partyId) {
  DataParamAcc paramAcc(GfGameParty::getHandleDriver(partyId));
  s_pThis->unknown14[partyId] = paramAcc.getBladeSet(false);
}

void GfGameParty::buildObjDriver(GF_OBJ_HANDLE *handle) {
  GfObjSetupDriver *setup = mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->unknown30);
  if (setup->unknown14 != PARTY_ID_NONE && unknown10[setup->unknown14].unknown00 == INVALID_HANDLE) {
    unknown10[setup->unknown14].unknown00 = handle;
  }
}

void GfGameParty::buildObjBlade(GF_OBJ_HANDLE *handle) {
  GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->unknown30);
  if (setup->unknown14 == PARTY_ID_NONE) {
    return;
  }

  int slot = getBladeSetId(setup->unknown14, setup->unknown6c);
  GfMemberInfo &member = unknown10[setup->unknown14];
  if (GfObjUtil::isTrinityBlade(handle)) {
    if (member.unknown30 == INVALID_HANDLE) {
      member.unknown30 = INVALID_HANDLE;
    }
  } else if (member.unknown08[slot] == INVALID_HANDLE) {
    member.unknown08[slot] = handle;
  }
}

void GfGameParty::buildObjWeapon(GF_OBJ_HANDLE *handle) {
  GfObjSetupWeapon *setup = mm::mtl::dynamicCast<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle)->unknown30);
  if (setup->unknown14 == PARTY_ID_NONE) {
    return;
  }

  GfWeapon *weapon = GfMountManager::getGfWeapon(handle, GFATTACH_WEAPON);
  GfAppend *append = GfObjUtil::getAppend(handle, GFATTACH_WEAPON);
  if (weapon == nullptr || append == nullptr) {
    return;
  }

  if (weapon->getHandle(setup->unknown78, append->getMountIndex()) == INVALID_HANDLE) {
    u16 index = append->getMountIndex();
    weapon->getCurrentHandles()[index] = handle;
  }
}

void GfGameParty::destroyObjDriver(GF_OBJ_HANDLE *handle) { mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->unknown30); }

void GfGameParty::destroyObjBlade(GF_OBJ_HANDLE *handle) {
  GfObjSetupBlade *setup = mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->unknown30);
  if (setup->unknown14 == PARTY_ID_NONE) {
    return;
  }

  getBladeSetId(setup->unknown14, setup->unknown6c);
  GfObjUtil::isTrinityBlade(handle);
}

void GfGameParty::setPartyStateForDestroyObj(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  u32 partyId = objAcc.getPartyID();
  if (partyId != PARTY_ID_NONE) {
    setPartyObjState(partyId, PARTYOBJ_STATE_NONE);
  }
}

void GfGameParty::checkPartyObjReady() {
  if (unknownf4 != 0) {
    if (!isReadyAllObjDisplay(false)) {
      unknownf8 = true;
    }
  } else if (isReadyAllObjDisplay(true)) {
    unknownf4 = 1;
  }

  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    if (unknown10[partyId].unknown00 == INVALID_HANDLE) {
      setPartyObjState(partyId, PARTYOBJ_STATE_NONE);
      continue;
    }

    if (!isUpdateDriver(unknown10[partyId])) {
      setPartyObjState(partyId, PARTYOBJ_STATE_LOADING);
      continue;
    }

    DataParamAcc paramAcc(unknown10[partyId].unknown00);
    int bladeSet = paramAcc.getBladeSet(false);
    if (bladeSet < 0) {
      setPartyObjState(partyId, PARTYOBJ_STATE_READY);
      continue;
    }

    GF_OBJ_HANDLE *blade = unknown10[partyId].unknown08[bladeSet];
    if (blade == INVALID_HANDLE) {
      continue;
    }

    GfObjAcc objAcc(blade);
    if (GfDataBlade::isDummyBlade(objAcc.getBladeId())) {
      setPartyObjState(partyId, PARTYOBJ_STATE_READY);
    } else if (objAcc.testFlag(OBJ_FLAG_LOADED_WAIT) && GfObjUtil::isLoading(blade)) {
      setPartyObjState(partyId, PARTYOBJ_STATE_LOADING);
    } else if (GfGameObj::isValidGameObj(blade, true, nullptr) || GfGameObj::isEnterGameObj(blade) || objAcc.isDestroy() || objAcc.isRebuild()) {
      if (paramAcc.getHp() != 0) {
        setPartyObjState(partyId, PARTYOBJ_STATE_READY);
      } else {
        setPartyObjState(partyId, PARTYOBJ_STATE_LOADING);
      }
    } else {
      setPartyObjState(partyId, PARTYOBJ_STATE_LOADING);
    }
  }
}

u32 GfGameParty::isExistDriver(u32 driver) {
  GfGameParty *party = get();
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GF_OBJ_HANDLE *handle = party->unknown10[partyId].unknown00;
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
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(paramAcc.getValidDriverId());
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
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(paramAcc.getValidDriverId());
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
    RQ_SETUP_PARTY::Member &member = info.unknown00[partyId];
    member.unknown00 = GfDataParty::getPartyMember(partyId)->unknown00;
    member.unknown04 = GfDataDriver::getBladeSet(GfDataParty::getPartyMember(partyId)->unknown00);
    int setBladeNum = GfDataDriver::getMaxSetBladeNum(member.unknown00);
    for (int slot = 0; slot < setBladeNum; slot++) {
      member.unknown08[slot] = getBladeBdatId(partyId, slot);
    }
  }

  unknown124 *dataParty = GfDataParty::getSDataParty();
  info.unknownc8 = dataParty->unknown3c;
  info.unknownd0 = dataParty->unknown44;
  info.unknowncc = dataParty->unknown40;
  info.unknownd4 = dataParty->unknown48;
}

void GfGameParty::getCurrentPartyInfo(RQ_SETUP_PARTY_DRIVER &info) {
  for (u32 partyId = 0; partyId < PARTY_MEMBER_MAX; partyId++) {
    info.unknown00[partyId] = GfDataParty::getPartyMember(partyId)->unknown00;
  }

  info.unknown14 = GfDataParty::getSDataParty()->unknown40;
}

u16 GfGameParty::getPartyGauge() { return GfDataParty::getSDataParty()->unknown4c; }

void GfGameParty::setPartyGauge(u16 partyGauge) { GfDataParty::getSDataParty()->unknown4c = partyGauge; }

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
  unknown124 *dataParty = GfDataParty::getSDataParty();
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    GF_OBJ_HANDLE *driver = getHandleDriver(partyId);
    GF_OBJ_HANDLE *blade = getHandleBlade(partyId, -1);
    if (driver == handle || blade == handle) {
      DataParamAcc paramAcc(handle);
      dataParty->unknown40 = paramAcc.getObjType() == OBJECT_TYPE_DRIVER ? paramAcc.getValidDriverId() : paramAcc.getValidBdatId();
      dataParty->unknown3c = paramAcc.getObjType();
      recalcHierarchy();
      GfEvent::callPartyChange();
      return;
    }
  }
}

void GfGameParty::recalcHierarchy() {
  unknown124 *dataParty = GfDataParty::getSDataParty();
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    unknown123 *partyMember = GfDataParty::getPartyMember(partyId);
    partyMember->unknown02 = 0;
    partyMember->unknown04 = 0;
  }

  u32 leaderPartyId = 0;
  switch (dataParty->unknown3c) {
  case OBJECT_TYPE_DRIVER:
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
      unknown123 *partyMember = GfDataParty::getPartyMember(partyId);
      if (getDriverBdatId(partyId) == dataParty->unknown40) {
        partyMember->unknown02 = 1;
        leaderPartyId = partyId;
        break;
      }
    }
    break;
  case OBJECT_TYPE_BLADE:
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
      unknown123 *partyMember = GfDataParty::getPartyMember(partyId);
      if (getBladeSetId(partyId, -1) >= 0 && getBladeBdatId(partyId, -1) == dataParty->unknown40) {
        partyMember->unknown04 = 1;
        leaderPartyId = partyId;
        break;
      }
    }
    break;
  default:
    for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
      if (getDriverBdatId(partyId) != 0) {
        dataParty->unknown3c = OBJECT_TYPE_DRIVER;
        dataParty->unknown40 = getDriverBdatId(partyId);
        for (u32 hierarchyPartyId = 0; hierarchyPartyId < PARTY_MEMBER_NUM; hierarchyPartyId++) {
          unknown123 *partyMember = GfDataParty::getPartyMember(hierarchyPartyId);
          if (partyMember->unknown02 == 0) {
            partyMember->unknown02 = 1;
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
  unknown123 *leaderMember = GfDataParty::getPartyMember(leaderPartyId);
  if (leaderMember->unknown00 != 0) {
    if (leaderMember->unknown02 == 0) {
      if (leaderMember->unknown04 == 0) {
        DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, leaderMember->unknown00, GIMMICK_TYPE_NONE);
        if (paramAcc.isScenarioMask()) {
          leaderMember->unknown04 = 2;
          leaderMember->unknown02 = 3;
        } else {
          leaderMember->unknown02 = 2;
          leaderMember->unknown04 = 3;
        }
        hierarchy = 3;
      } else {
        hierarchy = 2;
        leaderMember->unknown02 = hierarchy;
      }
    } else if (leaderMember->unknown04 == 0) {
      hierarchy = 2;
      leaderMember->unknown04 = hierarchy;
    }
  }

  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    unknown123 *partyMember = GfDataParty::getPartyMember(partyId);
    if (partyMember->unknown00 == 0) {
      continue;
    }

    if (partyMember->unknown02 == 0) {
      if (partyMember->unknown04 == 0) {
        DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, partyMember->unknown00, GIMMICK_TYPE_NONE);
        if (paramAcc.isScenarioMask()) {
          partyMember->unknown04 = hierarchy + 1;
          partyMember->unknown02 = hierarchy + 2;
        } else {
          partyMember->unknown02 = hierarchy + 1;
          partyMember->unknown04 = hierarchy + 2;
        }
        hierarchy += 2;
      } else {
        partyMember->unknown02 = ++hierarchy;
      }
    } else if (partyMember->unknown04 == 0) {
      partyMember->unknown04 = ++hierarchy;
    }
  }
}

void GfGameParty::createPartyStatusProperty(u32 partyId, u32, u32 hp) {
  GfGameParty *party = get();
  if (party == nullptr) {
    return;
  }

  party->unknown10[partyId].unknown38 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfStatusProperty(hp);
}

GfStatusProperty *GfGameParty::getPartyStatusProperty(u32 partyId) {
  GfGameParty *party = get();
  if (party == nullptr) {
    return nullptr;
  }

  return party->unknown10[partyId].unknown38.get();
}

void GfGameParty::setupNewGameParty() {
  RQ_SETUP_PARTY info;
  info.unknown00[0].unknown00 = DRIVER_REX;
  info.unknown00[0].unknown04 = 0;
  info.unknown00[0].unknown08[0] = BLADE_NEW_GAME;
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

    if (GfGameObj::isValidGameObj(driver, true, nullptr) == GfDataDriver::isScenarioMask(GfDataParty::getPartyMember(memberPartyId)->unknown00)) {
      return true;
    }
  }

  return false;
}

u32 GfGameParty::getLeaderLevel() {
  unknown124 *dataParty = GfDataParty::getSDataParty();
  u32 driver = 0;
  if (dataParty->unknown3c == OBJECT_TYPE_DRIVER) {
    driver = dataParty->unknown40;
  } else if (dataParty->unknown3c == OBJECT_TYPE_BLADE) {
    driver = getDriverBdatId(getPartyId(OBJECT_TYPE_BLADE, dataParty->unknown40));
  }

  DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  return paramAcc.getLevel(false);
}

u32 GfGameParty::getLeaderBdatID() { return GfDataParty::getSDataParty()->unknown40; }

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

    DataParamAcc paramAcc(obj->unknownf8);
    if (paramAcc.getHp() == 0) {
      MsgObjectHealHp message(0, HEAL_TYPE_FULL);
      message.unknown21 = true;
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

  GfMemberInfo *member = &party->unknown10[0];
  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++, member++) {
    if (member->unknown00 == INVALID_HANDLE) {
      continue;
    }

    if (!isInGameObj(member->unknown00)) {
      return false;
    }

    DataParamAcc paramAcc(member->unknown00);
    int bladeSet = paramAcc.getBladeSet(false);
    if (bladeSet < 0) {
      continue;
    }

    GF_OBJ_HANDLE *blade = member->unknown08[bladeSet];
    GfObjAcc objAcc(blade);
    if (objAcc.isValid() && !isInGameObj(blade) && !objAcc.testFlag(OBJ_FLAG_LOADED_WAIT_BLOCK)) {
      return false;
    }
  }

  return true;
}

void GfGameParty::getPartyPosition(GfPartyPosInfo &info) {
  GfPartyPosInfo defaultInfo;
  info = defaultInfo;
  for (u32 index = 0; index < 6; index++) {
    GfObjAcc objAcc(getHandleByHierarchy(index + 1));
    info.unknown00[index].unknown14 = objAcc.getObjPosRot(info.unknown00[index].unknown00, info.unknown00[index].unknown10);
  }
}

GfMemberInfo::GfMemberInfo() { clear(); }

void GfMemberInfo::clear() {
  unknown00 = INVALID_HANDLE;
  for (int slot = SET_BLADE_NUM_MAX - 1; slot >= 0; slot--) {
    unknown08[slot] = INVALID_HANDLE;
  }
  unknown30 = INVALID_HANDLE;
}

GfMemberInfo::~GfMemberInfo() { clear(); }

GfSelectBlade::GfSelectBlade() {
  s_pThis = this;
  for (int partyId = 0; partyId < 3; partyId++) {
    for (int index = 0; index < 3; index++) {
      unknown00[partyId].unknown03[index] = index;
    }
  }
  for (int partyId = 0; partyId < 3; partyId++) {
    unknown00[partyId].unknown00 = 0;
    for (int index = 0; index < 2; index++) {
      unknown00[partyId].unknown01[index] = index + 1;
    }
  }
  unknown14[0] = -1;
  unknown14[1] = -1;
  unknown14[2] = -1;
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

  u32 driver = GfDataParty::getPartyMember(partyId)->unknown00;
  if (driver == 0) {
    return false;
  }

  return GfDataDriver::getBladeSet(driver) != startBattleSetId;
}

int GfSelectBlade::getStartBattleSetId(u32 partyId) {
  if (s_pThis == nullptr) {
    return -1;
  }

  return s_pThis->unknown14[partyId];
}

int GfSelectBlade::getNeedFieldBladeChange(u32 partyId) {
  if (partyId == PARTY_ID_NONE) {
    return 0;
  }

  return s_pThis->unknown00[partyId].unknown03[0];
}

void GfSelectBlade::resetStartBattleSetId(u32 partyId) {
  if (s_pThis != nullptr) {
    s_pThis->unknown14[partyId] = -1;
  }
}

int GfSelectBlade::resetCurrentBlade(GF_OBJ_HANDLE *handle) {
  u32 partyId = GfGameParty::getPartyId(handle);
  if (partyId == PARTY_ID_NONE) {
    return -1;
  }

  unknown005 &member = s_pThis->unknown00[partyId];
  member.unknown00 = member.unknown03[0];
  member.unknown01[0] = member.unknown03[1];
  member.unknown01[1] = member.unknown03[2];
  return member.unknown00;
}

void GfSelectBlade::resetDefaultBladeForDebug(GF_OBJ_HANDLE *handle) {
  u32 partyId = GfGameParty::getPartyId(handle);
  GfSelectBlade *selectBlade = s_pThis;
  if (partyId == PARTY_ID_NONE) {
    return;
  }

  unknown005 &member = selectBlade->unknown00[partyId];
  int bladeSet = GfGameParty::getBladeSetId(partyId, -1);
  if (bladeSet < 0) {
    return;
  }

  switch (bladeSet) {
  case 0:
    member.unknown03[0] = 0;
    member.unknown03[1] = 1;
    member.unknown03[2] = 2;
    break;
  case 1:
    member.unknown03[0] = 1;
    member.unknown03[1] = 0;
    member.unknown03[2] = 2;
    break;
  case 2:
    member.unknown03[0] = 2;
    member.unknown03[1] = 0;
    member.unknown03[2] = 1;
    break;
  }

  member.unknown00 = member.unknown03[0];
  member.unknown01[0] = member.unknown03[1];
  member.unknown01[1] = member.unknown03[2];
}

int GfSelectBlade::getCurrentBladeIndex(GF_OBJ_HANDLE *handle) {
  u32 partyId = GfGameParty::getPartyId(handle);
  if (partyId == PARTY_ID_NONE) {
    return -1;
  }

  return s_pThis->unknown00[partyId].unknown00;
}

int GfSelectBlade::getChangeBladeIndex(GF_OBJ_HANDLE *handle, CHANGE_BLADE changeBlade) {
  u32 partyId = GfGameParty::getPartyId(handle);
  if (partyId == PARTY_ID_NONE) {
    return -1;
  }

  return s_pThis->unknown00[partyId].unknown01[changeBlade];
}

void GfSelectBlade::setBladeSetID(GF_OBJ_HANDLE *handle, int slot) {
  DataParamAcc paramAcc(handle);
  if (paramAcc.isValid() && paramAcc.getObjType() == OBJECT_TYPE_DRIVER && paramAcc.getBdatId() == DRIVER_REX && paramAcc.getBlade(SLOT_HIKARI, false) == BLADE_HIKARI &&
      paramAcc.getBlade(slot, false) == BLADE_HOMURA) {
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
  if (paramAcc.isValid() && paramAcc.getObjType() == OBJECT_TYPE_DRIVER && paramAcc.getBdatId() == DRIVER_REX && paramAcc.getBlade(SLOT_HIKARI, false) == BLADE_HIKARI &&
      paramAcc.getBlade(slot, false) == BLADE_HOMURA) {
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

int GfSelectBlade::getDefBladeIndexForDebug(u32 partyId, int index) { return s_pThis->unknown00[partyId].unknown03[index]; }

int GfSelectBlade::getChangeBladeIndexForDebug(u32 partyId, int index) { return s_pThis->unknown00[partyId].unknown01[index]; }

static void unknown001(mm::mtl::FixedVector<u16, 16> &drivers) { // Inferred role: getPartyDriverList; original function name unknown.
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
    unknown001(drivers);
    break;
  case LIST_TYPE_RESERVER:
    getReserverDriverList(drivers);
    break;
  case LIST_TYPE_PARTY_AND_RESERVER:
    unknown001(drivers);
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

static void unknown002(mm::mtl::FixedVector<u16, 422> &blades, u32 driver) { // Inferred role: getPartyBladeList; original function name unknown.
  DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  for (int slot = 0; slot < GfDataDriver::getMaxSetBladeNum(driver); slot++) {
    u32 blade = paramAcc.getBlade(slot, false);
    if (GfDataBlade::isActivateDriver(blade) && !GfDataBlade::isDummyBlade(blade) && GfDataParty::isExistBlade(blade)) {
      blades.push_back(blade);
    }
  }
}

static void unknown003(mm::mtl::FixedVector<u16, 422> &blades, u32 driver) { // Inferred role: getReserverBladeList; original function name unknown.
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
    unknown002(blades, driver);
    break;
  case LIST_TYPE_PARTY_AND_RESERVER:
    unknown002(blades, driver);
    unknown003(blades, driver);
    break;
  case LIST_TYPE_RESERVER:
    unknown003(blades, driver);
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
