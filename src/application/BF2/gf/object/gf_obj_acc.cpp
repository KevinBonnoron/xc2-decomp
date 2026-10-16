#include "gf/object/gf_obj_acc.h"

#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "framework/object/component_object.h"
#include "fw/fw_model_object.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "ml/scn_obj_model.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"

namespace fw {

class Framework {
public:
  static bool isLayerPause(u32 layer);
};

} // namespace fw

namespace gf {

static const char *EXTRA_PARTS_NAMES[] = {
    "ExtraPartsA",
    "ExtraPartsB",
    "ExtraPartsC",
    "ExtraPartsD",
    "ExtraPartsE",
    "ExtraPartsF",
};

GfObjAcc::GfObjAcc(GfObj *obj) : mObj(obj) { mInfo = obj != nullptr ? GfObjManager::getObjInfo(obj->handle) : nullptr; }

GfObjAcc::GfObjAcc(GF_OBJ_HANDLE *handle) {
  mInfo = GfObjManager::getObjInfo(handle);
  if (mInfo == nullptr) {
    mObj = nullptr;
  } else {
    mObj = mInfo->obj;
  }
}

bool GfObjAcc::isValidTransform() const {
  if (mObj == nullptr || mObj->components[GfComTransform::COMPONENT_INDEX] == nullptr) {
    return false;
  }

  return mObj->components[GfComTransform::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComTransform::m_rtti);
}

f32 GfObjAcc::getAlpha(OBJ_ALPHA type) const {
  f32 alpha = 1.0f;
  if (mObj != nullptr) {
    GfComProperty *property = mObj->getComponent<GfComProperty>();
    if (property != nullptr && property->alpha != nullptr) {
      alpha = property->alpha->alphas[type];
    }
  }

  return alpha;
}

void GfObjAcc::setAlpha(OBJ_ALPHA type, f32 alpha) {
  if (mObj != nullptr && getAlpha(type) != alpha) {
    MsgObjectAlpha message(type, alpha);
    mObj->sendMessage(mObj, message);
    if (isAlphaChanged() && GfObjManager::get() != nullptr) {
      GfObjManager::get()->addApplyParam(getHandle());
    }
  }
}

bool GfObjAcc::isAlphaChanged() const {
  if (mObj != nullptr) {
    GfComProperty *property = mObj->getComponent<GfComProperty>();
    if (property != nullptr) {
      GfPropertyAlpha *alpha = property->alpha;
      if (alpha != nullptr) {
        GfObjAcc parentAcc(GfObjUtil::getParentObj(mObj));
        if (parentAcc.isAlphaChanged()) {
          return true;
        }

        return alpha->isChanged;
      }
    }
  }

  return false;
}

void GfObjAcc::addApplyParam() {
  if (GfObjManager::get() != nullptr) {
    GfObjManager::get()->addApplyParam(getHandle());
  }
}

void GfObjAcc::setAlphaEvent(f32 alpha) { setAlpha(OBJ_ALPHA_EVENT, alpha); }

f32 GfObjAcc::getAlphaEvent() const { return getAlpha(OBJ_ALPHA_EVENT); }

void GfObjAcc::setAlphaEvtDisp(f32 alpha) { setAlpha(OBJ_ALPHA_EVT_DISP, alpha); }

f32 GfObjAcc::getAlphaEvtDisp() const { return getAlpha(OBJ_ALPHA_EVT_DISP); }

void GfObjAcc::setAlphaFade(f32 alpha) { setAlpha(OBJ_ALPHA_FADE, alpha); }

f32 GfObjAcc::getAlphaFade() const { return getAlpha(OBJ_ALPHA_FADE); }

void GfObjAcc::setAlphaCamera(f32 alpha) { setAlpha(OBJ_ALPHA_CAMERA, alpha); }

f32 GfObjAcc::getAlphaCamera() const { return getAlpha(OBJ_ALPHA_CAMERA); }

void GfObjAcc::setAlphaLife(f32 alpha) { setAlpha(OBJ_ALPHA_LIFE, alpha); }

f32 GfObjAcc::getAlphaLife() const { return getAlpha(OBJ_ALPHA_LIFE); }

void GfObjAcc::setAlphaNormal(f32 alpha) { setAlpha(OBJ_ALPHA_NORMAL, alpha); }

f32 GfObjAcc::getAlphaNormal() const { return getAlpha(OBJ_ALPHA_NORMAL); }

f32 GfObjAcc::getAlpha() const {
  f32 alpha = 1.0f;
  if (mObj != nullptr) {
    GfComProperty *property = mObj->getComponent<GfComProperty>();
    if (property != nullptr && property->alpha != nullptr) {
      alpha = property->alpha->totalAlpha;
      GfObj *parent = GfObjUtil::getParentObj(mObj);
      if (parent != nullptr) {
        GfComProperty *parentProperty = parent->getComponent<GfComProperty>();
        if (parentProperty != nullptr && parentProperty->alpha != nullptr) {
          alpha *= parentProperty->alpha->totalAlpha;
          GfObj *grandParent = GfObjUtil::getParentObj(parent);
          if (grandParent != nullptr) {
            GfComProperty *grandParentProperty = grandParent->getComponent<GfComProperty>();
            if (grandParentProperty != nullptr && grandParentProperty->alpha != nullptr) {
              alpha *= grandParentProperty->alpha->totalAlpha;
            }
          }
        }
      }
    }
  }

  return alpha;
}

ml::ScnObjModel *GfObjAcc::getScnModel() const {
  if (mObj != nullptr) {
    GfComModel *model = mObj->getComponent<GfComModel>();
    if (model != nullptr && model->modelObject != nullptr) {
      return model->modelObject->getInterface();
    }
  }

  return nullptr;
}

void GfObjAcc::setFrameSpeed(f32 speed) {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setFrameSpd(speed);
  }
}

