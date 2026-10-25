#include "dr/dr_draw_callback.h"

namespace ml {

void IDrDrawCallback::begin() {}

void IDrDrawCallback::end() {}

void IDrDrawCallback::apply(const IDrDrawWorkInfo *info) {}

void IDrDrawCallback::opacityRender(const IDrDrawWorkInfo *info) {}

void IDrDrawCallback::alphaRender(const IDrDrawWorkInfo *info) {}

void IDrDrawCallback::lastRender(const IDrDrawWorkInfo *info) {}

void IDrDrawCallback::blurRender(const IDrDrawWorkInfo *info) {}

void IDrDrawCallback::finalRender(const IDrDrawWorkInfo *info) {}

} // namespace ml
