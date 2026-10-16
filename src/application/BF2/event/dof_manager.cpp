#include "event/dof_manager.h"

#include "bdat.h"
#include "event/manager.h"
#include "scn/scn.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

namespace {

f32 getValF32(unsigned char *bdat, const char *name, int id) {
  Bdat::Value value;
  value.valueU32 = Bdat::getValCheck(bdat, name, id, 8);
  return value.valueF32;
}

} // namespace

DofManager::DofManager()
    : dispFlags(0), flags(0), mAxis(1), mDist(0.0f), mCurrentDist(0.0f), mRange(5.0f), mIsAutoFocus(false), mFocusNum(0), mFocusMin(0.1f),
      mPixel(5.0f), mLens(0.6f), mStrength(4.0f), mBlend(1.0f), mPixelLv(0), mIsHlv(false), mName("") {}

void DofManager::stop() {
  unsigned char *bdat = Bdat::getFP("EVT_dof");
  flags = 0;
  mAxis = 1;
  mDist = getValF32(bdat, "dist", Bdat::getIdTop(bdat));
  mCurrentDist = getValF32(bdat, "dist", Bdat::getIdTop(bdat));
  mRange = getValF32(bdat, "range", Bdat::getIdTop(bdat));
  mIsAutoFocus = false;
  mFocusNum = 0;
  mFocusMin = 0.1f;
  mPixel = getValF32(bdat, "pixel", Bdat::getIdTop(bdat));
  mLens = getValF32(bdat, "lens", Bdat::getIdTop(bdat));
  mStrength = getValF32(bdat, "strength", Bdat::getIdTop(bdat));
  mBlend = getValF32(bdat, "blend", Bdat::getIdTop(bdat));
  mPixelLv = static_cast<s16>(Bdat::getValCheck(bdat, "pixelLv", Bdat::getIdTop(bdat), 5));
  mIsHlv = static_cast<s16>(Bdat::getValCheck(bdat, "hlv", Bdat::getIdTop(bdat), 5)) > 0;
  mName = "";
  ml::Scn *scn = Manager::get()->getScn();
  if (scn != nullptr) {
    ml::ScnRenderDrSysParmAcc parmAcc(scn->renderDrSys, 0);
    parmAcc.setDOF(false);
    parmAcc.setDOFOverride(true);
    parmAcc.setDoFDistance(mCurrentDist);
    parmAcc.setDoFRange(mRange);
    parmAcc.setDOFAutoFocus(mIsAutoFocus);
    parmAcc.setDOFFocusNum(mFocusNum);
    parmAcc.setDOFFocusMin(mFocusMin);
    parmAcc.setDoFPixlRatio(mPixel);
    parmAcc.setDoFLens(mLens);
    parmAcc.setDoFStrength(mStrength);
    parmAcc.setDoFBlend(mBlend);
    parmAcc.setDofPixlLv(mPixelLv);
    parmAcc.setDofHLvMode(mIsHlv);
  }
}

void DofManager::clear() { stop(); }

void DofManager::update() {
  if (!(flags & FLAG_ENABLE)) {
    return;
  }
  if (mIsAutoFocus) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setDOF(true);
    parmAcc.setDOFOverride(true);
    parmAcc.setDoFDistance(0.0f);
    parmAcc.setDoFRange(0.0f);
    parmAcc.setDOFAutoFocus(true);
    parmAcc.setDOFFocusNum(mFocusNum);
    parmAcc.setDOFFocusMin(mFocusMin);
    parmAcc.setDoFPixlRatio(mPixel);
    parmAcc.setDoFLens(mLens);
    parmAcc.setDoFStrength(mStrength);
    parmAcc.setDoFBlend(mBlend);
    parmAcc.setDofPixlLv(mPixelLv);
    parmAcc.setDofHLvMode(mIsHlv);
  } else {
    if (mAxis == 0) {
      return;
    }
    if (flags & FLAG_CHANGED) {
      mCurrentDist = calcDist(mAxis, mDist);
    }
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setDOF(true);
    parmAcc.setDOFOverride(true);
    parmAcc.setDoFDistance(mCurrentDist);
    parmAcc.setDoFRange(mRange);
    parmAcc.setDOFAutoFocus(false);
    parmAcc.setDOFFocusNum(0);
    parmAcc.setDOFFocusMin(0.0f);
    parmAcc.setDoFPixlRatio(mPixel);
    parmAcc.setDoFLens(mLens);
    parmAcc.setDoFStrength(mStrength);
    parmAcc.setDoFBlend(mBlend);
    parmAcc.setDofPixlLv(mPixelLv);
    parmAcc.setDofHLvMode(mIsHlv);
  }
  flags &= ~FLAG_CHANGED;
}

