#include "dr/dr_shd_lgt_global_ibl.h"

#include <algorithm> // IWYU pragma: keep
#include <math.h>
#include <string.h>

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_light_obj_global_ibl.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_lgt_obj.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"
#include "types.h"

namespace ml {

namespace _dr_shd_lgt_glb_ibl {

bool CompareByPriority(const DrLightObjGlobalIBL *a, const DrLightObjGlobalIBL *b) {
  u32 priorityA = a->getPriority();
  u32 priorityB = b->getPriority();
  return priorityA > priorityB;
}

} // namespace _dr_shd_lgt_glb_ibl

DrShdLgtGlobalIBL::~DrShdLgtGlobalIBL() {
  for (int i = 0; i < 4; i++) {
    unknown001 &view = unknown10[i];
    if (view.unknown2048 != nullptr) {
      delete view.unknown2048;
      view.unknown2048 = nullptr;
    }
    view.unknown00.unknown001();
  }
}

void DrShdLgtGlobalIBL::delViewInfo(int viewNum) {}

void DrShdLgtGlobalIBL::resetColorBuff(int index) {
  if (m_drMan->unknown120[index]->unknownfe4 == 3) {
    unknown10[index].unknown2050 = true;
  }
}

bool DrShdLgtGlobalIBL::isEnable() const { return unknown10[m_drMan->unknown1c98].unknown00.size() > 0; }

void DrShdLgtGlobalIBL::setUniformBlock(u32 index) const { unknown10[m_drMan->unknown1c98].unknown2048->setUniformBlock(index); }

void DrShdLgtGlobalIBL::setStorageBuffer(u32 index) const { unknown10[m_drMan->unknown1c98].unknown2048->setStorageBuffer(index); }

const mm::Mat44 &DrShdLgtGlobalIBL::getSHMatrix(u32 row, u32 column) const {
  const unknown001 &view = unknown10[m_drMan->unknown1c98];
  return view.unknown340[row * 3 + column];
}

void DrShdLgtGlobalIBL::updateUB_ShMatrixList(u8 *work, int viewNum) { grlib::ShdMat44TransposeMat44Array(reinterpret_cast<f32 *>(work), unknown10[viewNum].unknown340, 0x60); }

void DrShdLgtGlobalIBL::updateUB_ToProxySpace(u8 *work, int viewNum) {
  unknown001 &view = unknown10[viewNum];
  for (int i = 0; i < 32; i++) {
    const DrLightObjGlobalIBL *obj = view.unknown40[i].m_drLightObjGlobalIBL;
    grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(work), obj == nullptr ? mm::Mat44::identity : obj->unknown3d0);
    work += sizeof(mm::Mat44);
  }
}

void DrShdLgtGlobalIBL::getSHAverage(mm::Vec3 &average, u32 index) const {
  const unknown001 &view = unknown10[m_drMan->unknown1c98];
  average.x = view.unknown340[index * 3].rows[3][3];
  average.y = view.unknown340[index * 3 + 1].rows[3][3];
  average.z = view.unknown340[index * 3 + 2].rows[3][3];
  if (average.isError()) {
    average = mm::Vec3::zero;
  }
}

void DrShdLgtGlobalIBL::update(int viewNum) {
  if (viewNum == 0 || (viewNum > 0 && m_drMan->unknown059(viewNum))) {
    updateView(viewNum);
  }
}

void DrShdLgtGlobalIBL::updateUniformBlock(int viewNum) { updateUniformBlockImpl(viewNum); }

// The slot loops of render (0x7100895178) and renderGlobalIBL (0x71008954d8) are written with the exit test `i != 32`: the game steps one byte-offset induction
// variable (`add x8, x8, #24; cmp x8, #768; b.ne`, 0x7100895230 in render) and `i < 32` gives one instruction more in both (a `mul` of the index by 0x18 instead
// of the game's `madd`); the loop of removeObj (0x7100895024) matches either way and keeps `i < 32`. The tests of removeObj are written null, state, then the
// object (ruling 4): with the object compared before the state byte the first branch becomes `cmp x9, #0` instead of the game's `cbz x9`. The object is passed to
// cancelIBL as an id (`unsigned long` in the symbol), as DrRequetIBL stores it.
void DrShdLgtGlobalIBL::render(DrShdLgtMan *man) {
  if (m_drMan->unknown120[m_drMan->unknown1c98]->unknown269) {
    renderIndexTable();
    renderLinkList(man);
    const unknown001 &view = unknown10[m_drMan->unknown1c98];
    for (int i = 0; i != 32; i++) {
      const unknown002 &slot = view.unknown40[i];
      if (slot.m_drLightObjGlobalIBL != nullptr && slot.unknown04[(slot.unknown08 + 2) % 3] != 3 && (slot.unknown04[0] == 2 || slot.unknown04[1] == 2 || slot.unknown04[2] == 2)) {
        grlib::CGLibCtlShader::setMemoryBarrierBit(2);
        renderByLinkList(man);
        return;
      }
    }
  }
}

