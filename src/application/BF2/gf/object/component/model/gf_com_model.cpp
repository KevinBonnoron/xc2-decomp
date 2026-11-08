#include "gf/object/component/model/gf_com_model.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_model_object.h"
#include "fw/fw_transform.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/algorithm.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

GfComModel::GfComModel() : unknown10(-1), unknown18(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), m_modelScale(1.0f), unknown11a8(nullptr) { unknown1198.unknown08 = this; }

GfComModel::~GfComModel() { ; }

bool GfComModel::hasBone(const char *name) const {
  if (name != nullptr) {
    return unknown28->getBoneID(name) != anm::Skeleton::INVALID_BONE;
  }

  return false;
}

bool GfComModel::isRender() const {
  if (unknown18 != nullptr) {
    return unknown18->isRender();
  }

  return false;
}

bool GfComModel::isVolumeFadeForUser() const { return GfObjUtil::isVolumeFadeForUser(static_cast<GfObj *>(unknown08)->unknownf8); }

void GfComModel::procMsgObjectNotifyDead(fw::MessageObject *, MsgObjectNotifyDead &) {}

void GfComModel::procMsgObjectNotifyDamage(fw::MessageObject *, MsgObjectNotifyDamage &) {}

void GfComModel::procMsgActivateComponentDebugWindow(fw::MessageObject *, MsgDebugActivateComponentWindow &) {}

void GfComModel::setModelScale(f32 scale) {
  m_modelScale = scale;
  if (unknown18 != nullptr) {
    unknown18->setScale(scale);
  }
}

mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::createBoneReferenceFrame(const char *name) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame;
  if (unknown28 != nullptr) {
    u16 bone = anm::Skeleton::INVALID_BONE;
    if (name != nullptr) {
      bone = unknown28->getBoneID(name);
    }
    if (bone != anm::Skeleton::INVALID_BONE) {
      BoneFrameInfo *info = findBoneFrameInfo(bone);
      if (info != unknown1140.end()) {
        info->unknown0c++;
        frame = info->unknown00;
        return frame;
      }

      frame = createBoneReferenceFrameImpl(bone);
      unknown001(unknown1140, frame, bone);
      return frame;
    }

    const anm::Skeleton *skeleton = unknown28;
    u16 mount = skeleton->unknown005(name);
    if (mount != anm::Skeleton::INVALID_BONE) {
      u16 parentBone = skeleton->unknown60[mount];
      mm::mtl::IntrusivePtr<fw::ReferenceFrame> parent;
      if (parentBone != anm::Skeleton::INVALID_BONE) {
        BoneFrameInfo *parentInfo = findBoneFrameInfo(parentBone);
        if (parentInfo == unknown1140.end()) {
          parent = createBoneReferenceFrameImpl(parentBone);
          unknown001(unknown1140, parent, parentBone);
        } else {
          parentInfo->unknown0c++;
          parent = parentInfo->unknown00;
        }
      }

      BoneFrameInfo *info = findMountFrameInfo(mount);
      if (info == unknown1168.end()) {
        frame = createMountReferenceFrameImpl(mount);
        unknown001(unknown1168, frame, mount);
      } else {
        info->unknown0c++;
        frame = info->unknown00;
      }

      if (parent.get() != nullptr) {
        parent->addChild(*frame);
      }
    }
  }

  return frame;
}

GfComModel::BoneFrameInfo *GfComModel::findBoneFrameInfo(u16 bone) {
  return mm::mtl::find_if(unknown1140.begin(), unknown1140.end(), [bone](const BoneFrameInfo &info) { return info.unknown08 == bone; });
}

GfComModel::BoneFrameInfo *GfComModel::findMountFrameInfo(u16 mount) {
  return mm::mtl::find_if(unknown1168.begin(), unknown1168.end(), [mount](const BoneFrameInfo &info) { return info.unknown08 == mount; });
}

mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::getBoneReferenceFrame(const char *name) {
  if (unknown28 == nullptr) {
    return mm::mtl::IntrusivePtr<fw::ReferenceFrame>();
  }

  u16 bone = anm::Skeleton::INVALID_BONE;
  if (name != nullptr) {
    bone = unknown28->getBoneID(name);
  }
  if (bone != anm::Skeleton::INVALID_BONE) {
    BoneFrameInfo *info = findBoneFrameInfo(bone);
    if (info != unknown1140.end()) {
      return info->unknown00;
    }
  } else {
    u16 mount = unknown28->unknown005(name);
    if (mount != anm::Skeleton::INVALID_BONE) {
      BoneFrameInfo *info = findMountFrameInfo(mount);
      if (info != unknown1168.end()) {
        return info->unknown00;
      }
    }
  }

  return mm::mtl::IntrusivePtr<fw::ReferenceFrame>();
}

bool GfComModel::addBoneReferenceFrame(const char *name, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> boneFrame = createBoneReferenceFrame(name);
  if (boneFrame.get() != nullptr) {
    boneFrame->addChild(*frame.get());
    return true;
  }

  return false;
}

void GfComModel::removeBoneReferenceFrame(const char *name, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> boneFrame = getBoneReferenceFrame(name);
  if (boneFrame.get() != nullptr) {
    boneFrame->removeChild(*frame);
    destroyBoneReferenceFrame(name);
  }
}

// __LINE__ must be 544 and 549 as in the original source: they are the line arguments of operator new and of the assert.
mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::createBoneReferenceFrameImpl(u16 bone) {
#line 544
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) fw::ReferenceFrame();
  bindReferenceFrameToBone(bone, frame);
  GfComTransform *com_trans = unknown08->getComponent<GfComTransform>();
#line 549
  MM_ASSERT(com_trans != NULL);
  com_trans->addReferenceFrame(frame);
  return frame;
}

// __LINE__ must be 564 as in the original source: it is the line argument of the assert.
void GfComModel::destroyBoneReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
  GfComTransform *com_trans = unknown08->getComponent<GfComTransform>();
#line 564
  MM_ASSERT(com_trans != NULL);
  com_trans->removeReferenceFrame(frame);
  unbindReferenceFrameToBone(frame);
}

// __LINE__ must be 580 and 583 as in the original source: they are the line arguments of operator new and of the assert.
mm::mtl::IntrusivePtr<fw::ReferenceFrame> GfComModel::createMountReferenceFrameImpl(u16 mount) {
#line 580
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) fw::ReferenceFrame();
  GfComTransform *com_trans = unknown08->getComponent<GfComTransform>();
#line 583
  MM_ASSERT(com_trans != NULL);
  com_trans->addAfterReferenceFrame(frame);
  const anm::Skeleton *skeleton = unknown28;
  if (skeleton != nullptr) {
    fw::Transform &local = frame->unknown002();
    const anm::QsTransform &transform = skeleton->unknown80[mount];
    local.unknown00 = mm::Vec3(transform.unknown00.x, transform.unknown00.y, transform.unknown00.z);
    local.unknown10 = transform.unknown10;
  }
  return frame;
}

// __LINE__ must be 604 as in the original source: it is the line argument of the assert.
void GfComModel::destroyMountReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame) {
  GfComTransform *com_trans = unknown08->getComponent<GfComTransform>();
#line 604
  MM_ASSERT(com_trans != NULL);
  com_trans->removeAfterReferenceFrame(frame);
}

// __LINE__ must be 618 as in the original source: it is the line argument of the assert.
void GfComModel::bindReferenceFrameToBone(u16 bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  unknown40.bindReferenceFrameToBone(bone, frame);
  GfComTransform *com_trans = unknown08->getComponent<GfComTransform>();
#line 618
  MM_ASSERT(com_trans != NULL);
  com_trans->unknown001().get()->addChild(*frame.get());
}

void GfComModel::unbindReferenceFrameToBone(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame) {
  unknown40.unbindReferenceFrame(frame);
  GfComTransform *com_trans = unknown08->getComponent<GfComTransform>();
  if (com_trans != nullptr) {
    com_trans->unknown001().get()->removeChild(*frame.get());
  }
}

} // namespace gf

template void mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::destroy();
template void mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::push_back(const gf::GfComModel::BoneFrameInfo &);
template gf::GfComModel::BoneFrameInfo *mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::erase(gf::GfComModel::BoneFrameInfo *);
template void mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::expand(size_t, size_t);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfComModel>(const mm::mtl::Delegate<bool()> *);
