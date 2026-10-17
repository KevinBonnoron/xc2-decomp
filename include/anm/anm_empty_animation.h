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

class EmptyAnimation : public Animation {
public:
  explicit EmptyAnimation(mm::mtl::IAllocator *pAllocator);
  explicit EmptyAnimation(const SerialiseArg &arg);
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  s32 getImplType() const override;
};

} // namespace anm
