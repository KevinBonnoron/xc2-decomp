#include "dr/dr_res_mdo_sort.h"

#include "cloud/cloud_man.h"
#include "dr/dr_draw_work_info.h"
#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_mpf.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_ctl_pos.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_grp_obj.h"

namespace ml {

DrResMdoSortNom::DrResMdoSortNom(DrMdoCtlNom *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNom::SetupRender() { static_cast<DrMdoCtlNom *>(unknown18)->callNomSetupRender(); }

void DrResMdoSortNom::ZPrepassRender() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortNomZpreePassRender(); }

void DrResMdoSortNom::ThicknessRenderFirst() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortThicknessRenderFirst(); }

void DrResMdoSortNom::ThicknessRenderSecond() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortThicknessRenderSecond(); }

void DrResMdoSortNom::render() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortNomRender(); }

void DrResMdoSortNom::GBuffRender() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortGBuffRender(); }

void DrResMdoSortNom::lightPrePassRender() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortLightPrePassRender(); }

void DrResMdoSortNom::alphaRender() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortNomAlphaRender(); }

void DrResMdoSortNom::spAlphaRender() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortNomSpAlphaRender(); }

void DrResMdoSortNom::refractionRender() { static_cast<DrMdoCtlNom *>(unknown18)->callZSortNomRefractionRender(); }

DrResMdoSortNomLastApha::DrResMdoSortNomLastApha(DrMdoCtlNom *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomLastApha::alphaRender() { static_cast<DrMdoCtlNom *>(unknown18)->callLastAlphaNomRender(); }

DrResMdoSortNomFastApha::DrResMdoSortNomFastApha(DrMdoCtlNom *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomFastApha::alphaRender() { static_cast<DrMdoCtlNom *>(unknown18)->callFastAlphaNomRender(); }

DrResMdoSortNomCldBackApha::DrResMdoSortNomCldBackApha(DrMdoCtlNom *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomCldBackApha::alphaRender() { static_cast<DrMdoCtlNom *>(unknown18)->callCldBackAlphaNomRender(); }

DrResMdoSortPos::DrResMdoSortPos(DrMdoCtlPos *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortPos::~DrResMdoSortPos() {}

void DrResMdoSortPos::ZPrepassRender() { static_cast<DrMdoCtlPos *>(unknown18)->callZpreePassRenderPosAll(); }

void DrResMdoSortPos::ThicknessRenderFirst() { static_cast<DrMdoCtlPos *>(unknown18)->callThicknessRenderFirstPosAll(); }

void DrResMdoSortPos::ThicknessRenderSecond() { static_cast<DrMdoCtlPos *>(unknown18)->callThicknessRenderSecondPosAll(); }

void DrResMdoSortPos::render() { static_cast<DrMdoCtlPos *>(unknown18)->callRenderPosAll(); }

void DrResMdoSortPos::GBuffRender() { static_cast<DrMdoCtlPos *>(unknown18)->callGBuffRenderPosAll(); }

void DrResMdoSortPos::alphaRender() { static_cast<DrMdoCtlPos *>(unknown18)->callAlphaRenderPosAll(); }

void DrResMdoSortPos::spAlphaRender() { static_cast<DrMdoCtlPos *>(unknown18)->callSpAlphaRenderPosAll(); }

void DrResMdoSortPos::lightPrePassRender() { static_cast<DrMdoCtlPos *>(unknown18)->callLightPrePassRenderPosAll(); }

void DrResMdoSortPos::refractionRender() { static_cast<DrMdoCtlPos *>(unknown18)->callRefractionRenderPosAll(); }

DrResMdoSortMpf::DrResMdoSortMpf(DrMdoCtlMpf *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortMpf::~DrResMdoSortMpf() {}

void DrResMdoSortMpf::ZPrepassRender() { static_cast<DrMdoCtlMpf *>(unknown18)->callZPrepassRender(); }

void DrResMdoSortMpf::render() { static_cast<DrMdoCtlMpf *>(unknown18)->callRenderMpf(); }

DrResMdoSortGrp::DrResMdoSortGrp(DrMdoGrpObj *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortGrp::SetupRender() { static_cast<DrMdoGrpObj *>(unknown18)->callNomSetupRender(); }

void DrResMdoSortGrp::ZPrepassRender() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortNomZpreePassRender(); }

void DrResMdoSortGrp::ThicknessRenderFirst() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortThicknessRenderFirst(); }

void DrResMdoSortGrp::ThicknessRenderSecond() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortThicknessRenderSecond(); }

void DrResMdoSortGrp::render() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortNomRender(); }

void DrResMdoSortGrp::GBuffRender() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortGBuffRender(); }

void DrResMdoSortGrp::lightPrePassRender() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortLightPrePassRender(); }

void DrResMdoSortGrp::alphaRender() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortNomAlphaRender(); }

void DrResMdoSortGrp::spAlphaRender() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortNomSpAlphaRender(); }

void DrResMdoSortGrp::refractionRender() { static_cast<DrMdoGrpObj *>(unknown18)->callZSortNomRefractionRender(); }

DrResMdoSortSeamAll::DrResMdoSortSeamAll(void *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortSeamAll::~DrResMdoSortSeamAll() {}

void DrResMdoSortSeamAll::ZPrepassRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callZPrePassSeamAll(); }

void DrResMdoSortSeamAll::ThicknessRenderFirst() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callThicknessFirstSeamAll(); }

void DrResMdoSortSeamAll::ThicknessRenderSecond() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callThicknessSecondSeamAll(); }

void DrResMdoSortSeamAll::render() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callRenderSeamAll(); }

void DrResMdoSortSeamAll::GBuffRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callGBuffRenderSeamAll(); }

void DrResMdoSortSeamAll::lightPrePassRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callLightPrePassRenderSeamAll(); }

void DrResMdoSortSeamAll::alphaRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callAlphaRenderSeamAll(); }

void DrResMdoSortSeamAll::spAlphaRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callSpAlphaRenderSeamAll(); }

void DrResMdoSortSeamAll::refractionRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callRefractionRenderSeamAll(); }

DrResMdoSortSeamEnvMap::DrResMdoSortSeamEnvMap(void *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortSeamEnvMap::~DrResMdoSortSeamEnvMap() {}

void DrResMdoSortSeamEnvMap::render() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::GBuffRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callGBuffRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::lightPrePassRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callLightPrePassRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::alphaRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callAlphaRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::spAlphaRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callSpAlphaRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::refractionRender() { static_cast<DrMdoCtlSeamAll *>(unknown18)->callRefractionRenderSeamEnvMap(); }

DrResMdoSortCloud::DrResMdoSortCloud(void *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortCloud::~DrResMdoSortCloud() {}

void DrResMdoSortCloud::alphaRender() {
  cloud::CloudMan *cloudMan = static_cast<cloud::CloudMan *>(unknown18);
  DrMan *drMan = DrMan::getIns();
  cloudMan->alphaRender(&drMan->unknown660[drMan->unknown1c98]);
}

} // namespace ml
