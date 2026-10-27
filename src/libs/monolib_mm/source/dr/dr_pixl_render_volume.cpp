#include "dr/dr_pixl_render_volume.h"

namespace ml {

DrPixlRenderVolume::DrPixlRenderVolume(DrMan *man) { unknown90 = man; }

DrPixlRenderVolume::~DrPixlRenderVolume() { releaseWork(); }

void DrPixlRenderVolume::setTextureInfo(f32 width, f32 height, f32 depth, GrlSurfaceFormat format, bool isResArea, u32 resArea) {
  grlib::CGLibRenderVolume::setTextureInfo(width, height, depth, format, isResArea, resArea);
}

} // namespace ml
