#include "dr/dr_pixl_post_obj_volume.h"

#include "grlib/cglib_render_target.h"

namespace ml {

void DrPixlPostObjVolume::resetColorBuff() { calcColorBuff(); }

void DrPixlPostObjVolume::update() {}

void DrPixlPostObjVolume::releaseColorBuff() {
  if (unknown18 != nullptr) {
    unknown18->releaseTexture();
  }
  if (unknown20 != nullptr) {
    unknown20->releaseTexture();
  }
  unknown28->releaseTexture();
}

} // namespace ml
