#pragma once

namespace ml {

class DrLightObjPnt;
class DrLightObjSpt;

class DrLightMan {
public:
  void render();
  void renderDir();
  void renderPnt();
  void renderSpt();
  void renderDebugDir();
  void releaseFastLight();
  DrLightObjPnt *createInstantPntLight();
  DrLightObjSpt *createInstantSptLight();
  void releaseInstantPntLight(DrLightObjPnt *light);
  void releaseInstantSptLight(DrLightObjSpt *light);
};

} // namespace ml
