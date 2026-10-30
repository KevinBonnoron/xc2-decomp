#pragma once
#include <stddef.h>

#include "ml/dev_graph_cb.h"
#include "ml/fixed_size_alloc.h"
#include "ml/reslist.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_obb.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
class Cube;
class PrimBase;
struct Col3;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class CriticalSectionNC;
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

  struct DTEX : unknown001 {
    void flush(DebDraw *draw) override;
    u32 unknown0c;                        // Inferred role: padding before the aligned pointer; original member name unknown.
    grlib::CGLibTextureBuffer *unknown10; // Inferred role: texture; original member name unknown.
  };

  struct DDOUBLESIDE : unknown001 {
    void flush(DebDraw *draw) override;
    bool unknown0c; // Inferred role: enable; original member name unknown.
  };

  struct DZCOMP : unknown001 {
    void flush(DebDraw *draw) override;
    bool unknown0c; // Inferred role: enable; original member name unknown.
  };

  struct DZWRITE : unknown001 {
    void flush(DebDraw *draw) override;
    bool unknown0c; // Inferred role: enable; original member name unknown.
  };

  struct DALPHA : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: alpha; original member name unknown.
  };

  struct DLINE_WIDTH : unknown001 {
    void flush(DebDraw *draw) override;
    u32 unknown0c; // Inferred role: width; original member name unknown.
  };

  struct DALPHA_BLEND : unknown001 {
    void flush(DebDraw *draw) override;
    bool unknown0c; // Inferred role: enable; original member name unknown.
  };

  struct DRTRI2D_FILL : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Pnt<int> unknown0c; // Inferred role: first corner; original member name unknown.
    mm::Pnt<int> unknown14; // Inferred role: second corner; original member name unknown.
    mm::Pnt<int> unknown1c; // Inferred role: third corner; original member name unknown.
  };

  struct DRLINE_PNT : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Pnt<int> unknown0c; // Inferred role: start; original member name unknown.
    mm::Pnt<int> unknown14; // Inferred role: end; original member name unknown.
  };

  struct DFONT32 : unknown001 {
    void flush(DebDraw *draw) override;
    mm::mtl::FixStr<32> unknown0c; // Inferred role: text; original member name unknown.
    s16 unknown30;                 // Inferred role: x; original member name unknown.
    s16 unknown32;                 // Inferred role: y; original member name unknown.
  };

  struct DFONT64 : unknown001 {
    void flush(DebDraw *draw) override;
    mm::mtl::FixStr<64> unknown0c; // Inferred role: text; original member name unknown.
    s16 unknown50;                 // Inferred role: x; original member name unknown.
    s16 unknown52;                 // Inferred role: y; original member name unknown.
  };

  struct DFONT128 : unknown001 {
    void flush(DebDraw *draw) override;
    mm::mtl::FixStr<128> unknown0c; // Inferred role: text; original member name unknown.
    s16 unknown90;                  // Inferred role: x; original member name unknown.
    s16 unknown92;                  // Inferred role: y; original member name unknown.
  };

  struct DFONT256 : unknown001 {
    void flush(DebDraw *draw) override;
    mm::mtl::FixStr<256> unknown0c; // Inferred role: text; original member name unknown.
    s16 unknown110;                 // Inferred role: x; original member name unknown.
    s16 unknown112;                 // Inferred role: y; original member name unknown.
  };

  struct DFONT_COL : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Col4 unknown0c; // Inferred role: font color; original member name unknown.
  };

  struct DFONT_BACKCOL : unknown001 {
    void flush(DebDraw *draw) override;
    mm::Col4 unknown0c; // Inferred role: font back color; original member name unknown.
  };

  struct DFONT_SHADOW : unknown001 {
    void flush(DebDraw *draw) override;
    bool unknown0c; // Inferred role: shadow enable; original member name unknown.
  };

  struct DFONT_FLUSH : unknown001 {
    void flush(DebDraw *draw) override;
    bool unknown0c; // Inferred role: flush enable; original member name unknown.
  };

  struct DFONT_SCALE : unknown001 {
    void flush(DebDraw *draw) override;
    f32 unknown0c; // Inferred role: scale x; original member name unknown.
    f32 unknown10; // Inferred role: scale y; original member name unknown.
  };
