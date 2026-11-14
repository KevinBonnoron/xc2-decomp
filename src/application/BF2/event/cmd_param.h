#pragma once
#include "event/cmd_variable.h"
#include <stddef.h>

namespace event {

class CmdParam {
public:
  static constexpr size_t VARIABLE_UNKNOWN_11 = 11; // Inferred role: variable count; original name unknown.

  CmdParam();
  virtual ~CmdParam() {}
  void clear();
  CmdVariable &val(size_t index);
  const CmdVariable &val(size_t index) const;

private:
  CmdVariable unknown08[VARIABLE_UNKNOWN_11]; // Inferred role: variables; original member name unknown.
};

static_assert(sizeof(CmdParam) == 0x110, "");

} // namespace event
