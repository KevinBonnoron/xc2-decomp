#pragma once
#include "event/i_manager.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class MercenariesManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  MercenariesManager();
  virtual ~MercenariesManager() {}
  void clear();
  virtual void OnEventProc(MSG_TYPE type);
  void entryable(u32 mission);
  void finish(u32 mission);
  u32 getState(u32 mission);
};

static_assert(sizeof(MercenariesManager) == 0x10, "");

} // namespace event
