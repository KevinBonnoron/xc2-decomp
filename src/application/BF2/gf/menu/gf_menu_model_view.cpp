#include "gf/menu/gf_menu_model_view.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "framework/effect/effect_pack.h"
#include "framework/effect/effect_point.h"
#include "framework/reference_frame.h"
#include "framework/resource/common_resource.h"
#include "fw/fw_model_object.h"
#include "fw/fw_render_resource.h"
#include "fw/fw_transform.h"
#include "gf/camera/gimmick/gf_camera_gimmick.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/model_view/gf_menu_model_view_camera.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "scn/scn_obj_acc.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace fw {
enum CAMERA_TYPE : unsigned int;
} // namespace fw

namespace gf {

fw::Transform GfMenuModelView::s_DefTransform;

GfMenuModelView::GfMenuModelView(u32 handle, u32 row) : unknown08(row), unknown0c(handle), unknown18(nullptr), unknown20(nullptr), unknown9a0(nullptr), unknown9a8(), unknownaa8(false) {
  ui::UIObjectAcc acc(handle);
  s_DefTransform.unknown00 = mm::Vec3::zero;
  s_DefTransform.unknown10 = mm::Quat::identity;
  unknown10 = acc.getRenderIndex();

  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MODEL_VIEW);
  GfMenuBdat::isValidBdatID(bdat, row);
  mm::mtl::FixStr<128> path;
  unknown18 = nullptr;
  unknown20 = nullptr;
  if (bdat != nullptr) {
    bool hasCamera = false;
    const char *cameraFile = Bdat::getVal(bdat, "camera_file", row).valueString;
    if (*cameraFile != '\0') {
      path.format("camera/%s.%s", cameraFile, "gcp");
      unknown18 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), path.c_str(), 10, false);
      hasCamera = true;
    }
    const char *effectFile = Bdat::getVal(bdat, "efp_file", row).valueString;
    if (*effectFile != '\0') {
      path.format("effect/bc/%s.%s", effectFile, "wiefb");
      unknown20 = fw::RenderResource::request(ui::UIUtil::getResourceAllocator(), path.c_str(), 10);
    } else if (!hasCamera) {
      unknownaa8 = true;
    }
  } else {
    unknownaa8 = true;
  }
  for (u32 i = 0; i < 16; i++) {
    unknown9a8[i].unknown00 = 0;
    unknown9a8[i].unknown08 = unknown020;
  }
  unknown930.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
}

GfMenuModelView::~GfMenuModelView() {
  unknownab0 = nullptr;
  if (fw::EffectManager::get() != nullptr && unknown9a0 != nullptr) {
    for (u32 i = 0; i < 16; i++) {
      if (unknown9a8[i].unknown00 != 0) {
        fw::EffectManager::get()->remove(unknown9a8[i].unknown00);
        unknown9a8[i].unknown00 = 0;
        unknown9a8[i].unknown08 = unknown020;
      }
    }
    mm::mtl::safeRelease(unknown9a0);
  }
  for (u32 i = 0; i < unknown28.size(); i++) {
    GfObjFactory::destroyObj(unknown28[i].unknown00);
  }
  fw::CameraManager *manager = fw::CameraManager::get();
  if (manager != nullptr) {
    fw::CameraLayer &layer = manager->unknown20[unknown10 + 1];
    for (u32 i = 0; i < unknown930.size(); i++) {
      if (unknown930[i]->unknowna0) {
        layer.pop(unknown930[i], 0.0f);
        unknown930[i] = nullptr;
      }
    }
  }
  mm::mtl::safeRelease(unknown18);
  mm::mtl::safeRelease(unknown20);
}

fw::Transform &GfMenuModelView::getObjectTransformLocal(GF_OBJ_HANDLE *handle) {
  static fw::Transform transform;
  GfObjAcc acc(handle);
  GfComTransform *comTransform = acc.getObj()->getComponent<GfComTransform>();
  if (comTransform != nullptr) {
    return comTransform->unknown001()->unknown002();
  }

  return transform;
}

