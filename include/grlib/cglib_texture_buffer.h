#pragma once
#include <stddef.h>

#include "grlib/cglib_vtl_mem_pool.h"
#include "types.h"

enum GrlSurfaceFormat {
  GRL_SURFACE_FORMAT_NONE,
  GRL_SURFACE_FORMAT_R8,
  GRL_SURFACE_FORMAT_R8SN,
  GRL_SURFACE_FORMAT_R8UI,
  GRL_SURFACE_FORMAT_R8I,
  GRL_SURFACE_FORMAT_R16F,
  GRL_SURFACE_FORMAT_R16,
  GRL_SURFACE_FORMAT_R16SN,
  GRL_SURFACE_FORMAT_R16UI,
  GRL_SURFACE_FORMAT_R16I,
  GRL_SURFACE_FORMAT_R32F,
  GRL_SURFACE_FORMAT_R32UI,
  GRL_SURFACE_FORMAT_R32I,
  GRL_SURFACE_FORMAT_RG8,
  GRL_SURFACE_FORMAT_RG8SN,
  GRL_SURFACE_FORMAT_RG8UI,
  GRL_SURFACE_FORMAT_RG8I,
  GRL_SURFACE_FORMAT_RG16F,
  GRL_SURFACE_FORMAT_RG16,
  GRL_SURFACE_FORMAT_RG16SN,
  GRL_SURFACE_FORMAT_RG16UI,
  GRL_SURFACE_FORMAT_RG16I,
  GRL_SURFACE_FORMAT_RG32F,
  GRL_SURFACE_FORMAT_RG32UI,
  GRL_SURFACE_FORMAT_RG32I,
  GRL_SURFACE_FORMAT_RGB8,
  GRL_SURFACE_FORMAT_RGB8SN,
  GRL_SURFACE_FORMAT_RGB8UI,
  GRL_SURFACE_FORMAT_RGB8I,
  GRL_SURFACE_FORMAT_RGB16F,
  GRL_SURFACE_FORMAT_RGB16,
  GRL_SURFACE_FORMAT_RGB16SN,
  GRL_SURFACE_FORMAT_RGB16UI,
  GRL_SURFACE_FORMAT_RGB16I,
  GRL_SURFACE_FORMAT_RGB32F,
  GRL_SURFACE_FORMAT_RGB32UI,
  GRL_SURFACE_FORMAT_RGB32I,
  GRL_SURFACE_FORMAT_RGBA8,
  GRL_SURFACE_FORMAT_RGBA8SN,
  GRL_SURFACE_FORMAT_RGBA8UI,
  GRL_SURFACE_FORMAT_RGBA8I,
  GRL_SURFACE_FORMAT_RGBA16F,
  GRL_SURFACE_FORMAT_RGBA16,
  GRL_SURFACE_FORMAT_RGBA16SN,
  GRL_SURFACE_FORMAT_RGBA16UI,
  GRL_SURFACE_FORMAT_RGBA16I,
  GRL_SURFACE_FORMAT_RGBA32F,
  GRL_SURFACE_FORMAT_RGBA32UI,
  GRL_SURFACE_FORMAT_RGBA32I,
  GRL_SURFACE_FORMAT_STENCIL8,
  GRL_SURFACE_FORMAT_DEPTH16,
  GRL_SURFACE_FORMAT_DEPTH24,
  GRL_SURFACE_FORMAT_DEPTH32F,
  GRL_SURFACE_FORMAT_DEPTH24_STENCIL8,
  GRL_SURFACE_FORMAT_DEPTH32F_STENCIL8,
  GRL_SURFACE_FORMAT_RGBX8_SRGB,
  GRL_SURFACE_FORMAT_RGBA8_SRGB,
  GRL_SURFACE_FORMAT_RGBA4,
  GRL_SURFACE_FORMAT_RGB5,
  GRL_SURFACE_FORMAT_RGB5A1,
  GRL_SURFACE_FORMAT_RGB565,
  GRL_SURFACE_FORMAT_RGB10A2,
  GRL_SURFACE_FORMAT_RGB10A2UI,
  GRL_SURFACE_FORMAT_R11G11B10F,
  GRL_SURFACE_FORMAT_RGB9E5F,
  GRL_SURFACE_FORMAT_RGB_DXT1,
  GRL_SURFACE_FORMAT_RGBA_DXT1,
  GRL_SURFACE_FORMAT_RGBA_DXT3,
  GRL_SURFACE_FORMAT_RGBA_DXT5,
  GRL_SURFACE_FORMAT_RGB_DXT1_SRGB,
  GRL_SURFACE_FORMAT_RGBA_DXT1_SRGB,
  GRL_SURFACE_FORMAT_RGBA_DXT3_SRGB,
  GRL_SURFACE_FORMAT_RGBA_DXT5_SRGB,
  GRL_SURFACE_FORMAT_RGTC1_UNORM,
  GRL_SURFACE_FORMAT_RGTC1_SNORM,
  GRL_SURFACE_FORMAT_RGTC2_UNORM,
  GRL_SURFACE_FORMAT_RGTC2_SNORM,
  GRL_SURFACE_FORMAT_BPTC_UNORM,
  GRL_SURFACE_FORMAT_BPTC_UNORM_SRGB,
  GRL_SURFACE_FORMAT_BPTC_SIGNED_FLOAT,
  GRL_SURFACE_FORMAT_BPTC_UNSIGNED_FLOAT,
};

