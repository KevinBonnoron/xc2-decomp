#include "gf/object/gf_obj_acc.h"

#include "anm/anm_skeleton.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "framework/framework.h"
#include "framework/object/component_object.h"
#include "fw/fw_model_object.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "ml/scn_obj_model.h"
#include "mm_math/mm_aabb.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"
#include "scn/scn_obj_acc.h"

namespace gf {

static const char *EXTRA_PARTS_NAMES[] = {
    "ExtraPartsA",
    "ExtraPartsB",
    "ExtraPartsC",
    "ExtraPartsD",
    "ExtraPartsE",
    "ExtraPartsF",
};

GfObjAcc::GfObjAcc(GfObj *obj) : m_obj(obj) { unknown00 = obj != nullptr ? GfObjManager::getObjInfo(obj->unknownf8) : nullptr; }

GfObjAcc::GfObjAcc(GF_OBJ_HANDLE *handle) {
  unknown00 = GfObjManager::getObjInfo(handle);
  if (unknown00 == nullptr) {
    m_obj = nullptr;
  } else {
    m_obj = unknown00->unknown18;
  }
}

int GfObjAcc::getBoneIdx(const char *name) {
  if (m_obj != nullptr) {
    GfComModel *model = m_obj->getComponent<GfComModel>();
    if (model != nullptr && model->unknown28 != nullptr) {
      u16 bone = anm::Skeleton::INVALID_BONE;
      if (name != nullptr) {
        bone = model->unknown28->getBoneID(name);
      }
      return static_cast<s16>(bone);
    }
  }

  return -1;
}

bool GfObjAcc::isValidTransform() const {
  if (m_obj == nullptr || m_obj->unknown38[GfComTransform::COMPONENT_INDEX] == nullptr) {
    return false;
  }

  return m_obj->unknown38[GfComTransform::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComTransform::m_rtti);
}

f32 GfObjAcc::getAlpha(OBJ_ALPHA type) const {
  f32 alpha = 1.0f;
  if (m_obj != nullptr) {
    GfComProperty *property = m_obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown20 != nullptr) {
      alpha = property->unknown20->unknown00[type];
    }
  }

  return alpha;
}

void GfObjAcc::setAlpha(OBJ_ALPHA type, f32 alpha) {
  if (m_obj != nullptr && getAlpha(type) != alpha) {
    MsgObjectAlpha message(type, alpha);
    m_obj->sendMessage(m_obj, message);
    if (isAlphaChanged() && GfObjManager::get() != nullptr) {
      GfObjManager::get()->addApplyParam(getHandle());
    }
  }
}

bool GfObjAcc::isAlphaChanged() const {
  if (m_obj != nullptr) {
    GfComProperty *property = m_obj->getComponent<GfComProperty>();
    if (property != nullptr) {
      GfPropertyAlpha *alpha = property->unknown20;
      if (alpha != nullptr) {
        GfObjAcc parentAcc(GfObjUtil::getParentObj(m_obj));
        if (parentAcc.isAlphaChanged()) {
          return true;
        }

        return alpha->unknown1c;
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
  if (m_obj != nullptr) {
    GfComProperty *property = m_obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown20 != nullptr) {
      alpha = property->unknown20->unknown18;
      GfObj *parent = GfObjUtil::getParentObj(m_obj);
      if (parent != nullptr) {
        GfComProperty *parentProperty = parent->getComponent<GfComProperty>();
        if (parentProperty != nullptr && parentProperty->unknown20 != nullptr) {
          alpha *= parentProperty->unknown20->unknown18;
          GfObj *grandParent = GfObjUtil::getParentObj(parent);
          if (grandParent != nullptr) {
            GfComProperty *grandParentProperty = grandParent->getComponent<GfComProperty>();
            if (grandParentProperty != nullptr && grandParentProperty->unknown20 != nullptr) {
              alpha *= grandParentProperty->unknown20->unknown18;
            }
          }
        }
      }
    }
  }

  return alpha;
}

ml::ScnObjModel *GfObjAcc::getScnModel() const {
  if (m_obj != nullptr) {
    GfComModel *model = m_obj->getComponent<GfComModel>();
    if (model != nullptr && model->unknown18 != nullptr) {
      return model->unknown18->getInterface();
    }
  }

  return nullptr;
}

f32 GfObjAcc::getModelAlpha() const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    return model->getAlpha();
  }

  return 1.0f;
}

