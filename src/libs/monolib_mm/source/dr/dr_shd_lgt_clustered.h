#pragma once
#include "types.h"

namespace ml {

class DrShdLgtClustered {
public:
  void setPntLightUniformBlock(u32 viewIndex, u32 index);
  void setSptLightUniformBlock(u32 viewIndex, u32 index);
  void setPointerListUniformBlock(u32 viewIndex, u32 index);
  void setLightListUniformBlock(u32 viewIndex, u32 index);
  void setParamUniformBlock(u32 viewIndex, u32 index);
  void setPntLightStorageBuffer(u32 viewIndex, u32 index);
  void setSptLightStorageBuffer(u32 viewIndex, u32 index);
  void setPointerListStorageBuffer(u32 viewIndex, u32 index);
  void setLightListStorageBuffer(u32 viewIndex, u32 index);
  void setParamStorageBuffer(u32 viewIndex, u32 index);
};

} // namespace ml
