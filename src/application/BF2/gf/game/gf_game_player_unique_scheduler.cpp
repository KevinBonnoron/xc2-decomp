#include "gf/game/gf_game_player_unique_scheduler.h"
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
  paramList = fw::ParamManager::get()->uniqueMotionParamList;
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
    Unit &unit = units[index];
    if (unit.state != UNIT_STATE_REQUEST) {
      continue;
    }

    unit.timer -= info.deltaTime;
    if (unit.timer < 0.0f) {
      MsgPcFieldSetUniqueMotion message(unit.motion < UNIQUE_MOTION_NUM ? unit.motion : 0);
      GfObj *obj = GfObjUtil::getObj(unit.handle);
      if (obj != nullptr) {
        sendMessage(obj, message);
      }

      unit.state = UNIT_STATE_READY;
    }
  }
}

GfGamePlayerUniqueScheduler::GfGamePlayerUniqueScheduler() : elapsedTime(0.0f) {}

GfGamePlayerUniqueScheduler::~GfGamePlayerUniqueScheduler() {}

const UniqueMotionParam *GfGamePlayerUniqueScheduler::getParam() const {
  const fw::ParamList *list = paramList.operator->();
  if (list->count == 0 || list->entries == nullptr) {
    return nullptr;
  }

  return static_cast<const UniqueMotionParam *>(list->entries[0].param);
}

void GfGamePlayerUniqueScheduler::gevBattleStart() {
  elapsedTime = 0.0f;
  for (u32 index = 0; index < UNIT_NUM; index++) {
    units[index].state = UNIT_STATE_READY;
  }
}

} // namespace gf
