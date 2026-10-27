#pragma once
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
class SoundPack;
}

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
struct GF_SLOT_HANDLE;
class GfAppend;
class GfAppendInfo;
enum OPTMNT : u32;
class GfAssetResource;
class GfComModel;
class GfObjProperty;
class GfVolumeFade;
class GfWeapon;

enum {
  OBJ_FLAG_DESTROY = 0,
  OBJ_FLAG_DISP_CHANGED = 1,
  OBJ_FLAG_CLIP = 2,
  OBJ_FLAG_GPU_CLIP = 3,
  OBJ_FLAG_RELOAD = 5,
  OBJ_FLAG_REBUILD = 6,
  OBJ_FLAG_LOADED_WAIT = 8,
  OBJ_FLAG_LOADED_WAIT_OK = 9,
  OBJ_FLAG_CAMERA_FADE = 0xa,
  OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_EVENT = 0xb,
  OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_BATTLE = 0xc,
  OBJ_FLAG_CALC_CAMERA_ALPHA = 0xd,
  OBJ_FLAG_UNKNOWN_E = 0xe, // Inferred role: flag tested by isDestroyGameObj; original name unknown.
  OBJ_FLAG_UNKNOWN_F = 0xf, // Inferred role: flag set when an object enters the game; original name unknown.
  OBJ_FLAG_WAIT = 0x10,
  OBJ_FLAG_UI_HIDDEN = 0x11,
  OBJ_FLAG_PARTY_OBJ = 0x12,
  OBJ_FLAG_UPDATED = 0x13,
  OBJ_FLAG_VOLUME_FADE_FOR_USER = 0x14,
  OBJ_FLAG_TALKING = 0x15,
  OBJ_FLAG_UNKNOWN_17 = 0x17, // Inferred role: set by enemies leaving the battle state; original name unknown.
  OBJ_FLAG_TOOL_MODE = 0x18,
  OBJ_FLAG_LOADED_WAIT_BLOCK = 0x1a,
};

