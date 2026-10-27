#include "gf/object/component/gf_com_ik.h"

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_ground_interface.h"
#include "framework/ik/ik_solver.h"
#include "framework/message/message_object.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"

namespace gf {

bool GfComIK::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_DEBUG_ACTIVATE_COMPONENT_WINDOW) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComIK::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComIK::GfComIK() : unknown48(nullptr), unknown50(0), unknown68(nullptr) {
  unknown10.unknown10.setAllocator(getAllocator(ALLOCATOR_DEFAULT));
  unknown58.unknown08 = this;
}

GfComIK::~GfComIK() {}

void GfComIK::cleanup() {
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    manager->removeIkResolver(getLayer(), unknown10);
  }
  unknown10.unknown10.clear();
  unknown48.reset();
}

void GfComIK::changeLayer(u32 oldLayer, u32 newLayer) {
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager == nullptr) {
    return;
  }
  manager->removeIkResolver(getLayer(), unknown10);
  manager->addIkResolver(newLayer, unknown10);
}

const mm::mtl::RTTI *GfComIK::getRTTI() const { return &m_rtti; }

} // namespace gf
