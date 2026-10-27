#include "dr/dr_pixl_render_cube_map_array.h"

namespace ml {

DrPixlRenderCubeMapArray::DrPixlRenderCubeMapArray(DrMan *man) { unknown98 = man; }

DrPixlRenderCubeMapArray::~DrPixlRenderCubeMapArray() { releaseWork(); }

void DrPixlRenderCubeMapArray::setTextureInfo(f32 width, f32 height, u32 slice, GrlSurfaceFormat format, bool isResArea, u32 resArea) {
  grlib::CGLibRenderArrayCubeMap::setTextureInfo(width, height, slice, false, format, isResArea, resArea);
}

} // namespace ml
