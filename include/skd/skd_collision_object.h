#pragma once
#include "anm/anm_reference_object.h"

namespace skd {

class CollisionObject : public anm::ReferenceObject {
public:
  void update();
};

} // namespace skd
