#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "ai/ai_state_fsm.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace gf {

struct GfSetupParam;
class GfMenuCallContext;

class GfMenuFieldSkill : public mm::mtl::PtrSingleton<GfMenuFieldSkill> {
public:
  class StateIdle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateStart : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateWait : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateSkip : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void update(GfMenuFieldSkill *skill, const fw::UpdateInfo &info);

    int unknown18; // Inferred role: wait frames; original member name unknown.
  };

  class StateTotalNext : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateQuit : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateDispTotal : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfMenuFieldSkill *skill, ai::State *previous);
    void update(GfMenuFieldSkill *skill, const fw::UpdateInfo &info);
  };

  class StateDispResult : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void update(GfMenuFieldSkill *skill, const fw::UpdateInfo &info);

    bool unknown18; // Inferred role: closing; original member name unknown.
    f32 unknown1c;  // Inferred role: elapsed time; original member name unknown.
  };

  class StateDispInfo : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfMenuFieldSkill *skill, ai::State *previous);
    void update(GfMenuFieldSkill *skill, const fw::UpdateInfo &info);

    bool unknown18; // Inferred role: info opened; original member name unknown.
  };

  // Name from the game symbol gf::GfMenuFieldSkill::StartParam::operator=.
  struct StartParam {
    // Inferred role: element of unknown120; original type name unknown.
    struct unknown001 {
      u16 unknown00; // Inferred role: field skill id; original member name unknown.
      u16 unknown02; // Role and original member name unknown.
    };

    // Inferred role: element of unknown08; original type name unknown.
    struct unknown002 {
      u32 unknown00; // Inferred role: data object id; original member name unknown.
      u16 unknown04; // Inferred role: field skill id; original member name unknown.
      u8 unknown06;  // Inferred role: skill level; original member name unknown.
    };

    int unknown00;                                  // Role and original member name unknown.
    mm::mtl::FixedVector<unknown002, 30> unknown08; // Role and original member name unknown.
    u64 unknown100;                                 // Role and original member name unknown.
    u32 unknown108;                                 // Role and original member name unknown.
    u8 _10c[0x110 - 0x10c];
    u64 unknown110;                                 // Role and original member name unknown.
    u64 unknown118;                                 // Role and original member name unknown.
    mm::mtl::FixedVector<unknown001, 2> unknown120; // Role and original member name unknown.
    u32 unknown130;                                 // Role and original member name unknown.
  };

  explicit GfMenuFieldSkill(const GfSetupParam &param);
  ~GfMenuFieldSkill();
  static bool isDisp();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static bool start(const StartParam &param);
  static bool isRunning();
  static int getTotalSkillIndex(GfMenuFieldSkill *skill, u16 id);

  ai::Fsm unknown08;    // Inferred role: state machine; original member name unknown.
  StartParam unknown80; // Inferred role: start parameters; original member name unknown.
  u32 unknown1b8;       // Role and original member name unknown.
  u8 _1bc[0x1c8 - 0x1bc];
  mm::mtl::FixedVector<mm::mtl::ReferenceObject *, 5> unknown1c8; // Role and original member name unknown; released by destroy.
  GfMenuCallContext *unknown1f8;                                  // Inferred role: call context of the skip input; original member name unknown.
  GfMenuCallContext *unknown200;                                  // Inferred role: call context of the result; original member name unknown.
  GfMenuCallContext *unknown208;                                  // Inferred role: call context of the total info; original member name unknown.
  int unknown210;                                                 // Role and original member name unknown.
  int unknown214;                                                 // Role and original member name unknown.
  bool unknown218;                                                // Role and original member name unknown.
  u8 _219[0x220 - 0x219];
};

static_assert(offsetof(GfMenuFieldSkill, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuFieldSkill, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuFieldSkill, unknown1b8) == 0x1b8, "");
static_assert(offsetof(GfMenuFieldSkill, unknown1c8) == 0x1c8, "");
static_assert(offsetof(GfMenuFieldSkill, unknown1f8) == 0x1f8, "");
static_assert(offsetof(GfMenuFieldSkill, unknown200) == 0x200, "");
static_assert(offsetof(GfMenuFieldSkill, unknown208) == 0x208, "");
static_assert(offsetof(GfMenuFieldSkill, unknown210) == 0x210, "");
static_assert(offsetof(GfMenuFieldSkill, unknown214) == 0x214, "");
static_assert(offsetof(GfMenuFieldSkill, unknown218) == 0x218, "");
static_assert(offsetof(GfMenuFieldSkill::StartParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuFieldSkill::StartParam::unknown002, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuFieldSkill::StartParam::unknown002, unknown06) == 0x06, "");
static_assert(sizeof(GfMenuFieldSkill::StartParam::unknown002) == 0x08, "");
static_assert(offsetof(GfMenuFieldSkill::StartParam, unknown100) == 0x100, "");
static_assert(offsetof(GfMenuFieldSkill::StartParam, unknown120) == 0x120, "");
static_assert(offsetof(GfMenuFieldSkill::StartParam, unknown130) == 0x130, "");
static_assert(sizeof(GfMenuFieldSkill::StartParam) == 0x138, "");
static_assert(sizeof(GfMenuFieldSkill) == 0x220, "");
static_assert(sizeof(GfMenuFieldSkill::StateSkip) == 0x20, "");
static_assert(sizeof(GfMenuFieldSkill::StateDispResult) == 0x20, "");
static_assert(sizeof(GfMenuFieldSkill::StateDispInfo) == 0x20, "");

} // namespace gf
