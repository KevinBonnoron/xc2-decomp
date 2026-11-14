#include "dr/dr_pixl_post_obj_fx_aa.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_shader.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrPixlPostObjFxAA::DrPixlPostObjFxAA(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown18 = new (drMan->unknown0c) DrPixlRenderTarget(drMan);
  resetColorBuff();
}

DrPixlPostObjFxAA::~DrPixlPostObjFxAA() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

void DrPixlPostObjFxAA::releaseColorBuff() { unknown18->releaseTexture(); }

void DrPixlPostObjFxAA::update() {}

void DrPixlPostObjFxAA::render() {
  DrAPGxType::setupScreenQuads(false);
  calcScale();
}

void DrPixlPostObjFxAA::resetColorBuff() {
  unknown20 = static_cast<f32>(unknown00->unknown5b8->unknown18);
  unknown24 = static_cast<f32>(unknown00->unknown5b8->unknown1c);
}

void DrPixlPostObjFxAA::calcLuminosity() {
  wkPixlManRes *res = unknown08->unknown7f0;
  DrPixlRenderTarget *target = res->unknown130;
  if (res->unknown138 == target) {
    target = res->unknown140;
  }
  unknown18->setRenderTarget(*target);
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getSelectShdObj(3);
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrPixlRenderTarget *source = unknown08->unknown7f0->unknown138;
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*source->unknown70, location);
  shdList->renderTriangle();
  unknown18->setColorInvalidate();
}

void DrPixlPostObjFxAA::debugRender() {
  const unknown057 *screen = unknown00->unknown5b8;
  unknown18->debugRender(0, 0, screen->unknown18 / 2, screen->unknown1c / 2, false, false, 1.0f, true);
}

} // namespace ml
