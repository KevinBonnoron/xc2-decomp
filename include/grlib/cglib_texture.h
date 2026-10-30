#pragma once
#include <stddef.h>

#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_color_buffer.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tex_swizzle.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

class CGLibDepthBuffer;

// Inferred role: footer at the end of a packaged texture image (read by createTextureImagePtrs and
// isTextureImagePtrs at the image end minus 0x38); original name unknown.
struct unknown004 {
  u8 _00[0x10];
  u32 unknown10; // Inferred role: image size; original member name unknown.
  u8 _14[0x18 - 0x14];
  u32 unknown18; // Inferred role: width; original member name unknown.
  u32 unknown1c; // Inferred role: height; original member name unknown.
  u32 unknown20; // Inferred role: depth; original member name unknown.
  u32 unknown24; // Inferred role: nvn texture target; original member name unknown.
  u32 unknown28; // Inferred role: format; original member name unknown.
  u32 unknown2c; // Inferred role: mipmap level count; original member name unknown.
  u32 unknown30; // Inferred role: version; original member name unknown.
  u32 unknown34; // Inferred role: magic; original member name unknown.
};

static_assert(offsetof(unknown004, unknown10) == 0x10, "");
static_assert(offsetof(unknown004, unknown30) == 0x30, "");
static_assert(sizeof(unknown004) == 0x38, "");

class CGLibTexture_plf {
public:
  // Inferred role: allocates an NVN texture from the context texture table; original name unknown.
  static NVNtexture *unknown005() {
    context::CGLibSystemContext *context = context::CGLibSystemContext::get();
    u32 id = context->unknowne60.allocID();
    return static_cast<NVNtexture *>(context->unknowne60.unknown00) + id;
  }

  // Inferred role: allocates and initializes the NVN texture of a texture buffer at an offset of a pool; original name unknown.
  static void unknown007(CGLibTextureBuffer &texture, const NVNtextureBuilder &builder, CGLibMemPool &memPool, u32 offset) {
    texture.unknown18 = unknown005();
    texture.unknown20 = nvnMemoryPoolGetBufferAddress(memPool.m_memoryPool) + offset;
    nvnTextureInitialize(texture.unknown18, &builder);
  }

  // Inferred role: sets the description of a texture buffer before its setup; original name unknown.
  static void unknown008(CGLibTextureBuffer &texture, u16 dimension, u32 width, u32 height, u32 depth, u32 slice, u32 mipmap, GrlSurfaceFormat format) {
    texture.unknown0e = dimension;
    texture.m_width = width;
    texture.m_height = height;
    texture.m_depth = depth;
    texture.m_slice = slice;
    texture.m_mipmap = mipmap;
    texture.m_format = format;
    texture.unknown10 |= CGLibTextureBuffer::FLAG_INITIALIZED;
  }

  // Inferred role: storage, flags and texture setup shared by the cubemap, volume and array setups; original name unknown.
  static void unknown009(CGLibTextureBuffer &texture, NVNtextureBuilder &builder, CGLibMemPool &memPool, u32 offset) {
    nvnTextureBuilderSetStorage(&builder, memPool.m_memoryPool, offset);
    nvnTextureBuilderSetFlags(&builder, NVN_TEXTURE_FLAGS_IMAGE | NVN_TEXTURE_FLAGS_COMPRESSIBLE);
    unknown007(texture, builder, memPool, offset);
  }

  static void setupTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset);
  static void setup1DTextureBuff(CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset);
  static void setupDepthBuff(CGLibDepthBuffer &depthBuffer, u32 width, u32 height, GrlDepthFormat format, CGLibMemPool &memPool, u32 offset);
  static void setupCubemapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset);
  static void setupVolumeTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset);
  static void setupTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset);
  static void setupCubeMapTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, CGLibMemPool &memPool, u32 offset);
  static void allocTextureID(CGLibTextureBuffer &texture, bool isImage);

  static const u32 s_CubeMapFaceTable[6];
};

class CGLibTexture {
public:
  // Inferred role: texture builder defaults and device shared by the size queries and setups; original name unknown.
  static void unknown006(NVNtextureBuilder &builder) {
    nvnTextureBuilderSetDefaults(&builder);
    nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  }

