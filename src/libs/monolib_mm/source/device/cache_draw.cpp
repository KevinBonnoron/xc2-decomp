#include "ml/cache_draw.h"

#include "ml/critical_section.h"
#include "ml/win_view.h"
#include "ml/work_cpu.h"
#include "mtl/mem_manager.h"

namespace ml {

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
