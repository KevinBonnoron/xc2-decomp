#include "dr/dr_pixl_post_obj_motion_blur2.h"

#include <math.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlPostObjMotionBlur2::DrPixlPostObjMotionBlur2(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown60(0), unknown64(true) {
  unknown28 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown30 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown38 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown48 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown40 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  unknown20 = new (m_drMan->unknown0c) DrPixlRenderTarget(m_drMan);
  for (s32 i = 0; i < 2; i++) {
    unknown50[i] = new (m_drMan->unknown0c) grlib::CGLibVtxVertex();
  }
  calcBludBuffColorBuff();
  unknown18 = 0.0f;
  unknown1c = 0.0f;
}

void DrPixlPostObjMotionBlur2::calcBludBuffColorBuff() {
  f32 height = static_cast<f32>(m_drMan->unknown5b8->unknown1c);
  f32 width = static_cast<f32>(m_drMan->unknown5b8->unknown18);
  f32 quarterX = width * 0.25f;
  f32 quarterY = height * 0.25f;
  f32 tileOutX = width * 0.05f;
  f32 tileOutY = height * 0.05f;
  f32 maskX = width * 0.4f;
  f32 maskY = height * 0.4f;
  f32 tileX = width * 0.05f;
  f32 tileY = height * 0.05f;
  calc1PixlOfs(quarterX, quarterY);
  calc1PixlOfs(maskX, maskY);
  calc1PixlOfs(tileOutX, tileOutY);
  calc1PixlOfs(tileX, tileY);
  unknown28->setTextureInfo(quarterX, quarterY, DrPixlFormat::s_BlurVelFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown174);
  unknown30->setTextureInfo(quarterX, quarterY, DrPixlFormat::s_BlurVelFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown178);
  unknown20->setTextureInfo(maskX, maskY, DrPixlFormat::s_BlurOutFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown17c);
  unknown38->setTextureInfo(tileOutX, tileOutY, DrPixlFormat::s_BlurVelFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown180);
  unknown40->setTextureInfo(tileOutX, quarterY, DrPixlFormat::s_BlurVelFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown184);
  unknown48->setTextureInfo(tileX, tileY, DrPixlFormat::s_BlurMaskFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown188);
  s32 columns = static_cast<s32>(tileX);
  s32 rows = static_cast<s32>(tileY);
  unknown60 ^= 1;
  unknown50[unknown60]->release();
  unknown50[unknown60]->createVertexBuff(columns * rows * 0x10, 0x10);
  void *buffer;
  u32 size;
  unknown50[unknown60]->lock(&buffer, &size);
  f32 *vertex = static_cast<f32 *>(buffer);
  f32 columnCount = static_cast<f32>(columns);
  for (s32 row = 0; row < rows; row++) {
    f32 y = (static_cast<f32>(row) + 0.5f) / static_cast<f32>(rows);
    y = y * 2.0f - 1.0f;
    for (s32 column = 0; column < columns; column++) {
      f32 x = (static_cast<f32>(column) + 0.5f) / columnCount;
      vertex[0] = x * 2.0f - 1.0f;
      vertex[1] = y;
      vertex[2] = 1.0f;
      vertex[3] = 1.0f;
      vertex += 4;
    }
  }
  unknown50[unknown60]->unlock();
}

void DrPixlPostObjMotionBlur2::debugRender() {
  if (m_drMan->unknown120[m_drMan->unknown1c98]->isMotBlur2() && m_drMan->unknown120[m_drMan->unknown1c98]->unknown1000) {
    s32 width = m_drMan->unknown5b8->unknown28;
    s32 height = m_drMan->unknown5b8->unknown2c;
    m_drMan->m_drPixlMan->debugRender(*unknown48->unknown70, 0, 0, width, height, false, false, 0.2f, true);
  }
}

DrPixlPostObjMotionBlur2::~DrPixlPostObjMotionBlur2() {
  for (int i = 0; i < 2; i++) {
    unknown001(unknown50[i]);
  }
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown38);
  unknown001(unknown48);
  unknown001(unknown40);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur2::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur2::update() {}

void DrPixlPostObjMotionBlur2::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  unknown40->releaseTexture();
  unknown48->releaseTexture();
}

void DrPixlPostObjMotionBlur2::render() {
  DrAPGxType::setupScreenQuads(false);
  calcBlurWork();
  calcObjMotionBlur();
  grlib::CGLibCtlShader::setMemoryBarrierBit(3);
  if (unknown64) {
    renderCalcBlur();
  }
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  if (unknown64) {
    lastRender();
  }
}

