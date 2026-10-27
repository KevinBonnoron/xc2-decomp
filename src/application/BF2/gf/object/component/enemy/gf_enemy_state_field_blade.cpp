#include "gf/object/component/enemy/gf_enemy_state_field_blade.h"

#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace enemy {

bool StateFieldBlade::getOwnerDriverPos(mm::Vec3 &position, GF_OBJ_HANDLE *handle) const {
  GfObjAcc acc(GfMountManager::getHandle(handle, GFATTACH_WEAPON, OPTMNT_WIRE));
  if (acc.isValidTransform()) {
    position = acc.getWorldTransform().unknown00;
    return true;
  }

  return false;
}

f32 StateFieldBlade::getEnRadius(const GfComBehaviorEnemy &behavior) const {
  DataParamAcc dataParam(static_cast<GfObj *>(behavior.unknown08)->unknownf8);
  u16 resource = dataParam.getSDataEnemy()->unknown44;
  return GfBdatRsc::get()->getRscEnEnRadius(resource);
}

void StateFieldBlade::leave(GfComBehaviorEnemy *behavior, ai::State *next) {}

void StateFieldBlade::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  if (behavior->isStateCondMatch(STATE_ID_UNKNOWN_1)) {
    behavior->unknown140.isArrivedToGoal();
  }

  if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateFieldBlade::seqWaitIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown18.update(info.unknown04);
  if (unknown18.unknown34 && unknown18.unknown35) {
    unknown50 = &StateFieldBlade::seqIdle;
  }
}

} // namespace enemy
} // namespace gf
