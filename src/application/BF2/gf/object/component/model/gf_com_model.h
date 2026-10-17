#pragma once
#include <stddef.h>

#include "gf/object/component/gf_component.h"
#include "types.h"

namespace anm {
class ExtraTruckBuffer;
class Pose;
class Skeleton;
} // namespace anm
namespace fw {
class ModelObject;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComModel : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 1;

  bool isRender() const;
  void setModelScale(f32 scale);

  u8 _10[0x18 - 0x10];
  fw::ModelObject *modelObject;
  u8 _20[0x28 - 0x20];
  const anm::Skeleton *skeleton;
  anm::Pose *pose;
  anm::ExtraTruckBuffer *extraTruckBuffer;
};

static_assert(offsetof(GfComModel, modelObject) == 0x18, "");
static_assert(offsetof(GfComModel, skeleton) == 0x28, "");
static_assert(offsetof(GfComModel, pose) == 0x30, "");
static_assert(offsetof(GfComModel, extraTruckBuffer) == 0x38, "");

} // namespace gf
