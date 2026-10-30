#include "ml/cache_draw.h"

namespace ml {

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

} // namespace ml
