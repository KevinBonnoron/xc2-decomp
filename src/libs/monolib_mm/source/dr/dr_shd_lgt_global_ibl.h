#pragma once

namespace ml {

class DrLightObjGlobalIBL;
class DrShdLgtMan;

namespace _dr_shd_lgt_glb_ibl {
bool CompareByPriority(const DrLightObjGlobalIBL *a, const DrLightObjGlobalIBL *b);
} // namespace _dr_shd_lgt_glb_ibl

class DrShdLgtGlobalIBL {
public:
  void update(int viewNum);
  void render(DrShdLgtMan *man);
  void resetColorBuff(int index);
  void delViewInfo(int viewNum);
};

} // namespace ml
