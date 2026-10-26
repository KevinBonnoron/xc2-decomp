#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace mm {
struct Col4;
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class CacheDraw {
public:
  bool setMatrix(const mm::Mat44 &matrix);
  bool setCol(const mm::Col4 &color);
  bool setZComp(bool isEnable);
  bool setZWrite(bool isEnable);
  bool renderRect(const mm::Rect<int> &rect);
  bool renderRectFill(const mm::Rect<int> &rect);
  bool renderTriangleFill(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third);
  bool renderTriangle2DFill(const mm::Pnt<int> &first, const mm::Pnt<int> &second, const mm::Pnt<int> &third);
  bool renderCircle2D(const mm::Vec3 &center, f32 radius, u32 division);
  bool renderCircle2DFill(const mm::Vec3 &center, f32 radius, u32 division);
  bool renderCircle(const mm::Mat44 &matrix, f32 radius, u32 division);
  bool renderAxis(f32 length);
  bool renderArrow(const mm::Vec3 &start, const mm::Vec3 &end);
  bool renderSphereFill(const mm::Vec3 &center, f32 radius, u32 division);
  bool renderSphere(const mm::Vec3 &center, f32 radius, u32 division);
  bool renderRealSphereFill(f32 radius, u32 division);
  bool renderRealSphere(f32 radius, u32 division);
  bool renderConeFill(f32 radius, f32 height, u32 division);
  bool renderCone(f32 radius, f32 height, u32 division);
  bool renderCylinderFill(f32 radius, f32 height, u32 division);
  bool renderCylinder(f32 radius, f32 height, u32 division);
  bool renderCapsuleFill(f32 radius, f32 height, u32 division);
  bool renderCapsule(f32 radius, f32 height, u32 division);
  bool renderOval(f32 width, f32 height);
  bool renderSquareFill(f32 width, f32 height);
  bool renderSquare(f32 width, f32 height);
  bool renderCamera();
  bool renderLine(const mm::Vec3 &start, const mm::Vec3 &end);
  bool renderLine(const mm::Pnt<int> &start, const mm::Pnt<int> &end);
  bool renderPoint2D(const mm::Vec3 &position, f32 size);
  bool fontColor(const mm::Col4 &color);
  bool fontScale(f32 x, f32 y);
  bool font(s16 x, s16 y, const char *text);
  bool fontShadow(bool isEnable);

  u8 _00[0x6054 - 0x00];
  f32 unknown6054; // Inferred role: font scale x; original member name unknown.
  f32 unknown6058; // Inferred role: font scale y; original member name unknown.
  u8 _605c[0x6070 - 0x605c];
  bool unknown6070; // Inferred role: z write; original member name unknown.
};

static_assert(offsetof(CacheDraw, unknown6054) == 0x6054, "");
static_assert(offsetof(CacheDraw, unknown6070) == 0x6070, "");

class DebDraw {
public:
  static DebDraw *get(u32 screen);
  static CacheDraw *getCacheDraw();
  void initialize();
  void release();
};

} // namespace ml
