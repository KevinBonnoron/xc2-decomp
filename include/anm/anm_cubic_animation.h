#pragma once
#include "anm/anm_animation.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {
struct SerialiseArg;

class CubicAnimation : public Animation {
public:
  explicit CubicAnimation(mm::mtl::IAllocator *pAllocator);
  explicit CubicAnimation(const SerialiseArg &arg);
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  s32 getImplType() const override;
};

} // namespace anm
