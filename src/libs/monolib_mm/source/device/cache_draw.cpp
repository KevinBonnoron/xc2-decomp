#include "ml/cache_draw.h"

#include <new>
#include <string.h>

#include "ml/critical_section.h"
#include "ml/win_view.h"
#include "ml/work_cpu.h"
#include "mtl/mem_manager.h"

namespace ml {

CacheDraw::CacheDraw(mtl::ALLOC_HANDLE handle, size_t size)
    : unknown6048(handle), m_currentPrio(-1), m_cacheDrawWID(0xffffffff), unknown6054(1.0f), unknown6058(1.0f), m_forceRenderQueue(false), m_suspendSwap(0), unknown6070(true) {
  unknown6060 = new (handle) CriticalSectionNC();
  unknown6060->setCostIgnore(true);
  for (int i = 0; i < 2; i++) {
    unknown08[i].unknown10 = size / 2;
    unknown08[i].unknown00 = static_cast<u8 *>(mtl::MemManager::allocate(handle, size / 2, 0x10, false, "no name", 0));
    unknown08[i].unknown08 = unknown08[i].unknown00;
  }
  clearSystem(true);
  clearSystem(false);
}

void CacheDraw::clearSystem(bool isOdd) {
  if (m_suspendSwap == 0) {
    unknown003 *buf = getBuf(isOdd);
    buf->unknown08 = buf->unknown00;
    buf->unknown3018 = 0;
    for (int i = 0; i < 0x200; i++) {
      // Original bug: every iteration clears the range at the range count, which is 0 here, instead of range i.
      buf->unknown18[buf->unknown3018].unknown08 = nullptr;
      buf->unknown18[buf->unknown3018].unknown00 = nullptr;
      buf->unknown18[buf->unknown3018].unknown10 = -1;
    }
  }
  unknown6054 = 1.0f;
  unknown6058 = 1.0f;
  unknown6070 = true;
}

CacheDraw::~CacheDraw() {
  mtl::MemManager::deallocate(unknown08[0].unknown00, 0, false);
  mtl::MemManager::deallocate(unknown08[1].unknown00, 0, false);
  if (unknown6060 != nullptr) {
    delete unknown6060;
    unknown6060 = nullptr;
  }
}

void CacheDraw::setSuspendSwap(bool isSuspend) {
  CSNC lock(*unknown6060);
  if (isSuspend) {
    if (m_suspendSwap == 0) {
      m_suspendSwap = WorkCpu::getOdd() + 1;
      unknown003 &src = unknown08[WorkCpu::getOdd()];
      unknown003 &dst = unknown08[WorkCpu::getEven()];
      memcpy(dst.unknown00, src.unknown00, src.unknown10);
      dst.unknown08 = reinterpret_cast<u8 *>(reinterpret_cast<size_t>(dst.unknown00) + (reinterpret_cast<size_t>(src.unknown08) - reinterpret_cast<size_t>(src.unknown00)));
      for (u32 i = 0; i < src.unknown3018; i++) {
        dst.unknown18[i].unknown08 = reinterpret_cast<u8 *>(reinterpret_cast<size_t>(dst.unknown00) + (reinterpret_cast<size_t>(src.unknown18[i].unknown08) - reinterpret_cast<size_t>(src.unknown00)));
        dst.unknown18[i].unknown00 = reinterpret_cast<u8 *>(reinterpret_cast<size_t>(dst.unknown00) + (reinterpret_cast<size_t>(src.unknown18[i].unknown00) - reinterpret_cast<size_t>(src.unknown00)));
        dst.unknown18[i].unknown10 = src.unknown18[i].unknown10;
      }
      dst.unknown3018 = src.unknown3018;
    }
  } else if (m_suspendSwap != 0) {
    m_suspendSwap = 0;
    unknown003 *buf = &unknown08[WorkCpu::getEven()];
    buf->unknown08 = buf->unknown00;
    buf->unknown3018 = 0;
    for (int i = 0; i < 0x200; i++) {
      // Original bug: the same range clearing as clearSystem, at the range count instead of range i.
      buf->unknown18[buf->unknown3018].unknown08 = nullptr;
      buf->unknown18[buf->unknown3018].unknown00 = nullptr;
      buf->unknown18[buf->unknown3018].unknown10 = -1;
    }
  }
}

void CacheDraw::swap() {
  if (m_suspendSwap == 0) {
    unknown003 &buf = unknown08[WorkCpu::getOdd()];
    u8 *end = buf.unknown08;
    if (buf.unknown00 < end) {
      buf.unknown3018++;
      buf.unknown18[buf.unknown3018].unknown08 = end;
      buf.unknown18[buf.unknown3018].unknown00 = end;
      buf.unknown18[buf.unknown3018].unknown10 = m_currentPrio;
    }
  }
}

CacheDraw::unknown003 *CacheDraw::getBuf(bool isOdd) {
  if (!isOdd && (WorkCpu::getCurrentThreadId() == WorkCpu::getMainThreadId() || !m_forceRenderQueue)) {
    return &unknown08[WorkCpu::getEven()];
  }
  return &unknown08[WorkCpu::getOdd()];
}

void CacheDraw::setForceRenderQueue(bool isForce) {
  m_forceRenderQueue = isForce;
  if (!isForce) {
    swap();
  }
}

void CacheDraw::reset_prim(u32 wid) {
  if (wid != 0xffffffff) {
    m_cacheDrawWID = wid;
  }
  if (m_currentPrio >= 0) {
    unknown003 *buf = getBuf(false);
    if (buf->unknown18[buf->unknown3018].unknown00 != buf->unknown18[buf->unknown3018].unknown08) {
      buf->unknown3018++;
    }
    buf->unknown18[buf->unknown3018].unknown08 = buf->unknown08;
    buf->unknown18[buf->unknown3018].unknown00 = buf->unknown08;
    buf->unknown18[buf->unknown3018].unknown10 = m_currentPrio;
  }
}

bool CacheDraw::calcCurrentBuf(size_t size) {
  unknown003 *buf = getBuf(false);
  u8 *start = buf->unknown18[buf->unknown3018].unknown00;
  u8 *end = buf->unknown08;
  if (start == nullptr) {
    buf->unknown18[buf->unknown3018].unknown00 = end;
    buf->unknown18[buf->unknown3018].unknown10 = m_currentPrio;
  }
  buf->unknown08 = end + size;
  buf->unknown18[buf->unknown3018].unknown08 = buf->unknown08;
  return true;
}

bool CacheDraw::clear() {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DCLEAR();
    return calcCurrentBuf(sizeof(DCLEAR));
  }
  return false;
}

