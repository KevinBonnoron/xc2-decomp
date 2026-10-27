#include "dr/dr_pixl_render_target_mip_map.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"

namespace ml {

DrPixlRenderTargetMipMap::DrPixlRenderTargetMipMap(DrMan *man) { unknown488 = man; }

DrPixlRenderTargetMipMap::~DrPixlRenderTargetMipMap() { releaseWork(); }

void DrPixlRenderTargetMipMap::debugRender(int x, int y, int width, int height, bool isAlpha) { unknown488->unknown78->debugRender(*unknown70, x, y, width, height, isAlpha, false, 1.0f, true); }

void DrPixlRenderTargetMipMap::debugRenderCh(int x, int y, int width, int height, u32 channel) { unknown488->unknown78->debugRenderCh(*unknown70, x, y, width, height, channel); }

} // namespace ml
