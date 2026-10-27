#include "dr/dr_pixl_post_obj_unbranch_to_depth.h"

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

DrPixlPostObjUnbranchToDepth::DrPixlPostObjUnbranchToDepth(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {}

DrPixlPostObjUnbranchToDepth::~DrPixlPostObjUnbranchToDepth() {}

void DrPixlPostObjUnbranchToDepth::debugRender() {}

void DrPixlPostObjUnbranchToDepth::resetColorBuff() {}

void DrPixlPostObjUnbranchToDepth::update() {}

} // namespace ml
