#include "dr/dr_pixl_post_obj_motion_blur.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_render_target.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {
class DrPixlMan;
class DrPixlPostMan;

DrPixlPostObjMotionBlur::DrPixlPostObjMotionBlur(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr) {
  unknown28 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown30 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown20 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  calcBludBuffColorBuff();
  unknown38.setup(0x50);
  unknown18 = 0.0f;
  unknown1c = 0.0f;
}

DrPixlPostObjMotionBlur::~DrPixlPostObjMotionBlur() {
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur::debugRender() {}

void DrPixlPostObjMotionBlur::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
}

void DrPixlPostObjMotionBlur::render() {
  DrAPGxType::setupScreenQuads(false);
  calcBlurWork();
  calcObjMotionBlur();
  renderCalcBlur();
  lastRender();
}

void DrPixlPostObjMotionBlur::calcObjMotionBlur() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!unknown00->unknown580->unknown10->unknown9a9 && postParm->unknown1cd && 0.0f < postParm->unknown1ec) {
    calcVelocityBlur();
  }
  unknown00->blurCallBackRender();
  unknown28->setColorInvalidate();
}
} // namespace ml
