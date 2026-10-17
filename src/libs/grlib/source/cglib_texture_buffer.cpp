#include "grlib/cglib_texture_buffer.h"

#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tex_descriptor.h"
#include "grlib/cglib_texture.h"
#include "mtl/mem_manager.h"
#include "nvn/nvn.h"

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

u16 CGLibColorBuffer::getWidth() const { return m_width; }

u16 CGLibColorBuffer::getHeight() const { return m_height; }

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
