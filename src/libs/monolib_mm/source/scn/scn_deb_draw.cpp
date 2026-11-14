#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "grlib/cglib_color_ctl.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_texture.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/cglib_polygon.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_vtx_vertex.h"
#include "grlib/shd_util.h"
#include "ml/cache_draw.h"
#include "ml/deb_draw_cmd.h"
#include "ml/dev_font.h"
#include "ml/dev_graph.h"
#include "ml/fixed_size_alloc.h"
#include "ml/ml_mem.h"
#include "ml/reslist.h"
#include "ml/work_cpu.h"
#include "ml/work_util.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_cube.h"
#include "mm_math/mm_cylinder.h"
#include "mm_math/mm_line2.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_obb.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_sphere.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

namespace {

// Inferred role: top ring of the unit cylinder, filled by the DebDraw constructor; original name unknown.
mm::Vec3 unknown005[16];
// Inferred role: bottom ring of the unit cylinder, filled by the DebDraw constructor; original name unknown.
mm::Vec3 unknown006[16];
// Inferred role: the DebDraw instance; original name unknown.
DebDraw *unknown007;
// Inferred role: vertex buffer handed to the render thread by the DebDrawCmd destructor; original name unknown.
grlib::CGLibVtxVertex *unknown008;

} // namespace

void DebDraw::clrTex() {
  if (unknown08 & 2) {
    unknown08 &= ~6;
  }
}

void DebDraw::setAlpha(f32 alpha) {
  if (!unknown210->setAlpha(alpha)) {
    unknown1c = alpha;
    if (alpha < 0.0f) {
      unknown1c = 0.0f;
    } else if (alpha > 1.0f) {
      unknown1c = 1.0f;
    }
    unknown08 &= ~4;
  }
}

void DebDraw::setAlphaBlend(bool isEnable) {
  if (!unknown210->setAlphaBlend(isEnable)) {
    if (isEnable) {
      unknown08 |= 0x10;
    } else {
      unknown08 &= ~0x10;
    }
  }
}

void DebDraw::setLineWidth(u32 width) {
  if (!unknown210->setLineWidth(width) && unknown144 != width) {
    unknown144 = width;
    unknown08 &= ~4;
  }
}

void FontLayer::font(int x, int y, const char *format, ...) {
  char text[512];
  va_list args;
  va_start(args, format);
  vsnprintf(text, sizeof(text), format, args);
  va_end(args);
  if (DebDraw::isNotRender()) {
    DebDraw::getOnly(0)->font(x, y, text);
    return;
  }
  DevFont::fontLayer(this, x, y, text);
}

void FontLayer::fontColor(const mm::Col4 &color) {
  if (DebDraw::isNotRender()) {
    DebDraw::getOnly(0)->fontColor(color);
    return;
  }
  DevFont::fontLayerColor(this, color);
}

void FontLayer::fontBack(const mm::Col4 &color) {
  if (DebDraw::isNotRender()) {
    DebDraw::getOnly(0)->fontBack(color);
    return;
  }
  DevFont::fontLayerBack(this, color);
}

void FontLayer::fontShadow(bool isShadow) {
  if (DebDraw::isNotRender()) {
    DebDraw::getOnly(0)->fontShadow(isShadow);
    return;
  }
  DevFont::fontLayerShadow(this, isShadow);
}

void FontLayer::fontFlush(bool isFlush) {
  if (DebDraw::isNotRender()) {
    DebDraw::getOnly(0)->fontFlush(isFlush);
    return;
  }
  DevFont::fontLayerFlush(this, isFlush);
}

void FontLayer::fontScale(f32 x, f32 y) {
  if (DebDraw::isNotRender()) {
    DebDraw::getOnly(0)->fontScale(x, y);
    return;
  }
  DevFont::fontLayerScale(this, x, y);
}

void DebDraw::setTex(grlib::CGLibTextureBuffer *texture) {
  if (!unknown210->setTex(texture)) {
    unknown08 |= 2;
    unknown180 = texture;
  }
}

DebDraw::DebDraw()
    : unknown08(0), unknown1c(1.0f), unknown20(-1), unknown24(0), unknown28(0), unknown140(0), unknown144(1), unknown148(0), unknown14c(0.0f), unknown150(0), unknown154(true), unknown155(true),
      unknown170(-1), unknown178(0), unknown1f8(-1), unknown1fc(-1), unknown200(0), unknown208(0), unknown210(nullptr), m_forceRenderQueue(false) {
  unknown007 = this;
  unknown210 = new (MlMem::getProductMem()) CacheDraw(MlMem::getDebugMem(), 0x20000);
  unknown0c = mm::Col4(1.0f, 1.0f, 1.0f, 1.0f);
  unknownc0 = mm::Mat44::identity;
  unknown30 = mm::Vec3::zero;
  unknown160 = mm::Vec3::zero;
  for (int i = 0; i < 16; i++) {
    f32 angle = i * 0.3926991f;
    f32 angleSin = sinf(angle);
    f32 angleCos = cosf(angle);
    unknown005[i].x = angleSin;
    unknown005[i].y = 1.0f;
    unknown005[i].z = angleCos;
    unknown006[i] = mm::Vec3(unknown005[i].x, -1.0f, unknown005[i].z);
  }
  unknown188.unknown001(MlMem::getDebugMem(), 0x400);
  unknown1b8.create(0x400, MlMem::getDebugMem());
}

DebDraw *DebDraw::getOnly(u32 screen) { return unknown007; }

void DebDraw::setup() {
  if (unknown007 != nullptr) {
    unknown007->fastSetup();
  }
}

void DebDraw::swap() {
  if (unknown007 != nullptr) {
    unknown007->unknown210->swap();
    unknown007->unknown210->clearSystem(false);
  }
}

bool DebDraw::isNotRender() {
  if (unknown007 == nullptr) {
    return false;
  }
  if (WorkCpu::getCurrentThreadId() == WorkCpu::getThreadId(WorkCpu::getRenderCPUID())) {
    return unknown007->m_forceRenderQueue;
  }
  return true;
}

DebDraw *DebDraw::get(u32 screen) {
  if (unknown007 != nullptr) {
    if (WorkCpu::getCurrentThreadId() == WorkCpu::getThreadId(WorkCpu::getRenderCPUID()) && !unknown007->m_forceRenderQueue) {
      unknown007->clear();
    } else {
      unknown007->unknown210->reset_prim(screen);
    }
  }
  return unknown007;
}

void DebDraw::renderLine(int x1, int y1, int x2, int y2) {
  if (!unknown210->renderLine(mm::Pnt<int>(x1, y1), mm::Pnt<int>(x2, y2))) {
    begin(2, 1);
    add(x1, y1, x2, y2);
    end();
  }
}

