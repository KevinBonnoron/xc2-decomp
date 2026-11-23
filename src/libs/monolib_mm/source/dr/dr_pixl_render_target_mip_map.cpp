#include "dr/dr_pixl_render_target_mip_map.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"

namespace ml {

DrPixlRenderTargetMipMap::DrPixlRenderTargetMipMap(DrMan *man) { m_drMan = man; }

DrPixlRenderTargetMipMap::~DrPixlRenderTargetMipMap() { releaseWork(); }

void DrPixlRenderTargetMipMap::debugRender(int x, int y, int width, int height, bool isAlpha) { m_drMan->m_drPixlMan->debugRender(*unknown70, x, y, width, height, isAlpha, false, 1.0f, true); }

void DrPixlRenderTargetMipMap::debugRenderCh(int x, int y, int width, int height, u32 channel) { m_drMan->m_drPixlMan->debugRenderCh(*unknown70, x, y, width, height, channel); }

} // namespace ml
