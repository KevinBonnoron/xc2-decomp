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

GfComTransform::GfComTransform() : unknown80(nullptr) { unknown88.unknown08 = this; }

GfComTransform::~GfComTransform() {}

void GfComTransform::setup(const SetupInfo &setup_info) {
  // __LINE__ must be 46 and 48 as in the original source: they are the line arguments of the assert and of operator new.
#line 46
  MM_ASSERT(setup_info.frame_max != 0);

  unknown10 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) fw::ReferenceFrame();
  fw::ReferenceFrame *referenceFrame = unknown10.get();
  referenceFrame->invalidateLocal();
  referenceFrame->worldTransform.position = setup_info.unknown00;
  referenceFrame->worldTransform.rotation = setup_info.unknown10;
  unknown10->syncLocalTransform();
  if (setup_info.unknown24) {
    // __LINE__ must be 62 as in the original source: it is the line argument of operator new.
#line 62
    unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) fw::ReferenceFrame();
    unknown10->addChild(*unknown18.get());
    unknown18->invalidateWorld();
    unknown18->syncWorldTransform();
  }

  unknown20.frames.setAllocator(getAllocator(ALLOCATOR_DEFAULT));
  unknown20.frames.reserve(setup_info.frame_max);
  unknown20.afterFrames.setAllocator(getAllocator(ALLOCATOR_DEFAULT));
  unknown20.afterFrames.reserve(setup_info.frame_max);
  unknown20.frames.push_back(unknown10.get());
  if (unknown18.get() != nullptr) {
    unknown20.frames.push_back(unknown18.get());
  }

  fw::TransformManager::get()->addUpdater(getLayer(), unknown20);
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
  fw::TransformManager::get()->removeUpdater(getLayer(), unknown20);
  if (unknown20.frames.capacity() != 0) {
    unknown20.frames.clear();
    unknown20.frames.destroy();
  }
  if (unknown20.afterFrames.capacity() != 0) {
    unknown20.afterFrames.clear();
    unknown20.afterFrames.destroy();
  }
}

void GfComTransform::addReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) { unknown20.frames.push_back(frame); }

void GfComTransform::removeReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> *found = mm::mtl::find(unknown20.frames.begin(), unknown20.frames.end(), frame);
  if (found != unknown20.frames.end()) {
    unknown20.frames.erase(found);
  }
}

void GfComTransform::addAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) { unknown20.afterFrames.push_back(frame); }

void GfComTransform::removeAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> *found = mm::mtl::find(unknown20.afterFrames.begin(), unknown20.afterFrames.end(), frame);
  if (found != unknown20.afterFrames.end()) {
    unknown20.afterFrames.erase(found);
  }
}

void GfComTransform::setPosition(const mm::Vec3 &position) {
  fw::ReferenceFrame *referenceFrame = unknown10.get();
  referenceFrame->invalidateLocal();
  referenceFrame->worldTransform.position = position;
}

const mm::Vec3 &GfComTransform::getPosition() const { return unknown10.get()->worldTransform.position; }

void GfComTransform::setRotation(const mm::Quat &rotation) {
  fw::ReferenceFrame *referenceFrame = unknown10.get();
  referenceFrame->invalidateLocal();
  referenceFrame->worldTransform.rotation = rotation;
}

const mm::Quat &GfComTransform::getRotation() const { return unknown10.get()->worldTransform.rotation; }

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
  fw::TransformManager::get()->removeUpdater(getLayer(), unknown20);
  fw::TransformManager::get()->addUpdater(newLayer, unknown20);
}

const mm::mtl::RTTI *GfComTransform::getRTTI() const { return &m_rtti; }

} // namespace gf
