#include "gf/object/component/gf_com_ik.h"

#include "anm/anm_pose.h"
#include "anm/anm_skeleton.h"
#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_blow_rotate_solver.h"
#include "framework/ik/ik_ground_interface.h"
#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_look_solver.h"
#include "framework/ik/ik_placement_ground_solver.h"
#include "framework/ik/ik_rotate_solver.h"
#include "framework/ik/ik_slope_ground_solver.h"
#include "framework/ik/ik_solver.h"
#include "framework/ik/ik_spherical_coordinates_solver.h"
#include "framework/ik/ik_spine_rotate_solver.h"
#include "framework/ik/ik_spine_solver.h"
#include "framework/ik/ik_trans_solver.h"
#include "framework/ik/ik_two_chara_ground_solver.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace fw {
class ReferenceFrame;
} // namespace fw

namespace gf {

u32 calcFootCnt(GfComModel *model) {
  if (model == nullptr || model->unknown30 == nullptr) {
    return 0;
  }
  const anm::Skeleton *skeleton = model->unknown30->unknown18;
  if (skeleton == nullptr) {
    return 0;
  }
  const anm::Skeleton::unknown004 *bone = skeleton->getBoneFromLabel(static_cast<anm::LabelType>(0), 2);
  if (bone != nullptr && bone->unknown00 != nullptr) {
    return 6;
  }
  bone = skeleton->getBoneFromLabel(static_cast<anm::LabelType>(0), 1);
  if (bone != nullptr && bone->unknown00 != nullptr) {
    return 4;
  }
  bone = skeleton->getBoneFromLabel(static_cast<anm::LabelType>(0), 0);
  u32 footCount = 0;
  if (bone != nullptr && bone->unknown00 != nullptr) {
    footCount = 2;
  }
  return footCount;
}

bool GfComIK::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_UNKNOWN_16777219) {
    procMsgActivateComponentDebugWindow(sender, static_cast<MsgDebugActivateComponentWindow &>(message));
    return true;
  }

  return false;
}

void GfComIK::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

GfComIK::GfComIK() : unknown48(nullptr), unknown50(0), unknown68(nullptr) {
  unknown10.unknown10.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  unknown58.unknown08 = this;
}

GfComIK::~GfComIK() {}

void GfComIK::setup(const SetupInfo &) {
  unknown10.unknown10.resize(9, mm::mtl::IntrusivePtr<fw::IkSolver>());
  unknown50 = calcFootCnt(unknown08->getComponent<GfComModel>());
  GfComProperty *property = unknown08->getComponent<GfComProperty>();
  if (property != nullptr && property->unknown28.get() != nullptr) {
    GfEnvProperty *env = property->unknown28.get();
// __LINE__ must be 267 as in the original file: it is an argument of the allocation.
#line 267
    unknown48.reset(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) Ground);
    unknown48->unknown001(env, unknown50);
  }
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    manager->addIkResolver(getLayer(), unknown10);
  }
}

void GfComIK::cleanup() {
  fw::AnimationManager *manager = fw::AnimationManager::get();
  if (manager != nullptr) {
    manager->removeIkResolver(getLayer(), unknown10);
  }
  unknown10.unknown10.clear();
  unknown48.reset();
}

