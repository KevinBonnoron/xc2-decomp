#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "grlib/cglib_depth_ctl.h"
#include "grlib/cglib_polygon.h"
#include "ml/cache_draw.h"
#include "ml/dev_font.h"
#include "ml/dev_graph.h"
#include "ml/fixed_size_alloc.h"
#include "ml/ml_mem.h"
#include "ml/reslist.h"
#include "ml/work_cpu.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_cube.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_prim_base.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
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

void DebDraw::setForceRenderQueue(bool isForce) {
  m_forceRenderQueue = isForce;
  unknown210->setForceRenderQueue(isForce);
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
