#include "gf/object/gf_obj_util.h"

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_blow_rotate_solver.h"
#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_look_solver.h"
#include "framework/ik/ik_placement_ground_solver.h"
#include "framework/ik/ik_rotate_solver.h"
#include "framework/ik/ik_slope_ground_solver.h"
#include "framework/ik/ik_spherical_coordinates_solver.h"
#include "framework/ik/ik_spine_rotate_solver.h"
#include "framework/ik/ik_spine_solver.h"
#include "framework/ik/ik_trans_solver.h"
#include "framework/ik/ik_two_chara_ground_solver.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/pointer_map.h"
#include "framework/reference_frame.h"
#include "fw/fw_model_object.h"
#include "fw/fw_transform.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_extend_resource.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_player_picker.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/behavior/gf_com_behavior_weapon.h"
#include "gf/object/component/behavior/plugin/gf_eye_blink_plugin.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_append_info.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_volume_fade.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"
#include "scn/scn_obj_acc.h"

namespace fw {
class IkSolver;
} // namespace fw

namespace gf {

// Inferred helper: ik component of the object; original name unknown.
static GfComIK *unknown001(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  return obj != nullptr ? obj->getComponent<GfComIK>() : nullptr;
}

template <typename T> static T *castSolver(const mm::mtl::IntrusivePtr<fw::IkSolver> &solver) {
  if (solver.get() == nullptr) {
    return nullptr;
  }
  return mm::mtl::dynamicCast<T>(solver.get());
}

void GfObjUtil::addDebugName(GF_OBJ_HANDLE *handle) {}

void GfObjUtil::addGfObj(GF_OBJ_HANDLE *handle, GfObj *obj) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown18 = obj;
  }
}

bool GfObjUtil::mountToBone(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *parent, const char *bone) {
  if (parent == INVALID_HANDLE) {
    return false;
  }

  GFOBJ_INFO *parentInfo = GfObjManager::getObjInfo(parent);
  if (parentInfo == nullptr) {
    return false;
  }

  if (parentInfo->unknown18 != nullptr) {
    GfComModel *model = parentInfo->unknown18->getComponent<GfComModel>();
    if (model != nullptr) {
      GfComTransform *transform = GfObjManager::getObjInfo(handle)->unknown18->getComponent<GfComTransform>();
      if (!model->addBoneReferenceFrame(bone, transform->unknown10)) {
        return false;
      }
    }

    GfObj *parentObj = GfObjUtil::getObj(parent);
    GfObj *childObj = GfObjUtil::getObj(handle);
    if (parentObj != nullptr && childObj != nullptr) {
      parentObj->addChild(childObj);
    }

    GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
    info->unknown3e0 = bone;
    return true;
  }

  return false;
}

bool GfObjUtil::unmountFromBone(GF_OBJ_HANDLE *handle) {
  if (handle == INVALID_HANDLE) {
    return false;
  }

  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info == nullptr) {
    return false;
  }

  GfObj *obj = info->unknown18;
  if (obj == nullptr) {
    return false;
  }

  GfObj *parentObj = getParentObj(obj);
  if (parentObj == nullptr) {
    return false;
  }

  GFOBJ_INFO *mountInfo = GfObjManager::getObjInfo(handle);
  GfComModel *model = parentObj->getComponent<GfComModel>();
  if (model != nullptr) {
    GfComTransform *transform = obj->getComponent<GfComTransform>();
    if (transform->unknown10->unknowna8 != nullptr) {
      model->removeBoneReferenceFrame(mountInfo->unknown3e0.c_str(), transform->unknown10);
    }
  }

  GfObj *mountedParentObj = getObj(getParentHandle(handle));
  GfObj *mountedObj = getObj(handle);
  if (mountedParentObj != nullptr && mountedObj != nullptr) {
    mountedParentObj->removeChild(mountedObj);
  }

  mountInfo->unknown3e0 = "";
  return true;
}

bool GfObjUtil::attachGfObj(GF_OBJ_HANDLE *parent, GF_OBJ_HANDLE *child) {
  GfObj *parentObj = getObj(parent);
  GfObj *childObj = getObj(child);
  if (parentObj == nullptr || childObj == nullptr) {
    return false;
  }

  GfComTransform *parentTransform = parentObj->getComponent<GfComTransform>();
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> *parentFrame;
  if (parentTransform->unknown18.get() == nullptr) {
    parentFrame = &parentTransform->unknown10;
  } else {
    parentFrame = &parentTransform->unknown18;
  }
  GfComTransform *childTransform = mm::mtl::dynamicCast<GfComTransform>(childObj->unknown38[GfComTransform::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &childFrame = childTransform->unknown10;
  if (childFrame->unknowna8 != nullptr) {
    return false;
  }

  (*parentFrame)->addChild(*childFrame);
  childFrame->unknown001();
  childFrame->syncLocalTransform();
  return true;
}

bool GfObjUtil::dettachGfObject(GF_OBJ_HANDLE *parent, GF_OBJ_HANDLE *child) {
  GfObj *parentObj = getObj(parent);
  GfObj *childObj = getObj(child);
  if (parentObj == nullptr || childObj == nullptr) {
    return false;
  }

  GfComTransform *parentTransform = parentObj->getComponent<GfComTransform>();
  if (parentTransform == nullptr) {
    return false;
  }

  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &parentFrame = parentTransform->unknown18.get() == nullptr ? parentTransform->unknown10 : parentTransform->unknown18;
  GfComTransform *childTransform = mm::mtl::dynamicCast<GfComTransform>(childObj->unknown38[GfComTransform::COMPONENT_INDEX]);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> &childFrame = childTransform->unknown10;
  if (childFrame->unknowna8 != parentFrame.get()) {
    return false;
  }

  parentFrame->removeChild(*childFrame);
  childFrame->unknown001();
  childFrame->syncLocalTransform();
  return true;
}

void GfObjUtil::removeGfObj(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown18 = nullptr;
  }
}

u32 GfObjUtil::getObjType(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->unknown28 : 0;
}

void GfObjUtil::setEnableBlowRotateIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    fw::BlowRotateIkSolver *solver = castSolver<fw::BlowRotateIkSolver>(ik->unknown10.unknown10[unknown002_1]);
    if (solver != nullptr) {
      if (isEnable) {
        solver->fadeIn(time);
      } else {
        solver->fadeOut(time);
      }
    }
  }
}

