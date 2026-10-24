#include "event/scheduler.h"

#include <math.h>

#include "event/chara_util.h"
#include "event/manager.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"

namespace event {

Scheduler::Scheduler(gf::GF_OBJ_HANDLE *handle, u32 type)
    : unknown08(0), unknown0c(0), unknown10(handle), unknown18(gf::GfObjAcc(handle).getBdatId()), unknown1c(type), unknown20(0), unknown28(handle) {
  unknown50[ORDER_FLD2EVT] = &Scheduler::func_stanby;
  unknown50[ORDER_EVT2IDLE] = &Scheduler::func_stanby;
  unknown50[ORDER_EVT2FLD] = &Scheduler::func_stanby;
  setup();
}

void Scheduler::func_stanby(gf::GfObj *obj) {}

void Scheduler::setup() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr) {
    return;
  }
  if (obj->type == gf::OBJECT_TYPE_DRIVER) {
    unknown0c |= USE_LOOK | USE_LOOK_RESET;
  } else if (obj->type == gf::OBJECT_TYPE_NPC) {
    switch (unknown1c) {
    case 0:
      unknown0c |= USE_TURN | USE_RETURN | USE_LOOK | USE_LOOK_RESET;
      if (unknown28.hasItem()) {
        unknown0c |= USE_FADE | USE_ITEM;
      }
      break;
    case 1:
      unknown0c |= USE_LOOK | USE_LOOK_RESET;
      unknown20 = 1;
      break;
    case 2:
      unknown0c |= USE_TURN | USE_RETURN | USE_LOOK | USE_LOOK_RESET;
      break;
    }
  }
}

Scheduler::Scheduler(const Scheduler *scheduler, u32 type)
    : unknown08(0), unknown0c(scheduler->unknown0c), unknown10(scheduler->unknown10), unknown18(scheduler->unknown18), unknown1c(type), unknown20(0), unknown28(scheduler->unknown10) {
  unknown50[ORDER_FLD2EVT] = &Scheduler::func_stanby;
  unknown50[ORDER_EVT2IDLE] = &Scheduler::func_stanby;
  unknown50[ORDER_EVT2FLD] = &Scheduler::func_stanby;
  setup();
}

Scheduler::~Scheduler() { unknown28.clear(); }

void Scheduler::play(ORDER order) {
  if (gf::GfObjUtil::getObj(unknown10) == nullptr) {
    return;
  }
  switch (order) {
  case ORDER_FLD2EVT:
    if (unknown50[ORDER_EVT2FLD] != &Scheduler::func_stanby) {
      break;
    }
    unknown50[ORDER_FLD2EVT] = &Scheduler::func_fld2evt;
    break;
  case ORDER_EVT2IDLE:
    if (unknown50[ORDER_EVT2FLD] != &Scheduler::func_stanby) {
      break;
    }
    unknown50[ORDER_EVT2IDLE] = &Scheduler::func_evt2idle;
    break;
  case ORDER_EVT2FLD:
    unknown50[ORDER_EVT2IDLE] = nullptr;
    unknown50[ORDER_FLD2EVT] = nullptr;
    unknown50[ORDER_EVT2FLD] = &Scheduler::func_evt2fld;
    break;
  default:
    break;
  }
}

void Scheduler::func_fld2evt(gf::GfObj *obj) {
  if ((unknown0c & USE_FADE) != 0) {
    unknown28.fadeout();
  }
  unknown50[ORDER_FLD2EVT] = obj->type == gf::OBJECT_TYPE_DRIVER ? nullptr : &Scheduler::func_motionEnd;
}

void Scheduler::func_evt2idle(gf::GfObj *obj) {
  unknown08 |= FLAG_LOOK_START;
  unknown50[ORDER_EVT2IDLE] = &Scheduler::func_look;
}

void Scheduler::func_evt2fld(gf::GfObj *obj) {
  if ((unknown0c & USE_LOOK_RESET) != 0) {
    lookTo(false, obj, nullptr, static_cast<EVT_aimtype>(0), true);
  }
  unknown50[ORDER_EVT2FLD] = &Scheduler::func_return;
}

