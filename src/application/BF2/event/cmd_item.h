#pragma once
#include "event/cmd_param.h"
#include "types.h"

namespace event {

class ICmd;

class CmdItem {
public:
  CmdItem(ICmd *cmd, const CmdParam &param) : mCmd(cmd), mParam(param), frame(0), mWaitFrame(0) {}
  virtual ~CmdItem() {}

  ICmd *mCmd;
  CmdParam mParam;
  s32 frame;
  s16 mWaitFrame;
};

static_assert(sizeof(CmdItem) == 0x128, "");

} // namespace event
