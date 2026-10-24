#pragma once
#include "event/i_manager.h"
#include "ml/time_count.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CpuManager : public IManager, public mm::mtl::Singleton<CpuManager> {
public:
  enum {
    FLAG_START = 1 << 0,
    FLAG_PAUSE = 1 << 1,
    FLAG_PAUSE_HOME = 1 << 2,
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
  bool isRunning() const { return (unknown10 & (FLAG_START | FLAG_PAUSE | FLAG_PAUSE_HOME)) == FLAG_START; }

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
