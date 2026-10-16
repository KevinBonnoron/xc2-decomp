#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {

enum AccCalcType {
  ACC_CALC_TYPE_8,
  ACC_CALC_TYPE_16_FLOAT,
  ACC_CALC_TYPE_16_INT,
  ACC_CALC_TYPE_16_UINT,
  ACC_CALC_TYPE_16_UNORM,
  ACC_CALC_TYPE_32_FLOAT,
  ACC_CALC_TYPE_32_INT,
  ACC_CALC_TYPE_32_UINT,
  ACC_CALC_TYPE_ERROR,
};

class CGLibAccUtilTexture {
public:
  typedef f32 (CGLibAccUtilTexture::*ReadF32Call)(u32 index);
  typedef int (CGLibAccUtilTexture::*ReadIntCall)(u32 index);
  typedef void (CGLibAccUtilTexture::*WriteF32Call)(const f32 *values, u32 index);
  typedef void (CGLibAccUtilTexture::*WriteIntCall)(const int *values, u32 index);
  typedef void (CGLibAccUtilTexture::*ReadF32Channel)(f32 *values);
  typedef void (CGLibAccUtilTexture::*ReadIntChannel)(int *values);
  typedef void (CGLibAccUtilTexture::*WriteF32Channel)(const f32 *values);
  typedef void (CGLibAccUtilTexture::*WriteIntChannel)(const int *values);

  void setup1DTexutreInfo(CGLibTextureBuffer &texture);
  void textureFlush(CGLibTextureBuffer &texture);
  void getF32(f32 *values, u32 x, u32 y);
  void getInt(int *values, u32 x, u32 y);
  void setF32(const f32 *values, u32 x, u32 y);
  void setInt(const int *values, u32 x, u32 y);
  void setup2DTexutreInfo(CGLibTextureBuffer &texture, u32 mipmap);
  void setupCubeTexutreInfo(CGLibTextureBuffer &texture, u32 face, u32 mipmap);
  void setup3DTexutreInfo(CGLibTextureBuffer &texture);
  void getF32(f32 *values, u32 x, u32 y, u32 z);
  void getInt(int *values, u32 x, u32 y, u32 z);
  void setF32(const f32 *values, u32 x, u32 y, u32 z);
  void setInt(const int *values, u32 x, u32 y, u32 z);
  AccCalcType getCalcType(GrlSurfaceFormat format) const;
  u32 getCalcChanel(GrlSurfaceFormat format) const;
  void setupFormatParam();
  u32 getSquaringPixel(u32 pixel) const;
  u32 getOfsPixelPos(u32 x, u32 y) const;
  u32 getOfsPixelPos(u32 x, u32 y, u32 z) const;
  void texaccread_f32_r(f32 *values);
  void texaccread_f32_rg(f32 *values);
  void texaccread_f32_rgba(f32 *values);
  void texaccread_int_r(int *values);
  void texaccread_int_rg(int *values);
  void texaccread_int_rgba(int *values);
  void texaccwrite_f32_r(const f32 *values);
  void texaccwrite_f32_rg(const f32 *values);
  void texaccwrite_f32_rgba(const f32 *values);
  void texaccwrite_int_r(const int *values);
  void texaccwrite_int_rg(const int *values);
  void texaccwrite_int_rgba(const int *values);
  f32 texaccread_f32_8(u32 index);
  f32 texaccread_f32_16_float(u32 index);
  f32 texaccread_f32_16_int(u32 index);
  f32 texaccread_f32_16_uint(u32 index);
  f32 texaccread_f32_16_unom(u32 index);
  f32 texaccread_f32_32_float(u32 index);
  f32 texaccread_f32_32_int(u32 index);
  f32 texaccread_f32_32_uint(u32 index);
  f32 texaccread_f32_err(u32 index);
  int texaccread_int_8(u32 index);
  int texaccread_int_16_float(u32 index);
  int texaccread_int_16_int(u32 index);
  int texaccread_int_16_uint(u32 index);
  int texaccread_int_16_unom(u32 index);
  int texaccread_int_32_float(u32 index);
  int texaccread_int_32_int(u32 index);
  int texaccread_int_32_uint(u32 index);
  int texaccread_int_err(u32 index);
  void texaccwrite_f32_8(const f32 *values, u32 index);
  void texaccwrite_f32_16_float(const f32 *values, u32 index);
  void texaccwrite_f32_16_int(const f32 *values, u32 index);
  void texaccwrite_f32_16_uint(const f32 *values, u32 index);
  void texaccwrite_f32_16_unom(const f32 *values, u32 index);
  void texaccwrite_f32_32_float(const f32 *values, u32 index);
  void texaccwrite_f32_32_int(const f32 *values, u32 index);
  void texaccwrite_f32_32_uint(const f32 *values, u32 index);
  void texaccwrite_f32_err(const f32 *values, u32 index);
  void texaccwrite_int_8(const int *values, u32 index);
  void texaccwrite_int_16_float(const int *values, u32 index);
  void texaccwrite_int_16_int(const int *values, u32 index);
  void texaccwrite_int_16_uint(const int *values, u32 index);
  void texaccwrite_int_16_unom(const int *values, u32 index);
  void texaccwrite_int_32_float(const int *values, u32 index);
  void texaccwrite_int_32_int(const int *values, u32 index);
  void texaccwrite_int_32_uint(const int *values, u32 index);
  void texaccwrite_int_err(const int *values, u32 index);

  static ReadF32Call s_pReadF32Call[9];
  static ReadIntCall s_pReadIntCall[9];
  static WriteF32Call s_pWriteF32Call[9];
  static WriteIntCall s_pWriteIntCall[9];
  static ReadF32Channel s_pReadF32Channel[3];
  static ReadIntChannel s_pReadIntChannel[3];
  static WriteF32Channel s_pWriteF32Channel[3];
  static WriteIntChannel s_pWriteIntChannel[3];

  ReadF32Call m_readF32;
  ReadIntCall m_readInt;
  WriteF32Call m_writeF32;
  WriteIntCall m_writeInt;
  u32 m_chanel;
  u32 m_pixelBytes;
  u32 m_chanelIndex;
  u32 m_width;
  u32 m_height;
  u32 m_depth;
  u32 m_sliceSize;
  u32 m_sectorWidth;
  u32 m_sectorHeight;
  u32 m_sectorDepth;
  u32 m_gobWidth;
  u32 m_gobHeight;
  u32 m_blockHeight;
  u32 m_bufferSize;
  u8 *m_buffer;
  u8 *m_pixel;
  bool m_isLinear;
};

static_assert(offsetof(CGLibAccUtilTexture, m_chanel) == 0x40, "");
static_assert(offsetof(CGLibAccUtilTexture, m_width) == 0x4c, "");
static_assert(offsetof(CGLibAccUtilTexture, m_sectorWidth) == 0x5c, "");
static_assert(offsetof(CGLibAccUtilTexture, m_bufferSize) == 0x74, "");
static_assert(offsetof(CGLibAccUtilTexture, m_buffer) == 0x78, "");
static_assert(offsetof(CGLibAccUtilTexture, m_isLinear) == 0x88, "");

} // namespace grlib