f32 GfObjAcc::getModelRadius() const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    return model->getLength();
  }

  return 0.0f;
}

bool GfObjAcc::getModelAabb(mm::Aabb &aabb) const {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    aabb.set(model->getAABBMin(), model->getAABBMax());
    return true;
  }

  return false;
}

void GfObjAcc::applyAlpha() {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setAlpha(getAlpha());
  }
}

void GfObjAcc::setFrameSpeed(f32 speed) {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setFrameSpd(speed);
  }
}

void GfObjAcc::setCameraFade(bool isEnable) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_CAMERA_FADE, isEnable); }

bool GfObjAcc::setFlag(u32 flag, bool value) { return GfObjUtil::setFlag(unknown00, flag, value); }

bool GfObjAcc::isCameraFadeEnable() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_CAMERA_FADE); }

bool GfObjAcc::testFlag(u32 flag) const { return GfObjUtil::testFlag(unknown00, flag); }

bool GfObjAcc::isCameraFadeDisableForEvent() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_EVENT); }

void GfObjAcc::setCameraFadeDisableForEvent(bool isDisable) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_EVENT, isDisable); }

bool GfObjAcc::isCameraFadeDisableForBattle() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_BATTLE); }

void GfObjAcc::setCameraFadeDisableForBattle(bool isDisable) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_CAMERA_FADE_DISABLE_FOR_BATTLE, isDisable); }

bool GfObjAcc::hasParent() const { return m_obj != nullptr && GfObjUtil::getParentObj(m_obj) != nullptr; }

GfObj *GfObjAcc::getObj() const { return m_obj; }

GF_OBJ_HANDLE *GfObjAcc::getHandle() const { return unknown00 != nullptr ? unknown00->unknown08 : INVALID_HANDLE; }

bool GfObjAcc::isDisp(OBJDISP disp) const {
  if (m_obj == nullptr) {
    return true;
  }

  if (disp != 0) {
    return (unknown00->unknown48 & disp) == 0;
  }

  return unknown00->unknown48 == 0;
}

bool GfObjAcc::isDispChanged() const {
  if (m_obj == nullptr) {
    return false;
  }

  GfObjAcc parentAcc(GfObjUtil::getParentObj(m_obj));
  if (parentAcc.isDispChanged()) {
    return true;
  }

  return GfObjUtil::testFlag(unknown00, OBJ_FLAG_DISP_CHANGED);
}

void GfObjAcc::applyDisp() {
  if (m_obj == nullptr) {
    return;
  }

  bool isDisp;
  if (unknown00->unknown48 == 0) {
    GfObj *parent = GfObjUtil::getParentObj(m_obj);
    if (parent == nullptr) {
      isDisp = true;
    } else {
      isDisp = GfObjManager::getObjInfo(parent->unknownf8)->unknown48 == 0;
    }
  } else {
    isDisp = false;
  }

  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setDisp(isDisp);
  }

  if (GfObjUtil::testFlag(unknown00, OBJ_FLAG_DISP_CHANGED)) {
    GfObjUtil::setFlag(unknown00, OBJ_FLAG_DISP_CHANGED, false);
  }
}

void GfObjAcc::setClip(bool isClip) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_CLIP, isClip); }

void GfObjAcc::setGpuClip(bool isClip) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_GPU_CLIP, isClip); }

void GfObjAcc::setModelScale(f32 scale) {
  if (m_obj == nullptr) {
    return;
  }

  mm::Vec3 &modelScale = unknown00->unknowna0;
  modelScale.x = scale;
  modelScale.y = scale;
  modelScale.z = scale;
  GfComModel *model = m_obj->getComponent<GfComModel>();
  if (model != nullptr) {
    model->setModelScale(scale);
  }
}

