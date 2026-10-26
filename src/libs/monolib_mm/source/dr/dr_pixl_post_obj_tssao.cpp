#include "dr/dr_pixl_post_obj_tssao.h"

#include "dr/dr_pixl_post_man.h"

namespace ml {

void DrPixlPostObjTSSAO::passUpScaling() { passUpScaleToMiddle(); }

void DrPixlPostObjTSSAO::update() { unknown10->setDownDepth(); }

} // namespace ml
