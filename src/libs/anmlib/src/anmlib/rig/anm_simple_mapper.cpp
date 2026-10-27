#include "anm/anm_simple_mapper.h"

#include "anm/anm_skeleton.h"

namespace anm {

SimpleMapper::~SimpleMapper() {
  unknown001(m_pSkeletonA);
  unknown001(m_pSkeletonB);
}

} // namespace anm
