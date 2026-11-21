#include "event/chara_eva_player.h"

#include <math.h>

#include "event/chara_dys_updater.h"
#include "event/chara_obj.h"
#include "event/chara_play_action.h"
#include "event/chara_util.h"
#include "event/tar_axis.h"
#include "gf/event/gf_evt_model.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "rcha/rcha_ex.h"

enum EVT_aimtype : int;
enum EVT_tarcvtype : int;

namespace event {

CharaEvaPlayer::CharaEvaPlayer()
    : unknown08(0), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(0.0f), unknown40(0.0f, 0.0f, 0.0f), unknown50(false),
      unknown60(0.0f, 0.0f, 0.0f), unknown70(0), unknown74(0), unknown78(0), unknown7c(1), unknown80(1), unknown84(1) {}

// Inferred helper: a Vec3 track of the rcha animation at a fractional frame, linearly interpolated between the two frames around it;
// original name unknown. Evidence: the interpolation is inlined in CharaEvaPlayer::update (0x71000c98c4) for the weapon and object
// positions and the target.
static inline mm::Vec3 unknown030(const CRchaEx *rcha, void (CRchaEx::*get)(mm::Vec3 &, f32) const, f32 frame) {
  mm::Vec3 a;
  mm::Vec3 b;
  mm::Vec3 value;
  f32 base = static_cast<f32>(static_cast<int>(frame));
  f32 next = base + 1.0f;
  if (base == frame) {
    (rcha->*get)(value, base);
  } else {
    (rcha->*get)(a, base);
    (rcha->*get)(b, next);
    value = a + (b - a) * (frame - base);
  }
  return value;
}

// Inferred helper: like unknown030 for a rotation: the second frame is first wrapped to within pi of the first on each axis;
// original name unknown. Evidence: inlined in CharaEvaPlayer::update for the weapon and object rotations.
static inline mm::Vec3 unknown031(const CRchaEx *rcha, void (CRchaEx::*get)(mm::Vec3 &, f32) const, f32 frame) {
  mm::Vec3 a;
  mm::Vec3 b;
  mm::Vec3 value;
  f32 base = static_cast<f32>(static_cast<int>(frame));
  f32 next = base + 1.0f;
  if (base == frame) {
    (rcha->*get)(value, base);
  } else {
    (rcha->*get)(a, base);
    (rcha->*get)(b, next);
    while (b.x < a.x - 3.1415927f) {
      b.x += 6.2831855f;
    }
    while (a.x + 3.1415927f < b.x) {
      b.x -= 6.2831855f;
    }
    while (b.y < a.y - 3.1415927f) {
      b.y += 6.2831855f;
    }
    while (a.y + 3.1415927f < b.y) {
      b.y -= 6.2831855f;
    }
    while (b.z < a.z - 3.1415927f) {
      b.z += 6.2831855f;
    }
    while (a.z + 3.1415927f < b.z) {
      b.z -= 6.2831855f;
    }
    value = a + (b - a) * (frame - base);
  }
  return value;
}

// Inferred helper: a scalar track of the rcha animation at a fractional frame, linearly interpolated between the two frames
// around it; original name unknown. Evidence: inlined in CharaEvaPlayer::update for the object and weapon scales and the
// dynamics blend.
template <typename R> static inline f32 unknown032(const CRchaEx *rcha, R (CRchaEx::*get)(f32 &, f32) const, f32 frame) {
  f32 a;
  f32 base = static_cast<f32>(static_cast<int>(frame));
  f32 next = base + 1.0f;
  if (base == frame) {
    (rcha->*get)(a, base);
    return a;
  }
  f32 b;
  (rcha->*get)(a, base);
  (rcha->*get)(b, next);
  return (b - a) * (frame - base) + a;
}

void CharaEvaPlayer::update(f32 delta) {
  if (unknown18 == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown18->unknown20);
  if (obj == nullptr) {
    return;
  }
  if (unknown30 == nullptr) {
    return;
  }
  f32 frame = unknown38;
  f32 lastFrame = static_cast<f32>(unknown30->getFrameCount()) - 1.0f;
  frame = mm::min(frame, lastFrame);
  u32 flags = unknown08;
  if ((flags & FLAG_UNKNOWN_1) != 0) {
    if (!unknown30->getWeaponSpMotion(frame)) {
      unknown08 &= ~FLAG_UNKNOWN_2;
    } else {
      unknown08 |= FLAG_UNKNOWN_2;
      if ((flags & FLAG_UNKNOWN_2) == 0 && unknown28 != nullptr) {
        setSpMotWeapon(true, unknown28);
        obj->getComponent<gf::GfComTransform>();
        unknown10->setPos(unknown40);
        unknown10->setRot(mm::Vec3::zero);
      }
    }
  }
  if ((unknown08 & (FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) == FLAG_UNKNOWN_1) {
    mm::Vec3 pos;
    mm::Vec3 rot;
    if ((unknown08 & FLAG_UNKNOWN_3) == 0) {
      pos = unknown030(unknown30, &CRchaEx::getWeaponPos, frame);
      rot = unknown031(unknown30, &CRchaEx::getWeaponRot, frame);
    } else {
      pos = unknown030(unknown30, &CRchaEx::getObjPos, frame);
      rot = unknown031(unknown30, &CRchaEx::getObjRot, frame);
    }
    f32 objScale = unknown032(unknown30, &CRchaEx::getObjScl, frame);
    f32 weaponScale = unknown032(unknown30, &CRchaEx::getWeaponScl, frame);
    obj->getComponent<gf::GfComTransform>();
    unknown10->setPos(pos);
    mm::Vec3 euler;
    mm::quatToEuler(mm::unknown005(rot), euler);
    unknown10->setRot(euler);
    if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_2) {
      unknown10->setScaleWeapon(weaponScale != 1.0f ? weaponScale : objScale);
    }
  }

  if ((unknown08 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_2)) == FLAG_UNKNOWN_0) {
    int prevAction = unknown70;
    mm::Vec3 pos;
    mm::Vec3 rot;
    pos = unknown030(unknown30, &CRchaEx::getObjPos, frame);
    rot = unknown031(unknown30, &CRchaEx::getObjRot, frame);
    bool isTarget = unknown30->isTargetEnable(frame);
    mm::Vec3 tar;
    if (isTarget) {
      tar = unknown030(unknown30, &CRchaEx::getTarget, frame);
    } else {
      tar = mm::Vec3::zero;
    }
    int actionType = unknown30->getActionType(frame);
    unknown30->getFacePrisetType(frame);
    unknown30->getEyeType(frame);
    obj->getComponent<gf::GfComTransform>();
    unknown10->setPos(pos);
    mm::Vec3 euler;
    mm::quatToEuler(mm::unknown005(rot), euler);
    unknown10->setRot(euler);
    if (unknown50 != isTarget || !(fabsf(tar.x - unknown60.x) <= 0.000001f && fabsf(tar.y - unknown60.y) <= 0.000001f && fabsf(tar.z - unknown60.z) <= 0.000001f)) {
      playTar(isTarget, tar);
    }
    if (prevAction != actionType) {
      playAction(actionType);
    }
  }

