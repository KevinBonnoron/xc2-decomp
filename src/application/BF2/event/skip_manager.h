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

  SkipManager();
  virtual ~SkipManager();
  bool isSkip() const { return (flags & FLAG_SKIP) != 0; }
  bool isSkipFast() const {
    if (flags & FLAG_SKIP_FAST_ENABLE) {
      if (mm::mtl::Singleton<DebugManager>::getPtr()->isFastSkipDisable() && !mm::mtl::Singleton<DebugManager>::getPtr()->isFastSkipEnableOneTime()) {
        return false;
      }
      if (isSkip()) {
        return true;
      }
    }
    return false;
  }
  f32 getEndFrame() const {
    if (!isSkip()) {
      return 0.0f;
    }
    return mSkipFrame < 0.0f ? DEFAULT_END_FRAME : mSkipFrame;
  }
  void clear();
  void update();
  void render();
  void tail();
  void setSkipVolume(bool isSkipVolume);
  bool isSkipVolume() const;
  void setSkipFastEnable(bool isEnable);
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  u32 mSkipState;
  f32 mSkipFrame;
};

static_assert(sizeof(SkipManager) == 0x20, "");

} // namespace event
