#pragma once
#include "event/cmd_variable.h"
#include <stddef.h>

namespace event {

class CmdParam {
public:
  static constexpr size_t VARIABLE_COUNT = 11;

  CmdParam();
  virtual ~CmdParam() {}
  void clear();
  CmdVariable &val(size_t index);
  const CmdVariable &val(size_t index) const;

private:
  CmdVariable mVariables[VARIABLE_COUNT];
};

static_assert(sizeof(CmdParam) == 0x110, "");

} // namespace event