enum GrlDepthFormat {
  GRL_DEPTH_FORMAT_UNKNOWN_0 = 0x32,
  GRL_DEPTH_FORMAT_UNKNOWN_1,
  GRL_DEPTH_FORMAT_UNKNOWN_2,
  GRL_DEPTH_FORMAT_UNKNOWN_3,
  GRL_DEPTH_FORMAT_UNKNOWN_4,
};

struct NVNtexture;

namespace grlib {

class CGLibTextureBuffer {
public:
  enum Flag {
    FLAG_INITIALIZED = 1 << 0,
    FLAG_OWN_BUFFER = 1 << 1,
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: display texture; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: depth view of a depth stencil texture; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: stencil view of a depth stencil texture; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: linear texture; original name unknown.
  };

  void delayRelease();
  u16 getWidth() const;
  u16 getHeight() const;
  GrlSurfaceFormat getFormat() const;
  u16 getMipmap() const;
  u16 getDepth() const;
  u32 get1PixelImageSize() const;
  u32 getImageSize() const;
  CGLibTextureBuffer();
  ~CGLibTextureBuffer();
  void release();
  u16 getSlice() const;
  bool isTexture1D() const;
  bool isTexture2D() const;
  bool isTexture3D() const;
  void setTexturePass(CGLibTextureBuffer &texture);
  void invalidate();
  bool isInitialized() const;
  f32 get1PixelTextureInfo();
  void writeDDS(const char *path, bool isMipmap);

  GrlSurfaceFormat m_format;
  u16 m_width;
  u16 m_height;
  u16 m_depth;
  u16 m_slice;
  u16 m_mipmap;
  u16 unknown0e; // Inferred role: dimension; original member name unknown.
  u32 unknown10; // Inferred role: flags; original member name unknown.
  u8 _14[0x18 - 0x14];
  NVNtexture *unknown18; // Inferred role: nvn texture; original member name unknown.
  u64 unknown20;         // Inferred role: gpu address; original member name unknown.
  void *m_buffer;
  u32 unknown30;             // Inferred role: buffer size; original member name unknown.
  int unknown34;             // Inferred role: texture id; original member name unknown.
  int unknown38;             // Inferred role: sampler id; original member name unknown.
  CGLibVtlMemPool unknown40; // Inferred role: mem pool; original member name unknown.
};

static_assert(offsetof(CGLibTextureBuffer, unknown10) == 0x10, "");
static_assert(offsetof(CGLibTextureBuffer, unknown18) == 0x18, "");
static_assert(offsetof(CGLibTextureBuffer, m_buffer) == 0x28, "");
static_assert(offsetof(CGLibTextureBuffer, unknown30) == 0x30, "");
static_assert(offsetof(CGLibTextureBuffer, unknown34) == 0x34, "");
static_assert(offsetof(CGLibTextureBuffer, unknown40) == 0x40, "");

} // namespace grlib
