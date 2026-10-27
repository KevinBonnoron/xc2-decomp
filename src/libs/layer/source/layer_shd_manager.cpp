#include "layer/layer_shd_manager.h"

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_texture.h"
#include "layer/layer_handle_allocator.h"
#include "layer/layer_res_sec_texture.h"
#include "layer/layer_vertex_obj.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {

void LayerShdManager::setupShader() { (this->*s_CallSelect[unknown4f0])(); }

grlib::CGLibDecShader *LayerShdManager::selectGamma() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  if (index != unknown4fe) {
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[index]]);
    unknown4fe = unknown4f0;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectFlowMap() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  if (index != unknown4fe) {
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[index]]);
    unknown4fe = unknown4f0;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectGsBlur() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  unknown001 &entry = unknown48[index];
  if (index != unknown4fe || unknown4f8 != unknown506) {
    shader->setDeclarationIdx(entry.unknown06, unknown4f8);
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
    unknown4fe = unknown4f0;
    unknown506 = unknown4f8;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectTest() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  unknown001 &entry = unknown48[index];
  if (index == unknown4fe && unknown506 == unknown4f8) {
    return shader;
  }
  shader->setDeclarationIdx(entry.unknown06, unknown4f8);
  grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
  unknown4fe = unknown4f0;
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectMemWrite() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  if (index == unknown4fe && unknown506 == unknown4f8) {
    return shader;
  }
  shader->setDeclarationIdx(unknown48[index].unknown06, unknown4f8);
  grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
  unknown4fe = unknown4f0;
  unknown506 = unknown4f8;
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectDebug() {
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(unknown4f0);
  unknown001 &entry = unknown48[unknown4f0];
  if (unknown4f0 != unknown4fe || unknown4f4 != unknown502 || unknown506 != unknown4f8) {
    shader->setDeclarationIdx(entry.unknown02, unknown4f4);
    shader->setDeclarationIdx(entry.unknown06, unknown4f8);
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
    unknown4fe = unknown4f0;
    unknown502 = unknown4f4;
    unknown506 = unknown4f8;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectFont() {
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(unknown4f0);
  unknown001 &entry = unknown48[unknown4f0];
  if (unknown4f0 != unknown4fe || unknown504 != unknown4f6 || unknown4f4 != unknown502 || unknown508 != unknown4fa) {
    shader->setDeclarationIdx(entry.unknown02, unknown4f4);
    shader->setDeclarationIdx(entry.unknown04, unknown4f6);
    shader->setDeclarationIdx(entry.unknown08, unknown4fa);
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
    if (unknown350 != nullptr) {
      unknown350->setUniformBlock(1);
    }
    unknown4fe = unknown4f0;
    unknown502 = unknown4f4;
    unknown504 = unknown4f6;
    unknown508 = unknown4fa;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectNumber() {
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(unknown4f0);
  unknown001 &entry = unknown48[unknown4f0];
  if (unknown4f0 != unknown4fe || unknown4f4 != unknown502 || unknown508 != unknown4fa || unknown50a != unknown4fc) {
    shader->setDeclarationIdx(entry.unknown02, unknown4f4);
    shader->setDeclarationIdx(entry.unknown08, unknown4fa);
    shader->setDeclarationIdx(entry.unknown0a, unknown4fc);
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
    if (unknown350 != nullptr) {
      unknown350->setUniformBlock(1);
    }
    unknown4fe = unknown4f0;
    unknown508 = unknown4fa;
    unknown502 = unknown4f4;
    unknown50a = unknown4fc;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectPoly() {
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(unknown4f0);
  unknown001 &entry = unknown48[unknown4f0];
  if (unknown4f0 == unknown4fe && unknown4f4 == unknown502 && unknown506 == unknown4f8 && unknown508 == unknown4fa && unknown50a == unknown4fc) {
    return shader;
  }
  shader->setDeclarationIdx(entry.unknown02, unknown4f4);
  shader->setDeclarationIdx(entry.unknown06, unknown4f8);
  shader->setDeclarationIdx(entry.unknown08, unknown4fa);
  shader->setDeclarationIdx(entry.unknown0a, unknown4fc);
  grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
  unknown4fe = unknown4f0;
  unknown502 = unknown4f4;
  unknown506 = unknown4f8;
  unknown508 = unknown4fa;
  unknown50a = unknown4fc;
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectWin() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  unknown001 &entry = unknown48[index];
  if (index != unknown4fe || unknown500 != unknown4f2 || unknown4f4 != unknown502 || unknown508 != unknown4fa || unknown50a != unknown4fc) {
    shader->setDeclarationIdx(entry.unknown00, unknown4f2);
    shader->setDeclarationIdx(entry.unknown02, unknown4f4);
    shader->setDeclarationIdx(entry.unknown08, unknown4fa);
    shader->setDeclarationIdx(entry.unknown0a, unknown4fc);
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
    if (unknown350 != nullptr) {
      unknown350->setUniformBlock(1);
    }
    unknown4fe = unknown4f0;
    unknown500 = unknown4f2;
    unknown508 = unknown4fa;
    unknown502 = unknown4f4;
    unknown50a = unknown4fc;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectIcon() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  unknown001 &entry = unknown48[index];
  if (index != unknown4fe || unknown500 != unknown4f2 || unknown4f4 != unknown502 || unknown508 != unknown4fa || unknown50a != unknown4fc) {
    shader->setDeclarationIdx(entry.unknown00, unknown4f2);
    shader->setDeclarationIdx(entry.unknown02, unknown4f4);
    shader->setDeclarationIdx(entry.unknown08, unknown4fa);
    shader->setDeclarationIdx(entry.unknown0a, unknown4fc);
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
    if (unknown350 != nullptr) {
      unknown350->setUniformBlock(1);
    }
    unknown4fe = unknown4f0;
    unknown500 = unknown4f2;
    unknown508 = unknown4fa;
    unknown502 = unknown4f4;
    unknown50a = unknown4fc;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectColor() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  unknown001 &entry = unknown48[index];
  if (index == unknown4fe && unknown500 == unknown4f2 && unknown4f4 == unknown502 && unknown508 == unknown4fa && unknown506 == unknown4f8 && unknown50a == unknown4fc) {
    return shader;
  }
  shader->setDeclarationIdx(entry.unknown00, unknown4f2);
  shader->setDeclarationIdx(entry.unknown02, unknown4f4);
  shader->setDeclarationIdx(entry.unknown08, unknown4fa);
  shader->setDeclarationIdx(entry.unknown06, unknown4f8);
  shader->setDeclarationIdx(entry.unknown0a, unknown4fc);
  grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
  if (unknown350 != nullptr) {
    unknown350->setUniformBlock(1);
  }
  unknown4fe = unknown4f0;
  unknown500 = unknown4f2;
  unknown502 = unknown4f4;
  unknown508 = unknown4fa;
  unknown506 = unknown4f8;
  unknown50a = unknown4fc;
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectTex() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown220 + static_cast<u32>(index);
  unknown001 &entry = unknown48[index];
  if (index == unknown4fe && unknown500 == unknown4f2 && unknown4f4 == unknown502 && unknown508 == unknown4fa && unknown506 == unknown4f8 && unknown50a == unknown4fc) {
    return shader;
  }
  shader->setDeclarationIdx(entry.unknown00, unknown4f2);
  shader->setDeclarationIdx(entry.unknown02, unknown4f4);
  shader->setDeclarationIdx(entry.unknown08, unknown4fa);
  shader->setDeclarationIdx(entry.unknown06, unknown4f8);
  shader->setDeclarationIdx(entry.unknown0a, unknown4fc);
  grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[unknown4f0]]);
  if (unknown350 != nullptr) {
    unknown350->setUniformBlock(1);
  }
  unknown4fe = unknown4f0;
  unknown500 = unknown4f2;
  unknown502 = unknown4f4;
  unknown508 = unknown4fa;
  unknown506 = unknown4f8;
  unknown50a = unknown4fc;
  return shader;
}

void LayerShdManager::allRelease() { shaderRelease(); }

void LayerShdManager::setupMainRenderTarget() { grlib::CGLibState::setMainFrameBuffer(); }

void LayerShdManager::createResWork() { grlib::CGLibTexture::createTextureImagePtrs(unknown368, unknown10, unknown18, false, nullptr, true); }

void LayerShdManager::setSecTexture(LayerResSecTexture *secTexture) {
  if (secTexture != nullptr && secTexture->unknown14 > 0.0f) {
    unknown58 = secTexture->getTexture();
    unknown60 = &secTexture->unknown18;
    unknown4fc = 2;
  } else {
    unknown58 = nullptr;
    unknown4fc = 1;
  }
}

void LayerShdManager::initColor(u32 index) {
  grlib::CGLibDecShader &shader = unknown220[index];
  unknown001 &entry = unknown48[index];
  entry.unknown00 = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initTex(u32 index) {
  grlib::CGLibDecShader &shader = unknown220[index];
  unknown001 &entry = unknown48[index];
  entry.unknown00 = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initFont(u32 index) {
  grlib::CGLibDecShader &shader = unknown220[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown04 = shader.getDeclarationOfs("MENU_ICON_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
}

void LayerShdManager::initWin(u32 index) {
  grlib::CGLibDecShader &shader = unknown220[index];
  unknown001 &entry = unknown48[index];
  entry.unknown00 = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initNumber(u32 index) {
  grlib::CGLibDecShader &shader = unknown220[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initPoly(u32 index) {
  grlib::CGLibDecShader &shader = unknown220[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_USE_TEX");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initMemWrite(u32 index) {
  unknown001 &entry = unknown48[index];
  entry.unknown06 = unknown220[index].getDeclarationOfs("MENU_DECODE_TYPE");
}

void LayerShdManager::initDebug(u32 index) {
  grlib::CGLibDecShader &shader = unknown220[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initGsBlur(u32 index) {
  unknown001 &entry = unknown48[index];
  entry.unknown06 = unknown220[index].getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initTest(u32 index) {
  unknown001 &entry = unknown48[index];
  entry.unknown06 = unknown220[index].getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::resetViewPort() {
  if (unknown528) {
    unknown360 = nullptr;
    unknown528 = false;
    unknown52a = false;
    unknown50c = 0.0f;
    unknown510 = 0.0f;
    unknown514 = unknown550;
    unknown518 = unknown554;
    grlib::CGLibState::setViewport(grlib::LibMainStateViewPort(0.0f, 0.0f, unknown550 * unknown55c, unknown554 * unknown560, 0.0f, 1.0f));
  }
}

void LayerShdManager::setShaderMaskOff() {
  unknown358 = nullptr;
  unknown50 = nullptr;
  unknown4fa = 1;
}

void LayerShdManager::setDepthBufferCheckOn() {
  if (!unknown529) {
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
    unknown529 = true;
  }
  unknown4f4 = 1;
  unknown350 = nullptr;
}

void LayerShdManager::setDepthBufferCheckOff() {
  if (unknown529) {
    grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_LESS);
    unknown529 = false;
  }
  unknown4f4 = 1;
  unknown350 = nullptr;
}

void LayerShdManager::set3DSpaceMode(grlib::CGLibDblUniformBlock *uniform) {
  if (!unknown529) {
    grlib::CGLibDepthCtl::setDepthControl(true, false, GRL_COMPARE_LEQUAL);
    unknown529 = true;
  }
  unknown4f4 = 2;
  unknown350 = uniform;
}

void LayerShdManager::setupTexture(const grlib::CGLibTextureBuffer &texture, LayerSamplerType type, u32 location) { grlib::CGLibCtlTexture::setTexture(texture, unknownc0[type], location); }

grlib::CGLibRenderTarget *LayerShdManager::getDefRenderTarget() {
  if (unknown360 != nullptr) {
    return unknown360;
  }
  return grlib::CGLibState::getMainRenderTarget();
}

void LayerShdManager::setupVertex(LayerVertexObj *vertex, u32 index) { vertex->setVertex(index); }

void LayerShdManager::setupVertex(LayerDefVertType type) { grlib::CGLibCtlVertex::setVertex(unknown238[type]); }

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxInstans &instance, u32 stride, u32 offset) { grlib::CGLibCtlVertex::setInstanceVertex(instance, stride, offset, 1, 1); }

void LayerShdManager::setupInstaceVertex(grlib::CGLibVtxOneInstans &instance, u32 stride, u32 offset) { grlib::CGLibCtlVertex::setInstanceVertex(instance, stride, offset, 1, 1); }

void LayerShdManager::renderQuadsIndex() { unknown300.drawIndex(); }

void LayerShdManager::renderInstaceQuadsIndex(u32 instanceCount) { unknown300.drawInsIndex(instanceCount); }

void LayerShdManager::renderLineQuadsIndex() { unknown328.drawIndex(); }

void LayerShdManager::setupBlendDef() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSwf() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendNo() { grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY); }

void LayerShdManager::setupBlendAdd() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendAddSwf() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSub() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendSubSwf() {
  grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_SUBTRACT, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::setupBlendMul() {
  grlib::CGLibColorCtl::setBlendControl(
      GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_COLOR, GRL_BLEND_COMBINE_ADD, GRL_BLEND_FUNC_ZERO, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
}

void LayerShdManager::initFlowMap(u32 index) {}

void LayerShdManager::initGamma(u32 index) {}

LayerHandleAllocator::LayerHandleAllocator() {}

LayerHandleAllocator::LayerHandleAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void LayerHandleAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { unknown08 = handle; }

mtl::ALLOC_HANDLE LayerHandleAllocator::getMemHandle() const { return unknown08; }

void *LayerHandleAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0); }

void LayerHandleAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

} // namespace layer
