#include "event/chara_walk_pos.h"

#include "event/chara_dys_updater.h"
#include "event/chara_ik_updater.h"
#include "event/chara_util.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/component/property/gf_com_property_event.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace event {

void CharaWalkPos::term() {
  if (unknown28 == 4 || unknown28 == 2) {
    gf::GfObj *obj = gf::GfObjUtil::getObj(unknown08);
    if (obj != nullptr) {
      gf::GfComPropertyEvent *property = obj->getComponent<gf::GfComPropertyEvent>();
      gf::GfComEvtAnim *anim = obj->getComponent<gf::GfComEvtAnim>();
      if (anim != nullptr) {
        anim->setState("S_idle");
      }
      if (unknown28 == 2) {
        gf::GfGameUtil::disposeTurnEnd(unknown08);
      }
      unknown18->resetMovement(0);
      if (unknown20 == 0) {
        CharaUtil::setGravity(unknown08, true);
      }
      anim = obj->getComponent<gf::GfComEvtAnim>();
      if (anim != nullptr) {
        anim->setVariable("V_speed", 0.0f);
      }
      if (property != nullptr) {
        property->setMoveSpeed(0.0f);
      }
      unknown10->setFootIK(true, CharaIKUpdater::FOOT_TYPE_1);
    }
  }
  unknown28 = 0;
}

} // namespace event
