#include "gf/game/gf_game_player_unique_scheduler.h"

#include "fw/fw_param_manager.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

constexpr u32 UNIQUE_MOTION_NUM = 3;

void GfGamePlayerUniqueScheduler::build(const GfSetupParam &) {
  GfGamePlayerUniqueScheduler *scheduler = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGamePlayerUniqueScheduler();
  scheduler->setup();
}

void GfGamePlayerUniqueScheduler::setup() {
  GfEvent::addEventCallback(this);
  unknown1d0 = fw::ParamManager::get()->unknown468;
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
  for (u32 index = 0; index < UNIT_NUM; index++) {
    Unit &unit = unknown30[index];
    if (unit.unknown0c != UNIT_STATE_REQUEST) {
      continue;
    }

    unit.unknown14 -= info.unknown04;
    if (unit.unknown14 < 0.0f) {
      MsgPcFieldSetUniqueMotion message(unit.unknown10 < UNIQUE_MOTION_NUM ? unit.unknown10 : 0);
      GfObj *obj = GfObjUtil::getObj(unit.unknown00);
      if (obj != nullptr) {
        sendMessage(obj, message);
      }

      unit.unknown0c = UNIT_STATE_READY;
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
  for (u32 index = 0; index < UNIT_NUM; index++) {
    unknown30[index].unknown0c = UNIT_STATE_READY;
  }
}

} // namespace gf
