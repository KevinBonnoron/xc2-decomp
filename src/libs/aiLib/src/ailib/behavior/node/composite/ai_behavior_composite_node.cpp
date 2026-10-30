// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/aiLib/src/ailib/behavior/node/composite/ai_behavior_composite_node.cpp.
#include "mm_mtl/vector.h" // IWYU pragma: keep

namespace ai {
class BehaviorNode; // IWYU pragma: keep
} // namespace ai

template void mm::mtl::Vector<ai::BehaviorNode *>::expand(size_t, size_t);
template void mm::mtl::Vector<ai::BehaviorNode *>::extend(size_t, size_t, ai::BehaviorNode *const &);
template void mm::mtl::Vector<ai::BehaviorNode *>::resize(size_t, ai::BehaviorNode *const &);
