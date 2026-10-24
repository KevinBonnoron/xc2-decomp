#include "gf/game/gf_game_player_formation.h"

#include "fw/fw_param_manager.h"
#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

constexpr u32 FORMATION_NUM = 4;
constexpr u32 PARAM_WARP_FOR_RANDOM_TALK = 2;

static void notifyChangePlayerID(GfGamePlayerFormation *formation, u32 playerId) {
  MsgPcFieldNotifyChangePlayerID message(playerId);
  GfObj *obj = GfObjUtil::getObj(formation->unknown1a0[playerId].unknown08);
  if (obj != nullptr) {
    formation->sendMessage(obj, message);
  }
}

const FormationParam *getFormationParam(u32 formation) {
  const fw::ParamList *paramList = fw::ParamManager::get()->formationParamList.operator->();
  const fw::ParamList::Entry *entry = formation < paramList->count ? &paramList->entries[formation] : nullptr;
  return entry != nullptr ? static_cast<const FormationParam *>(entry->param) : nullptr;
}

const WarpForRandomTalkParam *getWarpForRandomTalkParam() {
  const fw::ParamList *paramList = fw::ParamManager::get()->formationParamList.operator->();
  return paramList->count > PARAM_WARP_FOR_RANDOM_TALK ? static_cast<const WarpForRandomTalkParam *>(paramList->entries[PARAM_WARP_FOR_RANDOM_TALK].param) : nullptr;
}

void GfGamePlayerFormation::build(const GfSetupParam &param) {
  GfGamePlayerFormation *formation = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGamePlayerFormation();
  formation->setup(param);
}

void GfGamePlayerFormation::setup(const GfSetupParam &) {
  for (u32 playerId = 0; playerId < PLAYER_NUM; playerId++) {
    unknown20[playerId] = mm::Vec3::zero;
    unknown80[playerId] = mm::Vec3::zero;
    unknowne0[playerId].position = mm::Vec3::zero;
    unknowne0[playerId].rotation = mm::Quat::identity;
  }
}

void GfGamePlayerFormation::destroy() {
  GfGamePlayerFormation *formation = get();
  formation->cleanup();
  delete formation;
}

void GfGamePlayerFormation::cleanup() {}

void GfGamePlayerFormation::update(const fw::UpdateInfo &info) { get()->updateImpl(info); }

GfGamePlayerFormation::GfGamePlayerFormation() : unknown230(0), unknown234(false) {}

GfGamePlayerFormation::~GfGamePlayerFormation() {}

const fw::Transform &GfGamePlayerFormation::getFollowTransform(u32 playerId) const {
  u32 followIndex = unknown1a0[playerId].unknown00;
  if (followIndex != PLAYER_ID_NONE) {
    playerId = followIndex;
  }

  return unknowne0[playerId];
}

void GfGamePlayerFormation::swapFormation(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *otherHandle) { swapFormation(findPlayer(handle), findPlayer(otherHandle)); }

u32 GfGamePlayerFormation::findPlayer(GF_OBJ_HANDLE *handle) {
  for (u32 playerId = 0; playerId < PLAYER_NUM; playerId++) {
    if (unknown1a0[playerId].unknown08 == handle) {
      return playerId;
    }
  }

  return PLAYER_ID_NONE;
}

void GfGamePlayerFormation::swapFormation(u32 playerId, u32 otherPlayerId) {
  if (playerId == PLAYER_ID_NONE || otherPlayerId == PLAYER_ID_NONE) {
    return;
  }

  GF_OBJ_HANDLE *handle = unknown1a0[playerId].unknown08;
  unknown1a0[playerId].unknown08 = unknown1a0[otherPlayerId].unknown08;
  unknown1a0[otherPlayerId].unknown08 = handle;

  notifyChangePlayerID(this, playerId);
  notifyChangePlayerID(this, otherPlayerId);

  GfEvent::callSwapFormation(playerId, otherPlayerId);
}

void GfGamePlayerFormation::changeFormation(u32 formation) {
  if (formation < FORMATION_NUM) {
    this->unknown230 = formation;
  }
}

} // namespace gf
