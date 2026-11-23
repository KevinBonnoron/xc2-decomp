#include "gf/object/gf_append.h"

#include <string.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_skeleton.h"
#include "fw/fw_model_object.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gf/util/gf_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_obj_acc.h"

namespace gf {

GfAppendWire::GfAppendWire(GF_OBJ_HANDLE *wire, GF_OBJ_HANDLE *owner) {
  unknown00 = wire;
  unknown08 = owner;
  unknown10 = -1;
  unknown12 = -1;
  unknown14 = -1;
  unknown16 = -1;
  unknown18 = unknown020;
  unknown20 = mm::Vec3::zero;
  unknown30 = -1;
  unknown34 = 0;
  unknown38 = 0.0f;
  unknown3c = 0.0f;
  unknown40 = 0.0f;
  unknown44 = 0.0f;
  unknown48 = false;
  GfComModel *ownerModel = GfObjUtil::getComModel(owner);
  if (ownerModel != nullptr) {
    ml::ScnObjAccResNode nodes(ownerModel->unknown18->getInterface());
    unknown12 = nodes.getBoneIndex(GfDataDriver::getBelongingMountBoneA());
    unknown14 = nodes.getBoneIndex(GfDataDriver::getBelongingMountBoneB());
  }

  GfObjAcc ownerAcc(unknown08);
  unknown16 = ownerAcc.getBoneIdx(GfDataDriver::getBelongingMountBoneA());
  const anm::Skeleton *skeleton = GfObjUtil::getComModel(unknown00)->unknown28;
  if (skeleton != nullptr) {
    // The game reads the mount count once before the loop (ldr w28 at 0x71002fd0d8; without the local it is reloaded at each iteration) and masks
    // the index to 16 bits only for the element access (and w25, w26, #0xffff at 0x71002fd108; the counter itself is not masked, add w26 and cmp
    // w26, w28 at 0x71002fd158). anm is a reserved library, so the conversion is written here. Without it the counter widens to 64 bits (108
    // instructions against the game's 109); a `u16` counter or count masks the counter at each increment (110 and 108).
    u32 count = skeleton->unknown70.size();
    for (u32 i = 0; i < count; i++) {
      if (strcmp(skeleton->unknown70[static_cast<u16>(i)], GfDataDriver::getBelongingMountBone()) == 0) {
        unknown10 = i;
        break;
      }
    }
  }

  endWire(0.0f);
}

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
