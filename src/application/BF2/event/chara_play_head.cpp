#include "event/chara_play_head.h"

#include "event/chara_obj.h"
#include "event/chara_weight_item.h"
#include "event/chara_weight_player.h"
#include "event/cmd_variable.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void CharaPlayHead::idle() {
  if (gf::GfObjUtil::getObj(handle) != nullptr && (flags & FLAG_PLAY) != 0) {
    const char *stat = type2stat(type);
    u32 blendOutFlag = flags & FLAG_BLEND_OUT;
    f32 blend = 0.0f;
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && blendOutFlag != 0) {
      blend = type2blend(type);
    }
    weight->easeOut(gf::ANIM_LAYER_HEAD, stat, blend, CV_TYPE_EASE_IN_OUT, WEIGHT_LAYER_PLAY);
    type = 0;
    life = -1.0f;
    name = "";
  }
  flags = 0;
}

void CharaPlayHead::init() { flags = 0; }

ICmd::RESULT CharaPlayHead::update(const Param &param) {
  if (gf::GfObjUtil::getObj(handle) == nullptr) {
    return RESULT_END;
  }
  f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().delta;
  if (param.getFrame() <= 0) {
    play(param.val(1).getS32(), param.val(2).getF32(), param.val(3).getBool(), param.val(4).getBool());
  }
  if ((flags & FLAG_LOOP) == 0) {
    life -= delta;
    if (life < 0.0f) {
      idle();
      return RESULT_END;
    }
  }
  return RESULT_NEXT;
}

void CharaPlayHead::term() { idle(); }

} // namespace event
