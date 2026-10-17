#include "gf/object/component/gf_com_transform.h"

#include "framework/message/message_object.h"
#include "fw/fw_transform.h"
#include "gf/gf_allocator.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/vector.h"

namespace gf {

bool GfComTransform::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.id == MSG_DEBUG_ACTIVATE_COMPONENT_WINDOW) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComTransform::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComTransform::GfComTransform() : viewer(nullptr) { listener.owner = this; }

GfComTransform::~GfComTransform() {}

void GfComTransform::setup(const SetupInfo &setup_info) {
  // __LINE__ must be 46 and 48 as in the original source: they are the line arguments of the assert and of operator new.
#line 46
  MM_ASSERT(setup_info.frame_max != 0);

  frame = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) fw::ReferenceFrame();
  fw::ReferenceFrame *referenceFrame = frame.get();
  referenceFrame->invalidateLocal();
  referenceFrame->worldTransform.position = setup_info.position;
  referenceFrame->worldTransform.rotation = setup_info.rotation;
  frame->syncLocalTransform();
  if (setup_info.isUseChildFrame) {
    // __LINE__ must be 62 as in the original source: it is the line argument of operator new.
#line 62
    childFrame = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) fw::ReferenceFrame();
    frame->addChild(*childFrame.get());
    childFrame->invalidateWorld();
    childFrame->syncWorldTransform();
  }

  updater.frames.setAllocator(getAllocator(ALLOCATOR_DEFAULT));
  updater.frames.reserve(setup_info.frame_max);
  updater.afterFrames.setAllocator(getAllocator(ALLOCATOR_DEFAULT));
  updater.afterFrames.reserve(setup_info.frame_max);
  updater.frames.push_back(frame.get());
  if (childFrame.get() != nullptr) {
    updater.frames.push_back(childFrame.get());
  }

  fw::TransformManager::get()->addUpdater(getLayer(), updater);
}

void GfComTransform::cleanup() {
  fw::ReferenceFrame *referenceFrame = childFrame.get();
  if (referenceFrame != nullptr) {
    fw::ReferenceFrame::unlinkParent(*referenceFrame);
    fw::ReferenceFrame::unlinkChild(*referenceFrame);
  }

  referenceFrame = frame.get();
  fw::ReferenceFrame::unlinkParent(*referenceFrame);
  fw::ReferenceFrame::unlinkChild(*referenceFrame);
  fw::TransformManager::get()->removeUpdater(getLayer(), updater);
  if (updater.frames.capacity() != 0) {
    updater.frames.clear();
    updater.frames.destroy();
  }
  if (updater.afterFrames.capacity() != 0) {
    updater.afterFrames.clear();
    updater.afterFrames.destroy();
  }
}

void GfComTransform::addReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) { updater.frames.push_back(frame); }

void GfComTransform::removeReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> *found = mm::mtl::find(updater.frames.begin(), updater.frames.end(), frame);
  if (found != updater.frames.end()) {
    updater.frames.erase(found);
  }
}

void GfComTransform::addAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) { updater.afterFrames.push_back(frame); }

void GfComTransform::removeAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> *found = mm::mtl::find(updater.afterFrames.begin(), updater.afterFrames.end(), frame);
  if (found != updater.afterFrames.end()) {
    updater.afterFrames.erase(found);
  }
}

void GfComTransform::setPosition(const mm::Vec3 &position) {
  fw::ReferenceFrame *referenceFrame = frame.get();
  referenceFrame->invalidateLocal();
  referenceFrame->worldTransform.position = position;
}

const mm::Vec3 &GfComTransform::getPosition() const { return frame.get()->worldTransform.position; }

void GfComTransform::setRotation(const mm::Quat &rotation) {
  fw::ReferenceFrame *referenceFrame = frame.get();
  referenceFrame->invalidateLocal();
  referenceFrame->worldTransform.rotation = rotation;
}

const mm::Quat &GfComTransform::getRotation() const { return frame.get()->worldTransform.rotation; }

void GfComTransform::syncFrame() {
  if (frame.get() != nullptr) {
    frame.get()->syncLocalTransform();
  }

  fw::ReferenceFrame *referenceFrame = childFrame.get();
  if (referenceFrame != nullptr) {
    referenceFrame->invalidateWorld();
    childFrame->syncWorldTransform();
  }
}

void GfComTransform::openDebugWindow(ml::WinProc *window) {}

void GfComTransform::changeLayer(u32 oldLayer, u32 newLayer) {
  fw::TransformManager::get()->removeUpdater(getLayer(), updater);
  fw::TransformManager::get()->addUpdater(newLayer, updater);
}

const mm::mtl::RTTI *GfComTransform::getRTTI() const { return &m_rtti; }

} // namespace gf
