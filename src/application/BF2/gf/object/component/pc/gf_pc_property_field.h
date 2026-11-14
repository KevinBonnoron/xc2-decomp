#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "fw/fw_param_manager.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/gf_pc_property_pc_interface.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

class GfComPropertyPc;
struct GF_OBJ_HANDLE;
struct MsgObjectFlushProperty;

enum {
  MSG_PC_FIELD_NOTIFY_UNKNOWN_16777232 = 0x1000010, // Inferred role: msg pc field notify wall jump; original name unknown.
  MSG_PC_FIELD_NOTIFY_UNKNOWN_16777233 = 0x1000011, // Inferred role: msg pc field notify big jump; original name unknown.
  MSG_PC_FIELD_NOTIFY_UNKNOWN_16777234 = 0x1000012, // Inferred role: msg pc field notify wall jump start; original name unknown.
  MSG_PC_FIELD_NOTIFY_UNKNOWN_16777236 = 0x1000014, // Inferred role: msg pc field notify warp; original name unknown.
  MSG_PC_FIELD_NOTIFY_UNKNOWN_16777237 = 0x1000015, // Inferred role: msg pc field notify high jump; original name unknown.
  MSG_PC_FIELD_NOTIFY_UNKNOWN_16777239 = 0x1000017, // Inferred role: msg pc field notify water warp; original name unknown.
  MSG_PC_FIELD_NOTIFY_UNKNOWN_16777247 = 0x100001f, // Inferred role: msg pc field notify water warp buddy; original name unknown.
};

struct MsgPcFieldNotifyBigJump : fw::Message {
  MsgPcFieldNotifyBigJump()
      : fw::Message(MSG_PC_FIELD_NOTIFY_UNKNOWN_16777233, 0x40), unknown10(mm::Vec3::zero), unknown20(0.0f), unknown24(2.0f), unknown28(1.0f), unknown30(nullptr), unknown38(0), unknown3c(0) {}

  mm::Vec3 unknown10;    // Inferred role: target position; original member name unknown.
  f32 unknown20;         // Role and original member name unknown.
  f32 unknown24;         // Role and original member name unknown.
  f32 unknown28;         // Role and original member name unknown.
  const void *unknown30; // Inferred role: gimmick bdat row; original member name unknown.
  u32 unknown38;         // Inferred role: gimmick id; original member name unknown.
  u32 unknown3c;         // Inferred role: gimmick id; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown20) == 0x20, "");
static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown30) == 0x30, "");
static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown3c) == 0x3c, "");
static_assert(sizeof(MsgPcFieldNotifyBigJump) == 0x40, "");

// Layout evidence: StateFieldPrepareBigJump::procMsgPcFieldNotifyBigJump (0x7100554760) broadcasts it with the big jump
// info, and AIAgentField::procMsgPcFieldHighJump reads that info through the member at 0x8.
struct MsgPcFieldNotifyHighJump : fw::Message {
  explicit MsgPcFieldNotifyHighJump(const MsgPcFieldNotifyBigJump *info) : fw::Message(MSG_PC_FIELD_NOTIFY_UNKNOWN_16777237, 0x40), unknown08(info) {}

  const MsgPcFieldNotifyBigJump *unknown08; // Inferred role: big jump info; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyHighJump, unknown08) == 0x08, "");

struct MsgPcFieldNotifyWarp : fw::Message {
  MsgPcFieldNotifyWarp() : fw::Message(MSG_PC_FIELD_NOTIFY_UNKNOWN_16777236, 0x40), unknown10(mm::Vec3::zero), unknown20(0.0f), unknown28(nullptr), unknown30(0), unknown34(0) {}

