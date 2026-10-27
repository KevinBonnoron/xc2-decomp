#include "dr/dr_pixl_post_obj_motion_blur.h"

#include "grlib/cglib_render_target.h"

namespace ml {

void DrPixlPostObjMotionBlur::debugRender() {}

void DrPixlPostObjMotionBlur::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
}

} // namespace ml