void GfMenuModelView::setVanishRatio(GF_OBJ_HANDLE *handle, f32 ratio) {
  GfObjAcc acc(handle);
  GfComModel *model = acc.getObj()->getComponent<GfComModel>();
  if (model != nullptr && model->unknown18 != nullptr) {
    ml::ScnObjAccVolumeFade fade(model->unknown18->getInterface());
    fade.setRatio(ratio, -1);
  }
}

u32 GfMenuModelView::getMapObjID(u32 index) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MODEL_VIEW);
  GfMenuBdat::isValidBdatID(bdat, unknown08);
  mm::mtl::FixStr<16> name;
  name.format("obj_model%02d", index);
  u32 id = 0;
  if (Bdat::getMember(bdat, name.c_str()) != nullptr) {
    id = Bdat::getVal(bdat, name.c_str(), unknown08).valueU16;
  }
  return id;
}

void GfMenuModelView::addWeaponFromBlade(u32 blade, u32 id) { GfObjFactory::createUiWeapon(findGfObj(OBJECT_TYPE_PC, id), blade); }

void GfMenuModelView::delWeaponFromBlade(u32 id) { GfObjFactory::createUiWeapon(findGfObj(OBJECT_TYPE_PC, id), 0); }

void GfMenuModelView::sendObjectCommand(GF_OBJ_HANDLE *handle, const char *command) {
  GfComAsm *comAsm = GfObjAcc(handle).getObj()->getComponent<GfComAsm>();
  if (comAsm != nullptr && !comAsm->execCmd(command, ANIM_LAYER_UNKNOWN_0)) {
    comAsm->setState("S_idle", ANIM_LAYER_UNKNOWN_0);
  }
}

void GfMenuModelView::setObjectCommandValue(GF_OBJ_HANDLE *handle, const char *name, int value) {
  GfComAsm *comAsm = GfObjAcc(handle).getObj()->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    comAsm->setVariable(name, value);
  }
}

void GfMenuModelView::attachObject(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *parent, const char *bone) {
  GfComTransform *comTransform = GfObjAcc(handle).getObj()->getComponent<GfComTransform>();
  if (comTransform != nullptr) {
    GfComModel *model = GfObjAcc(parent).getObj()->getComponent<GfComModel>();
    if (model != nullptr) {
      model->addBoneReferenceFrame(bone, comTransform->unknown10);
    }
  }
}

void GfMenuModelView::detachObject(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *parent, const char *bone) {
  GfComTransform *comTransform = GfObjAcc(handle).getObj()->getComponent<GfComTransform>();
  if (comTransform != nullptr) {
    GfComModel *model = GfObjAcc(parent).getObj()->getComponent<GfComModel>();
    if (model != nullptr) {
      model->removeBoneReferenceFrame(bone, comTransform->unknown10);
    }
  }
}

fw::Transform &GfMenuModelView::getObjectTransform(GF_OBJ_HANDLE *handle) {
  static fw::Transform transform;
  GfObjAcc acc(handle);
  GfComTransform *comTransform = acc.getObj()->getComponent<GfComTransform>();
  if (comTransform != nullptr) {
    return comTransform->unknown001()->unknown003();
  }

  return transform;
}

bool GfMenuModelView::getObjectEffectPoint(GF_OBJ_HANDLE *handle, const char *name, mm::Vec3 &position) {
  GfObjAcc acc(handle);
  GfComEffectCaster *effectCaster = acc.getObj()->getComponent<GfComEffectCaster>();
  fw::EffectPoint *effectPoint = effectCaster->getEffectPoint();
  int index = effectPoint->getPointIndex(name);
  if (index != -1) {
    position = effectPoint->getPointTransform(index).unknown004();
    return true;
  }

  return false;
}

void GfMenuModelView::setObjectScale(GF_OBJ_HANDLE *handle, const mm::Vec3 &scale) { GfObjAcc(handle).setModelScaleForMenu(scale); }

