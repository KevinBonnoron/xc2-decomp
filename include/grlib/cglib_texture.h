#pragma once
#include "grlib/cglib_manager.h"
#include "grlib/cglib_texture_buffer.h"
#include "nvn/nvn.h"
#include "types.h"

namespace grlib {

struct CGLibTexSwizzle;

class CGLibTexture {
public:
  // Inferred role: texture builder setup shared by the size queries; original name unknown.
  static void unknown001(NVNtextureBuilder &builder, NVNtextureTarget target, int format) {
    nvnTextureBuilderSetDefaults(&builder);
    nvnTextureBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
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
  static bool createTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, bool, const CGLibTexSwizzle *swizzle, bool);
  static bool createMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize, bool, const CGLibTexSwizzle *swizzle, bool);
  static bool changeTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size);
  static bool changeMixTextureImagePtrs(CGLibTextureBuffer &texture, const void *data, u32 size, u32 mixSize);
};

} // namespace grlib
