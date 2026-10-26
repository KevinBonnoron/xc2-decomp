#pragma once
#include <stddef.h>

#include "dr/dr_man.h"
#include "types.h"

namespace mm {
struct Aabb;
struct Vec3;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
}

namespace ml {
class DrPixlPostParm;
class ScnRenderDrSys;
class ScnRenderDrCapture;
class ScnRenderDrViewCtrl;
struct DR_CAPCUBE_PARAM;

struct ScnRenderDrMdlTexture {
  grlib::CGLibTextureBuffer *unknown00; // Inferred role: texture; original member name unknown.
  u32 unknown08;                        // Inferred role: index; original member name unknown.
  bool unknown0c;                       // Inferred role: enable; original member name unknown.
};

class ScnRenderDrSysParmAcc {
public:
  enum GBuffDebugType {};

  ScnRenderDrSysParmAcc();
  ScnRenderDrSysParmAcc(ScnRenderDrSys *drSys, s32 index);
  void setDrSys(ScnRenderDrSys *drSys, s32 index);
  void setDOFOverride(bool dofOverride);
  void setGlbSpd(f32 glbSpd);
  f32 getGlbSpd() const;
  void setMdlSpd(f32 mdlSpd);
  f32 getMdlSpd() const;
  void setToneMap(bool toneMap);
  bool isToneMap() const;
  void setToneMax(f32 toneMax);
  void setToneMin(f32 toneMin);
  void setToneRatio(f32 toneRatio);
  void setToneRatioLast(f32 toneRatioLast);
  void setOverrideToneMap(f32 overrideToneMap);
  void setToneBlmMax(f32 toneBlmMax);
  void setToneBlmMin(f32 toneBlmMin);
  void setToneBlmRatio(f32 toneBlmRatio);
  void setToneBlmRatioLast(f32 toneBlmRatioLast);
  void setBloom(bool bloom);
  bool isBloomOn() const;
  void setBorderBlmSub(f32 borderBlmSub);
  void setBorderBlmMul(f32 borderBlmMul);
  void setBorderBlmSecSub(f32 borderBlmSecSub);
  void setBorderBlmSecMul(f32 borderBlmSecMul);
  void setBorderBlmMax(f32 borderBlmMax);
  void setBlmWeight(f32 x, f32 y, f32 z);
  void setBlmStr(f32 x, f32 y, f32 z);
  void setBlmGauss(f32 x, f32 y, f32 z);
  f32 getBorderBlmSub() const;
  f32 getBorderBlmMul() const;
  f32 getBorderBlmSecSub() const;
  f32 getBorderBlmSecMul() const;
  f32 getBorderBlmMax() const;
  const f32 *getBlmWeight() const;
  const f32 *getBlmStr() const;
  const f32 *getBlmGauss() const;
  void setLensFlare(bool lensFlare);
  bool isLensFlare() const;
  void setBlmLensSub(f32 blmLensSub);
  void setBlmLensMul(f32 blmLensMul);
  void setBlmLensMax(s32 blmLensMax);
  void setBlmLensRot(f32 blmLensRot);
  void setBlmLensWeight(f32 blmLensWeight);
  void setBlmLensDecay(f32 blmLensDecay);
  void setBlmLensStrength(f32 blmLensStrength);
  void setBlmLensParmMax(f32 blmLensParmMax);
  void setBlmLensUVDecay(f32 blmLensUVDecay);
  f32 getBlmLensSub() const;
  f32 getBlmLensMul() const;
  s32 getBlmLensMax() const;
  f32 getBlmLensRot() const;
  f32 getBlmLensWeight() const;
  f32 getBlmLensDecay() const;
  f32 getBlmLensStrength() const;
  f32 getBlmLensParmMax() const;
  f32 getBlmLensUVDecay() const;
  void setGodRay(bool godRay);
  bool isGodRay() const;
  void setGodRayWeight(f32 godRayWeight);
  void setGodRayDecay(f32 godRayDecay);
  void setGodRayStrength(f32 godRayStrength);
  f32 getGodRayWeight() const;
  f32 getGodRayDecay() const;
  f32 getGodRayStrength() const;
  void setAA(bool aa);
  bool isAA() const;
  void setAAEdgeSharpness(f32 aaEdgeSharpness);
  void setAAEdgeThreshold(f32 aaEdgeThreshold);
  void setAAEdgeThresholdMin(f32 aaEdgeThresholdMin);
  void setAAEdgeRanges(f32 aaEdgeRanges);
  f32 getAAEdgeSharpness() const;
  f32 getAAEdgeThreshold() const;
  f32 getAAEdgeThresholdMin() const;
  f32 getAAEdgeRanges() const;
  void setSSAO(bool ssao);
  bool isSSAO() const;
  void setSSAOBlurStr(f32 ssaoBlurStr);
  f32 getSSAOBlurStr() const;
  void setSpecularStr(f32 specularStr);
  f32 getSpecularStr() const;
  void setMotBlurOverride(bool motBlurOverride);
  void setMotBlur(bool motBlur);
  void setMotBlurDefault(bool motBlurDefault);
  void setAppBlur(bool appBlur);
  void setSpBlur(bool spBlur);
  void setSpBlurTarget(const mm::Vec3 &spBlurTarget);
  void setBlurSpParm(f32 blurSpParm);
  bool isMotBlur() const;
  void setMotBlurStrength(f32 motBlurStrength);
  void setMotBlurSub(f32 motBlurSub);
  f32 getBlurStrength() const;
  f32 getBlurSub() const;
  void setDOF(bool dof);
  bool isDOF() const;
  void setDoFPixlRatio(f32 dofPixlRatio);
  void setDoFDistance(f32 dofDistance);
  void setDoFRange(f32 dofRange);
  void setDoFStrength(f32 dofStrength);
  void setDoFLens(f32 dofLens);
  void setDoFBlend(f32 dofBlend);
  void setDofHLvMode(bool dofHLvMode);
  void setDofPixlLv(s32 dofPixlLv);
  void setDOFAutoFocus(bool dofAutoFocus);
  void setDOFFocusNum(s32 dofFocusNum);
  void setDOFFocusMin(f32 dofFocusMin);
  void setDOFFocusRatio(f32 dofFocusRatio);
  void setDOFFocusDebug(bool dofFocusDebug);
  f32 getDoFPixlRatio() const;
  f32 getDoFDistance() const;
  f32 getDoFRange() const;
  f32 getDoFStrength() const;
  f32 getDoFLens() const;
  f32 getDoFBlend() const;
  bool isDofHLvMode() const;
  s32 getDofPixlLv() const;
  bool isDOFAutoFocus() const;
  s32 getDOFFocusNum() const;
  f32 getDOFFocusMin() const;
  f32 getDOFFocusRatio() const;
  bool isDOFFocusDebug() const;
  void setPlaneCloudNum(u32 planeCloudNum);
  u32 getPlaneCloudNum();
  void setGlobalWind(const mm::Vec3 &globalWind);
  void setReduction(bool reduction);
  bool isReduction() const;
  void setAutoReduction(bool autoReduction);
  void setReductionScX(f32 reductionScX);
  void setReductionScY(f32 reductionScY);
  f32 getReductionScX() const;
  f32 getReductionScY() const;
  bool isDispReduction() const;
  void setDispReduction(bool dispReduction);
  void setGroupsDisp(s32 group, bool disp);
  void setColorFilterOverride(bool colorFilterOverride);
  void setColorFilterNum(s32 colorFilterNum);
  void setColorFilterFarNum(s32 colorFilterFarNum);
  void setColorFilterFrm(f32 colorFilterFrm);
  f32 getColorFilterFrm() const;
  void setRainDrop(bool rainDrop);
  bool getRainDrop() const;
  void setLightNum(s32 lightNum);
  s32 getLightNum() const;
  void setInOut(bool inOut);
  bool isInOut() const;
  void setTimeVal(f32 timeVal);
  f32 getTimerVal() const;
  void setWeather(s32 weather);
  s32 getWeather() const;
  void setWeatherFrame(f32 weatherFrame);
  f32 getWeatherFrame() const;
  void setSeamMapAddPosMode(bool seamMapAddPosMode);
  void setSeamMapReadPos(const mm::Vec3 &seamMapReadPos);
  void releaseFastLight();
  u32 isGblId(s32 id);
  void setSelectIdDisp(s32 id, bool disp);
  void setPlayAnime(s32 id, bool play, bool loop);
  bool isSelectIdDisp(s32 id);
  bool isPlayAnime(s32 id);
  void setClip(bool clip);
  void setFogSkip(bool fogSkip);
  u32 *getGblTbl();
  void setSpCapMode(s32 spCapMode);
  s32 getSpCapMode() const;
  void setMdlHeightTexSkip(bool mdlHeightTexSkip);
  bool isMdlHeightTexSkip() const;
  void setSeamMapOpenMode(bool seamMapOpenMode);
  bool isSeamMapOpenMode() const;
  void setScreenDispOff(bool screenDispOff);
  FILE_PRIO getSeamMapPriMdl() const;
  FILE_PRIO getSeamMapPriColi() const;
  void setSeamMapPriMdl(FILE_PRIO seamMapPriMdl);
  void setSeamMapPriColi(FILE_PRIO seamMapPriColi);
  void *getBlurVelocityMap();
  void setCharDirShadow(bool charDirShadow);
  bool isCharDirShadow() const;
  void setMdlDblPause(bool mdlDblPause);
  bool isMdlDblPause() const;
  bool isMdlAllMiddleTexStm() const;
  bool isSeamMapRead() const;
  void setSeamReadLv(s32 seamReadLv);
  void setHeightTexSkip(bool heightTexSkip);
  bool isHeightTexSkip() const;
  void setSeamHeightTexSkip(bool seamHeightTexSkip);
  bool isSeamHeightTexSkip() const;
  void setShadowStr(f32 shadowStr);
  f32 getShadowStr() const;
  void setShadowChacheAngle(f32 shadowChacheAngle);
  f32 getShadowChacheAngle() const;
  void callCubeMapRender(const DR_CAPCUBE_PARAM &param);
  bool getIrrVolIsValid() const;
  const mm::Vec3 &getIrrVolCenterPos() const;
  void setIrrVolCenterPos(const mm::Vec3 &irrVolCenterPos);
  u32 getIrrVolCascadeMax() const;
  bool getIrrVolVolumeArea(u32 cascade, mm::Aabb &area) const;
  void setToonDirLightScale(bool toonDirLightScale);
  void setToonAmbient(bool toonAmbient);
  void setDispChara(bool dispChara);
  bool isDispChara() const;
  bool isDispGlobalIBLTex() const;
  void setDispGlobalIBLTex(bool dispGlobalIBLTex);
  void setPlayerPos(const mm::Vec3 &playerPos);
  void setCameraLight(bool cameraLight);
  void setGBuffDebug(bool gBuffDebug);
  void setGBuffDebugDefault();
  void setGBuffDebugParam(GBuffDebugType type, f32 min, f32 max);
  void createAddRenderView(ScnRenderDrViewCtrl *viewCtrl);
  void deleteAddRenderView(ScnRenderDrViewCtrl *viewCtrl);
  void setModelTexture(const ScnRenderDrMdlTexture &texture);
  void resetModelTexture(u32 index);
  void setDefferedColor(bool defferedColor);
  bool isDefferedColor() const;
  void setRenderSpecMode(RenderSpecMode renderSpecMode);
  void setGlassBr(bool glassBr, u32 type);
  bool isGlassBr();
  void setCacherClearMode(bool cacherClearMode);
  bool isViewRenderSkip(u32 view) const;
  void setViewRenderSkip(u32 view, bool skip);
  void setWriteZBuffer(bool writeZBuffer);
  void resetScene();
  void setAutoResetScene(bool autoResetScene);
  f32 getGamma() const;
  void setGamma(f32 gamma);
  void startCapture(ScnRenderDrCapture *capture);
  void setCaptureMode(bool captureMode);

  DrMan *unknown00;          // Inferred role: dr man; original member name unknown.
  DrPixlPostParm *unknown08; // Inferred role: post parm; original member name unknown.
  s32 unknown10;             // Inferred role: view index; original member name unknown.
};

static_assert(offsetof(ScnRenderDrSysParmAcc, unknown00) == 0x00, "");
static_assert(offsetof(ScnRenderDrSysParmAcc, unknown08) == 0x08, "");
static_assert(offsetof(ScnRenderDrSysParmAcc, unknown10) == 0x10, "");

} // namespace ml
