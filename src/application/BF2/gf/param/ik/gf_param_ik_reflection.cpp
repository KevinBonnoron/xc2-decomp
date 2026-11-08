// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/ik/gf_param_ik_reflection.cpp.
#include "gf/param/ik/gf_param_ik_reflection.h"

#include "framework/ik/ik_foot_placement_solver.h"
#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_spherical_coordinates_solver.h"
#include "framework/ik/ik_spine_rotate_solver.h"
#include "framework/ik/ik_spine_solver.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "mm_mtl/vector.h"

namespace gf {

fw::Reflection *createLookAtIKReflection() {
#line 29
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(3, nullptr);
  fw::LookAtIkSolver::BoxLimit::createReflection(reflection, "look_at_human_00", 0);
  fw::LookAtIkSolver::BoxLimit::createReflection(reflection, "look_at_nopon_00", 1);
  fw::LookAtIkSolver::BoxLimit::createReflection(reflection, "look_at_dog_00", 2);
  return reflection;
}

fw::Reflection *createSpineIKReflection() {
#line 46
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(3, nullptr);
  fw::SpineIkSolver::Param::createReflection(reflection, "spine_human_00", 0);
  fw::SpineIkSolver::Param::createReflection(reflection, "spine_nopon_00", 1);
  fw::SpineIkSolver::Param::createReflection(reflection, "spine_dog_00", 2);
  return reflection;
}

fw::Reflection *createSPCIKReflection() {
#line 63
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  fw::SphericalCoordinatesIkSolver::AngleLimit::createReflection(reflection, "limit_00", 0);
  return reflection;
}

fw::Reflection *createSpineRotateIKReflection() {
#line 79
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(1, nullptr);
  fw::SpineRotateIKSolver::Param::createReflection(reflection, "spine_human_00", 0);
  return reflection;
}

fw::Reflection *createFootIKReflection() {
#line 95
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(2, nullptr);
  fw::FootPlacementIKSolver::Param::createReflection(reflection, "foot_default", 0);
  fw::FootPlacementIKSolver::Param::createReflection(reflection, "foot_big_enemy", 1);
  return reflection;
}

} // namespace gf
