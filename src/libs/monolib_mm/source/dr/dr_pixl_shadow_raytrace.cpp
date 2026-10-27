#include "dr/dr_pixl_shadow_raytrace.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_render_target.h"

namespace ml {

void DrPixlShadowRaytrace::update() {}

grlib::CGLibRenderTarget *DrPixlShadowRaytrace::getTemporalOutputTexture() { return unknown20[DrMan::s_nDblIdx]; }

grlib::CGLibRenderTarget *DrPixlShadowRaytrace::getTemporalHistoryTexture() { return unknown20[DrMan::s_nDblStockIdx]; }

grlib::CGLibTextureBuffer *DrPixlShadowRaytrace::getScreenSpaceShadow() const { return unknown20[DrMan::s_nDblIdx]->unknown70; }

void DrPixlShadowRaytrace::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3) {
    unknown20[0]->releaseTexture();
    unknown20[1]->releaseTexture();
  } else {
    unknown20[DrMan::s_nDblIdx]->releaseTexture();
  }
  if (postParm->unknownfe4 == 2) {
    return;
  }
  unknown18->releaseTexture();
  unknown30->releaseTexture();
  unknown38->releaseTexture();
}

} // namespace ml