// Same body shape as DrPixlPostObjTSSAO::passTemporalFiltering for the matrix block.
void DrPixlPostObjMotionBlur2::calcBlurWork() {
  DrCalcViewWork *viewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
  if (viewWork->unknown9aa) {
    unknown28->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 1.0f), static_cast<GrlClaerMask>(0xf));
  } else {
    DrAPGxType::setupBlend(0);
    unknown28->setRenderTarget();
    DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
    DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
    DrShdDataObj *shader = shdList->getPostShdObj(0x39);
    shdList->bindTriangleTex();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTVelocity");
    int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDep");
    // The game calls it and drops the result (the third getTextureLocation call; ruling 5).
    (shader->unknown38 + shader->unknown58)->getTextureLocation("gTStencil");
    u32 dpch = uniform.unknown001("dpch");
    u32 projInv = uniform.unknown001("gProjInv");
    u32 toPrevScreen = uniform.unknown001("gToPrevScreen");
    u32 sampleOffset = uniform.unknown001("gSampleOffset[0]");
    u32 sizeOfColor = uniform.unknown001("gSizeOfColor");
    u32 targetVelocity = uniform.unknown001("gTargetVelocity");
    DrAPCache *apCache = m_drMan->m_drAPCache;
    // unknown798 is read through m_drMan->m_drCalcMan->m_drCalcViewWork after the calls (the game reloads the view work pointer for it); the dpch value is a
    // float array (the game's slot is 8-byte aligned, a Vec4 would be 16).
    f32 blurParam[4] = {postParm->unknown200, postParm->unknown20c, postParm->unknown210 * m_drMan->m_drCalcMan->m_drCalcViewWork->unknown798, postParm->unknown204};
    uniform.setF32SetVec4(dpch, blurParam);
    uniform.setMat44SetMat44(projInv, viewWork->unknown3c0);
    // {} blocks: the frame of the game reuses the slots of the matrix, the sample offsets and the color size for later locals (ruling 3).
    {
      mm::Mat44 matrix = viewWork->unknown00;
      matrix.unknown009(matrix, viewWork->unknown280 * viewWork->unknown380);
      uniform.setMat44SetMat44(toPrevScreen, matrix);
    }
    {
      f32 halfHeight = 0.5f / static_cast<f32>(unknown28->unknownc0);
      f32 halfWidth = 0.5f / static_cast<f32>(unknown28->unknownbc);
      f32 offsets[8] = {-halfWidth, -halfHeight, -halfWidth, halfHeight, halfWidth, -halfHeight, halfWidth, halfHeight};
      uniform.setF32SetF32Array(sampleOffset, offsets, 8);
    }
    {
      mm::Vec4 colorSize(static_cast<f32>(m_drMan->unknown5b8->unknown18), static_cast<f32>(m_drMan->unknown5b8->unknown1c), 0.0f, 0.0f);
      uniform.setVec4SetVec4(sizeOfColor, colorSize);
    }
    mm::Vec4 velocity = mm::Vec4::zero;
    mm::Vec3 point = viewWork->unknown410 * viewWork->unknown4c8 * 10.0f + viewWork->unknown400;
    f32 w = (point.x * viewWork->unknown340.rows[0][3] + point.y * viewWork->unknown340.rows[1][3] + point.z * viewWork->unknown340.rows[2][3]) + viewWork->unknown340.rows[3][3];
    f32 x = (point.x * viewWork->unknown340.rows[0][0] + point.y * viewWork->unknown340.rows[1][0] + point.z * viewWork->unknown340.rows[2][0]) + viewWork->unknown340.rows[3][0];
    f32 y = (point.x * viewWork->unknown340.rows[0][1] + point.y * viewWork->unknown340.rows[1][1] + point.z * viewWork->unknown340.rows[2][1]) + viewWork->unknown340.rows[3][1];
    // The game branches on the negation of `<=` (b.ls after the fcmp against 1e-06; `1.0e-6f < fabsf(w)` gives b.le).
    if (!(fabsf(w) <= 1.0e-6f)) {
      w = 1.0f / w;
      x = x * w;
      y = y * w;
    }
    // The game computes the product twice (for gToPrevScreen and again here), each time with the runtime alias test of Mat44::unknown002.
    mm::Mat44 prevViewProj = viewWork->unknown280 * viewWork->unknown380;
    f32 prevW = (point.x * prevViewProj.rows[0][3] + point.y * prevViewProj.rows[1][3] + point.z * prevViewProj.rows[2][3]) + prevViewProj.rows[3][3];
    f32 prevX = (point.x * prevViewProj.rows[0][0] + point.y * prevViewProj.rows[1][0] + point.z * prevViewProj.rows[2][0]) + prevViewProj.rows[3][0];
    f32 prevY = (point.x * prevViewProj.rows[0][1] + point.y * prevViewProj.rows[1][1] + point.z * prevViewProj.rows[2][1]) + prevViewProj.rows[3][1];
    // Same projection through the previous view projection.
    if (!(fabsf(prevW) <= 1.0e-6f)) {
      prevW = 1.0f / prevW;
      prevX = prevX * prevW;
      prevY = prevY * prevW;
    }
    velocity.x = x - prevX;
    velocity.y = -(y - prevY);
    uniform.setVec4SetVec4(targetVelocity, velocity);
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*m_drPixlMan->getPixlObj(3)->unknown70, velocityLocation);
    apCache->setTexture(*m_drPixlMan->unknown7f0->m_drPixlPostMan->getDownDepth()->unknown70, depthLocation);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderTriangle();
  }
}

