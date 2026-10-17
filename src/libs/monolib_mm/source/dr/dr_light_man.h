#pragma once

namespace ml {

class DrLightObjPnt;
class DrLightObjSpt;

class DrLightMan {
public:
  void releaseFastLight();
  DrLightObjPnt *createInstantPntLight();
  DrLightObjSpt *createInstantSptLight();
  void releaseInstantPntLight(DrLightObjPnt *light);
  void releaseInstantSptLight(DrLightObjSpt *light);
};

} // namespace ml
