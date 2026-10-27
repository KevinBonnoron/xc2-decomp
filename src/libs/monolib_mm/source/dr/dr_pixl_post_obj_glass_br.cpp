#include "dr/dr_pixl_post_obj_glass_br.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_col4.h"
#include "mtl/mem_manager.h"

namespace ml {
class DrPixlMan;
class DrPixlPostMan;

DrPixlPostObjGlassBr::DrPixlPostObjGlassBr(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown4f8 = nullptr;
  unknown4e0 = nullptr;
  unknown508 = 3;
  unknown4e8 = 0;
  unknown50c = 0;
}

void DrPixlPostObjGlassBr::render() {
  if ((unknown508 & FLAG_UNKNOWN_2) == 0) {
    DrAPGxType::setupScreenQuads(false);
    renderCaputre();
    renderGlass();
  }
}

void DrPixlPostObjGlassBr::renderCaputre() {
  if (unknown508 & 2) {
    unknown508 &= ~2;
    unknown98.setRenderTarget();
    DrShdDataList *shdList = unknown00->unknown80->unknown00;
    DrShdDataObj *shader = shdList->unknown001();
    shdList->bindTriangleTex();
    shader->setupShader(0u);
    int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
    DrAPCache *apCache = unknown00->unknown5c0;
    apCache->beginTexSampling(2, 1);
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

void DrPixlPostObjGlassBr::renderGlass() {
  grlib::CGLibRenderTarget *mainTarget = grlib::CGLibState::getMainRenderTarget();
  mm::Col4 clearColor(0.0f, 0.0f, 0.0f, 0.0f);
  mainTarget->clearTexture(clearColor, static_cast<GrlClaerMask>(0xf));
  grlib::CGLibState::setMainFrameBuffer();
  grlib::CGLibPolygon::setCullingFront();
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
  DrShdDataObj *shader = unknown00->unknown80->unknown00->getPostShdObj(0x3d);
  shader->setupShader(0u);
  grlib::CGLibCtlVertex::setVertex(unknown18);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown98.unknown70, location);
  int blockOffset = (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_POST");
  unknown460.setUniformBlock(blockOffset);
  unknown40.drawIndex();
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
}

void DrPixlPostObjGlassBr::release() {
  unknown98.release();
  unknown18.release();
  unknown40.release();
  unknown68.release();
  unknown460.release();
  if (unknown4f8 != nullptr) {
    mtl::MemManager::deallocate(unknown4f8, 0, false);
    unknown4f8 = nullptr;
  }
  unknown508 = 3;
}

DrPixlPostObjGlassBr::~DrPixlPostObjGlassBr() { release(); }

} // namespace ml
