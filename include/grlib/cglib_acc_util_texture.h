#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {

// Inferred role: acc calc type; original type name unknown.
enum unknown013 {
  unknown013_0, // Inferred role: 8; original name unknown.
  unknown013_1, // Inferred role: 16 float; original name unknown.
  unknown013_2, // Inferred role: 16 int; original name unknown.
  unknown013_3, // Inferred role: 16 uint; original name unknown.
  unknown013_4, // Inferred role: 16 unorm; original name unknown.
  unknown013_5, // Inferred role: 32 float; original name unknown.
  unknown013_6, // Inferred role: 32 int; original name unknown.
  unknown013_7, // Inferred role: 32 uint; original name unknown.
  unknown013_8, // Inferred role: error; original name unknown.
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

  CGLibAccUtilTexture() : _90() {}

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
  unknown013 getCalcType(GrlSurfaceFormat format) const;
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

  ReadF32Call unknown00;  // Inferred role: read f32; original member name unknown.
  ReadIntCall unknown10;  // Inferred role: read int; original member name unknown.
  WriteF32Call unknown20; // Inferred role: write f32; original member name unknown.
  WriteIntCall unknown30; // Inferred role: write int; original member name unknown.
  u32 unknown40;          // Inferred role: chanel; original member name unknown.
  u32 unknown44;          // Inferred role: pixel bytes; original member name unknown.
  u32 unknown48;          // Inferred role: chanel index; original member name unknown.
  u32 unknown4c;          // Inferred role: width; original member name unknown.
  u32 unknown50;          // Inferred role: height; original member name unknown.
  u32 unknown54;          // Inferred role: depth; original member name unknown.
  u32 unknown58;          // Inferred role: slice size; original member name unknown.
  u32 unknown5c;          // Inferred role: sector width; original member name unknown.
  u32 unknown60;          // Inferred role: sector height; original member name unknown.
  u32 unknown64;          // Inferred role: sector depth; original member name unknown.
  u32 unknown68;          // Inferred role: gob width; original member name unknown.
  u32 unknown6c;          // Inferred role: gob height; original member name unknown.
  u32 unknown70;          // Inferred role: block height; original member name unknown.
  u32 unknown74;          // Inferred role: buffer size; original member name unknown.
  u8 *m_buffer;
  u8 *unknown80;  // Inferred role: pixel; original member name unknown.
  bool unknown88; // Inferred role: linear; original member name unknown.
  u64 _90;
};

static_assert(offsetof(CGLibAccUtilTexture, unknown40) == 0x40, "");
static_assert(offsetof(CGLibAccUtilTexture, unknown4c) == 0x4c, "");
static_assert(offsetof(CGLibAccUtilTexture, unknown5c) == 0x5c, "");
static_assert(offsetof(CGLibAccUtilTexture, unknown74) == 0x74, "");
static_assert(offsetof(CGLibAccUtilTexture, m_buffer) == 0x78, "");
static_assert(offsetof(CGLibAccUtilTexture, unknown88) == 0x88, "");

class CGLibAcc1DTexture : public CGLibAccUtilTexture {
public:
  CGLibAcc1DTexture();
  ~CGLibAcc1DTexture();
  bool lock(CGLibTextureBuffer &texture);
  void unlock();
  void getFloat(f32 &r, u32 x);
  void getFloat(f32 &r, f32 &g, u32 x);
  void getFloat(f32 &r, f32 &g, f32 &b, u32 x);
  void getFloat(f32 &r, f32 &g, f32 &b, f32 &a, u32 x);
  void getInt(int &r, u32 x);
  void getInt(int &r, int &g, u32 x);
  void getInt(int &r, int &g, int &b, u32 x);
  void getInt(int &r, int &g, int &b, int &a, u32 x);
  void setFloat(f32 r, u32 x);
  void setFloat(f32 r, f32 g, u32 x);
  void setFloat(f32 r, f32 g, f32 b, u32 x);
  void setFloat(f32 r, f32 g, f32 b, f32 a, u32 x);
  void setInt(int r, u32 x);
  void setInt(int r, int g, u32 x);
  void setInt(int r, int g, int b, u32 x);
  void setInt(int r, int g, int b, int a, u32 x);

  bool unknown98;                // Inferred role: lock; original member name unknown.
  bool unknown99;                // Inferred role: dirty; original member name unknown.
  CGLibTextureBuffer *unknowna0; // Inferred role: p texture; original member name unknown.
};

