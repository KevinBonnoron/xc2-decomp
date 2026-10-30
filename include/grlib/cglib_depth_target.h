#pragma once
#include <stddef.h>

#include "grlib/cglib_depth_buffer.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {

class CGLibDepthTarget {
public:
  CGLibDepthTarget();
  ~CGLibDepthTarget();
  void setRenderTarget();
  void release();
  void releaseWork();
  void releaseTexture();
  void clearDepth(bool isClear);
  void setTextureInfo(f32 width, f32 height, GrlDepthFormat format, bool isResArea, u32 resArea);
  void clearValDepth(float value, bool isClear);

  // Inferred role: key of a cached resident-area depth buffer; original type name unknown.
  struct unknown001 {
    u16 unknown00; // Inferred role: width; original member name unknown.
    u16 unknown02; // Inferred role: height; original member name unknown.
    s16 unknown04; // Inferred role: age since last use; original member name unknown.
    u8 _06[0x08 - 0x06];
    u32 unknown08;            // Inferred role: res area; original member name unknown.
    GrlDepthFormat unknown0c; // Inferred role: format; original member name unknown.
  };

  u32 unknown00;  // Inferred role: width; original member name unknown.
  u32 unknown04;  // Inferred role: height; original member name unknown.
  bool unknown08; // Inferred role: res area; original member name unknown.
  u8 _09[0x10 - 0x09];
  CGLibDepthBuffer unknown10;       // Inferred role: depth buffer; original member name unknown.
  CGLibTextureBuffer unknown40;     // Inferred role: depth texture; original member name unknown.
  CGLibTextureBuffer unknownb0;     // Inferred role: stencil texture; original member name unknown.
  CGLibDepthBuffer *unknown120;     // Inferred role: depth buffer; original member name unknown.
  CGLibTextureBuffer *unknown128;   // Inferred role: depth texture; original member name unknown.
  CGLibTextureBuffer *unknown130;   // Inferred role: stencil texture; original member name unknown.
  u16 unknown138;                   // Inferred role: cached buffer state; original member name unknown.
  unknown001 unknown13c[6];         // Inferred role: cached buffer keys; original member name unknown.
  CGLibDepthBuffer unknown1a0[6];   // Inferred role: cached depth buffers; original member name unknown.
  CGLibTextureBuffer unknown2c0[6]; // Inferred role: cached depth textures; original member name unknown.
  CGLibTextureBuffer unknown560[6]; // Inferred role: cached stencil textures; original member name unknown.
};

static_assert(sizeof(CGLibDepthTarget::unknown001) == 0x10, "");
static_assert(offsetof(CGLibDepthTarget, unknown04) == 0x004, "");
static_assert(offsetof(CGLibDepthTarget, unknown08) == 0x008, "");
static_assert(offsetof(CGLibDepthTarget, unknown10) == 0x010, "");
static_assert(offsetof(CGLibDepthTarget, unknown40) == 0x040, "");
static_assert(offsetof(CGLibDepthTarget, unknownb0) == 0x0b0, "");
static_assert(offsetof(CGLibDepthTarget, unknown120) == 0x120, "");
static_assert(offsetof(CGLibDepthTarget, unknown138) == 0x138, "");
static_assert(offsetof(CGLibDepthTarget, unknown13c) == 0x13c, "");
static_assert(offsetof(CGLibDepthTarget, unknown1a0) == 0x1a0, "");
static_assert(offsetof(CGLibDepthTarget, unknown2c0) == 0x2c0, "");
static_assert(offsetof(CGLibDepthTarget, unknown560) == 0x560, "");
static_assert(sizeof(CGLibDepthTarget) == 0x800, "");

} // namespace grlib
