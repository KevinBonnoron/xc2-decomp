#include "dr/dr_pixl_render_target.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"

namespace ml {

DrPixlRenderTarget::DrPixlRenderTarget(DrMan *man) { unknown3c8 = man; }

DrPixlRenderTarget::~DrPixlRenderTarget() { releaseWork(); }

void DrPixlRenderTarget::debugRender(int x, int y, int width, int height, bool isAlpha, bool isDepth, f32 scale, bool isFlip) {
  unknown3c8->unknown78->debugRender(*unknown70, x, y, width, height, isAlpha, isDepth, scale, isFlip);
}

void DrPixlRenderTarget::debugRenderCh(int x, int y, int width, int height, u32 channel) { unknown3c8->unknown78->debugRenderCh(*unknown70, x, y, width, height, channel); }

} // namespace ml
