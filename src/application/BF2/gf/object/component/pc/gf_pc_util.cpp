#include "gf/object/component/pc/gf_pc_util.h"

#include "ai/ai_state.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

bool IsBuddy(GfComPropertyPc &property) { return property.unknown38 & 1; }

bool isEnableTurn(GfComPropertyPc &property, const mm::Vec3 &direction) {
  return property.unknown1e0.x * direction.x + property.unknown1e0.y * direction.y + property.unknown1e0.z * direction.z < 0.0f;
}

bool isBuddyPcMove(GfComPropertyPc &property) {
  if (property.unknown94 < 0.0f || property.unknown94 > 0.0f) {
    return true;
  }

  if (property.unknown80.x * property.unknown80.x + property.unknown80.y * property.unknown80.y + property.unknown80.z * property.unknown80.z > 0.0f) {
    return true;
  }

  return property.unknownc0 > 0.0f;
}

bool isWallState(ai::State *state) {
  while (state != nullptr) {
    if (state->unknown08 == STATE_ID_FIELD_WALL) {
      return true;
    }

    state = state->unknown10;
  }

  return false;
}

const mm::Vec3 &getTargetFront() {
  GfObj *obj = GfObjUtil::getObj(GfGameManager::getPartyLeader());
  return obj->getComponent<GfComPropertyPc>()->unknown1e0;
}

} // namespace pc
} // namespace gf
