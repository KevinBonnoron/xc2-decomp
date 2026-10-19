#include "event/attach_actor_cs.h"

#include <new>

#include "event/attach_util.h"
#include "event/memory_manager.h"
#include "gf/object/gf_obj_handle.h"

namespace event {

AttachActorCS::AttachActorCS(const char *name) : AttachActorBase(name), unknowna0(gf::INVALID_HANDLE) {}

AttachActorCS::~AttachActorCS() {
  while (!unknowna8.empty()) {
    setEffectCaster(false, *unknowna8[0]);
  }
  while (!unknown4b0.empty()) {
    setEffectMount(false, unknown4b0[0]->unknown0, "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
  }
}

void AttachActorCS::setActor(gf::GF_OBJ_HANDLE *actor) {
  for (size_t i = 0; i < unknowna8.size(); i++) {
    AttachUtil::setCaster(false, unknowna0, *unknowna8[i]);
  }
  for (size_t i = 0; i < unknown4b0.size(); i++) {
    AttachUtil::setMount(false,
                         unknowna0,
                         unknown4b0[i]->unknown0,
                         unknown4b0[i]->unknown8.c_str(),
                         unknown4b0[i]->unknown30,
                         unknown4b0[i]->unknown40,
                         unknown4b0[i]->unknown44);
  }
  unknown50 = actor;
  unknowna0 = actor;
  for (size_t i = 0; i < unknowna8.size(); i++) {
    AttachUtil::setCaster(true, unknowna0, *unknowna8[i]);
  }
  for (size_t i = 0; i < unknown4b0.size(); i++) {
    AttachUtil::setMount(true,
                         unknowna0,
                         unknown4b0[i]->unknown0,
                         unknown4b0[i]->unknown8.c_str(),
                         unknown4b0[i]->unknown30,
                         unknown4b0[i]->unknown40,
                         unknown4b0[i]->unknown44);
  }
}

void AttachActorCS::render() { AttachActorBase::render(); }

void AttachActorCS::setEffectCaster(bool isSet, u32 effect) {
  if (isSet) {
    if (unknowna8.size() >= EFFECT_COUNT) {
      return;
    }
    u32 *caster = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) u32(effect);
    AttachUtil::setCaster(true, unknowna0, effect);
    unknowna8.push_back(caster);
  } else {
    for (u32 **it = unknowna8.begin(); it != unknowna8.end(); ++it) {
      u32 *caster = *it;
      if (*caster == effect) {
        unknowna8.erase(it);
        AttachUtil::setCaster(false, unknowna0, effect);
        delete caster;
        return;
      }
    }
  }
}

void AttachActorCS::setEffectMount(bool isSet, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  if (isSet) {
    if (unknown4b0.size() >= EFFECT_COUNT) {
      return;
    }
    Mount *mount =
        new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) Mount(effect, bone, offset, isRotate, type);
    AttachUtil::setMount(true, unknowna0, effect, bone, offset, isRotate, type);
    unknown4b0.push_back(mount);
  } else {
    for (Mount **it = unknown4b0.begin(); it != unknown4b0.end(); ++it) {
      Mount *mount = *it;
      if (mount->unknown0 == effect) {
        unknown4b0.erase(it);
        AttachUtil::setMount(false, unknowna0, effect, bone, offset, isRotate, type);
        delete mount;
        return;
      }
    }
  }
}

bool AttachActorCS::getMtpMat(mm::Mat44 &mat, const char *name) const {
  mat = mm::Mat44::identity;
  return false;
}

void AttachActorCS::setTransform(const mm::Mat44 &transform) { unknown60 = transform; }

} // namespace event
