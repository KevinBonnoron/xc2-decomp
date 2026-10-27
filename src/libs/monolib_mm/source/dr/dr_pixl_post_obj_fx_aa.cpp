#include "dr/dr_pixl_post_obj_fx_aa.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "grlib/cglib_render_target.h"

namespace ml {

DrPixlPostObjFxAA::~DrPixlPostObjFxAA() {
  grlib::CGLibRenderTarget *renderTarget = unknown18;
  if (renderTarget != nullptr) {
    renderTarget->releaseWork();
    delete renderTarget;
    unknown18 = nullptr;
  }
}

void DrPixlPostObjFxAA::releaseColorBuff() { unknown18->releaseTexture(); }

void DrPixlPostObjFxAA::update() {}

void DrPixlPostObjFxAA::render() {
  DrAPGxType::setupScreenQuads(false);
  calcScale();
}

void DrPixlPostObjFxAA::resetColorBuff() {
  unknown20 = static_cast<f32>(unknown00->unknown5b8->unknown18);
  unknown24 = static_cast<f32>(unknown00->unknown5b8->unknown1c);
}

} // namespace ml
