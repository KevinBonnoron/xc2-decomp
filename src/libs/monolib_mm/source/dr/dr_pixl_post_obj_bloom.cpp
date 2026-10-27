#include "dr/dr_pixl_post_obj_bloom.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_render_target.h"

namespace ml {

namespace _dppob {

f32 lerp(f32 a, f32 b, f32 t) { return a * (1.0f - t) + b * t; }

} // namespace _dppob

void DrPixlPostObjBloom::update() { unknown90 = 0; }

void DrPixlPostObjBloom::releaseColorBuff(bool isForce) {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3 || isForce) {
    unknown98[0]->releaseTexture();
    unknown98[1]->releaseTexture();
  } else {
    unknown98[DrMan::s_nDblIdx]->releaseTexture();
  }
  if (postParm->unknownfe4 == 2 && !isForce) {
    return;
  }
  unknown18->releaseTexture();
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  unknown60->releaseTexture();
  unknown40->releaseTexture();
  unknown68->releaseTexture();
  unknown48->releaseTexture();
  unknown70->releaseTexture();
  unknown50->releaseTexture();
  unknown78->releaseTexture();
  unknown58->releaseTexture();
  unknown80->releaseTexture();
  unknown28->releaseTexture();
  unknown30->releaseTexture();
}

grlib::CGLibRenderTarget *DrPixlPostObjBloom::getLgtDownTarget() { return unknown98[DrMan::s_nDblIdx]; }

} // namespace ml