  mm::Vec3 unknown10;    // Inferred role: target position; original member name unknown.
  f32 unknown20;         // Role and original member name unknown.
  const void *unknown28; // Inferred role: gimmick bdat row; original member name unknown.
  u32 unknown30;         // Inferred role: gimmick id; original member name unknown.
  u32 unknown34;         // Inferred role: gimmick id; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWarp, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldNotifyWarp, unknown20) == 0x20, "");
static_assert(offsetof(MsgPcFieldNotifyWarp, unknown28) == 0x28, "");
static_assert(offsetof(MsgPcFieldNotifyWarp, unknown34) == 0x34, "");
static_assert(sizeof(MsgPcFieldNotifyWarp) == 0x40, "");

struct MsgPcFieldNotifyWallJump : fw::Message {
  MsgPcFieldNotifyWallJump() : fw::Message(MSG_PC_FIELD_NOTIFY_UNKNOWN_16777232, 0x40), unknown10(mm::Vec3::zero), unknown20(nullptr), unknown28(0), unknown2c(0) {}

  mm::Vec3 unknown10;    // Inferred role: target position; original member name unknown.
  const void *unknown20; // Inferred role: gimmick bdat row; original member name unknown.
  u32 unknown28;         // Inferred role: gimmick id; original member name unknown.
  u32 unknown2c;         // Inferred role: gimmick id passed to SCOM_QUEST_GIMMICK::createJump; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWallJump, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldNotifyWallJump, unknown20) == 0x20, "");
static_assert(offsetof(MsgPcFieldNotifyWallJump, unknown2c) == 0x2c, "");
static_assert(sizeof(MsgPcFieldNotifyWallJump) == 0x30, "");

// Layout evidence: StateFieldWallPrepareJump broadcasts it with the wall jump info of GfPropertyField::getWallJumpInfo,
// and AIAgentField::recieveMessage reads that info through the member at 0x8.
struct MsgPcFieldNotifyWallJumpStart : fw::Message {
  MsgPcFieldNotifyWallJumpStart(const MsgPcFieldNotifyWallJump *wallJump) : fw::Message(MSG_PC_FIELD_NOTIFY_UNKNOWN_16777234, 0x40), unknown08(wallJump) {}

  const MsgPcFieldNotifyWallJump *unknown08; // Inferred role: wall jump info; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWallJumpStart, unknown08) == 0x08, "");

// Layout evidence: StateFieldWaterPrepareWarp broadcasts it with the warp info of GfPropertyField::getWarpInfo, and
// AIAgentField::procMsgPcFieldNotifyWaterWarp reads that info through the member at 0x8.
struct MsgPcFieldNotifyWaterWarp : fw::Message {
  MsgPcFieldNotifyWaterWarp(const MsgPcFieldNotifyWarp *warp) : fw::Message(MSG_PC_FIELD_NOTIFY_UNKNOWN_16777239, 0x40), unknown08(warp) {}

  const MsgPcFieldNotifyWarp *unknown08; // Inferred role: warp info; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWaterWarp, unknown08) == 0x08, "");

// Layout evidence: StateFieldWaterWarpDive sends it to the buddies with the warp info of GfPropertyField::getWarpInfo,
// and AIAgentField::procMsgPcFieldNotifyWaterWarpBuddy reads that info through the member at 0x8.
struct MsgPcFieldNotifyWaterWarpBuddy : fw::Message {
  MsgPcFieldNotifyWaterWarpBuddy(const MsgPcFieldNotifyWarp *warp) : fw::Message(MSG_PC_FIELD_NOTIFY_UNKNOWN_16777247, 0x40), unknown08(warp) {}

  const MsgPcFieldNotifyWarp *unknown08; // Inferred role: warp info; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWaterWarpBuddy, unknown08) == 0x08, "");

namespace pc {
struct FieldParam;
struct WaterCommonParam;

class GfPropertyField : public GfPropertyPcInterface {
public:
  enum WALL_MOVE_MODE {
    WALL_MOVE_MODE_UNKNOWN_FFFFFFFF = -1, // Inferred role: wall move mode invalid; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_0 = 0,         // Inferred role: wall move mode up; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_1 = 1,         // Inferred role: wall move mode up right; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_2 = 2,         // Inferred role: wall move mode right; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_3 = 3,         // Inferred role: wall move mode down right; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_4 = 4,         // Inferred role: wall move mode down; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_5 = 5,         // Inferred role: wall move mode down left; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_6 = 6,         // Inferred role: wall move mode left; original name unknown.
    WALL_MOVE_MODE_UNKNOWN_7 = 7,         // Inferred role: wall move mode up left; original name unknown.
  };

