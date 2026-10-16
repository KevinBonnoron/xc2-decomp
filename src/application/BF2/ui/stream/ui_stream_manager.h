#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {

class UIStreamManager : public mm::mtl::PtrSingleton<UIStreamManager> {
public:
  void start(u32 streamId, u32 handle, u32 index);
  u32 getContentsNum(u32 streamId);
};

} // namespace ui
