#include "scn/scn_render_dr_sys_parm_acc.h"

#include "cloud/cloud_man.h"
#include "dr/dr_irr_vol_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_motion_blur.h"
#include "dr/dr_pixl_post_parm.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_render_dr_sys.h"

namespace mm {
struct Aabb;
} // namespace mm

namespace ml {
struct DR_CAPCUBE_PARAM;

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc() : unknown00(nullptr), unknown08(nullptr), unknown10(0) {
  unknown00 = DrMan::get();
  unknown08 = unknown00->unknown120[unknown10];
}

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc(ScnRenderDrSys *drSys, s32 index) : unknown00(nullptr), unknown08(nullptr) { setDrSys(drSys, index); }

void ScnRenderDrSysParmAcc::setDrSys(ScnRenderDrSys *drSys, s32 index) {
  unknown00 = drSys->unknown10;
  unknown08 = unknown00->unknown120[index];
  unknown10 = index;
}

void ScnRenderDrSysParmAcc::setDOFOverride(bool dofOverride) { unknown08->setOverrideDOF(dofOverride); }

void ScnRenderDrSysParmAcc::setGlbSpd(f32 glbSpd) { unknown00->unknown1c84 = glbSpd; }

f32 ScnRenderDrSysParmAcc::getGlbSpd() const { return unknown00->unknown1c84; }

void ScnRenderDrSysParmAcc::setMdlSpd(f32 mdlSpd) { unknown00->unknown1c88 = mdlSpd; }

f32 ScnRenderDrSysParmAcc::getMdlSpd() const { return unknown00->unknown1c88; }

void ScnRenderDrSysParmAcc::setToneMap(bool toneMap) { unknown08->m_toneMapOn = toneMap; }

bool ScnRenderDrSysParmAcc::isToneMap() const { return unknown08->getToneMapOn(); }

void ScnRenderDrSysParmAcc::setToneMax(f32 toneMax) { unknown08->unknown08 = toneMax; }

void ScnRenderDrSysParmAcc::setToneMin(f32 toneMin) { unknown08->unknown0c = toneMin; }

void ScnRenderDrSysParmAcc::setToneRatio(f32 toneRatio) { unknown08->unknown10 = toneRatio; }

void ScnRenderDrSysParmAcc::setToneRatioLast(f32 toneRatioLast) { unknown08->unknown14 = toneRatioLast; }

void ScnRenderDrSysParmAcc::setOverrideToneMap(f32 overrideToneMap) { unknown08->setOverrideToneMap(overrideToneMap); }

void ScnRenderDrSysParmAcc::setToneBlmMax(f32 toneBlmMax) { unknown08->unknown18 = toneBlmMax; }

void ScnRenderDrSysParmAcc::setToneBlmMin(f32 toneBlmMin) { unknown08->unknown1c = toneBlmMin; }

void ScnRenderDrSysParmAcc::setToneBlmRatio(f32 toneBlmRatio) { unknown08->unknown20 = toneBlmRatio; }

void ScnRenderDrSysParmAcc::setToneBlmRatioLast(f32 toneBlmRatioLast) { unknown08->unknown24 = toneBlmRatioLast; }

void ScnRenderDrSysParmAcc::setBloom(bool bloom) { unknown08->m_bloomOn = bloom; }

bool ScnRenderDrSysParmAcc::isBloomOn() const { return unknown08->getBloomOn(); }

void ScnRenderDrSysParmAcc::setBorderBlmSub(f32 borderBlmSub) { unknown08->unknown40 = borderBlmSub; }

void ScnRenderDrSysParmAcc::setBorderBlmMul(f32 borderBlmMul) { unknown08->m_borderBlmMul = borderBlmMul; }

void ScnRenderDrSysParmAcc::setBorderBlmSecSub(f32 borderBlmSecSub) { unknown08->unknown48 = borderBlmSecSub; }

void ScnRenderDrSysParmAcc::setBorderBlmSecMul(f32 borderBlmSecMul) { unknown08->unknown4c = borderBlmSecMul; }

void ScnRenderDrSysParmAcc::setBorderBlmMax(f32 borderBlmMax) { unknown08->unknown50 = borderBlmMax; }

void ScnRenderDrSysParmAcc::setBlmWeight(f32 x, f32 y, f32 z) {
  f32 *blmWeight = unknown08->unknown54;
  blmWeight[0] = x;
  blmWeight[1] = y;
  blmWeight[2] = z;
}

void ScnRenderDrSysParmAcc::setBlmStr(f32 x, f32 y, f32 z) {
  f32 *blmStr = unknown08->unknown7c;
  blmStr[0] = x;
  blmStr[1] = y;
  blmStr[2] = z;
}

void ScnRenderDrSysParmAcc::setBlmGauss(f32 x, f32 y, f32 z) {
  f32 *blmGauss = unknown08->unknown90;
  blmGauss[0] = x;
  blmGauss[1] = y;
  blmGauss[2] = z;
}

f32 ScnRenderDrSysParmAcc::getBorderBlmSub() const { return unknown08->unknown40; }

f32 ScnRenderDrSysParmAcc::getBorderBlmMul() const { return unknown08->getBorderBlmMul(); }

f32 ScnRenderDrSysParmAcc::getBorderBlmSecSub() const { return unknown08->unknown48; }

f32 ScnRenderDrSysParmAcc::getBorderBlmSecMul() const { return unknown08->unknown4c; }

f32 ScnRenderDrSysParmAcc::getBorderBlmMax() const { return unknown08->unknown50; }

const f32 *ScnRenderDrSysParmAcc::getBlmWeight() const { return unknown08->unknown54; }

const f32 *ScnRenderDrSysParmAcc::getBlmStr() const { return unknown08->unknown7c; }

const f32 *ScnRenderDrSysParmAcc::getBlmGauss() const { return unknown08->unknown90; }

void ScnRenderDrSysParmAcc::setLensFlare(bool lensFlare) { unknown08->unknown3e = lensFlare; }

bool ScnRenderDrSysParmAcc::isLensFlare() const { return unknown08->unknown3e; }

void ScnRenderDrSysParmAcc::setBlmLensSub(f32 blmLensSub) { unknown08->unknownc8 = blmLensSub; }

void ScnRenderDrSysParmAcc::setBlmLensMul(f32 blmLensMul) { unknown08->unknowncc = blmLensMul; }

void ScnRenderDrSysParmAcc::setBlmLensMax(s32 blmLensMax) { unknown08->unknownd0 = blmLensMax; }

void ScnRenderDrSysParmAcc::setBlmLensRot(f32 blmLensRot) { unknown08->unknownd4 = blmLensRot; }

void ScnRenderDrSysParmAcc::setBlmLensWeight(f32 blmLensWeight) { unknown08->unknownd8 = blmLensWeight; }

void ScnRenderDrSysParmAcc::setBlmLensDecay(f32 blmLensDecay) { unknown08->unknowndc = blmLensDecay; }

void ScnRenderDrSysParmAcc::setBlmLensStrength(f32 blmLensStrength) { unknown08->unknowne0 = blmLensStrength; }

void ScnRenderDrSysParmAcc::setBlmLensParmMax(f32 blmLensParmMax) { unknown08->unknowne4 = blmLensParmMax; }

void ScnRenderDrSysParmAcc::setBlmLensUVDecay(f32 blmLensUVDecay) { unknown08->unknowne8 = blmLensUVDecay; }

f32 ScnRenderDrSysParmAcc::getBlmLensSub() const { return unknown08->unknownc8; }

f32 ScnRenderDrSysParmAcc::getBlmLensMul() const { return unknown08->unknowncc; }

s32 ScnRenderDrSysParmAcc::getBlmLensMax() const { return unknown08->unknownd0; }

f32 ScnRenderDrSysParmAcc::getBlmLensRot() const { return unknown08->unknownd4; }

f32 ScnRenderDrSysParmAcc::getBlmLensWeight() const { return unknown08->unknownd8; }

f32 ScnRenderDrSysParmAcc::getBlmLensDecay() const { return unknown08->unknowndc; }

f32 ScnRenderDrSysParmAcc::getBlmLensStrength() const { return unknown08->unknowne0; }

f32 ScnRenderDrSysParmAcc::getBlmLensParmMax() const { return unknown08->unknowne4; }

f32 ScnRenderDrSysParmAcc::getBlmLensUVDecay() const { return unknown08->unknowne8; }

void ScnRenderDrSysParmAcc::setGodRay(bool godRay) { unknown08->unknownec = godRay; }

bool ScnRenderDrSysParmAcc::isGodRay() const { return unknown08->unknownec; }

void ScnRenderDrSysParmAcc::setGodRayWeight(f32 godRayWeight) { unknown08->unknownf0 = godRayWeight; }

void ScnRenderDrSysParmAcc::setGodRayDecay(f32 godRayDecay) { unknown08->unknownf4 = godRayDecay; }

void ScnRenderDrSysParmAcc::setGodRayStrength(f32 godRayStrength) { unknown08->unknownf8 = godRayStrength; }

f32 ScnRenderDrSysParmAcc::getGodRayWeight() const { return unknown08->unknownf0; }

f32 ScnRenderDrSysParmAcc::getGodRayDecay() const { return unknown08->unknownf4; }

f32 ScnRenderDrSysParmAcc::getGodRayStrength() const { return unknown08->unknownf8; }

void ScnRenderDrSysParmAcc::setAA(bool aa) { unknown08->m_AAOn = aa; }

bool ScnRenderDrSysParmAcc::isAA() const { return unknown08->getAAOn(); }

void ScnRenderDrSysParmAcc::setAAEdgeSharpness(f32 aaEdgeSharpness) { unknown08->unknown100 = aaEdgeSharpness; }

void ScnRenderDrSysParmAcc::setAAEdgeThreshold(f32 aaEdgeThreshold) { unknown08->unknown104 = aaEdgeThreshold; }

void ScnRenderDrSysParmAcc::setAAEdgeThresholdMin(f32 aaEdgeThresholdMin) { unknown08->unknown108 = aaEdgeThresholdMin; }

void ScnRenderDrSysParmAcc::setAAEdgeRanges(f32 aaEdgeRanges) { unknown08->unknown10c = aaEdgeRanges; }

f32 ScnRenderDrSysParmAcc::getAAEdgeSharpness() const { return unknown08->unknown100; }

f32 ScnRenderDrSysParmAcc::getAAEdgeThreshold() const { return unknown08->unknown104; }

f32 ScnRenderDrSysParmAcc::getAAEdgeThresholdMin() const { return unknown08->unknown108; }

f32 ScnRenderDrSysParmAcc::getAAEdgeRanges() const { return unknown08->unknown10c; }

void ScnRenderDrSysParmAcc::setSSAO(bool ssao) { unknown08->unknown194 = ssao; }

bool ScnRenderDrSysParmAcc::isSSAO() const { return unknown08->unknown194; }

void ScnRenderDrSysParmAcc::setSSAOBlurStr(f32 ssaoBlurStr) { unknown08->unknown19c = ssaoBlurStr; }

f32 ScnRenderDrSysParmAcc::getSSAOBlurStr() const { return unknown08->unknown19c; }

void ScnRenderDrSysParmAcc::setSpecularStr(f32 specularStr) { unknown08->unknown470 = specularStr; }

f32 ScnRenderDrSysParmAcc::getSpecularStr() const { return unknown08->unknown470; }

void ScnRenderDrSysParmAcc::setMotBlurOverride(bool motBlurOverride) { unknown08->setOverrideMotBlur(motBlurOverride); }

void ScnRenderDrSysParmAcc::setMotBlur(bool motBlur) { unknown08->unknown1ca = motBlur; }

void ScnRenderDrSysParmAcc::setMotBlurDefault(bool motBlurDefault) { unknown00->unknown70->unknownb6c = motBlurDefault; }

void ScnRenderDrSysParmAcc::setAppBlur(bool appBlur) { unknown08->unknown1ce = appBlur; }

void ScnRenderDrSysParmAcc::setSpBlur(bool spBlur) { unknown08->unknown1d0 = spBlur; }

void ScnRenderDrSysParmAcc::setSpBlurTarget(const mm::Vec3 &spBlurTarget) {
  mm::Vec3 &destination = unknown08->unknownff0;
  destination.x = spBlurTarget.x;
  destination.y = spBlurTarget.y;
  destination.z = spBlurTarget.z;
}

void ScnRenderDrSysParmAcc::setBlurSpParm(f32 blurSpParm) { unknown08->unknown1f0 = blurSpParm; }

bool ScnRenderDrSysParmAcc::isMotBlur() const { return unknown08->isMotBlur(); }

void ScnRenderDrSysParmAcc::setMotBlurStrength(f32 motBlurStrength) { unknown08->unknown1d4 = motBlurStrength; }

void ScnRenderDrSysParmAcc::setMotBlurSub(f32 motBlurSub) { unknown08->unknown1d8 = motBlurSub; }

f32 ScnRenderDrSysParmAcc::getBlurStrength() const { return unknown08->unknown1d4; }

f32 ScnRenderDrSysParmAcc::getBlurSub() const { return unknown08->unknown1d8; }

void ScnRenderDrSysParmAcc::setDOF(bool dof) { unknown08->setDOF(dof); }

bool ScnRenderDrSysParmAcc::isDOF() const { return unknown08->unknown218 || unknown08->unknown219; }

void ScnRenderDrSysParmAcc::setDoFPixlRatio(f32 dofPixlRatio) { unknown08->setDoFPixlRatio(dofPixlRatio); }

void ScnRenderDrSysParmAcc::setDoFDistance(f32 dofDistance) { unknown08->setDoFDistance(dofDistance); }

void ScnRenderDrSysParmAcc::setDoFRange(f32 dofRange) { unknown08->setDoFRange(dofRange); }

void ScnRenderDrSysParmAcc::setDoFStrength(f32 dofStrength) { unknown08->setDoFStrength(dofStrength); }

void ScnRenderDrSysParmAcc::setDoFLens(f32 dofLens) { unknown08->setDoFLens(dofLens); }

void ScnRenderDrSysParmAcc::setDoFBlend(f32 dofBlend) { unknown08->setDoFBlend(dofBlend); }

void ScnRenderDrSysParmAcc::setDofHLvMode(bool dofHLvMode) { unknown08->setDOFHlv(dofHLvMode); }

void ScnRenderDrSysParmAcc::setDOFAutoFocus(bool dofAutoFocus) { unknown08->setDOFAutoFocus(dofAutoFocus); }

void ScnRenderDrSysParmAcc::setDOFFocusNum(s32 dofFocusNum) {
  if (dofFocusNum < 0 || dofFocusNum > 11) {
    dofFocusNum = 0;
  }
  unknown08->setDoFocusNum(dofFocusNum);
}

void ScnRenderDrSysParmAcc::setDOFFocusMin(f32 dofFocusMin) { unknown08->setDofFocusMin(dofFocusMin); }

void ScnRenderDrSysParmAcc::setDOFFocusRatio(f32 dofFocusRatio) { unknown08->setDoFDofFocusRat(dofFocusRatio); }

void ScnRenderDrSysParmAcc::setDOFFocusDebug(bool dofFocusDebug) { unknown08->setDOFAutoFocusDebug(dofFocusDebug); }

f32 ScnRenderDrSysParmAcc::getDoFPixlRatio() const { return unknown08->unknown220; }

f32 ScnRenderDrSysParmAcc::getDoFDistance() const { return unknown08->unknown224; }

f32 ScnRenderDrSysParmAcc::getDoFRange() const { return unknown08->unknown228; }

f32 ScnRenderDrSysParmAcc::getDoFStrength() const { return unknown08->unknown22c; }

f32 ScnRenderDrSysParmAcc::getDoFLens() const { return unknown08->unknown230; }

f32 ScnRenderDrSysParmAcc::getDoFBlend() const { return unknown08->unknown234; }

bool ScnRenderDrSysParmAcc::isDofHLvMode() const { return unknown08->unknown21a; }

s32 ScnRenderDrSysParmAcc::getDofPixlLv() const { return unknown08->unknown238; }

bool ScnRenderDrSysParmAcc::isDOFAutoFocus() const { return unknown08->unknown21c; }

s32 ScnRenderDrSysParmAcc::getDOFFocusNum() const { return unknown08->unknown23c; }

f32 ScnRenderDrSysParmAcc::getDOFFocusMin() const { return unknown08->unknown244; }

f32 ScnRenderDrSysParmAcc::getDOFFocusRatio() const { return unknown08->unknown240; }

bool ScnRenderDrSysParmAcc::isDOFFocusDebug() const { return unknown08->unknown21e; }

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

void ScnRenderDrSysParmAcc::setGlobalWind(const mm::Vec3 &globalWind) { unknown00->setGlobalWind(globalWind); }

void ScnRenderDrSysParmAcc::setReduction(bool reduction) { unknown08->unknownfb2 = reduction; }

bool ScnRenderDrSysParmAcc::isReduction() const { return unknown08->unknownfb2; }

void ScnRenderDrSysParmAcc::setAutoReduction(bool autoReduction) { unknown00->setAutoReduction(autoReduction); }

void ScnRenderDrSysParmAcc::setReductionScX(f32 reductionScX) { unknown08->unknownfb8 = reductionScX; }

void ScnRenderDrSysParmAcc::setReductionScY(f32 reductionScY) { unknown08->unknownfbc = reductionScY; }

f32 ScnRenderDrSysParmAcc::getReductionScX() const { return unknown08->unknownfb8; }

f32 ScnRenderDrSysParmAcc::getReductionScY() const { return unknown08->unknownfbc; }

bool ScnRenderDrSysParmAcc::isDispReduction() const { return unknown08->unknown10fe; }

void ScnRenderDrSysParmAcc::setDispReduction(bool dispReduction) { unknown08->unknown10fe = dispReduction; }

void ScnRenderDrSysParmAcc::setGroupsDisp(s32 group, bool disp) { unknown00->setGroupsDisp(group, disp); }

void ScnRenderDrSysParmAcc::setColorFilterOverride(bool colorFilterOverride) { unknown08->setOverrideColorFilter(colorFilterOverride); }

void ScnRenderDrSysParmAcc::setColorFilterNum(s32 colorFilterNum) { unknown08->setColorFilterNum(colorFilterNum); }

void ScnRenderDrSysParmAcc::setColorFilterFarNum(s32 colorFilterFarNum) { unknown08->setColorFilterFarNum(colorFilterFarNum); }

void ScnRenderDrSysParmAcc::setColorFilterFrm(f32 colorFilterFrm) { unknown08->setColorFilterFrm(colorFilterFrm); }

f32 ScnRenderDrSysParmAcc::getColorFilterFrm() const { return unknown08->unknown270; }

void ScnRenderDrSysParmAcc::setRainDrop(bool rainDrop) { unknown08->m_rainDropOn = rainDrop; }

bool ScnRenderDrSysParmAcc::getRainDrop() const { return unknown08->getRainDropOn(); }

void ScnRenderDrSysParmAcc::setLightNum(s32 lightNum) { unknown08->unknown107c = lightNum; }

s32 ScnRenderDrSysParmAcc::getLightNum() const { return unknown08->unknown107c; }

void ScnRenderDrSysParmAcc::setInOut(bool inOut) { unknown08->unknown1080 = inOut; }

bool ScnRenderDrSysParmAcc::isInOut() const { return unknown08->unknown1080; }

void ScnRenderDrSysParmAcc::setTimeVal(f32 timeVal) { unknown00->setTimeVal(timeVal); }

f32 ScnRenderDrSysParmAcc::getTimerVal() const { return unknown00->unknown1cac; }

void ScnRenderDrSysParmAcc::setWeather(s32 weather) { unknown08->unknown1084 = weather; }

s32 ScnRenderDrSysParmAcc::getWeather() const { return unknown08->unknown1084; }

void ScnRenderDrSysParmAcc::setWeatherFrame(f32 weatherFrame) { unknown08->setWeatherFrame(weatherFrame); }

f32 ScnRenderDrSysParmAcc::getWeatherFrame() const { return unknown08->getWeatherFrame(); }

void ScnRenderDrSysParmAcc::setSeamMapAddPosMode(bool seamMapAddPosMode) { unknown00->unknown1c80 = seamMapAddPosMode; }

void ScnRenderDrSysParmAcc::setSeamMapReadPos(const mm::Vec3 &seamMapReadPos) {
  mm::Vec3 &destination = unknown00->unknown1c70;
  destination.x = seamMapReadPos.x;
  destination.y = seamMapReadPos.y;
  destination.z = seamMapReadPos.z;
}

void ScnRenderDrSysParmAcc::releaseFastLight() { unknown00->releaseFastLight(unknown10); }

u32 ScnRenderDrSysParmAcc::isGblId(s32 id) {
  u32 *gblTbl = unknown00->unknown1d20;
  return gblTbl[id >> 5] & (1 << (id & 31));
}

void ScnRenderDrSysParmAcc::setSelectIdDisp(s32 id, bool disp) {
  if (disp) {
    unknown00->offGblIdx(id);
  } else {
    unknown00->setGblIdx(id);
  }
}

void ScnRenderDrSysParmAcc::setPlayAnime(s32 id, bool play, bool loop) {}

bool ScnRenderDrSysParmAcc::isSelectIdDisp(s32 id) { return isGblId(id) == 0; }

bool ScnRenderDrSysParmAcc::isPlayAnime(s32 id) { return false; }

void ScnRenderDrSysParmAcc::setClip(bool clip) { unknown00->unknown1d80 = clip; }

void ScnRenderDrSysParmAcc::setFogSkip(bool fogSkip) { unknown00->unknown1d71 = fogSkip; }

u32 *ScnRenderDrSysParmAcc::getGblTbl() { return unknown00->unknown1d20; }

void ScnRenderDrSysParmAcc::setSpCapMode(s32 spCapMode) { unknown00->setAvatarCapMode(spCapMode); }

s32 ScnRenderDrSysParmAcc::getSpCapMode() const { return 0; }

void ScnRenderDrSysParmAcc::setMdlHeightTexSkip(bool mdlHeightTexSkip) { unknown00->unknown1cc4 = mdlHeightTexSkip; }

bool ScnRenderDrSysParmAcc::isMdlHeightTexSkip() const { return unknown00->unknown1cc4; }

void ScnRenderDrSysParmAcc::setSeamMapOpenMode(bool seamMapOpenMode) { unknown00->unknown1cc7 = seamMapOpenMode; }

bool ScnRenderDrSysParmAcc::isSeamMapOpenMode() const { return unknown00->unknown1cc7; }

void ScnRenderDrSysParmAcc::setScreenDispOff(bool screenDispOff) { unknown00->unknown1cc8 = screenDispOff; }

FILE_PRIO ScnRenderDrSysParmAcc::getSeamMapPriMdl() const { return unknown00->unknown1d94; }

FILE_PRIO ScnRenderDrSysParmAcc::getSeamMapPriColi() const { return unknown00->unknown1d98; }

void ScnRenderDrSysParmAcc::setSeamMapPriMdl(FILE_PRIO seamMapPriMdl) { unknown00->unknown1d94 = seamMapPriMdl; }

void ScnRenderDrSysParmAcc::setSeamMapPriColi(FILE_PRIO seamMapPriColi) { unknown00->unknown1d98 = seamMapPriColi; }

void *ScnRenderDrSysParmAcc::getBlurVelocityMap() {
  wkPixlManRes *resources = unknown00->unknown78->unknown10;
  DrPixlPostObjMotionBlur *motionBlur = resources[unknown10].unknown180->unknown50;
  if (motionBlur != nullptr) {
    return motionBlur->unknown28;
  }
  return nullptr;
}

void ScnRenderDrSysParmAcc::setCharDirShadow(bool charDirShadow) { unknown08->unknown103e = charDirShadow; }

bool ScnRenderDrSysParmAcc::isCharDirShadow() const { return unknown08->unknown103e; }

void ScnRenderDrSysParmAcc::setMdlDblPause(bool mdlDblPause) { unknown00->unknown1d7b = mdlDblPause; }

bool ScnRenderDrSysParmAcc::isMdlDblPause() const { return unknown00->unknown1d7b; }

bool ScnRenderDrSysParmAcc::isMdlAllMiddleTexStm() const { return unknown00->isAllMiddelTexStmChk(); }

bool ScnRenderDrSysParmAcc::isSeamMapRead() const { return unknown00->isSeamMapStmOk(); }

void ScnRenderDrSysParmAcc::setSeamReadLv(s32 seamReadLv) {
  if (seamReadLv < 0) {
    unknown00->unknown1cfc = 0;
  } else if (seamReadLv > 5) {
    unknown00->unknown1cfc = 5;
  } else {
    unknown00->unknown1cfc = seamReadLv;
  }
}

void ScnRenderDrSysParmAcc::setHeightTexSkip(bool heightTexSkip) { unknown00->unknown1cc5 = heightTexSkip; }

bool ScnRenderDrSysParmAcc::isHeightTexSkip() const { return unknown00->unknown1cc5; }

void ScnRenderDrSysParmAcc::setSeamHeightTexSkip(bool seamHeightTexSkip) { unknown00->unknown1cc6 = seamHeightTexSkip; }

bool ScnRenderDrSysParmAcc::isSeamHeightTexSkip() const { return unknown00->unknown1cc6; }

void ScnRenderDrSysParmAcc::setShadowStr(f32 shadowStr) { unknown08->unknown360 = shadowStr; }

f32 ScnRenderDrSysParmAcc::getShadowStr() const { return unknown08->unknown360; }

void ScnRenderDrSysParmAcc::setShadowChacheAngle(f32 shadowChacheAngle) { unknown08->unknown37c = shadowChacheAngle; }

f32 ScnRenderDrSysParmAcc::getShadowChacheAngle() const { return unknown08->unknown37c; }

void ScnRenderDrSysParmAcc::callCubeMapRender(const DR_CAPCUBE_PARAM &param) { unknown00->callCubeMapRender(param); }

bool ScnRenderDrSysParmAcc::getIrrVolIsValid() const { return unknown00->unknown90->isValid(); }

const mm::Vec3 &ScnRenderDrSysParmAcc::getIrrVolCenterPos() const { return unknown00->unknown90->unknown1a0; }

void ScnRenderDrSysParmAcc::setIrrVolCenterPos(const mm::Vec3 &irrVolCenterPos) {
  DrIrrVolMan *irrVolMan = unknown00->unknown90;
  irrVolMan->unknown190.x = irrVolCenterPos.x;
  irrVolMan->unknown190.y = irrVolCenterPos.y;
  irrVolMan->unknown190.z = irrVolCenterPos.z;
}

u32 ScnRenderDrSysParmAcc::getIrrVolCascadeMax() const {
  DrIrrVolMan *irrVolMan = unknown00->unknown90;
  u32 cascadeNum = irrVolMan->unknown1c4;
  u32 cascadeMax = irrVolMan->unknown08->unknown20;
  return cascadeNum < cascadeMax ? cascadeNum : cascadeMax;
}

bool ScnRenderDrSysParmAcc::getIrrVolVolumeArea(u32 cascade, mm::Aabb &area) const { return unknown00->unknown90->getVolumeArea(cascade, area); }

void ScnRenderDrSysParmAcc::setToonDirLightScale(bool toonDirLightScale) { unknown00->unknown1e08 = toonDirLightScale; }

void ScnRenderDrSysParmAcc::setToonAmbient(bool toonAmbient) {
  if (toonAmbient) {
    unknown00->unknown1e0c = 3;
  } else {
    unknown00->unknown1e0c = 0;
  }
}

void ScnRenderDrSysParmAcc::setDispChara(bool dispChara) { unknown00->unknown1d60 = !dispChara; }

bool ScnRenderDrSysParmAcc::isDispChara() const { return !unknown00->unknown1d60; }

bool ScnRenderDrSysParmAcc::isDispGlobalIBLTex() const { return unknown00->unknown120[0]->unknown248; }

void ScnRenderDrSysParmAcc::setDispGlobalIBLTex(bool dispGlobalIBLTex) { unknown00->unknown120[0]->unknown248 = dispGlobalIBLTex; }

void ScnRenderDrSysParmAcc::setPlayerPos(const mm::Vec3 &playerPos) {}

void ScnRenderDrSysParmAcc::setCameraLight(bool cameraLight) { unknown00->unknown1da0 = cameraLight; }

void ScnRenderDrSysParmAcc::setGBuffDebug(bool gBuffDebug) { unknown00->unknown120[0]->unknown488 = gBuffDebug; }

void ScnRenderDrSysParmAcc::setGBuffDebugParam(GBuffDebugType type, f32 min, f32 max) {
  DrPixlPostParm *firstPostParm = unknown00->unknown120[0];
  switch (static_cast<s32>(type)) {
  case 0:
    firstPostParm->unknown320[0].unknown00 = min;
    firstPostParm->unknown320[0].unknown04 = max;
    break;
  case 1:
    firstPostParm->unknown320[1].unknown00 = min;
    firstPostParm->unknown320[1].unknown04 = max;
    break;
  case 2:
    firstPostParm->unknown320[2].unknown00 = min;
    firstPostParm->unknown320[2].unknown04 = max;
    break;
  case 3:
    firstPostParm->unknown320[3].unknown00 = min;
    firstPostParm->unknown320[3].unknown04 = max;
    break;
  case 4:
    firstPostParm->unknown320[4].unknown00 = min;
    firstPostParm->unknown320[4].unknown04 = max;
    break;
  }
}

void ScnRenderDrSysParmAcc::deleteAddRenderView(ScnRenderDrViewCtrl *viewCtrl) { unknown00->deleteAddRenderSystem(viewCtrl->unknown08 + 1); }

void ScnRenderDrSysParmAcc::resetModelTexture(u32 index) { unknown00->resetModelTexture(index); }

void ScnRenderDrSysParmAcc::setDefferedColor(bool defferedColor) { unknown00->unknown120[0]->unknown304 = defferedColor; }

bool ScnRenderDrSysParmAcc::isDefferedColor() const { return unknown00->unknown120[0]->unknown304; }

void ScnRenderDrSysParmAcc::setRenderSpecMode(RenderSpecMode renderSpecMode) { unknown00->unknown1d28 = renderSpecMode; }

void ScnRenderDrSysParmAcc::setGlassBr(bool glassBr, u32 type) { unknown08->setGlassBrk(glassBr, type); }

bool ScnRenderDrSysParmAcc::isGlassBr() { return unknown08->unknown4d0; }

void ScnRenderDrSysParmAcc::setCacherClearMode(bool cacherClearMode) { unknown00->setCacherClearMode(cacherClearMode); }

bool ScnRenderDrSysParmAcc::isViewRenderSkip(u32 view) const { return (DrMan::get()->unknown1c9c & (1 << view)) != 0; }

void ScnRenderDrSysParmAcc::setViewRenderSkip(u32 view, bool skip) {
  DrMan *drMan = DrMan::get();
  if (skip) {
    drMan->unknown1c9c |= 1 << view;
  } else {
    drMan->unknown1c9c &= ~(1 << view);
  }
}

void ScnRenderDrSysParmAcc::setWriteZBuffer(bool writeZBuffer) { DrMan::get()->unknown1cc9 = writeZBuffer; }

void ScnRenderDrSysParmAcc::resetScene() { unknown08->resetScene(); }

void ScnRenderDrSysParmAcc::setAutoResetScene(bool autoResetScene) { DrMan::get()->unknown1cc1 = autoResetScene; }

f32 ScnRenderDrSysParmAcc::getGamma() const { return DrMan::get()->unknown1c90; }

void ScnRenderDrSysParmAcc::setGamma(f32 gamma) { DrMan::get()->unknown1c90 = gamma; }

void ScnRenderDrSysParmAcc::setCaptureMode(bool captureMode) {
  DrMan *instance = DrMan::get();
  s32 index = DrMan::s_nDblStockIdx;
  instance->unknown1c81[index] = captureMode ? 1 : 2;
}

} // namespace ml
