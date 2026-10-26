#include "dr/dr_pixl_toon_grad.h"

#include "dr/dr_man.h"
#include "grlib/cglib_render_target.h"

namespace ml {

void DrPixlToonGrad::update() {}

const grlib::CGLibTextureBuffer &DrPixlToonGrad::getGradTex() const { return *m_gradTex[DrMan::s_nDblIdx]->unknown70; }

const grlib::CGLibTextureBuffer &DrPixlToonGrad::getDarkGradTex() const { return *m_darkGradTex[DrMan::s_nDblIdx]->unknown70; }

} // namespace ml
