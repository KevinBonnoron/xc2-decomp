#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/property/gf_com_property.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace anm {
struct QsTransform;
} // namespace anm

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct MsgDebugActivateComponentWindow;
struct MsgObjectGetVelocity;
struct MsgPcFieldNotifyChangePlayerID;
struct MsgPcFieldWarpCancel;

namespace pc {
struct MoveParam;
struct SlideParam;

enum InputID {
  INPUT_ID_DECIDE = 0,
  INPUT_ID_LOCK = 1,
  INPUT_ID_JUMP = 2,
  INPUT_ID_WALL_RELEASE = 3,
  INPUT_ID_LURE = 4,
  INPUT_ID_BATTLE_START = 5,
  INPUT_ID_BATTLE_END = 6,
  INPUT_ID_ART_01 = 7,
  INPUT_ID_ART_02 = 8,
  INPUT_ID_ART_03 = 9,
  INPUT_ID_BLADE_CHANGE_00 = 10,
  INPUT_ID_BLADE_CHANGE_01 = 11,
  INPUT_ID_BLADE_CHANGE_02 = 12,
  INPUT_ID_KAKUSEI = 13,
  INPUT_ID_REQUEST_PERMIT_01 = 14,
  INPUT_ID_REQUEST_PERMIT_02 = 15,
  INPUT_ID_SP_ATTACK = 16,
  INPUT_ID_CHAIN_ATTACK = 17,
  INPUT_ID_BATTLE_RESCUE = 18,
  INPUT_ID_CHANGE_CAMERA_MODE = 19,
  INPUT_ID_ORDER_RALLY = 20,
  INPUT_ID_CHANGE_TARGET_R = 21,
  INPUT_ID_CHANGE_TARGET_L = 22,
};

} // namespace pc

class GfComPropertyPc : public GfComProperty {
public:
  struct Input {
    f32 unknown00;                     // Inferred role: x; original member name unknown.
    f32 unknown04;                     // Inferred role: y; original member name unknown.
    mm::mtl::unknown027<32> unknown08; // Inferred role: flags; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  bool existInputXY() const;
  const mm::mtl::RTTI *getRTTI() const override;
  f32 getGravity() const;
  const fw::Transform &getLocomotion() const;
  void setPadControl(bool padControl);
  void resetParams();
  void setLocomotion(const anm::QsTransform &locomotion);
  void syncDirection();
  void procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message);
  void setEnvSensorCheckFlags(u32 flags, bool isEnable);
  bool testEnvSensorCheckFlags(EnviromentSensor::Flag flag);
  EnviromentSensor *getEnvSensor() const;
  void resetInput();
  void setInputDirPow(const mm::Vec3 &direction, f32 power);
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void procMsgPcFieldNotifyChangePlayerID(fw::MessageObject *object, MsgPcFieldNotifyChangePlayerID &message);
  void procMsgPcFieldWarpCancel(fw::MessageObject *object, MsgPcFieldWarpCancel &message);

  // Inferred role: slide param of the pc param list entry 4 ("slide"); original name unknown.
  const pc::SlideParam *unknown001() const { return static_cast<const pc::SlideParam *>(unknown300->unknown10[4].param); }
  // Inferred role: slide param of the pc param list entry 4 ("slide"), null when the list is shorter; original name unknown.
  const pc::SlideParam *unknown004() const {
    const fw::ParamList *paramList = unknown300.operator->();
    return paramList->unknown0c > 4 ? static_cast<const pc::SlideParam *>(paramList->unknown10[4].param) : nullptr;
  }
  // Inferred role: move param of the pc param list entry 1 ("move"), null when the list is shorter; original name unknown.
  const pc::MoveParam *unknown005() const {
    const fw::ParamList *paramList = unknown300.operator->();
    return paramList->unknown0c > 1 ? static_cast<const pc::MoveParam *>(paramList->unknown10[1].param) : nullptr;
  }

  // Inferred role: moving, from the velocity or the value at 0xc0 (shared by gf::pc::isMainPcMove and isBuddyPcMove); original
  // name unknown.
  bool unknown002() const {
    if (unknown80.x * unknown80.x + unknown80.y * unknown80.y + unknown80.z * unknown80.z > 0.0f) {
      return true;
    }

    return unknownc0 > 0.0f;
  }