void GfObjUtil::setEnableBodyIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    fw::RotateIkSolver *rotate = castSolver<fw::RotateIkSolver>(ik->unknown10.unknown10[unknown002_0]);
    if (rotate != nullptr) {
      if (isEnable) {
        rotate->fadeIn(time);
      } else {
        rotate->fadeOut(time);
      }
    }
    fw::SpineRotateIKSolver *spine = castSolver<fw::SpineRotateIKSolver>(ik->unknown10.unknown10[unknown002_4]);
    if (spine != nullptr) {
      if (isEnable) {
        spine->fadeIn(time);
      } else {
        spine->fadeOut(time);
      }
    }
  }
}

void GfObjUtil::setEnableLookIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    fw::LookIkSolver *look = castSolver<fw::LookIkSolver>(ik->unknown10.unknown10[unknown002_3]);
    if (look != nullptr) {
      if (isEnable) {
        look->fadeIn(time);
      } else {
        look->fadeOut(time);
      }
    }
    fw::SpineIkSolver *spine = castSolver<fw::SpineIkSolver>(ik->unknown10.unknown10[unknown002_3]);
    if (spine != nullptr) {
      if (isEnable) {
        spine->fadeIn(time);
      } else {
        spine->fadeOut(time);
      }
    }
    fw::LookAtIkSolver *lookAt = castSolver<fw::LookAtIkSolver>(ik->unknown10.unknown10[unknown002_5]);
    if (lookAt != nullptr) {
      if (isEnable) {
        lookAt->fadeIn(time);
      } else {
        lookAt->fadeOut(time);
      }
    }
  }
}

void GfObjUtil::setEnableFootIK(GF_OBJ_HANDLE *handle, bool isEnable) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    fw::PlacementGroundSolver *placement = castSolver<fw::PlacementGroundSolver>(ik->unknown10.unknown10[unknown002_2]);
    if (placement != nullptr) {
      placement->unknown65 = isEnable;
      placement->setEnablePlacement(isEnable);
    }
    fw::SlopeGroundSolver *slope = castSolver<fw::SlopeGroundSolver>(ik->unknown10.unknown10[unknown002_0]);
    if (slope != nullptr) {
      slope->setEnablePlacement(isEnable);
      slope->unknown88 = isEnable;
    }
    fw::TwoCharaGroundSolver *twoChara = castSolver<fw::TwoCharaGroundSolver>(ik->unknown10.unknown10[unknown002_2]);
    if (twoChara != nullptr) {
      twoChara->unknownb9 = isEnable;
      twoChara->setEnablePlacement(isEnable);
    }
  }
}

void GfObjUtil::setEnableSPCIK(GF_OBJ_HANDLE *handle, bool isEnable) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    fw::SphericalCoordinatesIkSolver *solver = castSolver<fw::SphericalCoordinatesIkSolver>(ik->unknown10.unknown10[unknown002_8]);
    if (solver != nullptr) {
      solver->m_enable = true;
    }
  }
}

void GfObjUtil::setBlowRotate(GF_OBJ_HANDLE *handle, const mm::Quat &rotation) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    fw::BlowRotateIkSolver *solver = castSolver<fw::BlowRotateIkSolver>(ik->unknown10.unknown10[unknown002_1]);
    if (solver != nullptr) {
      solver->unknown40 = rotation;
    }
  }
}

void GfObjUtil::setEnableEyeBlink(GF_OBJ_HANDLE *handle, bool isEnable) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComBehavior *behavior = obj->getComponent<GfComBehavior>();
    if (behavior != nullptr && behavior->unknown10.unknown28.size() > 1) {
      Plugin *plugin = behavior->unknown10.unknown28[1];
      if (plugin != nullptr && mm::mtl::dynamicCast<EyeBlinkPlugin>(plugin) != nullptr) {
        plugin->setActivate(isEnable);
      }
    }
  }
}

void GfObjUtil::setEnableLipSync(GF_OBJ_HANDLE *handle, bool isEnable) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComBehavior *behavior = obj->getComponent<GfComBehavior>();
    if (behavior != nullptr && behavior->unknown10.unknown28.size() > 2) {
      Plugin *plugin = behavior->unknown10.unknown28[2];
      if (plugin != nullptr && mm::mtl::dynamicCast<LipSyncPlugin>(plugin) != nullptr) {
        plugin->setActivate(isEnable);
      }
    }
  }
}

u32 GfObjUtil::getEyeIKType(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj == nullptr) {
    return 0;
  }
  GfComIK *ik = obj->getComponent<GfComIK>();
  if (ik != nullptr) {
    u32 index = unknown002_6;
    if (ik->unknown10.unknown10[unknown002_6].get() == nullptr) {
      index = unknown002_7;
    }
    if (castSolver<fw::TransLocalIkSolver>(ik->unknown10.unknown10[index]) != nullptr) {
      return 1;
    }
    if (castSolver<fw::RotateLocalIkSolver>(ik->unknown10.unknown10[index]) != nullptr) {
      return 2;
    }
  }
  return 0;
}

