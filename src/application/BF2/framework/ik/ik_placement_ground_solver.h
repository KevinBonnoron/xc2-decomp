#pragma once

#include "framework/ik/ik_solver.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {

class PlacementGroundSolver : public IkSolver {
public:
  static mm::mtl::RTTI m_rtti;

  void solve(const UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
};

} // namespace fw
