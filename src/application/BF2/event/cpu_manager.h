#pragma once
#include "event/i_manager.h"
#include "ml/time_count.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CpuManager : public IManager, public mm::mtl::Singleton<CpuManager> {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: start flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: pause flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: pause home flag; original name unknown.
  };

  CpuManager();
  virtual ~CpuManager() {}
  void init();
  void end();
  void update();
  f32 calcCpuFrame() const;
  void tailAlways();
  void start();
  f32 getFrame() const;
  void pause(bool isPause);
  void pauseHome(bool isPause);
  virtual void OnEventProc(MSG_TYPE type);

private:
  bool isRunning() const { return (unknown10 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2)) == FLAG_UNKNOWN_0; }

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  u32 unknown10; // Inferred role: flags; original member name unknown.
  f32 m_frame;
  f32 unknown18;           // Inferred role: start frame; original member name unknown.
  f32 unknown1c;           // Inferred role: pause frame; original member name unknown.
  f32 unknown20;           // Inferred role: cpu frame; original member name unknown.
  ml::TimeCount unknown28; // Inferred role: time count; original member name unknown.
};

static_assert(sizeof(CpuManager) == 0x30, "");

} // namespace event