void GfObjAcc::setCameraFade(bool isEnable) { GfObjUtil::setFlag(mInfo, OBJ_FLAG_CAMERA_FADE, isEnable); }

bool GfObjAcc::setFlag(u32 flag, bool value) { return GfObjUtil::setFlag(mInfo, flag, value); }

bool GfObjAcc::isCameraFadeEnable() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_CAMERA_FADE); }

bool GfObjAcc::testFlag(u32 flag) const { return GfObjUtil::testFlag(mInfo, flag); }

bool GfObjAcc::isCameraFadeDisableForEvent() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_EVENT); }

void GfObjAcc::setCameraFadeDisableForEvent(bool isDisable) { GfObjUtil::setFlag(mInfo, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_EVENT, isDisable); }

bool GfObjAcc::isCameraFadeDisableForBattle() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_BATTLE); }

void GfObjAcc::setCameraFadeDisableForBattle(bool isDisable) { GfObjUtil::setFlag(mInfo, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_BATTLE, isDisable); }

bool GfObjAcc::hasParent() const { return mObj != nullptr && GfObjUtil::getParentObj(mObj) != nullptr; }

GfObj *GfObjAcc::getObj() const { return mObj; }

GF_OBJ_HANDLE *GfObjAcc::getHandle() const { return mInfo != nullptr ? mInfo->handle : INVALID_HANDLE; }

bool GfObjAcc::isDisp(OBJDISP disp) const {
  if (mObj == nullptr) {
    return true;
  }

  if (disp != 0) {
    return (mInfo->dispFlags & disp) == 0;
  }

  return mInfo->dispFlags == 0;
}

bool GfObjAcc::isDispChanged() const {
  if (mObj == nullptr) {
    return false;
  }

  GfObjAcc parentAcc(GfObjUtil::getParentObj(mObj));
  if (parentAcc.isDispChanged()) {
    return true;
  }

  return GfObjUtil::testFlag(mInfo, OBJ_FLAG_DISP_CHANGED);
}

