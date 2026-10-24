#include "grlib/cglib_polygon.h"

#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_system_context.h"
#include "nvn/nvn.h"

namespace grlib {

void CGLibPolygon::setCullingOff() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->unknown1070.unknown00, &context->unknown1070.unknown30);
}

void CGLibPolygon::setCullingFront() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->unknown1070.unknown00, &context->unknown1070.unknown34);
}

void CGLibPolygon::setCullingBack() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->unknown1070.unknown00, &context->unknown1070.unknown38);
}

void CGLibPolygon::setCullingDispOff() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->unknown1070.unknown00, &context->unknown1070.unknown3c);
}

void CGLibPolygon::setPointMode() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->unknown1070.unknown00, &context->unknown1070.unknown40);
}

void CGLibPolygon::setLineMode() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->unknown1070.unknown00, &context->unknown1070.unknown44);
}

void CGLibPolygon::setTraiangle() {
  context::CGLibSystemContext *context = context::CGLibSystemContext::get();
  nvnCommandBufferBindPolygonState(context->unknown1070.unknown00, &context->unknown1070.unknown48);
}

void CGLibPolygon::setLineWidth(f32 width) { nvnCommandBufferSetLineWidth(context::CGLibSystemContext::get()->unknown1070.unknown00, width); }

void CGLibPolygon::setRasterizer(u8 isDiscard) { nvnCommandBufferSetRasterizerDiscard(context::CGLibSystemContext::get()->unknown1070.unknown00, isDiscard); }

void CGLibPolygon::setConservativeRaster(u8 isEnable) { nvnCommandBufferSetConservativeRasterEnable(context::CGLibSystemContext::get()->unknown1070.unknown00, isEnable); }

void CGLibPolygon::setConservativeDilate(f32 dilate) { nvnCommandBufferSetConservativeRasterDilate(context::CGLibSystemContext::get()->unknown1070.unknown00, dilate); }

void CGLibPolygon::setConservativeSubpixelBias(int xBits, int yBits) { nvnCommandBufferSetSubpixelPrecisionBias(context::CGLibSystemContext::get()->unknown1070.unknown00, xBits, yBits); }

} // namespace grlib
