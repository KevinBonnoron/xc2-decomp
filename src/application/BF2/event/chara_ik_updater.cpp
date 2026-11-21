#include "event/chara_ik_updater.h"

#include "event/chara_facial_util.h"
#include "framework/ik/ik_look_at_solver.h"
#include "framework/ik/ik_look_solver.h"
#include "framework/ik/ik_spine_solver.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior_event.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/intrusive_ptr.h"

namespace event {

// The constructor at 0x71000b9044 writes flags at +0x8, the handle at
// +0x10, Vec3::zero at +0x20, and Vec2::zero at +0x30 through +0x70.
CharaIKUpdater::CharaIKUpdater() : unknown08(), unknown0c(), unknown10(gf::unknown020), unknown18(0.0f), unknown20(mm::Vec3::zero) {
  f32 x = mm::Vec2::zero.x;
  f32 y = mm::Vec2::zero.y;
  unknown30.x = x;
  unknown30.y = y;
  unknown40.x = x;
  unknown40.y = y;
  unknown50.x = x;
  unknown50.y = y;
  unknown60.x = x;
  unknown60.y = y;
  unknown70.x = x;
  unknown70.y = y;
}

void CharaIKUpdater::create(gf::GF_OBJ_HANDLE *handle) {
  this->unknown10 = handle;
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    CharaFacialUtil::getLensLimit(unknown40, unknown50, unknown60, unknown70, obj);
  }
  unknown08.set(FLAG_UNKNOWN_0, true);
  unknown08.set(FLAG_UNKNOWN_1, true);
  unknown08.set(FLAG_UNKNOWN_2, true);
  unknown08.set(FLAG_UNKNOWN_3, true);
  unknown08.set(FLAG_UNKNOWN_4, false);
  unknown08.set(FLAG_UNKNOWN_6, false);
}

// The game calls update here without setting its float argument (0x71000b90fc, the register is never written): update never reads it, so
// the value is erased; 0.0f is the plausible expression and the original one cannot be checked.
void CharaIKUpdater::destroy() {
  update(0.0f);
  // The handle is reset before the two flag words are cleared, as in CharaDysUpdater::destroy and CharaPartUpdater::destroy. The order is
  // visible where this is inlined in ~CharaObj (0x71000be088 `str x21, [x19, #0xd70]` before 0x71000be08c `str xzr, [x19, #0xd68]`); the
  // clears first (the constructor's order) give `str xzr` first there, while this standalone copy (0x71000b9114, one `stp`) matches both.
  unknown10 = gf::unknown020;
  unknown08.clear();
  unknown0c.clear();
}

// 1.0.0: 0x71000b9124. Evidence for the forms below: `hasLook` is the game's own flag (w25, set by `orr w25, wzr, #1` at 0x71000b921c and read by
// `and w8, w25, w8` at 0x71000b93ec); the solver variables are declared in the order that gives the game's zeroing of the paths without a look solver
// (0x71000b9224..0x71000b9238: the lookAt zero apart, then the look zero, then the flag and spine zeros shared by both paths). The foot test
// `(flags & 0xe) == 0xe` and the target test `(flags & 0x11) == 0x11` are one `and` + `cmp` each (0x71000b9298, 0x71000b93c4), which a chain of test()
// calls does not give; the request test comes first, then the flag, then the behavior component (another order of the three gives another order of the
// `tbz`/`cbz`).
void CharaIKUpdater::update(f32 delta) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown10);
  if (obj == nullptr) {
    return;
  }
  gf::GfComBehaviorEvent *behavior = obj->getComponent<gf::GfComBehaviorEvent>();
  gf::GfComIK *ik = obj->getComponent<gf::GfComIK>();
  fw::SpineIkSolver *spine = nullptr;
  fw::LookAtIkSolver *lookAt = nullptr;
  fw::LookIkSolver *look = nullptr;
  bool hasLook = false;
  if (ik != nullptr) {
    look = ik->unknown003<fw::LookIkSolver>(gf::unknown002_3);
    if (look != nullptr) {
      hasLook = true;
      spine = look->unknown20.get();
      lookAt = look->unknown28.get();
    }
  }
  gf::GfComAsm *asmComponent = obj->getComponent<gf::GfComAsm>();
  if (unknown0c.test(REQUEST_UNKNOWN_0)) {
    gf::GfObjUtil::setEnableAllIK(unknown10, unknown08.test(FLAG_UNKNOWN_0), 0.0f);
  }
  if (unknown0c.test(REQUEST_UNKNOWN_1) && unknown08.test(FLAG_UNKNOWN_0) && behavior != nullptr) {
    behavior->setFootIK((unknown08.unknown001(0) & 0xe) == 0xe);
  }
  if (unknown0c.test(REQUEST_UNKNOWN_2) && unknown08.test(FLAG_UNKNOWN_0)) {
    if (behavior != nullptr) {
      if (!unknown08.test(FLAG_UNKNOWN_4)) {
        behavior->setTarget(false, unknown18 / 30.0f, false);
      } else {
        behavior->setTarget(true, unknown18 / 30.0f, unknown08.test(FLAG_UNKNOWN_5));
      }
    } else if (lookAt != nullptr && spine != nullptr && asmComponent != nullptr) {
      if (!unknown08.test(FLAG_UNKNOWN_4)) {
        if (!unknown08.test(FLAG_UNKNOWN_5)) {
          spine->startTargetFade(unknown18 / 30.0f);
          spine->fadeOut(unknown18 / 30.0f);
        }
        lookAt->startTargetFade(unknown18 / 30.0f);
        lookAt->fadeOut(unknown18 / 30.0f);
      } else {
        if (!unknown08.test(FLAG_UNKNOWN_5)) {
          spine->fadeIn(unknown18 / 30.0f);
          spine->startTargetFade(unknown18 / 30.0f);
        }
        lookAt->fadeIn(unknown18 / 30.0f);
        lookAt->startTargetFade(unknown18 / 30.0f);
      }
    }
  }
  if (unknown0c.test(REQUEST_UNKNOWN_3) && (unknown08.unknown001(0) & 0x11) == 0x11) {
    if (behavior != nullptr) {
      behavior->setTargetPos(unknown20);
    } else if (hasLook && asmComponent != nullptr) {
      look->setTarget(unknown20);
    }
  }
  if (unknown0c.test(REQUEST_UNKNOWN_4) && unknown08.test(FLAG_UNKNOWN_0)) {
    // The game copies the lens move into integer registers (`ldp w20, w21, [x19, #0x30]`, 0x71000b9418) and keeps the clamps there (`fmov w8, s0; eor w,
    // w8, #0x80000000`); two float locals give float registers.
    mm::Vec2 lens = unknown30;
    u32 type = gf::GfObjUtil::getEyeIKType(unknown10);
    if (type == 1) {
      if (lens.x < 0.0f) {
        lens.x = -(lens.x * unknown40.x);
      }
      if (lens.y < 0.0f) {
        lens.y = -(lens.y * unknown40.y);
      }
      if (lens.x > 0.0f) {
        lens.x = lens.x * unknown50.x;
      }
      if (lens.y > 0.0f) {
        lens.y = lens.y * unknown50.y;
      }
    } else if (type == 2) {
      if (lens.x < 0.0f) {
        lens.x = -(lens.x * unknown60.x);
      }
      if (lens.y < 0.0f) {
        lens.y = -(lens.y * unknown60.y);
      }
      if (lens.x > 0.0f) {
        lens.x = lens.x * unknown70.x;
      }
      if (lens.y > 0.0f) {
        lens.y = lens.y * unknown70.y;
      }
    } else {
      unknown0c.clear();
      return;
    }
    gf::GfObjUtil::setEnableEyeIK(unknown10, unknown08.test(FLAG_UNKNOWN_6), 0.0f);
    gf::GfObjUtil::setMoveEyeIK(unknown10, lens.y, lens.x);
  }
  unknown0c.clear();
}

