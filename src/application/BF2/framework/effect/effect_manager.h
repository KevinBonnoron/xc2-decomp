#pragma once
#include <stddef.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <utility>

#include "dr/dr_draw_callback.h"
#include "framework/effect/effect_caster.h"
#include "framework/manager_object.h"
#include "ml/stl_custom_allocator.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;

namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {
class Scn;
} // namespace ml

namespace effect {
struct SendParam;
} // namespace effect

namespace fw {

class EffectData;
class EffectPack;
class RenderResource;
enum EF_CATEGORY : int;

class EffectManager : public mm::mtl::PtrSingleton<EffectManager>, public ManagerObject, public ml::IDrDrawCallback, public ml::IScnRender {
public:
  static const u32 LAYER_MAX = 32;
  static const u32 COMMON_EFFECT_MAX = 128;

  struct CasterGroup {
    mm::mtl::IntrusiveList<EffectCasterSend> casters;
  };

  struct CommonEffect {
    RenderResource *resource;
    EffectPack *pack;
  };

  typedef std::unordered_map<std::string, EffectPack *, std::hash<std::string>, std::equal_to<std::string>,
                             ml::StlCustomAllocator<std::pair<const std::string, EffectPack *>>>
      PackMap;
  typedef std::unordered_map<std::string, EffectData *, std::hash<std::string>, std::equal_to<std::string>,
                             ml::StlCustomAllocator<std::pair<const std::string, EffectData *>>>
      DataMap;

  ~EffectManager() override;
  bool initialize() override;
  bool isCommonLoaded();
  bool commonLoaded();
  void getNum(u32 &emitterNum, u32 &particleNum, u32 &drawNum);
  static void efSystemEnd();
  void addPack(EffectPack *pack);
  void removePack(EffectPack *pack);
  EffectPack *findPack(const char *name);
  void addData(EffectData *data);
  void removeData(EffectData *data);
  EffectData *findData(const char *name);
  void setMasterPause(bool isPause);
  bool isMasterPause() const;
  EffectCasterSend *getCaster(EffectCasterBase *caster);
  void remove(EffectCasterBase *caster);
  void changeLayerCaster(EffectCasterBase *caster, u32 layer, u32 newLayer);
  void sendCaster(EffectCasterBase *caster, mm::Mat44 &matrix, const char *name, int index);
  void sendCaster(EffectCasterBase *caster, f32 scale);
  void sendCasterFrame(EffectCasterBase *caster, f32 frame);
  void sendCasterStateName(EffectCasterBase *caster, const char *name);
  EffectCasterSend *getCasterCB(EffectCasterBase *caster);
  void setIBLSaturation(f32 saturation);
  void setDirScale(f32 scale);
  void setSpecScale(f32 scale);
  void setResponsiveAA(f32 responsiveAA);
  void setAllDisp(bool isDisp);
  void setDisableCollision(bool isDisable);
  u32 create(const char *name, EffectPack *pack, bool isLoop);
  void *search(const char *name, EffectPack *pack);
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
  void setParam(u32 handle, EffectCasterBase *caster, f32 scale);
  void setSignal(u32 handle);
  bool isExist(u32 handle);
  bool getDeadFlag(u32 handle);
  bool isLoop(void *data) const;
  bool isLoop(const char *name, EffectPack *pack) const;
  bool containsCamAxis(void *data) const;
  bool containsCamAxis(const char *name, EffectPack *pack) const;
  void *seachAssetEffectHandle(const char *name);
  static void *effectAllocSys(void *user, u32 size, u32 alignment, const char *name, u32 line);
  static void effectFreeSys(void *user, void *pointer);
  static void *effectAllocRes(void *user, u32 size, u32 alignment, const char *name, u32 line);
  static void effectFreeRes(void *user, void *pointer);
  static mtl::ALLOC_HANDLE effectSysHandle();
  static mtl::ALLOC_HANDLE effectResHandle();
  static void debugReadFileEnd(void *data);
  static void debugOutputString(const char *string);
  static void warnOutputString(const char *string);
  static void *createMdl(const void *data, const char *name, int index, const void *group, int groupIndex);
  static void deleteMdl(void *model);
  static void deleteLgt(u32 type, void *light);
  static void setMdlPos(void *model, void *position);
  static void setMdlMatrix(void *model, void *matrix);
  static void setMdlAlpha(void *model, f32 alpha);
  static void setMdlSpeed(void *model, void *speed);
  static void setLgtPos(u32 type, void *light, void *position);
  static void setLgtMatrix(u32 type, void *light, void *matrix);
  static void *createGroup(int num, int flags);
  static void destroyGroup(void *group);
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
  static void memoryDump();
  u32 createHateRing();
  void updateHateRing(u32 handle, const mm::Vec3 &position, const f32 &rotation, bool isEnable, const f32 &scale);
  void destroyHateRing(u32 handle);
  u32 createHateRingVec();
  void destroyHateRingVec(u32 handle);
  u32 createHateArrow();
  void destroyHateArrow(u32 handle);
  u32 createComboBall(u32 level);
  void destroyComboBall(u32 handle);
  void setPerfLoggingCsv(bool isLogging);
  void begin() override;
  void end() override;
  void opacityRender(const ml::IDrDrawWorkInfo *info) override;
  void alphaRender(const ml::IDrDrawWorkInfo *info) override;
  void lastRender(const ml::IDrDrawWorkInfo *info) override;
  void blurRender(const ml::IDrDrawWorkInfo *info) override;
  void finalRender(const ml::IDrDrawWorkInfo *info) override;

  u8 _28[0x2c - 0x28];
  mtl::ALLOC_HANDLE sysHandle;
  mtl::ALLOC_HANDLE resHandle;
  u8 _34[0x38 - 0x34];
  mm::mtl::IAllocator *allocator;
  ml::Scn *scn;
  mm::mtl::FixedArray<CasterGroup, LAYER_MAX> casterGroups;
  PackMap *packMap;
  DataMap *dataMap;
  u8 _358[0x1fb8 - 0x358];
  mm::mtl::FixedVector<CommonEffect, COMMON_EFFECT_MAX> commonEffects;
  u8 _27c0[0x2fd5 - 0x27c0];
  bool masterPause;
  bool finalizing;
};

static_assert(sizeof(EffectManager::CasterGroup) == 0x18, "");
static_assert(offsetof(EffectManager, sysHandle) == 0x2c, "");
static_assert(offsetof(EffectManager, allocator) == 0x38, "");
static_assert(offsetof(EffectManager, casterGroups) == 0x48, "");
static_assert(offsetof(EffectManager, packMap) == 0x348, "");
static_assert(offsetof(EffectManager, dataMap) == 0x350, "");
static_assert(offsetof(EffectManager, commonEffects) == 0x1fb8, "");
static_assert(offsetof(EffectManager, masterPause) == 0x2fd5, "");
static_assert(offsetof(EffectManager, finalizing) == 0x2fd6, "");

} // namespace fw