const mm::Quat &GfObjUtil::getBlowRotate(GF_OBJ_HANDLE *handle) {
  const mm::Quat *rotation = &mm::Quat::identity;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComIK *ik = obj->getComponent<GfComIK>();
    if (ik != nullptr) {
      fw::BlowRotateIkSolver *solver = castSolver<fw::BlowRotateIkSolver>(ik->unknown10.unknown10[unknown002_1]);
      if (solver != nullptr) {
        const mm::Quat &blowRotate = solver->unknown40;
        if (solver->isEnable()) {
          rotation = &blowRotate;
        }
      }
    }
  }
  return *rotation;
}

void GfObjUtil::setEnableEyeIK(GF_OBJ_HANDLE *handle, bool isEnable, f32 time) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    u32 type = getEyeIKType(handle);
    if (isEnable) {
      if (type == 1) {
        for (u32 i = unknown002_6; i <= unknown002_7; i++) {
          fw::TransLocalIkSolver *solver = castSolver<fw::TransLocalIkSolver>(ik->unknown10.unknown10[i]);
          if (solver != nullptr) {
            solver->fadeIn(time);
          }
        }
      } else if (type == 2) {
        for (u32 i = unknown002_6; i <= unknown002_7; i++) {
          fw::RotateLocalIkSolver *solver = castSolver<fw::RotateLocalIkSolver>(ik->unknown10.unknown10[i]);
          if (solver != nullptr) {
            solver->fadeIn(time);
          }
        }
      }
    } else {
      if (type == 1) {
        for (u32 i = unknown002_6; i <= unknown002_7; i++) {
          fw::TransLocalIkSolver *solver = castSolver<fw::TransLocalIkSolver>(ik->unknown10.unknown10[i]);
          if (solver != nullptr) {
            solver->fadeOut(time);
          }
        }
      } else if (type == 2) {
        for (u32 i = unknown002_6; i <= unknown002_7; i++) {
          fw::RotateLocalIkSolver *solver = castSolver<fw::RotateLocalIkSolver>(ik->unknown10.unknown10[i]);
          if (solver != nullptr) {
            solver->fadeOut(time);
          }
        }
      }
    }
  }
}

void GfObjUtil::setMoveEyeIK(GF_OBJ_HANDLE *handle, f32 moveX, f32 moveY) {
  GfComIK *ik = unknown001(handle);
  if (ik != nullptr) {
    u32 type = getEyeIKType(handle);
    u32 control;
    {
      DataParamAcc paramAcc(handle);
      control = paramAcc.getEyeRotControl();
    }
    if (type == 1) {
      fw::TransLocalIkSolver *first = castSolver<fw::TransLocalIkSolver>(ik->unknown10.unknown10[unknown002_6]);
      if (first != nullptr) {
        first->unknown40 = mm::Vec3(moveX, 0.0f, moveY);
      }
      fw::TransLocalIkSolver *second = castSolver<fw::TransLocalIkSolver>(ik->unknown10.unknown10[unknown002_7]);
      if (second != nullptr) {
        second->unknown40 = mm::Vec3(moveX, 0.0f, moveY);
      }
    } else if (type == 2) {
      fw::RotateLocalIkSolver *first = castSolver<fw::RotateLocalIkSolver>(ik->unknown10.unknown10[unknown002_6]);
      if (first != nullptr) {
        switch (control) {
        case 1:
        case 4:
          first->unknown40 = mm::Vec3(0.0f, moveY, moveX);
          break;
        case 2:
          first->unknown40 = mm::Vec3(moveY, 0.0f, -moveX);
          break;
        case 6:
          first->unknown40 = mm::Vec3(0.0f, -moveY, -moveX);
          break;
        case 7:
          first->unknown40 = mm::Vec3(moveX, -moveY, 0.0f);
          break;
        }
      }
      fw::RotateLocalIkSolver *second = castSolver<fw::RotateLocalIkSolver>(ik->unknown10.unknown10[unknown002_7]);
      if (second != nullptr) {
        switch (control) {
        case 1:
        case 4:
          second->unknown40 = mm::Vec3(0.0f, moveY, moveX);
          break;
        case 2:
          second->unknown40 = mm::Vec3(moveY, 0.0f, -moveX);
          break;
        case 6:
          second->unknown40 = mm::Vec3(0.0f, -moveY, -moveX);
          break;
        case 7:
          second->unknown40 = mm::Vec3(-moveX, -moveY, 0.0f);
          break;
        }
      }
    }
  }
}

GfObj *GfObjUtil::getObj(GF_OBJ_HANDLE *handle) {
  if (handle == INVALID_HANDLE) {
    return nullptr;
  }

  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown18 : nullptr;
}

u32 GfObjUtil::getObjLayer(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->unknown2c : 4;
}

f32 GfObjUtil::getSetupScale(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown30 != nullptr ? info->unknown30->unknown40 : 1.0f;
}

GfObjSetup *GfObjUtil::getObjSetup(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown30 : nullptr;
}

GF_ASSET_HANDLE *GfObjUtil::getAssetHandle(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown10 : reinterpret_cast<GF_ASSET_HANDLE *>(-1);
}

