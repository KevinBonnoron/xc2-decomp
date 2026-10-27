#include "framework/ik/ik_placement_ground_solver.h"

#include "framework/ik/ik_foot_placement_solver.h"

namespace fw {

PlacementGroundSolver::PlacementGroundSolver() : unknown58(0.3f), unknown5c(2), unknown60(0), unknown64(false), unknown65(false), unknown68(nullptr) {}

PlacementGroundSolver::~PlacementGroundSolver() {}

void PlacementGroundSolver::setEnablePlacement(bool enable) {
  unknown64 = enable;
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown003(enable);
    }
  }
}

void PlacementGroundSolver::overwriteRaycastUp(f32 distance) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown001(distance);
    }
  }
}

void PlacementGroundSolver::resetRaycastUp() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknowna0 &= ~4;
    }
  }
}

void PlacementGroundSolver::overwriteRaycastDown(f32 distance) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknown002(distance);
    }
  }
}

void PlacementGroundSolver::resetRaycastDown() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    if (unknown20[i].get() != nullptr) {
      unknown20[i]->unknowna0 &= ~8;
    }
  }
}

const mm::mtl::RTTI *PlacementGroundSolver::getRTTI() const { return &m_rtti; }

} // namespace fw
