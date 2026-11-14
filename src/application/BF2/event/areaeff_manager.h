#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class AreaeffManager : public IManager, public mm::mtl::Singleton<AreaeffManager> {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: hide light flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: sleep light flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: disable light flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: hide se flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: pause flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: disable se flag; original name unknown.
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
    bool isOn(u32 flag) const { return (unknown00 & flag) != 0; }

    void set(u32 flag, bool isSet) {
      if (isSet) {
        unknown00 |= flag;
      } else {
        unknown00 &= ~flag;
      }
    }

    u32 unknown00; // Inferred role: bits; original member name unknown.
  };

  Flags unknown10; // Inferred role: flags; original member name unknown.
  f32 unknown14;   // Inferred role: sleep time; original member name unknown.
};

static_assert(sizeof(AreaeffManager) == 0x18, "");

} // namespace event