void DrPixlPostObjMotionBlur2::calcObjMotionBlur() {
  if (!m_drMan->m_drCalcMan->m_drCalcViewWork->unknown9aa && m_drMan->unknown120[m_drMan->unknown1c98]->unknown1cd) {
    calcVelocityBlur();
  }
  m_drMan->blurCallBackRender();
  calcMaxVelocityPerTile();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  calcBlurMask();
}

void DrPixlPostObjMotionBlur2::lastRender() {
  DrPixlRenderTarget *target = m_drPixlMan->unknown7f0->unknown138;
  target->setRenderTarget();
  DrAPGxType::setupBlend(1);
  DrShdDataObj *shader = m_drMan->m_drShdMan->m_drShdDataList->getPostShdObj(0x46);
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 posOffset = uniform.unknown001("gPosOffset");
  u32 fragToUv = uniform.unknown001("gFragToUV");
  mm::Vec4 position = mm::Vec4::zero;
  position.x = 1.0f / static_cast<f32>(unknown48->unknownbc);
  position.y = 1.0f / static_cast<f32>(unknown48->unknownc0);
  uniform.setVec4SetVec4(posOffset, position);
  mm::Vec4 fragment = mm::Vec4::zero;
  fragment.x = 1.0f / static_cast<f32>(target->unknownbc);
  fragment.y = 1.0f / static_cast<f32>(target->unknownc0);
  uniform.setVec4SetVec4(fragToUv, fragment);
  uniform.updateData();
  uniform.setUniformBlock();
  int frameLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  DrAPCache *apCache = m_drMan->m_drAPCache;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown20->unknown70, frameLocation);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown48->unknown70, velocityLocation);
  grlib::CGLibCtlVertex::setVertex(*unknown50[unknown60]);
  grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, unknown50[unknown60]->unknown08);
  DrAPGxType::setupBlend(0);
}

