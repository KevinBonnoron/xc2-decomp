#include "dr/dr_pixl_post_obj_capture.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_uni_base_utility.h"

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

void DrPixlPostObjCapture::renderCaputre() {
  if (unknown3e0 & 2) {
    unknown18.setRenderTarget();
    DrShdDataList *shdList = unknown00->unknown80->unknown00;
    DrShdDataObj *shader = shdList->unknown001();
    shdList->bindTriangleTex();
    shader->setupShader(0u);
    int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
    DrAPCache *apCache = unknown00->unknown5c0;
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*grlib::CGLibState::getMainRenderTarget()->unknown70, location);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    u32 offset = uniform.unknown001("gScal");
    f32 scale[4];
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    scale[2] = 0.0f;
    scale[3] = 0.0f;
    uniform.setF32SetVec4(offset, scale);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
  }
}

void DrPixlPostObjCapture::renderDef() {
  grlib::CGLibState::setMainFrameBuffer();
  if (!(unknown3e0 & 2)) {
    DrShdDataList *shdList = unknown00->unknown80->unknown00;
    DrShdDataObj *shader = shdList->unknown001();
    shdList->bindTriangleTex();
    shader->setupShader(0u);
    int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
    DrAPCache *apCache = unknown00->unknown5c0;
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*unknown18.unknown70, location);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    u32 offset = uniform.unknown001("gScal");
    f32 scale[4];
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    scale[2] = 0.0f;
    scale[3] = 0.0f;
    uniform.setF32SetVec4(offset, scale);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
  }
}

} // namespace ml
