#include "framework/ik/ik_foot_placement_solver.h"

#include "anm/anm_foot_placement_ik_solver.h"
#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "framework/debug/debug_draw.h"
#include "framework/ik/ik_raycaster.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_param_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_vector.h" // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace fw {

void FootPlacementIKSolver::Param::createReflection(Reflection *reflection, const char *name, u32 index) {
#line 26
  ReflectionValueStruct *value = new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueStruct(name, sizeof(Param));
#line 27
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("maxAnkleHeight", offsetof(Param, unknown00), 0.0f, 90.0f, 0.7f));
#line 28
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("raisedAnkleOffset", offsetof(Param, unknown04), 0.0f, 90.0f, 0.3f));
#line 29
  value->add(new (Allocator::getDebAllocator(), 16, __FILE__, __LINE__) ReflectionValueF32("plantedAnkleOffset", offsetof(Param, unknown08), 0.0f, 90.0f, 0.1f));
  reflection->setReflectionStruct(index, value);
}

FootPlacementIKSolver::FootPlacementIKSolver()
    : unknown20(nullptr), unknown58(0xffff), unknown60(mm::Vec3::zero), unknownb0(mm::Quat::identity), unknownc0(mm::Quat::identity), m_iKFootGroundInterface(nullptr) {}

FootPlacementIKSolver *FootPlacementIKSolver::create(const Description &description, mm::mtl::IntrusivePtr<ReferenceFrame> &frame, anm::Pose &pose, IKFootGroundInterface *ground) {
#line 66
  FootPlacementIKSolver *solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) FootPlacementIKSolver();
  solver->addRef();
  if (!solver->createImpl(description, frame, pose, ground)) {
    mm::mtl::safeRelease(solver);
    return nullptr;
  }
  return solver;
}

FootPlacementIKSolver::~FootPlacementIKSolver() {
  if (unknown20 != nullptr) {
    unknown20->release();
    unknown20 = nullptr;
  }
}

void FootPlacementIKSolver::solve(const UpdateInfo &info) {
  IKFootGroundInterface *ground = m_iKFootGroundInterface;
  if (ground != nullptr) {
    ground->m_planeRayCaster.bind(*ground);
    solveImpl(ground->m_planeRayCaster);
  } else {
    static Raycaster defaultRaycaster;
    solveImpl(defaultRaycaster);
  }
}

f32 FootPlacementIKSolver::getRaycastUp() const {
  if (unknowna0.test(FLAG_UNKNOWN_2)) {
    return unknowna4;
  }

  anm::FootPlacementIKSolver *solver = unknown20;
  const anm::QsTransform &ankle = unknown18->getBoneModelSpace(solver->m_desc.ankleBone);
  return __builtin_fmaxf(solver->m_desc.maxAnkleHeightMS - ankle.unknown00.y, 0.0f);
}

f32 FootPlacementIKSolver::getRaycastDown() const {
  if (unknowna0.test(FLAG_UNKNOWN_3)) {
    return unknowna8;
  }

  anm::FootPlacementIKSolver *solver = unknown20;
  const anm::QsTransform &ankle = unknown18->getBoneModelSpace(solver->m_desc.ankleBone);
  return __builtin_fmaxf(ankle.unknown00.y - solver->m_desc.minAnkleHeightMS, 0.0f) + 0.1f;
}

void FootPlacementIKSolver::setGroundAngle(const mm::Vec3 &angle) { unknownb0 = mm::unknown005(angle); }

void FootPlacementIKSolver::drawDebug() {
  if (unknowna0.test(FLAG_UNKNOWN_1)) {
    mm::Vec3 position = unknown60;
    mm::Mat44 matrix;
    matrix.unknown007(position);
    debug::drawAxis(matrix, 1.0f);
  }
}

void buildDescFromParam(ParamAdapter &param, anm::FootPlacementIKSolver::Description *description) {
  const FootPlacementIKSolver::Param *data = param.get<FootPlacementIKSolver::Param>();
  if (data != nullptr) {
    description->maxAnkleHeightMS = data->unknown00;
    description->raisedAnkleHeightMS = description->minAnkleHeightMS + data->unknown04;
    description->plantedAnkleHeightMS = description->minAnkleHeightMS + data->unknown08;
  }
}

const mm::mtl::RTTI *FootPlacementIKSolver::getRTTI() const { return &m_rtti; }

} // namespace fw

template void mm::mtl::FixedVector<mm::mtl::IntrusivePtr<fw::FootPlacementIKSolver>, 6>::resize(size_t, const mm::mtl::IntrusivePtr<fw::FootPlacementIKSolver> &);
