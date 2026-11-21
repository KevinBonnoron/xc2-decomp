#include "dr/dr_mdo_sml_shadow_man.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_list.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoSmlShadowObj::DrMdoSmlShadowObj(int viewNum, const u8 *data, DrMan *man) {
  unknown28 = 0;
  unknown00 = nullptr;
  unknown08 = nullptr;
  unknown10 = reinterpret_cast<const unknown002 *>(data);
  unknown18 = nullptr;
  unknown2a = viewNum;
  int size = unknown10->unknown00 * 0x30;
  size += (32 - size % 32) % 32;
  unknown18 = mtl::MemManager::allocate(man->unknown14, size, 0x20, false, "no name", 0);
  unknown20 = unknown18;
}

DrMdoSmlShadowObj::~DrMdoSmlShadowObj() {
  if (unknown18 != nullptr) {
    mtl::MemManager::deallocate(unknown18, 0, false);
    unknown18 = nullptr;
  }
}

DrMdoSmlShadowObj *DrMdoSmlShadowMan::createObj(int viewNum, const u8 *data) {
  DrMdoSmlShadowObj *shadow = new (unknown08->unknown10) DrMdoSmlShadowObj(viewNum, data, unknown08);
  unknown101(unknown50[DrMan::s_nDblStockIdx][0], unknown50[DrMan::s_nDblStockIdx][1], shadow);
  return shadow;
}

DrMdoSmlShadowMan::DrMdoSmlShadowMan(DrMan *man) : unknown00(0), unknown04(0), unknown08(man) {
  for (int i = 0; i < 4; i++) {
    unknown10[i][0] = nullptr;
    unknown10[i][1] = nullptr;
  }
  for (int i = 0; i < 2; i++) {
    unknown50[i][0] = nullptr;
    unknown50[i][1] = nullptr;
  }
  unknown70[0] = nullptr;
  unknown70[1] = nullptr;
}

// Inferred helper: deletes the objects of a list and empties it; original name unknown.
static void unknown001(DrMdoSmlShadowObj **list) {
  DrMdoSmlShadowObj *shadow = list[0];
  while (shadow != nullptr) {
    DrMdoSmlShadowObj *next = shadow->unknown08;
    delete shadow;
    shadow = next;
  }
  list[0] = nullptr;
  list[1] = nullptr;
}

DrMdoSmlShadowMan::~DrMdoSmlShadowMan() {
  for (int i = 0; i < 2; i++) {
    unknown001(unknown50[i]);
  }
  unknown001(unknown70);
  for (int i = 0; i < 4; i++) {
    unknown001(unknown10[i]);
  }
}

void DrMdoSmlShadowMan::releaseObj(DrMdoSmlShadowObj *shadow) { shadow->unknown28 |= DrMdoSmlShadowObj::FLAG_UNKNOWN_14 << DrMan::s_nDblStockIdx; }

void DrMdoSmlShadowMan::delObjList() {
  unknown50[DrMan::s_nDblIdx][0] = nullptr;
  unknown50[DrMan::s_nDblIdx][1] = nullptr;
  unknown001(unknown70);
}

bool DrMdoSmlShadowMan::checkDisp() {
  for (DrMdoSmlShadowObj *shadow = unknown10[unknown04][0]; shadow != nullptr; shadow = shadow->unknown08) {
    if (shadow->unknown28 & DrMdoSmlShadowObj::FLAG_UNKNOWN_0) {
      return true;
    }
  }
  return false;
}

// Ruling 8: the shader pass block (setupShader, the uniform utility, setUseUniformBlock and the value offset lookups) repeats in the other post passes
// (DrPixlPostObjFxAA, DrPixlPostObjDepthofField, DrPixlPostObjMotionBlur...). The game writes it out in each function (0x7100830334: four
// getUniformBlockValOfs calls at 0x7100830434 to 0x71008304a0, each on the shader's uniform block; no call to a shared helper).
void DrMdoSmlShadowMan::shadowRender() {
  if (unknown08->unknown1d73) {
    return;
  }
  DrPixlPostMan *postMan = unknown08->unknown78->unknown7f0->unknown180;
  if (postMan->unknown78 == nullptr) {
    return;
  }
  DrMdoSmlShadowObj *shadow = unknown10[unknown04][0];
  if (shadow == nullptr) {
    return;
  }
  DrAPGxType::beginSimpleShadow();
  DrAPGxType::setupBlend(2);
  DrAPGxType::setupCullingBack();
  // P2: the single-use local places the getPixlObj call (0x71008303a8) before the view work load (0x71008303ac to 0x71008303b4), which the game takes
  // between it and setRenderTarget (0x71008303bc); `getPixlObj(2)->setRenderTarget()` after the view work load gives 144 instructions against 145.
  DrPixlRenderTarget *target = unknown08->unknown78->getPixlObj(2);
  DrCalcViewWork *viewWork = unknown08->unknown580->unknown10;
  target->setRenderTarget();
  DrShdDataList *shdList = unknown08->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x18);
  shdList->bindShdBoxVertex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  DrAPCache *apCache = unknown08->unknown5c0;
  u32 modelOfs = uniform.unknown001("gMdl");
  u32 projOfs = uniform.unknown001("gProj");
  u32 invOfs = uniform.unknown001("gInv");
  u32 parmOfs = uniform.unknown001("parm[0]");
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("dep");
  uniform.setMat44SetMat44(projOfs, viewWork->unknown180);
  uniform.setMat44SetMat44(invOfs, viewWork->unknown1c0);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*postMan->getDownDepth()->unknown70, location);
  for (; shadow != nullptr; shadow = shadow->unknown08) {
    shadow->renderNode(shdList, modelOfs, parmOfs, uniform);
  }
  DrAPGxType::setupBlend(0);
  DrAPGxType::endSimpleShadow();
}

} // namespace ml
