#pragma once
#include <stddef.h>

#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace mm {
struct Quat;
struct Vec3;
} // namespace mm

namespace fw {
class SoundPack;
enum SoundCategory : int;
struct Transform;
} // namespace fw

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
  OBJ_FLAG_UNKNOWN_0 = 0,     // Inferred role: obj flag destroy; original name unknown.
  OBJ_FLAG_UNKNOWN_1 = 1,     // Inferred role: obj flag disp changed; original name unknown.
  OBJ_FLAG_UNKNOWN_2 = 2,     // Inferred role: obj flag clip; original name unknown.
  OBJ_FLAG_UNKNOWN_3 = 3,     // Inferred role: obj flag gpu clip; original name unknown.
  OBJ_FLAG_UNKNOWN_5 = 5,     // Inferred role: obj flag reload; original name unknown.
  OBJ_FLAG_UNKNOWN_6 = 6,     // Inferred role: obj flag rebuild; original name unknown.
  OBJ_FLAG_UNKNOWN_8 = 8,     // Inferred role: obj flag loaded wait; original name unknown.
  OBJ_FLAG_UNKNOWN_9 = 9,     // Inferred role: obj flag loaded wait ok; original name unknown.
  OBJ_FLAG_UNKNOWN_10 = 0xa,  // Inferred role: obj flag camera fade; original name unknown.
  OBJ_FLAG_UNKNOWN_11 = 0xb,  // Inferred role: obj flag camera fade disable for event; original name unknown.
  OBJ_FLAG_UNKNOWN_12 = 0xc,  // Inferred role: obj flag camera fade disable for battle; original name unknown.
  OBJ_FLAG_UNKNOWN_13 = 0xd,  // Inferred role: obj flag calc camera alpha; original name unknown.
  OBJ_FLAG_UNKNOWN_14 = 0xe,  // Inferred role: flag tested by isDestroyGameObj; original name unknown.
  OBJ_FLAG_UNKNOWN_15 = 0xf,  // Inferred role: flag set when an object enters the game; original name unknown.
  OBJ_FLAG_UNKNOWN_16 = 0x10, // Inferred role: obj flag wait; original name unknown.
  OBJ_FLAG_UNKNOWN_17 = 0x11, // Inferred role: obj flag ui hidden; original name unknown.
  OBJ_FLAG_UNKNOWN_18 = 0x12, // Inferred role: obj flag party obj; original name unknown.
  OBJ_FLAG_UNKNOWN_19 = 0x13, // Inferred role: obj flag updated; original name unknown.
  OBJ_FLAG_UNKNOWN_20 = 0x14, // Inferred role: obj flag volume fade for user; original name unknown.
  OBJ_FLAG_UNKNOWN_21 = 0x15, // Inferred role: obj flag talking; original name unknown.
  OBJ_FLAG_UNKNOWN_23 = 0x17, // Inferred role: set by enemies leaving the battle state; original name unknown.
  OBJ_FLAG_UNKNOWN_24 = 0x18, // Inferred role: obj flag tool mode; original name unknown.
  OBJ_FLAG_UNKNOWN_26 = 0x1a, // Inferred role: obj flag loaded wait block; original name unknown.
};

// Layout from GfObjUtil::parseFadeParam (0x71005b3674), which parses "fadeout_<frames>" or "fadein_<frames>" and an
// optional list of '-' separated values; GfComBehaviorWeapon::procMsgObjectNotifyAsmCallback zeroes the list size.
struct GfFadeInfo {
  u32 unknown00;                          // Inferred role: fade type, 0 fade in, 1 fade out; original member name unknown.
  u32 unknown04;                          // Inferred role: fade frames; original member name unknown.
  mm::mtl::FixedVector<int, 6> unknown08; // Inferred role: values of the parameter list, -1 when absent; original member name unknown.
};

static_assert(offsetof(GfFadeInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfFadeInfo, unknown08) == 0x08, "");
static_assert(sizeof(GfFadeInfo) == 0x28, "");