void GfMenuModelView::setObjectDisp(GF_OBJ_HANDLE *handle, bool isDisp) { GfObjAcc(handle).setDisp(OBJDISP_UNKNOWN_0, isDisp); }

f32 GfMenuModelView::getVanishRatio(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  GfComModel *model = acc.getObj()->getComponent<GfComModel>();
  f32 ratio = 0.0f;
  if (model != nullptr && model->unknown18 != nullptr) {
    ml::ScnObjAccVolumeFade fade(model->unknown18->getInterface());
    ratio = fade.getRatio(0);
  }
  return ratio;
}

void GfMenuModelView::stopObjectCtrl(GF_OBJ_HANDLE *handle) {
  for (unknown001 *ctrl = unknown28.begin(); ctrl != unknown28.end(); ++ctrl) {
    if (ctrl->unknown00 == handle) {
      ctrl->unknown08.time = ctrl->unknown08.duration;
    }
  }
}

bool GfMenuModelView::isObjectCtrlBusy(GF_OBJ_HANDLE *handle) {
  for (unknown001 *ctrl = unknown28.begin(); ctrl != unknown28.end(); ++ctrl) {
    if (ctrl->unknown00 == handle) {
      return ctrl->unknown08.isBusy();
    }
  }
  return false;
}

bool GfMenuModelView::isObjectAnimationBusy(GF_OBJ_HANDLE *handle) {
  for (unknown001 *ctrl = unknown28.begin(); ctrl != unknown28.end(); ++ctrl) {
    if (ctrl->unknown00 == handle) {
      GfObjAcc acc(handle);
      GfComAsm *comAsm = acc.getObj()->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        return !comAsm->isEnd(ANIM_LAYER_UNKNOWN_0);
      }
    }
  }
  return false;
}

const char *GfMenuModelView::getObjectAnimationState(GF_OBJ_HANDLE *handle) {
  for (unknown001 *ctrl = unknown28.begin(); ctrl != unknown28.end(); ++ctrl) {
    if (ctrl->unknown00 == handle) {
      GfObjAcc acc(handle);
      GfComAsm *comAsm = acc.getObj()->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        return comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
      }
    }
  }
  return nullptr;
}

void GfMenuModelView::setObjectVanishParam(GF_OBJ_HANDLE *handle, u32 param) {
  if (param == 0) {
    return;
  }

  for (unknown001 *ctrl = unknown28.begin(); ctrl != unknown28.end(); ++ctrl) {
    if (ctrl->unknown00 == handle) {
      ml::VolumeFadeParams params;
      if (!fw::EffectManager::get()->getVolumeFadeParam(param, params)) {
        return;
      }

      GfObjAcc acc(handle);
      GfComModel *model = acc.getObj()->getComponent<GfComModel>();
      if (model != nullptr && model->unknown18 != nullptr) {
        ml::ScnObjAccVolumeFade fade(model->unknown18->getInterface());
        fade.setParams(params, -1);
      }
    }
  }
}

void GfMenuModelView::setObjectVanishRatio(GF_OBJ_HANDLE *handle, f32 ratio) {
  for (unknown001 *ctrl = unknown28.begin(); ctrl != unknown28.end(); ++ctrl) {
    if (ctrl->unknown00 == handle) {
      setVanishRatio(handle, ratio);
    }
  }
}

u32 GfMenuModelView::addCamera(mm::mtl::IntrusivePtr<fw::Camera> camera) {
  u32 index = unknown930.size();
  unknown930.push_back(camera);
  return index;
}

void GfMenuModelView::pushCamera(u32 index, f32 time) {
  if (index < unknown930.size()) {
    if (!unknown930[index]->unknowna0 && fw::CameraManager::get() != nullptr) {
      fw::CameraManager::get()->push(static_cast<fw::CAMERA_TYPE>(unknown10 + 1), unknown930[index], time);
      unknown958.push_back(index);
    }
  }
}

