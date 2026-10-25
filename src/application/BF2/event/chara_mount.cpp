#include "event/chara_mount.h"

#include <math.h>

#include "event/chara_dys_updater.h"
#include "event/cmd_variable.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

// Original name unknown: tests whether every component of a vector is within
// 1e-6 of zero.
static inline bool unknown001(const mm::Vec3 &vector) { return fabsf(vector.x) <= 1.0e-6f && fabsf(vector.y) <= 1.0e-6f && fabsf(vector.z) <= 1.0e-6f; }

void CharaMount::init() {}

ICmd::RESULT CharaMount::update(const Param &param) {
  if (param.getFrame() < 1 && unknown08 != nullptr) {
    gf::GfEvtModel *model = static_cast<gf::GfEvtModel *>(param.val(0).getUserdata());
    const char *bone = param.val(1).getStr();
    gf::GfComTransform *transform = gf::GfObjUtil::getObj(unknown08->unknown20)->getComponent<gf::GfComTransform>();
    if (unknown10 != nullptr) {
      unknown08->resetMount(unknown10);
      transform->setPosition(unknown20);
      transform->setRotation(unknown30);
      unknown10 = nullptr;
    }
    if (model != nullptr) {
      unknown20 = transform->getPosition();
      unknown30 = transform->getRotation();
      mm::Vec3 position(param.val(2).getF32(), param.val(3).getF32(), param.val(4).getF32());
      mm::Vec3 rotation(param.val(5).getF32(), param.val(6).getF32(), param.val(7).getF32());
      if (!unknown001(position) || !unknown001(rotation)) {
        unknown08->setMount(model, bone, position, rotation);
      } else {
        unknown08->setMount(model, bone);
      }
      unknown18->resetDynamics(0);
      unknown10 = model;
    }
  }
  return RESULT_NEXT;
}

void CharaMount::term() {
  if (unknown08 != nullptr && unknown10 != nullptr) {
    gf::GfComTransform *transform = gf::GfObjUtil::getObj(unknown08->unknown20)->getComponent<gf::GfComTransform>();
    unknown08->resetMount(unknown10);
    transform->setPosition(unknown20);
    transform->setRotation(unknown30);
    unknown10 = nullptr;
  }
}

} // namespace event
