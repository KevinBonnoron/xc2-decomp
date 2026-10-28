#include "gf/object/component/gf_com_ik.h"

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_ground_interface.h"
#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_rotate_solver.h"
#include "framework/ik/ik_solver.h"
#include "framework/ik/ik_spherical_coordinates_solver.h"
#include "framework/ik/ik_spine_rotate_solver.h"
#include "framework/ik/ik_spine_solver.h"
#include "framework/ik/ik_trans_solver.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace fw {
class ReferenceFrame;
} // namespace fw

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

fw::RotateIkSolver *GfComIK::createRotateBodyIK(const char *boneName) {
  GfComTransform *transform = unknown08->getComponent<GfComTransform>();
  GfComModel *model = mm::mtl::dynamicCast<GfComModel>(unknown08->unknown38[GfComModel::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame = transform->unknown001();
  fw::RotateIkSolver *solver = nullptr;
  if (model->unknown30 != nullptr) {
    solver = fw::RotateIkSolver::create(boneName, frame, *model->unknown30);
    unknown10.unknown10[IK_SOLVER_INDEX_UNKNOWN_0] = solver;
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
    unknown10.unknown10[IK_SOLVER_INDEX_UNKNOWN_3] = solver;
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
    unknown10.unknown10[IK_SOLVER_INDEX_UNKNOWN_5] = solver;
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
    unknown10.unknown10[IK_SOLVER_INDEX_UNKNOWN_8] = solver;
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
    unknown10.unknown10[IK_SOLVER_INDEX_UNKNOWN_4] = solver;
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