void GfObjUtil::destroy(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
    GfObjAcc acc(handle);
    if (acc.isValid()) {
      if (acc.setFlag(OBJ_FLAG_DESTROY, true)) {
        if (GfObjManager::get() != nullptr) {
          GfObjManager::get()->addDestroyObj(handle, true);
        }
        applyExecUpdate(acc.getObj());
      }
      if (acc.isValid()) {
        GfObj *obj = acc.getObj();
        for (mm::mtl::IntrusiveList<fw::UpdatableObject>::iterator it = obj->unknownb8.begin(), last = obj->unknownb8.end(); it != last; ++it) {
          destroy(mm::mtl::dynamicCast<GfObj>(it.operator->())->unknownf8);
        }
      }
    }
  }
}

void GfObjUtil::applyExecUpdate(GfObj *obj) { obj->unknown118 = isUpdateComponent(obj) && !isFollowObjNotReady(obj->unknownf8); }

GF_OBJ_HANDLE *GfObjUtil::getParentHandle(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    fw::UpdatableObject *parent = obj->unknownd0.get();
    if (parent != nullptr) {
      GfObj *parentObj = mm::mtl::dynamicCast<GfObj>(parent);
      if (parentObj != nullptr) {
        return parentObj->unknownf8;
      }
    }
  }

  return INVALID_HANDLE;
}

GfObj *GfObjUtil::getParentObj(GfObj *obj) {
  fw::UpdatableObject *parent = obj->unknownd0.get();
  if (parent == nullptr) {
    return nullptr;
  }

  return mm::mtl::dynamicCast<GfObj>(parent);
}

u32 GfObjUtil::getLayerSection(u32 layer) {
  switch (layer) {
  case 0:
    return 0;
  case 1:
  case 2:
  case 3:
    return 1;
  case 4:
  case 5:
  case 6:
    return 4;
  case 7:
  case 8:
  case 9:
    return 7;
  case 10:
  case 11:
  case 12:
    return 10;
  default:
    return 4;
  }
}

void GfObjUtil::changeLayer(GfObj *obj, u32 layer) {
  u32 oldLayer = obj->unknown2c;
  for (u32 i = 0; i < fw::UpdatableObject::COMPONENT_MAX; i++) {
    fw::ComponentObject *component = obj->unknown38[i];
    if (component != nullptr) {
      GfComponent *gfComponent = mm::mtl::dynamicCast<GfComponent>(component);
      if (gfComponent != nullptr) {
        gfComponent->changeLayer(oldLayer, layer);
      }
    }
  }

  obj->unknown2c = layer;
}

void GfObjUtil::changeLayer(GF_OBJ_HANDLE *handle, u32 layer) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    changeLayer(obj, layer);
  }
}

const char *GfObjUtil::getResourceName(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getModelResourceName();
}

const char *GfObjUtil::getModelResourceName(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getModelResourceName();
}

const char *GfObjUtil::getMotionResourceName(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getMotionResourceName();
}

const char *GfObjUtil::getAddResourceName(GF_OBJ_HANDLE *handle) {
  switch (getObjType(handle)) {
  case OBJECT_TYPE_ENEMY: {
    DataParamAcc paramAcc(handle);
    return GfBdatRsc::get()->getRscEnRefMotion(paramAcc.getBdatIdEnRsc());
  }
  case OBJECT_TYPE_NPC: {
    DataParamAcc paramAcc(handle);
    return GfDataNpc::getAddMotionName(paramAcc.isValid() ? paramAcc.getBdatId() : 0);
  }
  }

  return nullptr;
}

void GfObjUtil::resetWeaponMotion(GF_OBJ_HANDLE *handle, OPTMNT type) {
  GfGameMount *mount = GfMountManager::getMount(getMountHandle(handle, GFATTACH_WEAPON));
  if (mount != nullptr) {
    if (type == OPTMNT_UNKNOWN_FFFFFFFF) {
      type = mount->unknown20;
    }
    GF_OBJ_HANDLE *owner = mount->getHandle(type);
    if (handle != INVALID_HANDLE) {
      for (u32 i = 0; i < 10; i++) {
        GfObj *obj = getObj(handle);
        if (obj != nullptr) {
          GfObj *weapon = getObj(mount->unknown18->getCurrentHandles()[i]);
          if (weapon != nullptr) {
            MsgObjectForceWeaponMount message(type, owner);
            obj->sendMessage(weapon, message);
          }
        }
      }
    }
  }
}

GF_MOUNT_HANDLE *GfObjUtil::getMountHandle(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknownb8[attach].unknown00 : reinterpret_cast<GF_MOUNT_HANDLE *>(-1);
}

u32 GfObjUtil::getGameObjectID(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr && info->unknown30 != nullptr) {
    GfObjSetup *setup = info->unknown30;
    if (getObjType(handle) != OBJECT_TYPE_ENEMY) {
      return setup->unknown10;
    }

    GfObjSetupEnemy *setupEnemy = mm::mtl::dynamicCast<GfObjSetupEnemy>(setup);
    if (setupEnemy != nullptr) {
      return setupEnemy->m_enArrangeID;
    }
  }

  return 0xffffffff;
}

void GfObjUtil::setLimitHP(GF_OBJ_HANDLE *handle, u32 limitHp) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    MsgObjectLimitHP message(limitHp);
    obj->sendMessage(obj, message);
  }
}

u32 GfObjUtil::getLimitHP(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      return property->unknown10->unknown14;
    }
  }

  return 0;
}

void GfObjUtil::setInvincible(GF_OBJ_HANDLE *handle, bool invincible, bool invincibleSub) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    MsgObjectInvincible message(invincible, invincibleSub);
    obj->sendMessage(obj, message);
  }
}

bool GfObjUtil::testInvincible(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool invincible;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      invincible = property->unknown10->unknown18;
      isFound = true;
    }
  }

  return invincible & isFound;
}