void DofManager::play(int axis, int id) {
  unsigned char *bdat = Bdat::getFP("EVT_dof");
  play(axis,
       getValF32(bdat, "dist", id),
       getValF32(bdat, "range", id),
       getValF32(bdat, "pixel", id),
       getValF32(bdat, "lens", id),
       getValF32(bdat, "strength", id),
       getValF32(bdat, "blend", id),
       static_cast<s16>(Bdat::getValCheck(bdat, "pixelLv", id, 5)),
       static_cast<s16>(Bdat::getValCheck(bdat, "hlv", id, 5)) > 0,
       reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "name", id, 7)));
}

void DofManager::playSimple(int focusNum, f32 focusMin, f32 pixel, f32 lens, f32 strength, f32 blend, int pixelLv, bool isHlv, const char *name) {
  mIsAutoFocus = true;
  flags |= FLAG_ENABLE | FLAG_CHANGED;
  mFocusNum = focusNum;
  mFocusMin = focusMin;
  mPixel = pixel;
  mLens = lens;
  mStrength = strength;
  mBlend = blend;
  mPixelLv = pixelLv;
  mIsHlv = isHlv;
  mName = name;
}

void DofManager::playSimple(int focusNum, int id) {
  unsigned char *bdat = Bdat::getFP("EVT_dof");
  playSimple(focusNum,
             getValF32(bdat, "foMin", id),
             getValF32(bdat, "pixel", id),
             getValF32(bdat, "lens", id),
             getValF32(bdat, "strength", id),
             getValF32(bdat, "blend", id),
             static_cast<s16>(Bdat::getValCheck(bdat, "pixelLv", id, 5)),
             static_cast<s16>(Bdat::getValCheck(bdat, "hlv", id, 5)) > 0,
             reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "name", id, 7)));
}

void DofManager::setEnable(bool isEnable) { setFlag(FLAG_ENABLE | FLAG_CHANGED, isEnable); }

bool DofManager::isEnable() const { return (flags & FLAG_ENABLE) != 0; }

void DofManager::setAxis(int axis) {
  setChanged();
  mAxis = axis;
  mIsAutoFocus = false;
}

int DofManager::getAxis() const { return mAxis; }

void DofManager::setDist(f32 dist) {
  setChanged();
  mDist = dist;
  mIsAutoFocus = false;
}

f32 DofManager::getDist() const { return mDist; }

void DofManager::setRange(f32 range) {
  setChanged();
  mRange = range;
  mIsAutoFocus = false;
}

void DofManager::setFocusNum(int focusNum) {
  setChanged();
  mIsAutoFocus = true;
  mFocusNum = focusNum;
}

void DofManager::setFocusMin(f32 focusMin) {
  setChanged();
  mIsAutoFocus = true;
  mFocusMin = focusMin;
}

void DofManager::setPixel(f32 pixel) {
  setChanged();
  mPixel = pixel;
}

void DofManager::setLens(f32 lens) {
  setChanged();
  mLens = lens;
}

void DofManager::setStrength(f32 strength) {
  setChanged();
  mStrength = strength;
}

void DofManager::setBlend(f32 blend) {
  setChanged();
  mBlend = blend;
}

void DofManager::setPixelLv(int pixelLv) {
  setChanged();
  mPixelLv = pixelLv;
}

void DofManager::setHlv(bool isHlv) {
  setChanged();
  mIsHlv = isHlv;
}

void DofManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool DofManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void DofManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER_POST:
    render();
    break;
  default:
    break;
  }
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event
