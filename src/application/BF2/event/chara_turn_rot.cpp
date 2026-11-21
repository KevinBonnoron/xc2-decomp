#include "event/chara_turn_rot.h"

#include "event/chara_dys_updater.h"
#include "event/chara_obj.h"
#include "event/chara_util.h"
#include "event/cmd_variable.h"
#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"

namespace event {

void CharaTurnRot::init() {}

// 0x71000cdfa8, 293 instructions.
ICmd::RESULT CharaTurnRot::update(const Param &param) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr) {
    return RESULT_UNKNOWN_1;
  }
  CharaObj *chara = static_cast<CharaObj *>(param.val(0).getUserdata());
  mm::Vec3 rot(param.val(1).getF32(), param.val(2).getF32(), param.val(3).getF32());
  // The game loads the two factors of the turn time (the fifth value at 0x71000ce048 and the frame info at 0x71000ce068) before the Euler
  // angles of the transform and multiplies them only when it fills the turn info (0x71000ce3c8): the local places those loads (ruling 2,
  // P2). Multiplying at the store of the info gives 290 instructions instead of 293, and so does reading the value after the `type` load.
  f32 turn = param.val(5).getF32() * chara->getFrameInfo().unknown0c;
  // The Euler angles of the transform are computed and discarded: the game runs the asinf and atan2f calls of the conversion (0x71000ce140,
  // 0x71000ce198 and 0x71000ce1bc) on the transform's rotation and stores nothing from them (ruling 5, a statement the game's code holds).
  mm::quatToEuler(obj->getComponent<gf::GfComTransform>()->getRotation());
  s32 type = param.val(4).getS32();
  if (type != 1) {
    if (type != 0) {
      return RESULT_UNKNOWN_1;
    }
    chara->setRot(rot);
    unknown18->resetMovement(0);
    return RESULT_UNKNOWN_1;
  }
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    chara->setRot(mm::Vec3(0.0f, rot.y, 0.0f));
    CharaUtil::execCmd(obj, "C_idle");
    unknown18->resetMovement(0);
    unknown08 &= ~1;
    return RESULT_UNKNOWN_1;
  }
  if (param.getFrame() == 0) {
    unknown08 = 0;
  }
  if ((unknown08 & 1) == 0 && chara->isTurnable()) {
    gf::GfGameUtil::ExecTurnCmdInfo info;
    info.unknown14 = 0.25f;
    info.unknown00 = unknown10;
    info.unknown10 = 0.0f;
    info.unknown08 = rot.y;
    info.unknown0c = turn;
    gf::GfGameUtil::execTurnCmd(info);
    unknown08 |= 1;
  }
  if (!gf::GfGameUtil::isTurnEnd(unknown10)) {
    return RESULT_UNKNOWN_0;
  }
  unknown08 &= ~1;
  return RESULT_UNKNOWN_1;
}

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