class GfObjUtil {
public:
  static void addDebugName(GF_OBJ_HANDLE *handle);
  static void addGfObj(GF_OBJ_HANDLE *handle, GfObj *obj);
  static void removeGfObj(GF_OBJ_HANDLE *handle);
  static u32 getObjType(GF_OBJ_HANDLE *handle);
  static void setEnableBlowRotateIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time);
  static void setEnableBodyIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time);
  static void setEnableLookIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time);
  static void setEnableFootIK(GF_OBJ_HANDLE *handle, bool isEnable);
  static void setEnableSPCIK(GF_OBJ_HANDLE *handle, bool isEnable);
  static fw::SoundCategory getSoundCategoryNormal(GF_OBJ_HANDLE *handle);
  static fw::SoundCategory getSoundCategoryWithoutSlow(GF_OBJ_HANDLE *handle);
  static void setBlowRotate(GF_OBJ_HANDLE *handle, const mm::Quat &rotation);
  static void setEnableLipSync(GF_OBJ_HANDLE *handle, bool isEnable);
  static u32 getEyeIKType(GF_OBJ_HANDLE *handle);
  static const mm::Quat &getBlowRotate(GF_OBJ_HANDLE *handle);
  static void setEnableEyeIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time);
  static void setMoveEyeIK(GF_OBJ_HANDLE *handle, f32 moveX, f32 moveY);
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
  static bool mountToBone(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *parent, const char *bone);
  static bool unmountFromBone(GF_OBJ_HANDLE *handle);
  static bool attachGfObj(GF_OBJ_HANDLE *parent, GF_OBJ_HANDLE *child);
  static bool dettachGfObject(GF_OBJ_HANDLE *parent, GF_OBJ_HANDLE *child);
  static void setOwner(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner);
  static GF_OBJ_HANDLE *getOwner(GF_OBJ_HANDLE *handle);
  static u32 getSetupObjNumberByEnArrangeId(u32 arrange);
  static bool getSetupObj(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objects, u32 objectType);
  static void reload(GF_OBJ_HANDLE *handle);
  static bool isExistAsm(GF_OBJ_HANDLE *handle);
  static bool isEnemyBlade(GF_OBJ_HANDLE *handle);
  static bool setFlag(GF_OBJ_HANDLE *handle, u32 flag, bool value);
  static bool setFlag(GFOBJ_INFO *info, u32 flag, bool value);
  static bool testFlag(GF_OBJ_HANDLE *handle, u32 flag);
  static bool testFlag(const GFOBJ_INFO *info, u32 flag);
  static void copyTransformToSetup(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *setupHandle);
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
  static void saveRebuildInfo(GF_OBJ_HANDLE *handle);
  static bool isVolumeFadeForUser(GF_OBJ_HANDLE *handle);
  static void setVolumeFadeUserFlag(GF_OBJ_HANDLE *handle, bool isForUser);
  static bool isStanbyTalkingPlayer(GF_OBJ_HANDLE *handle);
  static void setTalking(GF_OBJ_HANDLE *handle, bool isTalking);
  static bool isTalking(GF_OBJ_HANDLE *handle);
  static bool isSearchEmptyResource(GF_OBJ_HANDLE *handle);
  static GfAssetResource *getResourceEab(GF_OBJ_HANDLE *handle);
  static GfAssetResource *getResourceEfb(GF_OBJ_HANDLE *handle);
  static u32 getWeaponResourceSwtNum(GF_OBJ_HANDLE *handle);
  static GfAssetResource *getWeaponResourceSwt(GF_OBJ_HANDLE *handle, u32 index);
  static u32 getWeaponResourceEabNum(GF_OBJ_HANDLE *handle);
  static GfAssetResource *getWeaponResourceEab(GF_OBJ_HANDLE *handle, u32 index);
  static u32 getWeaponResourceEfbNum(GF_OBJ_HANDLE *handle);
  static GfAssetResource *getWeaponResourceEfb(GF_OBJ_HANDLE *handle, u32 index);
  static fw::SoundPack *getSePack(GF_OBJ_HANDLE *handle);
  static fw::SoundPack *getSePackFoot1(GF_OBJ_HANDLE *handle);
  static fw::SoundPack *getSePackFoot2(GF_OBJ_HANDLE *handle);
  static bool getSePackAll(mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, GF_OBJ_HANDLE *handle);
  static bool getMobSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_OBJ_HANDLE *handle);
  static bool isTrinityBlade(GF_OBJ_HANDLE *handle);
  static bool isUpdateComponent(const GfObj *obj);
  static void applyExecUpdate(GF_OBJ_HANDLE *handle);
  static void createVolumeFade(GF_OBJ_HANDLE *handle);
  static bool isFollowObjNotReady(GF_OBJ_HANDLE *handle);
  static void setWarpTransform(GF_OBJ_HANDLE *handle, const fw::Transform &transform, bool isResetState);
  static bool parseFadeParam(const char *param, GfFadeInfo *info);
  static void setDeadParticle(GF_OBJ_HANDLE *handle, bool isActive, u32 attribute, f32 alpha);

  // Inferred name; shared by every object setup class for GfObjUtil::getObjSetup<T>.
  template <typename T> static T *getObjSetup(GF_OBJ_HANDLE *handle) {
    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->unknown30 == nullptr) {
      return nullptr;
    }

    // Inferred name; shared by every object setup class for GfObjUtil::getObjSetup<T>.
    if (info->unknown30->unknown08 != info->unknown18->unknown28 || info->unknown18->unknown28 != T::OBJECT_TYPE) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(info->unknown30);
  }
};

} // namespace gf
