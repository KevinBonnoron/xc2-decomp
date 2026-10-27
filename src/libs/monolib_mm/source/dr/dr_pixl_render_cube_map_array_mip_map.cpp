#include "dr/dr_pixl_render_cube_map_array_mip_map.h"

namespace ml {

void DrPixlRenderCubeMapArrayMipMap::setTextureInfo(f32 width, f32 height, u32 slice, GrlSurfaceFormat format, bool isResArea, u32 resArea) {
  grlib::CGLibRenderArrayCubeMap::setTextureInfo(width, height, slice, true, format, isResArea, resArea);
}

} // namespace ml
