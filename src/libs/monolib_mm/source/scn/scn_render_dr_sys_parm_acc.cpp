#include "scn/scn_render_dr_sys_parm_acc.h"

#include "cloud/cloud_man.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_irr_vol_man.h"
#include "dr/dr_irr_vol_sector.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_motion_blur.h"
#include "dr/dr_pixl_post_parm.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "scn/scn_render_dr_sys.h"

namespace mm {
struct Aabb;
} // namespace mm

namespace ml {
struct DR_CAPCUBE_PARAM;

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc() : m_drMan(nullptr), m_drPixlPostParm(nullptr), unknown10(0) {
  m_drMan = DrMan::get();
  m_drPixlPostParm = m_drMan->unknown120[unknown10];
}

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc(ScnRenderDrSys *drSys, s32 index) : m_drMan(nullptr), m_drPixlPostParm(nullptr) { setDrSys(drSys, index); }

void ScnRenderDrSysParmAcc::setDrSys(ScnRenderDrSys *drSys, s32 index) {
  m_drMan = drSys->m_drMan;
  m_drPixlPostParm = m_drMan->unknown120[index];
  unknown10 = index;
}

void ScnRenderDrSysParmAcc::setDOFOverride(bool dofOverride) { m_drPixlPostParm->setOverrideDOF(dofOverride); }

void ScnRenderDrSysParmAcc::setGlbSpd(f32 glbSpd) { m_drMan->m_glbSpd = glbSpd; }

f32 ScnRenderDrSysParmAcc::getGlbSpd() const { return m_drMan->m_glbSpd; }

void ScnRenderDrSysParmAcc::setMdlSpd(f32 mdlSpd) { m_drMan->m_mdlSpd = mdlSpd; }

f32 ScnRenderDrSysParmAcc::getMdlSpd() const { return m_drMan->m_mdlSpd; }

void ScnRenderDrSysParmAcc::setToneMap(bool toneMap) { m_drPixlPostParm->m_toneMapOn = toneMap; }

bool ScnRenderDrSysParmAcc::isToneMap() const { return m_drPixlPostParm->getToneMapOn(); }

void ScnRenderDrSysParmAcc::setToneMax(f32 toneMax) { m_drPixlPostParm->m_toneMax = toneMax; }

void ScnRenderDrSysParmAcc::setToneMin(f32 toneMin) { m_drPixlPostParm->m_toneMin = toneMin; }

void ScnRenderDrSysParmAcc::setToneRatio(f32 toneRatio) { m_drPixlPostParm->m_toneRatio = toneRatio; }

void ScnRenderDrSysParmAcc::setToneRatioLast(f32 toneRatioLast) { m_drPixlPostParm->m_toneRatioLast = toneRatioLast; }

void ScnRenderDrSysParmAcc::setOverrideToneMap(f32 overrideToneMap) { m_drPixlPostParm->setOverrideToneMap(overrideToneMap); }

void ScnRenderDrSysParmAcc::setToneBlmMax(f32 toneBlmMax) { m_drPixlPostParm->m_toneBlmMax = toneBlmMax; }

void ScnRenderDrSysParmAcc::setToneBlmMin(f32 toneBlmMin) { m_drPixlPostParm->m_toneBlmMin = toneBlmMin; }

void ScnRenderDrSysParmAcc::setToneBlmRatio(f32 toneBlmRatio) { m_drPixlPostParm->m_toneBlmRatio = toneBlmRatio; }

void ScnRenderDrSysParmAcc::setToneBlmRatioLast(f32 toneBlmRatioLast) { m_drPixlPostParm->m_toneBlmRatioLast = toneBlmRatioLast; }

void ScnRenderDrSysParmAcc::setBloom(bool bloom) { m_drPixlPostParm->m_bloomOn = bloom; }

bool ScnRenderDrSysParmAcc::isBloomOn() const { return m_drPixlPostParm->getBloomOn(); }

void ScnRenderDrSysParmAcc::setBorderBlmSub(f32 borderBlmSub) { m_drPixlPostParm->m_borderBlmSub = borderBlmSub; }

void ScnRenderDrSysParmAcc::setBorderBlmMul(f32 borderBlmMul) { m_drPixlPostParm->m_borderBlmMul = borderBlmMul; }

void ScnRenderDrSysParmAcc::setBorderBlmSecSub(f32 borderBlmSecSub) { m_drPixlPostParm->m_borderBlmSecSub = borderBlmSecSub; }

void ScnRenderDrSysParmAcc::setBorderBlmSecMul(f32 borderBlmSecMul) { m_drPixlPostParm->m_borderBlmSecMul = borderBlmSecMul; }

void ScnRenderDrSysParmAcc::setBorderBlmMax(f32 borderBlmMax) { m_drPixlPostParm->m_borderBlmMax = borderBlmMax; }

void ScnRenderDrSysParmAcc::setBlmWeight(f32 x, f32 y, f32 z) {
  f32 *blmWeight = m_drPixlPostParm->m_blmWeight;
  blmWeight[0] = x;
  blmWeight[1] = y;
  blmWeight[2] = z;
}

void ScnRenderDrSysParmAcc::setBlmStr(f32 x, f32 y, f32 z) {
  f32 *blmStr = m_drPixlPostParm->m_blmStr;
  blmStr[0] = x;
  blmStr[1] = y;
  blmStr[2] = z;
}

void ScnRenderDrSysParmAcc::setBlmGauss(f32 x, f32 y, f32 z) {
  f32 *blmGauss = m_drPixlPostParm->m_blmGauss;
  blmGauss[0] = x;
  blmGauss[1] = y;
  blmGauss[2] = z;
}

f32 ScnRenderDrSysParmAcc::getBorderBlmSub() const { return m_drPixlPostParm->m_borderBlmSub; }

f32 ScnRenderDrSysParmAcc::getBorderBlmMul() const { return m_drPixlPostParm->getBorderBlmMul(); }

f32 ScnRenderDrSysParmAcc::getBorderBlmSecSub() const { return m_drPixlPostParm->m_borderBlmSecSub; }

f32 ScnRenderDrSysParmAcc::getBorderBlmSecMul() const { return m_drPixlPostParm->m_borderBlmSecMul; }

f32 ScnRenderDrSysParmAcc::getBorderBlmMax() const { return m_drPixlPostParm->m_borderBlmMax; }

const f32 *ScnRenderDrSysParmAcc::getBlmWeight() const { return m_drPixlPostParm->m_blmWeight; }

const f32 *ScnRenderDrSysParmAcc::getBlmStr() const { return m_drPixlPostParm->m_blmStr; }

const f32 *ScnRenderDrSysParmAcc::getBlmGauss() const { return m_drPixlPostParm->m_blmGauss; }

void ScnRenderDrSysParmAcc::setLensFlare(bool lensFlare) { m_drPixlPostParm->m_lensFlare = lensFlare; }

bool ScnRenderDrSysParmAcc::isLensFlare() const { return m_drPixlPostParm->m_lensFlare; }

void ScnRenderDrSysParmAcc::setBlmLensSub(f32 blmLensSub) { m_drPixlPostParm->m_blmLensSub = blmLensSub; }

void ScnRenderDrSysParmAcc::setBlmLensMul(f32 blmLensMul) { m_drPixlPostParm->m_blmLensMul = blmLensMul; }

void ScnRenderDrSysParmAcc::setBlmLensMax(s32 blmLensMax) { m_drPixlPostParm->m_blmLensMax = blmLensMax; }

void ScnRenderDrSysParmAcc::setBlmLensRot(f32 blmLensRot) { m_drPixlPostParm->m_blmLensRot = blmLensRot; }

void ScnRenderDrSysParmAcc::setBlmLensWeight(f32 blmLensWeight) { m_drPixlPostParm->m_blmLensWeight = blmLensWeight; }

void ScnRenderDrSysParmAcc::setBlmLensDecay(f32 blmLensDecay) { m_drPixlPostParm->m_blmLensDecay = blmLensDecay; }

void ScnRenderDrSysParmAcc::setBlmLensStrength(f32 blmLensStrength) { m_drPixlPostParm->m_blmLensStrength = blmLensStrength; }

void ScnRenderDrSysParmAcc::setBlmLensParmMax(f32 blmLensParmMax) { m_drPixlPostParm->m_blmLensParmMax = blmLensParmMax; }

void ScnRenderDrSysParmAcc::setBlmLensUVDecay(f32 blmLensUVDecay) { m_drPixlPostParm->m_blmLensUVDecay = blmLensUVDecay; }

f32 ScnRenderDrSysParmAcc::getBlmLensSub() const { return m_drPixlPostParm->m_blmLensSub; }

f32 ScnRenderDrSysParmAcc::getBlmLensMul() const { return m_drPixlPostParm->m_blmLensMul; }

s32 ScnRenderDrSysParmAcc::getBlmLensMax() const { return m_drPixlPostParm->m_blmLensMax; }

f32 ScnRenderDrSysParmAcc::getBlmLensRot() const { return m_drPixlPostParm->m_blmLensRot; }

f32 ScnRenderDrSysParmAcc::getBlmLensWeight() const { return m_drPixlPostParm->m_blmLensWeight; }

f32 ScnRenderDrSysParmAcc::getBlmLensDecay() const { return m_drPixlPostParm->m_blmLensDecay; }

f32 ScnRenderDrSysParmAcc::getBlmLensStrength() const { return m_drPixlPostParm->m_blmLensStrength; }

f32 ScnRenderDrSysParmAcc::getBlmLensParmMax() const { return m_drPixlPostParm->m_blmLensParmMax; }

f32 ScnRenderDrSysParmAcc::getBlmLensUVDecay() const { return m_drPixlPostParm->m_blmLensUVDecay; }

void ScnRenderDrSysParmAcc::setGodRay(bool godRay) { m_drPixlPostParm->m_godRay = godRay; }

bool ScnRenderDrSysParmAcc::isGodRay() const { return m_drPixlPostParm->m_godRay; }

void ScnRenderDrSysParmAcc::setGodRayWeight(f32 godRayWeight) { m_drPixlPostParm->m_godRayWeight = godRayWeight; }

void ScnRenderDrSysParmAcc::setGodRayDecay(f32 godRayDecay) { m_drPixlPostParm->m_godRayDecay = godRayDecay; }

void ScnRenderDrSysParmAcc::setGodRayStrength(f32 godRayStrength) { m_drPixlPostParm->m_godRayStrength = godRayStrength; }

f32 ScnRenderDrSysParmAcc::getGodRayWeight() const { return m_drPixlPostParm->m_godRayWeight; }

f32 ScnRenderDrSysParmAcc::getGodRayDecay() const { return m_drPixlPostParm->m_godRayDecay; }

f32 ScnRenderDrSysParmAcc::getGodRayStrength() const { return m_drPixlPostParm->m_godRayStrength; }

void ScnRenderDrSysParmAcc::setAA(bool aa) { m_drPixlPostParm->m_AAOn = aa; }

bool ScnRenderDrSysParmAcc::isAA() const { return m_drPixlPostParm->getAAOn(); }

void ScnRenderDrSysParmAcc::setAAEdgeSharpness(f32 aaEdgeSharpness) { m_drPixlPostParm->m_aAEdgeSharpness = aaEdgeSharpness; }

void ScnRenderDrSysParmAcc::setAAEdgeThreshold(f32 aaEdgeThreshold) { m_drPixlPostParm->m_aAEdgeThreshold = aaEdgeThreshold; }

void ScnRenderDrSysParmAcc::setAAEdgeThresholdMin(f32 aaEdgeThresholdMin) { m_drPixlPostParm->m_aAEdgeThresholdMin = aaEdgeThresholdMin; }

void ScnRenderDrSysParmAcc::setAAEdgeRanges(f32 aaEdgeRanges) { m_drPixlPostParm->m_aAEdgeRanges = aaEdgeRanges; }

f32 ScnRenderDrSysParmAcc::getAAEdgeSharpness() const { return m_drPixlPostParm->m_aAEdgeSharpness; }

f32 ScnRenderDrSysParmAcc::getAAEdgeThreshold() const { return m_drPixlPostParm->m_aAEdgeThreshold; }

f32 ScnRenderDrSysParmAcc::getAAEdgeThresholdMin() const { return m_drPixlPostParm->m_aAEdgeThresholdMin; }

f32 ScnRenderDrSysParmAcc::getAAEdgeRanges() const { return m_drPixlPostParm->m_aAEdgeRanges; }

void ScnRenderDrSysParmAcc::setSSAO(bool ssao) { m_drPixlPostParm->m_sSAO = ssao; }

bool ScnRenderDrSysParmAcc::isSSAO() const { return m_drPixlPostParm->m_sSAO; }

void ScnRenderDrSysParmAcc::setSSAOBlurStr(f32 ssaoBlurStr) { m_drPixlPostParm->m_sSAOBlurStr = ssaoBlurStr; }

f32 ScnRenderDrSysParmAcc::getSSAOBlurStr() const { return m_drPixlPostParm->m_sSAOBlurStr; }

void ScnRenderDrSysParmAcc::setSpecularStr(f32 specularStr) { m_drPixlPostParm->m_specularStr = specularStr; }

f32 ScnRenderDrSysParmAcc::getSpecularStr() const { return m_drPixlPostParm->m_specularStr; }

void ScnRenderDrSysParmAcc::setMotBlurOverride(bool motBlurOverride) { m_drPixlPostParm->setOverrideMotBlur(motBlurOverride); }

void ScnRenderDrSysParmAcc::setMotBlur(bool motBlur) { m_drPixlPostParm->unknown1ca = motBlur; }

void ScnRenderDrSysParmAcc::setMotBlurDefault(bool motBlurDefault) { m_drMan->m_drIniSys->m_drPixlPostParm.m_motBlur2 = motBlurDefault; }

void ScnRenderDrSysParmAcc::setAppBlur(bool appBlur) { m_drPixlPostParm->m_appBlur = appBlur; }

void ScnRenderDrSysParmAcc::setSpBlur(bool spBlur) { m_drPixlPostParm->m_spBlur = spBlur; }

void ScnRenderDrSysParmAcc::setSpBlurTarget(const mm::Vec3 &spBlurTarget) {
  mm::Vec3 &destination = m_drPixlPostParm->unknownff0;
  destination.x = spBlurTarget.x;
  destination.y = spBlurTarget.y;
  destination.z = spBlurTarget.z;
}

void ScnRenderDrSysParmAcc::setBlurSpParm(f32 blurSpParm) { m_drPixlPostParm->m_blurSpParm = blurSpParm; }

bool ScnRenderDrSysParmAcc::isMotBlur() const { return m_drPixlPostParm->isMotBlur(); }

void ScnRenderDrSysParmAcc::setMotBlurStrength(f32 motBlurStrength) { m_drPixlPostParm->unknown1d4 = motBlurStrength; }

void ScnRenderDrSysParmAcc::setMotBlurSub(f32 motBlurSub) { m_drPixlPostParm->unknown1d8 = motBlurSub; }

f32 ScnRenderDrSysParmAcc::getBlurStrength() const { return m_drPixlPostParm->unknown1d4; }

f32 ScnRenderDrSysParmAcc::getBlurSub() const { return m_drPixlPostParm->unknown1d8; }

void ScnRenderDrSysParmAcc::setDOF(bool dof) { m_drPixlPostParm->setDOF(dof); }

bool ScnRenderDrSysParmAcc::isDOF() const { return m_drPixlPostParm->unknown218 || m_drPixlPostParm->unknown219; }

void ScnRenderDrSysParmAcc::setDoFPixlRatio(f32 dofPixlRatio) { m_drPixlPostParm->setDoFPixlRatio(dofPixlRatio); }

void ScnRenderDrSysParmAcc::setDoFDistance(f32 dofDistance) { m_drPixlPostParm->setDoFDistance(dofDistance); }

void ScnRenderDrSysParmAcc::setDoFRange(f32 dofRange) { m_drPixlPostParm->setDoFRange(dofRange); }

void ScnRenderDrSysParmAcc::setDoFStrength(f32 dofStrength) { m_drPixlPostParm->setDoFStrength(dofStrength); }

void ScnRenderDrSysParmAcc::setDoFLens(f32 dofLens) { m_drPixlPostParm->setDoFLens(dofLens); }

void ScnRenderDrSysParmAcc::setDoFBlend(f32 dofBlend) { m_drPixlPostParm->setDoFBlend(dofBlend); }

void ScnRenderDrSysParmAcc::setDofHLvMode(bool dofHLvMode) { m_drPixlPostParm->setDOFHlv(dofHLvMode); }

void ScnRenderDrSysParmAcc::setDofPixlLv(s32 dofPixlLv) {
  if (dofPixlLv < 0 || dofPixlLv > 2) {
    m_drPixlPostParm->setDoFPixlLv(0);
  } else {
    m_drPixlPostParm->setDoFPixlLv(dofPixlLv);
  }
}

void ScnRenderDrSysParmAcc::setDOFAutoFocus(bool dofAutoFocus) { m_drPixlPostParm->setDOFAutoFocus(dofAutoFocus); }

void ScnRenderDrSysParmAcc::setDOFFocusNum(s32 dofFocusNum) {
  if (dofFocusNum < 0 || dofFocusNum > 11) {
    dofFocusNum = 0;
  }
  m_drPixlPostParm->setDoFocusNum(dofFocusNum);
}

void ScnRenderDrSysParmAcc::setDOFFocusMin(f32 dofFocusMin) { m_drPixlPostParm->setDofFocusMin(dofFocusMin); }

void ScnRenderDrSysParmAcc::setDOFFocusRatio(f32 dofFocusRatio) { m_drPixlPostParm->setDoFDofFocusRat(dofFocusRatio); }

void ScnRenderDrSysParmAcc::setDOFFocusDebug(bool dofFocusDebug) { m_drPixlPostParm->setDOFAutoFocusDebug(dofFocusDebug); }

f32 ScnRenderDrSysParmAcc::getDoFPixlRatio() const { return m_drPixlPostParm->m_doFPixlRatio; }

f32 ScnRenderDrSysParmAcc::getDoFDistance() const { return m_drPixlPostParm->m_doFDistance; }

f32 ScnRenderDrSysParmAcc::getDoFRange() const { return m_drPixlPostParm->m_doFRange; }

f32 ScnRenderDrSysParmAcc::getDoFStrength() const { return m_drPixlPostParm->m_doFStrength; }

f32 ScnRenderDrSysParmAcc::getDoFLens() const { return m_drPixlPostParm->m_doFLens; }

f32 ScnRenderDrSysParmAcc::getDoFBlend() const { return m_drPixlPostParm->m_doFBlend; }

bool ScnRenderDrSysParmAcc::isDofHLvMode() const { return m_drPixlPostParm->m_dofHLvMode; }

s32 ScnRenderDrSysParmAcc::getDofPixlLv() const { return m_drPixlPostParm->m_dofPixlLv; }

bool ScnRenderDrSysParmAcc::isDOFAutoFocus() const { return m_drPixlPostParm->m_dOFAutoFocus; }

s32 ScnRenderDrSysParmAcc::getDOFFocusNum() const { return m_drPixlPostParm->m_dOFFocusNum; }

f32 ScnRenderDrSysParmAcc::getDOFFocusMin() const { return m_drPixlPostParm->m_dOFFocusMin; }

f32 ScnRenderDrSysParmAcc::getDOFFocusRatio() const { return m_drPixlPostParm->m_dOFFocusRatio; }

bool ScnRenderDrSysParmAcc::isDOFFocusDebug() const { return m_drPixlPostParm->m_DOFAutoFocusDebug; }

void ScnRenderDrSysParmAcc::setPlaneCloudNum(u32 planeCloudNum) {
  cloud::CloudMan *cloudMan = DrMan::getIns()->unknown1e00;
  if (cloudMan != nullptr) {
    cloudMan->setCldNum(planeCloudNum);
  }
}

u32 ScnRenderDrSysParmAcc::getPlaneCloudNum() {
  cloud::CloudMan *cloudMan = DrMan::getIns()->unknown1e00;
  if (cloudMan != nullptr) {
    return cloudMan->getCldNum();
  }
  return 0;
}

void ScnRenderDrSysParmAcc::setGlobalWind(const mm::Vec3 &globalWind) { m_drMan->setGlobalWind(globalWind); }

void ScnRenderDrSysParmAcc::setReduction(bool reduction) { m_drPixlPostParm->m_reduction = reduction; }

bool ScnRenderDrSysParmAcc::isReduction() const { return m_drPixlPostParm->m_reduction; }

void ScnRenderDrSysParmAcc::setAutoReduction(bool autoReduction) { m_drMan->setAutoReduction(autoReduction); }

void ScnRenderDrSysParmAcc::setReductionScX(f32 reductionScX) { m_drPixlPostParm->m_reductionScX = reductionScX; }

void ScnRenderDrSysParmAcc::setReductionScY(f32 reductionScY) { m_drPixlPostParm->m_reductionScY = reductionScY; }

f32 ScnRenderDrSysParmAcc::getReductionScX() const { return m_drPixlPostParm->m_reductionScX; }

f32 ScnRenderDrSysParmAcc::getReductionScY() const { return m_drPixlPostParm->m_reductionScY; }

bool ScnRenderDrSysParmAcc::isDispReduction() const { return m_drPixlPostParm->m_dispReduction; }

void ScnRenderDrSysParmAcc::setDispReduction(bool dispReduction) { m_drPixlPostParm->m_dispReduction = dispReduction; }

void ScnRenderDrSysParmAcc::setGroupsDisp(s32 group, bool disp) { m_drMan->setGroupsDisp(group, disp); }

void ScnRenderDrSysParmAcc::setColorFilterOverride(bool colorFilterOverride) { m_drPixlPostParm->setOverrideColorFilter(colorFilterOverride); }

void ScnRenderDrSysParmAcc::setColorFilterNum(s32 colorFilterNum) { m_drPixlPostParm->setColorFilterNum(colorFilterNum); }

void ScnRenderDrSysParmAcc::setColorFilterFarNum(s32 colorFilterFarNum) { m_drPixlPostParm->setColorFilterFarNum(colorFilterFarNum); }

void ScnRenderDrSysParmAcc::setColorFilterFrm(f32 colorFilterFrm) { m_drPixlPostParm->setColorFilterFrm(colorFilterFrm); }

f32 ScnRenderDrSysParmAcc::getColorFilterFrm() const { return m_drPixlPostParm->m_colorFilterFrm; }

void ScnRenderDrSysParmAcc::setRainDrop(bool rainDrop) { m_drPixlPostParm->m_rainDropOn = rainDrop; }

bool ScnRenderDrSysParmAcc::getRainDrop() const { return m_drPixlPostParm->getRainDropOn(); }

void ScnRenderDrSysParmAcc::setLightNum(s32 lightNum) { m_drPixlPostParm->m_lightNum = lightNum; }

s32 ScnRenderDrSysParmAcc::getLightNum() const { return m_drPixlPostParm->m_lightNum; }

void ScnRenderDrSysParmAcc::setInOut(bool inOut) { m_drPixlPostParm->m_inOut = inOut; }

bool ScnRenderDrSysParmAcc::isInOut() const { return m_drPixlPostParm->m_inOut; }

void ScnRenderDrSysParmAcc::setTimeVal(f32 timeVal) { m_drMan->setTimeVal(timeVal); }

f32 ScnRenderDrSysParmAcc::getTimerVal() const { return m_drMan->m_timerVal; }

void ScnRenderDrSysParmAcc::setWeather(s32 weather) { m_drPixlPostParm->m_weather = weather; }

s32 ScnRenderDrSysParmAcc::getWeather() const { return m_drPixlPostParm->m_weather; }

void ScnRenderDrSysParmAcc::setWeatherFrame(f32 weatherFrame) { m_drPixlPostParm->setWeatherFrame(weatherFrame); }

f32 ScnRenderDrSysParmAcc::getWeatherFrame() const { return m_drPixlPostParm->getWeatherFrame(); }

void ScnRenderDrSysParmAcc::setSeamMapAddPosMode(bool seamMapAddPosMode) { m_drMan->m_seamMapAddPosMode = seamMapAddPosMode; }

void ScnRenderDrSysParmAcc::setSeamMapReadPos(const mm::Vec3 &seamMapReadPos) {
  mm::Vec3 &destination = m_drMan->unknown1c70;
  destination.x = seamMapReadPos.x;
  destination.y = seamMapReadPos.y;
  destination.z = seamMapReadPos.z;
}

void ScnRenderDrSysParmAcc::releaseFastLight() { m_drMan->releaseFastLight(unknown10); }

u32 ScnRenderDrSysParmAcc::isGblId(s32 id) { return m_drMan->isGblIdx(id); }

void ScnRenderDrSysParmAcc::setSelectIdDisp(s32 id, bool disp) {
  if (disp) {
    m_drMan->offGblIdx(id);
  } else {
    m_drMan->setGblIdx(id);
  }
}

void ScnRenderDrSysParmAcc::setPlayAnime(s32 id, bool play, bool loop) {}

bool ScnRenderDrSysParmAcc::isSelectIdDisp(s32 id) { return isGblId(id) == 0; }

bool ScnRenderDrSysParmAcc::isPlayAnime(s32 id) { return false; }

void ScnRenderDrSysParmAcc::setClip(bool clip) { m_drMan->m_clip = clip; }

void ScnRenderDrSysParmAcc::setFogSkip(bool fogSkip) { m_drMan->m_fogSkip = fogSkip; }

u32 *ScnRenderDrSysParmAcc::getGblTbl() { return m_drMan->m_gblIdx; }

void ScnRenderDrSysParmAcc::setSpCapMode(s32 spCapMode) { m_drMan->setAvatarCapMode(spCapMode); }

s32 ScnRenderDrSysParmAcc::getSpCapMode() const { return 0; }

void ScnRenderDrSysParmAcc::setMdlHeightTexSkip(bool mdlHeightTexSkip) { m_drMan->m_mdlHeightTexSkip = mdlHeightTexSkip; }

bool ScnRenderDrSysParmAcc::isMdlHeightTexSkip() const { return m_drMan->m_mdlHeightTexSkip; }

void ScnRenderDrSysParmAcc::setSeamMapOpenMode(bool seamMapOpenMode) { m_drMan->m_seamMapOpenMode = seamMapOpenMode; }

bool ScnRenderDrSysParmAcc::isSeamMapOpenMode() const { return m_drMan->m_seamMapOpenMode; }

void ScnRenderDrSysParmAcc::setScreenDispOff(bool screenDispOff) { m_drMan->m_screenDispOff = screenDispOff; }

FILE_PRIO ScnRenderDrSysParmAcc::getSeamMapPriMdl() const { return m_drMan->m_seamMapPriMdl; }

FILE_PRIO ScnRenderDrSysParmAcc::getSeamMapPriColi() const { return m_drMan->m_seamMapPriColi; }

void ScnRenderDrSysParmAcc::setSeamMapPriMdl(FILE_PRIO seamMapPriMdl) { m_drMan->m_seamMapPriMdl = seamMapPriMdl; }

void ScnRenderDrSysParmAcc::setSeamMapPriColi(FILE_PRIO seamMapPriColi) { m_drMan->m_seamMapPriColi = seamMapPriColi; }

void *ScnRenderDrSysParmAcc::getBlurVelocityMap() {
  wkPixlManRes *resources = m_drMan->m_drPixlMan->unknown10;
  DrPixlPostObjMotionBlur *motionBlur = resources[unknown10].m_drPixlPostMan->m_drPixlPostObjMotionBlur;
  if (motionBlur != nullptr) {
    return motionBlur->unknown28;
  }
  return nullptr;
}

void ScnRenderDrSysParmAcc::setCharDirShadow(bool charDirShadow) { m_drPixlPostParm->m_charDirShadow = charDirShadow; }

bool ScnRenderDrSysParmAcc::isCharDirShadow() const { return m_drPixlPostParm->m_charDirShadow; }

void ScnRenderDrSysParmAcc::setMdlDblPause(bool mdlDblPause) { m_drMan->m_mdlDblPause = mdlDblPause; }

bool ScnRenderDrSysParmAcc::isMdlDblPause() const { return m_drMan->m_mdlDblPause; }

bool ScnRenderDrSysParmAcc::isMdlAllMiddleTexStm() const { return m_drMan->isAllMiddelTexStmChk(); }

bool ScnRenderDrSysParmAcc::isSeamMapRead() const { return m_drMan->isSeamMapStmOk(); }

void ScnRenderDrSysParmAcc::setSeamReadLv(s32 seamReadLv) {
  if (seamReadLv < 0) {
    m_drMan->unknown1cfc = 0;
  } else if (seamReadLv > 5) {
    m_drMan->unknown1cfc = 5;
  } else {
    m_drMan->unknown1cfc = seamReadLv;
  }
}

void ScnRenderDrSysParmAcc::setHeightTexSkip(bool heightTexSkip) { m_drMan->m_heightTexSkip = heightTexSkip; }

bool ScnRenderDrSysParmAcc::isHeightTexSkip() const { return m_drMan->m_heightTexSkip; }

void ScnRenderDrSysParmAcc::setSeamHeightTexSkip(bool seamHeightTexSkip) { m_drMan->m_seamHeightTexSkip = seamHeightTexSkip; }

bool ScnRenderDrSysParmAcc::isSeamHeightTexSkip() const { return m_drMan->m_seamHeightTexSkip; }

void ScnRenderDrSysParmAcc::setShadowStr(f32 shadowStr) { m_drPixlPostParm->m_shadowStr = shadowStr; }

f32 ScnRenderDrSysParmAcc::getShadowStr() const { return m_drPixlPostParm->m_shadowStr; }

void ScnRenderDrSysParmAcc::setShadowChacheAngle(f32 shadowChacheAngle) { m_drPixlPostParm->m_shadowChacheAngle = shadowChacheAngle; }

f32 ScnRenderDrSysParmAcc::getShadowChacheAngle() const { return m_drPixlPostParm->m_shadowChacheAngle; }

void ScnRenderDrSysParmAcc::callCubeMapRender(const DR_CAPCUBE_PARAM &param) { m_drMan->callCubeMapRender(param); }

bool ScnRenderDrSysParmAcc::getIrrVolIsValid() const { return m_drMan->m_drIrrVolMan->isValid(); }

const mm::Vec3 &ScnRenderDrSysParmAcc::getIrrVolCenterPos() const { return m_drMan->m_drIrrVolMan->m_irrVolCenterPos; }

void ScnRenderDrSysParmAcc::setIrrVolCenterPos(const mm::Vec3 &irrVolCenterPos) {
  DrIrrVolMan *irrVolMan = m_drMan->m_drIrrVolMan;
  irrVolMan->unknown190.x = irrVolCenterPos.x;
  irrVolMan->unknown190.y = irrVolCenterPos.y;
  irrVolMan->unknown190.z = irrVolCenterPos.z;
}

u32 ScnRenderDrSysParmAcc::getIrrVolCascadeMax() const {
  DrIrrVolMan *irrVolMan = m_drMan->m_drIrrVolMan;
  u32 cascadeNum = irrVolMan->unknown1c4;
  u32 cascadeMax = irrVolMan->unknown08->unknown20;
  return cascadeNum < cascadeMax ? cascadeNum : cascadeMax;
}

void ScnRenderDrSysParmAcc::getIrrVolVolumeArea(u32 cascade, mm::Aabb &area) const { m_drMan->m_drIrrVolMan->getVolumeArea(cascade, area); }

void ScnRenderDrSysParmAcc::setToonDirLightScale(bool toonDirLightScale) { m_drMan->m_toonDirLightScale = toonDirLightScale; }

void ScnRenderDrSysParmAcc::setToonAmbient(bool toonAmbient) {
  if (toonAmbient) {
    m_drMan->unknown1e0c = 3;
  } else {
    m_drMan->unknown1e0c = 0;
  }
}

void ScnRenderDrSysParmAcc::setDispChara(bool dispChara) { m_drMan->m_dispChara = !dispChara; }

bool ScnRenderDrSysParmAcc::isDispChara() const { return !m_drMan->m_dispChara; }

bool ScnRenderDrSysParmAcc::isDispGlobalIBLTex() const { return m_drMan->unknown120[0]->m_dispGlobalIBLTex; }

void ScnRenderDrSysParmAcc::setDispGlobalIBLTex(bool dispGlobalIBLTex) { m_drMan->unknown120[0]->m_dispGlobalIBLTex = dispGlobalIBLTex; }

void ScnRenderDrSysParmAcc::setPlayerPos(const mm::Vec3 &playerPos) {}

void ScnRenderDrSysParmAcc::setCameraLight(bool cameraLight) { m_drMan->m_cameraLight = cameraLight; }

void ScnRenderDrSysParmAcc::setGBuffDebug(bool gBuffDebug) { m_drMan->unknown120[0]->m_gBuffDebug = gBuffDebug; }

void ScnRenderDrSysParmAcc::setGBuffDebugParam(GBuffDebugType type, f32 min, f32 max) {
  DrPixlPostParm *firstPostParm = m_drMan->unknown120[0];
  switch (static_cast<s32>(type)) {
  case 0:
    firstPostParm->unknown320[0].unknown00[0] = min;
    firstPostParm->unknown320[0].unknown00[1] = max;
    break;
  case 1:
    firstPostParm->unknown320[1].unknown00[0] = min;
    firstPostParm->unknown320[1].unknown00[1] = max;
    break;
  case 2:
    firstPostParm->unknown320[2].unknown00[0] = min;
    firstPostParm->unknown320[2].unknown00[1] = max;
    break;
  case 3:
    firstPostParm->unknown320[3].unknown00[0] = min;
    firstPostParm->unknown320[3].unknown00[1] = max;
    break;
  case 4:
    firstPostParm->unknown320[4].unknown00[0] = min;
    firstPostParm->unknown320[4].unknown00[1] = max;
    break;
  }
}

void ScnRenderDrSysParmAcc::createAddRenderView(ScnRenderDrViewCtrl *viewCtrl) {
  DR_VIEW_PARAM param;
  param.unknown00 = viewCtrl->unknown00.x;
  param.unknown04 = viewCtrl->unknown00.y;
  param.unknown08 = viewCtrl->unknown08 + 1;
  param.unknown0c = viewCtrl->unknown1c;
  param.unknown0d = viewCtrl->unknown28;
  param.unknown0e = viewCtrl->unknown34;
  param.unknown30 = &viewCtrl->unknown20;
  param.unknown18 = &viewCtrl->unknown35;
  param.unknown10 = &viewCtrl->unknown0c;
  param.unknown20 = &viewCtrl->unknown2c;
  param.unknown28 = &viewCtrl->unknown30;
  m_drMan->createAddRenderSystem(&param);
}

void ScnRenderDrSysParmAcc::deleteAddRenderView(ScnRenderDrViewCtrl *viewCtrl) { m_drMan->deleteAddRenderSystem(viewCtrl->unknown08 + 1); }

void ScnRenderDrSysParmAcc::setModelTexture(const ScnRenderDrMdlTexture &texture) {
  DR_MODEL_TEXTURE param;
  param.unknown00 = texture.unknown00;
  param.unknown08 = texture.unknown0c;
  m_drMan->setModelTexture(&param, texture.unknown08);
}

void ScnRenderDrSysParmAcc::resetModelTexture(u32 index) { m_drMan->resetModelTexture(index); }

void ScnRenderDrSysParmAcc::setDefferedColor(bool defferedColor) { m_drMan->unknown120[0]->m_defferedColor = defferedColor; }

bool ScnRenderDrSysParmAcc::isDefferedColor() const { return m_drMan->unknown120[0]->m_defferedColor; }

void ScnRenderDrSysParmAcc::setRenderSpecMode(RenderSpecMode renderSpecMode) { m_drMan->m_renderSpecMode = renderSpecMode; }

void ScnRenderDrSysParmAcc::setGlassBr(bool glassBr, u32 type) { m_drPixlPostParm->setGlassBrk(glassBr, type); }

bool ScnRenderDrSysParmAcc::isGlassBr() { return m_drPixlPostParm->m_glassBr; }

void ScnRenderDrSysParmAcc::setCacherClearMode(bool cacherClearMode) { m_drMan->setCacherClearMode(cacherClearMode); }

bool ScnRenderDrSysParmAcc::isViewRenderSkip(u32 view) const { return (DrMan::get()->unknown1c9c & (1 << view)) != 0; }

void ScnRenderDrSysParmAcc::setViewRenderSkip(u32 view, bool skip) {
  DrMan *drMan = DrMan::get();
  if (skip) {
    drMan->unknown1c9c |= 1 << view;
  } else {
    drMan->unknown1c9c &= ~(1 << view);
  }
}

void ScnRenderDrSysParmAcc::setWriteZBuffer(bool writeZBuffer) { DrMan::get()->m_writeZBuffer = writeZBuffer; }

void ScnRenderDrSysParmAcc::resetScene() { m_drPixlPostParm->resetScene(); }

void ScnRenderDrSysParmAcc::setAutoResetScene(bool autoResetScene) { DrMan::get()->m_autoResetScene = autoResetScene; }

f32 ScnRenderDrSysParmAcc::getGamma() const { return DrMan::get()->m_gamma; }

void ScnRenderDrSysParmAcc::setGamma(f32 gamma) { DrMan::get()->m_gamma = gamma; }

void ScnRenderDrSysParmAcc::setCaptureMode(bool captureMode) {
  DrMan *instance = DrMan::get();
  s32 index = DrMan::s_nDblStockIdx;
  instance->unknown1c81[index] = captureMode ? 1 : 2;
}

} // namespace ml
