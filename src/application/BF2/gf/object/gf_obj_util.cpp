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
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/behavior/plugin/gf_eye_blink_plugin.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_append_info.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"

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
  GfComIK *ik = unknown001(handle);
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
  return info == nullptr ? "" : info->unknown404;
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

bool GfObjUtil::getMobSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_OBJ_HANDLE *handle) {
  slots.clear();
  if (getObjType(handle) == OBJECT_TYPE_MOB) {
    GfAssetManager::getSlotHandle(slots, getAssetHandle(handle));
  }

  return !slots.empty();
}

GfAppendInfo *GfObjUtil::getAppendInfo(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GFOBJ_MOUNT *mount = info != nullptr ? &info->unknownb8[attach] : nullptr;
  return info == nullptr ? nullptr : &mount->unknown10;
}

GfAppend *GfObjUtil::getAppend(GF_OBJ_HANDLE *handle, GFATTACH attach) {
  bool isAlternate = false;
  GfObjSetupWeapon *setup = getObjSetup<GfObjSetupWeapon>(handle);
  if (setup != nullptr) {
    isAlternate = setup->unknown78;
  }
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GFOBJ_MOUNT *mount = info != nullptr ? &info->unknownb8[attach] : nullptr;
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

} // namespace gf