  if ((unknown08 & FLAG_UNKNOWN_2) == 0) {
    int curDisp = unknown7c;
    int curMount = unknown80;
    int battle = unknown84;
    int disp = 0;
    int mount = 0;
    int battleType = 0;
    int footL = 0;
    int footR = 0;
    f32 blend = unknown032(unknown30, &CRchaEx::getDynamicsBlend, frame);
    unknown30->getWeaponDisp(disp, frame);
    unknown30->getWeaponMount(mount, frame);
    unknown30->getWeaponBattle(battleType, frame);
    unknown30->getFootEffectL(footL, frame);
    unknown30->getFootEffectR(footR, frame);
    unknown20->setDynamicsBlendWeight(blend);
    if (disp > 0 && curDisp != disp) {
      setDispWeapon(disp);
    }
    if (mount > 0 && curMount != mount) {
      setMountWeapon(mount);
    }
    if (battleType > 0 && battle != battleType) {
      setBattleWeapon(battleType);
    }
    if (footL > 0) {
      playFoot(false);
    }
    if (footR > 0) {
      playFoot(true);
    }
  }

  gf::GfObjAcc acc(unknown18->unknown20);
  int extMeshMax = acc.getExtMeshMax();
  for (int i = 0; i < extMeshMax; i++) {
    const char *name = acc.getExtMeshName(i);
    if (*name != '\0') {
      int visible = 0;
      unknown30->getVisible(visible, name, frame);
      if (visible == 1) {
        unknown10->setExtDisp(name, true);
      } else if (visible == 2) {
        unknown10->setExtDisp(name, false);
      }
    }
  }

  unknown88.update(delta);
  unknowne0.update(delta);
  unknown38 = unknown38 + delta;
  f32 maxFrame = static_cast<f32>(unknown30->getFrameCount()) - 1.0f;
  if (maxFrame < unknown38) {
    unknown38 = maxFrame;
  }
}

// The game's setSpMotWeapon (0x71000cab7c, called from nowhere else in the binary) is what CharaEvaPlayer::update inlines at 0x71000c9970: the true
// arm below is its instruction sequence with the constant argument. Defined inline because the out-of-line copy does not match: its false arm stores
// unknown84 before the flags where the game stores it after them (one store order, 36 instructions each); the forms tried for it (84 before or after
// the execCmd call in either arm, a ternary command and data, `unknown84 = isSpMotion ? 20 : 1` after the arms (csel, 37), an early return, the arms
// swapped, a call of setBattleWeapon(1) (not inlined)) either keep that order or stop update matching.
inline void CharaEvaPlayer::setSpMotWeapon(bool isSpMotion, void *data) {
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_2) {
    if (isSpMotion) {
      unknown88.execCmd(unknown18, CharaWpnAsm::CMD_UNKNOWN_19, false, data);
      unknown84 = 20;
    } else {
      unknown88.execCmd(unknown18, CharaWpnAsm::CMD_UNKNOWN_0, false, nullptr);
      unknown84 = 1;
    }
  }
}

