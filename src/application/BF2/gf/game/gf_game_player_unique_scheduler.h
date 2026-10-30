#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/data/gf_bdat_unique_motion.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
class ParamList;
} // namespace fw

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

  // Inferred role: unit; original type name unknown.
  struct unknown001 {
    unknown001() : unknown00(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown08(0), unknown0c(UNIT_STATE_NONE), unknown10(0), unknown14(0.0f) {}

    GF_OBJ_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
    u16 unknown08;            // Inferred role: bdat id; original member name unknown.
    UNIT_STATE unknown0c;     // Inferred role: state; original member name unknown.
    u16 unknown10;            // Inferred role: motion; original member name unknown.
    f32 unknown14;            // Inferred role: timer; original member name unknown.
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

  f32 unknown28;                                                             // Inferred role: elapsed time; original member name unknown.
  unknown001 unknown30[UNIT_NUM];                                            // Inferred role: units; original member name unknown.
  mm::mtl::FixedQueue<const GfBdatUniqueMotion::PresetInfo *, 32> unknownc0; // Inferred role: presets; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ParamList> unknown1d0;                           // Inferred role: param list; original member name unknown.
};

static_assert(offsetof(GfGamePlayerUniqueScheduler, unknown28) == 0x28, "");
static_assert(offsetof(GfGamePlayerUniqueScheduler, unknown30) == 0x30, "");
static_assert(offsetof(GfGamePlayerUniqueScheduler, unknownc0) == 0xc0, "");
static_assert(offsetof(GfGamePlayerUniqueScheduler, unknown1d0) == 0x1d0, "");
static_assert(sizeof(GfGamePlayerUniqueScheduler) == 0x1d8, "");

} // namespace gf