bool CacheDraw::setMatrix(const mm::Mat44 &matrix) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DMAT(matrix);
    return calcCurrentBuf(sizeof(DMAT));
  }
  return false;
}

bool CacheDraw::setOrtho() {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DORTHO();
    return calcCurrentBuf(sizeof(DORTHO));
  }
  return false;
}

bool CacheDraw::setTex(grlib::CGLibTextureBuffer *texture) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DTEX(texture);
    return calcCurrentBuf(sizeof(DTEX));
  }
  return false;
}

bool CacheDraw::setDoubleSide(bool isEnable) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DDOUBLESIDE(isEnable);
    return calcCurrentBuf(sizeof(DDOUBLESIDE));
  }
  return false;
}

bool CacheDraw::setZComp(bool isEnable) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DZCOMP(isEnable);
    return calcCurrentBuf(sizeof(DZCOMP));
  }
  return false;
}

bool CacheDraw::setZWrite(bool isEnable) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    unknown6070 = isEnable;
    new (getBuf(false)->unknown08) DZWRITE(isEnable);
    return calcCurrentBuf(sizeof(DZWRITE));
  }
  return false;
}

bool CacheDraw::setAlpha(f32 alpha) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DALPHA(alpha);
    return calcCurrentBuf(sizeof(DALPHA));
  }
  return false;
}

bool CacheDraw::renderRect(const mm::Rect<int> &rect) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRRECT(rect);
    return calcCurrentBuf(sizeof(DRRECT));
  }
  return false;
}

bool CacheDraw::renderRectFill(const mm::Rect<int> &rect) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRRECT_FILL(rect);
    return calcCurrentBuf(sizeof(DRRECT_FILL));
  }
  return false;
}

bool CacheDraw::renderTriangle2DFill(const mm::Pnt<int> &first, const mm::Pnt<int> &second, const mm::Pnt<int> &third) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRTRI2D_FILL(first, second, third);
    return calcCurrentBuf(sizeof(DRTRI2D_FILL));
  }
  return false;
}

bool CacheDraw::renderCircle(const mm::Mat44 &matrix, f32 radius, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCIRCLE_MAT(matrix, radius, division);
    return calcCurrentBuf(sizeof(DRCIRCLE_MAT));
  }
  return false;
}

bool CacheDraw::renderAxis(f32 length) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRAXIS(length);
    return calcCurrentBuf(sizeof(DRAXIS));
  }
  return false;
}

bool CacheDraw::renderRealSphereFill(f32 radius, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSPHERE_REAL_FILL(radius, division);
    return calcCurrentBuf(sizeof(DRSPHERE_REAL_FILL));
  }
  return false;
}

bool CacheDraw::renderRealSphere(f32 radius, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRSPHERE_REAL(radius, division);
    return calcCurrentBuf(sizeof(DRSPHERE_REAL));
  }
  return false;
}