void GfObjUtil::setInvincibleForDebug(GF_OBJ_HANDLE *handle, bool invincible) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      property->unknown30->invincible = invincible;
    }
  }
}

bool GfObjUtil::testInvincibleForDebug(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool invincible;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      invincible = property->unknown30->invincible;
      isFound = true;
    }
  }

  return invincible & isFound;
}

void GfObjUtil::setDisableFallDeadForDebug(GF_OBJ_HANDLE *handle, bool disableFallDead) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      property->unknown30->disableFallDead = disableFallDead;
    }
  }
}

bool GfObjUtil::testDisableFallDeadForDebug(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool disableFallDead;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown30 != nullptr) {
      disableFallDead = property->unknown30->disableFallDead;
      isFound = true;
    }
  }

  return disableFallDead & isFound;
}

void GfObjUtil::setDisableAutoHeal(GF_OBJ_HANDLE *handle, bool disableAutoHeal) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    MsgObjectStopAutoHeal message(disableAutoHeal);
    obj->sendMessage(obj, message);
  }
}

bool GfObjUtil::testDisableAutoHeal(GF_OBJ_HANDLE *handle) {
  bool isFound = false;
  bool disableAutoHeal;
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      disableAutoHeal = property->unknown10->unknown1a;
      isFound = true;
    }
  }

  return disableAutoHeal & isFound;
}

GfObjProperty *GfObjUtil::getProperty(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown98 : nullptr;
}

u32 GfObjUtil::getHp(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->unknown10 != nullptr) {
      return property->unknown10->unknown10;
    }
  }

  return 0;
}

int GfObjUtil::getPartyID(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info == nullptr || info->unknown30 == nullptr) {
    return -1;
  }

  return info->unknown30->unknown14;
}

GfWeapon *GfObjUtil::getWeaponMountObject(GF_OBJ_HANDLE *handle) { return GfMountManager::getAppendHandles(handle, GFATTACH_WEAPON); }

GfWeapon *GfObjUtil::getExtraMountObject(GF_OBJ_HANDLE *handle) { return GfMountManager::getAppendHandles(handle, GFATTACH_APPEND); }

bool GfObjUtil::isValid(GF_OBJ_HANDLE *handle) { return getObj(handle) != nullptr; }

bool GfObjUtil::isLoading(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown06 == GFOBJ_STATE_LOADING;
}

bool GfObjUtil::isUpdate(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown06 == GFOBJ_STATE_UPDATE;
}

void GfObjUtil::setOwner(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown90 = owner;
  }
}

GF_OBJ_HANDLE *GfObjUtil::getOwner(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown90 : INVALID_HANDLE;
}

void GfObjUtil::reload(GF_OBJ_HANDLE *handle) {}

bool GfObjUtil::isExistAsm(GF_OBJ_HANDLE *handle) {
  GfExtendResource *resource = GfAssetManager::getExtentResource(getAssetHandle(handle), 0);
  if (resource == nullptr) {
    return false;
  }
  if (!resource->getRTTI()->isKindOf(&GfExtendPacking::m_rtti)) {
    return false;
  }
  return static_cast<GfExtendPacking *>(resource)->unknown10 != nullptr;
}

bool GfObjUtil::isEnemyBlade(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  if (objAcc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }

  GfObjSetup *setup = getObjSetup(handle);
  return setup != nullptr && setup->unknown1c == unknown030_5;
}

bool GfObjUtil::testFlag(GF_OBJ_HANDLE *handle, u32 flag) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown38.test(flag);
}

bool GfObjUtil::testFlag(const GfObj *obj, u32 flag) { return obj->unknown100 != nullptr && obj->unknown100->unknown38.test(flag); }

void GfObjUtil::copyTransformToSetup(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *setupHandle) {
  GfObjAcc acc(handle);
  if (acc.isValidTransform()) {
    GfObjSetup *setup = getObjSetup(setupHandle);
    if (setup != nullptr) {
      setup->setInitialTransform(acc.getWorldTransform());
    }
  }
}

void GfObjUtil::copyTransformToSetup(GF_OBJ_HANDLE *handle, const mm::Vec3 &position, const mm::Vec3 &rotation) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    GfObjSetup *setup = info->unknown30;
    if (setup != nullptr) {
      setup->unknown20 = position;
      setup->unknown30 = rotation;
    }
  }
}

void GfObjUtil::saveRebuildInfo(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  GfObjSetup *setup = getObjSetup(handle);
  mm::Vec3 rotation = mm::quatToEuler(acc.getWorldTransform().unknown10);
  setup->unknown20 = acc.getWorldTransform().unknown00;
  setup->unknown30 = mm::Vec3(0.0f, rotation.y, 0.0f);
  if (acc.getType() == OBJECT_TYPE_DRIVER) {
    GfObjSetupDriver *driver = getObjSetup<GfObjSetupDriver>(handle);
    GfComPropertyPc *property = acc.getObj()->getComponent<GfComPropertyPc>();
    if (property != nullptr) {
      driver->unknown70 = property->unknown38;
    }
  } else if (acc.getType() == OBJECT_TYPE_BLADE) {
    GfObjSetupBlade *blade = getObjSetup<GfObjSetupBlade>(handle);
    GfComPropertyPc *property = acc.getObj()->getComponent<GfComPropertyPc>();
    if (property != nullptr) {
      blade->unknown74 = property->unknown38;
    }
  }
}