void CharaIKUpdater::render(const mm::Vec3 &position, f32 height) { gf::GfObjUtil::getObj(unknown10); }

void CharaIKUpdater::setAllIK(bool isEnable) {
  unknown08.set(FLAG_UNKNOWN_0, isEnable);
  unknown18 = 0.0f;
  unknown0c.set(REQUEST_UNKNOWN_0);
  unknown0c.set(REQUEST_UNKNOWN_1);
  unknown0c.set(REQUEST_UNKNOWN_2);
  unknown0c.set(REQUEST_UNKNOWN_3);
  unknown0c.set(REQUEST_UNKNOWN_4);
}

void CharaIKUpdater::setFootIK(bool isEnable, FOOT_TYPE type) {
  switch (type) {
  case FOOT_TYPE_UNKNOWN_0:
    unknown08.set(FLAG_UNKNOWN_1, isEnable);
    break;
  case FOOT_TYPE_UNKNOWN_1:
    unknown08.set(FLAG_UNKNOWN_2, isEnable);
    break;
  case FOOT_TYPE_UNKNOWN_2:
    unknown08.set(FLAG_UNKNOWN_3, isEnable);
    break;
  }
  unknown0c.set(REQUEST_UNKNOWN_1);
}

void CharaIKUpdater::setTargetIK(bool isEnable, f32 frame, bool isNoSpine) {
  if (isEnable) {
    unknown18 = frame;
    unknown08.set(FLAG_UNKNOWN_4, true);
    unknown08.set(FLAG_UNKNOWN_5, isNoSpine);
    unknown0c.set(REQUEST_UNKNOWN_2);
  } else if (unknown08.test(FLAG_UNKNOWN_4)) {
    unknown08.set(FLAG_UNKNOWN_4, false);
    unknown08.set(FLAG_UNKNOWN_5, isNoSpine);
    unknown18 = frame;
    unknown0c.set(REQUEST_UNKNOWN_2);
  }
}

void CharaIKUpdater::setTargetPos(const mm::Vec3 &position) {
  unknown20 = position;
  unknown0c.set(REQUEST_UNKNOWN_3);
}

void CharaIKUpdater::setLensIK(bool isEnable, f32 x, f32 y) {
  unknown30.x = x;
  unknown30.y = y;
  unknown08.set(FLAG_UNKNOWN_6, isEnable);
  unknown0c.set(REQUEST_UNKNOWN_4);
}

bool CharaIKUpdater::checkField(gf::GfObj *obj) {
  gf::GF_OBJ_HANDLE *handle = obj->unknownf8;
  for (u32 i = 0; i < 3; i++) {
    gf::GF_OBJ_HANDLE *driver = gf::GfGameParty::getHandleDriver(i);
    if (gf::GfGameParty::isLeaderDriver(driver)) {
      continue;
    }
    if (driver == handle) {
      return false;
    }
  }
  for (u32 i = 0; i < 3; i++) {
    if (gf::GfGameParty::getHandleBlade(i, -1) == handle) {
      return false;
    }
  }
  return true;
}

} // namespace event
