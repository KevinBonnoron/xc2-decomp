#include "dr/dr_pixl_post_obj_motion_blur2.h"

#include "grlib/cglib_render_target.h"

namespace ml {

void DrPixlPostObjMotionBlur2::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur2::update() {}

void DrPixlPostObjMotionBlur2::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  unknown40->releaseTexture();
  unknown48->releaseTexture();
}

} // namespace ml
