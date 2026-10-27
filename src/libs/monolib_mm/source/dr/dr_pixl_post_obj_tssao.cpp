#include "dr/dr_pixl_post_obj_tssao.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_render_target.h"
#include "mm_math/mm_vec4.h"

namespace ml {

void DrPixlPostObjTSSAO::calcFragCoordToUV(mm::Vec4 &uv, f32 width, f32 height) {
  uv.x = 1.0f / width;
  uv.y = 1.0f / height;
  uv.z = static_cast<f32>(unknown70) / width;
  uv.w = static_cast<f32>(unknown70) / height;
}

void DrPixlPostObjTSSAO::calcFragCoordToScreen(mm::Vec4 &screen, f32 width, f32 height) {
  screen.x = 2.0f / width;
  screen.y = 2.0f / height;
  screen.z = (static_cast<f32>(unknown70) + static_cast<f32>(unknown70)) / width - 1.0f;
  screen.w = (static_cast<f32>(unknown70) + static_cast<f32>(unknown70)) / height - 1.0f;
}

void DrPixlPostObjTSSAO::passUpScaling() { passUpScaleToMiddle(); }

void DrPixlPostObjTSSAO::update() { unknown10->setDownDepth(); }

void DrPixlPostObjTSSAO::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3) {
    unknown28[0]->releaseTexture();
    unknown50[0]->releaseTexture();
    unknown28[1]->releaseTexture();
    unknown50[1]->releaseTexture();
  } else {
    unknown28[DrMan::s_nDblIdx]->releaseTexture();
    unknown50[DrMan::s_nDblIdx]->releaseTexture();
    if (postParm->unknownfe4 == 2) {
      return;
    }
  }
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  if (unknown60 != nullptr) {
    unknown60->releaseTexture();
  }
  if (unknown68 != nullptr) {
    unknown68->releaseTexture();
  }
  unknown48->releaseTexture();
}

} // namespace ml