void CharaEvaPlayer::setScaleWeapon(f32 scale) {
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_2) {
    unknown10->setScaleWeapon(scale);
  }
}

void CharaEvaPlayer::playTar(bool isPlay, const mm::Vec3 &tar) {
  if ((unknown08 & FLAG_UNKNOWN_0) == 0) {
    return;
  }
  if (isPlay) {
    unknown10->setTar(TarAxis(TarAxis::AXIS_UNKNOWN_1, tar), -1.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  } else {
    unknown10->setTar(TarAxis(TarAxis::AXIS_UNKNOWN_1, tar), 0.0f, static_cast<EVT_tarcvtype>(0), static_cast<EVT_aimtype>(0), -1.0f, -1.0f);
  }
  unknown50 = isPlay;
  this->unknown60 = tar;
}

void CharaEvaPlayer::playAction(int type) {
  if (unknown18 == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown18->unknown20);
  if (obj == nullptr || (unknown08 & FLAG_UNKNOWN_0) == 0) {
    return;
  }
  stopAction();
  if (type <= 0) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (type == 1) {
    CharaUtil::setStat(obj, CharaPlayAction::type2stat(type, 1));
  } else if (type <= 16) {
    CharaUtil::setStat(obj, CharaPlayAction::type2stat(type, 1));
  } else if (type <= 22) {
    CharaUtil::setStat(obj, CharaPlayAction::type2stat(type, 1));
    CharaUtil::combat(unknown18, true, true);
  }
  unknown70 = type;
}

void CharaEvaPlayer::setDispWeapon(int type) {
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_0) {
    unknown10->setHideWeapon(WPNHIDEID_UNKNOWN_1, type > 1, false);
    unknown10->setHideWeapon(WPNHIDEID_UNKNOWN_1, type > 1, true);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_1) {
    unknown10->setHideWeapon(WPNHIDEID_UNKNOWN_1, type > 1, false);
    unknown10->setHideWeapon(WPNHIDEID_UNKNOWN_1, type > 1, true);
  }
  unknown7c = type;
}

void CharaEvaPlayer::setBattleWeapon(int type) {
  CharaWpnAsm::CMD cmd = static_cast<CharaWpnAsm::CMD>(type - 1);
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_2) {
    unknown88.execCmd(unknown18, cmd, false, nullptr);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_0) {
    unknown88.execCmd(unknown18, cmd, false, nullptr);
    unknowne0.execCmd(unknown18, cmd, true, nullptr);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_1) {
    unknown88.execCmd(unknown18, cmd, false, nullptr);
    unknowne0.execCmd(unknown18, cmd, true, nullptr);
  }
  unknown84 = type;
}

// The two arms send the same message with the other foot: the game keeps a branch on isRight (tbz at 0x71000cb104) with the stores of the message in each arm and
// one shared send. A ternary of two messages gives a select and one 64-bit store of the id and mask (56 instructions), so each arm builds and sends its own.
void CharaEvaPlayer::playFoot(bool isRight) {
  if (unknown18 == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown18->unknown20);
  if (obj == nullptr) {
    return;
  }
  gf::GfComProperty *property = obj->getComponent<gf::GfComProperty>();
  gf::GfComEffectCaster *caster = obj->getComponent<gf::GfComEffectCaster>();
  if (property != nullptr && caster != nullptr) {
    if (isRight) {
      gf::MsgFxFootPrintEv message(0);
      gf::GfObj *sender = static_cast<gf::GfObj *>(property->unknown08);
      caster->recieveMessage(sender, message);
    } else {
      gf::MsgFxFootPrintEv message(1);
      gf::GfObj *sender = static_cast<gf::GfObj *>(property->unknown08);
      caster->recieveMessage(sender, message);
    }
  }
}

void CharaEvaPlayer::setMountWeapon(int type) {
  if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_0) {
    unknown88.mount(unknown18, type > 1, false);
    unknowne0.mount(unknown18, type > 1, true);
  } else if (unknown18->unknown18 == gf::GF_EVT_MODEL_UNKNOWN_1) {
    unknown88.mount(unknown18, type > 1, false);
    unknowne0.mount(unknown18, type > 1, true);
  }
  unknown80 = type;
}

void CharaEvaPlayer::stopTar() {
  if (unknown50) {
    unknown50 = false;
    unknown60 = mm::Vec3::zero;
  }
}

void CharaEvaPlayer::stopAction() {
  if (unknown18 == nullptr) {
    return;
  }
  gf::GfObj *obj = gf::GfObjUtil::getObj(unknown18->unknown20);
  if (obj == nullptr || unknown70 <= 0) {
    return;
  }
  if (unknown70 == 1) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (unknown70 <= 16) {
    CharaUtil::setStat(obj, "S_idle");
  } else if (unknown70 <= 22) {
    CharaUtil::setStat(obj, "S_idle");
    CharaUtil::combat(unknown18, false, true);
  }
  unknown70 = 0;
}

} // namespace event
