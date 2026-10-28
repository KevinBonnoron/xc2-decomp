#pragma once
#include <functional>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <utility>

#include "dr/dr_draw_callback.h"
#include "framework/effect/effect_caster.h" // IWYU pragma: keep
#include "framework/manager_object.h"
#include "ml/stl_custom_allocator.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h" // IWYU pragma: keep
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "ptlib/forcefield/particle_force_field.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Col4;

namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {
class DrMdlObj;
class Scn;
} // namespace ml

namespace effect {
struct SendParam;
} // namespace effect

namespace fw {

struct UpdateInfo;
class EffectData;
class EffectPack;
class RenderResource;
enum EF_CATEGORY : int;

struct AddForceParam : public ptlib::AddForceParam {};

class EffectManager : public mm::mtl::PtrSingleton<EffectManager>, public ManagerObject, public ml::IDrDrawCallback, public ml::IScnRender {
public:
  static const u32 LAYER_MAX = 32;
  static const u32 COMMON_EFFECT_MAX = 128;
  static const u32 unknown002 = 8; // Inferred role: kizuna line slot count, slot 0 is unused; original name unknown.

  struct CasterGroup {
    mm::mtl::IntrusiveList<EffectCasterSend> unknown00; // Inferred role: casters; original member name unknown.
  };

  struct CommonEffect {
    RenderResource *unknown00; // Inferred role: resource; original member name unknown.
    EffectPack *unknown08;     // Inferred role: pack; original member name unknown.
  };

  class KizunaWork {
  public:
    static const u32 unknown001 = 20; // Inferred role: rope point count; original name unknown.
    static const u32 unknown002 = 8;  // Inferred role: effect handle count; original name unknown.

    ~KizunaWork();
    void term();

    f32 unknown00; // Inferred role: gravity; original member name unknown.
    u32 unknown04; // Inferred role: line level; original member name unknown.
    u8 _08[0x10 - 0x08];
    mm::Vec3 unknown10;              // Inferred role: start position; original member name unknown.
    mm::Vec3 unknown20;              // Inferred role: end position; original member name unknown.
    mm::Vec3 unknown30[unknown001];  // Inferred role: rope points; original member name unknown.
    mm::Vec3 unknown170[unknown001]; // Inferred role: previous rope points; original member name unknown.
    mm::Vec3 unknown2b0[unknown001]; // Inferred role: rope velocities; original member name unknown.
    u32 unknown3f0[unknown002];      // Inferred role: effect handles; original member name unknown.
    mm::Vec3 unknown410;             // Inferred role: previous start position; original member name unknown.
    mm::Vec3 unknown420;             // Inferred role: previous end position; original member name unknown.
    u8 _430[0x440 - 0x430];
    mm::Vec3 unknown440;                                        // Inferred role: default offset; original member name unknown.
    f32 unknown450;                                             // Inferred role: rope length; original member name unknown.
    f32 unknown454;                                             // Inferred role: phase; original member name unknown.
    u8 unknown458;                                              // Inferred role: counter; original member name unknown.
    u8 unknown459;                                              // Role and original member name unknown.
    u8 unknown45a;                                              // Role and original member name unknown.
    u8 unknown45b;                                              // Inferred role: reset flag; original member name unknown.
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> unknown460; // Inferred role: unknown reference object; original type and member name unknown.
    ml::DrMdlObj *unknown468;                                   // Inferred role: model; original member name unknown.
  };

  typedef std::unordered_map<std::string, EffectPack *, std::hash<std::string>, std::equal_to<std::string>, ml::StlCustomAllocator<std::pair<const std::string, EffectPack *>>> PackMap;
  typedef std::unordered_map<std::string, EffectData *, std::hash<std::string>, std::equal_to<std::string>, ml::StlCustomAllocator<std::pair<const std::string, EffectData *>>> DataMap;

