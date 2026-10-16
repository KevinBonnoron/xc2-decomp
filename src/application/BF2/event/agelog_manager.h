#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/noncopyable.h"
#include "types.h"

namespace event {

class AgelogManager : public IManager, public mm::mtl::NoncopyableBase {
public:
  enum {
    FLAG_RESERVE = 1 << 0,
    FLAG_ACTIVE = 1 << 1,
  };

  static const char *LOG_DIR;

  AgelogManager();
  virtual ~AgelogManager() {}
  void clear();
  void render();
  void reserve(bool isReserve);
  void start();
  void stop();
  virtual void OnEventProc(MSG_TYPE type);

  bool isReserved() const { return (flags & (FLAG_RESERVE | FLAG_ACTIVE)) == FLAG_RESERVE; }

private:
  u32 flags;
  mm::mtl::FixStr<128> path;
};

static_assert(sizeof(AgelogManager) == 0x98, "");

} // namespace event