const mm::Vec3 &GfObjAcc::getModelScaleXYZ() const { return unknown00 != nullptr ? unknown00->unknowna0 : mm::Vec3::unit; }

f32 GfObjAcc::getModelScale() const { return getModelScaleXYZ().x; }

void GfObjAcc::setModelScaleForDebug(f32 scale) {
  if (unknown00 == nullptr) {
    return;
  }

  mm::Vec3 &modelScale = unknown00->unknowna0;
  modelScale.x = scale;
  modelScale.y = scale;
  modelScale.z = scale;
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setScl(unknown00->unknowna0);
  }
}

void GfObjAcc::setGravity(bool isGravity) {}

bool GfObjAcc::isGravity() const { return false; }

bool GfObjAcc::isReload() const {
  if (GfObjUtil::testFlag(unknown00, OBJ_FLAG_RELOAD)) {
    return true;
  }

  return GfAssetManager::isReload(unknown00->unknown10);
}

bool GfObjAcc::isRebuild() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_REBUILD); }

void GfObjAcc::setToolMode(bool isToolMode) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_TOOL_MODE, isToolMode); }

bool GfObjAcc::isToolMode() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_TOOL_MODE); }

void GfObjAcc::setAttribute(u32 attribute) {
  if (m_obj != nullptr) {
    m_obj->unknown110 = attribute;
  }
}

u32 GfObjAcc::getAttribute() const { return m_obj != nullptr ? m_obj->unknown110 : 0; }

void GfObjAcc::applyClip() {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setClip(GfObjUtil::testFlag(unknown00, OBJ_FLAG_CLIP));
  }
}

void GfObjAcc::applyClipGpu() {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResMdlInfo modelInfo(model);
    modelInfo.setGpuClip(GfObjUtil::testFlag(unknown00, OBJ_FLAG_GPU_CLIP));
  }
}

bool GfObjAcc::isValidProperty() const {
  if (m_obj == nullptr || m_obj->unknown38[GfComProperty::COMPONENT_INDEX] == nullptr) {
    return false;
  }

  return m_obj->unknown38[GfComProperty::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComProperty::m_rtti);
}

bool GfObjAcc::isValidModel() const {
  if (m_obj == nullptr || m_obj->unknown38[GfComModel::COMPONENT_INDEX] == nullptr) {
    return false;
  }

  return m_obj->unknown38[GfComModel::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComModel::m_rtti);
}

bool GfObjAcc::isDestroy() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_DESTROY); }

u32 GfObjAcc::getType() const { return m_obj != nullptr ? m_obj->unknown28 : 0; }

void GfObjAcc::setCalcCameraAlpha() { GfObjUtil::setFlag(unknown00, OBJ_FLAG_CALC_CAMERA_ALPHA, true); }

u16 GfObjAcc::getMultiBindUniqId() const { return unknown00 != nullptr ? unknown00->unknown00 : 0; }

bool GfObjAcc::isMultiBindWaiting() const {
  if (unknown00 == nullptr || unknown00->unknown00 == 0) {
    return false;
  }

  return !GfObjManager::get()->isValidMultiBind(unknown00->unknown08, unknown00->unknown00);
}

GF_ASSET_HANDLE *GfObjAcc::getAssetHandle() const { return unknown00 != nullptr ? unknown00->unknown10 : reinterpret_cast<GF_ASSET_HANDLE *>(-1); }