  ~EffectManager() override;
  bool initialize() override;
  bool isCommonLoaded();
  bool commonLoaded();
  void updateLayerPost(const UpdateInfo &info, u32 layers);
  void tail(const UpdateInfo &info, bool flag);
  void getNum(u32 &emitterNum, u32 &particleNum, u32 &drawNum);
  static void efSystemEnd();
  void addPack(EffectPack *pack);
  void removePack(EffectPack *pack);
  EffectPack *findPack(const char *name);
  void addData(EffectData *data);
  void removeData(EffectData *data);
  EffectData *findData(const char *name);
  EffectData *searchData(const char *name);
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
  void addForce(const AddForceParam *param);
  void setIBLSaturation(f32 saturation);
  void setDirScale(f32 scale);
  void setSpecScale(f32 scale);
  void setResponsiveAA(f32 responsiveAA);
  void setAllDisp(bool isDisp);
  void setDisableCollision(bool isDisable);
  u32 create(const char *name, EffectPack *pack, bool isLoop);
  void *search(const char *name, EffectPack *pack);
  u32 create(const char *name, EffectPack *pack, const effect::SendParam *param, bool isLoop);
  u32 create(void *data, bool isLoop);
  u32 create(void *data, const effect::SendParam *param, bool isLoop);
  u32 create(void *data, const mm::Mat44 &matrix, const mm::Vec3 &scale, bool isLoop);
  void create(void *data, EffectCasterBase *caster, int category, f32 scale, bool isLoop);
  void create(void *data, const effect::SendParam *param, EffectCasterBase *caster, int category, bool isLoop);
  void kill(u32 handle);
  void remove(u32 handle);
  void dead(u32 handle);
  void destroyKizunaLine(u32 handle);
  void setDispAllKizunaLine(bool isDisp);
  void updateKizunaLine(u32 handle, const mm::Vec3 &start, const mm::Vec3 &end, u32 level);
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
  void setParam(u32 handle, const mm::Mat44 &matrix, const mm::Vec3 &scale, u8 unknown);
  void setParam(u32 handle, const mm::Vec3 &position, f32 scale);
  void setParam(u32 handle, EffectCasterBase *caster, int category, f32 scale);
  void setParam(u32 handle, EffectCasterBase *caster, const mm::Mat44 &matrix);
  void setParam(u32 handle, EffectCasterBase *caster, const mm::Vec3 &position);
  void setMatrix(u32 handle, const mm::Mat44 &matrix);
  void setParam(u32 handle, EffectCasterBase *caster, f32 scale);
  void setParam(u32 handle, const mm::Vec3 &position, const mm::Vec3 &scale);
  void setSignal(u32 handle);
  bool isExist(u32 handle);
  int getDeadFlag(u32 handle);
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
  static void *debugReadFile(const char *path, int &size);
  static void debugReadFileEnd(void *data);
  static void debugOutputString(const char *string);
  static void warnOutputString(const char *string);
  static void *createMdl(const void *data, const char *name, int index, const void *group, int groupIndex);
  static void deleteMdl(void *model);
  static void deleteLgt(u32 type, void *light);
  static void setMdlPos(void *model, void *position);
  static void setMdlMatrix(void *model, void *matrix);
  static void setMdlAlpha(void *model, f32 alpha);
  static void setMdlColor(void *model, void *color);
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
  void updateHateRingVec(u32 handle, const mm::Vec3 &position, const f32 &rotation, const f32 &scale, const mm::Col4 &color);
  void destroyHateRingVec(u32 handle);
  u32 createHateArrow();
  void destroyHateArrow(u32 handle);
  u32 createComboBall(u32 level);
  bool updateComboBall(u32 handle, const mm::Vec3 &position, const f32 &scale);
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
  mtl::ALLOC_HANDLE unknown2c; // Inferred role: sys handle; original member name unknown.
  mtl::ALLOC_HANDLE unknown30; // Inferred role: res handle; original member name unknown.
  u8 _34[0x38 - 0x34];
  mm::mtl::IAllocator *unknown38;                        // Inferred role: allocator; original member name unknown.
  ml::Scn *unknown40;                                    // Inferred role: scn; original member name unknown.
  mm::mtl::FixedArray<CasterGroup, LAYER_MAX> unknown48; // Inferred role: caster groups; original member name unknown.
  PackMap *unknown348;                                   // Inferred role: pack map; original member name unknown.
  DataMap *unknown350;                                   // Inferred role: data map; original member name unknown.
  u8 _358[0x1fb8 - 0x358];
  mm::mtl::FixedVector<CommonEffect, COMMON_EFFECT_MAX> unknown1fb8; // Inferred role: common effects; original member name unknown.
  u8 _27c0[0x2fd5 - 0x27c0];
  bool unknown2fd5; // Inferred role: master pause; original member name unknown.
  bool unknown2fd6; // Inferred role: finalizing; original member name unknown.
  u8 _2fd7[0x2fd8 - 0x2fd7];
  u8 unknown2fd8;   // Inferred role: caster buffer index flipped every tail; original member name unknown.
  bool unknown2fd9; // Inferred role: destroy the effect system on tail; original member name unknown.
  u8 _2fda[0x353e0 - 0x2fda];
  KizunaWork unknown353e0[unknown002]; // Inferred role: kizuna lines; original member name unknown.
  u8 _37760[0x37980 - 0x37760];
};

static_assert(offsetof(EffectManager::KizunaWork, unknown10) == 0x10, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown30) == 0x30, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown170) == 0x170, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown2b0) == 0x2b0, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown3f0) == 0x3f0, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown410) == 0x410, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown440) == 0x440, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown450) == 0x450, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown458) == 0x458, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown460) == 0x460, "");
static_assert(offsetof(EffectManager::KizunaWork, unknown468) == 0x468, "");
static_assert(sizeof(EffectManager::KizunaWork) == 0x470, "");
static_assert(sizeof(EffectManager::CasterGroup) == 0x18, "");
static_assert(offsetof(EffectManager, unknown2c) == 0x2c, "");
static_assert(offsetof(EffectManager, unknown38) == 0x38, "");
static_assert(offsetof(EffectManager, unknown48) == 0x48, "");
static_assert(offsetof(EffectManager, unknown348) == 0x348, "");
static_assert(offsetof(EffectManager, unknown350) == 0x350, "");
static_assert(offsetof(EffectManager, unknown1fb8) == 0x1fb8, "");
static_assert(offsetof(EffectManager, unknown2fd5) == 0x2fd5, "");
static_assert(offsetof(EffectManager, unknown2fd6) == 0x2fd6, "");
static_assert(offsetof(EffectManager, unknown2fd8) == 0x2fd8, "");
static_assert(offsetof(EffectManager, unknown2fd9) == 0x2fd9, "");
static_assert(offsetof(EffectManager, unknown353e0) == 0x353e0, "");
static_assert(sizeof(EffectManager) == 0x37980, "");

} // namespace fw
