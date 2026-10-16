#pragma once
#include "event/i_manager.h"
#include "ml/time_count.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class CpuManager : public IManager, public mm::mtl::NoncopyableBase {
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
  bool isRunning() const { return (flags & (FLAG_START | FLAG_PAUSE | FLAG_PAUSE_HOME)) == FLAG_START; }

  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  u32 flags;
  f32 frame;
  f32 mStartFrame;
  f32 mPauseFrame;
  f32 mCpuFrame;
  ml::TimeCount mTimeCount;
};

static_assert(sizeof(CpuManager) == 0x30, "");

} // namespace event
