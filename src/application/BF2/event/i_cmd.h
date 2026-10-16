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
    Param(const CmdParam &param, s32 frame) : mParam(param), frame(frame) {}
    virtual ~Param() {}
    const CmdVariable &val(size_t index) const { return mParam.val(index); }
    s32 getFrame() const { return frame; }

  private:
    CmdParam mParam;
    s32 frame;
  };

  virtual ~ICmd() {}
  virtual void init() {}
  virtual RESULT update(const Param &param) = 0;
  virtual void term() {}
};

static_assert(sizeof(ICmd::Param) == 0x120, "");

} // namespace event
