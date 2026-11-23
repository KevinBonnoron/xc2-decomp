#include "dr/dr_pixl_render_target.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"

namespace ml {

DrPixlRenderTarget::DrPixlRenderTarget(DrMan *man) { m_drMan = man; }

DrPixlRenderTarget::~DrPixlRenderTarget() { releaseWork(); }

void DrPixlRenderTarget::debugRender(int x, int y, int width, int height, bool isAlpha, bool isDepth, f32 scale, bool isFlip) {
  m_drMan->m_drPixlMan->debugRender(*unknown70, x, y, width, height, isAlpha, isDepth, scale, isFlip);
}

void DrPixlRenderTarget::debugRenderCh(int x, int y, int width, int height, u32 channel) { m_drMan->m_drPixlMan->debugRenderCh(*unknown70, x, y, width, height, channel); }

} // namespace ml
