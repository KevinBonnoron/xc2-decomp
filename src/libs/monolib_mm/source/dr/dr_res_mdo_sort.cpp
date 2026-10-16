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

void DrResMdoSortNom::SetupRender() { static_cast<DrMdoCtlNom *>(m_owner)->callNomSetupRender(); }

void DrResMdoSortNom::ZPrepassRender() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortNomZpreePassRender(); }

void DrResMdoSortNom::ThicknessRenderFirst() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortThicknessRenderFirst(); }

void DrResMdoSortNom::ThicknessRenderSecond() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortThicknessRenderSecond(); }

void DrResMdoSortNom::render() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortNomRender(); }

void DrResMdoSortNom::GBuffRender() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortGBuffRender(); }

void DrResMdoSortNom::lightPrePassRender() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortLightPrePassRender(); }

void DrResMdoSortNom::alphaRender() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortNomAlphaRender(); }

void DrResMdoSortNom::spAlphaRender() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortNomSpAlphaRender(); }

void DrResMdoSortNom::refractionRender() { static_cast<DrMdoCtlNom *>(m_owner)->callZSortNomRefractionRender(); }

DrResMdoSortNomLastApha::DrResMdoSortNomLastApha(DrMdoCtlNom *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomLastApha::alphaRender() { static_cast<DrMdoCtlNom *>(m_owner)->callLastAlphaNomRender(); }

DrResMdoSortNomFastApha::DrResMdoSortNomFastApha(DrMdoCtlNom *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomFastApha::alphaRender() { static_cast<DrMdoCtlNom *>(m_owner)->callFastAlphaNomRender(); }

DrResMdoSortNomCldBackApha::DrResMdoSortNomCldBackApha(DrMdoCtlNom *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortNomCldBackApha::alphaRender() { static_cast<DrMdoCtlNom *>(m_owner)->callCldBackAlphaNomRender(); }

DrResMdoSortPos::DrResMdoSortPos(DrMdoCtlPos *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortPos::~DrResMdoSortPos() {}

void DrResMdoSortPos::ZPrepassRender() { static_cast<DrMdoCtlPos *>(m_owner)->callZpreePassRenderPosAll(); }

void DrResMdoSortPos::ThicknessRenderFirst() { static_cast<DrMdoCtlPos *>(m_owner)->callThicknessRenderFirstPosAll(); }

void DrResMdoSortPos::ThicknessRenderSecond() { static_cast<DrMdoCtlPos *>(m_owner)->callThicknessRenderSecondPosAll(); }

void DrResMdoSortPos::render() { static_cast<DrMdoCtlPos *>(m_owner)->callRenderPosAll(); }

void DrResMdoSortPos::GBuffRender() { static_cast<DrMdoCtlPos *>(m_owner)->callGBuffRenderPosAll(); }

void DrResMdoSortPos::alphaRender() { static_cast<DrMdoCtlPos *>(m_owner)->callAlphaRenderPosAll(); }

void DrResMdoSortPos::spAlphaRender() { static_cast<DrMdoCtlPos *>(m_owner)->callSpAlphaRenderPosAll(); }

void DrResMdoSortPos::lightPrePassRender() { static_cast<DrMdoCtlPos *>(m_owner)->callLightPrePassRenderPosAll(); }

void DrResMdoSortPos::refractionRender() { static_cast<DrMdoCtlPos *>(m_owner)->callRefractionRenderPosAll(); }

DrResMdoSortMpf::DrResMdoSortMpf(DrMdoCtlMpf *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortMpf::~DrResMdoSortMpf() {}

void DrResMdoSortMpf::ZPrepassRender() { static_cast<DrMdoCtlMpf *>(m_owner)->callZPrepassRender(); }

void DrResMdoSortMpf::render() { static_cast<DrMdoCtlMpf *>(m_owner)->callRenderMpf(); }

DrResMdoSortGrp::DrResMdoSortGrp(DrMdoGrpObj *owner) : DrMdoZSortObj(owner) {}

void DrResMdoSortGrp::SetupRender() { static_cast<DrMdoGrpObj *>(m_owner)->callNomSetupRender(); }

void DrResMdoSortGrp::ZPrepassRender() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortNomZpreePassRender(); }

void DrResMdoSortGrp::ThicknessRenderFirst() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortThicknessRenderFirst(); }

void DrResMdoSortGrp::ThicknessRenderSecond() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortThicknessRenderSecond(); }

void DrResMdoSortGrp::render() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortNomRender(); }

void DrResMdoSortGrp::GBuffRender() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortGBuffRender(); }

void DrResMdoSortGrp::lightPrePassRender() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortLightPrePassRender(); }

void DrResMdoSortGrp::alphaRender() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortNomAlphaRender(); }

void DrResMdoSortGrp::spAlphaRender() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortNomSpAlphaRender(); }

void DrResMdoSortGrp::refractionRender() { static_cast<DrMdoGrpObj *>(m_owner)->callZSortNomRefractionRender(); }

DrResMdoSortSeamAll::DrResMdoSortSeamAll(void *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortSeamAll::~DrResMdoSortSeamAll() {}

void DrResMdoSortSeamAll::ZPrepassRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callZPrePassSeamAll(); }

void DrResMdoSortSeamAll::ThicknessRenderFirst() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callThicknessFirstSeamAll(); }

void DrResMdoSortSeamAll::ThicknessRenderSecond() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callThicknessSecondSeamAll(); }

void DrResMdoSortSeamAll::render() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callRenderSeamAll(); }

void DrResMdoSortSeamAll::GBuffRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callGBuffRenderSeamAll(); }

void DrResMdoSortSeamAll::lightPrePassRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callLightPrePassRenderSeamAll(); }

void DrResMdoSortSeamAll::alphaRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callAlphaRenderSeamAll(); }

void DrResMdoSortSeamAll::spAlphaRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callSpAlphaRenderSeamAll(); }

void DrResMdoSortSeamAll::refractionRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callRefractionRenderSeamAll(); }

DrResMdoSortSeamEnvMap::DrResMdoSortSeamEnvMap(void *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortSeamEnvMap::~DrResMdoSortSeamEnvMap() {}

void DrResMdoSortSeamEnvMap::render() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::GBuffRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callGBuffRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::lightPrePassRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callLightPrePassRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::alphaRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callAlphaRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::spAlphaRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callSpAlphaRenderSeamEnvMap(); }

void DrResMdoSortSeamEnvMap::refractionRender() { static_cast<DrMdoCtlSeamAll *>(m_owner)->callRefractionRenderSeamEnvMap(); }

DrResMdoSortCloud::DrResMdoSortCloud(void *owner) : DrMdoZSortObj(owner) {}

DrResMdoSortCloud::~DrResMdoSortCloud() {}

void DrResMdoSortCloud::alphaRender() {
  cloud::CloudMan *cloudMan = static_cast<cloud::CloudMan *>(m_owner);
  DrMan *drMan = DrMan::getIns();
  cloudMan->alphaRender(&drMan->drawWorkInfos[drMan->viewIndex]);
}

} // namespace ml
