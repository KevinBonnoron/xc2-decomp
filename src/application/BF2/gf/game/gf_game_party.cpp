#include "gf/game/gf_game_party.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"

namespace gf {

static GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

constexpr u32 PARTY_ID_NONE = 0xffffffff;
constexpr int SET_BLADE_NUM_MAX = 5;
constexpr u32 READY_FRAME_MEMBER_OK = 2;
constexpr u32 READY_FRAME_MAX = 100;

GfSelectBlade *GfSelectBlade::s_pThis;

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

u32 GfGameParty::getDriverBdatId(u32 partyId) {
  if (partyId == PARTY_ID_NONE) {
    return 0;
  }

  return GfDataParty::getPartyMember(partyId)->driver;
}

u32 GfGameParty::getPartyId(u32 hierarchy) { return getPartyId(getHandleByHierarchy(hierarchy)); }

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

bool GfGameParty::isMemberEmpty() { return GfDataParty::empty(); }

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

void GfGameParty::setupBattleStart(u32 partyId) {
  DataParamAcc paramAcc(getHandleDriver(partyId));
  GfSelectBlade::s_pThis->startBattleSetIds[partyId] = paramAcc.getBladeSet(false);
}

void GfSelectBlade::setupBattleStart(u32 partyId) {
  DataParamAcc paramAcc(GfGameParty::getHandleDriver(partyId));
  s_pThis->startBattleSetIds[partyId] = paramAcc.getBladeSet(false);
}

u16 GfGameParty::getPartyGauge() { return GfDataParty::getSDataParty()->partyGauge; }

void GfGameParty::setPartyGauge(u16 partyGauge) { GfDataParty::getSDataParty()->partyGauge = partyGauge; }

GfStatusProperty *GfGameParty::getPartyStatusProperty(u32 partyId) {
  GfGameParty *party = get();
  if (party == nullptr) {
    return nullptr;
  }

  return party->mMembers[partyId].statusProperty.get();
}

void GfGameParty::setDebugData(u32, bool, bool) {}

GF_OBJ_HANDLE *GfGameParty::getLeaderDriver() { return getHandleDriver(getPartyId(getHandleByHierarchy(1))); }

u32 GfGameParty::getLeaderBdatID() { return GfDataParty::getSDataParty()->leader; }

GF_OBJ_HANDLE *GfGameParty::getLeader() { return getHandleByHierarchy(1); }

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
      members[partyId].defaultBladeIndices[index] = index;
    }
  }
  for (int partyId = 0; partyId < 3; partyId++) {
    for (int index = 0; index < 3; index++) {
      members[partyId].bladeIndices[index] = index;
    }
  }
  startBattleSetIds[0] = -1;
  startBattleSetIds[1] = -1;
  startBattleSetIds[2] = -1;
}

GfSelectBlade::~GfSelectBlade() { s_pThis = nullptr; }

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

  return s_pThis->members[partyId].defaultBladeIndices[0];
}

void GfSelectBlade::resetStartBattleSetId(u32 partyId) {
  if (s_pThis != nullptr) {
    s_pThis->startBattleSetIds[partyId] = -1;
  }
}

int GfSelectBlade::getDefBladeIndexForDebug(u32 partyId, int index) { return s_pThis->members[partyId].defaultBladeIndices[index]; }

int GfSelectBlade::getChangeBladeIndexForDebug(u32 partyId, int index) { return s_pThis->members[partyId].bladeIndices[index + 1]; }

} // namespace gf
