#include "gf/game/gf_game_player_unique_scheduler.h"

#include <algorithm>

#include "fw/fw_param_manager.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

constexpr u32 MOTION_UNKNOWN_3 = 3; // Inferred role: unique motion num; original name unknown.

void GfGamePlayerUniqueScheduler::build(const GfSetupParam &) {
  GfGamePlayerUniqueScheduler *scheduler = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGamePlayerUniqueScheduler();
  scheduler->setup();
}

void GfGamePlayerUniqueScheduler::setup() {
  GfEvent::addEventCallback(this);
  unknown1d0 = fw::ParamManager::get()->unknown408[12];
}

void GfGamePlayerUniqueScheduler::destroy() {
  GfGamePlayerUniqueScheduler *scheduler = get();
  scheduler->cleanup();
  delete scheduler;
}

void GfGamePlayerUniqueScheduler::cleanup() { GfEvent::removeEventCallback(this); }

void GfGamePlayerUniqueScheduler::update(const fw::UpdateInfo &info) {
  GfGamePlayerUniqueScheduler *scheduler = get();
  if (scheduler == nullptr || GfGameManager::isBattle()) {
    return;
  }

  scheduler->executeRequest(info);
  scheduler->judge(info);
}

void GfGamePlayerUniqueScheduler::executeRequest(const fw::UpdateInfo &info) {
  for (u32 index = 0; index < UNIT_UNKNOWN_6; index++) {
    unknown001 &unit = unknown30[index];
    if (unit.unknown0c != UNIT_STATE_UNKNOWN_3) {
      continue;
    }

    unit.unknown14 -= info.unknown04;
    if (unit.unknown14 < 0.0f) {
      MsgPcFieldSetUniqueMotion message(unit.unknown10 < MOTION_UNKNOWN_3 ? unit.unknown10 : 0);
      GfObj *obj = GfObjUtil::getObj(unit.unknown00);
      if (obj != nullptr) {
        sendMessage(obj, message);
      }

      unit.unknown0c = UNIT_STATE_UNKNOWN_1;
    }
  }
}

GfGamePlayerUniqueScheduler::GfGamePlayerUniqueScheduler() : unknown28(0.0f) {}

GfGamePlayerUniqueScheduler::~GfGamePlayerUniqueScheduler() {}

const UniqueMotionParam *GfGamePlayerUniqueScheduler::getParam() const {
  const fw::ParamList *list = unknown1d0.operator->();
  if (list->unknown0c == 0 || list->unknown10 == nullptr) {
    return nullptr;
  }

  return static_cast<const UniqueMotionParam *>(list->unknown10[0].param);
}

void GfGamePlayerUniqueScheduler::gevBattleStart() {
  unknown28 = 0.0f;
  for (u32 index = 0; index < UNIT_UNKNOWN_6; index++) {
    unknown30[index].unknown0c = UNIT_STATE_UNKNOWN_1;
  }
}

// Inferred role: sets the unit of a party member from its handle; original name unknown.
static void unknown002(GfGamePlayerUniqueScheduler::unknown001 &unit, GF_OBJ_HANDLE *handle) {
  unit.unknown00 = handle;
  if (handle != unknown020) {
    unit.unknown08 = GfObjUtil::getObjSetup(handle)->unknown10;
    unit.unknown0c = GfGamePlayerUniqueScheduler::UNIT_STATE_UNKNOWN_1;
  } else {
    unit.unknown08 = 0;
    unit.unknown0c = GfGamePlayerUniqueScheduler::UNIT_STATE_UNKNOWN_0;
  }
}

void GfGamePlayerUniqueScheduler::gevPartyMemberOK(bool isOK) {
  if (isOK) {
    for (u32 partyId = 0; partyId < 3; partyId++) {
      unknown002(unknown30[partyId * 2], GfGameParty::getHandleDriver(partyId));
      unknown002(unknown30[partyId * 2 + 1], GfGameParty::getHandleBlade(partyId, -1));
    }
    rebuildPreset();
  }
}

void GfGamePlayerUniqueScheduler::onReload() {
  GfGamePlayerUniqueScheduler *scheduler = get();
  if (scheduler != nullptr) {
    scheduler->rebuildPreset();
  }
}

void GfGamePlayerUniqueScheduler::rebuildPreset() {
  unknownc0.clear();
  GfBdatUniqueMotion::PresetKey key(unknown30[0].unknown08, unknown30[1].unknown08, unknown30[2].unknown08, unknown30[3].unknown08, unknown30[4].unknown08, unknown30[5].unknown08);
  std::sort(key.ids, key.ids + UNIT_UNKNOWN_6);
  GfBdatUniqueMotion::queryPreset(&unknownc0, key);
}

} // namespace gf
