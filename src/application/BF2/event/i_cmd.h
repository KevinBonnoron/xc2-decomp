#pragma once
#include <stddef.h>

#include "event/cmd_param.h"
#include "types.h"

namespace event {
class CmdVariable;

class ICmd {
public:
  enum RESULT {
    RESULT_WAIT,
    RESULT_END,
    RESULT_NEXT,
  };

  class Param {
  public:
    Param(const CmdParam &param, s32 frame) : unknown08(param), unknown118(frame) {}
    virtual ~Param() {}
    const CmdVariable &val(size_t index) const { return unknown08.val(index); }
    s32 getFrame() const { return unknown118; }

  private:
    CmdParam unknown08; // Inferred role: param; original member name unknown.
    s32 unknown118;     // Inferred role: frame; original member name unknown.
  };

  virtual ~ICmd() {}
  virtual void init() {}
  virtual RESULT update(const Param &param) = 0;
  virtual void term() {}
};

static_assert(sizeof(ICmd::Param) == 0x120, "");

} // namespace event
