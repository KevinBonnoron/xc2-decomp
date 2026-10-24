#pragma once
#include "event/debug_manager.h"
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class SkipManager : public IManager, public mm::mtl::Singleton<SkipManager> {
public:
  static constexpr f32 DEFAULT_END_FRAME = 99999.0f;

  enum {
    FLAG_SKIP = 1 << 0,
    FLAG_SKIP_VOLUME = 1 << 1,
    FLAG_SKIP_FAST_ENABLE = 1 << 2,
  };

  bool isSkipFast() const {
    if (unknown10 & FLAG_SKIP_FAST_ENABLE) {
      if (mm::mtl::Singleton<DebugManager>::getPtr()->isFastSkipDisable() && !mm::mtl::Singleton<DebugManager>::getPtr()->isFastSkipEnableOneTime()) {
        return false;
      }
      if (isSkip()) {
        return true;
      }
    }
    return false;
  }
  bool isSkip() const;
  void skip(bool isSkip, f32 frame);
  void setSkipVolume(bool isSkipVolume);
  f32 getEndFrame() const;
  SkipManager();
  virtual ~SkipManager();
  void clear();
  void update();
  void render();
  void tail();
  bool isSkipVolume() const;
  void setSkipFastEnable(bool isEnable);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10; // Inferred role: flags; original member name unknown.
  u32 unknown14; // Inferred role: skip state; original member name unknown.
  f32 unknown18; // Inferred role: skip frame; original member name unknown.
};

static_assert(sizeof(SkipManager) == 0x20, "");

} // namespace event
