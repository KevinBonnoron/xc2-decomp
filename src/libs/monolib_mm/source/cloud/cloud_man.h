#pragma once
#include "types.h"

namespace ml {
class IDrDrawWorkInfo;
} // namespace ml

namespace cloud {

class CloudMan {
public:
  void setCldNum(u32 cldNum);
  u32 getCldNum() const;
  void alphaRender(const ml::IDrDrawWorkInfo *workInfo);
};

} // namespace cloud
