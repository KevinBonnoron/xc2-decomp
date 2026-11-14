#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class EvtxtManager : public IManager, public mm::mtl::Singleton<EvtxtManager> {
public:
  static const char *EVTXT_PATH; // Name given by the xc2 symbol _ZN5event12EvtxtManager10EVTXT_PATHE.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: reserve flag; original name unknown.
  };

  EvtxtManager();
  virtual ~EvtxtManager() {}
  void render();
  void write();
  void reserve(bool isReserve);
  bool isReserve() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10; // Inferred role: flags; original member name unknown.
};

static_assert(sizeof(EvtxtManager) == 0x18, "");

} // namespace event
