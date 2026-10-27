#include "dr/dr_pixl_post_obj_capture.h"

#include "dr/dr_ap_gx_type.h"

namespace ml {

void DrPixlPostObjCapture::release() {
  unknown18.release();
  unknown3e0 = 3;
}

void DrPixlPostObjCapture::render() {
  if (!(unknown3e0 & 4)) {
    DrAPGxType::setupScreenQuads(false);
    renderCaputre();
    renderDef();
    unknown3e0 &= ~2;
  }
}

} // namespace ml
