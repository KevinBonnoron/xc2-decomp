#include "event/chara_play_motion_abc.h"

#include "event/chara_dys_updater.h"
#include "event/chara_ik_updater.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

CharaPlayMotionABC::CharaPlayMotionABC() {
  unknown08 = 0;
  unknown10 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown18 = 0;
  unknown20 = 0;
  unknown28 = 0;
  unknown58 = 0.0f;
  unknown5c = 0.0f;
  unknown60 = 0;
  unknown68 = 0.0f;
  unknown6c = 0.0f;
  unknown70 = 0.0f;
  unknown74 = 0.0f;
  unknown78 = 0.0f;
  unknown7c = 0.0f;
}

bool CharaPlayMotionABC::has(unsigned int index) const { return unknown34[index] > -1; }

void CharaPlayMotionABC::stopMotion(gf::GfObj *obj) {
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->stopMulti();
    anim->setSpeed(1.0f, gf::ANIM_LAYER_BASE);
  }
  unknown20->resetDynamics(0);
}

void CharaPlayMotionABC::term() {
  if ((unknown08 & 1) != 0) {
    gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
    if (obj != nullptr) {
      stopMotion(obj);
    }
    unknown18->setFootIK(true, CharaIKUpdater::FOOT_TYPE_2);
    unknown08 &= ~1;
  }
}

} // namespace event
