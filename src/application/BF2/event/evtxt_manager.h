#pragma once
#include "event/i_manager.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class EvtxtManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  static const char *EVTXT_PATH;

  enum {
    FLAG_RESERVE = 1 << 0,
  };

  EvtxtManager();
  virtual ~EvtxtManager() {}
  void render();
  void write();
  void reserve(bool isReserve);
  bool isReserve() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 flags;
};

static_assert(sizeof(EvtxtManager) == 0x18, "");

} // namespace event