  // Inferred role: texture builder setup shared by the size queries; original name unknown.
  static void unknown001(NVNtextureBuilder &builder, NVNtextureTarget target, int format) {
    unknown006(builder);
    nvnTextureBuilderSetTarget(&builder, target);
    nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(format));
  }

  // Inferred role: texture builder setup of a 2D size shared by the size queries; original name unknown.
  static void unknown001(NVNtextureBuilder &builder, NVNtextureTarget target, int format, u32 width, u32 height) {
    unknown001(builder, target, format);
    nvnTextureBuilderSetSize2D(&builder, width, height);
  }

  // Inferred role: texture builder storage query shared by the size queries; original name unknown.
  static void unknown002(NVNtextureBuilder &builder, int flags, u32 &size, u32 &alignment) {
    nvnTextureBuilderSetFlags(&builder, flags);
    size = nvnTextureBuilderGetStorageSize(&builder);
    alignment = nvnTextureBuilderGetStorageAlignment(&builder);
  }

  // Inferred role: row stride of a linear texture aligned to the linear texture stride; original name unknown.
  static u32 unknown010(u32 width, GrlSurfaceFormat format) {
    u32 size = get1PixelSize(format) * width;
    u32 stride = context::CGLibSystemContext::s_nLinerTextureStride;
    return size + (stride - size % stride) % stride;
  }

  // Inferred role: attaches an allocated own pixel buffer to a texture buffer and returns its offset in the pixel pool;
  // original name unknown.
  static u32 unknown021(CGLibTextureBuffer &texture, void *buffer, u32 size) {
    texture.m_buffer = buffer;
    texture.unknown30 = size;
    texture.unknown10 |= CGLibTextureBuffer::FLAG_OWN_BUFFER;
    return static_cast<u8 *>(texture.m_buffer) - static_cast<u8 *>(context::CGLibSystemContext::get()->unknown2478.unknown18);
  }

  // Inferred role: texture builder setup from a packaged texture footer, a mix texture having twice the size and one
  // more level; original name unknown.
  static void unknown011(NVNtextureBuilder &builder, const unknown004 *footer, const void *data, bool isMix) {
    nvnTextureBuilderSetDefaults(&builder);
    nvnTextureBuilderSetTarget(&builder, static_cast<NVNtextureTarget>(footer->unknown24));
    nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(footer->unknown28));
    if (isMix) {
      nvnTextureBuilderSetSize2D(&builder, footer->unknown18 * 2, footer->unknown1c * 2);
    } else {
      nvnTextureBuilderSetSize2D(&builder, footer->unknown18, footer->unknown1c);
    }
    nvnTextureBuilderSetDepth(&builder, footer->unknown20);
    nvnTextureBuilderSetLevels(&builder, isMix ? footer->unknown2c + 1 : footer->unknown2c);
    nvnTextureBuilderSetPackagedTextureData(&builder, data);
    nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  }

  // Inferred role: offset of packaged texture data in the memory pool holding it, the texture's own pool taking the data
  // when no pool holds it; original name unknown.
  static ptrdiff_t unknown012(CGLibTextureBuffer &texture, const CGLibMemPool *memPool, const void *data, u32 size) {
    if (memPool != nullptr) {
      return static_cast<const u8 *>(data) - static_cast<const u8 *>(memPool->unknown18);
    }
    texture.unknown40.setupBuffer(const_cast<void *>(data), size);
    return 0;
  }

  // Inferred role: texture storage in the memory pool holding packaged texture data or in the texture's own pool; original name unknown.
  static void unknown013(CGLibTextureBuffer &texture, NVNtextureBuilder &builder, const CGLibMemPool *memPool, ptrdiff_t offset) {
    NVNbufferAddress address;
    if (memPool != nullptr) {
      nvnTextureBuilderSetStorage(&builder, memPool->m_memoryPool, offset);
      address = nvnMemoryPoolGetBufferAddress(memPool->m_memoryPool);
    } else {
      nvnTextureBuilderSetStorage(&builder, texture.unknown40.unknown00, offset);
      address = texture.unknown40.unknown08;
    }
    texture.unknown20 = address + offset;
  }

  // Inferred role: texture builder format of a packaged texture, in sRGB when asked; original name unknown.
  static void unknown014(NVNtextureBuilder &builder, const unknown004 *footer, bool isSrgb) {
    if (isSrgb) {
      switch (footer->unknown28) {
      // Original game bug: the sRGB format of the compressed formats is replaced by the format set below.
      case GRL_SURFACE_FORMAT_RGBA_DXT1:
        nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(GRL_SURFACE_FORMAT_RGBA_DXT1_SRGB));
        break;
      case GRL_SURFACE_FORMAT_RGBA_DXT5:
        nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(GRL_SURFACE_FORMAT_RGBA_DXT5_SRGB));
        break;
      case GRL_SURFACE_FORMAT_RGBA8:
        nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(GRL_SURFACE_FORMAT_RGBA8_SRGB));
        return;
      }
      nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(footer->unknown28));
    } else {
      nvnTextureBuilderSetFormat(&builder, static_cast<NVNformat>(footer->unknown28));
    }
  }

  // Inferred role: description of a created packaged texture, a mix texture having twice the size and one more level;
  // original name unknown.
  static void unknown015(CGLibTextureBuffer &texture, const unknown004 *footer, bool isMix) {
    texture.unknown0e = 0;
    if (isMix) {
      texture.m_width = footer->unknown18 * 2;
      texture.m_height = footer->unknown1c * 2;
    } else {
      texture.m_width = footer->unknown18;
      texture.m_height = footer->unknown1c;
    }
    texture.m_depth = footer->unknown20;
    texture.m_slice = 0;
    texture.m_mipmap = isMix ? footer->unknown2c : footer->unknown2c - 1;
    texture.m_format = static_cast<GrlSurfaceFormat>(footer->unknown28);
    texture.unknown10 |= CGLibTextureBuffer::FLAG_INITIALIZED;
  }

  // Inferred role: texture builder swizzle of a created packaged texture, single channel formats being read as grey;
  // original name unknown.
  static void unknown016(NVNtextureBuilder &builder, const unknown004 *footer, const CGLibTexSwizzle *swizzle) {
    if (swizzle != nullptr) {
      nvnTextureBuilderSetSwizzle(&builder,
                                  static_cast<NVNtextureSwizzle>(swizzle->unknown00),
                                  static_cast<NVNtextureSwizzle>(swizzle->unknown04),
                                  static_cast<NVNtextureSwizzle>(swizzle->unknown08),
                                  static_cast<NVNtextureSwizzle>(swizzle->unknown0c));
    } else if (footer->unknown28 == GRL_SURFACE_FORMAT_RGTC1_UNORM || footer->unknown28 == GRL_SURFACE_FORMAT_R8) {
      nvnTextureBuilderSetSwizzle(&builder, NVN_TEXTURE_SWIZZLE_R, NVN_TEXTURE_SWIZZLE_R, NVN_TEXTURE_SWIZZLE_R, NVN_TEXTURE_SWIZZLE_ONE);
    }
  }

  static u32 get1PixelSize(GrlSurfaceFormat format);
  static u32 get1DepthPixelSize(GrlDepthFormat format);
  static void get1DPixelSize(u32 &size, u32 &alignment, u32 width, GrlSurfaceFormat format);
  static void getDefPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format);
  static void getCubePixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format);
  static void getArrayCubePixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format);
  static void getVolumePixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 depth, GrlSurfaceFormat format);
  static void getArrayPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format);
  static void getDepthPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, GrlDepthFormat format);
  static void get1PixelTextureInfo(f32 *info, CGLibTextureBuffer &texture);
  static void createTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format);
  static void create1DTextureBuff(CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format, u32 offset);
  static void create1DTextureBuff(CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format);
  static void create1DColorTextureBuff(CGLibColorBuffer &colorBuffer, CGLibTextureBuffer &texture, u32 width, GrlSurfaceFormat format);
  static void createTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format, u32 offset);
  static void createColorTextureBuff(CGLibColorBuffer &colorBuffer, CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format);
  static void createTextureMipMapBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, u32 offset);
  static void createTextureMipMapBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format);
  static void createColorTextureMipMapBuff(CGLibColorBuffer *colorBuffers, CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format);
  static void createTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, u32 offset);
  static void createTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format);
  static void createCubemapMipMapColorTextureBuff(CGLibColorBuffer (*colorBuffers)[16], CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format);
  static void createCubemapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format, u32 offset);
  static void createCubemapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format);
  static void createCubemapColorTextureBuff(CGLibColorBuffer *colorBuffers, CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format);
  static void createCubemapMipMapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format, u32 offset);
  static void createCubemapMipMapTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, GrlSurfaceFormat format);
  static void createCubeMapTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format, u32 offset);
  static void createCubeMapTextureArrayBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 slice, u32 mipmap, GrlSurfaceFormat format);
  static void createVolumeTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format, u32 offset);
  static void createVolumeTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format);
  static void createVolumeColorTextureBuff(CGLibColorBuffer *colorBuffers, CGLibTextureBuffer &texture, u32 width, u32 height, u32 depth, GrlSurfaceFormat format);
  static void createDepthTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &texture, u32 width, u32 height, GrlDepthFormat format, u32 offset);
  static void createDepthTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &texture, u32 width, u32 height, GrlDepthFormat format);
  static void createDepthStencilTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &depthTexture, CGLibTextureBuffer &stencilTexture, u32 width, u32 height, GrlDepthFormat format,
                                            u32 offset);
  static void createDepthStencilTextureBuff(CGLibDepthBuffer &depthBuffer, CGLibTextureBuffer &depthTexture, CGLibTextureBuffer &stencilTexture, u32 width, u32 height, GrlDepthFormat format);

  // Inferred role: color buffer description and texture view setup shared by the create*ColorTextureBuff functions; original name unknown.
  static void unknown020(CGLibColorBuffer &colorBuffer, CGLibTextureBuffer &texture, u32 width, u32 height, u32 mipmap, u32 slice, GrlSurfaceFormat format, NVNtextureTarget target) {
    colorBuffer.m_width = width;
    colorBuffer.m_height = height;
    colorBuffer.m_mipmap = mipmap;
    colorBuffer.m_slice = slice;
    colorBuffer.m_format = format;
    colorBuffer.unknown0c = CGLibColorBuffer::FLAG_INITIALIZED;
    colorBuffer.unknown38 = texture.unknown18;
    nvnTextureViewSetDefaults(&colorBuffer.unknown10);
    nvnTextureViewSetFormat(&colorBuffer.unknown10, static_cast<NVNformat>(format));
    nvnTextureViewSetTarget(&colorBuffer.unknown10, target);
  }

  static void createTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, bool isSrgb, const CGLibTexSwizzle *swizzle, bool);
  static void createMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize, bool isSrgb, const CGLibTexSwizzle *swizzle, bool);
  static void changeTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size);
  static void changeMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize);
  static void copyTextureBuff(CGLibTextureBuffer &dst, CGLibTextureBuffer &src);
  static void createDepthBuff(CGLibDepthBuffer &depthBuffer, u32 width, u32 height, GrlDepthFormat format);
  static void createDepthBuff(CGLibDepthBuffer &depthBuffer, u32 width, u32 height, GrlDepthFormat format, u32 offset);
  static bool isTextureImagePtrs(const void *data, u32 size);
  static void createLinerTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format);
  static void getLinerPixelSize(u32 &size, u32 &alignment, u32 width, u32 height, GrlSurfaceFormat format);
  static void createLinerTextureBuff(CGLibTextureBuffer &texture, u32 width, u32 height, GrlSurfaceFormat format, u32 offset);
  static void changeTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, CGLibVtlMemPool &memPool, u32 offset);
  static void changeMixTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, u32 mixSize, CGLibVtlMemPool &memPool, u32 offset);
  static void createTextureImagePtrs(CGLibTextureBuffer &texture, const void *, u32, const void *data, u32 size, bool isSrgb, const CGLibTexSwizzle *swizzle, bool);
  static void createTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, CGLibVtlMemPool &memPool, u32 offset, bool isSrgb, const CGLibTexSwizzle *swizzle, bool);
  static void createTextureImagePtrs(CGLibTextureBuffer &texture, u32, u32 size, CGLibVtlMemPool &, CGLibVtlMemPool &memPool, u32, u32 offset, bool isSrgb, const CGLibTexSwizzle *swizzle, bool);
  static void createMixTextureImagePtrs(CGLibTextureBuffer &texture, u32 size, u32 mixSize, CGLibVtlMemPool &memPool, u32 offset, bool isSrgb, const CGLibTexSwizzle *swizzle, bool);
};

} // namespace grlib
