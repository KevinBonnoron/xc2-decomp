#include "ptlib/renderer/screen_render_manager.h"

#include <new>

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec4.h"
#include "ptlib/material/particle_material_manager.h"
#include "ptlib/particle_stack_allocater.h"
#include "ptlib/particle_system.h"
#include "ptlib/renderer/particle_renderer_manager.h"
#include "ptlib/renderer/particle_renderer_obj.h"
#include "ptlib/renderer/particle_renderer_shader.h"
#include "types.h"

namespace ptlib {
namespace screen {

namespace {
ScreenRenderManager *unknown001;
f32 unknown002[20] = {-1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, -1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f};
const u16 unknown003[4] = {0, 1, 2, 3};
f32 unknown005;

// Inferred role: leading screen rectangle values shared by the uniform blocks of the screen shaders; original name unknown.
struct unknown008 {
  f32 unknown00; // Inferred role: width ratio; original member name unknown.
  f32 unknown04; // Inferred role: height ratio; original member name unknown.
  f32 unknown08; // Inferred role: x offset; original member name unknown.
  f32 unknown0c; // Inferred role: y offset; original member name unknown.
};

// Inferred role: converts a screen rectangle to the leading values of a uniform block; original name unknown.
inline void unknown009(unknown008 *buffer, const DrDrawWorkInfoEF *info, f32 x, f32 y, f32 width, f32 height) {
  f32 scaleX = width / info->unknown550;
  buffer->unknown00 = scaleX;
  f32 scaleY = height / info->unknown554;
  buffer->unknown04 = scaleY;
  f32 offsetX = 1.0f - scaleX;
  buffer->unknown08 = (x / info->unknown550 + x / info->unknown550) - offsetX;
  f32 offsetY = 1.0f - scaleY;
  buffer->unknown0c = offsetY - (y / info->unknown554 + y / info->unknown554);
}

// Inferred role: uniform block of the separate shader; original name unknown.
struct unknown007 {
  f32 unknown00; // Inferred role: width; original member name unknown.
  f32 unknown04; // Inferred role: height; original member name unknown.
  f32 unknown08; // Inferred role: inverse width; original member name unknown.
  f32 unknown0c; // Inferred role: inverse height; original member name unknown.
  f32 unknown10; // Inferred role: reset by RenderSeparate; original member name unknown.
  f32 unknown14; // Inferred role: reset by RenderSeparate; original member name unknown.
  f32 unknown18; // Inferred role: reset by RenderSeparate; original member name unknown.
  f32 unknown1c; // Inferred role: reset by RenderSeparate; original member name unknown.
};

// Inferred role: uniform block of the screen shader; original name unknown.
struct unknown006 : unknown008 {
  f32 unknown10; // Inferred role: color r; original member name unknown.
  f32 unknown14; // Inferred role: color g; original member name unknown.
  f32 unknown18; // Inferred role: color b; original member name unknown.
  f32 unknown1c; // Inferred role: color a; original member name unknown.
  f32 unknown20; // Inferred role: parameter x; original member name unknown.
  f32 unknown24; // Inferred role: parameter y; original member name unknown.
  f32 unknown28; // Inferred role: parameter z; original member name unknown.
  f32 unknown2c; // Inferred role: parameter w; original member name unknown.
};

// Inferred role: uniform block of the buffer copy shaders; original name unknown.
struct unknown004 : unknown008 {
  f32 unknown10; // Inferred role: color r; original member name unknown.
  f32 unknown14; // Inferred role: color g; original member name unknown.
  f32 unknown18; // Inferred role: color b; original member name unknown.
  f32 unknown1c; // Inferred role: color a; original member name unknown.
};
} // namespace

void ScreenRenderManager::init() {
#line 98
  MM_ASSERT(!getPtr());
  StaticAllocObj *allocator = StaticAllocObj::create(0x2f0, __FILE__, 102);
  unknown001 = static_cast<ScreenRenderManager *>(allocator->sysAlloc(sizeof(ScreenRenderManager), 0x10, nullptr, 0));
  new (unknown001) ScreenRenderManager();
  if (getPtr() != nullptr) {
    getPtr()->InitSub(allocator);
  }
}

ScreenRenderManager *&ScreenRenderManager::getPtr() { return unknown001; }

void ScreenRenderManager::InitSub(StaticAllocObj *allocator) {
  unknown0e0 = allocator;
  InitVertex();
  InitTexture();
  InitFetchVertex();
  efAstMsg("m_uAllocSizeUse < m_uAllocSize", "memory empty");
}

void ScreenRenderManager::term() {
#line 114
  MM_ASSERT(getPtr());
  getPtr()->ReleaseSub();
  getPtr()->~ScreenRenderManager();
  StaticAllocObj::destroy(getPtr()->unknown0e0);
  unknown001 = nullptr;
}

void ScreenRenderManager::ReleaseSub() {
  unknownd0.release();
  unknown80.release();
  unknowna8.release();
}

ScreenRenderManager *ScreenRenderManager::get() {
#line 133
  MM_ASSERT(getPtr());
  return getPtr();
}

bool ScreenRenderManager::isValid() { return getPtr() != nullptr; }

void ScreenRenderManager::InitVertex() {
  unknown80.createCopyVertexBuff(unknown002, 0x50, 0x14);
  unknowna8.createCopyIndexBuff(unknown003, 4, GRL_PRIMITIVE_QUADS, GRL_INDEX_FORMAT_U16);
}

void ScreenRenderManager::InitTexture() {
  unknown00[0].initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_LINEAR);
  unknown00[0].updateData();
  unknown00[2].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_NEAREST);
  unknown00[2].updateData();
  unknown00[3].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_LINEAR);
  unknown00[3].updateData();
  unknown00[1].initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_LINEAR);
  unknown00[1].setClamp(GRL_TEX_CLAMP_REPEAT, GRL_TEX_CLAMP_REPEAT, GRL_TEX_CLAMP_REPEAT);
  unknown00[1].updateData();
}

