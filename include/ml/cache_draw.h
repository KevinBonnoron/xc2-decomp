#pragma once
#include <stddef.h>

#include "ml/dev_graph_cb.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_obb.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
class Cube;
class PrimBase;
struct Col3;
struct Col4;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DebDraw;

class CacheDraw {
public:
  // Inferred role: base of the recorded draw commands, replayed by flush; original name unknown.
  struct unknown001 {
    virtual void flush(DebDraw *draw) = 0;
    u32 unknown08; // Inferred role: command header; original member name unknown.
  };

#pragma pack(push, 4)
  struct DMAT : unknown001 {
    void flush(DebDraw *draw) override;
    u32 unknown0c;       // Inferred role: padding before the aligned matrix; original member name unknown.
    mm::Mat44 unknown10; // Inferred role: matrix; original member name unknown.
  };

  struct DCLEAR : unknown001 {
    void flush(DebDraw *draw) override;
  };

  struct DEND : unknown001 {
    void flush(DebDraw *draw) override;
  };

  struct DORTHO : unknown001 {
    void flush(DebDraw *draw) override;
  };

  struct DBEGIN : unknown001 {
    void flush(DebDraw *draw) override;
    u32 unknown0c; // Inferred role: primitive; original member name unknown.
    u32 unknown10; // Inferred role: count; original member name unknown.
  };

  struct DADDV3_1 : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Vec3 unknown0c; // Inferred role: position; original member name unknown.
  };

  struct DPERS : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Mat44 unknown0c; // Inferred role: matrix; original member name unknown.
    f32 unknown4c;       // Inferred role: first perspective value; original member name unknown.
    f32 unknown50;       // Inferred role: second perspective value; original member name unknown.
    f32 unknown54;       // Inferred role: third perspective value; original member name unknown.
    mm::Vec3 unknown58;  // Inferred role: position; original member name unknown.
  };

  struct DRAXIS : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: length; original member name unknown.
  };

  struct DRCAMERA : unknown001 {
    void flush(DebDraw *draw) override;
  };

  struct DROBB : unknown001 {
    void flush(DebDraw *draw) override;
    u32 unknown0c;     // Inferred role: padding before the aligned box; original member name unknown.
    mm::Obb unknown10; // Inferred role: box; original member name unknown.
  };

  struct DRRECT : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Rect<int> unknown0c; // Inferred role: rectangle; original member name unknown.
  };

  struct DRRECT_FILL : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Rect<int> unknown0c; // Inferred role: rectangle; original member name unknown.
  };

  struct DRGRID : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: first size; original member name unknown.
    f32 unknown10; // Inferred role: second size; original member name unknown.
  };

  struct DROVAL : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: width; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
  };

  struct DRSQUARE : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: width; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
  };

  struct DRSQUARE_FILL : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: width; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
  };

  struct DRCAPSULE : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u32 unknown14; // Inferred role: division; original member name unknown.
  };

  struct DRCAPSULE_FILL : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u32 unknown14; // Inferred role: division; original member name unknown.
  };

  struct DRCONE : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u32 unknown14; // Inferred role: division; original member name unknown.
  };

  struct DRCONE_FILL : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u32 unknown14; // Inferred role: division; original member name unknown.
  };

  struct DRCYLINDER : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u32 unknown14; // Inferred role: division; original member name unknown.
  };

  struct DRCYLINDER_FILL : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u32 unknown14; // Inferred role: division; original member name unknown.
  };

  struct DRCIRCLE_MAT : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Mat44 unknown0c; // Inferred role: matrix; original member name unknown.
    f32 unknown4c;       // Inferred role: radius; original member name unknown.
    s32 unknown50;       // Inferred role: division; original member name unknown.
  };

  struct DRSPHERE_REAL : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    s32 unknown10; // Inferred role: division; original member name unknown.
  };

  struct DRSPHERE_REAL_FILL : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: radius; original member name unknown.
    s32 unknown10; // Inferred role: division; original member name unknown.
  };
