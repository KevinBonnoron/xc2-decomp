#pragma once
#include "framework/message/message_object.h"
#include "fw/fw_transform.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
class Reflection;
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

constexpr u32 PLAYER_ID_UNKNOWN_4294967295 = 0xffffffff; // Inferred role: player id none; original name unknown.

struct MsgPcFieldNotifyChangePlayerID : fw::Message {
  MsgPcFieldNotifyChangePlayerID(u32 playerId) : fw::Message(0x100001c, 0x20), playerId(playerId) {}

  u32 playerId;
};

struct FormationParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  // FormationParam::createReflection registers a 0x28 byte struct (five OffsetX/OffsetY float pairs), so the pairs are 8 bytes wide: not mm::Vec2.
  mm::Pnt<f32> offsets[5];
};

static_assert(sizeof(FormationParam) == 0x28, "");

struct WarpForRandomTalkParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 distVert;
  f32 distHorz;
};

const FormationParam *getFormationParam(u32 formation);
const WarpForRandomTalkParam *getWarpForRandomTalkParam();

class GfGamePlayerFormation : public mm::mtl::PtrSingleton<GfGamePlayerFormation>, public fw::MessageObject {
public:
  static const u32 PLAYER_UNKNOWN_6 = 6; // Inferred role: player num; original name unknown.

  // Inferred role: player; original type name unknown.
  struct unknown004 {
    unknown004() : unknown00(0xffffffff), unknown08(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown10(true) {}

    u32 unknown00;            // Inferred role: follow index; original member name unknown.
    GF_OBJ_HANDLE *unknown08; // Inferred role: handle; original member name unknown.
    bool unknown10;           // Inferred role: main pc; original member name unknown.
  };

  static void build(const GfSetupParam &param);
  void setup(const GfSetupParam &param);
  static void destroy();
  void cleanup();
  void update(const fw::UpdateInfo &info);
  void updateImpl(const fw::UpdateInfo &info);
  GfGamePlayerFormation();
  ~GfGamePlayerFormation();
  void calcTargetTransform(const fw::Transform &transform, u32 playerId, mm::Vec3 *position) const;
  bool stopPlayer(u32 playerId, const mm::Vec3 &position, f32 distance);
  const fw::Transform &getFollowTransform(u32 playerId) const;
  void swapFormation(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *otherHandle);
  u32 findPlayer(GF_OBJ_HANDLE *handle);
  void swapFormation(u32 playerId, u32 otherPlayerId);
  void drawDebug(u32 formation);
  void drawDebugRandomTalk();
  void changeFormation(u32 formation);
  bool isFarRandomTalk(GF_OBJ_HANDLE *handle);

  mm::Vec3 unknown20[PLAYER_UNKNOWN_6];      // Inferred role: target positions; original member name unknown.
  mm::Vec3 unknown80[PLAYER_UNKNOWN_6];      // Inferred role: formation positions; original member name unknown.
  fw::Transform unknowne0[PLAYER_UNKNOWN_6]; // Inferred role: transforms; original member name unknown.
  unknown004 unknown1a0[PLAYER_UNKNOWN_6];   // Inferred role: players; original member name unknown.
  u32 unknown230;                            // Inferred role: formation; original member name unknown.
  bool unknown234;                           // Inferred role: mirror; original member name unknown.
};

static_assert(offsetof(GfGamePlayerFormation, unknown20) == 0x20, "");
static_assert(offsetof(GfGamePlayerFormation, unknown80) == 0x80, "");
static_assert(offsetof(GfGamePlayerFormation, unknowne0) == 0xe0, "");
static_assert(offsetof(GfGamePlayerFormation, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GfGamePlayerFormation, unknown230) == 0x230, "");
static_assert(offsetof(GfGamePlayerFormation, unknown234) == 0x234, "");
static_assert(sizeof(GfGamePlayerFormation) == 0x240, "");

} // namespace gf
