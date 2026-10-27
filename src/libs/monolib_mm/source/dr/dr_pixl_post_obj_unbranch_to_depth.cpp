#include "dr/dr_pixl_post_obj_unbranch_to_depth.h"

#include "dr/dr_man.h"

namespace ml {
class DrPixlMan;
class DrPixlPostMan;

DrPixlPostObjUnbranchToDepth::DrPixlPostObjUnbranchToDepth(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {}

DrPixlPostObjUnbranchToDepth::~DrPixlPostObjUnbranchToDepth() {}

void DrPixlPostObjUnbranchToDepth::debugRender() {}

void DrPixlPostObjUnbranchToDepth::resetColorBuff() {}

void DrPixlPostObjUnbranchToDepth::update() {}

void DrPixlPostObjUnbranchToDepth::render() {
  renderFull();
  if (unknown00->unknown1e10) {
    renderQuater();
  }
}

} // namespace ml
