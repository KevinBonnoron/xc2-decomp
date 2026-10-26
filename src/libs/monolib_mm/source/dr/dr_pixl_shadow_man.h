#pragma once

namespace ml {
class DrLightObj;
class DrPixlShadowObj;

class DrPixlShadowMan {
public:
  void releaseShadow(DrPixlShadowObj *shadow);
  DrPixlShadowObj *createDirCacheShadow(DrLightObj *light, int index);
};

} // namespace ml
