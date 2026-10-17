#pragma once
#include "ml/dev_base.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class FontLayer {
public:
  virtual ~FontLayer();

  u8 _08[0x10 - 0x08];
};

class DevFont : public FontLayer, public DevBase, public mm::mtl::PtrSingleton<DevFont> {
public:
  static bool isInitialized();
};

} // namespace ml
