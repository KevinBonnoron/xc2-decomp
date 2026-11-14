#include "gf/field/gf_fobj_gotten_effect_manager.h"

#include "framework/effect/effect_manager.h"
#include "fw/fw_transform.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"

namespace gf {

GfFobjGottenEffectManager::GfFobjGottenEffectManager(const CreateInfo *info) : unknown00(0) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfFobjGottenEffectManager::create(const CreateInfo &info) {
  dispose();
  unknown00 = info.unknown00;
  createResHandles();
  unknown20.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  unknown20.reserve(info.unknown00, 16);
}

void GfFobjGottenEffectManager::dispose() {
  if (unknown20.size() != 0) {
    for (EffectInfo &effect : unknown20) {
      fw::EffectManager::get()->kill(effect.unknown40);
    }
    unknown20.destroy();
  }
  unknown00 = 0;
}

void GfFobjGottenEffectManager::createResHandles() {
  unknown08[0] = fw::EffectManager::get()->search("cmn_200_030", nullptr);
  unknown08[1] = fw::EffectManager::get()->search("cmn_200_031", nullptr);
  unknown08[2] = fw::EffectManager::get()->search("cmn_200_032", nullptr);
}

bool GfFobjGottenEffectManager::getTargetPos(mm::Vec3 &position, GF_OBJ_HANDLE *handle) const {
  GfObjAcc acc(handle);
  if (acc.isValidTransform()) {
    position = acc.getWorldTransform().unknown00;
    position.y += 1.0f;
    return true;
  }
  return false;
}

} // namespace gf

template void mm::mtl::Vector<gf::GfFobjGottenEffectManager::EffectInfo>::push_back(const gf::GfFobjGottenEffectManager::EffectInfo &);
template gf::GfFobjGottenEffectManager::EffectInfo *mm::mtl::Vector<gf::GfFobjGottenEffectManager::EffectInfo>::erase(gf::GfFobjGottenEffectManager::EffectInfo *);
template void mm::mtl::Vector<gf::GfFobjGottenEffectManager::EffectInfo>::expand(size_t, size_t);
