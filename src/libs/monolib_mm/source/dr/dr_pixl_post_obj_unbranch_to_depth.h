#pragma once
#include "dr/dr_pixl_post_obj.h"

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjUnbranchToDepth : public DrPixlPostObj {
public:
  DrPixlPostObjUnbranchToDepth(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjUnbranchToDepth();
  void debugRender();
  void resetColorBuff();
  void update();
};

} // namespace ml
