#pragma once
#include "event/i_manager.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"

namespace event {

class AgelogManager : public IManager, public mm::mtl::Singleton<AgelogManager> {
public:
  enum {
    FLAG_UNKNOWN_0 = 0, // Inferred role: reserve flag; original name unknown.
    FLAG_UNKNOWN_1 = 1, // Inferred role: active flag; original name unknown.
  };

  static const char *LOG_DIR; // Name given by the xc2 symbol _ZN5event13AgelogManager7LOG_DIRE.

  AgelogManager();
  virtual ~AgelogManager() {}
  void clear();
  void render();
  void reserve(bool isReserve);
  void start();
  void stop();
  virtual void OnEventProc(MSG_TYPE type);

  bool isReserved() const { return unknown10.test(FLAG_UNKNOWN_0) && !unknown10.test(FLAG_UNKNOWN_1); }

private:
  mm::mtl::unknown027<32> unknown10; // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<128> unknown14;    // Inferred role: path; original member name unknown.
};

static_assert(sizeof(AgelogManager) == 0x98, "");

} // namespace event