#pragma pack(pop)

  // Inferred role: range of recorded commands of one priority; original name unknown.
  struct unknown002 {
    u8 *unknown00; // Inferred role: begin; original member name unknown.
    u8 *unknown08; // Inferred role: end; original member name unknown.
    int unknown10; // Inferred role: priority; original member name unknown.
  };

  // Inferred role: command buffer of one frame parity; original name unknown.
  struct unknown003 {
    u8 *unknown00;               // Inferred role: memory; original member name unknown.
    u8 *unknown08;               // Inferred role: write position; original member name unknown.
    size_t unknown10;            // Inferred role: size; original member name unknown.
    unknown002 unknown18[0x200]; // Inferred role: recorded ranges; original member name unknown.
    u32 unknown3018;             // Inferred role: current range index; original member name unknown.
  };

  CacheDraw(mtl::ALLOC_HANDLE handle, size_t size);
  virtual ~CacheDraw();
  void clearSystem(bool isOdd);
  void swap();
  unknown003 *getBuf(bool isOdd);
  void setForceRenderQueue(bool isForce);
  void flush(int priority, const mm::Mat44 &projection, const mm::Mat44 &view);
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

  unknown003 unknown08[2];       // Inferred role: command buffers, indexed by frame parity; original member name unknown.
  mtl::ALLOC_HANDLE unknown6048; // Inferred role: memory handle; original member name unknown.
  int m_currentPrio;
  u32 m_cacheDrawWID;
  f32 unknown6054; // Inferred role: font scale x; original member name unknown.
  f32 unknown6058; // Inferred role: font scale y; original member name unknown.
  u8 _605c[0x6060 - 0x605c];
  CriticalSectionNC *unknown6060; // Inferred role: recording lock; original member name unknown.
  bool m_forceRenderQueue;
  int m_suspendSwap;
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
static_assert(offsetof(CacheDraw::DTEX, unknown10) == 0x10, "");
static_assert(offsetof(CacheDraw::DALPHA, unknown0c) == 0x0c, "");
static_assert(offsetof(CacheDraw::DFONT32, unknown30) == 0x30, "");
static_assert(offsetof(CacheDraw::DFONT64, unknown50) == 0x50, "");
static_assert(offsetof(CacheDraw::DFONT128, unknown90) == 0x90, "");
static_assert(offsetof(CacheDraw::DFONT256, unknown110) == 0x110, "");
static_assert(offsetof(CacheDraw::DFONT_SCALE, unknown10) == 0x10, "");
static_assert(offsetof(CacheDraw, unknown6054) == 0x6054, "");
static_assert(offsetof(CacheDraw, unknown6070) == 0x6070, "");
static_assert(sizeof(CacheDraw::unknown002) == 0x18, "");
static_assert(offsetof(CacheDraw::unknown003, unknown3018) == 0x3018, "");
static_assert(sizeof(CacheDraw::unknown003) == 0x3020, "");
static_assert(offsetof(CacheDraw, unknown6048) == 0x6048, "");
static_assert(offsetof(CacheDraw, unknown6060) == 0x6060, "");
static_assert(offsetof(CacheDraw, m_forceRenderQueue) == 0x6068, "");
static_assert(offsetof(CacheDraw, m_suspendSwap) == 0x606c, "");
static_assert(sizeof(CacheDraw) == 0x6078, "");

class DebDraw : public DevGraphCB {
public:
  // Inferred role: priority draw entry, 0x10 bytes from the pool allocation size; layout unknown.
  struct PRM_DATA {
    u8 _00[0x10];
  };

  DebDraw();
  // The game vtable holds __cxa_pure_virtual in these slots and has no complete-object constructor symbol.
  virtual void fastSetup() = 0;
  virtual void restoreShader() = 0;
  virtual void begin(u32 primitive, u32 count) = 0;
  virtual void end() = 0;
  virtual void add(const mm::Vec3 &first, const mm::Vec3 &second) = 0;
  virtual void add(const mm::Pnt<int> &first, const mm::Pnt<int> &second) = 0;
  virtual void add(int x1, int y1, int x2, int y2) = 0;
  virtual void add(const mm::Vec3 &position) = 0;
  virtual void add(const mm::Pnt<int> &position) = 0;
  virtual void add(f32 x, f32 y, f32 z) = 0;
  virtual void add(int x, int y, int z) = 0;
  virtual void add(int x, int y) = 0;
  virtual void add(const mm::Vec3 &position, const mm::Col4 &color) = 0;
  virtual void add(const mm::Vec3 &position, const mm::Col3 &color) = 0;
  virtual void add(int x, int y, const mm::Col4 &color) = 0;
  virtual void add(int x, int y, const mm::Col3 &color) = 0;
  virtual void add(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Col4 &color) = 0;
  virtual void add(const mm::Rect<int> &rect) = 0;
  virtual void add(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third) = 0;
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
  static DebDraw *getOnly(u32 screen);
  static void setup();
  static bool isNotRender();
  static u32 getCacheDrawWID();
  static void setCurrentPrio(int priority);
  static void flushPrio(int priority, const mm::Mat44 &projection, const mm::Mat44 &view);
  static void swap();
  void setForceRenderQueue(bool isForce);
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

