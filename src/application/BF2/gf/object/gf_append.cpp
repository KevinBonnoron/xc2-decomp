#include "gf/object/gf_append.h"

#include "fw/fw_transform.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/util/gf_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {

GfAppendWire::~GfAppendWire() {}

void GfAppendWire::endWire(f32 time) {
  if (time <= 0.0f) {
    unknown3c = 0.0f;
    unknown38 = 0.0f;
    unknown34 = 0;
    unknown18 = unknown020;
    GfObjAcc acc(unknown08);
    acc.setAlphaNormal(0.0f);
  } else {
    unknown34 = 3;
    unknown3c = time;
    unknown18 = unknown020;
  }
}

void GfAppendWire::startWire(GF_OBJ_HANDLE *target, f32 time) { startWireWithClose(target, time, 0.0f, 0.0f); }

void GfAppendWire::startWireWithClose(GF_OBJ_HANDLE *target, f32 time, f32 closeTime, f32 closeDistance) {
  endWire(0.0f);
  if (unknown34 == 0) {
    GfObjAcc acc(unknown08);
    acc.setAlphaNormal(1.0f);
  }
  unknown18 = target;
  unknown34 = 1;
  unknown3c = time;
  unknown38 = 0.0f;
  GfObjAcc targetAcc(target);
  unknown30 = targetAcc.getBoneIdx("JD_hip");
  if (unknown30 < 0) {
    unknown30 = targetAcc.getBoneIdx("JD_hipA");
  }
  unknown40 = closeTime;
  unknown44 = closeDistance;
  checkAndSetupSalvagePoint();
}

void GfAppendWire::startWireWithBone(GF_OBJ_HANDLE *target, const char *bone, f32 time) {
  endWire(0.0f);
  if (unknown34 == 0) {
    GfObjAcc acc(unknown08);
    acc.setAlphaNormal(1.0f);
    GfObjAcc wireAcc(unknown00);
    wireAcc.setExtMeshAlpha(0, 0.0f);
  }
  unknown18 = target;
  unknown34 = 1;
  unknown3c = time;
  unknown38 = 0.0f;
  GfObjAcc targetAcc(target);
  unknown30 = targetAcc.getBoneIdx(bone);
}

void GfAppendWire::checkAndSetupSalvagePoint() {
  GfObjAcc acc(unknown18);
  if (acc.getType() == OBJECT_TYPE_GIMMICK) {
    gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(unknown18);
    if (gmkInst != nullptr && gmkInst->getGmkType() == gmk::GMK_TYPE_SALVAGE) {
      mm::Vec3 direction = acc.getWorldTransform().unknown10.rotate(mm::Vec3(0.0f, 0.0f, 2.0f)) + acc.getWorldTransform().unknown00;
      unknown20 = acc.getWorldTransform().unknown00;
      direction -= unknown20;
      direction.unknown001();
      direction *= 0.1f;
      mm::Vec3 position = unknown20;
      for (u32 i = 1; i <= 20; i++) {
        position += direction;
        mm::Vec3 start = position + mm::Vec3(0.0f, 1.0f, 0.0f);
        mm::Vec3 end = position + mm::Vec3(0.0f, -0.8f, 0.0f);
        mm::Vec3 hit;
        if (!util::getHitCollision(hit, start, end)) {
          break;
        }
        unknown20 = hit + mm::Vec3(0.0f, -0.1f, 0.0f);
      }
      unknown48 = true;
    }
  }
}

GF_OBJ_HANDLE *GfAppendWire::getWireObject(GF_OBJ_HANDLE *handle) {
  GfWeapon *belonging = GfMountManager::getAppendHandles(handle, GFATTACH_UNKNOWN_2);
  if (belonging != nullptr) {
    return belonging->getCurrentHandles()[0];
  }
  return unknown020;
}

} // namespace gf
