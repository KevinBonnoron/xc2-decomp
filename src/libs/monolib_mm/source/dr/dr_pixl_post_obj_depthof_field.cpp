#include "dr/dr_pixl_post_obj_depthof_field.h"

#include "grlib/cglib_render_target.h"

namespace ml {

void DrPixlPostObjDepthofField::releaseColorBuff() {
  unknown18->releaseTexture();
  unknown20->releaseTexture();
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown38->releaseTexture();
  unknown48->releaseTexture();
}

} // namespace ml
