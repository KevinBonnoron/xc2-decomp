#include <new>
#include <stddef.h>
#include <string.h>

#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_depth_target.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_mem_pool_adder.h"
#include "grlib/cglib_render_array.h"
#include "grlib/cglib_render_cube_map.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_render_target_1d.h"
#include "grlib/cglib_render_target_base.h"
#include "grlib/cglib_render_target_mip_map.h"
#include "grlib/cglib_render_volume.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tex_descriptor.h"
#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {
struct CGLibTexSwizzle;

void CGLibColorBuffer::release() { unknown0c &= ~FLAG_INITIALIZED; }

void CGLibTextureBuffer::delayRelease() {
  if ((unknown10 & (FLAG_INITIALIZED | FLAG_OWN_BUFFER)) == 0) {
    return;
  }
  void *buffer = (unknown10 & FLAG_OWN_BUFFER) ? m_buffer : nullptr;
  NVNtexture *texture = (unknown10 & FLAG_INITIALIZED) ? unknown18 : nullptr;
  m_buffer = nullptr;
  unknown30 = 0;
  unknown10 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
  context::CGLibSystemContext::get()->releaseDelayTexture(texture, buffer, unknown34, unknown38);
  unknown34 = -1;
  unknown38 = -1;
  unknown40.delayRelease();
}

CGLibRenderTargetBase::CGLibRenderTargetBase() : unknown70(this) {}

void CGLibRenderTargetBase::setColorInvalidate() {}

u32 CGLibTextureBuffer::getImageSize() const {
  NVNtextureBuilder builder;
  switch (unknown0e) {
  case 2: {
    int width = m_width;
    int height = m_height;
    GrlSurfaceFormat format = m_format;
    int depth = m_depth;
    int mipmap = m_mipmap;
    CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_2D_ARRAY, format, width, height);
    nvnTextureBuilderSetDepth(&builder, depth);
    nvnTextureBuilderSetLevels(&builder, mipmap + 1);
    break;
  }
  case 3: {
    int width = m_width;
    int height = m_height;
    GrlSurfaceFormat format = m_format;
    int mipmap = m_mipmap;
    CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_CUBEMAP, format, width, height);
    nvnTextureBuilderSetLevels(&builder, mipmap + 1);
    break;
  }
  case 4: {
    int width = m_width;
    int height = m_height;
    GrlSurfaceFormat format = m_format;
    int slice = m_slice;
    int mipmap = m_mipmap;
    CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_CUBEMAP_ARRAY, format, width, height);
    nvnTextureBuilderSetDepth(&builder, slice * 6);
    nvnTextureBuilderSetLevels(&builder, mipmap + 1);
    break;
  }
  case 5: {
    int width = m_width;
    int height = m_height;
    GrlSurfaceFormat format = m_format;
    int depth = m_depth;
    CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_3D, format);
    nvnTextureBuilderSetSize3D(&builder, width, height, depth);
    break;
  }
  default: {
    int width = m_width;
    GrlSurfaceFormat format = m_format;
    if (!isTexture1D()) {
      int height = m_height;
      int mipmap = m_mipmap;
      CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_2D, format, width, height);
      nvnTextureBuilderSetDepth(&builder, 1);
      nvnTextureBuilderSetLevels(&builder, mipmap + 1);
    } else {
      CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_1D, format);
      nvnTextureBuilderSetSize1D(&builder, width);
      nvnTextureBuilderSetLevels(&builder, 1);
    }
    break;
  }
  }
  u32 size;
  u32 alignment;
  CGLibTexture::unknown002(builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
  return size;
}

u32 CGLibRenderTargetBase::getImageSize() const { return unknown70->CGLibTextureBuffer::getImageSize(); }

CGLibRenderArray::CGLibRenderArray() : unknown70(this), unknown78(nullptr), unknown80(false), unknown84(0), unknown88(0), unknown8c(0), unknown90(0) {}

CGLibRenderArray::~CGLibRenderArray() { releaseWork(); }

