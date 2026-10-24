#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ml {
class ScnObjModel;
}

namespace fw {

class ModelObject : public mm::mtl::ReferenceObject {
public:
  virtual ~ModelObject();
  virtual void update();
  ml::ScnObjModel *getInterface();
  void setActive(bool isActive);
  bool isActive() const;
  void setAddOffsetPos(const mm::Vec3 &offset);

  u8 _10[0x30 - 0x10];
  ml::ScnObjModel *m_interface;
  u8 _38[0x3c - 0x38];
  bool m_active;
  u8 _3d[0x50 - 0x3d];
  mm::Vec3 unknown50; // Inferred role: add offset pos; original member name unknown.
};

static_assert(offsetof(ModelObject, m_interface) == 0x30, "");
static_assert(offsetof(ModelObject, m_active) == 0x3c, "");
static_assert(offsetof(ModelObject, unknown50) == 0x50, "");

} // namespace fw