void GfObjAcc::applyDisp() {
  if (mObj == nullptr) {
    return;
  }

  bool isDisp;
  if (mInfo->dispFlags == 0) {
    GfObj *parent = GfObjUtil::getParentObj(mObj);
    if (parent == nullptr) {
      isDisp = true;
    } else {
      isDisp = GfObjManager::getObjInfo(parent->handle)->dispFlags == 0;
    }
  } else {
    isDisp = false;
  }

  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setDisp(isDisp);
  }

  if (GfObjUtil::testFlag(mInfo, OBJ_FLAG_DISP_CHANGED)) {
    GfObjUtil::setFlag(mInfo, OBJ_FLAG_DISP_CHANGED, false);
  }
}

void GfObjAcc::setClip(bool isClip) { GfObjUtil::setFlag(mInfo, OBJ_FLAG_CLIP, isClip); }

void GfObjAcc::setGpuClip(bool isClip) { GfObjUtil::setFlag(mInfo, OBJ_FLAG_GPU_CLIP, isClip); }

void GfObjAcc::setModelScale(f32 scale) {
  if (mObj == nullptr) {
    return;
  }

  mm::Vec3 &modelScale = mInfo->modelScale;
  modelScale.x = scale;
  modelScale.y = scale;
  modelScale.z = scale;
  GfComModel *model = mObj->getComponent<GfComModel>();
  if (model != nullptr) {
    model->setModelScale(scale);
  }
}

const mm::Vec3 &GfObjAcc::getModelScaleXYZ() const { return mInfo != nullptr ? mInfo->modelScale : mm::Vec3::unit; }

f32 GfObjAcc::getModelScale() const { return getModelScaleXYZ().x; }

void GfObjAcc::setModelScaleForDebug(f32 scale) {
  if (mInfo == nullptr) {
    return;
  }

  mm::Vec3 &modelScale = mInfo->modelScale;
  modelScale.x = scale;
  modelScale.y = scale;
  modelScale.z = scale;
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setScl(mInfo->modelScale);
  }
}

void GfObjAcc::setGravity(bool isGravity) {}

bool GfObjAcc::isGravity() const { return false; }

bool GfObjAcc::isReload() const {
  if (GfObjUtil::testFlag(mInfo, OBJ_FLAG_RELOAD)) {
    return true;
  }

  return GfAssetManager::isReload(mInfo->assetHandle);
}

bool GfObjAcc::isRebuild() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_REBUILD); }

void GfObjAcc::setToolMode(bool isToolMode) { GfObjUtil::setFlag(mInfo, OBJ_FLAG_TOOL_MODE, isToolMode); }

bool GfObjAcc::isToolMode() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_TOOL_MODE); }

void GfObjAcc::setAttribute(u32 attribute) {
  if (mObj != nullptr) {
    mObj->attribute = attribute;
  }
}

u32 GfObjAcc::getAttribute() const { return mObj != nullptr ? mObj->attribute : 0; }

void GfObjAcc::applyClip() {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setClip(GfObjUtil::testFlag(mInfo, OBJ_FLAG_CLIP));
  }
}

void GfObjAcc::applyClipGpu() {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResMdlInfo modelInfo(model);
    modelInfo.setGpuClip(GfObjUtil::testFlag(mInfo, OBJ_FLAG_GPU_CLIP));
  }
}

bool GfObjAcc::isValidProperty() const {
  if (mObj == nullptr || mObj->components[GfComProperty::COMPONENT_INDEX] == nullptr) {
    return false;
  }

  return mObj->components[GfComProperty::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComProperty::m_rtti);
}

bool GfObjAcc::isValidModel() const {
  if (mObj == nullptr || mObj->components[GfComModel::COMPONENT_INDEX] == nullptr) {
    return false;
  }

  return mObj->components[GfComModel::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComModel::m_rtti);
}

bool GfObjAcc::isDestroy() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_DESTROY); }

u32 GfObjAcc::getType() const { return mObj != nullptr ? mObj->type : 0; }

void GfObjAcc::setCalcCameraAlpha() { GfObjUtil::setFlag(mInfo, OBJ_FLAG_CALC_CAMERA_ALPHA, true); }

u16 GfObjAcc::getMultiBindUniqId() const { return mInfo != nullptr ? mInfo->multiBindUniqId : 0; }

