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
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {
class DrPixlMan;
class DrPixlPostMan;

DrPixlPostObjGlassBr::DrPixlPostObjGlassBr(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown4f8 = nullptr;
  unknown4e0 = nullptr;
  unknown508 = FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1;
  unknown4e8 = 0;
  unknown50c = 0;
}

void DrPixlPostObjGlassBr::setup() {
  unknown508 &= ~FLAG_UNKNOWN_0;
  DrIniSys::unknown004 *glass = unknown00->unknown70->getGlassBreakage();
  unknown4f0 = glass;
  unknown68.setupBuffer(glass->unknown002(glass->unknown10), glass->unknown14);
  unknown18.createMemVertexBuff(&unknown68, glass->unknown18, glass->unknown1c, 0xc);
  unknown40.createMemIndexBuff(&unknown68, glass->unknown24, glass->unknown2c, GRL_PRIMITIVE_TRIANGLES, GRL_INDEX_FORMAT_U16);
  // Placed before the store of the count: the game loads the count once, shifts it (lsl w1, w8, #6 at 0x71008bab28) and then stores it (0x71008bab2c). Without the
  // local the store comes first (first difference at 0x71008bab28); a local holding the count itself loads it as ldrsw instead of ldr.
  u32 size = glass->unknown0c * sizeof(unknown001);
  unknown500 = glass->unknown0c;
  unknown4f8 = static_cast<unknown001 *>(mtl::MemManager::allocate(unknown00->unknown14, size, 0x10, false, "no name", 0));
  unknown460.setup(unknown500 * 0x30 + 0x70);
  unknown98.setTextureInfo(static_cast<f32>(unknown00->unknown5b8->unknown28) * 0.5f, static_cast<f32>(unknown00->unknown5b8->unknown2c) * 0.5f, DrAPCache::TEXTYPE_RGBA_8, false, 0);
  posInt();
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