void ScreenRenderManager::InitFetchVertex() {
  void *memory = unknown0e0->sysAlloc(0x100, 0x10, nullptr, 0);
  grlib::CGLibVtxAttr attributes[2];
  attributes[0] = {GRL_VTX_FORMAT_RGB32F, 0, 0, 0};
  attributes[1] = {GRL_VTX_FORMAT_RG32F, 1, 0xc, 0};
  unknownd0.createMemFetchObj(memory, attributes, 2);
}

void ScreenRenderManager::RenderBuffer(const DrDrawWorkInfoEF *info, const mm::Mat44 &rect, const mm::Vec3 &unused, const mm::Col4 &color, const grlib::CGLibTextureBuffer *texture) {
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_9);
  grlib::CGLibCtlVertex::setVertex(unknown80);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  f32 x = rect.rows[0][0];
  f32 y = rect.rows[0][1];
  f32 width = rect.rows[0][2];
  f32 height = rect.rows[0][3];
  {
    grlib::CGLibEtcUniformBlock block;
    block.setMoveMem(sizeof(unknown004));
    unknown004 *buffer = reinterpret_cast<unknown004 *>(block.getBuff());
    unknown009(buffer, info, x, y, width, height);
    buffer->unknown10 = color.r;
    buffer->unknown14 = color.g;
    buffer->unknown18 = color.b;
    buffer->unknown1c = color.a;
    block.updateData(sizeof(unknown004));
    block.setUniformBlock(0);
  }
  u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  if (texture != nullptr) {
    grlib::CGLibCtlTexture::setTexture(*texture, unknown00[0], location);
  }
  unknowna8.drawIndex();
}

void ScreenRenderManager::RenderBufferMain(const DrDrawWorkInfoEF *info, const mm::Mat44 &rect, const mm::Vec3 &unused, const mm::Col4 &color, const grlib::CGLibTextureBuffer *texture) {
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_10);
  grlib::CGLibCtlVertex::setVertex(unknown80);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  f32 x = rect.rows[0][0];
  f32 y = rect.rows[0][1];
  f32 width = rect.rows[0][2];
  f32 height = rect.rows[0][3];
  {
    grlib::CGLibEtcUniformBlock block;
    block.setMoveMem(sizeof(unknown004));
    unknown004 *buffer = reinterpret_cast<unknown004 *>(block.getBuff());
    unknown009(buffer, info, x, y, width, height);
    buffer->unknown10 = color.r;
    buffer->unknown14 = color.g;
    buffer->unknown18 = color.b;
    buffer->unknown1c = color.a;
    block.updateData(sizeof(unknown004));
    block.setUniformBlock(0);
  }
  u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  if (texture != nullptr) {
    grlib::CGLibCtlTexture::setTexture(*texture, unknown00[0], location);
  }
  unknowna8.drawIndex();
}

