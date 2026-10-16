#pragma once
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace effect {
struct SendParam;
} // namespace effect

namespace fw {

enum EF_CATEGORY : int;

class EffectManager : public mm::mtl::PtrSingleton<EffectManager> {
public:
  bool isCommonLoaded();
  bool commonLoaded();
  void getNum(u32 &emitterNum, u32 &particleNum, u32 &drawNum);
  static void efSystemEnd();
  void setMasterPause(bool isPause);
  bool isMasterPause() const;
  void setIBLSaturation(f32 saturation);
  void setDirScale(f32 scale);
  void setSpecScale(f32 scale);
  void setResponsiveAA(f32 responsiveAA);
  void setAllDisp(bool isDisp);
  void setDisableCollision(bool isDisable);
  u32 create(void *data, bool isLoop);
  u32 create(void *data, const effect::SendParam *param, bool isLoop);
  void kill(u32 handle);
  void remove(u32 handle);
  void dead(u32 handle);
  void fadeOutDead(u32 handle);
  void fadeOutDead(u32 handle, u32 frame);
  void setDisp(u32 handle, bool isDisp);
  void setAlpha(u32 handle, f32 alpha);
  void setSpeed(u32 handle, f32 speed);
  void setCategory(u32 handle, EF_CATEGORY category);
  void setViewnum(u32 handle, u32 viewnum);
  void setParamPosOnly(u32 handle, const effect::SendParam *param);
  void setParamPosOnly2(u32 handle, const effect::SendParam *param);
  void setParam(u32 handle, const effect::SendParam *param);
  void setSignal(u32 handle);
  bool isExist(u32 handle);
  bool getDeadFlag(u32 handle);
  bool isLoop(void *data) const;
  bool containsCamAxis(void *data) const;
  static void *effectAllocSys(void *user, u32 size, u32 alignment, const char *name, u32 line);
  static void effectFreeSys(void *user, void *pointer);
  static void *effectAllocRes(void *user, u32 size, u32 alignment, const char *name, u32 line);
  static void effectFreeRes(void *user, void *pointer);
  static mtl::ALLOC_HANDLE effectSysHandle();
  static mtl::ALLOC_HANDLE effectResHandle();
  static void debugReadFileEnd(void *data);
  static void debugOutputString(const char *string);
  static void warnOutputString(const char *string);
  static bool isEfSystemValid();
  u32 getEmitterForm(u32 handle);
  void getNumDetail(u32 &emitterNum, u32 &particleNum, u32 &drawNum, u32 &workNum);
  bool *getDispPTex();
  bool *getWorkTex();
  bool getDispEmitter();
  void setDispEmitter(bool isDisp);
  bool isOldVersion();
  void setOldVersion(bool isOldVersion);
  bool isDebugShader();
  void setDebugShader(bool isDebugShader);
  bool isPerfMonitoring();
  void destroyHateRing(u32 handle);
  void destroyHateRingVec(u32 handle);
  void destroyHateArrow(u32 handle);
  void destroyComboBall(u32 handle);
  void setPerfLoggingCsv(bool isLogging);

  u8 _08[0x2c - 0x08];
  mtl::ALLOC_HANDLE sysHandle;
  mtl::ALLOC_HANDLE resHandle;
  u8 _34[0x2fd5 - 0x34];
  bool masterPause;
};

} // namespace fw
