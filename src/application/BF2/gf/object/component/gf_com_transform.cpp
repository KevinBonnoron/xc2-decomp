#include "gf/object/component/gf_com_transform.h"

#include "framework/message/message_object.h"
#include "fw/fw_transform.h"
#include "gf/gf_allocator.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/vector.h"

namespace gf {

bool GfComTransform::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_UNKNOWN_16777219) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComTransform::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComTransform::GfComTransform() : unknown80(nullptr) { m_listener.m_comTransform = this; }

GfComTransform::~GfComTransform() {}

void GfComTransform::setup(const SetupInfo &setup_info) {
  // __LINE__ must be 46 and 48 as in the original source: they are the line arguments of the assert and of operator new.
#line 46
  MM_ASSERT(setup_info.frame_max != 0);

  unknown10 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) fw::ReferenceFrame();
  fw::ReferenceFrame *referenceFrame = unknown10.get();
  referenceFrame->invalidateLocal();
  referenceFrame->unknown40.unknown00 = setup_info.unknown00;
  referenceFrame->unknown40.unknown10 = setup_info.unknown10;
  unknown10->syncLocalTransform();
  if (setup_info.unknown24) {
    // __LINE__ must be 62 as in the original source: it is the line argument of operator new.
#line 62
    unknown18 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) fw::ReferenceFrame();
    unknown10->addChild(*unknown18.get());
    unknown18->invalidateWorld();
    unknown18->syncWorldTransform();
  }

  m_transformUpdater.unknown10.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  m_transformUpdater.unknown10.reserve(setup_info.frame_max);
  m_transformUpdater.unknown38.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  m_transformUpdater.unknown38.reserve(setup_info.frame_max);
  m_transformUpdater.unknown10.push_back(unknown10.get());
  if (unknown18.get() != nullptr) {
    m_transformUpdater.unknown10.push_back(unknown18.get());
  }

  fw::TransformManager::get()->addUpdater(getLayer(), m_transformUpdater);
}

void GfComTransform::cleanup() {
  fw::ReferenceFrame *referenceFrame = unknown18.get();
  if (referenceFrame != nullptr) {
    fw::ReferenceFrame::unlinkParent(*referenceFrame);
    fw::ReferenceFrame::unlinkChild(*referenceFrame);
  }

  referenceFrame = unknown10.get();
  fw::ReferenceFrame::unlinkParent(*referenceFrame);
  fw::ReferenceFrame::unlinkChild(*referenceFrame);
  fw::TransformManager::get()->removeUpdater(getLayer(), m_transformUpdater);
  if (m_transformUpdater.unknown10.capacity() != 0) {
    m_transformUpdater.unknown10.clear();
    m_transformUpdater.unknown10.destroy();
  }
  if (m_transformUpdater.unknown38.capacity() != 0) {
    m_transformUpdater.unknown38.clear();
    m_transformUpdater.unknown38.destroy();
  }
}

void GfComTransform::addReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) { m_transformUpdater.unknown10.push_back(frame); }

void GfComTransform::removeReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> *found = mm::mtl::find(m_transformUpdater.unknown10.begin(), m_transformUpdater.unknown10.end(), frame);
  if (found != m_transformUpdater.unknown10.end()) {
    m_transformUpdater.unknown10.erase(found);
  }
}

void GfComTransform::addAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) { m_transformUpdater.unknown38.push_back(frame); }

void GfComTransform::removeAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> *found = mm::mtl::find(m_transformUpdater.unknown38.begin(), m_transformUpdater.unknown38.end(), frame);
  if (found != m_transformUpdater.unknown38.end()) {
    m_transformUpdater.unknown38.erase(found);
  }
}

void GfComTransform::setPosition(const mm::Vec3 &position) {
  fw::ReferenceFrame *referenceFrame = unknown10.get();
  referenceFrame->invalidateLocal();
  referenceFrame->unknown40.unknown00 = position;
}

const mm::Vec3 &GfComTransform::getPosition() const { return unknown10.get()->unknown40.unknown00; }

void GfComTransform::setRotation(const mm::Quat &rotation) {
  fw::ReferenceFrame *referenceFrame = unknown10.get();
  referenceFrame->invalidateLocal();
  referenceFrame->unknown40.unknown10 = rotation;
}

const mm::Quat &GfComTransform::getRotation() const { return unknown10.get()->unknown40.unknown10; }

void GfComTransform::syncFrame() {
  if (unknown10.get() != nullptr) {
    unknown10.get()->syncLocalTransform();
  }

  fw::ReferenceFrame *referenceFrame = unknown18.get();
  if (referenceFrame != nullptr) {
    referenceFrame->invalidateWorld();
    unknown18->syncWorldTransform();
  }
}

void GfComTransform::openDebugWindow(ml::WinProc *window) {}

void GfComTransform::changeLayer(u32 oldLayer, u32 newLayer) {
  fw::TransformManager::get()->removeUpdater(getLayer(), m_transformUpdater);
  fw::TransformManager::get()->addUpdater(newLayer, m_transformUpdater);
}

const mm::mtl::RTTI *GfComTransform::getRTTI() const { return &m_rtti; }

} // namespace gf
