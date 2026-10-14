#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

class EffectManager : public mm::mtl::PtrSingleton<EffectManager> {
public:
  void remove(u32 handle);
  void dead(u32 handle);
  void setAlpha(u32 handle, f32 alpha);
  void setSpeed(u32 handle, f32 speed);
  bool isExist(u32 handle);
};

} // namespace fw
