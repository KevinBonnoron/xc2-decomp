#include "gf/field/gf_field_look_ik.h"

#include <math.h>

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_look_solver.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_quat_impl_nx.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace fw {
class IkSolver;
} // namespace fw

namespace gf {

template <typename T> static T *castSolver(const mm::mtl::IntrusivePtr<fw::IkSolver> &solver) {
  if (solver.get() == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<T>(solver.get());
}

GfFieldLookIk::GfFieldLookIk(GF_OBJ_HANDLE *handle) {
  if (handle != unknown020) {
    create(handle);
  }
}

void GfFieldLookIk::create(GF_OBJ_HANDLE *handle) {
  dispose();
  unknown00 = handle;
}

void GfFieldLookIk::create(GF_OBJ_HANDLE *handle, const CBdatWrapper &bdat, int id) {
  // Inferred table: slot of the look solver for the bdat look at type; original name unknown.
  static const u32 unknown001[] = {9, 5, 3};

  dispose();
  unknown00 = handle;
  u8 lookAt = bdat.getValCheck("LookAt", id, gmk::BDAT_TYPE_UNKNOWN_1);
  if (lookAt == 0) {
    unknown1c = false;
  } else {
    unknown0c = static_cast<u16>(bdat.getValCheck("LookAtRange", id, gmk::BDAT_TYPE_UNKNOWN_2));
    if (lookAt > 2) {
      dispose();
      return;
    }
    unknown08 = unknown001[lookAt];
    unknown1c = true;
  }
}

void GfFieldLookIk::dispose() {
  unknown30 = false;
  if (unknown00 != unknown020) {
    GfObjAcc acc(unknown00);
    if (!acc.isDestroy() && !acc.testFlag(OBJ_FLAG_UNKNOWN_17)) {
      GfObj *obj = acc.getObj();
      if (obj != nullptr) {
        GfComIK *ik = obj->getComponent<GfComIK>();
        if (ik != nullptr) {
          const mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>> &solvers = ik->unknown10.unknown10;
          fw::LookIkSolver *look = castSolver<fw::LookIkSolver>(solvers[unknown08]);
          if (look != nullptr) {
            look->fadeOut(unknown18);
          }
        }
      }
    }
    unknown00 = unknown020;
  }
}

void GfFieldLookIk::update(f32 deltaTime) {
  if (unknown00 == unknown020 || !unknown1c) {
    return;
  }

  GfObjAcc acc(unknown00);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    dispose();
    return;
  }

  GfComIK *ik = obj->getComponent<GfComIK>();
  if (ik != nullptr) {
    const mm::mtl::Vector<mm::mtl::IntrusivePtr<fw::IkSolver>> &solvers = ik->unknown10.unknown10;
    if (unknown08 == 3) {
      fw::LookIkSolver *look = castSolver<fw::LookIkSolver>(solvers[unknown002_3]);
      if (look != nullptr) {
        updateIkSolver(*look);
      }
    } else if (unknown08 == 5) {
      fw::LookIkSolver *look = castSolver<fw::LookIkSolver>(solvers[unknown002_3]);
      if (look != nullptr && look->unknown28.get() != nullptr) {
        updateIkSolver(*look->unknown28.get());
      }
    }
  }
}

bool GfFieldLookIk::isCondMatched(const mm::Vec3 &target) const {
  mm::Vec3 position;
  if (!findPos(position)) {
    return false;
  }
  mm::Vec3 direction = target - position;
  if (fabsf(direction.x) <= 0.000001f && fabsf(direction.y) <= 0.000001f && fabsf(direction.z) <= 0.000001f) {
    return false;
  }
  f32 distance = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  if (unknown0c < distance) {
    return false;
  }
  direction *= 1.0f / distance;
  GfObjAcc acc(unknown00);
  mm::Quat rotation = acc.getWorldTransformNoSync().unknown10;
  mm::Quat::inverse(rotation);
  mm::Vec3 local = rotation.rotate(direction);
  f32 pitch = mm::unknown003(fabsf(atan2f(local.y, sqrtf(local.x * local.x + local.z * local.z))));
  if (unknown14 < pitch) {
    return false;
  }
  if (fabsf(local.x) <= 0.000001f && fabsf(local.z) <= 0.000001f) {
    return false;
  }
  mm::Vec3 horizontal(local.x, 0.0f, local.z);
  horizontal.unknown001();
  f32 yaw = mm::unknown003(fabsf(atan2f(horizontal.x, horizontal.z)));
  if (unknown10 < yaw) {
    return false;
  }
  return true;
}

bool GfFieldLookIk::isCondMatched() const {
  mm::Vec3 target;
  if (!findTargetPos(target)) {
    return false;
  }
  return isCondMatched(target);
}

bool GfFieldLookIk::findTargetPos(mm::Vec3 &position) const {
  GfObjAcc acc(unknown00);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return false;
  }

  if (gmk::GmkManager::get()->unknown198 == gmk::unknown080_1) {
    if (!gmk::isInterestPosExist()) {
      return false;
    }
    position = gmk::getInterestPos();
  } else {
    GfObj *leader = GfObjUtil::getObj(GfGameManager::getPartyLeader());
    if (leader == nullptr) {
      return false;
    }
    MsgPcGetLookPoint message;
    if (!obj->sendMessage(leader, message) || !message.unknown20) {
      return false;
    }
    position = message.unknown10;
  }
  return true;
}

bool GfFieldLookIk::findPos(mm::Vec3 &position) const {
  GfObjAcc acc(unknown00);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return false;
  }

  MsgPcGetLookPoint message;
  if (obj->sendMessage(obj, message) && message.unknown20) {
    position = message.unknown10;
  } else {
    if (!acc.isValidTransform()) {
      return false;
    }
    position = acc.getWorldTransform().unknown00;
  }
  return true;
}

} // namespace gf