void GfMenuModelView::popCamera(f32 time) {
  if (fw::CameraManager::get() != nullptr) {
    fw::CameraManager::get()->pop(static_cast<fw::CAMERA_TYPE>(unknown10 + 1), unknown930[unknown958.back()], time);
    unknown958.pop_back();
  }
}

void GfMenuModelView::changeCamera(u32 index, f32 time) {
  popCamera(0.0f);
  pushCamera(index, time);
}

int GfMenuModelView::getCurrentCameraIndex() {
  if (!unknown958.empty()) {
    return unknown958.back();
  }
  return -1;
}

void GfMenuModelView::stopCameraMotion() {
  if (unknownab0.get() != nullptr) {
    if (unknownab0.get()->getRTTI()->isKindOf(&GimmickCamera::m_rtti) && fw::CameraManager::get() != nullptr) {
      fw::CameraManager::get()->unknown20[unknown10 + 1].pop(unknownab0, 0.5f);
      unknownab0 = nullptr;
    }
  }
}

mm::Vec3 GfMenuModelView::getCameraPos(u32 index) {
  if (index < unknown930.size()) {
    fw::Camera *camera = unknown930[index].get();
    if (camera != nullptr && camera->getRTTI()->isKindOf(&GfMenuModelViewCamera::m_rtti)) {
      return static_cast<GfMenuModelViewCamera *>(camera)->unknownb0;
    }
  }
  return mm::Vec3::zero;
}

mm::Vec3 GfMenuModelView::getCameraRot(u32 index) {
  if (index < unknown930.size()) {
    fw::Camera *camera = unknown930[index].get();
    if (camera != nullptr && camera->getRTTI()->isKindOf(&GfMenuModelViewCamera::m_rtti)) {
      return static_cast<GfMenuModelViewCamera *>(camera)->unknownc0;
    }
  }
  return mm::Vec3::zero;
}

bool GfMenuModelView::playCameraMotion(const char *name, const mm::Vec3 &position, f32 rotation) {
  if (name != nullptr && *name != '\0') {
    mm::mtl::IntrusivePtr<fw::Camera> camera = GimmickCamera::create(name, position, rotation);
    GimmickCamera *gimmick = static_cast<GimmickCamera *>(camera.get());
    if (gimmick != nullptr) {
      if (gimmick->getRTTI()->isKindOf(&GimmickCamera::m_rtti)) {
        gimmick->setNearClip(0.01f);
        gimmick->play();
      }
      if (fw::CameraManager::get() != nullptr) {
        fw::CameraManager::get()->unknown20[unknown10 + 1].push(camera, 0.5f);
        unknownab0 = camera;
      }
      return true;
    }
  }
  return false;
}

void GfMenuModelView::resetCamera(u32 index, f32 time) {
  fw::CameraManager *manager = fw::CameraManager::get();
  if (manager != nullptr) {
    fw::CameraLayer &layer = manager->unknown20[unknown10 + 1];
    for (u32 i = 0; i < unknown930.size(); i++) {
      if (unknown930[i]->unknowna0) {
        layer.pop(unknown930[i], 0.0f);
      }
    }
  }
  unknown958.clear();
  pushCamera(index, time);
}

void GfMenuModelView::playEffect(u32 type, const char *name, const mm::Vec3 &position, GF_OBJ_HANDLE *handle) {
  if (fw::EffectManager::get() != nullptr && unknown9a0 != nullptr) {
    if (unknown9a8[type].unknown00 == 0) {
      u32 effect = fw::EffectManager::get()->create(name, unknown9a0, true);
      fw::EffectManager::get()->setViewnum(effect, unknown10 + 1);
      unknown9a8[type].unknown00 = effect;
      if (effect != 0) {
        unknown9a8[type].unknown08 = handle;
      }
    }
  }
}

u32 GfMenuModelView::createEffect(u32 type, const char *name) {
  if (fw::EffectManager::get() == nullptr || unknown9a0 == nullptr || unknown9a8[type].unknown00 != 0) {
    return 0;
  }

  u32 effect = fw::EffectManager::get()->create(name, unknown9a0, true);
  fw::EffectManager::get()->setViewnum(effect, unknown10 + 1);
  unknown9a8[type].unknown00 = effect;
  return effect;
}

