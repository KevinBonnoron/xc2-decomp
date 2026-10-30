#include "ml/dev_font.h"

#include "ml/dev_font_layer.h"
#include "ml/work_util.h"

namespace ml {
enum FONT_STYLE : int;

DevFontLayer *DevFont::createLayer(const FontLayer *layer) {
  DevFont *font = get();
  if (font == nullptr) {
    return nullptr;
  }
  DevFontLayer *fontLayer = WorkUtil::createWork<DevFontLayer>("DevFontLayer", font, false);
  fontLayer->unknown1c0 = layer;
  return fontLayer;
}

void FontLayer::fontStyle(FONT_STYLE style) { DevFont::fontLayerStyle(this, style); }

void FontLayer::fontZ(u32 z) { DevFont::fontLayerZ(this, z); }

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFont>::~PtrSingleton();