class CGLibAcc2DTexture : public CGLibAccUtilTexture {
public:
  CGLibAcc2DTexture();
  ~CGLibAcc2DTexture();
  bool lock(CGLibTextureBuffer &texture);
  bool lockMipmap(CGLibTextureBuffer &texture, u32 mipmap);
  bool lockCubemap(CGLibTextureBuffer &texture, u32 face);
  bool lockCubemapMipmap(CGLibTextureBuffer &texture, u32 face, u32 mipmap);
  void unlock();
  void getFloat(f32 &r, u32 x, u32 y);
  void getFloat(f32 &r, f32 &g, u32 x, u32 y);
  void getFloat(f32 &r, f32 &g, f32 &b, u32 x, u32 y);
  void getFloat(f32 &r, f32 &g, f32 &b, f32 &a, u32 x, u32 y);
  void getInt(int &r, u32 x, u32 y);
  void getInt(int &r, int &g, u32 x, u32 y);
  void getInt(int &r, int &g, int &b, u32 x, u32 y);
  void getInt(int &r, int &g, int &b, int &a, u32 x, u32 y);
  void setFloat(f32 r, u32 x, u32 y);
  void setFloat(f32 r, f32 g, u32 x, u32 y);
  void setFloat(f32 r, f32 g, f32 b, u32 x, u32 y);
  void setFloat(f32 r, f32 g, f32 b, f32 a, u32 x, u32 y);
  void setInt(int r, u32 x, u32 y);
  void setInt(int r, int g, u32 x, u32 y);
  void setInt(int r, int g, int b, u32 x, u32 y);
  void setInt(int r, int g, int b, int a, u32 x, u32 y);

  u32 unknown98;                 // Inferred role: mipmap; original member name unknown.
  u32 unknown9c;                 // Inferred role: face; original member name unknown.
  bool unknowna0;                // Inferred role: lock; original member name unknown.
  bool unknowna1;                // Inferred role: dirty; original member name unknown.
  bool unknowna2;                // Inferred role: cubemap; original member name unknown.
  CGLibTextureBuffer *unknowna8; // Inferred role: p texture; original member name unknown.
};

class CGLibAcc3DTexture : public CGLibAccUtilTexture {
public:
  CGLibAcc3DTexture();
  ~CGLibAcc3DTexture();
  bool lock(CGLibTextureBuffer &texture);
  void unlock();
  void getFloat(f32 &r, u32 x, u32 y, u32 z);
  void getFloat(f32 &r, f32 &g, u32 x, u32 y, u32 z);
  void getFloat(f32 &r, f32 &g, f32 &b, u32 x, u32 y, u32 z);
  void getFloat(f32 &r, f32 &g, f32 &b, f32 &a, u32 x, u32 y, u32 z);
  void getInt(int &r, u32 x, u32 y, u32 z);
  void getInt(int &r, int &g, u32 x, u32 y, u32 z);
  void getInt(int &r, int &g, int &b, u32 x, u32 y, u32 z);
  void getInt(int &r, int &g, int &b, int &a, u32 x, u32 y, u32 z);
  void setFloat(f32 r, u32 x, u32 y, u32 z);
  void setFloat(f32 r, f32 g, u32 x, u32 y, u32 z);
  void setFloat(f32 r, f32 g, f32 b, u32 x, u32 y, u32 z);
  void setFloat(f32 r, f32 g, f32 b, f32 a, u32 x, u32 y, u32 z);
  void setInt(int r, u32 x, u32 y, u32 z);
  void setInt(int r, int g, u32 x, u32 y, u32 z);
  void setInt(int r, int g, int b, u32 x, u32 y, u32 z);
  void setInt(int r, int g, int b, int a, u32 x, u32 y, u32 z);

  bool unknown98;                // Inferred role: dirty; original member name unknown.
  CGLibTextureBuffer *unknowna0; // Inferred role: p texture; original member name unknown.
};

static_assert(offsetof(CGLibAcc1DTexture, unknown98) == 0x98, "");
static_assert(offsetof(CGLibAcc1DTexture, unknowna0) == 0xa0, "");
static_assert(offsetof(CGLibAcc2DTexture, unknown98) == 0x98, "");
static_assert(offsetof(CGLibAcc2DTexture, unknowna0) == 0xa0, "");
static_assert(offsetof(CGLibAcc2DTexture, unknowna8) == 0xa8, "");
static_assert(offsetof(CGLibAcc3DTexture, unknown98) == 0x98, "");
static_assert(sizeof(CGLibAcc3DTexture) == 0xa8, "");

} // namespace grlib
