#pragma once
#include <stddef.h>

#include "event/cmd_queue.h"
#include "event/i_cmd.h"
#include "types.h"

namespace event {

class RandPlayer {
public:
  static constexpr size_t QUEUE_COUNT = 8;

  enum {
    FLAG_PLAY = 1 << 0,
  };

  class Warp : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class Wait : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class Reply : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class Reset : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  RandPlayer();
  virtual ~RandPlayer() {}
  void clear();
  void update();
  void play(int id, bool isWarp);
  bool isPlaying() const;

private:
  Warp unknown08;                     // Inferred role: cmd warp; original member name unknown.
  Wait unknown10;                     // Inferred role: cmd wait; original member name unknown.
  Reply unknown18;                    // Inferred role: cmd reply; original member name unknown.
  Reset unknown20;                    // Inferred role: cmd reset; original member name unknown.
  CmdQueue<QUEUE_COUNT, 0> unknown28; // Inferred role: queue; original member name unknown.
  u32 unknown978;                     // Inferred role: flags; original member name unknown.
};

static_assert(sizeof(RandPlayer) == 0x980, "");

} // namespace event
