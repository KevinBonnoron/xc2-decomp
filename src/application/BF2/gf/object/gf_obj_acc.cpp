#include "gf/object/gf_obj_acc.h"

#include "anm/anm_pose.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "framework/coli/coli_object.h"
#include "framework/framework.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_model_object.h"
#include "fw/fw_transform.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/component/gf_com_collider.h"
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
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "scn/scn_obj_acc.h"

namespace gf {

static const char *unknown021[] = {
    // Inferred role: extra parts names; original name unknown.
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

bool GfObjAcc::getBoneTransform(fw::Transform &transform, const char *name) { return getBoneTransform(transform, getBoneIdx(name)); }

bool GfObjAcc::getBoneTransform(fw::Transform &transform, int bone) {
  if (m_obj == nullptr || bone == -1) {
    return false;
  }

  GfComModel *model = m_obj->getComponent<GfComModel>();
  if (model == nullptr) {
    return false;
  }

  anm::Pose *pose = model->unknown30;
  if (pose == nullptr) {
    return false;
  }

  fw::TransformUtil::mul(getWorldTransform(), pose->getBoneModelSpace(bone), model->m_modelScale, &transform);
  return true;
}

bool GfObjAcc::getBoneTransformModelSpace(fw::Transform &transform, const char *name) { return getBoneTransformModelSpace(transform, getBoneIdx(name)); }

bool GfObjAcc::getBoneTransformModelSpace(fw::Transform &transform, int bone) {
  if (m_obj == nullptr || bone == -1) {
    return false;
  }

  GfComModel *model = m_obj->getComponent<GfComModel>();
  if (model == nullptr) {
    return false;
  }

  anm::Pose *pose = model->unknown30;
  if (pose == nullptr) {
    return false;
  }

  const anm::QsTransform &boneTransform = pose->getBoneModelSpace(bone);
  transform.unknown00 = mm::Vec3(boneTransform.unknown00.x, boneTransform.unknown00.y, boneTransform.unknown00.z);
  transform.unknown10 = boneTransform.unknown10;
  return true;
}

bool GfObjAcc::isValidTransform() const {
  if (m_obj == nullptr || m_obj->unknown38[GfComTransform::COMPONENT_INDEX] == nullptr) {
    return false;
  }

  return m_obj->unknown38[GfComTransform::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComTransform::m_rtti);
}

const fw::Transform &GfObjAcc::getWorldTransform() const {
  static fw::Transform transform;
  if (m_obj != nullptr) {
    GfComTransform *com = m_obj->getComponent<GfComTransform>();
    if (com != nullptr) {
      return com->unknown10->getSyncedWorldTransform();
    }
  }

  transform.unknown00 = mm::Vec3::zero;
  transform.unknown10 = mm::Quat::identity;
  return transform;
}

const fw::Transform &GfObjAcc::getWorldTransformNoSync() const {
  static fw::Transform transform;
  if (m_obj != nullptr) {
    GfComTransform *com = m_obj->getComponent<GfComTransform>();
    if (com != nullptr) {
      return com->unknown10->unknown40;
    }
  }

  transform.unknown00 = mm::Vec3::zero;
  transform.unknown10 = mm::Quat::identity;
  return transform;
}

f32 GfObjAcc::getAlpha(OBJ_ALPHA type) const {
  f32 alpha = 1.0f;
  if (m_obj != nullptr) {
    GfComProperty *property = m_obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown20.get() != nullptr) {
      alpha = property->unknown20.get()->unknown00[type];
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
      GfAlphaProperty *alpha = property->unknown20.get();
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

void GfObjAcc::setAlphaEvent(f32 alpha) { setAlpha(OBJ_ALPHA_UNKNOWN_3, alpha); }

f32 GfObjAcc::getAlphaEvent() const { return getAlpha(OBJ_ALPHA_UNKNOWN_3); }

void GfObjAcc::setAlphaEvtDisp(f32 alpha) { setAlpha(OBJ_ALPHA_UNKNOWN_5, alpha); }

f32 GfObjAcc::getAlphaEvtDisp() const { return getAlpha(OBJ_ALPHA_UNKNOWN_5); }

void GfObjAcc::setAlphaFade(f32 alpha) { setAlpha(OBJ_ALPHA_UNKNOWN_1, alpha); }

f32 GfObjAcc::getAlphaFade() const { return getAlpha(OBJ_ALPHA_UNKNOWN_1); }

void GfObjAcc::setAlphaCamera(f32 alpha) { setAlpha(OBJ_ALPHA_UNKNOWN_2, alpha); }

f32 GfObjAcc::getAlphaCamera() const { return getAlpha(OBJ_ALPHA_UNKNOWN_2); }

void GfObjAcc::setAlphaLife(f32 alpha) { setAlpha(OBJ_ALPHA_UNKNOWN_4, alpha); }

f32 GfObjAcc::getAlphaLife() const { return getAlpha(OBJ_ALPHA_UNKNOWN_4); }

void GfObjAcc::setAlphaNormal(f32 alpha) { setAlpha(OBJ_ALPHA_UNKNOWN_0, alpha); }

f32 GfObjAcc::getAlphaNormal() const { return getAlpha(OBJ_ALPHA_UNKNOWN_0); }

f32 GfObjAcc::getAlpha() const {
  f32 alpha = 1.0f;
  if (m_obj != nullptr) {
    GfComProperty *property = m_obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown20.get() != nullptr) {
      alpha = property->unknown20.get()->unknown18;
      GfObj *parent = GfObjUtil::getParentObj(m_obj);
      if (parent != nullptr) {
        GfComProperty *parentProperty = parent->getComponent<GfComProperty>();
        if (parentProperty != nullptr && parentProperty->unknown20.get() != nullptr) {
          alpha *= parentProperty->unknown20.get()->unknown18;
          GfObj *grandParent = GfObjUtil::getParentObj(parent);
          if (grandParent != nullptr) {
            GfComProperty *grandParentProperty = grandParent->getComponent<GfComProperty>();
            if (grandParentProperty != nullptr && grandParentProperty->unknown20.get() != nullptr) {
              alpha *= grandParentProperty->unknown20.get()->unknown18;
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

void GfObjAcc::setCameraFade(bool isEnable) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_10, isEnable); }

void GfObjAcc::setRenderCameraFade(bool isEnable) {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResMdlInfo modelInfo(model);
    modelInfo.setSpAlphaMode(isEnable);
  }

  for (mm::mtl::IntrusiveList<fw::UpdatableObject>::iterator it = m_obj->unknownb8.begin(), last = m_obj->unknownb8.end(); it != last; ++it) {
    GfObjAcc childAcc(mm::mtl::dynamicCast<GfObj>(it.operator->())->unknownf8);
    childAcc.setRenderCameraFade(isEnable);
  }
}

bool GfObjAcc::setFlag(u32 flag, bool value) { return GfObjUtil::setFlag(unknown00, flag, value); }

bool GfObjAcc::isCameraFadeEnable() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_10); }

bool GfObjAcc::testFlag(u32 flag) const { return GfObjUtil::testFlag(unknown00, flag); }

bool GfObjAcc::isCameraFadeDisableForEvent() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_11); }

void GfObjAcc::setCameraFadeDisableForEvent(bool isDisable) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_11, isDisable); }

bool GfObjAcc::isCameraFadeDisableForBattle() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_12); }

