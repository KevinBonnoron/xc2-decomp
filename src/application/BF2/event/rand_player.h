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
  Warp cmdWarp;
  Wait cmdWait;
  Reply cmdReply;
  Reset cmdReset;
  CmdQueue<QUEUE_COUNT, 0> queue;
  u32 flags;
};

static_assert(sizeof(RandPlayer) == 0x980, "");

} // namespace event
