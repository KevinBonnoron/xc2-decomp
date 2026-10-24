#pragma once
#include "event/i_manager.h"
#include "event/rand_player.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class RandManager : public IManager, public mm::mtl::Singleton<RandManager> {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_WARP = 1 << 1,
  };

  RandManager();
  virtual ~RandManager() {}
  void clear();
  void update();
  virtual void OnEventProc(MSG_TYPE type);
  bool play(int id);

private:
  u32 unknown10;        // Inferred role: flags; original member name unknown.
  RandPlayer unknown18; // Inferred role: player; original member name unknown.
};

static_assert(sizeof(RandManager) == 0x998, "");

} // namespace event
