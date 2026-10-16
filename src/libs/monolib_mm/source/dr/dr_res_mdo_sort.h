#pragma once
#include "dr/dr_mdo_zsort.h"

namespace ml {
class DrMdoCtlMpf;
class DrMdoCtlNom;
class DrMdoCtlPos;
class DrMdoGrpObj;

class DrResMdoSortNom : public DrMdoZSortObj {
public:
  DrResMdoSortNom(DrMdoCtlNom *owner);
  void SetupRender() override;
  void ZPrepassRender() override;
  void ThicknessRenderFirst() override;
  void ThicknessRenderSecond() override;
  void render() override;
  void GBuffRender() override;
  void lightPrePassRender() override;
  void alphaRender() override;
  void spAlphaRender() override;
  void refractionRender() override;
};

class DrResMdoSortNomLastApha : public DrMdoZSortObj {
public:
  DrResMdoSortNomLastApha(DrMdoCtlNom *owner);
  void alphaRender() override;
};

class DrResMdoSortNomFastApha : public DrMdoZSortObj {
public:
  DrResMdoSortNomFastApha(DrMdoCtlNom *owner);
  void alphaRender() override;
};

class DrResMdoSortNomCldBackApha : public DrMdoZSortObj {
public:
  DrResMdoSortNomCldBackApha(DrMdoCtlNom *owner);
  void alphaRender() override;
};

class DrResMdoSortPos : public DrMdoZSortObj {
public:
  DrResMdoSortPos(DrMdoCtlPos *owner);
  ~DrResMdoSortPos() override;
  void ZPrepassRender() override;
  void ThicknessRenderFirst() override;
  void ThicknessRenderSecond() override;
  void render() override;
  void GBuffRender() override;
  void alphaRender() override;
  void spAlphaRender() override;
  void lightPrePassRender() override;
  void refractionRender() override;
};

class DrResMdoSortMpf : public DrMdoZSortObj {
public:
  DrResMdoSortMpf(DrMdoCtlMpf *owner);
  ~DrResMdoSortMpf() override;
  void ZPrepassRender() override;
  void render() override;
};

class DrResMdoSortGrp : public DrMdoZSortObj {
public:
  DrResMdoSortGrp(DrMdoGrpObj *owner);
  void SetupRender() override;
  void ZPrepassRender() override;
  void ThicknessRenderFirst() override;
  void ThicknessRenderSecond() override;
  void render() override;
  void GBuffRender() override;
  void lightPrePassRender() override;
  void alphaRender() override;
  void spAlphaRender() override;
  void refractionRender() override;
};

class DrResMdoSortSeamAll : public DrMdoZSortObj {
public:
  DrResMdoSortSeamAll(void *owner);
  ~DrResMdoSortSeamAll() override;
  void ZPrepassRender() override;
  void ThicknessRenderFirst() override;
  void ThicknessRenderSecond() override;
  void render() override;
  void GBuffRender() override;
  void lightPrePassRender() override;
  void alphaRender() override;
  void spAlphaRender() override;
  void refractionRender() override;
};

class DrResMdoSortSeamEnvMap : public DrMdoZSortObj {
public:
  DrResMdoSortSeamEnvMap(void *owner);
  ~DrResMdoSortSeamEnvMap() override;
  void render() override;
  void GBuffRender() override;
  void lightPrePassRender() override;
  void alphaRender() override;
  void spAlphaRender() override;
  void refractionRender() override;
};

class DrResMdoSortCloud : public DrMdoZSortObj {
public:
  DrResMdoSortCloud(void *owner);
  ~DrResMdoSortCloud() override;
  void alphaRender() override;
};

} // namespace ml
