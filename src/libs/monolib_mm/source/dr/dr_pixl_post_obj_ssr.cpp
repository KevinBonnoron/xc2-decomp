#include "dr/dr_pixl_post_obj_ssr.h"

#include "dr/dr_man.h"

namespace ml {

void DrPixlPostObjSSR::setClear() { unknown18 |= 1; }

grlib::CGLibTextureBuffer *DrPixlPostObjSSR::getReflectionTexture() const { return m_reflectionTexture[DrMan::s_nDblIdx]; }

} // namespace ml