void ScreenRenderManager::RenderScreen3D(const DrDrawWorkInfoEF *info, const mm::Mat44 &rect, const mm::Vec3 &unused, const mm::Col4 &color, const grlib::CGLibTextureBuffer *texture, bool isBlend) {
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_8);
  u32 blendOffset = shader->getDeclarationOfs("BLEND_TYPE");
  if (isBlend) {
    shader->setDeclarationIdx(blendOffset, 2);
  } else {
    shader->setDeclarationIdx(blendOffset, 1);
  }
  grlib::CGLibCtlVertex::setVertex(unknown80);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  f32 x = rect.rows[0][0];
  f32 y = rect.rows[0][1];
  f32 width = rect.rows[0][2];
  f32 height = rect.rows[0][3];
  {
    grlib::CGLibEtcUniformBlock block;
    block.setMoveMem(sizeof(unknown004));
    unknown004 *buffer = reinterpret_cast<unknown004 *>(block.getBuff());
    unknown009(buffer, info, x, y, width, height);
    buffer->unknown10 = unknown005;
    buffer->unknown14 = unknown005;
    buffer->unknown18 = unknown005;
    buffer->unknown1c = unknown005;
    unknown005 += 0.01f;
    if (unknown005 >= 1.0f) {
      unknown005 -= 1.0f;
    }
    block.updateData(sizeof(unknown004));
    block.setUniformBlock(0);
  }
  u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  if (texture != nullptr) {
    grlib::CGLibCtlTexture::setTexture(*texture, unknown00[1], location);
  }
  unknowna8.drawIndex();
}

void ScreenRenderManager::RenderScreen(const DrDrawWorkInfoEF *info, const mm::Mat44 &rect, const mm::Vec3 &unused, const mm::Col4 &color, const grlib::CGLibTextureBuffer *texture, bool isBlend,
                                       mm::Vec4 parameter) {
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_7);
  grlib::CGLibEtcUniformBlock block;
  u32 blendOffset = shader->getDeclarationOfs("BLEND_TYPE");
  if (isBlend) {
    shader->setDeclarationIdx(blendOffset, 2);
  } else {
    shader->setDeclarationIdx(blendOffset, 1);
  }
  grlib::CGLibCtlVertex::setVertex(unknown80);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  f32 x = rect.rows[0][0];
  f32 y = rect.rows[0][1];
  f32 width = rect.rows[0][2];
  f32 height = rect.rows[0][3];
  block.setMoveMem(sizeof(unknown006));
  unknown006 *buffer = reinterpret_cast<unknown006 *>(block.getBuff());
  unknown009(buffer, info, x, y, width, height);
  buffer->unknown10 = color.r;
  buffer->unknown14 = color.g;
  buffer->unknown18 = color.b;
  buffer->unknown1c = color.a;
  buffer->unknown20 = parameter.x;
  buffer->unknown24 = parameter.y;
  buffer->unknown28 = parameter.z;
  buffer->unknown2c = parameter.w;
  block.updateData(sizeof(unknown006));
  block.setUniformBlock(0);
  u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  if (texture != nullptr) {
    grlib::CGLibCtlTexture::setTexture(*texture, unknown00[0], location);
  }
  unknowna8.drawIndex();
}