void DrShdLgtGlobalIBL::renderGlobalIBL(DrShdLgtMan *man) {
  renderLinkList(man);
  const unknown001 &view = unknown10[m_drMan->unknown1c98];
  for (int i = 0; i != 32; i++) {
    const unknown002 &slot = view.unknown40[i];
    if (slot.m_drLightObjGlobalIBL != nullptr && slot.unknown04[(slot.unknown08 + 2) % 3] != 3 && (slot.unknown04[0] == 2 || slot.unknown04[1] == 2 || slot.unknown04[2] == 2)) {
      grlib::CGLibCtlShader::setMemoryBarrierBit(2);
      renderByLinkList(man);
      return;
    }
  }
}

void DrShdLgtGlobalIBL::getLowestPrioritySH(mm::Mat44 &red, mm::Mat44 &green, mm::Mat44 &blue) const {
  const unknown001 &view = unknown10[m_drMan->unknown1c98];
  int index = -1;
  for (DrLightObjGlobalIBL *const *it = view.unknown1b40.end(); it != view.unknown1b40.begin(); --it) {
    const unknown002 &slot = view.unknown40[0];
    if (slot.m_drLightObjGlobalIBL == nullptr) {
      break;
    }
    if (slot.m_drLightObjGlobalIBL == it[-1] && slot.unknown04[(slot.unknown08 + 2) % 3] != 3 && (slot.unknown04[0] == 2 || slot.unknown04[1] == 2 || slot.unknown04[2] == 2)) {
      index = slot.unknown00;
    }
  }
  if (index != -1) {
    red = view.unknown340[index * 3];
    green = view.unknown340[index * 3 + 1];
    blue = view.unknown340[index * 3 + 2];
  } else {
    memset(&red, 0, sizeof(mm::Mat44));
    memset(&green, 0, sizeof(mm::Mat44));
    memset(&blue, 0, sizeof(mm::Mat44));
  }
}

void DrShdLgtGlobalIBL::addObj(DrLightObjGlobalIBL *obj, int viewNum) { unknown10[viewNum].unknown00.push_back(obj); }

void DrShdLgtGlobalIBL::removeObj(DrLightObjGlobalIBL *obj, int viewNum) {
  for (int i = 0; i < 32; i++) {
    const unknown002 &slot = unknown10[viewNum].unknown40[i];
    if (slot.m_drLightObjGlobalIBL != nullptr && slot.unknown04[(slot.unknown08 + 2) % 3] != 3 && slot.m_drLightObjGlobalIBL == obj) {
      DrPixlPostObjCubeMapMultiIBL *cubeMap = m_drMan->m_drPixlMan->unknown10[viewNum].m_drPixlPostMan->m_drPixlPostObjCubeMapMultiIBL;
      if (cubeMap != nullptr) {
        cubeMap->cancelIBL(reinterpret_cast<u64>(obj));
      }
    }
  }
  mm::mtl::List<DrLightObjGlobalIBL *> &list = unknown10[viewNum].unknown00;
  for (mm::mtl::List<DrLightObjGlobalIBL *>::iterator it = list.begin(), end = list.end(); it != end;) {
    mm::mtl::List<DrLightObjGlobalIBL *>::iterator next = it;
    ++next;
    if (*it == obj) {
      list.erase(it);
    }
    it = next;
  }
}

