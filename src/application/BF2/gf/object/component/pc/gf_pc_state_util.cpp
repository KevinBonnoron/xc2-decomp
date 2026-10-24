#include "gf/object/component/pc/gf_pc_state_util.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_target.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void StateUtil::resetCamera() { GfGamePlayerCamera::resetCamera(); }

bool StateUtil::isManualCamera() { return GfGamePlayerCamera::isManualCamera(); }

void StateUtil::setTargetLock(bool isLock) { GfGameTarget::lockTarget(isLock); }

bool StateUtil::isBattle(GfComBehaviorPc &behavior) {
  if (GfGameManager::get() != nullptr) {
    return GfGameManager::isBattle();
  }
  return false;
}

void StateUtil::setEnableAgentField(GfComBehaviorPc &behavior, bool isEnable) { behavior.setEnableAgentField(isEnable); }

void StateUtil::setEnableAgentBattle(GfComBehaviorPc &behavior, bool isEnable) { behavior.setEnableAgentBattle(isEnable); }

void StateUtil::setEnableGravity(GfComBehaviorPc &behavior, bool isEnable) {
  GfComPropertyPc *property = behavior.getProperty();
  if (isEnable) {
    property->unknown110_3 = true;
  } else {
    property->unknown110_3 = false;
  }
}

bool StateUtil::testEnableGravity(GfComBehaviorPc &behavior) { return behavior.getProperty()->unknown110_3; }

void StateUtil::setEnvSensor(GfComBehaviorPc &behavior, u32 flags, bool isEnable) { behavior.unknown08->getComponent<GfComPropertyPc>()->setEnvSensorCheckFlags(flags, isEnable); }

} // namespace pc
} // namespace gf
