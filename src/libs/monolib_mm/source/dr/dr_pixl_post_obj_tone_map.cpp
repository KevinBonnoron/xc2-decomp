#include "dr/dr_pixl_post_obj_tone_map.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_format.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_mem_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_vec4.h"
#include "mtl/alloc_handle.h"

namespace ml {

void DrPixlPostObjToneMap::update() {
  if (unknown00->unknown058()) {
    return;
  }
  if ((unknownb4 & 0x10) != 0) {
    updateByCompute();
  } else {
    updateByRenderTarget();
  }
}

DrPixlPostObjToneMap::DrPixlPostObjToneMap(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan), unknownb0(1.0f), unknownb4(0x10), unknownb8(0) {
  for (s32 i = 0; i < 6; i++) {
    unknown18[i] = new (unknown00->unknown0c) DrPixlRenderTarget(drMan);
  }
  unknown48.setup(0x10);
  unknown70.setup(0x10);
  unknown98 = new (unknown00->unknown0c) DrPixlRenderTarget(drMan);
  unknowna0 = new (unknown00->unknown0c) DrPixlRenderTarget(drMan);
  unknowna8 = unknown98;
  unknown98->setTextureInfo(1.0f, 1.0f, DrAPCache::TEXTYPE_HALF_X1, false, 0);
  unknowna0->setTextureInfo(1.0f, 1.0f, DrAPCache::TEXTYPE_HALF_X1, false, 0);
  for (s32 i = 0; i < 6; i++) {
    unknown18[i]->setTextureInfo(
        static_cast<f32>(128 >> i), static_cast<f32>(128 >> i), DrPixlFormat::s_ToneMapFormat, true, (DrPixlMemMan::get()->unknown010 + DrMan::getIns()->unknown1c98)->unknown19c[i]);
  }
}

DrPixlPostObjToneMap::~DrPixlPostObjToneMap() {
  for (s32 i = 0; i < 6; i++) {
    unknown001(unknown18[i]);
  }
  unknown001(unknown98);
  unknown001(unknowna0);
  unknown48.release();
  unknown70.release();
}

void DrPixlPostObjToneMap::createMeasureLuminance() {
  if ((unknownb4 & 0x10) == 0) {
    creaetMeasureLuminaceByRenderTarget();
  } else {
    createMeasureLuminanceByCompute();
  }
}

void DrPixlPostObjToneMap::createSclDow() {
  unknown18[0]->setRenderTarget();
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0);
  shdList->bindQuadsTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 paramOffset = uniform.unknown001("gParam");
  mm::Vec4 param = mm::Vec4::zero;
  param.x = unknown00->unknown588->getSkyLuminance();
  uniform.setVec4SetVec4(paramOffset, param);
  uniform.updateData();
  uniform.setUniformBlock();
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDownDepth");
  DrPixlRenderTarget *colorBuff = unknown08->unknown7f0->unknown138;
  DrPixlRenderTarget *downDepth = unknown08->unknown7f0->unknown180->getDownDepth();
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*colorBuff->unknown70, location);
  apCache->setTexture(*downDepth->unknown70, depthLocation);
  shdList->renderQuads();
  unknown18[0]->setColorInvalidate();
}

