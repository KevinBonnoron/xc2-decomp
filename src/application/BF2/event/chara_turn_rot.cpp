#include "event/chara_turn_rot.h"

#include "event/chara_dys_updater.h"
#include "event/chara_util.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/gf_obj_util.h"

namespace gf {
class GfObj;
} // namespace gf

namespace event {

void CharaTurnRot::init() {}

void CharaTurnRot::term() {
  if ((unknown08 & 1) == 0) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj != nullptr) {
    CharaUtil::execCmd(obj, "C_idle");
    gf::GfGameUtil::disposeTurnEnd(unknown10);
    unknown18->resetMovement(0);
  }
  unknown08 &= ~1;
}

} // namespace event