#pragma pack(pop)

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
  bool renderCircle(const mm::Vec3 &center, f32 radius, u32 division);
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
  bool renderGrid(f32 size, f32 step);
  bool renderCamera();
  bool setOrtho();
  bool setDoubleSide(bool isEnable);
  bool renderPoint(const mm::Vec3 &position);
  bool renderTriangle(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third);
  bool renderLine(const mm::Vec3 &start, const mm::Vec3 &end);
  bool renderLine(const mm::Pnt<int> &start, const mm::Pnt<int> &end);
  bool renderPoint2D(const mm::Vec3 &position, f32 size);
  bool fontColor(const mm::Col4 &color);
  bool fontBack(const mm::Col4 &color);
  bool fontFlush(bool isEnable);
  bool setAlpha(f32 alpha);
  bool setAlphaBlend(bool isEnable);
  bool setLineWidth(u32 width);
  bool setTex(grlib::CGLibTextureBuffer *texture);
  bool fontScale(f32 x, f32 y);
  bool font(s16 x, s16 y, const char *text);
  bool fontShadow(bool isEnable);

  u8 _00[0x6054 - 0x00];
  f32 unknown6054; // Inferred role: font scale x; original member name unknown.
  f32 unknown6058; // Inferred role: font scale y; original member name unknown.
  u8 _605c[0x6070 - 0x605c];
  bool unknown6070; // Inferred role: z write; original member name unknown.
};

static_assert(offsetof(CacheDraw::DBEGIN, unknown10) == 0x10, "");
static_assert(offsetof(CacheDraw::DPERS, unknown4c) == 0x4c, "");
static_assert(offsetof(CacheDraw::DPERS, unknown58) == 0x58, "");
static_assert(offsetof(CacheDraw::DMAT, unknown10) == 0x10, "");
static_assert(offsetof(CacheDraw::DROBB, unknown10) == 0x10, "");
static_assert(offsetof(CacheDraw::DRCIRCLE_MAT, unknown4c) == 0x4c, "");
static_assert(offsetof(CacheDraw::DRCIRCLE_MAT, unknown50) == 0x50, "");
static_assert(offsetof(CacheDraw::DRSPHERE_REAL, unknown10) == 0x10, "");
static_assert(offsetof(CacheDraw::DRCAPSULE, unknown14) == 0x14, "");
static_assert(offsetof(CacheDraw, unknown6054) == 0x6054, "");
static_assert(offsetof(CacheDraw, unknown6070) == 0x6070, "");

