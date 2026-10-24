#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerBase;
class LayerFontIconObj;
class LayerFontStyleObj;

class LayerFontManager {
public:
  LayerBase *createFontResObj(const void *data);
  LayerBase *createStyleObj(const void *data);
  LayerBase *createFontIconObj(const void *data);
  LayerBase *createFontColMapObj(const void *data);
  void update();

  u8 _00[0x68 - 0x00];
  LayerFontIconObj *unknown68;  // Inferred role: default icon object; original member name unknown.
  LayerFontStyleObj *unknown70; // Inferred role: default style object; original member name unknown.
};

static_assert(offsetof(LayerFontManager, unknown68) == 0x68, "");

} // namespace layer
