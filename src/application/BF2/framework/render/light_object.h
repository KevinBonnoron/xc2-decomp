#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ml {
class DrEnvironmentObj;
} // namespace ml

namespace fw {

class LightObject : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<LightObject> {
public:
  LightObject();
  ~LightObject() override;
  void setup();
  void update();
  ml::DrEnvironmentObj *getInterface();

  ml::DrEnvironmentObj *unknown20; // Inferred role: light interface; original member name unknown.
  u32 unknown28;                   // Inferred role: layer; original member name unknown.
};

static_assert(offsetof(LightObject, unknown20) == 0x20, "");
static_assert(offsetof(LightObject, unknown28) == 0x28, "");
static_assert(sizeof(LightObject) == 0x30, "");

} // namespace fw
