#include "dr/dr_pixl_post_obj_motion_blur.h"

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

DrPixlPostObjMotionBlur::~DrPixlPostObjMotionBlur() {
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur::debugRender() {}

void DrPixlPostObjMotionBlur::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
}

} // namespace ml