void ScreenRenderManager::RenderScreenDebug(const DrDrawWorkInfoEF *info, const mm::Mat44 &rect, const mm::Vec3 &unused, const mm::Col4 &color, material::MaterialTexture *texture, bool isBlend,
                                            mm::Vec4 parameter) {
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_7);
  u32 blendOffset = shader->getDeclarationOfs("BLEND_TYPE");
  if (isBlend) {
    shader->setDeclarationIdx(blendOffset, 2);
  } else {
    shader->setDeclarationIdx(blendOffset, 1);
  }
  grlib::CGLibCtlVertex::setVertex(unknown80);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  f32 x = rect.rows[0][0];
  f32 y = rect.rows[0][1];
  f32 width = rect.rows[0][2];
  f32 height = rect.rows[0][3];
  grlib::CGLibEtcUniformBlock block;
  block.setMoveMem(sizeof(unknown006));
  unknown006 *buffer = reinterpret_cast<unknown006 *>(block.getBuff());
  buffer->unknown00 = width / info->unknown550;
  buffer->unknown04 = height / info->unknown554;
  buffer->unknown08 = x / info->unknown550 + x / info->unknown550;
  buffer->unknown0c = -y / info->unknown554 + -y / info->unknown554;
  buffer->unknown18 = 1.0f;
  buffer->unknown1c = 1.0f;
  buffer->unknown10 = 1.0f;
  buffer->unknown14 = 1.0f;
  buffer->unknown20 = parameter.x;
  buffer->unknown24 = parameter.y;
  buffer->unknown28 = parameter.z;
  buffer->unknown2c = parameter.w;
  block.updateData(sizeof(unknown006));
  block.setUniformBlock(0);
  u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  if (texture != nullptr) {
    grlib::CGLibCtlTexture::setTexture(texture->unknown40, unknown00[0], location);
  }
  unknowna8.drawIndex();
}

void ScreenRenderManager::RenderCapScreen(const DrDrawWorkInfoEF *info, const grlib::CGLibTextureBuffer *texture0, const grlib::CGLibTextureBuffer *texture1) {
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_7);
  grlib::CGLibEtcUniformBlock block;
  shader->setDeclarationIdx(shader->getDeclarationOfs("BLEND_TYPE"), 1);
  shader->setDeclarationIdx(shader->getDeclarationOfs("TEX_TYPE"), 2);
  grlib::CGLibCtlVertex::setVertex(unknown80);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  unknown006 *buffer = reinterpret_cast<unknown006 *>(block.getBuff());
  buffer->unknown00 = 1.0f;
  buffer->unknown04 = 1.0f;
  buffer->unknown08 = 0.0f;
  buffer->unknown0c = 0.0f;
  buffer->unknown10 = 1.0f;
  buffer->unknown14 = 1.0f;
  buffer->unknown18 = 1.0f;
  buffer->unknown1c = 1.0f;
  buffer->unknown20 = 0.0f;
  buffer->unknown24 = 0.0f;
  buffer->unknown28 = 1.0f;
  buffer->unknown2c = 1.0f;
  block.updateData(sizeof(unknown006));
  block.setUniformBlock((shader->unknown38 + shader->unknown58)->getUniformBlockOfs("CommonBuff"));
  grlib::CGLibCtlTexture::setTexture(*texture0, unknown00[0], (shader->unknown38 + shader->unknown58)->getTextureLocation("s0"));
  grlib::CGLibCtlTexture::setTexture(*texture1, unknown00[0], (shader->unknown38 + shader->unknown58)->getTextureLocation("s1"));
  unknowna8.drawIndex();
  shader->setDeclarationIdx(shader->getDeclarationOfs("TEX_TYPE"), 1);
}

