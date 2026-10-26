#pragma once
#include "ml/dev_base.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {
enum FONT_STYLE : int;

class FontLayer {
public:
  virtual ~FontLayer();
  void fontStyle(FONT_STYLE style);
  void fontZ(u32 z);

  u8 _08[0x10 - 0x08];
};

class DevFont : public FontLayer, public DevBase, public mm::mtl::PtrSingleton<DevFont> {
public:
  static bool isInitialized();
  static void fontLayerStyle(const FontLayer *layer, FONT_STYLE style);
  static void fontLayerZ(const FontLayer *layer, u32 z);
};

} // namespace ml
