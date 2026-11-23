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
  DrIniSys::unknown004 *glass = m_drMan->m_drIniSys->getGlassBreakage();
  unknown4f0 = glass;
  m_cGLibVtlMemPool.setupBuffer(glass->unknown002(glass->unknown10), glass->unknown14);
  m_cGLibVtxVertex.createMemVertexBuff(&m_cGLibVtlMemPool, glass->unknown18, glass->unknown1c, 0xc);
  m_cGLibVtxIndex.createMemIndexBuff(&m_cGLibVtlMemPool, glass->unknown24, glass->unknown2c, GRL_PRIMITIVE_TRIANGLES, GRL_INDEX_FORMAT_U16);
  // Placed before the store of the count: the game loads the count once, shifts it (lsl w1, w8, #6 at 0x71008bab28) and then stores it (0x71008bab2c). Without the
  // local the store comes first (first difference at 0x71008bab28); a local holding the count itself loads it as ldrsw instead of ldr.
  u32 size = glass->unknown0c * sizeof(unknown001);
  unknown500 = glass->unknown0c;
  unknown4f8 = static_cast<unknown001 *>(mtl::MemManager::allocate(m_drMan->unknown14, size, 0x10, false, "no name", 0));
  m_cGLibDblUniformBlock.setup(unknown500 * 0x30 + 0x70);
  m_cGLibRenderTarget.setTextureInfo(static_cast<f32>(m_drMan->unknown5b8->unknown28) * 0.5f, static_cast<f32>(m_drMan->unknown5b8->unknown2c) * 0.5f, DrAPCache::TEXTYPE_RGBA_8, false, 0);
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
    m_cGLibRenderTarget.setRenderTarget();
    DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
    DrShdDataObj *shader = shdList->unknown001();
    shdList->bindTriangleTex();
    shader->setupShader(0u);
    int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
    DrAPCache *apCache = m_drMan->m_drAPCache;
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
  DrShdDataObj *shader = m_drMan->m_drShdMan->m_drShdDataList->getPostShdObj(0x3d);
  shader->setupShader(0u);
  grlib::CGLibCtlVertex::setVertex(m_cGLibVtxVertex);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrAPCache *apCache = m_drMan->m_drAPCache;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*m_cGLibRenderTarget.unknown70, location);
  int blockOffset = (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_POST");
  m_cGLibDblUniformBlock.setUniformBlock(blockOffset);
  m_cGLibVtxIndex.drawIndex();
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
}

void DrPixlPostObjGlassBr::release() {
  m_cGLibRenderTarget.release();
  m_cGLibVtxVertex.release();
  m_cGLibVtxIndex.release();
  m_cGLibVtlMemPool.release();
  m_cGLibDblUniformBlock.release();
  if (unknown4f8 != nullptr) {
    mtl::MemManager::deallocate(unknown4f8, 0, false);
    unknown4f8 = nullptr;
  }
  unknown508 = 3;
}

DrPixlPostObjGlassBr::~DrPixlPostObjGlassBr() { release(); }

} // namespace ml
