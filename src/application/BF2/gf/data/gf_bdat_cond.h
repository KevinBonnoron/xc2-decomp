#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatCond : public mm::mtl::PtrSingleton<GfBdatCond> {
public:
  u32 getConditionListConditionType(u32 condition, u32 index) const;
  u32 getConditionListCondition(u32 condition, u32 index) const;
  u32 getConditionPTCategory(u32 condition) const;
  u32 getConditionPTPCID(u32 condition, u32 index) const;
};

} // namespace gf