GF_OBJ_HANDLE *GfObjAcc::getTarget() const {
  if (m_obj != nullptr) {
    GfComProperty *property = m_obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown18 != nullptr) {
      return property->unknown18->handle;
    }
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfObjAcc::getMaster() const { return unknown00 != nullptr ? unknown00->unknown88 : INVALID_HANDLE; }

void GfObjAcc::setUserData(GfObjUserData type, u64 data) {
  if (unknown00 != nullptr) {
    unknown00->unknown70[type] = data;
  }
}

u64 GfObjAcc::getUserData(GfObjUserData type) const { return unknown00 != nullptr ? unknown00->unknown70[type] : 0; }

u32 GfObjAcc::getBdatId() const {
  if (m_obj == nullptr) {
    return 0;
  }

  switch (m_obj->unknown28) {
  case OBJECT_TYPE_MAP:
    return mm::mtl::dynamicCast<GfObjSetupMap>(GfObjManager::getObjInfo(getHandle())->unknown30)->unknown6c;
  case OBJECT_TYPE_DRIVER:
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_NPC:
  case OBJECT_TYPE_MOB:
  case OBJECT_TYPE_GIMMICK:
  case 9:
  case OBJECT_TYPE_PC_WEAPON:
  case 15:
    return GfObjUtil::getObjSetup(getHandle())->unknown10;
  case OBJECT_TYPE_ENEMY:
    return mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(getHandle())->unknown30)->getEnArrangeID();
  default:
    return 0;
  }
}

u32 GfObjAcc::getDriverId() const { return getBdatId(); }

u32 GfObjAcc::getBladeId() const {
  GfObjSetup *setup = GfObjUtil::getObjSetup(getHandle());
  if (setup != nullptr) {
    switch (setup->unknown1c) {
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
  return setup != nullptr && setup->unknown1c == CHARACTER_TYPE_ENEMY_BLADE;
}

u32 GfObjAcc::getEnArrangeId() const { return getBdatId(); }

u32 GfObjAcc::getEnRscId() const {
  if (m_obj == nullptr || m_obj->unknown28 != OBJECT_TYPE_ENEMY) {
    return 0;
  }

  return mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(getHandle())->unknown30)->unknown10;
}

u32 GfObjAcc::getEnParamId() const {
  if (m_obj == nullptr || m_obj->unknown28 != OBJECT_TYPE_ENEMY) {
    return 0;
  }

  return mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(getHandle())->unknown30)->unknown6c;
}

u32 GfObjAcc::getNpcRscId() const { return getBdatId(); }

u32 GfObjAcc::getMobRscId() const { return getBdatId(); }

u32 GfObjAcc::getPcWeaponId() const { return getBdatId(); }

u32 GfObjAcc::getUiObjId() const { return getBdatId(); }

bool GfObjAcc::isMasterObjValid() const {
  if (unknown00 != nullptr && unknown00->unknown88 != INVALID_HANDLE && GfObjUtil::isValid(unknown00->unknown88)) {
    return GfObjUtil::isUpdate(unknown00->unknown88);
  }

  return true;
}

bool GfObjAcc::isLoadedWaitOK() const {
  if (!isMasterObjValid() || GfObjUtil::testFlag(unknown00, OBJ_FLAG_LOADED_WAIT_BLOCK)) {
    return false;
  }

  if (GfObjUtil::testFlag(unknown00, OBJ_FLAG_LOADED_WAIT)) {
    return GfObjUtil::testFlag(unknown00, OBJ_FLAG_LOADED_WAIT_OK);
  }

  return true;
}

u16 GfObjAcc::getView() const { return unknown00 != nullptr ? unknown00->unknown02 : 0; }

u32 GfObjAcc::getLayer() const { return m_obj != nullptr ? m_obj->unknown2c : 4; }

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

bool GfObjAcc::isUpdated() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UPDATED); }

const char *GfObjAcc::getDebugName() const { return ""; }

bool GfObjAcc::isBattle() const {
  if (btl::CharacterManager::get() != nullptr) {
    btl::BattleCharacter *character = btl::CharacterManager::get()->GetCharacterConst(getHandle());
    if (character != nullptr) {
      btl::CharacterParameter *parameter = character->GetCharacterParameter(false);
      if (parameter != nullptr) {
        return parameter->unknown5df_1;
      }
    }
  }

  return false;
}

GF_MOUNT_HANDLE *GfObjAcc::getMountHandle(GFATTACH attach) const { return unknown00 != nullptr ? unknown00->unknownb8[attach].unknown00 : reinterpret_cast<GF_MOUNT_HANDLE *>(-1); }

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

bool GfObjAcc::isPartyObj() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_PARTY_OBJ); }

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
