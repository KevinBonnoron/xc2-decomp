#include "gf/object/component/pc/field/gf_pc_state_field_wall_move.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWallMove::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->unknown310.unknown10_7 = false; }

void StateFieldWallMove::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (property->unknown310.unknown10_6) {
    MsgPcFieldNotifyWall message;
    message.unknown10 = property->unknown310.unknown130.unknown00;
    message.unknown30.unknown00 = property->unknown160.unknown00;
    message.unknown30.unknown10 = property->unknown160.unknown10;
    message.unknown50 = 3;
    StateUtilField::sendMessageWallChilds(*property, message);
  }
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
}

void StateFieldWallMove::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (StateUtilField::isWallClimbEnd(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_UPLANDING_01)) {
    reqState(STATE_ID_UNKNOWN_43);
    return;
  }
  if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0)) {
    GfPropertyField::WALL_MOVE_MODE mode = StateUtilField::decideWallMoveMode(*property);
    if (StateUtilField::isMovableWall(*property, mode)) {
      if (StateUtilField::execAsmCmd(*comAsm, StateUtilField::getAsmID(mode))) {
        property->unknown310.unknown14 = mode;
        reqState(STATE_ID_UNKNOWN_47);
        return;
      }
    } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_CLIMBIDLE)) {
      property->unknown310.unknown14 = GfPropertyField::WALL_MOVE_MODE_UNKNOWN_FFFFFFFF;
      reqState(STATE_ID_UNKNOWN_46);
      return;
    }
  }
  MoveUtilField::updateMoveWall(info, *property);
}

} // namespace pc
} // namespace gf
