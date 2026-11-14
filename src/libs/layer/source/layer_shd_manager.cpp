#include "layer/layer_shd_manager.h"

#include <string.h>

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_texture.h"
#include "layer/layer_handle_allocator.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_res_sec_texture.h"
#include "layer/layer_res_view_port_info.h"
#include "layer/layer_texture_obj.h"
#include "layer/layer_vertex_obj.h"
#include "ml/dev_file_th.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {
namespace {

// Inferred role: colored vertex of the default vertex buffers; original type name unknown.
struct unknown006 {
  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  u32 unknown08; // Inferred role: color; original member name unknown.
};

static_assert(sizeof(unknown006) == 0x0c, "");

// Inferred role: colored and textured vertex of the default vertex buffers; original type name unknown.
struct unknown007 {
  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  u32 unknown08; // Inferred role: color; original member name unknown.
  f32 unknown0c; // Inferred role: u; original member name unknown.
  f32 unknown10; // Inferred role: v; original member name unknown.
};

static_assert(sizeof(unknown007) == 0x14, "");

// Inferred role: textured vertex of the default vertex buffers; original type name unknown.
struct unknown008 {
  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  f32 unknown08; // Inferred role: u; original member name unknown.
  f32 unknown0c; // Inferred role: v; original member name unknown.
};

static_assert(sizeof(unknown008) == 0x10, "");

// Inferred role: unit quad with a color; original name unknown.
const unknown006 unknown009[4] = {
    {0.0f, 1.0f, 0xffffffff},
    {1.0f, 1.0f, 0xffffffff},
    {1.0f, 0.0f, 0xffffffff},
    {0.0f, 0.0f, 0xffffffff},
};

// Inferred role: unit quad with a color and texture coordinates; original name unknown.
const unknown007 unknown010[4] = {
    {0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f},
    {1.0f, 1.0f, 0xffffffff, 1.0f, 1.0f},
    {1.0f, 0.0f, 0xffffffff, 1.0f, 0.0f},
    {0.0f, 0.0f, 0xffffffff, 0.0f, 0.0f},
};

// Inferred role: unit quad with texture coordinates; original name unknown.
const unknown008 unknown011[4] = {
    {0.0f, 1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
};

// Inferred role: full screen quad with texture coordinates; original name unknown.
const unknown008 unknown012[4] = {
    {-1.0f, -1.0f, 0.0f, 1.0f},
    {1.0f, -1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {-1.0f, 1.0f, 0.0f, 0.0f},
};

// Inferred role: second unit quad with texture coordinates; original name unknown.
const unknown008 unknown013[4] = {
    {0.0f, 1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
};

// Inferred role: quad indices, closed for the line quads; original name unknown.
const u8 unknown014[5] = {0, 1, 2, 3, 0};

} // namespace

grlib::CGLibDecShader *LayerShdManager::setupShader() { return (this->*s_CallSelect[unknown4f0])(); }

grlib::CGLibDecShader *LayerShdManager::selectGamma() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
  if (index != unknown4fe) {
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[index]]);
    unknown4fe = unknown4f0;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectFlowMap() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
  if (index != unknown4fe) {
    grlib::CGLibCtlShader::setShader(*shader, unknown70[s_eFetchTbl[index]]);
    unknown4fe = unknown4f0;
  }
  return shader;
}

grlib::CGLibDecShader *LayerShdManager::selectGsBlur() {
  s16 index = unknown4f0;
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(unknown4f0);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(unknown4f0);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(unknown4f0);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(unknown4f0);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
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
  grlib::CGLibDecShader *shader = unknown1e0.unknown40 + static_cast<u32>(index);
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

void LayerShdManager::shaderRelease() {
  unknown1e0.release();
  unknown368.release();
  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
  if (unknown10 != nullptr) {
    mtl::MemManager::deallocate(unknown10, 0, false);
    unknown10 = nullptr;
  }
  unknown18 = 0;
  if (unknown48 != nullptr) {
    mtl::MemManager::deallocate(unknown48, 0, false);
    unknown48 = nullptr;
  }
  if (unknown28 != nullptr) {
    ml::DevFileTh::cancel(unknown28, false);
    unknown28 = nullptr;
  }
  if (unknown30 != nullptr) {
    ml::DevFileTh::cancel(unknown30, false);
    unknown30 = nullptr;
  }
}

void LayerShdManager::readShader() {
  shaderRelease();
  ml::DevFileParamTh param;
  param._08 = unknown20->unknown24;
  param._54 = 0x1000;
  param.unknown60 = this;
  param._6d = false;
  param.unknown00 = "/monolib/shader/shd_layout.wishp";
  unknown28 = ml::DevFileTh::readFile(param);
  param.unknown00 = "/monolib/shader/layer_lut.witx";
  unknown30 = ml::DevFileTh::readFile(param);
}

void LayerShdManager::createShader() {
  unknown1e0.createPacShader(unknown08, 0x3ea, true);
  u32 size = unknown1e0.unknown50 * sizeof(unknown001);
  unknown48 = static_cast<unknown001 *>(mtl::MemManager::allocate(unknown20->unknown2c, size, 0x10, false, "no name", 0));
  memset(unknown48, 0xff, size);
  s32 count = unknown1e0.unknown50;
  for (s32 i = 0; i < count; i++) {
    (this->*s_CallSetup[i])(i);
  }
}

bool LayerShdManager::setupUpdate() {
  if (unknown08 == nullptr || unknown10 == nullptr) {
    return false;
  }
  if (unknown48 == nullptr) {
    createShader();
  }
  if (!unknown68) {
    createRenderWork();
  }
  createResWork();
  return true;
}

void LayerShdManager::createRenderWork() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0] = {unknown073_22, 0, 0, 0};
  attributes[1] = {unknown073_37, 1, 8, 0};
  unknown70[0].createFetchObj(attributes, 2);
  attributes[0] = {unknown073_22, 0, 0, 0};
  attributes[1] = {unknown073_37, 1, 8, 0};
  attributes[2] = {unknown073_22, 2, 12, 0};
  unknown70[1].createFetchObj(attributes, 3);
  attributes[0] = {unknown073_22, 0, 0, 0};
  attributes[1] = {unknown073_22, 1, 8, 0};
  attributes[2] = {unknown073_46, 2, 0, 1};
  attributes[3] = {unknown073_46, 3, 16, 1};
  attributes[4] = {unknown073_37, 4, 32, 1};
  unknown70[2].createFetchObj(attributes, 5);
  attributes[0] = {unknown073_34, 0, 0, 0};
  attributes[1] = {unknown073_37, 1, 12, 0};
  attributes[2] = {unknown073_22, 2, 16, 0};
  unknown70[3].createFetchObj(attributes, 3);
  attributes[0] = {unknown073_22, 0, 0, 0};
  attributes[1] = {unknown073_22, 1, 8, 0};
  unknown70[4].createFetchObj(attributes, 2);
  unknownc0[0].initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_NEAREST);
  unknownc0[0].updateData();
  unknownc0[1].initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_LINEAR);
  unknownc0[1].updateData();
  unknownc0[3].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_LINEAR);
  unknownc0[3].updateData();
  unknownc0[2].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_NEAREST);
  unknownc0[2].updateData();
  unknownc0[5].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_LINEAR);
  unknownc0[5].setFilter(GRL_TEX_MAG_FILTER_LINEAR, GRL_TEX_MIN_FILTER_UNKNOWN_5, GRL_TEX_ANISO_RATIO_UNKNOWN_0);
  unknownc0[5].updateData();
  unknownc0[4].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_NEAREST);
  unknownc0[4].setFilter(GRL_TEX_MAG_FILTER_NEAREST, GRL_TEX_MIN_FILTER_UNKNOWN_2, GRL_TEX_ANISO_RATIO_UNKNOWN_0);
  unknownc0[4].updateData();
  unknownc0[6].initSampler(GRL_TEX_CLAMP_CLAMP_TO_BORDER, GRL_TEX_MAG_FILTER_LINEAR);
  unknownc0[6].setBorderType(GRL_TEX_BORDER_TRANSPARENT_BLACK);
  unknownc0[6].updateData();
  unknownc0[7].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_LINEAR);
  unknownc0[7].setClamp(GRL_TEX_CLAMP_REPEAT, GRL_TEX_CLAMP_CLAMP, GRL_TEX_CLAMP_CLAMP);
  unknownc0[7].updateData();
  unknownc0[8].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_LINEAR);
  unknownc0[8].setClamp(GRL_TEX_CLAMP_CLAMP, GRL_TEX_CLAMP_REPEAT, GRL_TEX_CLAMP_CLAMP);
  unknownc0[8].updateData();
  unknown238[0].createCopyVertexBuff(unknown009, sizeof(unknown009), sizeof(unknown006));
  unknown238[1].createCopyVertexBuff(unknown010, sizeof(unknown010), sizeof(unknown007));
  unknown238[2].createCopyVertexBuff(unknown011, sizeof(unknown011), sizeof(unknown008));
  unknown238[3].createCopyVertexBuff(unknown012, sizeof(unknown012), sizeof(unknown008));
  unknown238[4].createCopyVertexBuff(unknown013, sizeof(unknown013), sizeof(unknown008));
  unknown300.createCopyIndexBuff(unknown014, 4, GRL_PRIMITIVE_QUADS, GRL_INDEX_FORMAT_U8);
  unknown328.createCopyIndexBuff(unknown014, 5, GRL_PRIMITIVE_UNKNOWN_3, GRL_INDEX_FORMAT_U8);
  unknown68 = true;
}

