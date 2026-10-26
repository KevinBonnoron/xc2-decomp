#include "dr/dr_pixl_post_obj_bloom.h"

#include "dr/dr_man.h"

namespace ml {

void DrPixlPostObjBloom::update() { unknown90 = 0; }

grlib::CGLibRenderTarget *DrPixlPostObjBloom::getLgtDownTarget() { return unknown98[DrMan::s_nDblIdx]; }

} // namespace ml
