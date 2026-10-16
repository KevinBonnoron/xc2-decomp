#pragma once

namespace ml {

class DrMdoGrpObj {
public:
  void callNomSetupRender();
  void callZSortNomZpreePassRender();
  void callZSortThicknessRenderFirst();
  void callZSortThicknessRenderSecond();
  void callZSortNomRender();
  void callZSortGBuffRender();
  void callZSortLightPrePassRender();
  void callZSortNomAlphaRender();
  void callZSortNomSpAlphaRender();
  void callZSortNomRefractionRender();
};

} // namespace ml