void GfMenuModelView::playEffectFromCAS(u32 type, const char *name, GF_OBJ_HANDLE *handle) {
  if (fw::EffectManager::get() != nullptr && unknown9a0 != nullptr && unknown9a8[type].unknown00 == 0) {
    u32 effect = fw::EffectManager::get()->create(name, unknown9a0, true);
    fw::EffectManager::get()->setViewnum(effect, unknown10 + 1);
    unknown9a8[type].unknown00 = effect;
    if (effect != 0) {
      GfComEffectCaster *caster = GfObjAcc(handle).getObj()->getComponent<GfComEffectCaster>();
      fw::EffectManager::get()->setParam(effect, caster->unknown388, 1.0f);
    }
  }
}

bool GfMenuModelView::isPlayEffect(u32 index) {
  if (index >= 16) {
    return false;
  }
  return unknown9a8[index].unknown00 != 0;
}

void GfMenuModelView::stopEffect(u32 index) {
  if (unknown9a8[index].unknown00 != 0) {
    fw::EffectManager::get()->dead(unknown9a8[index].unknown00);
  }
}

void GfMenuModelView::removeEffect(u32 index) {
  if (unknown9a8[index].unknown00 != 0) {
    fw::EffectManager::get()->kill(unknown9a8[index].unknown00);
    unknown9a8[index].unknown00 = 0;
    unknown9a8[index].unknown08 = unknown020;
  }
}

bool GfMenuModelView::isLoading() const {
  if (!unknownaa8) {
    return true;
  }

  for (u32 i = 0; i < unknown28.size(); i++) {
    if (!GfObjUtil::isUpdate(unknown28[i].unknown00)) {
      return true;
    }
  }
  return false;
}

void GfMenuModelView::delGfObj(u32 type, u32 id) {
  for (unknown001 *ctrl = unknown28.begin(); ctrl != unknown28.end(); ++ctrl) {
    GfObjAcc acc(ctrl->unknown00);
    if (acc.getType() == type && acc.getBdatId() == id) {
      GfObjFactory::destroyObj(ctrl->unknown00);
      unknown28.erase(ctrl);
      return;
    }
  }
}

GF_OBJ_HANDLE *GfMenuModelView::findGfObj(u32 type, u32 id) {
  for (u32 i = 0; i < unknown28.size(); i++) {
    GfObjAcc acc(unknown28[i].unknown00);
    if (acc.getType() == type && acc.getBdatId() == id) {
      return unknown28[i].unknown00;
    }
  }
  return unknown020;
}

bool GfMenuModelView::checkGfObj(u32 type, u32 id) {
  for (u32 i = 0; i < unknown28.size(); i++) {
    GfObjAcc acc(unknown28[i].unknown00);
    if (acc.getType() == type && acc.getBdatId() == id) {
      return GfObjUtil::isUpdate(acc.getHandle());
    }
  }
  return false;
}

GfMenuModelView::CtrlParam::CtrlParam(GF_OBJ_HANDLE *handle, f32 duration, bool unknown) : unknown00(handle), unknown0a(0), unknown0c(duration), unknown10(unknown) {
  GfObjAcc acc(handle);
  const fw::Transform &transform = getObjectTransformLocal(unknown00);
  m_movePosX = transform.unknown00.x;
  m_movePosY = transform.unknown00.y;
  m_movePosZ = transform.unknown00.z;
  m_moveRotY = mm::quatToEuler(transform.unknown10).y;
  m_moveSclX = acc.getModelScaleXYZ().x;
  m_moveSclY = acc.getModelScaleXYZ().y;
  m_moveSclZ = acc.getModelScaleXYZ().z;
  m_moveAlpha = acc.getAlpha(OBJ_ALPHA_UNKNOWN_0);
  m_moveVanish = getVanishRatio(handle);
}

void GfMenuModelView::CtrlParam::setMovePosX(f32 value) {
  unknown08 |= 0x1;
  m_movePosX = value;
}