LayerShdManager::~LayerShdManager() {
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
  if (unknown40 != nullptr) {
    delete unknown40;
    unknown40 = nullptr;
  }
  allRelease();
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
  grlib::CGLibDecShader &shader = unknown1e0.unknown40[index];
  unknown001 &entry = unknown48[index];
  entry.unknown00 = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initTex(u32 index) {
  grlib::CGLibDecShader &shader = unknown1e0.unknown40[index];
  unknown001 &entry = unknown48[index];
  entry.unknown00 = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_FILBLEND_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initFont(u32 index) {
  grlib::CGLibDecShader &shader = unknown1e0.unknown40[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown04 = shader.getDeclarationOfs("MENU_ICON_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
}

void LayerShdManager::initWin(u32 index) {
  grlib::CGLibDecShader &shader = unknown1e0.unknown40[index];
  unknown001 &entry = unknown48[index];
  entry.unknown00 = shader.getDeclarationOfs("MENU_GAUGE_TYPE");
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initNumber(u32 index) {
  grlib::CGLibDecShader &shader = unknown1e0.unknown40[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initPoly(u32 index) {
  grlib::CGLibDecShader &shader = unknown1e0.unknown40[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_USE_TEX");
  entry.unknown08 = shader.getDeclarationOfs("MENU_MASKOBJ_TYPE");
  entry.unknown0a = shader.getDeclarationOfs("MENU_SECTEX_TYPE");
}

void LayerShdManager::initMemWrite(u32 index) {
  unknown001 &entry = unknown48[index];
  entry.unknown06 = unknown1e0.unknown40[index].getDeclarationOfs("MENU_DECODE_TYPE");
}

void LayerShdManager::initDebug(u32 index) {
  grlib::CGLibDecShader &shader = unknown1e0.unknown40[index];
  unknown001 &entry = unknown48[index];
  entry.unknown02 = shader.getDeclarationOfs("MENU_WORLD_TYPE");
  entry.unknown06 = shader.getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initGsBlur(u32 index) {
  unknown001 &entry = unknown48[index];
  entry.unknown06 = unknown1e0.unknown40[index].getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::initTest(u32 index) {
  unknown001 &entry = unknown48[index];
  entry.unknown06 = unknown1e0.unknown40[index].getDeclarationOfs("MENU_USE_TEX");
}

void LayerShdManager::resetViewPort() {
  if (unknown528) {
    unknown360 = nullptr;
    unknown528 = false;
    unknown52a = false;
    unknown50c.unknown00 = 0.0f;
    unknown50c.unknown04 = 0.0f;
    unknown50c.unknown08 = unknown550;
    unknown50c.unknown0c = unknown554;
    grlib::CGLibState::setViewport(grlib::LibMainStateViewPort(0.0f, 0.0f, unknown550 * unknown55c, unknown554 * unknown560, 0.0f, 1.0f));
  }
}

void LayerShdManager::endShader(const ml::IDrDrawWorkInfo *info) {
  grlib::CGLibState::setMainFrameBuffer();
  resetViewPort();
}

bool LayerShdManager::OnFileEvent(ml::EventFileTh *event) {
  if (event->type == ml::EventFileTh::TYPE_UNKNOWN_2) {
    if (unknown28 == event->unknown08) {
      unknown08 = event->moveFileData();
      unknown28 = nullptr;
    }
    if (unknown30 == event->unknown08) {
      unknown10 = event->moveFileData();
      unknown18 = event->unknown30;
      unknown30 = nullptr;
    }
  }
  return true;
}

void LayerShdManager::selectViewPort(const LayerViewPort &viewPort) {
  if (unknown52a || unknown50c.unknown00 != viewPort.unknown00 || unknown50c.unknown04 != viewPort.unknown04 || unknown50c.unknown08 != viewPort.unknown08 ||
      unknown50c.unknown0c != viewPort.unknown0c) {
    unknown50c = viewPort;
    unknown528 = true;
    unknown52a = false;
    f32 width = unknown558 * viewPort.unknown08;
    f32 height = unknown558 * viewPort.unknown0c;
    f32 x = unknown558 * viewPort.unknown00;
    f32 y = unknown558 * viewPort.unknown04;
    grlib::CGLibState::setViewport(grlib::LibMainStateViewPort(x, y, width, height, 0.0f, 1.0f));
  }
}

void LayerShdManager::setViewPort(LayerResViewPortInfo *viewPort) {
  grlib::CGLibRenderTarget *target = viewPort->unknown10;
  if (target == nullptr) {
    unknown360 = nullptr;
    selectViewPort(viewPort->unknown00);
  } else if (unknown360 != target) {
    if (!(viewPort->unknown30 & 1)) {
      target->clearTexture(viewPort->unknown20, static_cast<GrlClaerMask>(0xf));
      target = viewPort->unknown10;
      viewPort->unknown30 |= 1;
    }
    target->setRenderTarget();
    unknown52a = true;
    unknown528 = true;
    unknown360 = viewPort->unknown10;
    unknown50c.unknown00 = 0.0f;
    unknown50c.unknown04 = 0.0f;
    unknown50c.unknown08 = static_cast<f32>(viewPort->unknown10->unknownbc) / unknown558;
    unknown50c.unknown0c = static_cast<f32>(viewPort->unknown10->unknownc0) / unknown558;
  }
  unknown358 = viewPort->unknown18;
  unknown4fa = 3;
}

void LayerShdManager::setShaderMaskMode(const LayerObjTopMaskObj *mask) {
  unknown50 = mask;
  unknown358 = nullptr;
  unknown4fa = 2;
  selectViewPort(mask->unknown258);
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

grlib::CGLibDecShader *LayerShdManager::setupShader(grlib::CGLibDblUniformBlock *uniform) {
  grlib::CGLibDecShader *shader = setupShader();
  uniform->setUniformBlock(0);
  const LayerObjTopMaskObj *mask = unknown50;
  if (mask != nullptr) {
    const_cast<LayerObjTopMaskObj *>(mask)->unknown290.setUniformBlock(2);
    grlib::CGLibCtlTexture::setTexture(mask->getTexture(), unknownc0[6], 3);
  } else if (unknown358 != nullptr) {
    unknown358->setUniformBlock(2);
  }
  if (unknown58 != nullptr) {
    unknown60->setUniformBlock(3);
    grlib::CGLibCtlTexture::setTexture(*unknown58, unknownc0[3], 2);
  }
  return shader;
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

// The game builds these files in one unit with this one, in this order.
// clang-format off
#include "layer_font_draw_buffer.cpp"
#include "layer_font_manager.cpp"
#include "layer_font_icon_obj.cpp"
#include "layer_font_res_obj.cpp"
#include "layer_font_style_obj.cpp"
#include "layer_font_tag.cpp"
// clang-format on
