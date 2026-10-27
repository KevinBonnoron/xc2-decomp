#include "dr/dr_pixl_render_target_1d.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"

namespace ml {

DrPixlRenderTarget1D::DrPixlRenderTarget1D(DrMan *man) { unknownc0 = man; }

DrPixlRenderTarget1D::~DrPixlRenderTarget1D() { releaseWork(); }

void DrPixlRenderTarget1D::debugRender(int x, int y, int width, int height, bool isAlpha, bool isDepth) {
  unknownc0->unknown78->debugRender(*unknown70, x, y, width, height, isAlpha, isDepth, 1.0f, true);
}

void DrPixlRenderTarget1D::debugRenderCh(int x, int y, int width, int height, u32 channel) { unknownc0->unknown78->debugRenderCh(*unknown70, x, y, width, height, channel); }

} // namespace ml
