#include "gf/object/component/gf_com_collider.h"

#include "framework/anim/anim_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/rtti.h"

namespace fw {
struct ColiCharacterInfo;
struct ColiPhantomInfo;
} // namespace fw

namespace gf {

GfComCollider::GfComCollider() : colis(getAllocator(ALLOCATOR_DEFAULT)) { userData.owner = this; }

GfComCollider::~GfComCollider() {}

void GfComCollider::cleanup() {
  if (poseModifier.modelObject != nullptr && poseModifier.coliObject != nullptr) {
    fw::AnimationManager *manager = fw::AnimationManager::get();
    if (manager != nullptr) {
      manager->removeAfterModifier(getLayer(), poseModifier);
    }
    poseModifier.unbind();
  }

  for (u32 i = 0; i < colis.size(); i++) {
    fw::ColiObject *coli = colis[i];
    if (coli != nullptr) {
      coli->eventFlags.clear();
      coli->listener = nullptr;
      coli->coliUserData = nullptr;
    }
    if (colis[i] != nullptr) {
      colis[i]->release();
      colis[i] = nullptr;
    }
  }

  colis.clear();
}

void GfComCollider::createColiCharacter(u32 index, const fw::ColiCharacterInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
  createColi(&fw::ColiObject::createColiCharacter, index, info, frame);
}

void GfComCollider::createColiMoveCharacter(u32 index, const fw::ColiCharacterInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
  createColi(&fw::ColiMoveObject::createColiCharacter, index, info, frame);
}

void GfComCollider::createColiPhantom(u32 index, const fw::ColiPhantomInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
  createColi(&fw::ColiObject::createColiPhantom, index, info, frame);
}

void GfComCollider::enter(const EnterInfo &info) {
  fw::ColiUserData *userData = info.other->coliUserData;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
    return;
  }

  MsgObjectColiEnter message;
  message.handle = static_cast<GfObj *>(static_cast<UserData *>(userData)->owner->owner)->handle;
  message.info = &info;
  GfObj *obj = static_cast<GfObj *>(owner);
  obj->sendMessage(obj, message);
}

void GfComCollider::leave(const LeaveInfo &info) {
  fw::ColiUserData *userData = info.other->coliUserData;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
    return;
  }

  MsgObjectColiLeave message;
  message.handle = static_cast<GfObj *>(static_cast<UserData *>(userData)->owner->owner)->handle;
  message.info = &info;
  GfObj *obj = static_cast<GfObj *>(owner);
  obj->sendMessage(obj, message);
}

void GfComCollider::contact(const EnterInfo &info) {
  fw::ColiUserData *userData = info.other->coliUserData;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
    return;
  }

  MsgObjectColiContact message;
  message.handle = static_cast<GfObj *>(static_cast<UserData *>(userData)->owner->owner)->handle;
  message.info = &info;
  GfObj *obj = static_cast<GfObj *>(owner);
  obj->sendMessage(obj, message);
}

const mm::mtl::RTTI *GfComCollider::getRTTI() const { return &m_rtti; }

void GfComCollider::changeLayer(u32 oldLayer, u32 newLayer) {}

const mm::mtl::RTTI *GfComCollider::UserData::getRTTI() const { return &m_rtti; }

} // namespace gf