void DrPixlPostObjMotionBlur2::renderCalcBlur() {
  unknown20->clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
  DrAPGxType::setupScreenQuads(false);
  unknown20->setRenderTarget();
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  DrShdDataObj *shader = shdList->getPostShdObj(0x3a);
  u32 declHlv = postParm->unknown1cf ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("DECL_HLV"), declHlv);
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int frameLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int velocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  int blurMaskLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTBlurMask");
  int maxVelocityLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("sMaxVelocity");
  u32 ofsOffset = uniform.unknown001("ofs[0]");
  u32 sizeOfS0Offset = uniform.unknown001("gSizeOfS0");
  u32 sizeOfMaxVelocityOffset = uniform.unknown001("gSizeOfMaxVelocity");
  u32 sizeOfOutputOffset = uniform.unknown001("gSizeOfOutput");
  u32 paramOffset = uniform.unknown001("gParam");
  u32 posOffsetOffset = uniform.unknown001("gPosOffset");
  f32 velocityWidth = static_cast<f32>(unknown28->unknownbc);
  f32 velocityHeight = static_cast<f32>(unknown28->unknownc0);
  f32 maxVelocityWidth = static_cast<f32>(unknown38->unknownbc);
  f32 maxVelocityHeight = static_cast<f32>(unknown38->unknownc0);
  DrPixlRenderTarget *target = m_drPixlMan->unknown7f0->unknown138;
  DrAPCache *apCache = m_drMan->m_drAPCache;
  f32 targetHeight = static_cast<f32>(target->unknownc0);
  f32 targetWidth = static_cast<f32>(target->unknownbc);
  f32 ofs[12];
  ofs[0] = (targetWidth - 1.0f) / targetWidth;
  ofs[1] = (targetHeight - 1.0f) / targetHeight;
  ofs[2] = 1.0f / (targetWidth + targetWidth);
  ofs[3] = 1.0f / (targetHeight + targetHeight);
  ofs[4] = (velocityWidth - 1.0f) / velocityWidth;
  ofs[5] = (velocityHeight - 1.0f) / velocityHeight;
  ofs[6] = 1.0f / (velocityWidth + velocityWidth);
  ofs[7] = 1.0f / (velocityHeight + velocityHeight);
  ofs[8] = (maxVelocityWidth - 1.0f) / maxVelocityWidth;
  ofs[9] = (maxVelocityHeight - 1.0f) / maxVelocityHeight;
  ofs[10] = 1.0f / (maxVelocityWidth + maxVelocityWidth);
  ofs[11] = 1.0f / (maxVelocityHeight + maxVelocityHeight);
  uniform.setF32SetF32Array(ofsOffset, ofs, 12);
  mm::Vec4 sizeOfS0;
  sizeOfS0.x = targetWidth;
  sizeOfS0.y = targetHeight;
  sizeOfS0.z = 1.0f / targetWidth;
  sizeOfS0.w = 1.0f / targetHeight;
  uniform.setVec4SetVec4(sizeOfS0Offset, sizeOfS0);
  mm::Vec4 sizeOfMaxVelocity;
  sizeOfMaxVelocity.x = static_cast<f32>(unknown38->unknownbc);
  sizeOfMaxVelocity.y = static_cast<f32>(unknown38->unknownc0);
  sizeOfMaxVelocity.z = 1.0f / sizeOfMaxVelocity.x;
  sizeOfMaxVelocity.w = 1.0f / sizeOfMaxVelocity.y;
  uniform.setVec4SetVec4(sizeOfMaxVelocityOffset, sizeOfMaxVelocity);
  mm::Vec4 sizeOfOutput;
  sizeOfOutput.x = static_cast<f32>(unknown20->unknownbc);
  sizeOfOutput.y = static_cast<f32>(unknown20->unknownc0);
  sizeOfOutput.z = 1.0f / sizeOfOutput.x;
  sizeOfOutput.w = 1.0f / sizeOfOutput.y;
  uniform.setVec4SetVec4(sizeOfOutputOffset, sizeOfOutput);
  f32 scale = 1.0f;
  if (postParm->unknownfb3) {
    scale = powf(postParm->unknownfc0 * postParm->unknownfc0 + postParm->unknownfc4 * postParm->unknownfc4, 0.7f);
  }
  mm::Vec4 param;
  param.x = scale * postParm->unknown214;
  param.z = 0.0f;
  param.w = 0.0f;
  param.y = 0.0f;
  uniform.setVec4SetVec4(paramOffset, param);
  mm::Vec4 posOffset;
  f32 posHeight = static_cast<f32>(unknown48->unknownc0);
  f32 posWidth = static_cast<f32>(unknown48->unknownbc);
  posOffset.x = 1.0f / posWidth;
  posOffset.y = 1.0f / posHeight;
  posOffset.z = 0.5f / posWidth;
  posOffset.w = -0.5f / posHeight;
  uniform.setVec4SetVec4(posOffsetOffset, posOffset);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*m_drPixlMan->unknown7f0->unknown138->unknown70, frameLocation);
  apCache->setTexture(*unknown28->unknown70, velocityLocation);
  apCache->setTexture(*unknown38->unknown70, maxVelocityLocation);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown48->unknown70, blurMaskLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  grlib::CGLibCtlVertex::setVertex(*unknown50[unknown60]);
  grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, unknown50[unknown60]->unknown08);
  unknown20->setColorInvalidate();
}

// 0x71008bdabc. The test is written as an early return of `<= 0.0f`: the game skips the body only for an ordered `<=` (b.ls), `0.0f < x` gives b.le.
// setMoveMem is called through the base class like DrPixlPostObj3dLut::render_updateLUT: the call through the utility gives 145 instructions
// against the game's 147.
void DrPixlPostObjMotionBlur2::calcVelocityBlur() {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (postParm->unknown208 <= 0.0f) {
    return;
  }
  DrAPCache *apCache = m_drMan->m_drAPCache;
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x1c);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  shdList->unknown002(shader);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 ofsOffset = uniform.unknown001("ofs[0]");
  f32 width = static_cast<f32>(unknown30->unknownbc) * postParm->unknown208;
  f32 height = postParm->unknown208 * static_cast<f32>(unknown30->unknownc0);
  apCache->beginTexSampling(2, 1);
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown30->setRenderTarget();
  apCache->setTexture(*unknown28->unknown70, location);
  f32 offsets[20];
  DrPixlPostObj::getSampleOffsets_GaussBlur_Horizontally(width, height, 2, offsets, 1.0f, 1.0f);
  uniform.setF32SetF32Array(ofsOffset, offsets, 20);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  uniform.unknown20.Rebuilding();
  static_cast<grlib::CGLibUniBaseUtility &>(uniform).setMoveMem();
  unknown30->setColorInvalidate();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  unknown28->setRenderTarget();
  apCache->setTexture(*unknown30->unknown70, location);
  DrPixlPostObj::getSampleOffsets_GaussBlur_Verticaly(width, height, 2, offsets, 1.0f, 1.0f);
  uniform.setF32SetF32Array(ofsOffset, offsets, 20);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  unknown28->setColorInvalidate();
}