void Scheduler::func_motionEnd(gf::GfObj *obj) { unknown50[ORDER_FLD2EVT] = &Scheduler::func_motionEnd_loop; }

void Scheduler::func_motionEnd_loop(gf::GfObj *obj) { unknown50[ORDER_FLD2EVT] = &Scheduler::func_turn; }

f32 Scheduler::getRotY(gf::GfObj *obj, gf::GfObj *target) {
  gf::GfComTransform *targetTransform = target->getComponent<gf::GfComTransform>();
  gf::GfComTransform *transform = obj->getComponent<gf::GfComTransform>();
  const mm::Vec3 &pos = transform->getPosition();
  const mm::Vec3 &targetPos = targetTransform->getPosition();
  return -atan2f(pos.x - targetPos.x, -(pos.z - targetPos.z));
}

void Scheduler::func_turn_loop(gf::GfObj *obj) {
  if ((unknown0c & USE_TURN) == 0 || gf::GfGameUtil::isTurnEnd(unknown10)) {
    unknown50[ORDER_FLD2EVT] = nullptr;
  }
}

void Scheduler::func_look(gf::GfObj *obj) {
  if ((unknown0c & USE_LOOK) == 0) {
    unknown50[ORDER_EVT2IDLE] = nullptr;
    return;
  }
  gf::GfObj *target = nullptr;
  if (obj->type == gf::OBJECT_TYPE_DRIVER) {
    target = gf::GfObjUtil::getObj(Manager::get()->getObjHandle());
  } else if (obj->type == gf::OBJECT_TYPE_NPC) {
    target = gf::GfGameParty::getLeaderTransformObj();
  }
  if (target == nullptr) {
    return;
  }
  if ((unknown08 & FLAG_LOOK_START) == 0) {
    lookTo(true, obj, target, static_cast<EVT_aimtype>(unknown20), false);
    return;
  }
  if (CharaUtil::isCanTarget(obj->unknownf8, target->unknownf8)) {
    lookTo(true, obj, target, static_cast<EVT_aimtype>(unknown20), true);
    unknown08 &= ~FLAG_LOOK_START;
  }
}

void Scheduler::func_return(gf::GfObj *obj) {
  if ((unknown0c & USE_RETURN) != 0) {
    unknown80 = 360;
  }
  unknown50[ORDER_EVT2FLD] = &Scheduler::func_return_loop;
}

void Scheduler::func_return_loop(gf::GfObj *obj) { unknown50[ORDER_EVT2FLD] = &Scheduler::func_motion; }

void Scheduler::func_motion(gf::GfObj *obj) { unknown50[ORDER_EVT2FLD] = &Scheduler::func_motion_loop; }

void Scheduler::func_motion_loop(gf::GfObj *obj) {
  if ((unknown0c & USE_ITEM) != 0) {
    gf::GfComAsm *anim = obj->getComponent<gf::GfComAsm>();
    if (unknown80-- > 0 && anim != nullptr) {
      bool isLoop = anim->isLoop(gf::ANIM_LAYER_BASE);
      const char *state = anim->getStateName(gf::ANIM_LAYER_BASE);
      if (!isLoop || __builtin_strcmp(state, "S_idle") == 0) {
        return;
      }
    }
  }
  unknown50[ORDER_EVT2FLD] = &Scheduler::func_item;
}

void Scheduler::func_item(gf::GfObj *obj) {
  if ((unknown0c & USE_ITEM) != 0) {
    unknown28.fadein();
  }
  unknown50[ORDER_EVT2FLD] = &Scheduler::func_item_loop;
}

void Scheduler::func_item_loop(gf::GfObj *obj) {
  if ((unknown0c & USE_ITEM) == 0 || !unknown28.isFading()) {
    unknown50[ORDER_EVT2FLD] = nullptr;
  }
}

void Scheduler::setUse(USE use, bool isUse) {
  if (isUse) {
    if ((unknown0c & use) != use) {
      unknown0c |= use;
    }
  } else {
    if ((unknown0c & use) != 0) {
      unknown0c &= ~use;
    }
  }
}

f32 Scheduler::getRotY(gf::GfObj *obj) { return mm::quatToEuler(obj->getComponent<gf::GfComTransform>()->getRotation()).y; }

} // namespace event