void GfObjUtil::rebuild(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.isValid()) {
    if (acc.getUserData(OBJ_USER_DATA_GMK) == 0) {
      acc.setFlag(OBJ_FLAG_REBUILD, true);
      if (GfObjManager::get() != nullptr) {
        GfObjManager::get()->addDestroyObj(handle, false);
      }
    } else {
      destroy(handle);
    }
  }
}

const char *GfObjUtil::getModelBaseName(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info == nullptr ? "" : info->unknown404.c_str();
}

const char *GfObjUtil::getAssetModelName(GF_OBJ_HANDLE *handle) { return GfAssetManager::getModelInfo(getAssetHandle(handle)); }

const char *GfObjUtil::getAssetMotionName(GF_OBJ_HANDLE *handle) { return GfAssetManager::getMotionInfo(getAssetHandle(handle)); }

u32 GfObjUtil::getEyeRotControl(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  return paramAcc.getEyeRotControl();
}

GfComModel *GfObjUtil::getComModel(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  return obj != nullptr ? obj->getComponent<GfComModel>() : nullptr;
}

GfVolumeFade *GfObjUtil::getVolumeFade(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr ? info->unknown3d8 : nullptr;
}

bool GfObjUtil::isBattle(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  bool isFound = false;
  bool isBattle;
  if (info != nullptr && info->unknown98 != nullptr && info->unknown98->unknown10 != nullptr) {
    isBattle = info->unknown98->unknown10->unknown30;
    isFound = true;
  }

  return isFound & isBattle;
}

void GfObjUtil::createVolumeFade(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  GfComModel *model = obj->getComponent<GfComModel>();
  if (model != nullptr) {
    GfObjSetup *setup = getObjSetup(handle);
    GFOBJ_INFO *info = GfObjManager::getObjInfo(obj->unknownf8);
    info->createVolumeFade(model);
    if (info->unknown3d8 != nullptr) {
      if (setup->unknown64 == VFACC_UNKNOWN_FFFFFFFF) {
        if (setup->isEvent()) {
          return;
        }

        DataParamAcc paramAcc(handle);
        if (paramAcc.getObjType() == OBJECT_TYPE_BLADE) {
          u32 attribute = paramAcc.getAttribute(-1, false);
          if (attribute != 0) {
            info->unknown3d8->setEffectType(static_cast<VFEFF>(attribute));
            info->unknown3d8->applyFadeRatio();
          }
        }
      } else {
        setVolumeFadeUserFlag(handle, true);
        DataParamAcc paramAcc(handle);
        info->unknown3d8->setEffectType(static_cast<VFEFF>(paramAcc.getAttribute(-1, false)));
        info->unknown3d8->setFadeRatio(setup->unknown64, VFPARTS_UNKNOWN_FFFFFFFF, 0.0f);
        setup->unknown64 = VFACC_UNKNOWN_FFFFFFFF;
        ml::ScnObjAccEtcParams etcParams(model->unknown18->getInterface());
        if (etcParams.getMax() != 0) {
          for (u32 i = 0; i < 6; i++) {
            etcParams.setInitParams(i, 1.0f);
          }
        }
      }
    }
  }
}

bool GfObjUtil::isVolumeFadeForUser(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown38.test(OBJ_FLAG_VOLUME_FADE_FOR_USER);
}

void GfObjUtil::setVolumeFadeUserFlag(GF_OBJ_HANDLE *handle, bool isForUser) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr && info->unknown38.test(OBJ_FLAG_VOLUME_FADE_FOR_USER) != isForUser) {
    info->unknown38.set(OBJ_FLAG_VOLUME_FADE_FOR_USER, isForUser);
  }
}

bool GfObjUtil::isStanbyTalkingPlayer(GF_OBJ_HANDLE *handle) {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  GfObjProperty *property = getProperty(handle);
  if (formation == nullptr || property == nullptr) {
    return false;
  }
  unknown070 *move = property->unknown18;
  if (move == nullptr) {
    return false;
  }
  if (move->unknown7f) {
    return false;
  }
  return !formation->isFarRandomTalk(handle);
}

void GfObjUtil::setTalking(GF_OBJ_HANDLE *handle, bool isTalking) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr) {
    info->unknown38.set(OBJ_FLAG_TALKING, isTalking);
  }
}

bool GfObjUtil::isTalking(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  return info != nullptr && info->unknown38.test(OBJ_FLAG_TALKING);
}

bool GfObjUtil::isSearchEmptyResource(GF_OBJ_HANDLE *handle) {
  GF_ASSET_HANDLE *assetHandle = getAssetHandle(handle);
  if (GfAssetManager::get() != nullptr) {
    return GfAssetManager::get()->isFullResource(assetHandle);
  }

  return false;
}

GfAssetResource *GfObjUtil::getResourceEab(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj == nullptr) {
    return nullptr;
  }

  switch (obj->unknown28) {
  case OBJECT_TYPE_DRIVER:
  case OBJECT_TYPE_BLADE:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(36), ASSET_TYPE_BASE);
  case OBJECT_TYPE_ENEMY:
  case OBJECT_TYPE_NPC:
  case OBJECT_TYPE_MOB:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(10), ASSET_TYPE_BASE);
  case OBJECT_TYPE_GIMMICK:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(4), ASSET_TYPE_BASE);
  case OBJECT_TYPE_EVENT:
  case OBJECT_TYPE_BELONGING:
  case OBJECT_TYPE_UNKNOWN_14:
  case OBJECT_TYPE_UI:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(3), ASSET_TYPE_BASE);
  default:
    return nullptr;
  }
}

