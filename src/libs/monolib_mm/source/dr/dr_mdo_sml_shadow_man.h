#pragma once

namespace ml {
class DrMdoSmlShadowObj;

class DrMdoSmlShadowMan {
public:
  void changeViewNum(DrMdoSmlShadowObj *shadow, int viewNum);
  void shadowRender();
};

} // namespace ml
