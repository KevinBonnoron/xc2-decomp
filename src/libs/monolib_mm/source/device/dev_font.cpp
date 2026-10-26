#include "ml/dev_font.h"

namespace ml {
enum FONT_STYLE : int;

void FontLayer::fontStyle(FONT_STYLE style) { DevFont::fontLayerStyle(this, style); }

void FontLayer::fontZ(u32 z) { DevFont::fontLayerZ(this, z); }

} // namespace ml