bool GfObjAcc::isMultiBindWaiting() const {
  if (mInfo == nullptr || mInfo->multiBindUniqId == 0) {
    return false;
  }

  return !GfObjManager::get()->isValidMultiBind(mInfo->handle, mInfo->multiBindUniqId);
}

GF_ASSET_HANDLE *GfObjAcc::getAssetHandle() const { return mInfo != nullptr ? mInfo->assetHandle : reinterpret_cast<GF_ASSET_HANDLE *>(-1); }

GF_OBJ_HANDLE *GfObjAcc::getTarget() const {
  if (mObj != nullptr) {
    GfComProperty *property = mObj->getComponent<GfComProperty>();
    if (property != nullptr && property->target != nullptr) {
      return property->target->handle;
    }
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfObjAcc::getMaster() const { return mInfo != nullptr ? mInfo->master : INVALID_HANDLE; }

void GfObjAcc::setUserData(GfObjUserData type, u64 data) {
  if (mInfo != nullptr) {
    mInfo->userData[type] = data;
  }
}

u64 GfObjAcc::getUserData(GfObjUserData type) const { return mInfo != nullptr ? mInfo->userData[type] : 0; }

u32 GfObjAcc::getBdatId() const {
  if (mObj == nullptr) {
    return 0;
  }

  switch (mObj->type) {
  case OBJECT_TYPE_MAP:
    return mm::mtl::dynamicCast<GfObjSetupMap>(GfObjManager::getObjInfo(getHandle())->setup)->bdatId;
  case OBJECT_TYPE_DRIVER:
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_NPC:
  case OBJECT_TYPE_MOB:
  case OBJECT_TYPE_GIMMICK:
  case 9:
  case OBJECT_TYPE_PC_WEAPON:
  case 15:
    return GfObjUtil::getObjSetup(getHandle())->id;
  case OBJECT_TYPE_ENEMY:
    return mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(getHandle())->setup)->getEnArrangeID();
  default:
    return 0;
  }
}

u32 GfObjAcc::getDriverId() const { return getBdatId(); }

u32 GfObjAcc::getBladeId() const {
  GfObjSetup *setup = GfObjUtil::getObjSetup(getHandle());
  if (setup != nullptr) {
    switch (setup->characterType) {
    case CHARACTER_TYPE_ENEMY_BLADE:
      return GfDataEnemy::getBladeID(getBdatId());
    default:
      return getBdatId();
    }
  }

  return getBdatId();
}

bool GfObjAcc::isEnemyBlade() const {
  GfObjSetup *setup = GfObjUtil::getObjSetup(getHandle());
  return setup != nullptr && setup->characterType == CHARACTER_TYPE_ENEMY_BLADE;
}

u32 GfObjAcc::getEnArrangeId() const { return getBdatId(); }

u32 GfObjAcc::getEnRscId() const {
  if (mObj == nullptr || mObj->type != OBJECT_TYPE_ENEMY) {
    return 0;
  }

  return mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(getHandle())->setup)->id;
}

u32 GfObjAcc::getEnParamId() const {
  if (mObj == nullptr || mObj->type != OBJECT_TYPE_ENEMY) {
    return 0;
  }

  return mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(getHandle())->setup)->enParamId;
}

u32 GfObjAcc::getNpcRscId() const { return getBdatId(); }

u32 GfObjAcc::getMobRscId() const { return getBdatId(); }

u32 GfObjAcc::getPcWeaponId() const { return getBdatId(); }

u32 GfObjAcc::getUiObjId() const { return getBdatId(); }

bool GfObjAcc::isMasterObjValid() const {
  if (mInfo != nullptr && mInfo->master != INVALID_HANDLE && GfObjUtil::isValid(mInfo->master)) {
    return GfObjUtil::isUpdate(mInfo->master);
  }

  return true;
}