class DebDraw : public DevGraphCB {
public:
  virtual void fastSetup();
  virtual void restoreShader();
  virtual void begin(u32 primitive, u32 count);
  virtual void end();
  virtual void add(const mm::Vec3 &first, const mm::Vec3 &second);
  virtual void add(const mm::Pnt<int> &first, const mm::Pnt<int> &second);
  virtual void add(int x1, int y1, int x2, int y2);
  virtual void add(const mm::Vec3 &position);
  virtual void add(const mm::Pnt<int> &position);
  virtual void add(f32 x, f32 y, f32 z);
  virtual void add(int x, int y, int z);
  virtual void add(int x, int y);
  virtual void add(const mm::Vec3 &position, const mm::Col4 &color);
  virtual void add(const mm::Vec3 &position, const mm::Col3 &color);
  virtual void add(int x, int y, const mm::Col4 &color);
  virtual void add(int x, int y, const mm::Col3 &color);
  virtual void add(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Col4 &color);
  virtual void add(const mm::Rect<int> &rect);
  virtual void add(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third);
  virtual void setPerspective(f32 first, f32 second, f32 third, const mm::Mat44 &matrix, const mm::Vec3 *position);
  virtual void setOrtho();
  virtual void clear();
  void renderAxis(f32 length);
  void renderCamera();
  void renderOBB(const mm::Obb &obb);
  void renderRect(const mm::Rect<int> &rect);
  void renderRectFill(const mm::Rect<int> &rect);
  void renderGrid(f32 first, f32 second);
  void renderOval(f32 width, f32 height);
  void renderSquare(f32 width, f32 height);
  void renderSquareFill(f32 width, f32 height);
  void renderCapsule(f32 radius, f32 height, u32 division);
  void renderCapsuleFill(f32 radius, f32 height, u32 division);
  void renderCone(f32 radius, f32 height, u32 division);
  void renderConeFill(f32 radius, f32 height, u32 division);
  void renderCylinder(f32 radius, f32 height, u32 division);
  void renderCylinderFill(f32 radius, f32 height, u32 division);
  void renderCircle(const mm::Mat44 &matrix, f32 radius, int division);
  void renderCircle(const mm::Vec3 &center, f32 radius, int division);
  void renderCircleFill(const mm::Vec3 &center, f32 radius, int division);
  void renderRealSphere(f32 radius, int division);
  void renderRealSphereFill(f32 radius, int division);
  void setMatrix(const mm::Mat44 &matrix);
  void setZComp(bool isEnable);
  void setZWrite(bool isEnable);
  void setDoubleSide(bool isEnable);
  void renderPoint(const mm::Vec3 &position);
  void renderLine(const mm::Vec3 &start, const mm::Vec3 &end);
  void renderLine(const mm::Pnt<int> &start, const mm::Pnt<int> &end);
  void renderTriangle(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third);
  void renderTriangleFill(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third);
  void renderRect(int x, int y, int width, int height);
  void renderRectFill(int x, int y, int width, int height);
  void renderRectFill(const mm::Rect<int> &first, const mm::Rect<int> &second);
  void renderDiamondFill(const mm::Rect<int> &rect);
  void renderPrimFill(const mm::PrimBase *prim);
  void cubeFill(const mm::Cube *cube);
  static DebDraw *get(u32 screen);
  static void swap();
  static CacheDraw *getCacheDraw();
  void initialize();
  void release();
  void clrTex();
  void setAlpha(f32 alpha);
  void setAlphaBlend(bool isEnable);
  void setLineWidth(u32 width);
  void setTex(grlib::CGLibTextureBuffer *texture);
  void fontColor(const mm::Col4 &color);
  void fontBack(const mm::Col4 &color);
  void fontShadow(bool isEnable);
  void fontFlush(bool isEnable);
  void fontScale(f32 x, f32 y);
  void font(int x, int y, const char *text);

  u32 unknown08; // Inferred role: state flags; original member name unknown.
  u8 _0c[0x1c - 0xc];
  f32 unknown1c; // Inferred role: alpha; original member name unknown.
  u8 _20[0x144 - 0x20];
  u32 unknown144; // Inferred role: line width; original member name unknown.
  u8 _148[0x154 - 0x148];
  bool unknown154; // Inferred role: z compare; original member name unknown.
  bool unknown155; // Inferred role: z write; original member name unknown.
  u8 _156[0x180 - 0x156];
  grlib::CGLibTextureBuffer *unknown180; // Inferred role: texture; original member name unknown.
  u8 _188[0x210 - 0x188];
  CacheDraw *unknown210; // Inferred role: recorded draw commands; original member name unknown.
};

static_assert(offsetof(DebDraw, unknown08) == 0x8, "");
static_assert(offsetof(DebDraw, unknown1c) == 0x1c, "");
static_assert(offsetof(DebDraw, unknown144) == 0x144, "");
static_assert(offsetof(DebDraw, unknown154) == 0x154, "");
static_assert(offsetof(DebDraw, unknown155) == 0x155, "");
static_assert(offsetof(DebDraw, unknown180) == 0x180, "");
static_assert(offsetof(DebDraw, unknown210) == 0x210, "");

} // namespace ml
