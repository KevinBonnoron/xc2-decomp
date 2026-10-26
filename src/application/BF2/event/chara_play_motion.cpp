#include "event/chara_play_motion.h"

#include "event/chara_dys_updater.h"
#include "event/chara_ik_updater.h"
#include "event/chara_manager.h"
#include "event/motstm_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

CharaPlayMotion::CharaPlayMotion() {
  unknown08 = 0;
  unknown10 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown18 = 0;
  unknown20 = 0;
  unknown28 = 0;
  unknown30 = 0;
  unknown3c = 0.0f;
  unknown40 = 0.0f;
}

void CharaPlayMotion::play(gf::GfObj *obj, void *motion, u64 size, f32 time) {
  if ((unknown08 & 1) == 0) {
    return;
  }
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->play(motion, size, time / 30.0f);
  }
  unknown20->resetDynamics(0);
  unknown08 |= 4;
}

void CharaPlayMotion::term() {
  if ((unknown08 & 2) == 0) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj != nullptr) {
    stop(obj);
  }
  unknown18->setFootIK(true, CharaIKUpdater::FOOT_TYPE_2);
  if (CharaManager::getPtr()->isStreamMode() && unknown28 != nullptr) {
    MotstmManager::getPtr()->free(unknown28);
  }
  unknown28 = nullptr;
  unknown08 &= ~2;
}

void CharaPlayMotion::stop(gf::GfObj *obj) {
  if ((unknown08 & 4) == 0) {
    return;
  }
  gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
  if (anim != nullptr) {
    anim->stop();
    anim->setSpeed(1.0f, gf::ANIM_LAYER_BASE);
  }
  unknown20->resetDynamics(0);
  unknown08 &= ~4;
}

} // namespace event
