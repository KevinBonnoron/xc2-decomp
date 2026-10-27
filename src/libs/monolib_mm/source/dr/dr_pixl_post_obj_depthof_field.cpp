#include "dr/dr_pixl_post_obj_depthof_field.h"

#include "grlib/cglib_render_target.h"

namespace ml {

// Inferred role: releases and deletes a render target; original name unknown.
inline void unknown001(grlib::CGLibRenderTarget *&target) {
  grlib::CGLibRenderTarget *renderTarget = target;
  if (renderTarget != nullptr) {
    renderTarget->releaseWork();
    delete renderTarget;
    target = nullptr;
  }
}

DrPixlPostObjDepthofField::~DrPixlPostObjDepthofField() {
  unknown001(unknown18);
  unknown001(unknown20);
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown38);
  unknown001(unknown48);
  unknown001(unknown40);
}

void DrPixlPostObjDepthofField::releaseColorBuff() {
  unknown18->releaseTexture();
  unknown20->releaseTexture();
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown38->releaseTexture();
  unknown48->releaseTexture();
}

} // namespace ml
