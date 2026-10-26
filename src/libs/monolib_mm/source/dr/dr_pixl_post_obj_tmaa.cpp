#include "dr/dr_pixl_post_obj_tmaa.h"

#include "dr/dr_man.h"

namespace ml {

void DrPixlPostObjTMAA::update() {}

void DrPixlPostObjTMAA::debugRender() {}

grlib::CGLibTextureBuffer *DrPixlPostObjTMAA::getBloomTexture() { return m_bloomTexture[DrMan::s_nDblIdx]; }

} // namespace ml
