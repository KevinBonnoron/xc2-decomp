#include "dr/dr_pixl_shadow_raytrace.h"

#include "dr/dr_man.h"
#include "grlib/cglib_render_target.h"

namespace ml {

void DrPixlShadowRaytrace::update() {}

grlib::CGLibRenderTarget *DrPixlShadowRaytrace::getTemporalOutputTexture() { return unknown20[DrMan::s_nDblIdx]; }

grlib::CGLibRenderTarget *DrPixlShadowRaytrace::getTemporalHistoryTexture() { return unknown20[DrMan::s_nDblStockIdx]; }

grlib::CGLibTextureBuffer *DrPixlShadowRaytrace::getScreenSpaceShadow() const { return unknown20[DrMan::s_nDblIdx]->unknown70; }

} // namespace ml
