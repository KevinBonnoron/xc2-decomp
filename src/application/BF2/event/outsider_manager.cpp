#include "event/outsider_manager.h"

#include "event/alpha_manager.h"
#include "event/alpha_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"

namespace event {

OutsiderManager::OutsiderManager() : unknown10(), unknown14(0), unknown18(OBJ_TYPE_UNKNOWN_0) {}

void OutsiderManager::clear() {
  if (unknown14 & FLAG_UNKNOWN_0) {
    update(false);
  }
  unknown20.clear();
  unknown18 = OBJ_TYPE_UNKNOWN_0;
  unknown14 = 0;
}

void OutsiderManager::update(bool isHide) {
  if (unknown20.getType() < OutsiderField::TYPE_UNKNOWN_1) {
    return;
  }
  if (unknown18 & OBJ_TYPE_UNKNOWN_0_2) {
    updateSub(isHide, gmk::GMK_TYPE_NPC);
  }
  if (unknown18 & OBJ_TYPE_UNKNOWN_1) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_NPC);
  }
  if (unknown18 & OBJ_TYPE_UNKNOWN_2) {
    updateSub(isHide, gmk::GMK_TYPE_ENEMY);
  }
  if (unknown18 & OBJ_TYPE_UNKNOWN_3) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_ENEMY);
  }
  if (unknown18 & OBJ_TYPE_UNKNOWN_4) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MAP_OBJ);
  }
  if (unknown18 & OBJ_TYPE_UNKNOWN_5) {
    updateSub(isHide, gmk::GMK_TYPE_MOB);
  }
  if (unknown18 & OBJ_TYPE_UNKNOWN_6) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MOB);
  }
}

void OutsiderManager::update() {
  if (unknown14 & FLAG_UNKNOWN_0) {
    unknown20.update();
    if (unknown20.getRadius() > 0.0f) {
      update(true);
    }
  }
}

void OutsiderManager::updateSub(bool isHide, gmk::GmkType type) {
  mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024> handles;
  handles.clear();
  if (gf::GfGameUtil::collectGfObjHandleByGmkType(handles, type)) {
    for (mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024>::iterator it = handles.begin(); it != handles.end(); ++it) {
      gf::GF_OBJ_HANDLE *handle = *it;
      gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
      if (obj != nullptr && obj->getComponent<gf::GfComTransform>() != nullptr) {
        gf::GfObjSetup *setup = gf::GfObjUtil::getObjSetup(handle);
        if (setup == nullptr || !setup->isEvent()) {
          updateSub(isHide, *it);
        }
      }
    }
  }
}

void OutsiderManager::updateSub(bool isHide, gf::GF_OBJ_HANDLE *handle) {
  gf::GfComTransform *transform = gf::GfObjUtil::getObj(handle)->getComponent<gf::GfComTransform>();
  if (!isHide) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, ALPHA_ATTR_UNKNOWN_0, 1.0f, 1.0f);
    return;
  }
  f32 alpha = gf::GfObjAcc(handle).getAlphaEvent();
  if (unknown20.isInside(transform->getPosition())) {
    alpha = __builtin_fmaxf(alpha - 0.1f, 0.0f);
  } else {
    alpha = __builtin_fminf(alpha + 0.1f, 1.0f);
  }
  mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, ALPHA_ATTR_UNKNOWN_0, alpha, 1.0f);
}

void OutsiderManager::render() {
  if (isDisp() && (unknown14 & FLAG_UNKNOWN_0)) {
    unknown20.draw();
  }
}

void OutsiderManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
  case MSG_TYPE_UNKNOWN_10:
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_16:
    render();
    break;
  default:
    break;
  }
}

void OutsiderManager::defineTgt(OBJ_TYPE targets) { unknown18 = targets; }

void OutsiderManager::defineFld(OutsiderField::TYPE type, const mm::Vec3 &pos, f32 radius) { unknown20.setField(type, pos, radius); }

void OutsiderManager::setActive(bool isActive) {
  if (isActive) {
    unknown14 |= FLAG_UNKNOWN_0;
  } else {
    clear();
  }
}

void OutsiderManager::setDisp(bool isDisp) { unknown10.set(DISP_FLAG_UNKNOWN_0, isDisp); }

bool OutsiderManager::isDisp() const { return unknown10.test(DISP_FLAG_UNKNOWN_0); }

} // namespace event