bool GfObjAcc::isLoadedWaitOK() const {
  if (!isMasterObjValid() || GfObjUtil::testFlag(mInfo, OBJ_FLAG_LOADED_WAIT_BLOCK)) {
    return false;
  }

  if (GfObjUtil::testFlag(mInfo, OBJ_FLAG_LOADED_WAIT)) {
    return GfObjUtil::testFlag(mInfo, OBJ_FLAG_LOADED_WAIT_OK);
  }

  return true;
}

u16 GfObjAcc::getView() const { return mInfo != nullptr ? mInfo->view : 0; }

u32 GfObjAcc::getLayer() const { return mObj != nullptr ? mObj->layer : 4; }

bool GfObjAcc::isLayerPause() const { return fw::Framework::isLayerPause(getLayer()); }

void GfObjAcc::setExtMeshAlpha(u32 index, f32 alpha) {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResSubMesh subMesh(model);
    if (subMesh.getExtMax() > 0) {
      subMesh.setExtAlpha(index, alpha);
    }
  }
}

f32 GfObjAcc::getExtMeshAlpha(u32 index) const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResSubMesh subMesh(model);
    return subMesh.getExtAlpha(index);
  }

  return 1.0f;
}

int GfObjAcc::getExtMeshMax() const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResSubMesh subMesh(model);
    return subMesh.getExtMax();
  }

  return 0;
}

int GfObjAcc::getExtMeshIdx(const char *name) const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResSubMesh subMesh(model);
    return subMesh.getExtIdx(name);
  }

  return -1;
}

const char *GfObjAcc::getExtMeshName(int index) const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResSubMesh subMesh(model);
    return subMesh.getExtName(index);
  }

  return "";
}

bool GfObjAcc::isUpdated() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_UPDATED); }

const char *GfObjAcc::getDebugName() const { return ""; }

bool GfObjAcc::isBattle() const {
  if (btl::CharacterManager::get() != nullptr) {
    btl::BattleCharacter *character = btl::CharacterManager::get()->GetCharacterConst(getHandle());
    if (character != nullptr) {
      btl::CharacterParameter *parameter = character->GetCharacterParameter(false);
      if (parameter != nullptr) {
        return parameter->isBattle;
      }
    }
  }

  return false;
}

GF_MOUNT_HANDLE *GfObjAcc::getMountHandle(GFATTACH attach) const {
  return mInfo != nullptr ? mInfo->mounts[attach].handle : reinterpret_cast<GF_MOUNT_HANDLE *>(-1);
}

void GfObjAcc::setupExtraParts() {
  ml::ScnObjModel *model = getScnModel();
  if (model == nullptr) {
    return;
  }

  ml::ScnObjAccResSubMesh subMesh(model);
  subMesh.getExtMax();
  DataParamAcc paramAcc(getType(), getBdatId(), GIMMICK_TYPE_NONE);
  int count = paramAcc.getObjType() == OBJECT_TYPE_ENEMY ? 4 : 6;
  for (int i = 0; i < count; i++) {
    int index = subMesh.getExtIdx(EXTRA_PARTS_NAMES[i]);
    if (index >= 0) {
      subMesh.setExtAlpha(index, paramAcc.isDispInitExtraParts(i) ? 1.0f : 0.0f);
    }
  }
}

void GfObjAcc::setEtcParam(int index, f32 value) {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccEtcParams etcParams(model);
    etcParams.setInitParams(index, value);
  }
}

int GfObjAcc::getEtcParamIndex(const char *name) const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccEtcParams etcParams(model);
    return etcParams.getIndex(name);
  }

  return -1;
}

bool GfObjAcc::isPartyObj() const { return GfObjUtil::testFlag(mInfo, OBJ_FLAG_PARTY_OBJ); }

int GfObjAcc::getPartyID() const { return GfObjUtil::getPartyID(getHandle()); }

bool GfObjAcc::isCollideModelClip() const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResMdlInfo modelInfo(model);
    return modelInfo.isCamCheckResl();
  }

  return false;
}

void GfObjAcc::setEnableCollideModelClip(bool isEnable) {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResMdlInfo modelInfo(model);
    modelInfo.setCamCheckMode(isEnable);
  }
}

} // namespace gf
