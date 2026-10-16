#pragma once
#include "gf/object/gf_obj_manager.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class ScnObjModel;
}

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_MOUNT_HANDLE;
struct GF_OBJ_HANDLE;
class GfObj;

enum OBJ_ALPHA {
  OBJ_ALPHA_NORMAL,
  OBJ_ALPHA_FADE,
  OBJ_ALPHA_CAMERA,
  OBJ_ALPHA_EVENT,
  OBJ_ALPHA_LIFE,
  OBJ_ALPHA_EVT_DISP,
  OBJ_ALPHA_MAX,
};

enum OBJDISP {};

enum GfObjUserData {};

class GfObjAcc {
public:
  GfObjAcc(GfObj *obj);
  GfObjAcc(GF_OBJ_HANDLE *handle);

  bool getObjPosRot(mm::Vec3 &position, f32 &rotation);

  bool isValid() const { return mObj != nullptr; }
  bool isValidTransform() const;
  f32 getAlpha(OBJ_ALPHA type) const;
  void setAlpha(OBJ_ALPHA type, f32 alpha);
  bool isAlphaChanged() const;
  void addApplyParam();
  void setAlphaEvent(f32 alpha);
  f32 getAlphaEvent() const;
  void setAlphaEvtDisp(f32 alpha);
  f32 getAlphaEvtDisp() const;
  void setAlphaFade(f32 alpha);
  f32 getAlphaFade() const;
  void setAlphaCamera(f32 alpha);
  f32 getAlphaCamera() const;
  void setAlphaLife(f32 alpha);
  f32 getAlphaLife() const;
  void setAlphaNormal(f32 alpha);
  f32 getAlphaNormal() const;
  f32 getAlpha() const;
  ml::ScnObjModel *getScnModel() const;
  void setFrameSpeed(f32 speed);
  void setCameraFade(bool isEnable);
  bool setFlag(u32 flag, bool value);
  bool isCameraFadeEnable() const;
  bool testFlag(u32 flag) const;
  bool isCameraFadeDisableForEvent() const;
  void setCameraFadeDisableForEvent(bool isDisable);
  bool isCameraFadeDisableForBattle() const;
  void setCameraFadeDisableForBattle(bool isDisable);
  bool isCameraFadeAllOK() const;
  bool hasParent() const;
  GfObj *getObj() const;
  GF_OBJ_HANDLE *getHandle() const;
  bool isDisp(OBJDISP disp) const;
  bool isDispChanged() const;
  void applyDisp();
  void setClip(bool isClip);
  void setGpuClip(bool isClip);
  void setModelScaleForMenu(const mm::Vec3 &scale);
  void setModelScale(f32 scale);
  const mm::Vec3 &getModelScaleXYZ() const;
  f32 getModelScale() const;
  void setModelScaleForDebug(f32 scale);
  void setGravity(bool isGravity);
  bool isGravity() const;
  bool isReload() const;
  bool isRebuild() const;
  void setToolMode(bool isToolMode);
  bool isToolMode() const;
  void setAttribute(u32 attribute);
  u32 getAttribute() const;
  void applyClip();
  void applyClipGpu();
  bool isValidProperty() const;
  bool isValidModel() const;
  bool isDestroy() const;
  u32 getType() const;
  void setCalcCameraAlpha();
  u16 getMultiBindUniqId() const;
  bool isMultiBindWaiting() const;
  GF_ASSET_HANDLE *getAssetHandle() const;
  GF_OBJ_HANDLE *getTarget() const;
  GF_OBJ_HANDLE *getMaster() const;
  void setUserData(GfObjUserData type, u64 data);
  u64 getUserData(GfObjUserData type) const;
  u32 getBdatId() const;
  u32 getDriverId() const;
  u32 getBladeId() const;
  bool isEnemyBlade() const;
  u32 getEnArrangeId() const;
  u32 getEnRscId() const;
  u32 getEnParamId() const;
  u32 getNpcRscId() const;
  u32 getMobRscId() const;
  u32 getPcWeaponId() const;
  u32 getUiObjId() const;
  bool isMasterObjValid() const;
  bool isLoadedWaitOK() const;
  u16 getView() const;
  u32 getLayer() const;
  bool isLayerPause() const;
  void setExtMeshAlpha(u32 index, f32 alpha);
  f32 getExtMeshAlpha(u32 index) const;
  int getExtMeshMax() const;
  int getExtMeshIdx(const char *name) const;
  const char *getExtMeshName(int index) const;
  bool isUpdated() const;
  const char *getDebugName() const;
  bool isBattle() const;
  GF_MOUNT_HANDLE *getMountHandle(GFATTACH attach) const;
  void setupExtraParts();
  void setEtcParam(int index, f32 value);
  int getEtcParamIndex(const char *name) const;
  bool isPartyObj() const;
  int getPartyID() const;
  bool isCollideModelClip() const;
  void setEnableCollideModelClip(bool isEnable);

private:
  GFOBJ_INFO *mInfo;
  GfObj *mObj;
};

static_assert(sizeof(GfObjAcc) == 0x10, "");

} // namespace gf