GfAssetResource *GfObjUtil::getResourceEfb(GF_OBJ_HANDLE *handle) {
  GfObj *obj = getObj(handle);
  if (obj == nullptr) {
    return nullptr;
  }

  switch (obj->unknown28) {
  case OBJECT_TYPE_DRIVER:
  case OBJECT_TYPE_BLADE:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(37), ASSET_TYPE_BASE);
  case OBJECT_TYPE_ENEMY:
  case OBJECT_TYPE_NPC:
  case OBJECT_TYPE_MOB:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(11), ASSET_TYPE_BASE);
  case OBJECT_TYPE_GIMMICK:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(5), ASSET_TYPE_BASE);
  case OBJECT_TYPE_EVENT:
  case OBJECT_TYPE_BELONGING:
  case OBJECT_TYPE_UNKNOWN_14:
  case OBJECT_TYPE_UI:
    return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(4), ASSET_TYPE_BASE);
  default:
    return nullptr;
  }
}

// Inferred helper: counts the weapon swt resources of the object; original name unknown.
static u32 unknown005(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  u32 count = 0;
  if (paramAcc.isValid()) {
    for (u32 index = 0x65; index < 0x99; index++) {
      if (GfAssetManager::getResource(GfObjUtil::getAssetHandle(handle), static_cast<GfFileIdx>(index), ASSET_TYPE_BASE) != nullptr) {
        count++;
      }
    }
  }

  return count;
}

u32 GfObjUtil::getWeaponResourceSwtNum(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  if (!objAcc.isValid()) {
    return 0;
  }

  u32 count = 0;
  switch (objAcc.getType()) {
  case OBJECT_TYPE_DRIVER:
    count = unknown005(handle);
    break;
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_PC_WEAPON:
    if (!GfObjManager::getObjInfo(handle)->unknown30->unknown54) {
      count = unknown005(GfGameParty::getHandleDriver(GfObjManager::getObjInfo(handle)->unknown30->unknown14));
    } else {
      count = unknown005(handle);
    }
    break;
  case OBJECT_TYPE_ENEMY:
    count = GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(3), ASSET_TYPE_BASE) != nullptr;
    count += GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(0x11), ASSET_TYPE_BASE) != nullptr;
    break;
  }

  return count;
}

// Inferred helper: counts the weapon eab resources of the object; original name unknown.
static u32 unknown006(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  u32 count = 0;
  if (paramAcc.isValid()) {
    for (u32 index = 0x9a; index < 0x26e; index++) {
      if (GfAssetManager::getResource(GfObjUtil::getAssetHandle(handle), static_cast<GfFileIdx>(index), ASSET_TYPE_BASE) != nullptr) {
        count++;
      }
    }
  }

  return count;
}

u32 GfObjUtil::getWeaponResourceEabNum(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  if (!objAcc.isValid()) {
    return 0;
  }

  u32 count = 0;
  switch (objAcc.getType()) {
  case OBJECT_TYPE_DRIVER:
    count = unknown006(handle);
    break;
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_PC_WEAPON:
    getAssetHandle(handle);
    count = unknown006(handle);
    break;
  case OBJECT_TYPE_ENEMY: {
    u32 enemyCount = GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(0x12), ASSET_TYPE_BASE) != nullptr;
    count = unknown006(handle);
    count += enemyCount;
    break;
  }
  }

  return count;
}

// Inferred helper: counts the weapon efb resources of the asset; original name unknown.
static u32 unknown007(GF_ASSET_HANDLE *asset) {
  u32 count = 0;
  for (u32 index = 0x26f; index < 0x443; index++) {
    if (GfAssetManager::getResource(asset, static_cast<GfFileIdx>(index), ASSET_TYPE_BASE) != nullptr) {
      count++;
    }
  }

  return count;
}

u32 GfObjUtil::getWeaponResourceEfbNum(GF_OBJ_HANDLE *handle) {
  DataParamAcc paramAcc(handle);
  if (!paramAcc.isValid()) {
    return 0;
  }

  u32 count = 0;
  switch (paramAcc.getObjType()) {
  case OBJECT_TYPE_DRIVER:
    count = unknown007(getAssetHandle(handle));
    break;
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_PC_WEAPON:
    getAssetHandle(handle);
    count = unknown007(getAssetHandle(handle));
    break;
  case OBJECT_TYPE_ENEMY: {
    u32 enemyCount = GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(0xb), ASSET_TYPE_BASE) != nullptr;
    enemyCount += GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(0x13), ASSET_TYPE_BASE) != nullptr;
    count = unknown007(getAssetHandle(handle));
    count = enemyCount + count;
    break;
  }
  }

  return count;
}

fw::SoundPack *GfObjUtil::getSePack(GF_OBJ_HANDLE *handle) {
  u32 type = getObjType(handle);
  GfFileIdx index = FILE_IDX_NONE;
  switch (type) {
  case OBJECT_TYPE_DRIVER:
  case OBJECT_TYPE_BLADE:
  case OBJECT_TYPE_ENEMY:
  case OBJECT_TYPE_NPC:
  case OBJECT_TYPE_MOB:
    index = FILE_IDX_MODEL;
    break;
  default:
    break;
  }
  if (type - OBJECT_TYPE_DRIVER < 5) {
    GfAssetManager *assetManager = GfAssetManager::get();
    if (assetManager != nullptr) {
      return assetManager->getSePackByFileIdx(getAssetHandle(handle), index);
    }
  }

  return nullptr;
}

fw::SoundPack *GfObjUtil::getSePackFoot1(GF_OBJ_HANDLE *handle) {
  if (getObjType(handle) - OBJECT_TYPE_DRIVER < 5) {
    GfAssetManager *assetManager = GfAssetManager::get();
    if (assetManager != nullptr) {
      return assetManager->getSePackByFileIdx(getAssetHandle(handle), static_cast<GfFileIdx>(1));
    }
  }

  return nullptr;
}

