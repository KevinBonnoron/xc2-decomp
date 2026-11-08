#include "gf/field/gf_big_obj_unique.h"

#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "ml/rand.h"

namespace gf {

constexpr f32 UNIQUE_MOTION_INTERVAL = 120.0f;

GfBigObjUnique::GfBigObjUnique(const CreateInfo *info) : unknown00(INVALID_HANDLE), unknown08(0.0f), unknown0c(0.0f) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfBigObjUnique::create(const CreateInfo &info) {
  dispose();
  unknown00 = info.unknown00;
  unknown08 = 0.0f;
  unknown0c = 0.0f;
}

void GfBigObjUnique::dispose() { unknown00 = INVALID_HANDLE; }

void GfBigObjUnique::update(f32 deltaTime) {
  if (unknown00 != INVALID_HANDLE) {
    GfObjAcc acc(unknown00);
    GfObj *obj = acc.getObj();
    if (obj != nullptr) {
      GfComAsm *comAsm = obj->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        f32 localTime = comAsm->getLocalTime(ANIM_LAYER_BASE);
        f32 prevTime = unknown08;
        f32 prevLocalTime = unknown0c;
        unknown08 = prevTime + deltaTime;
        unknown0c = localTime;
        if (localTime < prevLocalTime && prevTime + deltaTime >= UNIQUE_MOTION_INTERVAL) {
          unknown08 = 0.0f;
          comAsm->execCmd(ml::mtRand(0, 2) == 0 ? "C_uniqueA" : "C_uniqueB", ANIM_LAYER_BASE);
        }
      }
    }
  }
}

} // namespace gf
