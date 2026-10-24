#include "grlib/cglib_texture_buffer.h"

#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_render_array.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_state.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tex_descriptor.h"
#include "grlib/cglib_texture.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {

void CGLibColorBuffer::release() { m_flags &= ~FLAG_INITIALIZED; }

void CGLibTextureBuffer::delayRelease() {
  if ((m_flags & (FLAG_INITIALIZED | FLAG_OWN_BUFFER)) == 0) {
    return;
  }
  void *buffer = (m_flags & FLAG_OWN_BUFFER) ? m_buffer : nullptr;
  NVNtexture *texture = (m_flags & FLAG_INITIALIZED) ? m_nvnTexture : nullptr;
  m_buffer = nullptr;
  m_bufferSize = 0;
  m_flags &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
  context::CGLibSystemContext::get()->releaseDelayTexture(texture, buffer, m_textureId, m_samplerId);
  m_textureId = -1;
  m_samplerId = -1;
  m_memPool.delayRelease();
}

CGLibRenderArray::CGLibRenderArray() : m_texture(this), m_colorBuffers(nullptr), m_isResArea(false), m_arrayWidth(0), m_arrayHeight(0), m_sliceNum(0), m_mipmapNum(0) {}

CGLibRenderArray::~CGLibRenderArray() { releaseWork(); }

void CGLibRenderArray::releaseWork() {
  u32 count = m_sliceNum + m_mipmapNum * m_sliceNum;
  for (u32 i = 0; i < count; i++) {
    m_colorBuffers[i].release();
  }
  if (m_colorBuffers != nullptr) {
    mtl::MemManager::deallocate(m_colorBuffers, 0, false);
    m_colorBuffers = nullptr;
  }
  delayRelease();
  m_isResArea = false;
  m_sliceNum = 0;
  m_mipmapNum = 0;
  m_arrayWidth = 0;
  m_arrayHeight = 0;
}

void CGLibRenderArray::release() { releaseWork(); }

u16 CGLibColorBuffer::getWidth() const { return m_width; }

u16 CGLibColorBuffer::getHeight() const { return m_height; }

void CGLibRenderArray::releaseTexture() {
  releaseWork();
  m_arrayWidth = 0;
  m_arrayHeight = 0;
}

void CGLibRenderArray::clearTexture(u32 slice, const mm::Col4 &color, GrlClaerMask mask) { CGLibDepthCtl::clearColorBuffer(m_colorBuffers[slice], color, mask); }

CGLibColorBuffer *CGLibRenderArray::getColorBuffer(u32 slice) { return &m_colorBuffers[slice]; }

void CGLibRenderArray::clearMipmapTexture(u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) {
  CGLibDepthCtl::clearColorBuffer(m_colorBuffers[slice + m_sliceNum * mipmap], color, mask);
}

CGLibColorBuffer *CGLibRenderArray::getMipmapColorBuffer(u32 slice, u32 mipmap) { return &m_colorBuffers[slice + m_sliceNum * mipmap]; }

void CGLibRenderArray::clearIntTexture(u32 slice, const int *color, GrlClaerMask mask) { CGLibDepthCtl::clearIntColorBuffer(m_colorBuffers[slice], color, mask); }

void CGLibRenderArray::clearIntMipmapTexture(u32 slice, u32 mipmap, const int *color, GrlClaerMask mask) {
  CGLibDepthCtl::clearIntColorBuffer(m_colorBuffers[slice + m_sliceNum * mipmap], color, mask);
}