fw::SoundPack *GfObjUtil::getSePackFoot2(GF_OBJ_HANDLE *handle) {
  if (getObjType(handle) - OBJECT_TYPE_DRIVER < 5) {
    GfAssetManager *assetManager = GfAssetManager::get();
    if (assetManager != nullptr) {
      return assetManager->getSePackByFileIdx(getAssetHandle(handle), static_cast<GfFileIdx>(2));
    }
  }

  return nullptr;
}

bool GfObjUtil::getSePackAll(mm::mtl::FixedVector<fw::SoundPack *, 4> &packs, GF_OBJ_HANDLE *handle) {
  fw::SoundPack *pack = getSePack(handle);
  if (pack != nullptr) {
    packs.push_back(pack);
  }
  pack = getSePackFoot1(handle);
  if (pack != nullptr) {
    packs.push_back(pack);
  }
  pack = getSePackFoot2(handle);
  if (pack != nullptr) {
    packs.push_back(pack);
  }
  return !packs.empty();
}

bool GfObjUtil::getMobSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_OBJ_HANDLE *handle) {
  slots.clear();
  if (getObjType(handle) == OBJECT_TYPE_MOB) {
    GfAssetManager::getSlotHandle(slots, getAssetHandle(handle));
  }

  return !slots.empty();
}

// Inferred helper: mount of an object info for an attach type; original name unknown.
static GFOBJ_MOUNT *unknown004(GFOBJ_INFO *info, GFATTACH attach) { return info != nullptr ? &info->unknownb8[attach] : nullptr; }

GfAppendInfo *GfObjUtil::getAppendInfo(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GFOBJ_MOUNT *mount = unknown004(info, attach);
  return info == nullptr ? nullptr : &mount->unknown10;
}

GfAppend *GfObjUtil::getAppend(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  bool isAlternate = false;
  GfObjSetupWeapon *setup = getObjSetup<GfObjSetupWeapon>(handle);
  if (setup != nullptr) {
    isAlternate = setup->unknown78;
  }
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GFOBJ_MOUNT *mount = unknown004(info, attach);
  if (info == nullptr) {
    return nullptr;
  }
  u32 index = mount->unknown08;
  if (static_cast<s32>(index) < 0 || mount->unknown10.unknown00[isAlternate].size() <= index) {
    return nullptr;
  }
  return *mount->unknown10.unknown00[isAlternate].at(index);
}

bool GfObjUtil::isTrinityBlade(GF_OBJ_HANDLE *handle) {
  GfObjSetup *setup = getObjSetup(handle);
  return setup != nullptr && setup->unknown1c == unknown030_8;
}

bool GfObjUtil::isUpdateComponent(const GfObj *obj) {
  const GFOBJ_INFO *info = obj->unknown100;
  if (!obj->unknown114.test(OBJ_STATE_UPDATE_ENABLE) || (info != nullptr && info->unknown38.test(OBJ_FLAG_DESTROY)) || (GfObjManager::get() != nullptr && GfObjManager::get()->isSuspendUpdate()) ||
      (info != nullptr && info->unknown38.test(OBJ_FLAG_PARTY_OBJ) && !GfGameParty::isPartyMemberInGameObj())) {
    return false;
  }

  return true;
}

void GfObjUtil::applyExecUpdate(GF_OBJ_HANDLE *handle) { applyExecUpdate(getObj(handle)); }

void GfObjUtil::setWarpTransform(GF_OBJ_HANDLE *handle, const fw::Transform &transform, bool isResetState) {
  GfObj *obj = getObj(handle);
  if (obj == nullptr) {
    return;
  }
  if (isResetState) {
    MsgPcResetState message;
    obj->sendMessage(obj, message);
  }
  GfComTransform *comTransform = obj->getComponent<GfComTransform>();
  if (comTransform != nullptr) {
    comTransform->setPosition(transform.unknown00);
    comTransform->setRotation(transform.unknown10);
  }
  GfComDynamics *dynamics = obj->getComponent<GfComDynamics>();
  if (dynamics != nullptr) {
    dynamics->resetMovement();
  }
}

// Inferred helper: number of enemies of the list with the given arrange id; original name unknown.
static int unknown002(const mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> *list, u32 arrange) {
  int count = 0;
  for (GF_OBJ_HANDLE *handle : *list) {
    DataParamAcc acc(handle);
    if (acc.getObjType() == OBJECT_TYPE_ENEMY && acc.getValidBdatId() == arrange) {
      count++;
    }
  }
  return count;
}

u32 GfObjUtil::getSetupObjNumberByEnArrangeId(u32 arrange) {
  GfObjManager *manager = GfObjManager::get();
  if (manager == nullptr) {
    return 0;
  }
  int loading = unknown002(manager->getLoadingObj(), arrange);
  return loading + unknown002(manager->getDestroyObj(), arrange);
}

// Inferred helper: adds the objects of the list with the given object type; original name unknown.
static void unknown003(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objects, const mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> *list, u32 objectType) {
  for (GF_OBJ_HANDLE *const &handle : *list) {
    if (GfObjUtil::getObjType(handle) == objectType) {
      objects.push_back(handle);
    }
  }
}

bool GfObjUtil::getSetupObj(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objects, u32 objectType) {
  GfObjManager *manager = GfObjManager::get();
  if (manager != nullptr) {
    unknown003(objects, manager->getLoadingObj(), objectType);
    unknown003(objects, manager->getDestroyObj(), objectType);
  }
  return objects.size() != 0;
}

} // namespace gf
