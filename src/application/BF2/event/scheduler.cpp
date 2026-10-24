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

Scheduler::Scheduler(gf::GF_OBJ_HANDLE *handle, u32 type) : flags(0), mUse(0), handle(handle), mBdatId(gf::GfObjAcc(handle).getBdatId()), mType(type), mAimType(0), mItem(handle) {
  mFuncs[ORDER_FLD2EVT] = &Scheduler::func_stanby;
  mFuncs[ORDER_EVT2IDLE] = &Scheduler::func_stanby;
  mFuncs[ORDER_EVT2FLD] = &Scheduler::func_stanby;
  setup();
}

void Scheduler::func_stanby(gf::GfObj *obj) {}

void Scheduler::setup() {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }
  if (obj->type == gf::OBJECT_TYPE_DRIVER) {
    mUse |= USE_LOOK | USE_LOOK_RESET;
  } else if (obj->type == gf::OBJECT_TYPE_NPC) {
    switch (mType) {
    case 0:
      mUse |= USE_TURN | USE_RETURN | USE_LOOK | USE_LOOK_RESET;
      if (mItem.hasItem()) {
        mUse |= USE_FADE | USE_ITEM;
      }
      break;
    case 1:
      mUse |= USE_LOOK | USE_LOOK_RESET;
      mAimType = 1;
      break;
    case 2:
      mUse |= USE_TURN | USE_RETURN | USE_LOOK | USE_LOOK_RESET;
      break;
    }
  }
}

Scheduler::Scheduler(const Scheduler *scheduler, u32 type)
    : flags(0), mUse(scheduler->mUse), handle(scheduler->handle), mBdatId(scheduler->mBdatId), mType(type), mAimType(0), mItem(scheduler->handle) {
  mFuncs[ORDER_FLD2EVT] = &Scheduler::func_stanby;
  mFuncs[ORDER_EVT2IDLE] = &Scheduler::func_stanby;
  mFuncs[ORDER_EVT2FLD] = &Scheduler::func_stanby;
  setup();
}

Scheduler::~Scheduler() { mItem.clear(); }

void Scheduler::play(ORDER order) {
  if (gf::GfObjUtil::getObj(handle) == nullptr) {
    return;
  }
  switch (order) {
  case ORDER_FLD2EVT:
    if (mFuncs[ORDER_EVT2FLD] != &Scheduler::func_stanby) {
      break;
    }
    mFuncs[ORDER_FLD2EVT] = &Scheduler::func_fld2evt;
    break;
  case ORDER_EVT2IDLE:
    if (mFuncs[ORDER_EVT2FLD] != &Scheduler::func_stanby) {
      break;
    }
    mFuncs[ORDER_EVT2IDLE] = &Scheduler::func_evt2idle;
    break;
  case ORDER_EVT2FLD:
    mFuncs[ORDER_EVT2IDLE] = nullptr;
    mFuncs[ORDER_FLD2EVT] = nullptr;
    mFuncs[ORDER_EVT2FLD] = &Scheduler::func_evt2fld;
    break;
  default:
    break;
  }
}

void Scheduler::func_fld2evt(gf::GfObj *obj) {
  if ((mUse & USE_FADE) != 0) {
    mItem.fadeout();
  }
  mFuncs[ORDER_FLD2EVT] = obj->type == gf::OBJECT_TYPE_DRIVER ? nullptr : &Scheduler::func_motionEnd;
}

void Scheduler::func_evt2idle(gf::GfObj *obj) {
  flags |= FLAG_LOOK_START;
  mFuncs[ORDER_EVT2IDLE] = &Scheduler::func_look;
}

void Scheduler::func_evt2fld(gf::GfObj *obj) {
  if ((mUse & USE_LOOK_RESET) != 0) {
    lookTo(false, obj, nullptr, static_cast<EVT_aimtype>(0), true);
  }
  mFuncs[ORDER_EVT2FLD] = &Scheduler::func_return;
}

void Scheduler::func_motionEnd(gf::GfObj *obj) { mFuncs[ORDER_FLD2EVT] = &Scheduler::func_motionEnd_loop; }

void Scheduler::func_motionEnd_loop(gf::GfObj *obj) { mFuncs[ORDER_FLD2EVT] = &Scheduler::func_turn; }

f32 Scheduler::getRotY(gf::GfObj *obj, gf::GfObj *target) {
  gf::GfComTransform *targetTransform = target->getComponent<gf::GfComTransform>();
  gf::GfComTransform *transform = obj->getComponent<gf::GfComTransform>();
  const mm::Vec3 &pos = transform->getPosition();
  const mm::Vec3 &targetPos = targetTransform->getPosition();
  return -atan2f(pos.x - targetPos.x, -(pos.z - targetPos.z));
}

void Scheduler::func_turn_loop(gf::GfObj *obj) {
  if ((mUse & USE_TURN) == 0 || gf::GfGameUtil::isTurnEnd(handle)) {
    mFuncs[ORDER_FLD2EVT] = nullptr;
  }
}

void Scheduler::func_look(gf::GfObj *obj) {
  if ((mUse & USE_LOOK) == 0) {
    mFuncs[ORDER_EVT2IDLE] = nullptr;
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
  if ((flags & FLAG_LOOK_START) == 0) {
    lookTo(true, obj, target, static_cast<EVT_aimtype>(mAimType), false);
    return;
  }
  if (CharaUtil::isCanTarget(obj->unknownf8, target->unknownf8)) {
    lookTo(true, obj, target, static_cast<EVT_aimtype>(mAimType), true);
    flags &= ~FLAG_LOOK_START;
  }
}

void Scheduler::func_return(gf::GfObj *obj) {
  if ((mUse & USE_RETURN) != 0) {
    mWait = 360;
  }
  mFuncs[ORDER_EVT2FLD] = &Scheduler::func_return_loop;
}

void Scheduler::func_return_loop(gf::GfObj *obj) { mFuncs[ORDER_EVT2FLD] = &Scheduler::func_motion; }

void Scheduler::func_motion(gf::GfObj *obj) { mFuncs[ORDER_EVT2FLD] = &Scheduler::func_motion_loop; }

void Scheduler::func_motion_loop(gf::GfObj *obj) {
  if ((mUse & USE_ITEM) != 0) {
    gf::GfComAsm *anim = obj->getComponent<gf::GfComAsm>();
    if (mWait-- > 0 && anim != nullptr) {
      bool isLoop = anim->isLoop(gf::ANIM_LAYER_BASE);
      const char *state = anim->getStateName(gf::ANIM_LAYER_BASE);
      if (!isLoop || __builtin_strcmp(state, "S_idle") == 0) {
        return;
      }
    }
  }
  mFuncs[ORDER_EVT2FLD] = &Scheduler::func_item;
}

void Scheduler::func_item(gf::GfObj *obj) {
  if ((mUse & USE_ITEM) != 0) {
    mItem.fadein();
  }
  mFuncs[ORDER_EVT2FLD] = &Scheduler::func_item_loop;
}

void Scheduler::func_item_loop(gf::GfObj *obj) {
  if ((mUse & USE_ITEM) == 0 || !mItem.isFading()) {
    mFuncs[ORDER_EVT2FLD] = nullptr;
  }
}

void Scheduler::setUse(USE use, bool isUse) {
  if (isUse) {
    if ((mUse & use) != use) {
      mUse |= use;
    }
  } else {
    if ((mUse & use) != 0) {
      mUse &= ~use;
    }
  }
}

f32 Scheduler::getRotY(gf::GfObj *obj) { return mm::quatToEuler(obj->getComponent<gf::GfComTransform>()->getRotation()).y; }

} // namespace event
