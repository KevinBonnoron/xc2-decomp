#include "dr/dr_pixl_post_obj_3d_lut.h"

#include "grlib/cglib_ctl_shader.h"

namespace ml {

void DrPixlPostObj3dLut::update() {}

void DrPixlPostObj3dLut::render(bool isFirst, bool isSecond) {
  render_applyLUT(isFirst, isSecond);
  unknown18 = false;
}

void DrPixlPostObj3dLut::renderLUT() {
  render_updateLUT();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown18 = true;
}

} // namespace ml
