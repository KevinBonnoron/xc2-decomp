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
    Player() : followIndex(0xffffffff), handle(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), isMainPc(true) {}

    u32 followIndex;
    GF_OBJ_HANDLE *handle;
    bool isMainPc;
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

  mm::Vec3 targetPositions[PLAYER_NUM];
  mm::Vec3 formationPositions[PLAYER_NUM];
  fw::Transform transforms[PLAYER_NUM];
  Player players[PLAYER_NUM];
  u32 formation;
  bool isMirror;
};

static_assert(offsetof(GfGamePlayerFormation, targetPositions) == 0x20, "");
static_assert(offsetof(GfGamePlayerFormation, formationPositions) == 0x80, "");
static_assert(offsetof(GfGamePlayerFormation, transforms) == 0xe0, "");
static_assert(offsetof(GfGamePlayerFormation, players) == 0x1a0, "");
static_assert(offsetof(GfGamePlayerFormation, formation) == 0x230, "");
static_assert(offsetof(GfGamePlayerFormation, isMirror) == 0x234, "");
static_assert(sizeof(GfGamePlayerFormation) == 0x240, "");

} // namespace gf
