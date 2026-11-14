#include "gf/object/component/gf_com_collider.h"

#include "framework/anim/anim_manager.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "mm_mtl/rtti.h"

namespace gf {

GfComCollider::GfComCollider() : unknown18(getAllocator(ALLOCATOR_UNKNOWN_0)) { unknown40.unknown08 = this; }

GfComCollider::~GfComCollider() {}

void GfComCollider::setup(const SetupInfo &) { unknown18.resize(2, nullptr); }

void GfComCollider::cleanup() {
  if (unknown50.unknown18 != nullptr && unknown50.unknown20 != nullptr) {
    fw::AnimationManager *manager = fw::AnimationManager::get();
    if (manager != nullptr) {
      manager->removeAfterModifier(getLayer(), unknown50);
    }
    unknown50.unbind();
  }

  for (u32 i = 0; i < unknown18.size(); i++) {
    fw::ColiObject *coli = unknown18[i];
    if (coli != nullptr) {
      coli->setListener(nullptr);
      coli->setColiUserData(nullptr);
    }
    if (unknown18[i] != nullptr) {
      unknown18[i]->release();
      unknown18[i] = nullptr;
    }
  }

  unknown18.clear();
}

template <typename Info, typename Creator> void GfComCollider::createColi(const Creator &creator, u32 index, const Info &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> coliFrame = frame;
  if (coliFrame.get() == nullptr) {
    coliFrame = unknown08->getComponent<GfComTransform>()->unknown001();
  }
  unknown18[index] = creator(info, coliFrame);
  fw::unknown136 events;
  events.unknown00 = info.unknown28.unknown00;
  events.unknown08 = this;
  unknown18[index]->unknown48 = events;
  unknown18[index]->setColiUserData(&unknown40);
  if (info.unknown80 != nullptr && info.unknown80->unknown00 == fw::unknown031::TYPE_UNKNOWN_5) {
    GfComModel *model = unknown08->getComponent<GfComModel>();
    if (model != nullptr) {
      unknown50.bind(model->unknown18, unknown18[index], getAllocator(ALLOCATOR_UNKNOWN_0));
      fw::AnimationManager *manager = fw::AnimationManager::get();
      if (manager != nullptr) {
        manager->addAfterModifier(getLayer(), unknown50);
      }
    }
  }
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
  fw::ColiUserData *userData = info.other->unknown58;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
    return;
  }

  unknown095 message;
  message.unknown08 = static_cast<GfObj *>(static_cast<UserData *>(userData)->unknown08->unknown08)->unknownf8;
  message.unknown10 = &info;
  GfObj *obj = static_cast<GfObj *>(unknown08);
  obj->sendMessage(obj, message);
}

void GfComCollider::leave(const LeaveInfo &info) {
  fw::ColiUserData *userData = info.other->unknown58;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
    return;
  }

  unknown096 message;
  message.unknown08 = static_cast<GfObj *>(static_cast<UserData *>(userData)->unknown08->unknown08)->unknownf8;
  message.unknown10 = &info;
  GfObj *obj = static_cast<GfObj *>(unknown08);
  obj->sendMessage(obj, message);
}

void GfComCollider::contact(const EnterInfo &info) {
  fw::ColiUserData *userData = info.other->unknown58;
  if (userData == nullptr || !userData->getRTTI()->isKindOf(&UserData::m_rtti)) {
    return;
  }

  unknown097 message;
  message.unknown08 = static_cast<GfObj *>(static_cast<UserData *>(userData)->unknown08->unknown08)->unknownf8;
  message.unknown10 = &info;
  GfObj *obj = static_cast<GfObj *>(unknown08);
  obj->sendMessage(obj, message);
}

const mm::mtl::RTTI *GfComCollider::getRTTI() const { return &m_rtti; }

void GfComCollider::changeLayer(u32 oldLayer, u32 newLayer) {}

const mm::mtl::RTTI *GfComCollider::UserData::getRTTI() const { return &m_rtti; }

} // namespace gf
