#include "dr/dr_pixl_post_obj_rain_drop.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"

namespace ml {

void DrPixlPostObjRainDrop::resetColorBuff() {}

void DrPixlPostObjRainDrop::releaseColorBuff() {}

void DrPixlPostObjRainDrop::requestRebuildDepth() { unknown18 |= 2; }

void DrPixlPostObjRainDrop::requestUseLoadedDepth() { unknown18 &= ~4; }

void DrPixlPostObjRainDrop::requestSaveDepth(const char *) {}

void DrPixlPostObjRainDrop::update() { unknown00->unknown120[unknown00->unknown1c98]->getRainDropOn(); }

} // namespace ml
