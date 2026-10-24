#pragma once
#include <stddef.h>

#include "event/cmd_queue.h"
#include "event/i_cmd.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace event {

class ShakerUpdater {
public:
  static constexpr size_t CMD_COUNT = 8;

  class Update : public ICmd {
  public:
    virtual ~Update() {}
    virtual RESULT update(const Param &param);
  };

  ShakerUpdater();
  void clear();
  void update();
  void reserve(const mm::Vec3 &pos, const mm::Vec3 &rot);

private:
  Update unknown00;                 // Inferred role: cmd; original member name unknown.
  CmdQueue<CMD_COUNT, 0> unknown08; // Inferred role: queue; original member name unknown.
};

static_assert(sizeof(ShakerUpdater) == 0x958, "");

} // namespace event
