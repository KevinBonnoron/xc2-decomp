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
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_math/mm_col4.h"
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
  unknown28 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown30 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown38 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown48 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown40 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown20 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  for (s32 i = 0; i < 2; i++) {
    unknown50[i] = new (unknown00->unknown0c) grlib::CGLibVtxVertex();
  }
  calcBludBuffColorBuff();
  unknown18 = 0.0f;
  unknown1c = 0.0f;
}

void DrPixlPostObjMotionBlur2::calcBludBuffColorBuff() {
  f32 height = static_cast<f32>(unknown00->unknown5b8->unknown1c);
  f32 width = static_cast<f32>(unknown00->unknown5b8->unknown18);
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
  if (unknown00->unknown120[unknown00->unknown1c98]->isMotBlur2() && unknown00->unknown120[unknown00->unknown1c98]->unknown1000) {
    s32 width = unknown00->unknown5b8->unknown28;
    s32 height = unknown00->unknown5b8->unknown2c;
    unknown00->unknown78->debugRender(*unknown48->unknown70, 0, 0, width, height, false, false, 0.2f, true);
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

void DrPixlPostObjMotionBlur2::calcObjMotionBlur() {
  if (!unknown00->unknown580->unknown10->unknown9aa && unknown00->unknown120[unknown00->unknown1c98]->unknown1cd) {
    calcVelocityBlur();
  }
  unknown00->blurCallBackRender();
  calcMaxVelocityPerTile();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  calcBlurMask();
}

void DrPixlPostObjMotionBlur2::lastRender() {
  DrPixlRenderTarget *target = unknown08->unknown7f0->unknown138;
  target->setRenderTarget();
  DrAPGxType::setupBlend(1);
  DrShdDataObj *shader = unknown00->unknown80->unknown00->getPostShdObj(0x46);
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
  DrAPCache *apCache = unknown00->unknown5c0;
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
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
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
  DrPixlRenderTarget *target = unknown08->unknown7f0->unknown138;
  DrAPCache *apCache = unknown00->unknown5c0;
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
  apCache->setTexture(*unknown08->unknown7f0->unknown138->unknown70, frameLocation);
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

} // namespace ml
