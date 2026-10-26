#include "ml/cache_draw.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace mm {
struct Col4;
} // namespace mm

namespace ml {

void DebDraw::clrTex() {
  if (unknown08 & 2) {
    unknown08 &= ~6;
  }
}

void DebDraw::setAlpha(f32 alpha) {
  if (!unknown210->setAlpha(alpha)) {
    unknown1c = alpha;
    if (alpha < 0.0f) {
      unknown1c = 0.0f;
    } else if (alpha > 1.0f) {
      unknown1c = 1.0f;
    }
    unknown08 &= ~4;
  }
}

void DebDraw::setAlphaBlend(bool isEnable) {
  if (!unknown210->setAlphaBlend(isEnable)) {
    if (isEnable) {
      unknown08 |= 0x10;
    } else {
      unknown08 &= ~0x10;
    }
  }
}

void DebDraw::setLineWidth(u32 width) {
  if (!unknown210->setLineWidth(width) && unknown144 != width) {
    unknown144 = width;
    unknown08 &= ~4;
  }
}

void DebDraw::setTex(grlib::CGLibTextureBuffer *texture) {
  if (!unknown210->setTex(texture)) {
    unknown08 |= 2;
    unknown180 = texture;
  }
}

void DebDraw::fontColor(const mm::Col4 &color) { unknown210->fontColor(color); }

void DebDraw::fontBack(const mm::Col4 &color) { unknown210->fontBack(color); }

void DebDraw::fontShadow(bool isEnable) { unknown210->fontShadow(isEnable); }

void DebDraw::fontFlush(bool isEnable) { unknown210->fontFlush(isEnable); }

void DebDraw::fontScale(f32 x, f32 y) { unknown210->fontScale(x, y); }

void DebDraw::font(int x, int y, const char *text) { unknown210->font(x, y, text); }

void DebDraw::initialize() {}

void DebDraw::release() {}

} // namespace ml