fw::LookIkSolver *GfComIK::createLookIK(f32 fadeInTime, f32 fadeOutTime) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::LookIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    fw::LookIkSolver::Description description;
    description.unknown04 = fadeInTime;
    description.unknown00 = fadeOutTime;
    solver = fw::LookIkSolver::create(description, frame, *model->unknown30);
    unknown10.unknown10[unknown002_3] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::RotateIkSolver *GfComIK::createRotateBodyIK(const char *boneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::RotateIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::RotateIkSolver::create(boneName, frame, *model->unknown30);
    unknown10.unknown10[unknown002_0] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::SpineIkSolver *GfComIK::createSpineIK(const fw::ParamAdapter &param, const char *boneName, const char *endBoneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::SpineIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::SpineIkSolver::create(param, boneName, endBoneName, frame, *model->unknown30);
    unknown10.unknown10[unknown002_3] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::LookAtIkSolver *GfComIK::createLookAtIK(const fw::ParamAdapter &param, const char *boneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::LookAtIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::LookAtIkSolver::create(param, boneName, frame, *model->unknown30);
    unknown10.unknown10[unknown002_5] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::PlacementGroundSolver *GfComIK::createPlacementGroundIK(f32 value) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::PlacementGroundSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    fw::PlacementGroundSolver::Description description = {value, unknown50};
    solver = fw::PlacementGroundSolver::create(description, frame, *model->unknown30, unknown48.get());
    unknown10.unknown10[unknown002_2] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::TwoCharaGroundSolver *GfComIK::createTwoCharaGroundIK(f32 value, const char *boneName, const char *endBoneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::TwoCharaGroundSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    fw::TwoCharaGroundSolver::Description description = {value, unknown50, boneName, endBoneName};
    solver = fw::TwoCharaGroundSolver::create(description, frame, *model->unknown30, unknown48.get());
    unknown10.unknown10[unknown002_2] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::SlopeGroundSolver *GfComIK::createSlopeGroundIK(f32 first, f32 second) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::SlopeGroundSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    fw::SlopeGroundSolver::Description description;
    description.unknown1c = unknown50;
    description.unknown14 = first;
    description.unknown18 = second;
    solver = fw::SlopeGroundSolver::create(description, frame, *model->unknown30, unknown48.get());
    unknown10.unknown10[unknown002_0] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::SphericalCoordinatesIkSolver *GfComIK::createSphericalCoordinatesIkSolver(const fw::ParamAdapter &param, const char *boneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::SphericalCoordinatesIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::SphericalCoordinatesIkSolver::create(param, boneName, frame, *model->unknown30);
    unknown10.unknown10[unknown002_8] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::SpineRotateIKSolver *GfComIK::createSpineRotateIkSolver(const fw::ParamAdapter &param, const char *boneName, const char *endBoneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::SpineRotateIKSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::SpineRotateIKSolver::create(param, boneName, endBoneName, frame, *model->unknown30);
    unknown10.unknown10[unknown002_4] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::TransLocalIkSolver *GfComIK::createTransEyeIkSolver(u32 index, const char *boneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::TransLocalIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::TransLocalIkSolver::create(boneName, frame, *model->unknown30);
    unknown10.unknown10[index] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::RotateLocalIkSolver *GfComIK::createRotateEyeIkSolver(u32 index, const char *boneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::RotateLocalIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::RotateLocalIkSolver::create(boneName, frame, *model->unknown30);
    unknown10.unknown10[index] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
}

fw::BlowRotateIkSolver *GfComIK::createBlowRotateIkSolver(const char *boneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  anm::Pose *pose = model->unknown30;
  fw::BlowRotateIkSolver *solver = nullptr;
  if (pose != nullptr) {
    u16 boneIndex = 1;
    if (boneName != nullptr) {
      u16 id = pose->unknown18->getBoneID(boneName);
      if (id != anm::Skeleton::INVALID_BONE) {
        boneIndex = id;
      }
    }
    solver = fw::BlowRotateIkSolver::create(frame, *pose, boneIndex);
    unknown10.unknown10[unknown002_1] = solver;
    if (solver != nullptr) {
      solver->release();
    }
  }
  return solver;
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

fw::IKFootGroundInterface *GfComIK::Ground::getFootGround(fw::IKFootIndex index) { return &unknown10[index]; }

const mm::Plane *GfComIK::Ground::getPlane() const {
  const GfEnvProperty::unknown002 *ground = unknown002(GfEnvProperty::GROUND_INDEX_UNKNOWN_0);
  if (ground == nullptr) {
    return nullptr;
  }
  return &ground->unknown10;
}

const mm::Vec3 *GfComIK::Ground::getHitPos() const {
  const GfEnvProperty::unknown002 *ground = unknown002(GfEnvProperty::GROUND_INDEX_UNKNOWN_0);
  if (ground == nullptr) {
    return nullptr;
  }
  return &ground->unknown00;
}

const mm::Plane *GfComIK::Ground::getPlaneSub() const {
  const GfEnvProperty::unknown002 *ground = unknown002(GfEnvProperty::GROUND_INDEX_UNKNOWN_7);
  if (ground == nullptr) {
    return nullptr;
  }
  return &ground->unknown10;
}

const mm::Vec3 *GfComIK::Ground::getHitPosSub() const {
  const GfEnvProperty::unknown002 *ground = unknown002(GfEnvProperty::GROUND_INDEX_UNKNOWN_7);
  if (ground == nullptr) {
    return nullptr;
  }
  return &ground->unknown00;
}

const mm::Plane *GfComIK::FootGround::getPlane() const {
  const GfEnvProperty::unknown002 *ground = unknown001();
  if (ground == nullptr) {
    return nullptr;
  }
  return &ground->unknown10;
}

const mm::Vec3 *GfComIK::FootGround::getHitPos() const {
  const GfEnvProperty::unknown002 *ground = unknown001();
  if (ground == nullptr) {
    return nullptr;
  }
  return &ground->unknown00;
}

} // namespace gf
