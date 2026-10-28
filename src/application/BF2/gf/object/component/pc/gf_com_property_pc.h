#pragma once
#include <stddef.h>

#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/property/gf_com_property.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
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

class EnviromentSensor;
struct MsgDebugActivateComponentWindow;
struct MsgPcFieldNotifyChangePlayerID;
struct MsgPcFieldWarpCancel;

namespace pc {

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
    f32 unknown00;                  // Inferred role: x; original member name unknown.
    f32 unknown04;                  // Inferred role: y; original member name unknown.
    mm::mtl::BitFlag<32> unknown08; // Inferred role: flags; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  bool existInputXY() const;
  void setLocomotion(const anm::QsTransform &locomotion);
  void setEnvSensorCheckFlags(u32 flags, bool isEnable);
  EnviromentSensor *getEnvSensor() const;
  void resetInput();
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void procMsgPcFieldNotifyChangePlayerID(fw::MessageObject *object, MsgPcFieldNotifyChangePlayerID &message);
  void procMsgPcFieldWarpCancel(fw::MessageObject *object, MsgPcFieldWarpCancel &message);

  u32 unknown38; // Inferred role: player id set by MsgPcFieldNotifyChangePlayerID; original member name unknown.
  u8 _3c[0x60 - 0x3c];
  Input unknown60; // Inferred role: input; original member name unknown.
  Input unknown6c; // Inferred role: previous input; original member name unknown.
  u8 _78[0x80 - 0x78];
  mm::Vec3 unknown80; // Inferred role: velocity; original member name unknown.
  f32 unknown90;      // Inferred role: vertical speed; original member name unknown.
  f32 unknown94;      // Inferred role: horizontal speed; original member name unknown.
  u8 _98[0xc0 - 0x98];
  f32 unknownc0; // Role and original member name unknown.
  u8 _c4[0x110 - 0xc4];
  u32 unknown110_0 : 1; // Inferred role: field control; original member name unknown.
  u32 unknown110_1 : 1; // Inferred role: battle control; original member name unknown.
  u32 : 1;
  u32 unknown110_3 : 1; // Inferred role: enable gravity; original member name unknown.
  u32 unknown110_4 : 1; // Inferred role: set by GfPropertyField::flushOwner while sliding; original member name unknown.
  u32 : 2;
  u32 unknown110_7 : 1; // Inferred role: on slide; original member name unknown.
  u32 : 1;
  u32 unknown111_1 : 1; // Inferred role: selects mode 2 in getMode; original member name unknown.
  u32 unknown111_2 : 1; // Inferred role: pad control; original member name unknown.
  u32 unknown111_3 : 1; // Inferred role: dead; original member name unknown.
  u32 unknown111_4 : 1; // Inferred role: dead sequence requested; original member name unknown.
  u32 : 13;
  u32 unknown113_2 : 1; // Inferred role: warp requested, cleared by MsgPcFieldWarpCancel; original member name unknown.
  u32 : 5;
  u8 _114[0x118 - 0x114];
  f32 unknown118; // Inferred role: water height compared by StateUtilField::isInterruptionWater; original member name unknown.
  u8 _11c[0x120 - 0x11c];
  s32 unknown120; // Inferred role: mode compared with 1 by StateFieldWaterDeadDive::enter; original member name unknown.
  u8 _124[0x160 - 0x124];
  mm::Vec3 unknown160; // Inferred role: position; original member name unknown.
  mm::Quat unknown170; // Inferred role: rotation; original member name unknown.
  u8 _180[0x1e0 - 0x180];
  mm::Vec3 unknown1e0; // Inferred role: default input direction; original member name unknown.
  u8 _1f0[0x2b0 - 0x1f0];
  mm::Vec3 unknown2b0; // Inferred role: input Y axis; original member name unknown.
  u8 _2c0[0x2d0 - 0x2c0];
  mm::Vec3 unknown2d0; // Inferred role: input X axis; original member name unknown.
  u8 _2e0[0x2f0 - 0x2e0];
  f32 unknown2f0; // Inferred role: water offset compared by StateUtilField::isInterruptionWater; original member name unknown.
  u8 _2f4[0x310 - 0x2f4];
  pc::GfPropertyField unknown310; // Inferred role: field; original member name unknown.
};

static_assert(offsetof(GfComPropertyPc, unknown38) == 0x38, "");
static_assert(offsetof(GfComPropertyPc, unknown60) == 0x60, "");
static_assert(offsetof(GfComPropertyPc, unknown6c) == 0x6c, "");
static_assert(offsetof(GfComPropertyPc, unknown80) == 0x80, "");
static_assert(offsetof(GfComPropertyPc, unknown90) == 0x90, "");
static_assert(offsetof(GfComPropertyPc, unknown94) == 0x94, "");
static_assert(offsetof(GfComPropertyPc, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComPropertyPc, unknown118) == 0x118, "");
static_assert(offsetof(GfComPropertyPc, unknown120) == 0x120, "");
static_assert(offsetof(GfComPropertyPc, unknown160) == 0x160, "");
static_assert(offsetof(GfComPropertyPc, unknown170) == 0x170, "");
static_assert(offsetof(GfComPropertyPc, unknown1e0) == 0x1e0, "");
static_assert(offsetof(GfComPropertyPc, unknown2b0) == 0x2b0, "");
static_assert(offsetof(GfComPropertyPc, unknown2d0) == 0x2d0, "");
static_assert(offsetof(GfComPropertyPc, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfComPropertyPc, unknown310) == 0x310, "");

u32 getMode(GfComPropertyPc &property);

} // namespace gf