bool CacheDraw::renderConeFill(f32 radius, f32 height, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCONE_FILL(radius, height, division);
    return calcCurrentBuf(sizeof(DRCONE_FILL));
  }
  return false;
}

bool CacheDraw::renderCone(f32 radius, f32 height, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCONE(radius, height, division);
    return calcCurrentBuf(sizeof(DRCONE));
  }
  return false;
}

bool CacheDraw::renderCylinderFill(f32 radius, f32 height, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCYLINDER_FILL(radius, height, division);
    return calcCurrentBuf(sizeof(DRCYLINDER_FILL));
  }
  return false;
}

bool CacheDraw::renderCylinder(f32 radius, f32 height, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCYLINDER(radius, height, division);
    return calcCurrentBuf(sizeof(DRCYLINDER));
  }
  return false;
}

bool CacheDraw::renderCapsuleFill(f32 radius, f32 height, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCAPSULE_FILL(radius, height, division);
    return calcCurrentBuf(sizeof(DRCAPSULE_FILL));
  }
  return false;
}

bool CacheDraw::renderCapsule(f32 radius, f32 height, u32 division) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCAPSULE(radius, height, division);
    return calcCurrentBuf(sizeof(DRCAPSULE));
  }
  return false;
}

bool CacheDraw::renderOBB(const mm::Obb &obb) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DROBB(obb);
    return calcCurrentBuf(sizeof(DROBB));
  }
  return false;
}

bool CacheDraw::renderCamera() {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRCAMERA();
    return calcCurrentBuf(sizeof(DRCAMERA));
  }
  return false;
}

bool CacheDraw::renderLine(const mm::Pnt<int> &start, const mm::Pnt<int> &end) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DRLINE_PNT(start, end);
    return calcCurrentBuf(sizeof(DRLINE_PNT));
  }
  return false;
}

bool CacheDraw::setLineWidth(u32 width) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DLINE_WIDTH(width);
    return calcCurrentBuf(sizeof(DLINE_WIDTH));
  }
  return false;
}

bool CacheDraw::setAlphaBlend(bool isEnable) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DALPHA_BLEND(isEnable);
    return calcCurrentBuf(sizeof(DALPHA_BLEND));
  }
  return false;
}

bool CacheDraw::begin(u32 primitive, u32 count) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DBEGIN(primitive, count);
    return calcCurrentBuf(sizeof(DBEGIN));
  }
  return false;
}

bool CacheDraw::end() {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DEND();
    return calcCurrentBuf(sizeof(DEND));
  }
  return false;
}

bool CacheDraw::fontColor(const mm::Col4 &color) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_COL(color);
    return calcCurrentBuf(sizeof(DFONT_COL));
  }
  return false;
}

bool CacheDraw::fontBack(const mm::Col4 &color) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_BACKCOL(color);
    return calcCurrentBuf(sizeof(DFONT_BACKCOL));
  }
  return false;
}

bool CacheDraw::fontShadow(bool isEnable) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_SHADOW(isEnable);
    return calcCurrentBuf(sizeof(DFONT_SHADOW));
  }
  return false;
}

bool CacheDraw::fontFlush(bool isEnable) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    new (getBuf(false)->unknown08) DFONT_FLUSH(isEnable);
    return calcCurrentBuf(sizeof(DFONT_FLUSH));
  }
  return false;
}

bool CacheDraw::font(s16 x, s16 y, const char *text) {
  CSNC lock(*unknown6060);
  if (DebDraw::isNotRender()) {
    unknown003 *buf = getBuf(false);
    size_t length = strlen(text);
    size_t size;
    if (length < 32) {
      new (buf->unknown08) DFONT32(x, y, text);
      size = sizeof(DFONT32);
    } else if (length < 64) {
      new (buf->unknown08) DFONT64(x, y, text);
      size = sizeof(DFONT64);
    } else if (length < 128) {
      new (buf->unknown08) DFONT128(x, y, text);
      size = sizeof(DFONT128);
    } else {
      new (buf->unknown08) DFONT256(x, y, text);
      size = sizeof(DFONT256);
    }
    return calcCurrentBuf(size);
  }
  return false;
}

void CacheDraw::DMAT::flush(DebDraw *draw) { draw->setMatrix(unknown10); }

void CacheDraw::DCLEAR::flush(DebDraw *draw) { draw->clear(); }

void CacheDraw::DEND::flush(DebDraw *draw) { draw->end(); }

void CacheDraw::DORTHO::flush(DebDraw *draw) { draw->setOrtho(); }

void CacheDraw::DBEGIN::flush(DebDraw *draw) { draw->begin(unknown0c, unknown10); }

void CacheDraw::DADDV3_1::flush(DebDraw *draw) { draw->add(unknown0c); }

void CacheDraw::DPERS::flush(DebDraw *draw) { draw->setPerspective(unknown4c, unknown50, unknown54, unknown0c, &unknown58); }