void CGLibRenderArray::setRenderTarget(u32 slice) {
  CGLibColorBuffer &colorBuffer = m_colorBuffers[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, m_arrayWidth, m_arrayHeight, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setRenderTarget(u32 slice, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, m_arrayWidth, m_arrayHeight, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setRenderTarget(u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, m_arrayWidth, m_arrayHeight, 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap) {
  CGLibColorBuffer &target = m_colorBuffers[slice + m_sliceNum * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[slice + m_sliceNum * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArray::setMipmapRenderTarget(u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[slice + m_sliceNum * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

const CGLibColorBuffer *CGLibRenderArray::getColorBuffer(u32 slice) const { return &m_colorBuffers[slice]; }

const CGLibColorBuffer *CGLibRenderArray::getMipmapColorBuffer(u32 slice, u32 mipmap) const { return &m_colorBuffers[slice + m_sliceNum * mipmap]; }

CGLibRenderArrayCubeMap::CGLibRenderArrayCubeMap() : m_texture(this), m_colorBuffers(nullptr), m_isResArea(false), m_arrayWidth(0), m_arrayHeight(0), m_sliceNum(0), m_mipmapNum(0) {}

CGLibRenderArrayCubeMap::~CGLibRenderArrayCubeMap() { releaseWork(); }

void CGLibRenderArrayCubeMap::releaseWork() {
  u32 count = getFaceBufferNum() * GRL_CUBE_MAP_FACE_NUM;
  for (u32 i = 0; i < count; i++) {
    m_colorBuffers[i].release();
  }
  if (m_colorBuffers != nullptr) {
    mtl::MemManager::deallocate(m_colorBuffers, 0, false);
    m_colorBuffers = nullptr;
  }
  delayRelease();
  m_isResArea = false;
  m_sliceNum = 0;
  m_mipmapNum = 0;
  m_arrayWidth = 0;
  m_arrayHeight = 0;
}

void CGLibRenderArrayCubeMap::release() { releaseWork(); }

void CGLibRenderArrayCubeMap::releaseTexture() {
  releaseWork();
  m_arrayWidth = 0;
  m_arrayHeight = 0;
}

void CGLibRenderArrayCubeMap::clearTexture(GrlCubeMapFace face, u32 slice, const mm::Col4 &color, GrlClaerMask mask) {
  CGLibDepthCtl::clearColorBuffer(m_colorBuffers[getFaceBufferNum() * face + slice], color, mask);
}

CGLibColorBuffer *CGLibRenderArrayCubeMap::getColorBuffer(GrlCubeMapFace face, u32 slice) { return &m_colorBuffers[getFaceBufferNum() * face + slice]; }

void CGLibRenderArrayCubeMap::clearMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const mm::Col4 &color, GrlClaerMask mask) {
  CGLibDepthCtl::clearColorBuffer(m_colorBuffers[getFaceBufferNum() * face + slice + m_sliceNum * mipmap], color, mask);
}

CGLibColorBuffer *CGLibRenderArrayCubeMap::getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap) { return &m_colorBuffers[getFaceBufferNum() * face + slice + m_sliceNum * mipmap]; }

void CGLibRenderArrayCubeMap::clearIntTexture(GrlCubeMapFace face, u32 slice, const int *color, GrlClaerMask mask) {
  CGLibDepthCtl::clearIntColorBuffer(m_colorBuffers[getFaceBufferNum() * face + slice], color, mask);
}

void CGLibRenderArrayCubeMap::clearIntMipmapTexture(GrlCubeMapFace face, u32 slice, u32 mipmap, const int *color, GrlClaerMask mask) {
  CGLibDepthCtl::clearIntColorBuffer(m_colorBuffers[getFaceBufferNum() * face + slice + m_sliceNum * mipmap], color, mask);
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice) {
  CGLibColorBuffer &target = m_colorBuffers[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setRenderTarget(GrlCubeMapFace face, u32 slice, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[getFaceBufferNum() * face + slice];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap) {
  CGLibColorBuffer &target = m_colorBuffers[getFaceBufferNum() * face + slice + m_sliceNum * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibColorBuffer &colorBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[getFaceBufferNum() * face + slice + m_sliceNum * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterRenderTarget(colorBuffer, GRL_MRT_TYPE_1);
  CGLibState::endRegisterRenderTarget();
}

void CGLibRenderArrayCubeMap::setMipmapRenderTarget(GrlCubeMapFace face, u32 slice, u32 mipmap, CGLibDepthBuffer &depthBuffer) {
  CGLibColorBuffer &target = m_colorBuffers[getFaceBufferNum() * face + slice + m_sliceNum * mipmap];
  CGLibState::setViewport(LibMainStateViewPort(0.0f, 0.0f, target.getWidth(), target.getHeight(), 0.0f, 1.0f));
  CGLibState::beginRegisterRenderTarget();
  CGLibState::setRegisterRenderTarget(target, GRL_MRT_TYPE_0);
  CGLibState::setRegisterDepthTarget(depthBuffer);
  CGLibState::endRegisterRenderTarget();
}

const CGLibColorBuffer *CGLibRenderArrayCubeMap::getColorBuffer(GrlCubeMapFace face, u32 slice) const { return &m_colorBuffers[getFaceBufferNum() * face + slice]; }

const CGLibColorBuffer *CGLibRenderArrayCubeMap::getMipmapColorBuffer(GrlCubeMapFace face, u32 slice, u32 mipmap) const {
  return &m_colorBuffers[getFaceBufferNum() * face + slice + m_sliceNum * mipmap];
}

void CGLibDepthBuffer::delayRelease() {
  if ((m_flags & (FLAG_INITIALIZED | FLAG_OWN_BUFFER)) == 0) {
    return;
  }
  void *buffer = (m_flags & FLAG_OWN_BUFFER) ? m_buffer : nullptr;
  m_buffer = nullptr;
  m_bufferSize = 0;
  NVNtexture *texture = (m_flags & FLAG_INITIALIZED) ? m_nvnTexture : nullptr;
  m_flags &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
  context::CGLibSystemContext::get()->releaseDelayTexture(texture, buffer, -1, -1);
}

CGLibTextureBuffer::CGLibTextureBuffer() {
  m_flags = 0;
  m_buffer = nullptr;
  m_bufferSize = 0;
  m_textureId = -1;
  m_samplerId = -1;
  m_nvnTexture = nullptr;
  m_gpuAddress = 0;
}

CGLibTextureBuffer::~CGLibTextureBuffer() { release(); }

void CGLibTextureBuffer::release() {
  if (m_flags & FLAG_OWN_BUFFER) {
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  } else {
    m_buffer = nullptr;
  }
  m_bufferSize = 0;
  m_gpuAddress = 0;
  if (m_flags & FLAG_INITIALIZED) {
    nvnTextureFinalize(m_nvnTexture);
    context::CGLibSystemContext::get()->m_buffTexture.freeBuffer(m_nvnTexture);
  }
  m_memPool.release();
  if (m_textureId != -1) {
    context::CGLibSystemContext::get()->m_texDescriptor.freeID(m_textureId);
    m_textureId = -1;
  }
  if (m_samplerId != -1) {
    context::CGLibSystemContext::get()->m_texDescriptor.freeID(m_samplerId);
    m_samplerId = -1;
  }
  m_flags &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
}

u16 CGLibTextureBuffer::getSlice() const { return m_slice; }

bool CGLibTextureBuffer::isTexture1D() const { return m_dimension == 1; }

bool CGLibTextureBuffer::isTexture2D() const { return m_dimension == 0; }

bool CGLibTextureBuffer::isTexture3D() const { return m_dimension == 5; }

void CGLibTextureBuffer::setTexturePass(CGLibTextureBuffer &texture) {}

void CGLibTextureBuffer::invalidate() {}

bool CGLibTextureBuffer::isInitialized() const { return m_flags & FLAG_INITIALIZED; }

f32 CGLibTextureBuffer::get1PixelTextureInfo() {
  f32 info;
  CGLibTexture::get1PixelTextureInfo(&info, *this);
  return info;
}

void CGLibTextureBuffer::writeDDS(const char *path, bool isMipmap) {}

CGLibColorBuffer::CGLibColorBuffer() { m_flags = 0; }

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
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->m_device);
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

bool CGLibColorBuffer::isInitialized() const { return m_flags & FLAG_INITIALIZED; }

CGLibDepthBuffer::CGLibDepthBuffer() {
  m_flags = 0;
  m_bufferSize = 0;
  m_gpuAddress = 0;
  m_buffer = nullptr;
}

CGLibDepthBuffer::~CGLibDepthBuffer() { release(); }

void CGLibDepthBuffer::release() {
  if (m_flags & FLAG_OWN_BUFFER) {
    if (m_buffer != nullptr) {
      mtl::MemManager::deallocate(m_buffer, 0, false);
      m_buffer = nullptr;
    }
  } else {
    m_buffer = nullptr;
  }
  m_gpuAddress = 0;
  m_bufferSize = 0;
  if (m_flags & FLAG_INITIALIZED) {
    nvnTextureFinalize(m_nvnTexture);
    context::CGLibSystemContext::get()->m_buffTexture.freeBuffer(m_nvnTexture);
  }
  m_flags &= ~(FLAG_INITIALIZED | FLAG_OWN_BUFFER);
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
  nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->m_device);
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

bool CGLibDepthBuffer::isInitialized() const { return m_flags & FLAG_INITIALIZED; }

} // namespace grlib