void DebDraw::renderLine(const mm::Line2 &line) {
  if (!unknown210->renderLine(line.start, line.end)) {
    begin(2, 1);
    add(line.start, line.end);
    end();
  }
}

void DebDraw::setForceRenderQueue(bool isForce) {
  m_forceRenderQueue = isForce;
  unknown210->setForceRenderQueue(isForce);
}

void DebDraw::renderRectUpFill(const mm::Rect<int> &rect) {
  begin(9, 1);
  add(rect);
  end();
  renderRectUp(rect);
}

void DebDraw::fontColor(const mm::Col4 &color) { unknown210->fontColor(color); }

void DebDraw::fontBack(const mm::Col4 &color) { unknown210->fontBack(color); }

void DebDraw::fontShadow(bool isEnable) { unknown210->fontShadow(isEnable); }

void DebDraw::fontFlush(bool isEnable) { unknown210->fontFlush(isEnable); }

void DebDraw::fontScale(f32 x, f32 y) { unknown210->fontScale(x, y); }

void DebDraw::font(int x, int y, const char *text) { unknown210->font(x, y, text); }

u32 DebDraw::getCacheDrawWID() {
  if (unknown007 != nullptr) {
    return unknown007->unknown210->m_cacheDrawWID;
  }
  return 0xffffffff;
}

CacheDraw *DebDraw::getCacheDraw() {
  unknown007->unknown210->m_currentPrio = -2;
  return unknown007->unknown210;
}

void DebDraw::setCurrentPrio(int priority) {
  if (unknown007 != nullptr) {
    unknown007->unknown210->m_currentPrio = priority;
  }
}

void DebDraw::flushPrio(int priority, const mm::Mat44 &projection, const mm::Mat44 &view) {
  if (unknown007 != nullptr) {
    unknown007->unknown210->flush(priority, projection, view);
  }
}

void DebDraw::initialize() {}

void DebDraw::release() {}

void DebDrawCmd::initialize() {}

void DebDrawCmd::release() {}

DebDrawCmd::DebDrawCmd()
    : unknown219(false), unknown21c(mm::Col4::white), unknown230(mm::Vec3::unitY), unknown240(mm::Col4::white), unknown250(mm::Col4::white), unknown260(mm::Col4::white), unknown270(false),
      unknown2d0(nullptr), unknown2d8(0), unknown2e8(nullptr) {
  WorkCpu::runThread(WorkCpu::getRenderCPUID(), thInitialize, this, nullptr, nullptr, false, WKCPU_SYNC_UNKNOWN_0);
}

u32 DebDrawCmd::thInitialize(void *argument, void *userData) {
  DebDrawCmd *draw = static_cast<DebDrawCmd *>(argument);
  draw->unknown2e0 = 0xc00000;
  draw->unknown2d0 = new (WorkUtil::getWorkMem()) grlib::CGLibVtxVertex();
  draw->unknown2d0->createVertexBuff(draw->unknown2e0, sizeof(unknown001));
  draw->unknown2f0 = false;
  return 0;
}

DebDrawCmd::~DebDrawCmd() {
  unknown008 = unknown2d0;
  WorkCpu::runThread(WorkCpu::getRenderCPUID(), thDestroy, &unknown008, nullptr, nullptr, false, WKCPU_SYNC_UNKNOWN_0);
}

u32 DebDrawCmd::thDestroy(void *argument, void *userData) {
  grlib::CGLibVtxVertex **vertex = static_cast<grlib::CGLibVtxVertex **>(argument);
  if (*vertex != nullptr) {
    delete *vertex;
    *vertex = nullptr;
  }
  return 0;
}

void DebDrawCmd::fastSetup() {
  unknown156 = false;
  if (unknown2f0) {
    unknown2dc = unknown2d8 = unknown2e0 / 2;
    unknown2f0 = false;
  } else {
    unknown2dc = unknown2d8 = 0;
    unknown2f0 = true;
  }
}

void DebDrawCmd::setVertex(const mm::Vec3 &position, const mm::Col4 &color, f32 u, f32 v) {
  static_cast<unknown001 *>(unknown2e8)->unknown003(position);
  static_cast<unknown001 *>(unknown2e8)->unknown004(color);
  static_cast<unknown001 *>(unknown2e8)->unknown005(u, v);
  unknown2dc += sizeof(unknown001);
  unknown2e8 = static_cast<unknown001 *>(unknown2e8) + 1;
}

void DebDrawCmd::add(const mm::Pnt<int> &first, const mm::Pnt<int> &second) {
  setVertex(mm::Vec3(first.x, first.y, unknown14c), unknown0c, 0.0f, 0.0f);
  setVertex(mm::Vec3(second.x, second.y, unknown14c), unknown0c, 0.0f, 0.0f);
  unknown140 += 2;
}

void DebDrawCmd::add(int x1, int y1, int x2, int y2) {
  setVertex(mm::Vec3(x1, y1, unknown14c), unknown0c, 0.0f, 0.0f);
  setVertex(mm::Vec3(x2, y2, unknown14c), unknown0c, 0.0f, 0.0f);
  unknown140 += 2;
}

