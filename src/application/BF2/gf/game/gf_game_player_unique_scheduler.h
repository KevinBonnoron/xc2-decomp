#pragma once
#include "framework/message/message_object.h"
#include "fw/fw_param_manager.h"
#include "gf/data/gf_bdat_unique_motion.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
struct UniqueMotionParam;

struct MsgPcFieldSetUniqueMotion : fw::Message {
  MsgPcFieldSetUniqueMotion(u32 motion) : fw::Message(0x1000022, 0x40), motion(motion), _0c() {}

  u32 motion;
  u8 _0c[0x0d - 0x0c];
};

class GfGamePlayerUniqueScheduler : public mm::mtl::PtrSingleton<GfGamePlayerUniqueScheduler>, public IGfEvent, public fw::MessageObject {
public:
  static const u32 UNIT_NUM = 6;

  enum UNIT_STATE {
    UNIT_STATE_NONE,
    UNIT_STATE_READY,
    UNIT_STATE_REQUEST = 3,
  };

  struct Unit {
    Unit() : handle(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), bdatId(0), state(UNIT_STATE_NONE), motion(0), timer(0.0f) {}

    GF_OBJ_HANDLE *handle;
    u16 bdatId;
    UNIT_STATE state;
    u16 motion;
    f32 timer;
  };

  static void build(const GfSetupParam &param);
  void setup();
  static void destroy();
  void cleanup();
  static void update(const fw::UpdateInfo &info);
  void executeRequest(const fw::UpdateInfo &info);
  void judge(const fw::UpdateInfo &info);
  static void onReload();
  void rebuildPreset();
  GfGamePlayerUniqueScheduler();
  ~GfGamePlayerUniqueScheduler();
  const UniqueMotionParam *getParam() const;
  void gevPartyMemberOK(bool isOK) override;
  void gevBattleStart() override;

  f32 elapsedTime;
  Unit units[UNIT_NUM];
  mm::mtl::FixedQueue<const GfBdatUniqueMotion::PresetInfo *, 32> presets;
  mm::mtl::IntrusivePtr<fw::ParamList> paramList;
};

static_assert(offsetof(GfGamePlayerUniqueScheduler, elapsedTime) == 0x28, "");
static_assert(offsetof(GfGamePlayerUniqueScheduler, units) == 0x30, "");
static_assert(offsetof(GfGamePlayerUniqueScheduler, presets) == 0xc0, "");
static_assert(offsetof(GfGamePlayerUniqueScheduler, paramList) == 0x1d0, "");
static_assert(sizeof(GfGamePlayerUniqueScheduler) == 0x1d8, "");

} // namespace gf
