#pragma once
#include "event/cmd_param.h"
#include "types.h"

namespace event {

class ICmd;

class CmdItem {
public:
  CmdItem(ICmd *cmd, const CmdParam &param) : unknown08(cmd), unknown10(param), unknown120(0), unknown124(0) {}
  virtual ~CmdItem() {}

  ICmd *unknown08;    // Inferred role: cmd; original member name unknown.
  CmdParam unknown10; // Inferred role: param; original member name unknown.
  s32 unknown120;     // Inferred role: frame; original member name unknown.
  s16 unknown124;     // Inferred role: wait frame; original member name unknown.
};

static_assert(sizeof(CmdItem) == 0x128, "");

} // namespace event