void GfMenuModelView::CtrlParam::setMovePosX(f32 start, f32 end) {
  getObjectTransformLocal(unknown00).unknown00.x = start;
  unknown08 |= 0x1;
  m_movePosX = end;
}

void GfMenuModelView::CtrlParam::setMovePosY(f32 value) {
  unknown08 |= 0x2;
  m_movePosY = value;
}

// The game's setMovePosY/Z(f32, f32) write the X members and flag, like setMovePosX (same code in the binary).
void GfMenuModelView::CtrlParam::setMovePosY(f32 start, f32 end) {
  getObjectTransformLocal(unknown00).unknown00.x = start;
  unknown08 |= 0x1;
  m_movePosX = end;
}

void GfMenuModelView::CtrlParam::setMovePosZ(f32 value) {
  unknown08 |= 0x4;
  m_movePosZ = value;
}

void GfMenuModelView::CtrlParam::setMovePosZ(f32 start, f32 end) {
  getObjectTransformLocal(unknown00).unknown00.x = start;
  unknown08 |= 0x1;
  m_movePosX = end;
}

void GfMenuModelView::CtrlParam::setAddPosX(f32 value) {
  fw::Transform &transform = getObjectTransformLocal(unknown00);
  unknown08 |= 0x1;
  m_movePosX = transform.unknown00.x + value;
}

void GfMenuModelView::CtrlParam::setAddPosY(f32 value) {
  fw::Transform &transform = getObjectTransformLocal(unknown00);
  unknown08 |= 0x2;
  m_movePosY = transform.unknown00.y + value;
}

void GfMenuModelView::CtrlParam::setAddPosZ(f32 value) {
  fw::Transform &transform = getObjectTransformLocal(unknown00);
  unknown08 |= 0x4;
  m_movePosZ = transform.unknown00.z + value;
}

void GfMenuModelView::CtrlParam::setMoveSclX(f32 value) {
  unknown08 |= 0x8;
  m_moveSclX = value;
}

void GfMenuModelView::CtrlParam::setMoveSclX(f32 start, f32 end) {
  GfObjAcc acc(unknown00);
  mm::Vec3 scale = acc.getModelScaleXYZ();
  scale.x = end;
  acc.setModelScaleForMenu(scale);
  unknown08 |= 0x8;
  m_moveSclX = end;
}

void GfMenuModelView::CtrlParam::setMoveSclY(f32 value) {
  unknown08 |= 0x10;
  m_moveSclY = value;
}

// The game's setMoveSclY/Z(f32, f32) set the X flag and m_moveSclX, like setMoveSclX (same code in the binary).
void GfMenuModelView::CtrlParam::setMoveSclY(f32 start, f32 end) {
  GfObjAcc acc(unknown00);
  mm::Vec3 scale = acc.getModelScaleXYZ();
  scale.y = end;
  acc.setModelScaleForMenu(scale);
  unknown08 |= 0x8;
  m_moveSclX = end;
}

void GfMenuModelView::CtrlParam::setMoveSclZ(f32 value) {
  unknown08 |= 0x20;
  m_moveSclZ = value;
}

void GfMenuModelView::CtrlParam::setMoveSclZ(f32 start, f32 end) {
  GfObjAcc acc(unknown00);
  mm::Vec3 scale = acc.getModelScaleXYZ();
  scale.z = end;
  acc.setModelScaleForMenu(scale);
  unknown08 |= 0x8;
  m_moveSclX = end;
}

void GfMenuModelView::CtrlParam::setMoveRotY(f32 value) {
  unknown08 |= 0x80;
  m_moveRotY = value;
}

void GfMenuModelView::CtrlParam::setMoveAlpha(f32 value) {
  unknown08 |= 0x40;
  m_moveAlpha = value;
}

void GfMenuModelView::CtrlParam::setMoveVanish(f32 value) {
  unknown08 |= 0x100;
  m_moveVanish = value;
}

} // namespace gf