void CacheDraw::DRAXIS::flush(DebDraw *draw) { draw->renderAxis(unknown0c); }

void CacheDraw::DRCAMERA::flush(DebDraw *draw) { draw->renderCamera(); }

void CacheDraw::DROBB::flush(DebDraw *draw) { draw->renderOBB(unknown10); }

void CacheDraw::DRRECT::flush(DebDraw *draw) { draw->renderRect(unknown0c); }

void CacheDraw::DRRECT_FILL::flush(DebDraw *draw) { draw->renderRectFill(unknown0c); }

void CacheDraw::DRGRID::flush(DebDraw *draw) { draw->renderGrid(unknown0c, unknown10); }

void CacheDraw::DROVAL::flush(DebDraw *draw) { draw->renderOval(unknown0c, unknown10); }

void CacheDraw::DRSQUARE::flush(DebDraw *draw) { draw->renderSquare(unknown0c, unknown10); }

void CacheDraw::DRSQUARE_FILL::flush(DebDraw *draw) { draw->renderSquareFill(unknown0c, unknown10); }

void CacheDraw::DRCAPSULE::flush(DebDraw *draw) { draw->renderCapsule(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCAPSULE_FILL::flush(DebDraw *draw) { draw->renderCapsuleFill(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCONE::flush(DebDraw *draw) { draw->renderCone(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCONE_FILL::flush(DebDraw *draw) { draw->renderConeFill(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCYLINDER::flush(DebDraw *draw) { draw->renderCylinder(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCYLINDER_FILL::flush(DebDraw *draw) { draw->renderCylinderFill(unknown0c, unknown10, unknown14); }

void CacheDraw::DRCIRCLE_MAT::flush(DebDraw *draw) { draw->renderCircle(unknown0c, unknown4c, unknown50); }

void CacheDraw::DRSPHERE_REAL::flush(DebDraw *draw) { draw->renderRealSphere(unknown0c, unknown10); }

void CacheDraw::DRSPHERE_REAL_FILL::flush(DebDraw *draw) { draw->renderRealSphereFill(unknown0c, unknown10); }

void CacheDraw::DTEX::flush(DebDraw *draw) { draw->setTex(unknown10); }

void CacheDraw::DDOUBLESIDE::flush(DebDraw *draw) { draw->setDoubleSide(unknown0c); }

void CacheDraw::DZCOMP::flush(DebDraw *draw) { draw->setZComp(unknown0c); }

void CacheDraw::DZWRITE::flush(DebDraw *draw) { draw->setZWrite(unknown0c); }

void CacheDraw::DALPHA::flush(DebDraw *draw) { draw->setAlpha(unknown0c); }

void CacheDraw::DLINE_WIDTH::flush(DebDraw *draw) { draw->setLineWidth(unknown0c); }

void CacheDraw::DALPHA_BLEND::flush(DebDraw *draw) { draw->setAlphaBlend(unknown0c); }

void CacheDraw::DRTRI2D_FILL::flush(DebDraw *draw) {
  draw->renderTriangleFill(mm::Vec3(unknown0c.x, unknown0c.y, 0.0f), mm::Vec3(unknown14.x, unknown14.y, 0.0f), mm::Vec3(unknown1c.x, unknown1c.y, 0.0f));
}

void CacheDraw::DRLINE_PNT::flush(DebDraw *draw) { draw->renderLine(unknown0c, unknown14); }

void CacheDraw::DFONT32::flush(DebDraw *draw) { WinView::getView(false)->font(unknown30, unknown32, unknown0c.c_str()); }

void CacheDraw::DFONT64::flush(DebDraw *draw) { WinView::getView(false)->font(unknown50, unknown52, unknown0c.c_str()); }

void CacheDraw::DFONT128::flush(DebDraw *draw) { WinView::getView(false)->font(unknown90, unknown92, unknown0c.c_str()); }

void CacheDraw::DFONT256::flush(DebDraw *draw) { WinView::getView(false)->font(unknown110, unknown112, unknown0c.c_str()); }

void CacheDraw::DFONT_COL::flush(DebDraw *draw) { WinView::getView(false)->fontColor(unknown0c); }

void CacheDraw::DFONT_BACKCOL::flush(DebDraw *draw) { WinView::getView(false)->fontBack(unknown0c); }

void CacheDraw::DFONT_SHADOW::flush(DebDraw *draw) { WinView::getView(false)->fontShadow(unknown0c); }

void CacheDraw::DFONT_FLUSH::flush(DebDraw *draw) { WinView::getView(false)->fontFlush(unknown0c); }

void CacheDraw::DFONT_SCALE::flush(DebDraw *draw) { WinView::getView(false)->fontScale(unknown0c, unknown10); }

} // namespace ml
