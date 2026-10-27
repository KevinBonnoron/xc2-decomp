#include "grlib/cglib_texture.h"

#include "grlib/cglib_texture_buffer.h"
#include "nvn/nvn.h"

namespace grlib {

namespace {

const u32 unknown003[] = {
    // Inferred role: bytes per pixel by surface format; original table name unknown.
    1, 1, 1, 1, 2, 2,  2,  2,  2, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 4, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4,
    8, 8, 8, 8, 8, 16, 16, 16, 0, 0, 0, 0, 4, 4, 0, 4, 2, 0, 2, 2, 4, 4, 4, 0, 0, 1, 2, 2, 0, 1, 2, 2, 1, 1, 2, 2, 4, 0, 4, 4,
};

} // namespace

u32 CGLibTexture::get1PixelSize(GrlSurfaceFormat format) {
  if (format - 1U < 0x50) {
    return unknown003[format - 1];
  }
  return 0;
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

} // namespace grlib