void ScreenRenderManager::RenderSeparate(const DrDrawWorkInfoEF *info) {
  grlib::CGLibCtlShader::setMemoryBarrierBit(4);
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_15);
  grlib::CGLibColorCtl::setMrtBlend(7, GRL_LOGIC_TYPE_COPY);
  grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_0, GRL_BLEND_FUNC_ONE, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_COMBINE_ADD);
  grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_1, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
  grlib::CGLibColorCtl::setMrtBlendControl(grlib::GRL_MRT_TYPE_2, GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE, GRL_BLEND_COMBINE_ADD);
  grlib::CGLibRenderTarget *thirdTarget = info->unknown058;
  grlib::CGLibRenderTarget *mainTarget = info->unknown000;
  u32 outType;
  if (info->unknown070 == nullptr) {
    if (thirdTarget == nullptr) {
      mainTarget->setRenderTarget();
      outType = 4;
    } else {
      mainTarget->setRenderTarget(*thirdTarget);
      outType = 3;
    }
  } else if (thirdTarget == nullptr) {
    mainTarget->setRenderTarget(*info->unknown040);
    outType = 2;
  } else {
    mainTarget->setRenderTarget(*info->unknown040, *thirdTarget);
    outType = 1;
  }
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUTTYPE"), outType);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  f32 width = info->unknown068->unknownbc;
  f32 height = info->unknown068->unknownc0;
  grlib::CGLibEtcUniformBlock block;
  unknown007 *buffer = reinterpret_cast<unknown007 *>(block.getBuff());
  buffer->unknown00 = width;
  buffer->unknown04 = height;
  buffer->unknown10 = 0.0f;
  buffer->unknown14 = 0.0f;
  buffer->unknown18 = 0.0f;
  buffer->unknown1c = 0.0f;
  buffer->unknown08 = 1.0f / width;
  buffer->unknown0c = 1.0f / height;
  block.updateData(sizeof(unknown007));
  block.setUniformBlock((shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_POST"));
  u32 depColLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("depCol");
  u32 depBlmLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("depBlm");
  u32 dwnDepLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("dwnDep");
  u32 orgDepLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("orgDep");
  grlib::CGLibCtlTexture::setTexture(*info->unknown018->unknown70, unknown00[2], dwnDepLocation);
  grlib::CGLibCtlTexture::setTexture(*info->unknown020->unknown70, unknown00[2], orgDepLocation);
  grlib::CGLibCtlTexture::setTexture(*info->unknown068->unknown70, unknown00[3], depColLocation);
  if (info->unknown070 != nullptr) {
    grlib::CGLibCtlTexture::setTexture(*info->unknown070->unknown70, unknown00[3], depBlmLocation);
  }
  grlib::CGLibCtlVertex::setVertex(unknown80);
  unknowna8.drawIndex();
  grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
}

void ScreenRenderManager::RenderBufferWithFXAA(const DrDrawWorkInfoEF *info, const mm::Mat44 &rect, const mm::Vec3 &unused, const mm::Col4 &color, const grlib::CGLibTextureBuffer *texture) {
  grlib::CGLibDecShader *shader = renderer::RenderManager::getPtr()->getRenderGrObj()->unknownb0.getShaderByIndex(renderer::EFF_SHD_TYPE_UNKNOWN_14);
  grlib::CGLibCtlVertex::setVertex(unknown80);
  grlib::CGLibCtlShader::setShader(*shader, unknownd0);
  grlib::CGLibRenderTarget *target = info->unknown018;
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 textureLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("dep");
  u32 fxaaRcpFrOptOffset = uniform.unknown001("fxaaRcpFrOpt");
  u32 aaValOffset = uniform.unknown001("aaVal");
  u32 ratioOffset = uniform.unknown001("ratio");
  u32 gScalOffset = uniform.unknown001("gScal");
  u32 gSubOffset = uniform.unknown001("gSub");
  u32 uvsclOffset = uniform.unknown001("uvscl");
  f32 width = info->unknown550;
  f32 height = info->unknown554;
  f32 value[4];
  value[0] = (width - 1.0f) / width;
  value[1] = (height - 1.0f) / height;
  value[2] = 1.0f / (width + width);
  value[3] = 1.0f / (height + height);
  uniform.setF32SetVec4(gScalOffset, value);
  value[0] = 1.0f / width;
  value[1] = 1.0f / height;
  uniform.setF32SetVec4(gSubOffset, value);
  value[0] = 0.5f / width;
  value[1] = 0.5f / height;
  value[2] = 2.0f / width;
  value[3] = 2.0f / height;
  uniform.setF32SetVec4(fxaaRcpFrOptOffset, value);
  value[0] = 0.17f;
  value[1] = 0.05f;
  value[2] = 8.0f;
  uniform.setF32SetVec4(aaValOffset, value);
  f32 targetWidth = target->unknownbc;
  f32 targetHeight = target->unknownc0;
  value[0] = (targetWidth - 1.0f) / targetWidth;
  value[1] = (targetHeight - 1.0f) / targetHeight;
  value[2] = 1.0f / (targetWidth + targetWidth);
  value[3] = 1.0f / (targetHeight + targetHeight);
  uniform.setF32SetVec4(uvsclOffset, value);
  value[0] = 0.0f;
  value[1] = info->unknown1b8;
  value[2] = info->unknown1c8;
  value[3] = 0.0f;
  uniform.setF32SetVec4(ratioOffset, value);
  uniform.updateData();
  uniform.setUniformBlock();
  grlib::CGLibCtlTexture::setTexture(*texture, unknown00[0], textureLocation);
  grlib::CGLibCtlTexture::setTexture(*target->unknown70, unknown00[0], depthLocation);
  unknowna8.drawIndex();
}

} // namespace screen
} // namespace ptlib