  u32 unknown08;      // Inferred role: state flags; original member name unknown.
  mm::Col4 unknown0c; // Inferred role: color; original member name unknown.
  f32 unknown1c;      // Inferred role: alpha; original member name unknown.
  s32 unknown20;      // Inferred role: primitive; original member name unknown.
  u32 unknown24;      // Inferred role: vertex count; original member name unknown.
  u32 unknown28;      // Inferred role: buffered vertex count; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  mm::Vec3 unknown30; // Inferred role: camera position; original member name unknown.
  u8 _40[0xc0 - 0x40];
  mm::Mat44 unknownc0; // Inferred role: model matrix; original member name unknown.
  u8 _100[0x140 - 0x100];
  u32 unknown140;  // Inferred role: added vertex count; original member name unknown.
  u32 unknown144;  // Inferred role: line width; original member name unknown.
  u32 unknown148;  // Inferred role: unknown, cleared with the draw state; original member name unknown.
  f32 unknown14c;  // Inferred role: 2D depth; original member name unknown.
  u32 unknown150;  // Inferred role: requested vertex count; original member name unknown.
  bool unknown154; // Inferred role: z compare; original member name unknown.
  bool unknown155; // Inferred role: z write; original member name unknown.
  u8 _156[0x160 - 0x156];
  mm::Vec3 unknown160; // Inferred role: perspective position; original member name unknown.
  s32 unknown170;      // Inferred role: draw primitive type; original member name unknown.
  u8 _174[0x178 - 0x174];
  u64 unknown178;                        // Inferred role: unknown, cleared by the constructor; original member name unknown.
  grlib::CGLibTextureBuffer *unknown180; // Inferred role: texture; original member name unknown.
  fixed_size_alloc<PRM_DATA> unknown188; // Inferred role: priority draw entry pool; original member name unknown.
  reslist<PRM_DATA *> unknown1b8;        // Inferred role: priority draw entries; original member name unknown.
  s32 unknown1f8;                        // Inferred role: unknown, -1 when unused; original member name unknown.
  s32 unknown1fc;                        // Inferred role: unknown, -1 when unused; original member name unknown.
  u32 unknown200;                        // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 _204[0x208 - 0x204];
  u64 unknown208;        // Inferred role: unknown, cleared by the constructor; original member name unknown.
  CacheDraw *unknown210; // Inferred role: recorded draw commands; original member name unknown.
  bool m_forceRenderQueue;
};

static_assert(offsetof(DebDraw, unknown08) == 0x8, "");
static_assert(offsetof(DebDraw, unknown0c) == 0xc, "");
static_assert(offsetof(DebDraw, unknown1c) == 0x1c, "");
static_assert(offsetof(DebDraw, unknown30) == 0x30, "");
static_assert(offsetof(DebDraw, unknownc0) == 0xc0, "");
static_assert(offsetof(DebDraw, unknown144) == 0x144, "");
static_assert(offsetof(DebDraw, unknown154) == 0x154, "");
static_assert(offsetof(DebDraw, unknown155) == 0x155, "");
static_assert(offsetof(DebDraw, unknown160) == 0x160, "");
static_assert(offsetof(DebDraw, unknown170) == 0x170, "");
static_assert(offsetof(DebDraw, unknown180) == 0x180, "");
static_assert(offsetof(DebDraw, unknown188) == 0x188, "");
static_assert(offsetof(DebDraw, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DebDraw, unknown1f8) == 0x1f8, "");
static_assert(offsetof(DebDraw, unknown208) == 0x208, "");
static_assert(offsetof(DebDraw, unknown210) == 0x210, "");
static_assert(offsetof(DebDraw, m_forceRenderQueue) == 0x218, "");
static_assert(sizeof(DebDraw) == 0x220, "");
static_assert(sizeof(DebDraw::PRM_DATA) == 0x10, "");

} // namespace ml