void DrPixlPostObjToneMap::createMeasureLuminanceByCompute() {
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(1);
  DrAPCache *apCache = unknown00->unknown5c0;
  wkPixlManRes *res = unknown08->unknown7f0;
  f32 offsets[32];
  f32 toneAveMin = res->unknown194;
  f32 toneAveMax = res->unknown198;
  f32 range[4] = {toneAveMin, toneAveMax, 0.0f, 0.0f};
  f32 size = 128.0f;
  for (int i = 0; i < 5; i++) {
    f32 tu = 1.0f / size;
    f32 scale = (size - 1.0f) / size;
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < 2; y++) {
        offsets[(x * 2 + y) * 2] = scale * (tu * static_cast<f32>(x) + tu * static_cast<f32>(x) - tu);
        offsets[(x * 2 + y) * 2 + 1] = scale * (tu * static_cast<f32>(y) + tu * static_cast<f32>(y) - tu);
      }
    }
    unknown18[i + 1]->setRenderTarget();
    shdList->bindQuadsTex();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
    u32 offsetsOffset = uniform.unknown001("ofs[0]");
    u32 rangeOffset = uniform.unknown001("range");
    uniform.setF32SetF32Array(offsetsOffset, offsets, 8);
    uniform.setF32SetVec4(rangeOffset, range);
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*unknown18[i]->unknown70, location);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderQuads();
    unknown18[i + 1]->setColorInvalidate();
    size = size * 0.5f;
  }
  shader = shdList->getComputeObj(3);
  shader->setupComputeShader();
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  f32 tu = 1.0f / size;
  f32 scale = (size - 1.0f) / size;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      offsets[(x * 4 + y) * 2] = tu * 0.5f + scale * (tu + (tu * static_cast<f32>(x) + tu * static_cast<f32>(x)));
      offsets[(x * 4 + y) * 2 + 1] = tu * 0.5f + scale * (tu + (tu * static_cast<f32>(y) + tu * static_cast<f32>(y)));
    }
  }
  grlib::CGLibOneUniformBlock *block;
  if ((unknownb4 & 1) != 0) {
    block = &unknown48;
    unknownb4 |= 2;
  } else {
    block = &unknown70;
    unknownb4 |= 4;
  }
  u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 offsetsOffset = uniform.unknown001("ofs[0]");
  u32 rangeOffset = uniform.unknown001("range");
  uniform.setF32SetF32Array(offsetsOffset, offsets, 32);
  uniform.setF32SetVec4(rangeOffset, range);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown18[5]->unknown70, location);
  uniform.updateData();
  uniform.setUniformBlock();
  block->setStorageBuffer(0);
  grlib::CGLibCtlShader::setDispatchCompute(1, 1, 1);
  grlib::CGLibCtlShader::setMemoryBarrier();
}

void DrPixlPostObjToneMap::creaetMeasureLuminaceByRenderTarget() {
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(1);
  DrAPCache *apCache = unknown00->unknown5c0;
  wkPixlManRes *res = unknown08->unknown7f0;
  f32 offsets[32];
  f32 toneAveMin = res->unknown194;
  f32 toneAveMax = res->unknown198;
  f32 range[4] = {toneAveMin, toneAveMax, 0.0f, 0.0f};
  f32 size = 128.0f;
  for (int i = 0; i < 5; i++) {
    f32 tu = 1.0f / size;
    f32 scale = (size - 1.0f) / size;
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < 2; y++) {
        offsets[(x * 2 + y) * 2] = scale * (tu * static_cast<f32>(x) + tu * static_cast<f32>(x) - tu);
        offsets[(x * 2 + y) * 2 + 1] = scale * (tu * static_cast<f32>(y) + tu * static_cast<f32>(y) - tu);
      }
    }
    unknown18[i + 1]->setRenderTarget();
    shdList->bindQuadsTex();
    shader->setupShader(0u);
    grlib::CGLibUniformEtcUtility uniform(shader);
    uniform.setUseUniformBlock("U_POST");
    u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
    u32 offsetsOffset = uniform.unknown001("ofs[0]");
    u32 rangeOffset = uniform.unknown001("range");
    uniform.setF32SetF32Array(offsetsOffset, offsets, 8);
    uniform.setF32SetVec4(rangeOffset, range);
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*unknown18[i]->unknown70, location);
    uniform.updateData();
    uniform.setUniformBlock();
    shdList->renderQuads();
    unknown18[i + 1]->setColorInvalidate();
    grlib::CGLibCtlShader::setMemoryBarrierBit(2);
    size = size * 0.5f;
  }
  shader = shdList->getPostShdObj(0x3b);
  shdList->bindShdVertex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  f32 tu = 1.0f / size;
  f32 scale = (size - 1.0f) / size;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      offsets[(x * 4 + y) * 2] = tu * 0.5f + scale * (tu + (tu * static_cast<f32>(x) + tu * static_cast<f32>(x)));
      offsets[(x * 4 + y) * 2 + 1] = tu * 0.5f + scale * (tu + (tu * static_cast<f32>(y) + tu * static_cast<f32>(y)));
    }
  }
  grlib::CGLibRenderTarget *target;
  if ((unknownb4 & 1) != 0) {
    target = unknown98;
    unknownb4 |= 2;
  } else {
    target = unknowna0;
    unknownb4 |= 4;
  }
  target->setRenderTarget();
  u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 offsetsOffset = uniform.unknown001("ofs[0]");
  u32 rangeOffset = uniform.unknown001("range");
  uniform.setF32SetF32Array(offsetsOffset, offsets, 32);
  uniform.setF32SetVec4(rangeOffset, range);
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown18[5]->unknown70, location);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  target->setColorInvalidate();
  unknowna8 = target;
}

} // namespace ml