// 0x71008bdd08. The game never writes the z and w of the five 4-float taps of `ofs` (stores at sp+0x0/0x4, 0x10/0x14... of each pass, 0x71008bde94 to 0x71008bdecc and
// 0x71008bdf5c to 0x71008bdfb0) nor the z and w of `size` (only sp+0x50 and sp+0x54, 0x71008bde3c and 0x71008bde58): it passes both buffers on, and setF32SetF32Array
// (20 floats) and setVec4SetVec4 (four floats, 0x71007a40f8 to 0x71007a4118) read them, so the uninitialised read is the game's own and they stay uninitialised here.
// The height of the second pass is read inside the loop: a local for it moves three of the zero stores.
void DrPixlPostObjMotionBlur2::calcMaxVelocityPerTile() {
  DrAPCache *apCache = m_drMan->m_drAPCache;
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x40);
  shdList->unknown002(shader);
  DrAPGxType::setupBlend(0);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 sizeOffset = uniform.unknown001("size");
  u32 ofsOffset = uniform.unknown001("ofs[0]");
  apCache->beginTexSampling(2, 1);
  unknown40->setRenderTarget();
  apCache->setTexture(*unknown28->unknown70, location);
  mm::Vec4 size;
  size.x = 1.0f / static_cast<f32>(unknown40->unknownbc);
  size.y = 1.0f / static_cast<f32>(unknown40->unknownc0);
  uniform.setVec4SetVec4(sizeOffset, size);
  f32 ofs[20];
  f32 width = static_cast<f32>(unknown28->unknownbc);
  for (int i = 0; i < 5; i++) {
    ofs[i * 4] = static_cast<f32>(i) / width;
    ofs[i * 4 + 1] = 0.0f;
  }
  uniform.setF32SetF32Array(ofsOffset, ofs, 20);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  uniform.unknown20.Rebuilding();
  static_cast<grlib::CGLibUniBaseUtility &>(uniform).setMoveMem();
  unknown40->setColorInvalidate();
  unknown38->setRenderTarget();
  apCache->setTexture(*unknown30->unknown70, location);
  size.x = 1.0f / static_cast<f32>(unknown38->unknownbc);
  size.y = 1.0f / static_cast<f32>(unknown38->unknownc0);
  uniform.setVec4SetVec4(sizeOffset, size);
  for (int i = 0; i < 5; i++) {
    ofs[i * 4] = 0.0f;
    ofs[i * 4 + 1] = static_cast<f32>(i) / static_cast<f32>(unknown40->unknownc0);
  }
  uniform.setF32SetF32Array(ofsOffset, ofs, 20);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  unknown38->setColorInvalidate();
}

// 0x71008be01c. The game writes only the x and y of the Vec4 it passes (stores at sp and sp+4, 0x71008be118 and 0x71008be134): setVec4SetVec4 copies all four floats
// (0x71007a40f8 to 0x71007a4118), so the read of z and w is the game's own and they stay uninitialised here.
void DrPixlPostObjMotionBlur2::calcBlurMask() {
  DrAPCache *apCache = m_drMan->m_drAPCache;
  DrShdDataList *shdList = m_drMan->m_drShdMan->m_drShdDataList;
  DrShdDataObj *shader = shdList->getPostShdObj(0x49);
  shdList->unknown002(shader);
  DrAPGxType::setupBlend(0);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 vOfs = uniform.unknown001("vOfs");
  apCache->beginTexSampling(2, 1);
  unknown48->setRenderTarget();
  apCache->setTexture(*unknown38->unknown70, location);
  mm::Vec4 offset;
  offset.x = 0.5f / static_cast<f32>(unknown48->unknownbc);
  offset.y = 0.5f / static_cast<f32>(unknown48->unknownc0);
  uniform.setVec4SetVec4(vOfs, offset);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  unknown48->setColorInvalidate();
}

} // namespace ml