void DrShdLgtGlobalIBL::setShaderGlobalIBLListFadeParameter(DrShdLgtObj *shader, u32 index, const mm::Mat44 &world, const mm::Vec4 &fadeMul, const mm::Vec4 &fadeCenter,
                                                            grlib::CGLibDblUniformBlock &block, u32 blockIndex) {
  u8 *buffer = static_cast<u8 *>(block.getBuff());
  DrCalcViewWork *viewWork = m_drMan->m_drCalcMan->m_drCalcViewWork;
  u32 offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gWVP");
  if (offset != 0xffffffff) {
    mm::Mat44 worldViewProj;
    worldViewProj.unknown009(world, viewWork->unknown200);
    grlib::ShdMat44SetMat44(reinterpret_cast<f32 *>(buffer + offset), worldViewProj);
  }
  offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gIndex");
  if (offset != 0xffffffff) {
    int indexValue[4] = {};
    indexValue[0] = index;
    grlib::ShdS32SetIVec4(reinterpret_cast<int *>(buffer + offset), indexValue);
  }
  u32 widthValue;
  u32 heightValue;
  if (m_drMan->isIBLHalfRes()) {
    widthValue = m_drMan->m_drPixlMan->getPixlObj(10)->unknownbc;
    heightValue = m_drMan->m_drPixlMan->getPixlObj(10)->unknownc0;
  } else {
    widthValue = m_drMan->m_drPixlMan->getPixlObj(14)->unknownbc;
    heightValue = m_drMan->m_drPixlMan->getPixlObj(14)->unknownc0;
  }
  f32 width = static_cast<f32>(widthValue);
  f32 height = static_cast<f32>(heightValue);
  offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gFragToUV");
  if (offset != 0xffffffff) {
    mm::Vec4 value;
    value.x = 1.0f / width;
    value.y = 1.0f / height;
    value.z = 0.0f;
    value.w = 0.0f;
    grlib::ShdVec4SetVec4(reinterpret_cast<f32 *>(buffer + offset), value);
  }
  offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gFragToScreen");
  if (offset != 0xffffffff) {
    mm::Vec4 value;
    value.x = 2.0f / width;
    value.y = -2.0f / height;
    value.z = -1.0f;
    value.w = 1.0f;
    grlib::ShdVec4SetVec4(reinterpret_cast<f32 *>(buffer + offset), value);
  }
  offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gScreenToViewPos");
  if (offset != 0xffffffff) {
    mm::Vec4 value;
    value.y = tanf(viewWork->unknown4c4 * 0.5f);
    value.x = value.y * viewWork->unknown4c0;
    value.w = 0.0f;
    value.z = 0.0f;
    grlib::ShdVec4SetVec4(reinterpret_cast<f32 *>(&buffer[offset]), value);
  }
  offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gToLocal");
  if (offset != 0xffffffff) {
    mm::Mat44 toLocal = viewWork->unknown00;
    mm::Mat44 inverse;
    inverse.unknown014(world);
    toLocal.unknown009(toLocal, inverse);
    grlib::ShdMat44SetMat44(reinterpret_cast<f32 *>(buffer + offset), toLocal);
  }
  offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gFadeParamMul");
  if (offset != 0xffffffff) {
    grlib::ShdVec4SetVec4(reinterpret_cast<f32 *>(&buffer[offset]), fadeMul);
  }
  offset = (shader->unknown38 + shader->unknown58)->getUniformBlockValOfs(blockIndex, "gFadeParamCenter");
  if (offset != 0xffffffff) {
    grlib::ShdVec4SetVec4(reinterpret_cast<f32 *>(buffer + offset), fadeCenter);
  }
  u32 depLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDep");
  DrAPCache *apCache = m_drMan->m_drAPCache;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*m_drMan->m_drPixlMan->getPixlObj(4)->unknown70, depLocation);
}