  // Inferred role: requests a warp of the given type to the transform (sets the warp requested flag); original name unknown.
  void unknown003(const fw::Transform &transform, u32 type) {
    unknown150 = type;
    unknown130 = transform;
    unknown113_2 = true;
  }

  u32 unknown38; // Inferred role: player id set by MsgPcFieldNotifyChangePlayerID; original member name unknown.
  u8 _3c[0x60 - 0x3c];
  Input unknown60; // Inferred role: input; original member name unknown.
  Input unknown6c; // Inferred role: previous input; original member name unknown.
  u8 _78[0x80 - 0x78];
  mm::Vec3 unknown80; // Inferred role: velocity; original member name unknown.
  f32 unknown90;      // Inferred role: vertical speed; original member name unknown.
  f32 unknown94;      // Inferred role: horizontal speed; original member name unknown.
  u8 _98[0xa0 - 0x98];
  fw::Transform m_locomotion;
  f32 unknownc0; // Role and original member name unknown.
  u8 _c4[0xd0 - 0xc4];
  mm::Vec3 unknownd0; // Inferred role: slide direction, written by StateUtilField::setSlideDirForce; original member name unknown.
  u8 _e0[0xf0 - 0xe0];
  f32 unknownf0; // Role and original member name unknown; compared with the start time of the slide param by StateUtilField::isStartSlidePosuture.
  u8 _f4[0x100 - 0xf4];
  mm::Vec3 unknown100;  // Inferred role: offset added to the fall speed; original member name unknown.
  u32 unknown110_0 : 1; // Inferred role: field control; original member name unknown.
  u32 unknown110_1 : 1; // Inferred role: battle control; original member name unknown.
  u32 unknown110_2 : 1; // Inferred role: locomotion set by setLocomotion; original member name unknown.
  u32 unknown110_3 : 1; // Inferred role: enable gravity; original member name unknown.
  u32 unknown110_4 : 1; // Inferred role: set by GfPropertyField::flushOwner while sliding; original member name unknown.
  u32 unknown110_5 : 1; // Inferred role: water warp enabled, tested by AIAgentField::procMsgPcFieldNotifyWaterWarp; original member name unknown.
  u32 unknown110_6 : 1; // Inferred role: battle action running, cleared by StateBattle::Leave; original member name unknown.
  u32 unknown110_7 : 1; // Inferred role: on slide; original member name unknown.
  u32 : 1;
  u32 unknown111_1 : 1; // Inferred role: selects mode 2 in getMode; original member name unknown.
  u32 unknown111_2 : 1; // Inferred role: pad control; original member name unknown.
  u32 unknown111_3 : 1; // Inferred role: dead; original member name unknown.
  u32 unknown111_4 : 1; // Inferred role: dead sequence requested; original member name unknown.
  u32 unknown111_5 : 1; // Inferred role: poisoned, selects the poison slow of the field param; original member name unknown.
  u32 unknown111_6 : 1; // Inferred role: head detect for the switcher, set by StateUtil::setEnableHeadDetectForSwitcher; original member name unknown.
  u32 unknown111_7 : 1; // Inferred role: cleared with the battle control flag by StateBattle::Leave; original member name unknown.
  u32 : 10;
  u32 unknown113_2 : 1; // Inferred role: warp requested, cleared by MsgPcFieldWarpCancel; original member name unknown.
  u32 : 5;
  s32 unknown114; // Inferred role: ground type, 3 in water (the field AI then reads the water params); original member name unknown.
  f32 unknown118; // Inferred role: water height compared by StateUtilField::isInterruptionWater; original member name unknown.
  f32 unknown11c; // Inferred role: water depth; original member name unknown.
  s32 unknown120; // Inferred role: mode compared with 1 by StateFieldWaterDeadDive::enter; original member name unknown.
  u8 _124[0x130 - 0x124];
  fw::Transform unknown130; // Inferred role: warp target transform; original member name unknown.
  u32 unknown150;           // Inferred role: warp type; original member name unknown.
  u8 _154[0x160 - 0x154];
  mm::Vec3 unknown160; // Inferred role: position; original member name unknown.
  mm::Quat unknown170; // Inferred role: rotation; original member name unknown.
  mm::Vec3 unknown180; // Inferred role: previous position, compared with the position by gf::pc::isStack; original member name unknown.
  u8 _190[0x1c0 - 0x190];
  mm::Vec3 unknown1c0; // Inferred role: up axis, unitY rotated by the rotation in syncDirection; original member name unknown.
  u8 _1d0[0x1e0 - 0x1d0];
  mm::Vec3 unknown1e0; // Inferred role: default input direction; original member name unknown.
  mm::Vec3 unknown1f0; // Inferred role: negated unknown1e0, written by syncDirection; original member name unknown.
  mm::Vec3 unknown200; // Inferred role: negated X axis, -unitX rotated by the rotation in syncDirection; original member name unknown.
  u8 _210[0x290 - 0x210];
  mm::Vec3 unknown290; // Inferred role: input Y axis on the wall, read by TaskFieldWallEscape::update; original member name unknown.
  u8 _2a0[0x2b0 - 0x2a0];
  mm::Vec3 unknown2b0; // Inferred role: input Y axis; original member name unknown.
  u8 _2c0[0x2d0 - 0x2c0];
  mm::Vec3 unknown2d0; // Inferred role: input X axis; original member name unknown.
  u8 _2e0[0x2f0 - 0x2e0];
  f32 unknown2f0; // Inferred role: water offset compared by StateUtilField::isInterruptionWater; original member name unknown.
  u8 _2f4[0x2f8 - 0x2f4];
  f32 unknown2f8; // Inferred role: landing height; original member name unknown.
  u8 _2fc[0x300 - 0x2fc];
  mm::mtl::IntrusivePtr<fw::ParamList> unknown300; // Inferred role: pc param list; original member name unknown.
  u8 _308[0x310 - 0x308];
  pc::GfPropertyField unknown310;  // Inferred role: field; original member name unknown.
  pc::GfPropertyBattle unknown470; // Inferred role: battle; original member name unknown.
};

