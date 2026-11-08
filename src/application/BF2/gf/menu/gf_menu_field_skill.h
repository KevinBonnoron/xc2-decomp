#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "ai/ai_state_fsm.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

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

  static bool isInitialized();
  static bool isRunning();

  ai::Fsm unknown08; // Inferred role: state machine; original member name unknown.
  int unknown80;     // Role and original member name unknown.
  u8 _84[0x178 - 0x84];
  size_t unknown178; // Role and original member name unknown.
  u8 _180[0x1b8 - 0x180];
  u32 unknown1b8; // Role and original member name unknown.
  u8 _1bc[0x1f8 - 0x1bc];
  GfMenuCallContext *unknown1f8; // Inferred role: call context of the skip input; original member name unknown.
  GfMenuCallContext *unknown200; // Inferred role: call context of the result; original member name unknown.
  GfMenuCallContext *unknown208; // Inferred role: call context of the total info; original member name unknown.
  int unknown210;                // Role and original member name unknown.
  int unknown214;                // Role and original member name unknown.
  bool unknown218;               // Role and original member name unknown.
  u8 _219[0x220 - 0x219];
};

static_assert(offsetof(GfMenuFieldSkill, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuFieldSkill, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuFieldSkill, unknown178) == 0x178, "");
static_assert(offsetof(GfMenuFieldSkill, unknown1b8) == 0x1b8, "");
static_assert(offsetof(GfMenuFieldSkill, unknown1f8) == 0x1f8, "");
static_assert(offsetof(GfMenuFieldSkill, unknown200) == 0x200, "");
static_assert(offsetof(GfMenuFieldSkill, unknown208) == 0x208, "");
static_assert(offsetof(GfMenuFieldSkill, unknown210) == 0x210, "");
static_assert(offsetof(GfMenuFieldSkill, unknown214) == 0x214, "");
static_assert(offsetof(GfMenuFieldSkill, unknown218) == 0x218, "");
static_assert(sizeof(GfMenuFieldSkill) == 0x220, "");
static_assert(sizeof(GfMenuFieldSkill::StateSkip) == 0x20, "");
static_assert(sizeof(GfMenuFieldSkill::StateDispResult) == 0x20, "");
static_assert(sizeof(GfMenuFieldSkill::StateDispInfo) == 0x20, "");

} // namespace gf