  GfPropertyField();
  void setup(const GfComPropertyPc &property) override;
  void cleanup(const GfComPropertyPc &property) override;
  void flush(const GfComPropertyPc &property) override;
  void flushOwner(GfComPropertyPc &property) override;
  bool recieveMessage(const GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectFlushProperty(const GfComPropertyPc &property, fw::MessageObject *sender, MsgObjectFlushProperty &message);
  void resetStatus(const GfComPropertyPc &property);
  void setBigJumpInfo(const MsgPcFieldNotifyBigJump *message);
  const MsgPcFieldNotifyBigJump *getBigJumpInfo() const;
  void setWarpInfo(const MsgPcFieldNotifyWarp *message);
  const MsgPcFieldNotifyWarp *getWarpInfo() const;
  void setWallJump(const MsgPcFieldNotifyWallJump *message);
  const MsgPcFieldNotifyWallJump *getWallJumpInfo() const;
  f32 getWallHeightOffset() const;
  void flashWallInfo(const GfComPropertyPc &property);

  // Inferred role: field param of the param list entry 0 ("common"); original name unknown.
  const FieldParam *unknown001() const { return static_cast<const FieldParam *>(unknown08->unknown10[0].param); }
  // Inferred role: water param of the param list entry 9 ("water_common"); original name unknown.
  const WaterCommonParam *unknown002() const { return static_cast<const WaterCommonParam *>(unknown08->unknown10[9].param); }
  // Inferred role: climb wall info when it is valid; original name unknown.
  const EnviromentSensor::unknown003 *unknown003() const { return unknown10_6 ? &unknown130 : nullptr; }
  // Inferred role: adapter of the field param list entry at the index, null when the list is shorter; original name unknown.
  fw::ParamAdapter unknown004(u32 index) const {
    const fw::ParamList *paramList = unknown08.operator->();
    fw::ParamAdapter adapter;
    adapter.unknown00 = index < paramList->unknown0c ? &paramList->unknown10[index] : nullptr;
    return adapter;
  }
  // Inferred role: water param of the param list entry 9 ("water_common"), null when the list is shorter; original name unknown.
  const WaterCommonParam *unknown005() const {
    const fw::ParamList *paramList = unknown08.operator->();
    return paramList->unknown0c > 9 ? static_cast<const WaterCommonParam *>(paramList->unknown10[9].param) : nullptr;
  }
  // Inferred role: field param of the param list entry 0 ("common"), null when the list has no entries; original name unknown.
  const FieldParam *unknown006() const {
    const fw::ParamList *paramList = unknown08.operator->();
    if (paramList->unknown0c == 0 || paramList->unknown10 == nullptr) {
      return nullptr;
    }

    return static_cast<const FieldParam *>(paramList->unknown10[0].param);
  }

  mm::mtl::IntrusivePtr<fw::ParamList> unknown08; // Inferred role: param list; original member name unknown.
  u32 unknown10_0 : 1;                            // Inferred role: walk mode; original member name unknown.
  u32 unknown10_1 : 1;                            // Role and original member name unknown.
  u32 unknown10_2 : 1;                            // Inferred role: idle; original member name unknown.
  u32 unknown10_3 : 1;                            // Inferred role: pad control; original member name unknown.
  u32 unknown10_4 : 1;                            // Role and original member name unknown.
  u32 unknown10_5 : 1;                            // Inferred role: on wall, set by StateFieldOnWall; original member name unknown.
  u32 unknown10_6 : 1;                            // Inferred role: climb wall info valid; original member name unknown.
  u32 unknown10_7 : 1;                            // Inferred role: wall up move lock; original member name unknown.
  u32 unknown11_0 : 1;                            // Inferred role: auto run; original member name unknown.
  u32 unknown11_1 : 1;                            // Inferred role: air; original member name unknown.
  u32 unknown11_2 : 1;                            // Inferred role: special action; original member name unknown.
  u32 unknown11_3 : 1;                            // Inferred role: slide; original member name unknown.
  u32 unknown11_4 : 1;                            // Inferred role: big jump info valid; original member name unknown.
  u32 unknown11_5 : 1;                            // Inferred role: warp info valid; original member name unknown.
  u32 unknown11_6 : 1;                            // Inferred role: wall jump info valid; original member name unknown.
  u32 unknown11_7 : 1;                            // Role and original member name unknown.
  u32 unknown12_0 : 1;                            // Inferred role: under ground wall adsorption; original member name unknown.
  u32 unknown12_1 : 1;                            // Inferred role: field status reset; original member name unknown.
  u32 unknown12_2 : 14;                           // Role and original member name unknown.
  WALL_MOVE_MODE unknown14;                       // Inferred role: wall move mode; original member name unknown.
  f32 unknown18;                                  // Inferred role: wall float; original member name unknown.
  f32 unknown1c;                                  // Inferred role: horizontal distance of the S_uplanding_00 locomotion; original member name unknown.
  f32 unknown20;                                  // Inferred role: height of the S_uplanding_00 locomotion; original member name unknown.
  f32 unknown24;                                  // Inferred role: horizontal distance of the S_uplanding_01 locomotion; original member name unknown.
  f32 unknown28;                                  // Inferred role: wall height; original member name unknown.
  f32 unknown2c;                                  // Inferred role: horizontal distance of the S_downlanding_00 locomotion; original member name unknown.
  f32 unknown30;                                  // Inferred role: height of the S_downlanding_00 locomotion; original member name unknown.
  f32 unknown34;                                  // Inferred role: horizontal distance of the S_downlanding_01 locomotion; original member name unknown.
  f32 unknown38;                                  // Inferred role: wall detach distance; original member name unknown.
  f32 unknown3c;                                  // Inferred role: climb up motion distance; original member name unknown.
  f32 unknown40;                                  // Inferred role: climb down motion distance; original member name unknown.
  f32 unknown44;                                  // Inferred role: climb right motion distance; original member name unknown.
  f32 unknown48;                                  // Inferred role: height of the S_climbjump_base_02 locomotion; original member name unknown.
  f32 unknown4c;                                  // Inferred role: wall offset (asm appendix "wallOffset"); original member name unknown.
  f32 unknown50;                                  // Inferred role: height of the S_waterhole_01 locomotion; original member name unknown.
  f32 unknown54;                                  // Inferred role: unique idle space (asm appendix "uniqueIdleSpace"); original member name unknown.
  u8 _58[0x60 - 0x58];
  mm::Vec3 unknown60; // Role and original member name unknown.
  f32 unknown70;      // Inferred role: input power paired with the direction at 0x60 (auto run); original member name unknown.
  u8 _74[0x78 - 0x74];
  GF_OBJ_HANDLE *unknown78;                // Inferred role: object that sent the jump or warp notification, told about the skill action; original member name unknown.
  MsgPcFieldNotifyBigJump unknown80;       // Inferred role: big jump info; original member name unknown.
  MsgPcFieldNotifyWarp unknownc0;          // Inferred role: warp info; original member name unknown.
  MsgPcFieldNotifyWallJump unknown100;     // Inferred role: wall jump info; original member name unknown.
  EnviromentSensor::unknown003 unknown130; // Inferred role: climb wall info; original member name unknown.
};

static_assert(offsetof(GfPropertyField, unknown08) == 0x08, "");
static_assert(offsetof(GfPropertyField, unknown14) == 0x14, "");
static_assert(offsetof(GfPropertyField, unknown18) == 0x18, "");
static_assert(offsetof(GfPropertyField, unknown28) == 0x28, "");
static_assert(offsetof(GfPropertyField, unknown38) == 0x38, "");
static_assert(offsetof(GfPropertyField, unknown78) == 0x78, "");
static_assert(offsetof(GfPropertyField, unknown80) == 0x80, "");
static_assert(offsetof(GfPropertyField, unknownc0) == 0xc0, "");
static_assert(offsetof(GfPropertyField, unknown100) == 0x100, "");
static_assert(offsetof(GfPropertyField, unknown130) == 0x130, "");
static_assert(sizeof(GfPropertyField) == 0x160, "");

} // namespace pc
} // namespace gf
