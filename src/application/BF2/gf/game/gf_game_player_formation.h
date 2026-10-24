#pragma once
#include "framework/message/message_object.h"
#include "fw/fw_transform.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

constexpr u32 PLAYER_ID_NONE = 0xffffffff;

struct MsgPcFieldNotifyChangePlayerID : fw::Message {
  MsgPcFieldNotifyChangePlayerID(u32 playerId) : fw::Message(0x100001c, 0x20), playerId(playerId) {}

  u32 playerId;
};

struct FormationParam {
  mm::Vec2 offsets[5];
};

struct WarpForRandomTalkParam {
  f32 height;
  f32 distance;
};

const FormationParam *getFormationParam(u32 formation);
const WarpForRandomTalkParam *getWarpForRandomTalkParam();

class GfGamePlayerFormation : public mm::mtl::PtrSingleton<GfGamePlayerFormation>, public fw::MessageObject {
public:
  static const u32 PLAYER_NUM = 6;

  struct Player {
    Player() : unknown00(0xffffffff), unknown08(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown10(true) {}

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

  mm::Vec3 unknown20[PLAYER_NUM];      // Inferred role: target positions; original member name unknown.
  mm::Vec3 unknown80[PLAYER_NUM];      // Inferred role: formation positions; original member name unknown.
  fw::Transform unknowne0[PLAYER_NUM]; // Inferred role: transforms; original member name unknown.
  Player unknown1a0[PLAYER_NUM];       // Inferred role: players; original member name unknown.
  u32 unknown230;                      // Inferred role: formation; original member name unknown.
  bool unknown234;                     // Inferred role: mirror; original member name unknown.
};

static_assert(offsetof(GfGamePlayerFormation, unknown20) == 0x20, "");
static_assert(offsetof(GfGamePlayerFormation, unknown80) == 0x80, "");
static_assert(offsetof(GfGamePlayerFormation, unknowne0) == 0xe0, "");
static_assert(offsetof(GfGamePlayerFormation, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GfGamePlayerFormation, unknown230) == 0x230, "");
static_assert(offsetof(GfGamePlayerFormation, unknown234) == 0x234, "");
static_assert(sizeof(GfGamePlayerFormation) == 0x240, "");

} // namespace gf
