#include "dr/dr_pixl_render_array.h"

namespace ml {

DrPixlRenderArray::DrPixlRenderArray(DrMan *man) { m_drMan = man; }

DrPixlRenderArray::~DrPixlRenderArray() { releaseWork(); }

void DrPixlRenderArray::setTextureInfo(f32 width, f32 height, u32 slice, GrlSurfaceFormat format, bool isResArea, u32 resArea) {
  grlib::CGLibRenderArray::setTextureInfo(width, height, slice, false, format, isResArea, resArea);
}

} // namespace ml
