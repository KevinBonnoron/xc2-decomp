#pragma once
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "types.h"

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
class GfComModel;
class GfObjProperty;
class GfVolumeFade;

enum GFATTACH {};

enum {
  OBJ_FLAG_DESTROY = 0,
  OBJ_FLAG_REBUILD = 6,
  OBJ_FLAG_CALC_CAMERA_ALPHA = 0xd,
  OBJ_FLAG_WAIT = 0x10,
  OBJ_FLAG_UI_HIDDEN = 0x11,
  OBJ_FLAG_VOLUME_FADE_FOR_USER = 0x14,
  OBJ_FLAG_TALKING = 0x15,
};

enum {
  CHARACTER_TYPE_ENEMY_BLADE = 5,
  CHARACTER_TYPE_TRINITY_BLADE = 8,
};

class GfObjUtil {
public:
  static void addDebugName(GF_OBJ_HANDLE *handle);
  static void addGfObj(GF_OBJ_HANDLE *handle, GfObj *obj);
  static void removeGfObj(GF_OBJ_HANDLE *handle);
  static u32 getObjType(GF_OBJ_HANDLE *handle);
  static GfObj *getObj(GF_OBJ_HANDLE *handle);
  static u32 getObjLayer(GF_OBJ_HANDLE *handle);
  static f32 getSetupScale(GF_OBJ_HANDLE *handle);
  static GfObjSetup *getObjSetup(GF_OBJ_HANDLE *handle);
  static GF_ASSET_HANDLE *getAssetHandle(GF_OBJ_HANDLE *handle);
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
  static u32 getHp(GF_OBJ_HANDLE *handle);
  static int getPartyID(GF_OBJ_HANDLE *handle);
  static bool isValid(GF_OBJ_HANDLE *handle);
  static bool isLoading(GF_OBJ_HANDLE *handle);
  static bool isUpdate(GF_OBJ_HANDLE *handle);
  static void setOwner(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner);
  static GF_OBJ_HANDLE *getOwner(GF_OBJ_HANDLE *handle);
  static void reload(GF_OBJ_HANDLE *handle);
  static bool isEnemyBlade(GF_OBJ_HANDLE *handle);
  static bool setFlag(GF_OBJ_HANDLE *handle, u32 flag, bool value);
  static bool setFlag(GFOBJ_INFO *info, u32 flag, bool value);
  static bool testFlag(GF_OBJ_HANDLE *handle, u32 flag);
  static bool testFlag(const GFOBJ_INFO *info, u32 flag);
  static bool testFlag(const GfObj *obj, u32 flag);
  static const char *getModelBaseName(GF_OBJ_HANDLE *handle);
  static const char *getAssetModelName(GF_OBJ_HANDLE *handle);
  static const char *getAssetMotionName(GF_OBJ_HANDLE *handle);
  static GfComModel *getComModel(GF_OBJ_HANDLE *handle);
  static GfVolumeFade *getVolumeFade(GF_OBJ_HANDLE *handle);
  static bool isBattle(GF_OBJ_HANDLE *handle);
  static bool isVolumeFadeForUser(GF_OBJ_HANDLE *handle);
  static void setVolumeFadeUserFlag(GF_OBJ_HANDLE *handle, bool isForUser);
  static void setTalking(GF_OBJ_HANDLE *handle, bool isTalking);
  static bool isTalking(GF_OBJ_HANDLE *handle);
  static bool isTrinityBlade(GF_OBJ_HANDLE *handle);

  template <typename T> static T *getObjSetup(GF_OBJ_HANDLE *handle) {
    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->setup == nullptr) {
      return nullptr;
    }

    if (info->setup->objType != info->obj->type || info->obj->type != T::OBJECT_TYPE) {
      return nullptr;
    }

    return mm::mtl::dynamicCast<T>(info->setup);
  }
};

} // namespace gf
