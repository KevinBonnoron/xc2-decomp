#include "dr/dr_pixl_post_obj_capture.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"

namespace ml {

DrPixlPostObjCapture::DrPixlPostObjCapture(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) { unknown3e0 = 3; }

void DrPixlPostObjCapture::setup() {
  unknown3e0 &= ~1;
  unknown18.setTextureInfo(static_cast<f32>(unknown00->unknown5b8->unknown28), static_cast<f32>(unknown00->unknown5b8->unknown2c), DrAPCache::TEXTYPE_RGBA_8, false, 0);
}

DrPixlPostObjCapture::~DrPixlPostObjCapture() {
  unknown18.release();
  unknown3e0 = 3;
}

void DrPixlPostObjCapture::release() {
  unknown18.release();
  unknown3e0 = 3;
}

void DrPixlPostObjCapture::update() {
  if (unknown3e0 & FLAG_UNKNOWN_2) {
    unknown3e0 |= FLAG_UNKNOWN_3;
    return;
  }
  if (unknown3e0 & 1) {
    setup();
  }
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
