#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class CharaPlayTalk : public ICmd {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
    FLAG_MANUAL = 1 << 3,
  };

  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

  bool isManual() const { return (flags & FLAG_MANUAL) != 0; }

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  u8 _18[0x78 - 0x18];
};

static_assert(sizeof(CharaPlayTalk) == 0x78, "");

} // namespace event
