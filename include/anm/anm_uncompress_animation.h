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

class UncompressAnimation : public Animation {
public:
  explicit UncompressAnimation(mm::mtl::IAllocator *pAllocator);
  explicit UncompressAnimation(const SerialiseArg &arg);
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  s32 getImplType() const override;
};

} // namespace anm
