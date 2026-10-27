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

} // namespace ml
