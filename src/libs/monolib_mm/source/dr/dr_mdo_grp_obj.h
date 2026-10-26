#pragma once
#include "types.h"

namespace ml {

class DrMdlObj;

class DrMdoGrpObj {
public:
  void resourceInit();
  DrMdlObj *createInstantMdl(const void *data, const char *name, u32 index);
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
