#pragma once

namespace ml {

class DrShdLgtMan;

class DrShdLgtGlobalIBL {
public:
  void update(int viewNum);
  void render(DrShdLgtMan *man);
  void resetColorBuff(int index);
  void delViewInfo(int viewNum);
};

} // namespace ml
