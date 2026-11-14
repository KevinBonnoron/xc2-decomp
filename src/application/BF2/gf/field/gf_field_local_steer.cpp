#include "gf/field/gf_field_local_steer.h"

#include <math.h>
#include <string.h>

#include "framework/object/component_object.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior_mob.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_squad.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {

constexpr f32 unknown040 = 5.0f; // Inferred role: collide time out; original name unknown.

GfFieldLocalSteer::GfFieldLocalSteer(const CreateInfo *info) : unknown20(false), unknown24(0.0f) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfFieldLocalSteer::create(const CreateInfo &info) {
  dispose();
  if (isUseLocalSteer(info.unknown00)) {
    unknown00 = info;
    unknown28.unknown08 = 0.0f;
    unknown28.unknown0c = 0.0f;
    unknown28.unknown10 = 0.0f;
    unknown28.unknown14 = 0.0f;
  }
}

bool GfFieldLocalSteer::isTimeOutCollide() const {
  if (unknown00.unknown00 != unknown020) {
    return unknown040 < unknown24;
  }
  return false;
}

f32 GfFieldLocalSteer::getCurAngle() const {
  f32 angle = unknown28.unknown0c;
  if (unknown28.unknown10 != 0.0f) {
    f32 rate = mm::max(mm::min(1.0f, unknown28.unknown14 / unknown28.unknown10), 0.0f);
    angle = unknown28.unknown08 + (angle - unknown28.unknown08) * rate;
  }
  return angle;
}

void GfFieldLocalSteer::dispose() {
  unknown00.unknown00 = unknown020;
  unknown00.unknown08 = 2.0f;
  unknown00.unknown0c = 1.0f;
  unknown00.unknown10 = 0.5f;
  unknown00.unknown14 = true;
  unknown00.unknown18 = 0;
}

bool GfFieldLocalSteer::isUseLocalSteer(GF_OBJ_HANDLE *handle) {
  const char *model = GfAssetManager::getModelInfo(GfObjUtil::getAssetHandle(handle));
  if (model == nullptr) {
    return true;
  }
  return strcmp(model, "np510301") != 0 && strcmp(model, "np510311") != 0 && strcmp(model, "np550401") != 0;
}

void GfFieldLocalSteer::castRay(const mm::Vec3 &position) {
  unknown40.clear();
  if (unknown00.unknown00 == unknown020) {
    return;
  }
  GfObjAcc acc(unknown00.unknown00);
  if (!acc.isValid()) {
    return;
  }
  const mm::Vec3 &origin = acc.getWorldTransform().unknown00;
  mm::Vec3 ray = position - origin;
  if (fabsf(ray.x) <= 0.000001f && fabsf(ray.y) <= 0.000001f && fabsf(ray.z) <= 0.000001f) {
    return;
  }
  f32 length = sqrtf(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z);
  if (unknown00.unknown08 < length) {
    ray *= unknown00.unknown08 / length;
  }
  fw::ColiCheckConfig config;
  config.unknown04 = 0xffffffff;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown15 = false;
  config.unknown14 = true;
  config.unknown00 = 2;
  config.unknown10 = unknown00.unknown14 ? 1 : 2;
  mm::Vec3 end = ray + (origin + mm::Vec3(0.0f, unknown00.unknown0c, 0.0f));
  fw::ColiCheck::testLineChara(unknown40, origin, end, config);
}

void GfFieldLocalSteer::apply(mm::Vec3 &result, const mm::Vec3 &direction) const {
  f32 angle = getCurAngle();
  if (angle == 0.0f) {
    result = direction;
  } else {
    mm::Mat44 rotation;
    rotation.setRotY(angle);
    mm::Vec3 rotated;
    rotated.x = direction.x * rotation.rows[0][0] + direction.y * rotation.rows[1][0] + direction.z * rotation.rows[2][0];
    rotated.y = direction.x * rotation.rows[0][1] + direction.y * rotation.rows[1][1] + direction.z * rotation.rows[2][1];
    rotated.z = direction.x * rotation.rows[0][2] + direction.y * rotation.rows[1][2] + direction.z * rotation.rows[2][2];
    result = rotated;
  }
}

void validateGmkRouteNaviConsideringGfLocalSteer(gmk::GmkRouteNavi &navi, const GfFieldLocalSteer &steer, const mm::Vec3 &position) {
  if (navi.unknown00.isValid() && navi.unknown28.isValid() && navi.unknown80 && steer.unknown00.unknown00 != unknown020 && steer.unknown20) {
    f32 dx = navi.unknown90.x - position.x;
    f32 dy = navi.unknown90.y - position.y;
    f32 dz = navi.unknown90.z - position.z;
    if (sqrtf(dx * dx + dy * dy + dz * dz) < steer.unknown00.unknown08) {
      navi.updateNextPos();
    }
  }
}

bool canGetMoveVec(const navi::NvmshAcObj *navi) {
  bool result = false;
  if (navi != nullptr && (navi->unknown10 & 2) != 0 && navi->unknown08 == 1) {
    result = true;
  }
  return result;
}

bool getMoveVec(mm::Vec3 &vector, const navi::NvmshAcObj *navi) {
  if (canGetMoveVec(navi)) {
    vector = navi->getMoveVec();
    return true;
  }
  return false;
}

bool execEndSchedule(fw::ComponentObject &component) {
  GfComAsm *comAsm = static_cast<GfObj *>(component.unknown08)->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    const char *state = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
    if (state != nullptr && strstr(state, "S_schedule_") != nullptr) {
      mm::mtl::FixStr<32> command(state);
      command[0] = 'C';
      command[command.length() - 1] = '2';
      return comAsm->execCmd(command.c_str(), ANIM_LAYER_UNKNOWN_0);
    }
  }
  return false;
}

// Inferred helper: squad of the behavior component T of an object; original name unknown.
template <typename T> static gmk::GmkSquad *unknown002(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    T *behavior = obj->getComponent<T>();
    if (behavior != nullptr) {
      return behavior->unknown009();
    }
  }
  return nullptr;
}

template <typename T> bool GfFieldLocalSteer::TIsTargetNotSameSquad<T>::operator()(const GfFieldLocalSteer &steer, GF_OBJ_HANDLE *handle) const {
  gmk::GmkSquad *squad = unknown002<T>(steer.unknown00.unknown00);
  if (squad == nullptr) {
    return true;
  }
  if (squad == unknown002<T>(handle)) {
    const gmk::GmkSquadLeader *leader = squad->getBindedGmkSquadLeader();
    if (leader != nullptr && leader->getData()->unknown00 == 1) {
      return false;
    }
  }
  return true;
}

} // namespace gf

template class gf::GfFieldLocalSteer::TIsTargetNotSameSquad<gf::GfComBehaviorEnemy>;
template class gf::GfFieldLocalSteer::TIsTargetNotSameSquad<gf::GfComBehaviorMob>;
