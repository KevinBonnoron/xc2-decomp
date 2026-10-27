#include "ml/dev_font_layer.h"

namespace ml {

u32 DevFontLayer::getMem1Size() { return 0x10000; }

void DevFontLayer::clear() {
  unknown1cc = mm::Col4(0.0f, 0.0f, 0.0f, 0.0f);
  unknown1dc = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
  unknown1b0 = 0;
}

void DevFontLayer::flushColor(const LAYER_COLOR *color) { unknown1dc = color->unknown04; }

void DevFontLayer::fontSetMaxQue(u32 maxQue) { unknown1f0 = maxQue; }

} // namespace ml
