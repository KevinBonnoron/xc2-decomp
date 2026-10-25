#pragma once

namespace ml {

class DrShdLgtGlobalIBL {
public:
  void update(int viewNum);
  void resetColorBuff(int index);
  void delViewInfo(int viewNum);
};

} // namespace ml