class GfObjUtil {
public:
  static void addDebugName(GF_OBJ_HANDLE *handle);
  static void addGfObj(GF_OBJ_HANDLE *handle, GfObj *obj);
  static void removeGfObj(GF_OBJ_HANDLE *handle);
  static u32 getObjType(GF_OBJ_HANDLE *handle);
  static void setEnableBlowRotateIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time);
  static GfObj *getObj(GF_OBJ_HANDLE *handle);
  static u32 getObjLayer(GF_OBJ_HANDLE *handle);
  static f32 getSetupScale(GF_OBJ_HANDLE *handle);
  static GfObjSetup *getObjSetup(GF_OBJ_HANDLE *handle);
  static GF_ASSET_HANDLE *getAssetHandle(GF_OBJ_HANDLE *handle);
  static void destroy(GF_OBJ_HANDLE *handle);
  static void applyExecUpdate(GfObj *obj);
  static GF_OBJ_HANDLE *getParentHandle(GF_OBJ_HANDLE *handle);
  static GfObj *getParentObj(GfObj *obj);
  static u32 getLayerSection(u32 layer);
  static void changeLayer(GfObj *obj, u32 layer);
  static void changeLayer(GF_OBJ_HANDLE *handle, u32 layer);
  static const char *getResourceName(GF_OBJ_HANDLE *handle);
  static const char *getModelResourceName(GF_OBJ_HANDLE *handle);
  static const char *getMotionResourceName(GF_OBJ_HANDLE *handle);
  static const char *getAddResourceName(GF_OBJ_HANDLE *handle);
  static GF_MOUNT_HANDLE *getMountHandle(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static u32 getGameObjectID(GF_OBJ_HANDLE *handle);
  static void setLimitHP(GF_OBJ_HANDLE *handle, u32 limitHp);
  static u32 getLimitHP(GF_OBJ_HANDLE *handle);
  static void setInvincible(GF_OBJ_HANDLE *handle, bool invincible, bool invincibleSub);
  static bool testInvincible(GF_OBJ_HANDLE *handle);
  static void setInvincibleForDebug(GF_OBJ_HANDLE *handle, bool invincible);
  static bool testInvincibleForDebug(GF_OBJ_HANDLE *handle);
  static void setDisableFallDeadForDebug(GF_OBJ_HANDLE *handle, bool disableFallDead);
  static bool testDisableFallDeadForDebug(GF_OBJ_HANDLE *handle);
  static void setDisableAutoHeal(GF_OBJ_HANDLE *handle, bool disableAutoHeal);
  static bool testDisableAutoHeal(GF_OBJ_HANDLE *handle);
  static GfObjProperty *getProperty(GF_OBJ_HANDLE *handle);
  static GfWeapon *getWeaponMountObject(GF_OBJ_HANDLE *handle);
  static GfWeapon *getExtraMountObject(GF_OBJ_HANDLE *handle);
  static u32 getHp(GF_OBJ_HANDLE *handle);
  static int getPartyID(GF_OBJ_HANDLE *handle);
  static GfAppend *getAppend(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static GfAppendInfo *getAppendInfo(GF_OBJ_HANDLE *handle, GFATTACH attach);
  static void resetWeaponMotion(GF_OBJ_HANDLE *handle, OPTMNT type);
  static bool isValid(GF_OBJ_HANDLE *handle);
  static bool isLoading(GF_OBJ_HANDLE *handle);
  static bool isUpdate(GF_OBJ_HANDLE *handle);
  static void mountToBone(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *parent, const char *bone);
  static void unmountFromBone(GF_OBJ_HANDLE *handle);
  static void setOwner(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner);
  static GF_OBJ_HANDLE *getOwner(GF_OBJ_HANDLE *handle);
  static u32 getSetupObjNumberByEnArrangeId(u32 arrange);
  static void reload(GF_OBJ_HANDLE *handle);
  static bool isEnemyBlade(GF_OBJ_HANDLE *handle);
  static bool setFlag(GF_OBJ_HANDLE *handle, u32 flag, bool value);
  static bool setFlag(GFOBJ_INFO *info, u32 flag, bool value);
  static bool testFlag(GF_OBJ_HANDLE *handle, u32 flag);
  static bool testFlag(const GFOBJ_INFO *info, u32 flag);
  static void copyTransformToSetup(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, const mm::Vec3 &rotation);
  static bool testFlag(const GfObj *obj, u32 flag);
  static const char *getModelBaseName(GF_OBJ_HANDLE *handle);
  static const char *getAssetModelName(GF_OBJ_HANDLE *handle);
  static const char *getAssetMotionName(GF_OBJ_HANDLE *handle);
  static u32 getEyeRotControl(GF_OBJ_HANDLE *handle);
  static void setEnableEyeBlink(GF_OBJ_HANDLE *handle, bool isEnable);
  static GfComModel *getComModel(GF_OBJ_HANDLE *handle);
  static GfVolumeFade *getVolumeFade(GF_OBJ_HANDLE *handle);
  static bool isBattle(GF_OBJ_HANDLE *handle);
  static void rebuild(GF_OBJ_HANDLE *handle);
  static bool isVolumeFadeForUser(GF_OBJ_HANDLE *handle);
  static void setVolumeFadeUserFlag(GF_OBJ_HANDLE *handle, bool isForUser);
  static bool isStanbyTalkingPlayer(GF_OBJ_HANDLE *handle);
  static void setTalking(GF_OBJ_HANDLE *handle, bool isTalking);
  static bool isTalking(GF_OBJ_HANDLE *handle);
  static bool isSearchEmptyResource(GF_OBJ_HANDLE *handle);
  static GfAssetResource *getResourceEab(GF_OBJ_HANDLE *handle);
  static GfAssetResource *getResourceEfb(GF_OBJ_HANDLE *handle);
  static fw::SoundPack *getSePackFoot1(GF_OBJ_HANDLE *handle);
  static fw::SoundPack *getSePackFoot2(GF_OBJ_HANDLE *handle);
  static bool getSePackAll(mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, GF_OBJ_HANDLE *handle);
  static bool getMobSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_OBJ_HANDLE *handle);
  static bool isTrinityBlade(GF_OBJ_HANDLE *handle);
  static bool isUpdateComponent(const GfObj *obj);
  static void applyExecUpdate(GF_OBJ_HANDLE *handle);
  static bool isFollowObjNotReady(GF_OBJ_HANDLE *handle);

  template <typename T> static T *getObjSetup(GF_OBJ_HANDLE *handle) {
    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->unknown30 == nullptr) {
      return nullptr;
    }

    if (info->unknown30->unknown08 != info->unknown18->unknown28 || info->unknown18->unknown28 != T::OBJECT_TYPE) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(info->unknown30);
  }
};

} // namespace gf