void CGLibRenderArray::releaseWork() {
  u32 count = unknown8c + unknown90 * unknown8c;
  for (u32 i = 0; i < count; i++) {
    unknown78[i].release();
  }
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
  delayRelease();
  unknown80 = false;
  unknown8c = 0;
  unknown90 = 0;
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArray::release() { releaseWork(); }

CGLibRenderTarget1D::CGLibRenderTarget1D() : unknown70(this), unknownb8(0), unknownbc(false) {}

CGLibRenderTarget1D::~CGLibRenderTarget1D() { releaseWork(); }

void CGLibRenderTarget1D::releaseWork() {
  unknown78.release();
  delayRelease();
  unknownbc = false;
}

void CGLibRenderTarget1D::setTextureInfo(f32 width, GrlSurfaceFormat format, bool isResArea, u32 resArea) {
  releaseWork();
  unknownbc = isResArea;
  unknownb8 = width;
  if (isResArea) {
    CGLibTexture::create1DTextureBuff(*this, unknownb8, format, resArea);
  } else {
    CGLibTexture::create1DTextureBuff(*this, unknownb8, format);
  }
  CGLibTexture::create1DColorTextureBuff(unknown78, *this, unknownb8, format);
}

void CGLibTexture::create1DTextureBuff(CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  get1DPixelSize(size, alignment, width, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setup1DTextureBuff(texture, width, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::create1DTextureBuff(CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  get1DPixelSize(size, alignment, width, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setup1DTextureBuff(texture, width, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::create1DColorTextureBuff(CGLibColorBuffer &colorBuffer, CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format) {
  unknown020(colorBuffer, texture, width, 1, 0, 0, format, NVN_TEXTURE_TARGET_1D);
}

void CGLibTexture::createTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getArrayPixelSize(size, alignment, width, height, slice, mipmap, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupTextureArrayBuff(texture, width, height, slice, mipmap, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getArrayPixelSize(size, alignment, width, height, slice, mipmap, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setupTextureArrayBuff(texture, width, height, slice, mipmap, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::createCubeMapTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getArrayCubePixelSize(size, alignment, width, height, slice, mipmap, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupCubeMapTextureArrayBuff(texture, width, height, slice, mipmap, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createCubeMapTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getArrayCubePixelSize(size, alignment, width, height, slice, mipmap, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setupCubeMapTextureArrayBuff(texture, width, height, slice, mipmap, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::createCubemapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getCubePixelSize(size, alignment, width, height, 0, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupCubemapTextureBuff(texture, width, height, 0, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createCubemapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getCubePixelSize(size, alignment, width, height, 0, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setupCubemapTextureBuff(texture, width, height, 0, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::createCubemapColorTextureBuff(CGLibColorBuffer *colorBuffers, CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format) {
  for (u32 face = 0; face < GRL_CUBE_MAP_FACE_NUM; face++) {
    CGLibColorBuffer &colorBuffer = colorBuffers[face];
    unknown020(colorBuffer, texture, width, height, 0, face, format, NVN_TEXTURE_TARGET_CUBEMAP);
    nvnTextureViewSetLayers(&colorBuffer.unknown10, CGLibTexture_plf::s_CubeMapFaceTable[face], 1);
  }
}

void CGLibTexture::createTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getDefPixelSize(size, alignment, width, height, 0, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupTextureBuff(texture, width, height, 0, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getDefPixelSize(size, alignment, width, height, 0, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setupTextureBuff(texture, width, height, 0, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::createColorTextureBuff(CGLibColorBuffer &colorBuffer, CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format) {
  unknown020(colorBuffer, texture, width, height, 0, 0, format, NVN_TEXTURE_TARGET_2D);
}

void CGLibTexture::createCubemapMipMapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getCubePixelSize(size, alignment, width, height, mipmap, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupCubemapTextureBuff(texture, width, height, mipmap, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createCubemapMipMapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getCubePixelSize(size, alignment, width, height, mipmap, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setupCubemapTextureBuff(texture, width, height, mipmap, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::createCubemapMipMapColorTextureBuff(CGLibColorBuffer (*colorBuffers)[16], CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format) {
  for (u32 face = 0; face < GRL_CUBE_MAP_FACE_NUM; face++) {
    u32 levelWidth = width;
    u32 levelHeight = height;
    for (u32 level = 0; level <= mipmap; level++) {
      CGLibColorBuffer &colorBuffer = colorBuffers[face][level];
      unknown020(colorBuffer, texture, levelWidth, levelHeight, level, face, format, NVN_TEXTURE_TARGET_2D);
      nvnTextureViewSetLayers(&colorBuffer.unknown10, CGLibTexture_plf::s_CubeMapFaceTable[face], 1);
      if (level != 0) {
        nvnTextureViewSetLevels(&colorBuffer.unknown10, level, 1);
      }
      levelWidth >>= 1;
      levelHeight >>= 1;
      if (levelWidth == 0) {
        levelWidth = 1;
      }
      if (levelHeight == 0) {
        levelHeight = 1;
      }
    }
  }
}

void CGLibTexture::createTextureMipMapBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getDefPixelSize(size, alignment, width, height, mipmap, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupTextureBuff(texture, width, height, mipmap, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createTextureMipMapBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getDefPixelSize(size, alignment, width, height, mipmap, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setupTextureBuff(texture, width, height, mipmap, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::createColorTextureMipMapBuff(CGLibColorBuffer *colorBuffers, CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format) {
  for (u32 level = 0; level <= mipmap; level++) {
    CGLibColorBuffer &colorBuffer = colorBuffers[level];
    colorBuffer.m_width = width;
    colorBuffer.m_height = height;
    colorBuffer.m_mipmap = level;
    colorBuffer.m_slice = 0;
    colorBuffer.m_format = format;
    colorBuffer.unknown0c = CGLibColorBuffer::FLAG_INITIALIZED;
    width >>= 1;
    height >>= 1;
    colorBuffer.unknown38 = texture.unknown18;
    nvnTextureViewSetDefaults(&colorBuffer.unknown10);
    nvnTextureViewSetLevels(&colorBuffer.unknown10, level, 1);
    nvnTextureViewSetFormat(&colorBuffer.unknown10, static_cast<NVNformat>(format));
    nvnTextureViewSetTarget(&colorBuffer.unknown10, NVN_TEXTURE_TARGET_2D);
  }
}

void CGLibTexture::createVolumeTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getVolumePixelSize(size, alignment, width, height, depth, format);
  texture.unknown30 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupVolumeTextureBuff(texture, width, height, depth, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createVolumeTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getVolumePixelSize(size, alignment, width, height, depth, format);
  u32 offset = unknown021(texture, mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0), size);
  CGLibTexture_plf::setupVolumeTextureBuff(texture, width, height, depth, format, context::CGLibSystemContext::get()->unknown2478, offset);
}

void CGLibTexture::createVolumeColorTextureBuff(CGLibColorBuffer *colorBuffers, CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format) {
  for (u32 i = 0; i < depth; i++) {
    CGLibColorBuffer &colorBuffer = colorBuffers[i];
    colorBuffer.release();
    colorBuffer.unknown38 = texture.unknown18;
    nvnTextureViewSetDefaults(&colorBuffer.unknown10);
    nvnTextureViewSetFormat(&colorBuffer.unknown10, static_cast<NVNformat>(format));
    nvnTextureViewSetTarget(&colorBuffer.unknown10, NVN_TEXTURE_TARGET_3D);
    nvnTextureViewSetLayers(&colorBuffer.unknown10, i, 1);
    colorBuffer.m_width = width;
    colorBuffer.m_height = height;
    colorBuffer.m_mipmap = 0;
    colorBuffer.m_slice = i;
    colorBuffer.m_format = format;
    colorBuffer.unknown0c = CGLibColorBuffer::FLAG_INITIALIZED;
  }
}

void CGLibTexture::createDepthStencilTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &depthTexture, CGLibTextureBuffer &stencilTexture, u32 width, u32 height, GrlDepthFormat format,
                                                 u32 offset) {
  createDepthBuff(depthBuffer, width, height, format, offset);
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  depthTexture.release();
  depthTexture.unknown10 |= CGLibTextureBuffer::FLAG_UNKNOWN_3;
  depthTexture.unknown30 = depthBuffer.unknown28;
  CGLibTexture_plf::setupTextureBuff(depthTexture, width, height, 0, static_cast<GrlSurfaceFormat>(format), context->unknown2478, context->getPixelResAreaOffset(offset));
  stencilTexture.release();
  stencilTexture.unknown10 |= CGLibTextureBuffer::FLAG_UNKNOWN_4;
  stencilTexture.unknown30 = depthBuffer.unknown28;
  CGLibTexture_plf::setupTextureBuff(stencilTexture, width, height, 0, static_cast<GrlSurfaceFormat>(format), context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createDepthTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &texture, u32 width, u32 height, GrlDepthFormat format, u32 offset) {
  createDepthBuff(depthBuffer, width, height, format, offset);
  texture.release();
  texture.unknown10 |= CGLibTextureBuffer::FLAG_UNKNOWN_3;
  texture.unknown30 = depthBuffer.unknown28;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupTextureBuff(texture, width, height, 0, static_cast<GrlSurfaceFormat>(format), context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createDepthStencilTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &depthTexture, CGLibTextureBuffer &stencilTexture, u32 width, u32 height, GrlDepthFormat format) {
  createDepthBuff(depthBuffer, width, height, format);
  CGLibMemPool &memPool = context::CGLibSystemContext::get()->unknown2478;
  depthTexture.release();
  depthTexture.unknown10 |= CGLibTextureBuffer::FLAG_UNKNOWN_3;
  depthTexture.m_buffer = depthBuffer.m_buffer;
  depthTexture.unknown30 = depthBuffer.unknown28;
  CGLibTexture_plf::setupTextureBuff(depthTexture, width, height, 0, static_cast<GrlSurfaceFormat>(format), memPool, static_cast<u8 *>(depthBuffer.m_buffer) - static_cast<u8 *>(memPool.unknown18));
  stencilTexture.release();
  stencilTexture.unknown10 |= CGLibTextureBuffer::FLAG_UNKNOWN_4;
  stencilTexture.m_buffer = depthBuffer.m_buffer;
  stencilTexture.unknown30 = depthBuffer.unknown28;
  CGLibTexture_plf::setupTextureBuff(stencilTexture, width, height, 0, static_cast<GrlSurfaceFormat>(format), memPool, static_cast<u8 *>(depthBuffer.m_buffer) - static_cast<u8 *>(memPool.unknown18));
}

void CGLibTexture::createDepthTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &texture, u32 width, u32 height, GrlDepthFormat format) {
  createDepthBuff(depthBuffer, width, height, format);
  texture.release();
  texture.unknown10 |= CGLibTextureBuffer::FLAG_UNKNOWN_3;
  texture.m_buffer = depthBuffer.m_buffer;
  texture.unknown30 = depthBuffer.unknown28;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupTextureBuff(
      texture, width, height, 0, static_cast<GrlSurfaceFormat>(format), context->unknown2478, static_cast<u8 *>(texture.m_buffer) - static_cast<u8 *>(context->unknown2478.unknown18));
}

CGLibRenderTargetMipMap::CGLibRenderTargetMipMap() : unknown70(this) {
  unknown47c = 0;
  unknown480 = 0;
  unknown484 = 0;
  unknown478 = false;
}

CGLibRenderTargetMipMap::~CGLibRenderTargetMipMap() { releaseWork(); }

void CGLibRenderTargetMipMap::releaseWork() {
  unknown484 = 0;
  for (u32 i = 0; i < 16; i++) {
    unknown78[i].release();
  }
  delayRelease();
  unknown478 = false;
}

CGLibRenderCubeMapMipMap::CGLibRenderCubeMapMipMap() : unknown70(this) {
  unknown1880 = 0;
  unknown1884 = 0;
  unknown187c = 0;
  unknown1878 = false;
}

CGLibRenderCubeMapMipMap::~CGLibRenderCubeMapMipMap() { releaseWork(); }

void CGLibRenderCubeMapMipMap::releaseWork() {
  for (u32 i = 0; i < GRL_CUBE_MAP_FACE_NUM; i++) {
    for (u32 j = 0; j < 16; j++) {
      unknown78[i][j].release();
    }
  }
  unknown187c = 0;
  delayRelease();
  unknown1878 = false;
}

CGLibRenderTarget::CGLibRenderTarget() {
  unknownbc = 0;
  unknownc0 = 0;
  unknownb8 = false;
  unknownc4 = 0;
  memset(unknownc8, 0, sizeof(unknownc8));
}

CGLibRenderTarget::~CGLibRenderTarget() {
  releaseWork();
  for (int i = 0; i < 6; i++) {
    unknown128[i].delayRelease();
  }
  unknownc4 = 0;
}

void CGLibRenderTarget::releaseWork() {
  unknown78.release();
  delayRelease();
  unknownb8 = false;
}

void CGLibRenderTarget::setTextureInfo(CGLibTextureBuffer &texture) {
  releaseWork();
  unknownbc = texture.m_width;
  unknownc0 = texture.m_height;
  CGLibTexture::copyTextureBuff(*unknown70, texture);
  CGLibTexture::createColorTextureBuff(unknown78, *unknown70, unknownbc, unknownc0, texture.m_format);
}

CGLibRenderCubeMap::CGLibRenderCubeMap() : unknown70(this) {
  unknown1fc = 0.0f;
  unknown200 = 0.0f;
  unknown1f8 = false;
}

CGLibRenderCubeMap::~CGLibRenderCubeMap() { releaseWork(); }

void CGLibRenderCubeMap::releaseWork() {
  for (u32 i = 0; i < GRL_CUBE_MAP_FACE_NUM; i++) {
    unknown78[i].release();
  }
  delayRelease();
  unknown1f8 = false;
}

void CGLibRenderCubeMap::setTextureInfo(f32 width, f32 height, GrlSurfaceFormat format, bool isResArea, u32 resArea) {
  releaseWork();
  unknown1f8 = isResArea;
  unknown1fc = width;
  unknown200 = height;
  if (isResArea) {
    CGLibTexture::createCubemapTextureBuff(*this, width, height, format, resArea);
  } else {
    CGLibTexture::createCubemapTextureBuff(*this, width, height, format);
  }
  CGLibTexture::createCubemapColorTextureBuff(unknown78, *this, unknown1fc, unknown200, format);
}

CGLibRenderVolume::CGLibRenderVolume() : unknown70(this), unknown78(nullptr) {
  unknown84 = 0;
  unknown88 = 0;
  unknown8c = 0;
  unknown80 = false;
}

CGLibRenderVolume::~CGLibRenderVolume() { releaseWork(); }

void CGLibRenderVolume::releaseWork() {
  for (u32 i = 0; i < unknown8c; i++) {
    unknown78[i].release();
  }
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
  delayRelease();
  unknown80 = false;
  unknown84 = 0;
  unknown88 = 0;
  unknown8c = 0;
}

void CGLibRenderVolume::setTextureInfo(f32 width, f32 height, f32 depth, GrlSurfaceFormat format, bool isResArea, u32 resArea) {
  releaseWork();
  unknown80 = isResArea;
  unknown84 = width;
  unknown88 = height;
  unknown8c = depth;
  unknown78 = static_cast<CGLibColorBuffer *>(mtl::MemManager::allocate(CGLibMemHandle::s_hMemHandle, unknown8c * sizeof(CGLibColorBuffer), 0x10, false, "no name", 0));
  for (u32 i = 0; i < unknown8c; i++) {
    new (&unknown78[i]) CGLibColorBuffer();
  }
  if (!isResArea) {
    CGLibTexture::createVolumeTextureBuff(*this, unknown84, unknown88, unknown8c, format);
  } else {
    CGLibTexture::createVolumeTextureBuff(*this, unknown84, unknown88, unknown8c, format, resArea);
  }
  CGLibTexture::createVolumeColorTextureBuff(unknown78, *this, unknown84, unknown88, unknown8c, format);
}

void CGLibRenderTarget1D::release() { releaseWork(); }

void CGLibRenderTarget1D::releaseTexture() {
  releaseWork();
  unknownb8 = 0;
}

void CGLibRenderTarget1D::clearTexture(const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget1D::clearIntTexture(const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget1D::setRenderTarget() {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownb8, 1.0f, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget1D::setRenderTarget(CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownb8, 1.0f, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTargetMipMap::release() { releaseWork(); }

void CGLibRenderTargetMipMap::releaseTexture() {
  releaseWork();
  unknown47c = 0;
  unknown480 = 0;
}

void CGLibRenderTargetMipMap::clearTexture(u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[mipmap], color, mask); }

void CGLibRenderTargetMipMap::clearIntTexture(u32 mipmap, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[mipmap], color, mask); }

void CGLibRenderTargetMipMap::setRenderTarget(u32 mipmap) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[mipmap].getWidth(), unknown78[mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[mipmap], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTargetMipMap::setRenderTarget(u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[mipmap].getWidth(), unknown78[mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[mipmap], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMapMipMap::release() { releaseWork(); }

void CGLibRenderCubeMapMipMap::releaseTexture() {
  releaseWork();
  unknown1880 = 0;
  unknown1884 = 0;
}

void CGLibRenderCubeMapMipMap::clearTexture(GrlCubeMapFace face, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[face][mipmap], color, mask); }

void CGLibRenderCubeMapMipMap::clearIntTexture(GrlCubeMapFace face, u32 mipmap, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[face][mipmap], color, mask); }

CGLibColorBuffer *CGLibRenderCubeMapMipMap::getColorBuffer(GrlCubeMapFace face, u32 mipmap) { return &unknown78[face][mipmap]; }

const CGLibColorBuffer *CGLibRenderCubeMapMipMap::getColorBuffer(GrlCubeMapFace face, u32 mipmap) const { return &unknown78[face][mipmap]; }

void CGLibRenderCubeMapMipMap::setRegisterRenderTarget(GrlCubeMapFace face, u32 mipmap, GrlMrtType mrt) { CGLibState::setRegisterRenderTarget(unknown78[face][mipmap], mrt); }

void CGLibRenderCubeMapMipMap::setRenderTarget(GrlCubeMapFace face, u32 mipmap) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[face][mipmap].getWidth(), unknown78[face][mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face][mipmap], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMapMipMap::setRenderTarget(GrlCubeMapFace face, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown78[face][mipmap].getWidth(), unknown78[face][mipmap].getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face][mipmap], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::release() { releaseWork(); }

void CGLibRenderTarget::releaseTexture() {
  releaseWork();
  unknownbc = 0;
  unknownc0 = 0;
}

void CGLibRenderTarget::clearTexture(const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget::clearIntTexture(const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78, color, mask); }

void CGLibRenderTarget::setRenderTarget() { setRenderTargetImpl(nullptr, 0, nullptr); }

void CGLibRenderTarget::setRenderTarget(CGLibColorBuffer &colorBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1) {
  CGLibRenderTarget *targets[] = {&target1};
  setRenderTargetImpl(targets, 1, nullptr);
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2) {
  CGLibRenderTarget *targets[] = {&target1, &target2};
  setRenderTargetImpl(targets, 2, nullptr);
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3) {
  CGLibRenderTarget *targets[] = {&target1, &target2, &target3};
  setRenderTargetImpl(targets, 3, nullptr);
}

void CGLibRenderTarget::setRenderTarget(CGLibDepthBuffer &depthBuffer) { setRenderTargetImpl(nullptr, 0, &depthBuffer); }

void CGLibRenderTarget::setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1) {
  CGLibRenderTarget *targets[] = {&target1};
  setRenderTargetImpl(targets, 1, &depthBuffer);
}

void CGLibRenderTarget::setRenderTarget(CGLibDepthBuffer &depthBuffer, CGLibRenderTarget &target1, CGLibRenderTarget &target2) {
  CGLibRenderTarget *targets[] = {&target1, &target2};
  setRenderTargetImpl(targets, 2, &depthBuffer);
}

void CGLibRenderTarget::setRenderTarget(CGLibRenderTarget &target1, CGLibRenderTarget &target2, CGLibRenderTarget &target3, CGLibRenderTarget &target4) {
  CGLibRenderTarget *targets[] = {&target1, &target2, &target3, &target4};
  setRenderTargetImpl(targets, 4, nullptr);
}

void CGLibRenderTarget::setRenderTargetImpl(CGLibRenderTarget **targets, u64 count, CGLibDepthBuffer *depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknownbc, unknownc0, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78, GRL_MRT_TYPE_0);
  for (u64 i = 0; i < count; i++) {
    CGLibState::setRegisterRenderTarget(*targets[i], static_cast<GrlMrtType>(i + 1));
  }
  if (depthBuffer != nullptr) {
    CGLibState::setRegisterDepthTarget(*depthBuffer);
  }
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMap::release() { releaseWork(); }

void CGLibRenderCubeMap::releaseTexture() {
  releaseWork();
  unknown1fc = 0;
  unknown200 = 0;
}

void CGLibRenderCubeMap::clearTexture(GrlCubeMapFace face, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[face], color, mask); }

void CGLibRenderCubeMap::clearIntTexture(GrlCubeMapFace face, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[face], color, mask); }

void CGLibRenderCubeMap::setRegisterRenderTarget(GrlCubeMapFace face, GrlMrtType mrt) { CGLibState::setRegisterRenderTarget(unknown78[face], mrt); }

void CGLibRenderCubeMap::setRenderTarget(GrlCubeMapFace face) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown1fc, unknown200, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderCubeMap::setRenderTarget(GrlCubeMapFace face, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown1fc, unknown200, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[face], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderVolume::release() { releaseWork(); }

void CGLibRenderVolume::releaseTexture() { releaseWork(); }

void CGLibRenderVolume::clearTexture(u32 slice, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[slice], color, mask); }

void CGLibRenderVolume::clearIntTexture(u32 slice, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[slice], color, mask); }

void CGLibRenderVolume::setRenderTarget(u32 slice) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[slice], GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderVolume::setRenderTarget(u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[slice], GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderVolume::setRenderTarget(u32 slice, CGLibRenderVolume &target) {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(unknown78[slice], GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(target.unknown78[slice], GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

CGLibDepthTarget::CGLibDepthTarget() {
  unknown08 = false;
  unknown00 = 0;
  unknown04 = 0;
  unknown120 = &unknown10;
  unknown128 = &unknown40;
  unknown130 = &unknownb0;
  unknown138 = 0;
  memset(unknown13c, 0, sizeof(unknown13c));
}

CGLibDepthTarget::~CGLibDepthTarget() {
  releaseWork();
  for (int i = 0; i < 6; i++) {
    unknown1a0[i].delayRelease();
    unknown2c0[i].delayRelease();
    unknown560[i].delayRelease();
  }
  unknown138 = 0;
}

void CGLibDepthTarget::releaseWork() {
  unknown10.delayRelease();
  unknown40.delayRelease();
  unknownb0.delayRelease();
  unknown08 = false;
}

void CGLibDepthTarget::release() { releaseWork(); }

void CGLibDepthTarget::releaseTexture() {
  releaseWork();
  unknown00 = 0;
  unknown04 = 0;
}

void CGLibDepthTarget::clearDepth(bool isClear) { CGLibDepthCtl::clearDepthBuffer(*unknown120, isClear); }

void CGLibDepthTarget::clearValDepth(float value, bool isClear) { CGLibDepthCtl::clearValDepthBuffer(*unknown120, value, isClear); }

void CGLibDepthTarget::setRenderTarget() {
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown00, unknown04, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterDepthTarget(*unknown120);
  CGLibState::endRegisterRenderTarget();
}

u16 CGLibColorBuffer::getWidth() const { return m_width; }

u16 CGLibColorBuffer::getHeight() const { return m_height; }

void CGLibRenderArray::releaseTexture() {
  releaseWork();
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArray::clearTexture(u32 slice, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[slice], color, mask); }

CGLibColorBuffer *CGLibRenderArray::getColorBuffer(u32 slice) { return &unknown78[slice]; }

void CGLibRenderArray::clearMipmapTexture(u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(unknown78[slice + unknown8c * mipmap], color, mask); }

CGLibColorBuffer *CGLibRenderArray::getMipmapColorBuffer(u32 slice, u32 mipmap) { return &unknown78[slice + unknown8c * mipmap]; }

void CGLibRenderArray::clearIntTexture(u32 slice, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[slice], color, mask); }

void CGLibRenderArray::clearIntMipmapTexture(u32 slice, u32 mipmap, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(unknown78[slice + unknown8c * mipmap], color, mask); }

void CGLibRenderArray::setRenderTarget(u32 slice) {
  CGLibColorBuffer &colorBuffer = unknown78[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setRenderTarget(u32 slice, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setRenderTarget(u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, unknown84, unknown88, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap) {
  CGLibColorBuffer &target = unknown78[slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

const CGLibColorBuffer *CGLibRenderArray::getColorBuffer(u32 slice) const { return &unknown78[slice]; }

const CGLibColorBuffer *CGLibRenderArray::getMipmapColorBuffer(u32 slice, u32 mipmap) const { return &unknown78[slice + unknown8c * mipmap]; }

CGLibRenderArrayCubeMap::CGLibRenderArrayCubeMap() : unknown70(this), unknown78(nullptr), unknown80(false), unknown84(0), unknown88(0), unknown8c(0), unknown90(0) {}

CGLibRenderArrayCubeMap::~CGLibRenderArrayCubeMap() { releaseWork(); }

void CGLibRenderArrayCubeMap::releaseWork() {
  u32 count = getFaceBufferNum() * GRL_CUBE_MAP_FACE_NUM;
  for (u32 i = 0; i < count; i++) {
    unknown78[i].release();
  }
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
  delayRelease();
  unknown80 = false;
  unknown8c = 0;
  unknown90 = 0;
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArrayCubeMap::release() { releaseWork(); }

void CGLibRenderArrayCubeMap::releaseTexture() {
  releaseWork();
  unknown84 = 0;
  unknown88 = 0;
}

void CGLibRenderArrayCubeMap::clearTexture(GrlCubeMapFace face, u32 slice, const mm::Col4 &color, GrlClaerMask mask) {
  CGLibDepthCtl::clearColorBuffer(unknown78[getFaceBufferNum() * face + slice], color, mask);
}

CGLibColorBuffer *CGLibRenderArrayCubeMap::getColorBuffer(GrlCubeMapFace face, u32 slice) { return &unknown78[getFaceBufferNum() * face + slice]; }

void CGLibRenderArrayCubeMap::clearMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) {
  CGLibDepthCtl::clearColorBuffer(unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap], color, mask);
}

CGLibColorBuffer *CGLibRenderArrayCubeMap::getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap) { return &unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap]; }

void CGLibRenderArrayCubeMap::clearIntTexture(GrlCubeMapFace face, u32 slice, const int *color, GrlClaerMask mask) {
  CGLibDepthCtl::clearIntColorBuffer(unknown78[getFaceBufferNum() * face + slice], color, mask);
}

void CGLibRenderArrayCubeMap::clearIntMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const int *color, GrlClaerMask mask) {
  CGLibDepthCtl::clearIntColorBuffer(unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap], color, mask);
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

const CGLibColorBuffer *CGLibRenderArrayCubeMap::getColorBuffer(GrlCubeMapFace face, u32 slice) const { return &unknown78[getFaceBufferNum() * face + slice]; }

const CGLibColorBuffer *CGLibRenderArrayCubeMap::getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap) const { return &unknown78[getFaceBufferNum() * face + slice + unknown8c * mipmap]; }

void CGLibDepthBuffer::delayRelease() {
  if ((unknown08 & (FLAG_INITIALIZED | FLAG_OWN_BUFFER)) == 0) {
    return;
  }
  void *buffer = (unknown08 & FLAG_OWN_BUFFER) ? m_buffer : nullptr;
  m_buffer = nullptr;
  unknown28 = 0;
  NVNtexture *texture = (unknown08 & FLAG_INITIALIZED) ? unknown10 : nullptr;
  unknown08 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
  context::CGLibSystemContext::get()->releaseDelayTexture(texture, buffer, -1, -1);
}

CGLibTextureBuffer::CGLibTextureBuffer() {
  unknown10 = 0;
  m_buffer = nullptr;
  unknown30 = 0;
  unknown34 = -1;
  unknown38 = -1;
  unknown18 = nullptr;
  unknown20 = 0;
}

CGLibTextureBuffer::~CGLibTextureBuffer() { release(); }

void CGLibTextureBuffer::release() {
  if (unknown10 & FLAG_OWN_BUFFER) {
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  } else {
    m_buffer = nullptr;
  }
  unknown30 = 0;
  unknown20 = 0;
  if (unknown10 & FLAG_INITIALIZED) {
    nvnTextureFinalize(unknown18);
    context::CGLibSystemContext::get()->unknowne60.freeBuffer(unknown18);
  }
  unknown40.release();
  if (unknown34 != -1) {
    context::CGLibSystemContext::get()->unknown538.freeID(unknown34);
    unknown34 = -1;
  }
  if (unknown38 != -1) {
    context::CGLibSystemContext::get()->unknown538.freeID(unknown38);
    unknown38 = -1;
  }
  unknown10 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
}

u16 CGLibTextureBuffer::getSlice() const { return m_slice; }

bool CGLibTextureBuffer::isTexture1D() const { return unknown0e == 1; }

bool CGLibTextureBuffer::isTexture2D() const { return unknown0e == 0; }

bool CGLibTextureBuffer::isTexture3D() const { return unknown0e == 5; }

void CGLibTextureBuffer::setTexturePass(CGLibTextureBuffer &texture) {}

void CGLibTextureBuffer::invalidate() {}

bool CGLibTextureBuffer::isInitialized() const { return unknown10 & FLAG_INITIALIZED; }

f32 CGLibTextureBuffer::get1PixelTextureInfo() {
  f32 info;
  CGLibTexture::get1PixelTextureInfo(&info, *this);
  return info;
}

void CGLibTextureBuffer::writeDDS(const char *path, bool isMipmap) {}

CGLibColorBuffer::CGLibColorBuffer() { unknown0c = 0; }

CGLibColorBuffer::~CGLibColorBuffer() { release(); }

u16 CGLibColorBuffer::getSlice() const { return m_slice; }

GrlSurfaceFormat CGLibColorBuffer::getFormat() const { return m_format; }

u16 CGLibColorBuffer::getMipmap() const { return m_mipmap; }

u32 CGLibColorBuffer::getImageSize() const {
  int width = m_width;
  int height = m_height;
  GrlSurfaceFormat format = m_format;
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_2D);
  nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(format));
  nvnTextureBuilderSetSize2D(&builder, width, height);
  nvnTextureBuilderSetDepth(&builder, 1);
  nvnTextureBuilderSetLevels(&builder, 1);
  nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
  u32 size = nvnTextureBuilderGetStorageSize(&builder);
  nvnTextureBuilderGetStorageAlignment(&builder);
  return size;
}

u32 CGLibColorBuffer::get1PixelImageSize() const {
  switch (m_format) {
  case GRL_SURFACE_FORMAT_R8:
  case GRL_SURFACE_FORMAT_R8SN:
  case GRL_SURFACE_FORMAT_R8UI:
  case GRL_SURFACE_FORMAT_R8I:
  case GRL_SURFACE_FORMAT_RGBA_DXT1:
  case GRL_SURFACE_FORMAT_RGBA_DXT1_SRGB:
  case GRL_SURFACE_FORMAT_RGTC1_UNORM:
  case GRL_SURFACE_FORMAT_RGTC1_SNORM:
    return 1;
  case GRL_SURFACE_FORMAT_R16F:
  case GRL_SURFACE_FORMAT_R16:
  case GRL_SURFACE_FORMAT_R16SN:
  case GRL_SURFACE_FORMAT_R16UI:
  case GRL_SURFACE_FORMAT_R16I:
  case GRL_SURFACE_FORMAT_RG8:
  case GRL_SURFACE_FORMAT_RG8SN:
  case GRL_SURFACE_FORMAT_RG8UI:
  case GRL_SURFACE_FORMAT_RG8I:
  case GRL_SURFACE_FORMAT_RGBA4:
  case GRL_SURFACE_FORMAT_RGB5A1:
  case GRL_SURFACE_FORMAT_RGB565:
  case GRL_SURFACE_FORMAT_RGBA_DXT3:
  case GRL_SURFACE_FORMAT_RGBA_DXT5:
  case GRL_SURFACE_FORMAT_RGBA_DXT3_SRGB:
  case GRL_SURFACE_FORMAT_RGBA_DXT5_SRGB:
  case GRL_SURFACE_FORMAT_RGTC2_UNORM:
  case GRL_SURFACE_FORMAT_RGTC2_SNORM:
    return 2;
  case GRL_SURFACE_FORMAT_R32F:
  case GRL_SURFACE_FORMAT_R32UI:
  case GRL_SURFACE_FORMAT_R32I:
  case GRL_SURFACE_FORMAT_RG16F:
  case GRL_SURFACE_FORMAT_RG16:
  case GRL_SURFACE_FORMAT_RG16SN:
  case GRL_SURFACE_FORMAT_RG16UI:
  case GRL_SURFACE_FORMAT_RG16I:
  case GRL_SURFACE_FORMAT_RGBA8:
  case GRL_SURFACE_FORMAT_RGBA8SN:
  case GRL_SURFACE_FORMAT_RGBA8UI:
  case GRL_SURFACE_FORMAT_RGBA8I:
  case GRL_SURFACE_FORMAT_DEPTH24_STENCIL8:
  case GRL_SURFACE_FORMAT_DEPTH32F_STENCIL8:
  case GRL_SURFACE_FORMAT_RGBA8_SRGB:
  case GRL_SURFACE_FORMAT_RGB10A2:
  case GRL_SURFACE_FORMAT_RGB10A2UI:
  case GRL_SURFACE_FORMAT_R11G11B10F:
  case GRL_SURFACE_FORMAT_BPTC_UNORM:
  case GRL_SURFACE_FORMAT_BPTC_SIGNED_FLOAT:
  case GRL_SURFACE_FORMAT_BPTC_UNSIGNED_FLOAT:
    return 4;
  case GRL_SURFACE_FORMAT_RG32F:
  case GRL_SURFACE_FORMAT_RG32UI:
  case GRL_SURFACE_FORMAT_RG32I:
  case GRL_SURFACE_FORMAT_RGBA16F:
  case GRL_SURFACE_FORMAT_RGBA16:
  case GRL_SURFACE_FORMAT_RGBA16SN:
  case GRL_SURFACE_FORMAT_RGBA16UI:
  case GRL_SURFACE_FORMAT_RGBA16I:
    return 8;
  case GRL_SURFACE_FORMAT_RGBA32F:
  case GRL_SURFACE_FORMAT_RGBA32UI:
  case GRL_SURFACE_FORMAT_RGBA32I:
    return 16;
  default:
    return 0;
  }
}

bool CGLibColorBuffer::isInitialized() const { return unknown0c & FLAG_INITIALIZED; }

CGLibDepthBuffer::CGLibDepthBuffer() {
  unknown08 = 0;
  unknown28 = 0;
  unknown18 = 0;
  m_buffer = nullptr;
}

CGLibDepthBuffer::~CGLibDepthBuffer() { release(); }

void CGLibDepthBuffer::release() {
  if (unknown08 & FLAG_OWN_BUFFER) {
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  } else {
    m_buffer = nullptr;
  }
  unknown18 = 0;
  unknown28 = 0;
  if (unknown08 & FLAG_INITIALIZED) {
    nvnTextureFinalize(unknown10);
    context::CGLibSystemContext::get()->unknowne60.freeBuffer(unknown10);
  }
  unknown08 &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
}

u16 CGLibDepthBuffer::getWidth() const { return m_width; }

u16 CGLibDepthBuffer::getHeight() const { return m_height; }

GrlSurfaceFormat CGLibDepthBuffer::getFormat() const { return m_format; }

u32 CGLibDepthBuffer::getImageSize() const {
  int width = m_width;
  int height = m_height;
  GrlSurfaceFormat format = m_format;
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_2D);
  nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(format));
  nvnTextureBuilderSetSize2D(&builder, width, height);
  nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_COMPRESSIBLE);
  u32 size = nvnTextureBuilderGetStorageSize(&builder);
  nvnTextureBuilderGetStorageAlignment(&builder);
  return size;
}

u32 CGLibDepthBuffer::get1PixelImageSize() const {
  switch (m_format) {
  case GRL_SURFACE_FORMAT_DEPTH16:
    return 2;
  case GRL_SURFACE_FORMAT_DEPTH32F:
  case GRL_SURFACE_FORMAT_DEPTH24_STENCIL8:
    return 4;
  case GRL_SURFACE_FORMAT_DEPTH32F_STENCIL8:
    return 5;
  default:
    return 0;
  }
}

void CGLibDepthBuffer::invalidate() {}

bool CGLibDepthBuffer::isInitialized() const { return unknown08 & FLAG_INITIALIZED; }

namespace {

const u32 unknown003[] = {
    // Inferred role: bytes per pixel by surface format; original table name unknown.
    1, 1, 1, 1, 2, 2,  2,  2,  2, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 4, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4,
    8, 8, 8, 8, 8, 16, 16, 16, 0, 0, 0, 0, 4, 4, 0, 4, 2, 0, 2, 2, 4, 4, 4, 0, 0, 1, 2, 2, 0, 1, 2, 2, 1, 1, 2, 2, 4, 0, 4, 4,
};

} // namespace

// Values read from the game's .rodata at 0x7100f7e16c.
const u32 CGLibTexture_plf::s_CubeMapFaceTable[6] = {0, 1, 3, 2, 4, 5};

void CGLibTexture::copyTextureBuff(CGLibTextureBuffer &dst, CGLibTextureBuffer &src) {
  dst.release();
  dst.m_buffer = src.m_buffer;
  dst.unknown30 = src.unknown30;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibMemPool &memPool = context->unknown2478;
  CGLibTexture_plf::setupTextureBuff(dst, src.m_width, src.m_height, 0, src.m_format, memPool, static_cast<u8 *>(dst.m_buffer) - static_cast<u8 *>(memPool.unknown18));
}

u32 CGLibTexture::get1PixelSize(GrlSurfaceFormat format) {
  if (format - 1U < 0x50) {
    return unknown003[format - 1];
  }
  return 0;
}

void CGLibTexture_plf::setupTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset) {
  unknown008(texture, 0, width, height, 0, 0, mipmap, format);
  NVNtextureBuilder builder;
  CGLibTexture::unknown006(builder);
  bool isImage;
  if (texture.unknown10 & CGLibTextureBuffer::FLAG_UNKNOWN_3) {
    nvnTextureBuilderSetDepthStencilMode(&builder, NVN_TEXTURE_DEPTH_STENCIL_MODE_DEPTH);
    nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
    isImage = false;
  } else if (texture.unknown10 & CGLibTextureBuffer::FLAG_UNKNOWN_4) {
    nvnTextureBuilderSetDepthStencilMode(&builder, NVN_TEXTURE_DEPTH_STENCIL_MODE_STENCIL);
    nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
    isImage = false;
  } else if (texture.unknown10 & CGLibTextureBuffer::FLAG_UNKNOWN_5) {
    nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_LINEAR);
    nvnTextureBuilderSetStride(&builder, CGLibTexture::unknown010(width, format));
    isImage = true;
  } else {
    if (texture.unknown10 & CGLibTextureBuffer::FLAG_UNKNOWN_2) {
      nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_DISPLAY | NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
    } else {
      nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
    }
    isImage = true;
  }
  nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_2D);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(format));
  nvnTextureBuilderSetSize2D(&builder, width, height);
  nvnTextureBuilderSetStorage(&builder, memPool.m_memoryPool, offset);
  unknown007(texture, builder, memPool, offset);
  allocTextureID(texture, isImage);
}

void CGLibTexture::createLinerTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format) {
  texture.release();
  u32 size;
  u32 alignment;
  getLinerPixelSize(size, alignment, width, height, format);
  texture.m_buffer = mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0);
  texture.unknown30 = size;
  texture.unknown10 |= CGLibTextureBuffer::FLAG_OWN_BUFFER | CGLibTextureBuffer::FLAG_UNKNOWN_5;
  CGLibMemPool &memPool = context::CGLibSystemContext::get()->unknown2478;
  CGLibTexture_plf::setupTextureBuff(texture, width, height, 0, format, memPool, static_cast<u8 *>(texture.m_buffer) - static_cast<u8 *>(memPool.unknown18));
}

void CGLibTexture::getLinerPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, GrlSurfaceFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_2D, format, width, height);
  nvnTextureBuilderSetDepth(&builder, 1);
  nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_LINEAR);
  nvnTextureBuilderSetStride(&builder, unknown010(width, format));
  size = nvnTextureBuilderGetStorageSize(&builder);
  u32 storageAlignment = nvnTextureBuilderGetStorageAlignment(&builder);
  alignment = storageAlignment + (0x1000 - storageAlignment % 0x1000) % 0x1000;
}

void CGLibTexture::createLinerTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format, u32 offset) {
  texture.release();
  u32 size;
  u32 alignment;
  getLinerPixelSize(size, alignment, width, height, format);
  texture.unknown30 = size;
  texture.unknown10 |= CGLibTextureBuffer::FLAG_UNKNOWN_5;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupTextureBuff(texture, width, height, 0, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture::createDepthBuff(CGLibDepthBuffer &depthBuffer, u32 width, u32 height, GrlDepthFormat format) {
  depthBuffer.release();
  u32 size;
  u32 alignment;
  getDepthPixelSize(size, alignment, width, height, format);
  void *buffer = mtl::MemManager::allocate(CGLibMemHandle::s_hPxlHandle, size, alignment, false, "no name", 0);
  depthBuffer.unknown28 = size;
  depthBuffer.m_buffer = buffer;
  CGLibMemPool &memPool = context::CGLibSystemContext::get()->unknown2478;
  CGLibTexture_plf::setupDepthBuff(depthBuffer, width, height, format, memPool, static_cast<u8 *>(buffer) - static_cast<u8 *>(memPool.unknown18));
  depthBuffer.unknown08 |= CGLibDepthBuffer::FLAG_OWN_BUFFER;
}

void CGLibTexture::createDepthBuff(CGLibDepthBuffer &depthBuffer, u32 width, u32 height, GrlDepthFormat format, u32 offset) {
  depthBuffer.release();
  u32 size;
  u32 alignment;
  getDepthPixelSize(size, alignment, width, height, format);
  depthBuffer.unknown28 = size;
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibTexture_plf::setupDepthBuff(depthBuffer, width, height, format, context->unknown2478, context->getPixelResAreaOffset(offset));
}

void CGLibTexture_plf::setup1DTextureBuff(CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset) {
  unknown008(texture, 1, width, 1, 0, 0, 0, format);
  NVNtextureBuilder builder;
  CGLibTexture::unknown006(builder);
  nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
  nvnTextureBuilderSetTarget(&builder, NVN_TEXTURE_TARGET_1D);
  nvnTextureBuilderSetLevels(&builder, 1);
  nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(format));
  nvnTextureBuilderSetSize1D(&builder, width);
  nvnTextureBuilderSetStorage(&builder, memPool.m_memoryPool, offset);
  unknown007(texture, builder, memPool, offset);
  allocTextureID(texture, true);
}

void CGLibTexture_plf::setupDepthBuff(CGLibDepthBuffer &depthBuffer, u32 width, u32 height, GrlDepthFormat format, CGLibMemPool &memPool, u32 offset) {
  depthBuffer.m_width = width;
  depthBuffer.m_height = height;
  depthBuffer.m_format = static_cast<GrlSurfaceFormat>(format);
  depthBuffer.unknown08 = CGLibDepthBuffer::FLAG_INITIALIZED;
  NVNtextureBuilder builder;
  CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_2D, format, width, height);
  nvnTextureBuilderSetStorage(&builder, memPool.m_memoryPool, offset);
  nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_COMPRESSIBLE);
  depthBuffer.unknown10 = unknown005();
  depthBuffer.unknown18 = nvnMemoryPoolGetBufferAddress(memPool.m_memoryPool) + offset;
  nvnTextureInitialize(depthBuffer.unknown10, &builder);
}

void CGLibTexture_plf::setupCubemapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset) {
  unknown008(texture, 3, width, height, 0, 0, mipmap, format);
  NVNtextureBuilder builder;
  CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_CUBEMAP, format, width, height);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  unknown009(texture, builder, memPool, offset);
  allocTextureID(texture, true);
}

void CGLibTexture_plf::setupVolumeTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset) {
  unknown008(texture, 5, width, height, depth, 0, 0, format);
  NVNtextureBuilder builder;
  CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_3D, format);
  nvnTextureBuilderSetSize3D(&builder, width, height, depth);
  unknown009(texture, builder, memPool, offset);
  allocTextureID(texture, true);
}

void CGLibTexture_plf::setupTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset) {
  unknown008(texture, 2, width, height, 0, slice, mipmap, format);
  NVNtextureBuilder builder;
  CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_2D_ARRAY, format, width, height);
  nvnTextureBuilderSetDepth(&builder, slice);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  unknown009(texture, builder, memPool, offset);
  allocTextureID(texture, true);
}

void CGLibTexture_plf::setupCubeMapTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset) {
  unknown008(texture, 4, width, height, 0, slice, mipmap, format);
  NVNtextureBuilder builder;
  CGLibTexture::unknown001(builder, NVN_TEXTURE_TARGET_CUBEMAP_ARRAY, format, width, height);
  nvnTextureBuilderSetDepth(&builder, slice * 6);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  unknown009(texture, builder, memPool, offset);
  allocTextureID(texture, true);
}

u32 CGLibTexture::get1DepthPixelSize(GrlDepthFormat format) {
  switch (format) {
  case GRL_DEPTH_FORMAT_UNKNOWN_0:
    return 2;
  case GRL_DEPTH_FORMAT_UNKNOWN_2:
  case GRL_DEPTH_FORMAT_UNKNOWN_3:
    return 4;
  case GRL_DEPTH_FORMAT_UNKNOWN_4:
    return 5;
  default:
    return 0;
  }
}

void CGLibTexture::get1DPixelSize(u32 &size, u32 &alignment, u32 width, GrlSurfaceFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_1D, format);
  nvnTextureBuilderSetSize1D(&builder, width);
  nvnTextureBuilderSetLevels(&builder, 1);
  unknown002(builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
}

void CGLibTexture::getDefPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_2D, format, width, height);
  nvnTextureBuilderSetDepth(&builder, 1);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  unknown002(builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
}

void CGLibTexture::getCubePixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_CUBEMAP, format, width, height);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  unknown002(builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
}

void CGLibTexture::getArrayCubePixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_CUBEMAP_ARRAY, format, width, height);
  nvnTextureBuilderSetDepth(&builder, slice * 6);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  unknown002(builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
}

void CGLibTexture::getVolumePixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 depth, GrlSurfaceFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_3D, format);
  nvnTextureBuilderSetSize3D(&builder, width, height, depth);
  unknown002(builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
}

void CGLibTexture::getArrayPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_2D_ARRAY, format, width, height);
  nvnTextureBuilderSetDepth(&builder, slice);
  nvnTextureBuilderSetLevels(&builder, mipmap + 1);
  unknown002(builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
}

void CGLibTexture::getDepthPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, GrlDepthFormat format) {
  NVNtextureBuilder builder;
  unknown001(builder, NVN_TEXTURE_TARGET_2D, format, width, height);
  unknown002(builder, NVN_TEXTURE_FLAGS_COMPRESSIBLE, size, alignment);
}

void CGLibTexture_plf::allocTextureID(CGLibTextureBuffer &texture, bool isImage) {
  CGLibTexDescriptor &descriptor = context::CGLibSystemContext::get()->unknown538;
  if (texture.unknown34 != -1) {
    descriptor.freeID(texture.unknown34);
  }
  if (texture.unknown38 != -1) {
    descriptor.freeID(texture.unknown38);
  }
  texture.unknown34 = descriptor.allocID();
  texture.unknown38 = isImage ? descriptor.allocID() : -1;
  descriptor.bindTexture(texture, texture.unknown34, texture.unknown38);
}

void CGLibTexture::changeTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size) {
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(static_cast<const u8 *>(data) + (size - sizeof(unknown004)));
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibMemPool *memPool = context->unknownef8.getMemPool(data);
  ptrdiff_t offset = unknown012(texture, memPool, data, footer->unknown10);
  texture.delayRelease();
  texture.unknown10 |= CGLibTextureBuffer::FLAG_INITIALIZED;
  NVNtextureBuilder builder;
  unknown011(builder, footer, data, false);
  unknown013(texture, builder, memPool, offset);
  u32 id = context->unknowne60.allocID();
  texture.unknown18 = static_cast<NVNtexture *>(context->unknowne60.unknown00) + id;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::changeTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, CGLibVtlMemPool &memPool, u32 offset) {
  const u8 *data = static_cast<const u8 *>(memPool.m_buffer) + offset;
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(data + (size - sizeof(unknown004)));
  u64 storageOffset = memPool.unknown18 + offset;
  texture.delayRelease();
  texture.unknown10 |= CGLibTextureBuffer::FLAG_INITIALIZED;
  NVNtextureBuilder builder;
  unknown011(builder, footer, data, false);
  nvnTextureBuilderSetStorage(&builder, memPool.unknown00, storageOffset);
  texture.unknown18 = CGLibTexture_plf::unknown005();
  texture.unknown20 = memPool.unknown08 + storageOffset;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::changeMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize) {
  u32 totalSize = size + mixSize;
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(static_cast<const u8 *>(data) + (totalSize - sizeof(unknown004)));
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibMemPool *memPool = context->unknownef8.getMemPool(data);
  ptrdiff_t offset = unknown012(texture, memPool, data, totalSize);
  texture.delayRelease();
  texture.unknown10 |= CGLibTextureBuffer::FLAG_INITIALIZED;
  NVNtextureBuilder builder;
  unknown011(builder, footer, data, true);
  unknown013(texture, builder, memPool, offset);
  u32 id = context->unknowne60.allocID();
  texture.unknown18 = static_cast<NVNtexture *>(context->unknowne60.unknown00) + id;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::changeMixTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, u32 mixSize, CGLibVtlMemPool &memPool, u32 offset) {
  const u8 *data = static_cast<const u8 *>(memPool.m_buffer) + offset;
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(data + (size + mixSize - sizeof(unknown004)));
  u64 storageOffset = memPool.unknown18 + offset;
  texture.delayRelease();
  texture.unknown10 |= CGLibTextureBuffer::FLAG_INITIALIZED;
  NVNtextureBuilder builder;
  unknown011(builder, footer, data, true);
  nvnTextureBuilderSetStorage(&builder, memPool.unknown00, storageOffset);
  texture.unknown18 = CGLibTexture_plf::unknown005();
  texture.unknown20 = memPool.unknown08 + storageOffset;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::createTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, bool isSrgb, const CGLibTexSwizzle *swizzle, bool) {
  texture.release();
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(static_cast<const u8 *>(data) + (size - sizeof(unknown004)));
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibMemPool *memPool = context->unknownef8.getMemPool(data);
  ptrdiff_t offset = unknown012(texture, memPool, data, footer->unknown10);
  unknown015(texture, footer, false);
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetTarget(&builder, static_cast<NVNtextureTarget>(footer->unknown24));
  unknown014(builder, footer, isSrgb);
  nvnTextureBuilderSetSize2D(&builder, footer->unknown18, footer->unknown1c);
  nvnTextureBuilderSetDepth(&builder, footer->unknown20);
  nvnTextureBuilderSetLevels(&builder, footer->unknown2c);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetPackagedTextureData(&builder, data);
  unknown013(texture, builder, memPool, offset);
  unknown016(builder, footer, swizzle);
  u32 id = context->unknowne60.allocID();
  texture.unknown18 = static_cast<NVNtexture *>(context->unknowne60.unknown00) + id;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::createTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, CGLibVtlMemPool &memPool, u32 offset, bool isSrgb, const CGLibTexSwizzle *swizzle, bool) {
  texture.release();
  const u8 *data = static_cast<const u8 *>(memPool.m_buffer) + offset;
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(data + (size - sizeof(unknown004)));
  u64 storageOffset = memPool.unknown18 + offset;
  unknown015(texture, footer, false);
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetTarget(&builder, static_cast<NVNtextureTarget>(footer->unknown24));
  unknown014(builder, footer, isSrgb);
  nvnTextureBuilderSetSize2D(&builder, footer->unknown18, footer->unknown1c);
  nvnTextureBuilderSetDepth(&builder, footer->unknown20);
  nvnTextureBuilderSetLevels(&builder, footer->unknown2c);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetPackagedTextureData(&builder, data);
  nvnTextureBuilderSetStorage(&builder, memPool.unknown00, storageOffset);
  unknown016(builder, footer, swizzle);
  texture.unknown18 = CGLibTexture_plf::unknown005();
  texture.unknown20 = memPool.unknown08 + storageOffset;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::createMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize, bool isSrgb, const CGLibTexSwizzle *swizzle, bool) {
  u32 totalSize = size + mixSize;
  texture.release();
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(static_cast<const u8 *>(data) + (totalSize - sizeof(unknown004)));
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  CGLibMemPool *memPool = context->unknownef8.getMemPool(data);
  ptrdiff_t offset = unknown012(texture, memPool, data, totalSize);
  unknown015(texture, footer, true);
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetTarget(&builder, static_cast<NVNtextureTarget>(footer->unknown24));
  unknown014(builder, footer, isSrgb);
  nvnTextureBuilderSetSize2D(&builder, footer->unknown18 * 2, footer->unknown1c * 2);
  nvnTextureBuilderSetDepth(&builder, footer->unknown20);
  nvnTextureBuilderSetLevels(&builder, footer->unknown2c + 1);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetPackagedTextureData(&builder, data);
  unknown013(texture, builder, memPool, offset);
  unknown016(builder, footer, swizzle);
  u32 id = context->unknowne60.allocID();
  texture.unknown18 = static_cast<NVNtexture *>(context->unknowne60.unknown00) + id;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::createMixTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, u32 mixSize, CGLibVtlMemPool &memPool, u32 offset, bool isSrgb, const CGLibTexSwizzle *swizzle, bool) {
  texture.release();
  u32 totalSize = size + mixSize;
  const u8 *data = static_cast<const u8 *>(memPool.m_buffer) + offset;
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(data + (totalSize - sizeof(unknown004)));
  u64 storageOffset = memPool.unknown18 + offset;
  unknown015(texture, footer, true);
  NVNtextureBuilder builder;
  nvnTextureBuilderSetDefaults(&builder);
  nvnTextureBuilderSetTarget(&builder, static_cast<NVNtextureTarget>(footer->unknown24));
  unknown014(builder, footer, isSrgb);
  nvnTextureBuilderSetSize2D(&builder, footer->unknown18 * 2, footer->unknown1c * 2);
  nvnTextureBuilderSetDepth(&builder, footer->unknown20);
  nvnTextureBuilderSetLevels(&builder, footer->unknown2c + 1);
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnTextureBuilderSetPackagedTextureData(&builder, data);
  nvnTextureBuilderSetStorage(&builder, memPool.unknown00, storageOffset);
  unknown016(builder, footer, swizzle);
  texture.unknown18 = CGLibTexture_plf::unknown005();
  texture.unknown20 = memPool.unknown08 + storageOffset;
  nvnTextureInitialize(texture.unknown18, &builder);
  CGLibTexture_plf::allocTextureID(texture, false);
}

void CGLibTexture::createTextureImagePtrs(CGLibTextureBuffer &texture, const void *, u32, const void *data, u32 size, bool isSrgb, const CGLibTexSwizzle *swizzle, bool) {
  createTextureImagePtrs(texture, data, size, isSrgb, swizzle, false);
}

void CGLibTexture::createTextureImagePtrs(CGLibTextureBuffer &texture, u32, u32 size, CGLibVtlMemPool &, CGLibVtlMemPool &memPool, u32, u32 offset, bool isSrgb, const CGLibTexSwizzle *swizzle, bool) {
  createTextureImagePtrs(texture, size, memPool, offset, isSrgb, swizzle, false);
}

bool CGLibTexture::isTextureImagePtrs(const void *data, u32 size) {
  const unknown004 *footer = reinterpret_cast<const unknown004 *>(static_cast<const u8 *>(data) + (size - sizeof(unknown004)));
  // Inferred role: "LBIM" magic and version of the packaged texture footer.
  if (footer->unknown34 == 0x4d49424c && footer->unknown30 == 10001) {
    return true;
  }
  return false;
}
} // namespace grlib