void DebDrawCmd::add(const mm::Pnt<int> &position) {
  setVertex(mm::Vec3(position.x, position.y, unknown14c), unknown0c, 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(f32 x, f32 y, f32 z) { add(mm::Vec3(x, y, z)); }

void DebDrawCmd::add(int x, int y, int z) {
  setVertex(mm::Vec3(x, y, z), unknown0c, 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(int x, int y) {
  setVertex(mm::Vec3(x, y, unknown14c), unknown0c, 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(int x, int y, const mm::Col4 &color) {
  setVertex(mm::Vec3(x, y, unknown14c), color, 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(int x, int y, const mm::Col3 &color) {
  setVertex(mm::Vec3(x, y, unknown14c), mm::Col4(color.r, color.g, color.b, unknown0c.a), 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(const mm::Vec3 &position, const mm::Vec3 &texCoord, const mm::Col4 &color) {
  setVertex(position, color, texCoord.x, texCoord.y);
  unknown140++;
}

void DebDrawCmd::begin(u32 primitive, u32 count) {
  if (unknown210->begin(primitive, count)) {
    return;
  }
  unknown08 &= ~0xffff0004;
  unknown08 |= 0x200;
  unknown150 = count;
  unknown20 = primitive;
  switch (primitive) {
  case 1:
    unknown28 = count;
    unknown170 = GRL_PRIMITIVE_POINTS;
    unknown08 |= 0x10000;
    break;
  case 2:
    unknown28 = count * 2;
    unknown170 = GRL_PRIMITIVE_UNKNOWN_1;
    unknown08 |= 0x20000;
    break;
  case 3:
    unknown28 = count;
    unknown170 = GRL_PRIMITIVE_UNKNOWN_3;
    unknown08 |= 0xa0000;
    unknown150 = count - 1;
    break;
  case 4:
    unknown28 = count;
    unknown170 = GRL_PRIMITIVE_UNKNOWN_3;
    unknown08 |= 0xe0000;
    unknown150 = count - 1;
    break;
  case 5:
    unknown28 = count * 3;
    unknown170 = GRL_PRIMITIVE_TRIANGLES;
    unknown08 |= 0x200000;
    break;
  case 6:
    unknown28 = count;
    unknown170 = GRL_PRIMITIVE_TRIANGLE_STRIP;
    unknown08 |= 0x80000;
    unknown150 = count - 2;
    break;
  case 7:
    unknown28 = count;
    unknown170 = GRL_PRIMITIVE_UNKNOWN_6;
    unknown08 |= 0x80000;
    unknown150 = count - 2;
    break;
  case 8:
    unknown28 = count;
    unknown170 = GRL_PRIMITIVE_TRIANGLE_STRIP;
    unknown08 |= 0xc0000;
    unknown150 = count - 2;
    break;
  case 9:
    unknown28 = count * 4;
    unknown170 = GRL_PRIMITIVE_TRIANGLE_STRIP;
    unknown08 |= 0x100000;
    unknown150 = 2;
    break;
  case 10:
    unknown28 = count * 5;
    unknown170 = GRL_PRIMITIVE_UNKNOWN_3;
    unknown08 |= 0x1a0000;
    unknown150 = 4;
    break;
  case 12:
    unknown28 = count * 4;
    unknown170 = GRL_PRIMITIVE_QUADS;
    unknown08 |= 0x140002;
    unknown150 = 2;
    break;
  case 11:
    unknown28 = count * 4;
    unknown170 = GRL_PRIMITIVE_TRIANGLE_STRIP;
    unknown08 |= 0x180002;
    unknown150 = 2;
    break;
  }
  if (unknown08 & 8) {
    unknown280.unknown009(unknown40, unknown100);
  } else {
    DevGraph::get()->getOrthoSys(unknown280);
  }
  unknown2d0->lock(&unknown2e8, &unknown2e0);
  unknown2e8 = static_cast<u8 *>(unknown2e8) + unknown2d8;
  unknown2dc = unknown2d8;
  if (DevGraph::get() != nullptr) {
    if (unknown0c.a < 1.0f) {
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
    } else {
      grlib::CGLibColorCtl::setBlendOffControl(GRL_LOGIC_TYPE_COPY);
    }
  }
  grlib::CGLibPolygon::setLineWidth(unknown144);
  unknown140 = 0;
  unknown08 |= 4;
}

void DebDrawCmd::end() {
  if (unknown210->end()) {
    return;
  }
  if (unknown140 != 0 && unknown170 >= 0) {
    if (!unknown156) {
      grlib::CGLibColorCtl::setBlendControl(GRL_BLEND_FUNC_SRC_ALPHA, GRL_BLEND_FUNC_ONE_MINUS_SRC_ALPHA, GRL_BLEND_COMBINE_ADD, GRL_LOGIC_TYPE_COPY);
      unknown156 = true;
    }
    u32 start = unknown2d8;
    if (unknown2dc != start) {
      unknown2d0->unlock(start, unknown2dc - start);
      unknown2d8 = unknown2dc;
    }
    u32 mode = grlib::CGLibCtlShader::getDecShader()->getDeclarationOfs("DEBUG_MODE");
    grlib::GrlUtilVertFetch fetch;
    if (unknown08 & 2) {
      grlib::CGLibCtlShader::getDecShader()->setDeclarationIdx(mode, 2);
      fetch = grlib::GRL_UTIL_VERT_FETCH_UNKNOWN_0;
    } else {
      grlib::CGLibCtlShader::getDecShader()->setDeclarationIdx(mode, 1);
      fetch = grlib::GRL_UTIL_VERT_FETCH_UNKNOWN_1;
    }
    grlib::CGLibCtlVertex::setVertex(*unknown2d0, start);
    grlib::CGLibCtlShader::setShader(*grlib::CGLibCtlShader::getDecShader(), *grlib::CGLibCtlShader::getVtxFetch(fetch));
    grlib::CGLibDecShader *shader = grlib::CGLibCtlShader::getDecShader();
    u32 block = (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_MDL");
    grlib::CGLibEtcUniformBlock uniform;
    grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(uniform.getBuff()), unknown280);
    uniform.updateData(sizeof(mm::Mat44));
    uniform.setUniformBlock(block);
    if (unknown08 & 2) {
      shader = grlib::CGLibCtlShader::getDecShader();
      u32 location = (shader->unknown38 + shader->unknown58)->getTextureLocation("tex");
      grlib::CGLibCtlTexture::setTexture(*unknown180, *grlib::CGLibCtlShader::getSampler(grlib::GRL_UTIL_SAMPLER_UNKNOWN_1), location);
    }
    grlib::CGLibCtlVertex::renderVertex(static_cast<GrlPrimitiveType>(unknown170), unknown140);
    unknown140 = 0;
  }
  unknown08 &= ~0x200;
}

void DebDrawCmd::add(const mm::Vec3 &first, const mm::Vec3 &second) {
  if (unknown210->add(first, second)) {
    return;
  }
  u32 flags = unknown08;
  const mm::Vec3 *start = &first;
  const mm::Vec3 *end = &second;
  mm::Vec3 localStart;
  mm::Vec3 localEnd;
  if (flags & 8) {
    unknown002(localStart, first);
    unknown002(localEnd, second);
    start = &localStart;
    end = &localEnd;
  }
  if (!(flags & 2)) {
    if (flags & 0x20000) {
      setVertex(*start, unknown0c, 0.0f, 0.0f);
      setVertex(*end, unknown0c, 0.0f, 0.0f);
    }
    unknown140 += 2;
  }
}

void DebDrawCmd::add(const mm::Vec3 &position) {
  if (unknown210->add(position)) {
    return;
  }
  const mm::Vec3 *vertex = &position;
  mm::Vec3 local;
  if (unknown08 & 8) {
    unknown002(local, position);
    vertex = &local;
  }
  setVertex(*vertex, unknown0c, 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(const mm::Vec3 &position, const mm::Col4 &color) {
  const mm::Vec3 *vertex = &position;
  mm::Vec3 local;
  if (unknown08 & 8) {
    unknown002(local, position);
    vertex = &local;
  }
  setVertex(*vertex, color, 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(const mm::Vec3 &position, const mm::Col3 &color) {
  const mm::Vec3 *vertex = &position;
  mm::Vec3 local;
  if (unknown08 & 8) {
    unknown002(local, position);
    vertex = &local;
  }
  setVertex(*vertex, mm::Col4(color.r, color.g, color.b, unknown0c.a), 0.0f, 0.0f);
  unknown140++;
}

void DebDrawCmd::add(const mm::Rect<int> &rect) {
  u32 flags = unknown08;
  if (!(flags & 0x20000)) {
    if (!(flags & 2)) {
      setVertex(mm::Vec3(rect.x + rect.width, rect.y, unknown14c), unknown0c, 0.0f, 0.0f);
      setVertex(mm::Vec3(rect.x, rect.y, unknown14c), unknown0c, 0.0f, 0.0f);
      setVertex(mm::Vec3(rect.x + rect.width, rect.y + rect.height, unknown14c), unknown0c, 0.0f, 0.0f);
      setVertex(mm::Vec3(rect.x, rect.y + rect.height, unknown14c), unknown0c, 0.0f, 0.0f);
      unknown140 += 4;
    } else {
      setVertex(mm::Vec3(rect.x + rect.width, rect.y, unknown14c), unknown0c, 1.0f, 0.0f);
      setVertex(mm::Vec3(rect.x, rect.y, unknown14c), unknown0c, 0.0f, 0.0f);
      setVertex(mm::Vec3(rect.x + rect.width, rect.y + rect.height, unknown14c), unknown0c, 1.0f, 1.0f);
      setVertex(mm::Vec3(rect.x, rect.y + rect.height, unknown14c), unknown0c, 0.0f, 1.0f);
      unknown140 += 4;
    }
  } else {
    setVertex(mm::Vec3(rect.x, rect.y, unknown14c), unknown0c, 0.0f, 0.0f);
    setVertex(mm::Vec3(rect.x + rect.width, rect.y, unknown14c), unknown0c, 0.0f, 0.0f);
    setVertex(mm::Vec3(rect.x + rect.width, rect.y + rect.height, unknown14c), unknown0c, 0.0f, 0.0f);
    setVertex(mm::Vec3(rect.x, rect.y + rect.height, unknown14c), unknown0c, 0.0f, 0.0f);
    setVertex(mm::Vec3(rect.x, rect.y, unknown14c), unknown0c, 0.0f, 0.0f);
    unknown140 += 5;
  }
}

void DebDraw::setOrtho() {
  if (!unknown210->setOrtho()) {
    if (unknown08 & 8) {
      unknown08 &= ~4;
    }
    unknown08 &= ~8;
  }
}

void DebDraw::setZComp(bool isEnable) {
  if (!unknown210->setZComp(isEnable)) {
    unknown154 = isEnable;
    if (DevGraph::get() != nullptr) {
      if (isEnable) {
        grlib::CGLibDepthCtl::setDepthControl(true, unknown155, GRL_COMPARE_LEQUAL);
      } else {
        grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_ALWAYS);
      }
    }
  }
}

void DebDraw::setZWrite(bool isEnable) {
  if (!unknown210->setZWrite(isEnable)) {
    unknown155 = isEnable;
    if (DevGraph::get() != nullptr) {
      if (unknown154) {
        grlib::CGLibDepthCtl::setDepthControl(true, isEnable, GRL_COMPARE_LEQUAL);
      } else {
        grlib::CGLibDepthCtl::setDepthControl(false, false, GRL_COMPARE_ALWAYS);
      }
    }
  }
}

void DebDraw::setDoubleSide(bool isEnable) {
  if (!unknown210->setDoubleSide(isEnable) && DevGraph::get() != nullptr) {
    if (isEnable) {
      grlib::CGLibPolygon::setCullingOff();
    } else {
      grlib::CGLibPolygon::setCullingBack();
    }
  }
}

void DebDraw::renderPoint(const mm::Vec3 &position) {
  if (!unknown210->renderPoint(position)) {
    begin(1, 1);
    add(position);
    end();
  }
}

void CacheDraw::DRPNT::flush(DebDraw *draw) { draw->renderPoint(unknown0c); }

void DebDraw::renderLine(const mm::Vec3 &start, const mm::Vec3 &end) {
  if (!unknown210->renderLine(start, end)) {
    begin(2, 1);
    add(start, end);
    this->end();
  }
}

void DebDraw::renderLine(const mm::Pnt<int> &start, const mm::Pnt<int> &end) {
  if (!unknown210->renderLine(start, end)) {
    begin(2, 1);
    add(start, end);
    this->end();
  }
}

void DebDraw::renderTriangle(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third) {
  if (!unknown210->renderTriangle(first, second, third)) {
    begin(3, 4);
    add(first);
    add(second);
    add(third);
    add(first);
    end();
  }
}

void DebDraw::renderTriangleFill(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third) {
  if (!unknown210->renderTriangleFill(first, second, third)) {
    begin(6, 3);
    add(first);
    add(second);
    add(third);
    end();
  }
}

void DebDraw::renderRect(int x, int y, int width, int height) {
  if (!unknown210->renderRect(mm::Rect<int>(x, y, width, height))) {
    renderRect(mm::Rect<int>(x, y, width, height));
  }
}

void DebDraw::renderRectFill(int x, int y, int width, int height) {
  if (!unknown210->renderRectFill(mm::Rect<int>(x, y, width, height))) {
    renderRectFill(mm::Rect<int>(x, y, width, height));
  }
}

void DebDraw::renderPrimFill(const mm::PrimBase *prim) {
  if (prim->type == mm::PrimBase::PRIM_CUBE) {
    cubeFill(static_cast<const mm::Cube *>(prim));
  }
}

void DebDraw::cubeFill(const mm::Cube *cube) {
  mm::mtl::FixedArray<mm::Vec3, 8> vertices;
  cube->getVertices(vertices);
  begin(6, 10);
  add(vertices[0]);
  add(vertices[1]);
  add(vertices[3]);
  add(vertices[2]);
  add(vertices[7]);
  add(vertices[6]);
  add(vertices[4]);
  add(vertices[5]);
  add(vertices[0]);
  add(vertices[1]);
  end();
  begin(6, 4);
  add(vertices[1]);
  add(vertices[2]);
  add(vertices[5]);
  add(vertices[6]);
  end();
  begin(6, 4);
  add(vertices[3]);
  add(vertices[0]);
  add(vertices[7]);
  add(vertices[4]);
  end();
}

void DebDraw::cube(const mm::Cube *cube) {
  mm::mtl::FixedArray<mm::Vec3, 8> vertices;
  cube->getVertices(vertices);
  begin(3, 10);
  add(vertices[0]);
  add(vertices[1]);
  add(vertices[2]);
  add(vertices[3]);
  add(vertices[0]);
  add(vertices[4]);
  add(vertices[5]);
  add(vertices[6]);
  add(vertices[7]);
  add(vertices[4]);
  end();
  begin(2, 3);
  add(vertices[5], vertices[1]);
  add(vertices[6], vertices[2]);
  add(vertices[7], vertices[3]);
  end();
}

void DebDraw::cylinder(const mm::Cylinder *cylinder) {
  mm::Mat44 matrix;
  cylinder->getMat(matrix);
  setMatrix(matrix);
  begin(3, 34);
  for (int i = 0; i < 17; i++) {
    add(unknown005[i % 16]);
  }
  for (int i = 0; i < 17; i++) {
    add(unknown006[i % 16]);
  }
  end();
  begin(2, 15);
  for (int i = 1; i < 16; i++) {
    add(unknown005[i], unknown006[i]);
  }
  end();
}

void DebDraw::sphere(const mm::Sphere *sphere) { renderSphere(sphere->getPos(), sphere->scale.x, 8); }

void DebDraw::renderSphere(const mm::Sphere &sphere, int division) { renderSphere(sphere.getPos(), sphere.scale.x, division); }

void DebDraw::setCol(const mm::Col4 &color) {
  if (!unknown210->setCol(color)) {
    unknown0c = color;
    unknown004(unknown0c);
    unknown08 &= ~4;
  }
}

void DebDraw::setCol(const mm::Col3 &color, f32 alpha) {
  CacheDraw *cacheDraw = unknown210;
  mm::Col4 opaque;
  opaque.r = color.r;
  opaque.g = color.g;
  opaque.b = color.b;
  opaque.a = 1.0f;
  if (!cacheDraw->setCol(opaque)) {
    unknown0c.r = color.r;
    unknown0c.g = color.g;
    unknown0c.b = color.b;
    unknown0c.a = alpha;
    unknown004(unknown0c);
    unknown08 &= ~4;
  }
}

void DebDraw::setCol(f32 r, f32 g, f32 b, f32 a) { setCol(mm::Col4(r, g, b, a)); }

void DebDraw::renderAxis(f32 length) {
  if (!unknown210->renderAxis(length)) {
    mm::Col4 color = unknown0c;
    setCol(mm::Col3::red, 1.0f);
    renderLine(mm::Vec3::zero, mm::Vec3(length, 0.0f, 0.0f));
    setCol(mm::Col3::green, 1.0f);
    renderLine(mm::Vec3::zero, mm::Vec3(0.0f, length, 0.0f));
    setCol(mm::Col3::blue, 1.0f);
    renderLine(mm::Vec3::zero, mm::Vec3(0.0f, 0.0f, length));
    setCol(color);
  }
}

void DebDraw::renderArrowAxisX(const mm::Vec3 &position, int size, const mm::Col4 *color, bool isCube) {
  mm::Vec3 screenStart;
  if (!getScreenPos(screenStart, position)) {
    return;
  }
  mm::Vec3 screenEnd;
  if (!getScreenPos(screenEnd,
                    mm::Vec3(mm::Vec3::unitX.x * unknown80.rows[0][0] + mm::Vec3::unitX.y * unknown80.rows[1][0] + mm::Vec3::unitX.z * unknown80.rows[2][0],
                             mm::Vec3::unitX.x * unknown80.rows[0][1] + mm::Vec3::unitX.y * unknown80.rows[1][1] + mm::Vec3::unitX.z * unknown80.rows[2][1],
                             mm::Vec3::unitX.x * unknown80.rows[0][2] + mm::Vec3::unitX.y * unknown80.rows[1][2] + mm::Vec3::unitX.z * unknown80.rows[2][2]) +
                        position)) {
    return;
  }
  screenStart.z = 0.0f;
  screenEnd.z = 0.0f;
  f32 length = sqrtf((screenStart.x - screenEnd.x) * (screenStart.x - screenEnd.x) + (screenStart.y - screenEnd.y) * (screenStart.y - screenEnd.y) +
                     (screenStart.z - screenEnd.z) * (screenStart.z - screenEnd.z));
  f32 scale = size / length;
  mm::Col4 saved = unknown0c;
  if (color == nullptr) {
    setCol(mm::Col3::red, 1.0f);
  } else {
    setCol(*color);
  }
  if (isCube) {
    renderCubeArrow(position, position + mm::Vec3(scale, 0.0f, 0.0f));
  } else {
    renderArrow(position, position + mm::Vec3(scale, 0.0f, 0.0f));
  }
  setCol(saved);
}

void DebDraw::renderArrowAxisY(const mm::Vec3 &position, int size, const mm::Col4 *color, bool isCube) {
  mm::Vec3 screenStart;
  if (!getScreenPos(screenStart, position)) {
    return;
  }
  mm::Vec3 screenEnd;
  if (!getScreenPos(screenEnd,
                    mm::Vec3(mm::Vec3::unitX.x * unknown80.rows[0][0] + mm::Vec3::unitX.y * unknown80.rows[1][0] + mm::Vec3::unitX.z * unknown80.rows[2][0],
                             mm::Vec3::unitX.x * unknown80.rows[0][1] + mm::Vec3::unitX.y * unknown80.rows[1][1] + mm::Vec3::unitX.z * unknown80.rows[2][1],
                             mm::Vec3::unitX.x * unknown80.rows[0][2] + mm::Vec3::unitX.y * unknown80.rows[1][2] + mm::Vec3::unitX.z * unknown80.rows[2][2]) +
                        position)) {
    return;
  }
  screenStart.z = 0.0f;
  screenEnd.z = 0.0f;
  f32 length = sqrtf((screenStart.x - screenEnd.x) * (screenStart.x - screenEnd.x) + (screenStart.y - screenEnd.y) * (screenStart.y - screenEnd.y) +
                     (screenStart.z - screenEnd.z) * (screenStart.z - screenEnd.z));
  f32 scale = size / length;
  mm::Col4 saved = unknown0c;
  if (color == nullptr) {
    setCol(mm::Col3::green, 1.0f);
  } else {
    setCol(*color);
  }
  if (isCube) {
    renderCubeArrow(position, position + mm::Vec3(0.0f, scale, 0.0f));
  } else {
    renderArrow(position, position + mm::Vec3(0.0f, scale, 0.0f));
  }
  setCol(saved);
}

void DebDraw::renderArrowAxisZ(const mm::Vec3 &position, int size, const mm::Col4 *color, bool isCube) {
  mm::Vec3 screenStart;
  if (!getScreenPos(screenStart, position)) {
    return;
  }
  mm::Vec3 screenEnd;
  if (!getScreenPos(screenEnd,
                    mm::Vec3(mm::Vec3::unitX.x * unknown80.rows[0][0] + mm::Vec3::unitX.y * unknown80.rows[1][0] + mm::Vec3::unitX.z * unknown80.rows[2][0],
                             mm::Vec3::unitX.x * unknown80.rows[0][1] + mm::Vec3::unitX.y * unknown80.rows[1][1] + mm::Vec3::unitX.z * unknown80.rows[2][1],
                             mm::Vec3::unitX.x * unknown80.rows[0][2] + mm::Vec3::unitX.y * unknown80.rows[1][2] + mm::Vec3::unitX.z * unknown80.rows[2][2]) +
                        position)) {
    return;
  }
  screenStart.z = 0.0f;
  screenEnd.z = 0.0f;
  f32 length = sqrtf((screenStart.x - screenEnd.x) * (screenStart.x - screenEnd.x) + (screenStart.y - screenEnd.y) * (screenStart.y - screenEnd.y) +
                     (screenStart.z - screenEnd.z) * (screenStart.z - screenEnd.z));
  f32 scale = size / length;
  mm::Col4 saved = unknown0c;
  if (color == nullptr) {
    setCol(mm::Col3::blue, 1.0f);
  } else {
    setCol(*color);
  }
  if (isCube) {
    renderCubeArrow(position, position + mm::Vec3(0.0f, 0.0f, scale));
  } else {
    renderArrow(position, position + mm::Vec3(0.0f, 0.0f, scale));
  }
  setCol(saved);
}

void DebDraw::renderArrowAxis(const mm::Vec3 &position, int size, bool isCube) {
  mm::Vec3 screenStart;
  if (!getScreenPos(screenStart, position)) {
    return;
  }
  mm::Vec3 screenEnd;
  if (!getScreenPos(screenEnd,
                    mm::Vec3(mm::Vec3::unitX.x * unknown80.rows[0][0] + mm::Vec3::unitX.y * unknown80.rows[1][0] + mm::Vec3::unitX.z * unknown80.rows[2][0],
                             mm::Vec3::unitX.x * unknown80.rows[0][1] + mm::Vec3::unitX.y * unknown80.rows[1][1] + mm::Vec3::unitX.z * unknown80.rows[2][1],
                             mm::Vec3::unitX.x * unknown80.rows[0][2] + mm::Vec3::unitX.y * unknown80.rows[1][2] + mm::Vec3::unitX.z * unknown80.rows[2][2]) +
                        position)) {
    return;
  }
  screenStart.z = 0.0f;
  screenEnd.z = 0.0f;
  f32 length = sqrtf((screenStart.x - screenEnd.x) * (screenStart.x - screenEnd.x) + (screenStart.y - screenEnd.y) * (screenStart.y - screenEnd.y) +
                     (screenStart.z - screenEnd.z) * (screenStart.z - screenEnd.z));
  f32 scale = size / length;
  mm::Col4 saved = unknown0c;
  setCol(mm::Col3::red, 1.0f);
  if (isCube) {
    renderCubeArrow(position, position + mm::Vec3(scale, 0.0f, 0.0f));
  } else {
    renderArrow(position, position + mm::Vec3(scale, 0.0f, 0.0f));
  }
  setCol(mm::Col3::green, 1.0f);
  if (isCube) {
    renderCubeArrow(position, position + mm::Vec3(0.0f, scale, 0.0f));
  } else {
    renderArrow(position, position + mm::Vec3(0.0f, scale, 0.0f));
  }
  setCol(mm::Col3::blue, 1.0f);
  if (isCube) {
    renderCubeArrow(position, position + mm::Vec3(0.0f, 0.0f, scale));
  } else {
    renderArrow(position, position + mm::Vec3(0.0f, 0.0f, scale));
  }
  setCol(saved);
}

void DebDraw::renderOBB(const mm::Obb &obb) {
  if (!unknown210->renderOBB(obb)) {
    mm::Vec3 vertices[8];
    obb.getVertices(vertices);
    begin(3, 10);
    add(vertices[0]);
    add(vertices[1]);
    add(vertices[2]);
    add(vertices[3]);
    add(vertices[0]);
    add(vertices[4]);
    add(vertices[5]);
    add(vertices[6]);
    add(vertices[7]);
    add(vertices[4]);
    end();
    renderLine(vertices[1], vertices[5]);
    renderLine(vertices[2], vertices[6]);
    renderLine(vertices[3], vertices[7]);
  }
}

void DebDraw::renderCube(const mm::Vec3 &min, const mm::Vec3 &max) {
  if (!unknown210->renderCube(min, max)) {
    unknown08 &= ~4;
    begin(3, 10);
    add(min);
    add(mm::Vec3(max.x, min.y, min.z));
    add(mm::Vec3(max.x, max.y, min.z));
    add(mm::Vec3(min.x, max.y, min.z));
    add(min);
    add(mm::Vec3(min.x, min.y, max.z));
    add(mm::Vec3(max.x, min.y, max.z));
    add(mm::Vec3(max.x, max.y, max.z));
    add(mm::Vec3(min.x, max.y, max.z));
    add(mm::Vec3(min.x, min.y, max.z));
    end();
    begin(2, 3);
    add(mm::Vec3(max.x, min.y, min.z), mm::Vec3(max.x, min.y, max.z));
    add(mm::Vec3(max.x, max.y, min.z), mm::Vec3(max.x, max.y, max.z));
    add(mm::Vec3(min.x, max.y, min.z), mm::Vec3(min.x, max.y, max.z));
    end();
  }
}

void DebDraw::renderCubeFill(const mm::Vec3 &min, const mm::Vec3 &max) {
  if (!unknown210->renderCubeFill(min, max)) {
    begin(6, 10);
    add(min);
    add(mm::Vec3(max.x, min.y, min.z));
    add(mm::Vec3(min.x, max.y, min.z));
    add(mm::Vec3(max.x, max.y, min.z));
    add(mm::Vec3(min.x, max.y, max.z));
    add(mm::Vec3(max.x, max.y, max.z));
    add(mm::Vec3(min.x, min.y, max.z));
    add(mm::Vec3(max.x, min.y, max.z));
    add(min);
    add(mm::Vec3(max.x, min.y, min.z));
    end();
    begin(6, 4);
    add(min);
    add(mm::Vec3(min.x, max.y, min.z));
    add(mm::Vec3(min.x, min.y, max.z));
    add(mm::Vec3(min.x, max.y, max.z));
    end();
    begin(6, 4);
    add(mm::Vec3(max.x, max.y, min.z));
    add(mm::Vec3(max.x, min.y, min.z));
    add(mm::Vec3(max.x, max.y, max.z));
    add(mm::Vec3(max.x, min.y, max.z));
    end();
  }
}

void DebDraw::renderPrim(const mm::PrimBase *prim) {
  CacheDraw *cacheDraw = unknown210;
  mm::Mat44 matrix;
  prim->getMat(matrix);
  if (!cacheDraw->renderPrim(matrix, prim->type)) {
    switch (prim->type) {
    case mm::PrimBase::PRIM_CUBE:
      cube(static_cast<const mm::Cube *>(prim));
      break;
    case mm::PrimBase::PRIM_CYLINDER:
      cylinder(static_cast<const mm::Cylinder *>(prim));
      break;
    case mm::PrimBase::PRIM_SPHERE:
      sphere(static_cast<const mm::Sphere *>(prim));
      break;
    }
  }
}

void DebDraw::renderRect(const mm::Rect<int> &rect) {
  if (!unknown210->renderRect(rect)) {
    unknown08 &= ~0xa;
    begin(3, 5);
    add(rect.x, rect.y, 0);
    add(rect.x + rect.width, rect.y, 0);
    add(rect.x + rect.width, rect.y + rect.height, 0);
    add(rect.x - 1, rect.y + rect.height, 0);
    add(rect.x, rect.y, 0);
    end();
  }
}

void DebDraw::renderRectFill(const mm::Rect<int> &rect) {
  if (!unknown210->renderRectFill(rect)) {
    unknown08 &= ~0xa;
    begin(6, 4);
    add(rect.x, rect.y, 0);
    add(rect.x + rect.width, rect.y, 0);
    add(rect.x, rect.y + rect.height, 0);
    add(rect.x + rect.width, rect.y + rect.height, 0);
    end();
  }
}

void DebDraw::renderRectFill(const mm::Rect<int> &first, const mm::Rect<int> &second) {
  begin(6, 4);
  add(first.x, first.y, second.x, second.y);
  add(first.x + first.width, first.y, second.x + second.width, second.y);
  add(first.x, first.y + first.height, second.x, second.y + second.height);
  add(first.x + first.width, first.y + first.height, second.x + second.width, second.y + second.height);
  end();
}

void DebDraw::renderDiamondUp(const mm::Rect<int> &rect) {
  mm::Col4 color = unknown0c;
  setCol(mm::Col4(color.r * 1.3f, color.g * 1.3f, color.b * 1.3f, color.a));
  begin(2, 1);
  add(rect.x, rect.y + rect.height / 2, rect.x + rect.width / 2, rect.y);
  end();
  setCol(mm::Col4(color.r * 1.1f, color.g * 1.1f, color.b * 1.1f, color.a));
  begin(2, 1);
  add(rect.x + rect.width / 2, rect.y, rect.x + rect.width, rect.y + rect.height / 2);
  end();
  setCol(mm::Col4(color.r * 0.7f, color.g * 0.7f, color.b * 0.7f, color.a));
  begin(2, 1);
  add(rect.x + rect.width, rect.y + rect.height / 2, rect.x + rect.width / 2, rect.y + rect.height);
  end();
  setCol(mm::Col4(color.r * 0.9f, color.g * 0.9f, color.b * 0.9f, color.a));
  begin(2, 1);
  add(rect.x + rect.width / 2, rect.y + rect.height, rect.x, rect.y + rect.height / 2);
  end();
  setCol(color);
}

void DebDraw::renderDiamondDown(const mm::Rect<int> &rect) {
  mm::Col4 color = unknown0c;
  setCol(mm::Col4(color.r * 0.7f, color.g * 0.7f, color.b * 0.7f, color.a));
  begin(2, 1);
  add(rect.x, rect.y + rect.height / 2, rect.x + rect.width / 2, rect.y);
  end();
  setCol(mm::Col4(color.r * 0.9f, color.g * 0.9f, color.b * 0.9f, color.a));
  begin(2, 1);
  add(rect.x + rect.width / 2, rect.y, rect.x + rect.width, rect.y + rect.height / 2);
  end();
  setCol(mm::Col4(color.r * 1.3f, color.g * 1.3f, color.b * 1.3f, color.a));
  begin(2, 1);
  add(rect.x + rect.width / 2, rect.y + rect.height, rect.x + rect.width, rect.y + rect.height / 2);
  end();
  setCol(mm::Col4(color.r * 1.1f, color.g * 1.1f, color.b * 1.1f, color.a));
  begin(2, 1);
  add(rect.x, rect.y + rect.height / 2, rect.x + rect.width / 2, rect.y + rect.height);
  end();
  setCol(color);
}

void DebDraw::renderDiamondFill(const mm::Rect<int> &rect) {
  begin(6, 4);
  add(rect.x + rect.width / 2, rect.y);
  add(rect.x + rect.width, rect.y + rect.height / 2);
  add(rect.x, rect.y + rect.height / 2);
  add(rect.x + rect.width / 2, rect.y + rect.height);
  end();
}

void DebDraw::renderSquareFill(f32 width, f32 height) {
  if (!unknown210->renderSquareFill(width, height)) {
    mm::Vec3 fourth(width * -0.5f, height * 0.5f, 0.0f);
    mm::Vec3 third(width * 0.5f, height * 0.5f, 0.0f);
    mm::Vec3 second(width * -0.5f, height * -0.5f, 0.0f);
    mm::Vec3 first(width * 0.5f, height * -0.5f, 0.0f);
    begin(6, 4);
    add(fourth);
    add(third);
    add(second);
    add(first);
    end();
  }
}

void DebDraw::renderSquare(f32 width, f32 height) {
  if (!unknown210->renderSquare(width, height)) {
    mm::Vec3 fourth(width * -0.5f, height * 0.5f, 0.0f);
    mm::Vec3 third(width * 0.5f, height * 0.5f, 0.0f);
    mm::Vec3 second(width * -0.5f, height * -0.5f, 0.0f);
    mm::Vec3 first(width * 0.5f, height * -0.5f, 0.0f);
    begin(3, 5);
    add(fourth);
    add(third);
    add(first);
    add(second);
    add(fourth);
    end();
  }
}

void DebDraw::renderGrid(f32 size, f32 step) {
  if (!unknown210->renderGrid(size, step)) {
    int count = static_cast<int>(size / step);
    begin(2, count << 2 | 2);
    if (count >= 0) {
      f32 min = -(count * step);
      f32 max = count * step;
      f32 pos = min;
      for (int i = 0; i <= count * 2; i++) {
        add(mm::Vec3(pos, 0.0f, min), mm::Vec3(pos, 0.0f, max));
        add(mm::Vec3(min, 0.0f, pos), mm::Vec3(max, 0.0f, pos));
        pos += step;
      }
    }
    end();
    renderAxis(1.0f);
  }
}

void DebDraw::renderCircle(const mm::Vec3 &center, f32 radius, int division) {
  if (!unknown210->renderCircle(center, radius, division)) {
    u32 flags = unknown08;
    begin(3, division + 1);
    if (!(flags & 8)) {
      for (int i = 0; i <= division; i++) {
        f32 angle = (6.2831855f / division) * i;
        add(mm::Vec3(center.x + sinf(angle) * radius, center.y + cosf(angle) * radius, 0.0f));
      }
    } else {
      for (int i = 0; i <= division; i++) {
        f32 angle = (6.2831855f / division) * i;
        add(mm::Vec3(center.x + sinf(angle) * radius, center.y, center.z + cosf(angle) * radius));
      }
    }
    end();
  }
}

void DebDraw::renderCircleFill(const mm::Vec3 &center, f32 radius, int division) {
  if (!unknown210->renderCircle(center, radius, division)) {
    u32 flags = unknown08;
    begin(7, division + 2);
    add(center);
    if (!(flags & 8)) {
      for (int i = division; i >= 0; i--) {
        f32 angle = (6.2831855f / division) * i;
        add(mm::Vec3(center.x + sinf(angle) * radius, center.y + cosf(angle) * radius, 0.0f));
      }
    } else {
      for (int i = division; i >= 0; i--) {
        f32 angle = (6.2831855f / division) * i;
        add(mm::Vec3(center.x + sinf(angle) * radius, center.y, center.z + cosf(angle) * radius));
      }
    }
    end();
  }
}

void DebDraw::renderFanFill(const mm::Vec3 &center, f32 radius, f32 direction, f32 angle) {
  if (!unknown210->renderFanFill(center, radius, direction, angle)) {
    u32 flags = unknown08;
    int division = static_cast<int>(angle / 0.17453294f) + 1;
    begin(7, division + 2);
    add(center);
    if (!(flags & 8)) {
      for (int i = division; i >= 0; i--) {
        f32 rot = (angle / division) * i - angle * 0.5f + direction;
        add(center.x + sinf(rot) * radius, center.y + cosf(rot) * radius, 0.0f);
      }
    } else {
      for (int i = division; i >= 0; i--) {
        f32 rot = (angle / division) * i - angle * 0.5f + direction;
        add(center.x + sinf(rot) * radius, center.y, center.z + cosf(rot) * radius);
      }
    }
    end();
  }
}

void DebDraw::renderConeFill(f32 radius, f32 height, u32 division) {
  if (!unknown210->renderConeFill(radius, height, division)) {
    mm::Vec3 apex(0.0f, radius, 0.0f);
    u32 count = 8;
    if (division >= 8) {
      count = division;
    }
    begin(5, count);
    for (u32 i = 0; i < count; i++) {
      f32 angle = (6.2831855f / count) * i;
      f32 nextIndex = 0.0f;
      if (i != count - 1) {
        nextIndex = i + 1;
      }
      f32 nextAngle = (6.2831855f / count) * nextIndex;
      f32 firstSin = sinf(angle);
      f32 firstCos = cosf(angle);
      f32 secondSin = sinf(nextAngle);
      f32 secondCos = cosf(nextAngle);
      mm::Vec3 first(firstSin * height, 0.0f, firstCos * height);
      mm::Vec3 second(secondSin * height, 0.0f, secondCos * height);
      add(apex, first, second);
    }
    end();
  }
}

void DebDraw::renderCylinder(f32 radius, f32 height, u32 division) {
  if (!unknown210->renderCylinder(radius, height, division)) {
    u32 count = 8;
    if (division >= 8) {
      count = division;
    }
    begin(3, count + 1);
    f32 step = 6.2831855f / count;
    u32 i = 0;
    do {
      i++;
      f32 angle = step * (i % count);
      f32 angleSin = sinf(angle);
      f32 angleCos = cosf(angle);
      mm::Vec3 rim(angleSin * height, radius * 0.5f, angleCos * height);
      add(rim);
    } while (i <= count);
    end();
    begin(3, count + 1);
    i = 0;
    do {
      i++;
      f32 angle = step * (i % count);
      f32 angleSin = sinf(angle);
      f32 angleCos = cosf(angle);
      mm::Vec3 rim(angleSin * height, radius * -0.5f, angleCos * height);
      add(rim);
    } while (i <= count);
    end();
    begin(2, count);
    for (u32 j = 0; j < count; j++) {
      f32 angle = step * j;
      f32 angleSin = sinf(angle);
      f32 angleCos = cosf(angle);
      mm::Vec3 top(angleSin * height, radius * 0.5f, angleCos * height);
      mm::Vec3 bottom(angleSin * height, radius * -0.5f, angleCos * height);
      add(top, bottom);
    }
    end();
  }
}

void DebDraw::renderCylinderFill(f32 radius, f32 height, u32 division) {
  if (!unknown210->renderCylinderFill(radius, height, division)) {
    u32 count = 8;
    if (division >= 8) {
      count = division;
    }
    begin(5, count * 2);
    for (u32 i = 0; i < count; i++) {
      f32 angle = (6.2831855f / count) * i;
      f32 nextIndex = 0.0f;
      if (i != count - 1) {
        nextIndex = i + 1;
      }
      f32 nextAngle = (6.2831855f / count) * nextIndex;
      f32 firstSin = sinf(angle);
      f32 firstCos = cosf(angle);
      f32 secondSin = sinf(nextAngle);
      f32 secondCos = cosf(nextAngle);
      mm::Vec3 topFirst(firstSin * height, radius * 0.5f, firstCos * height);
      mm::Vec3 topSecond(secondSin * height, radius * 0.5f, secondCos * height);
      mm::Vec3 bottomFirst(firstSin * height, radius * -0.5f, firstCos * height);
      mm::Vec3 bottomSecond(secondSin * height, radius * -0.5f, secondCos * height);
      add(topFirst, bottomFirst, bottomSecond);
      add(topFirst, bottomSecond, topSecond);
    }
    end();
  }
}

void DebDraw::renderCone(f32 radius, f32 height, u32 division) {
  if (!unknown210->renderConeFill(radius, height, division)) {
    mm::Vec3 apex(0.0f, radius, 0.0f);
    u32 count = 8;
    if (division >= 8) {
      count = division;
    }
    begin(3, count + 1);
    f32 step = 6.2831855f / count;
    u32 i = 0;
    do {
      i++;
      f32 angle = step * (i % count);
      f32 angleSin = sinf(angle);
      f32 angleCos = cosf(angle);
      mm::Vec3 rim(angleSin * height, 0.0f, angleCos * height);
      add(rim);
    } while (i <= count);
    end();
    begin(2, count);
    for (u32 j = 0; j < count; j++) {
      f32 angle = step * j;
      f32 angleSin = sinf(angle);
      f32 angleCos = cosf(angle);
      mm::Vec3 rim(angleSin * height, 0.0f, angleCos * height);
      add(apex, rim);
    }
    end();
  }
}

template class fixed_size_alloc<DebDraw::PRM_DATA>;
template class reslist<DebDraw::PRM_DATA *>;

} // namespace ml
