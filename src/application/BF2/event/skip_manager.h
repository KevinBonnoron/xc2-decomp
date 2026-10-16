#pragma once
#include "event/i_manager.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class SkipManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  enum {
    FLAG_SKIP = 1 << 0,
  };

  SkipManager();
  virtual ~SkipManager();
  bool isSkip() const { return (flags & FLAG_SKIP) != 0; }
  bool isSkipFast() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
  u32 mSkipState;
  f32 mSkipFrame;
};

static_assert(sizeof(SkipManager) == 0x20, "");

} // namespace event
