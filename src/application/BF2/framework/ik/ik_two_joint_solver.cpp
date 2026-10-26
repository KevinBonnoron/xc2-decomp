#include "framework/ik/ik_two_joint_solver.h"

namespace fw {

TwoJointIkSolver::~TwoJointIkSolver() {}

const mm::mtl::RTTI *TwoJointIkSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
