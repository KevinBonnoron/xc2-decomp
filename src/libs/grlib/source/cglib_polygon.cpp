#include "grlib/cglib_polygon.h"

#include "grlib/cglib_system_context.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibPolygon::setCullingOff() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->m_cmdBuf, &context->m_cullingOff);
}

void CGLibPolygon::setCullingFront() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->m_cmdBuf, &context->m_cullingFront);
}

void CGLibPolygon::setCullingBack() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->m_cmdBuf, &context->m_cullingBack);
}

void CGLibPolygon::setCullingDispOff() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->m_cmdBuf, &context->m_cullingDispOff);
}

void CGLibPolygon::setPointMode() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->m_cmdBuf, &context->m_pointMode);
}

void CGLibPolygon::setLineMode() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->m_cmdBuf, &context->m_lineMode);
}

void CGLibPolygon::setTraiangle() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->m_cmdBuf, &context->m_triangle);
}

void CGLibPolygon::setLineWidth(f32 width) { nvnCommandBufferSetLineWidth(context::CGLibSystemContext::get()->m_cmdBuf, width); }

void CGLibPolygon::setRasterizer(u8 isDiscard) { nvnCommandBufferSetRasterizerDiscard(context::CGLibSystemContext::get()->m_cmdBuf, isDiscard); }

void CGLibPolygon::setConservativeRaster(u8 isEnable) {
  nvnCommandBufferSetConservativeRasterEnable(context::CGLibSystemContext::get()->m_cmdBuf, isEnable);
}

void CGLibPolygon::setConservativeDilate(f32 dilate) {
  nvnCommandBufferSetConservativeRasterDilate(context::CGLibSystemContext::get()->m_cmdBuf, dilate);
}

void CGLibPolygon::setConservativeSubpixelBias(int xBits, int yBits) {
  nvnCommandBufferSetSubpixelPrecisionBias(context::CGLibSystemContext::get()->m_cmdBuf, xBits, yBits);
}

} // namespace grlib