static_assert(offsetof(GfComPropertyPc, unknown38) == 0x38, "");
static_assert(offsetof(GfComPropertyPc, unknown60) == 0x60, "");
static_assert(offsetof(GfComPropertyPc, unknown6c) == 0x6c, "");
static_assert(offsetof(GfComPropertyPc, unknown80) == 0x80, "");
static_assert(offsetof(GfComPropertyPc, unknown90) == 0x90, "");
static_assert(offsetof(GfComPropertyPc, unknown94) == 0x94, "");
static_assert(offsetof(GfComPropertyPc, m_locomotion) == 0xa0, "");
static_assert(offsetof(GfComPropertyPc, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComPropertyPc, unknownd0) == 0xd0, "");
static_assert(offsetof(GfComPropertyPc, unknownf0) == 0xf0, "");
static_assert(offsetof(GfComPropertyPc, unknown100) == 0x100, "");
static_assert(offsetof(GfComPropertyPc, unknown114) == 0x114, "");
static_assert(offsetof(GfComPropertyPc, unknown118) == 0x118, "");
static_assert(offsetof(GfComPropertyPc, unknown11c) == 0x11c, "");
static_assert(offsetof(GfComPropertyPc, unknown120) == 0x120, "");
static_assert(offsetof(GfComPropertyPc, unknown130) == 0x130, "");
static_assert(offsetof(GfComPropertyPc, unknown150) == 0x150, "");
static_assert(offsetof(GfComPropertyPc, unknown160) == 0x160, "");
static_assert(offsetof(GfComPropertyPc, unknown170) == 0x170, "");
static_assert(offsetof(GfComPropertyPc, unknown180) == 0x180, "");
static_assert(offsetof(GfComPropertyPc, unknown1c0) == 0x1c0, "");
static_assert(offsetof(GfComPropertyPc, unknown1e0) == 0x1e0, "");
static_assert(offsetof(GfComPropertyPc, unknown1f0) == 0x1f0, "");
static_assert(offsetof(GfComPropertyPc, unknown200) == 0x200, "");
static_assert(offsetof(GfComPropertyPc, unknown290) == 0x290, "");
static_assert(offsetof(GfComPropertyPc, unknown2b0) == 0x2b0, "");
static_assert(offsetof(GfComPropertyPc, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfComPropertyPc, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfComPropertyPc, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfComPropertyPc, unknown300) == 0x300, "");
static_assert(offsetof(GfComPropertyPc, unknown310) == 0x310, "");
static_assert(offsetof(GfComPropertyPc, unknown470) == 0x470, "");

u32 getMode(GfComPropertyPc &property);

} // namespace gf
