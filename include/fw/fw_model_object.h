#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class ScnObjModel;
}

namespace fw {

class ModelObject {
public:
  ml::ScnObjModel *getInterface();
  void setActive(bool isActive);
  bool isActive() const;
  void setAddOffsetPos(const mm::Vec3 &offset);

  u8 _00[0x30 - 0x00];
  ml::ScnObjModel *model;
  u8 _38[0x3c - 0x38];
  bool active;
  u8 _3d[0x50 - 0x3d];
  mm::Vec3 addOffsetPos;
};

static_assert(offsetof(ModelObject, model) == 0x30, "");
static_assert(offsetof(ModelObject, active) == 0x3c, "");
static_assert(offsetof(ModelObject, addOffsetPos) == 0x50, "");

} // namespace fw