void GfObjAcc::setCameraFadeDisableForBattle(bool isDisable) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_12, isDisable); }

void GfObjAcc::setCollisionChar(bool isEnable) {
  if (m_obj == nullptr) {
    return;
  }

  GfComCollider *collider = m_obj->getComponent<GfComCollider>();
  if (collider == nullptr) {
    return;
  }

  for (u32 i = 0; i < collider->unknown18.size(); i++) {
    if (collider->unknown18[i] != nullptr) {
      if (isEnable) {
        collider->unknown18[i]->setState(fw::COLI_STATE_UNKNOWN_1);
      } else {
        collider->unknown18[i]->clearState(fw::COLI_STATE_UNKNOWN_1);
      }
    }
  }
}

bool GfObjAcc::hasParent() const { return m_obj != nullptr && GfObjUtil::getParentObj(m_obj) != nullptr; }

GfObj *GfObjAcc::getObj() const { return m_obj; }

GF_OBJ_HANDLE *GfObjAcc::getHandle() const { return unknown00 != nullptr ? unknown00->unknown08 : unknown020; }

bool GfObjAcc::isDisp(OBJDISP disp) const {
  if (m_obj == nullptr) {
    return true;
  }

  if (disp != 0) {
    return (unknown00->unknown48 & disp) == 0;
  }

  return unknown00->unknown48 == 0;
}

void GfObjAcc::setDisp(OBJDISP disp, bool isDisp) {
  if (m_obj == nullptr) {
    return;
  }

  bool isHidden = (unknown00->unknown48 & disp) != 0;
  if (isHidden == isDisp) {
    u32 flags = unknown00->unknown48;
    if (isDisp) {
      flags &= ~disp;
    } else {
      flags |= disp;
    }
    unknown00->unknown48 = flags;
    GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_1, true);
    for (mm::mtl::IntrusiveList<fw::UpdatableObject>::iterator it = m_obj->unknownb8.begin(), last = m_obj->unknownb8.end(); it != last; ++it) {
      GfObjUtil::setFlag(GfObjManager::getObjInfo(mm::mtl::dynamicCast<GfObj>(it.operator->())->unknownf8), OBJ_FLAG_UNKNOWN_1, true);
    }
  }

  GfWeapon *weapon = GfObjUtil::getExtraMountObject(getHandle());
  if (weapon != nullptr) {
    for (u32 index = 0; index < 10; index++) {
      GF_OBJ_HANDLE *handle = weapon->getCurrentHandles()[index];
      if (handle != unknown020 && handle != getHandle()) {
        GfObjAcc weaponAcc(handle);
        weaponAcc.setDisp(OBJDISP_UNKNOWN_1, isDisp);
      }
    }
  }
}