// 0x7100898274 (487 instructions). `view` is the alias of `unknown10[viewIndex]` that the other functions of this unit take (getSHMatrix, getSHAverage, getLowestPrioritySH...) and is used
// by the loop bounds, the stencil argument, hasNext and the fade call. Measured without it (`unknown10[viewIndex]` written out) or with `pixlMan` declared before `viewIndex`: 487
// instructions, the one difference being x19 and x23 swapped between pixlMan and viewIndex (0x71008982a0); with the alias taken right after viewIndex the registers are the game's.
void DrShdLgtGlobalIBL::renderDirect(DrShdLgtMan *man) {
  int viewIndex = m_drMan->unknown1c98;
  const unknown001 &view = unknown10[viewIndex];
  DrPixlMan *pixlMan = m_drMan->m_drPixlMan;
  {
    int clearColor[4] = {0, 0, 0, 0};
    pixlMan->unknown7f0->unknown1e8->clearIntTexture(clearColor, static_cast<GrlClaerMask>(0xf));
    pixlMan->unknown7f0->unknown1e0->clearIntTexture(clearColor, static_cast<GrlClaerMask>(0xf));
  }
  DrPixlRenderTarget *target = m_drMan->m_drPixlMan->getPixlObj(14);
  DrPixlRenderTarget *second = m_drMan->m_drPixlMan->getPixlObj(9);
  target->setRenderTarget(*pixlMan->getDepthObj()->unknown120, *second);
  for (s64 i = 0; i < static_cast<int>(view.unknown1b40.size()); i++) {
    DrLightObjGlobalIBL *obj = view.unknown1b40[i];
    for (u32 j = 0; j < obj->unknown18; j++) {
      obj->bindVertex(j);
      grlib::CGLibColorCtl::setColorBufferOff();
      DrAPGxType::setupCullingFront();
      DrAPGxType::setupStencilTestWriteMask(true, false, i == view.unknown1b40.size() - 1 ? 7 : 6, true, 0x40, 0x40, 0x40, 7, 2, 0, 0);
      DrShdLgtObj *shader = man->getGlobalIBLShader(DrShdLgtMan::GIBL_SHADER_TYPE_UNKNOWN_0);
      shader->setDeclarationIdx(shader->getDeclarationOfs("USE_PIXL_COUNTER"), 2);
      man->setupGlobalIBLShader(shader);
      {
        grlib::CGLibUniformEtcUtility uniform(shader);
        uniform.setUseUniformBlock("UB_VS");
        shader->setShaderGlobalIBLIndexVS(m_drMan, obj->unknown20[j].unknown50, uniform.getBuff(), (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("UB_VS"));
        uniform.updateData();
        uniform.setUniformBlock();
        obj->drawVertex();
      }
      bool hasNext = m_drMan->unknown120[m_drMan->unknown1c98]->unknown105f && i != view.unknown1b40.size() - 1;
      obj->beginOccQuery();
      grlib::CGLibColorCtl::setColorBufferOn();
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_UNKNOWN_8, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      DrAPGxType::setupCullingBack();
      DrAPGxType::setupStencilTestWriteMask(true, false, 3, true, 0x40, 0x40, 0x40, 2, 1, 1, 1);
      u8 fadeDir = obj->unknown20[j].unknown11a;
      u8 fadeShape = obj->unknown20[j].unknown11b;
      u8 fadePos = obj->unknown20[j].unknown11c;
      bool fadeInvert = obj->unknown20[j].unknown11d;
      shader = man->getGlobalIBLShader(DrShdLgtMan::GIBL_SHADER_TYPE_UNKNOWN_3);
      shader->setDeclarationIdx(shader->getDeclarationOfs("FADE_SHAPE"), fadeShape);
      u32 fadeDirIndex = hasNext ? fadeDir + 1 : 1;
      shader->setDeclarationIdx(shader->getDeclarationOfs("FADE_DIR"), fadeDirIndex);
      u32 fadeInvertIndex = fadeInvert ? 1 : 2;
      shader->setDeclarationIdx(shader->getDeclarationOfs("FADE_INVERT"), fadeInvertIndex);
      u32 fadePosIndex = fadePos + 1;
      shader->setDeclarationIdx(shader->getDeclarationOfs("FADE_POS"), fadePosIndex);
      man->setupGlobalIBLShader(shader);
      {
        grlib::CGLibUniformEtcUtility viewUniform(shader);
        viewUniform.setUseUniformBlock("UB_VS");
        grlib::CGLibUniformEtcUtility fadeUniform(shader);
        fadeUniform.setUseUniformBlock("UB_PS");
        setShaderGlobalIBLDirectFadeParameter(shader, view.unknown003(i), obj->unknown20[j].unknown50, obj->unknown20[j].unknown130, obj->unknown20[j].unknown140, viewUniform, fadeUniform);
        viewUniform.updateData();
        viewUniform.setUniformBlock();
        fadeUniform.updateData();
        fadeUniform.setUniformBlock();
        grlib::CGLibCtlTexture::setUAVTexture(*pixlMan->unknown7f0->unknown1e8->unknown70, 0, 0, 0);
      }
      obj->drawVertex();
      DrAPGxType::setupCullingFront();
      DrAPGxType::setupStencilTestWriteMask(false, false, 3, true, 0x40, 0x40, 0x40, 2, 1, 1, 1);
      obj->drawVertex();
      obj->endOccQuery();
    }
  }
  grlib::CGLibColorCtl::setColorBufferOn();
  DrAPGxType::setupCullingBack();
}
} // namespace ml

template mm::mtl::FixedList<ml::DrShdLgtGlobalIBL::SlotCandidate, 32>::iterator
    mm::mtl::FixedList<ml::DrShdLgtGlobalIBL::SlotCandidate, 32>::erase(mm::mtl::FixedList<ml::DrShdLgtGlobalIBL::SlotCandidate, 32>::iterator);

// Temporary device: the game emits this instantiation in this unit, from the std::sort of DrShdLgtGlobalIBL::updateView (1.0.0: 0x710089428c, `bl` at 0x7100894a1c), which is not
// reconstructed yet. It also instantiates __sort4, __insertion_sort_3 and __insertion_sort_incomplete. Measured: __sort (0x710089a214) 388 instructions, __sort4 (0x710089a824) 95,
// __insertion_sort_3 76 and __insertion_sort_incomplete 203, all MATCH. Replace it with the std::sort call when updateView is reconstructed in this file, and delete this line.
template void std::__sort<bool (*&)(const ml::DrLightObjGlobalIBL *, const ml::DrLightObjGlobalIBL *), ml::DrLightObjGlobalIBL **>(ml::DrLightObjGlobalIBL **, ml::DrLightObjGlobalIBL **,
                                                                                                                                   bool (*&)(const ml::DrLightObjGlobalIBL *,
                                                                                                                                             const ml::DrLightObjGlobalIBL *));
