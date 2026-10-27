#pragma once
#include "types.h"

namespace ptlib {

struct DrDrawWorkInfoEF;

namespace renderer {

class RenderSet;

class StreamObj {
public:
  void release();
  void lockStream(const DrDrawWorkInfoEF *info);
  void unlockStream(const DrDrawWorkInfoEF *info, u32 count);
  void renderStreamNum(RenderSet &renderSet, const DrDrawWorkInfoEF *info);
};

} // namespace renderer
} // namespace ptlib
