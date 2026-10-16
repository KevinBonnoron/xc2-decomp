#include "scn/scn_render_dr_sys_parm_acc.h"

#include "cloud/cloud_man.h"
#include "dr/dr_irr_vol_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_render_dr_sys.h"

namespace mm {
struct Aabb;
} // namespace mm

namespace ml {
struct DR_CAPCUBE_PARAM;

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc() : drMan(nullptr), postParm(nullptr), viewIndex(0) {
  drMan = DrMan::get();
  postParm = drMan->postParms[viewIndex];
}

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc(ScnRenderDrSys *drSys, s32 index) : drMan(nullptr), postParm(nullptr) { setDrSys(drSys, index); }

void ScnRenderDrSysParmAcc::setDrSys(ScnRenderDrSys *drSys, s32 index) {
  drMan = drSys->drMan;
  postParm = drMan->postParms[index];
  viewIndex = index;
}

void ScnRenderDrSysParmAcc::setDOFOverride(bool dofOverride) { postParm->setOverrideDOF(dofOverride); }

void ScnRenderDrSysParmAcc::setGlbSpd(f32 glbSpd) { drMan->glbSpd = glbSpd; }

f32 ScnRenderDrSysParmAcc::getGlbSpd() const { return drMan->glbSpd; }

void ScnRenderDrSysParmAcc::setMdlSpd(f32 mdlSpd) { drMan->mdlSpd = mdlSpd; }

f32 ScnRenderDrSysParmAcc::getMdlSpd() const { return drMan->mdlSpd; }

void ScnRenderDrSysParmAcc::setToneMap(bool toneMap) { postParm->toneMap = toneMap; }

bool ScnRenderDrSysParmAcc::isToneMap() const { return postParm->getToneMapOn(); }

void ScnRenderDrSysParmAcc::setToneMax(f32 toneMax) { postParm->toneMax = toneMax; }

void ScnRenderDrSysParmAcc::setToneMin(f32 toneMin) { postParm->toneMin = toneMin; }

void ScnRenderDrSysParmAcc::setToneRatio(f32 toneRatio) { postParm->toneRatio = toneRatio; }

void ScnRenderDrSysParmAcc::setToneRatioLast(f32 toneRatioLast) { postParm->toneRatioLast = toneRatioLast; }

void ScnRenderDrSysParmAcc::setOverrideToneMap(f32 overrideToneMap) { postParm->setOverrideToneMap(overrideToneMap); }

void ScnRenderDrSysParmAcc::setToneBlmMax(f32 toneBlmMax) { postParm->toneBlmMax = toneBlmMax; }

void ScnRenderDrSysParmAcc::setToneBlmMin(f32 toneBlmMin) { postParm->toneBlmMin = toneBlmMin; }

void ScnRenderDrSysParmAcc::setToneBlmRatio(f32 toneBlmRatio) { postParm->toneBlmRatio = toneBlmRatio; }

void ScnRenderDrSysParmAcc::setToneBlmRatioLast(f32 toneBlmRatioLast) { postParm->toneBlmRatioLast = toneBlmRatioLast; }

void ScnRenderDrSysParmAcc::setBloom(bool bloom) { postParm->bloom = bloom; }

bool ScnRenderDrSysParmAcc::isBloomOn() const { return postParm->getBloomOn(); }

void ScnRenderDrSysParmAcc::setBorderBlmSub(f32 borderBlmSub) { postParm->borderBlmSub = borderBlmSub; }

void ScnRenderDrSysParmAcc::setBorderBlmMul(f32 borderBlmMul) { postParm->borderBlmMul = borderBlmMul; }

void ScnRenderDrSysParmAcc::setBorderBlmSecSub(f32 borderBlmSecSub) { postParm->borderBlmSecSub = borderBlmSecSub; }

void ScnRenderDrSysParmAcc::setBorderBlmSecMul(f32 borderBlmSecMul) { postParm->borderBlmSecMul = borderBlmSecMul; }

void ScnRenderDrSysParmAcc::setBorderBlmMax(f32 borderBlmMax) { postParm->borderBlmMax = borderBlmMax; }

void ScnRenderDrSysParmAcc::setBlmWeight(f32 x, f32 y, f32 z) {
  f32 *blmWeight = postParm->blmWeight;
  blmWeight[0] = x;
  blmWeight[1] = y;
  blmWeight[2] = z;
}

void ScnRenderDrSysParmAcc::setBlmStr(f32 x, f32 y, f32 z) {
  f32 *blmStr = postParm->blmStr;
  blmStr[0] = x;
  blmStr[1] = y;
  blmStr[2] = z;
}

void ScnRenderDrSysParmAcc::setBlmGauss(f32 x, f32 y, f32 z) {
  f32 *blmGauss = postParm->blmGauss;
  blmGauss[0] = x;
  blmGauss[1] = y;
  blmGauss[2] = z;
}

f32 ScnRenderDrSysParmAcc::getBorderBlmSub() const { return postParm->borderBlmSub; }

f32 ScnRenderDrSysParmAcc::getBorderBlmMul() const { return postParm->getBorderBlmMul(); }

f32 ScnRenderDrSysParmAcc::getBorderBlmSecSub() const { return postParm->borderBlmSecSub; }

f32 ScnRenderDrSysParmAcc::getBorderBlmSecMul() const { return postParm->borderBlmSecMul; }

f32 ScnRenderDrSysParmAcc::getBorderBlmMax() const { return postParm->borderBlmMax; }

const f32 *ScnRenderDrSysParmAcc::getBlmWeight() const { return postParm->blmWeight; }

const f32 *ScnRenderDrSysParmAcc::getBlmStr() const { return postParm->blmStr; }

const f32 *ScnRenderDrSysParmAcc::getBlmGauss() const { return postParm->blmGauss; }

void ScnRenderDrSysParmAcc::setLensFlare(bool lensFlare) { postParm->lensFlare = lensFlare; }

bool ScnRenderDrSysParmAcc::isLensFlare() const { return postParm->lensFlare; }

void ScnRenderDrSysParmAcc::setBlmLensSub(f32 blmLensSub) { postParm->blmLensSub = blmLensSub; }

void ScnRenderDrSysParmAcc::setBlmLensMul(f32 blmLensMul) { postParm->blmLensMul = blmLensMul; }

void ScnRenderDrSysParmAcc::setBlmLensMax(s32 blmLensMax) { postParm->blmLensMax = blmLensMax; }

void ScnRenderDrSysParmAcc::setBlmLensRot(f32 blmLensRot) { postParm->blmLensRot = blmLensRot; }

void ScnRenderDrSysParmAcc::setBlmLensWeight(f32 blmLensWeight) { postParm->blmLensWeight = blmLensWeight; }

void ScnRenderDrSysParmAcc::setBlmLensDecay(f32 blmLensDecay) { postParm->blmLensDecay = blmLensDecay; }

void ScnRenderDrSysParmAcc::setBlmLensStrength(f32 blmLensStrength) { postParm->blmLensStrength = blmLensStrength; }

void ScnRenderDrSysParmAcc::setBlmLensParmMax(f32 blmLensParmMax) { postParm->blmLensParmMax = blmLensParmMax; }

void ScnRenderDrSysParmAcc::setBlmLensUVDecay(f32 blmLensUVDecay) { postParm->blmLensUVDecay = blmLensUVDecay; }

f32 ScnRenderDrSysParmAcc::getBlmLensSub() const { return postParm->blmLensSub; }

f32 ScnRenderDrSysParmAcc::getBlmLensMul() const { return postParm->blmLensMul; }

s32 ScnRenderDrSysParmAcc::getBlmLensMax() const { return postParm->blmLensMax; }

f32 ScnRenderDrSysParmAcc::getBlmLensRot() const { return postParm->blmLensRot; }

f32 ScnRenderDrSysParmAcc::getBlmLensWeight() const { return postParm->blmLensWeight; }

f32 ScnRenderDrSysParmAcc::getBlmLensDecay() const { return postParm->blmLensDecay; }

f32 ScnRenderDrSysParmAcc::getBlmLensStrength() const { return postParm->blmLensStrength; }

f32 ScnRenderDrSysParmAcc::getBlmLensParmMax() const { return postParm->blmLensParmMax; }

f32 ScnRenderDrSysParmAcc::getBlmLensUVDecay() const { return postParm->blmLensUVDecay; }

void ScnRenderDrSysParmAcc::setGodRay(bool godRay) { postParm->godRay = godRay; }

bool ScnRenderDrSysParmAcc::isGodRay() const { return postParm->godRay; }

void ScnRenderDrSysParmAcc::setGodRayWeight(f32 godRayWeight) { postParm->godRayWeight = godRayWeight; }

void ScnRenderDrSysParmAcc::setGodRayDecay(f32 godRayDecay) { postParm->godRayDecay = godRayDecay; }

void ScnRenderDrSysParmAcc::setGodRayStrength(f32 godRayStrength) { postParm->godRayStrength = godRayStrength; }

f32 ScnRenderDrSysParmAcc::getGodRayWeight() const { return postParm->godRayWeight; }

f32 ScnRenderDrSysParmAcc::getGodRayDecay() const { return postParm->godRayDecay; }

f32 ScnRenderDrSysParmAcc::getGodRayStrength() const { return postParm->godRayStrength; }

void ScnRenderDrSysParmAcc::setAA(bool aa) { postParm->aa = aa; }

bool ScnRenderDrSysParmAcc::isAA() const { return postParm->getAAOn(); }

void ScnRenderDrSysParmAcc::setAAEdgeSharpness(f32 aaEdgeSharpness) { postParm->aaEdgeSharpness = aaEdgeSharpness; }

void ScnRenderDrSysParmAcc::setAAEdgeThreshold(f32 aaEdgeThreshold) { postParm->aaEdgeThreshold = aaEdgeThreshold; }

void ScnRenderDrSysParmAcc::setAAEdgeThresholdMin(f32 aaEdgeThresholdMin) { postParm->aaEdgeThresholdMin = aaEdgeThresholdMin; }

void ScnRenderDrSysParmAcc::setAAEdgeRanges(f32 aaEdgeRanges) { postParm->aaEdgeRanges = aaEdgeRanges; }

f32 ScnRenderDrSysParmAcc::getAAEdgeSharpness() const { return postParm->aaEdgeSharpness; }

f32 ScnRenderDrSysParmAcc::getAAEdgeThreshold() const { return postParm->aaEdgeThreshold; }

f32 ScnRenderDrSysParmAcc::getAAEdgeThresholdMin() const { return postParm->aaEdgeThresholdMin; }

f32 ScnRenderDrSysParmAcc::getAAEdgeRanges() const { return postParm->aaEdgeRanges; }

void ScnRenderDrSysParmAcc::setSSAO(bool ssao) { postParm->ssao = ssao; }

bool ScnRenderDrSysParmAcc::isSSAO() const { return postParm->ssao; }

void ScnRenderDrSysParmAcc::setSSAOBlurStr(f32 ssaoBlurStr) { postParm->ssaoBlurStr = ssaoBlurStr; }

f32 ScnRenderDrSysParmAcc::getSSAOBlurStr() const { return postParm->ssaoBlurStr; }

void ScnRenderDrSysParmAcc::setSpecularStr(f32 specularStr) { postParm->specularStr = specularStr; }

f32 ScnRenderDrSysParmAcc::getSpecularStr() const { return postParm->specularStr; }

void ScnRenderDrSysParmAcc::setMotBlurOverride(bool motBlurOverride) { postParm->setOverrideMotBlur(motBlurOverride); }

void ScnRenderDrSysParmAcc::setMotBlur(bool motBlur) { postParm->motBlur = motBlur; }

void ScnRenderDrSysParmAcc::setMotBlurDefault(bool motBlurDefault) { drMan->motBlurState->motBlurDefault = motBlurDefault; }

void ScnRenderDrSysParmAcc::setAppBlur(bool appBlur) { postParm->appBlur = appBlur; }

void ScnRenderDrSysParmAcc::setSpBlur(bool spBlur) { postParm->spBlur = spBlur; }

void ScnRenderDrSysParmAcc::setSpBlurTarget(const mm::Vec3 &spBlurTarget) {
  mm::Vec3 &destination = postParm->spBlurTarget;
  destination.x = spBlurTarget.x;
  destination.y = spBlurTarget.y;
  destination.z = spBlurTarget.z;
}

void ScnRenderDrSysParmAcc::setBlurSpParm(f32 blurSpParm) { postParm->blurSpParm = blurSpParm; }

bool ScnRenderDrSysParmAcc::isMotBlur() const { return postParm->isMotBlur(); }

void ScnRenderDrSysParmAcc::setMotBlurStrength(f32 motBlurStrength) { postParm->motBlurStrength = motBlurStrength; }

void ScnRenderDrSysParmAcc::setMotBlurSub(f32 motBlurSub) { postParm->motBlurSub = motBlurSub; }

f32 ScnRenderDrSysParmAcc::getBlurStrength() const { return postParm->motBlurStrength; }

f32 ScnRenderDrSysParmAcc::getBlurSub() const { return postParm->motBlurSub; }

void ScnRenderDrSysParmAcc::setDOF(bool dof) { postParm->setDOF(dof); }

bool ScnRenderDrSysParmAcc::isDOF() const { return postParm->dof || postParm->dofOverride; }

void ScnRenderDrSysParmAcc::setDoFPixlRatio(f32 dofPixlRatio) { postParm->setDoFPixlRatio(dofPixlRatio); }

void ScnRenderDrSysParmAcc::setDoFDistance(f32 dofDistance) { postParm->setDoFDistance(dofDistance); }

void ScnRenderDrSysParmAcc::setDoFRange(f32 dofRange) { postParm->setDoFRange(dofRange); }

void ScnRenderDrSysParmAcc::setDoFStrength(f32 dofStrength) { postParm->setDoFStrength(dofStrength); }

void ScnRenderDrSysParmAcc::setDoFLens(f32 dofLens) { postParm->setDoFLens(dofLens); }

void ScnRenderDrSysParmAcc::setDoFBlend(f32 dofBlend) { postParm->setDoFBlend(dofBlend); }

void ScnRenderDrSysParmAcc::setDofHLvMode(bool dofHLvMode) { postParm->setDOFHlv(dofHLvMode); }

void ScnRenderDrSysParmAcc::setDOFAutoFocus(bool dofAutoFocus) { postParm->setDOFAutoFocus(dofAutoFocus); }

void ScnRenderDrSysParmAcc::setDOFFocusNum(s32 dofFocusNum) {
  if (dofFocusNum < 0 || dofFocusNum > 11) {
    dofFocusNum = 0;
  }
  postParm->setDoFocusNum(dofFocusNum);
}

void ScnRenderDrSysParmAcc::setDOFFocusMin(f32 dofFocusMin) { postParm->setDofFocusMin(dofFocusMin); }

void ScnRenderDrSysParmAcc::setDOFFocusRatio(f32 dofFocusRatio) { postParm->setDoFDofFocusRat(dofFocusRatio); }

void ScnRenderDrSysParmAcc::setDOFFocusDebug(bool dofFocusDebug) { postParm->setDOFAutoFocusDebug(dofFocusDebug); }

f32 ScnRenderDrSysParmAcc::getDoFPixlRatio() const { return postParm->dofPixlRatio; }

f32 ScnRenderDrSysParmAcc::getDoFDistance() const { return postParm->dofDistance; }

f32 ScnRenderDrSysParmAcc::getDoFRange() const { return postParm->dofRange; }

f32 ScnRenderDrSysParmAcc::getDoFStrength() const { return postParm->dofStrength; }

f32 ScnRenderDrSysParmAcc::getDoFLens() const { return postParm->dofLens; }

f32 ScnRenderDrSysParmAcc::getDoFBlend() const { return postParm->dofBlend; }

bool ScnRenderDrSysParmAcc::isDofHLvMode() const { return postParm->dofHLvMode; }

s32 ScnRenderDrSysParmAcc::getDofPixlLv() const { return postParm->dofPixlLv; }

bool ScnRenderDrSysParmAcc::isDOFAutoFocus() const { return postParm->dofAutoFocus; }

s32 ScnRenderDrSysParmAcc::getDOFFocusNum() const { return postParm->dofFocusNum; }

f32 ScnRenderDrSysParmAcc::getDOFFocusMin() const { return postParm->dofFocusMin; }

f32 ScnRenderDrSysParmAcc::getDOFFocusRatio() const { return postParm->dofFocusRatio; }

bool ScnRenderDrSysParmAcc::isDOFFocusDebug() const { return postParm->dofFocusDebug; }

void ScnRenderDrSysParmAcc::setPlaneCloudNum(u32 planeCloudNum) {
  cloud::CloudMan *cloudMan = DrMan::getIns()->cloudMan;
  if (cloudMan != nullptr) {
    cloudMan->setCldNum(planeCloudNum);
  }
}

u32 ScnRenderDrSysParmAcc::getPlaneCloudNum() {
  cloud::CloudMan *cloudMan = DrMan::getIns()->cloudMan;
  if (cloudMan != nullptr) {
    return cloudMan->getCldNum();
  }
  return 0;
}

void ScnRenderDrSysParmAcc::setGlobalWind(const mm::Vec3 &globalWind) { drMan->setGlobalWind(globalWind); }

void ScnRenderDrSysParmAcc::setReduction(bool reduction) { postParm->reduction = reduction; }

bool ScnRenderDrSysParmAcc::isReduction() const { return postParm->reduction; }

void ScnRenderDrSysParmAcc::setAutoReduction(bool autoReduction) { drMan->setAutoReduction(autoReduction); }

void ScnRenderDrSysParmAcc::setReductionScX(f32 reductionScX) { postParm->reductionScX = reductionScX; }

void ScnRenderDrSysParmAcc::setReductionScY(f32 reductionScY) { postParm->reductionScY = reductionScY; }

f32 ScnRenderDrSysParmAcc::getReductionScX() const { return postParm->reductionScX; }

f32 ScnRenderDrSysParmAcc::getReductionScY() const { return postParm->reductionScY; }

bool ScnRenderDrSysParmAcc::isDispReduction() const { return postParm->dispReduction; }

void ScnRenderDrSysParmAcc::setDispReduction(bool dispReduction) { postParm->dispReduction = dispReduction; }

void ScnRenderDrSysParmAcc::setGroupsDisp(s32 group, bool disp) { drMan->setGroupsDisp(group, disp); }

void ScnRenderDrSysParmAcc::setColorFilterOverride(bool colorFilterOverride) { postParm->setOverrideColorFilter(colorFilterOverride); }

void ScnRenderDrSysParmAcc::setColorFilterNum(s32 colorFilterNum) { postParm->setColorFilterNum(colorFilterNum); }

void ScnRenderDrSysParmAcc::setColorFilterFarNum(s32 colorFilterFarNum) { postParm->setColorFilterFarNum(colorFilterFarNum); }

void ScnRenderDrSysParmAcc::setColorFilterFrm(f32 colorFilterFrm) { postParm->setColorFilterFrm(colorFilterFrm); }

f32 ScnRenderDrSysParmAcc::getColorFilterFrm() const { return postParm->colorFilterFrm; }

void ScnRenderDrSysParmAcc::setRainDrop(bool rainDrop) { postParm->rainDrop = rainDrop; }

bool ScnRenderDrSysParmAcc::getRainDrop() const { return postParm->getRainDropOn(); }

void ScnRenderDrSysParmAcc::setLightNum(s32 lightNum) { postParm->lightNum = lightNum; }

s32 ScnRenderDrSysParmAcc::getLightNum() const { return postParm->lightNum; }

void ScnRenderDrSysParmAcc::setInOut(bool inOut) { postParm->inOut = inOut; }

bool ScnRenderDrSysParmAcc::isInOut() const { return postParm->inOut; }

void ScnRenderDrSysParmAcc::setTimeVal(f32 timeVal) { drMan->setTimeVal(timeVal); }

f32 ScnRenderDrSysParmAcc::getTimerVal() const { return drMan->timerVal; }

void ScnRenderDrSysParmAcc::setWeather(s32 weather) { postParm->weather = weather; }

s32 ScnRenderDrSysParmAcc::getWeather() const { return postParm->weather; }

void ScnRenderDrSysParmAcc::setWeatherFrame(f32 weatherFrame) { postParm->setWeatherFrame(weatherFrame); }

f32 ScnRenderDrSysParmAcc::getWeatherFrame() const { return postParm->getWeatherFrame(); }

void ScnRenderDrSysParmAcc::setSeamMapAddPosMode(bool seamMapAddPosMode) { drMan->seamMapAddPosMode = seamMapAddPosMode; }

void ScnRenderDrSysParmAcc::setSeamMapReadPos(const mm::Vec3 &seamMapReadPos) {
  mm::Vec3 &destination = drMan->seamMapReadPos;
  destination.x = seamMapReadPos.x;
  destination.y = seamMapReadPos.y;
  destination.z = seamMapReadPos.z;
}

void ScnRenderDrSysParmAcc::releaseFastLight() { drMan->releaseFastLight(viewIndex); }

u32 ScnRenderDrSysParmAcc::isGblId(s32 id) {
  u32 *gblTbl = drMan->gblTbl;
  return gblTbl[id >> 5] & (1 << (id & 31));
}

void ScnRenderDrSysParmAcc::setSelectIdDisp(s32 id, bool disp) {
  if (disp) {
    drMan->offGblIdx(id);
  } else {
    drMan->setGblIdx(id);
  }
}

void ScnRenderDrSysParmAcc::setPlayAnime(s32 id, bool play, bool loop) {}

bool ScnRenderDrSysParmAcc::isSelectIdDisp(s32 id) { return isGblId(id) == 0; }

bool ScnRenderDrSysParmAcc::isPlayAnime(s32 id) { return false; }

void ScnRenderDrSysParmAcc::setClip(bool clip) { drMan->clip = clip; }

void ScnRenderDrSysParmAcc::setFogSkip(bool fogSkip) { drMan->fogSkip = fogSkip; }

u32 *ScnRenderDrSysParmAcc::getGblTbl() { return drMan->gblTbl; }

void ScnRenderDrSysParmAcc::setSpCapMode(s32 spCapMode) { drMan->setAvatarCapMode(spCapMode); }

s32 ScnRenderDrSysParmAcc::getSpCapMode() const { return 0; }

void ScnRenderDrSysParmAcc::setMdlHeightTexSkip(bool mdlHeightTexSkip) { drMan->mdlHeightTexSkip = mdlHeightTexSkip; }

bool ScnRenderDrSysParmAcc::isMdlHeightTexSkip() const { return drMan->mdlHeightTexSkip; }

void ScnRenderDrSysParmAcc::setSeamMapOpenMode(bool seamMapOpenMode) { drMan->seamMapOpenMode = seamMapOpenMode; }

bool ScnRenderDrSysParmAcc::isSeamMapOpenMode() const { return drMan->seamMapOpenMode; }

void ScnRenderDrSysParmAcc::setScreenDispOff(bool screenDispOff) { drMan->screenDispOff = screenDispOff; }

FILE_PRIO ScnRenderDrSysParmAcc::getSeamMapPriMdl() const { return drMan->seamMapPriMdl; }

FILE_PRIO ScnRenderDrSysParmAcc::getSeamMapPriColi() const { return drMan->seamMapPriColi; }

void ScnRenderDrSysParmAcc::setSeamMapPriMdl(FILE_PRIO seamMapPriMdl) { drMan->seamMapPriMdl = seamMapPriMdl; }

void ScnRenderDrSysParmAcc::setSeamMapPriColi(FILE_PRIO seamMapPriColi) { drMan->seamMapPriColi = seamMapPriColi; }

void *ScnRenderDrSysParmAcc::getBlurVelocityMap() {
  wkPixlManRes *resources = drMan->pixlMan->m_resources;
  DrBlurTarget *target = resources[viewIndex].blur->target;
  if (target != nullptr) {
    return target->velocityMap;
  }
  return nullptr;
}

void ScnRenderDrSysParmAcc::setCharDirShadow(bool charDirShadow) { postParm->charDirShadow = charDirShadow; }

bool ScnRenderDrSysParmAcc::isCharDirShadow() const { return postParm->charDirShadow; }

void ScnRenderDrSysParmAcc::setMdlDblPause(bool mdlDblPause) { drMan->mdlDblPause = mdlDblPause; }

bool ScnRenderDrSysParmAcc::isMdlDblPause() const { return drMan->mdlDblPause; }

bool ScnRenderDrSysParmAcc::isMdlAllMiddleTexStm() const { return drMan->isAllMiddelTexStmChk(); }

bool ScnRenderDrSysParmAcc::isSeamMapRead() const { return drMan->isSeamMapStmOk(); }

void ScnRenderDrSysParmAcc::setSeamReadLv(s32 seamReadLv) {
  if (seamReadLv < 0) {
    drMan->seamReadLv = 0;
  } else if (seamReadLv > 5) {
    drMan->seamReadLv = 5;
  } else {
    drMan->seamReadLv = seamReadLv;
  }
}

void ScnRenderDrSysParmAcc::setHeightTexSkip(bool heightTexSkip) { drMan->heightTexSkip = heightTexSkip; }

bool ScnRenderDrSysParmAcc::isHeightTexSkip() const { return drMan->heightTexSkip; }

void ScnRenderDrSysParmAcc::setSeamHeightTexSkip(bool seamHeightTexSkip) { drMan->seamHeightTexSkip = seamHeightTexSkip; }

bool ScnRenderDrSysParmAcc::isSeamHeightTexSkip() const { return drMan->seamHeightTexSkip; }

void ScnRenderDrSysParmAcc::setShadowStr(f32 shadowStr) { postParm->shadowStr = shadowStr; }

f32 ScnRenderDrSysParmAcc::getShadowStr() const { return postParm->shadowStr; }

void ScnRenderDrSysParmAcc::setShadowChacheAngle(f32 shadowChacheAngle) { postParm->shadowChacheAngle = shadowChacheAngle; }

f32 ScnRenderDrSysParmAcc::getShadowChacheAngle() const { return postParm->shadowChacheAngle; }

void ScnRenderDrSysParmAcc::callCubeMapRender(const DR_CAPCUBE_PARAM &param) { drMan->callCubeMapRender(param); }

bool ScnRenderDrSysParmAcc::getIrrVolIsValid() const { return drMan->irrVolMan->isValid(); }

const mm::Vec3 &ScnRenderDrSysParmAcc::getIrrVolCenterPos() const { return drMan->irrVolMan->centerPos; }

void ScnRenderDrSysParmAcc::setIrrVolCenterPos(const mm::Vec3 &irrVolCenterPos) {
  DrIrrVolMan *irrVolMan = drMan->irrVolMan;
  irrVolMan->requestCenterPos.x = irrVolCenterPos.x;
  irrVolMan->requestCenterPos.y = irrVolCenterPos.y;
  irrVolMan->requestCenterPos.z = irrVolCenterPos.z;
}

u32 ScnRenderDrSysParmAcc::getIrrVolCascadeMax() const {
  DrIrrVolMan *irrVolMan = drMan->irrVolMan;
  u32 cascadeNum = irrVolMan->cascadeNum;
  u32 cascadeMax = irrVolMan->setting->cascadeMax;
  return cascadeNum < cascadeMax ? cascadeNum : cascadeMax;
}

bool ScnRenderDrSysParmAcc::getIrrVolVolumeArea(u32 cascade, mm::Aabb &area) const { return drMan->irrVolMan->getVolumeArea(cascade, area); }

void ScnRenderDrSysParmAcc::setToonDirLightScale(bool toonDirLightScale) { drMan->toonDirLightScale = toonDirLightScale; }

void ScnRenderDrSysParmAcc::setToonAmbient(bool toonAmbient) {
  if (toonAmbient) {
    drMan->toonAmbient = 3;
  } else {
    drMan->toonAmbient = 0;
  }
}

void ScnRenderDrSysParmAcc::setDispChara(bool dispChara) { drMan->charaDispOff = !dispChara; }

bool ScnRenderDrSysParmAcc::isDispChara() const { return !drMan->charaDispOff; }

bool ScnRenderDrSysParmAcc::isDispGlobalIBLTex() const { return drMan->postParms[0]->dispGlobalIBLTex; }

void ScnRenderDrSysParmAcc::setDispGlobalIBLTex(bool dispGlobalIBLTex) { drMan->postParms[0]->dispGlobalIBLTex = dispGlobalIBLTex; }

void ScnRenderDrSysParmAcc::setPlayerPos(const mm::Vec3 &playerPos) {}

void ScnRenderDrSysParmAcc::setCameraLight(bool cameraLight) { drMan->cameraLight = cameraLight; }

void ScnRenderDrSysParmAcc::setGBuffDebug(bool gBuffDebug) { drMan->postParms[0]->gBuffDebug = gBuffDebug; }

void ScnRenderDrSysParmAcc::setGBuffDebugParam(GBuffDebugType type, f32 min, f32 max) {
  DrPixlPostParm *firstPostParm = drMan->postParms[0];
  switch (static_cast<s32>(type)) {
  case 0:
    firstPostParm->gBuffDebugRanges[0].min = min;
    firstPostParm->gBuffDebugRanges[0].max = max;
    break;
  case 1:
    firstPostParm->gBuffDebugRanges[1].min = min;
    firstPostParm->gBuffDebugRanges[1].max = max;
    break;
  case 2:
    firstPostParm->gBuffDebugRanges[2].min = min;
    firstPostParm->gBuffDebugRanges[2].max = max;
    break;
  case 3:
    firstPostParm->gBuffDebugRanges[3].min = min;
    firstPostParm->gBuffDebugRanges[3].max = max;
    break;
  case 4:
    firstPostParm->gBuffDebugRanges[4].min = min;
    firstPostParm->gBuffDebugRanges[4].max = max;
    break;
  }
}

void ScnRenderDrSysParmAcc::deleteAddRenderView(ScnRenderDrViewCtrl *viewCtrl) { drMan->deleteAddRenderSystem(viewCtrl->viewId + 1); }

void ScnRenderDrSysParmAcc::resetModelTexture(u32 index) { drMan->resetModelTexture(index); }

void ScnRenderDrSysParmAcc::setDefferedColor(bool defferedColor) { drMan->postParms[0]->defferedColor = defferedColor; }

bool ScnRenderDrSysParmAcc::isDefferedColor() const { return drMan->postParms[0]->defferedColor; }

void ScnRenderDrSysParmAcc::setRenderSpecMode(RenderSpecMode renderSpecMode) { drMan->renderSpecMode = renderSpecMode; }

void ScnRenderDrSysParmAcc::setGlassBr(bool glassBr, u32 type) { postParm->setGlassBrk(glassBr, type); }

bool ScnRenderDrSysParmAcc::isGlassBr() { return postParm->glassBr; }

void ScnRenderDrSysParmAcc::setCacherClearMode(bool cacherClearMode) { drMan->setCacherClearMode(cacherClearMode); }

bool ScnRenderDrSysParmAcc::isViewRenderSkip(u32 view) const { return (DrMan::get()->viewRenderSkip & (1 << view)) != 0; }

void ScnRenderDrSysParmAcc::setViewRenderSkip(u32 view, bool skip) {
  DrMan *drMan = DrMan::get();
  if (skip) {
    drMan->viewRenderSkip |= 1 << view;
  } else {
    drMan->viewRenderSkip &= ~(1 << view);
  }
}

void ScnRenderDrSysParmAcc::setWriteZBuffer(bool writeZBuffer) { DrMan::get()->writeZBuffer = writeZBuffer; }

void ScnRenderDrSysParmAcc::resetScene() { postParm->resetScene(); }

void ScnRenderDrSysParmAcc::setAutoResetScene(bool autoResetScene) { DrMan::get()->autoResetScene = autoResetScene; }

f32 ScnRenderDrSysParmAcc::getGamma() const { return DrMan::get()->gamma; }

void ScnRenderDrSysParmAcc::setGamma(f32 gamma) { DrMan::get()->gamma = gamma; }

void ScnRenderDrSysParmAcc::setCaptureMode(bool captureMode) {
  DrMan *instance = DrMan::get();
  s32 index = DrMan::s_nDblStockIdx;
  instance->captureModes[index] = captureMode ? 1 : 2;
}

} // namespace ml