bool GfObjAcc::isDispChanged() const {
  if (m_obj == nullptr) {
    return false;
  }

  GfObjAcc parentAcc(GfObjUtil::getParentObj(m_obj));
  if (parentAcc.isDispChanged()) {
    return true;
  }

  return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_1);
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

  if (GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_1)) {
    GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_1, false);
  }
}

void GfObjAcc::setClip(bool isClip) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_2, isClip); }

void GfObjAcc::setGpuClip(bool isClip) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_3, isClip); }

void GfObjAcc::setModelScaleForMenu(const mm::Vec3 &scale) {
  if (m_obj == nullptr) {
    return;
  }

  unknown00->unknowna0 = scale;
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    f32 setupScale = GfObjUtil::getSetupScale(getHandle());
    mm::Vec3 modelScale = scale * setupScale;
    GfObj *parent = GfObjUtil::getParentObj(m_obj);
    if (parent != nullptr) {
      modelScale *= GfObjUtil::getSetupScale(parent->unknownf8);
    }
    model->setScl(modelScale);
  }
}

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
  if (GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_5)) {
    return true;
  }

  return GfAssetManager::isReload(unknown00->unknown10);
}

bool GfObjAcc::isRebuild() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_6); }

void GfObjAcc::setToolMode(bool isToolMode) { GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_24, isToolMode); }

bool GfObjAcc::isToolMode() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_24); }

void GfObjAcc::setAttribute(u32 attribute) {
  if (m_obj != nullptr) {
    m_obj->unknown110 = attribute;
  }
}

u32 GfObjAcc::getAttribute() const { return m_obj != nullptr ? m_obj->unknown110 : 0; }

void GfObjAcc::applyClip() {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    model->setClip(GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_2));
  }
}

void GfObjAcc::applyClipGpu() {
  ml::ScnObjModel *model = getScnModel();
  if (model != nullptr) {
    ml::ScnObjAccResMdlInfo modelInfo(model);
    modelInfo.setGpuClip(GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_3));
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

bool GfObjAcc::isDestroy() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_0); }

u32 GfObjAcc::getType() const { return m_obj != nullptr ? m_obj->unknown28 : 0; }

void GfObjAcc::setCalcCameraAlpha() { GfObjUtil::setFlag(unknown00, OBJ_FLAG_UNKNOWN_13, true); }

u32 GfObjAcc::getMultiBindUniqId() const { return unknown00 != nullptr ? unknown00->unknown00 : 0; }

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
    if (property != nullptr && property->unknown18.get() != nullptr) {
      return property->unknown18.get()->handle;
    }
  }

  return unknown020;
}

GF_OBJ_HANDLE *GfObjAcc::getMaster() const { return unknown00 != nullptr ? unknown00->unknown88 : unknown020; }

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
  case OBJECT_TYPE_PC:
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
    case unknown030_5:
      return GfDataEnemy::getBladeID(getBdatId());
    default:
      return getBdatId();
    }
  }

  return getBdatId();
}

bool GfObjAcc::isEnemyBlade() const {
  GfObjSetup *setup = GfObjUtil::getObjSetup(getHandle());
  return setup != nullptr && setup->unknown1c == unknown030_5;
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
  if (unknown00 != nullptr && unknown00->unknown88 != unknown020 && GfObjUtil::isValid(unknown00->unknown88)) {
    return GfObjUtil::isUpdate(unknown00->unknown88);
  }

  return true;
}

bool GfObjAcc::isLoadedWaitOK() const {
  if (!isMasterObjValid() || GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_26)) {
    return false;
  }

  if (GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_8)) {
    return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_9);
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

bool GfObjAcc::isUpdated() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_19); }

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
  DataParamAcc paramAcc(getType(), getBdatId(), GIMMICK_TYPE_UNKNOWN_0);
  int count = paramAcc.getObjType() == OBJECT_TYPE_ENEMY ? 4 : 6;
  for (int i = 0; i < count; i++) {
    int index = subMesh.getExtIdx(unknown021[i]);
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

bool GfObjAcc::isPartyObj() const { return GfObjUtil::testFlag(unknown00, OBJ_FLAG_UNKNOWN_18); }

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

void GfObjAcc::setCollisionGround(bool isCollisionGround) {
  if (m_obj == nullptr) {
    return;
  }

  GfComCollider *collider = m_obj->getComponent<GfComCollider>();
  if (collider == nullptr) {
    return;
  }

  for (u32 i = 0; i < collider->unknown18.size(); i++) {
    if (collider->unknown18[i] != nullptr) {
      if (isCollisionGround) {
        collider->unknown18[i]->setState(fw::COLI_STATE_UNKNOWN_0);
      } else {
        collider->unknown18[i]->clearState(fw::COLI_STATE_UNKNOWN_0);
      }
    }
  }
}

} // namespace gf
