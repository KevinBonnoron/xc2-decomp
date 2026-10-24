#include "event/attach_util.h"

#include "framework/effect/effect_manager.h"
#include "framework/object/component_object.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace fw {
class EffectCasterBase;
} // namespace fw

namespace event {

void AttachUtil::setCaster(bool isSet, gf::GF_OBJ_HANDLE *handle, u32 effect) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  if (isSet) {
    fw::EffectCasterBase *caster = mm::mtl::dynamicCast<gf::GfComEffectCaster>(gf::GfObjUtil::getObj(handle)->unknown38[gf::GfComEffectCaster::COMPONENT_INDEX])->unknown388;
    fw::EffectManager::get()->setParam(effect, caster, 1.0f);
  } else {
    fw::EffectManager::get()->setParam(effect, nullptr, 1.0f);
  }
}

void AttachUtil::setMount(bool isSet, gf::GF_OBJ_HANDLE *handle, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  gf::GfComEffectCaster *caster = gf::GfObjUtil::getObj(handle)->getComponent<gf::GfComEffectCaster>();
  if (!isSet) {
    caster->removeMountEffectEv(effect);
    return;
  }
  gf::EffectMountSetupEv setup;
  setup.unknown0 = effect;
  setup.unknown8 = bone;
  setup.unknown41 = isRotate;
  setup.unknown30 = offset;
  setup._40[0] = false;
  setup.unknown42 = type == static_cast<ATTACH_TYPE>(1);
  caster->addMountEffectEv(setup);
}

} // namespace event
