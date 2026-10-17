#include "dr/dr_pixl_post_parm.h"

#include "dr/dr_man.h"

namespace ml {

bool DrPixlPostParm::isShwRaytrace() const { return shwRaytrace; }

void DrPixlPostParm::calcReductionTransBuffer(int &width, int &height) const {
  width = width * reductionTransScX;
  height = height * reductionTransScY;
}

void DrPixlPostParm::setDOF(bool dof) { dblParms[DrMan::s_nDblIdx].dof = dof; }

bool DrPixlPostParm::getTMAAOn() const { return tmaa; }

bool DrPixlPostParm::isMotBlur2() const { return motBlur2; }

bool DrPixlPostParm::getBloomOn() const { return bloom; }

bool DrPixlPostParm::getToneMapOn() const { return toneMap; }

void DrPixlPostParm::update() {
  if (attriMenuClosed) {
    attriMenuClosed = false;
  }
}

bool DrPixlPostParm::getAAOn() const { return aa; }

bool DrPixlPostParm::getColTblOn() const { return colorFilter; }

f32 DrPixlPostParm::getBorderBlmMul() const { return borderBlmMul; }

DrPixlPostParm *DrPixlPostParm::get() { return s_pIns; }

void DrPixlPostParm::setInst() { s_pIns = this; }

DrPixlPostParm::DrPixlPostParm() { reset(); }

DrPixlPostParm::~DrPixlPostParm() {}

DrPixlPostParm &DrPixlPostParm::operator=(const DrPixlPostParm &parm) {
  __builtin_memcpy(this, &parm, sizeof(DrPixlPostParm));
  return *this;
}

void DrPixlPostParm::calcOfsRenderCheck(f32 x, f32 y) { ofsRenderCheck = static_cast<u32>(x * 100.0f) | static_cast<u32>(y * 100.0f) << 8; }

void DrPixlPostParm::calcReductionBuffer(int &width, int &height) {
  if (reductionBuffer) {
    width = static_cast<int>(width * reductionBufferScX);
    height = static_cast<int>(height * reductionBufferScY);
    width += -width & 7;
    height += -height & 7;
  }
}

void DrPixlPostParm::setOverrideToneMap(f32 overrideToneMap) {
  DrPixlPostDblParm &parm = dblParms[DrMan::s_nDblIdx];
  parm.overrideToneMap = true;
  parm.toneMap = overrideToneMap;
}

f32 DrPixlPostParm::getToonDirLightScale() const {
  if (DrMan::getIns()->toonDirLightScale) {
    return toonDirLightScale;
  }
  return 1.0f;
}

void DrPixlPostParm::OnCloseAttriMenu() { attriMenuClosed = true; }

void DrPixlPostParm::resetScene() { resetScenes[DrMan::s_nDblStockIdx] = true; }

void DrPixlPostParm::setWeatherFrame(f32 weatherFrame) { weatherFrames[DrMan::s_nDblStockIdx] = weatherFrame; }

f32 DrPixlPostParm::getWeatherFrame() const { return weatherFrames[DrMan::s_nDblIdx]; }

void DrPixlPostParm::resetWeatherFrame() { weatherFrames[DrMan::s_nDblIdx] = 60.0f; }

void DrPixlPostParm::writeParameter(const char *path, const char *name) {}

void DrPixlPostParm::readParameter(const char *path, bool isCreate, const char *name) {}

void DrPixlPostParm::updateParameter(const char *name) {}

void DrPixlPostParm::setOverrideMotBlur(bool overrideMotBlur) { dblParms[DrMan::s_nDblIdx].overrideMotBlur = overrideMotBlur; }

void DrPixlPostParm::setMotBlur2(bool motBlur2) { dblParms[DrMan::s_nDblIdx].motBlur2 = motBlur2; }

void DrPixlPostParm::setOverrideDOF(bool overrideDOF) { dblParms[DrMan::s_nDblIdx].overrideDOF = overrideDOF; }

void DrPixlPostParm::setDOFHlv(bool dofHlv) { dblParms[DrMan::s_nDblIdx].dofHlv = dofHlv; }

void DrPixlPostParm::setDOFDownSec(bool dofDownSec) { dblParms[DrMan::s_nDblIdx].dofDownSec = dofDownSec; }

void DrPixlPostParm::setDOFAutoFocus(bool dofAutoFocus) { dblParms[DrMan::s_nDblIdx].dofAutoFocus = dofAutoFocus; }

void DrPixlPostParm::setDOFAutoFocusDebug(bool dofAutoFocusDebug) { dofFocusDebug = dofAutoFocusDebug; }

void DrPixlPostParm::setDoFPixlRatio(f32 dofPixlRatio) { dblParms[DrMan::s_nDblIdx].dofPixlRatio = dofPixlRatio; }

void DrPixlPostParm::setDoFDistance(f32 dofDistance) { dblParms[DrMan::s_nDblIdx].dofDistance = dofDistance; }

void DrPixlPostParm::setDoFRange(f32 dofRange) { dblParms[DrMan::s_nDblIdx].dofRange = dofRange; }

void DrPixlPostParm::setDoFStrength(f32 dofStrength) { dblParms[DrMan::s_nDblIdx].dofStrength = dofStrength; }

void DrPixlPostParm::setDoFLens(f32 dofLens) { dblParms[DrMan::s_nDblIdx].dofLens = dofLens; }

void DrPixlPostParm::setDoFBlend(f32 dofBlend) { dblParms[DrMan::s_nDblIdx].dofBlend = dofBlend; }

void DrPixlPostParm::setDoFPixlLv(s32 dofPixlLv) { dblParms[DrMan::s_nDblIdx].dofPixlLv = dofPixlLv; }

void DrPixlPostParm::setDoFocusNum(s32 dofFocusNum) { dblParms[DrMan::s_nDblIdx].dofFocusNum = dofFocusNum; }

void DrPixlPostParm::setDoFDofFocusRat(f32 dofFocusRatio) { dblParms[DrMan::s_nDblIdx].dofFocusRatio = dofFocusRatio; }

void DrPixlPostParm::setDofFocusMin(f32 dofFocusMin) { dblParms[DrMan::s_nDblIdx].dofFocusMin = dofFocusMin; }

bool DrPixlPostParm::isOverrideDOF() const { return dblParms[DrMan::s_nDblIdx].overrideDOF; }

bool DrPixlPostParm::isOverrideColorFilter() const { return dblParms[DrMan::s_nDblIdx].overrideColorFilter; }

void DrPixlPostParm::setOverrideColorFilter(bool overrideColorFilter) { dblParms[DrMan::s_nDblIdx].overrideColorFilter = overrideColorFilter; }

void DrPixlPostParm::setColorFilterNum(s32 colorFilterNum) { dblParms[DrMan::s_nDblIdx].colorFilterNum = colorFilterNum; }

void DrPixlPostParm::setColorFilterFrm(f32 colorFilterFrm) { dblParms[DrMan::s_nDblIdx].colorFilterFrm = colorFilterFrm; }

void DrPixlPostParm::setColorFilterTransZ(bool colorFilterTransZ) { this->colorFilterTransZ = colorFilterTransZ; }

void DrPixlPostParm::setColorFilterFarNum(s32 colorFilterFarNum) { dblParms[DrMan::s_nDblIdx].colorFilterFarNum = colorFilterFarNum; }

bool DrPixlPostParm::getRainDropOn() const { return rainDrop; }

bool DrPixlPostParm::getSSRWithTrans() const { return !DrMan::getIns()->autoResetScene; }

} // namespace ml
