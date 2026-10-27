#include "framework/ik/ik_foot_placement_solver.h"

#include "anm/anm_foot_placement_ik_solver.h"
#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "framework/debug/debug_draw.h"
#include "fw/fw_param_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec4.h"

namespace fw {

FootPlacementIKSolver::~FootPlacementIKSolver() {
  if (unknown20 != nullptr) {
    unknown20->release();
    unknown20 = nullptr;
  }
}

f32 FootPlacementIKSolver::getRaycastDown() const {
  if (unknowna0 & 8) {
    return unknowna8;
  }

  anm::FootPlacementIKSolver *solver = unknown20;
  f32 height = unknown18->getBoneModelSpace(solver->unknown2c).unknown00.y;
  return __builtin_fmaxf(height - solver->unknown74, 0.0f) + 0.1f;
}

void FootPlacementIKSolver::drawDebug() {
  if (unknowna0 & 2) {
    mm::Vec3 position = unknown60;
    mm::Mat44 matrix;
    matrix.unknown007(position);
    debug::drawAxis(matrix, 1.0f);
  }
}

void buildDescFromParam(ParamAdapter &param, anm::FootPlacementIKSolver::Description *description) {
  const FootPlacementIKSolver::Param *data = param.get<FootPlacementIKSolver::Param>();
  if (data != nullptr) {
    description->unknown50 = data->unknown00;
    description->unknown4c = description->unknown54 + data->unknown04;
    description->unknown48 = description->unknown54 + data->unknown08;
  }
}

const mm::mtl::RTTI *FootPlacementIKSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
