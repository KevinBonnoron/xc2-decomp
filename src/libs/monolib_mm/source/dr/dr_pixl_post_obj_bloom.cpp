#include "dr/dr_pixl_post_obj_bloom.h"

#include "dr/dr_man.h"

namespace ml {

namespace _dppob {

f32 lerp(f32 a, f32 b, f32 t) { return a * (1.0f - t) + b * t; }

} // namespace _dppob

void DrPixlPostObjBloom::update() { unknown90 = 0; }

grlib::CGLibRenderTarget *DrPixlPostObjBloom::getLgtDownTarget() { return unknown98[DrMan::s_nDblIdx]; }

} // namespace ml
