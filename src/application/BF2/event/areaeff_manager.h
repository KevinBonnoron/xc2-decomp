#pragma once
#include "event/i_manager.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class AreaeffManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  enum {
    FLAG_HIDE_LIGHT = 1 << 0,
    FLAG_SLEEP_LIGHT = 1 << 1,
    FLAG_DISABLE_LIGHT = 1 << 2,
    FLAG_HIDE_SE = 1 << 3,
    FLAG_PAUSE = 1 << 4,
    FLAG_DISABLE_SE = 1 << 5,
  };

  AreaeffManager();
  virtual ~AreaeffManager() {}
  virtual void clear();
  virtual void exec(f32 deltaFrame);
  void updateDisable();
  virtual void pause(bool isPause);
  void setup();
  void start();
  void setDispLight(bool isDisp);
  void sleepLight(bool isSleep, f32 sleepTime);
  void setDispSe(bool isDisp);

private:
  struct Flags {
    bool isOn(u32 flag) const { return (bits & flag) != 0; }

    void set(u32 flag, bool isSet) {
      if (isSet) {
        bits |= flag;
      } else {
        bits &= ~flag;
      }
    }

    u32 bits;
  };

  Flags flags;
  f32 mSleepTime;
};

static_assert(sizeof(AreaeffManager) == 0x18, "");

} // namespace event
