#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class AgelogManager : public IManager, public mm::mtl::Singleton<AgelogManager> {
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

  bool isReserved() const { return (unknown10 & (FLAG_RESERVE | FLAG_ACTIVE)) == FLAG_RESERVE; }

private:
  u32 unknown10;                  // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<128> unknown14; // Inferred role: path; original member name unknown.
};

static_assert(sizeof(AgelogManager) == 0x98, "");

} // namespace event
