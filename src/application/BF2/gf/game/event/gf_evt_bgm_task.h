#pragma once
#include <stddef.h>

#include "gf/game/event/gf_event_bgm_setup.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfEvtBgm;

// Task of the event bgm queue of GfEvtBgm (0x78..0x478, 128 pointers). Vtable layout (the vtables of EvtBgmTaskDelay 0x7101189610, EvtBgmTaskDelayStop
// 0x7101189658 and EvtBgmTaskVolume 0x71011896a0): destructors (the complete one is the empty EvtBgmTask::~EvtBgmTask, 0x7100307eec), isVolumeTask,
// isPlayTask, start, update, cancel. The game has no vtable symbol for EvtBgmTask itself and no body of start, update or cancel for it, which is what an
// abstract class gives: they are declared pure (the three derived classes override all of them).
class EvtBgmTask {
public:
  virtual ~EvtBgmTask() {}
  virtual bool isVolumeTask() const { return false; } // 0x7100307ec4
  virtual bool isPlayTask() const { return false; }   // 0x7100307ed8
  virtual void start(GfEvtBgm *bgm) = 0;
  virtual bool update(GfEvtBgm *bgm, const fw::UpdateInfo &info) = 0;
  virtual void cancel(GfEvtBgm *bgm) = 0;
};

class EvtBgmTaskVolume : public EvtBgmTask {
public:
  EvtBgmTaskVolume(const EventBgmSetup &setup);
  bool isVolumeTask() const override;
  void start(GfEvtBgm *bgm) override;
  bool update(GfEvtBgm *bgm, const fw::UpdateInfo &info) override;
  void cancel(GfEvtBgm *bgm) override;
  static EvtBgmTaskVolume *create(const EventBgmSetup &setup);

  f32 unknown08;  // Inferred role: seconds left; copy of EventBgmSetup::unknown48 (ldr/str at 0x7100307df4+8); original member name unknown.
  f32 unknown0c;  // Inferred role: target volume; copy of EventBgmSetup::m_playBgmVolume; original member name unknown.
  bool unknown10; // Inferred role: cancelled; set by cancel (strb at 0x7100307eb4), tested first by update; original member name unknown.
};

static_assert(offsetof(EvtBgmTaskVolume, unknown08) == 0x08, "");
static_assert(offsetof(EvtBgmTaskVolume, unknown10) == 0x10, "");
static_assert(sizeof(EvtBgmTaskVolume) == 0x18, ""); // operator new(0x18) in create, 0x7100307724

class EvtBgmTaskDelay : public EvtBgmTask {
public:
  EvtBgmTaskDelay(const EventBgmSetup &setup);
  bool isPlayTask() const override;
  void start(GfEvtBgm *bgm) override;
  bool update(GfEvtBgm *bgm, const fw::UpdateInfo &info) override;
  void cancel(GfEvtBgm *bgm) override;
  static EvtBgmTaskDelay *create(const EventBgmSetup &setup);

  EventBgmSetup m_eventBgmSetup; // Inferred role: setup to play; the constructor copies it the way the implicit EventBgmSetup copy does (name at 0x08, memcpy of 0x22 bytes at 0x4c); original member
                                 // name unknown.
  bool unknown70;                // Inferred role: cancelled; set by cancel (strb at 0x7100307c54), tested first by update; original member name unknown.
};

static_assert(offsetof(EvtBgmTaskDelay, m_eventBgmSetup) == 0x08, "");
static_assert(offsetof(EvtBgmTaskDelay, unknown70) == 0x70, "");
static_assert(sizeof(EvtBgmTaskDelay) == 0x78, ""); // operator new(0x78) in create, 0x71003074a0

class EvtBgmTaskDelayStop : public EvtBgmTask {
public:
  EvtBgmTaskDelayStop(const EventBgmSetup &setup);
  void start(GfEvtBgm *bgm) override;
  bool update(GfEvtBgm *bgm, const fw::UpdateInfo &info) override;
  void cancel(GfEvtBgm *bgm) override;
  static EvtBgmTaskDelayStop *create(const EventBgmSetup &setup);

  EventBgmSetup m_eventBgmSetup; // Inferred role: setup of the bgm to play after the stop; same copy as EvtBgmTaskDelay::m_eventBgmSetup; original member name unknown.
  f32 unknown70;                 // Inferred role: seconds left; copy of EventBgmSetup::unknown58 (create, 0x71003073f4); original member name unknown.
  bool unknown74;                // Inferred role: cancelled; set by cancel (strb at 0x7100307de8), tested first by update; original member name unknown.
};

static_assert(offsetof(EvtBgmTaskDelayStop, m_eventBgmSetup) == 0x08, "");
static_assert(offsetof(EvtBgmTaskDelayStop, unknown70) == 0x70, "");
static_assert(offsetof(EvtBgmTaskDelayStop, unknown74) == 0x74, "");
static_assert(sizeof(EvtBgmTaskDelayStop) == 0x78, ""); // operator new(0x78) in create, 0x71003073f4

} // namespace gf
