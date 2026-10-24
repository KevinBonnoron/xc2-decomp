#include "grlib/cglib_acc_util_texture.h"

#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_util_pixel.h"
#include "nn/os.h"

namespace grlib {

CGLibAccUtilTexture::ReadF32Call CGLibAccUtilTexture::s_pReadF32Call[] = {
    &CGLibAccUtilTexture::texaccread_f32_8,
    &CGLibAccUtilTexture::texaccread_f32_16_float,
    &CGLibAccUtilTexture::texaccread_f32_16_int,
    &CGLibAccUtilTexture::texaccread_f32_16_uint,
    &CGLibAccUtilTexture::texaccread_f32_16_unom,
    &CGLibAccUtilTexture::texaccread_f32_32_float,
    &CGLibAccUtilTexture::texaccread_f32_32_int,
    &CGLibAccUtilTexture::texaccread_f32_32_uint,
    &CGLibAccUtilTexture::texaccread_f32_err,
};
CGLibAccUtilTexture::ReadIntCall CGLibAccUtilTexture::s_pReadIntCall[] = {
    &CGLibAccUtilTexture::texaccread_int_8,
    &CGLibAccUtilTexture::texaccread_int_16_float,
    &CGLibAccUtilTexture::texaccread_int_16_int,
    &CGLibAccUtilTexture::texaccread_int_16_uint,
    &CGLibAccUtilTexture::texaccread_int_16_unom,
    &CGLibAccUtilTexture::texaccread_int_32_float,
    &CGLibAccUtilTexture::texaccread_int_32_int,
    &CGLibAccUtilTexture::texaccread_int_32_uint,
    &CGLibAccUtilTexture::texaccread_int_err,
};
CGLibAccUtilTexture::WriteF32Call CGLibAccUtilTexture::s_pWriteF32Call[] = {
    &CGLibAccUtilTexture::texaccwrite_f32_8,
    &CGLibAccUtilTexture::texaccwrite_f32_16_float,
    &CGLibAccUtilTexture::texaccwrite_f32_16_int,
    &CGLibAccUtilTexture::texaccwrite_f32_16_uint,
    &CGLibAccUtilTexture::texaccwrite_f32_16_unom,
    &CGLibAccUtilTexture::texaccwrite_f32_32_float,
    &CGLibAccUtilTexture::texaccwrite_f32_32_int,
    &CGLibAccUtilTexture::texaccwrite_f32_32_uint,
    &CGLibAccUtilTexture::texaccwrite_f32_err,
};
CGLibAccUtilTexture::WriteIntCall CGLibAccUtilTexture::s_pWriteIntCall[] = {
    &CGLibAccUtilTexture::texaccwrite_int_8,
    &CGLibAccUtilTexture::texaccwrite_int_16_float,
    &CGLibAccUtilTexture::texaccwrite_int_16_int,
    &CGLibAccUtilTexture::texaccwrite_int_16_uint,
    &CGLibAccUtilTexture::texaccwrite_int_16_unom,
    &CGLibAccUtilTexture::texaccwrite_int_32_float,
    &CGLibAccUtilTexture::texaccwrite_int_32_int,
    &CGLibAccUtilTexture::texaccwrite_int_32_uint,
    &CGLibAccUtilTexture::texaccwrite_int_err,
};
CGLibAccUtilTexture::ReadF32Channel CGLibAccUtilTexture::s_pReadF32Channel[] = {
    &CGLibAccUtilTexture::texaccread_f32_r,
    &CGLibAccUtilTexture::texaccread_f32_rg,
    &CGLibAccUtilTexture::texaccread_f32_rgba,
};
CGLibAccUtilTexture::ReadIntChannel CGLibAccUtilTexture::s_pReadIntChannel[] = {
    &CGLibAccUtilTexture::texaccread_int_r,
    &CGLibAccUtilTexture::texaccread_int_rg,
    &CGLibAccUtilTexture::texaccread_int_rgba,
};
CGLibAccUtilTexture::WriteF32Channel CGLibAccUtilTexture::s_pWriteF32Channel[] = {
    &CGLibAccUtilTexture::texaccwrite_f32_r,
    &CGLibAccUtilTexture::texaccwrite_f32_rg,
    &CGLibAccUtilTexture::texaccwrite_f32_rgba,
};
CGLibAccUtilTexture::WriteIntChannel CGLibAccUtilTexture::s_pWriteIntChannel[] = {
    &CGLibAccUtilTexture::texaccwrite_int_r,
    &CGLibAccUtilTexture::texaccwrite_int_rg,
    &CGLibAccUtilTexture::texaccwrite_int_rgba,
};

u16 CGLibTextureBuffer::getWidth() const { return m_width; }

u16 CGLibTextureBuffer::getHeight() const { return m_height; }

GrlSurfaceFormat CGLibTextureBuffer::getFormat() const { return m_format; }

CGLibAcc1DTexture::CGLibAcc1DTexture() : unknown98(false), unknown99(false) {}

CGLibAcc1DTexture::~CGLibAcc1DTexture() {}

bool CGLibAcc1DTexture::lock(CGLibTextureBuffer &texture) {
  setup1DTexutreInfo(texture);
  unknown98 = true;
  unknowna0 = &texture;
  return true;
}

void CGLibAccUtilTexture::setup1DTexutreInfo(CGLibTextureBuffer &texture) {
  unknown4c = texture.getWidth();
  unknown88 = false;
  unknown50 = 1;
  unknown54 = 1;
  unknown58 = unknown4c * unknown50;
  unknown40 = getCalcChanel(texture.getFormat());
  unknown48 = unknown40 - 1 > 2 ? 2 : unknown40 - 1;
  unknown44 = texture.get1PixelImageSize();
  AccCalcType calcType = getCalcType(texture.getFormat());
  unknown00 = s_pReadF32Call[calcType];
  unknown10 = s_pReadIntCall[calcType];
  unknown20 = s_pWriteF32Call[calcType];
  unknown30 = s_pWriteIntCall[calcType];
  m_buffer = static_cast<u8 *>(texture.m_buffer);
  unknown74 = texture.unknown30;
  setupFormatParam();
}

void CGLibAcc1DTexture::unlock() {
  if (unknown99) {
    textureFlush(*unknowna0);
  }
}

void CGLibAccUtilTexture::textureFlush(CGLibTextureBuffer &texture) { nn::os::FlushDataCache(texture.m_buffer, texture.unknown30); }

CGLibAcc2DTexture::CGLibAcc2DTexture() : unknown98(0), unknown9c(0), unknowna0(false), unknowna1(false), unknowna2(false) {}

CGLibAcc2DTexture::~CGLibAcc2DTexture() {}

bool CGLibAcc2DTexture::lock(CGLibTextureBuffer &texture) {
  unknowna8 = &texture;
  unknowna0 = true;
  setup2DTexutreInfo(texture, 0);
  return true;
}

void CGLibAccUtilTexture::setup2DTexutreInfo(CGLibTextureBuffer &texture, u32 mipmap) {
  u32 width = texture.getWidth();
  u32 height = texture.getHeight();
  if (mipmap != 0) {
    width >>= mipmap;
    height >>= mipmap;
    if (width == 0) {
      width = 1;
    }
    if (height == 0) {
      height = 1;
    }
  }

  unknown4c = width;
  unknown50 = height;
  unknown54 = 1;
  unknown58 = unknown4c * unknown50;
  unknown40 = getCalcChanel(texture.getFormat());
  unknown48 = unknown40 - 1 > 2 ? 2 : unknown40 - 1;
  unknown44 = texture.get1PixelImageSize();
  AccCalcType calcType = getCalcType(texture.getFormat());
  unknown00 = s_pReadF32Call[calcType];
  unknown10 = s_pReadIntCall[calcType];
  unknown20 = s_pWriteF32Call[calcType];
  unknown30 = s_pWriteIntCall[calcType];
  m_buffer = static_cast<u8 *>(texture.m_buffer);
  unknown74 = texture.unknown30;
  setupFormatParam();
  unknown88 = (texture.unknown10 >> 5) & 1;
}

bool CGLibAcc2DTexture::lockMipmap(CGLibTextureBuffer &texture, u32 mipmap) {
  if (mipmap < texture.getMipmap()) {
    unknown98 = mipmap;
    unknowna8 = &texture;
    unknowna0 = true;
    setup2DTexutreInfo(texture, mipmap);
    return true;
  }
  return false;
}

u16 CGLibTextureBuffer::getMipmap() const { return m_mipmap; }

bool CGLibAcc2DTexture::lockCubemap(CGLibTextureBuffer &texture, u32 face) {
  if (face < texture.getDepth()) {
    unknown9c = face;
    unknowna8 = &texture;
    unknowna0 = true;
    unknowna2 = true;
    setupCubeTexutreInfo(texture, face, 0);
    return true;
  }
  return false;
}

u16 CGLibTextureBuffer::getDepth() const { return m_depth; }

void CGLibAccUtilTexture::setupCubeTexutreInfo(CGLibTextureBuffer &texture, u32 face, u32 mipmap) {
  u32 width = texture.getWidth();
  u32 height = texture.getHeight();
  if (mipmap != 0) {
    width >>= mipmap;
    height >>= mipmap;
    if (width == 0) {
      width = 1;
    }
    if (height == 0) {
      height = 1;
    }
  }

  unknown4c = width;
  unknown50 = height;
  unknown54 = 1;
  unknown58 = unknown4c * unknown50;
  unknown40 = getCalcChanel(texture.getFormat());
  unknown48 = unknown40 - 1 > 2 ? 2 : unknown40 - 1;
  unknown44 = texture.get1PixelImageSize();
  AccCalcType calcType = getCalcType(texture.getFormat());
  unknown00 = s_pReadF32Call[calcType];
  unknown10 = s_pReadIntCall[calcType];
  unknown20 = s_pWriteF32Call[calcType];
  unknown30 = s_pWriteIntCall[calcType];
  m_buffer = static_cast<u8 *>(texture.m_buffer);
  unknown74 = texture.unknown30;
  unknown88 = false;
  setupFormatParam();
}

bool CGLibAcc2DTexture::lockCubemapMipmap(CGLibTextureBuffer &texture, u32 face, u32 mipmap) {
  if (face < texture.getDepth() && mipmap < texture.getMipmap()) {
    unknown98 = mipmap;
    unknown9c = face;
    unknowna8 = &texture;
    unknowna0 = true;
    unknowna2 = true;
    setupCubeTexutreInfo(texture, face, mipmap);
    return true;
  }
  return false;
}

void CGLibAcc2DTexture::unlock() {
  if (unknowna1) {
    textureFlush(*unknowna8);
  }
}

void CGLibAcc2DTexture::getFloat(f32 &r, u32 x, u32 y) {
  f32 values[4];
  getF32(values, x, y);
  r = values[0];
}

void CGLibAcc2DTexture::getFloat(f32 &r, f32 &g, u32 x, u32 y) {
  f32 values[4];
  getF32(values, x, y);
  r = values[0];
  g = values[1];
}

void CGLibAcc2DTexture::getFloat(f32 &r, f32 &g, f32 &b, u32 x, u32 y) {
  f32 values[4];
  getF32(values, x, y);
  r = values[0];
  g = values[1];
  b = values[2];
}

void CGLibAcc2DTexture::getFloat(f32 &r, f32 &g, f32 &b, f32 &a, u32 x, u32 y) {
  f32 values[4];
  getF32(values, x, y);
  r = values[0];
  g = values[1];
  b = values[2];
  a = values[3];
}

void CGLibAcc2DTexture::getInt(int &r, u32 x, u32 y) {
  int values[4];
  CGLibAccUtilTexture::getInt(values, x, y);
  r = values[0];
}

void CGLibAcc2DTexture::getInt(int &r, int &g, u32 x, u32 y) {
  int values[4];
  CGLibAccUtilTexture::getInt(values, x, y);
  r = values[0];
  g = values[1];
}

void CGLibAcc2DTexture::getInt(int &r, int &g, int &b, u32 x, u32 y) {
  int values[4];
  CGLibAccUtilTexture::getInt(values, x, y);
  r = values[0];
  g = values[1];
  b = values[2];
}

void CGLibAcc2DTexture::getInt(int &r, int &g, int &b, int &a, u32 x, u32 y) {
  int values[4];
  CGLibAccUtilTexture::getInt(values, x, y);
  r = values[0];
  g = values[1];
  b = values[2];
  a = values[3];
}

void CGLibAcc2DTexture::setFloat(f32 r, u32 x, u32 y) {
  f32 values[4] = {r, 0.0f, 0.0f, 1.0f};
  setF32(values, x, y);
  unknowna1 = true;
}

void CGLibAcc2DTexture::setFloat(f32 r, f32 g, u32 x, u32 y) {
  f32 values[4] = {r, g, 0.0f, 1.0f};
  setF32(values, x, y);
  unknowna1 = true;
}

void CGLibAcc2DTexture::setFloat(f32 r, f32 g, f32 b, u32 x, u32 y) {
  f32 values[4] = {r, g, b, 1.0f};
  setF32(values, x, y);
  unknowna1 = true;
}

void CGLibAcc2DTexture::setFloat(f32 r, f32 g, f32 b, f32 a, u32 x, u32 y) {
  f32 values[4] = {r, g, b, a};
  setF32(values, x, y);
  unknowna1 = true;
}

void CGLibAcc2DTexture::setInt(int r, u32 x, u32 y) {
  int values[4] = {r, 0, 0, 0};
  CGLibAccUtilTexture::setInt(values, x, y);
  unknowna1 = true;
}

void CGLibAcc2DTexture::setInt(int r, int g, u32 x, u32 y) {
  int values[4] = {r, g, 0, 0};
  CGLibAccUtilTexture::setInt(values, x, y);
  unknowna1 = true;
}

void CGLibAcc2DTexture::setInt(int r, int g, int b, u32 x, u32 y) {
  int values[4] = {r, g, b, 0};
  CGLibAccUtilTexture::setInt(values, x, y);
  unknowna1 = true;
}

void CGLibAcc2DTexture::setInt(int r, int g, int b, int a, u32 x, u32 y) {
  int values[4] = {r, g, b, a};
  CGLibAccUtilTexture::setInt(values, x, y);
  unknowna1 = true;
}

CGLibAcc3DTexture::CGLibAcc3DTexture() : unknown98(false) {}

CGLibAcc3DTexture::~CGLibAcc3DTexture() {}

bool CGLibAcc3DTexture::lock(CGLibTextureBuffer &texture) {
  unknowna0 = &texture;
  setup3DTexutreInfo(texture);
  return true;
}

void CGLibAccUtilTexture::setup3DTexutreInfo(CGLibTextureBuffer &texture) {
  unknown4c = texture.getWidth();
  unknown50 = texture.getHeight();
  unknown54 = texture.getDepth();
  unknown58 = unknown4c * unknown50;
  unknown40 = getCalcChanel(texture.getFormat());
  unknown48 = unknown40 - 1 > 2 ? 2 : unknown40 - 1;
  unknown44 = texture.get1PixelImageSize();
  AccCalcType calcType = getCalcType(texture.getFormat());
  unknown00 = s_pReadF32Call[calcType];
  unknown10 = s_pReadIntCall[calcType];
  unknown20 = s_pWriteF32Call[calcType];
  unknown30 = s_pWriteIntCall[calcType];
  m_buffer = static_cast<u8 *>(texture.m_buffer);
  unknown74 = texture.unknown30;
  unknown88 = false;
  setupFormatParam();
}

void CGLibAcc3DTexture::unlock() {
  if (unknown98) {
    textureFlush(*unknowna0);
  }
}

AccCalcType CGLibAccUtilTexture::getCalcType(GrlSurfaceFormat format) const {
  switch (format) {
  case GRL_SURFACE_FORMAT_R8:
  case GRL_SURFACE_FORMAT_R8SN:
  case GRL_SURFACE_FORMAT_R8UI:
  case GRL_SURFACE_FORMAT_R8I:
  case GRL_SURFACE_FORMAT_RG8:
  case GRL_SURFACE_FORMAT_RG8SN:
  case GRL_SURFACE_FORMAT_RG8UI:
  case GRL_SURFACE_FORMAT_RG8I:
  case GRL_SURFACE_FORMAT_RGBA8:
  case GRL_SURFACE_FORMAT_RGBA8SN:
  case GRL_SURFACE_FORMAT_RGBA8UI:
  case GRL_SURFACE_FORMAT_RGBA8I:
  case GRL_SURFACE_FORMAT_RGBA8_SRGB:
    return ACC_CALC_TYPE_8;
  case GRL_SURFACE_FORMAT_R16F:
  case GRL_SURFACE_FORMAT_RG16F:
  case GRL_SURFACE_FORMAT_RGBA16F:
  case GRL_SURFACE_FORMAT_DEPTH24_STENCIL8:
  case GRL_SURFACE_FORMAT_DEPTH32F_STENCIL8:
    return ACC_CALC_TYPE_16_FLOAT;
  case GRL_SURFACE_FORMAT_R16:
  case GRL_SURFACE_FORMAT_R16SN:
  case GRL_SURFACE_FORMAT_RG16:
  case GRL_SURFACE_FORMAT_RG16SN:
  case GRL_SURFACE_FORMAT_RGBA16:
  case GRL_SURFACE_FORMAT_RGBA16SN:
    return ACC_CALC_TYPE_16_UNORM;
  case GRL_SURFACE_FORMAT_R16UI:
  case GRL_SURFACE_FORMAT_RG16UI:
  case GRL_SURFACE_FORMAT_RGBA16UI:
    return ACC_CALC_TYPE_16_UINT;
  case GRL_SURFACE_FORMAT_R16I:
  case GRL_SURFACE_FORMAT_RG16I:
  case GRL_SURFACE_FORMAT_RGBA16I:
    return ACC_CALC_TYPE_16_INT;
  case GRL_SURFACE_FORMAT_R32F:
  case GRL_SURFACE_FORMAT_RG32F:
  case GRL_SURFACE_FORMAT_RGBA32F:
    return ACC_CALC_TYPE_32_FLOAT;
  case GRL_SURFACE_FORMAT_R32UI:
  case GRL_SURFACE_FORMAT_RG32UI:
  case GRL_SURFACE_FORMAT_RGBA32UI:
    return ACC_CALC_TYPE_32_UINT;
  case GRL_SURFACE_FORMAT_R32I:
  case GRL_SURFACE_FORMAT_RG32I:
  case GRL_SURFACE_FORMAT_RGBA32I:
    return ACC_CALC_TYPE_32_INT;
  default:
    return ACC_CALC_TYPE_ERROR;
  }
}

u32 CGLibAccUtilTexture::getCalcChanel(GrlSurfaceFormat format) const {
  switch (format) {
  case GRL_SURFACE_FORMAT_R8:
  case GRL_SURFACE_FORMAT_R8SN:
  case GRL_SURFACE_FORMAT_R8UI:
  case GRL_SURFACE_FORMAT_R8I:
  case GRL_SURFACE_FORMAT_R16F:
  case GRL_SURFACE_FORMAT_R16:
  case GRL_SURFACE_FORMAT_R16SN:
  case GRL_SURFACE_FORMAT_R16UI:
  case GRL_SURFACE_FORMAT_R16I:
  case GRL_SURFACE_FORMAT_R32F:
  case GRL_SURFACE_FORMAT_R32UI:
  case GRL_SURFACE_FORMAT_R32I:
    return 1;
  case GRL_SURFACE_FORMAT_RG8:
  case GRL_SURFACE_FORMAT_RG8SN:
  case GRL_SURFACE_FORMAT_RG8UI:
  case GRL_SURFACE_FORMAT_RG8I:
  case GRL_SURFACE_FORMAT_RG16F:
  case GRL_SURFACE_FORMAT_RG16:
  case GRL_SURFACE_FORMAT_RG16SN:
  case GRL_SURFACE_FORMAT_RG16UI:
  case GRL_SURFACE_FORMAT_RG16I:
  case GRL_SURFACE_FORMAT_RG32F:
  case GRL_SURFACE_FORMAT_RG32UI:
  case GRL_SURFACE_FORMAT_RG32I:
  case GRL_SURFACE_FORMAT_DEPTH24_STENCIL8:
  case GRL_SURFACE_FORMAT_DEPTH32F_STENCIL8:
    return 2;
  default:
    return 4;
  }
}

void CGLibAccUtilTexture::setupFormatParam() {
  unknown5c = 16 / unknown44;
  unknown60 = 2;
  unknown64 = 2;
  unknown68 = 32 / unknown44;
  unknown6c = 8;
  unknown70 = 8;
}

u32 CGLibAccUtilTexture::getSquaringPixel(u32 pixel) const { return pixel; }

u32 CGLibTextureBuffer::get1PixelImageSize() const {
  GrlSurfaceFormat format = m_format;
  switch (format) {
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

void CGLibAccUtilTexture::texaccread_f32_r(f32 *values) { values[0] = (this->*unknown00)(0); }

void CGLibAccUtilTexture::texaccread_f32_rg(f32 *values) {
  values[0] = (this->*unknown00)(0);
  values[1] = (this->*unknown00)(1);
}

void CGLibAccUtilTexture::texaccread_f32_rgba(f32 *values) {
  values[0] = (this->*unknown00)(0);
  values[1] = (this->*unknown00)(1);
  values[2] = (this->*unknown00)(2);
  values[3] = (this->*unknown00)(3);
}

void CGLibAccUtilTexture::texaccread_int_r(int *values) { values[0] = (this->*unknown10)(0); }

void CGLibAccUtilTexture::texaccread_int_rg(int *values) {
  values[0] = (this->*unknown10)(0);
  values[1] = (this->*unknown10)(1);
}

void CGLibAccUtilTexture::texaccread_int_rgba(int *values) {
  values[0] = (this->*unknown10)(0);
  values[1] = (this->*unknown10)(1);
  values[2] = (this->*unknown10)(2);
  values[3] = (this->*unknown10)(3);
}

void CGLibAccUtilTexture::texaccwrite_f32_r(const f32 *values) { (this->*unknown20)(values, 0); }

void CGLibAccUtilTexture::texaccwrite_f32_rg(const f32 *values) {
  (this->*unknown20)(values, 0);
  (this->*unknown20)(values, 1);
}

void CGLibAccUtilTexture::texaccwrite_f32_rgba(const f32 *values) {
  (this->*unknown20)(values, 0);
  (this->*unknown20)(values, 1);
  (this->*unknown20)(values, 2);
  (this->*unknown20)(values, 3);
}

void CGLibAccUtilTexture::texaccwrite_int_r(const int *values) { (this->*unknown30)(values, 0); }

void CGLibAccUtilTexture::texaccwrite_int_rg(const int *values) {
  (this->*unknown30)(values, 0);
  (this->*unknown30)(values, 1);
}

void CGLibAccUtilTexture::texaccwrite_int_rgba(const int *values) {
  (this->*unknown30)(values, 0);
  (this->*unknown30)(values, 1);
  (this->*unknown30)(values, 2);
  (this->*unknown30)(values, 3);
}

f32 CGLibAccUtilTexture::texaccread_f32_8(u32 index) { return unknown80[index] / 255.0f; }

f32 CGLibAccUtilTexture::texaccread_f32_16_float(u32 index) { return CGLibUtilPixel::convF16toF32(*reinterpret_cast<u16 *>(unknown80 + index * 2)); }

f32 CGLibAccUtilTexture::texaccread_f32_16_int(u32 index) { return *reinterpret_cast<s16 *>(unknown80 + index * 2); }

f32 CGLibAccUtilTexture::texaccread_f32_16_uint(u32 index) { return *reinterpret_cast<u16 *>(unknown80 + index * 2); }

f32 CGLibAccUtilTexture::texaccread_f32_16_unom(u32 index) { return *reinterpret_cast<u16 *>(unknown80 + index * 2) / 65535.0f; }

f32 CGLibAccUtilTexture::texaccread_f32_32_float(u32 index) { return *reinterpret_cast<f32 *>(unknown80 + index * 4); }

f32 CGLibAccUtilTexture::texaccread_f32_32_int(u32 index) { return *reinterpret_cast<s32 *>(unknown80 + index * 4); }

f32 CGLibAccUtilTexture::texaccread_f32_32_uint(u32 index) { return *reinterpret_cast<u32 *>(unknown80 + index * 4); }

f32 CGLibAccUtilTexture::texaccread_f32_err(u32 index) { return 0.0f; }

int CGLibAccUtilTexture::texaccread_int_8(u32 index) { return unknown80[index]; }

int CGLibAccUtilTexture::texaccread_int_16_float(u32 index) { return CGLibUtilPixel::convF16toF32(*reinterpret_cast<u16 *>(unknown80 + index * 2)) * 255.0f; }

int CGLibAccUtilTexture::texaccread_int_16_int(u32 index) { return *reinterpret_cast<s16 *>(unknown80 + index * 2); }

int CGLibAccUtilTexture::texaccread_int_16_uint(u32 index) { return *reinterpret_cast<u16 *>(unknown80 + index * 2); }

int CGLibAccUtilTexture::texaccread_int_16_unom(u32 index) { return *reinterpret_cast<u16 *>(unknown80 + index * 2); }

int CGLibAccUtilTexture::texaccread_int_32_float(u32 index) { return *reinterpret_cast<f32 *>(unknown80 + index * 4) * 255.0f; }

int CGLibAccUtilTexture::texaccread_int_32_int(u32 index) { return *reinterpret_cast<s32 *>(unknown80 + index * 4); }

int CGLibAccUtilTexture::texaccread_int_32_uint(u32 index) { return *reinterpret_cast<u32 *>(unknown80 + index * 4); }

int CGLibAccUtilTexture::texaccread_int_err(u32 index) { return 0; }

void CGLibAccUtilTexture::texaccwrite_f32_8(const f32 *values, u32 index) { unknown80[index] = static_cast<int>(values[index] * 255.0f); }

void CGLibAccUtilTexture::texaccwrite_f32_16_float(const f32 *values, u32 index) { *reinterpret_cast<u16 *>(unknown80 + index * 2) = CGLibUtilPixel::convF32toF16(values[index]); }

void CGLibAccUtilTexture::texaccwrite_f32_16_int(const f32 *values, u32 index) { *reinterpret_cast<s16 *>(unknown80 + index * 2) = static_cast<int>(values[index]); }

void CGLibAccUtilTexture::texaccwrite_f32_16_uint(const f32 *values, u32 index) { *reinterpret_cast<u16 *>(unknown80 + index * 2) = static_cast<int>(values[index]); }

void CGLibAccUtilTexture::texaccwrite_f32_16_unom(const f32 *values, u32 index) { *reinterpret_cast<u16 *>(unknown80 + index * 2) = static_cast<int>(values[index] * 65535.0f); }

void CGLibAccUtilTexture::texaccwrite_f32_32_float(const f32 *values, u32 index) { *reinterpret_cast<f32 *>(unknown80 + index * 4) = values[index]; }

void CGLibAccUtilTexture::texaccwrite_f32_32_int(const f32 *values, u32 index) { *reinterpret_cast<s32 *>(unknown80 + index * 4) = static_cast<int>(values[index]); }

void CGLibAccUtilTexture::texaccwrite_f32_32_uint(const f32 *values, u32 index) { *reinterpret_cast<u32 *>(unknown80 + index * 4) = static_cast<int>(values[index]); }

void CGLibAccUtilTexture::texaccwrite_f32_err(const f32 *values, u32 index) {}

void CGLibAccUtilTexture::texaccwrite_int_8(const int *values, u32 index) { unknown80[index] = values[index]; }

void CGLibAccUtilTexture::texaccwrite_int_16_float(const int *values, u32 index) { *reinterpret_cast<u16 *>(unknown80 + index * 2) = CGLibUtilPixel::convF32toF16(values[index] * (1.0f / 255.0f)); }

void CGLibAccUtilTexture::texaccwrite_int_16_int(const int *values, u32 index) { *reinterpret_cast<s16 *>(unknown80 + index * 2) = values[index]; }

void CGLibAccUtilTexture::texaccwrite_int_16_uint(const int *values, u32 index) { *reinterpret_cast<u16 *>(unknown80 + index * 2) = values[index]; }

void CGLibAccUtilTexture::texaccwrite_int_16_unom(const int *values, u32 index) { *reinterpret_cast<u16 *>(unknown80 + index * 2) = values[index]; }

void CGLibAccUtilTexture::texaccwrite_int_32_float(const int *values, u32 index) { *reinterpret_cast<f32 *>(unknown80 + index * 4) = values[index] * (1.0f / 255.0f); }

void CGLibAccUtilTexture::texaccwrite_int_32_int(const int *values, u32 index) { *reinterpret_cast<s32 *>(unknown80 + index * 4) = values[index]; }

void CGLibAccUtilTexture::texaccwrite_int_32_uint(const int *values, u32 index) { *reinterpret_cast<u32 *>(unknown80 + index * 4) = values[index]; }

void CGLibAccUtilTexture::texaccwrite_int_err(const int *values, u32 index) {}

} // namespace grlib
