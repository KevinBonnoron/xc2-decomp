#include "dr/dr_pixl_deferred.h"

#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"

namespace ml {

void DrPixlDeferred::globalIBLRender() {
  DrShdLgtMan *lgtMan = unknown08->unknown80->unknown18;
  lgtMan->unknown58->render(lgtMan);
}

grlib::CGLibTextureBuffer *DrPixlDeferred::getTemporalInputShadowMap() { return unknown20; }

grlib::CGLibTextureBuffer *DrPixlDeferred::getTemporalOutputShadowMap() { return unknown28[DrMan::s_nDblIdx]; }

grlib::CGLibTextureBuffer *DrPixlDeferred::getTemporalOutputShadowMap() const { return unknown28[DrMan::s_nDblIdx]; }

grlib::CGLibTextureBuffer *DrPixlDeferred::getTemporalHistoryShadowMap() { return unknown28[DrMan::s_nDblStockIdx]; }

} // namespace ml
